# Description of Analysis Data Set Used with Deliverable 9.1

## General Information

### Name of Deliverable
D9.1 Longitudinal Analysis of the Effect of Antipsychotic Use on Behavior Disturbance in LTC Homes: Cross-National Validation

### Responsible Consortium Partner
- Daniel Leme  
- Ilona Baranska  

### Contact Person, Email, and Affiliation
- **Daniel Leme**: `ddacunha@uwaterloo.ca`, Postdoctoral Fellow, University of Waterloo  
- **Ilona Baranska**: `ilona.baranska@uj.edu.pl`, Jagiellonian University  

### Short Description of Data Contents, Analysis Purpose, and Methods
Two data sources were used in this deliverable:  
1. **Model Development**: Data from long-term care (LTC) patients aged 18 and older assessed in Canada using the interRAI Long-Term Care Facility (LTCF) Assessment.  
2. **External Validation**: Data from LTC patients aged 18 and older assessed in Belgium and the Netherlands using the interRAI version 9.1 instruments.  

**Purpose**: The analyses aimed to verify the effect of antipsychotic use on the worsening behaviour of LTC patients.  
**Methods**: Treatment Effect Analysis with Propensity Score matching and weighting methods were used for development and external validation. Models were adjusted for confounders such as age, sex, social engagement, Alzheimer’s and related dementias, psychosis, risk of falls, and interRAI-CHESS, Pain, and ADL hierarchy scales.

### Sample Size
- **Canada (Derivation Cohort)**: 494,215 LTC clients  
- **Netherlands and Belgium (Validation Cohort)**: 4,962 LTC clients  
*Note*: Sample sizes reflect baseline and follow-up assessments used to develop the model.

---

## Data Processing

### Sample Restrictions
- **Age**: Individuals aged 18 years or older at baseline.  
- **Assessments**: Two assessments (baseline and closest follow-up) were used.  
- **Exclusion Criteria**:  
  - Only residents alive at follow-up were included.  
  - Individuals with severe aggressive behaviors (score ≥5 on the Aggressive Behavior Scale [ABS] at baseline) were excluded.

### Major Re-codings or Transformations Applied
None

### How Missing Values Were Handled
Listwise deletion was applied for model development and validation.

### Short Description of Methods Used in Each Analysis Phase
Using Treatment Effect Analysis, we estimated the probability of participants receiving antipsychotics at baseline based on demographic and clinical characteristics (e.g., age, sex, chronic diseases, neurological conditions, frailty). The goal was to produce a comparable sample with equivalent probabilities of receiving or not receiving antipsychotics. Steps included:  
1. **Data Cleaning and Manipulation**: Ensured no missing values and correct variable categorization.  
2. **Confounder Selection**: Applied the Direct Acyclic Graph method to select confounders.  
3. **Propensity Score Estimation**: Calculated the probability of treatment based on patient characteristics.  
4. **Data Balancing**: Checked balance to ensure equal distribution of characteristics between treated and untreated groups, mimicking randomization.  
5. **Logistic Regression**: Estimated a model with antipsychotic treatment as the independent variable and worsening behavior as the dependent variable using the balanced sample.

### Multi-Country Analysis Details
#### Countries Whose Data Were Used
- Canada  
- Belgium  
- Netherlands  

#### Contact Person for Each Country
- **Canada**: Daniel Leme (`ddacunha@uwaterloo.ca`)  
- **Belgium and Netherlands**: Ilona Baranska (`ilona.baranska@uj.edu.pl`)

---

## Data Contents

