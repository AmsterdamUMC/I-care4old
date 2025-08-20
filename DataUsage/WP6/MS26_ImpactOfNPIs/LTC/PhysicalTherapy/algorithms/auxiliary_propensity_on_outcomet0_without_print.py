from sklearn.impute import KNNImputer
import numpy as np
import pandas as pd
import pickle

# import necessary libraries
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

from sklearn.utils import resample


#from sklearn.impute import KNNImputer
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score, accuracy_score, f1_score
from sklearn.model_selection import GridSearchCV

# get standard models
from sklearn.linear_model import LogisticRegression
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPRegressor

from sklearn.cluster import KMeans
import numpy as np


from datetime import timedelta
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import NearestNeighbors
from sklearn.linear_model import LogisticRegression
import pandas as pd
import numpy as np
import os
import pickle

def data_processing(file, undersampled, include_propensity, machine, intervention, outcome, target='OutcomeT1', treatment='treatment', caliper=0.2, zmienne=None):
    """
    Przetwarza dane, przeprowadza undersampling, oblicza propensity score dla contraindications,
    ale bez dzielenia na train/test w przypadku clinicalindications.
    """
    # Wczytanie danych
    
    data = pd.read_csv(file)
#     print(data.dtype)
    
    
    
#     data = pd.get_dummies(data =, columns = ['ih1', 'ih3', 'il7', 'ij2d', 'ij2c', 'ij2b','iA2'], drop_first=True , dtype =int)
#     print(data.dtypes)
    
    
    # Przeprowadzenie undersamplingu
    if undersampled:
        freq_treated = len(data[data[treatment] == 1])
        control = data[data[treatment] == 0].sample(freq_treated)
        treated = data[data[treatment] == 1]
        data = pd.concat([control, treated])

    # Usuwanie braków danych
    data = data.dropna(axis=1)
    # Izolacja zmiennych
    X = data.drop(columns=[target, 'treatment']).columns
    outcomes = target
    # Obliczanie propensity score tylko dla contraindications, jeśli podano
    if zmienne is not None:
        # Wybieramy tylko kolumny związane z contraindications
        # The change is here: using double square brackets to create a DataFrame
        X_treated = data.query(f'{treatment} == 1')[zmienne]
        X_control = data.query(f'{treatment} == 0')[zmienne]

        # Dopasowanie modelu regresji logistycznej dla propensity score
        ps_model = LogisticRegression(C=1e2, max_iter=10000).fit(
            pd.concat([X_control, X_treated]),  # X_combined = X_control + X_treated
            pd.concat([data.query(f'{treatment} == 0')[treatment], data.query(f'{treatment} == 1')[treatment]])  # y_combined = control + treated
        )

        # example, replace if you have more variables
        # Dodanie propensity score do grupy treated i control
        data.loc[data[treatment] == 1, 'ps'] = ps_model.predict_proba(X_treated)[:, 1]
        data.loc[data[treatment] == 0, 'ps'] = ps_model.predict_proba(X_control)[:, 1]

    else:
        ps_model = None# Jeżeli nie podano clinicalindications, nie obliczamy propensity score

    # Jeśli include_propensity == False, usuwamy kolumnę 'ps' z całego zbioru danych
    if not include_propensity:
        data.drop(columns=['ps'], inplace=True, errors='ignore')
    # Zapisywanie modelu propensity score, jeśli został obliczony
    if ps_model:
        os.makedirs('storage', exist_ok=True)
        filename_prob_score_model = f"storage/propensity_score_model_{intervention}-{outcome}.sav"
        pickle.dump(ps_model, open(filename_prob_score_model, 'wb'))

    treated_data = data[data[treatment] == 1]
    control_data = data[data[treatment] == 0]

    #Sortowanie po propensity score
    treated_data_sorted = treated_data.sort_values(by='ps')
    control_data_sorted = control_data.sort_values(by='ps')
#     print(treated_data_sorted)
#     print(control_data_sorted)

#     import matplotlib.pyplot as plt

# # Wykres rozkładu `ps` dla grupy leczonej i kontrolnej
#     plt.hist(treated_data_sorted['ps'], bins=20, alpha=0.5, label='Treated')
#     plt.hist(control_data_sorted['ps'], bins=20, alpha=0.5, label='Control')
#     plt.legend()
#     plt.show()
# #     #Lista dopasowanych par

