# Description of Analysis Data Set Used with Milestone 26

## General Information
The analyses are related to M26 – trained ML algorithms on impact of non-pharmacological treatments.

**Responsible Consortium Partner:** UJ  
**Contact Person:** Ilona Barańska

## Short Description of Data Content, Analysis Purpose, and Methods
This dataset contains routine care data from multiple long-term care facilities in The Netherlands and Belgium. Data was available from 2005 until the beginning of 2023. In total, 698 persons were included at baseline, and follow-up measurements were included for longitudinal analysis. This data was used for developing trained machine learning algorithms for integration of causal inference and machine learning, to predict treatment effects for non-pharmacological interventions. Multiple machine learning methods have been used: random forest regressor, gradient boosting regressor, multi-layer perceptron regressor, decision tree regressor, linear regression, ridge regression, lasso regression, Adaboost regressor, extra trees regressor, bagging regressor, and TARNet.

**Non-Pharmacological Interventions (NPIs) Included:** Physical therapy (in3eb)  
**Outcome Included:** ADLSF (Activities of Daily Living Short Form)

## Data Processing
A follow-up time between measurements of 90 to 210 days was used. For the analysis of physical therapy (PT), individuals with unstable conditions (ij6a), flare-up (ij6b), end-stage disease (ij6c), and GI/GU bleeding (ij2r) were excluded from the analysis.

Inclusion and exclusion criteria were selected for the study sample. Then, confounders were selected based on the NPI and outcome variable. Because a subsample of the population needs to be selected, the confounders were partly based on indications and contra-indications. Next, treatment exposure was defined. For the purposes of analysis, patients were categorized into two groups: those who received at least 30 minutes of physical therapy in the past 7 days at baseline and continued therapy at follow-up, and those who did not receive any physical therapy during that period.

In this analysis, the outcome variable is continuous, so it can be replaced with any other continuous variable. Both the intensity of therapy (e.g., increasing the threshold to 45 minutes) and the interval between assessments can be adjusted, depending on the analytical objectives.

Missing values were imputed using knn-imputer with 5 neighbors. Dummy variables were created for nominal variables. A propensity score for OutcomeT0 (ADL in baseline) was calculated and included in the model. Then the analysis was run.

## Data Contents
The dataset contains information on demographic characteristics, clinical, psychological, and functional features. InterRAI LTCF (HC) v.9.1 was used.

### Variables Included per NPI and Outcome Variable
| Variable Code | Description                                  |
|---------------|----------------------------------------------|
| sADLSF        | Outcome: ADL Short Form (iG2b, iG2f, iG2h, iG2j) |
| in3eb         | NPI: Physical therapy                        |
| ij6c          | End-stage disease                            |
| ij6a          | Unstable conditions                          |
| ij6b          | Flare-up                                     |
| ij2r          | GI/GU bleeding                               |
| ij2d          | Unsteady gait                                |
| ij2c          | Dizziness                                    |
| ij2a          | Difficulty standing                          |
| ij2b          | Difficulty turning around                    |
| ii1e          | Hemiplegia                                   |
| ii1f          | Multiple sclerosis (MS)                      |
| sAGE_cat      | Age                                          |
| sDRS          | Depression Rating Scale (iE1a, iE1b, iE1c, iE1d, iE1e, iE1f, iE1g) |
| sCPS          | Cognitive Performance Scale (iC1, iC2a, iD1, iG2j) |
| ih1           | Bladder continence                           |
| ih3           | Bowel continence                             |
| il7           | Foot problems                                |
| ig2b          | Personal hygiene - performance               |
| ig2f          | Locomotion on same floor (unit) - performance |
| ig2j          | Eating - performance                         |
| ig2h          | Toilet use - performance                     |
| ID            | ID                                           |
| iA2           | Gender                                       |
| iA9           | Reference Date                               |

## Publications
- Not yet.