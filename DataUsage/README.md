# Description of how data is used

This folder contains a description of how data is used by the analytical work packages (WP) of the I-CARE4OLD project. The programming code for selected algorithms is also included. The analytical work packages are

* WP3: Identifying homogeneous groups of patients sharing common patterns of complex chronic conditions (CCC)
* WP4: Specification of profiles of health trajectories
* WP5: Identification of pharmological factors that modify health trajectories
* WP6: Impact of non-pharmacological interventions (NPI) on health outcomes
* WP9: COVID impact

The data usage descriptions and algorithms of each work package are given in the corresponding subfolder. The WP folders are further subdivided according to the topic of analysis:

* WP3
    - Deliverable 3.1: Validation of operationalized patient groups
	- Deliverable 3.2: Characterization HC and NH patients' groups
* WP4
    - Home care
	- Nursing home (long-term care facilities)
	- Profiling
* WP5
    - Training causal models for estimating treatment effects
	- Validating the causal models
* WP6
    - Milestone 25: Describe exposure to non-pharmacological interventions during care trajectories
    - Milestone 26: Trained ML algorithms on impact of non-pharmacological treatments
* WP9
    - Deliverable 9.1: Longitudinal Analysis of the Effect of Antipsychotic Use on Behavior Disturbance in LTC Homes: Cross-National Validation
	- Deliverable 9.2: Identification of risk profiles for adverse outcomes during the COVID-19 pandemic
	
All algorithms are listed in the CSV table `AlgorithmIndex.csv`.

## 1. Overview of project objectives

The overall objective of the I-CARE4OLD project is to develop high quality decision support for better prognostication of health trajectories, including treatment impact, in older home care (HC) and long-term care (LTC) recipients with complex chronic conditions (CCC) using linked real world data. The health impact is mainly through six health outcomes: death, unplanned hospital admission, change in self-care functioning, change in cognitive functioning, health instability, and change in health-related quality of life. The analytical work packages WP3–WP6 use data from different health and social care registries to model the health trajectories (WP3–WP4) and the impact of various treatments (WP5–WP6). In addition, work package WP9 studies the effect of COVID-19 on older care recipients.

Selected and validated algorithms developed by the analytical work packages are to be combined in a decision-support tool by work package WP7. The tool is intended for care professionals and it would give estimates on individual trajectories and suggestions for treatment options for older care recipients with complex chronic conditions.

## 2. Data handling within work packages

Since the real-world data used in the project comes from different countries and is of sensitive nature, the analytical work packages work within a _federated analysis_ framework. This means that the data sets will be harmonised to a common structure and nomenclature, so that models and algorithms developed in the project can be transferred and run on different data sets. Each analytical work package chooses themselves which parts of the data they use for model development: they pick the relevant variables, choose the country-level data sets, clean and possibly restructure the data that they use for developing and validating the models. Models are typically developed initially on one country's data, then sent to further development to other countries. The data sets used in model development and validation are described alongside the algorithms in this metadata repository.

## 3. Re-use of the algorithms

Algorithms included in this repository are intended to be used for reviewing and learning purposes, but they may also be re-used in new research. However, the **original authors should be contacted** before re-using of modifying their code for new research or commercial purposes.
