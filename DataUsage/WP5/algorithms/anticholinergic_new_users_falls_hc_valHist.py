#%%
# LOAD ALL LIBRARIES
import warnings
warnings.filterwarnings("ignore")
import pandas as pd
import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from econml.dr import DRLearner
from econml.dml import DML, CausalForestDML
from econml.metalearners import XLearner
from econml.cate_interpreter import SingleTreeCateInterpreter
from sklift.viz import plot_uplift_curve
from sklift.metrics import uplift_by_percentile, uplift_auc_score
from sklearn.model_selection import train_test_split, KFold
from sklearn.linear_model import LinearRegression, LogisticRegression, LassoCV
from sklearn.ensemble import GradientBoostingRegressor, GradientBoostingClassifier, RandomForestRegressor, RandomForestClassifier
from sklearn.metrics import roc_auc_score
import scipy.stats as st
import random
import shap 
from utils_ml import rank_variables
from utils_form_groups import select_variables_ps


#%%
# SET PATHS
data_save_dir = "path_to_source_data" # all data files
presentation_dir = "path_to_result_folder"

#%%
# READ DATA FROM DISK (TRAIN & TEST DATA FILES)
X_orig_train = pd.read_pickle(data_save_dir+'data_hist_train_ach_new_users_hc.pki')
X_orig_test = pd.read_pickle(data_save_dir+'data_hist_test_ach_new_users_hc.pki')
X_train = pd.read_pickle(data_save_dir+'data_hist_train_norm_ach_new_users_hc.pki')
X_test = pd.read_pickle(data_save_dir+'data_hist_test_norm_ach_new_users_hc.pki')


#%%
# HELPER FUNCTIONS

def elast(data, y, t):
        return (np.sum((data[t] - data[t].mean())*(data[y] - data[y].mean())) /
                np.sum((data[t] - data[t].mean())**2))

def cumulative_gain(dataset, prediction, y, t, min_periods=30, steps=100):
    size = dataset.shape[0]
    ordered_df = dataset.sort_values(prediction, ascending=False).reset_index(drop=True)
    n_rows = list(range(min_periods, size, size // steps)) + [size]
    ## add (rows/size) as a normalizer. 
    return np.array([elast(ordered_df.head(rows), y, t) * (rows/size) for rows in n_rows])


# C-FOR-BENEFITS function
def c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c):

    df_c_for_benefit = pd.DataFrame()
    df_c_for_benefit['predicted_benefit_t'] = predicted_benefit_t
    df_c_for_benefit['observed_outcome_t'] = observed_outcome_t
    df_c_for_benefit['predicted_benefit_c'] = predicted_benefit_c
    df_c_for_benefit['observed_outcome_c'] = observed_outcome_c
    df_c_for_benefit['predicted_benefit'] = (df_c_for_benefit['predicted_benefit_t'] + df_c_for_benefit['predicted_benefit_c']) / 2
    df_c_for_benefit['observed_benefit'] = df_c_for_benefit['observed_outcome_t'] - df_c_for_benefit['observed_outcome_c']

    result_vector_all = []
    for b in range (len(df_c_for_benefit)):
        result_vector = []
        for a in range (len(df_c_for_benefit)):
            if (b>a):
                if ((df_c_for_benefit['predicted_benefit'][a])<=(df_c_for_benefit['predicted_benefit'][b])):
                    if ((df_c_for_benefit['observed_benefit'][a])<(df_c_for_benefit['observed_benefit'][b])):
                        result_vector.append('c')
                    if ((df_c_for_benefit['observed_benefit'][a])>(df_c_for_benefit['observed_benefit'][b])):
                        result_vector.append('d')
                    if ((df_c_for_benefit['observed_benefit'][a])==(df_c_for_benefit['observed_benefit'][b])):
                        result_vector.append('u')
                elif ((df_c_for_benefit['predicted_benefit'][a])>(df_c_for_benefit['predicted_benefit'][b])):
                    if ((df_c_for_benefit['observed_benefit'][a])>(df_c_for_benefit['observed_benefit'][b])):
                        result_vector.append('c')
                    if ((df_c_for_benefit['observed_benefit'][a])<(df_c_for_benefit['observed_benefit'][b])):
                        result_vector.append('d')
                    if ((df_c_for_benefit['observed_benefit'][a])==(df_c_for_benefit['observed_benefit'][b])):
                        result_vector.append('u')
                else:
                    result_vector.append(0)
            else:
                result_vector.append(0)
        result_vector_all = result_vector_all + result_vector
        df_c_for_benefit[str(b)] = result_vector


    return result_vector_all, df_c_for_benefit

def matching_te(X_t, X_c):
    
    df_treatment_matched = []
    df_control_matched = []

    caliper = X_t['te'].std()*0.1 # caliper 20% of stdev

    df_treatment = X_t
    df_control = X_c

    # Find the most similar te pairs from the treatment and control customers
    df_treatment_matched = pd.DataFrame()
    df_control_matched = pd.DataFrame()

    for k in range (len(X_t)):
        df_treatment_te = df_treatment['te'][k]
        df_control['te_diff'] = abs(df_control['te'] - (df_treatment_te))
        df_control = df_control.sort_values(by=['te_diff']).reset_index(drop=True)

        if (df_control[0:1]['te_diff'][0] < caliper):
            df_treatment_matched = df_treatment_matched.append([df_treatment[k:k+1]])
            df_control_matched = df_control_matched.append([df_control[0:1]])
            df_control = df_control[1:].reset_index(drop=True) # drop selected control (without replacement)

    df_treatment_matched = df_treatment_matched.reset_index(drop=True)
    df_control_matched = df_control_matched.reset_index(drop=True)

    return df_treatment_matched, df_control_matched


# Ground truth CATE approximation based metrics
# Matching approach [Rolling and Yang 2013] <- "Emprical Analysis of Model selection for heterogeneous Causal effect estimationms"
def tau_error_matching(X_t, X_c, y_t, y_c, tau_t, vars_matching):
    from sklearn.neighbors import NearestNeighbors
    from utils_ml import replace_missing_as_med

    #X_t, missing = replace_missing_as_med(X_t[vars_matching])  # replace missing values
    #X_c, missing = replace_missing_as_med(X_c[vars_matching]) 

    X_t = X_t[vars_matching].reset_index(drop=True)
    X_c = X_c[vars_matching].reset_index(drop=True)

    X_t=(X_t-X_t.mean())/(X_t.std()+0.000001).astype(float)  # normalize X
    X_c=(X_c-X_c.mean())/(X_c.std()+0.000001).astype(float)  # normalize X

    knn = NearestNeighbors(n_neighbors=len(X_c)).fit(X_c[vars_matching])
    distances, indices = knn.kneighbors(X_t[vars_matching])

    matched = []
    pairs = []
    a=0
    b=0
    distance_set = []
    for indexA, candidatesB in enumerate(indices):
        #print (indexA)
        personA = X_t.index[indexA]
        for indexB in candidatesB:
            dist = distances[a][b]
            if indexB not in matched:
                matched.append(indexB)
                personB = X_c.index[indexB]
                pairs.append([personA, personB])
                break
            b=b+1
        distance_set.append(dist)
        
        a=a+1
    matches = pd.DataFrame(pairs, columns=['SetA', 'SetB'])
    matches['distance'] = distance_set

    df_data = pd.DataFrame()
    df_data['y_t'] = y_t.iloc[matches['SetA'].tolist()].reset_index(drop=True).astype(float)
    df_data['y_c'] = y_c.iloc[matches['SetB'].tolist()].reset_index(drop=True).astype(float)
    df_data['tau_match'] = df_data['y_t']-df_data['y_c']
    df_data['tau_est'] = tau_t
    df_data['tau_error_sqr'] = np.power(df_data['tau_est']-df_data['tau_match'],2)
    match_error = df_data['tau_error_sqr'].sum()/len(df_data)

    return df_data, match_error


def mean_confidence_interval(data, confidence=0.95):
    import numpy as np
    import scipy.stats
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n-1)
    return m, m-h, m+h


#%%

###############################################################
#   - Falls
#####################################################


seed = 12

outcome = 'K5_bin_target' # falls

#%%
# DATA-DRIVEN FEATURE IMPORTANCE VALUES

variables_sel_manual, variables_sel_manual_names = select_variables_ps(variables = 'ate_variables_anticholinergic')
variables_sel_manual.remove('HT_NRO')
variables_sel_manual_names.remove('HT_NRO')

test_set_size = 5000 # Test set size
n_iterations = 10 # Number of iterations

variables_uni_best_y = []
variables_uni_best_T = []

df_univariate_results = pd.DataFrame()
df_univariate_results['code'] = variables_sel_manual
df_univariate_results['names'] = variables_sel_manual_names

X = X_test[variables_sel_manual]
y = X_test[outcome]
T = X_test['T']

# Feature importances for predicting outcome
variables_best_y, df_univariate_results_y = rank_variables(X, y.astype(int), variables_sel_manual, variables_sel_manual_names, test_set_size, n_iterations)
variables_uni_best_y.append(variables_best_y[0])#
df_univariate_results['AUC_'+outcome] = df_univariate_results_y['AUC']
df_univariate_results['coef_'+outcome] = df_univariate_results_y['coef']

# Feature importances for predicting treatment
variables_best_T, df_univariate_results_T = rank_variables(X, T, variables_sel_manual, variables_sel_manual_names, test_set_size, n_iterations)
variables_uni_best_T.append(variables_best_T[0])
df_univariate_results['AUC_T'] = df_univariate_results_T['AUC']
df_univariate_results['coef_T'] = df_univariate_results_T['coef']

# save data
df_univariate_results.to_csv(presentation_dir+'/data/feature_importance_univariate_y_and_T_'+outcome+'.csv')



#%%
# Expert opinion confounder selection (Daniela, Rosa, 8.1.2024)

confounders = [
'IKA', # Age
'BB1', # Gender
'sBMI_hc', # BMI
'K5', # Number of times fell in last 90 days
'unsteady_gait_or_falls', # 'Unsteady gait or falls' #, Unsteady gait
'pain_scale', #combined item "Frequency with which client complains or shows evidence of pain" or "From clients point of view, pain intensity disrupts usual activities")
'hilmo_hospital_visits_last6months', # Hospital visits, last 6 months (HILMO)
'unplanned_hospital_ER_visit', # ER visits, last 6 months (HILMO)….rather combined item "9 or 18 or 27"
'numberOfMeds', # Number of drugs
'numberOfComorbidities', # Number of comorbidities
'H2C_6cat', # Primary modes of locomotion - Indoors
'atc_antidepressants_SSRI_v2', # combined variable for any antidepressant
'atc_antipsychotics', #antipsychotics
'painmed_or_analgesics', # Pain medications or analgesics
'atc_hypnotics_and_sedatives', # Hypno-sedative medications (seems better than all psychotropics)
'SADLLF_hc', #ADL long (mobility i bed, locomotion, dressing upper and lower body included in ADL long)
'CPS_3', # CPS3+
'K3C', #Dizziness or lightheadedness
'J1E', #Irregular pulse
'problems_because_of_drinking', # drink too much or problems with alcohol (combined item "87 or 105")
]

confounders_name = [
'Age',
'Gender',
'BMI',
'Number of times fell in last 90 days',
'Unsteady gait or falls', #, Unsteady gait
'Pain scale', #combined item "Frequency with which client complains or shows evidence of pain" or "From clients point of view, pain intensity disrupts usual activities")
'Hospital visits',
'Unplanned hospital or ER visit',
'Number of drugs',
'Number of comorbidities',
'Primary modes of locomotion - Indoors',
'Antidepressants',
'Antipsychotics',
'Pain medications or analgesics',
'Hypno-sedative medications',
'ADL Long',
'CPS3',
'Dizziness or lightheadedness',
'Irregular pulse',
'Problems because of drinking',
]


