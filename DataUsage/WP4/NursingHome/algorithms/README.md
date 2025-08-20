# Algorithm cover sheets, WP4 Home care, I-CARE4OLD

**Work package responsible**: WP 4
**Contact person and main creator**: John N Morris, email: jnm@hsl.harvard.edu

## Algorithm: Hospitalization Among Home Care Clients

**Name of algorithm**: Prediction Model for Hospitalization Among Home Care Clients

**Other creators**: Margaret Bryan

**Purpose of algorithm**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems. 

### List of variables

| Var - I Code | Var Name  pre I Code HC | Var Name |
|--------------|-------------------------|----------|
| | | **_SUB-MODEL 1–NO BASELINE HOSPITAL STAY_**<br />**_(mean hosp time2= 15.2%) (n=942,327)_** |
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
| Il4 | N3a N3b | Skin lesions or burns – yes to either |
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
| | | **_SUB-MODEL 2 – BASELINE HOSPITAL STAY_**<br />**_(mean hosp time2= 54.4%)(n=509,439)_** |
| | | **Clinical Status** |
| Ii1l | J1b | Congestive heart failure |
| II1m | J1z | COPD, emphysema |
| I2ac-fc Icd10 (N17, N17.9, N19) -| J1aa | Renal failure / dialysis |
| Ik2a | L1a | Weight loss – 5% (30 days); 10% (180 days) |
| Ij7 | K8a | Client feels in poor health - yes |
| | | **Functional Measures** |
| Ig1aa | H1aa | Independent in meal preparation – yes |
| Ig1ga | H1fa | Independent in shopping - yes |


## Algorithm: Cognitive Decline Among Home Care Clients

**Name of algorithm**:  Prediction Model for Cognitive Decline Among Home Care Clients

**Purpose of algorithm**: The purpose was to examine changes in cognitive performance among older adult home care clients and to develop and validate a model to predict change. The cognitive status and cognitive change measures were based on the Cognitive Performance Scale version2 (CPS2).  

### List of variables

| Variable Code - I and Program | Equation: One | Equation: Two | Var Name and Code 1 (all others scores = 0) |
|-------------------------------|---------------|---------------|---------|
| | | | **ODDS RATIO OF 1.20 OR HIGHER** |
| Ic1 (B2a2) | | X | Decision-making – 2+ (impaired) |
| Ic4 (b3b) | X | | Agitated, disoriented, difficult to arouse – yes | |
| Ii1h (j1l) | X | | Parkinsonism – yes |
| Age80 | X | | Age 80 or older – yes |
| Age70 | X | X | Age 70 or older – yes |
| Ii1c (j1g) | X | X | Alzheimer’s diagnosis –  yes |
| Ii1d (j1h) | X | X | Dementia other than Alzheimer’s – yes |
| Ie3c (e3c) | X | X | Physically abusive – yes |
| If3d (e3d) | X | X | Socially inappropriate behaviour – yes |
| Kin | X | X | Lives with spouse or child – yes |
| | | | **ODDS RATIO OF 0.85 OR LOWER** |
| Del1 | X | | Delirium symptom – yes |
| Ig1gb (h1fb) | | X | Shopping – some difficulty |
| Ij2n (k2e) | | X | Vomiting – yes |
| Ij6b (k8c) | | X | Experiencing acute episode, flare up – yes |
(j1f) | | X | Peripheral vascular disease – yes |
| Ii1l (j1b) | X | X | Congestive heart failure – yes |
| Ii1e (j1j) | X | X | Hemiplegia – yes |
| Il1 (n2a) | X | X | Pressure ulcer (any stage) – yes |
| Ij7 (K8a) | X | X | Says in poor health – yes |


## Algorithm: Risk of Death Among Home Care Clients

**Name of algorithm**: Prediction Model for Risk of Death Among Home Care Clients

**Purpose of algorithm**: The purpose was to develop a proximity to death prediction model for home care clients, with quarterly assessments up to one year.  

### List of variables

| icode | Variable |
|-------|----------|
| | **NOT IN MODEL** |
| bb4 | Marital status – married |
| ii1c, ii1d | Alz or other dementia |
| ii1i | Stroke |
| | **DIAGNOSES** |
| ii1k | Coronary heart disease |
| ii1m | COPD |
| ii1m, in2e | COPD and received Oxygen |
| ii1l | Congestive heart failure |
| | **CLINICAL PROBLEMS** |
| ij6b | Flare up of recurrent problem |
| ij2s | Edema |
| ij2n | Vomiting |
| il5 | Skin tears or cuts |
| ik2a | Weight loss |
| ij2c | Dizziness |
| ik2b | Insufficient fluid |
| ij6c | Less than 6 months to live |
| | **PERFORMANCE - COGNITIVE / FUNCNAL** |
| ig6a | Less than 2 hrs phy act in 3 days |
| ig8a | ADL Decline Over Prior 90 Days |
| ig2b,d,f,h,I,j | ADLs |
| ic5 | Worsen decision making 90 days  |
| ig1ab,bb,gb,(6)H3 IADL, or ig8a(2) | decline |
| | **TREATMENTS AND SERVICES** |
| in2a | Chemotherapy |
| in5a | Hosp admission at baseline |
| ia13 | Hosp stay within last week  |
| in2e | Oxygen |
| | **OTHER** |
| ia2 | Male |