### General Description of the Data Contents
- **Model Development (Derivation Cohort)**: Data collected in Canada using the interRAI LTCF Assessment (and predecessor RAI 2.0). Ethics clearance provided by the University of Waterloo Office Research Ethics (ORE# 30173). Written informed consent was not required per Canadian legislation.  
- **External Validation**: Data collected in Belgium and the Netherlands using interRAI version 9.1 instruments. Ethical approval obtained in Belgium (G-2023-6216-R5(MIN)) and the Netherlands (2021.0358). Consent procedures varied by country and time period (e.g., opt-out in the Netherlands pre-2018).  
- **Data Quality**: All data were deidentified, collected by trained assessors (usually nurses), and deemed high-quality based on interRAI reliability across 12 countries (Hirdes et al., 2008).

### Data Sources
- **Canada**: interRAI LTCF Assessment (and RAI 2.0)  
- **Belgium and Netherlands**: interRAI instruments (version 9.1)

### Number of Variables
15

### List of Variables
Below is a table of harmonized variable names, categories, codes, and descriptions from the Canadian (derivation) and Belgium/Netherlands (validation) datasets.

| **Variable Name**         | **Categories Used in Study** | **Code in Derivation Cohort** | **Code in Validation Cohort** | **Details/Description**                                                                                   |
|---------------------------|------------------------------|-------------------------------|-------------------------------|-----------------------------------------------------------------------------------------------------------|
| Age at Assessment         | 18-64; 65–74; 75–84; 85–94; ≥95 | `age.num` (orig: `AGE_ASSESMENT`) | `sAGE_cat`                  | Derived standard age variable based on date of birth (AA3a).                                              |
| Sex                       | Male; Female                | `sex` (orig: `A2a`)           | `iA2`                       | Derived from gender identity variable (AA2).                                                              |
| ISE                       | 0-2; 3+                     | `Soceng_nh2` (orig: `sRISE`)  | `sRISE`                     | Index of Social Engagement (ISE). Higher scores (3+) indicate high social engagement.                     |
| Psychosis                 | No; Yes                     | `Psychosis`                   | `ii1p`                      | Diagnosis of psychosis (binary).                                                                          |
| Alzheimer and Related Dementia | No; Yes                | `adrd` (orig: `I1r`)          | `ii1c`, `ii1d`              | Diagnosis of Alzheimer’s and related dementia (binary).                                                   |
| Delirium                  | Not Triggered; Triggered    | `delir.cap` (orig: `cDELIR`)  | `cDELIR`                    | Diagnosis of delirium (binary).                                                                           |
| Falls Risk CAP            | No Falls Risk; Medium Risk; High Risk | `falls.cap` (orig: `cFALLS`) | `cFALLS`                  | Assessed via interRAI Falls Risk CAP.                                                                     |
| CHESS                     | 0; 1–2; 3–5                | `chesscat` (orig: `sCHESS`)   | `sCHESS_r`                  | Changes in Health, End Stage Disease and Signs and Symptoms (CHESS). Higher scores indicate instability.   |
| CPS Scale                 | 0; 1; 2–3; 4–6             | (orig: `sCPS`)                | `sCPS_cat` (orig: `sCPS`)   | Cognitive Performance Scale (CPS). Higher scores indicate severe cognitive impairment.                    |
| Pain                      | 0; 1; 2; 3                 | `Pain_nh2`                    | `sPAIN1`                    | interRAI Pain Scale. Higher scores indicate greater pain frequency/intensity.                             |
| ADL-S                     | 0; 1-2; 3-6                | `ADL_hier_nh2`                | `adl.cat` (orig: `sADLH`)   | Activities of Daily Living Self-Performance Hierarchy Scale (ADL-S). Higher scores indicate greater loss.  |
| DRS                       | 0-2; 3+                    | `DRS_nh2` (orig: `sDRS`)      | `drs.cat` (orig: `sDRS`)    | Depression Rating Scale (DRS). Scores ≥3 indicate potential depression.                                   |
| Frailty                   | Non-frail; Pre-frail; Frail | `Armstrong_Fl`                | `frailty_r` (orig: `sFI_corrected`) | Modified Armstrong Frailty Index. Cutoffs: <0.2 (non-frail), 0.2-0.3 (pre-frail), >0.3 (frail).          |
| Antipsychotic Use         | No; Yes                     | `antipsy` (orig: `O4a`)       | `N05A`                      | Days of antipsychotic use in last 7 days. Categorized as 0 (No) or ≥1 (Yes).                              |
| Worsening Behaviour       | Same; Worse                 | `beh_worse_only`              | `beh_wrose_only`            | Derived from Aggressive Behaviour Scale (ABS). Worse = ABS ≥5 at follow-up (from 0-4 at baseline).        |

### Country-Specific Differences
None noteworthy.

### Other Important Notes
None.

---

## Publications
- **Canada (Data Development)**: Leme, DEC et al. *A Longitudinal Treatment Effect Analysis of Antipsychotics on Behavior of Residents in Long-Term Care*. DOI: [10.1016/j.jamda.2024.105255](https://doi.org/10.1016/j.jamda.2024.105255)