#     display(treated_data_sorted['ps'].value_counts())
#     display(control_data_sorted['ps'].value_counts())


    matched_pairs = []
    matched_controls = set()  # Zbiór, aby uniknąć duplikatów

#     display(treated_data_sorted)
# Dopasowanie na podstawie najbliższej wartości propensity score z uwzględnieniem caliper
    for idx_treated, row_treated in treated_data_sorted.iterrows():
    # Szukamy wszystkich możliwych dopasowań w granicach caliper

        possible_matches = control_data_sorted[(control_data_sorted['ps'] - row_treated['ps']).abs() <= caliper]


        if not possible_matches.empty:
        # Szukamy wszystkich możliwych dopasowań i bierzemy tylko te, które jeszcze nie zostały dopasowane
            possible_matches = possible_matches[~possible_matches.index.isin(matched_controls)]


            if not possible_matches.empty:
            # Dopasuj wszystkich kontrolnych pacjentów, którzy spełniają warunek caliper
                closest_match = possible_matches.iloc[(possible_matches['ps'] - row_treated['ps']).abs().argmin()]
                matched_controls.add(closest_match.name)
                matched_pairs.append((idx_treated, closest_match.name))

# Liczymy liczbę dopasowanych przypadków
    matched_treated_count = len(matched_pairs)
    unmatched_treated_count = len(treated_data_sorted) - matched_treated_count
    unmatched_control_count = len(control_data_sorted) - matched_treated_count



# Zbieramy dopasowane dane
    treated_matched_data = [treated_data_sorted.loc[matched_pairs[i][0]] for i in range(matched_treated_count)]
    control_matched_data = [control_data_sorted.loc[matched_pairs[i][1]] for i in range(matched_treated_count)]

# Łączymy obie listy danych w jeden DataFrame
    matched_data = pd.DataFrame(treated_matched_data + control_matched_data)

# Zapisujemy dane do pliku CSV
    matched_data.to_csv(f"matched_data_{intervention}_{outcome}.csv", index=False)

# Wyświetlamy dane
#     print(matched_data)
    matched_data1 = matched_data.drop('ps', axis=1)
    matched_data1 = matched_data1.drop(zmienne, axis=1)

#     print(matched_data1)

    OutcomeT1 ='OutcomeT1'

    y_control =matched_data1.query('treatment==0')['OutcomeT1']
    X_control =matched_data1.drop(columns=OutcomeT1).query('treatment==0')
    #print(f"Mean_control_outcomeT0: {X_control['OutcomeT0'].mean()}")
#     display(f"y_control: {len(y_control)}")
#     display(f"X_control: {len(X_control)}")

    y_treated =matched_data1.query('treatment==1')['OutcomeT1']
    X_treated =matched_data1.drop(columns=OutcomeT1).query('treatment==1')
   # print(f"Mean_treatment_outcomeT0: {X_treated['OutcomeT0'].mean()}")
#     display(f"y_treated: {len(y_treated)}")
#     display(f"X_treated: {len(X_treated)}")

  
    X_train_c, X_test_c, y_train_c, y_test_c = train_test_split(X_control, y_control, test_size = 0.3)
    X_train_t, X_test_t, y_train_t, y_test_t = train_test_split(X_treated, y_treated, test_size = 0.3)
    
    
    X_train_c = X_train_c.drop(columns =['treatment'])
    X_train_t = X_train_t.drop(columns =['treatment'])
    X_test_c  = X_test_c.drop(columns =['treatment'])
    X_test_t  = X_test_t.drop(columns =['treatment'])
    X_combined_c = pd.concat([X_train_c, X_test_c], axis =0).reset_index(drop=True)
    X_combined_t = pd.concat([X_train_t, X_test_t], axis =0).reset_index(drop=True)


    return X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t,X_combined_c,X_combined_t

###############################################################################################################################
def doubly_robust(df, X, T, Y):
    ps = LogisticRegression(C=1e2, max_iter=10000).fit(df[X], df[T]).predict_proba(df[X])[:, 1]
    mu0 = LinearRegression().fit(df.query(f"{T}==0")[X], df.query(f"{T}==0")[Y]).predict(df[X])
    mu1 = LinearRegression().fit(df.query(f"{T}==1")[X], df.query(f"{T}==1")[Y]).predict(df[X])
    
    print(f"Estimated outcome under control {np.mean(mu0)}.")
    print(f"Estimated outcome under treatment {np.mean(mu1)}.")
    
    return (
        np.mean(df[T]*(df[Y] - mu1)/ps + mu1) -
        np.mean((1-df[T])*(df[Y] - mu0)/(1-ps) + mu0)
    )

