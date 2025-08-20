
###Syntax prepared by Ilona Baranska & Adrianna Ziuziakowska (UJCM)
##version 1; 08/20/2023

#The analysis is concerned to compare how many patients/clients continue or do not continue therapy comparing two time points
#The result of the analysis is the categorization of patients/clients into four groups 
#       (see attached Table 1 for iCodes version or 2 for MDS):
#1 - stable no intervention (If the patient/client has not received therapy at two assessment points)
#2 - stable intervention (if the patient/client received therapy at two assessment points)
#3 - discontinued intervention (if the patient/client received therapy only at the first measurement point)
#4 - new intervention (if the patient received therapy only at the second measurement point)

#The time between next assessments depends on how often data were collected in your country
#We would like to compare four assessments that were conducted in a similar time interval (e.g., for every three months)

#The variable that determines next assessments should be coded as 1, 2, 3 and 4 
#If you have any doubts on this matter, contact with Ilona Baranska (ilona.baranska@uj.edu.pl)

#Remember to have only one measurement per respondent at one assessment point!
#The analysis requires reconstructing the database from long to wide (see details below)

#Before analysis:
#1. Select data between 2014 and 2018 
#2. Determine the period between assessments (e.g., every three months - it depends on how often measurements were conducted)
#3. Create a new variable (Assess_type), which will determine the following  assessments 
#           (1- first assessment, 2 - second, 3-third and 4 -fourth)

# !Note:
# To choose patients/clients for analysis you can start from 2014
# Select all patients/clients who had an assessment in that year and add three more assessments at similar time intervals (e.g., every three months)
# Don't exclude patients/clients from the analysis if they don't have all four assessments
# To include a patient/client in the analysis it is enough if they have assessment 1 and assessments 2 
# In the analysis, we compare the next two assessments (1 vs 2, 2 vs 3, 3 vs 4)
# So it is not necessary for the patient/client to have all four assessments





############################################ interRAI Manual HC v9 ########################################################

###MDS version ---> line 500

#############################################################################################################################

#### The analysis requires the following variables;
# Please double check if the variable coding is consistent and modify if necessary
# ID: Identifier
# Age: age                 # Note: Modify when necessary
# iA8: Assessment type, 1: First assessment; 2: Routine reassessment; 3: Return assessment;
#                       4: Significant change in status reassessment; 5: Discharge assessment, covers last 3 days of service;
#                       6: Discharge tracking only; 7: Other e.g., research  # Note: Modify when necessary
# Assess_type:   1: first assessment;
#               2: second assessment;
#               3: third assessment;
#               4: four assessment;
# iF1a: Social activities:
#     0: never;
#     1: more than 30 days ago;
#     2: 8 to 30 days ago;
#     3: 4 to 7 days ago;
#     4: last 3 days;
#     8: Unable to determine;
# iG6a: Hours exercise:
#     0: none;
#     1: less than 1 hour;
#     2: 1-2 hours;
#     3: 3-4 hours;
#     4: more than 4 hours;
# iG6b: Days went out:
#     0: no days out;
#     1: not out, usually out;
#     2: 1-2 days out;
#     3: 3 days out;
# iN3ea: Physical therapy: days of care (at last 15 minutes) in last 7 days;
# iN3fa: Occupational therapy: days of care (at last 15 minutes) in last 7 days;
# iN3ga: Speech therapy: days of care (at last 15 minutes) in last 7 days;
# iN3ha: Psychological therapies: days of care (at last 15 minutes) in last 7 days;
# iN3aa: Home health aides, days of care (at last 15 minutes) in last 7; 
# iN3ba: Home nurse, days of care (at last 15 minutes) in last 7; 
# iN3ca: Homemaking services, days of care (at last 15 minutes) in last 7; 
# iN3da: Meals, days of care (at last 15 minutes) in last 7; 
# iN1e: Dental exam: 0:no, 1: yes;
# iN1f: Hearing exam: 0:no, 1: yes;
# iN1g: Eye exam: 0:no, 1: yes;
# iN4: Physical restraints: 0:no, 1: yes;
# iN2k: Wound care:
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN2l: Scheduled toileting programme:
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN2m: Palliative care:  
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN2n: Turning programe: 
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN5c: Physician visit,number of visits in last 90 days:
# iK3:  Mode of nutritional intake:
#     0: normal;
#     1: mod independence;
#     2: mod to swallow solids;
#     3: mod to swallow liquids;
#     4: only swallow puree;
#     5: oral & parenteral tube;
#     6: nasogastric tube;
#     7: abdmonial feeding;
#     8: parenteral feeding;
#     9: activity did not occur; 
# iH2: Urinary collection device:
#     0: none;
#     1: Condom catheter;
#     2: indwelling catheter;
#     3: Cystostomy; 
# iH4: Pads worn: 0:no, 1: yes;
# iQ2: Handicapped re-engineered apartment: 0:no, 1: yes; 
# iQ3a: Emergency assistance available: 0:no, 1: yes; 

###Step1 Install packages and prepare your own data

##Install packages

#install.packages(c("haven", "tidyr", "dplyr", "reshape2", "tableone"))
library(haven); library(tidyr); library(dplyr); library(reshape2); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format
data <- read_sav('C:/Users/ziuziakowskaa/Desktop/SHELTER_meds_totalANONYM CZYSTA HC.sav')

## Select relevant variables for analysis
mydata <- data [ , c("ID", "age", "iA8", "Assess_type","iF1a", "iG6a","iG6b",
                     "iN3ea","iN3fa", "iN3ga", "iN3ha", "iN3aa", "iN3ba", "iN3ca", "iN3da", "iN1e", "iN1f","iN1g", "iN4",
                     "iN2k","iN2l", "iN2m",  "iN2n", "iN5c", "iK3","iH2", "iH4", "iQ2", "iQ3a")]


##Recode the variables for selected nonpharmocologic therapies (NPIs) into dichotomous variables

#Social activities
mydata$iF1a_r[mydata$iF1a<=1] <- "1"
mydata$iF1a_r[mydata$iF1a>=2 & mydata$iF1a<=4] <- "2" 