confounders_name_short = [
'Age',
'Gender',
'BMI',
'Number of times fell in last 90 days',
'Unsteady gait or falls', #, Unsteady gait
'Pain scale', #combined item "Frequency with which client complains or shows evidence of pain" or "From clients point of view, pain intensity disrupts usual activities")
'Hospital visits, last 6 months',
'Unplanned hospital or ER visit',
'Number of drugs',
'Number of comorbidities',
'Primary modes of locomotion - Indoors',
'Antidepressants',
'Antipsychotics',
'Pain medications or analgesics',
'Hypno-sedative medications',
'ADL Long',
'CPS3',
'Dizziness or lightheadedness',
'Irregular pulse',
'Problems because of drinking',
]




#%%
# STATISTICS: MEANS OF TRAIN AND TEST DATA

def calc_desc_stats(df, variables_sel, variables_sel_names):
    variable_groups=[]
    stats_all=[]
    stats_treated=[]
    stats_control = []
    stats_smd0 = []

    variable_groups.append(' ')
    stats_all.append(len(df))
    stats_treated.append(len(df[df['T'] == True]))
    stats_control.append(len(df[df['T'] == False]))
    stats_smd0.append('')

    for k in range(len(variables_sel)):
        if (df[variables_sel[k]].max() == 1):
            stats_all.append(str((df[variables_sel[k]]).sum()) + ' (' + str(np.round(df[variables_sel[k]].mean()*100,2)) + ')')
            stats_treated.append(str((df[df['T'] == True][variables_sel[k]]).sum()) + ' (' + str(np.round(df[df['T'] == True][variables_sel[k]].mean()*100,2))+')')
            stats_control.append(str((df[df['T'] == False][variables_sel[k]]).sum()) + ' (' + str(np.round(df[df['T'] == False][variables_sel[k]].mean()*100,2))+')')
            variables_sel_names[k] = variables_sel_names[k] + ', n (%)'
        else:
            stats_all.append(str(np.round(df[variables_sel[k]].mean(),2)) + ' ('+ str(np.round(df[variables_sel[k]].std(),2)) + ')')
            stats_treated.append(str(np.round(df[df['T'] == True][variables_sel[k]].mean(),2)) + '(' + str(np.round(df[df['T'] == True][variables_sel[k]].std(),2)) + ')')
            stats_control.append(str(np.round(df[df['T'] == False][variables_sel[k]].mean(),2)) + ' (' + str(np.round(df[df['T'] == False][variables_sel[k]].std(),2)) + ')')
            variables_sel_names[k] = variables_sel_names[k] + ', mean (std)'

        xt_mean = df[df['T'] == True][variables_sel[k]].mean()
        xt_std = df[df['T'] == True][variables_sel[k]].std()
        xc_mean = df[df['T'] == False][variables_sel[k]].mean()
        xc_std = df[df['T'] == False][variables_sel[k]].std()
        stats_smd0.append(np.round((xt_mean-xc_mean)/(np.sqrt(np.power(xt_std,2) + np.power(xc_std,2))/2),3))


    df_stats = pd.DataFrame()
    df_stats['code'] = [' '] + variables_sel
    df_stats['Item name'] = ['Clients, n'] + variables_sel_names
    df_stats['All'] = stats_all
    df_stats['Control'] =   stats_control
    df_stats['Treated'] = stats_treated

    return df_stats


df = X_orig_train.copy()
df_stats_train = calc_desc_stats(df, confounders.copy(), confounders_name_short.copy())
df = X_orig_test.copy()
df_stats_test = calc_desc_stats(df, confounders.copy(), confounders_name_short.copy())
df_stats = pd.DataFrame()
df_stats['Item name'] = df_stats_train['Item name']
df_stats['All (train)'] = df_stats_train['All']
df_stats['All (test)'] = df_stats_test['All']
df_stats['Control (train)'] = df_stats_train['Control'] 
df_stats['Control (test)'] = df_stats_test['Control'] 
df_stats['Treated (train)'] = df_stats_train['Treated']
df_stats['Treated (test)'] = df_stats_test['Treated']

# save data
df_stats.to_csv(presentation_dir+'/data/Stats_train_and_test_confounders_'+outcome+'.csv')





#%%
# PROPENSITY SCORE DISTRIBUTION OF TRAIN DATA
#%matplotlib inline
X = X_orig_train[confounders]
T = X_orig_train['T']

from utils_ml import replace_missing_as_med
X, missing = replace_missing_as_med(X)  # replace missing values
X=(X-X.mean())/(X.std()+0.0001)  # normalize X

# Train logistic regression model (Propensity Scores)
log = LogisticRegression(penalty='l1', class_weight="balanced", solver='liblinear')
log.fit(X,T)
y_pred_prob = log.predict_proba(X)
df_ps = pd.DataFrame()
df_ps['T'] = T
df_ps['ps'] = y_pred_prob[:,1] # add proensity scores in df
print('AUC: ', roc_auc_score(T, y_pred_prob[:,1])) # auc of treatment prediction

# Histogram of propensity scores of control and treatment groups before matching
x0 = df_ps[df_ps['T'] == False]['ps']
x1 = df_ps[df_ps['T'] == True]['ps']
plt.figure(figsize=(6, 4), dpi=120)
plt.rcParams['figure.figsize'] = 8, 6
plt.rcParams['font.size'] = 12
sns.distplot(x0, label='No ACH users')
sns.distplot(x1, label='New ACH users')
plt.xlim(0, 1)
plt.ylabel('Density')
plt.xlabel('Propensity score')
plt.legend(loc=3)
plt.show()
plt.tight_layout()
plt.axvspan(0, 0.05, facecolor='r', alpha=0.1)
plt.axvspan(0.95, 1.0, facecolor='r', alpha=0.1)
filename = os.path.expanduser(presentation_dir+'/imgs/FIG_ps_dist_TRAIN')
plt.savefig(filename+'.png', facecolor='w')



#%%
# SELECT OUTCOME (K5_bin_target)

# Normal data (no normaliztion)
y_train_all = X_orig_train['K5_bin_target'].astype(float)
x_train_all = X_orig_train
y_test = X_orig_test['K5_bin_target'].astype(float)
x_test = X_orig_test

# Normalized data
#y_train_all = X_train['K5_bin_target'].astype(float)
#x_train_all = X_train
#y_test = X_test['K5_bin_target'].astype(float)
#x_test = X_test


#%%


#######################
#
# TRAIN DML MODEL
#
#######################



#%%
# Five-fold cross-validation (train data set) - valitaan kaikki esivalitut confounderit - lasketaan ate, auuc, c-for-benefit
# Tehdään mallivalintaa
    
model_names = ['GB (2,2)','GB (4,4)','GB (8,8)','GB (12,12)','GB (16,16)','GB (20,20)','GB (24,124)','GB (28,28)','RF (2,2)','RF (4,4)','RF (8,8)','RF (12,12)','RF (16,16)','RF (20,20)','RF (24,124)','RF (28,28)', 'LR']

models = [
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=2),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=2),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3)),
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=4),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=4),discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3)),
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=8),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=8),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3)),
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=12),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=12),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3)),
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=16),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=16),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3)),
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=20),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=20),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3)),
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=24),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=124),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=GradientBoostingClassifier(max_depth=2,n_estimators=28),
                model_t=GradientBoostingClassifier(max_depth=2,n_estimators=28),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=2),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=2),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=4),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=4),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=8),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=8),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=12),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=12),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=16),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=16),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=20),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=20),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=24),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=24),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))
    DML(model_y=RandomForestClassifier(max_depth=2,n_estimators=28),
                model_t=RandomForestClassifier(max_depth=2,n_estimators=28),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression()),
                #model_final=LassoCV(cv=3))

    DML(model_y=LogisticRegression(),
                model_t=LogisticRegression(),
                discrete_treatment=True,
                #model_final=RandomForestRegressor(max_depth=2,n_estimators=16))
                model_final=LinearRegression())
                #model_final=LassoCV(cv=3))
]



#%%

outcome = 'K5_bin_target'

#X['T'] = X_orig['T']
#X['y'] = Y_all_outcomes[outcome]

X_train_all = x_train_all
X_train_all['y'] = y_train_all

ate_all_models = []
cate_all_models = []
auuc_models = []
cfB_all_models = []
match_error_all_models = []
cate_results_train = []

for model_nro in range(len(models)):
    ate_all = []
    cate_all = []
    auuc = []
    cfB_all = []
    match_error_all = []

    kf = KFold(n_splits=5, shuffle = True, random_state=seed)
    aa = 0
    for train_idx, test_idx in kf.split(X_train_all):

        train = X_train_all.iloc[train_idx]
        test = X_train_all.iloc[test_idx]

        variables_model = confounders

        np.random.seed(123)

        est = models[model_nro]

        est.fit(train['y'].astype(int), train['T'], X=train[variables_model], W=None)

        treatment_effects_train = est.effect(train[variables_model], T0=0, T1=1)
        cate_results_train.append(treatment_effects_train)

        treatment_effects = est.effect(test[variables_model], T0=0, T1=1)
        cate_all.append(treatment_effects)

        ate = est.ate(test[variables_model], T0=0, T1=1)
        ate_all.append(ate)
        #lb_ate, ub_ate = est.ate_interval(x_test[confounders], T0=0, T1=1, alpha=0.05)
        
        # AUUQ = area under uplift curve
        auuc.append(uplift_auc_score(test['y'].astype(int), (treatment_effects), test['T']))
        print(f"Uplift auc score on validation data: {auuc[aa]:.4f}")

        # Plot uplift curve
        if (model_nro==1): # talletaan valitun mallin käyrät
            uplift_disp=plot_uplift_curve(test['y'], treatment_effects, test['T'], perfect=False);
            uplift_disp.figure_.suptitle("DML: Uplift curve (Fold "+str(aa)+')');
            plt.tight_layout()
            plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_dml_CV5_'+str(aa)+'.png', facecolor='white', transparent=False)

        # Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
        #if (model_nro==1): # talletaan valitun mallin käyrät
        #    X_t = test[test['T'] == True].reset_index(drop=True)
        #    X_c = test[test['T'] == False].reset_index(drop=True)
        #    point_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #    point_c = est.effect(X_c[variables_model], T0=0, T1=1)
        #    X_t['te'] = point_t
        #    X_c['te'] = point_c
        #    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
        #    predicted_benefit_t = df_treatment_matched['te']
        #    observed_outcome_t = df_treatment_matched['y'].astype(int)
        #    predicted_benefit_c = df_control_matched['te']
        #    observed_outcome_c = df_control_matched['y'].astype(int)
        #    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)
        #    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
        #    cfB_all.append(cfb)
        #    print(f"C-for-benefit on validation data: {cfB_all[aa]:.4f}")
        #else:
        #    cfB_all.append(0)


        # Ground Truth CATE approximation: matching
        #X_t = test[test['T']==True]
        #X_c = test[test['T']==False]
        #y_t = X_t['y']
        #y_c = X_c['y']
        #tau_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #df_match_error, match_error = tau_error_matching(X_t, X_c, y_t, y_c, tau_t, confounders)
        #match_error_all.append(match_error)
        #print(f"Match error on validation data: {match_error_all[aa]:.4f}")

        aa = aa+1

    print("ATE: " + str(np.mean(ate_all)))
    print ("AUUC: " + str(np.mean(auuc)))
    print (np.mean(cfB_all))
    #print (np.mean(match_error_all))

    ate_all_models.append(ate_all)
    auuc_models.append(auuc)
    cfB_all_models.append(cfB_all)
    match_error_all_models.append(match_error_all)


