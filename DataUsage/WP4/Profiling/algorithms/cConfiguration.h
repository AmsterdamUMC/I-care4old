#pragma once

#include "definitions.h"
#include "tHashTable.h"
#include "tOperator.h"
#include "tInputBuffer.h"
#include "tOutputBuffer.h"
#include "cControlledVariables.h"
//#include "cDataManager.h"


/*
Overview
The purpose of this class is
1.	To  enable recognizing the person data input variable names
2.	To classify the data items to the right variable type 
3.	To create groups of variable:  similarity ,  predictive and results , under one target variable. .
4.	To enable some functions that needs lookup by names
5.	Other rules and strategy
The data entry with a person assessment will hold meta variables that belong to the different target variables , 
and the configuration file will hold separate mappings for variables that are dedicated for specific target variable so we know
where to place each. For example  Age_Adl_S means that this variable name is Age, it is normalized for the target variable “Adl” and 
is classified as a Similarity variable.  The configuration class will enable the user to notify the engine what variables belong to
what target variable and what is it classified as.
Here are the types of variables, divided into two groups – predictive and dependant.
General variable types:
Predictive types:
•	Similarity - predictive variables that get to be “upgraded” to be similarity variables. The algorithm first finds a smaller 
                 group of similar others using the similarity variables, and then performing regression and other methods on the
				 most homogenous groups of similar others
•	What if – predictive variables with some control or partial control. Also these are not a point in time data but a data about 
              the institute or place , mode of care, support  or treatment overtime. ,  what will be used to cut homogenous groups 
			  into sub sets and get ready to perform regression on such sub sets who are individual what if variations and that 
			  support the application needs.
•	Predictive  - predictive which are not controlled, and not fit to be similarity by nature. Will be a part of the regression 
                  test to be used for prediction. All the similarity variables are by definition included and a part of the predictive
				  variables.  
Dependent types
•	Target – dependant variables that is going to be presented to the application as a prediction, and that the algorithm is 
             tuned on the profile level around satisfying this parameter. 
•	Result – dependant variables. These variables also are predicted but will not form dedicated profiles. A result variable is 
             attached to the profile under a target variable (See Profile concept). Target and result variables will be presented in a similar way.


The configuration file will include the list of names under each group. here is what we have so far but will be set later:

All: 
ID, 6MonthChangeInADL_T, 6MonthHospitalization_T, Cognition_Adl_S, Age_Adl_S, Cognition_Hos_S, Age_Hos_S,
Cognition_Hos_S, Age_Hos_S, CoState_Adl_P, MentalHealthHistory_Adl_P, CoState_Hos_P, MentalHealthHistory_Hos_P,
12MonthChangeInADL_Adl_R, 12MonthHospitalization_Hos_R, InsitueType_W

ID:ID

What if: InsitueType_W,
What if variations: InsitueType_W:homecare, InsitueType_W:NircingHome

Targets: 6MonthChangeInADL_T, 6MonthHospitalization_T

Similarity:
	6MonthChangeInADL_T:
		Cognition_Adl_S:60, Age_Adl_S:40
		Prediction:1,2
		

	6MonthHospitalization_T:
		Cognition_Hos_S, Age_Hos_S


Predictive: 
	6MonthChangeInADL_T:CoState_Adl_P, MentalHealthHistory_Adl_P
	6MonthHospitalization_T:CoState_Hos_P, MentalHealthHistory_Hos_P

Results: 
	6MonthChangeInADL_T:12MonthChangeInADL_Adl_R
	6MonthHospitalization_T:12MonthHospitalization_Hos_R


the configuration class will get the list of all variables in the order as appears in the input person assessment file. It will build a hash table where the variable name is the key and the position in the array of person variables will be the data. When we load a person profile that has built an array of short integers (together with one variable which is  unique person ID and  is not a short integer ) we will be able to use the configuration class to get around. We will be able to get the list of similarity variables by order, and the predictive, and copy the right variables to the profile object.
The class will also have a special mission, to bridge the what if variables to the what if variation.  The configuration class includes the what if variables and the what if variations. In an almost a direct copy of rules we need to be able to get a what if index number when sending the what if variable list from the object, and so updating the profile object with the list of valid what if scenarios belong to the profile root. The class will hold a small hash that gets from the file the names of what if variabvles and what if variation combinations  and enable building the right what if variation value from the list of what if variables. 

*/

#define MAX_NUMBER_OF_LONGTERM_ASSESSMENTS 9

#define HH_CARE_SETTING_CODE 0
#define SNF_CARE_SETTING_CODE 1
#define IRF_CARE_SETTING_CODE 2
#define ALL_CARE_SETTING_CODE 3


//5 10 18 * new 3 deflines
#define BASE_HH_WEIGHT_FROM_ALL 1.0
#define BASE_SNF_WEIGHT_FROM_ALL 1.0
#define BASE_IRF_WEIGHT_FROM_ALL 0.3


class cConfigParameterInfo
{
private:
	string_m m_name;
	string_m m_value;

public:
	cConfigParameterInfo();
	~cConfigParameterInfo();
	void SetParameterName(char* name);
	void SetParameterValue(char* value);
	string_m& GetGetParameterName(){return m_name;}
	string_m& GetGetParameterValue(){return m_value;}
};

typedef cArrayList<cConfigParameterInfo*> ConfigParameterList;


class cTestCase
{
private:
	unsigned int m_id;
	ConfigParameterList m_configParametersList;
	unsigned int m_numberOfParameters;
public:
	cTestCase();
	~cTestCase();
	void SetCaseID(unsigned int id);
	void AddParameter(string_m name, string_m value);
	unsigned int GetNumOfParameters(){return m_numberOfParameters;}
	cConfigParameterInfo* GetOneParameterByIndex(unsigned int index);
	unsigned int GetTestID(){return m_id;}
};

typedef enum { BiggerThan_e = '1', BiggerOrEqual_e = '2', SmallerThan_e = '3', SmallerOrEqual_e = '4', 
               EqualTo_e = '5', NotEqualTo_e = '6'} eOperatorType;

typedef enum { IncreaseBy_e = '1', DecreaseBy_e = '2', SetTo_e = '3', PositiveLinear_e = '4',NegativeLinear_e = '5'} eActionType;
//Ohad 5.6.19
typedef enum { FunctionalImprove_e = '1', DischargeHome_e = '2', Readmission_e = '3', FunctionalDecline_e = '4', Death_e = '5', WalkingImprovement_e='6', Fall_e='7', Depression_e='8' ,
               DepressionSymp_e='9',PressureUlcer_e='10',Delirium_e='11', ADLDep_e = '12', WalkingDep_e = '13', DeliriumDischarge_e = '14', TransferDep_e = '15', Infection_e='16', 
				WalkingFullDep_e = '17', TransferFullDep_e = '18'} eQIMode;

typedef cArrayList<tNumericOperator<float>*> OperatorList;
typedef cArrayList<OperatorList*> OperatorListArray;


class cActionInfo
{
private:
	eActionType m_actionType;
	float m_value;
	unsigned int m_fieldIndex;
	tNumericOperator<float>* m_targetOperator;

	
public:
	cActionInfo();
	~cActionInfo();
	void SetActionInfo(eActionType actionType, float actionVal, unsigned int fieldIndex);
	float GetActionNewValue(float originalValue);
	unsigned int GetLineaRFieldIndex() {return m_fieldIndex;}
	bool IsTargetValueChancesShouldBeManipulated(float val);
	void SetOneRuleTargetCondition(eOperatorType operatorType, float conditionVal );
	tNumericOperator<float>* GetOperatorPTRByType(eOperatorType operatorType, float conditionVal );
};

typedef cArrayList<cActionInfo*> ActionInfoListArray;


class cDataRule
{
private:
	OperatorListArray m_fieldsRules;
	cActionInfo* m_actionInfo;
	ActionInfoListArray m_actionListinfo;
	unsigned int m_numOfActions;
	unsigned int m_populationPercentage;
	//tNumericOperator<float>* m_targetOperator;
	bool m_isLinearRule;
	unsigned int m_ruleWeight;

	

public:
	cDataRule();
	~cDataRule();
	void SetOneFiledCondition(unsigned int fieldIndex ,eOperatorType operatorType, float conditionVal );
	void SetOneRuleActionInfo(eActionType actionType, float actionVal, unsigned int fieldIndex);
	void SetOneRuleTargetCondition(eOperatorType operatorType, float conditionVal, unsigned int actionIndex );
	bool IsValueMeetsRuleConditions(float* fieldsValues);
	float GetValueAfterRuleAction(float origValue, unsigned int actionIndex);
	bool IsTargetValueChancesShouldBeManipulated(float val, unsigned int actionIndex);
	void SetPopulationPercentage(unsigned int populationPercentage);
	unsigned int GetOneRulePopulationPercentage();
	unsigned int GetPopulationPercentage(){return m_populationPercentage;}
	bool IsLinearRule(){return m_isLinearRule;}
	unsigned int GetLinearFieldIndex(unsigned int actionIndex);
	unsigned int GetNumberOfRulesActions();

};

typedef cArrayList<cDataRule*> DataRulesArray;

class cDataRulesManager
{
private:
	unsigned int m_NumberOfRules;
	DataRulesArray m_rules;
	eOperatorType GetOperatorTypeFromStr(string_m conditionStr);
	eActionType GetActionTypeFromStr(string_m actionStr);
	unsigned int m_rulesWeight;

public:
	cDataRulesManager();
	~cDataRulesManager();
	unsigned int GetNumOfRules(){ return m_NumberOfRules; }

	void SetOneRuleCondition(unsigned int fieldIndex, string_m conditionStr, float conditionVal);
	void SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex );
	void SetOneRuleAction(string_m actionStr, float actionVal, unsigned int fieldIndex );
	void SetPopulationPercentage(unsigned int populationPercentage);
	bool IsValueMeetsRuleConditions(float* fieldsValues, unsigned int ruleIndex);
	bool IsTargetValueChancesShouldBeManipulated(float val, unsigned int ruleIndex,unsigned int actionIndex);
	unsigned int GetOneRulePopulationPercentage(unsigned int ruleIndex);
	float GetValueAfterRuleAction(float origValue, unsigned int ruleIndex, unsigned int actionIndex);
	bool IsLinearRule(unsigned int ruleIndex);
	unsigned int GetLinearFieldIndex(unsigned int ruleIndex, unsigned int actionIndex);
	unsigned int GetNumberOfRulesActions(unsigned int ruleIndex);
	void SetRulesWeight(unsigned int weight);
	unsigned int GetRulesWeight() {return m_rulesWeight;}
	
	void AddRule();
};


typedef cArrayList<short int, 50, 50> ShortIntArray;

typedef enum { defaultType_e = '0', numOfTopSimilarForEditScore_e = '1', Kcount_e = '2', KcontrolCount_e = '3', Ncount_e = '4', 
               maxCountPerformanceList_e = '5', } eGeneralInfoType ;

class cOneWhatIfinfo
{
private:

	string_m m_fieldName;
	unsigned int m_fieldIndex;
	unsigned int m_numberOfValues;
	ShortIntArray m_values;
	UIArray m_ratio;
	unsigned int m_WhatIFOrederIndex;

public:
	cOneWhatIfinfo();
	~cOneWhatIfinfo();
	void SetOneWhatIfName(char* name, unsigned int index, unsigned int whatIfOrderIndex);
	void SetOneWhatIfValue(char* value, unsigned int ValueIndex,  unsigned int ratio);
	void GetWhatIfFieldValues();
	short int GetValueByIndex(unsigned int index);
	unsigned  int GetRatioByIndex(unsigned int index);
	unsigned int GetNumWhatIFValues();
	unsigned int GetFieldIndex() { return m_fieldIndex; }
	const char* GetWhatIFFieldName(){return m_fieldName.c_str();}
	
};

class cMappingRule
{
private:
	UIArray m_fieldsIndexArray;
	ShortIArray m_fieldsValues;
	float m_virtualValue;
public:
	cMappingRule();
	~cMappingRule();
	void SetRule(string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue);
	bool isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues);

};


typedef cArrayList<cMappingRule*> MappingRulesArray;

class cVirtualField
{
private:
	MappingRulesArray m_mappingRulesArray;
public:
	cVirtualField();
	~cVirtualField();
	bool isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues);
	void SetSingleMappingRule(string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue);
};

class cSimilarityInfo
{
private:
	unsigned int m_fieldIndex;
	unsigned short m_weight;
	int m_minRange;
	int m_maxRange;
	bool m_isFloatVal;
	cVirtualField* m_virtualField;
	cVirtualField* m_internalFieldMapping;

	//Ohad 30.1.17
	bool m_isExtandedField;
	bool m_isPredictedField;

	bool m_isProfileOutputField;
	bool m_isProfilePriorityOutputField;

	bool m_isServiceField;
	bool m_isToAddToProfile;
	bool m_isManualprofileField;

	bool m_isPartOfProfile;