#Hours exercise
mydata$iG6a_r <- "1"
mydata$iG6a_r[mydata$iG6a>0 & mydata$iG6a<=4] <- "2"
mydata$iG6a_r[is.na(mydata$iG6a)] <- NA
mydata$iG6a_r[mydata$iG6a >4] <- NA

#Days went out
mydata$iG6b_r <- "1"
mydata$iG6b_r[mydata$iG6b>0 & mydata$iG6b<=4] <- "2"
mydata$iG6b_r[is.na(mydata$iG6b)] <- NA
mydata$iG6b_r[mydata$iG6b >4] <- NA

#Physical therapy
mydata$iN3ea_r <- "1"
mydata$iN3ea_r[mydata$iN3ea>0 & mydata$iN3ea<=7] <- "2"
mydata$iN3ea_r[is.na(mydata$iN3ea)] <- NA
mydata$iN3ea_r[mydata$iN3ea>7] <- NA

#Occupational therapy
mydata$iN3fa_r <- "1"
mydata$iN3fa_r[mydata$iN3fa>0 & mydata$iN3fa<=7] <- "2"
mydata$iN3fa_r[is.na(mydata$iN3fa)] <- NA
mydata$iN3fa_r[mydata$iN3fa>7] <- NA

#Speech therapy
mydata$iN3ga_r <- "1"
mydata$iN3ga_r[mydata$iN3ga>0 & mydata$iN3ga<=7] <- "2"
mydata$iN3ga_r[is.na(mydata$iN3ga)] <- NA
mydata$iN3ga_r[mydata$iN3ga>7] <- NA

#Psychological therapies
mydata$iN3ha_r <- "1"
mydata$iN3ha_r[mydata$iN3ha>0 & mydata$iN3ha<=7] <- "2"
mydata$iN3ha_r[is.na(mydata$iN3ha)] <- NA
mydata$iN3ha_r[mydata$iN3ha>7] <- NA

#Home health aides
mydata$iN3aa_r <- "1"
mydata$iN3aa_r[mydata$iN3aa>0 & mydata$iN3aa<=7] <- "2"
mydata$iN3aa_r[is.na(mydata$iN3aa)] <- NA
mydata$iN3aa_r[mydata$iN3aa>7] <- NA

#Home nurse
mydata$iN3ba_r <- "1"
mydata$iN3ba_r[mydata$iN3ba>0 & mydata$iN3ba<=7] <- "2"
mydata$iN3ba_r[is.na(mydata$iN3ba)] <- NA
mydata$iN3ba_r[mydata$iN3ba>7] <- NA

#Homemaking services
mydata$iN3ca_r <- "1"
mydata$iN3ca_r[mydata$iN3ca>0 & mydata$iN3ca<=7] <- "2"
mydata$iN3ca_r[is.na(mydata$iN3ca)] <- NA
mydata$iN3ca_r[mydata$iN3ca>7] <- NA

#Meals
mydata$iN3da_r <- "1"
mydata$iN3da_r[mydata$iN3da>0 & mydata$iN3da<=7] <- "2"
mydata$iN3da_r[is.na(mydata$iN3da)] <- NA
mydata$iN3da_r[mydata$iN3da>7] <- NA

#Dental exam in last year
mydata$iN1e_r <- "1"
mydata$iN1e_r[mydata$iN1e==1] <- "2"
mydata$iN1e_r[is.na(mydata$iN1e)] <- NA

#Hearing exam in last 2 years
mydata$iN1f_r <- "1"
mydata$iN1f_r[mydata$iN1f==1] <- "2"
mydata$iN1f_r[is.na(mydata$iN1f)] <- NA

#Eye exam in last year
mydata$iN1g_r <- "1"
mydata$iN1g_r[mydata$iN1g==1] <- "2"
mydata$iN1g_r[is.na(mydata$iN1g)] <- NA

#Physical restraints
mydata$iN4_r <- "1"
mydata$iN4_r[mydata$iN4==1] <- "2"
mydata$iN4_r[is.na(mydata$iN4)] <- NA

#Wound care
mydata$iN2k_r <- "1"
mydata$iN2k_r[mydata$iN2k==2 | mydata$iN2k==3] <- "2"
mydata$iN2k_r[is.na(mydata$iN2k)] <- NA

#Scheduled toileting program
mydata$iN2l_r <- "1"
mydata$iN2l_r[mydata$iN2l==2 | mydata$iN2l==3] <- "2"
mydata$iN2l_r[is.na(mydata$iN2l)] <- NA

#Palliative care
mydata$iN2m_r <- "1"
mydata$iN2m_r[mydata$iN2m==2 | mydata$iN2m==3] <- "2"
mydata$iN2m_r[is.na(mydata$iN2m)] <- NA

#Turning programe
mydata$iN2n_r <- "1"
mydata$iN2n_r[mydata$iN2n==2 | mydata$iN2n==3] <- "2"
mydata$iN2n_r[is.na(mydata$iN2n)] <- NA

#Physician visit
mydata$iN5c_r <- "1"
mydata$iN5c_r[mydata$iN5c>0] <- "2"
mydata$iN5c_r[is.na(mydata$iN5c)] <- NA

#PEG feeding
mydata$iN2aaa_r <- "1"
mydata$iN2aaa_r[mydata$iK3 ==7] <- "2"
mydata$iN2aaa_r[mydata$iK3 >0 & mydata$iK3 <=6] <- NA
mydata$iN2aaa_r[mydata$iK3 >7 & mydata$iK3 <9] <- NA

#Nasogastric feeding (LTCF)
mydata$iN2zz_r <- "1"
mydata$iN2zz_r[mydata$iK3 ==6] <- "2" 
mydata$iN2zz_r[is.na(mydata$iK3)] <- NA
mydata$iN2zz_r[mydata$iK3 >0 & mydata$iK3 <=5] <- NA
mydata$iN2zz_r[mydata$iK3 >6 & mydata$iK3 <9] <- NA