def visualise(predictions_t, predictions_c, y_test_t, y_test_c, machine, target, intervention):
    sns.set_palette('Set2')
    sns.set_theme(style="whitegrid")#sns.color_palette('vlag')
    
    # predictions into dataframe and append
    pred_t = pd.DataFrame([predictions_t, y_test_t, ['treated' for i in range(len(y_test_t))]]).T
    pred_c = pd.DataFrame([predictions_c, y_test_c, ['control' for i in range(len(y_test_c))]]).T
    pred = pred_t.append(pred_c)
    pred.columns = ['Predicted', 'True', 'Type']

    # separate predicted and true
    predicted = pred['Predicted']
    true = pred['True']

    # plot
    plt.figure(figsize=(12,6))
    sns.scatterplot(x=predicted, y=true, hue = pred['Type'])
    plt.title(f'Predicted vs. True Outcomes for {intervention}-{target} using {machine}')
    plt.legend()

    # store result
    #plt.savefig(f"results/{machine}/Meta{intervention}-{target}.png", dpi=300)    
    
    plt.show()
    
def visualise_ites(ites, machine, target, intervention, split="test"): 
    ites = [i[0] for i in ites.reshape(-1,1)]
    ites = sorted(list(ites))

    x_values = range(1, len(ites) + 1)
    stdev = np.std(ites)
    upper_bound = [val + stdev for val in ites]
    lower_bound = [val - stdev for val in ites]

    sns.set(style="whitegrid")

    #plt.figure(figsize=(8,4))
    plt.figure(figsize=(12,6))

    plt.fill_between(x_values, lower_bound, upper_bound, color='gray', alpha=0.2, label="standard deviation")
    plt.axhline(y=np.mean(ites), color='red', linestyle='--', label='ATE estimate')
    plt.xlabel("Ordered Patient Indices")
    plt.ylabel(target)
    plt.title(f"Orded ITE-estimates for {intervention}-{target} pair on {split}.")
    
    print(f"ATE {np.mean(ites)}")

    sns.lineplot(x=x_values, y=ites, marker='o', color='b', label='predicted ITE values', ci=stdev)
    plt.savefig(f"plots/{machine}-{intervention}-{target}.png", dpi=300)

    plt.show()
    
    
    
def visualise_ites_proba(ites, machine, target, intervention, split="test"): 
    ites = [i[0] for i in ites.reshape(-1,1)]
    ites = sorted(list(ites))

    x_values = range(1, len(ites) + 1) 
    stdev = np.std(ites)
    upper_bound = [val + stdev for val in ites]
    lower_bound = [val - stdev for val in ites]

    sns.set(style="whitegrid")

    #plt.figure(figsize=(8,4))
    plt.figure(figsize=(12,6))

    plt.fill_between(x_values, lower_bound, upper_bound, color='gray', alpha=0.2, label="standard deviation")
    plt.axhline(y=np.mean(ites), color='red', linestyle='--', label='ATE estimate')
    plt.xlabel("Ordered Patient Indices")
    plt.ylabel(target)
    plt.title(f"Orded Prediction of Probabilities for {intervention}-{target} pair on {split}.")
    
    print(f"Probabilistic ATE {np.mean(ites)}")

    #x_values = [i + 0.5 for i in x_values]
    
    sns.lineplot(x=x_values, y=ites, marker='o', color='b', label='predicted ITE values', ci=stdev)
    plt.savefig(f"plots/probabilities-{machine}-{intervention}-{target}.png", dpi=300)

    plt.show()
    
def undersample(df, kind = "control"):
    # undersample control
    if kind == "control":
        # number of treated
        freq_treated = len(df[df['treatment']==1])
        control = df[df['treatment']==0].sample(freq_treated)
        treated = df[df['treatment']==1]
    elif kind == "treated":
        freq_control = len(df[df['treatment']==0])
        control = df[df['treatment']==0]
        treated = df[df['treatment']==1].sample(freq_control)

    df = pd.concat((control, treated))
    
    return df



