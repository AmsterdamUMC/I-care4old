# Description of analysis data set used with MS22

## General information

**MS22 Validated ML algorithms that predict impact on health outcomes**

### Responsible consortium partner: ###

NHG

### Contact person: ### 

Mikko Nuutinen (email: mikko.nuutinen@nhg.fi); affiliations: Nordic Healthcare Group, Helsinki, Finland

### Short description of data contents, analysis purpose, and methods ###

Multi-database cohort study using clinical assessment data routinely collected from Finland, Canada, and Italy. Main goal was to develop model validation pipeline containing processes to evaluate internal and external validity of causal ML models. The data sources were RAI-HC (Resident Assessment Instrument for Home Care) and RAI-LTC (Long Term Care) assessments (MDS 2.0 instruments). The data were collected from the years 2014-2020. 

### Sample size ###
- Finland, LTCF: n=53513, HC: n=77311. Time windows of recruitment: 01/01/2014 – 31/12/202
- Canadian, LTCF: n=200000.
- Italy, HC: n=7813

## Data processing

### Sample restrictions ###

Individuals aged 65 years or older were included, with at least one assessment record within trunked time window.

###  Major re-codings or transformations applied ### 

- N/A

### How missing values were handled ### 

If background information was missing (gender, BMI and age), the client was excluded from the study. If more than 10% of variables (confounders) was missing, the client was excluded from the study. For other binary variables [0, 1], where missing values were judged to mean no positivity (e.g., no pain, no memory problem), the values were replaced with 0. For continuous or categorical ordinal variables missing values or outliers were replaced by the nearest neighbors imputation method.

### Short description of the methods used in each analysis phase ### 

Figure 1 presents the proposed pipeline of causal ML model validation. The pipeline is split in internal and external validation paths. The first step (phase 1) is to choose how generalizability of the models is measured. That is, what data is used for internal and external validation or what data is used for model training and testing. Second step (phase 2) evaluates the main assumptions required for causal modelling. Third step (phase 3) applies surrogate measures for evaluating internal and external validity of causal ML models. The detailed description of each task can be found from the MS22 report.
 
![Figure 1](./img/figure1.png)<br>
*Figure 1. Pipeline of causal ML model validation. ATE: Average Treatment Effect, AUUC: Area Under Uplift Curve, CI: Confidence Interval, ML: Machine Learning, CV: Cross Validation, STD: Standard Deviation*

### Countries whose data were used and contact person for each country ### 
- Finland, Jokke Häsä (jokke.hasa@thl.fi)

##  Data contents

### General description of the data contents ### 
Variables selected for model training (confounders) were based on the domain knowledge with the aid of data-driven approach. Data-driven approach searches candidate confounders by the univariate models that were trained for predicting treatment or outcome. The domain experts were professionals in clinical geriatrics and pharmacology. They use the data-driven results as a candidate list of potential confounders, but the final confounder selection was based on expert opinions.

### List of variables using harmonised names and short descriptions ###