#%%
# Talletetaan hyperparametrien etsintädata

model_ate = []
model_auuc = []
model_c_for_benefit = []
match_error = []
for k in range (len(auuc_models)):
    m, lb, hb = mean_confidence_interval(ate_all_models[k], confidence=0.95)
    model_ate.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    m, lb, hb = mean_confidence_interval(auuc_models[k], confidence=0.95)
    model_auuc.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    #model_c_for_benefit.append(str(np.round(np.mean(cfB_all_models[k]),3)) + ' (' + str(np.round(np.min(cfB_all_models[k]),3)) + ',' + str(np.round(np.max(cfB_all_models[k]),3))+')')
    #match_error.append(str(np.round(np.mean(match_error_all_models[k]),4)) + ' (' + str(np.round(np.min(match_error_all_models[k]),4)) + ',' + str(np.round(np.max(match_error_all_models[k]),4))+')')

df_model_selection = pd.DataFrame()
df_model_selection['ML model'] = model_names
df_model_selection['ATE, mean (CI 95%)'] = model_ate
df_model_selection['AUUC, mean (CI 95%)'] = model_auuc
#df_model_selection['C-for-benefit, mean (min,max)'] = model_c_for_benefit
#df_model_selection['Match error, mean (min,max)'] = match_error

file_name = '/data/hyperparameters_anticholinergic_falls'
with pd.ExcelWriter(presentation_dir+file_name+'.xlsx', engine = 'openpyxl', if_sheet_exists = 'replace', mode = 'a') as writer:
    df_model_selection.to_excel(writer, sheet_name = 'DML')

#%%

est = models[1]

df_ITE_values = pd.DataFrame()
ite_model_name = []
ate_list = []
ate_list_train = []
auuc_list = []
auuc_list_train = []
ate_list_random = []
auuc_list_random = []
c_for_benefit_list = []
ite_and_ci_results = []


#%%
# Train model and estimate values for test data
np.random.seed(123)



