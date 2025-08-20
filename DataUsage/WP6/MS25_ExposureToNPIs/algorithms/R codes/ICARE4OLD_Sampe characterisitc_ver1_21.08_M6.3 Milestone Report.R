
###Syntax prepared by Ilona Baranska (UJCM)
##version 1; 08/21/2023

#Analysis for "Report on non-pharmacological interventions and (dis)continuation during care trajectories” under the ICARE4OLD project

#Please prepare a table with patient/client characteristics based on the first assessment
#For information on how to prepare the database for analysis, see the code: 
#     "ICARE4OLD_LTCF_ver1_21.08_M6.3 Milestone Report" or 
#     "ICARE4OLD_HC_ver1_21.08_M6.3 Milestone Report"


###################################### interRAI Manual LTCF or HC v9 ########################################################

###MDS for NH version ---> line 200
###MDS for HC version ---> line 430

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
# sADLH; sCPS; sDRS;
# iA2: Gender
# iI1a: Hip fracture 
# iI1b: Other fracture 
# iI1c: Alzheimer's disease 
# iI1d: Other dementia 
# iI1e: Hemiplegia 
# iI1f: Multiple sclerosis 
# iI1g: Paraplegia 
# iI1h: Parkinson's disease 
# iI1i: Quadriplegia 
# iI1j: Stroke 
# iI1k: Coronary heart disease 
# iI1l: Congestive heart failure 
# iI1m: Chronic obstructive pulmonary disease 
# iI1n: Anxiety 
# iI1o: Depression 
# iI1p: Schizophrenia 
# iI1s: Cancer 
# iI1t: Diabetes mellitus 
# iI1w: Bipolar disorder 

###Step1 Install packages and prepare your own data

##Install packages

install.packages(c("haven", "tidyr", "dplyr", "tableone"))
library(haven); library(tidyr); library(dplyr); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format

data <- read_sav('C:/Users/User/Desktop/icare2023/database_example.sav')

## Select relevant variables for analysis

mydata_charac <- data [ , c("ID",  "iA8", "Assess_type","age", "iA2", "sADLH", "sCPS", "sDRS",
                     "iI1a", "iI1b", "iI1c", "iI1d", "iI1e", "iI1f", "iI1g",
                     "iI1h", "iI1i", "iI1j", "iI1k", "iI1l", "iI1m", "iI1n",
                      "iI1o", "iI1p", "iI1s", "iI1t", "iI1w")]

## Apply inclusion criteria 

# Inclusion criteria 1. Exclude discharge or return assessment
mydata_charac$iA8_r[mydata_charac$iA8==1 | mydata_charac$iA8==2 | mydata_charac$iA8==4 | mydata_charac$iA8==7] <- "1"
mydata_charac$iA8_r[mydata_charac$iA8==3 | mydata_charac$iA8==5 | mydata_charac$iA8==6 ] <- "2"
mydata_charac <- mydata_charac[!is.na(mydata_charac$iA8_r) & mydata_charac$iA8_r == 1,]

#Note: only for HC:
#mydata$iA8_r[mydata$A2==1 | mydata$A2==2 | mydata$A2==3 | mydata$A2==6 | mydata$A2==7] <- "1"
#mydata$iA8_r[mydata$A2==4 | mydata$A2==5] <- "2"
#mydata <- mydata[!is.na(mydata$iA8_r) & mydata$iA8_r == 1,]

# Inclusion criteria 2. People aged 60+
n.under60 <- length(unique(mydata_charac[mydata_charac$age <60, ]$ID))
mydata_charac <- mydata_charac[mydata_charac$age >= 60, ]

##Calculate number of patients/client in each assessment point
#!Note: for home care analysis, change LTCF to HC

no_observationLTCF <- CreateTableOne(vars = c("Assess_type"),data = mydata_charac, 
                                 factorVars = c("Assess_type"))

