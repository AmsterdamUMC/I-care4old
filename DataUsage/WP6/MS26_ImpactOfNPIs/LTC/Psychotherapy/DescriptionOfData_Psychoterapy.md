# Description of analysis data set, MS26 Impact of psychotherapy, WP6

## General information

Responsible consortium partner:  
- Charles University, Czech Republic

Contact person, email and affiliation: 
- Jitka Pokladníková (selection of analysed items), POKLJ7AA@faf.cuni.cz, Department of Social and Clinical Pharmacy, Charles University, Hradec Kralové, Czech Republic
- Jindra Reissigová (Python code application), reisj2a1@faf.cuni.cz, Department of Social and Clinical Pharmacy, Charles University, Hradec Kralové, Czech Republic

Short description of data contents, analysis purpose, and methods:  
- This retrospective study used data collected in the Long-Term Care Facilities (LTCF) setting using the interRAI (Resident Assessment Instrument) assessment form during the period from 2014 to 2018 in Canada. 
- The aim was to estimate the effect of psychotherapy on treatment of 1. cognitive functions, 2. frailty and health disability, and 3. functional independence. These outcome variables were measured on the cognitive performance scale (CPS), the changes in health, end-stage disease and signs and symptoms scale (CHESS), and the activities of daily living short scale (ADL), respectively. 
- The effect of psychotherapy (at least 15 minutes provided in last 7 days at baseline assessment) was assessed approximately three months (specifically 60 to 120 days) after psychotherapy in the LTCF residents aged 60 years and over. 

Sample size:  Out of 400748 residents in 2014-2018, a total of 3246 were selected for all analyses.

## Data processing

Sample restrictions: Inclusion and exclusion criteria are stated below, see Clinical indications and Contraindications. The baseline assessments were based on the admission assessments or the full annual assessments.

Major re-codings or transformations applied:
- AA2 (sex; M = Male, F = Female, O = Other): renamed to AA2.female and recoded as 1: Female; 0: Male
- A5 (Marital status at admission; 1 = Never married, 2 = Married, 3 = Widowed, 4 = Separated, 5 = Divorced, 9 = Unknown): renamed to A5. married and recorded as 1: 2; 0: 1, 3, 4, 5 
- A3 (Assessment date): converted to date format
- E4AA (Wandering; 0 = Not exhibited in last 7 days, 1 = Occurred 1 to 3 days in last 7 days, 2 = Occurred 4 to 6 days in last 7 days, but less than daily, 3 = Occurred daily ); E4AB (Wandering; 0 = Not present or behaviour was easily altered, 1 = Not easily altered): renamed to E4AA.123_E4AB.1 and recorded as 1: E4AA = 1/2/3 & E4AB=1; 0: Otherwise
- C1 (Hearing; 0 = Hears adequately, 1 = Minimal difficulty, 2 = Hears in special situations only, 3 = Highly impaired), C2B (Hearing aid, present and not used regularly; 0 = No, 1 = Yes, 8 = Comatose): renamed to C1.3_C2B.1 and recorded as 1: C1 = 3 & C2B = 1; 0: Otherwise

How missing values were handled: Missing values in marital status (14.5% in A5. married) were imputed using the 1-nearest neighbor algorithm.  There were no missing values in the other variables. 