## Algorithm: Change in IADL Status Among Home Care Clients

**Name of algorithm**: Prediction Model for Change in IADL Status 
                                Among Home Care Clients
								
**Purpose of algorithm**:  The purpose was to assess IADL change among adult home care clients and develop a predictive risk model.  

**Number of variables**: 8

### List of variables

| Item | Name and Code |
|------|---------------|
| Short-term Memory Problem  | Ic2a (1) |
| Meal Preparation Capacity – Independent | Ig1ab (0,1,2) |
| Meal Prepare Capacity -- Not Dependent | Ig1ab (0-5) |
| Ordinary Housework Capacity -- Independent | Ig1bb (0,1,2) |
| Shopping Capacity -- Independent  | Ig2gb (0,1,2) |
| Bathing -- Independent  | Ig2j (0) |
| Alzheimer's Diagnosis | II1c (1-3) |
| Other Dementia Diagnosis  | Ii1d (1-3) |


## Algorithm: Health-Related Quality of Life Among Home-Care Clients

**Name of algorithm: Change in Health-Related Quality of Life Among Home-Care Clients**:   
                                       A Cross-National Perspective
									   
**Purpose of algorithm**: The objectives of this project were to report on health-related quality of life (QoL) among adult home care clients, describe their baseline QoL profile and assess the stability of the QoL assessment over time.  Additionally, we developed a model to characterize a person’s risk of QoL decline and evaluate its stability across countries.

### List of variables

| Independent Variable Name | Independent Variable at Baseline | Code |
|---------------------------|----------------------------------|------|
| | **Problem Free at Baseline** |
| Ie1b | Persistent anger | 0 – no |
| Ie1c | Unrealistic fears | 0 – no |
| Ie1f | Sad expressions | 0 – no |
| Ie1g | Recurrent crying | 0 – no |
| Ig2b | Personal hygiene | 0 – indep |
| Ig3 | Assistive walking device | 0 – no |
| Ij5a | Pain | 0 – no |
| Id2 | Understand others | 0 - understand |
| | **Not Problem Free at Baseline** |
| Ii1c | Alzheimer’s | 1+ - yes |
| Ii1h | Parkinsonism | 1+ - yes |
| Il2aba-fba | Glaucoma | H40.9 – yes |
| Il2aba-fba | Thyroid disease | E07.9 – yes |


## Algorithm: Frailty Among Home-Care Clients

**Name of algorithm**: Prediction Model for Frailty – 
                                     FrailtyRisk-HC Scale Development to Predict Change
									 
**Purpose of algorithm**: The objectives of this project were to address frailty within a multi-national, older adult, home care population. Goals were to: (1) describe the primary frailty pattern for this international cohort of home care clients; (2) describe how frailty changes between a baseline measure and a follow-up measure, completed  about 11 months later; (3)  evaluate how the baseline characteristics of these clients may contribute to subsequent decline or improvement; and (4) develop and validate a risk scale to predict frailty change, assessing how decline and improvement present across the risk scale categories

### List of variables

| Independent Variable Name | Independent Variable at Baseline |
|---------------------------|----------------------------------|
|  | **RISK OF DECLINE MEASURES** |
| b1a (Ic2a) | Short-term memory problem = 1,2 (yes) |
| b2b (Ic5)0 | Worsening decision making = 2 (yes) |
| J1g (Ii1c) | Alzheimer's disease = 1+ (yes) |
| J1h (Ii1d) | Dementia other than Alzhimer's = 1+ (yes) |
| J1l (Ii1h) | Parkison's disease = 1+ (yes) |
| H2g (Ig2g) | Eating Not independent = 1+ (yes) |
|  | **POSSIBLE RECOVERY MEASURES** |
| H2c (Ig2f) | Locomotion in the home Not independent =0+ (yes) |
| I2b (Ih2) | Use of Indwelling catheter = 2 (yes) |
| J1u (Ii1g) | Pneumonia = 1+ (yes) |
| J1w (Ii1r) | Urinary tract infection = 1+ (yes) |
| J1o (ii1a) | Hip fracture = 1+ (Yes) |