est.fit(y_train_all, x_train_all['T'], X=x_train_all[confounders], W=None, inference='bootstrap')
treatment_effects = est.effect(x_test[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_test[confounders], T0=0, T1=1, alpha=0.05)

print ('ATE:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

ite_model_name.append('DML')
ate_list.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Save test data
x_test_dml_learner = x_test
x_test_dml_learner['treatment_effects'] = treatment_effects.tolist()
df_ITE_values['DML'] = x_test_dml_learner['treatment_effects'] 

# ATE of train data
treatment_effects_train = est.effect(x_train_all[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_train_all[confounders], T0=0, T1=1, alpha=0.05)
ate_list_train.append(str(np.round(np.mean(treatment_effects_train),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')




#%%
# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("DML: Uplift curve");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_dml.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))
plt.show()




#%%
df_uplift = uplift_by_percentile(y_test, (treatment_effects), x_test['T'], 
                     strategy='overall', 

                     total=True, std=True, bins=5)

rr_treatment = df_uplift['response_rate_treatment'].reset_index(drop=True)[:5]
rr_control = df_uplift['response_rate_control'].reset_index(drop=True)[:5]
std_treatment = df_uplift['std_treatment'].reset_index(drop=True)[:5]
std_control = df_uplift['std_control'].reset_index(drop=True)[:5]

x=[]
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[:int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[1*int(11595/5):2*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[2*int(11595/5):3*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[3*int(11595/5):4*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[4*int(11595/5):].mean()[0])

fig = plt.figure()
y = rr_treatment
yerr = std_treatment

yc = rr_control
yerrc = std_control

plt.errorbar(x, y, yerr=yerr, label='Treatment group')

plt.errorbar(x, yc, yerr=yerrc, label='Control group')
plt.title('DML', fontsize=14)
plt.ylabel('Unsteady gait rate', fontsize=14)
plt.xlabel('Estimated ITE', fontsize=14)
plt.legend(loc='lower left', fontsize=14)
plt.tight_layout()
fig.savefig(presentation_dir + '/imgs/FIG_uplift_by_percentile_dml.png', facecolor='w')




#%%
# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')


#%%
# Bootstrap AUUC (TRAIN)
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_train_all
df_y_te['te'] = treatment_effects_train
df_y_te['T'] = x_train_all['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_train.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')




#%%
# Plot histogram 
plt.style.use(['default'])
fig=plt.figure(facecolor='white')
plt.hist(treatment_effects.tolist(), bins=100)
plt.xlabel('ITE estimate')
plt.ylabel('Count')
plt.title('DML')
plt.tight_layout()
fig.savefig(presentation_dir + '/imgs/FIG_ite_histograms_dml.png')


#%%
# Surrogate DT
intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=4, min_samples_leaf=30)
intrp.interpret(est, x_test[confounders])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_4_DML.pdf')
intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=5, min_samples_leaf=30)
intrp.interpret(est, x_test[confounders])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_5_DML.pdf')


#%%
plt.rc('xtick', labelsize=32) #fontsize of the x tick labels
plt.rc('ytick', labelsize=32) #fontsize of the x tick labels
# Plot treatment effect + CI
df = pd.DataFrame()
df['te'] = treatment_effects
df['lb'] = lb
df['ub'] = ub
df.sort_values('te', inplace=True, ascending=True)
df.reset_index(inplace=True, drop=True)
z = df.rolling(window=10, center=True).mean()
fig, ax = plt.subplots(figsize=(24, 16))
ax.plot(z['te'],
        marker='.', linestyle='-', linewidth=2, label='ITE', color='indigo')
ax.plot(z['lb'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.plot(z['ub'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.set_title('DML', fontsize = 36)
ax.set_ylabel('Difference in absolute risk \n of Unsteady gait', fontsize = 36)
ax.set_xlabel('Patients (sorted)', fontsize = 36)
ax.legend(fontsize = 36)
ax.hlines(y=0, xmin=0, xmax=len(z), linewidth=4, color='k', linestyle='--')

plt.show()
fig.savefig(presentation_dir + '/imgs/FIG_sorted_ITE_DML.png', facecolor='white', transparent=False)

ite_and_ci_results.append(['min','max','negative ite osuus', 'neg ite with ci osuus', 'neg ite with ci n'])
ite_and_ci_results.append([str(z['te'].min()),str(z['te'].max()),str((z['te']<0).sum()/len(z)),str((z['ub']<0).sum()/len(z)),str((z['ub']<0).sum())])




#%%
# SHAP

plt.rc('xtick', labelsize=12) #fontsize of the x tick labels
plt.rc('ytick', labelsize=12) #fontsize of the x tick labels

shap_values = est.shap_values(X = np.array(x_train_all[confounders], dtype=float))
df_shap_values = pd.DataFrame()
for bb in range (len(confounders)):
    list_temp = []
    for aa in range(len(shap_values[outcome]['T_1'].values)):
        list_temp.append(list(shap_values[outcome]['T_1'].values[aa])[bb])
    df_shap_values[str(bb)] = list_temp
df_variables_names = pd.DataFrame()
df_variables_names['code'] = confounders
df_variables_names['names'] = confounders_name
names = []
for aa in range(len(confounders)):
    names.append(df_variables_names[df_variables_names['code']==confounders[aa]]['names'].reset_index(drop=True)[0])
df_shap_mean_abs = pd.DataFrame()
df_shap_mean_abs['codes_'+outcome] = confounders
df_shap_mean_abs['names_'+outcome] = names
df_shap_mean_abs['SHAP_'+outcome] = list(df_shap_values.abs().mean()) 
df_shap_mean_abs.to_csv(presentation_dir + '/data/intrp_shap_DML_'+outcome+'.csv')
plt.figure(facecolor=(1, 1, 1))
plt.title('DML')
shap.summary_plot(shap_values[outcome]['T_1'], max_display = 10, feature_names = names)
plt.savefig(presentation_dir + '/imgs/FIG_shap_DML.png', dpi=300, bbox_inches='tight')






#%%
# Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
import scipy.stats as st
cfB_all = []
for rr in range (100):
    print (rr)
    x_test['y'] = y_test
    X_t = x_test[x_test['T'] == True].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)
    X_c = x_test[x_test['T'] == False].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)
    point_t = est.effect(X_t[confounders], T0=0, T1=1)
    point_c = est.effect(X_c[confounders], T0=0, T1=1)
    X_t['te'] = point_t
    X_c['te'] = point_c
    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
    (df_treatment_matched['y'] - df_control_matched['y']).mean()
    predicted_benefit_t = df_treatment_matched['te']
    observed_outcome_t = df_treatment_matched['y']
    predicted_benefit_c = df_control_matched['te']
    observed_outcome_c = df_control_matched['y']

    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)

    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
    cfB_all.append(cfb)

cfb_mean = np.round(np.mean(cfB_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[1],3)
print(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

c_for_benefit_list.append(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')




#%%
# PDP plots
ATE = np.mean(treatment_effects)

confounders_shap_sorted = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['codes_'+outcome])
confounders_shap_sorted_names = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['names_'+outcome])
for vari_nro in range(len(confounders_shap_sorted)):
    print ('PDP: ' + confounders_shap_sorted[vari_nro] + ' ' + str(vari_nro) + '/' + str(len(confounders_shap_sorted)))
    df_ite_temp = pd.DataFrame()
    samples = 250
    for dd in range(samples):
        print (dd)
        int_rand = random.randint(0, len(x_train_all)-1)
        patients_copy_row = x_train_all[confounders_shap_sorted].reset_index(drop=True)[int_rand:int_rand+1]
        patients_copy = pd.DataFrame()
        for cc in range (100): patients_copy = patients_copy.append(patients_copy_row, ignore_index = True) 

        for gg in range(len(patients_copy)):
            patients_copy[confounders_shap_sorted[vari_nro]][gg] = gg * x_train_all[confounders_shap_sorted[vari_nro]].max()/len(patients_copy)

        point = est.effect(patients_copy[confounders], T0=0, T1=1)
        point_list = []
        for aa in range(len(point)):
            point_list.append(point[aa].tolist())
        df_ite_temp[str(dd)] = point_list

    # mean and ci of ITE
    ite_mean = []
    ite_ci_low = []
    ite_ci_high = []
    value = []
    for jj in range(len(df_ite_temp)):
        values = list(df_ite_temp[jj:jj+1].T[jj])
        ite_mean.append(np.mean(values))
        ite_ci_low.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[0])
        ite_ci_high.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[1])
        value.append((x_train_all[confounders_shap_sorted[vari_nro]].astype(float).max()-x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min()) *(jj * 1/len(patients_copy)) + x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min())

    # plot
    df = pd.DataFrame()
    df['te'] = ite_mean
    df['lb'] = ite_ci_low
    df['ub'] = ite_ci_high
    df['value'] = value
    z = df
    fig, ax = plt.subplots(figsize=(12, 12),facecolor='white')
    ax.plot(z['value'], z['te'],
            marker='.', linestyle='-', linewidth=2, color='indigo')
    ax.plot(z['value'], z['lb'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.plot(z['value'], z['ub'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.set_ylabel('ITE estimates', fontsize = 36)
    ax.set_xlabel(confounders_shap_sorted_names[vari_nro], fontsize = 36)
    ax.legend(fontsize = 36)
    ax.xaxis.set_tick_params(labelsize=24)
    ax.yaxis.set_tick_params(labelsize=24)
    ax.hlines(y=ATE, xmin=z['value'].min(), xmax=z['value'].max(), linewidth=4, color='k', linestyle='--')
    plt.show()
    fig.savefig(presentation_dir + '/imgs/FIG_PDP_DML_'+str(vari_nro)+'.png', bbox_inches='tight')




#%%
# SENSITIVITY ANALYSIS
#----------------------------

random.seed(111)
T_train_shuffle = x_train_all['T'].copy()
random.shuffle(T_train_shuffle)

# Train model and estimate values for test data

est.fit(y_train_all, T_train_shuffle, X=x_train_all[confounders], W=None, inference='bootstrap')
treatment_effects = est.effect(x_test[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_test[confounders], T0=0, T1=1, alpha=0.05)

ate_list_random.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

print ('ATE shuffle:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("DML: Uplift curve (Random Treatment)");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_dml_RANDOM_T.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))

# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print ('AUUC shuffle:')
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_random.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')








#%%

#-----------------
# DR learner
#------------------



#%%
# Five-fold cross-validation (train data set)
    
plt.style.use(['default'])

model_names = ['GB (2,2)','GB (4,4)','GB (8,8)','GB (12,12)', 'GB (16,16)', 'GB (20,20)','RF (2,2)','RF (4,4)','RF (8,8)','RF (12,12)', 'RF (16,16)', 'RF (20,20)', 'LR']

models = [
    DRLearner(model_propensity=GradientBoostingClassifier(max_depth=2,n_estimators=2),
                model_regression=GradientBoostingRegressor(max_depth=2,n_estimators=2),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=GradientBoostingClassifier(max_depth=2,n_estimators=4),
                model_regression=GradientBoostingRegressor(max_depth=2,n_estimators=4),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=GradientBoostingClassifier(max_depth=2,n_estimators=8),
                model_regression=GradientBoostingRegressor(max_depth=2,n_estimators=8),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=GradientBoostingClassifier(max_depth=2,n_estimators=12),
                model_regression=GradientBoostingRegressor(max_depth=2,n_estimators=12),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=GradientBoostingClassifier(max_depth=2,n_estimators=16),
                model_regression=GradientBoostingRegressor(max_depth=2,n_estimators=16),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=GradientBoostingClassifier(max_depth=2,n_estimators=20),
                model_regression=GradientBoostingRegressor(max_depth=2,n_estimators=20),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=RandomForestClassifier(max_depth=2,n_estimators=2),
                model_regression=RandomForestRegressor(max_depth=2,n_estimators=2),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=RandomForestClassifier(max_depth=2,n_estimators=4),
                model_regression=RandomForestRegressor(max_depth=2,n_estimators=4),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=RandomForestClassifier(max_depth=2,n_estimators=8),
                model_regression=RandomForestRegressor(max_depth=2,n_estimators=8),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=RandomForestClassifier(max_depth=2,n_estimators=12),
                model_regression=RandomForestRegressor(max_depth=2,n_estimators=12),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=RandomForestClassifier(max_depth=2,n_estimators=16),
                model_regression=RandomForestRegressor(max_depth=2,n_estimators=16),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=RandomForestClassifier(max_depth=2,n_estimators=20),
                model_regression=RandomForestRegressor(max_depth=2,n_estimators=20),
                min_propensity=0.001,
                model_final=LinearRegression()),
    DRLearner(model_propensity=LogisticRegression(),
                model_regression=LinearRegression(),
                min_propensity=0.001,
                model_final=LinearRegression()),
]

#%%
outcome = 'K5_bin_target'


X_train_all = x_train_all
X_train_all['y'] = y_train_all

ate_all_models = []
cate_all_models = []
auuc_models = []
cfB_all_models = []
match_error_all_models = []

np.random.seed(123)

for model_nro in range(len(models)):
    ate_all = []
    cate_all = []
    auuc = []
    cfB_all = []
    match_error_all = []

    kf = KFold(n_splits=5, shuffle=True, random_state=seed)
    aa = 0
    for train_idx, test_idx in kf.split(X_train_all):

        train = X_train_all.iloc[train_idx]
        test = X_train_all.iloc[test_idx]

        variables_model = confounders

        est = models[model_nro]

        est.fit(train['y'].astype(int), train['T'], X=train[variables_model], W=None)

        treatment_effects_train = est.effect(train[variables_model], T0=0, T1=1)
        cate_results_train.append(treatment_effects_train)

        treatment_effects = est.effect(test[variables_model], T0=0, T1=1)
        cate_all.append(treatment_effects)

        ate = est.ate(test[variables_model], T0=0, T1=1)
        ate_all.append(ate)
        
        auuc.append(uplift_auc_score(test['y'].astype(int), (treatment_effects), test['T']))
        print(f"Uplift auc score on validation data: {auuc[aa]:.4f}")

        # Plot uplift curve
        if (model_nro == 1): # Piirretään käyrät valitulle mallille
            uplift_disp=plot_uplift_curve(test['y'], treatment_effects, test['T'], perfect=False);
            uplift_disp.figure_.suptitle("DR-learner: Uplift curve (Fold "+str(aa)+')');
            plt.tight_layout()
            plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_dr_CV5_'+str(aa)+'.png', facecolor='white', transparent=False)

        #    # Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
        #    X_t = test[test['T'] == True].reset_index(drop=True)
        #    X_c = test[test['T'] == False].reset_index(drop=True)
        #    point_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #    point_c = est.effect(X_c[variables_model], T0=0, T1=1)
        #    X_t['te'] = point_t
        #    X_c['te'] = point_c
        #    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
        #    predicted_benefit_t = df_treatment_matched['te']
        #    observed_outcome_t = df_treatment_matched['y'].astype(int)
        #    predicted_benefit_c = df_control_matched['te']
        #    observed_outcome_c = df_control_matched['y'].astype(int)
        #    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)
        #    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
        #    cfB_all.append(cfb)
        #    print(f"C-for-benefit on validation data: {cfB_all[aa]:.4f}")
        #else:
        #    cfB_all.append(0)

        # Ground Truth CATE approximation: matching
        #X_t = test[test['T']==True]
        #X_c = test[test['T']==False]
        #y_t = X_t['y']
        #y_c = X_c['y']
        #tau_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #df_match_error, match_error = tau_error_matching(X_t, X_c, y_t, y_c, tau_t, confounders)
        #match_error_all.append(match_error)
        #print(f"Match error on validation data: {match_error_all[aa]:.4f}")

        aa = aa+1

    print("ATE: " + str(np.mean(ate_all)))
    print ("AUUC: " + str(np.mean(auuc)))
    print (np.mean(cfB_all))
    #print (np.mean(match_error_all))

    ate_all_models.append(ate_all)
    auuc_models.append(auuc)
    cfB_all_models.append(cfB_all)
    match_error_all_models.append(match_error_all)


#%%
# Talletetaan hyperparametrien etsintädata

model_ate = []
model_auuc = []
model_c_for_benefit = []
match_error = []
for k in range (len(auuc_models)):
    m, lb, hb = mean_confidence_interval(ate_all_models[k], confidence=0.95)
    model_ate.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    m, lb, hb = mean_confidence_interval(auuc_models[k], confidence=0.95)
    model_auuc.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    #model_c_for_benefit.append(str(np.round(np.mean(cfB_all_models[k]),3)) + ' (' + str(np.round(np.min(cfB_all_models[k]),3)) + ',' + str(np.round(np.max(cfB_all_models[k]),3))+')')
    #match_error.append(str(np.round(np.mean(match_error_all_models[k]),4)) + ' (' + str(np.round(np.min(match_error_all_models[k]),4)) + ',' + str(np.round(np.max(match_error_all_models[k]),4))+')')

df_model_selection = pd.DataFrame()
df_model_selection['ML model'] = model_names
df_model_selection['ATE, mean (CI 95%)'] = model_ate
df_model_selection['AUUC, mean (CI 95%)'] = model_auuc
#df_model_selection['C-for-benefit, mean (min,max)'] = model_c_for_benefit
#df_model_selection['Match error, mean (min,max)'] = match_error

file_name = '/data/hyperparameters_anticholinergic_falls'
with pd.ExcelWriter(presentation_dir+file_name+'.xlsx', engine = 'openpyxl', if_sheet_exists = 'replace', mode = 'a') as writer:
    df_model_selection.to_excel(writer, sheet_name = 'DR')

#%%

est = models[1]


#%%
# Train model and estimate values for test data

variables_model = confounders

np.random.seed(123)
est.fit(y_train_all, x_train_all['T'], X=x_train_all[variables_model], W=None, inference='bootstrap')
treatment_effects = est.effect(x_test[variables_model], T0=0, T1=1)
lb, ub = est.effect_interval(x_test[variables_model], T0=0, T1=1, alpha=0.05)

print ('ATE:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

ite_model_name.append('DR learner')
ate_list.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Talletetaan test_data
x_test_dr_learner = x_test
x_test_dr_learner['treatment_effects'] = treatment_effects.tolist()
df_ITE_values['DR'] = x_test_dr_learner['treatment_effects'] 

# ATE of train data
treatment_effects_train = est.effect(x_train_all[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_train_all[confounders], T0=0, T1=1, alpha=0.05)
ate_list_train.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')




#%%
# Plot uplift curve
plt.style.use(['default'])
from sklift.viz import plot_uplift_curve
from sklift.metrics import uplift_by_percentile
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("DR-learner: Uplift curve");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_dr.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))



#%%

df_uplift = uplift_by_percentile(y_test, (treatment_effects), x_test['T'], 
                     strategy='overall', 
                     total=True, std=True, bins=5)


rr_treatment = df_uplift['response_rate_treatment'].reset_index(drop=True)[:5]
rr_control = df_uplift['response_rate_control'].reset_index(drop=True)[:5]
std_treatment = df_uplift['std_treatment'].reset_index(drop=True)[:5]
std_control = df_uplift['std_control'].reset_index(drop=True)[:5]

x=[]
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[:int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[1*int(11595/5):2*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[2*int(11595/5):3*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[3*int(11595/5):4*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[4*int(11595/5):].mean()[0])

fig = plt.figure()
y = rr_treatment
yerr = std_treatment

yc = rr_control
yerrc = std_control

plt.errorbar(x, y, yerr=yerr, label='Treatment group')

plt.errorbar(x, yc, yerr=yerrc, label='Control group')
plt.title('DR-learner', fontsize=14)
plt.ylabel('Unsteady gait', fontsize=14)
plt.xlabel('Estimated ITE', fontsize=14)
plt.legend(loc='lower left', fontsize=14)
fig.savefig(presentation_dir + '/imgs/FIG_uplift_by_percentile_dr.png')



#%%
# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

#%%
# Bootstrap AUUC (TRAIN)
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_train_all
df_y_te['te'] = treatment_effects_train
df_y_te['T'] = x_train_all['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_train.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')




#%%
# Plot histogram 
plt.style.use(['default'])
# import matplotlib.pyplot as plt
fig=plt.figure(facecolor='white')
plt.rcParams['font.size'] = '12'
plt.hist(treatment_effects.tolist(), bins=100)
plt.xlabel('ITE estimate', fontsize=12)
plt.ylabel('Count', fontsize=12)
plt.title('DR learner', fontsize=12)
plt.tight_layout()
fig.savefig(presentation_dir + '/imgs/FIG_ite_histograms_dr.png')



#%%
# Surrogate DT
intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=4, min_samples_leaf=30)
intrp.interpret(est, x_test[variables_model])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_4_DR_Learner_.pdf')
intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=5, min_samples_leaf=30)
intrp.interpret(est, x_test[variables_model])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_5_DR_Learner_.pdf')





#%%
plt.rc('xtick', labelsize=32) #fontsize of the x tick labels
plt.rc('ytick', labelsize=32) #fontsize of the x tick labels
# Plot treatment effect + CI
df = pd.DataFrame()
df['te'] = treatment_effects
df['lb'] = lb
df['ub'] = ub
df.sort_values('te', inplace=True, ascending=True)
df.reset_index(inplace=True, drop=True)
z = df.rolling(window=10, center=True).mean()
fig, ax = plt.subplots(figsize=(24, 16))
ax.plot(z['te'],
        marker='.', linestyle='-', linewidth=2, label='ITE', color='indigo')
ax.plot(z['lb'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.plot(z['ub'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.set_title('DR learner', fontsize = 36)
ax.set_ylabel('Difference in absolute risk \n of unsteady gait', fontsize = 28)
ax.set_xlabel('Patients (sorted)', fontsize = 36)

ax.legend(fontsize = 36)
ax.hlines(y=0, xmin=0, xmax=len(z), linewidth=4, color='k', linestyle='--')
plt.show()
#plt.tight_layout()
fig.savefig(presentation_dir + '/imgs/FIG_sorted_ITE_DR.png')


ite_and_ci_results.append([str(z['te'].min()),str(z['te'].max()),str((z['te']<0).sum()/len(z)),str((z['ub']<0).sum()/len(z)),str((z['ub']<0).sum())])


#%%
# SHAP
shap_values = est.shap_values(X = np.array(x_train_all[variables_model], dtype=float))

df_shap_values = pd.DataFrame()
for bb in range (len(variables_model)):
    list_temp = []
    for aa in range(len(shap_values[outcome]['T_1'].values)):
        list_temp.append(list(shap_values[outcome]['T_1'].values[aa])[bb])
    df_shap_values[str(bb)] = list_temp
df_variables_names = pd.DataFrame()
df_variables_names['code'] = confounders
df_variables_names['names'] = confounders_name
names = []
for aa in range(len(variables_model)):
    names.append(df_variables_names[df_variables_names['code']==variables_model[aa]]['names'].reset_index(drop=True)[0])
df_shap_mean_abs = pd.DataFrame()
df_shap_mean_abs['codes_'+outcome] = variables_model
df_shap_mean_abs['names_'+outcome] = names
df_shap_mean_abs['SHAP_'+outcome] = list(df_shap_values.abs().mean()) 
df_shap_mean_abs.to_csv(presentation_dir + '/data/intrp_shap_DR_'+outcome+'.csv')
plt.figure(facecolor=(1, 1, 1))
plt.title('DR learner')
shap.summary_plot(shap_values[outcome]['T_1'], max_display = 10, feature_names = names)

plt.savefig(presentation_dir + '/imgs/FIG_shap_DR.png', dpi=300, bbox_inches='tight')





#%%
# Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
import scipy.stats as st
cfB_all = []
for rr in range (100):
    print (rr)
    x_test['y'] = y_test
    X_t = x_test[x_test['T'] == True].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)
    X_c = x_test[x_test['T'] == False].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)
    point_t = est.effect(X_t[variables_model], T0=0, T1=1)
    point_c = est.effect(X_c[variables_model], T0=0, T1=1)
    X_t['te'] = point_t
    X_c['te'] = point_c
    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
    (df_treatment_matched['y'] - df_control_matched['y']).mean()
    predicted_benefit_t = df_treatment_matched['te']
    observed_outcome_t = df_treatment_matched['y']
    predicted_benefit_c = df_control_matched['te']
    observed_outcome_c = df_control_matched['y']

    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)

    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
    cfB_all.append(cfb)

cfb_mean = np.round(np.mean(cfB_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[1],3)
print(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

c_for_benefit_list.append(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')




#%%
# PDP plots
ATE = np.mean(treatment_effects)

confounders_shap_sorted = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['codes_'+outcome])
confounders_shap_sorted_names = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['names_'+outcome])
for vari_nro in range(len(confounders_shap_sorted)):
    print ('PDP: ' + confounders_shap_sorted[vari_nro] + ' ' + str(vari_nro) + '/' + str(len(confounders_shap_sorted)))
    df_ite_temp = pd.DataFrame()
    samples = 250
    for dd in range(samples):
        print (dd)
        int_rand = random.randint(0, len(x_train_all)-1)
        patients_copy_row = x_train_all[confounders_shap_sorted].reset_index(drop=True)[int_rand:int_rand+1]
        patients_copy = pd.DataFrame()
        for cc in range (100): patients_copy = patients_copy.append(patients_copy_row, ignore_index = True) 

        for gg in range(len(patients_copy)):
            patients_copy[confounders_shap_sorted[vari_nro]][gg] = gg * x_train_all[confounders_shap_sorted[vari_nro]].max()/len(patients_copy)

        point = est.effect(patients_copy[confounders], T0=0, T1=1)
        point_list = []
        for aa in range(len(point)):
            point_list.append(point[aa].tolist())
        df_ite_temp[str(dd)] = point_list

    # mean and ci of ITE
    ite_mean = []
    ite_ci_low = []
    ite_ci_high = []
    value = []
    for jj in range(len(df_ite_temp)):
        values = list(df_ite_temp[jj:jj+1].T[jj])
        ite_mean.append(np.mean(values))
        ite_ci_low.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[0])
        ite_ci_high.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[1])
        value.append((x_train_all[confounders_shap_sorted[vari_nro]].astype(float).max()-x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min()) *(jj * 1/len(patients_copy)) + x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min())

    # plot
    df = pd.DataFrame()
    df['te'] = ite_mean
    df['lb'] = ite_ci_low
    df['ub'] = ite_ci_high
    df['value'] = value
    z = df
    fig, ax = plt.subplots(figsize=(12, 12),facecolor='white')
    ax.plot(z['value'], z['te'],
            marker='.', linestyle='-', linewidth=2, color='indigo')
    ax.plot(z['value'], z['lb'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.plot(z['value'], z['ub'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.set_ylabel('ITE estimates', fontsize = 36)
    ax.set_xlabel(confounders_shap_sorted_names[vari_nro], fontsize = 36)
    ax.legend(fontsize = 36)
    ax.xaxis.set_tick_params(labelsize=24)
    ax.yaxis.set_tick_params(labelsize=24)
    ax.hlines(y=ATE, xmin=z['value'].min(), xmax=z['value'].max(), linewidth=4, color='k', linestyle='--')
    plt.show()
    fig.savefig(presentation_dir + '/imgs/FIG_PDP_DR_'+str(vari_nro)+'.png', bbox_inches='tight')



#%%
# SENSITIVITY ANALYSIS
#----------------------------

random.seed(111)
T_train_shuffle = x_train_all['T'].copy()
random.shuffle(T_train_shuffle)

# Train model and estimate values for test data
est.fit(y_train_all, T_train_shuffle, X=x_train_all[confounders], W=None, inference='bootstrap')
treatment_effects = est.effect(x_test[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_test[confounders], T0=0, T1=1, alpha=0.05)

ate_list_random.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

print ('ATE shuffle:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("DR: Uplift curve (Random Treatment)");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_dr_RANDOM_T.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))

# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print ('AUUC shuffle:')
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_random.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')








#%%
# Five-fold cross-validation (train data set) - valitaan kaikki esivalitut confounderit - lasketaan ate, auuc, c-for-benefit
# Tehdään mallivalintaa
    
plt.style.use(['default'])

model_names = ['GB (2,2)','GB (4,4)','GB (8,8)', 'GB (12,12)', 'GB (16,16)', 'GB (20,20)','RF (2,2)','RF (4,4)','RF (8,8)','RF (12,12)', 'RF (16,16)', 'RF (20,20)', 'LR']

models = [
    XLearner(models=[GradientBoostingRegressor(max_depth=2,n_estimators=2, random_state=0), 
                GradientBoostingRegressor(max_depth=2,n_estimators=2, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[GradientBoostingRegressor(max_depth=2,n_estimators=4, random_state=0), 
                GradientBoostingRegressor(max_depth=2,n_estimators=4, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[GradientBoostingRegressor(max_depth=2,n_estimators=8, random_state=0), 
                GradientBoostingRegressor(max_depth=2,n_estimators=8, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[GradientBoostingRegressor(max_depth=2,n_estimators=12, random_state=0), 
                GradientBoostingRegressor(max_depth=2,n_estimators=12, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[GradientBoostingRegressor(max_depth=2,n_estimators=16, random_state=0), 
                GradientBoostingRegressor(max_depth=2,n_estimators=16, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[GradientBoostingRegressor(max_depth=2,n_estimators=20, random_state=0), 
                GradientBoostingRegressor(max_depth=2,n_estimators=20, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[RandomForestRegressor(max_depth=2,n_estimators=2, random_state=0), 
                RandomForestRegressor(max_depth=2,n_estimators=2, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[RandomForestRegressor(max_depth=2,n_estimators=4, random_state=0), 
                RandomForestRegressor(max_depth=2,n_estimators=4, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[RandomForestRegressor(max_depth=2,n_estimators=8, random_state=0), 
                RandomForestRegressor(max_depth=2,n_estimators=8, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[RandomForestRegressor(max_depth=2,n_estimators=12, random_state=0), 
                RandomForestRegressor(max_depth=2,n_estimators=12, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[RandomForestRegressor(max_depth=2,n_estimators=16, random_state=0), 
                RandomForestRegressor(max_depth=2,n_estimators=16, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[RandomForestRegressor(max_depth=2,n_estimators=20, random_state=0), 
                RandomForestRegressor(max_depth=2,n_estimators=20, random_state=0)], 
                cate_models=None, propensity_model=LogisticRegression()),
    XLearner(models=[LinearRegression(), 
                LinearRegression()], 
                cate_models=None, propensity_model=LogisticRegression())
]

#%%

outcome = 'K5_bin_target'

X_train_all = x_train_all
X_train_all['y'] = y_train_all

ate_all_models = []
cate_all_models = []
auuc_models = []
cfB_all_models = []
match_error_all_models = []

for model_nro in range(len(models)):
    ate_all = []
    cate_all = []
    auuc = []
    cfB_all = []
    match_error_all = []

    kf = KFold(n_splits=5, shuffle=True, random_state=seed)
    aa = 0
    for train_idx, test_idx in kf.split(X_train_all):

        train = X_train_all.iloc[train_idx]
        test = X_train_all.iloc[test_idx]

        variables_model = confounders

        np.random.seed(123)

        est = models[model_nro]

        est.fit(train['y'], train['T'], X=train[variables_model])

        treatment_effects_train = est.effect(train[variables_model], T0=0, T1=1)
        cate_results_train.append(treatment_effects_train)

        treatment_effects = est.effect(test[variables_model], T0=0, T1=1)
        cate_all.append(treatment_effects)

        ate = est.ate(test[variables_model], T0=0, T1=1)
        ate_all.append(ate)
        #lb_ate, ub_ate = est.ate_interval(x_test[confounders], T0=0, T1=1, alpha=0.05)
        
        # AUUQ = area under uplift curve
        auuc.append(uplift_auc_score(test['y'].astype(int), (treatment_effects), test['T']))
        print(f"Uplift auc score on validation data: {auuc[aa]:.4f}")

        # Plot uplift curve
        #if (model_nro == 12): # Piirretään käyrät valitulle mallille
        #    uplift_disp=plot_uplift_curve(test['y'], treatment_effects, test['T'], perfect=False);
        #    uplift_disp.figure_.suptitle("X-learner: Uplift curve (Fold "+str(aa)+')');
        #    plt.tight_layout()
        #    plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_x_CV5_'+str(aa)+'.png', facecolor='white', transparent=False)

        #    # Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
        #    X_t = test[test['T'] == True].reset_index(drop=True)
        #    X_c = test[test['T'] == False].reset_index(drop=True)
        #    point_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #    point_c = est.effect(X_c[variables_model], T0=0, T1=1)
        #    X_t['te'] = point_t
        #    X_c['te'] = point_c
        #    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
        #    predicted_benefit_t = df_treatment_matched['te']
        #    observed_outcome_t = df_treatment_matched['y'].astype(int)
        #    predicted_benefit_c = df_control_matched['te']
        #    observed_outcome_c = df_control_matched['y'].astype(int)
        #    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)
        #    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
        #    cfB_all.append(cfb)
         #   print(f"C-for-benefit on validation data: {cfB_all[aa]:.4f}")
        #else:
        #    cfB_all.append(cfb)


        # Ground Truth CATE approximation: matching
        #X_t = test[test['T']==True]
        #X_c = test[test['T']==False]
        #y_t = X_t['y']
        #y_c = X_c['y']
        #tau_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #df_match_error, match_error = tau_error_matching(X_t, X_c, y_t, y_c, tau_t, confounders)
        #match_error_all.append(match_error)
        #print(f"Match error on validation data: {match_error_all[aa]:.4f}")

        aa = aa+1

    print("ATE: " + str(np.mean(ate_all)))
    print ("AUUC: " + str(np.mean(auuc)))
    #print (np.mean(cfB_all))
    #print (np.mean(match_error_all))

    ate_all_models.append(ate_all)
    auuc_models.append(auuc)
    cfB_all_models.append(cfB_all)
    match_error_all_models.append(match_error_all)


#%%
# Talletetaan hyperparametrien etsintädata



model_ate = []
model_auuc = []
model_c_for_benefit = []
match_error = []
for k in range (len(auuc_models)):
    m, lb, hb = mean_confidence_interval(ate_all_models[k], confidence=0.95)
    model_ate.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    m, lb, hb = mean_confidence_interval(auuc_models[k], confidence=0.95)
    model_auuc.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    #model_c_for_benefit.append(str(np.round(np.mean(cfB_all_models[k]),3)) + ' (' + str(np.round(np.min(cfB_all_models[k]),3)) + ',' + str(np.round(np.max(cfB_all_models[k]),3))+')')
    #match_error.append(str(np.round(np.mean(match_error_all_models[k]),4)) + ' (' + str(np.round(np.min(match_error_all_models[k]),4)) + ',' + str(np.round(np.max(match_error_all_models[k]),4))+')')

df_model_selection = pd.DataFrame()
df_model_selection['ML model'] = model_names
df_model_selection['ATE, mean (CI 95%)'] = model_ate
df_model_selection['AUUC, mean (CI 95%)'] = model_auuc
#df_model_selection['C-for-benefit, mean (min,max)'] = model_c_for_benefit
#df_model_selection['Match error, mean (min,max)'] = match_error

file_name = '/data/hyperparameters_anticholinergic_falls'
with pd.ExcelWriter(presentation_dir+file_name+'.xlsx', engine = 'openpyxl', if_sheet_exists = 'replace', mode = 'a') as writer:
    df_model_selection.to_excel(writer, sheet_name = 'X-learner')



#%%
# Mikä malli valitaan??
est = models[12]





#%%
# Train model and estimate values for test data
np.random.seed(123)
variables_model = confounders
est.fit(y_train_all, x_train_all['T'], X=x_train_all[variables_model], inference='bootstrap')
treatment_effects = est.effect(x_test[variables_model], T0=0, T1=1)
lb, ub = est.effect_interval(x_test[variables_model], T0=0, T1=1, alpha=0.05)

print ('ATE:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

ite_model_name.append('X-learner')
ate_list.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Talletetaan test_data
x_test_x_learner = x_test
x_test_x_learner['treatment_effects'] = treatment_effects.tolist()
df_ITE_values['X'] = x_test_x_learner['treatment_effects'] 


# ATE of train data
treatment_effects_train = est.effect(x_train_all[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_train_all[confounders], T0=0, T1=1, alpha=0.05)
ate_list_train.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')





#%%
# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("X-learner: Uplift curve");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_x.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))





#%%
# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')


#%%
# Bootstrap AUUC (TRAIN)
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_train_all
df_y_te['te'] = treatment_effects_train
df_y_te['T'] = x_train_all['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_train.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')





#%%
plt.style.use(['default'])
df_uplift = uplift_by_percentile(y_test, (treatment_effects), x_test['T'], 
                     strategy='overall', 
                     total=True, std=True, bins=5)

rr_treatment = df_uplift['response_rate_treatment'].reset_index(drop=True)[:5]
rr_control = df_uplift['response_rate_control'].reset_index(drop=True)[:5]
std_treatment = df_uplift['std_treatment'].reset_index(drop=True)[:5]
std_control = df_uplift['std_control'].reset_index(drop=True)[:5]

x=[]
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[:int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[1*int(11595/5):2*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[2*int(11595/5):3*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[3*int(11595/5):4*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[4*int(11595/5):].mean()[0])


fig = plt.figure()
y = rr_treatment
yerr = std_treatment

yc = rr_control
yerrc = std_control

plt.errorbar(x, y, yerr=yerr, label='Treatment group')

plt.errorbar(x, yc, yerr=yerrc, label='Control group')
plt.title('X-learner', fontsize=14)
plt.ylabel('Unsteady gait rate', fontsize=14)
plt.xlabel('Estimated ITE', fontsize=14)
plt.legend(loc='lower left', fontsize=14)
fig.savefig(presentation_dir + '/imgs/FIG_uplift_by_percentile_x.png')




#%%
# Plot histogram 
plt.style.use(['default'])
fig=plt.figure(facecolor='white')
plt.hist(treatment_effects.tolist(), bins=100)
plt.xlabel('ITE estimate')
plt.ylabel('Count')
plt.title('X learner')
plt.show()
fig.savefig(presentation_dir + '/imgs/FIG_ite_histograms_x.png')


# Surogate DT
intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=4, min_samples_leaf=30)
intrp.interpret(est, x_test[variables_model])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_4_X.pdf',bbox_inches='tight',facecolor='white')

intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=5, min_samples_leaf=30)
intrp.interpret(est, x_test[variables_model])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_5_X.pdf',bbox_inches='tight',facecolor='white')

# Plot treatment effect + CI
plt.rc('xtick', labelsize=32) #fontsize of the x tick labels
plt.rc('ytick', labelsize=32) #fontsize of the x tick labels
df = pd.DataFrame()
df['te'] = treatment_effects
df['lb'] = lb
df['ub'] = ub
df.sort_values('te', inplace=True, ascending=True)
df.reset_index(inplace=True, drop=True)
z = df.rolling(window=10, center=True).mean()
fig, ax = plt.subplots(figsize=(24, 16))
ax.plot(z['te'],
        marker='.', linestyle='-', linewidth=2, label='ITE', color='indigo')
ax.plot(z['lb'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.plot(z['ub'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.set_title('X learner', fontsize = 36)
ax.set_ylabel('Difference in absolute risk \n of unsteady gait', fontsize = 28)
ax.set_xlabel('Patients (sorted)', fontsize = 36)
ax.legend(fontsize = 36)
ax.hlines(y=0, xmin=0, xmax=len(z), linewidth=4, color='k', linestyle='--')
plt.show()
fig.savefig(presentation_dir + '/imgs/FIG_sorted_ITE_X.png')


plt.style.use(['default'])

ite_and_ci_results.append([str(z['te'].min()),str(z['te'].max()),str((z['te']<0).sum()/len(z)),str((z['ub']<0).sum()/len(z)),str((z['ub']<0).sum())])



#%%
# SHAP
plt.style.use(['default'])
shap_values = est.shap_values(X = np.array(x_test[variables_model], dtype=float))
df_shap_values = pd.DataFrame()

for bb in range (len(variables_model)):
    list_temp = []
    for aa in range(len(shap_values[outcome]['T_1'].values)):
        list_temp.append(list(shap_values[outcome]['T_1'].values[aa])[bb])
    df_shap_values[str(bb)] = list_temp
df_variables_names = pd.DataFrame()
df_variables_names['code'] = confounders
df_variables_names['names'] = confounders_name
names = []
for aa in range(len(variables_model)):
    names.append(df_variables_names[df_variables_names['code']==variables_model[aa]]['names'].reset_index(drop=True)[0])
df_shap_mean_abs = pd.DataFrame()
df_shap_mean_abs['codes_'+outcome] = variables_model
df_shap_mean_abs['names_'+outcome] = names
df_shap_mean_abs['SHAP_'+ outcome] = list(df_shap_values.abs().mean()) 
df_shap_mean_abs.to_csv(presentation_dir + '/data/intrp_shap_X_'+outcome+'.csv')
plt.figure(facecolor=(1, 1, 1))
plt.title('X learner')
shap.summary_plot(shap_values[outcome]['T_1'], max_display = 10, feature_names = names)
plt.savefig(presentation_dir + '/imgs/FIG_shap_X.png', dpi=300, bbox_inches='tight')





#%%
# Concordance-statistics for benefit (TE MATCHING) BOOTSTRAPPING
cfB_all = []
for rr in range (100):
    print (rr)
    x_test['y'] = y_test
    X_t = x_test[x_test['T'] == True].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)
    X_c = x_test[x_test['T'] == False].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)

    point_t = est.effect(X_t[variables_model], T0=0, T1=1)
    point_c = est.effect(X_c[variables_model], T0=0, T1=1)
    X_t['te'] = point_t
    X_c['te'] = point_c
    
    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
    (df_treatment_matched['y'] - df_control_matched['y']).mean()
    predicted_benefit_t = df_treatment_matched['te']
    observed_outcome_t = df_treatment_matched['y']
    predicted_benefit_c = df_control_matched['te']
    observed_outcome_c = df_control_matched['y']

    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)

    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
    cfB_all.append(cfb)

cfb_mean = np.round(np.mean(cfB_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[1],3)
print(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

c_for_benefit_list.append(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')





#%%
# PDP plots
ATE = np.mean(treatment_effects)

confounders_shap_sorted = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['codes_'+outcome])
confounders_shap_sorted_names = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['names_'+outcome])
for vari_nro in range(len(confounders_shap_sorted)):
    print ('PDP: ' + confounders_shap_sorted[vari_nro] + ' ' + str(vari_nro) + '/' + str(len(confounders_shap_sorted)))
    df_ite_temp = pd.DataFrame()
    samples = 250
    for dd in range(samples):
        print (dd)
        int_rand = random.randint(0, len(x_train_all)-1)
        patients_copy_row = x_train_all[confounders_shap_sorted].reset_index(drop=True)[int_rand:int_rand+1]
        patients_copy = pd.DataFrame()
        for cc in range (100): patients_copy = patients_copy.append(patients_copy_row, ignore_index = True) 

        for gg in range(len(patients_copy)):
            patients_copy[confounders_shap_sorted[vari_nro]][gg] = gg * x_train_all[confounders_shap_sorted[vari_nro]].max()/len(patients_copy)

        point = est.effect(patients_copy[confounders], T0=0, T1=1)
        point_list = []
        for aa in range(len(point)):
            point_list.append(point[aa].tolist())
        df_ite_temp[str(dd)] = point_list

    # mean and ci of ITE
    ite_mean = []
    ite_ci_low = []
    ite_ci_high = []
    value = []
    for jj in range(len(df_ite_temp)):
        values = list(df_ite_temp[jj:jj+1].T[jj])
        ite_mean.append(np.mean(values))
        ite_ci_low.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[0])
        ite_ci_high.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[1])
        value.append((x_train_all[confounders_shap_sorted[vari_nro]].astype(float).max()-x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min()) *(jj * 1/len(patients_copy)) + x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min())

    # plot
    df = pd.DataFrame()
    df['te'] = ite_mean
    df['lb'] = ite_ci_low
    df['ub'] = ite_ci_high
    df['value'] = value
    z = df
    fig, ax = plt.subplots(figsize=(12, 12),facecolor='white')
    ax.plot(z['value'], z['te'],
            marker='.', linestyle='-', linewidth=2, color='indigo')
    ax.plot(z['value'], z['lb'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.plot(z['value'], z['ub'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.set_ylabel('ITE estimates', fontsize = 36)
    ax.set_xlabel(confounders_shap_sorted_names[vari_nro], fontsize = 36)
    ax.legend(fontsize = 36)
    ax.xaxis.set_tick_params(labelsize=24)
    ax.yaxis.set_tick_params(labelsize=24)
    ax.hlines(y=ATE, xmin=z['value'].min(), xmax=z['value'].max(), linewidth=4, color='k', linestyle='--')
    plt.show()
    fig.savefig(presentation_dir + '/imgs/FIG_PDP_X_'+str(vari_nro)+'.png', bbox_inches='tight')




#%%
# SENSITIVITY ANALYSIS
#----------------------------

random.seed(111)
T_train_shuffle = x_train_all['T'].copy()
random.shuffle(T_train_shuffle)

# Train model and estimate values for test data
est.fit(y_train_all, T_train_shuffle, X=x_train_all[variables_model], inference='bootstrap')
treatment_effects = est.effect(x_test[confounders], T0=0, T1=1)
lb, ub = est.effect_interval(x_test[confounders], T0=0, T1=1, alpha=0.05)

ate_list_random.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

print ('ATE shuffle:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("X-learner: Uplift curve (Random Treatment)");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_x_RANDOM_T.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))

# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print ('AUUC shuffle:')
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_random.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')









#%%
# ECONML causal forest
##########################



#%%
# Five-fold cross-validation (train data set)
    

plt.style.use(['default'])

"""
model_names = ['CF (2,2)','CF (2,4)','CF (2,8)','CF (2,16)','CF (2,32)','CF (2,64)','CF (2,128)','CF (2,256)', 'CF (2,512)', 'CF (2,1024)', 'CF (4,8)','CF (4,16)','CF (4,32)','CF (4,64)','CF (4,128)','CF (4,256)','CF (4,512)','CF (4,1024)']

models = [
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 4, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 4, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 8, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 16, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 32, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 64, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 128, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 256, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 512, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 2, 
                    n_estimators = 1024, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 8, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 16, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 32, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 64, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 128, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 256, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 512, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 1024, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
]
"""

model_names = ['CF (4,32)','CF (4,64)','CF (4,128)','CF (4,256)']

models = [
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 32, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 64, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 128, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
    CausalForestDML(model_y = RandomForestRegressor(), model_t= RandomForestClassifier(), 
                    discrete_treatment = True, 
                    cv= 3, 
                    max_depth = 4, 
                    n_estimators = 256, 
                    max_features = 'sqrt', inference = True, random_state = 123, verbose = 0),
]

#%%

outcome = 'K5_bin_target'


X_train_all = x_train_all
X_train_all['y'] = y_train_all

ate_all_models = []
cate_all_models = []
auuc_models = []
cfB_all_models = []
match_error_all_models = []

for model_nro in range(len(models)):
    ate_all = []
    cate_all = []
    auuc = []
    cfB_all = []
    match_error_all = []

    kf = KFold(n_splits=5, shuffle=True, random_state=seed)
    aa = 0
    for train_idx, test_idx in kf.split(X_train_all):

        train = X_train_all.iloc[train_idx]
        test = X_train_all.iloc[test_idx]

        variables_model = confounders

        np.random.seed(123)

        est = models[model_nro]

        est = est.fit(Y = train['y'], T = train['T'], X = train[variables_model], W = train[variables_model], cache_values=True)

        treatment_effects_train = est.effect(train[variables_model], T0=0, T1=1)
        cate_results_train.append(treatment_effects_train)

        treatment_effects = est.effect(test[variables_model], T0=0, T1=1)
        cate_all.append(treatment_effects)

        ate = est.ate(test[variables_model], T0=0, T1=1)
        ate_all.append(ate)
        
        # AUUQ = area under uplift curve
        auuc.append(uplift_auc_score(test['y'].astype(int), (treatment_effects), test['T']))
        print(f"Uplift auc score on validation data: {auuc[aa]:.4f}")

        # Plot uplift curve
        if (model_nro == 2):
            uplift_disp=plot_uplift_curve(test['y'], treatment_effects, test['T'], perfect=False);
            uplift_disp.figure_.suptitle("Causal forest: Uplift curve (Fold "+str(aa)+')');
            plt.tight_layout()
            plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_cf_CV5_'+str(aa)+'.png', facecolor='white', transparent=False)

            # Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
            X_t = test[test['T'] == True].reset_index(drop=True)
            X_c = test[test['T'] == False].reset_index(drop=True)
            point_t = est.effect(X_t[variables_model], T0=0, T1=1)
            point_c = est.effect(X_c[variables_model], T0=0, T1=1)
            X_t['te'] = point_t
            X_c['te'] = point_c
            df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
            predicted_benefit_t = df_treatment_matched['te']
            observed_outcome_t = df_treatment_matched['y'].astype(int)
            predicted_benefit_c = df_control_matched['te']
            observed_outcome_c = df_control_matched['y'].astype(int)
            result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)
            cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
            cfB_all.append(cfb)
            print(f"C-for-benefit on validation data: {cfB_all[aa]:.4f}")
        else:
            cfB_all.append(cfb)


        # Ground Truth CATE approximation: matching
        #X_t = test[test['T']==True]
        #X_c = test[test['T']==False]
        #y_t = X_t['y']
        #y_c = X_c['y']
        #tau_t = est.effect(X_t[variables_model], T0=0, T1=1)
        #df_match_error, match_error = tau_error_matching(X_t, X_c, y_t, y_c, tau_t, confounders)
        #match_error_all.append(match_error)
        #print(f"Match error on validation data: {match_error_all[aa]:.4f}")

        aa = aa+1

    print(np.mean(ate_all))
    print (np.mean(auuc))
    #print (np.mean(cfB_all))
    #print (np.mean(match_error_all))

    ate_all_models.append(ate_all)
    auuc_models.append(auuc)
    cfB_all_models.append(cfB_all)
    match_error_all_models.append(match_error_all)


#%%
# Talletetaan hyperparametrien etsintädata


model_ate = []
model_auuc = []
model_c_for_benefit = []
match_error = []
for k in range (len(auuc_models)):
    m, lb, hb = mean_confidence_interval(ate_all_models[k], confidence=0.95)
    model_ate.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    m, lb, hb = mean_confidence_interval(auuc_models[k], confidence=0.95)
    model_auuc.append(str(np.round(m,5)) + ' (' + str(np.round(lb,4)) + ',' + str(np.round(hb,4))+')')
    #model_c_for_benefit.append(str(np.round(np.mean(cfB_all_models[k]),3)) + ' (' + str(np.round(np.min(cfB_all_models[k]),3)) + ',' + str(np.round(np.max(cfB_all_models[k]),3))+')')
    #match_error.append(str(np.round(np.mean(match_error_all_models[k]),4)) + ' (' + str(np.round(np.min(match_error_all_models[k]),4)) + ',' + str(np.round(np.max(match_error_all_models[k]),4))+')')

df_model_selection = pd.DataFrame()
df_model_selection['ML model'] = model_names
df_model_selection['ATE, mean (CI 95%)'] = model_ate
df_model_selection['AUUC, mean (CI 95%)'] = model_auuc
#df_model_selection['C-for-benefit, mean (min,max)'] = model_c_for_benefit
#df_model_selection['Match error, mean (min,max)'] = match_error

file_name = '/data/hyperparameters_anticholinergic_falls'
with pd.ExcelWriter(presentation_dir+file_name+'.xlsx', engine = 'openpyxl', if_sheet_exists = 'replace', mode = 'a') as writer:
    df_model_selection.to_excel(writer, sheet_name = 'CF')



#%%
# Mikä malli valitaan??
est_cf = models[2]





#%%
variables_model = confounders[:]
est_cf = est_cf.fit(Y = y_train_all, T = x_train_all['T'], X = x_train_all[variables_model], W = x_train_all[variables_model], cache_values=True)
treatment_effects = est_cf.effect(x_test[variables_model], T0=0, T1=1)
lb, ub = est_cf.effect_interval(x_test[variables_model], T0=0, T1=1, alpha=0.05)
print ('ATE:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

ite_model_name.append('Causal forest (ECONML)')
ate_list.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Talletetaan test_data
x_test_cf_learner = x_test
x_test_cf_learner['treatment_effects'] = treatment_effects.tolist()
df_ITE_values['CF'] = x_test_cf_learner['treatment_effects']





#%%
# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("Causal forest: Uplift curve");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_cf.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))



#%%
# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')



#%%

df_uplift = uplift_by_percentile(y_test, (treatment_effects), x_test['T'], 
                     strategy='overall', 
                     total=True, std=True, bins=5)

rr_treatment = df_uplift['response_rate_treatment'].reset_index(drop=True)[:5]
rr_control = df_uplift['response_rate_control'].reset_index(drop=True)[:5]
std_treatment = df_uplift['std_treatment'].reset_index(drop=True)[:5]
std_control = df_uplift['std_control'].reset_index(drop=True)[:5]

x=[]
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[:int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[1*int(11595/5):2*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[2*int(11595/5):3*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[3*int(11595/5):4*int(11595/5)].mean()[0])
x.append(pd.DataFrame(treatment_effects[0:]).sort_values(by=[0], ascending=False).reset_index(drop=True)[4*int(11595/5):].mean()[0])


fig = plt.figure()
y = rr_treatment
yerr = std_treatment

yc = rr_control
yerrc = std_control

plt.errorbar(x, y, yerr=yerr, label='Treatment group')

plt.errorbar(x, yc, yerr=yerrc, label='Control group')
plt.title('Causal forest', fontsize=14)
plt.ylabel('Unsteady gait rate', fontsize=14)
plt.xlabel('Estimated ITE', fontsize=14)
plt.legend(loc='lower left', fontsize=14)
fig.savefig(presentation_dir + '/imgs/FIG_uplift_by_percentile_cf.png')




#%%
# Plot histogram 
fig=plt.figure(facecolor='white')
plt.hist(treatment_effects.tolist(), bins=100)
plt.xlabel('ITE estimate')
plt.ylabel('Count')
plt.title('Causal forest')
plt.show()
fig.savefig(presentation_dir + '/imgs/FIG_ite_histograms_CF.png')


# Surogate DT
intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=4, min_samples_leaf=30)
intrp.interpret(est_cf, x_test[confounders])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_4_CF.pdf',bbox_inches='tight',facecolor='white')

intrp = SingleTreeCateInterpreter(include_model_uncertainty=False, max_depth=5, min_samples_leaf=30)
intrp.interpret(est_cf, x_test[confounders])
plt.figure()
intrp.plot(feature_names=confounders_name, fontsize=4)
plt.savefig(presentation_dir + '/imgs/FIG_intrp_tree_5_CF.pdf',bbox_inches='tight',facecolor='white')



# Plot treatment effect + CI
plt.rc('xtick', labelsize=32) #fontsize of the x tick labels
plt.rc('ytick', labelsize=32) #fontsize of the x tick labels
df = pd.DataFrame()
df['te'] = treatment_effects
df['lb'] = lb
df['ub'] = ub
df.sort_values('te', inplace=True, ascending=True)
df.reset_index(inplace=True, drop=True)
z = df.rolling(window=10, center=True).mean()
fig, ax = plt.subplots(figsize=(24, 16))
ax.plot(z['te'],
        marker='.', linestyle='-', linewidth=2, label='ITE', color='indigo')
ax.plot(z['lb'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.plot(z['ub'],
        marker='.', linestyle='-', linewidth=0.1, color='steelblue')
ax.set_title('Causal forest', fontsize = 36)
ax.set_ylabel('Difference in absolute risk of \n unsteady gait', fontsize = 28)
ax.set_xlabel('Patients (sorted)', fontsize = 36)
ax.legend(fontsize = 36)
ax.hlines(y=0, xmin=0, xmax=len(z), linewidth=4, color='k', linestyle='--')
plt.show()
fig.savefig(presentation_dir + '/imgs/FIG_sorted_ite_CF.png')
plt.rc('xtick', labelsize=12) #fontsize of the x tick labels
plt.rc('ytick', labelsize=12) #fontsize of the x tick labels

plt.style.use(['default'])

ite_and_ci_results.append([str(z['te'].min()),str(z['te'].max()),str((z['te']<0).sum()/len(z)),str((z['ub']<0).sum()/len(z)),str((z['ub']<0).sum())])


#%%
# SHAP
shap_values = est_cf.shap_values(X = np.array(x_test[variables_model], dtype=float))
df_shap_values = pd.DataFrame()

k=11
for bb in range (len(variables_model)):
    list_temp = []
    for aa in range(len(shap_values[outcome]['T_1'].values)):
        list_temp.append(list(shap_values[outcome]['T_1'].values[aa])[bb])
    df_shap_values[str(bb)] = list_temp
df_variables_names = pd.DataFrame()
df_variables_names['code'] = confounders
df_variables_names['names'] = confounders_name
names = []
for aa in range(len(variables_model)):
    names.append(df_variables_names[df_variables_names['code']==variables_model[aa]]['names'].reset_index(drop=True)[0])
df_shap_mean_abs = pd.DataFrame()
df_shap_mean_abs['codes_'+outcome] = variables_model
df_shap_mean_abs['names_'+outcome] = names
df_shap_mean_abs['SHAP_'+outcome] = list(df_shap_values.abs().mean()) 
df_shap_mean_abs.to_csv(presentation_dir + '/data/intrp_shap_CF_'+outcome+'.csv')
plt.figure(facecolor=(1, 1, 1))
plt.title('Causal forest')
shap.summary_plot(shap_values[outcome]['T_1'], max_display = 10, feature_names = names)
plt.savefig(presentation_dir + '/imgs/FIG_shap_CF.png', dpi=300, bbox_inches='tight')





#%%
# Concordance-statistics for benefit (TE MATCHING) BOOSTRAPPING
cfB_all = []
for rr in range (100):
    print (rr)
    x_test['y'] = y_test
    X_t = x_test[x_test['T'] == True].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)
    X_c = x_test[x_test['T'] == False].sample(frac=0.3, replace=True, random_state=rr).reset_index(drop=True)

    point_t = est_cf.effect(X_t[variables_model], T0=0, T1=1)
    point_c = est_cf.effect(X_c[variables_model], T0=0, T1=1)
    X_t['te'] = point_t
    X_c['te'] = point_c
    
    df_treatment_matched, df_control_matched = matching_te(X_t, X_c)
    (df_treatment_matched['y'] - df_control_matched['y']).mean()
    predicted_benefit_t = df_treatment_matched['te']
    observed_outcome_t = df_treatment_matched['y']
    predicted_benefit_c = df_control_matched['te']
    observed_outcome_c = df_control_matched['y']

    result_vector, df_c_for_benefit = c_for_benefit(predicted_benefit_t,observed_outcome_t,predicted_benefit_c,observed_outcome_c)

    cfb = result_vector.count('c') / (result_vector.count('c')+result_vector.count('d'))
    cfB_all.append(cfb)

cfb_mean = np.round(np.mean(cfB_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(cfB_all)-1, loc=np.mean(cfB_all), scale=st.sem(cfB_all))[1],3)
print(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

c_for_benefit_list.append(str(cfb_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')






#%%
# PDP plots
ATE = np.mean(treatment_effects)

confounders_shap_sorted = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['codes_'+outcome])
confounders_shap_sorted_names = list(df_shap_mean_abs.sort_values(by=['SHAP_'+outcome],ascending=False)['names_'+outcome])
for vari_nro in range(len(confounders_shap_sorted)):
    print ('PDP: ' + confounders_shap_sorted[vari_nro] + ' ' + str(vari_nro) + '/' + str(len(confounders_shap_sorted)))
    df_ite_temp = pd.DataFrame()
    samples = 250
    for dd in range(samples):
        print (dd)
        int_rand = random.randint(0, len(x_train_all)-1)
        patients_copy_row = x_train_all[confounders_shap_sorted].reset_index(drop=True)[int_rand:int_rand+1]
        patients_copy = pd.DataFrame()
        for cc in range (100): patients_copy = patients_copy.append(patients_copy_row, ignore_index = True) 

        for gg in range(len(patients_copy)):
            patients_copy[confounders_shap_sorted[vari_nro]][gg] = gg * x_train_all[confounders_shap_sorted[vari_nro]].max()/len(patients_copy)

        point = est_cf.effect(patients_copy[confounders], T0=0, T1=1)
        point_list = []
        for aa in range(len(point)):
            point_list.append(point[aa].tolist())
        df_ite_temp[str(dd)] = point_list

    # mean and ci of ITE
    ite_mean = []
    ite_ci_low = []
    ite_ci_high = []
    value = []
    for jj in range(len(df_ite_temp)):
        values = list(df_ite_temp[jj:jj+1].T[jj])
        ite_mean.append(np.mean(values))
        ite_ci_low.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[0])
        ite_ci_high.append(st.t.interval(alpha=0.95, df=samples-1, loc=np.mean(values), scale=st.sem(values))[1])
        value.append((x_train_all[confounders_shap_sorted[vari_nro]].astype(float).max()-x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min()) *(jj * 1/len(patients_copy)) + x_train_all[confounders_shap_sorted[vari_nro]].astype(float).min())

    # plot
    df = pd.DataFrame()
    df['te'] = ite_mean
    df['lb'] = ite_ci_low
    df['ub'] = ite_ci_high
    df['value'] = value
    z = df
    fig, ax = plt.subplots(figsize=(12, 12),facecolor='white')
    ax.plot(z['value'], z['te'],
            marker='.', linestyle='-', linewidth=2, color='indigo')
    ax.plot(z['value'], z['lb'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.plot(z['value'], z['ub'],
            marker='.', linestyle='-', linewidth=0.1, color='steelblue')
    ax.set_ylabel('ITE estimates', fontsize = 36)
    ax.set_xlabel(confounders_shap_sorted_names[vari_nro], fontsize = 36)
    ax.legend(fontsize = 36)
    ax.xaxis.set_tick_params(labelsize=24)
    ax.yaxis.set_tick_params(labelsize=24)
    ax.hlines(y=ATE, xmin=z['value'].min(), xmax=z['value'].max(), linewidth=4, color='k', linestyle='--')
    plt.show()
    fig.savefig(presentation_dir + '/imgs/FIG_PDP_CF_'+str(vari_nro)+'.png', bbox_inches='tight')




#%%
# SENSITIVITY ANALYSIS
#----------------------------

random.seed(111)
T_train_shuffle = x_train_all['T'].copy()
random.shuffle(T_train_shuffle)

# Train model and estimate values for test data
est_cf = est_cf.fit(Y = y_train_all, T = T_train_shuffle, X = x_train_all[variables_model], W = x_train_all[variables_model], cache_values=True)
treatment_effects = est_cf.effect(x_test[variables_model], T0=0, T1=1)
lb, ub = est_cf.effect_interval(x_test[variables_model], T0=0, T1=1, alpha=0.05)

ate_list_random.append(str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

print ('ATE shuffle:')
print (str(np.round(np.mean(treatment_effects),3)) + ' [' + str(np.round(np.mean(lb),3)) +','+str(np.round(np.mean(ub),3)) +']')

# Plot uplift curve
plt.style.use(['default'])
uplift_disp=plot_uplift_curve(y_test, treatment_effects, x_test['T'], perfect=False);
uplift_disp.figure_.suptitle("Causal forest: Uplift curve (Random Treatment)");
plt.tight_layout()
plt.savefig(presentation_dir + '/imgs/FIG_uplift_curve_cf_RANDOM_T.png', facecolor='white', transparent=False)
print (uplift_auc_score(y_test, (treatment_effects), x_test['T']))

# Bootstrap AUUC
auuc_all = []
df_y_te = pd.DataFrame()
df_y_te['y'] = y_test
df_y_te['te'] = treatment_effects
df_y_te['T'] = x_test['T']
for kk in range (1000):
    df_y_te_sample = df_y_te.sample(frac=0.3, replace=True, random_state=seed+kk).reset_index(drop=True)
    auuc_all.append(uplift_auc_score(df_y_te_sample['y'], df_y_te_sample['te'], df_y_te_sample['T']))
auuc_mean = np.round(np.mean(auuc_all),3)
ci_low = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[0],3)
ci_high = np.round(st.t.interval(alpha=0.95, df=len(auuc_all)-1, loc=np.mean(auuc_all), scale=st.sem(auuc_all))[1],3)
print ('AUUC shuffle:')
print(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')

auuc_list_random.append(str(auuc_mean) + ' [' + str(ci_low) + ', ' + str(ci_high) + ']')










#%%
# Average treatment effect (ATE), area under the uplift curve (AUUC) and c-for-benefit measures.
df_ITE_results = pd.DataFrame()
df_ITE_results['Algorithm'] = ite_model_name
df_ITE_results['ATE [CI95%]'] = ate_list
df_ITE_results['AUUC [CI95%]'] = auuc_list
#df_ITE_results['C-for-benefit [CI95%]'] = c_for_benefit_list

#file_name = 'Article_material/Tables_main_text'
#with pd.ExcelWriter(presentation_dir+file_name+'.xlsx', engine = 'openpyxl', if_sheet_exists = 'replace', mode = 'a') as writer:
#    df_ITE_results.to_excel(writer, sheet_name = 'Table 2 performance')

df_ITE_results.to_csv(presentation_dir + '/data/df_models_ave_performance.csv')

#%%
# Correlation matrix between models
df_corr = df_ITE_values.corr()
df_corr.to_csv(presentation_dir + '/data/df_corr_models.csv')



#%%
# Sensitivity analysis
df_sensitivity = pd.DataFrame()
df_sensitivity['Algorithm'] = ite_model_name
df_sensitivity['ATE [CI95%]'] = ate_list_random
df_sensitivity['AUUC [CI95%]'] = auuc_list_random

df_sensitivity.to_csv(presentation_dir + '/data/df_models_random_performance.csv')

#%%
# ITE + CI95 plot values
"""
df_ite_and_ci_results = pd.DataFrame()
df_ite_and_ci_results['values'] = ite_and_ci_results[0]
df_ite_and_ci_results['DML'] = ite_and_ci_results[1]
df_ite_and_ci_results['DR'] = ite_and_ci_results[2]
df_ite_and_ci_results['X'] = ite_and_ci_results[3]
df_ite_and_ci_results['CF'] = ite_and_ci_results[4]
"""












