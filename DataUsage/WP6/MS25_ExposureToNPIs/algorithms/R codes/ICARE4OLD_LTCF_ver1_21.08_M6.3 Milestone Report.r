
###Syntax prepared by Ilona Baranska & Adrianna Ziuziakowska (UJCM)
##version 1; 08/20/2023

#Analysis for "Report on non-pharmacological interventions and (dis)continuation during care trajectories - LTCF” under the ICARE4OLD project

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



############################################ interRAI Manual LTCF v9 ########################################################

###MDS version ---> line 785

#############################################################################################################################

#### The analysis requires the following variables;
# Please double check if the variable coding is consistent and modify if necessary
# ID: Identifier
# Age: age                 # Note: Modify when necessary
# iA8: Assessment type, 1: First assessment; 2: Routine reassessment; 3: Return assessment;
#                       4: Significant change in status reassessment; 5: Discharge assessment, covers last 3 days of service;
#                       6: Discharge tracking only; 7: Other e.g., research  # Note: Modify when necessary
# Assess_type:   1: first assessment;
#                2: second assessment;
#                3: third assessment;
#                4: fourth assessment;
# iN3ea: Physical therapy: days of care (at last 15 minutes) in last 7 days;
# iN3fa: Occupational therapy: days of care (at last 15 minutes) in last 7 days;
# iN3ga: Speech therapy: days of care (at last 15 minutes) in last 7 days;
# iN3ha: Psychological therapies: days of care (at last 15 minutes) in last 7 days;
# iN3ia: Respiratory therapy: days of care (at last 15 minutes) in last 7 days;
# iN3ja: Funcational rehabilitation: days of care (at last 15 minutes) in last 7 days;
# iD3b: Hearing aid used:  0: no; 1: yes;
# iD4b: Visual appliance used: 0: no; 1: yes;  
# iN2k: Wound care:
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN2n: Turning programe: 
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN2m: Palliative care:  
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iK3: Mode of nutritional intake:
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
# iK5:  Parenteral intake:
#     0: No parenteral/enteral tube;
#     1: Parenteral/enteral tube but no caloric intake;
#     2: 1% to 25% of total calories through device;
#     3: 26% or more of total calories through device;
# iF1a: Social activities:
#     0: never;
#     1: more than 30 days ago;
#     2: 8 to 30 days ago;
#     3: 4 to 7 days ago;
#     4: last 7 days;
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
# iH2: Urinary collection device:
#     0: none;
#     1: Condom catheter;
#     2: indwelling catheter;
#     3: Cystostomy;
# iH5:  Ostomy: 0: no; 1: yes; 
# iN1e: Dental exam: 0: no; 1: yes; 
# iN1f: Hearing exam: 0: no; 1: yes; 
# iN1g: Eye exam: 0: no; 1: yes; 
# iN2l: Scheduled toileting programme:
#      0: not orderd, did not occur;
#      1: order, not implemented;
#      2: 1-2 of last 3 days;
#      3: daily, in last 3 days;
# iN6b: Trunk restraint:
#      0: not used;
#      1: used less than daily;
#      2: used daily-nights only;
#      3: used daily-days only;
#      4: used night and days, but not constant;
#      5: constant use for full 24 hours;
# iN6c: Chairs prevents rising:
#      0: not used;
#      1: used less than daily;
#      2: used daily-nights only;
#      3: used daily-days only;
#      4: used night and days, but not constant;
#      5: constant use for full 24 hours;
# iN6a: Full bed rails:
#      0: not used;
#      1: used less than daily;
#      2: used daily-nights only;
#      3: used daily-days only;
#      4: used night and days, but not constant;
#      5: constant use for full 24 hours;
# iO2a: Do not resuscitate: 0: no; 1: yes; 
# iO2b: Do not intubate: 0: no; 1: yes; 
# iO2c: Do not hospitalize: 0: no; 1: yes; 
# iO2d: No tube feeding: 0: no; 1: yes; 
# iO2e: Medication restrictions: 0: no; 1: yes; 
# iS2n: Walking outdoors:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2h: Helping others:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2m: Trips/shopping: 
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2a: Cards/games:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2b: Computer use:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2c: Conversing:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2e: Dancing:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2f: Exercise:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2g: Gardening:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2k: Reading:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2l: Spiritual activities:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2o: TV:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2r: Reminiscing about life:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2i: Music: 
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2j: Pets: 
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days;
# iS2d: Crafts:
#      0: No preference;
#      1: No pref involved in last 3 days;
#      2: Pref, not involved;
#      3: Pref, not reg involved but not last 3 days;
#      4: Pref involved in last 3 days.


###Step1 Install packages and prepare your own data

##Install packages

install.packages(c("haven", "tidyr", "dplyr", "reshape2", "tableone"))
library(haven); library(tidyr); library(dplyr); library(reshape2); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format
data <- read_sav('C:/Users/User/Desktop/icare2023/database_example.sav')

## Select relevant variables for analysis
mydata <- data [ , c("ID", "age", "iA8", "Assess_type","iN3ea", "iN3fa" , "iN3ga" , "iN3ha" ,  "iN3ia", "iN3ja" ,
                     "iD3b",  "iD4b", "iN2k" ,  "iN2n" , "iN2m" , "iK3" , "iK5", "iF1a" ,  "iG6a" ,  "iG6b" ,"iH2" ,  
                     "iH5" ,  "iN1e",  "iN1f" ,  "iN1g" , "iN2l" , "iN6b" , "iN6c" , "iN6a" ,"iO2a" ,  "iO2b" , 
                     "iO2c" , "iO2d", "iO2e" , "iS2n" ,"iS2h" , "iS2m", "iS2a" , "iS2b" , "iS2c" , "iS2e" , "iS2f" , 
                     "iS2g" , "iS2k" , "iS2l" , "iS2o" , "iS2r" , "iS2i" , "iS2j" ,"iS2d")]


##Recode the variables for selected nonpharmocologic therapies (NPIs) into dichotomous variables

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

#Respiratory therapy
mydata$iN3ia_r <- "1"
mydata$iN3ia_r[mydata$iN3ia>0 & mydata$iN3ia<=7] <- "2"
mydata$iN3ia_r[is.na(mydata$iN3ia)] <- NA
mydata$iN3ia_r[mydata$iN3ia>7] <- NA

#Funcational rehabilitation
mydata$iN3ja_r <- "1"
mydata$iN3ja_r[mydata$iN3ja>0 & mydata$iN3ja<=7] <- "2"
mydata$iN3ja_r[is.na(mydata$iN3ja)] <- NA
mydata$iN3ja_r[mydata$iN3ja>7] <- NA

#Hearing aid used
mydata$iD3b_r <- "1"
mydata$iD3b_r[mydata$iD3b==1] <- "2"
mydata$iD3b_r[is.na(mydata$iD3b)] <- NA

#Visual appliance used
mydata$iD4b_r <- "1"
mydata$iD4b_r[mydata$iD4b==1] <- "2"
mydata$iD4b_r[is.na(mydata$iD4b)] <- NA

#Social activities
mydata$iF1a_r <- "1"
mydata$iF1a_r[mydata$iF1a>=2 & mydata$iF1a<=4] <- "2" 
mydata$iF1a_r[is.na(mydata$iF1a)] <- NA
mydata$iF1a_r[mydata$iF1a==8] <- NA

#Nasogastric feeding (LTCF)
mydata$iK3_r6 <- "1"
mydata$iK3_r6[mydata$iK3 ==6] <- "2" 
mydata$iK3_r6[is.na(mydata$iK3)] <- NA
mydata$iK3_r6[mydata$iK3 >0 & mydata$iK3 <=5] <- NA
mydata$iK3_r6[mydata$iK3 >6 & mydata$iK3 <9] <- NA

#Parenteral intake
mydata$iK5_r <- "1"
mydata$iK5_r[mydata$iK5 >0 & mydata$iK5 <=3] <- "2"
mydata$iK5_r[is.na(mydata$iK5)] <- NA

#Mode of nutritional intake
mydata$iK3_r <- "1"
mydata$iK3_r[mydata$iK3 >0 & mydata$iK3<=8] <- "2" 
mydata$iK3_r[is.na(mydata$iK3)] <- NA
mydata$iK3_r[mydata$iK3 >8] <- NA

#Hours exercise
mydata$iG6a_r <- "1"
mydata$iG6a_r[mydata$iG6a>0 & mydata$iG6a<=4] <- "2"
mydata$iG6a_r[is.na(mydata$iG6a)] <- NA
mydata$iG6a_r[mydata$iK3 >4] <- NA

#Days went out
mydata$iG6b_r <- "1"
mydata$iG6b_r[mydata$iG6b>0 & mydata$iG6b<=4] <- "2"
mydata$iG6b_r[is.na(mydata$iG6b)] <- NA
mydata$iG6b_r[mydata$iK3 >4] <- NA