# Function to calculate prediction intervals
def get_prediction_intervals(predictions, percentile=95):
    lower_bound = np.percentile(predictions, (100 - percentile) / 2.0, axis=0)
    upper_bound = np.percentile(predictions, 100 - (100 - percentile) / 2.0, axis=0)
    return lower_bound, upper_bound

# Function to compute bootstrapped confidence intervals
def bootstrap_confidence_intervals(model, X, y, n_bootstrap=100, percentile=95):
    predictions_bootstrap = []
    for i in range(n_bootstrap):
        #print(i)
        bootstrap_indices = np.random.choice(range(len(X)), size=len(X), replace=True)
        X = np.array(X)
        y = np.array(y)
        X_bootstrap = X[bootstrap_indices]
        model.fit(X_bootstrap, y[bootstrap_indices])
        predictions_bootstrap.append(model.predict(X))
    predictions_bootstrap = np.array(predictions_bootstrap)
    return get_prediction_intervals(predictions_bootstrap, percentile)
    
def run_model(n_bootstraps, file, model0, model1, machine, intervention, outcome, include_propensity, undersampled = False, num_iter = 1, zmienne =None):
    # if more iterations are necessary
    maec, maet, msec, mset, rtc, rtt = [], [], [], [], [], []
    tr_maec, tr_maet, tr_msec, tr_mset, tr_rtc, tr_rtt = [], [], [], [], [], []
    
    
    X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t,X_combined_c,X_combined_t= data_processing(file,undersampled,
                                                                                                         include_propensity, machine,
                                                                                                         intervention, outcome,
                                                                                                         target='OutcomeT1',
                                                                                                         treatment='treatment', caliper=0.2,
                                                                                                       zmienne =zmienne )
   
   

    f_c = model0
    f_c.fit(X_train_c, y_train_c)
    predictions_c = f_c.predict(X_test_c)
    # treated
    f_t = model1
    f_t.fit(X_train_t, y_train_t)

    predictions_t = f_t.predict(X_test_t)

    maec.append(mean_absolute_error(predictions_c, y_test_c))
    maet.append(mean_absolute_error(predictions_t, y_test_t))
    msec.append(mean_squared_error(predictions_c, y_test_c))
    mset.append(mean_squared_error(predictions_t, y_test_t))
    rtc.append(r2_score(y_test_c, predictions_c))
    rtt.append(r2_score(y_test_t, predictions_t))
    
    predictions_t_train = f_t.predict(X_train_t)
    predictions_c_train = f_c.predict(X_train_c)
    

    tr_maec.append(mean_absolute_error(predictions_c_train, y_train_c))
    tr_maet.append(mean_absolute_error(predictions_t_train, y_train_t))
    tr_msec.append(mean_squared_error(predictions_c_train, y_train_c))
    tr_mset.append(mean_squared_error(predictions_t_train, y_train_t))
    tr_rtc.append(r2_score(y_train_c, predictions_c_train))
    tr_rtt.append(r2_score(y_train_t, predictions_t_train))

    # compute ITEs for test
    ites_t = f_t.predict(X_test_t) - f_c.predict(X_test_t)
    ites_c = f_t.predict(X_test_c) - f_c.predict(X_test_c)
    # compute Individual treatment effects
    ites_test = np.append(ites_t, ites_c)

    # compute ITEs for train
    ites_t_train = f_t.predict(X_train_t) - f_c.predict(X_train_t)
    ites_c_train = f_t.predict(X_train_c) - f_c.predict(X_train_c)
    # compute Individual treatment effects
    ites_train = np.append(ites_t_train, ites_c_train)

    # compute relevant errors and record 
    results = {'MAE_C (test)': np.mean(maec),
               'MAE_T (test)': np.mean(maet),
                'MSE_C (test)': np.mean(msec),
                'MSE_T (test)': np.mean(mset),
                 'R2_C (test)': np.mean(rtc),
                 'R2_T (test)': np.mean(rtt),
              'MAE_C (train)': np.mean(tr_maec),
               'MAE_T (train)': np.mean(tr_maet),
                'MSE_C (train)': np.mean(tr_msec),
                'MSE_T (train)': np.mean(tr_mset),
                 'R2_C (train)': np.mean(tr_rtc),
                 'R2_T (train)': np.mean(tr_rtt)}

    hyperparameters = f_t.get_params()
    print(hyperparameters)

    # Convert to DataFrame
    df = pd.DataFrame([hyperparameters])
    df.to_csv(f'C:/Users/Paulina.Wisniewska/Desktop/Do_wyslania/hyperparameters/model_hyperparameters_{machine}.csv')

    metrics = pd.DataFrame.from_dict(results, orient = 'index', columns = [machine])
    metrics.to_csv(f"C:/Users/Paulina.Wisniewska/Desktop/Do_wyslania/results/model_results_{machine}_{intervention}-{outcome}.csv")
    
    filename_t = f"C:/Users/Paulina.Wisniewska/Desktop/Do_wyslania/storage/model_t_{machine}_{intervention}-{outcome}.sav"
    filename_c = f"C:/Users/Paulina.Wisniewska/Desktop/Do_wyslania/storage/model_c_{machine}_{intervention}-{outcome}.sav"

    # save models
    pickle.dump(f_t, open(filename_t, 'wb'))
    pickle.dump(f_c, open(filename_c, 'wb'))

    # Compute ITEs for test
    ites_t = f_t.predict(X_test_t) - f_c.predict(X_test_t)
    ites_c = f_t.predict(X_test_c) - f_c.predict(X_test_c)
    
    outcome_under_treatment = np.concatenate([f_t.predict(X_test_t), f_t.predict(X_test_c)])
    outcome_under_treatment = np.mean(outcome_under_treatment)
    
    outcome_under_control = np.concatenate([f_c.predict(X_test_t), f_c.predict(X_test_c)])
    outcome_under_control = np.mean(outcome_under_control)
   
    print(f"(Test) ATE {outcome_under_treatment - outcome_under_control}.")
    
    

    # Compute individual treatment effects
    ites_test = np.concatenate([ites_t, ites_c])
    
    ate_confidence(model0, model1, machine, X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t, n_bootstraps = n_bootstraps)
    
        
    return metrics, predictions_t, predictions_c, y_test_t, y_test_c, ites_test, ites_train, X_test_t, X_test_c, X_train_c, X_train_t, y_train_c, y_train_t,X_combined_c,X_combined_t