Short description of the methods used in each analysis phase:  
- The analysis was done using the pre-prepared Python code, version 5.5, with one pair of assessments (baseline, 3-month follow-up) randomly selected for each resident analysed, if there were multiple such pairs.
- Multicollinearity was considered when correlation coefficient 0.75 or higher. 
- Treatment and control groups were designed to have the same size (undersampling strategy was performed). 
- The dataset (3246 residents, i.e. 1623 per group) was split into training and testing datasets using the 80/20 rule. 
- Seven classification machine learning models were used to estimate the effect of psychotherapy on the CPS and CHESS outcomes:  Random Forest Classifier, Multi-Layer Perception Classifier, Decision Tree Classifier, Adaptive Boosting Classifier, Gradient Boosting Classifier, Extra Tree Classifier, Logistic Regression. In the case of the ADL outcome, the following ten regression models were run: Random Forest Regressor, Multi-Layer Perception Regressor, Decision Tree Regressor, Adaptive Boosting Regressor, Gradient Boosting Regressor, Extra Tree Regressor, Linear Regression, Ridge, Lasso, Bagging Regressor. 
- Propensity score weighting method was used to ensure comparability of treatment and control groups at baseline. 
- The performances of the classification models were evaluated using accuracy in the training and testing datasets, and the regression models using R-squared, the mean absolute error (MAE) and the mean square error (MSE).  
- The average treatment effect (ATE) was then calculated in the test data set at three months from baseline. The ATE was calculated as the average of the individual treatment effects (ITE) estimated using the T-learner algorithm.

Countries whose data were used and contact person for each country: Canada, micaela.jantzi@uwaterloo.ca

## Data contents
General description of the data contents: The data included information on socio-demographic characteristics, and health status of the LTCF residents.

Data sources: Canada, interRAI LTCF Assessment Form

List of variables using harmonised names and short descriptions:

Outcomes
1.	cps_nh2: CPS
2.	chess_nh2: CHESS 
3.	ADL_short_nh2: ADL  

Treatment
P1BEB: Total minutes of psychotherapy in the last 7 days

Confounders
- AGE_ASSESSMENT: Age at assessment
- AA2.female: Female sex of the resident
- A5.married: Married status at admission
- chess_nh2: CHESS scale (excluded from confounders when CHESS was outcome)
- G8A: Resident believes self to be capable of increased independence in at least some ADLs
- G8B: Direct care staff believe resident is capable of increased independence in at least some ADLs
- I1A: Diabetes mellitus
- I1AA: Parkinson’s disease
- I1BB: Quadriplegia
- I1C: Hypothyroidism
- I1D: Arteriosclerotic Heart Disease
- I1F: Congestive Heart Failure
- I1JJ: Asthma
- I1KK: Emphysema
- I1R: Alzheimer’s
- I1RR: Cancer
- I1V: Dementia, not Alzheimer’s
- I1W: Hemiplegia/Hemiparesis
- I1Y: Multiple sclerosis
- I1Z: Paraplegia
- O1: Number of medications
- O4A: Antipsychotic: number of days during last 7 days
- O4B: Antianxiety: number of days during last 7 days
- O4C: Antidepressant: number of days during last 7 days
- O4D: Hypnotic: number of days during last 7 days
- P1BCA: Number of days of physical therapy administered for 15 min daily in the last 7 days
- P1BCB: Total minutes of physical therapy in the last 7 days 
- P2A: Special behaviour symptom evaluation program
- P2B: Evaluation by a licensed mental health specialist in last 90 days
- P2C: Group therapy
- P2D: Resident-specific deliberate changes in the environment to address mood/behaviour/patterns
- P2E: Reorientation e.g. cueing
- P5: Number of times resident was admitted to hospital in last 90 days
- P6: Number of times resident visited ER in last 90 days
- P7: In the last 14 days, on how many days has the physician examined the resident

Contraindications (the feature values)
- B1: Comatose (1 = Yes)
- cps_nh2: CPS (5,6)
- P1AO: Hospice care (1 = Yes) 
- C5: Speech Clarity (1 = Unclear speech, 2 = No speech)
- C1.3_C2B.1: Hearing (1 = Highly impaired & Hearing aid, present and not used regularly)

Clinical indications (the feature values)
- drs_nh2: DRS (3-14)

