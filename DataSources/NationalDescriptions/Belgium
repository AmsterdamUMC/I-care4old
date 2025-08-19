# Description of I-CARE4OLD data source: Belgium

## Data controller

Belgian Federal Government

## Data contents

* interRAI data
    - Home care (HC): 2752 persons / 4606 assessments
    - Long-term care (LTC): 650 persons / 1050 assessments
    - Instrument versions: interRAI Suite 9.1
    - Medication information: not collected
* Hospital visits
* Deaths
* Medication
* Non-pharmacological interventions
* Moving to LTC service

The available data cover the years 2011–2021. The data are collected electronically using interRAI instruments (version 9.1) in periods of 6–12 months. The interRAI data set does not contain information on medications. Belgium is able to link hospital visits, deaths, medication events, non-pharmacological events, and change of care events to interRAI data. These events are available from the Belgian Intermutualistic Agency (IMA) database for all medical/care consumption (treatments and drugs). Because of privacy issues, event dates may only be provided by month and year.

## Data collection

### interRAI data

Belgian interRAI data are collected by professional caregivers working in nursing homes or home care organizations. They fill out the interRAI data using the standardised interRAI LTCF (long-term care facilities) or the interRAI HC (home care) instruments. They are mostly nurses, physiotherapists, occupational therapists, physicians, nurse aids, social workers etc., responsible for the care of older persons. The interRAI is filled out for practical use in these organizations, but is also used for quality improvement and research. For secondary use, an approval from the Belgian Privacy Commission is needed. (For this project, the approval was acquired on May 9, 2023.) The data are filled out in a secure platform from the Federal government (BelRAI.org), as well as from the Flemish Community government (Status Vlaams BelRAI-platform en toepassingen | Zorg en Gezondheid (zorg-en-gezondheid.be). These platforms are connected to a data warehouse in Healthdata.be, hosted by the Federal Institute Sciensano.

### Non-interRAI data

For non-interRAI event data, the registry database Intermutualistic Agency (IMA) contains data on treatments, consumption of medications, hospitalizations, medical consultations, as well as death. The database is constructed from data on invoices reimbursed by the National Institute for Health and Disability Insurance (NIHDI). The IMA data are filled out by the mutualities, which are official institutions handling the invoicing of medical services and prescribed drugs. Billing data from services and prescribed drugs are transferred to the national insurance institute (NIHDI), which reimburses the clients and care providers.  Data from invoices from care organizations such as hospitals or clinics, nursing homes, home care organizations are also transferred to the National Insurance through the mutualities and are included in the IMA database.

## Linkage and pseudonymisation

The interRAI data from Belgian organizations and the pseudonyms of all clients registered in the BelRAI database are kept in the data warehouse of Healthdata.be. Healthdata.be then transfers this list of unique pseudonyms for decoding to eHealth, which has the original Social Security Identification Numbers (INSS), generating a new unique pseudonym for each national number to be coupled with the registry data by a unique key. This list of pseudonyms and the key is transferred to a Trusted Third Party appointed by the Belgian Privacy Commission, also called Information Security Committee (IVC), and to the IMA, which hosts the national registry data. The IMA selects the necessary data from the IMA warehouse and transfers this data back to the Trusted Third Party. Healthdata.be selects the BelRAI data of the persons who are also represented in the IMA database. After this, Healthdata.be sends the BelRAI data to the TTP and the TTP places both databases in the IMA Project Data Warehouse. A Small Cell Risk Analysis (SCRA) is performed if deemed necessary by the Information Security Committee (IVC). Both databases are then made available to the researchers by a VPN connection. All data stays in the IMA Project Data Warehouse. No data can be copied or stored in other servers or storage devices, which complies to the highest data protection standards.

## Data security

The responsible for the use of the data is the principal investigator (prof. dr. Anja Declercq, from KU Leuven). The organization responsible for the secure storage of the data is the IMA (InterMutualistisch Agentschap), with Birgit Gielen as director. The IMA provides back up of the data, as well as a fault tolerance system. These features are provided in a secure server which can only be accessed with a VPN connection and a secure key. The following features are in place to prevent data leaks: Security policy guidelines, organizational measures such as confidential agreements and training of personnel, network security, provision of loggings and documentation, as well as the supervision by a data protection officer. The data will be stored in a safe server at the IMA. The data cannot be copied or transferred out of this server and can only be accessed remotely by the researcher of the KU Leuven, using a VPN connection and a secure key. The key is automatically generated for each session of use. Data will only be available during the period of the I-CARE4OLD project and 2–3 years after. Then, the access to the data will be terminated.

## Legal basis for use

Processing of routinely collected health data is permitted – under certain conditions – for scientific research. The legal basis follows GDPR art.9, par.2 (i, j), with exceptions arranged under Belgian AVG law "Wet van 30 juli 2018" (Belgian Act on Data Protection, C – 2018/40581) art. 186–208, the national application of EU's GDPR. All data is pseudonymised by a Trusted Third Party appointed by the Ethical Committee, also called Information Security Committee (IVC). Re-identification is not possible.

## Data re-use

Researchers can request the data via the following procedure:

1. Ask official permission from the BelRAI unit at the Federal government for obtaining the BelRAI data – FOD Volksgezondheid, Veiligheid van de Voedselketen en Leefmilieu. Once they agree to give the data, they will make a contract with the receiver of the data.
2. Ask official permission from the Intermutualistische Agentschap (IMA) to have access to the registry data of health consumption (medications, hospitalizations and treatments).
3. Fill out the form of the Privacy Commission (IVC) with information about the organizations that will deliver the data (previous), the receiver of the data, and the reason why you need the data. The form has to be filled out with the following information as well:

    - Which variables/items of the assessment are needed and why
    - How data will be linked to other database by a trusted third party
    - How Small Cell Risk Analysis will be performed, and 
    - How data will be stored and handled safely

The data remains in the server of the IMA and the BelRAI data is added to that server. It is prohibited to take the data out of that server. Access to the server is made by VPN connection, using a token. There is a high price to get access to the data, as the agencies charge fees for handling the data and cleaning and matching the databases.
