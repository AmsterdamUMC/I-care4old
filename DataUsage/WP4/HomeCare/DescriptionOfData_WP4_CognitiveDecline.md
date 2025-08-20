# COGNITIVE DECLINE

## General information

**Deliverable**: Prediction Model for Cognitive Decline Among Home Care Clients

**Consortium Partner**: Hebrew SeniorLife, Profility, Inc.

**Contact**: John N Morris, email: jnm@hsl.harvard.edu, Hebrew SeniorLife

**Description of Data Contents, Analysis Purpose, Methods**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems. The purpose was to examine changes in cognitive performance among older adult home care clients and to develop and validate a model to predict change. The cognitive status and cognitive change measures were based on the Cognitive Performance Scale version 2 (CPS2).

**Sample Size**: Analyses of international home-care assessment data both at baseline (n=2,928,674) and at the first follow-up assessments about 11 months later (n=1,892,099) were completed. Improvement and decline rates were contrasted across the scale and a new risk of decline model was configured to identify the predictors of decline (note – the decline sample included 1,832,766 home-care clients).

## Data Processing

**Sample Restrictions**: Among the international cohort of home care clients, 26.4% lived with a spouse or a spouse and other relatives, 30.2% lived alone, and 14.5% lived with a child. The average age at baseline was 76.9 years; 12.7% were 90 years of age or older, while 15.8% were under 65. The majority were female (57.8%) and 29.5% of the sample was married.

**Major Re-coding or Transformations**: In most instances, variables with multiple values were recoded as dichotomous. Beyond the file creation, there were no major transformations.

**How Missing Values were Handled**: For missing values, cases with many missing items were removed prior to analysis. For some missing items, the value equivalence was set to NO.

**Methods for Analysis**: The baseline CPS2 provides an initial descriptive profile of the cognitive status of the cohort members. On this scale, categories 0 and 1 reference those who were cognitively intact, categories 2 and 3 represent those with borderline status (a pre-dementia plateau), while categories 4 through 8 represent those with more serious cognitive loss (categories 4 and 5 are labelled moderate loss, 6 and 7 severe loss, and 8 very severe loss).

Using follow-up assessment data, for each CPS2 baseline category, we examined whether those in the category stayed the same, declined or improved. Next, we identified which of the independent risk of decline factors had a minimally meaningful level of association – i.e., the odds ratio with cognitive decline had to be 1.2 or higher, or 0.85 or lower. Each dichotomous independent variable was assessed in three sample groupings: (1) for all home care clients; (2) for home-care clients in CPS2 categories 0-3; and (3) for home care clients in CPS2 categories 4-6. If any one or more of the three sample groupings met the odds ratio criteria, the measure was then assessed in two distinct sub-modelling efforts: those with a CPS2 score of 0-3 and those with a CPS2 score of 4-7.

The first of the two sub-models examined those with a relatively higher rate of baseline cognitive engagement, while the second sub-model included those more impaired at baseline. In our view, the rate of decline would differ across these two sub-groups and the independent variables driving decline would across differ between groups.

A summary risk of decline scale (CogRisk-HC) was created based on an integration of these two sub-models. In each case we first summed positive risk factors that increased the risk of decline and then reduced the risk score for those who had a number of factors that demonstrated a protective role. Using this integrated risk of cognitive decline scale, we looked at its distribution and the decline rates across the risk scale.

**Country Source and Contact for Data**: Data (full combined data set) is housed in US. John Morris is contact person.

Jurisdictions providing data included Canadian Provinces–Ontario, Manitoba, British Columbia, Alberta, Newfoundland, and Nova Scotia. US data came from New York, New Jersey, Missouri, Georgia, Massachusetts, Louisiana, Arkansas, Connecticut, Maryland, and Michigan. Other assessments were from mandated home care programs in New Zealand, and several European countries. Representative subsets of cross-European cases previously derived from the EU-funded AD HOC study and I-BENC project also were included.

## Data contents

**General description of the data contents**: The HC assessment provides information needed to produce comprehensive care plans and information to create descriptive scales, resource use estimates, program quality indicators, and demographic characteristics.

**Data sources**: interRAI Home Care version 2.0

**Number of variables**: 19 – 10 for those associated with decline, 9 for those associated with improvement

**List of variables**:

| Variable Code - I and Program | Equation: One Two | Variable Name and Code 1 (all others scores = 0) |
| --- | --- | --- |
| | | **ODDS RATIO OF 1.20 OR HIGHER** |
| Ic1 (B2a2) | X | Decision-making – 2+ (impaired) |
| Ic4 (b3b) | X | Agitated, disoriented, difficult to arouse – yes |
| Ii1h (j1l) | X | Parkinsonism – yes |
| Age80 | X | Age 80 or older – yes |
| Age70 | X X | Age 70 or older – yes |
| Ii1c (j1g) | X X | Alzheimer’s diagnosis – yes |
| Ii1d (j1h) | X X | Dementia other than Alzheimer’s – yes |
| Ie3c (e3c) | X X | Physically abusive – yes |
| If3d (e3d) | X X | Socially inappropriate behaviour – yes |
| Kin | X X | Lives with spouse or child – yes |
| | | **ODDS RATIO OF 0.85 OR LOWER** |
| Del1 | X | Delirium symptom – yes |
| Ig1gb (h1fb) | X | Shopping – some difficulty |
| Ij2n (k2e) | X | Vomiting – yes |
| Ij6b (k8c) | X | Experiencing acute episode, flare up – yes |
| (j1f) | X | Peripheral vascular disease – yes |
| Ii1l (j1b) | X X | Congestive heart failure – yes |
| Ii1e (j1j) | X X | Hemiplegia – yes |
| Il1 (n2a) | X X | Pressure ulcer (any stage) – yes |
| Ij7 (K8a) | X X | Says in poor health – yes |

## Publications

**Manuscript currently being revised for a new submission**:

*Cognitive change among older adults home care clients; CogRisk-HC scale development to predict decline*
