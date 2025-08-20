# HOSPITALIZATION

## General information

**Deliverable**: Prediction Model for Hospitalization Among Home Care Clients

**Consortium Partner**: Hebrew SeniorLife, Profility, Inc.

**Contact**: John N Morris, email: jnm@hsl.harvard.edu, Hebrew SeniorLife

**Description of Data Contents, Analysis Purpose, Methods**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems.

**Sample Size**: The baseline sample consisted of 2,359,166 assessments and the follow-up cohort included 1,451,766 assessments. For interRAI HC assessments, previous hospitalization within 90 days is recorded at the time of baseline assessment. Follow-up assessments provide hospital use records for approximately months 9 through 11 months because, on average, there were approximately 9 to 11 months between baseline and follow-up assessments.

## Data Processing

**Sample Restrictions**: Among the client cohort, 26.4% lived with a spouse and/or another relative, 30.2% lived alone, and 14.5% lived with a child. Average age at baseline was 76.9 years; 12.7% were 90 years of age or older and 15.8% were <65. The majority were female (57.8%) and married (29.5%).

**Major Re-coding or Transformations**: In most instances, variables with multiple values were recoded as dichotomous. Beyond the file creation, there were no major transformations.

**How Missing Values were Handled**: For missing values, cases with many missing items were removed prior to analysis. For some missing items, the value equivalence was set to NO.

**Methods for Analysis**: Analyses of international home care assessment data at baseline and first follow-up, approximately 11 months post-baseline (n=1,451,766). The primary dependent measure was hospitalization in the three months prior to follow-up. For the total cohort, we next identified a subset of independent variables that met “clinically meaningful” minimal odds ratio criterion with Hosp2. Variables entering the final multivariate model had a minimum univariate odds ratio of 1.20 or higher. Logistic regression process occurred in two steps resulting in two sub-models; the first sub-model was for persons without a baseline hospital stay, and the second sub-model, for persons with one or more baseline hospitalizations.

**Country Source and Contact for Data**:

Data (full combined data set) is housed in US. John Morris is contact person.

Jurisdictions providing data included Canadian Provinces–Ontario, Manitoba, British Columbia, Alberta, Newfoundland, and Nova Scotia. US data came from New York, New Jersey, Missouri, Georgia, Massachusetts, Louisiana, Arkansas, Connecticut, Maryland, and Michigan. Other assessments were from mandated home care programs in New Zealand, and several European countries. Representative subsets of cross-European cases previously derived from the EU-funded AD HOC study and I-BENC project also were included.

## Data contents

**General description of the data contents**: The HC assessment provides information needed to produce comprehensive care plans and information to create descriptive scales, resource use estimates, program quality indicators, and demographic characteristics.

**Data sources**: interRAI Home Care version 2.0

**Number of variables**: 24 – 17 for those without a prior hospitalization, 7 for those with a prior hospitalization

**List of variables**:

| Variable Code | Variable Name (HC) | Description |
| --- | --- | --- |
| | | **SUB-MODEL 1 – NO BASELINE HOSPITAL STAY (mean hosp time2=15.2%) (n=942,327)** |
| | | **Clinical – Cardio / Respiratory** |
| Ii1l | J1b | Congestive heart failure – yes |
| II1m | J1z | COPD, emphysema – yes |
| Ii1b | J10 | Other fracture – yes |
| | | **Clinical Conditions – Instability** |
| Ik2a | L1a | Weight loss – 5% (30 days); 10% (180 days) |
| Ii1r | J1w | Urinary tract infection |
| Ir2 | P6 | Deteriorated in last 90 days, receives more support |
| Il1 | N2a | Pressure ulcer – yes |
| Il3 | N2b | Stasis ulcer – yes |
| Il4 | N3a, N3b | Skin lesions or burns – yes to either |
| I2ac-fc, Icd10 (N17, N17.9, N19) | J1aa | Renal failure/dialysis – yes |
| Ii1s | J1x | Cancer – yes |
| | | **Functional Related** |
| Ij1 | K5 | One or more falls in last 90 days – yes |
| Ig1aa | H1aa | Independent in meal preparation – yes |
| Ig3 | H4a | Locomotion indoors – with walker/crutch |
| | | **Care Measures That Reflect Complexity** |
| In2k | N5c | Wound care – yes |
| In2d | P2h, P2i | IV infusion – yes to either |
| In5b | P4b | Emergency room visit – yes |
| | | **SUB-MODEL 2 – BASELINE HOSPITAL STAY (mean hosp time2=54.4%) (n=509,439)** |
| | | **Clinical Status** |
| Ii1l | J1b | Congestive heart failure |
| II1m | J1z | COPD, emphysema |
| I2ac-fc, Icd10 (N17, N17.9, N19) | J1aa | Renal failure / dialysis |
| Ik2a | L1a | Weight loss – 5% (30 days); 10% (180 days) |
| Ij7 | K8a | Client feels in poor health - yes |
| | | **Functional Measures** |
| Ig1aa | H1aa | Independent in meal preparation – yes |
| Ig1ga | H1fa | Independent in shopping - yes |

## Publications

**Manuscript currently being revised for resubmission to Geriatric Nursing**:

*Predicting Risk of Hospitalization Among Adult Home Care Clients: An International Perspective*

John N. Morris, Elizabeth P. Howard, Erez Schachter, Sharran N. Burney, Anna Laytham, Daniela Fialova, Vanja Pešić
