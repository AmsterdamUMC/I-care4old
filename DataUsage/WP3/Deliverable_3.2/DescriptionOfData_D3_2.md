# Description of analysis data set used with Deliverable 3.2

## General information

**D3.2 Characterization HC and NH patients' groups**

### Responsible consortium partner: ###

KI

### Contact person: ###

Davide Vetrano (email: davide.vetrano@ki.se); affiliations: Aging Research Center, Department of Neurobiology, Care Sciences and Society (NVS), Karolinska Institutet-Stockholm University, Solna, Sweden; Stockholm Gerontology Research Center, Stockholm, Sweden.

### Short description of data contents, analysis purpose, and methods ###

Multi-database cohort study using clinical assessment data routinely collected from Canada, the US, Finland, New Zealand, Italy, Belgium and the Netherlands, over a minimum of five years. 

Main goal was to conduct replicative analyses and to validate the characterization of disease patterns across countries and care settings, based on the results achieved from previous deliverable (D3.1). In the current validation analysis and in order to achieve robust and reliable results, we extended the time window of sample recruitment in countries, beyond Italy and New Zealand, such as Finland, Canada, US, the Netherlands and Belgium. Particularly, the multimorbidity pattern classifications (i.e., LTCF and HC settings, Deliverable 3.1) identified in the Canadian datasets was selected as the most clinically-relevant and robust, also in consideration of the well-known data collection high quality. We then applied the weighs of LCA derived from Canadian datasets to the rest of countries, replicated the analysis and assessed commonalities and inconsistencies of the characteristics of individuals sharing the same disease clusters (with a focus on evaluating the functional, physical and cognitive status) across LTCF and HC, as well as across countries. Further, in order to quantify the risk stratification value of the disease clusters, we performed survival analysis to compute the association between disease clusters and 1-y all-cause mortality across country and care settings, with additional subgroup analysis stratified by each scale of physical and cognitive measurements of ADL, CPS and DRS, respectively. 

### Sample size ###

Overall, a total sample of over 2 million individuals (1,259,673 in LTCF and 1,047,119 in HC) were analysed. For each country, sample sizes and time windows of recruitment are reported below. 
- Belgium, LTCF: n=8930. Time windows of recruitment: 01/01/2019 – 31/12/2023. Note: the sample from Belgium was restricted to LTCF setting
- Canada, LTCF: n=325267, HC: n=503254. Time windows of recruitment: 01/01/2010 – 31/12/2018
- Finland, LTCF: n=56749, HC: n=69087. Time windows of recruitment: 01/01/2010 – 31/12/2018
- Italy, LTCF: n=8506, HC: n=15008, Time windows of recruitment: 01/01/2014 – 31/12/2018
- New Zealand, LTCF: n=31978, HC: n=36075. Time windows of recruitment: 01/01/2014 – 31/12/2018
- The Netherlands, LTCF: n= 2219, HC: n=1395. Time windows of recruitment: 01/01/2010 – 31/12/2018
- United States, LTCF: n=325267, HC: n=432899. Time windows of recruitment: 01/01/2010 – 31/12/2018

## Data processing

### Sample restrictions ###

Individuals aged 60 years or older were included (in Canada, defined as aged 65 years or older for administrative reasons), with at least one assessment record within trunked time window in each country setting. Only the first records within the study period are used. Individuals without any chronic condition were excluded. 

### Major re-codings or transformations applied ###
- iA2 (gender, 1: Male; 2: Female): renamed as “Female” and recoded as 0: Male; 1: Female;
- iA9 (Date of assessment): converted in date format if not;
- Recoding of the 19 conditions of interest: coded as 1 if a diagnosis is present, irrespective of whether it is the primary diagnosis or/and receiving active treatment, and 0 otherwise.
- Recoding of ADL: None (0), Mild-Moderate (1-2), and Severe (3-6)
- Recoding of CPS: None (0), Mild-Moderate (1-2), and Severe (3-6)
- Recoding of DRS: None (0), Mild-Moderate (1-4), and Severe (5-14)
- Creation of a variable reporting the total number of diseases, “n.condition”
- Creation of categorial variable for age, “Age_group”: 60-69, 70-79, 80-89, 90+.

### How missing values were handled ###

Individuals with missing value for age were excluded. Eventual missing value for death were set to 0. In the 19 conditions of interest, missing values were replaced with 0 (disease not present).