#Urinary collection device
mydata$iH2_r <- "1"
mydata$iH2_r[mydata$iH2>0 & mydata$iH2<=3] <- "2"
mydata$iH2_r[is.na(mydata$iH2)] <- NA
mydata$iH2_r[mydata$iK3 >3] <- NA

#Ostomy
mydata$iH5_r <- "1"
mydata$iH5_r[mydata$iH5==1] <- "2"
mydata$iH5_r[is.na(mydata$iH5)] <- NA

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

#Palliative care
mydata$iN2m_r <- "1"
mydata$iN2m_r[mydata$iN2m==2 | mydata$iN2m==3] <- "2"
mydata$iN2m_r[is.na(mydata$iN2m)] <- NA

#Wound care
mydata$iN2k_r <- "1"
mydata$iN2k_r[mydata$iN2k==2 | mydata$iN2k==3] <- "2"
mydata$iN2k_r[is.na(mydata$iN2k)] <- NA

#Turning programe
mydata$iN2n_r <- "1"
mydata$iN2n_r[mydata$iN2n==2 | mydata$iN2n==3] <- "2"
mydata$iN2n_r[is.na(mydata$iN2n)] <- NA

#Scheduled toileting program
mydata$iN2l_r <- "1"
mydata$iN2l_r[mydata$iN2l==2 | mydata$iN2l==3] <- "2"
mydata$iN2l_r[is.na(mydata$iN2l)] <- NA

#Trunk restraint
mydata$iN6b_r <- "1"
mydata$iN6b_r[mydata$iN6b>=1 & mydata$iN6b<=5 ] <- "2"
mydata$iN6b_r[is.na(mydata$iN6b)] <- NA

#Chairs prevents rising
mydata$iN6c_r <- "1"
mydata$iN6c_r[mydata$iN6c>=1 & mydata$iN6c<=5] <- "2"
mydata$iN6c_r[is.na(mydata$iN6c)] <- NA

#Full bed rails
mydata$iN6a_r <- "1"
mydata$iN6a_r[mydata$iN6a>=1 & mydata$iN6a<=5] <- "2"
mydata$iN6a_r[is.na(mydata$iN6a)] <- NA

#Do not resuscitate
mydata$iO2a_r <- "1"
mydata$iO2a_r[mydata$iO2a==1] <- "2"
mydata$iO2a_r[is.na(mydata$iO2a)] <- NA

#Do not intubate
mydata$iO2b_r <- "1"
mydata$iO2b_r[mydata$iO2b>=1] <- "2"
mydata$iO2b_r[is.na(mydata$iO2b)] <- NA

#Do not hospitalize
mydata$iO2c_r <- "1"
mydata$iO2c_r[mydata$iO2c==1] <- "2"
mydata$iO2c_r[is.na(mydata$iO2c)] <- NA

#No tubefeeding
mydata$iO2d_r <- "1"
mydata$iO2d_r[mydata$iO2d==1] <- "2"
mydata$iO2d_r[is.na(mydata$iO2d)] <- NA

#Medication restriction
mydata$iO2e_r <- "1"
mydata$iO2e_r[mydata$iO2e==1] <- "2"
mydata$iO2e_r[is.na(mydata$iO2e)] <- NA

#Walking outdoors
mydata$iS2n_r <- "1"
mydata$iS2n_r[mydata$iS2n==1 | mydata$iS2n==3 | mydata$iS2n==4] <- "2"
mydata$iS2n_r[is.na(mydata$iS2n)] <- NA

#Helping others
mydata$iS2h_r<- "1"
mydata$iS2h_r[mydata$iS2h==1 | mydata$iS2h==3 | mydata$iS2h==4] <- "2"
mydata$iS2h_r[is.na(mydata$iS2h)] <- NA

#Trips/shopping
mydata$iS2m_r <- "1"
mydata$iS2m_r[mydata$iS2m==1 | mydata$iS2m==3 | mydata$iS2m==4] <- "2"
mydata$iS2m_r[is.na(mydata$iS2m)] <- NA

#Cards/games
mydata$iS2a_r <- "1"
mydata$iS2a_r[mydata$iS2a==1 | mydata$iS2a==3 | mydata$iS2a==4] <- "2"
mydata$iS2a_r[is.na(mydata$iS2a)] <- NA

#Computer use
mydata$iS2b_r <- "1"
mydata$iS2b_r[mydata$iS2b==1 | mydata$iS2b==3 | mydata$iS2b==4] <- "2"
mydata$iS2b_r[is.na(mydata$iS2b)] <- NA

#Conversing
mydata$iS2c_r <- "1"
mydata$iS2c_r[mydata$iS2c==1 | mydata$iS2c==3 | mydata$iS2c==4] <- "2"
mydata$iS2c_r[is.na(mydata$iS2c)] <- NA

#Dancing
mydata$iS2e_r <- "1"
mydata$iS2e_r[mydata$iS2e==1 | mydata$iS2e==3 | mydata$iS2e==4] <- "2"
mydata$iS2e_r[is.na(mydata$iS2e)] <- NA

#Exercise
mydata$iS2f_r <- "1"
mydata$iS2f_r[mydata$iS2f==1 | mydata$iS2f==3 | mydata$iS2f==4] <- "2"
mydata$iS2f_r[is.na(mydata$iS2f)] <- NA

#Gardening
mydata$iS2g_r <- "1"
mydata$iS2g_r[mydata$iS2g==1 | mydata$iS2g==3 | mydata$iS2g==4] <- "2"
mydata$iS2g_r[is.na(mydata$iS2g)] <- NA

#Reading
mydata$iS2k_r <- "1"
mydata$iS2k_r[mydata$iS2k==1 | mydata$iS2k==3 | mydata$iS2k==4] <- "2"
mydata$iS2k_r[is.na(mydata$iS2k)] <- NA

#Spiritual activities
mydata$iS2l_r <- "1"
mydata$iS2l_r[mydata$iS2l==1 | mydata$iS2l==3 | mydata$iS2l==4] <- "2"
mydata$iS2l_r[is.na(mydata$iS2l)] <- NA

#TV
mydata$iS2o_r<- "1"
mydata$iS2o_r[mydata$iS2o==1 | mydata$iS2o==3 | mydata$iS2o==4] <- "2"
mydata$iS2o_r[is.na(mydata$iS2o)] <- NA

#Reminiscing about life
mydata$iS2r_r <- "1"
mydata$iS2r_r[mydata$iS2r==1 | mydata$iS2r==3 | mydata$iS2r==4] <- "2"
mydata$iS2r_r[is.na(mydata$iS2r)] <- NA

#Music
mydata$iS2i_r <- "1"
mydata$iS2i_r[mydata$iS2i==1 | mydata$iS2i==3 | mydata$iS2i==4] <- "2"
mydata$iS2i_r[is.na(mydata$iS2i)] <- NA

#Pets
mydata$iS2j_r <- "1"
mydata$iS2j_r[mydata$iS2j==1 | mydata$iS2j==3 | mydata$iS2j==4] <- "2"
mydata$iS2j_r[is.na(mydata$iS2j)] <- NA

#Crafts
mydata$iS2d_r <- "1"
mydata$iS2d_r[mydata$iS2d==1 | mydata$iS2d==3 | mydata$iS2d==4] <- "2"
mydata$iS2d_r[is.na(mydata$iS2d)] <- NA


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
                           values_from =c("iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,  "iN3ia_r", "iN3ja_r", 
                                          "iD3b_r",  "iD4b_r", "iF1a_r" ,"iK3_r6" , "iK5_r", "iK3_r","iG6a_r" ,  "iG6b_r",
                                          "iH2_r" ,"iH5_r", "iN1e_r",  "iN1f_r" ,  "iN1g_r" ,"iN2m_r" ,"iN2k_r" ,  "iN2n_r" ,
                                          "iN2l_r" , "iN6b_r" , "iN6c_r" ,"iN6a_r", "iO2a_r" ,  "iO2b_r" ,"iO2c_r" , "iO2d_r", "iO2e_r",
                                          "iS2n_r" ,"iS2h_r" , "iS2m_r", "iS2a_r" , "iS2b_r" , "iS2c_r" , "iS2e_r" , "iS2f_r" ,
                                          "iS2g_r" , "iS2k_r" , "iS2l_r" , "iS2o_r" , "iS2r_r" , "iS2i_r" , "iS2j_r" ,"iS2d_r"))


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