**RAI-MDS HC**
- ABS: ABS;
- ADLH_4: ADLH > 3;
- anticoagulant_temp: Anticoagulants;
- atc_analgesics: Analgesics;
- atc_analgesics : Analgesics;
- atc\_antidepressants\_SSRI_v2: Antidepressants;
- atc\_antipsychotics: Antipsychotics;
- atc\_antithrombotic_agents: Antithrombotic agents;
- atc\_cardiac_therapy: Cardiac therapy;
- atc\_diuretics: Diuretics;
- atc\_hypnotics\_and_sedatives: Hypno-sedative medications;
- BB1: Gender;
- CPS_3: CPS > 3;
- DRS_3: DRS > 3 ;
- E1B_3cat: Persistent anger with self or others (3 cat);
- E1I_3cat: Reduced social interaction;
- F2: Change in social activities;
- H2C_6cat: Locomotion in home (6cat);
- H2G_6cat: Eating (6cat);
- H3: ADL status has become worse;
- H4A: Primary modes of locomotion - Indoors;
- H6B: Hours of physical activities in the last 3 days;
- hilmo\_e\_visits_last6months: ER visits last 6 months (HILMO);
- hilmo\_hospital\_visits_last6months: Hospital visits;
- IKA: Age;
- J1E: Irregular pulse;
- J1S: Any psychiatric diagnosis;
- K3C: Dizziness or lightheadedness;
- K5: Number of times fell in last 90 days;
- K6A: Unsteady gait;
- K8A: Client feels he/she has poor health;
- MMC\_alzheimer_dementia: MMC Alzheimer dementia;
- MMC\_cardio\_respiratory: MMC Cardio_respiratory;
- MMC_cerebrovascular: MMC Cerebrovascular;
- MMC\_non\_alzheimer_dementia: MMC Non-alzheimer dementia;
- MMC_psychiatric: MMC Psychiatric;
- neurological_diagnosis: Neurological diagnosis;
- numberOfComorbidities: Number of comorbidities ;
- numberOfMeds: Number of drugs;
- pain_scale: Pain scale;
- painmed\_or_analgesics: Pain medications or analgesics;
- painmed_temp: Pain medications ;
- painmed_temp  : Pain medication ;
- problems\_because\_of_drinking: Problems because of drinking;
- psychotropic_temp: psychotropic medications ;
- SADLH_hc: ADL hierarchy;
- SADLLF_hc: ADL Long;
- sBMI_hc: BMI;
- SCHESS_hc: CHESS;
- SDRS_hc: DRS;
- unplanned\_hospital\_ER_visit: Unplanned hospital or ER visit;
- unsteady\_gait\_or_falls: Unsteady gait or falls;

**RAI-MDS LTC**
- IKA\_ltc: Age;
- AA3\_\_: Gender;
- sBMI\_ltc: BMI;
- numberOfMeds\_ltc: Number of drugs;
- numberOfComorbidities: Number of comorbidities;
- SCPS\_ltc: CPS;
- SADLH\_ltc: ADLH;
- SDRS\_ltc: DRS;
- ABS: ABS;
- delirium: Delirium scale;
- psychotic\_symptoms: Delusions OR halucinations;
- J1\_N: Unsteady gait;
- acute\_episode\_monitoring\_acute\_condition: Flare-up or monitoring of acute condition;
- hospital\_er\_last6months: Hospital or ER visits (last 6 months);
- Chemotherapy\_or\_end\_stage\_disease: Chemotherapy or end stage disease;
- K1\_D: No mouth problems;
- any\_restrains\_used: Any restrains used;
- Physician\_visits\_doctors\_orders\_changed\_abnormal\_labs: Physician visits, doctors orders changed or abnormal labs;
- SCPS\_ltc : CPS;
- B4\_\_ : Cognitive skills for making every day decisions;
- SADLLF\_ltc : ADLLF;
- B3\_A : Memory recall - current season;
- sBMI\_ltc : BMI;
- B3\_D : Memory recall - that he / she is in a facility;
- IKA\_ltc : Age;
- SCHESS\_ltc : CHESS;
- B6\_\_ : Resident cognitive status, skills or abilities have changed;
- numberOfMeds\_ltc : Number of drugs;
- G1HA\_ : Self performance - eating;
- I1\_Q : Alzheimer;
- G1GA\_ : Self performance - dressing;
- I1\_S : Cerebral palsy;
- E4AA\_ : wandering - density;
- SADLH\_ltc : ADLH;
- J4\_A : Fell in past 30 days;
- B3\_B : Memory recall - location of own room;
- SDRS\_ltc : DRS;
- E4CA\_ : physically abusive symptoms - density;
- B3\_C : Memory recall - staff names / faces;
- E4BB\_ : verbally abusive symptoms - change;
- G1IA\_ : Self performance - toilet;
- J1\_N : Unsteady gait;
- SCHESS\_ltc: SCHESS\_ltc;
- G1HA\_: G1HA\_;
- SADLLF\_ltc: SADLLF\_ltc;
- atc\_memory\_N06D\_ltc: atc\_memory\_N06D\_ltc;

### Data sources for each country ###

- Canada: Canadian interRAI data are collected through interRAI Long-Term Care Facilities (LTCF) Assessment Form, 9.1. 
- Finland: MDS-HC and MDS-LTC instruments are used. 
- Italy: interRAI Home Care (HC) v.9.1 and InterRAI Long Term Care Facility (LTCF) v.9.1 are used.