def ate_confidence(model0, model1, machine, X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t, n_bootstraps = 1000):
    
    f_c_samp = model0
    f_t_samp = model1
    
    # Number of bootstrap samples

    # Placeholder for predictions
    #predictions = np.zeros((n_bootstraps, len(X_test)))
    ates = []
    
    # Bootstrapping
    for i in range(n_bootstraps):
        # Resample the training data
        X_resampled_c, y_resampled_c = resample(X_train_c, y_train_c)
        X_resampled_t, y_resampled_t = resample(X_train_t, y_train_t)

        f_c_samp = model0
        f_c_samp.fit(X_resampled_c, y_resampled_c)
        predictions_c = f_c_samp.predict(X_resampled_c)
        # treated
        f_t_samp = model1
        f_t_samp.fit(X_resampled_t, y_resampled_t)
        predictions_t = f_t_samp.predict(X_resampled_t)
        
        # compute ITEs for test
        ites_t_samp = f_t_samp.predict(X_resampled_t) - f_c_samp.predict(X_resampled_t)
        ites_c_samp = f_t_samp.predict(X_resampled_c) - f_c_samp.predict(X_resampled_c)
        
        ites_samp = np.concatenate([ites_t_samp, ites_c_samp])
        # compute Individual treatment effects
        ates.append(np.mean(ites_samp))
        
    #print(f"ATE Conf. Interval {np.mean(ates)}")
    
    # Calculate the 95% confidence intervals (2.5th and 97.5th percentiles)
#     lower_bound = np.percentile(ites_samp, 2.5, axis=0)
#     upper_bound = np.percentile(ites_samp, 97.5, axis=0)
    
    
#     lower = np.percentile(ites_samp, 2.5)
#     upper = np.percentile(ites_samp, 97.5)
    
#     print(f"ATE: {np.mean(ates):.2f}, 95% CI: [{lower:.2f}, {upper:.2f}]")
    
    ate_mean = np.mean(ates)
    ate_vars = np.var(ates, ddof=1)
    ate_se = np.sqrt(ate_vars)
    critical_value = 1.96
    ci_lower = ate_mean - critical_value + ate_se
    ci_upper = ate_mean + critical_value + ate_se
    
    print(f"ATE: {ate_mean:.2f}, 95% CI: [{ci_lower:.2f}, {ci_upper:.2f}]")


