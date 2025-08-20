# FRAILTY (CHANGE)

## General information

**Deliverable**: Prediction Model for Frailty – FrailtyRisk-HC Scale Development to Predict Change

**Consortium Partner**: Hebrew SeniorLife, Profility, Inc.

**Contact**: John N Morris, email: jnm@hsl.harvard.edu, Hebrew SeniorLife

**Description of Data Contents, Analysis Purpose, Methods**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems.

The objectives of this project were to address frailty within a multi-national, older adult, home care population. Goals were to: (1) describe the primary frailty pattern for this international cohort of home care clients; (2) describe how frailty changes between a baseline measure and a follow-up measure, completed about 11 months later; (3) evaluate how the baseline characteristics of these clients may contribute to subsequent decline or improvement; and (4) develop and validate a risk scale to predict frailty change, assessing how decline and improvement present across the risk scale categories.

**Sample Size**: The study cohort included 1,119,129 follow-up assessments, each with a corresponding baseline interRAI HC assessment, with an average of about eleven months between assessments.

## Data Processing

**Sample Restrictions**: Among the cohort of home care clients, the majority were female (59.8%). A third (33.2%) were widowed, 32.3% were married, 14.6% had never married, and the remainder were divorced or separated. Regarding living status, 36.2% lived alone and 87.4% lived in a private home or apartment. The average age was 77.0 years, 13.9% were 85 years of age or older, and 15.6% were under age 65.

Within the areas of cognition and communication, many exhibited a problem. Slightly over half (54.1%) had a short-term memory problem, 55.2% had some level of problem in decision-making, 6.9% had an Alzheimer’s diagnosis, and 15.8% had a dementia diagnosis other than Alzheimer’s.

Functional status, as measured by IADLs, indicated that few were fully independent – 11.6% in meal preparation, 6.0% in housework, and 8.1% in shopping. The numbers for ADLs are somewhat better, but still, large numbers require some type of help, supervision, or setup. Among the ADLs, the fully independent rates were as follows – 47.1% transfer, 40.2% dressing, and 60.0% eating. In terms of movement, 22.6% could do stairs without help, 36.6% used a cane, 19.4% used a walker, and 8.0% were in a wheelchair. Within the clinical domain, many older adults had issues. In bladder continence, slightly over half (51.4%) were not fully continent. About one-quarter had problems such as dizziness (28.4%), edema (24.4%), and shortness of breath (31.4%). A lower percent described their health status as poor (15.9%), while many more said they had daily pain (55.9%).

**Major Re-coding or Transformations**: In most instances, variables with multiple values were recoded as dichotomous. Beyond the file creation, there were no major transformations.

**How Missing Values were Handled**: For missing values, cases with many missing items were removed prior to analysis. For some missing items, the value equivalence was set to NO.

**Methods for Analysis**: The frailty measure of choice was the previously validated interRAI Home-Care Frailty Scale (HCFS). This 29-item summary scale provides a wide-ranging assessment of frailty among home care clients. The tool consists of measures of instrumental activities of daily living (IADL) and ADL function, cognitive status, health complications, and social activities. The HCFS scale is scored from 0 (indicating “no frailty”) to 24 (indicating “highest frailty”) and is related to changes in cognitive status, functional performance, and perceived health status.

The measure of the primary dependent variable, frailty decline, was obtained by comparing the clients’ frailty status per HCFS scores at baseline (0 months) and again at the approximate one-year follow-up. Frailty decline point on the HCFS between baseline and follow-up. When there was a one or more point increase the person was assigned a score of “1” indicating a frailty decline. Conversely, if a person’s HCFS score did not increase at follow-up, they were assigned a score of “0”, indicating an absence of frailty decline. This one-plus point increase measure is the primary outcome of our work because we base our model development and reporting efforts on this measure. In addition, we also report on two other case outcomes, a decline of 2 or more points, and an improvement of one or more points.

**Independent Measures**:

A two-step process was followed to create the list of independent variables to be evaluated as possible correlates with frailty decline. First, we evaluated the list of items we had previously identified as frailty decline predictors for persons in nursing homes. Second, in light of the scope of coverage in the HCFS, we secondarily cast a broad net to bring in additional independent variables such as immutable measures of cognitive and communication impairment we also included several potentially mutable baseline clinical complications (e.g., weight loss, pneumonia, urinary tract infection). To have a minimally meaningful level of association, and thus be considered in our model creation effort, a measure had to have an a priori forward-stepping multivariate logistic models. The two risk subscales that resulted from this review included only the most relevant latent measures, thereby avoiding the inappropriate inclusion of variables with high inter-item correlations.

**Development of the Frailty Risk Home Care Scale (FrailtyRisk-HC)**:

A summary nine-category risk of frailty decline scale (FrailtyRisk-HC) was created based on the multi-step process: (1) indentation of those categories across the HCFR scale where there was a relatively high likelihood of decline; (2) identify the independent variables that predict decline based on the presence of a 1.20 or higher odds ratio (positive) or a .75 or lower odds ratio (negative); (3) reduce the list of independent variables by review within the logistic model; (4) create positive and negative risk subscales; (5) use the two subscales plus the person’s baseline frailty scale to assign persons into the most appropriate risk category; and (6) describe decline and improvement across the categories of the risk scale.

**Country Source and Contact for Data**: Data (full combined data set) is housed in US. John Morris is contact person.

Jurisdictions providing data included Canadian Provinces–Ontario, Manitoba, British Columbia, Alberta, Newfoundland, and Nova Scotia. US data came from New York, New Jersey, Missouri, Georgia, Massachusetts, Louisiana, Arkansas, Connecticut, Maryland, and Michigan. Other assessments were from mandated home care programs in New Zealand, and several European countries. Representative subsets of cross-European cases previously derived from the EU-funded AD HOC study and I-BENC project also were included.

## Data contents

**General description of the data contents**: The HC assessment provides information needed to produce comprehensive care plans and information to create descriptive scales, resource use estimates, program quality indicators, and demographic characteristics.

**Data sources**: interRAI Home Care version 2.0

**Number of variables**: 11 - 6 contributing to decline, 5 possible recovery

**List of variables**:

| Independent Variable Name | Independent Variable at Baseline |
| --- | --- |
| | **RISK OF DECLINE MEASURES** |
| b1a (Ic2a) | Short-term memory problem = 1,2 (yes) |
| b2b (Ic5) | Worsening decision making = 2 (yes) |
| J1g (Ii1c) | Alzheimer's disease = 1+ (yes) |
| J1h (Ii1d) | Dementia other than Alzheimer's = 1+ (yes) |
| J1l (Ii1h) | Parkinson's disease = 1+ (yes) |
| H2g (Ig2g) | Eating Not independent = 1+ (yes) |
| | **POSSIBLE RECOVERY MEASURES** |
| H2c (Ig2f) | Locomotion in the home Not independent =0+ (yes) |
| I2b (Ih2) | Use of Indwelling catheter = 2 (yes) |
| J1u (Ii1g) | Pneumonia = 1+ (yes) |
| J1w (Ii1r) | Urinary tract infection = 1+ (yes) |
| J1o (ii1a) | Hip fracture = 1+ (yes) |

## Publications

**Manuscript currently being prepared**:

*Frailty Among Home Care Clients: FrailtyRisk-HC Scale Development to Predict Change*
