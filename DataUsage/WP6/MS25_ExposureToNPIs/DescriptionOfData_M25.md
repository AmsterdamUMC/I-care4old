# Description of Analysis Data Set Used with Milestone 25

## General Information
**Milestone:** M25 Describe exposure to non-pharmacological interventions during care trajectories  
**Responsible Consortium Partner:** UI  
**Contact Person:** Ilona Barańska (email: ilona.baranska@uj.edu.pl)  
**Affiliations:** Laboratory for Research on Aging Society, in the Department of Medical Sociology at The Chair of Epidemiology and Preventive Medicine, Medical Faculty Jagiellonian University Medical College

## Short Description of Data Contents, Analysis Purpose, and Methods
We examined the use of non-pharmacological interventions (NPIs) at baseline and two follow-up time points to assess the stability or change in receiving NPIs over time, using data from multiple sources from: Czech Republic, Germany, United Kingdom, Finland, Israel, Italy, the Netherlands, Belgium, Canada, and Iceland. The list of NPIs, prepared based on a literature review and clinical expertise, included 28 NPIs in home care (HC) and 54 NPIs in long-term care facilities (LTCFs). The data were collected with tools developed by the international interRAI research group: Minimum Data Set and interRAI instrument.

For the analysis, we used assessments conducted at three time points: baseline and two follow-up evaluations, all performed at consistent intervals (ranging from 3 to 6 months). All NPIs were recoded as dichotomous variables (yes or no). To evaluate the stability of intervention receipt, we compared two consecutive assessment points (baseline to first follow-up and first to second follow-up), categorizing patients into four groups:

1. Stable no intervention - the patient/client did not receive the intervention at either assessment point.
2. Stable intervention - the patient/client received the intervention at both assessment points.
3. Discontinued intervention - the patient/client received the intervention only at the first assessment point.
4. New intervention - the patient/client received the intervention only at the second assessment point.

## Sample Size
We analyzed data from 376,419 long-term care facility (LTCF) patients and 673,730 home care (HC) patients, all aged 60+. Assessments conducted due to patient discharge or hospital return were excluded as they lacked NPI usage data.

### LTCF Data
- **SHELTER Project (2009-2011):** Data from seven EU countries (Czech Republic, UK, Finland, France, Germany, Italy, Netherlands) and one non-EU country (Israel), including 4,156 residents. Follow-ups at 6 and 12 months recorded outcomes such as death, hospitalization, or discharge. France was excluded due to 60-80% missing NPI data.
- **Real-World Data (RWD):** From Finland, Canada, Italy, and the Netherlands, collected using interRAI LTCF (Italy, Netherlands) and MDS 2.0 (Finland, Canada). Follow-ups occurred every 3-6 months, with data spanning 2014-2018.

### HC Data
- **IBenC Project (2013-2016):** Data from six European countries (Belgium, Finland, Germany, Iceland, Italy, Netherlands), including 2,884 community care clients. Each participant had 1-3 assessments using interRAI HC.
- **Real-World Data (RWD):** From Finland, Canada, Italy, and the Netherlands, collected via MDS 2.0 (Finland, Canada) and interRAI HC (Italy, Netherlands). Follow-up intervals were 3-6 months, with baseline samples ranging from 514 (Netherlands) to 650,000 (Canada).

## Data Processing
### Sample Restrictions
- Included patients aged 60 years and older or 65 years and older (depending on the data collection methodology).
- Excluded assessments conducted due to patient discharge or return from hospital, as these lacked NPI usage data.

### Major Re-codings or Transformations
- **NPIs:** 54 NPIs for LTCF and 28 NPIs for HC recoded as dichotomous (1 if present, 0 otherwise). E.g., if a patient received at least one minute of physical therapy in the past week, assigned 1; otherwise, 0.
- **ADL:** Recoded as Independent (0), Early-loss (1-3), and Dependent (4-6).
- **CPS:** Recoded as No (0), Mild (1-2), and Moderate-severe (3-6).
- **DRS:** Recoded as Low (0), Medium (1-2), and High (3-14).
- **Conditions/Diseases:** Recoded as 1 if present, 0 if absent.
- **Age:** Created categorical variable "Age_group": 60-69, 70-79, 80-89, 90+.

