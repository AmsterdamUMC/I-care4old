# Description of analysis data set, MS26 Impact of social engagement and actitivities, WP6

## General information

D5.3 & 5.5 Characterization NH patients' groups
- Responsible consortium partner
Charles University, Czech Republic
- Contact person, email and affiliation
-	Jitka Pokladníková (selection of analysed items), POKLJ7AA@faf.cuni.cz, Department of Social and Clinical Pharmacy, Charles University, Hradec Kralové, Czech Republic
-	Shireen Aziz (python code application) email: azizshi@faf.cuni.cz, Affiliation: Department of Social and Clinical Pharmacy, Charles University, Hradec Kralove, Czech Republic.
- Short description of data contents, analysis purpose, and methods
This retrospective study analyzed data from the Dutch Comprehensive Academic Search (CAS), Netherlands. Clinical assessment data routinely collected using standardized interRAI between 2005-2023 in long term care residents (LTCF). Main purpose of this analysis is to predict impact of selected non-pharmacological (social engagement, spiritual care and musical therapy) interventions on various outcomes (CPS, DRS, HUI, ADLH, hospitalization). For each resident, the time intervals (the number of days) between every two adjacent assessments were calculated. Two assessments (baseline, follow-up) with a time interval of 120-240 days were selected for each resident. When there were more than one such pair, one was randomly selected.
- Sample size 
Overall, a total sample of 45037 assessments with 12012 residents from LTCF Dutch databases were analysed.
- Netherlands, LTCF: n=12012. Time windows of recruitment: 06/06/2005 – 02/02/2023. Note: the sample from Netherlands was restricted to LTCF setting

## Data processing
- Sample restrictions (age limit, morbidities etc.)
Residents aged 60 years or older from 2007-2022, with the baseline assessments (the first or routine assessments) and the 6-month follow-up were included in the final data set (n=4782).
- Major re-codings or transformations applied
1.	iA9 (Date of assessment): converted in date format if not; Recoding of the chronic conditions: coded as 1 if a diagnosis is present, irrespective of whether it is the primary diagnosis or/and receiving active treatment, and 0 otherwise.
2.	ia4 (Marital status; 1 = Never married, 2 = Married, 3 = with partner, 4=Widowed, 5= Separated, 6 = Divorced) recorded as 1: 2,3; 0: 1, 4, 5,6 
3.	ij8a (smoke; 0= no, 1=not in last 3 days but usually a smoker ,2= yes) recorded as 1: 1,2; 0: 0
4.	ij8b (Alcohol (no of drinks); 0= no, 1= 1 in last 14 days ,2= 2-4 in last 14 days, 3=5 or more in last 14 days) recorded as 1: 2,3; 0: 0,1
5.	if1c (social interaction; 0=never, 1= more than 30 days ago, 2= 8-30days ago, 3= 4-7days ago, 4= in last 3 days, 5= unable to determine) recorded as 1= 1,2,3,4; 0=0,8
6.	ie1k (expression of lack of pleasure in life; 0=not present,1=present but exhibited in last 3 days,2= exhibited on 1-2 of last 3 days,3=exhibited daily in last 3 days) recorded as 1: 1,2,3; 0;0
7.	ia12a (living arrangements; 1=alone, 2=with spouse/partner, 3=with spouse/partner or others, 4=with child, 5=with parents, 6=with siblings, 7= with other relatives, 8= with non-relatives, 9= in residential care) recorded as 1: 1,2,3,4,5,6,7,8,9; 0: 1
8.	Categorical variables like marital status, social interaction, chronic diseases, living arrangements, lifestyle factors (smoking, alcohol) coded as 1 for "Yes" and 0 for "No" as binary variable

How missing values were handled
- Missing items more than 30% (change in ADL, mental health residence history) were excluded, and other missing data was imputed using the 1-nearest neighbor algorithm.  

