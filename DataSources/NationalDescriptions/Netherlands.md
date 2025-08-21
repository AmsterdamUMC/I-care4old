# Description of I-CARE4OLD data source: The Netherlands

## Data controller

Amsterdam University Medical Centers (AUMC)

## Data contents

* interRAI data (sample sizes for 2014–2018)
    - Home care (HC): 2,424 persons / 7,440 assessments
    - Long-term care (LTC): 2,239 persons / 4,513 assessments
    - Instrument versions: interRAI Suite 9.1, CHA and Check-up Plus (only HC)
    - Medication information: selected medication categories
* Hospital visits
* Deaths
* Medication
* Living arrangement

The Dutch interRAI data are controlled by the care organisations, but Amsterdam University Medical Centers (VUMC) have pseudonymised exports of the data. The available data cover the years 2005–2021 and are collected electronically using interRAI instruments (version 9.1), and in home care, also with a concise form of the interRAI HC instrument (CHA and Check-up Plus). The period of data collection varies with the care organisation. The data cover about 1% of the older persons in the country, as interRAI assessments are used only in certain regions, in a mixed set of care organisations. The Netherlands is able to link hospital visits, deaths, medications, and living arrangement events to interRAI data. These events come from the Dutch Hospital Data admission repository (DHD, hospital visits), the municipal administrations (death and living situation), medication registry from public pharmacies and hospitals (including care homes but excluding nursing homes).

## Data collection

### interRAI data

In the Netherlands, interRAI data are collected as routine healthcare assessments within different care organizations by trained health professionals in primary care, homecare and long-term care settings. The assessments are done through licensed Software vendors Pyxicare & Mensken. A unique code, so-called pseudonym, is assigned to every patient by vendors that can be linked to their original ID. Amsterdam UMC/VUmc receives pseudonymised data exports.

### Non-RAI data

The Dutch team at Amsterdam UMC are able to link interRAI data to national registries on hospitalizations, mortality date, date of long-term care admission, and medications. Hospitalisations are recorded by hospitals' own registries, mortality date and living situation is registered in municipality registries, and issued medication data is collected by community and hospital pharmacies. These registries are hosted at Statistics Netherlands (CBS) in a protected digital environment.

## Linkage and pseudonymisation

For linkage, the software vendors extract and upload a file holding identifiable variables only together with the pseudonym to a secured linkage partition of Statistics Netherlands. Researchers from Amsterdam UMC location VUMC upload cleaned and harmonised interRAI data including the same pseudonym to a secured research partition of Statistics Netherlands. Within the secured linkage partition, Statistics Netherlands links the identifiable data to unique persons and assigns a national unique pseudonym, a so-called RIN number. A new keyed file is created with the interRAI pseudonym and the RIN number. This keyed file is added to the secured research partition to allow the researchers to link persons with interRAI assessments to the other registries that all have an RIN number.

## Data security

Professor Hein van Hout, Amsterdam university Medical Centers, is responsible for secure storage and transfer of the data. Data Backups are stored at a secured cloud of Amsterdam University medical center location VUMC. All Content Data is coded (pseudonymised) without direct identifiable information and stored on password and authentication secured clouds (at VUMC, MyDRE and Statistics Netherlands). After approval of the supervisor (Hein van Hout) colleagues and I-CARE4OLD researchers can access the data. They cannot download the data. Deidentified interRAI data is stored at VUMC's secured cloud for at least 15 years. The linked data is stored at the secured cloud of Statistics Netherlands for about 10 years. The interRAI data stored at MyDRE secured cloud will be stored as long as researchers remain active. 

## Legal basis for use

Processing of health data is permitted for scientific research, under conditions. This is defined by two laws: the UAVG (Dutch GDPR Implementing act, articles 24 and 28)  and WGBO (Dutch Act on Medical Treatment Contracts which is part of the civil code, articles 7:457 and 7:458). The starting point for secondary use of health care data is that participants are asked for GDPR consent for provision and secondary use. Exemptions to this principle are possible under certain conditions, with the UAVG and WGBO providing the derogations on which the data can be used (this has been assessed as part of the ethical review process). Fon linking data, a pseudonym is assigned to every patient by RAI software vendors. The software vendors extract and upload a file holding identifiable variables only together with the pseudonym to a secured linkage partition of Statistics Netherlands. Within the secured linkage partition, Statistics Netherlands links the identifiable data to unique persons and assigns a national unique pseudonym, a so-called RIN number. A new keyed file is created with the interRAI pseudonym and the RIN number to allow the researchers to link persons with interRAI assessments to the other registries that all have an RIN number.

## Data re-use

Requests to analyse interRAI data can be directed to the national interRAI fellow who oversees implementations and governs data collections, currently prof. Hein van Hout at Amsterdam UMC. Pseudonymised remain on a secured data platform (MyDre). If a request is regarded valid, the requester can receive terminal access to this data platform for analyses. Common statistical packages are available and comprise SPSS, R studio, Python.