def run_model_class(n_bootstraps, file, model0, model1, machine, intervention, outcome, include_propensity, undersampled = False, num_iter = 1, zmienne =None):
    
    acc_c, acc_t, f1_c, f1_t = [], [], [], []
    train_acc_c, train_acc_t = [], []
    
    X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t= data_processing(file, undersampled,
                                                                                                         include_propensity, machine,
                                                                                                         intervention, outcome,
                                                                                                         target='OutcomeT1',
                                                                                                         treatment='treatment', caliper=0.2,
                                                                                                       zmienne =zmienne )
   
    print("")

   
    f_c = model0
    f_c.fit(X_train_c, y_train_c)
    predictions_c = f_c.predict(X_test_c)
    predictions_c_proba = f_c.predict_proba(X_test_c)
    # treated
    f_t = model1
    f_t.fit(X_train_t, y_train_t)
    predictions_t = f_t.predict(X_test_t)
    predictions_t_proba = f_t.predict_proba(X_test_t)

    acc_c.append(accuracy_score(predictions_c, y_test_c))
    acc_t.append(accuracy_score(predictions_t, y_test_t))
#     f1_c.append(f1_score(predictions_c, y_test_c))
#     f1_t.append(f1_score(predictions_t, y_test_t))

    predictions_c_train = f_c.predict(X_train_c)
    predictions_t_train = f_t.predict(X_train_t)
    
    train_acc_c.append(accuracy_score(predictions_c_train, y_train_c))
    train_acc_t.append(accuracy_score(predictions_t_train, y_train_t))

    # compute ITEs for test
    ites_t = f_t.predict(X_test_t) - f_c.predict(X_test_t)
    ites_c = f_t.predict(X_test_c) - f_c.predict(X_test_c)
    # compute Individual treatment effects
    ites_test = np.append(ites_t, ites_c)
    
    outcome_under_treatment = np.concatenate([f_t.predict(X_test_t), f_t.predict(X_test_c)])
    outcome_under_treatment = np.mean(outcome_under_treatment)
    print(f"Test outcome under treatment {outcome_under_treatment}.")
    
    outcome_under_control = np.concatenate([f_c.predict(X_test_t), f_c.predict(X_test_c)])
    outcome_under_control = np.mean(outcome_under_control)
    print(f"Test outcome under treatment {outcome_under_control}.")
    
    print(f"(Test) ATE {outcome_under_treatment - outcome_under_control}.")
    
    
    
    

    # compute ITEs for train
    ites_t_train = f_t.predict(X_train_t) - f_c.predict(X_train_t)
    ites_c_train = f_t.predict(X_train_c) - f_c.predict(X_train_c)
    # compute Individual treatment effects
    ites_train = np.append(ites_t_train, ites_c_train)

    # compute relevant errors and record 
    results = {'ACC_C (Test)': np.mean(acc_c),
               'ACC_T (Test)': np.mean(acc_t),
              'ACC_C (Train)': np.mean(train_acc_c),
              'ACC_T (Train)': np.mean(train_acc_t)}

    hyperparameters = f_t.get_params()
    print(hyperparameters)

    # Convert to DataFrame
    df = pd.DataFrame([hyperparameters])
    df.to_csv(f'hyperparameters/model_hyperparameters_{machine}.csv')

    metrics = pd.DataFrame.from_dict(results, orient = 'index', columns = [machine])
    metrics.to_csv(f"results/model_results_{machine}_{intervention}-{outcome}.csv")
    
    filename_t = f"storage/model_t_{machine}_{intervention}-{outcome}.sav"
    filename_c = f"storage/model_c_{machine}_{intervention}-{outcome}.sav"

    # save models
    pickle.dump(f_t, open(filename_t, 'wb'))
    pickle.dump(f_c, open(filename_c, 'wb'))

    
#     # Calculate confidence intervals for predictions
#     lower_c, upper_c = bootstrap_confidence_intervals(f_c, X_test_c, y_test_c)
#     lower_t, upper_t = bootstrap_confidence_intervals(f_t, X_test_t, y_test_t)

