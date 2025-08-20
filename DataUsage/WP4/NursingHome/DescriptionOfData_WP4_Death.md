# DEATH

## General information

**Deliverable**: Prediction Model for Risk of Death Among Home Care Clients

**Consortium Partner**: Hebrew SeniorLife, Profility, Inc.

**Contact**: John N Morris, email: jnm@hsl.harvard.edu, Hebrew SeniorLife

**Description of Data Contents, Analysis Purpose, Methods**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems. The purpose was to develop a proximity to death prediction model for home care clients, with quarterly assessments up to one year. Death was first assessed for a cohort of Canadian home-care clients from Ontario. The model was next extended to other Canadian Provinces, the USA, Europe, New Zealand, and Hong Kong. The dependent measures were death at 3, 6, 9 and 12 months after the home care baseline assessment.

**Sample Size**: The baseline sample consisted of 2,356,945 assessments.

## Data Processing

**Sample Restrictions**: Among the client cohort, 34% lived alone and the majority were female - 61.2%. The average age at baseline was 80.0 years. In ADLs, 42.6% (70.2%) were independent in transfer and 39.2% (68.9%) were independent in locomotion. Higher rates of support were seen for stair climbing – 78.5% (64.8%), and the report of a recent ADL decline – 33.9% (58.6%). In IADLs, 59.6% were dependent in meal preparation and 72.3% in housework.

In terms of cognition, 52.9% (47.4%) had a short-term memory problem and 39.5% (50.7%) were independent in decision making. In communication, 59.2% (70.3%) could fully understand others.

The clients exhibited a variety of indicators of clinical complexity. About four in ten had recently fallen – 36.5% (51.1%), and 67.0% had unsteady gait. Twenty percent said they were in poor health, 26.8% had shortness of breath, 18.7% (26.4%) had edema, 22.1% had a recent unplanned weight loss, and 66.0% experienced pain daily. In terms of diagnoses, 6.4% had Alzheimer’s, 16.7% had another dementia, 5.8% had a stroke, 12.7 had congestive heart failure, 3.4% had Parkinsonism, and 15.9% had COPD.

**Major Re-coding or Transformations**: In most instances, variables with multiple values were recoded as dichotomous. Beyond the file creation, there were no major transformations.

**How Missing Values were Handled**: For missing values, cases with many missing items were removed prior to analysis. For some missing items, the value equivalence was set to NO.

**Methods for Analysis**: The dependent variables were defined based on the person’s death status at quarterly windows from three-months to one year – with at each measurement point a score of “1” indicated the person had died and a score of “0” indicated the person was still alive. These data came from the Province of Ontario Canada.

Each independent variable was contrasted with the three-month death value for Ontario home-care clients – alive or dead. Our task at this point was to confirm or fail to confirm that these previously reported death predictors worked in the Ontario sample. If they did not they were dropped from further consideration. If they did, they went forward to be included in the death-risk scale. More, we defined variables in this large population cohort to have a “clinically meaningful” relationship to death when the univariate odds ratio was 1.20 or higher. This is a conservative inclusion criterion we have used in the past, and it ensures that only variables that in fact reflect a more substantial relationship to death were included in the final risk model.

Variables coming out of one of the above reviews form the new risk scale. Each item where a problem or condition were found adds a count of “1” to the final model. Next, the count distribution for this scale was contrasted with the three-month death measure. This permitted the scale to be collapsed to create the final risk index, which ranges from “1” Very low risk to “5” Very high risk. Once constructed the scale values were compared against the death rates at three, six, nine, and twelve months.

**Country Source and Contact for Data**:

Data (full combined data set) is housed in US. John Morris is contact person.

Jurisdictions providing data included Canadian Provinces–Ontario, Manitoba, British Columbia, Alberta, Newfoundland, and Nova Scotia. US data came from New York, New Jersey, Missouri, Georgia, Massachusetts, Louisiana, Arkansas, Connecticut, Maryland, and Michigan. Other assessments were from mandated home care programs in New Zealand, and several European countries. Representative subsets of cross-European cases previously derived from the EU-funded AD HOC study and I-BENC project also were included.

## Data contents

**General description of the data contents**: The HC assessment provides information needed to produce comprehensive care plans and information to create descriptive scales, resource use estimates, program quality indicators, and demographic characteristics.

**Data sources**: interRAI Home Care version 2.0

**Number of variables**: 23

**List of variables**:

| Variable (and icode) | Description |
| --- | --- |
| **NOT IN MODEL** | |
| bb4 | Marital status – married |
| ii1c, ii1d | Alz or other dementia |
| ii1i | Stroke |
| **DIAGNOSES** | |
| ii1k | Coronary heart disease |
| ii1m | COPD |
| ii1m, in2e | COPD and received Oxygen |
| ii1l | Congestive heart failure |
| **CLINICAL PROBLEMS** | |
| ij6b | Flare up of recurrent problem |
| ij2s | Edema |
| ij2n | Vomiting |
| il5 | Skin tears or cuts |
| ik2a | Weight loss |
| ij2c | Dizziness |
| ik2b | Insufficient fluid |
| ij6c | Less than 6 months to live |
| **PERFORMANCE - COGNITIVE / FUNCTIONAL** | |
| ig6a | Less than 2 hrs phy act in 3 days |
| ig8a | ADL Decline Over Prior 90 Days |
| ig2b,d,f,h,I,j | ADLs |
| ic5 | Worsen decision making 90 days |
| ig1ab,bb,gb,(6)H3 IADL, or ig8a(2) decline |
| **TREATMENTS AND SERVICES** | |
| in2a | Chemotherapy |
| in5a | Hosp admission at baseline |
| ia13 | Hosp stay within last week |
| in2e | Oxygen |
| **OTHER** | |
| ia2 | Male |

## Publications

**Manuscript currently in development**:

*Risk of Death Among Adult Home Care Clients*