#Urinary collection device
mydata$iH2_r <- "1"
mydata$iH2_r[mydata$iH2>0 & mydata$iH2<=3] <- "2"
mydata$iH2_r[is.na(mydata$iH2)] <- NA

#Pads worn
mydata$iH4_r <- "1"
mydata$iH4_r[mydata$iH4==1] <- "2"
mydata$iH4_r[is.na(mydata$iH4)] <- NA

#Handicapped re-engineered apartment
mydata$iQ2_r <- "1"
mydata$iQ2_r[mydata$iQ2==1] <- "2"
mydata$iQ2_r[is.na(mydata$iQ2)] <- NA

#Emergency assistance available
mydata$iQ3a_r <- "1"
mydata$iQ3a_r[mydata$iQ3a==1] <- "2"
mydata$iQ3a_r[is.na(mydata$iQ3a)] <- NA


## Apply inclusion criteria 
# Inclusion criteria 1. Exclude discharge or return assessment
mydata$iA8_r[mydata$iA8==1 | mydata$iA8==2 | mydata$iA8==4 | mydata$iA8==7] <- "1"
mydata$iA8_r[mydata$iA8==3 | mydata$iA8==5 | mydata$iA8==6 ] <- "2"
mydata <- mydata[!is.na(mydata$iA8_r) & mydata$iA8_r == 1,]

# Inclusion criteria 2. People aged 60+
n.under60 <- length(unique(mydata[mydata$age <60, ]$ID))
mydata <- mydata[mydata$age >= 60, ]


###Step2
##Change your base from long to wide so that the next measurements are in columns labeled 1,2,3,4

# Arrange the dataset by assessment time within individual
mydata <- arrange(mydata, mydata$ID, mydata$Assess_type)

#Change your base from long to wide
mydata_wide <- pivot_wider(data=mydata,
                           names_from = "Assess_type",
                           id_cols = "ID",
                           values_from =c("iF1a_r", "iG6a_r","iG6b_r",
                                          "iN3ea_r","iN3fa_r", "iN3ga_r", "iN3ha_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", "iN3da_r", "iN1e_r", "iN1f_r","iN1g_r", "iN4_r",
                                          "iN2k_r","iN2l_r", "iN2m_r",  "iN2n_r", "iN5c_r", "iN2aaa_r", "iN2zz_r", "iH2_r", "iH4_r", "iQ2_r", "iQ3a_r"))


###Step 3

##Use following code for calculate NPIs changes

#Changes between Baseline (1) and first follow up (2)

create_change_column_wide1 <- function(data, column_name) {
  change_column <- paste0(column_name, "_change1")
  data[[change_column]] <- "stable no intervention"
  data[[change_column]][data[[paste0(column_name, "_1")]] == 2 & data[[paste0(column_name, "_2")]] == 2] <- "stable intervention"
  data[[change_column]][data[[paste0(column_name, "_1")]] == 2 & data[[paste0(column_name, "_2")]] == 1] <- "discontinued intervention"
  data[[change_column]][data[[paste0(column_name, "_1")]] == 1 & data[[paste0(column_name, "_2")]] == 2] <- "new intervention"
  data[[change_column]][is.na(data[[paste0(column_name, "_1")]]) | is.na(data[[paste0(column_name, "_2")]])] <- NA
  return(data)
}

# Apply the function to create change columns for each variable in mydata_wide

variables_to_change <- c("iF1a_r", "iG6a_r","iG6b_r",
                         "iN3ea_r","iN3fa_r", "iN3ga_r", "iN3ha_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", 
                         "iN3da_r", "iN1e_r", "iN1f_r","iN1g_r", "iN4_r",
                         "iN2k_r","iN2l_r", "iN2m_r",  "iN2n_r", "iN5c_r", "iN2aaa_r", 
                         "iN2zz_r", "iH2_r", "iH4_r", "iQ2_r", "iQ3a_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide1(mydata_wide, variable)
}

names(mydata_wide)[106:131] <- c("Social activities- change1", "Hours exercise- change1","Days went out- change1", "Physical therapy- change1",  
                                 "Occupational therapy- change1",  "Speech therapy- change1","Psychological therapies- change1 ","Home health aides- change1",
                                 "Home nurse- change1", "Homemaking services- change1", "Meals- change1", "Dental exam in last year- change1",
                                 "Hearing exam in last 2 years- change1","Eye exam in last year- change1", "Physical restraints- change1", 
                                 "Wound care- change1",  "Scheduled toileting program- change1",
                                 "Palliative care- change1","Turning programe- change1", "Physician visit- change1", "PEG feeding- change1", "Nasogastric feeding- change1",
                                 "Urinary collection device- change1", "Pads worn- change1", "Handicapped re-engineered apartment- change1", 
                                 "Emergency assistance available- change1")

###Step 4

##Use following code for calculate NPIs changes

#Changes between first (2) and second follow up (3)

create_change_column_wide2 <- function(data, column_name) {
  change_column <- paste0(column_name, "_change2")
  data[[change_column]] <- "stable no intervention"
  data[[change_column]][data[[paste0(column_name, "_2")]] == 2 & data[[paste0(column_name, "_3")]] == 2] <- "stable intervention"
  data[[change_column]][data[[paste0(column_name, "_2")]] == 2 & data[[paste0(column_name, "_3")]] == 1] <- "discontinued intervention"
  data[[change_column]][data[[paste0(column_name, "_2")]] == 1 & data[[paste0(column_name, "_3")]] == 2] <- "new intervention"
  data[[change_column]][is.na(data[[paste0(column_name, "_2")]]) | is.na(data[[paste0(column_name, "_3")]])] <- NA
  return(data)
}

# Apply the function to create change columns for each variable in mydata_wide

variables_to_change <- c("iF1a_r", "iG6a_r","iG6b_r",
                         "iN3ea_r","iN3fa_r", "iN3ga_r", "iN3ha_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", 
                         "iN3da_r", "iN1e_r", "iN1f_r","iN1g_r", "iN4_r",
                         "iN2k_r","iN2l_r", "iN2m_r",  "iN2n_r", "iN5c_r", "iN2aaa_r", 
                         "iN2zz_r", "iH2_r", "iH4_r", "iQ2_r", "iQ3a_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide2(mydata_wide, variable)
}

