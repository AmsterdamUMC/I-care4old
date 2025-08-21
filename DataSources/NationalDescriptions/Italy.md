# Description of I-CARE4OLD data source: Italy

## Data controller

Italian National Institute of Health (ISS)

## Data contents

* interRAI data (sample sizes for 2014–2018)
    - Home care (HC): 17,096 persons
    - Long-term care (LTC): 8,726 persons
    - Instrument versions: interRAI Suite 9.1
    - Medication information: ATC lists
* Hospital visits
* Deaths (only in-hospital)
* Medications

The data cover the years 2014–2018 and are collected electronically using interRAI instruments (version 9.1.2) every 6 months on average. The HC data cover 97% of the target population of over 65 years old receiving home care in one of the two health jurisdiction areas (ASL) of the Umbria region, and the LTC data cover 96% of the analogous population in long-term care. In home care, about 30% receive palliative care. Italy is able to link hospital visits, deaths (only in-hospital events) and medication events to interRAI data. The information comes from hospital discharge records (hospital and death events) controlled by the Umbria Region, and the drug prescription registry (medication events) controlled by the Italian Medicines Agency (AIFA).

## Data collection

### interRAI data

The Italian interRAI data are managed by the Umbria Region. The interRAI data from clients are collected by health professionals providing home care services and working in nursing homes, trained to use a variety of information sources, such as direct observation, interviews with the person under care, family, friends, or formal service providers, and review clinical records, both medical and nursing. interRAI data are collected and stored in a dedicated server managed and maintained by the Italian interRAI suite provider (Studio Vega).

### Non-interRAI data

It is possible to link hospital visits, deaths (only in-hospital events) and medication events to interRAI data. These types of information come from hospital discharge records (hospital and death events), owned by the Umbria Region, and the drug dispensation registry owned by AIFA, the Italian Medicine Agency. Linkage to hospital and death administrative data is therefore performed by Umbria Region. The Italian National Institute of Health (ISS) recovers the data collected by the Umbria Region within the project through a web platform provided by the Umbria region, which is accessible only to authorized people using dedicated credentials. The platform is reachable through connection to a specific VPN network.

## Linkage and pseudonymisation

For linking health event data to interRAI data, Umbria Region owns the pseudonymization key linked to the clients’ social security number. Personal data are pseudonymised by the source, which is Umbria Region, through the application of the MD5 hashing algorithm which converts the tax code of the subjects included in the study into a non-invertible string of 32 characters. The extraction and linking is done by Umbria Region, supported by AIFA (Italian Medicine Agency) and Studio Vega (software/server provider). When linking is requested, interRAI data, hospital records and drug dispensation records are communicated back to Umbria Region, which carry out the linkage and transmit back the pseudonymised data.

Data is taken by the ISS working group from a platform of the Umbria Region accessible exclusively to authorized parties. The data is archived on the centralized storage of the ISS, which access is limited exclusively to authorized parties. The data processing takes place on ISS workstations, which access is permitted exclusively to ISS personnel authorized to process; access to the workstations, managed centrally from a security and update point of view, occurs by authorized parties using specific dedicated credentials.

## Data security

The data custodian is the Italian National Institute of Health (ISS). Data are not transferable outside of ISS
and the analyses are executed within the institution. Data are backed up through storage on a specific
server. Several provisions have been put in place to prevent sensitive data leaks. Demographic and
personal data are stored in a separated database and their linkage to clinical and health data takes place
through a unique identification code. Data are pseudonymized using a unique personal code. The final
cohort of I-CARE4OLD data contains no direct identifiable information and is stored on a specific server.
As an additional security measure, the data used in the project are processed internally at ISS. Only
authorized personnel with a direct involvement in the project have access to the data. Data will be stored
at ISS; the retention period should be until the end of the study.

## Legal basis for use

The legal basis for the processing of personal data carried out by the ISS (the Italian beneficiary in the I-CARE4OLD project), is found for common data in the article 6, par 1, lett. e) GDPR, as "processing is necessary for the performance of a task carried out in the public interest or in the exercise of official authority vested in the controller", and, for the special categories of personal data, in the article 9, par. 2, lett. i) GDPR, as "processing is necessary for reasons of public interest in the area of public health”, and in the article 9, par. 2, lett. j) GDPR, as "processing is necessary for (…) scientific research purposes (…) based on Union or Member State law”. The special derogation on which data can be processed by ISS is the decree of 24 October 2014: Approval of the Statute of the Instituto Superiore di Sanità, pursuant to article 2 of the legislative decree of 28 June 2012, n. 106, as adapted to the Legislative Decree. n. 218/2016 by virtue of Resolution no. 1 – Board of Directors 26.7.2022 2. In particular, the statute provides that the ISS in the exercise of its functions, directly carries out research activities and promotes, participates in and coordinates study programs and research of national and international interest. Umbria Region owns the pseudonymisation key linked to the social security number of the clients. When linking is requested, interRAI data, hospital records and drug dispensation records are communicated back to Umbria Region, which carry out the linkage and transmit back the pseudonymized data.

## Data re-use

Obtaining and being granted permission to use RAI data must be authorized by the competent regional authorities that hold the data. Data collection takes place within the individual regions that have adopted the RAI tools as the instruments for comprehensive geriatric assessment in facilities and services dedicated to older adults.

In Italy, obtaining personal data for research purposes, including testing algorithms, is governed by the **GDPR** and the **Italian Data Protection Code (Legislative Decree No. 196/2003)**. The following steps are generally involved:
 
- **Informed Consent**: Researchers must obtain explicit consent from individuals whose data will be used. This consent should clearly outline the purpose of the research, how the data will be used, and the rights of the participants.
- **Data Minimization**: Only the necessary data should be collected to achieve the research purpose.
- **Data Anonymization or Pseudonymization**: When possible, data should be anonymized or pseudonymized to reduce privacy risks.
- **Ethics Committee Approval**: For certain types of research, especially involving sensitive data (e.g., health data), approval from an ethics committee may be required. The committee ensures that the research complies with ethical standards and legal requirements.
- **Data Controller and Processor**: Clear roles must be defined between the data controller (the entity responsible for the data) and data processors (those handling the data on behalf of the controller).
- **Barriers**: Barriers may include difficulties in obtaining informed consent, especially for sensitive data, as well as the complexity of navigating ethical review processes. Delays in approval from ethics committees can also be an obstacle.