	UIArray m_dependencyFields;

public:
	cSimilarityInfo();
	//Ohad 30.1.17
	cSimilarityInfo(unsigned int fieldIndex, unsigned short weight, int minRange, int maxRange, bool isFloatVal) : m_fieldIndex(fieldIndex),
		            m_weight(weight), m_minRange(minRange), m_maxRange(maxRange), m_virtualField(NULL), m_internalFieldMapping(NULL),
					m_isFloatVal(isFloatVal){m_isExtandedField=false;m_isPredictedField = true;m_isProfileOutputField=false;
											 m_isProfilePriorityOutputField=false;m_isServiceField = false;m_isToAddToProfile=false;
											 m_isManualprofileField = false;m_isPartOfProfile = false;}
	unsigned short GetWeight();
	unsigned int GetIndex();
	int GetMinRange();
	int GetMaxRange();
	void SetVirtualField();
	bool isVirtualField();
	bool isInternalFieldMapping();
	bool isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues);
	void SetSingleMappingRule(string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue);
	bool IsInRange(int value) { return (value >= m_minRange && value <= m_maxRange); }
	void SetInternalMappingRule(float target, string_m_array& fieldNameArray,FloatArray& fieldsValues);
	bool isMatchedInternalMappingRule(float& target, FloatArray& fieldsValues);
	void SetIsFloatFlag(bool isFloatVal){m_isFloatVal = isFloatVal;}
	bool GetIsFloatVal(){return m_isFloatVal;}

	//Ohad 30.1.17
	void SetExtandedField(bool isExtanded){m_isExtandedField=isExtanded;}
	bool isExtandedField(){return m_isExtandedField;}


	void SetProfileOutputField(bool isProfileOutputField){m_isProfileOutputField=isProfileOutputField;}
	bool isProfileOutputField(){return m_isProfileOutputField;}

	
	void SetProfilePriorityOutputField(bool isProfilePriorityOutputField){m_isProfilePriorityOutputField=isProfilePriorityOutputField;}
	bool isProfilePriorityOutputField(){return m_isProfilePriorityOutputField;}

	void SetIsServiceField(bool isServiceField){m_isServiceField=isServiceField;}
	bool IsServiceField(){return m_isServiceField;}
	void SetIsToAddFieldToProfile(bool isToAddToProfile){m_isToAddToProfile=isToAddToProfile;}
	bool IsToAddFieldToProfile(){return m_isToAddToProfile;}

	void SetIsManualProfileField(bool value){m_isManualprofileField=value;}
	bool IsManualProfileField(){return m_isManualprofileField;}
	
	void SetIsPartOfProfile(bool value){m_isPartOfProfile=value;}
	bool IsPartOfProfile(){return m_isPartOfProfile;}
	

	
	

	void SetPredictedField(bool isPredictedField){m_isPredictedField=isPredictedField;}
	bool isPredictedField(){return m_isPredictedField;}

	void AddDependentField(unsigned int index){m_dependencyFields.Add(index);}
	unsigned int GEtNumOfDependentFields(){return m_dependencyFields.GetSize();}
	unsigned int GetDependentFieldIndex(unsigned int index){return *(m_dependencyFields.GetAt(index));}

	
};

class cPredictiveInfo
{
private:
	unsigned int m_fieldIndex;
	int m_minRange;
	int m_maxRange;
	cVirtualField* m_virtualField;
	cVirtualField* m_internalFieldMapping;

public:
	cPredictiveInfo();
	cPredictiveInfo(unsigned int fieldIndex, int minRange, int maxRange) : m_fieldIndex(fieldIndex),
		             m_minRange(minRange), m_maxRange(maxRange), m_virtualField(NULL), m_internalFieldMapping(NULL) {}
	~cPredictiveInfo();
	unsigned int GetIndex();
	int GetMinRange();
	int GetMaxRange();
	void SetVirtualField();
	bool isVirtualField();
	bool isInternalFieldMapping();
	bool isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues);
	void SetSingleMappingRule(string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue);
	bool IsInRange(int value) { return (value >= m_minRange && value <= m_maxRange); }
	void SetInternalMappingRule(float target, string_m_array& fieldNameArray,FloatArray& fieldsValues);
	bool isMatchedInternalMappingRule(float& target, FloatArray& fieldsValues);
};

class cResultInfoValueData
{
private:
	float m_value;
	float m_genralAvg;
	float m_specificAvg;
	string_m m_type;
	int m_similarityIndex;
public:
	cResultInfoValueData();
	~cResultInfoValueData();
	void SetDataInfo(float value, float genAvg, float specificAvg, string_m& type , int similarityIndex);
	void GetDataInfo(float& value, float& genAvg, float& specificAvg,string_m& type , int& similarityIndex );
	float GetValue(){return m_value;}

};
typedef cArrayList<cResultInfoValueData> ResultInfoDataArray;
class cResultInfo
{
private:
	unsigned int m_fieldIndex;
	int m_minRange;
	int m_maxRange;
	string_m m_type;
	int m_dependentFieldIndex;
	int m_similarityIndex;
	bool m_isDynamicCalculation;
	ResultInfoDataArray m_resultInfoDataArray;

public:
	cResultInfo();
	cResultInfo(unsigned int fieldIndex, int minRange, int maxRange, string_m type, int dependentIndex, int similarityIndex) : m_fieldIndex(fieldIndex),
		             m_minRange(minRange), m_maxRange(maxRange), m_type(type) , m_dependentFieldIndex(dependentIndex), 
					 m_similarityIndex(similarityIndex){m_isDynamicCalculation = false;}
	cResultInfo(unsigned int fieldIndex, int minRange, int maxRange, string_m type, int dependentIndex, int similarityIndex, bool isDynamicCalculation) : m_fieldIndex(fieldIndex),
		             m_minRange(minRange), m_maxRange(maxRange), m_type(type) , m_dependentFieldIndex(dependentIndex), 
					 m_similarityIndex(similarityIndex), m_isDynamicCalculation(isDynamicCalculation){}

	unsigned int GetIndex();
	int GetMinRange();
	int GetMaxRange();
	bool GetIsDynamicCalculation(){return m_isDynamicCalculation;}
	bool IsInRange(int value) { return (value >= m_minRange && value <= m_maxRange); }
	string_m& GetType(){return m_type;}
	int GetDependentIndex(){return m_dependentFieldIndex;}
	int GetSimilarityIndex() {return m_similarityIndex;}
	void SetResultDataInfo(float value, float genAvg, float specificAvg, string_m& type, int similarityIndex);
	void GetDataInfo(float value, float& genAvg, float& specificAvg,string_m& type,int& similarityIndex );
};


typedef cArrayList<cSimilarityInfo*> SimilarityInfoArray;
typedef cArrayList<cPredictiveInfo*> PredictiveInfoArray;
typedef cArrayList<cResultInfo*> ResultInfoArray;
typedef enum { NoPPI_e = '0', Difference_e = '1', DifferenceDividedToBase_e = '2'} ePPICalcType;

class cOneTargetInfo
{
private:
	string_m m_fieldName;
	SimilarityInfoArray m_similarityInfo;
	PredictiveInfoArray m_PredictiveInfo;
	ResultInfoArray m_ResultInfo;

	ResultInfoArray m_MetaDataInfo;

	unsigned int m_targetFieldIndex;
	unsigned int m_numberOFSimilarity;
	unsigned int m_numberOFPredictive;
	unsigned int m_numberOFResults;
	unsigned int m_numberOFMetaData;

	unsigned int m_numberOfMetaDataForOutput;

	int m_minRange;
	int m_maxRange;

	cDataRulesManager* m_rulesManager;

	ePPICalcType m_PPIType;
	int m_PPIDependentIndex;
	

	void MoveAllPredictiveInfo(unsigned int moveValue);

public:

	cOneTargetInfo();
	~cOneTargetInfo();

	void SetTargetFieldIndex(unsigned int index);
	void SetTargetFieldName(char* name);
	void SetVirtualField(bool isPredictive, unsigned int index);
	void SetSingleMappingRule(bool isPredictive , unsigned int index ,string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue);
	void SetInternalMappingRule(bool isPredictive , unsigned int index , string_m_array& fieldNameArray,
										  FloatArray& fieldsValues, float virtualValue);
	void SetPredictiveFieldInfo(unsigned int index, unsigned int predictiveIndex, int minRange, int maxRange);
	void SetResultFieldInfo(unsigned int index, unsigned int ResultIndex, int minRange, int maxRange);
	void SetMetaDataFieldInfo(unsigned int index,  unsigned int resultIndex, int minRange, int maxRange, char* type, int dependentIndex, 
		int referenceSimilarityIndex, bool isDynamicCalculation);
	void SetMetaDataFieldDataInfo(float value,float generalAvg,float specifcAvg,string_m& metadataType,unsigned int orderIndex,int similarityIndex);
	//Ohad 30.1.17
	void SetSimilarityFieldInfo(unsigned int index, unsigned short weight, unsigned int SimilarityIndex, int minRange, int maxRange, bool isFloatVal,
		bool isExtanded, bool isPredictedField,bool isOutputProfileField,bool IsProfilePriorityOutputField, bool isServiceField,
		unsigned int* dependentIndexArray,bool isToAddToProfile, bool isManualProfileField, bool isPartOfProfile);
	
	unsigned int GetSimilarityFieldIndexByFieldIndex(unsigned int index);

	void RemoveSimilarityInfo();
	void RemovePredictiveInfo();

	void SetPPICalcType(char* value, int dependentIndex);
	ePPICalcType GetPPICalcType(){return  m_PPIType;}
	int GetPPIDependentIndex(){return m_PPIDependentIndex;}
	
	unsigned int GetNumberOfSimilarityFields();
	unsigned short GetSumOfSimilarityWeights();
	unsigned int GetNumberOfPredictiveFields();
	unsigned int GetNumberOfResultFields();
	unsigned int GetNumberOfMetaDataFields();
	unsigned int GetNumberOfMetaDataFieldsForOutput();
	cSimilarityInfo* GetSimilarityInfoByIndex(unsigned int index);
	cPredictiveInfo* GetPredictiveInfoByIndex(unsigned int index);
	cResultInfo* GetResultInfoByIndex(unsigned int index);
	cResultInfo* GetMetaDAtaInfoByIndex(unsigned int index);
	string_m& GetTargetName() { return m_fieldName; }
	unsigned int GetTargetFieldIndex() { return m_targetFieldIndex; }
	void SetTargetFieldRanges(int minRange, int maxRange);
	int GetTargetFieldMinRange() {return m_minRange;}
	int GetTargetFieldMaxRange() {return m_maxRange;}
	bool IsInRange(int value) { return (value >= m_minRange && value <= m_maxRange); }
	void UpdatePredictiveInfo();
	void SetOneRuleCondition(unsigned int fieldIndex, string_m conditionStr, float conditionVal);
	void SetRulesWeight(unsigned int weight);
	unsigned int GetRulesWeight();
	void SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex);
	void SetOneRuleAction(string_m actionStr, float actionVal, unsigned int fieldIndex);
	void SetPopulationPercentage(unsigned int populationPercentage);
	bool IsValueMeetsRuleConditions(float* fieldsValues, unsigned int ruleIndex);
	bool IsTargetValueChancesShouldBeManipulated(float val, unsigned int ruleIndex,unsigned int actionIndex);
	float GetValueAfterRuleAction(float origValue, unsigned int ruleIndex, unsigned int actionIndex);
	bool IsLinearRule(unsigned int ruleIndex);
	unsigned int GetLinearFieldIndex(unsigned int ruleIndex, unsigned int actionIndex);
	unsigned int GetNumberOfRulesActions(unsigned int ruleIndex);
	
	void AddRule();
	unsigned int GetNumberOfRules();
	unsigned int GetOneRulePopulationPercentage(unsigned int ruleIndex);


};

class cWhatIFVariotionInfo
{
private:
	unsigned int m_variotoinIndex;
	unsigned int m_variotionRatio;

public:
	cWhatIFVariotionInfo();
	~cWhatIFVariotionInfo();
	void SetVariotionInfo(unsigned int index, unsigned int ratio);
	unsigned int GetVariotionIndex();
	unsigned int GetVariotionRatio();
};

typedef tHashTable<const char*, cOneTargetInfo*, sKeyStringFunctions> StringToTargetInfoHash;
typedef tHashTable<const char*, cOneWhatIfinfo*, sKeyStringFunctions> StringToWhatIfInfoHash;

typedef tHashTable<const char*, cWhatIFVariotionInfo*, sKeyStringFunctions> StringToWhatIfVariotionInfoHash;
typedef tHashTable<unsigned int,  const char*> UnsignedIntToStringHash;
typedef tHashTable<const char*,  const char*, sKeyStringFunctions> StringToStringHash;

#define MAX_NUMBER_OF_TARGET_FIELDS 100
#define MAX_NUMBER_OF_WHATIF_FIELDS 100
#define MAX_NUMBER_OF_SIMILARITY_FIELDS 100
#define MAX_NUMBER_OF_PREDICTIVE_FIELDS 100

#define FIELD_VALUE_TO_IGNORE -23456
#define DUMMY_FIELD_INDEX 999999
#define DUMMY_GROUP_VAL 999999


class cAllWhatIfInfo
{
private:

	string_m_array m_whatifname;
	StringToWhatIfInfoHash m_whatifInfo;
	unsigned int m_numberOFFields;
public:
	cAllWhatIfInfo();
	~cAllWhatIfInfo();
	void AddNewField();
	void AddNewName(char* name, unsigned int index, unsigned int WhatIFOrderIndex);
	void AddNewValue(char* value, unsigned int ValueIndex, unsigned int WhatIFOrderIndex, unsigned int ratio);
	unsigned int GetNumberOfFields();
	cOneWhatIfinfo* GetWhatIfFieldInfoByIndex(unsigned int index);
	void ValidateWhatIFData(unsigned int numberOfInputFields);
};






class cAllTargetsInfo
{
private:
	string_m_array m_targetsName;
	StringToTargetInfoHash m_targetInfo;

public:
	cAllTargetsInfo();
	~cAllTargetsInfo();
	void AddNewField();
	void addNewName(char* name, unsigned int index, int minRange, int maxRange, int TargetIndex);
	void AddResultField(char* name);
	void SetVirtualField(bool isPredictive, unsigned int index , int inputTargetIndex);
	void SetSingleMappingRule(bool isPredictive , unsigned int index, int inputTargetIndex ,string_m_array& fieldNameArray,
		FloatArray& fieldsValues, float virtualValue);
	void SetInternalMappingRule(bool isPredictive , unsigned int index, int inputTargetIndex ,string_m_array& fieldNameArray,
										   FloatArray& fieldsValues, float virtualValue);
	