names(mydata_wide)[132:157] <- c("Social activities- change2", "Hours exercise- change2","Days went out- change2", "Physical therapy- change2",  
                                 "Occupational therapy- change2",  "Speech therapy- change2","Psychological therapies- change2 ","Home health aides- change2",
                                 "Home nurse- change2", "Homemaking services- change2", "Meals- change2", "Dental exam in last year- change2",
                                 "Hearing exam in last 2 years- change2","Eye exam in last year- change2", "Physical restraints- change2", 
                                 "Wound care- change2",  "Scheduled toileting program- change2",
                                 "Palliative care- change2","Turning programe- change2", "Physician visit- change2", "PEG feeding- change2", "Nasogastric feeding- change2",
                                 "Urinary collection device- change2", "Pads worn- change2", "Handicapped re-engineered apartment- change2", 
                                 "Emergency assistance available- change2")

###Step 5

##Use following code for calculate NPIs changes

#Changes between  second (3) and fourth follow up (4)

create_change_column_wide3 <- function(data, column_name) {
  change_column <- paste0(column_name, "_change3")
  data[[change_column]] <- "stable no intervention"
  data[[change_column]][data[[paste0(column_name, "_3")]] == 2 & data[[paste0(column_name, "_4")]] == 2] <- "stable intervention"
  data[[change_column]][data[[paste0(column_name, "_3")]] == 2 & data[[paste0(column_name, "_4")]] == 1] <- "discontinued intervention"
  data[[change_column]][data[[paste0(column_name, "_3")]] == 1 & data[[paste0(column_name, "_4")]] == 2] <- "new intervention"
  data[[change_column]][is.na(data[[paste0(column_name, "_3")]]) | is.na(data[[paste0(column_name, "_4")]])] <- NA
  return(data)
}

# Apply the function to create change columns for each variable in mydata_wide

variables_to_change <- c("iF1a_r", "iG6a_r","iG6b_r",
                         "iN3ea_r","iN3fa_r", "iN3ga_r", "iN3ha_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", 
                         "iN3da_r", "iN1e_r", "iN1f_r","iN1g_r", "iN4_r",
                         "iN2k_r","iN2l_r", "iN2m_r",  "iN2n_r", "iN5c_r", "iN2aaa_r", 
                         "iN2zz_r", "iH2_r", "iH4_r", "iQ2_r", "iQ3a_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide3(mydata_wide, variable)
}

names(mydata_wide)[158:183] <- c("Social activities- change3", "Hours exercise- change3","Days went out- change3", "Physical therapy- change3",  
                                 "Occupational therapy- change3",  "Speech therapy- change3","Psychological therapies- change3 ","Home health aides- change3",
                                 "Home nurse- change3", "Homemaking services- change3", "Meals- change3", "Dental exam in last year- change3",
                                 "Hearing exam in last 2 years- change3","Eye exam in last year- change3", "Physical restraints- change3", 
                                 "Wound care- change3",  "Scheduled toileting program- change3",
                                 "Palliative care- change3","Turning programe- change3", "Physician visit- change3", "PEG feeding- change3", "Nasogastric feeding- change3",
                                 "Urinary collection device- change3", "Pads worn- change3", "Handicapped re-engineered apartment- change3", 
                                 "Emergency assistance available- change3")


### Step 6 Create tables 

changeHC_1 <- CreateTableOne(vars = c("Social activities- change1", "Hours exercise- change1","Days went out- change1", "Physical therapy- change1",  
                                      "Occupational therapy- change1",  "Speech therapy- change1","Psychological therapies- change1 ","Home health aides- change1",
                                      "Home nurse- change1", "Homemaking services- change1", "Meals- change1", "Dental exam in last year- change1",
                                      "Hearing exam in last 2 years- change1","Eye exam in last year- change1", "Physical restraints- change1", 
                                      "Wound care- change1",  "Scheduled toileting program- change1",
                                      "Palliative care- change1","Turning programe- change1", "Physician visit- change1", "PEG feeding- change1", "Nasogastric feeding- change1",
                                      "Urinary collection device- change1", "Pads worn- change1", "Handicapped re-engineered apartment- change1", 
                                      "Emergency assistance available- change1"),data = mydata_wide, factorVars = c("Social activities- change1", "Hours exercise- change1","Days went out- change1", "Physical therapy- change1",  
                                                                                                                    "Occupational therapy- change1",  "Speech therapy- change1","Psychological therapies- change1 ","Home health aides- change1",
                                                                                                                    "Home nurse- change1", "Homemaking services- change1", "Meals- change1", "Dental exam in last year- change1",
                                                                                                                    "Hearing exam in last 2 years- change1","Eye exam in last year- change1", "Physical restraints- change1", 
                                                                                                                    "Wound care- change1",  "Scheduled toileting program- change1",
                                                                                                                    "Palliative care- change1","Turning programe- change1", "Physician visit- change1", "PEG feeding- change1", "Nasogastric feeding- change1",
                                                                                                                    "Urinary collection device- change1", "Pads worn- change1", "Handicapped re-engineered apartment- change1", 
                                                                                                                    "Emergency assistance available- change1"))