Mood and behaviour patterns, items from E1A to E1P (1 = Exhibited up to 5 days a week, 2 = Exhibited daily or almost daily (6, 7 days a week))
- E1A: Resident makes negative statements (1,2)
- E1B: Repetitive questions (1,2)
- E1C: Repetitive verbalizations (1,2)
- E1D: Persistent anger with self or others (1,2)
- E1E: Self-deprecation (1,2)
- E1F: Expressions of what seem to be unrealistic fears (1,2)
- E1G: Recurrent statements that something terrible is about to happen (1,2)
- E1H: Repetitive health complaints (1,2)
- E1I: Repetitive anxious complaints/concerns (1,2)
- E1J: Unpleasant mood in morning (1,2)
- E1K: Insomnia/Change in usual sleep pattern (1,2)
- E1L: Sad, pained, worried facial expressions (1,2)
- E1M: Crying, tearfulness (1,2)
- E1N: Repetitive physical movements (1,2)
- E1O:  Withdrawal from activities of interest (1,2)
- E1P: Reduced social interaction (1,2)
- E2: Mood persistence in last 7 days (1 = Present, easily altered, 2 = Present, not easily altered)
- E4AA.123_E4AB.1: Wandering (1 = Exhibited & Not easily altered)
- I1FF: Anxiety Disorder (1 = Yes)
- I1GG: Depression (1 = Yes)
- I1HH: Manic depressive (1 = Yes)
- I1II: Schizophrenia (1 = Yes)
- K3A: Weight loss 5% or more in last 30 days (1 = Yes)
- K3B: Weight gain 5% or more in last 30 days (1 = Yes)
- P1AM: Alcohol/Drug treatment program (1 = Yes)
- P1AN: Alzheimer’s/Dementia special care unit (1 = Yes)

It should be noted that different combinations of confounders and clinical indications were entered into the models to avoid overfitting. In addition to the settings mentioned above (missing data imputation, multicollinearity, undersampling, propensity score weighting), we also tested other settings (e.g., no missing data imputation, and so on).

## Publications

No publication considered. No functional ML models were derived to estimate the effect of psychotherapy on the analysed outcomes (CPS, CHESS, ADL). The number of the LTCF residents receiving psychotherapy was very low.

## Comments on the Python code, version 5.5
Based on our work with the Python code, we recommend some improvements to it, which may be useful for further scientific work:
- The eligibility criteria should only be applied to baseline, but the criteria (contra indication, clinical indication) are also applied to the follow-up assessment.
- The follow-up period is based on adjacent assessments. The Python code does not allow skipping assessments after baseline, for example when the follow-up is one year. This could result in selection bias, as only residents who have no other assessments between baseline and 1-year follow-up are selected. For this reason, we limited to a three-month follow-up (in Canada, assessments are done regularly every three months).
- Multicollinearity is assessed using the Pearson correlation coefficient, but this coefficient is not suitable for all features, e.g. when assessing the correlation between two binary variables.
- In some cases, missing values are imputed inappropriately (imputation is based on the 5-nearest neighbors algorithm). For example, missing values in a binary variable (which takes on the values 0 and 1) are imputed with decimal numbers. For this reason, we used the 1-nearest neighbor imputation. Note that there are recommendations for when it is appropriate to impute missing values (missingness could be of 3 type: be missing completely at random, missing at random, missing not at random). 
- In classical statistical analysis, the calculation of the propensity score generally distinguishes whether the characteristics affect treatment, the outcome, or both. The quality of the model for calculating the conditional probability of treatment (i.e. propensity score) should be also verified. 
- It would be advantageous if the Python code also allowed easy access to other features besides outcome at follow-up (preferably all of those confounders entering the model at baseline). For example, it would be useful to know how the intervention changed from baseline to the follow-up.
- In the ITEs plots, we would recommend displaying the 95% confidence interval instead of the standard deviations, and also adding some discrimination and calibration metrics and error analysis. This would also make it easier to choose the best model.
- Since the values of the outcome variables are also measured at baseline, a repeated measures design should be taken into account. It would also be worth considering the possibility of time-varying confounders.  Then it would not be necessary to randomly select one pair of assessments (baseline, 3-month follow-up) from each resident for analysis.
