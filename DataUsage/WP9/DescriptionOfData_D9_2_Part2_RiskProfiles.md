# D9.2 PART 2 Risk Profiles WP9

## General Information

### Name of Deliverable or Other Purpose of Use
**D9.2 Identification of risk profiles for adverse outcomes during the COVID-19 pandemic (Part 2)**

### Responsible Consortium Partner
- **Daniel Leme, PhD**
- **Reem Mula, PhD**

### Contact Person, Email, and Affiliation
- **Daniel Leme** - [ddacunha@uwaterloo.ca](mailto:ddacunha@uwaterloo.ca) - Postdoctoral Fellow, University of Waterloo  
- **Reem Mula** - [rmulla@uwaterloo.ca](mailto:rmulla@uwaterloo.ca) - Postdoctoral Fellow, University of Waterloo  

### Short Description of Data Contents, Analysis Purpose, and Methods
This study focuses on the effects of the COVID-19 pandemic on **frailty, cognitive function, and mortality risk** among **long-term care (LTC) residents in Canada**. It utilizes data from the **interRAI Minimum Data Set 2.0 (MDS 2.0)**.

#### Objectives
1. **Assess frailty progression** among LTC residents before and during COVID-19.
2. **Investigate cognitive decline trends** and their associations with key risk factors.
3. **Estimate mortality risk** using survival models and hazard ratios.

## Data Processing

### Sample Restrictions
- **Frailty model**: LTC residents aged 65+ with at least one frailty assessment before and during COVID-19.
- **Cognitive function model**: LTC residents with at least two cognitive assessments.
- **Mortality risk model**: Residents with complete follow-up data.

### Major Recodings or Transformations Applied
- **Categorization of frailty scores** into mild, moderate, and severe.
- **Cognitive performance grouped** by Clinical Dementia Rating Scale (CDR).
- **Survival status** tracked using mortality indicators.

### Handling of Missing Values
- **Excluded cases with more than 20% missing data** for key variables.

### Methods Used in Each Analysis Phase
#### 1. Frailty Progression Analysis
- **Generalized Estimating Equations (GEE)** for repeated measures.
- Covariates: age, sex, pre-existing conditions, facility factors.

#### 2. Cognitive Decline Trends
- **Mixed-effects regression models** to track changes in cognition.
- Adjustments for baseline cognitive status and comorbidities.

#### 3. Mortality Risk Estimation
- **Cox proportional hazards model** for survival analysis.
- **Kaplan-Meier survival curves** comparing pre- and post-pandemic mortality rates.

### Countries Whose Data Were Used
- **Canada**

### Contact Persons by Country
- **Daniel Leme** ([ddacunha@uwaterloo.ca](mailto:ddacunha@uwaterloo.ca))
- **Reem Mula** ([rmulla@uwaterloo.ca](mailto:rmulla@uwaterloo.ca))
- **Micaela Jantzi** ([micaela.jantzi@uwaterloo.ca](mailto:micaela.jantzi@uwaterloo.ca))

## Data Contents

### General Description of Data Contents
- Collected using **interRAI MDS 2.0** from LTC facilities.
- Ethics clearance: **Research Ethics Office, University of Waterloo (ORE File# 30372)**.
- De-identified resident data collected by trained assessors.

### Data Sources
- **interRAI Long-Term Care Facilities (LTCF) Assessment**.

### Number of Variables
- **20**

### List of Variables

| Variable Name | Categories Used | Code/Variable Name | Description |
|--------------|----------------|--------------------|-------------|
| Age at Assessment | 65-74; 75-84; 85-94; ≥95 | age.num (AGE_ASSESMENT) | Standard age variable |
| Sex | Male; Female | sex (A2a) | Binary classification |
| Frailty Score | Mild; Moderate; Severe | frailty_index | Derived frailty classification |
| Cognitive Performance (CDR) | 0-1; 2-3; 4-5 | sCDR | Higher scores = more severe cognitive impairment |
| Activities of Daily Living (ADL) Scale | 0-1; 2-4; 5+ | ADL_hier | Functional ability measure |
| Chronic Conditions | 0-1; 2-3; 4+ | chronic_count | Count of major conditions |
| Depression Scale (DRS) | 0-2; 3-5; 6+ | DRS_score | Higher scores indicate more depressive symptoms |
| Social Engagement (ISE) | 0-2; 3-4; 5-6 | Soceng_nh2 | Measures social participation |
| Pain Scale | 0; 1-2; 3+ | Pain_nh2 | Higher scores indicate greater pain levels |
| Falls History | No; Yes | falls_indicator | Identifies history of falls |
| Hospitalization History | No; Yes | hosp_indicator | Identifies past hospitalizations |
| COVID-19 Diagnosis | No; Yes | covid_positive | Indicates confirmed infection |
| Mortality Status | Alive; Deceased | mortality_flag | Binary indicator |
| Follow-up Time (months) | Continuous | followup_time | Time until event (death or censoring) |
| LTC Home Size | Small; Medium; Large | facility_size | Categorized by bed capacity |
| LTC Home Location | Urban; Rural | facility_location | Identifies geographic setting |
| Province | AB, BC, MB, NL, ON | province_code | Identifies Canadian province |

### Country-Specific Differences
- **None**

### Other Important Notes
- **No external dataset linkage.**

## Publications

### Relevant Studies
- **Leme D et al.** (2025). *Frailty and Mortality in Canadian Long-Term Care Homes During the COVID-19 Pandemic: A Longitudinal Study*. [DOI: 10.1016/j.gero.2025.02.001](https://doi.org/10.1016/j.gero.2025.02.001)
- **Mulla R et al.** (Under Review). *Cognitive Decline Among Older Adults in LTC: Pre- and Post-COVID Trends* (JAMDA).