#     # Print prediction intervals
#     print("Control group prediction intervals:")
#     print("Lower:", lower_c)
#     print("Upper:", upper_c)

#     print("\nTreatment group prediction intervals:")
#     print("Lower:", lower_t)
#     print("Upper:", upper_t)


    # Compute ITEs for test
    ites_t = f_t.predict(X_test_t) - f_c.predict(X_test_t)
    ites_c = f_t.predict(X_test_c) - f_c.predict(X_test_c)

    # Compute individual treatment effects
    ites_test = np.concatenate([ites_t, ites_c])
    
    # Compute ITEs for test
    ites_t_proba = f_t.predict_proba(X_test_t)[:,1] - f_c.predict_proba(X_test_t)[:,1]
    ites_c_proba = f_t.predict_proba(X_test_c)[:,1] - f_c.predict_proba(X_test_c)[:,1]

    # Compute individual treatment effects
    ites_test_proba = np.concatenate([ites_t_proba, ites_c_proba])
    
    ate_confidence(model0, model1, machine, X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t, n_bootstraps = n_bootstraps, )
    

    return metrics, predictions_t, predictions_c, y_test_t, y_test_c, ites_test, ites_train, X_test_t, X_test_c, X_train_c, X_train_t, ites_test_proba




def cv_model(k, model0, model1, file, param_grid):
    X_train_c, X_test_c, y_train_c, y_test_c, X_train_t, X_test_t, y_train_t, y_test_t = data_processing(file = file)

    # Perform GridSearchCV with cross-validation on model 0
    grid_search0 = GridSearchCV(estimator=model0, param_grid=param_grid, cv=5, scoring='neg_mean_squared_error')
    score_model0 = cross_val_score(model0, X_train_c, y_train_c, cv = k, scoring = 'neg_mean_squared_error')
    grid_search0.fit(X_train_c, y_train_c)  # X and y are your dataset and target values

    # Get the best hyperparameters and model
    best_params0 = grid_search0.best_params_
    best_model0 = grid_search0.best_estimator_

    # Train the best model on the entire dataset (if needed)
    best_model0.fit(X_train_c, y_train_c)
    predictions_c = best_model0.predict(X_test_c)

    # Perform GridSearchCV with cross-validation on model 1
    grid_search1 = GridSearchCV(estimator=model1, param_grid=param_grid, cv=5, scoring='neg_mean_squared_error')
    score_model1 = cross_val_score(model1, X_train_t, y_train_t, cv = k, scoring = 'neg_mean_squared_error')
    grid_search1.fit(X_train_t, y_train_t)  # X and y are your dataset and target values

    # Get the best hyperparameters and model
    best_params1 = grid_search1.best_params_
    best_model1 = grid_search1.best_estimator_

    # Train the best model on the entire dataset (if needed)
    best_model1.fit(X_train_t, y_train_t)
    predictions_t = best_model1.predict(X_test_t)

    # compute ITEs for test
    ites_t = best_model1.predict(X_test_t) - best_model0.predict(X_test_t)
    ites_c = best_model1.predict(X_test_c) - best_model0.predict(X_test_c)
    # compute Individual treatment effects
    ites_test = np.append(ites_t, ites_c)
    
    # compute ITEs for test
    ites_t_train = best_model1.predict(X_train_t) - best_model0.predict(X_train_t)
    ites_c_train = best_model1.predict(X_train_c) - best_model0.predict(X_train_c)
    # compute Individual treatment effects
    ites_train = np.append(ites_t_train, ites_c_train)
    
    return np.mean(-score_model0), np.mean(-score_model1), ites_test, ites_train, y_test_t, y_test_c, predictions_t, predictions_c

def impute_missing_values_knn(df, n_neighbors=5):
    # Copy the original DataFrame to avoid modifying it
    imputed_df = df.copy()

    # Initialize KNNImputer with the specified number of neighbors
    imputer = KNNImputer(n_neighbors=n_neighbors)

    # Perform KNN imputation on the DataFrame
    imputed_array = imputer.fit_transform(imputed_df.values)

    # Convert the imputed array back to a DataFrame
    imputed_df = pd.DataFrame(imputed_array, columns=imputed_df.columns)

    return imputed_df

