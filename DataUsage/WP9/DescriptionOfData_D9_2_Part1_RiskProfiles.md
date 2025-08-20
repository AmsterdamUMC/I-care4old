# D9.2 PART 1 Risk Profiles WP9

## General Information

### Name of Deliverable or Other Purpose of Use
**D9.2 Identification of risk profiles for adverse outcomes during the COVID-19 pandemic**

### Responsible Consortium Partner
- **Daniel Leme, PhD**
- **Reem Mula, PhD**

### Contact Person, Email, and Affiliation
- **Daniel Leme** - [ddacunha@uwaterloo.ca](mailto:ddacunha@uwaterloo.ca) - Postdoctoral Fellow, University of Waterloo  
- **Reem Mula** - [rmulla@uwaterloo.ca](mailto:rmulla@uwaterloo.ca) - Postdoctoral Fellow, University of Waterloo  

### Short Description of Data Contents, Analysis Purpose, and Methods
Data from LTC residents aged 18 years or older in pre-COVID-19 (11,532) and during COVID-19 (10,909) periods assessed using the **interRAI Minimum Data Set 2.0 (MDS 2.0)**.

#### Objectives
1. **Verify depressive symptoms incidence** and the factors associated with transitions in mood or depressive symptoms states.
2. **Estimate mood transition** factors using a **one-step Markov multistate transition model**.

## Data Processing

### Sample Restrictions
- **Depressive symptoms model**: LTC clients aged 18+ with no depressive symptoms (score = 0 on DRS scale at baseline).
- **Mood symptoms transition model**: LTC clients aged 65+ with no mood symptoms at baseline.

### Major Recodings or Transformations Applied
- **None**

### Handling of Missing Values
- **Major comorbidity count** variable was excluded due to large missing values.

### Methods Used in Each Analysis Phase
#### 1. Estimating the effect of COVID-19 on depressive symptoms
- **Partial proportional odds logistic regression model** applied.
- Stratified analysis by resident-level (age, sex, cognitive performance) and facility-level (province, facility size, location).

#### 2. Analyzing mood state transitions
- **Markov multistate transition model** used to track shifts in mood states and transitions to absorbing states (hospital, death, etc.).

### Countries Whose Data Were Used
- **Canada**

### Contact Persons by Country
- **Daniel Leme** ([ddacunha@uwaterloo.ca](mailto:ddacunha@uwaterloo.ca))
- **Reem Mula** ([rmulla@uwaterloo.ca](mailto:rmulla@uwaterloo.ca))
- **Micaela Jantzi** ([micaela.jantzi@uwaterloo.ca](mailto:micaela.jantzi@uwaterloo.ca))

## Data Contents

### General Description of Data Contents
- Data collected using **interRAI Minimum Data Set 2.0 (MDS 2.0)**.
- Ethics clearance: **Research Ethics Office, University of Waterloo (ORE File# 30372)**.
- All data were **de-identified** and collected by **trained assessors (nurses).**

### Data Sources
- **interRAI Long-Term Care Facilities (LTCF) Assessment** and its predecessor **RAI 2.0**.

### Number of Variables
- **17**

### List of Variables

| Variable Name | Categories Used | Code/Variable Name | Description |
|--------------|----------------|--------------------|-------------|
| Age at Assessment | 18-44; 45–64; 65–74; 75–84; 85-94; ≥95 | age.num (AGE_ASSESMENT) | Standard age variable from DOB |
| Sex | Male; Female | sex (A2a) | Derived from gender identity |
| Marital Status | Not married; Married | BB4 | Original variable collapsed from 6 categories |
| Cognitive Performance (CPS) Scale | 0;1-2;3-4;5-6 | sCPS | Higher scores = more severe cognitive impairment |
| Index of Social Engagement (ISE) | 0; 1-2; 3-4; 5-6 | Soceng_nh2 (sRISE) | Measures social involvement within facility |
| CHESS Score | 0;1-2;3+ | chesscat (sCHESS) | Detects health instability |
| ADL Hierarchy Scale | 0;1-2;3-6 | ADL_hier_nh2 | Higher scores = greater functional loss |
| Aggressive Behaviour Scale (ABS) | 0;1-4;5+ | sABS | Measures aggressive behavior; 5+ indicates high aggression |
| Pain Scale | 0;1;2;3 | Pain_nh2 | Higher scores = more pain |
| Anxiety Diagnosis | No; Yes | Not found | Anxiety diagnosis status |
| Conflict With Others | No; Yes | F2a-F2b-F2c | Binary variable for conflicts with staff, family, etc. |
| Newly Admitted Resident Status | No; Yes | Aa8 | Identifies newly admitted residents |
| Canadian Province | AB, BC, MB, NL, ON | province_code | Identifies province |
| LTC Home Size | Small; Medium; Large | Not found | Categorized by facility size |
| LTC Home Location | Urban; Rural | FAC_URBAN_RURAL_CODE | Identifies rural/urban location |
| New Depressive Symptoms (DRS) | 0; 1-2;3+ | DRS_nh2 (sDRS) | Measures depressive symptoms using the DRS scale |

### Country-Specific Differences
- **None**

### Other Important Notes
- **No additional connections** to other datasets.

## Publications

### Relevant Studies
- **Mulla R et al.** (2025). *Incidence of New Mood Symptoms Among Residents in Canadian Long-Term Care Homes During the COVID-19 Pandemic: A Longitudinal Analysis*. [DOI: 10.1016/j.osep.2025.01.002](https://doi.org/10.1016/j.osep.2025.01.002)
- **Mulla R et al.** (Under Review). *Factors Associated with Mood Transitions Among Older Canadian Long-Term Care Residents: A Multistate Transition Model* (JAMDA).