Short description of the methods used in each analysis phase (phases may include model training, validation etc.; more detailed description can be left to the deliverable itself)
- Data from LTCF Netherlands used to analyse various non-pharmacological interventions, based on activity preferences and involvement various social activities (e.g. cards, games, puzzles, computer activity, conversing or talking on phone, crafts, arts, music, dancing, discussion, exercise support and so on) from inter RAI instrument were analysed for various outcomes such as DRS, CPS, ADLH, and HUI, hospitalization. Data from year 2007-2022 was included, various confounders from previous literature and clinical expert selection were selected. Data preprocessing involved several steps to prepare the dataset for analysis. Missing values were imputed using the 1-nearest neighbors (k-NN) algorithm to minimize data loss. The following regression machine learning models were implemented: Gradient Boosting Regressor, Multi-Layer Perceptron (MLP), Random Forest Regressor, Decision Tree Regressor, Lasso, Ada Boost Regressor, Extra Tree Regressor, Bagging Regressor, Ridge Regression, and Linear Regression. The dataset was split into 80% for training and 20% for testing, with the aim of evaluating the model's performance on out-of-sample data. A propensity score was utilized to mitigate any treatment assignment biases, using a simple Inverse Propensity Treatment Weighting (IPTW) procedure. Each model was trained separately for the treatment and control groups to estimate the Individual Treatment Effects (ITE) using T-learner and the Average Treatment Effect (ATE, the average of ITEs). Sample characteristics (basic demographics, clinical conditions and functional status) were described in LTCF data. Then, Shapley Additive Explanations (SHAP) values were used to interpret the contribution of individual predictors to model predictions. Further validation analysis is currently being conducted on the Finland dataset. 

Countries whose data were used and contact person
- The Netherlands, Eline Tankink - Kooijmans (e.c.m.kooijmans@amsterdamumc.nl) 

## Data contents
General description of the data contents
- Data comprised information on socio-demographic and clinical (e.g., number of chronic diseases) characteristics and functional and mental health features such as physical functioning (ADL), cognitive impairment (CPS) and depressive symptoms (DRS), hearing, vision and lifestyle (smoking, alcohol, exercise). 

List of variables using harmonised names and short descriptions 
- iA9: Date of assessment
- iA2: Gender
- iA8: Assessment type 
- Age: Age at the assessment 
- sADLH: Activities of daily living 
- sCPS: Cognitive performance scale 
- sDRS: Depression rating scale 
- sPain: Pain scale
- sRISE_LTCF: Rise index long term care facility
- iI1c: Alzheimer’s disease 
- iI1d: Dementia other than Alzheimer’s disease 
- iI1j: Stroke/CVA 
- iI1k: Coronary heart disease
- iI1l: Congestive heart failure 
- iI1m: Chronic obstructive pulmonary disease (COPD) 
- iI1o: Depression 
- iI1p: Schizophrenia 
- iI1s: Cancer 
- iI1t: Diabetes mellitus 
- if1c: Interaction with family members
- if1d: Loneliness
- id3a: Hearing
- id4a: Vision
- ij8a: Smoking
- ij8b: Alcohol

Data sources (including e.g., interRAI form version) and important notes on the contents, such as connections to other data sets
- InterRAI Long Term Care Facility (LTCF) v.9.1 are used. 

## Publications
Articles or other written publications made using this data set (manuscript preparation)
- Presented poster on the topic ‘Impact of Social Engagement on Cognitive Function in Long-Term Care Facility Residents: A Machine Learning Approach’(ESCP conference in Krakow, Poland on 21st October 2024). 
- Presented poster on the 20th EuGMS Valencia, Spain conference on the topic of ‘Impact of Spiritual activities on Cognitive Functions and Activities of Daily Living in Long-term Care Facility Residents in the Netherlands: A Preliminary Result from Machine Learning Approach’ (18th September 2024). 
- Presented poster in collaboration on the 20th EuGMS Valencia, Spain conference on the topic of ‘Exposure to non-pharmacological therapies among older people in long-term care facilities and home care-the ICARE4OLD project ‘(18th September 2024). 
- Presented poster on the topic ‘The Trends in Prevalence of Depression, Psychological Therapy and Minor Social Activities in Nursing Home Residents’(ESCP conference in Bratislava, Slovakia, 24th April 2024).  ‘The Role of Spiritual Engagement in Modulating Cognitive Performance among Geriatric Patients: Insight from Artificial Intelligence Approaches’
