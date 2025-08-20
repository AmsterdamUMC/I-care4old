# Description of analysis data set used with Deliverable 3.1

## General information

**Deliverable 3.1 - Validation of operationalized patient groups**

###  Responsible consortium partner:  ### 

KI

 ### Contact person: ### 

Davide Liborio Vetrano (email: davide.vetrano@ki.se); affiliations: Aging Research Center, Department of Neurobiology, Care Sciences and Society (NVS), Karolinska Institutet-Stockholm University, Solna, Sweden; Stockholm Gerontology Research Center, Stockholm, Sweden.

 ### Short description of data contents, analysis purpose, and methods ### 

Multi-database cohort study using clinical assessment data routinely collected from Canada, Finland, New Zealand, and Italy, over five years. Main goal was to apply a validated methodology to identify homogeneous groups of care-dependent older adults based on their disease patterns. Taking advantage of InterRAI Home Care (HC) and Long-Term Care Facilities (LTCF), a common comprehensive geriatric assessment tool, it was possible to identify and cross-replicate clinically-relevant patterns of multimorbidity in older adults receiving home care services or living in nursing home. Latent Class Analysis (LCA) was used to classify individuals with common underlying diseases, identified through disease-related codes assessed by the interRAI HC and interRAI LTCF instruments, by exploiting information on 19 chronic conditions. LCA was performed independently in four countries and two settings, for a total of eight different environments, and several class-solutions were appraised from a statistical and clinical point of view.

 ### Sample size  ### 

Overall, a total of 256,350 older adults were included in the LTCF setting and 402,902 were included in the HC setting. Time windows of recruitment was between 01/01/2024 and 31/12/2018. Sample sizes for each country are reported below.
- Canada LTCF: n=178780 HC: n=306930
- Finland LTCF: n=37086 HC: n=44889
- Italy LTCF: n=8506 HC: n=15008
- New Zealand LTCF: n=31978 HC: n=36075

## Data processing

### Sample restrictions ### 

Individuals aged 60 years or older were included (in Canada, defined as aged 65 years or older for administrative reasons), with at least one assessment record between January 1, 2014, and December 31, 2018. Only the first records within the study period were used. Individuals without any chronic condition were excluded.

### Major re-codings or transformations applied ### 
- iA2 (gender, 1: Male; 2: Female): renamed as “Female” and recoded as 0: Male; 1: Female);
- iA9 (Date of assessment): converted in date format if not;
- Recoding of the 19 conditions of interest: coded as 1 if a diagnosis is present, irrespective of whether it is the primary diagnosis or/and receiving active treatment, and 0 otherwise.
- Recoding of ADL: None (0), Mild-Moderate (1-2), and Severe (3-6)
- Recoding of CPS: None (0), Mild-Moderate (1-2), and Severe (3-6)
- Recoding of DRS: None (0), Mild-Moderate (1-4), and Severe (5-14)
- Creation of a variable reporting the total number of diseases, “n.condition”
- Creation of categorial variable for age, “Age_group”: 60-69, 70-79, 80-89, 90+.


### How missing values were handled ### 

Generally, individuals with missing value for age were excluded. In the 19 conditions of interest, missing values were replaced with 0 (disease not present).

 ### Short description of the methods used in each analysis phase ### 

For each database, we first tabulated sample characteristics (basic demographics and functional status) and reported the prevalence of each condition and the average number of conditions. The results were stratified by gender and/or age group.

We then applied LCA to identify homogeneous groups of individuals across different countries and care settings. In this context, LCA estimated the posterior probability that each individual belonged to each class (i.e., a specific multimorbidity pattern), conditional on the observed values of the manifest variables (i.e., whether the individual has a diagnosis of a condition of interest) using the Bayes’ formula. Each individual will be assigned to the class with the highest posterior probability. 

Countries whose data were used and contact person for each country

- Canada: Luke Turcotte (lturcotte@brocku.ca)
- Finland: Jokke Häsä (jokke.hasa@thl.fi)
- Italy: Cecilia Damiano (cecilia.damiano@iss.it)
- New Zealand: Gary Cheung (g.cheung@auckland.ac.nz)

## Data contents

 ### General description of the data contents ### 

Data comprised information on demographic characteristics, clinical (e.g., number of chronic diseases) and functional features such as physical functioning (ADL), cognitive impairment (CPS) and depressive symptoms (DRS). 

 ### List of variables using harmonised names and short descriptions ### 

iA2: gender;
iA9: date of assessment;
iA8: assessment type;
sADLH: activities of daily living;
sCPS: cognitive performance scale;
sDRS: depression rating scale;
iI1a: hip fracture;
iI1b: other fracture;
iI1c: Alzheimer’s disease;
iI1d: dementia other than Alzheimer’s disease;
iI1e: hemiplegia;
iI1f: multiple sclerosis;
iI1g: paraplegia;
iI1h: Parkinson’s disease;
iI1i: quadriplegia;
iI1j: stroke/CVA;
iI1k: coronary heart disease;
iI1l: congestive heart failure;
iI1m: chronic obstructive pulmonary disease (COPD);
iI1n: anxiety;
iI1o: depression;
iI1p: schizophrenia;
iI1s: cancer;
iI1t: diabetes mellitus;
i1w: bipolar disorder.

 ### Data sources for each country ### 

- Canada: Canadian interRAI data are collected through interRAI Home Care (HC) Assessment Form, Version 9.1 and interRAI Long-Term Care Facilities (LTCF) Assessment Form, 9.1. 
- Finland: MDS-HC and MDS-LTC instruments are used. 
- Italy: interRAI Home Care (HC) v.9.1 and InterRAI Long Term Care Facility (LTCF) v.9.1 are used. 
- New Zealand: interRAI Home Care (HC) Assessment Form, Version 9.1 and interRAI Long-Term Care Facilities (LTCF) Assessment Form, 9.1 are used. 

## Publications

No publication yet.