	void AddPredictiveField(char* name,unsigned int index, unsigned int predictiveIndex,int minRange, int maxRange, int inputTargetIndex);
	void AddResultField(char* name,unsigned int index, unsigned int ResultIndex,int minRange, int maxRange);
	void AddMetaDataField(char* name,unsigned int index, unsigned int resultIndex,int minRange, int maxRange, char* type, int dependentIndex,
		int referenceSimilarityIndex, bool isDynamicCalculation);
	void AddMetaDataFieldDataInfo(float value,float generalAvg,float specifcAvg,string_m& metadataType,unsigned int orderIndex, int similarityIndex);
	//Ohad 30.1.17
	void AddSimilarityField(char* name, unsigned int index, unsigned int weight,unsigned int SimilarityIndex,int minRange, int maxRange,bool isFloatVal, 
		bool isExtanded, bool isPredictedField,bool isOutputProfileField,bool IsProfilePriorityOutputField,bool isServiceField,
		unsigned int* dependentIndexArray,bool isToAddToProfile, bool isManualProfileField, bool isPartOfProfile);
	unsigned int GetSimilarityFieldIndexByFieldIndex(unsigned int index);
	unsigned int GetNumberOfFields();
	void RemoveSimilarityInfo(unsigned int targetIndex);
	void RemovePredictiveInfo(unsigned int targetIndex);
	cOneTargetInfo* GetTargetFieldInfoByIndex(unsigned int index);
	void ValidateTargetData(unsigned int numberOfInputFields);
	void SetOneRuleCondition(unsigned int fieldIndex, string_m conditionStr, float conditionVal);
	void SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex );
	void SetRulesWeight(unsigned int weight);
	void SetOneRuleAction(string_m actionStr, float actionVal, unsigned int fieldIndex);
	void SetPopulationPercentage(unsigned int populationPercentage);
	void AddRule();

	void SetPPICalcType(char* value,int dependentIndex);
};

class cMetaDatanfo
{
private:
	float m_minRange;
	float m_maxRange;
	string_m m_color;
	string_m m_defaultOutput;
	string_m_array m_fieldsLanguages;

	string_m_array m_RangesPerFIeldsName;
	FloatArray m_MinPerField;
	FloatArray m_MaxPerField;
public:
	cMetaDatanfo();
	~cMetaDatanfo();
	void SetInfo(float minRange, float MaxRange, string_m& color);
	void SetDefaultOutput(char* str);
	void SetFieldLanguageInfo(char* info, unsigned int index);
	void GetInfo(float minRange, float MaxRange, string_m& color);
	bool IsInRange(float val, const char* fieldNAme);
	string_m& GetColor(){return m_color;}
	string_m& GetDefaultOutput(){return m_defaultOutput;}
	string_m& GetFieldLanguageInfo( int index);
	void AddSingleFieldRange(char* fieldNAme, float min, float max);
};




typedef cArrayList<cMetaDatanfo*> metaDataMenuInfoList;
class cFieldParameters
{
private:
	float m_averageValue;
	float m_minRange;
	float m_maxRange;
	unsigned int m_index;
	string_m_array m_fieldsLanguages;
public:
	cFieldParameters();
	~cFieldParameters();
	void SetFieldAverage(float val);
	void SetFieldMinRange(float val);
	void SetFieldMaxRange(float val);
	void SetFieldIndex(unsigned int val);

	float GetAverage(){return m_averageValue;}
	float GetMinRange(){return m_minRange;}
	float GetMaxRange(){return m_maxRange;}
	unsigned int GetFieldIndex(){return m_index;}
	void SetFieldLanguageInfo(char* info, unsigned int index);
	string_m& GetFieldLanguageInfo( int index);
};

class sDataStringFunction
{
	public:
	static unsigned int GetSizeOfData(string_m& data )
	{
		return strlen((const char*)data.c_str());
	}

	

	static void Delete(string_m& data) 
	{
		data.clear();
	}
};

typedef tHashTable<const char*, cFieldParameters* , sKeyStringFunctions> StringToFieldParametersHash;
typedef tHashTable<short , short*> ShortToShortHash;

typedef tHashTable<const char*, int , sKeyStringFunctions> StringToIntHash;
typedef tHashTable<const char*, int , sKeyStringFunctions> StringToShortIntHash;
typedef tHashTable<const char*, float, sKeyStringFunctions> TD_StringToFloatHash;
typedef tHashTable<const char*, string_m, sKeyStringFunctions> TD_StringToStringHash;
typedef tHashTable<const char*, string_xl, sKeyStringFunctions> TD_StringToLongStringHash;
typedef tHashTable<const char*, string_m_array*, sKeyStringFunctions> TD_StringToStringArrayHash;

typedef tHashTable<float, float> TD_FloatToFloatHash;
typedef tHashTable<float, TD_FloatToFloatHash*> TD_FloatToHashFloatToFloatHash;
typedef tHashTable<const char*, int* , sKeyStringFunctions> StringToIntPTRHash;
typedef tHashTable<const char*, double* , sKeyStringFunctions> StringToDoublePTRHash;

typedef enum { prossesing_e = 0, runtime_e = 1, test_e = 2, weightBuild_e = 3 } eRunType;



#define MAX_FIELDS_IN_FILE 1000

class cInputFileInfo
{
private:
	StringToIntHash m_nameToInputIndexHash;
	StringToIntHash m_nameToOutputIndexHash;
	UnsignedIntToStringHash m_outputIndexToNameHash;
	string_m_array m_idTag;
	string_m m_startDate;
	string_m m_startDateYear;
	string_m m_startDateMonth;
	string_m m_startDateDay;
	string_m m_endDate;
	string_m m_filePath;
	unsigned int m_numberOfFieldsPreviousFiles;
	unsigned int m_numberOfFieldsCurrentFile;
	void CalculateOutputFieldIndex();
	unsigned int m_numOffields;
public:
	cInputFileInfo();
	cInputFileInfo(unsigned int numOfFieldsPreviousFiles);
	~cInputFileInfo();
	void SetFileIDTag(string_m& id);
	void SetFileStartDate(string_m& date);
	void SetFileStartDateYear(string_m& date);
	void SetFileStartDateMonth(string_m& date);
	void SetFileStartDateDay(string_m& date);
	void SetFileEndDate(string_m& date);
	void SetNumOfFields(unsigned int num);
	void FileInputField(string_m& field,int index);
	unsigned int GetNumOffieldsInCurrentFile(){return m_numberOfFieldsCurrentFile;}
	void SetInputfilePath(string_m& path);
	void UpdateOutputstr(string_xl& outStr,string_xl& inStr,string_xl_array& inStrs , string_xl_array& outStrs );
	string_m& GetInputfilePath(){return m_filePath;}
	int GetIDIndex(unsigned int idIndex);
	int GetStartDateIndex();
	int GetStartDateYearIndex();
	int GetStartDateMonthIndex();
	int GetStartDateDayIndex();
	int GetEndDateIndex();
	int GetFieldIndexByName(string_m& name);
	char* GetfieldNameByOutputIndex(unsigned int index);
	unsigned int GetNumOfIDFields(){return m_idTag.GetSize();}
	unsigned int GetNumOffields(){return m_numOffields;}
	
};

typedef cArrayList<cInputFileInfo*> InputFileInfoArray;
#define MAX_STRING_LENGTH 200




class cQuestionnaireQuestionInfo
{
private:
	string_m m_name;
	bool m_isSingle;
	string_m_array m_values;
public:
	cQuestionnaireQuestionInfo();
	~cQuestionnaireQuestionInfo();
	void SetQuestionData(string_m& name, bool isSingle, string_m_array& values);
	void GetQuestionInfo(string_m& name, bool& isSingle, string_m_array& values);
};
typedef cArrayList<cQuestionnaireQuestionInfo*> QuestionsList;

class cQuestionnaireCategoryInfo
{
private:
	string_m m_name;
	QuestionsList m_questionList;
	
public:
	cQuestionnaireCategoryInfo();
	~cQuestionnaireCategoryInfo();
	void SetCategoryName(char* name);
	void GEtCategoryName(string_m& name){name.assign(m_name);}
	void AddQuestion(string_m& name, bool isSingle, string_m_array& values);
	unsigned int GEtNumOfQuestions(){return m_questionList.GetSize();}
	void GetSingleQuestionData(string_m& name, bool& isSingle, string_m_array& values, unsigned int qI);
};

typedef cArrayList<cQuestionnaireCategoryInfo> CategoriesList;

class cQuestionnaireInfo
{
private:
	CategoriesList m_categoriesList;
	StringToIntHash m_multiQuestionsHash;
	
public:
	cQuestionnaireInfo();
	~cQuestionnaireInfo();
	void AddCategory();
	void SetCategoryName(char* name);
	void AddQuestion(string_m& name, bool isSingle, string_m_array& values);
	unsigned int GetNumOfCatgeories(){return m_categoriesList.GetSize();}
	void GetCategoryNameByIndex(string_m& name, unsigned int index );
	unsigned int GetNumQuestionsPerCategory(unsigned int categoryIndex);
	void GetSingleQuestionInfo(string_m& name, bool& isSingle, string_m_array& values, unsigned int categoryIndex, unsigned int qIndex);
	bool isMultiField(const char* name);
};

typedef cArrayList<cTestCase*> TestCasesList;
#define GENERAL_SUB_POPULATION "GeneralSubPopulation"


class cUSerLinksInfo
{
private:
	string_m_array* m_links;
	string_m_array* m_linksPath;
	string_m_array* m_linksDirection;
public:
	cUSerLinksInfo();
	~cUSerLinksInfo();
	void AddSingleLinkInfo(string_m& link, string_m& singlePath,string_m& singleDirection);
	void GetSingleLinkInfo(string_m& link, string_m& singlePath,string_m& singleDirection, unsigned int index);
	unsigned int GetNumOfLinks(){return m_links->GetSize();}
};
typedef cArrayList<cUSerLinksInfo*> UserLinksInfoList;


class cResearchProfileInfo
{
private:
	string_m_array m_names;
	UIArray m_fieldsIndexArray;
	FloatArray m_fieldsValues;

public:
	cResearchProfileInfo();
	~cResearchProfileInfo();
	void SetResearchProfileNAme(char* profileName){m_names.Add(profileName);}
	void AddSingleFieldInfo(unsigned int fieldIndex, string_m& value);
	unsigned int GetNumOfFieldsInProfile(){return m_fieldsIndexArray.GetSize();}
	unsigned int GetSingleFieldIndexInProfile(unsigned int index){return *(m_fieldsIndexArray.GetAt(index));}
	bool isFieldValuePartOfManualProfile(unsigned int similarityIndex , short int value);

};
typedef cArrayList<cResearchProfileInfo*> ResearchProfileInfoList;
class cConfiguration
{
private:
	static cConfiguration* m_thisPtr;

	string_m m_mostUpdatedBinaryFilePath;
	unsigned int m_idFieldIndex;
	unsigned int m_numberOfThreads;
	unsigned int m_numOfFilesToSplit;
	unsigned int m_numOfEntriesPerRecord;
	cAllTargetsInfo m_targets;
	unsigned int m_midSizeArray;
	unsigned int m_smallSizeArray;
	unsigned int m_numOfWhatIfVars;
	unsigned int m_bigSizeHash;
	string_m_array m_x;
	StringToIndexInfoHash m_nameToIndexHash;
	StringToFieldParametersHash m_nameToFieldParametersHash;
	StringToIndexInfoHash m_displayNameToIndexHash;
	UnsignedIntToStringHash m_fieldIndexToFieldNameHash;
	cAllWhatIfInfo m_WhatIfInfo;	
	string_m m_inputFile;
	string_m m_workingDir;
	StringToWhatIfVariotionInfoHash m_WhatIFVariotionsHash;
	UnsignedIntToStringHash m_WhatIFVariotionsIndexHash;
	unsigned int m_numberOfDataLines;
	eLogType m_logType;
	float m_dataVariance;
	string_m_array m_data;
	tOutputBuffer m_flatFile;

	float m_mediumVarinaceRatio;
	float m_strongVarinaceRatio;
	unsigned int m_maxSimilarityFieldsInProfile;

	ShortToShortHash m_manipulatedDataValuesHash;
	float m_evolutiontestWeightAdjustment;
	float m_evolutionOverallWeightAdjustment;
	bool m_outputRegressionFlag;
	bool m_IsSpecialCareSettingCalculationMode;
	bool m_CameFromToPatientPathConvert;
	bool m_IsToLiitPerformanceToSpecificPath;
	bool m_isCalcExtVariabes;
	bool m_IsWithCancelZeroVarValueForHomog;
	bool m_IsSwitchDateStructure;
	unsigned int m_numOfCalibrationOptions;

	bool m_IsManualCalibartionSetting;
	fieldsArray m_calibrationArray;
	unsigned int m_numOfCalibrationQIs;
	string_m_array m_calibrationQIs;
	bool m_IsManualPRofileExpansion;
	bool m_isRetrospcetciveTest;
	bool m_isStudyMode;
	bool m_IsPartialSubString;
	bool m_IsNLPRelated;
	bool m_IsSubStringOneWordLimit;
	UIArray m_careSettingToConsider;
	bool m_isMultiCareSettingCollection;
	bool m_isToSwitchReadmissionQI;
	bool m_IsSingleCareSettingApplciation;
	bool m_IsAllDataForCalibration;
	string_m m_profileCalcMode;
	string_m m_studyPopulation;

