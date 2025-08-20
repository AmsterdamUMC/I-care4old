# CHANGE IN HEALTH-RELATED QUALITY OF LIFE

## General information

**Deliverable**: Change in Health-Related Quality of Life Among Home-Care Clients: A Cross-National Perspective

**Consortium Partner**: Hebrew SeniorLife, Profility, Inc.

**Contact**: John N Morris, email: jnm@hsl.harvard.edu, Hebrew SeniorLife

**Description of Data Contents, Analysis Purpose, Methods**: The project is based on secondary analysis of data derived from a multi-national cohort of adult home care clients. The dataset consists of de-identified computerized records of interRAI Home Care (HC) clients. The data were provided to the not-for-profit interRAI collaborative by government agencies pursuant to use of interRAI assessment systems.

The objectives of this project were to report on health-related quality of life (QoL) among adult home care clients, describe their baseline QoL profile and assess the stability of the QoL assessment over time. Additionally, we developed a model to characterize a person’s risk of QoL decline and evaluate its stability across countries.

**Sample Size**: The baseline cohort consisted of 2,277,273 assessments. The follow-up cohort included 1,386,625 assessments, occurring on average of 11 months post-baseline.

## Data Processing

**Sample Restrictions**: Among the client cohort, 61.3% were female, 32% were married, 23.4% lived with a spouse or spouse and another relative, 34.4% lived alone, and 15.0% lived with a child. Average age at baseline was 76.5 years —13% were > 90 years of age or older, while 18.6% were < 65.

Cognitive status was varied. About half (51.1%) had memory problems. A slightly smaller percent were independent in making decisions about the everyday tasks of life (43.1%), and, finally, at the other extreme, only 5.2% were fully dependent on others. Even more positively, 85.2 had no or only minimal difficulties in hearing, and 90.5% had adequate or only slightly impaired vision.

IADL dependency was more common than ADL dependency. In two of the most common IADLs – housework and meal preparation – only 5.2% and 11.1% were able to carry out these tasks fully on their own. With respect to ADLs, persons are more likely to require physical help with so-called early loss functions such as personal hygiene (31.6%) and dressing (49.3%), than with a so-called middle-loss function such as ambulation (23.4%).

Members of the cohort also present with a variety of clinical deficits. Most conditions have a prevalence of less than 20%, including: stroke (15.6%), congestive heart failure (12.0%), Alzheimer’s disease (6.4%), any other dementia diagnosis (16.5); and infections such as UTI (5.3%) and pneumonia (2.6%); and finally unintended weight loss (9.1%), pressure ulcers (4.5%) and stasis ulcers (2.7%). At the same time there were a number of more prevalent conditions, including: coronary artery disease (24%), dizziness (22.1%), shortness of breath (25.6%), daily pain (49.9%), and having an unsteady gait (67.1%).

**Major Re-coding or Transformations**: In most instances, variables with multiple values were recoded as dichotomous. Beyond the file creation, there were no major transformations.

**Modeling QoL Risk**:

- Baseline QoL scores are present, the model is adjusted (reducing the risk of decline estimate).
- Scoring of the risk model is based on the items in Table 1 plus the person’s baseline QoL score [note – see Appendix for rules to create this score]. The Table 1 items set the basic model. The first step is to sum the two sub-groups of variables in Table 1.
- **NOproblem** -- Add “1” to count when each is true: ii1l (1+) ii1h (1+) jil1aba-il2fba (H40.9 iltaba – iltfba (E07.9).
- **Problem** – Add “1” to count when each is true: ie1b ie1c ie1f ie1g ig2b ig3 ij5a id2 (1).
- **Adjust Problem count**:
  - If NoProblem count greater than “0,” add “1” to Problem count.
- **Recode Problem count AND as FINALqolRISK**:
  - (0 thru 2=1)(3,4=2)(5,6=3)(7=4)(8 thru high =5)
- **FINALqolRISK Category Labels**: (1) Very low (2) Low (3) Typical (4) High (5) Very high
- The last adjustment is based on the person’s baseline Quality of Life score. When this is in the low part of the range, the person’s QoL decline risk goes down.
- If the baseline QoL score is less than or equal to “-.17,” then the FINALqolRISK score is set to “1”.
- If the baseline QoL score is in range of -.17 to .10, and FINALqolRISK score is greater than “2,” then subtract “1” from the FINALqolScore.

**How Missing Values were Handled**: For missing values, cases with many missing items were removed prior to analysis. For some missing items, the value equivalence was set to NO.

**Methods for Analysis**: The dependent interRAI HcQol index was created by comparing the person’s health-related quality of life score on the baseline assessment with the corresponding assessment at follow-up. Two change measures were created: (1) a decline of one quarter or more of the QoL baseline standard deviation, and (2) an improvement of one-quarter or more of the baseline QoL standard deviation.

The baseline items on the MDS 2.0 provide the array of independent measures reviewed to assess a person’s elevated risk of decline. In addition, to round out our independent variable set in light of the several hundred measures in the interRAI HC, many of which were not available to others, we extended the set of independent measures. Ultimately, 142 independent variables were considered.

We reviewed each measure to assess whether it in fact tracked with decline in health-related quality of life. Note, because of the size of the available follow-up cohort (i.e., 1,386,625 clients), measures of significance were not useful – very, very small differences proved to be significant at the commonly used probability standards (e.g., .05 or .01). In its place we assessed the role of the independent variables based on the strength of their relationship to decline in QoL. More specifically, a measure had to have a minimally meaningful odds ratio of 1.20 or higher, or .70 or lower to be further considered.

**Country Source and Contact for Data**: Data (full combined data set) is housed in US. John Morris is contact person.

Jurisdictions providing data included Canadian Provinces–Ontario, Manitoba, British Columbia, Alberta, Newfoundland, and Nova Scotia. US data came from New York, New Jersey, Missouri, Georgia, Massachusetts, Louisiana, Arkansas, Connecticut, Maryland, and Michigan. Other assessments were from mandated home care programs in New Zealand, and several European countries. Representative subsets of cross-European cases previously derived from the EU-funded AD HOC study and I-BENC project also were included.

## Data contents

**General description of the data contents**: The HC assessment provides information needed to produce comprehensive care plans and information to create descriptive scales, resource use estimates, program quality indicators, and demographic characteristics.

**Data sources**: interRAI Home Care version 2.0

**Number of variables**: 9

**List of variables**:

| Independent Variable Name | Independent Variable at Baseline | Code |
| --- | --- | --- |
| | **Problem Free at Baseline** | |
| Ie1b | Persistent anger | 0 – no |
| Ie1c | Unrealistic fears | 0 – no |
| Ie1f | Sad expressions | 0 – no |
| Ie1g | Recurrent crying | 0 – no |
| Ig2b | Personal hygiene | 0 – indep |
| Ig3 | Assistive walking device | 0 – no |
| Ij5a | Pain | 0 – no |
| Id2 | Understand others | 0 - understand |
| | **Not Problem Free at Baseline** | |
| Ii1c | Alzheimer’s | 1+ - yes |
| Ii1h | Parkinsonism | 1+ - yes |
| Il2aba-fba | Glaucoma | H40.9 – yes |
| Il2aba-fba | Thyroid disease | E07.9 – yes |

## Publications

**Manuscript currently being prepared**:

*Change in Health-Related Quality of Life Among Home-Care Clients: A Cross-National Perspective*