variables_to_change <- c("iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,  "iN3ia_r", "iN3ja_r", 
                         "iD3b_r",  "iD4b_r", "iF1a_r" ,"iK3_r6" , "iK5_r", "iK3_r","iG6a_r" ,  "iG6b_r",
                         "iH2_r" ,"iH5_r", "iN1e_r",  "iN1f_r" ,  "iN1g_r" ,"iN2m_r" ,"iN2k_r" ,  "iN2n_r" ,
                         "iN2l_r" , "iN6b_r" , "iN6c_r" ,"iN6a_r", "iO2a_r" ,  "iO2b_r" ,"iO2c_r" , "iO2d_r", "iO2e_r",
                         "iS2n_r" ,"iS2h_r" , "iS2m_r", "iS2a_r" , "iS2b_r" , "iS2c_r" , "iS2e_r" , "iS2f_r" ,
                         "iS2g_r" , "iS2k_r" , "iS2l_r" , "iS2o_r" , "iS2r_r" , "iS2i_r" , "iS2j_r" ,"iS2d_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide1(mydata_wide, variable)
}


names(mydata_wide)[190:236] <- c("Physical therapy - change1",  "Occupational therapy- change1",  "Speech therapy- change1",
                                 "Psychological therapies- change1 ", "Respiratory therapy- change1", "Funcational rehabilitation- change1",
                                 "Hearing aid used- change1", "Visual appliance used- change1","Social activities- change1",
                                 "Nasogastric feeding (LTCF)- change1",
                                 "Parenteral intake- change1","Mode of nutritional intake- change1",
                                 "Hours exercise- change1","Days went out- change1","Urinary collection device- change1","Ostomy- change1",
                                 "Dental exam in last year- change1","Hearing exam in last 2 years- change1","Eye exam in last year- change1",
                                 "Palliative care- change1","Wound care- change1","Turning programe- change1",
                                 "Scheduled toileting program- change1","Trunk restraint- change1","Chairs prevents rising- change1",
                                 "Full bed rails- change1","Do not resuscitate- change1","Do not intubate- change1","Do not hospitalize- change1",
                                 "No tube feeding- change1","Medication restriction- change1","Walking outdoors- change1",
                                 "Helping others- change1","Trips/shopping- change1", "Cards/games- change1","Computer use- change1",
                                 "Conversing- change1","Dancing- change1","Exercise- change1","Gardening- change1","Reading- change1",
                                 "Spiritual activities- change1","TV- change1","Reminiscing about life- change1","Music- change1",
                                 "Pets- change1","Crafts- change1")


###Step 4

##Use following code for calculate NPIs changes.

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
variables_to_change <- c("iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,  "iN3ia_r", "iN3ja_r", 
                         "iD3b_r",  "iD4b_r", "iF1a_r" ,"iK3_r6" , "iK5_r", "iK3_r","iG6a_r" ,  "iG6b_r",
                         "iH2_r" ,"iH5_r", "iN1e_r",  "iN1f_r" ,  "iN1g_r" ,"iN2m_r" ,"iN2k_r" ,  "iN2n_r" ,
                         "iN2l_r" , "iN6b_r" , "iN6c_r" ,"iN6a_r", "iO2a_r" ,  "iO2b_r" ,"iO2c_r" , "iO2d_r", "iO2e_r",
                         "iS2n_r" ,"iS2h_r" , "iS2m_r", "iS2a_r" , "iS2b_r" , "iS2c_r" , "iS2e_r" , "iS2f_r" ,
                         "iS2g_r" , "iS2k_r" , "iS2l_r" , "iS2o_r" , "iS2r_r" , "iS2i_r" , "iS2j_r" ,"iS2d_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide2(mydata_wide, variable)
}

names(mydata_wide)[237:283] <- c("Physical therapy- change2",  "Occupational therapy- change2",  "Speech therapy- change2",
                                 "Psychological therapies- change2 ", "Respiratory therapy- change2", "Funcational rehabilitation- change2",
                                 "Hearing aid used- change2", "Visual appliance used- change2","Social activities- change2","Nasogastric feeding (LTCF)- change2","Parenteral intake- change2","Mode of nutritional intake- change2",
                                 "Hours exercise- change2","Days went out- change2","Urinary collection device- change2","Ostomy- change2",
                                 "Dental exam in last year- change2","Hearing exam in last 2 years- change2","Eye exam in last year- change2",
                                 "Palliative care- change2","Wound care- change2","Turning programe- change2",
                                 "Scheduled toileting program- change2","Trunk restraint- change2","Chairs prevents rising- change2",
                                 "Full bed rails- change2","Do not resuscitate- change2","Do not intubate- change2","Do not hospitalize- change2",
                                 "No tube feeding- change2","Medication restriction- change2","Walking outdoors- change2",
                                 "Helping others- change2","Trips/shopping- change2", "Cards/games- change2","Computer use- change2",
                                 "Conversing- change2","Dancing- change2","Exercise- change2","Gardening- change2","Reading- change2",
                                 "Spiritual activities- change2","TV- change2","Reminiscing about life- change2","Music- change2",
                                 "Pets- change2","Crafts- change2")


###Step 5

##Use following codes for calculate NPIs changes.

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
variables_to_change <- c("iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,  "iN3ia_r", "iN3ja_r", 
                         "iD3b_r",  "iD4b_r", "iF1a_r" ,"iK3_r6" , "iK5_r", "iK3_r","iG6a_r" ,  "iG6b_r",
                         "iH2_r" ,"iH5_r", "iN1e_r",  "iN1f_r" ,  "iN1g_r" ,"iN2m_r" ,"iN2k_r" ,  "iN2n_r" ,
                         "iN2l_r" , "iN6b_r" , "iN6c_r" ,"iN6a_r", "iO2a_r" ,  "iO2b_r" ,"iO2c_r" , "iO2d_r", "iO2e_r",
                         "iS2n_r" ,"iS2h_r" , "iS2m_r", "iS2a_r" , "iS2b_r" , "iS2c_r" , "iS2e_r" , "iS2f_r" ,
                         "iS2g_r" , "iS2k_r" , "iS2l_r" , "iS2o_r" , "iS2r_r" , "iS2i_r" , "iS2j_r" ,"iS2d_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide3(mydata_wide, variable)
}

names(mydata_wide)[284:330] <- c("Physical therapy- change3",  "Occupational therapy- change3",  "Speech therapy- change3",
                                 "Psychological therapies- change3 ", "Respiratory therapy- change3", "Funcational rehabilitation- change3",
                                 "Hearing aid used- change3", "Visual appliance used- change3","Social activities- change3","Nasogastric feeding (LTCF)- change3","Parenteral intake- change3","Mode of nutritional intake- change3",
                                 "Hours exercise- change3","Days went out- change3","Urinary collection device- change3","Ostomy- change3",
                                 "Dental exam in last year- change3","Hearing exam in last 2 years- change3","Eye exam in last year- change3",
                                 "Palliative care- change3","Wound care- change3","Turning programe- change3",
                                 "Scheduled toileting program- change3","Trunk restraint- change3","Chairs prevents rising- change3",
                                 "Full bed rails- change3","Do not resuscitate- change3","Do not intubate- change3","Do not hospitalize- change3",
                                 "No tube feeding- change3","Medication restriction- change3","Walking outdoors- change3",
                                 "Helping others- change3","Trips/shopping- change3", "Cards/games- change3","Computer use- change3",
                                 "Conversing- change3","Dancing- change3","Exercise- change3","Gardening- change3","Reading- change3",
                                 "Spiritual activities- change3","TV- change3","Reminiscing about life- change3","Music- change3",
                                 "Pets- change3","Crafts- change3")


### Step 6 Create tables 