	TestCasesList m_testCases;
	unsigned int m_numberOfTestCases;

	string_m_array m_testParametersNames;
	string_xl_array m_testParametersVals;

	unsigned int m_numOfIterationForRunTime;
	bool m_simplePredictionEvaluation;
	bool m_isAdjustErrorReducPerAveControlGrp;
	double m_lLevelErrorEvaluation;
	float m_coreVectorWeightChange;
	float m_multipleCoreVectorWeightChange;
	float m_percentSumAllRegression;
	float m_dynamicSeekAddConstant;
	float m_ExponentialEditDistanceScoreConst;
	float m_PercDelutionPredVars;
	float m_ExponensialConstantForPredict;
	float m_ExactMatchRatio;
	float m_PercSimilarInMidSizeArray;
	float m_PercRemoveFrequentExactMatch;
	float m_TotalPercRemoveLowPerfomaceSimVars;//not used
	float m_MaxEDForNGroupAllowed;
	float m_MaxEDForKregGroupAllowed;
	float m_AditionalEvolutionVectorValue;
	float m_LinearConstEvolution;
	float m_TooLowSimVariableThreshold;
	int m_MinSizeSimFormForPRofile;
	float m_VectorIncEvolution;
	float m_PPIMinThresold;
	float m_LongProfileMinThrshold;
	unsigned int m_predictKCountEvolution;
	unsigned int m_predictKCountCohortEvo;
	unsigned int m_PredictKEvolutionFinal;
	unsigned int m_SizeOfLPGroupMedium;
	unsigned int m_ConstDecreaseScorePreviousSample;
	unsigned int m_IncreasePredCntForKcountEvoArr;
	unsigned int m_NumOfVariablesParticipateInTriples;
	float m_PredictNConstant;
	float m_ExpoValueToDifferentiateTestGroup;
	float m_LocalGenVectorEvolution;
	float m_EXPForCutExtremePredict;
	float m_EXPForCutExtreme;
	float m_PercTestStartValue;
	float m_PercTestEndValue;
	float m_LocalGenVectorWeight;
	unsigned int m_MinSDAllowedForRegression;
	unsigned int m_MinGroupCountForEvoTest;
	unsigned int m_NumOfRandomOutputVaiationPerfomanceProcessing;
	unsigned int m_NumOfVariablesSimFormulaChangeEvolution;
	unsigned int m_NumberOfManipulationVariables;
	unsigned int m_predictKCountForMeta;
	unsigned int m_predictKCount;
	bool m_isControlGroupStableAcrossGeneration;
	bool m_isSymetricTestAll;
	bool m_IsToSetDefaultSimfromRegBeta;
	bool m_isRegressionBasedCNTRGrpAvgDelta;
	bool m_isFlaggedRequiredForLinearMetaRegression;
	bool m_isCleanFlaggedImpY;
	bool m_IsDynamicResultVal;
	bool m_isWithForcingSim;
	bool m_IsRecoverySmallToBig;
	float m_ImprovedModeThreshold;
	float m_DeclineModeThreshold;
	float m_MinDiffToBeImproved;
	bool m_isAdjustYValuesWithMean;
	bool m_debugProfileProcessing;
	bool m_AdjustPetImpOnlyAllowed;
	bool m_IsRegStatForMSDUniversal;
	bool m_IsSimplePredict;
	bool m_IsCuttingDependentExtreme;
	bool m_IsSimpleMethodOfChildPrediction;
	bool m_IsMeanOnly;
	bool m_IsWithFeatureSelection;
	bool m_IsWithADJSimForKN;//not used
	bool m_IsAddSortToKNForTest;
	bool m_IsDevidingPerfomanceToParentError;
	bool m_IsFullControlGroupEvolution;
	bool m_IsExponUpgradeForTestGroupSimilar;
	bool m_IsDivideByVarEvolution;
	bool m_IsCompareSetToZeroFormula;
	bool m_IsCompareSetToStraightFormula;
	bool m_IsExtremeCutUsingUniversal;
	bool m_IsStandardPredictiveValuesProfileBased;
	bool m_IsWithSubSetTestGroup;
	bool m_IsStartLinearContTestGrpZero;
	bool m_IsWithSemiRandomPredictiveSelection;
	bool m_IsDefaultFormulaByRegression;
	bool m_IsOnlyProfilePrediction;
	bool m_IsToShiftDepPerfByMeanEvolution;
	bool m_IsToIncludePreviousWeightsInCurrentInternReg;
	bool m_IsTestVersion;
	cControlledVariables m_controlledVarsManager;

	StringToIntHash m_specialFieldValueCombinationsHash;
	StringToIntHash m_notAllowedMissingFieldsHash;
	StringToIntHash m_treeSimilarityFieldsHash;
	unsigned int m_numberOfPercentiles;
	unsigned int m_SimilarityTreeLevels;
	unsigned int m_AnalyticsIterationJump;
	unsigned int m_AnalyticsMatchingPercent;
	unsigned int m_MaxNumberOfAllowedMissingFields;

	string_m_array m_MultiCollections;
	string_m_array m_MultiCollectionsNames;

	unsigned int m_multiCollectionsTimeOut;

	StringToIntHash m_langaugesIndexesHash;

	bool m_IsReplacedMissingWithAverage;
	bool m_IsReplacedMissingWithEmptyField;
	bool m_IsSmallToBigApp;

	bool m_isDataRulesMaipulation;
	bool m_isSwitchRulesOrder;
	bool m_isFlatDataRulesMaipulation;
	string_m m_dataRulesManipulationPath;
	string_m m_dataSpecialRulesManipulationPath;
	string_m m_applciatioName;

	unsigned int m_numofPrimaryReasonFields;

	
	unsigned int m_numberOfValuesForInteligentPrediction;
	unsigned int m_basicFieldIndex;

	unsigned int m_numberOfItemsForLongProfile;

	metaDataMenuInfoList m_metaDataMenuList;

	InputFileInfoArray m_inputFilesInfoList;

	OperatorList* m_successRateRules;
	tNumericOperator<float>* GetOperatorPTRByType(eOperatorType operatorType, float conditionVal );

	TD_FloatToHashFloatToFloatHash m_isCategorialFieldHash;

	string_m_array m_QIList;
	BoolArray m_isSmallToBigQIList;
	string_m_array m_QITimeFrames;
	string_m_array m_QIReferenceGroups;
	fieldsArray m_QIReferenceGroupsItemList;

	string_m_array m_IsIndividuaGetMatchedQIList;

	TD_StringToStringArrayHash m_QIToSubPopulationHAsh;
	TD_StringToStringArrayHash m_SubpopulationToValuesHash;

	string_m_array m_UserList;
	string_m_array m_passwordList;
	fieldsArray m_UserQIList;
	fieldsArray m_ReferenceList;
	fieldsArray m_DataItemsList;
	string_m m_dataItemsMappingFileName;

	string_m m_CMSRatingFileName;
	
	string_m_array m_primaryReasonInput;
	string_m_array m_primaryReasonMapping;

	UserLinksInfoList m_usersLinksInfo;
	

	string_m m_ResearchField;
	FloatArray m_MinResearchFieldGroupValues;
	FloatArray m_MaxResearchFieldGroupValues;
	UIArray m_GroupMapping;
	FloatArray m_GroupAverage;
	string_m_array m_groupNameList;
	string_m_array m_dependentFieldsList;
	string_m_array 	m_expectedFieldsList;
	string_m_array 	m_HistogramFieldsList;

	bool m_isSpecialGUI;
	bool m_IsShortCalculationQI;
	string_m m_QI;

	bool m_isPublicationMode;
	bool m_isResearchMode;
	bool m_isLOSMode;
	unsigned int m_AdversOR30DayLOS;
	string_m m_baselineAsse;
	UIArray m_realTimeFieldToChange;
	FloatArray m_realTimeMultipler;

	eQIMode m_QIMode;
	bool m_isHistoricalUpdate;
	char m_HistoricalFieldUpdateFieldName[MAX_STRING_LENGTH];
	bool m_IsNewQICalcualtionMode;
	bool m_IsToAddFieldsHeader;
	bool m_IsAsverseOutcomeFailue;
	unsigned int m_publciationProfieSize;
	unsigned int m_PublicationExtrnalProfileSize;
	float m_PublicationMinHomogScore;
	float m_PublicationMinUniqeScore;
	float m_ThresholdForRecoveryPotential;
	unsigned int m_MaxNumOfExtandedItems;
	unsigned int m_MaxNumOfPublicationProfiles;
	bool m_isComplexSystem;
	bool m_IsTreatSingleWordsInput;
	bool m_IsAndRelationsInRules;
	bool m_isMAxRelationsRules;
	bool m_IsNumericStrRules;
	bool m_IsDataManagerForSingleField;
	bool m_UpdateRelationsFilesBasedONSynonyms;
	unsigned int m_MaxThreadsForComplexSystem;
	string_m_array m_similarityFieldsToAdjustIndex;
	FloatArray m_similarityFieldsToAdjustWeights;
	string_m_array m_similarityFieldsToAdjustIndexQIRelated;

	string_m_array m_primaryFieldsArray;
	unsigned int m_minimumSizeOfProfile;
	unsigned int m_NumberOfAssessmentsDaysfromAddmission;

	UIArray m_effectFieldsIndexs;
	FloatArrayList m_effectFieldsValues;

	cQuestionnaireInfo m_cQuestionnaire;

	UIArray m_similarityMAppingFieldIndex;
	FloatArrayList m_similarityMappingMinValues;
	FloatArrayList m_similarityMappingMaxValues;
	UIArrayList m_similarityMappingMappedValues;

	bool m_isPRofileDashboardView;
	string_m m_profileLogic;
	string_m m_IDFieldForOutput;
	string_m m_profileLogicExpansion;
	unsigned int m_NumOfFollowUps;
	string_m m_followUpFieldName;
	string_m m_followUpNumOfDayFieldName;
	string_m m_followUpChangeFieldName;
	string_m m_liveWithName;
	string_m m_ChangeFieldName;
	string_m m_DischargeFieldName;
	string_m m_yearToAnalyze;
	ResearchProfileInfoList m_ResearchProfileInfoList;

	bool m_IsToChangeSignForReport;

	TD_StringToStringHash m_directRulesHAsh;

	TD_StringToStringHash m_revereseRulesHAsh;

	string_m_array m_callibartionCatgeories;
	DoubleArray m_callibartionCatgeoriesAvg;

	////cDataRulesDictionaryManager m_ruleManager;

	void CreateWhatIFVariotion(string_m& variotion, short int* whatIfVarArray);
	short int* CreateWhatIFVariotionValues(string_m variotion);
	void FillGeneralVariotinWeights(unsigned int* arrayWeight);
	unsigned int SumVarionWeight(unsigned int* arrayWeight);
	unsigned int GetNumOfExtraFields();
	
	void DeleteUnsignedIntToStringHash(UnsignedIntToStringHash& hash);
	void CreateSpecialFieldValueCombination(string_m& combination ,char* name, char* value);

	StringToIntHash m_termsHash;

	TD_StringToStringHash m_ICDMappaingHash;

	
public:

	cConfiguration();
	~cConfiguration();
	void SetDirectRulesHash(TD_StringToStringHash& rulesHash);
	bool isToCovertDirectName(string_m& output, string_m& nameToCheck);
	void FillGenralTErmsHash();
	bool IsGeneralTerm(string_m str);

	void SetReverseRulesHash(TD_StringToStringHash& rulesHash);
	bool isToCovertName(string_m& output, string_m& nameToCheck);

	//cDataRulesDictionaryManager& GetRuleManager() { return m_ruleManager;};
	

	// Need to add default values to all bellow parameters
	unsigned int m_numOfTopSimilarForEditScore;
	unsigned int m_Kcount;
	unsigned int m_KcontrolCount;
	unsigned int m_Ncount;
	unsigned int m_maxCountPerformanceList;
	unsigned short m_sumOfSimilarityWeights;
	unsigned int m_numOfSimilarityVars;

	unsigned int GetNumOfThreads() { return m_numberOfThreads; }
	unsigned int GetNumOFFilesToSplit(){return m_numOfFilesToSplit;}
	unsigned int GetNumOFEntiresPerRecord(){return m_numOfEntriesPerRecord;}
	unsigned int GetIDFieldIndex() { return m_idFieldIndex; }
	unsigned int GetBigSizeHash() {return m_bigSizeHash;}
	unsigned int GetMidSizeArray(){return m_midSizeArray;}
	unsigned int GetSmallSizeArray(){return m_smallSizeArray;}
	unsigned int GetNumOfWhatIfVars(){return m_numOfWhatIfVars;}

	bool isComplexSystem(){return m_isComplexSystem;}
	void SetIsComplexSystem(bool isComplex){m_isComplexSystem = isComplex;}

	bool IsTreatSingleWordsInput(){return m_IsTreatSingleWordsInput;}
	void SetIsTreatSingleWordsInput(bool value){m_IsTreatSingleWordsInput = value;}

	bool IsAndRelationsInRules(){return m_IsAndRelationsInRules;}
	void SetIsAndRelationsInRules(bool value){m_IsAndRelationsInRules = value;}

	bool IsMAxRelationsRules(){return m_isMAxRelationsRules;}
	void SetIsMAxRelationsRules(bool value){m_isMAxRelationsRules = value;}
	

	bool IsNumericStrRules(){return m_IsNumericStrRules;}
	void SetIsNumericStrRules(bool value){m_IsNumericStrRules = value;}

	
	
	bool IsDataManagerForSingleField(){return m_IsDataManagerForSingleField;}
	void SetIsDataManagerForSingleField(bool value){m_IsDataManagerForSingleField = value;}