### Handling Missing Values
- Excluded cases with missing data on age or reason for assessment.
- Used pairwise deletion for remaining analyses.

## Short Description of Methods Used
The NPI list (Deliverable 6.1) was developed based on a literature review and expert opinion, selecting 54 NPIs for LTCFs and 28 for HC. Some NPIs (e.g., physical therapy, hearing aid use) were collected uniformly, while others varied by country and tool version. Database harmonization (using Deliverable 2.5) standardized variable codes and coding methods. For example, MDS 2.0 responses on watching TV/reading were binary, while interRAI 9.0 had five categories; these were harmonized by grouping responses 1-3 as "participating" and 4-5 as "not participating."

## Countries and Contact Persons
| Country | Contact Person | Email |
|---------|----------------|-------|
| Canada | Daniel Da Cunha Leme | ddacunhaleme@uwaterloo.ca |
| Finland | Jokke Häsä | jokke.hasa@thl.fi |
| Italy | Cecilia Damiano | cecilia.damiano@iss.it |
| The Netherlands | Eline Tankink - Kooijmans | e.c.m.kooijmans@amsterdamumc.nl |

## Data Contents
### General Description
The report presents characteristics of LTCF and HC patients, including age, gender, functional status, and presence of diseases. Main tables provide country-specific data on NPI stability.

### List of Variables
#### LTCF Variables
| Variable Code | Description |
|---------------|-------------|
| age | Age |
| iA8 | Assessment type |
| iN3ea | Physical therapy: days of care (at least 15 minutes) in last 7 days |
| iN3fa | Occupational therapy: days of care (at least 15 minutes) in last 7 days |
| iN3ga | Speech therapy: days of care (at least 15 minutes) in last 7 days |
| iN3ha | Psychological therapies: days of care (at least 15 minutes) in last 7 days |
| iN3ia | Respiratory therapy: days of care (at least 15 minutes) in last 7 days |
| iN3ja | Functional rehabilitation: days of care (at least 15 minutes) in last 7 days |
| iD3b | Hearing aid used |
| iD4b | Visual appliance used |
| iN2k | Wound care |
| iN2n | Turning program |
| iN2m | Palliative care |
| iK3 | Mode of nutritional intake |
| iK5 | Parenteral intake |
| iF1a | Social activities |
| iG6a | Hours exercise |
| iG6b | Days went out |
| iH2 | Urinary collection device |
| iH5 | Ostomy |
| iN1e | Dental exam |
| iN1f | Hearing exam |
| iN1g | Eye exam |
| iN2l | Scheduled toileting programme |
| iN6b | Trunk restraint |
| iN6c | Chairs prevents rising |
| iN6a | Full bed rails |
| iO2a | Do not resuscitate |
| iO2b | Do not intubate |
| iO2c | Do not hospitalize |
| iO2d | No tube feeding |
| iO2e | Medication restrictions |
| iS2n | Walking outdoors |
| iS2h | Helping others |
| iS2m | Trips/shopping |
| iS2a | Cards/games |
| iS2b | Computer use |
| iS2c | Conversing |
| iS2e | Dancing |
| iS2f | Exercise |
| iS2g | Gardening |
| iS2k | Reading |
| iS2l | Spiritual activities |
| iS2o | TV |
| iS2r | Reminiscing about life |
| iS2i | Music |
| iS2j | Pets |
| iS2d | Crafts |
| iG2b | Personal hygiene - performance |
| iG2f | Locomotion on same floor - performance |
| iG2h | Toilet use - performance |
| iG2j | Eating - performance |
| iC1 | Cognitive skills for daily decision making |
| iC2a | Short-term memory |
| iD1 | Hearing |
| iE1a | Negative statements |
| iE1b | Persistent anger |
| iE1c | Unrealistic fears |
| iE1d | Repetitive health complaints |
| iE1e | Repetitive anxious complaints |
| iE1f | Sad, pained, worried facial expressions |
| iE1g | Crying, tearfulness |
| iA2 | Gender |
| iI1a | Hip fracture |
| iI1b | Other fracture |
| iI1c | Alzheimer's disease |
| iI1d | Other dementia |
| iI1e | Hemiplegia |
| iI1f | Multiple sclerosis |
| iI1g | Paraplegia |
| iI1h | Parkinson's disease |
| iI1i | Quadriplegia |
| iI1j | Stroke |
| iI1k | Coronary heart disease |
| iI1l | Congestive heart failure |
| iI1m | Chronic obstructive pulmonary disease |
| iI1n | Anxiety |
| iI1o | Depression |
| iI1p | Schizophrenia |
| iI1s | Cancer |
| iI1t | Diabetes mellitus |
| iI1w | Bipolar disorder |