changeHC_1 <- print(changeHC_1, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop

# !Note: Please change to your own path
write.csv(changeHC_1,file="C:/Users/ziuziakowskaa/Desktop/Output_HC/Change_HC_1.csv")


changeHC_2 <- CreateTableOne(vars = c("Social activities- change2", "Hours exercise- change2","Days went out- change2", "Physical therapy- change2",  
                                      "Occupational therapy- change2",  "Speech therapy- change2","Psychological therapies- change2 ","Home health aides- change2",
                                      "Home nurse- change2", "Homemaking services- change2", "Meals- change2", "Dental exam in last year- change2",
                                      "Hearing exam in last 2 years- change2","Eye exam in last year- change2", "Physical restraints- change2", 
                                      "Wound care- change2",  "Scheduled toileting program- change2",
                                      "Palliative care- change2","Turning programe- change2", "Physician visit- change2", "PEG feeding- change2", "Nasogastric feeding- change2",
                                      "Urinary collection device- change2", "Pads worn- change2", "Handicapped re-engineered apartment- change2", 
                                      "Emergency assistance available- change2"),data = mydata_wide, factorVars = c("Social activities- change2", "Hours exercise- change2","Days went out- change2", "Physical therapy- change2",  
                                                                                                                    "Occupational therapy- change2",  "Speech therapy- change2","Psychological therapies- change2 ","Home health aides- change2",
                                                                                                                    "Home nurse- change2", "Homemaking services- change2", "Meals- change2", "Dental exam in last year- change2",
                                                                                                                    "Hearing exam in last 2 years- change2","Eye exam in last year- change2", "Physical restraints- change2", 
                                                                                                                    "Wound care- change2",  "Scheduled toileting program- change2",
                                                                                                                    "Palliative care- change2","Turning programe- change2", "Physician visit- change2", "PEG feeding- change2", "Nasogastric feeding- change2",
                                                                                                                    "Urinary collection device- change2", "Pads worn- change2", "Handicapped re-engineered apartment- change2", 
                                                                                                                    "Emergency assistance available- change2"))
changeHC_2 <- print(changeHC_2, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeHC_2,file="C:/Users/ziuziakowskaa/Desktop/Output_HC/Change_HC_2.csv")

changeHC_3 <- CreateTableOne(vars = c("Social activities- change3", "Hours exercise- change3","Days went out- change3", "Physical therapy- change3",  
                                      "Occupational therapy- change3",  "Speech therapy- change3","Psychological therapies- change3 ","Home health aides- change3",
                                      "Home nurse- change3", "Homemaking services- change3", "Meals- change3", "Dental exam in last year- change3",
                                      "Hearing exam in last 2 years- change3","Eye exam in last year- change3", "Physical restraints- change3", 
                                      "Wound care- change3",  "Scheduled toileting program- change3",
                                      "Palliative care- change3","Turning programe- change3", "Physician visit- change3", "PEG feeding- change3", "Nasogastric feeding- change3",
                                      "Urinary collection device- change3", "Pads worn- change3", "Handicapped re-engineered apartment- change3", 
                                      "Emergency assistance available- change3"),data = mydata_wide, factorVars = c("Social activities- change3", "Hours exercise- change3","Days went out- change3", "Physical therapy- change3",  
                                                                                                                    "Occupational therapy- change3",  "Speech therapy- change3","Psychological therapies- change3 ","Home health aides- change3",
                                                                                                                    "Home nurse- change3", "Homemaking services- change3", "Meals- change3", "Dental exam in last year- change3",
                                                                                                                    "Hearing exam in last 2 years- change3","Eye exam in last year- change3", "Physical restraints- change3", 
                                                                                                                    "Wound care- change3",  "Scheduled toileting program- change3",
                                                                                                                    "Palliative care- change3","Turning programe- change3", "Physician visit- change3", "PEG feeding- change3", "Nasogastric feeding- change3",
                                                                                                                    "Urinary collection device- change3", "Pads worn- change3", "Handicapped re-engineered apartment- change3", 
                                                                                                                    "Emergency assistance available- change3"))
changeHC_3 <- print(changeHC_3, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeHC_3,file="C:/Users/ziuziakowskaa/Desktop/Output_HC/Change_HC_3.csv")








######################################################## MDS v2 #######################################################

###!Note:
##There are differences between countries (Finland, Canada and the USA) in terms of variable names, 
#     as well as their presence in the database 
##The changes for Finland, Canada and USA are noted in the code and explained

#### The analysis requires the following variables;
# Please double check if the variable coding is consistent and modify if necessary
# ID: Identifier
# Age: age                 # Note: Modify when necessary
# A2: Reason for assessment: 1. Initial assessment; 2. Follow-up assessment; 3. Routine assessment at fixed intervals;
#                           4. Review within 30-day period prior to discharge from the program; 5. Review at return from hospital;
#                           6. Change in status; 7. Other # Note: Modify when necessary
# Assess_type:   1: first assessment;
#                2: second assessment;
#                3: third assessment;
#                4: four assessment;
# H6b: Hours of physical activities in the last 3 days:
#     0: two or more hours;
#     1: less than 1 hour;
# H6a: The number of days client usually went out of the house or building in which client lives:
#     0: every day;
#     1: 2-6 days a week;
#     2: 1 day a week;
#     3: no days;
# I2a: Use of pads or briefs to protect against wetness:
#     0: no;
#     1: yes;
# I2b: Use of an indwelling urinary catheter:
#     0: no;
#     1: yes;
# P1aA: Home health aides, days of care (at last 15 minutes) in last 7; 
# P1bA: Home nurse, days of care (at last 15 minutes) in last 7; 
# P1cA: Homemaking services, days of care (at last 15 minutes) in last 7; 
# P1jA: Meals, days of care (at last 15 minutes) in last 7; 
# K9e: Physical restraints: 0: no, 1:yes;
# Q3: Medication review by physician:
#     0: discussed with at least one physician (or no medication taken;
#     1: No single physician reviewed all medications;
# L2d: Enteral tube feeding: 0: no, 1:yes;
# P1fA (Note: Finland: P1dA): Physical therapy, days of care (at last 15 minutes) in last 7 days;
# P1gA (Note: Finland: P1eA): Occupational therapy, days of care (at last 15 minutes) in last 7 days;
# P1hA (Note: Finland:P1fA): Speech therapy, days of care (at last 15 minutes) in last 7 days;
# N5a (Note: not in USA): Antibiotics, systemic or topical: 0: no, 1:yes;
# N5b (Note: not in USA): Dressings: 0: no, 1:yes;
# N5c (Note: not in USA): Surgical wound care: 0: no, 1:yes;
# N5d (Note: not in USA): Other wound/ulcer care (e.g., pressure relieving device, nutrition, turning, debridement): 0: no, 1:yes;
# P2s (Note: not in USA): Hospice care:
#     0: not applicable;
#     1: scheduled, full adherence as prescribed;
#     2: scheduled, partial adherence;
#     3: scheduled, not received;


###Step1 Install packages and prepare your own data

##Install packages

#install.packages(c("haven", "tidyr", "dplyr", "reshape2", "tableone"))
library(haven); library(tidyr); library(dplyr); library(reshape2); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format
data <- read_sav('C:/Users/ziuziakowskaa/Desktop/SHELTER_meds_totalANONYM CZYSTA HC.sav')

## Select relevant variables for analysis

#################################################################################################
# !Note: Finland - change: "P1fA" --> "P1dA"; "P1gA" --> "P1eA"; "P1hA" --> "P1fA";
# !Note: USA - remove: "N5a", "N5b", "N5c","N5d", "P2s";
#################################################################################################

mydata <- data [ , c("ID", "age", "iA8", "Assess_type","H6b", "H6a", "I2a", "I2b", "P1aA", "P1bA", 
                     "P1cA", "P1jA", "K9e", "Q3", "L2d", "P1fA", 
                     "P1gA", "P1hA","N5a", "N5b", "N5c","N5d", "P2s")]
                     
                
##Recode the variables for selected nonpharmocologic therapies (NPIs) into dichotomous variables

#Hours exercise
mydata$iG6a_r <- "1"
mydata$iG6a_r[mydata$H6b==0] <- "2"
mydata$iG6a_r[is.na(mydata$H6b)] <- NA

#Days went out
mydata$iG6b_r <- "1"
mydata$iG6b_r[mydata$H6a>=0 & mydata$H6a<=2] <- "2"
mydata$iG6b_r[is.na(mydata$H6a)] <- NA

#Pads worn
mydata$iH4_r <- "1"
mydata$iH4_r[mydata$I2a == 1] <- "2"
mydata$iH4_r[is.na(mydata$I2a)] <- NA

#Urinary collection device
mydata$iH2_r <- "1"
mydata$iH2_r[mydata$I2b == 1] <- "2"
mydata$iH2_r[is.na(mydata$I2b)] <- NA

#Home health aides
mydata$iN3aa_r <- "1"
mydata$iN3aa_r[mydata$P1aA>0 & mydata$P1aA<=7] <- "2"
mydata$iN3aa_r[is.na(mydata$P1aA)] <- NA
mydata$iN3aa_r[mydata$P1aA>7] <- NA

#Home nurse
mydata$iN3ba_r <- "1"
mydata$iN3ba_r[mydata$P1bA>0 & mydata$P1bA<=7] <- "2"
mydata$iN3ba_r[is.na(mydata$P1bA)] <- NA
mydata$iN3ba_r[mydata$P1bA>7] <- NA

#Homemaking services
mydata$iN3ca_r <- "1"
mydata$iN3ca_r[mydata$P1cA>0 & mydata$P1cA<=7] <- "2"
mydata$iN3ca_r[is.na(mydata$P1cA)] <- NA
mydata$iN3ca_r[mydata$P1cA>7] <- NA

#Meals
mydata$iN3da_r <- "1"
mydata$iN3da_r[mydata$P1jA>0 & mydata$P1jA<=7] <- "2"
mydata$iN3da_r[is.na(mydata$P1jA)] <- NA
mydata$iN3da_r[mydata$P1jA>7] <- NA

#Physical restraints
mydata$iN4_r <- "1"
mydata$iN4_r[mydata$K9e==1] <- "2"
mydata$iN4_r[is.na(mydata$K9e)] <- NA

#Medication review by physician
mydata$Q3_r <- "1"
mydata$Q3_r[mydata$Q3==0] <- "2"
mydata$Q3_r[is.na(mydata$Q3)] <- NA

#Enteral tube feeding
mydata$L2d_r <- "1"
mydata$L2d_r[mydata$L2d==0] <- "2"
mydata$L2d_r[is.na(mydata$L2d)] <- NA

########################################################################################################################
#Physical therapy !Note: Finland: change for P1dA
mydata$iN3ea_r <- "1"
mydata$iN3ea_r[mydata$P1fA>0 & mydata$P1fA<=7] <- "2"
mydata$iN3ea_r[is.na(mydata$P1fA)] <- NA
mydata$iN3ea_r[mydata$P1fA>7] <- NA

#Occupational therapy !Note: Finland change for P1eA
mydata$iN3fa_r <- "1"
mydata$iN3fa_r[mydata$P1gA>0 & mydata$P1gA<=7] <- "2"
mydata$iN3fa_r[is.na(mydata$P1gA)] <- NA
mydata$iN3fa_r[mydata$P1gA>7] <- NA

#Speech therapy !Note: Finland change for P1fA
mydata$iN3ga_r <- "1"
mydata$iN3ga_r[mydata$P1hA>0 & mydata$P1hA<=7] <- "2"
mydata$iN3ga_r[is.na(mydata$P1hA)] <- NA
mydata$iN3ga_r[mydata$P1hA>7] <- NA
########################################################################################################################

####################################################################################################################
#Wound care !Note: not in USA
mydata$iN2k_r <- "1"
mydata$iN2k_r[mydata$N5a==1  | mydata$N5b==1 | mydata$N5c==1 | mydata$N5d==1] <- "2"
mydata$iN2k_r[is.na(mydata$N5a)] <- NA
mydata$iN2k_r[is.na(mydata$N5b)] <- NA
mydata$iN2k_r[is.na(mydata$N5c)] <- NA
mydata$iN2k_r[is.na(mydata$N5d)] <- NA

#Hospice care !Note: not in USA
mydata$iN2m_r <- "1"
mydata$iN2m_r[mydata$P2s==1 | mydata$P2s==2]<- "2"
mydata$iN2m_r[is.na(mydata$P2s)] <- NA
########################################################################################################################

## Apply inclusion criteria 

# Inclusion criteria 1. Exclude discharge or return assessment
mydata$iA8_r[mydata$A2==1 | mydata$A2==2 | mydata$A2==3 | mydata$A2==6 | mydata$A2==7] <- "1"
mydata$iA8_r[mydata$A2==4 | mydata$A2==5] <- "2"
mydata <- mydata[!is.na(mydata$iA8_r) & mydata$iA8_r == 1,]

# Inclusion criteria 2. People aged 60+
n.under60 <- length(unique(mydata[mydata$age <60, ]$ID))
mydata <- mydata[mydata$age >= 60, ]


###Step2
##Change your base from long to wide so that the next measurements are in columns labeled 1,2,3,4

# Arrange the dataset by assessment time within individual
mydata <- arrange(mydata, mydata$ID, mydata$Assess_type)


#Change your base from long to wide

#######################################################################################################################
#!Note: USA remove: "iN2k_r", "iN2m_r";
#######################################################################################################################

mydata_wide <- pivot_wider(data=mydata,
                           names_from = "Assess_type",
                           id_cols = "ID",
                           values_from =c("iG6a_r","iG6b_r", "iH4_r", "iH2_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", "iN3da_r", "iN4_r", 
                                          "Q3_r", "L2d_r", "iN3ea_r","iN3fa_r", "iN3ga_r","iN2k_r","iN2m_r"))


###Step 3

##Use following code for calculate NPIs changes.

#Changes between Baseline (1) and first follow up (2)

create_change_column_wide1 <- function(data, column_name) {
  change_column <- paste0(column_name, "_change1")
  data[[change_column]] <- "stable no intervention"
  data[[change_column]][data[[paste0(column_name, "_1")]] == 2 & data[[paste0(column_name, "_2")]] == 2] <- "stable intervention"
  data[[change_column]][data[[paste0(column_name, "_1")]] == 2 & data[[paste0(column_name, "_2")]] == 1] <- "discontinued intervention"
  data[[change_column]][data[[paste0(column_name, "_1")]] == 1 & data[[paste0(column_name, "_2")]] == 2] <- "new intervention"
  data[[change_column]][is.na(data[[paste0(column_name, "_1")]]) | is.na(data[[paste0(column_name, "_2")]])] <- NA
  return(data)
}

# Apply the function to create change columns for each variable in mydata_wide

#######################################################################################################################
#!Note: USA remove: "iN2k_r", "iN2m_r";
#######################################################################################################################


variables_to_change <- c("iG6a_r","iG6b_r", "iH4_r", "iH2_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", "iN3da_r", "iN4_r", 
                         "Q3_r", "L2d_r", "iN3ea_r","iN3fa_r", "iN3ga_r","iN2k_r","iN2m_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide1(mydata_wide, variable)
}



#######################################################################################################################
#!Note: USA remove:"Wound care- change1", "Hospice care- change1" and change to [58:71]
#######################################################################################################################

names(mydata_wide)[66:81] <- c("Hours exercise- change1","Days went out- change1", "Pads worn- change1",
                                 "Urinary collection device- change1", "Home health aides- change1",
                                 "Home nurse- change1", "Homemaking services- change1", "Meals- change1",
                                 "Physical restraints- change1","Medication review by physician-change1",
                                 "Enteral tube feeding-change1", "Physical therapy- change1", 
                                 "Occupational therapy- change1",  "Speech therapy- change1", 
                                  "Wound care- change1", "Hospiece care- change1")
                             
###Step 4

##Use following code for calculate NPIs changes

#Changes between  first (2) and second follow up (3)

create_change_column_wide2 <- function(data, column_name) {
  change_column <- paste0(column_name, "_change2")
  data[[change_column]] <- "stable no intervention"
  data[[change_column]][data[[paste0(column_name, "_2")]] == 2 & data[[paste0(column_name, "_3")]] == 2] <- "stable intervention"
  data[[change_column]][data[[paste0(column_name, "_2")]] == 2 & data[[paste0(column_name, "_3")]] == 1] <- "discontinued intervention"
  data[[change_column]][data[[paste0(column_name, "_2")]] == 1 & data[[paste0(column_name, "_3")]] == 2] <- "new intervention"
  data[[change_column]][is.na(data[[paste0(column_name, "_2")]]) | is.na(data[[paste0(column_name, "_3")]])] <- NA
  return(data)
}

# Apply the function to create change columns for each variable in mydata_wide

#######################################################################################################################
#!Note: USA remove: "iN2k_r", "iN2m_r";
#######################################################################################################################


variables_to_change <- c("iG6a_r","iG6b_r", "iH4_r", "iH2_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", "iN3da_r", "iN4_r", 
                         "Q3_r", "L2d_r", "iN3ea_r","iN3fa_r", "iN3ga_r","iN2k_r","iN2m_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide2(mydata_wide, variable)
}


#######################################################################################################################
#!Note: USA remove:"Wound care- change2", "Hospice care- change2" and change to [72:85]
#######################################################################################################################

names(mydata_wide)[82:97] <- c("Hours exercise- change2","Days went out- change2", "Pads worn- change2",
                                 "Urinary collection device- change2", "Home health aides- change2",
                                 "Home nurse- change2", "Homemaking services- change2", "Meals- change2",
                                 "Physical restraints- change2","Medication review by physician- change2",
                                 "Enteral tube feeding- change2", "Physical therapy- change2", 
                                 "Occupational therapy- change2",  "Speech therapy- change2", 
                                 "Wound care- change2", "Hospiece care- change2")

###Step 5

##Use following code for calculate NPIs changes

#Changes between  second (3) and fourth follow up (4)

create_change_column_wide3 <- function(data, column_name) {
  change_column <- paste0(column_name, "_change3")
  data[[change_column]] <- "stable no intervention"
  data[[change_column]][data[[paste0(column_name, "_3")]] == 2 & data[[paste0(column_name, "_4")]] == 2] <- "stable intervention"
  data[[change_column]][data[[paste0(column_name, "_3")]] == 2 & data[[paste0(column_name, "_4")]] == 1] <- "discontinued intervention"
  data[[change_column]][data[[paste0(column_name, "_3")]] == 1 & data[[paste0(column_name, "_4")]] == 2] <- "new intervention"
  data[[change_column]][is.na(data[[paste0(column_name, "_3")]]) | is.na(data[[paste0(column_name, "_4")]])] <- NA
  return(data)
}

# Apply the function to create change columns for each variable in mydata_wide

#######################################################################################################################
#!Note: USA remove: "iN2k_r", "iN2m_r";
#######################################################################################################################


variables_to_change <- c("iG6a_r","iG6b_r", "iH4_r", "iH2_r", "iN3aa_r", "iN3ba_r", "iN3ca_r", "iN3da_r", "iN4_r", 
                         "Q3_r", "L2d_r", "iN3ea_r","iN3fa_r", "iN3ga_r","iN2k_r","iN2m_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide3(mydata_wide, variable)
}


#######################################################################################################################
#!Note: USA remove:"Wound care- change3", "Hospice care- change3" and change to [86:99]
#######################################################################################################################

names(mydata_wide)[98:113] <- c("Hours exercise- change3","Days went out- change3", "Pads worn- change3",
                                 "Urinary collection device- change3", "Home health aides- change3",
                                 "Home nurse- change3", "Homemaking services- change3", "Meals- change3",
                                 "Physical restraints- change3","Medication review by physician- change3",
                                 "Enteral tube feeding- change3", "Physical therapy- change3", 
                                 "Occupational therapy- change3",  "Speech therapy- change3", 
                                  "Wound care- change3", "Hospice care- change3")


### Step 6 Create tables 

#######################################################################################################################
#!Note: USA remove:"Wound care- change1", "Hospice care- change1"
#######################################################################################################################

changeHC_1 <- CreateTableOne(vars = c("Hours exercise- change1","Days went out- change1", "Pads worn- change1",
                                      "Urinary collection device- change1", "Home health aides- change1",
                                      "Home nurse- change1", "Homemaking services- change1", "Meals- change1",
                                      "Physical restraints- change1","Medication review by physician- change1",
                                      "Enteral tube feeding- change1", "Physical therapy- change1", 
                                      "Occupational therapy- change1",  "Speech therapy- change1", 
                                      "Wound care- change1", "Hospice care- change1"),data = mydata_wide, factorVars = c("Hours exercise- change1","Days went out- change1", "Pads worn- change1",
                                                                                                                         "Urinary collection device- change1", "Home health aides- change1",
                                                                                                                         "Home nurse- change1", "Homemaking services- change1", "Meals- change1",
                                                                                                                         "Physical restraints- change1","Medication review by physician- change1",
                                                                                                                         "Enteral tube feeding- change1", "Physical therapy- change1", 
                                                                                                                         "Occupational therapy- change1",  "Speech therapy- change1", 
                                                                                                                         "Wound care- change1", "Hospice care- change1"))
changeHC_1 <- print(changeHC_1, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop

# !Note: Please change to your own path
write.csv(changeHC_1,file="C:/Users/ziuziakowskaa/Desktop/Output_HC/Change_HC_1.csv")

#######################################################################################################################
#!Note:  USA remove:"Wound care- change2", "Hospice care- change2"
#######################################################################################################################

changeHC_2 <- CreateTableOne(vars = c("Hours exercise- change2","Days went out- change2", "Pads worn- change2",
                                 "Urinary collection device- change2", "Home health aides- change2",
                                 "Home nurse- change2", "Homemaking services- change2", "Meals- change2",
                                 "Physical restraints- change2","Medication review by physician- change2",
                                 "Enteral tube feeding- change2", "Physical therapy- change2", 
                                 "Occupational therapy- change2",  "Speech therapy- change2", 
                                 "Wound care- change2", "Hospiece care- change2"),data = mydata_wide, factorVars = c("Hours exercise- change2","Days went out- change2", "Pads worn- change2",
                                                                                                                     "Urinary collection device- change2", "Home health aides- change2",
                                                                                                                     "Home nurse- change2", "Homemaking services- change2", "Meals- change2",
                                                                                                                     "Physical restraints- change2","Medication review by physician- change2",
                                                                                                                     "Enteral tube feeding- change2", "Physical therapy- change2", 
                                                                                                                     "Occupational therapy- change2", "Speech therapy- change2", 
                                                                                                                     "Wound care- change2", "Hospiece care- change2"))
changeHC_2 <- print(changeHC_2, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeHC_2,file="C:/Users/ziuziakowskaa/Desktop/Output_HC/Change_HC_2.csv")

#######################################################################################################################
#!Note: USA remove:"Wound care- change3", "Hospice care- change3"
#######################################################################################################################

changeHC_3 <- CreateTableOne(vars = c("Hours exercise- change3","Days went out- change3", "Pads worn- change3",
                                      "Urinary collection device- change3", "Home health aides- change3",
                                      "Home nurse- change3", "Homemaking services- change3", "Meals- change3",
                                      "Physical restraints- change3","Medication review by physician- change3",
                                      "Enteral tube feeding- change3", "Physical therapy- change3", 
                                      "Occupational therapy- change3",  "Speech therapy- change3", 
                                      "Wound care- change3", "Hospice care- change3"),data = mydata_wide, factorVars = c("Hours exercise- change3","Days went out- change3", "Pads worn- change3",
                                                                                                                         "Urinary collection device- change3", "Home health aides- change3",
                                                                                                                         "Home nurse- change3", "Homemaking services- change3", "Meals- change3",
                                                                                                                         "Physical restraints- change3","Medication review by physician- change3",
                                                                                                                         "Enteral tube feeding- change3", "Physical therapy- change3", 
                                                                                                                         "Occupational therapy- change3",  "Speech therapy- change3", 
                                                                                                                         "Wound care- change3", "Hospice care- change3"))
changeHC_3 <- print(changeHC_3, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeHC_3,file="C:/Users/ziuziakowskaa/Desktop/Output_HC/Change_HC_3.csv")


