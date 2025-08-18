# I-CARE4OLD metadata repository

This repository contains descriptions of data sets and their use in the EU Horizon -funded project I-CARE4OLD (<https://www.icare4old.eu/>). It is divided in two parts.

* **Data sources**: Descriptions of national data sets used in the I-CARE4OLD project.
* **Data usage**: Descriptions of models and algorithms created in the project, including programming code for the algorithms and an algorithm index.

## Summary of the project and data

The objectives of the I-CARE4OLD project were to model the longitudinal development of older persons with complex chronic conditions and the effect of introduced or discontinued interventions on their life expectancy, hospitalization, self-care functioning, cognitive functioning, clinical disability, and quality of life. As an end product, a prototype of a decision-support tools for clinicians and other professionals was created and tested for usability and feasability. In addition, models were built to study the effects of COVID-19 on older persons receiving care.

The project deals mainly with re-used data. The re-used data are based on existing records of older persons receiving home care or long-term residential care over the years 2014–2021 in eight countries:

* Belgium
* Canada
* Finland
* Hong Kong 
* Italy
* the Netherlands
* USA
* New Zealand.

The core data consists of repeated assessments using the interRAI Suite 9 assessment instruments (or their previous versions, the interRAI MDS instruments). These core data is supplemented, where possible, by linkage with data from external administrative datasets (drug registries, hospital admission/discharge data, death registries and primary care use registries) to obtain complementary information on the clinical history of the persons receiving care. Combined, these data are used by the following analytical work packages to fulfill the objectives of the project:

* WP3: Identifying homogeneous groups of patients sharing common patterns of complex chronic conditions (CCC)
* WP4: Specification of profiles of health trajectories
* WP5: Identification of pharmological factors that modify health trajectories
* WP6: Impact of non-pharmacological interventions (NPI) on health outcomes
* WP9: COVID Impact.

All data are anonymised or pseudonymised before their use in this project. 

The format of the data is a distributed database, with the data from each country maintained in their separate databases. The sizes of the national databases range from thousands to millions of persons. The data were utilised through federated analyses, which means that the data sets remained separate, but the models and algorithms for the analysis were shared between countries to be run on their own data sets.

More detailed description of the overall structure of the source data sets is given in the [README file](DataSources/README.md) in the `DataSources` subfolder. Descriptions of each country's source data set are in the subfolder `DataSources/NationalDescriptions`. Descriptions on how the data sets are used for analysis can be found in the `DataUsage` subfolder, together with algorithm source codes and an index of developed algorithms.