changeLTCF_1 <- CreateTableOne(vars = c("Physical therapy - change1",  "Occupational therapy- change1",  "Speech therapy- change1",
                                        "Psychological therapies- change1 ", "Respiratory therapy- change1", "Funcational rehabilitation- change1",
                                        "Hearing aid used- change1", "Visual appliance used- change1","Social activities- change1","Nasogastric feeding (LTCF)- change1","Parenteral intake- change1","Mode of nutritional intake- change1",
                                        "Hours exercise- change1","Days went out- change1","Urinary collection device- change1","Ostomy- change1",
                                        "Dental exam in last year- change1","Hearing exam in last 2 years- change1","Eye exam in last year- change1",
                                        "Palliative care- change1","Wound care- change1","Turning programe- change1",
                                        "Scheduled toileting program- change1","Trunk restraint- change1","Chairs prevents rising- change1",
                                        "Full bed rails- change1","Do not resuscitate- change1","Do not intubate- change1","Do not hospitalize- change1",
                                        "No tube feeding- change1","Medication restriction- change1","Walking outdoors- change1",
                                        "Helping others- change1","Trips/shopping- change1", "Cards/games- change1","Computer use- change1",
                                        "Conversing- change1","Dancing- change1","Exercise- change1","Gardening- change1","Reading- change1",
                                        "Spiritual activities- change1","TV- change1","Reminiscing about life- change1","Music- change1",
                                        "Pets- change1","Crafts- change1"),data = mydata_wide, factorVars = c("Physical therapy - change1",  "Occupational therapy- change1",  "Speech therapy- change1",
                                                                                                              "Psychological therapies- change1 ", "Respiratory therapy- change1", "Funcational rehabilitation- change1",
                                                                                                              "Hearing aid used- change1", "Visual appliance used- change1","Social activities- change1","Nasogastric feeding (LTCF)- change1","Parenteral intake- change1","Mode of nutritional intake- change1",
                                                                                                              "Hours exercise- change1","Days went out- change1","Urinary collection device- change1","Ostomy- change1",
                                                                                                              "Dental exam in last year- change1","Hearing exam in last 2 years- change1","Eye exam in last year- change1",
                                                                                                              "Palliative care- change1","Wound care- change1","Turning programe- change1",
                                                                                                              "Scheduled toileting program- change1","Trunk restraint- change1","Chairs prevents rising- change1",
                                                                                                              "Full bed rails- change1","Do not resuscitate- change1","Do not intubate- change1","Do not hospitalize- change1",
                                                                                                              "No tube feeding- change1","Medication restriction- change1","Walking outdoors- change1",
                                                                                                              "Helping others- change1","Trips/shopping- change1", "Cards/games- change1","Computer use- change1",
                                                                                                              "Conversing- change1","Dancing- change1","Exercise- change1","Gardening- change1","Reading- change1",
                                                                                                              "Spiritual activities- change1","TV- change1","Reminiscing about life- change1","Music- change1",
                                                                                                              "Pets- change1","Crafts- change1"))