	bool IsUpdateRelationsFilesBasedONSynonyms(){return m_UpdateRelationsFilesBasedONSynonyms;}
	void SetUpdateRelationsFilesBasedONSynonyms(bool value){m_UpdateRelationsFilesBasedONSynonyms = value;}
	
	
	unsigned int  GetMaxThreadsForComplexSystem(){return m_MaxThreadsForComplexSystem;}
	void SetMaxThreadsForComplexSystem(unsigned int MaxThreadsForComplexSystem){m_MaxThreadsForComplexSystem = MaxThreadsForComplexSystem;}
	void SetMinimumProfileSize(unsigned int value){m_minimumSizeOfProfile = value;}
	unsigned int GEtMinimumSizeOfProfile(){return m_minimumSizeOfProfile;}

	void SetNumberOfAssessmentsDaysfromAddmission(unsigned int value){m_NumberOfAssessmentsDaysfromAddmission = value;}
	unsigned int GEtNumberOfAssessmentsDaysfromAddmission(){return m_NumberOfAssessmentsDaysfromAddmission;}

	
	
	void AddSimialrityFieldToAdjust(char* fieldName, float weight,string_m& QIList);
	void GetSingleSimialrityFiledToAdjustData(unsigned int& index, float& weight,unsigned int fieldIndex);
	unsigned int GetNutOfSimilarityFieldsToAdjust(){return m_similarityFieldsToAdjustIndex.GetSize();}

	void GetSingleSimialrityFiledToAdjustDataPerQI(unsigned int& index, float& weight,unsigned int fieldIndex, string_m& QI);
	unsigned int GetNutOfSimilarityFieldsToAdjustPerQI(string_m& QI);
	
	void SetMidSizeArray(unsigned int size);
	void SetSmallSizeArray(unsigned int size);
	//field single field info to hash contains mapping field name to index
	void FillFieldInfo (char* name, unsigned int index);
	void FillFieldAverage(char* name, float value);
	void FillFieldMinRange(char* name, float value);
	void FillFieldMaxRange(char* name, float value);
	void FillFieldLanguageSpecification(string_m& name, char*  lanugaeSpecification, string_m& language);
	void RemoveChar(char* inout, const char ch, unsigned int& numOfRemovedChars);
	void SwitchToParentCategory(string_m& currName ,const char* name);
	void SwitchToParentCategoryEPIC(string_m& currName ,const char* name);
	void NormelizeValue(string_m& value);
	void GetfieldDisplayByLanguage(char* displayName, const char* name , string_m& language);
	void GetFieldNameByDisplayName(char* name, char* displayName);
	unsigned int GetSimilarityFieldIndexByFieldName(char* name);
	bool IsMAtchGRuopDefintion(char* str ,ShortIArray&  realSimilarity, UIArray& OmitFieldsIndex ,StringToIntPTRHash& highRiskProfilesHAsh, StringToIntPTRHash& lowRiskProfileHAsh );
	int CalulateInfectionRisk(ShortIArray&  realSimilarity);
	bool IsMatchICDMapping(string_m& outputField , char* fieldStrValues, unsigned int pI);
	bool IsCOVIDICDMapping(char* fieldStrValues);
	void SetICDMapping();
	void ConvertStrToLowerCase(char* inout);
	bool isPartOfInfectionGroup(ShortIArray&  realSimilarity, unsigned int index);
	bool ISMatchRiskProfile(ShortIArray&  realSimilarity , int* dataArray, bool isHigh);
	bool IsPartOFRiskGroup(StringToIntPTRHash& hashToCheck ,StringToIntPTRHash& oppositeHash , ShortIArray&  realSimilarity, bool isHigh);
	int CalcEPICRiskValue(ShortIArray&  realSimilarity );
	bool IsPartOfFieldsToOmit(unsigned int index , UIArray& OmitFieldsIndex);
	bool IsNonPrimaryReasonDEfintion(char* str);
	void GetPrimaryFieldNameFromInput(string_m& output, string_m& input);
	int GetPrimaryReasonRiskGroup(string_m& input);
	int GetPrimaryReasonRiskGroupDetailedList(string_m& input);
	void SetPrimaryReasonMapping(char* input);

	// set the ID field index - need to add error handling
	void SetIDField (char* name);
	// add a new target field, should be called when targer tag is closed (</Target>)
	void AddTargetField();
	//add a new target name
	void AddTargetName(char* name, int minRange, int maxRange, int TargetIndex = -1);
	//add a new PRedictiv field
	void AddPredictiveField(char* name, unsigned int predictiveIndex,int minRange, int maxRange, int targetIndex = -1);
	//add a new Result field
	void SetVirtualField(bool isPredictive, unsigned int index, int targetIndex = -1);
	void SetSingleMappingRule(bool isPredictive, unsigned int index , string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue , 
		                      int targetIndex = -1);
	void SetInternalMappingRule(bool isPredictive , unsigned int index,  string_m_array& fieldNameArray,
										  FloatArray& fieldsValues, float virtualValue, int targetIndex = -1);
	void AddResultField(char* name, unsigned int resultIndex,int minRange, int maxRange, bool isConfigInput);
	void AddMetaDataField(char* name, unsigned int resultIndex, int minRange, int maxRange, bool isConfigInput, char* type, int dependentIndex,
		int referenceSimilarityIndex,  bool isDynamicCalculation);
	void AddMetaDataFieldDataInfo(float value,float generalAvg,float specifcAvg,string_m& metadataType,unsigned int orderIndex, int similarityIndex);
	void AddMetaDataFieldValueInfo(char* name, unsigned int resultIndex, float specificAvg, float GeneralAvg,char* type,  int dependentIndex,
									int referenceSimilarityIndex);
	//add a new similarity field
	//Ohad 30.1.17
	void AddSimilarityField(char* name, unsigned int weight, unsigned int SimilarityIndex,int minRange, int maxRange,bool isFloatVal, bool isExtanded,
		bool isPredictedField, bool isOutputProfileField,bool IsProfilePriorityOutputField, bool isServiceField,unsigned int* dependentIndexArray,
		bool isToAddToProfile, bool isManualProfileField,bool isPartOfProfile);
	// add a new whatif field, should be called only when the tag whatif is closed
	void AddWhatIfField();

	unsigned int GetNumOfServicesFields();
	unsigned int GetServiceFieldSimialrityIndex(unsigned int serviceIndex);

	bool IsToAddFieldToProfile(unsigned int similarityIndex);
	bool IsManualProfileField(unsigned int similarityIndex);
	
	void RemoveSimilarityInfo(unsigned int targetIndex);
	void RemovePredictiveInfo(unsigned int targetIndex);
	void UpdatePredictiveInfo();
	void FillSimilarityAndPredictiveFields(char* input , char* type);

	void AddWhatIfName(char* name,  unsigned int WhatIFOrderIndex);
	void AddWhatIfValue(char* value, unsigned int ValueIndex, unsigned int WhatIFOrderIndex, unsigned int ratio);

	void SetNumberOfThreads(unsigned int numberOfThreads);
	void SetNumOfFilesToSplit(unsigned int num);
	void SetNumOfEntiresPerRecord(unsigned int num);
	//return the number of fields in the input data file
	unsigned int GetNumOfInputFields();
	

	//how many target fields exits
	unsigned int GetNumberOfTargetFields();
	//get target field infromation by indicator (firts, second,...)
	cOneTargetInfo* GetTargetFieldInfoByIndex(unsigned int index);
	//how many WhatIf fields
	unsigned int GetNumberOfWhatIfFields();
	cOneWhatIfinfo* GetWhatIfInfoByIndex(unsigned int index);

	unsigned int GetNumOfExtentionFields();
	// TODO
	void SetInputFileName(char* fileName);
	void SetWorkDir(char* workDir);
	void SetGeneralParameterValue(unsigned int value, eGeneralInfoType type);
	const string_m& GetInputFileName() { return m_inputFile; }
	string_m& GetMostUpdatedBinaryPath() { return m_mostUpdatedBinaryFilePath; }
	const string_m& GetWorkingDirectory() { return m_workingDir; }
	unsigned int GetNumOfSimilarityVars(unsigned int targetFieldIndex);
	unsigned short GetSumOfSimilarityWeights(unsigned int targetFieldIndex);
	unsigned int GetNumOfPredictiveVars(unsigned int targetFieldIndex);
	unsigned int GetNumOfResultVars(unsigned int targetFieldIndex);
	unsigned int GetGeneralParameterVlaue(eGeneralInfoType type);	
	void CreateVariotionList(unsigned int WhatIfFieldNum, short int* valueArray, unsigned int& variotionIndex);
	void CreateVariotionListForSingleWhatIFField();

	void APplyOutputDependencyRules(bool* isProfileField);
	
	ePPICalcType GetPPICalcType(unsigned int targetFieldIndex);
	int GetPPIDependentIndex(unsigned int targetFieldIndex);
	void SetPPICalcType(char* value, int dependentIndex);
	
	unsigned int GetNumOfWhatIfVariations();
	unsigned int GetWhatIfVariationIndex(short int* whatIfVarArray);
	short int* GetWhatIfVariationByIndex(unsigned int variationIndex);
	cWhatIFVariotionInfo* GetWhatIFVariotionInfoByIndex(unsigned int variationIndex);
	void FillWhatIfVariationWeight(float* whatifVariationWeights, unsigned int* whatIfArraysCount);



	unsigned int GetNumIDFieldIndex();
	unsigned int GetPredectibilityScoreIndex();
	unsigned int GetNumOfFieldsIncludingExtra();
	unsigned int GetStartExtraFieldsIndex() { return m_nameToIndexHash.GetCount(); }

	void SetNumberOfDataLines(unsigned int value);
	unsigned int GetNumberOfDataLines(){return m_numberOfDataLines;}

	void ValidateTargetData();
	void ValidateWhatIFData();
	void OrgenizeConfigurationData();

	eLogType GetLogType() { return m_logType; }
	void SetLogType(char* type);
	