#### HC Variables
| Variable Code | Description |
|---------------|-------------|
| age | Age |
| iA8 | Assessment type |
| iF1a | Social activities |
| iG6a | Hours exercise |
| iG6b | Days went out |
| iN3ea | Physical therapy: days of care (at least 15 minutes) in last 7 days |
| iN3fa | Occupational therapy: days of care (at least 15 minutes) in last 7 days |
| iN3ga | Speech therapy: days of care (at least 15 minutes) in last 7 days |
| iN3ha | Psychological therapies: days of care (at least 15 minutes) in last 7 days |
| iN3aa | Home health aides: days of care (at least 15 minutes) in last 7 days |
| iN3ba | Home nurse: days of care (at least 15 minutes) in last 7 days |
| iN3ca | Homemaking services: days of care (at least 15 minutes) in last 7 days |
| iN3da | Meals: days of care (at least 15 minutes) in last 7 days |
| iN1e | Dental exam |
| iN1f | Hearing exam |
| iN1g | Eye exam |
| iN4 | Physical restraints |
| iN2k | Wound care |
| iN2l | Scheduled toileting programme |
| iN2m | Palliative care |
| iN2n | Turning programme |
| iN5c | Physician visit: number of visits in last 90 days |
| iK3 | Mode of nutritional intake |
| iH2 | Urinary collection device |
| iH4 | Pads worn |
| iQ2 | Handicapped re-engineered apartment |
| iQ3a | Emergency assistance available |
| iG2b | Personal hygiene - performance |
| iG2f | Locomotion on same floor - performance |
| iG2h | Toilet use - performance |
| iG2j | Eating - performance |
| iC1 | Cognitive skills for daily decision making |
| iC2a | Short-term memory |
| iC2b | Procedural memory |
| iD1 | Hearing |
| iE1a | Negative statements |
| iE1b | Persistent anger |
| iE1c | Unrealistic fears |
| iE1d | Repetitive health complaints |
| iE1e | Repetitive anxious complaints |
| iE1f | Sad, pained, worried facial expressions |
| iE1g | Crying, tearfulness |
| iA2 | Gender |
| iI1c | Alzheimer's disease |
| iI1d | Other dementia |
| iI1h | Parkinson's disease |
| iI1j | Stroke |
| iI1k | Coronary heart disease |
| iI1l | Congestive heart failure |
| iI1m | Chronic obstructive pulmonary disease |
| iI1n | Anxiety |
| iI1o | Depression |
| iI1s | Cancer |
| iI1t | Diabetes mellitus |

## Data Sources
| Country | Source | Notes |
|---------|--------|-------|
| IBenC and SHELTER | interRAI HC v.9.0, interRAI LTCF v.9.0 | |
| The Netherlands | interRAI HC v.9.1, interRAI LTCF v.9.1 | |
| Italy | interRAI HC v.9.1, interRAI LTCF v.9.1 | |
| Finland | MDS-HC, MDS-LTC | |
| Canada | MDS-HC, MDS-LTC | |

## Publications
- No publication yet.