no_observationLTCF <- print(no_observationLTCF, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop

# !Note: Please change to your own path
#!Note: for home care analysis, change LTCF to HC
write.csv(no_observationLTCF,file="C:/Users/User/Desktop/Results_LTCF/no_observationLTCF.csv")

# Inclusion criteria 3. Choose only first assessment point
mydata_charac <- mydata_charac[!is.na(mydata_charac$"Assess_type") & mydata_charac$"Assess_type" == 1,]

## Step 2 Recode variables for analysis

# Age
mydata_charac$Age_group <- "60-69"
mydata_charac$Age_group[mydata_charac$age >= 70 & mydata_charac$age <= 79] <- "70-79"
mydata_charac$Age_group[mydata_charac$age >= 80 & mydata_charac$age <= 89] <- "80-89"
mydata_charac$Age_group[mydata_charac$age >= 90] <- "90+"

# ADL: Independent (0), Early-loss (1-3), and Dependent (4-6)
mydata_charac$sADLH <- as.numeric(mydata_charac$sADLH)
mydata_charac$ADL_r <- "Independent"
mydata_charac$ADL_r[mydata_charac$sADLH >= 1 & mydata_charac$sADLH <= 3] <- "Early-loss"
mydata_charac$ADL_r[mydata_charac$sADLH >= 4 & mydata_charac$sADLH <= 6] <- "Dependent"
mydata_charac$ADL_r[is.na(mydata_charac$sADLH)] <- NA
mydata_charac$ADL_r <- factor(mydata_charac$ADL_r, levels = c("Independent", "Early-loss", "Dependent"))

# CPS: Robust (0), Mild (1-2), and Moderate to Severe (3-6)
mydata_charac$sCPS <- as.numeric(mydata_charac$sCPS)
mydata_charac$CPS_r <- "Robust"
mydata_charac$CPS_r[mydata_charac$sCPS >= 1 & mydata_charac$sCPS <= 2] <- "Mild"
mydata_charac$CPS_r[mydata_charac$sCPS >= 3 & mydata_charac$sCPS <= 6] <- "Moderate-Severe"
mydata_charac$CPS_r[is.na(mydata_charac$sCPS)] <- NA
mydata_charac$CPS_r <- factor(mydata_charac$CPS_r, levels = c("Robust", "Mild", "Moderate-Severe"))

# DRS: Low risk (0), Medium risk(1-2), and High risk (3-14)
mydata_charac$sDRS <- as.numeric(mydata_charac$sDRS)
mydata_charac$DRS_r <- "Low"
mydata_charac$DRS_r[mydata_charac$sDRS >= 1 & mydata_charac$sDRS <= 2] <- "Medium"
mydata_charac$DRS_r[mydata_charac$sDRS >= 3 & mydata_charac$sDRS <= 14] <- "High"
mydata_charac$DRS_r[is.na(mydata_charac$sDRS)] <- NA
mydata_charac$DRS_r <- factor(mydata_charac$DRS_r, levels = c("Low", "Medium", "High"))

# Gender
mydata_charac$iA2_r <- "male"
mydata_charac$iA2_r[mydata_charac$iA2 ==1] <- "female"
mydata_charac$iA2_r[is.na(mydata_charac$iA2)] <- NA

# Prevalence of diseases - create dichotomous variables (yes vs no)

vars <- c("iI1a", "iI1b", "iI1c", "iI1d", "iI1e", "iI1f", "iI1g",
          "iI1h", "iI1i", "iI1j", "iI1k", "iI1l", "iI1m", "iI1n",
          "iI1o", "iI1p", "iI1s", "iI1t", "iI1w")

for (var in vars) {
  new_var_name <- paste0(var, "_r")
  mydata_charac[[new_var_name]] <- "yes"
  mydata_charac[[new_var_name]][mydata_charac[[var]] == 0] <- "no"
  mydata_charac[[new_var_name]][is.na(mydata_charac[[var]])] <- NA
}
 
names(mydata_charac)[34:52] <- c("Hip fracture", "Other fracture", "Alzheimer's disease", "Other dementia",
                                 "Hemiplegia", "Multiple sclerosis", "Paraplegia", "Parkinson's disease",
                                 "Quadriplegia", "Stroke", "Coronary heart disease", "Congestive heart failure",
                                 "Chronic obstructive pulmonary disease", "Anxiety", "Depression", "Schizophrenia",
                                 "Cancer", "Diabetes mellitus", "Bipolar")

# Recode Hip fracture or Other fracture into Any fracture
mydata_charac$"any fracture" <- "no"
mydata_charac$"any fracture"[mydata_charac$"Hip fracture" == "yes" | mydata_charac$"Other fracture" == "yes"] <- "yes"
mydata_charac$"any fracture"[is.na(mydata_charac$"Hip fracture")] <- NA
mydata_charac$"any fracture"[is.na(mydata_charac$"Other fracture")] <- NA

# Recode Hemiplegia or Paraplegia or Quadriplegia into Any Plegia
mydata_charac$"any plegia" <- "no"
mydata_charac$"any plegia"[mydata_charac$"Hemiplegia" == "yes" 
                             | mydata_charac$"Paraplegia" == "yes" | mydata_charac$"Quadriplegia" ==1] <- "yes"
mydata_charac$"any plegia"[is.na(mydata_charac$"Hemiplegia")] <- NA
mydata_charac$"any plegia"[is.na(mydata_charac$"Paraplegia")] <- NA
mydata_charac$"any plegia"[is.na(mydata_charac$"Quadriplegia")] <- NA

## Step 3 Create a table with characteristics
#!Note: for home care analysis, change LTCF to HC

characteristicLTCF <- CreateTableOne(vars = c("iA2_r", "Age_group","ADL_r", "CPS_r", "DRS_r",
                                              "any fracture", "Alzheimer's disease", "Other dementia",
                                              "any plegia", "Multiple sclerosis", "Parkinson's disease",
                                              "Stroke", "Coronary heart disease", "Congestive heart failure",
                                              "Chronic obstructive pulmonary disease", "Anxiety", "Depression", "Schizophrenia",
                                              "Cancer", "Diabetes mellitus", "Bipolar"),data = mydata_charac, factorVars = c("iA2_r","Age_group","ADL_r", "CPS_r", "DRS_r",
                                                                                                                             "any fracture", "Alzheimer's disease", "Other dementia",
                                                                                                                             "any plegia", "Multiple sclerosis", "Parkinson's disease",
                                                                                                                             "Stroke", "Coronary heart disease", "Congestive heart failure",
                                                                                                                             "Chronic obstructive pulmonary disease", "Anxiety", "Depression", "Schizophrenia",
                                                                                                                             "Cancer", "Diabetes mellitus", "Bipolar"))
                                         
characteristicLTCF <- print(characteristicLTCF, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# Step 5 Save the results to a folder
#!Note: for home care analysis, change LTCF to HC

# !Note: Please change to your own path
write.csv(characteristicLTCF,file="C:/Users/User/Desktop/Results_LTCF/CharacteristicLTCF.csv")



############################################ MDS v2 for NH #######################################################

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
# sADLH; sCPS; sDRS;
# AA2 (Note: Finland AA3) : Gender
# J4c (Note: Finland also I1m): Hip fracture 
# J4d (Note: Finland also I1p): Other fracture 
# I1q (Note: in Canada: I1r): Alzheimer's disease 
# I1u (Note: in Canada: I1v): Other dementia 
# I1v (Note: not in Canada): Hemiplegia 
# I1w (Note: in Canada: I1y): Multiple sclerosis 
# I1x (Note: in Canada: I1z): Paraplegia 
# I1y (Note: in Canada: I1aa): Parkinson's disease 
# I1z (Note: in Canada: I1bb): Quadriplegia 
# I1t (Note: in Canada: I1u): Stroke 
# I1d (Note: in Canada: I1d): Coronary heart disease 
# I1f (Note: in Canada: I1f): Congestive heart failure 
# I1ii (Note: in Canada: I1kk): Chronic obstructive pulmonary disease 
# I1dd (Note: in Canada:I1ff): Anxiety 
# I1ee (Note: in Canada: I1gg): Depression 
# I1gg (Note: in Canada: I1ii): Schizophrenia 
# I1pp (Note: in Canada: I1rr): Cancer 
# I1a: (Note: in Canada: I1a): Diabetes mellitus 
# I1ff (Note: not in USA; in Canada: I1hh): Bipolar disorder 

###Step1 Install packages and prepare your own data

##Install packages

install.packages(c("haven", "tidyr", "dplyr", "tableone"))
library(haven); library(tidyr); library(dplyr); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format

data <- read_sav('C:/Users/User/Desktop/icare2023/database_example.sav')

## Select relevant variables for analysis

#####################################################################################################
#Note:  Finland: change "AA2" --> "AA3"; add: "I1m"; "I1p";
#       USA: remove: I1ff
#####################################################################################################

mydata_charac <- data [ , c("ID",  "AA8", "Assess_type","age", "AA2", "sADLH", "sCPS", "sDRS",
                            "J4c", "J4d", "I1q", "I1u", "I1v", "I1w", "I1x", "I1y",
                            "I1z", "I1t", "I1d", "I1f", "I1ii", "I1dd", "I1ee", "I1gg", 
                            "I1pp", "I1a", "I1ff")]

#####################################################################################################
#Note: only for Canada:
#mydata_charac <- data [ , c("ID",  "AA8", "Assess_type","age", "AA2", "sADLH", "sCPS", "sDRS",
#                            "J4c", "J4d", "J4c","J4d", "I1r", "I1v","I1y","I1z","I1aa", "I1bb", "I1u", 
#                             "I1d", "I1f", "I1kk", "I1ff","I1gg","I1ii", "I1rr","I1a", "I1hh")]
#####################################################################################################

## Apply inclusion criteria 

# Inclusion criteria 1. Exclude discharge or return assessment
mydata_charac$iA8_r[mydata_charac$AA8==1 | mydata_charac$AA8==2 | mydata_charac$AA8==4 | mydata_charac$AA8==7] <- "1"
mydata_charac$iA8_r[mydata_charac$AA8==3 | mydata_charac$AA8==5 | mydata_charac$AA8==6 ] <- "2"
mydata_charac <- mydata_charac[!is.na(mydata_charac$iA8_r) & mydata_charac$iA8_r == 1,]

# Inclusion criteria 2. People aged 60+
n.under60 <- length(unique(mydata_charac[mydata_charac$age <60, ]$ID))
mydata_charac <- mydata_charac[mydata_charac$age >= 60, ]

##Calculate number of patients/client in each assessment point

no_observationLTCF <- CreateTableOne(vars = c("Assess_type"),data = mydata_charac, 
                                     factorVars = c("Assess_type"))

no_observationLTCF <- print(no_observationLTCF, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop

# !Note: Please change to your own path
write.csv(no_observationLTCF,file="C:/Users/User/Desktop/Results_LTCF/no_observationLTCF.csv")

# Inclusion criteria 3. Choose only first assessment point
mydata_charac <- mydata_charac[!is.na(mydata_charac$"Assess_type") & mydata_charac$"Assess_type" == 1,]

## Step 2 Recode variables for analysis

# Age
mydata_charac$Age_group <- "60-69"
mydata_charac$Age_group[mydata_charac$age >= 70 & mydata_charac$age <= 79] <- "70-79"
mydata_charac$Age_group[mydata_charac$age >= 80 & mydata_charac$age <= 89] <- "80-89"
mydata_charac$Age_group[mydata_charac$age >= 90] <- "90+"

# ADL: Independent (0), Early-loss (1-3), and Dependent (4-6)
mydata_charac$sADLH <- as.numeric(mydata_charac$sADLH)
mydata_charac$ADL_r <- "Independent"
mydata_charac$ADL_r[mydata_charac$sADLH >= 1 & mydata_charac$sADLH <= 3] <- "Early-loss"
mydata_charac$ADL_r[mydata_charac$sADLH >= 4 & mydata_charac$sADLH <= 6] <- "Dependent"
mydata_charac$ADL_r[is.na(mydata_charac$sADLH)] <- NA
mydata_charac$ADL_r <- factor(mydata_charac$ADL_r, levels = c("Independent", "Early-loss", "Dependent"))

# CPS: Robust (0), Mild (1-2), and Moderate to Severe (3-6)
mydata_charac$sCPS <- as.numeric(mydata_charac$sCPS)
mydata_charac$CPS_r <- "Robust"
mydata_charac$CPS_r[mydata_charac$sCPS >= 1 & mydata_charac$sCPS <= 2] <- "Mild"
mydata_charac$CPS_r[mydata_charac$sCPS >= 3 & mydata_charac$sCPS <= 6] <- "Moderate-Severe"
mydata_charac$CPS_r[is.na(mydata_charac$sCPS)] <- NA
mydata_charac$CPS_r <- factor(mydata_charac$CPS_r, levels = c("Robust", "Mild", "Moderate-Severe"))

# DRS: Low risk (0), Medium risk(1-2), and High risk (3-14)
mydata_charac$sDRS <- as.numeric(mydata_charac$sDRS)
mydata_charac$DRS_r <- "Low"
mydata_charac$DRS_r[mydata_charac$sDRS >= 1 & mydata_charac$sDRS <= 2] <- "Medium"
mydata_charac$DRS_r[mydata_charac$sDRS >= 3 & mydata_charac$sDRS <= 14] <- "High"
mydata_charac$DRS_r[is.na(mydata_charac$sDRS)] <- NA
mydata_charac$DRS_r <- factor(mydata_charac$DRS_r, levels = c("Low", "Medium", "High"))

# Gender
mydata_charac$iA2_r <- "male"
mydata_charac$iA2_r[mydata_charac$AA2 ==1] <- "female"
mydata_charac$iA2_r[is.na(mydata_charac$AA2)] <- NA

#####################################################################################################
#Note: only in Finland:
#Recode hip fracture:
#mydata_charac$J4c_r <- "no"
#mydata_charac$J4c_r[mydata_charac$I1m ==1 | mydata_charac$J4c ==1] <- "yes"
#mydata_charac$J4c_r[is.na(mydata_charac$I1m)] <- NA
#mydata_charac$J4c_r[is.na(mydata_charac$J4c)] <- NA

#Recode other fracture:
#mydata_charac$J4d_r <- "no"
#mydata_charac$J4d_r[mydata_charac$I1p ==1 | mydata_charac$J4d ==1] <- "yes"
#mydata_charac$J4d_r[is.na(mydata_charac$I1p)] <- NA
#mydata_charac$J4d_r[is.na(mydata_charac$J4d)] <- NA
#####################################################################################################

# Prevalence of diseases - create dichotomous variables (yes vs no)
#####################################################################################################
#Note: Finland: change: "J4c" --> "J4c_r"; "J4d" --> "J4d_r";
#       USA: remove: "I1ff"
#
#       Canada: change for:
#vars <- c("J4c", "J4d", "J4c","J4d", "I1r", "I1v","I1y","I1z","I1aa", "I1bb", "I1u", 
#          "I1d", "I1f", "I1kk", "I1ff","I1gg","I1ii", "I1rr","I1a", "I1hh")
#####################################################################################################
vars <- c("J4c", "J4d", "I1q", "I1u", "I1v", "I1w", "I1x", "I1y",
          "I1z", "I1t", "I1d", "I1f", "I1ii", "I1dd", "I1ee", "I1gg", 
          "I1pp", "I1a", "I1ff")

for (var in vars) {
  new_var_name <- paste0(var, "_r")
  mydata_charac[[new_var_name]] <- "yes"
  mydata_charac[[new_var_name]][mydata_charac[[var]] == 0] <- "no"
  mydata_charac[[new_var_name]][is.na(mydata_charac[[var]])] <- NA
}


#####################################################################################################
#Note:   USA: remove: "Bipolar and change [33:50]
#        Canada: remove: "Hemiplegia" and change [33:50]
#####################################################################################################
names(mydata_charac)[34:52] <- c("Hip fracture", "Other fracture", "Alzheimer's disease", "Other dementia",
                                 "Hemiplegia", "Multiple sclerosis", "Paraplegia", "Parkinson's disease",
                                 "Quadriplegia", "Stroke", "Coronary heart disease", "Congestive heart failure",
                                 "Chronic obstructive pulmonary disease", "Anxiety", "Depression", "Schizophrenia",
                                 "Cancer", "Diabetes mellitus", "Bipolar")

# Recode Hip fracture or Other fracture into Any fracture
mydata_charac$"any fracture" <- "no"
mydata_charac$"any fracture"[mydata_charac$"Hip fracture" == "yes" | mydata_charac$"Other fracture" == "yes"] <- "yes"
mydata_charac$"any fracture"[is.na(mydata_charac$"Hip fracture")] <- NA
mydata_charac$"any fracture"[is.na(mydata_charac$"Other fracture")] <- NA

# Recode Hemiplegia or Paraplegia or Quadriplegia into Any Plegia
#####################################################################################################
#Note:  Canada: remove: "Hemiplegia" 
#####################################################################################################
mydata_charac$"any plegia" <- "no"
mydata_charac$"any plegia"[mydata_charac$"Hemiplegia" == "yes" 
                           | mydata_charac$"Paraplegia" == "yes" | mydata_charac$"Quadriplegia" ==1] <- "yes"
mydata_charac$"any plegia"[is.na(mydata_charac$"Hemiplegia")] <- NA
mydata_charac$"any plegia"[is.na(mydata_charac$"Paraplegia")] <- NA
mydata_charac$"any plegia"[is.na(mydata_charac$"Quadriplegia")] <- NA

## Step 3 Create a table with characteristics
#####################################################################################################
#Note:   USA: remove: Bipolar"; 
#        Canada: remove: "Hemiplegia";
#####################################################################################################

characteristicLTCF <- CreateTableOne(vars = c("iA2_r", "Age_group","ADL_r", "CPS_r", "DRS_r",
                                              "any fracture", "Alzheimer's disease", "Other dementia",
                                              "any plegia", "Multiple sclerosis", "Parkinson's disease",
                                              "Stroke", "Coronary heart disease", "Congestive heart failure",
                                              "Chronic obstructive pulmonary disease", "Anxiety", "Depression", "Schizophrenia",
                                              "Cancer", "Diabetes mellitus", "Bipolar"),data = mydata_charac, factorVars = c("iA2_r","Age_group","ADL_r", "CPS_r", "DRS_r",
                                                                                                                             "any fracture", "Alzheimer's disease", "Other dementia",
                                                                                                                             "any plegia", "Multiple sclerosis", "Parkinson's disease",
                                                                                                                             "Stroke", "Coronary heart disease", "Congestive heart failure",
                                                                                                                             "Chronic obstructive pulmonary disease", "Anxiety", "Depression", "Schizophrenia",
                                                                                                                             "Cancer", "Diabetes mellitus", "Bipolar"))


characteristicLTCF <- print(characteristicLTCF, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# Step 5 Save the results to a folder

# !Note: Please change to your own path

write.csv(characteristicLTCF,file="C:/Users/User/Desktop/Results_LTCF/CharacteristicLTCF.csv")






############################################ MDS v2 for HC #######################################################

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
#                4: fourth assessment;
# sADLH; sCPS; sDRS;
# BB1 : Gender
# J1n : Hip fracture 
# J1o : Other fracture 
# J1g : Alzheimer's disease 
# J1h : Other dementia 
# J1j : Hemiplegia 
# J1k : Multiple sclerosis 
# J1l : Parkinson's disease 
# J1a : Stroke 
# J1c : Coronary heart disease 
# J1b : Congestive heart failure 
# J1z : Chronic obstructive pulmonary disease 
# J1x : Cancer 
# J1y: : Diabetes mellitus 

###Step1 Install packages and prepare your own data

##Install packages

install.packages(c("haven", "tidyr", "dplyr", "tableone"))
library(haven); library(tidyr); library(dplyr); library(tableone)

## Import your data
# !Note: Please change to your own path and/or format

data <- read_sav('C:/Users/User/Desktop/icare2023/database_example.sav')

## Select relevant variables for analysis

mydata_charac <- data [ , c("ID",  "AA8", "Assess_type","age", "BB1", "sADLH", "sCPS", "sDRS",
                            "J1n","J1o","J1g","J1h","J1j","J1k","J1l","J1a","J1c", "J1b","J1z",
                            "J1x","J1y")]

## Apply inclusion criteria 

# Inclusion criteria 1. Exclude discharge or return assessment
mydata_charac$iA8_r[mydata_charac$A2==1 | mydata_charac$A2==2 | mydata_charac$A2==3 | 
                      mydata_charac$A2==6 | mydata_charac$A2==7] <- "1"
mydata_charac$iA8_r[mydata_charac$A2==4 | mydata_charac$A2==5] <- "2"
mydata_charac <- mydata_charac[!is.na(mydata_charac$iA8_r) & mydata_charac$iA8_r == 1,]

# Inclusion criteria 2. People aged 60+
n.under60 <- length(unique(mydata_charac[mydata_charac$age <60, ]$ID))
mydata_charac <- mydata_charac[mydata_charac$age >= 60, ]

##Calculate number of patients/client in each assessment point

no_observationHC <- CreateTableOne(vars = c("Assess_type"),data = mydata_charac, 
                                     factorVars = c("Assess_type"))

no_observationHC <- print(no_observationHC, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

## Create the output folder on your Desktop

# !Note: Please change to your own path
write.csv(no_observationHC,file="C:/Users/User/Desktop/Results_HC/no_observationHC.csv")

# Inclusion criteria 3. Choose only first assessment point
mydata_charac <- mydata_charac[!is.na(mydata_charac$"Assess_type") & mydata_charac$"Assess_type" == 1,]

## Step 2 Recode variables for analysis

# Age
mydata_charac$Age_group <- "60-69"
mydata_charac$Age_group[mydata_charac$age >= 70 & mydata_charac$age <= 79] <- "70-79"
mydata_charac$Age_group[mydata_charac$age >= 80 & mydata_charac$age <= 89] <- "80-89"
mydata_charac$Age_group[mydata_charac$age >= 90] <- "90+"

# ADL: Independent (0), Early-loss (1-3), and Dependent (4-6)
mydata_charac$sADLH <- as.numeric(mydata_charac$sADLH)
mydata_charac$ADL_r <- "Independent"
mydata_charac$ADL_r[mydata_charac$sADLH >= 1 & mydata_charac$sADLH <= 3] <- "Early-loss"
mydata_charac$ADL_r[mydata_charac$sADLH >= 4 & mydata_charac$sADLH <= 6] <- "Dependent"
mydata_charac$ADL_r[is.na(mydata_charac$sADLH)] <- NA
mydata_charac$ADL_r <- factor(mydata_charac$ADL_r, levels = c("Independent", "Early-loss", "Dependent"))

# CPS: Robust (0), Mild (1-2), and Moderate to Severe (3-6)
mydata_charac$sCPS <- as.numeric(mydata_charac$sCPS)
mydata_charac$CPS_r <- "Robust"
mydata_charac$CPS_r[mydata_charac$sCPS >= 1 & mydata_charac$sCPS <= 2] <- "Mild"
mydata_charac$CPS_r[mydata_charac$sCPS >= 3 & mydata_charac$sCPS <= 6] <- "Moderate-Severe"
mydata_charac$CPS_r[is.na(mydata_charac$sCPS)] <- NA
mydata_charac$CPS_r <- factor(mydata_charac$CPS_r, levels = c("Robust", "Mild", "Moderate-Severe"))

# DRS: Low risk (0), Medium risk(1-2), and High risk (3-14)
mydata_charac$sDRS <- as.numeric(mydata_charac$sDRS)
mydata_charac$DRS_r <- "Low"
mydata_charac$DRS_r[mydata_charac$sDRS >= 1 & mydata_charac$sDRS <= 2] <- "Medium"
mydata_charac$DRS_r[mydata_charac$sDRS >= 3 & mydata_charac$sDRS <= 14] <- "High"
mydata_charac$DRS_r[is.na(mydata_charac$sDRS)] <- NA
mydata_charac$DRS_r <- factor(mydata_charac$DRS_r, levels = c("Low", "Medium", "High"))

# Gender
mydata_charac$iA2_r <- "male"
mydata_charac$iA2_r[mydata_charac$BB1 ==1] <- "female"
mydata_charac$iA2_r[is.na(mydata_charac$BB1)] <- NA


# Prevalence of diseases - create dichotomous variables (yes vs no)

vars <- c("J1n","J1o","J1g","J1h","J1j","J1k","J1l","J1a","J1c", "J1b","J1z",
          "J1x","J1y")

for (var in vars) {
  new_var_name <- paste0(var, "_r")
  mydata_charac[[new_var_name]] <- "yes"
  mydata_charac[[new_var_name]][mydata_charac[[var]] == 0] <- "no"
  mydata_charac[[new_var_name]][is.na(mydata_charac[[var]])] <- NA
}

names(mydata_charac)[27:39] <- c("Hip fracture", "Other fracture", "Alzheimer's disease", "Other dementia",
                                 "Hemiplegia", "Multiple sclerosis", "Parkinson's disease",
                                 "Stroke", "Coronary heart disease", "Congestive heart failure",
                                 "Chronic obstructive pulmonary disease", "Cancer", "Diabetes mellitus")

# Recode Hip fracture or Other fracture into Any fracture
mydata_charac$"any fracture" <- "no"
mydata_charac$"any fracture"[mydata_charac$"Hip fracture" == "yes" | mydata_charac$"Other fracture" == "yes"] <- "yes"
mydata_charac$"any fracture"[is.na(mydata_charac$"Hip fracture")] <- NA
mydata_charac$"any fracture"[is.na(mydata_charac$"Other fracture")] <- NA

## Step 3 Create a table with characteristics

characteristicHC <- CreateTableOne(vars = c("iA2_r", "Age_group","ADL_r", "CPS_r", "DRS_r", "any fracture",
                                            "Alzheimer's disease", "Other dementia",
                                              "Hemiplegia", "Multiple sclerosis", "Parkinson's disease",
                                              "Stroke", "Coronary heart disease", "Congestive heart failure",
                                              "Chronic obstructive pulmonary disease","Cancer", "Diabetes mellitus"),data = mydata_charac, factorVars = c("iA2_r", "Age_group","ADL_r", "CPS_r", "DRS_r", "any fracture",
                                                                                                                                                          "Alzheimer's disease", "Other dementia",
                                                                                                                                                          "Hemiplegia", "Multiple sclerosis", "Parkinson's disease",
                                                                                                                                                          "Stroke", "Coronary heart disease", "Congestive heart failure",
                                                                                                                                                          "Chronic obstructive pulmonary disease","Cancer", "Diabetes mellitus"))


characteristicHC <- print(characteristicHC, quote = FALSE, noSpaces = TRUE, printToggle = FALSE)

# Step 5 Save the results to a folder

# !Note: Please change to your own path

write.csv(characteristicHC,file="C:/Users/User/Desktop/Results_HC/CharacteristicHC.csv")