	void SetOneRuleCondition(string_m fieldName, string_m conditionStr, float conditionVal);
	void SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex );
	void SetOneRuleAction(string_m actionStr, float actionVal, string_m fieldName);
	void SetPopulationPercentage(unsigned int populationPercentage);
	void AddRule();

	void SetRulesWeight(unsigned int weight);

	const char* GetFieldNameByIndex(unsigned int fieldIndex);
	bool AddExtansionFieldToProfile(char* name,unsigned int similarityFieldIndex);
	bool IsPriorityProfileField(unsigned int similarityFieldIndex);
	void IsSwitchValuesForProfileOutput(string_m& outputFieldsNames ,string_m& outputFieldsValues , char* displayName,  string_m& outputVal ,
		string_m&  language,unsigned int profileFieldIndex);
	const char* GetFieldNameBySimilarityIndex(unsigned int SimilarityIndex);
	bool IsVariableJFromCatHEART( int varIndex);//2 5 20

	//2 21 20  - copy from list in "2 21 20 list"
	bool IsVariableJFromCirculatory(int &numOfCirVars, int j);
	bool IsVariableJFromEndocrineDisorders(int &numOfEndoVars, int j);
	bool IsVariableJFromnMentalDisorders(int j);
	bool IsVariableJFromnInfections(int j );
	bool IsVariableJFromNerologicalDisorders(int &numOfNeourVars, int j);
	bool IsVariableJFromPulmonaryDisorders(int &numOfPulmonaryVars, int j);
	bool IsVariableJFromMusculatorySystems( int j);
	bool IsVariableJFromBMI( int j);

	//2 21 20 new
	bool IsOtherComorbidityField(unsigned int j);

	bool IsComorbidityField(unsigned int SimilarityIndex);
	unsigned int GetFieldIndexByTypeAndIndex(char* type , unsigned int targetIndex , unsigned int index);
	void SetDataVariance(float variance);
	float GetVariance() {return m_dataVariance;}
	unsigned int GetFieldIndexByName(char* name);
	float GetFieldAverageByName(char* name);
	float GetFieldMaxByName(char* name);
	float GetFieldMinByName(char* name);
	void FillFieldValueForFlatFile(char* value, char* fieldName);
	void AddPersonToFlatFile();
	void SetInfoForFlatCOnversion(string_m& fileName);
	void CloseFlatFile();

	void SetMediumVarianceRatio(float ratio);
	void SetStrongVarianceRatio(float ratio);
	float GetMediumVarianceRatio (){return m_mediumVarinaceRatio;}
	float GetStrongVarianceRatio(){return m_strongVarinaceRatio;}

	
	void SetMaxNumberOfSimilarityFieldsInProfile(unsigned int value);
	void SetNumberOfPercentilesForOutput(unsigned int value);
	unsigned int GetMaxNumberOfSimilarityFieldsInProfile (){return m_maxSimilarityFieldsInProfile;}
	unsigned int GetNumberOfPercentilesForOutput (){return m_numberOfPercentiles;}
	
	void SetDataManipulatedCombination(float source, float target);
	bool isToManipulateDataValue(float source , float& target);

	float GetEvolutionTestWeightAdjustmet(){return m_evolutiontestWeightAdjustment;}
	float GetEvolutionOverallWeightAdjustmet(){return m_evolutionOverallWeightAdjustment;}

	void SetEvolutionTestWeightAdjustmet(float val);
	void SetEvolutionOverallWeightAdjustmet(float val);

	bool IsToOutputTraditionalRegression(){return m_outputRegressionFlag; }
	void SetOutputRegressionFlag(bool flag);

	bool IsSpecialCareSettingCalculationMode(){return m_IsSpecialCareSettingCalculationMode;}
	void SetIsSpecialCareSettingCalculationMode(bool value){m_IsSpecialCareSettingCalculationMode = value;}

	bool IsCameFromToPatientPathConvert(){return m_CameFromToPatientPathConvert;}
	void SetCameFromToPatientPathConvert(bool value){m_CameFromToPatientPathConvert = value;}

	bool IsToLiitPerformanceToSpecificPath(){return m_IsToLiitPerformanceToSpecificPath;}
	void SetIsToLiitPerformanceToSpecificPath(bool value){m_IsToLiitPerformanceToSpecificPath = value;}

	bool IsCalculateExtandedVaribles(){return m_isCalcExtVariabes;}
	void SetIsCalculateExtandedVaribles(bool value){m_isCalcExtVariabes = value;}

	bool IsWithCancelZeroVarValueForHomog(){return m_IsWithCancelZeroVarValueForHomog;}
	void SetIsWithCancelZeroVarValueForHomog(bool value){m_IsWithCancelZeroVarValueForHomog = value;}

	bool IsSwitchDateStructure(){return m_IsSwitchDateStructure;}
	void SetIsSwitchDateStructure(bool value){m_IsSwitchDateStructure = value;}

	

	void AddCalibrationVal(char* str);

	void CloseCalibrationOption(){m_numOfCalibrationOptions++;}
	unsigned int GetNumOfCalibrationVals(){return m_numOfCalibrationOptions ;}
	unsigned int GetNumOfCalibrationQIs(){return m_numOfCalibrationQIs ;}
	void GetCalbrationNAmeByIndex(string_m& str, unsigned int index);
	bool IsNAmeMatchCalibrationName(unsigned int& index, string_m& str);
	void GetCalbrationQIByIndex(string_m& str, unsigned int index);
	void GetCalbrationOptionByIndex(string_m_array& strArray, unsigned int index);

	bool IsManualCalibartionSetting(){return m_IsManualCalibartionSetting;}
	void SetIsManualCalibartionSetting(bool value){m_IsManualCalibartionSetting = value;}
	
	unsigned int GetNumberOfClaibrationCategories();
	void GetCalibartionCategoryByIndex(string_m& category, unsigned int index);
	double GetCalibartionCategoryAvgByIndex( unsigned int index);

	bool IsManualPRofileExpansion(){return m_IsManualPRofileExpansion;}
	void SetIsManualPRofileExpansion(bool value){m_IsManualPRofileExpansion = value;}

	bool IsRetrosepctiveTest(){return m_isRetrospcetciveTest;}
	void SetIsRetrosepctiveTest(bool value){m_isRetrospcetciveTest = value;}

	bool IsStudyMode(){return m_isStudyMode;}
	void SetIsStudyMode(bool value){m_isStudyMode = value;}
	

	bool IsPartialSubString(){return m_IsPartialSubString;}
	void SetIsPartialSubString(bool value){m_IsPartialSubString = value;}

	bool IsNLPRelated(){return m_IsNLPRelated;}
	void SetIsNLPRelated(bool value){m_IsNLPRelated = value;}
	

	bool IsSubStringOneWordLimit(){return m_IsSubStringOneWordLimit;}
	void SetIsSubStringOneWordLimit(bool value){m_IsSubStringOneWordLimit = value;}

	

	
	unsigned int GetNumOfCareSettingToConsider(){return m_careSettingToConsider.GetSize();}
	unsigned int GetCareSettingByIndex(int index){return *(m_careSettingToConsider.GetAt(index));}
	void AddCareSettingToConsider(char* careSetting);
	

	bool IsMultiCareSettingCollection(){return m_isMultiCareSettingCollection;}
	void SetIsMultiCareSettingCollection(bool value){m_isMultiCareSettingCollection = value;}

	bool IsToSwitchReadmissionQI(){return m_isToSwitchReadmissionQI;}
	void SetIsToSwitchReadmissionQI(bool value){m_isToSwitchReadmissionQI = value;}

	bool IsSingleCareSettingApplciation(){return m_IsSingleCareSettingApplciation;}
	void SetIsSingleCareSettingApplciation(bool value){m_IsSingleCareSettingApplciation = value;}

	bool IsAllDataForCalibration(){return m_IsAllDataForCalibration;}
	void SetIsAllDataForCalibration(bool value){m_IsAllDataForCalibration = value;}

	

	const char* GEtStudyPopulationDefinition(){return m_studyPopulation.c_str();}
	void SetStudyPopulationDefinition(char* str){m_studyPopulation.assign(str);}
	

	const char* GetProfileCalculationMode(){return m_profileCalcMode.c_str();}

	void SetProfileCalculationMode(char* mode);

	void SetTestCaseID(unsigned int id);
	void SetTestCaseParameter(string_m name, string_m value);
	unsigned int GetNumberOfTestCases();
	cTestCase* GetASingleTestCAseByIndex(unsigned int index);

	void SetConfigParameter(string_m& name, string_m value);
	void SetExpoTestParameter(string_m& name, string_xl& value);
	void ExpandTestCases(unsigned int index, unsigned int& caseIndex, string_m_array& caseValuesList);

	int GetNumWords(char* array, char delimiter);
	int GetWord(char* out, const char* input, int inputStartIndex, char delimiter);

	unsigned int GetNumOFRunTimeIteration(){return m_numOfIterationForRunTime;}
	void SetNumberOFRUNTIMEIteration(unsigned int value);

	unsigned int GetNumberOfValuesForInteligentPrediction(){return m_numberOfValuesForInteligentPrediction;}
	void SetNumberOfValuesForInteligentPrediction(unsigned int value);

	unsigned int GetBasicFieldIndex(){return m_basicFieldIndex;}
	void SetBasicFieldIndex(unsigned int value);

	unsigned int GetNumberOfItemsForLongProfile(){return m_numberOfItemsForLongProfile;}
	void SetNumberOfItemsForLongProfile(unsigned int value);
	


	void SetSimplePredictionEvaluation(bool value);
	bool GetSimplePredictionEvaluation(){return m_simplePredictionEvaluation;}

	void SetIsAdjustErrorReducPerAveControlGrp(bool value);
	bool GetIsAdjustErrorReducPerAveControlGrp(){return m_isAdjustErrorReducPerAveControlGrp;}

	void SetIsProfileDashboardView(bool value);
	bool IsProfileDashboardView(){return m_isPRofileDashboardView;}

	void SetLLevelErrorEvaluation(double value);
	double GetLLevelErrorEvaluation(){return m_lLevelErrorEvaluation;}

	void SetCoreVectorWeightChange(float value);
	float GetCoreVectorWeightChange(){return m_coreVectorWeightChange;}

	void SetMultipleCoreVectorWeightChange(float value);
	float GetMultipleCoreVectorWeightChange(){return m_multipleCoreVectorWeightChange;}

	void SetPercentSumAllRegression(float value);
	float GetPercentSumAllRegression(){return m_percentSumAllRegression;}

	

	void SetDynamicSeekAddConstant(float value);
	float GetDynamicSeekAddConstant(){return m_dynamicSeekAddConstant;}

  
	void SetExponentialEditDistanceScoreConst(float value);
	float GetExponentialEditDistanceScoreConst(){return m_ExponentialEditDistanceScoreConst;}
	
	void SetPercDelutionPredVars(float value);
	float GetPercDelutionPredVars(){return m_PercDelutionPredVars;}
	
	void SetExponensialConstantForPredict(float value);
	float GetExponensialConstantForPredict(){return m_ExponensialConstantForPredict;}

	

	void SetExactMatchRatio(float value);
	float GetExactMatchRatio(){return m_ExactMatchRatio;}

	void SetPercSimilarInMidSizeArray(float value);
	float GetPercSimilarInMidSizeArray(){return m_PercSimilarInMidSizeArray;}

	void SetPercRemoveFrequentExactMatch(float value);
	float GetPercRemoveFrequentExactMatch(){return m_PercRemoveFrequentExactMatch;}

	void SetTotalPercRemoveLowPerfomaceSimVars(float value);
	float GetTotalPercRemoveLowPerfomaceSimVars(){return m_TotalPercRemoveLowPerfomaceSimVars;}
	
	void SetMaxEDForNGroupAllowed(float value);
	float GetMaxEDForNGroupAllowed(){return m_MaxEDForNGroupAllowed;}

	void SetMaxEDForKregGroupAllowed(float value);
	float GetMaxEDForKregGroupAllowed(){return m_MaxEDForKregGroupAllowed;}

	void SetAditionalEvolutionVectorValue(float value);
	float GetAditionalEvolutionVectorValue(){return m_AditionalEvolutionVectorValue;}


	void SetLinearConstEvolution(float value);
	float GetLinearConstEvolution(){return m_LinearConstEvolution;}

	void SetTooLowSimVariableThreshold(float value);
	float GetTooLowSimVariableThreshold(){return m_TooLowSimVariableThreshold;}

	void SetMinSizeSimFormForPRofile(int value);
	int GetMinSizeSimFormForPRofile(){return m_MinSizeSimFormForPRofile;}
	
	
	void SetVectorIncEvolution(float value);
	float GetVectorIncEvolution(){return m_VectorIncEvolution;}

	
	


	
	void SetPPIMinThresold(float value);
	float GetPPIMinThresold(){return m_PPIMinThresold;}

	void SetLongProfileMinThrshold(float value);
	float GetLongProfileMinThrshold(){return m_LongProfileMinThrshold;}


	unsigned int GetPredictKCountEvolution(){return m_predictKCountEvolution;}
	unsigned int GetPredictKCountForMeta();//{return m_predictKCountForMeta;}
	unsigned int GetPredictKCountCohortEvo(){return m_predictKCountCohortEvo;}
	void SetPredictKCountForMeta(unsigned int value);
	void SetPredictKCountEvolution(unsigned int value);
	void SetPredictKCountCohortEvo(unsigned int value);
	
	unsigned int GetPredictKCount(){return m_predictKCount;}
	void SetPredictKCount(unsigned int value);

	unsigned int GetPredictKEvolutionFinal(){return m_PredictKEvolutionFinal;}
	void SetPredictKEvolutionFinal(unsigned int value);

	unsigned int GetSizeOfLPGroupMedium(){return m_SizeOfLPGroupMedium;}
	void SetSizeOfLPGroupMedium(unsigned int value);
	
	unsigned int GetConstDecreaseScorePreviousSample(){return m_ConstDecreaseScorePreviousSample;}
	void SetConstDecreaseScorePreviousSample(unsigned int value);

	unsigned int GetIncreasePredCntForKcountEvoArr(){return m_IncreasePredCntForKcountEvoArr;}
	void SetIncreasePredCntForKcountEvoArr(unsigned int value);

	unsigned int GetNumOfVariablesParticipateInTriples(){return m_NumOfVariablesParticipateInTriples;}
	void SetNumOfVariablesParticipateInTriples(unsigned int value);
	
	

	float GetPredictNConstant(){return m_PredictNConstant;}
	void SetPredictNConstant(float value);

	float GetExpoValueToDifferentiateTestGroup(){return m_ExpoValueToDifferentiateTestGroup;}
	void SetExpoValueToDifferentiateTestGroup(float value);

	float GetLocalGenVectorEvolution(){return m_LocalGenVectorEvolution;}
	void SetLocalGenVectorEvolution(float value);

	float GetEXPForCutExtremePredict(){return m_EXPForCutExtremePredict;}
	void SetEXPForCutExtremePredict(float value);

	float GetEXPForCutExtreme(){return m_EXPForCutExtreme;}
	void SetEXPForCutExtreme(float value);

	float GetPercTestStartValue(){return m_PercTestStartValue;}
	void SetPercTestStartValue(float value);
	
	float GetPercTestEndValue(){return m_PercTestEndValue;}
	void SetPercTestEndValue(float value);
	
	float GetLocalGenVectorWeight(){return m_LocalGenVectorWeight;}
	void SetLocalGenVectorWeight(float value);

	
	unsigned int GetMinSDAllowedForRegression(){return m_MinSDAllowedForRegression;}
	void SetMinSDAllowedForRegression(unsigned int value);
	
	
	void SetIsControlGroupStableAcrossGeneration(bool value);
	bool GetIsControlGroupStableAcrossGeneration(){return m_isControlGroupStableAcrossGeneration;}

	void SetIsSymetricTestAll(bool value);
	bool GetIsSymetricTestAll(){return m_isSymetricTestAll;}
	
	void SetIsToSetDefaultSimfromRegBeta(bool value);
	bool GetIsToSetDefaultSimfromRegBeta(){return m_IsToSetDefaultSimfromRegBeta;}


	void SetIsRegressionBasedCNTRGrpAvgDelta(bool value);
	bool GetIsRegressionBasedCNTRGrpAvgDelta(){return m_isRegressionBasedCNTRGrpAvgDelta;}

	void SetIsFlaggedRequiredForLinearMetaRegression(bool value);
	bool GetIsFlaggedRequiredForLinearMetaRegression(){return m_isFlaggedRequiredForLinearMetaRegression;}

	void SetIsCleanFlaggedImpY(bool value);
	bool GetIsCleanFlaggedImpY(){return m_isCleanFlaggedImpY;}

	void SetIsDynamicResultVal(bool value);
	bool GetIsDynamicResultVal(){return m_IsDynamicResultVal;}
	void SetIsWithForcingSim(bool value);
	bool GetIsWithForcingSim(){return m_isWithForcingSim;}

	void SetIsRecoverySmallToBig(bool value){m_IsRecoverySmallToBig = value;}
	bool GetIsRecoverySmallToBig(){return m_IsRecoverySmallToBig;}
	
	void SetImprovedModeThreshold(float value){m_ImprovedModeThreshold = value;}
	float GetImprovedModeThreshold(){return m_ImprovedModeThreshold;}
	
	void SetDeclineModeThreshold(float value){m_DeclineModeThreshold = value;}
	float GetDeclineModeThreshold(){return m_DeclineModeThreshold;}

	void SetMinDiffToBeImproved(float value){m_MinDiffToBeImproved = value;}
	float GetMinDiffToBeImproved(){return m_MinDiffToBeImproved;}

	void SetIsAdjustYValuesWithMean(bool value);
	bool GetIsAdjustYValuesWithMean(){return m_isAdjustYValuesWithMean;}

	void SetAdjustPetImpOnlyAllowed(bool value);
	bool GetAdjustPetImpOnlyAllowed(){return m_AdjustPetImpOnlyAllowed;}

	void SetIsRegStatForMSDUniversal(bool value);
	bool GetIsRegStatForMSDUniversal(){return m_IsRegStatForMSDUniversal;}

	void SetIsSimplePredict(bool value);
	bool GetIsSimplePredict(){return m_IsSimplePredict;}

	void SetIsCuttingDependentExtreme(bool value);
	bool GetIsCuttingDependentExtreme(){return m_IsCuttingDependentExtreme;}
	
	void SetIsSimpleMethodOfChildPrediction(bool value);
	bool GetIsSimpleMethodOfChildPrediction(){return m_IsSimpleMethodOfChildPrediction;}

	void SetIsMeanOnly(bool value);
	bool GetIsMeanOnly(){return m_IsMeanOnly;}

	void SetIsWithFeatureSelection(bool value);
	bool GetIsWithFeatureSelection(){return m_IsWithFeatureSelection;}
	
	
	void SetIsWithADJSimForKN(bool value);
	bool GetIsWithADJSimForKN(){return m_IsWithADJSimForKN;}

	void SetIsAddSortToKNForTest(bool value);
	bool GetIsAddSortToKNForTest(){return m_IsAddSortToKNForTest;}

	void SetIsDevidingPerfomanceToParentError(bool value);
	bool GetIsDevidingPerfomanceToParentError(){return m_IsDevidingPerfomanceToParentError;}

	void SetIsFullControlGroupEvolution(bool value);
	bool GetIsFullControlGroupEvolution(){return m_IsFullControlGroupEvolution;}

	void SetIsExponUpgradeForTestGroupSimilar(bool value);
	bool GetIsExponUpgradeForTestGroupSimilar(){return m_IsExponUpgradeForTestGroupSimilar;}
	
	void SetIsDivideByVarEvolution(bool value);
	bool GetIsDivideByVarEvolution(){return m_IsDivideByVarEvolution;}

	void SetIsCompareSetToZeroFormula(bool value);
	bool GetIsCompareSetToZeroFormula(){return m_IsCompareSetToZeroFormula;}

	void SetIsCompareSetToStraightFormula(bool value);
	bool GetIsCompareSetToStraightFormula(){return m_IsCompareSetToStraightFormula;}

	void SetIsExtremeCutUsingUniversal(bool value);
	bool GetIsExtremeCutUsingUniversal(){return m_IsExtremeCutUsingUniversal;}
	
	void SetIsStandardPredictiveValuesProfileBased(bool value);
	bool GetIsStandardPredictiveValuesProfileBased(){return m_IsStandardPredictiveValuesProfileBased;}
	
	
	void SetIsWithSubSetTestGroup(bool value);
	bool GetIsWithSubSetTestGroup(){return m_IsWithSubSetTestGroup;}

	void SetIsStartLinearContTestGrpZero(bool value);
	bool GetIsStartLinearContTestGrpZero(){return m_IsStartLinearContTestGrpZero;}

	void SetIsWithSemiRandomPredictiveSelection(bool value);
	bool GetIsWithSemiRandomPredictiveSelection(){return m_IsWithSemiRandomPredictiveSelection;}

	void SetIsDefaultFormulaByRegression(bool value);
	bool GetIsDefaultFormulaByRegression(){return m_IsDefaultFormulaByRegression;}

	
	void SetIsOnlyProfilePrediction(bool value);
	bool GetIsOnlyProfilePrediction(){return m_IsOnlyProfilePrediction;}

	void SetIsToShiftDepPerfByMeanEvolution(bool value);
	bool GetIsToShiftDepPerfByMeanEvolution(){return m_IsToShiftDepPerfByMeanEvolution;}

	void SetIsToIncludePreviousWeightsInCurrentInternReg(bool value);
	bool GetIsToIncludePreviousWeightsInCurrentInternReg(){return m_IsToIncludePreviousWeightsInCurrentInternReg;}

	
	void SetIsTestVersion(bool value);
	bool GetIsIsTestVersion(){return m_IsTestVersion;}
	
	unsigned int GetMinGroupCountForEvoTest(){return m_MinGroupCountForEvoTest;}
	void SetMinGroupCountForEvoTest(unsigned int value);

	unsigned int GetNumOfRandomOutputVaiationPerfomanceProcessing(){return m_NumOfRandomOutputVaiationPerfomanceProcessing;}
	void SetNumOfRandomOutputVaiationPerfomanceProcessing(unsigned int value);

	unsigned int GetNumOfVariablesSimFormulaChangeEvolution(){return m_NumOfVariablesSimFormulaChangeEvolution;}
	void SetNumOfVariablesSimFormulaChangeEvolution(unsigned int value);

	unsigned int GetNumberOfManipulationVariables(){return m_NumberOfManipulationVariables;}
	void SetNumberOfManipulationVariables(unsigned int value);
	
	

	void SetDebugProfileProcessing(bool value);
	bool GetDebugProfileProcessing(){return m_debugProfileProcessing;}

	void FillContolledVarsInfo(decisionNodesArray& nodesArray);

	cControlledVariables& GetControlledVariblesManager(){return m_controlledVarsManager;} 
	unsigned int GetNumberOfControlledCombinaions();
	unsigned int GetCombinationIndexPerControlledGroup(string_m_array& fields, FloatArray& values);
	void FillFieldsValuesBasedOnCombinationIndex(unsigned int index, string_m_array& fields, FloatArray& values);
	UIArray& GetControlVaribalesFieldsIndexArray(){return m_controlledVarsManager.GetControlledFieldsIndexArray();}
	

	void SetSpecialFieldValueCombination(char* name, char* value);
	bool IsSpecialFieldValueCombination(char* name, short int value);
	bool IsSpecialFieldValueCombination(unsigned int similarityIndex, short int value);


	void SetTreeSimilarityValue(char* name, char* value);
	bool IsTreeSimilarityValue(unsigned int similarityIndex, short int value);
	
	void SetAnalyticsIterationJump(unsigned int value);
	unsigned int GetAnalyticsIterationJump(){return m_AnalyticsIterationJump;}

	void SetSimilarityTreeLevels(unsigned int value);
	unsigned int GetSimilarityTreeLevels(){return m_SimilarityTreeLevels;}

	void SetMaxNumberOfAllowedMissingFields(unsigned int value);
	unsigned int GetMaxNumberOfAllowedMissingFields(){return m_MaxNumberOfAllowedMissingFields;}

	void SetAnalyticsMatchingPercent(unsigned int value);
	unsigned int GetAnalyticsMatchingPercent(){return m_AnalyticsMatchingPercent;}

	void SetIsSmallToBigApp(char* str);
	bool IsSmallToBigApp(){return m_IsSmallToBigApp;}



	void SetNotAllowedMissingFields(char* name);
	bool IsNotAllowedMissingFields(char* name);
	
	
	void SetIsToReplaceMissingWithAverage(char* str);
	bool IsToReplaceMissingWithAverage(){return m_IsReplacedMissingWithAverage;}

	void SetIsToReplaceMissingWithEmptyField(char* str);
	bool IsToReplaceMissingWithEmptyField(){return m_IsReplacedMissingWithEmptyField;}
	
	void SetMultiCollectionInfo(char* workDir);
	unsigned int GetNumOfMultiCollections(){return m_MultiCollections.GetSize();}
	string_m& GetCollectionWorkDirByIndex(unsigned int index);


	string_m_array* GetQISubPopulationOptions(string_m& QI);
	void SetSubPopulationListPerQI(string_m& QI, string_m_array& values);

	string_m_array* GetSubPopulationOptionalValues(string_m& subPopulation);
	void SetSubPopulationOptionalValues(string_m& subPopulation, string_m_array& values);

	void CreateSubPopulationName(string_m& subPopulationPath,  string_m& QI, string_m& option, string_m& value);

	int GetSubPopulationIndex(string_m& populationName);
	void AddSingleQI(char* name);
	unsigned int GetNumOfQI(){return m_QIList.GetSize();}
	string_m& GetQIByIndex(unsigned int index);
	bool GetQIindexByQI(unsigned int& index,string_m& QI);
	bool IsIndividuaGetMatchedQI(string_m& QI);
	void SetIsIndividuaGetMatchedQI(char* value){m_IsIndividuaGetMatchedQIList.Add(value);}

	float GetTopFacilitiesThresholdPerQI(string_m& QI, string_m& subPopulation);

	void SetIndicatorDirection(bool isSmallToBigApplciation);
	bool isSmallToBigIndicator(unsigned int index);

	void AddSingleQITimeFrame(char* name);
	unsigned int GetNumOfQITimeFrames(){return m_QITimeFrames.GetSize();}
	string_m& GetQITimeFrameByIndex(unsigned int index);
	unsigned int GetTimeFrameIndexByName(string_m& timeFrame);

	void GetDataItemMappingFileNAme(string_m& file){file.assign(m_dataItemsMappingFileName);}
	void SetDataItemMappingFileNAme(char* file){m_dataItemsMappingFileName.assign(file);}

	void GetCMSRatingFileNAme(string_m& file){file.assign(m_CMSRatingFileName);}
	void SetCMSRatingFileNAme(char* file){m_CMSRatingFileName.assign(file);}

	void AddSingleUSer(char* name);
	unsigned int GetNumOfUsers(){return m_UserList.GetSize();}
	unsigned int GetUserIndex(string_m& userNAme);
	string_m& GetUserByIndex(unsigned int index);

	void AddSinglePAssword(char* str);
	string_m& GetPasswordByIndex(unsigned int index);

	void AddQIList(string_m_array& QIList);
	unsigned int  GetNumofQIPerUSer(unsigned int index);
	void GetSingleUserQIList(string_m_array& list, unsigned int userIndex);

	
	void AddDataItemsList(string_m_array& list);
	unsigned int  GetNumofDataItemsPerUSer(unsigned int index);
	void GetSingleUserDataItemsList(string_m_array& list, unsigned int userIndex);

	void AddSingleUSerLinksOptions(string_m_array& list,string_m_array& listPath,string_m_array& listDirections);
	unsigned int GetNumberOfLinksPErUSer(unsigned int index);
	void GetSingleUserSingleLink(string_m& link,string_m& linkPth,string_m& linkDirection,unsigned int userIndex, unsigned int linkIndex );

	void AddReferenceGroupList(string_m_array& list);
	unsigned int  GetNumofReferenceGroupPerUSer(unsigned int index);
	void GetSingleUserReferenceGroupList(string_m_array& list, unsigned int userIndex);
	

	void AddRefereneGroupData(string_m& groupName ,string_m_array& groupItemsList);
	unsigned int GetNumOfReferenceGroups(){return m_QIReferenceGroups.GetSize();}
	void GetSingleReferenceGroupByIndex(string_m& name, string_m_array& ItemsGroup, unsigned int index);
	void GetSingleReferenceGroupByName(string_m& name, string_m_array& ItemsGroup);
	bool IsItemAReferenceGroup(string_m& name);
	
	void SetMultiCollectionName(char* name);
	string_m& GetCollectionNameByIndex(unsigned int index);
	
	void SetMultiCollectionTimeOut(unsigned int value);
	unsigned int GetMultiCollectionTimeOut(){return m_multiCollectionsTimeOut;}

	void SetApplicationLanguge(char* ln);
	int GetAppLanguageIndex(char* ln);
	unsigned int GetNumOfLanguages(){return m_langaugesIndexesHash.GetCount();}
 
	void SetMetaDataInfo(float minRange, float MaxRange, string_m& color);
	void SetMetaDatDefaultOutput(char* str);
	void FillMetaDataMenuLanguageSpecification(char* lanugaeSpecification, string_m& language);
	void FillSingleMetadataFieldMenu(char* fieldNAme, float min, float max);
	void GetMetaDataMenuInfo(string_m& color, string_m& output, float value, string_m& inputLN, const char* fieldName);

	void SetDataRulesManipulationPath(char* path);
	void SetDataSpeiaclRulesManipulationPath(char* path);
	void SetAppllcationName(char* path);
	char* GetApplciationName(){return (char*)m_applciatioName.c_str();}
	char* GetDataRulesManipulationPath(){return (char*)m_dataRulesManipulationPath.c_str();}
	char* GetDataSpecialRulesManipulationPath(){return (char*)m_dataSpecialRulesManipulationPath.c_str();}
	unsigned int GetNumOfPRimaryReasonFields(){return m_numofPrimaryReasonFields;}
	void SetNumOfPRimaryReasonFields(unsigned int num){m_numofPrimaryReasonFields=num;}
	bool ISSwitchRulesOrder(){return m_isSwitchRulesOrder;}
	void SetSwitchRulesOrder(bool value){m_isSwitchRulesOrder = value;}
	bool IsDataRuleManipulation(){return m_isDataRulesMaipulation;}
	bool IsPrimaryField(char* name);
	void AddPrimaryField(char* name){m_primaryFieldsArray.Add(name);}
	void SetISDataRuleManipulation(bool value);
	void SetISFlatDataRuleManipulation(bool value);
	bool IsFlatDataRuleManipulation(){return m_isFlatDataRulesMaipulation;}

	void AddInputDataFile(string_m& fileName, string_m_array& id, bool isAllFields,StringToIntHash& fieldsNames, string_m& startDate,
							string_m& endDate, string_m& startDateYear,string_m& startDateMonth,string_m& startDateDay);
	string_m& GetInputFilePathByInputIndex(unsigned int index);
	unsigned int GetInputFileNumberOfFields(unsigned int index);
	unsigned int GetNumberOfTotalOutputFields();
	unsigned int GetNumberOfTotalInputFiles();
	void UpdateOutputStrBasedOnSingleInputFile(string_xl& outStr, string_xl& inStr, unsigned int fileIndex,string_xl_array& inStrs , string_xl_array& outStrs);
	int GetIDFieldIndexBasedOnFileIndex(unsigned int fileIndex,unsigned int idIndex);
	int GetStarttDateFieldIndexBasedOnFileIndex(unsigned int fileIndex);
	int GetStarttDateFieldYearIndexBasedOnFileIndex(unsigned int fileIndex);
	int GetStarttDateFieldMonthIndexBasedOnFileIndex(unsigned int fileIndex);
	int GetStarttDateFieldDayIndexBasedOnFileIndex(unsigned int fileIndex);
	int GetEndDateFieldIndexBasedOnFileIndex(unsigned int fileIndex);
	int GetFieldIndexByfieldNameAndFileIndex(string_m& name, unsigned int fileIndex);
	char* GetFieldNameByOutputFieldIndex(unsigned int outputFieldIndex);
	unsigned int GetNumberOfIDTagsPerFileIndex(unsigned int fileIndex);

	bool isValueMeetSuccessRateCondition(float value);
	void SetSuccessRatecondition(string_m& operatorStr, float conditionVal);
	eOperatorType GetOperatorTypeFromStr(string_m& conditionStr);


	float CalcualteED(short value1, short value2, unsigned int similarityFieldIndex);
	bool IsCategoricalVariable(unsigned int similarityFieldIndex);
	bool IsCategoricalMissingVariable(unsigned int similarityFieldIndex);
	float CreateDiffValueKey(float value1, float value2);
	void FillFieldValueDistance(unsigned int similarityFieldIndex,float value1, float value2, float dist);
	void FillSimialrityFieldMapping(float minRange , float maxRange , unsigned int mappedValue, unsigned int similarityFieldIndex);
	unsigned int GetSimialrityMappedValue(short int value,unsigned int similarityFieldIndex);
	void GetGroupBorders(float& min , float& max , unsigned int  similarityFieldIndex, unsigned int  similarityGroupVal);
	unsigned int GetNumOfAvilablefollowedGroups(unsigned int similarityFieldIndex , unsigned int value);
	unsigned int GetSimialrityGroupValue(short int value,unsigned int similarityFieldIndex );
	short int GetFieldValueFromFieldGroup(unsigned int similarityFieldIndex , unsigned int fieldGroup);
	unsigned int GetNumOfOptionsPerField(unsigned int similarityFieldIndex , short int value);
	unsigned int GetNumOfGroupsPerSimilarityField(unsigned int similarityFieldIndex);
	unsigned int GetSimialrityNextGroupValue( short int value ,unsigned int similarityFieldIndex, unsigned int optionIndex);
	short int GetMappedFieldValueFromFieldGroup(unsigned int similarityFieldIndex , unsigned int fieldGroup);
	bool IsMappedSimialrtyVariable(unsigned int similarityFieldIndex);
	unsigned int GetNumOfMappingOptions(unsigned int similarityFieldIndex);

	bool IsSpecialGUI(){return m_isSpecialGUI;}
	void SetIsSpecialGUI(bool value);

	bool IsShortCalculationQI(){return m_IsShortCalculationQI;}
	void SetIsShortCalculationQI(bool value){m_IsShortCalculationQI = value;}


	string_m& GetQIName(){return m_QI;}
	void SetQIName(char* value){m_QI.assign(value) ;}
	
	
	
	
	unsigned int GetPublciationProfieSize(){return m_publciationProfieSize;}
	void SetPublciationProfieSize(unsigned int value);
	unsigned int GetPublicationExtrnalProfileSize(){return m_PublicationExtrnalProfileSize;}//20
	void SetPublicationExtrnalProfileSize(unsigned int value);
	float GetPublicationMinHomogScore(){return m_PublicationMinHomogScore;}//0.1
	void SetPublicationMinHomogScore(float value);
	float GetPublicationMinUniqeScore(){return m_PublicationMinUniqeScore;}//0.25
	void SetPublicationMinUniqeScore(float value);

	float GetThresholdForRecoveryPotential(){return m_ThresholdForRecoveryPotential;}//0.25
	void SetThresholdForRecoveryPotential(float value){m_ThresholdForRecoveryPotential = value;}
	
	unsigned int GetMaxNumOfExtandedItems(){return m_MaxNumOfExtandedItems;}//20
	void SetMaxNumOfExtandedItems(unsigned int value);
	unsigned int GetMaxNumOfPublicationProfiles(){return m_MaxNumOfPublicationProfiles;}//10000
	void SetMaxNumOfPublicationProfiles(unsigned int value);
	bool IsPublicationMode(){return m_isPublicationMode;}
	bool IsResearchMode(){return m_isResearchMode;}
	void SetPublicationMode(bool value);
	void SetResearchMode(bool value);

	unsigned int GetAdversOR30DayLOS(){return m_AdversOR30DayLOS;}
	unsigned int GetQIModeIndex();
	void SetAdversOR30DayLOS(unsigned int value){m_AdversOR30DayLOS = value;}


	void GetBaseLineAssessmentType(string_m& str){str.assign(m_baselineAsse);}
	void SetBaseLineAssessmentType(char* str){m_baselineAsse.assign(str);}

	bool IsToChangeRealTimeValue(float& multiplier , unsigned index);
	void SetRealTimeFieldToChange(char* str);

	

	eQIMode GetQIMode(){return m_QIMode;}
	void GetQINAmeFromQIMode(string_m& QI,eQIMode QIMode);
	void SetQIMode(char* value);
	
	bool IsLOSMode(){return m_isLOSMode;}
	void SetLOSMode(bool value){m_isLOSMode = value;}

	bool IsHistoricalUdpate(){return m_isHistoricalUpdate;}
	void SetHistoricalUdpate(bool value){m_isHistoricalUpdate = value;}

	char* GetHistoricalFieldUpdateFieldName(){return m_HistoricalFieldUpdateFieldName;}
	void SetHistoricalFieldUpdateFieldName(char* value){strcpy(m_HistoricalFieldUpdateFieldName , value);};

	bool IsNewQICalcualtionMode(){return m_IsNewQICalcualtionMode;}
	void SetIsNewQICalcualtionMode(bool value){m_IsNewQICalcualtionMode = value;}


	bool IsToAddFieldsHeader(){return m_IsToAddFieldsHeader;}
	void SetIsToAddFieldsHeader(bool value){m_IsToAddFieldsHeader = value;}


	bool IsAsverseOutcomeFailue(){return m_IsAsverseOutcomeFailue;}
	void SetIsAsverseOutcomeFailue(bool value);

	unsigned int GEtNumOfEffectsFields(){return m_effectFieldsIndexs.GetSize();}
	unsigned int GetEffecFieldIndex(unsigned int index){return *(m_effectFieldsIndexs.GetAt(index));}
	unsigned int GetNumOfValuesSingleEffectField(unsigned int effectIindex  ){return (*(m_effectFieldsValues.GetAt(effectIindex)))->GetSize();}
	float GetSingleEffectFieldValueByIndex(unsigned int effectIindex , unsigned int effectValue){return *((*(m_effectFieldsValues.GetAt(effectIindex)))->GetAt(effectValue));}

	cQuestionnaireInfo& GetQuestionnaireObject(){return m_cQuestionnaire;}

	void SetResearchField(char* fieldNAme){m_ResearchField.assign(fieldNAme);}

	void IsToReplaceRefernceData(string_m& output, string_m& input, bool isReference );
	unsigned int GEtResearchFieldSimilarityIndex();
	void SetResearchFieldValue(float min, float max, unsigned int mappedGroup,float groupAverage, string_m& groupName);
	unsigned int GEtNumOfMappingValues(){return m_GroupMapping.GetSize();}
	void GetSingleGroupValues(float& min, float& max, unsigned int& mappedValue, unsigned int groupIndex);
	FloatArray& GEtGroupMinValues(){return m_MinResearchFieldGroupValues;}
	FloatArray& GEtGroupMaxValues(){return m_MaxResearchFieldGroupValues;}
	UIArray& GEtGroupMAppingArray(){return m_GroupMapping;}
	float GetSingleGroupAverage(unsigned int groupIndex){return *(m_GroupAverage.GetAt(groupIndex));}
	string_m& GetSingleGroupName(unsigned int groupIndex){return *(m_groupNameList.GetAt(groupIndex));}
	unsigned int GetNumOfDependendtFieldsForResearch(){return m_dependentFieldsList.GetSize();}
	void SetDependentFieldForResearch(char* fieldNAme){m_dependentFieldsList.Add(fieldNAme);}
	string_m&  GetDependentFieldForResearchByIndex(unsigned int index){return *(m_dependentFieldsList.GetAt(index)) ;}

	void SetExpectedFieldForResearch(char* fieldNAme){m_expectedFieldsList.Add(fieldNAme);}
	string_m&  GetExpectedFieldForResearchByIndex(unsigned int index){return *(m_expectedFieldsList.GetAt(index)) ;}
	
	unsigned int GetNumOfHistogramFieldsForResearch(){return m_HistogramFieldsList.GetSize();}
	void SetHistogramFieldResearch(char* fieldNAme){m_HistogramFieldsList.Add(fieldNAme);}
	string_m&  GetHistogramFieldResearch(unsigned int index){return *(m_HistogramFieldsList.GetAt(index)) ;}
	bool isFieldIsPartOfHistogram(unsigned int similarityFieldIndex);

	bool IsToChangeSignForReport(){return m_IsToChangeSignForReport;}
	void SetIsToChangeSignForReport(bool flag){m_IsToChangeSignForReport = flag;}
	

	void SetProfileLogicType(char* value){m_profileLogic.assign(value);}
	string_m& GetProfileLogicType(){return m_profileLogic;}
	void SetIDFieldForOutput(char* value){m_IDFieldForOutput.assign(value);}
	string_m& GetIDFieldForOutput(){return m_IDFieldForOutput;}

	void SetFollowUpFieldNAme(char* value){m_followUpFieldName.assign(value);}
	string_m& GetFollowUpFieldNAme(){return m_followUpFieldName;}
	void SetFollowUpNumOfDaysFieldNAme(char* value){m_followUpNumOfDayFieldName.assign(value);}
	string_m& GetFollowUpNumOfDaysFieldNAme(){return m_followUpNumOfDayFieldName;}

	void SetFollowUpChangeFieldNAme(char* value){m_followUpChangeFieldName.assign(value);}
	string_m& GetFollowUpChangeFieldNAme(){return m_followUpChangeFieldName;}

	void SetLiveWithField(char* value){m_liveWithName.assign(value);}
	string_m& GetLiveWithField(){m_liveWithName.assign("LiveWith");return m_liveWithName;}
	

	void SetChangeFieldNAme(char* value){m_ChangeFieldName.assign(value);}
	string_m& GetChangeFieldNAme(){return m_ChangeFieldName;}

	void SetDischargeFieldNAme(char* value){m_DischargeFieldName.assign(value);}
	string_m& GetDischargeFieldNAme(){return m_DischargeFieldName;}
	

	void SetYearToANalyze(char* value){m_yearToAnalyze.assign(value);}
	string_m& GetYearToANalyze(){return m_yearToAnalyze;}

	

	unsigned int GetNumOfFollowUps(){return m_NumOfFollowUps;}
	void SetNumOfFollowUps(unsigned int NumOfFollowUps){m_NumOfFollowUps = NumOfFollowUps;}
	

	void SetProfileLogicExpansionType(char* value){m_profileLogicExpansion.assign(value);}
	string_m& GetProfileLogicExpansionType(){return m_profileLogicExpansion;}
	bool isFieldValuePartOfManualProfileByProfileIndex(unsigned int similarityIndex , short int value, unsigned int profileIndex);
	void AddSingleManulaProfile();
	void AddSingleManualProfileFieldValuesCombinations(string_m& field, string_m& value);
	unsigned int GetNumOfManualProfiles(){return m_ResearchProfileInfoList.GetSize();}
	unsigned int GetNumOfFieldsInInSingleManualProfile(unsigned int profileIndex){return (*(m_ResearchProfileInfoList.GetAt(profileIndex)))->GetNumOfFieldsInProfile();}
	unsigned int GetSingleFieldIndexInSingleManualProfile(unsigned int profileIndex, unsigned int fieldIndex){return (*(m_ResearchProfileInfoList.GetAt(profileIndex)))->GetSingleFieldIndexInProfile(fieldIndex);}

	/////////// Static Functions //////////////////
	static cConfiguration* GetInstance()
	{
		return (!m_thisPtr) ? (m_thisPtr = new cConfiguration()) : m_thisPtr;
	}

	static void DeleteInstance()
	{
		if (m_thisPtr) { delete m_thisPtr; m_thisPtr = 0; }
	}
};


/*#define TOTAL_COMBINATIOSN_FOR_PRED_MANIP 1000
#define IS_ORDER_SCORE true
#define INCREASE_POS_ED_SCORE_EVO_BASE 0.2 
#define INCREASE_POS_ED_SCORE_EVO_CHD 1.0 
#define WITH_VECTOR_RECURSIVE_STRENGTH false
*/