### Short description of the methods used in each analysis phase ###

Based upon previous work in D3.1 indicating six classes of disease patterns as the most consistent grouping of individuals across countries and care settings, we validated these identified patterns by first determining the most robust six disease patterns in each care setting. Given that Canada had the evident largest sample size among other country data sources, and that the six disease patterns derived from Canada had a consistent overlapping with other two countries in both LTCF and HC, we used the weights derived from Canadian datasets as the most clinically-relevant and robust to be replicated across other countries. For each external sample, we estimated the posterior probability of an individual belonging to a class using parameter estimates obtained from the Canadian sample. All individuals were assigned to a disease pattern with the highest posterior probability. Sample characteristics (basic demographics and functional status) and the prevalence of each condition and the average number of conditions were described and compared across countries and care settings. 

We calculated the incidence rate of death for the total sample and by multimorbidity patterns. We also applied Cox proportional hazard regressions to examine the risk of one-year mortality associated with each disease pattern, with different levels of adjustment for covariates. Model 1 was adjusted for age and gender. Model 2 was adjusted for age, gender, and the number of conditions, and Model 3 was further adjusted for functional status measured by ADL, CPS, and DRS. In the sensitivity analyses, we repeated the same analysis stratified by different scales of ADL, by CPS, and by DRS. To note, the outcome variables in Belgium and US was not available, hence the association analyses were conducted exclusively in Canada, Finland, New Zealand, Italy, and the Netherlands. 

### Countries whose data were used and contact person for each country ###

- Belgium, Anja Declercq (anja.declercq@kuleuven.be>), Johanna Mello (johanna.mello@kuleuven.be)
- Canada, Luke Turcotte (lturcotte@brocku.ca)
- Finland, Jokke Häsä (jokke.hasa@thl.fi)
- Italy, Cecilia Damiano (cecilia.damiano@iss.it)
- New Zealand, Gary Cheung (g.cheung@auckland.ac.nz)
- The Netherlands, Eline Tankink - Kooijmans (e.c.m.kooijmans@amsterdamumc.nl) 
- United States, John Morris (jnm@hsl.harvard.edu), Elizabeth Howard (howardel@bc.edu)

## Data contents

### General description of the data contents ###

Data comprised information on demographic characteristics, mortality, clinical (e.g., number of chronic diseases) and functional features such as physical functioning (ADL), cognitive impairment (CPS) and depressive symptoms (DRS). 

### List of variables using harmonised names and short descriptions ###

iA2: gender;
iA9: date of assessment; 
iA8: assessment type; 
Age: age at the assessment; 
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
iI1w: bipolar disorder; 
DOD: date of death; 
death1: one year mortality.

### Data sources for each country ###

- Belgium: interRAI Home Care (HC) v.9.1 and InterRAI Long Term Care Facility (LTCF) v.9.1 are used. To note, mortality data was not available in Belgium.
- Canada: Canadian interRAI data are collected through interRAI Home Care (HC) Assessment Form, Version 9.1 and interRAI Long-Term Care Facilities (LTCF) Assessment Form, 9.1. Mortality data in Canada were identified from hospital electronic health records in the Discharge Abstract Databases, which is a national database managed by the Canadian Institute for Health Information (CIHI).
- Finland: MDS-HC and MDS-LTC instruments are used. Information on family relations and place of residence are retrieved from the Digital and Population Data Services Agency (DPDS); information on medication, diagnosis, and hospital discharge including deaths are retrieved from the Hospital discharge register (Hilmo).
- Italy: interRAI Home Care (HC) v.9.1 and InterRAI Long Term Care Facility (LTCF) v.9.1 are used. Mortality data in Italy were derived from InterRAI assessments (i.e., administrative closure of the case).
- New Zealand: interRAI Home Care (HC) Assessment Form, Version 9.1 and interRAI Long-Term Care Facilities (LTCF) Assessment Form, 9.1 are used. Mortality data from New Zealand were retrieved from the Ministry of Health National Minimum Dataset and Mortality Dataset contains information of all registered death in New Zealand.
- The Netherlands: interRAI Home Care (HC) v.9.1 and InterRAI Long Term Care Facility (LTCF) v.9.1 are used. Mortality data in The Netherland were derived from the national death register.
- United States: interRAI Home Care (HC) v.9.1 and InterRAI Long Term Care Facility (LTCF) v.9.1 are used. To note, mortality data was not available in the US.