def value_based_contra_indications_tracker(df, value_based_contra_indications):
    # initialize empty tracker
    contra_indication = lambda x: 1 if x > 0 else 0
    index_tracker = []

    # iterate over columns and corresponding values 
    for key, value in value_based_contra_indications.items():    
        patients_to_be_dropped = list(df[df[key]>value].index)
        for i in patients_to_be_dropped:
            index_tracker.append(i)

    df = df.drop(index=list(set(index_tracker)))
    print(f'{len(set(index_tracker))} observations with value-based contra-indications')
    
    return df

def full_contra_indications_tracker(df, contra_indications):
    # initialize empty tracker
    contra_indication = lambda x: 1 if x > 0 else 0
    index_tracker = []
    # check if there are selected counterindications
    for col in contra_indications:
        # first check if contra indication applies
        contra_ind = df[col].apply(contra_indication)
        # mark items with a contra-indication
        for i in list(contra_ind[contra_ind==1].index):
            index_tracker.append(i)
    
    print(f'{len(set(index_tracker))} observations with contra-indications')
    df = df.drop(index=list(set(index_tracker)))
    
    return df

def period_decomposition(df, target):
    # create temp df
    temp_df = pd.DataFrame(columns = list(df.columns) + ['OutcomeT0', 'OutcomeT1', 'OutcomeT0Date', 
                                                         'OutcomeT1Date'])#, 'AssesmentNumber'])
    counter = 0
    total = len(set(list(df['Clientid'])))

    # for each patient
    for i in set(list(df['Clientid'])):
        counter += 1
        if (counter % 1000) == 0:
            print(f'{counter} out of {total} items completed...')
        date_list = list(df[df['Clientid']==i]['iA9'])

        # for each date
        for j in range(len(date_list)):
            date_baseline = date_list[j]

            # check if end of list is reached
            if j+1 < len(date_list):
                date_followup = date_list[j+1]
                subdf = df[df['Clientid']==i][df[df['Clientid']==i]['iA9']==date_baseline]
                subdf['OutcomeT0'] = float(df[df['Clientid']==i][df[df['Clientid']==i]['iA9']==date_baseline][target])
                subdf['OutcomeT1'] = float(df[df['Clientid']==i][df[df['Clientid']==i]['iA9']==date_followup][target])
                subdf['OutcomeT0Date'] = date_baseline
                subdf['OutcomeT1Date'] = date_followup
                #subdf['AssesmentNumber'] = float(j)

                # append to temp df
                temp_df = temp_df.append(subdf)
            else:
                pass
            
    print("Completed.")
    
    return temp_df

# def multicol(df, correlation_threshold):
#     # Calculate the correlation matrix
#     correlation_matrix = df.corr()

#     # Find pairs of features with correlations greater than +0.25 or less than -0.25
#     high_correlation_pairs = []

#     # create pair list
#     for i in range(len(correlation_matrix.columns)):
#         for j in range(i + 1, len(correlation_matrix.columns)):
#             if (abs(correlation_matrix.iloc[i, j]) > correlation_threshold) and (correlation_matrix.iloc[i, j] != 1):
#                 high_correlation_pairs.append((correlation_matrix.columns[i], correlation_matrix.columns[j]))

#     # Remove one feature from each high-correlation pair
#     for pair in high_correlation_pairs:
#         if pair[0] in df.columns and pair[1] in df.columns:
#             if (pair[0] != 'OutcomeT1') and (pair[0] != 'treatment') and (pair[0] != 'OutcomeT0'):
#                 df.drop(columns=[pair[0]], inplace=True)
#             elif (pair[1] != 'OutcomeT1') and (pair[1] != 'treatment') and (pair[1] != 'OutcomeT0'):
#                 df.drop(columns=[pair[1]], inplace=True)
#             #df.drop(columns=[pair[0]], inplace=True)
            
#     # Generate a mask for the upper triangle
#     mask = np.triu(np.ones_like(correlation_matrix, dtype=bool))

#     # Set up the matplotlib figure
#     f, ax = plt.subplots(figsize=(11, 9))

#     # Generate a custom diverging colormap
#     cmap = sns.diverging_palette(230, 20, as_cmap=True)

#     # Draw the heatmap with the mask and correct aspect ratio
#     sns.heatmap(correlation_matrix, mask=mask, cmap=cmap, vmax=.3, center=0,
#                 square=True, linewidths=.5, cbar_kws={"shrink": .5})

#     plt.show()
            
#     return df