# FUNCTIONAL DECLINE

## CHANGE IN IADL STATUS

## General information

**Deliverable**: Prediction Model for Change in IADL Status Among Home Care Clients

**Consortium Partner**: Hebrew SeniorLife, Profility, Inc.

**Contact**: John N Morris, email: jnm@hsl.harvard.edu, Hebrew SeniorLife

**Description of Data Contents, Analysis Purpose, Methods**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems. The purpose was to assess IADL change among adult home care clients and develop a predictive risk model.

**Sample Size**: Analyses of home-care assessment data, from an international cohort of cases, using two assessments, spaced approximately 11 months apart (n=2,394,626 at baseline and 1,420,501 at follow-up).

## Data Processing

**Sample Restrictions**: Among the client cohort, 31.9% lived with a spouse or spouse and other relative, and the majority were female (61.3%). The average age at baseline was 80.0 years. On the ADL Functional Hierarchy scale, 46.6% were fully independent and 40.9% received help from others. Higher rates of support were seen for stair climbing (73.1%).

In terms of cognition, 50.7% had a short-term memory problem, while 70.5% required help in managing their finances, and 51.9% needed help in managing their medications. On the Cognitive Performance Scale, 33.1% were independent, 51.7% were in the two most independent categories, and 24.8% were in the more severe categories (3 thru 6).

The cohort of home-care clients displayed a variety of indicators of clinical complexity. About four in ten had recently fallen (38.8%) and 66.9% had unsteady gait. Twenty percent said they were in poor health, 25.6% had shortness of breath, 21.6% had edema, 22.1% had recent weight loss, and 49.9% experienced pain daily. In terms of diagnoses, 6.3% had Alzheimer’s, 16.2% had another dementia, 24.0% had coronary artery disease, 11.9% had heart failure, and 3.3% had Parkinsonism.

**Major Re-coding or Transformations**: In most instances, variables with multiple values were recoded as dichotomous. Beyond the file creation, there were no major transformations.

**How Missing Values were Handled**: For missing values, cases with many missing items were removed prior to analysis. For some missing items, the value equivalence was set to NO.

**Methods for Analysis**: The independent variable set were derived from the baseline home care assessment. Each independent measure was scored as a dichotomy, where “0” indicated that the problem or condition was not present, while “1” indicated it was present.

The two dependent variables were defined based on the person’s IADL Hierarchy status at baseline and follow-up. The scale has a range from 0 to 6, where 0 indicates independence and 6 full dependence. The hierarchy considers the following five IADL capacity measures: shopping, meal preparation, housework, managing finances, and managing medications.

A decline from a score of 0-5 (excluding those with a baseline score of 6, which represents persons who are fully dependent in the five IADLs – or about 1 in 4 of all clients) to a higher score was considered decline (and is scored as “1,” while those who did not decline were scored as “0”). Thus, of the 1,420,501 follow-up cases, 1,241,360 were used in the decline analyses.

An improvement from a score of 1 to 6 (excluding those with a 0 score, which represents persons who are fully independent at baseline – only about 3% of clients) to a lower score was considered to be an improvement (and was scored as “1” while those who did not decline are scored as “0”).

Each independent variable was contrasted with the two dependent measures. Those independent variables with a “clinically meaningful” univariate odds ratio – defined as 1.20 or higher or .75 or lower went forward to be assessed within two multi-variate logistic models. Note, while both were tested, meaningful rates of change were seen for decline, but not improvement.

Variables coming out of one of the decline logistic model, with each risk factor adding a count of “1” to the penultimate risk model [note, in fact some of the final items reflect risk, while others reflect a positive status at baseline and thus the potential to decline].

**Creation of Summary Risk of IADL Risk of Decline Scale (IADL Decline-HC)**: The ultimate risk scale (IADL Decline-HC) is based on a combination of the count of the eight risk factors identified above and the person’s baseline IADL Hierarchy status. Both are related to decline, and in effect for each IADL Hierarchy level the penultimate summary risk scale has the potential of separating the group into those that are more and less likely to decline. On the IADL Hierarchy scale, the higher the score the less likely the person is to decline. While on the penultimate risk summary scale (riskSUM) the higher the count the higher the likelihood of decline.

- **Penultimate Risk Summary (riskSUM)** Equals the COUNT of risk codes for the items in Table 3: Ic2a (1) ig1ab ig1bb ig1gb (0,1,2) Ig1ab (0-5) ig2j (0) ii1c ii1d (1,2,3) ig1ab (0-5)
- Record riskSUM (6 thru high=6)
- The combined IADL Hierarchy and RiskSUM code is as follows, creating the ultimate IADL Decline HC scale:
  - compute IADLdecHC =$sysmis
  - if (IADLhi eq 5 and any(iadlDEC,0,1))IADLdecHC=0
  - if (IADLhi eq 5 and iadlDEC gt 1)IADLdecHC=1
  - if (IADLhi eq 4 and iadlDEC lt 2)IADLdecHC=1
  - if (IADLhi eq 4 and any(iadlDEC,2,3))IADLdecHC=2
  - if (IADLhi eq 4 and any(iadlDEC,4,5,6))IADLdecHC=3
  - if (IADLhi eq 3 and any(iadlDEC,0,1,2))IADLdecHC=2
  - if (IADLhi eq 3 and iadlDEC eq 3)IADLdecHC=3
  - if (IADLhi eq 3 and iadlDEC gt 3)IADLdecHC=4
  - if (IADLhi eq 2 and iadlDEC lt 4)IADLdecHC=2
  - if (IADLhi eq 2 and iadlDEC eq 4)IADLdecHC=3
  - if (IADLhi eq 2 and iadlDEC gt 4)IADLdecHC=4
  - if (IADLhi eq 1)IADLdecHC=4
  - if (IADLhi eq 0)IADLdecHC=4

**Country Source and Contact for Data**: Data (full combined data set) is housed in US. John Morris is contact person.

Jurisdictions providing data included Canadian Provinces–Ontario, Manitoba, British Columbia, Alberta, Newfoundland, and Nova Scotia. US data came from New York, New Jersey, Missouri, Georgia, Massachusetts, Louisiana, Arkansas, Connecticut, Maryland, and Michigan. Other assessments were from mandated home care programs in New Zealand, and several European countries. Representative subsets of cross-European cases previously derived from the EU-funded AD HOC study and I-BENC project also were included.

## Data contents

**General description of the data contents**: The HC assessment provides information needed to produce comprehensive care plans and information to create descriptive scales, resource use estimates, program quality indicators, and demographic characteristics.

**Data sources**: interRAI Home Care version 2.0

**Number of variables**: 8

**List of variables**:

| Item | Name and Code |
| --- | --- |
| Short-term Memory Problem | Ic2a (1) |
| Meal Preparation Capacity – Independent | Ig1ab (0,1,2) |
| Meal Prepare Capacity -- Not Dependent | Ig1ab (0-5) |
| Ordinary Housework Capacity -- Independent | Ig1bb (0,1,2) |
| Shopping Capacity -- Independent | Ig2gb (0,1,2) |
| Bathing -- Independent | Ig2j (0) |
| Alzheimer's Diagnosis | II1c (1-3) |
| Other Dementia Diagnosis | Ii1d (1-3) |

## Publications

**Manuscript currently in development**:

*Change in IADL Status Among Adult Home Care Clients: An International Perspective*