changeLTCF_1 <- print(changeLTCF_1, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop 
# !Note: Please change to your own path
write.csv(changeLTCF_1,file="C:/Users/User/Desktop/Results_LTCF/Change_LTCF_1.csv")


changeLTCF_2 <- CreateTableOne(vars = c("Physical therapy- change2",  "Occupational therapy- change2",  "Speech therapy- change2",
                                        "Psychological therapies- change2 ", "Respiratory therapy- change2", "Funcational rehabilitation- change2",
                                        "Hearing aid used- change2", "Visual appliance used- change2","Social activities- change2","Nasogastric feeding (LTCF)- change2","Parenteral intake- change2","Mode of nutritional intake- change2",
                                        "Hours exercise- change2","Days went out- change2","Urinary collection device- change2","Ostomy- change2",
                                        "Dental exam in last year- change2","Hearing exam in last 2 years- change2","Eye exam in last year- change2",
                                        "Palliative care- change2","Wound care- change2","Turning programe- change2",
                                        "Scheduled toileting program- change2","Trunk restraint- change2","Chairs prevents rising- change2",
                                        "Full bed rails- change2","Do not resuscitate- change2","Do not intubate- change2","Do not hospitalize- change2",
                                        "No tube feeding- change2","Medication restriction- change2","Walking outdoors- change2",
                                        "Helping others- change2","Trips/shopping- change2", "Cards/games- change2","Computer use- change2",
                                        "Conversing- change2","Dancing- change2","Exercise- change2","Gardening- change2","Reading- change2",
                                        "Spiritual activities- change2","TV- change2","Reminiscing about life- change2","Music- change2",
                                        "Pets- change2","Crafts- change2"),data = mydata_wide, factorVars = c("Physical therapy- change2",  "Occupational therapy- change2",  "Speech therapy- change2",
                                                                                                              "Psychological therapies- change2 ", "Respiratory therapy- change2", "Funcational rehabilitation- change2",
                                                                                                              "Hearing aid used- change2", "Visual appliance used- change2","Social activities- change2","Nasogastric feeding (LTCF)- change2","Parenteral intake- change2","Mode of nutritional intake- change2",
                                                                                                              "Hours exercise- change2","Days went out- change2","Urinary collection device- change2","Ostomy- change2",
                                                                                                              "Dental exam in last year- change2","Hearing exam in last 2 years- change2","Eye exam in last year- change2",
                                                                                                              "Palliative care- change2","Wound care- change2","Turning programe- change2",
                                                                                                              "Scheduled toileting program- change2","Trunk restraint- change2","Chairs prevents rising- change2",
                                                                                                              "Full bed rails- change2","Do not resuscitate- change2","Do not intubate- change2","Do not hospitalize- change2",
                                                                                                              "No tube feeding- change2","Medication restriction- change2","Walking outdoors- change2",
                                                                                                              "Helping others- change2","Trips/shopping- change2", "Cards/games- change2","Computer use- change2",
                                                                                                              "Conversing- change2","Dancing- change2","Exercise- change2","Gardening- change2","Reading- change2",
                                                                                                              "Spiritual activities- change2","TV- change2","Reminiscing about life- change2","Music- change2",
                                                                                                              "Pets- change2","Crafts- change2"))
changeLTCF_2 <- print(changeLTCF_2, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeLTCF_2,file="C:/Users/User/Desktop/Results_LTCF/Change_LTCF_2.csv")


changeLTCF_3 <- CreateTableOne(vars = c("Physical therapy- change3",  "Occupational therapy- change3",  "Speech therapy- change3",
                                        "Psychological therapies- change3 ", "Respiratory therapy- change3", "Funcational rehabilitation- change3",
                                        "Hearing aid used- change3", "Visual appliance used- change3","Social activities- change3","Nasogastric feeding (LTCF)- change3","Parenteral intake- change3","Mode of nutritional intake- change3",
                                        "Hours exercise- change3","Days went out- change3","Urinary collection device- change3","Ostomy- change3",
                                        "Dental exam in last year- change3","Hearing exam in last 2 years- change3","Eye exam in last year- change3",
                                        "Palliative care- change3","Wound care- change3","Turning programe- change3",
                                        "Scheduled toileting program- change3","Trunk restraint- change3","Chairs prevents rising- change3",
                                        "Full bed rails- change3","Do not resuscitate- change3","Do not intubate- change3","Do not hospitalize- change3",
                                        "No tube feeding- change3","Medication restriction- change3","Walking outdoors- change3",
                                        "Helping others- change3","Trips/shopping- change3", "Cards/games- change3","Computer use- change3",
                                        "Conversing- change3","Dancing- change3","Exercise- change3","Gardening- change3","Reading- change3",
                                        "Spiritual activities- change3","TV- change3","Reminiscing about life- change3","Music- change3",
                                        "Pets- change3","Crafts- change3"),data = mydata_wide, factorVars = c("Physical therapy- change3",  "Occupational therapy- change3",  "Speech therapy- change3",
                                                                                                              "Psychological therapies- change3 ", "Respiratory therapy- change3", "Funcational rehabilitation- change3",
                                                                                                              "Hearing aid used- change3", "Visual appliance used- change3","Social activities- change3","Nasogastric feeding (LTCF)- change3","Parenteral intake- change3","Mode of nutritional intake- change3",
                                                                                                              "Hours exercise- change3","Days went out- change3","Urinary collection device- change3","Ostomy- change3",
                                                                                                              "Dental exam in last year- change3","Hearing exam in last 2 years- change3","Eye exam in last year- change3",
                                                                                                              "Palliative care- change3","Wound care- change3","Turning programe- change3",
                                                                                                              "Scheduled toileting program- change3","Trunk restraint- change3","Chairs prevents rising- change3",
                                                                                                              "Full bed rails- change3","Do not resuscitate- change3","Do not intubate- change3","Do not hospitalize- change3",
                                                                                                              "No tube feeding- change3","Medication restriction- change3","Walking outdoors- change3",
                                                                                                              "Helping others- change3","Trips/shopping- change3", "Cards/games- change3","Computer use- change3",
                                                                                                              "Conversing- change3","Dancing- change3","Exercise- change3","Gardening- change3","Reading- change3",
                                                                                                              "Spiritual activities- change3","TV- change3","Reminiscing about life- change3","Music- change3",
                                                                                                              "Pets- change3","Crafts- change3"))
changeLTCF_3 <- print(changeLTCF_3, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeLTCF_3,file="C:/Users/User/Desktop/Results_LTCF/Change_LTCF_3.csv")





######################################################## MDS v2 #######################################################

###!Note:
##There are differences between countries (Finland, Canada and the USA) in terms of variable names, as well as their presence in the database 
##The changes for Finland, Canada and USA are noted in the code and explained

#### The analysis requires the following variables;
# Please double check if the variable coding is consistent and modify if necessary
# ID: Identifier
# Age: age                 # Note: Modify when necessary
# AA8: Reasons for assessment: 1: Admission assessment, 2:Annual assessment;  3: Significant change in status assessment;
#                       4: Significant correction of prior full assessment; 5: Quarterly review assessment;
#                       10: Significant correction of prior quarterly assessment; 6:Discharged - return not anticipated;
#                       7: Discharged-return anticipated; 8: Discharged prior to completing initial assessment;
#                       9: Reentry; 0: None of above;# Note: Modify when necessary
# Assess_type:   1: first assessment;
#                2: second assessment;
#                3: third assessment;
#                4: fourth assessment;
# C2b: Hearing aid: 0: no; 1: yes;
# D3:  Visual appliance used: 0: no; 1: yes;
# H3c: Condom catheter: 0: no; 1: yes;
# H3d: Indwelling catheter: 0: no; 1: yes;
# H3e: (Note: only in Finland) : Intermittent catheter:  0: no; 1: yes;
# H3i: Ostomy:  0: no; 1: yes;
# K5a: Parenteral/IV: 0: no; 1: yes;
# K5b: Feeding tube:  0: no; 1: yes;
# M5e: (Note: not in Canada): Ulcer care:0: no; 1: yes;
# M5f: (Note: not in Canada): Surgical wound care:0: no; 1: yes;
# M5g: Application of dressing other than to feet:0: no; 1: yes;
# M5h: Application of ointments or medications:0: no; 1: yes;
# M6f: (Note: not in Canada): Application of dressing: 0: no; 1: yes;
# H3a: Any scheduled toileting program: 0: no; 1: yes;
# P1ao: Hospice care: 0: no; 1: yes;
# M5c:  Turning or repositioning program:0: no; 1: yes;
# P1bcA: Physical therapy: days of care (at last 15 minutes) in last 7 days;
# P1bbA: Occupational therapy: days of care (at last 15 minutes) in last 7 days;
# P1baA: Speech therapy: days of care (at last 15 minutes) in last 7 days;
# P1beA: Psychological therapies: days of care (at last 15 minutes) in last 7 days;
# P1bdA: Respiratory therapy: days of care (at last 15 minutes) in last 7 days;
# P4a: Full bed rails on all open sides of bed: 0: not used; 1: used less than daily;2 used daily
# P4c: Trunk restraint: 0: not used; 1: used less than daily;2 used daily
# P4e: Chairs prevents rising: 0: not used; 1: used less than daily;2 used daily
# A10a: Living will:0: no; 1: yes;
# A10b (Note: Finland: A8b; Canada: A12a): Do not resuscitate:0: no; 1: yes;
# A10c (Note: Finland: A8c; Canada: A12c): Do not hospitalize:0: no; 1: yes;
# A10f (Note: Finland: A8f; not in Canada): Feeding restrictions:0: no; 1: yes;
# A10g (Note: Finland: A8g; not in Canada): Medication restrictions:0: no; 1: yes;
# A10h (Note: not in Finland and Canada): Other treatment restrictions:0: no; 1: yes;
# N4a: Cards/games:0: no; 1: yes;
# N4k: Talking or conversing:0: no; 1: yes;
# N4b: Crafts or arts:0: no; 1: yes;
# N4c: Exercise or sports:0: no; 1: yes;
# N4j: Gardening or plants:0: no; 1: yes;
# N4l: Helping others:0: no; 1: yes;
# N4d: Music: 0: no; 1: yes;
# N4e: Reading, writing:0: no; 1: yes;
# N4f: Spiritual or religious activities:0: no; 1: yes;
# N4g: Trips/shopping:0: no; 1: yes;
# N4h: Walk/wheeling outdoors:0: no; 1: yes;
# N4i: Watching TV:0: no; 1: yes;
# G5a: Cane, walker or crutch:0: no; 1: yes;
# G5b: Wheeled self:0: no; 1: yes;


###Step1 Install packages and prepare your own data

##Install packages

install.packages(c("haven", "tidyr", "dplyr", "reshape2", "tableone"))
library(haven); library(tidyr); library(dplyr); library(reshape2); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format
data <- read_sav('C:/Users/User/Desktop/icare2023/database_example.sav')


## Select relevant variables for analysis
#######################################################################################################################
# !Note: Finland:
#         add: "H3e"; 
#         remove: "A10h";
#         change: "A10b" --> "A8b"; "A10c" --> "A8c"; "A10f" --> "A8f";
#                 "A10g" --> "A8g";
# !Note: Canada:
#         remove: "M5e","M5f","M6f", "A10h"; "A10f"; "A10g";
#         change: "A10b" --> "A12a"; "A10c" --> "A12c";
#######################################################################################################################

mydata <- data [ , c("ID", "age", "AA8", "Assess_type","C2b","D3","H3c", "H3d", "H3i",
                     "K5a", "K5b", "M5e", "M5f", "M5g", "M5h", "M6f", "H3a", "P1ao",
                     "M5c", "P1bcA", "P1bbA" , "P1baA" , "P1beA" ,  "P1bdA",
                     "P4a","P4c", "P4e","A10a", "A10b", "A10c", "A10f", "A10g",
                     "N4a", "N4k","N4b", "N4c", "N4j","N4l","N4d", "N4e","N4f", "N4g",
                     "N4h", "N4i", "G5a", "G5b")] 
                     
                     
##Recode the variables for selected nonpharmocologic therapies (NPIs) into dichotomous variables

#Hearing aid used
mydata$iD3b_r <- "1"
mydata$iD3b_r[mydata$C2b==1] <- "2"
mydata$iD3b_r[is.na(mydata$C2b)] <- NA

#Visual appliance used
mydata$iD4b_r <- "1"
mydata$iD4b_r[mydata$D3==1] <- "2"
mydata$iD4b_r[is.na(mydata$D3)] <- NA

#Urinary collection device
mydata$iH3_r <- "1"
mydata$iH3_r[mydata$H3c==1 | mydata$H3d==1] <- "2"
mydata$iH3_r[is.na(mydata$H3c)] <- NA
mydata$iH3_r[is.na(mydata$H3d)] <- NA

#######################################################################################################################
#Urinary collection device !Note: only for Finland
#mydata$iH3_r <- "1"
#mydata$iH3_r[mydata$H3c==1 | mydata$H3d==1 | mydata$H3e==1] <- "2"
#mydata$iH3_r[is.na(mydata$H3c)] <- NA
#mydata$iH3_r[is.na(mydata$H3d)] <- NA
#mydata$iH3_r[is.na(mydata$H3e)] <- NA
#######################################################################################################################

#Indwelling catheter
mydata$iH2_r <- "1"
mydata$iH2_r[mydata$H3d == 1] <- "2"
mydata$iH2_r[is.na(mydata$H3d)] <- NA

#Ostomy
mydata$iH5_r <- "1"
mydata$iH5_r[mydata$H3i == 1] <- "2"
mydata$iH5_r[is.na(mydata$H3i)] <- NA

#Parenteral intake
mydata$iK5_r <- "1"
mydata$iK5_r[mydata$K5a == 1] <- "2"
mydata$iK5_r[is.na(mydata$K5a)] <- NA

#Nasogastric feeding (LTCF)
mydata$iK3_r6 <- "1"
mydata$iK3_r6[mydata$K5b == 1] <- "2" 
mydata$iK3_r6[is.na(mydata$K5b)] <- NA

#Wound care
mydata$iN2k_r <- "1"
mydata$iN2k_r[mydata$M5e==1 | mydata$M5f==1 | mydata$M5g==1 | mydata$M5h==1
              | mydata$M6f==1] <- "2"
mydata$iN2k_r[is.na(mydata$M5e)] <- NA
mydata$iN2k_r[is.na(mydata$M5f)] <- NA
mydata$iN2k_r[is.na(mydata$M5g)] <- NA
mydata$iN2k_r[is.na(mydata$M5h)] <- NA
mydata$iN2k_r[is.na(mydata$M6f)] <- NA

#######################################################################################################################
#Wound care !Note: only for Canada
#mydata$iN2k_r <- "1"
#mydata$iN2k_r[mydata$M5g==1 | mydata$M5h==1] <- "2"
#mydata$iN2k_r[is.na(mydata$M5g)] <- NA
#mydata$iN2k_r[is.na(mydata$M5h)] <- NA
#######################################################################################################################

#Scheduled toileting program
mydata$iN2l_r <- "1"
mydata$iN2l_r[mydata$H3a == 1] <- "2"
mydata$iN2l_r[is.na(mydata$H3a)] <- NA

#Hospice care
mydata$iN2m_r <- "1"
mydata$iN2m_r[mydata$P1ao == 1] "2"
mydata$iN2m_r[is.na(mydata$P1ao)] <- NA

#Turning program
mydata$iN2n_r <- "1"
mydata$iN2n_r[mydata$M5c == 1] <- "2"
mydata$iN2n_r[is.na(mydata$M5c)] <- NA

#Physical therapy
mydata$iN3ea_r <- "1"
mydata$iN3ea_r[mydata$P1bcA>0 & mydata$P1bcA<=7] <- "2"
mydata$iN3ea_r[is.na(mydata$P1bcA)] <- NA
mydata$iN3ea_r[mydata$P1bcA>7] <- NA

#Occupational therapy
mydata$iN3fa_r <- "1"
mydata$iN3fa_r[mydata$P1bbA>0 & mydata$P1bbA<=7] <- "2"
mydata$iN3fa_r[is.na(mydata$P1bbA)] <- NA
mydata$iN3fa_r[mydata$P1bbA>7] <- NA

#Speech therapy
mydata$iN3ga_r <- "1"
mydata$iN3ga_r[mydata$P1baA>0 & mydata$P1baA<=7] <- "2"
mydata$iN3ga_r[is.na(mydata$P1baA)] <- NA
mydata$iN3ga_r[mydata$P1baA>7] <- NA

#Psychological therapies
mydata$iN3ha_r <- "1"
mydata$iN3ha_r[mydata$P1beA>0 & mydata$P1beA<=7] <- "2"
mydata$iN3ha_r[is.na(mydata$P1beA)] <- NA
mydata$iN3ha_r[mydata$P1beA>7] <- NA

#Respiratory therapy
mydata$iN3ia_r <- "1"
mydata$iN3ia_r[mydata$P1bdA>0 & mydata$P1bdA<=7] <- "2"
mydata$iN3ia_r[is.na(mydata$P1bdA)] <- NA
mydata$iN3ia_r[mydata$P1bdA>7] <- NA

#Full bed rails
mydata$iN6a_r <- "1"
mydata$iN6a_r[mydata$P4a==1 | mydata$P4a==2 ] <- "2"
mydata$iN6a_r[is.na(mydata$P4a)] <- NA

#Trunk restraint
mydata$iN6b_r <- "1"
mydata$iN6b_r[mydata$P4c==1 | mydata$P4c==2] <- "2"
mydata$iN6b_r[is.na(mydata$P4c)] <- NA

#Chairs prevents rising
mydata$iN6c_r <- "1"
mydata$iN6c_r[mydata$P4e==1 | mydata$P4e==2] <- "2"
mydata$iN6c_r[is.na(mydata$P4e)] <- NA

#Living will
mydata$A10a_r <- "1"
mydata$A10a_r[mydata$A10a==1] <- "2" 
mydata$A10a_r[is.na(mydata$A10a)] <- NA

#Do not resuscitate
mydata$A10b_r <- "1"
mydata$A10b_r[mydata$A10b==1] <- "2"
mydata$A10b_r[is.na(mydata$A10b)] <- NA

#######################################################################################################################
#Do not resuscitate !Note: only for Finland
#mydata$A10b_r <- "1"
#mydata$A10b_r[mydata$A8b==1] <- "2"
#mydata$A10b_r[is.na(mydata$A8b)] <- NA

#Do not resuscitate !Note: only for Canada
#mydata$A10b_r <- "1"
#mydata$A10b_r[mydata$A12a==1] <- "2"
#mydata$A10b_r[is.na(mydata$A12a)] <- NA
###################################################################################################

###################################################################################################
#Do not intubate !Note: not in Canada and Finland
mydata$A10h_r <- "1"
mydata$A10h_r[mydata$A10h==1] <- "2"
mydata$A10h_r[is.na(mydata$A10h)] <- NA
###################################################################################################

#Do not hospitalize
mydata$A10c_r <- "1"
mydata$A10c_r[mydata$A10c==1] <- "2"
mydata$A10c_r[is.na(mydata$A10c)] <- NA

###################################################################################################
#Do not hospitalize !Note: only for Finland
#mydata$A10c_r <- "1"
#mydata$A10c_r[mydata$A8c==1] <- "2"
#mydata$A10c_r[is.na(mydata$A8c)] <- NA

#Do not hospitalize !Note: only for Canada
#mydata$A10c_r <- "1"
#mydata$A10c_r[mydata$A12c==1] <- "2"
#mydata$A10c_r[is.na(mydata$A12c)] <- NA
###################################################################################################

#No tube feeding !Note: not in Canada 
mydata$A10f_r <- "1"
mydata$A10f_r[mydata$A10f==1] <- "2"
mydata$A10f_r[is.na(mydata$A10f)] <- NA

###################################################################################################
#Not tube feeding !Note: only for Finland
#mydata$A10f_r <- "1"
#mydata$A10f_r[mydata$A8f==1] <- "2"
#mydata$A10f_r[is.na(mydata$A8f)] <- NA
###################################################################################################

#Medication restrictions !Note: not in Canada
mydata$A10g_r <- "1"
mydata$A10g_r[mydata$A10g==1] <- "2"
mydata$A10g_r[is.na(mydata$A10g)] <- NA

###################################################################################################
#Medication restrictions !Note: only for Finland
#mydata$A10g_r <- "1"
#mydata$A10g_r[mydata$A8g==1] <- "2"
#mydata$A10g_r[is.na(mydata$A8g)] <- NA
#######################################################################################################################

#Cards/games
mydata$iS2a_r <- "1"
mydata$iS2a_r[mydata$N4a==1] <- "2" 
mydata$iS2a_r[is.na(mydata$N4a)] <- NA

#Conversing
mydata$iS2c_r <- "1"
mydata$iS2c_r[mydata$N4k==1] <- "2" 
mydata$iS2c_r[is.na(mydata$N4k)] <- NA

#Crafts
mydata$iS2d_r <- "1"
mydata$iS2d_r[mydata$N4b==1] <- "2" 
mydata$iS2d_r[is.na(mydata$N4b)] <- NA

#Exercise
mydata$iS2f_r <- "1"
mydata$iS2f_r[mydata$N4c==1] <- "2" 
mydata$iS2f_r[is.na(mydata$N4c)] <- NA

#Gardening
mydata$iS2g_r <- "1"
mydata$iS2g_r[mydata$N4j==1] <- "2" 
mydata$iS2g_r[is.na(mydata$N4j)] <- NA

#Helping others
mydata$iS2h_r <- "1"
mydata$iS2h_r[mydata$N4l==1] <- "2" 
mydata$iS2h_r[is.na(mydata$N4l)] <- NA

#Music
mydata$iS2i_r <- "1"
mydata$iS2i_r[mydata$N4d==1] <- "2" 
mydata$iS2i_r[is.na(mydata$N4d)] <- NA

#Reading
mydata$iS2k_r <- "1"
mydata$iS2k_r[mydata$N4e==1] <- "2" 
mydata$iS2k_r[is.na(mydata$N4e)] <- NA

#Spiritual activities
mydata$iS2l_r <- "1"
mydata$iS2l_r[mydata$N4f==1] <- "2" 
mydata$iS2l_r[is.na(mydata$N4f)] <- NA

#Trips/shopping
mydata$iS2m_r <- "1"
mydata$iS2m_r[mydata$N4g==1] <- "2" 
mydata$iS2m_r[is.na(mydata$N4g)] <- NA

#Walking outdoors
mydata$iS2n_r <- "1"
mydata$iS2n_r[mydata$N4h==1] <- "2" 
mydata$iS2n_r[is.na(mydata$N4h)] <- NA

#TV
mydata$iS2o_r<- "1"
mydata$iS2o_r[mydata$N4i==1] <- "2" 
mydata$iS2o_r[is.na(mydata$N4i)] <- NA

#Cane, walker or crutch
mydata$G5a_r <- "1"
mydata$G5a_r[mydata$G5a==1] <- "2" 
mydata$G5a_r[is.na(mydata$G5a)] <- NA

#Wheeled self
mydata$G5b_r <- "1"
mydata$G5b_r[mydata$G5b==1] <- "2" 
mydata$G5b_r[is.na(mydata$G5b)] <- NA


## Apply inclusion criteria 

# Inclusion criteria 1. Exclude discharge or return assessment
mydata$iA8_r[mydata$AA8==1 | mydata$AA8==2 | mydata$AA8==3 | mydata$AA8==4
             | mydata$AA8==5 | mydata$AA8==10 | mydata$AA8==0] <- "1"
mydata$iA8_r[mydata$AA8==6 | mydata$AA8==7 | mydata$AA8==8 | mydata$AA8==9 ] <- "2"
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
#!Note: Finland: remove: "A10h_r";
#!Note: Canada: remove: "A10h_r"; "A10f_r"; "A10g_r";
#######################################################################################################################

mydata_wide <- pivot_wider(data=mydata,
                           names_from = "Assess_type",
                           id_cols = "ID",
                           values_from =c("iD3b_r",  "iD4b_r","iH3_r", "iH2_r", "iH5_r","iK5_r", "iK3_r6",
                              "iN2k_r","iN2l_r", "iN2m_r","iN2n_r","iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,
                              "iN3ia_r",  "iN6a_r", "iN6b_r", "iN6c_r", "A10a_r", "A10b_r", "A10h_r",
                              "A10c_r", "A10f_r","A10g_r","iS2a_r", "iS2c_r","iS2d_r","iS2f_r", "iS2g_r",
                             "iS2h_r", "iS2i_r", "iS2k_r", "iS2l_r", "iS2m_r", "iS2n_r","iS2o_r",   
                              "G5a_r", "G5b_r"))
      
###Step 3

##Use following codes for calculate NPIs changes.

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
#!Note: Finland: remove: "A10h_r";
#!Note: Canada: remove: "A10h_r"; "A10f_r"; "A10g_r";
#######################################################################################################################

variables_to_change <- c("iD3b_r",  "iD4b_r","iH3_r", "iH2_r", "iH5_r","iK5_r", "iK3_r6",
                         "iN2k_r","iN2l_r", "iN2m_r","iN2n_r","iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,
                         "iN3ia_r",  "iN6a_r", "iN6b_r", "iN6c_r", "A10a_r", "A10b_r", "A10h_r",
                         "A10c_r", "A10f_r","A10g_r","iS2a_r", "iS2c_r","iS2d_r","iS2f_r", "iS2g_r",
                         "iS2h_r", "iS2i_r", "iS2k_r", "iS2l_r", "iS2m_r", "iS2n_r","iS2o_r",   
                         "G5a_r", "G5b_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide1(mydata_wide, variable)
}

#######################################################################################################################
#!Note: Finland remove:"Do not intubate- change1" and change to [154:191]
#!Note: Canada remove:"Do not intubate- change1", "No tube feeding- change1",
#                     "Medication restrictions-change1" and change to [146:181]
#######################################################################################################################

names(mydata_wide)[158:196] <- c("Hearing aid used- change1", "Visual appliance used- change1","Urinary collection device- change1",
                                 "Indwelling catheter- change1", "Ostomy- change1","Parenteral intake- change1","Nasogastric feeding (LTCF)- change1",
                                 "Wound care- change1","Scheduled toileting program- change1","Hospice care- change1",
                                 "Turning programe- change1","Physical therapy- change1", "Occupational therapy- change1",
                                  "Speech therapy- change1","Psychological therapies- change1 ", "Respiratory therapy- change1",
                                 "Full bed rails- change1", "Trunk restraint- change1","Chairs prevents rising- change1",
                                  "Living will- change1","Do not resuscitate- change1", "Do not intubate- change1", 
                                 "Do not hospitalize- change1", "No tube feeding- change1", "Medication restrictions- change1",
                                 "Cards/games- change1", "Conversing- change1", "Crafts- change1", "Exercise- change1",
                                  "Gardening- change1","Helping others- change1", "Music- change1","Reading- change1",
                                  "Spiritual activities- change1", "Trips/shopping- change1", "Walking outdoors- change1",
                                 "TV- change1","Cane, walker or crutch- change1","Wheeled self- change1")


###Step 4

##Use following codes for calculate NPIs changes.

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
#!Note: Finland: remove: "A10h_r";
#!Note: Canada: remove: "A10h_r"; "A10f_r"; "A10g_r";
#######################################################################################################################

variables_to_change <- c("iD3b_r",  "iD4b_r","iH3_r", "iH2_r", "iH5_r","iK5_r", "iK3_r6",
                         "iN2k_r","iN2l_r", "iN2m_r","iN2n_r","iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,
                         "iN3ia_r",  "iN6a_r", "iN6b_r", "iN6c_r", "A10a_r", "A10b_r", "A10h_r",
                         "A10c_r", "A10f_r","A10g_r","iS2a_r", "iS2c_r","iS2d_r","iS2f_r", "iS2g_r",
                         "iS2h_r", "iS2i_r", "iS2k_r", "iS2l_r", "iS2m_r", "iS2n_r","iS2o_r",   
                         "G5a_r", "G5b_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide2(mydata_wide, variable)
}


#######################################################################################################################
#!Note: Finland remove:"Do not intubate- change2" and change to [192:229]
#!Note: Canada remove:"Do not intubate- change2", "No tube feeding- change2",
#                     "Medication restrictions- change2" and change to [182:217]
#######################################################################################################################

names(mydata_wide)[197:235] <- c("Hearing aid used- change2", "Visual appliance used- change2","Urinary collection device- change2",
                                 "Indwelling catheter- change2", "Ostomy- change2","Parenteral intake- change2","Nasogastric feeding (LTCF)- change2",
                                 "Wound care- change2","Scheduled toileting program- change2","Hospice care- change2",
                                 "Turning programe- change2","Physical therapy- change2", "Occupational therapy- change2",
                                 "Speech therapy- change2","Psychological therapies- change2 ", "Respiratory therapy- change2",
                                 "Full bed rails- change2", "Trunk restraint- change2","Chairs prevents rising- change2",
                                 "Living will- change2","Do not resuscitate- change2", "Do not intubate- change2", 
                                 "Do not hospitalize- change2", "No tube feeding- change2", "Medication restrictions- change2",
                                 "Cards/games- change2", "Conversing- change2", "Crafts- change2", "Exercise- change2",
                                 "Gardening- change2","Helping others- change2", "Music- change2","Reading- change2",
                                 "Spiritual activities- change2", "Trips/shopping- change2", "Walking outdoors- change2",
                                 "TV- change2","Cane, walker or crutch- change2","Wheeled self- change2")


###Step 5

##Use following codes for calculate NPIs changes.

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
#!Note: Finland: remove: "A10h_r";
#!Note: Canada: remove: "A10h_r"; "A10f_r"; "A10g_r";
#######################################################################################################################

variables_to_change <- c("iD3b_r",  "iD4b_r","iH3_r", "iH2_r", "iH5_r","iK5_r", "iK3_r6",
                         "iN2k_r","iN2l_r", "iN2m_r","iN2n_r","iN3ea_r", "iN3fa_r", "iN3ga_r" ,"iN3ha_r" ,
                         "iN3ia_r",  "iN6a_r", "iN6b_r", "iN6c_r", "A10a_r", "A10b_r", "A10h_r",
                         "A10c_r", "A10f_r","A10g_r","iS2a_r", "iS2c_r","iS2d_r","iS2f_r", "iS2g_r",
                         "iS2h_r", "iS2i_r", "iS2k_r", "iS2l_r", "iS2m_r", "iS2n_r","iS2o_r",   
                         "G5a_r", "G5b_r")

for (variable in variables_to_change) {
  mydata_wide <- create_change_column_wide3(mydata_wide, variable)
}


#######################################################################################################################
#!Note: Finland remove:"Do not intubate- change3" and change to [230:267]
#!Note: Canada remove:"Do not intubate- change3", "No tube feeding- change3",
#                     "Medication restrictions- change3" and change to [218:253]
#######################################################################################################################
names(mydata_wide)[236:274] <- c("Hearing aid used- change3", "Visual appliance used- change3","Urinary collection device- change3",
                                 "Indwelling catheter- change3", "Ostomy- change3","Parenteral intake- change3","Nasogastric feeding (LTCF)- change3",
                                 "Wound care- change3","Scheduled toileting program- change3","Hospice care- change3",
                                 "Turning programe- change3","Physical therapy- change3", "Occupational therapy- change3",
                                 "Speech therapy- change3","Psychological therapies- change3 ", "Respiratory therapy- change3",
                                 "Full bed rails- change3", "Trunk restraint- change3","Chairs prevents rising- change3",
                                 "Living will- change3","Do not resuscitate- change3", "Do not intubate- change3", 
                                 "Do not hospitalize- change3", "No tube feeding- change3", "Medication restrictions- change3",
                                 "Cards/games- change3", "Conversing- change3", "Crafts- change3", "Exercise- change3",
                                 "Gardening- change3","Helping others- change3", "Music- change3","Reading- change3",
                                 "Spiritual activities- change3", "Trips/shopping- change3", "Walking outdoors- change3",
                                 "TV- change3","Cane, walker or crutch- change3","Wheeled self- change3")


### Step 6 Create tables 

#######################################################################################################################
#!Note: Finland remove:"Do not intubate- change1" 
#!Note: Canada remove:"Do not intubate- change1", "No tube feeding- change1","Medication restrictions- change1" 
#######################################################################################################################

changeLTCF_1 <- CreateTableOne(vars = c("Hearing aid used- change1", "Visual appliance used- change1","Urinary collection device- change1",
                                        "Indwelling catheter- change1", "Ostomy- change1","Parenteral intake- change1","Nasogastric feeding (LTCF)- change1",
                                        "Wound care- change1","Scheduled toileting program- change1","Hospice care- change1",
                                        "Turning programe- change1","Physical therapy- change1", "Occupational therapy- change1",
                                        "Speech therapy- change1","Psychological therapies- change1 ", "Respiratory therapy- change1",
                                        "Full bed rails- change1", "Trunk restraint- change1","Chairs prevents rising- change1",
                                        "Living will- change1","Do not resuscitate- change1", "Do not intubate- change1", 
                                        "Do not hospitalize- change1", "No tube feeding- change1", "Medication restrictions- change1",
                                        "Cards/games- change1", "Conversing- change1", "Crafts- change1", "Exercise- change1",
                                        "Gardening- change1","Helping others- change1", "Music- change1","Reading- change1",
                                        "Spiritual activities- change1", "Trips/shopping- change1", "Walking outdoors- change1",
                                        "TV- change1","Cane, walker or crutch- change1","Wheeled self- change1" ),data = mydata_wide, factorVars = c("Hearing aid used- change1", "Visual appliance used- change1","Urinary collection device- change1",
                                                                                                                                                   "Indwelling catheter- change1", "Ostomy- change1","Parenteral intake- change1","Nasogastric feeding (LTCF)- change1",
                                                                                                                                                   "Wound care- change1","Scheduled toileting program- change1","Hospice care- change1",
                                                                                                                                                   "Turning programe- change1","Physical therapy- change1", "Occupational therapy- change1",
                                                                                                                                                   "Speech therapy- change1","Psychological therapies- change1 ", "Respiratory therapy- change1",
                                                                                                                                                   "Full bed rails- change1", "Trunk restraint- change1","Chairs prevents rising- change1",
                                                                                                                                                   "Living will- change1","Do not resuscitate- change1", "Do not intubate- change1", 
                                                                                                                                                   "Do not hospitalize- change1", "No tube feeding- change1", "Medication restrictions- change1",
                                                                                                                                                   "Cards/games- change1", "Conversing- change1", "Crafts- change1", "Exercise- change1",
                                                                                                                                                   "Gardening- change1","Helping others- change1", "Music- change1","Reading- change1",
                                                                                                                                                   "Spiritual activities- change1", "Trips/shopping- change1", "Walking outdoors- change1",
                                                                                                                                                   "TV- change1","Cane, walker or crutch- change1","Wheeled self- change1" ))
changeLTCF_1 <- print(changeLTCF_1, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop 
# !Note: Please change to your own path
write.csv(changeLTCF_1,file="C:/Users/User/Desktop/Results_LTCF/Change_LTCF_1.csv")

#######################################################################################################################
#!Note: Finland: remove:"Do not intubate- change2" 
#!Note: Canada: remove:"Do not intubate- change2", "No tube feeding- change2","Medication restrictions- change2" 
#######################################################################################################################

changeLTCF_2 <- CreateTableOne(vars = c("Hearing aid used- change2", "Visual appliance used- change2","Urinary collection device- change2",
                                        "Indwelling catheter- change2", "Ostomy- change2","Parenteral intake- change2","Nasogastric feeding (LTCF)- change2",
                                        "Wound care- change2","Scheduled toileting program- change2","Hospice care- change2",
                                        "Turning programe- change2","Physical therapy- change2", "Occupational therapy- change2",
                                        "Speech therapy- change2","Psychological therapies- change2 ", "Respiratory therapy- change2",
                                        "Full bed rails- change2", "Trunk restraint- change2","Chairs prevents rising- change2",
                                        "Living will- change2","Do not resuscitate- change2", "Do not intubate- change2", 
                                        "Do not hospitalize- change2", "No tube feeding- change2", "Medication restrictions- change2",
                                        "Cards/games- change2", "Conversing- change2", "Crafts- change2", "Exercise- change2",
                                        "Gardening- change2","Helping others- change2", "Music- change2","Reading- change2",
                                        "Spiritual activities- change2", "Trips/shopping- change2", "Walking outdoors- change2",
                                        "TV- change2","Cane, walker or crutch- change2","Wheeled self- change2"),data = mydata_wide, factorVars = c("Hearing aid used- change2", "Visual appliance used- change2","Urinary collection device- change2",
                                                                                                                                                    "Indwelling catheter- change2", "Ostomy- change2","Parenteral intake- change2","Nasogastric feeding (LTCF)- change2",
                                                                                                                                                    "Wound care- change2","Scheduled toileting program- change2","Hospice care- change2",
                                                                                                                                                    "Turning programe- change2","Physical therapy- change2", "Occupational therapy- change2",
                                                                                                                                                    "Speech therapy- change2","Psychological therapies- change2 ", "Respiratory therapy- change2",
                                                                                                                                                    "Full bed rails- change2", "Trunk restraint- change2","Chairs prevents rising- change2",
                                                                                                                                                    "Living will- change2","Do not resuscitate- change2", "Do not intubate- change2", 
                                                                                                                                                    "Do not hospitalize- change2", "No tube feeding- change2", "Medication restrictions- change2",
                                                                                                                                                    "Cards/games- change2", "Conversing- change2", "Crafts- change2", "Exercise- change2",
                                                                                                                                                    "Gardening- change2","Helping others- change2", "Music- change2","Reading- change2",
                                                                                                                                                    "Spiritual activities- change2", "Trips/shopping- change2", "Walking outdoors- change2",
                                                                                                                                                    "TV- change2","Cane, walker or crutch- change2","Wheeled self- change2"))
changeLTCF_2 <- print(changeLTCF_2, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# !Note: Please change to your own path
write.csv(changeLTCF_2,file="C:/Users/User/Desktop/Results_LTCF/Change_LTCF_2.csv")

#######################################################################################################################
#!Note: Finland: remove:"Do not intubate- change3" 
#!Note: Canada: remove:"Do not intubate- change3", "No tube feeding- change3","Medication restrictions-change3" 
#######################################################################################################################


changeLTCF_3 <- CreateTableOne(vars = c("Hearing aid used- change3", "Visual appliance used- change3","Urinary collection device- change3",
                                        "Indwelling catheter- change3", "Ostomy- change3","Parenteral intake- change3","Nasogastric feeding (LTCF)- change3",
                                        "Wound care- change3","Scheduled toileting program- change3","Hospice care- change3",
                                        "Turning programe- change3","Physical therapy- change3", "Occupational therapy- change3",
                                        "Speech therapy- change3","Psychological therapies- change3 ", "Respiratory therapy- change3",
                                        "Full bed rails- change3", "Trunk restraint- change3","Chairs prevents rising- change3",
                                        "Living will- change3","Do not resuscitate- change3", "Do not intubate- change3", 
                                        "Do not hospitalize- change3", "No tube feeding- change3", "Medication restrictions- change3",
                                        "Cards/games- change3", "Conversing- change3", "Crafts- change3", "Exercise- change3",
                                        "Gardening- change3","Helping others- change3", "Music- change3","Reading- change3",
                                        "Spiritual activities- change3", "Trips/shopping- change3", "Walking outdoors- change3",
                                        "TV- change3","Cane, walker or crutch- change3","Wheeled self- change3"),data = mydata_wide, factorVars = c("Hearing aid used- change3", "Visual appliance used- change3","Urinary collection device- change3",
                                                                                                                                                    "Indwelling catheter- change3", "Ostomy- change3","Parenteral intake- change3","Nasogastric feeding (LTCF)- change3",
                                                                                                                                                    "Wound care- change3","Scheduled toileting program- change3","Hospice care- change3",
                                                                                                                                                    "Turning programe- change3","Physical therapy- change3", "Occupational therapy- change3",
                                                                                                                                                    "Speech therapy- change3","Psychological therapies- change3", "Respiratory therapy- change3",
                                                                                                                                                    "Full bed rails- change3", "Trunk restraint- change3","Chairs prevents rising- change3",
                                                                                                                                                    "Living will- change3","Do not resuscitate- change3", "Do not intubate- change3", 
                                                                                                                                                    "Do not hospitalize- change3", "No tube feeding- change3", "Medication restrictions- change3",
                                                                                                                                                    "Cards/games- change3", "Conversing- change3", "Crafts- change3", "Exercise- change3",
                                                                                                                                                    "Gardening- change3","Helping others- change3", "Music- change3","Reading- change3",
                                                                                                                                                    "Spiritual activities- change3", "Trips/shopping- change3", "Walking outdoors- change3",
                                                                                                                                                    "TV- change3","Cane, walker or crutch- change3","Wheeled self- change3"))

# !Note: Please change to your own path
write.csv(changeLTCF_3,file="C:/Users/User/Desktop/Results_LTCF/Change_LTCF_3.csv")




