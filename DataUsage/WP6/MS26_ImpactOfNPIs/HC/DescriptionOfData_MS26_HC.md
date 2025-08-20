# Description of analysis data set used with Milestone 26 / M6.5

## General information
M26 – trained ML algorithms on impact of non-pharmacological treatments

### Responsible consortium partner: 
Stichting VU

### Contact person:
Eline Kooijmans/Hein van Hout

## Short description of data content, analysis purpose and methods

This dataset contains routine care data from multiple homecare organizations in The Netherlands. Data was available from 2005 until beginning of 2023. In total 5521 persons were included at baseline, and follow-up measurements were included for longitudinal analysis. This data was used for developing trained machine learning algorithms for integration of causal inference and machine learning, to predict treatment-effects for non-pharmacological interventions. Multiple machine learning methods have been used; Random forest regressor, gradient boosting regressor, multi-layer perceptron regressor, decision tree regressor, linear regression, ridge regression, lasso regression, Adaboost regressor, extra trees regressor, bagging regressor, TARNet.

NPIs included in the current analysis were exercise (ig6a) and home nurse/home health aides (computed by adding in3ab + in3bb). Outcomes included in the analysis were: ADLLF, Hospitalization (in5a), CHESS, CPS and HUI3.

## Data processing
A follow-up time between measurements of between 90 and 270 days was used. For the analysis of exercise, people receiving palliative care (in2m) were excluded, as well as people with end-stage disease (ij6c), people with severe to excruciating pain (ij5b) and people with severe fatigue (ij4). For home health aides/home nurse no people were excluded in the analysis. Missing values were imputed using KNN-imputer with 5 neighbors.

In-and exclusion criteria were selected for the study sample. Then, confounders were selected based on NPI and outcome variable. Because a subsample of the population needs to be selected, the confounders were (partly) based on indications and contra-indications. Then, exposure to treatment was defined.
For physical therapy patients were divided into groups with more than 60 minutes of exercise in the last 3 days, and patients with no exercise in the last 3 days.
For home health aides/home nurse a minimum of 150 minutes was used for the treatment group compared to none for the control group (clean compare).

Multicollinear columns were automatically removed from the dataset with a correlation threshold of 0.6.
An undersampling procedure was not used.  Missing values were imputated using knn-imputer with 5 neighbors.
A propensity score was calculated and also included in the model.
Then the analysis was run, and a variable importance list was printed. Based on this list, the most important variables defining the outcome were selected, and the analysis was run again with only these variables included.

For ADLLF and HUI3 outcomes a regression model was used. For the CPS and CHESS a classification model was used, and for hospitalization a dichotomous model was used.

## Data contents

Dataset contains information on demographic characteristics, clinical, psychological and functional features. InterRAI Home Care (HC) v.9.1 was used.

### Variables included per NPI

**Exercise**:
- ih5: ostomy 
- iA2: gender
- ij12: recent falls 
- ij2a: difficulty standing
- ij2c: dizziness
- ii1a: hip fracture 
- ii1b: other fracture
- ii1c: alzheimers 
- ii1d: other dementia
- ii1e: hemiplegia
- ii1f MS
- ii1g: paraplegia
- ii1h parkinsons 
- ii1j stroke
- ii1k: coronary heart disease
- ii1m: COPD
- ii1lL CHF
- ij5a: pain frequency
- id2: ability to understand others
- il7: foot problems
- sAGE_cat: age
- ij2b: difficulty turning around
- ij2d: unsteady gait
- ij1: falls
- ig7a: person believes can improve

**Home nurse/home health aides**:
- ia12a: living arrangement
- ia13: time since last hospital stay 
- ih1: bladder continence
- ih3: bowel continence
- ih2: urinary collection device
- ih5: ostomy
- ii1c: alzheimers
- ii1d: other dementia
- ii1f: MS
- ii1j: Stroke
- ij3: dyspnea
- ij6b: flare-up
- il1: most severe pressure ulcer
- in2e: oxygen therapy
- in2k: wound care
- in2l: scheduled toileting program
- ip2a: unable to continue informal care
- ip2c: family overwhelmed
- ii1b: other fracture
- ij12: recent falls
- ij2s: peripheral edema
- ij6a: unstable conditions
- ii1a: hip fracture


## Publications

None planned.
