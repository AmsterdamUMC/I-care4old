#include "stdafx.h"
#include "cConfiguration.h"
#include "cSimilarityFormula.h"
#include "cProfilityException.h"


cConfiguration* cConfiguration::m_thisPtr = 0;

#define MAX_NUMBER_OF_RULES_UNDER_A_TARGET_FIELD 1000


cMappingRule::cMappingRule()
{

}
cMappingRule::~cMappingRule()
{

}
void cMappingRule::SetRule(string_m_array& fieldNameArray, FloatArray& fieldsValues, float virtualValue)
{
	for(unsigned int i =0 ; i < fieldNameArray.GetSize(); i++)
	{
		unsigned int index = cConfiguration::GetInstance()->GetFieldIndexByName((char*)(*(fieldNameArray.GetAt(i))).c_str());
		m_fieldsIndexArray.Add(cConfiguration::GetInstance()->GetFieldIndexByName((char*)(*(fieldNameArray.GetAt(i))).c_str()));

		float value = *(fieldsValues.GetAt(i));
		value *= MULTIPLIER;

		m_fieldsValues.Add((short)value);
	}
	m_virtualValue = virtualValue;
}
bool cMappingRule::isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues)
{
	for(unsigned int i=0; i<m_fieldsIndexArray.GetSize(); i++)
	{
		unsigned int fieldIndex = *(m_fieldsIndexArray.GetAt(i));
		float value = *(fieldsValues.GetAt(fieldIndex));
		value *= MULTIPLIER;
		short roundedValue = (short)value;

		if((*(m_fieldsValues.GetAt(i))) != roundedValue)
		{
			vitualValue = 0;
			return false;
		}
	}
	vitualValue = m_virtualValue;
	return true;
}

cVirtualField::cVirtualField()
{
	
}
cVirtualField::~cVirtualField()
{
	for(unsigned int i=0; i < m_mappingRulesArray.GetSize(); i++)
	{
		delete *(m_mappingRulesArray.GetAt(i));
	}
}
bool cVirtualField::isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues)
{
	for(unsigned int i=0; i < m_mappingRulesArray.GetSize(); i++)
	{
		if((*(m_mappingRulesArray.GetAt(i)))->isMatchedMappingRule(vitualValue, fieldsValues))
		{
			return true;
		}
	}
	return false;
}
void cVirtualField::SetSingleMappingRule(string_m_array& fieldNameArray, FloatArray& fieldsValues, float virtualValue)
{
	cMappingRule* newRule = new cMappingRule;
	newRule->SetRule(fieldNameArray,fieldsValues, virtualValue);
	m_mappingRulesArray.Add(newRule);
}


cActionInfo::cActionInfo()
{
	m_targetOperator = 0;
}
cActionInfo::~cActionInfo()
{
	if(m_targetOperator)
	{
		delete m_targetOperator;
	}
}

void cActionInfo::SetActionInfo(eActionType actionType, float actionVal, unsigned int fieldIndex)
{
	m_actionType = actionType;
	m_value	= actionVal;
	m_fieldIndex = fieldIndex;
}

float cActionInfo::GetActionNewValue(float originalValue)
{
	switch(m_actionType)
	{
		case IncreaseBy_e:
			return (originalValue + m_value);
	
		case DecreaseBy_e:
			return (originalValue - m_value);

		case SetTo_e:
			return (m_value);

		case PositiveLinear_e:
			return (originalValue + m_value);

		case NegativeLinear_e:
			return (originalValue + m_value);

	}
	return 	originalValue;
}
bool cActionInfo::IsTargetValueChancesShouldBeManipulated(float val)
{
	if(m_targetOperator->Exacute(val))
	{
		return true;
	}
	return false;
}
void cActionInfo::SetOneRuleTargetCondition(eOperatorType operatorType, float conditionVal)
{
	if(!m_targetOperator)
	{
		m_targetOperator = GetOperatorPTRByType(operatorType, conditionVal );
	}
}

tNumericOperator<float>* cActionInfo::GetOperatorPTRByType(eOperatorType operatorType, float conditionVal )
{
	tNumericOperator<float>* numericOp = 0;
	if(operatorType == BiggerThan_e) numericOp = new tNumericOperatorGreaterThen<float>(conditionVal);
	else if(operatorType == BiggerOrEqual_e) numericOp = new tNumericOperatorGreaterThenOrEqual<float>(conditionVal);
	else if(operatorType == SmallerThan_e) numericOp = new tNumericOperatorLessThen<float>(conditionVal);
	else if(operatorType == SmallerOrEqual_e) numericOp = new tNumericOperatorLessThenOrEqual<float>(conditionVal);
	else if(operatorType == EqualTo_e) numericOp = new tNumericOperatorEqual<float>(conditionVal);
	else if(operatorType == NotEqualTo_e) numericOp = new tNumericOperatorNotEqual<float>(conditionVal);

	return numericOp;
}

cDataRule::cDataRule()
{
	m_actionInfo = new cActionInfo;
	m_fieldsRules.SetSize(1000);
	m_actionListinfo.SetSize(1000);
	for(unsigned int i=0; i < 1000; i++)
	{
		m_fieldsRules.SetAt(i,0);
		m_actionListinfo.SetAt(i,0);
	}
	
	m_populationPercentage = 100;
	//m_targetOperator = 0;
	m_isLinearRule = false;
	m_ruleWeight = 0;
	m_numOfActions = 0;
}

cDataRule::~cDataRule()
{
	if(m_actionInfo)
	{
		delete m_actionInfo;
	}
	for(unsigned int i=0; i < 1000; i++)
	{
		if(m_fieldsRules[i])
		{
			delete m_fieldsRules[i];
		}
		if(m_actionListinfo[i])
		{
			delete m_actionListinfo[i];
		}
		
	}

}

void cDataRule::SetPopulationPercentage(unsigned int populationPercentage)
{
	m_populationPercentage = populationPercentage;
}
void cDataRule::SetOneRuleTargetCondition(eOperatorType operatorType, float conditionVal, unsigned int actionIndex )
{
	
	return (*(m_actionListinfo.GetAt(actionIndex)))->SetOneRuleTargetCondition(operatorType, conditionVal);
}




void cDataRule::SetOneFiledCondition(unsigned int fieldIndex ,eOperatorType operatorType, float conditionVal )
{
	OperatorList* operatorList = m_fieldsRules[fieldIndex];

	if (!operatorList) 
	{
		operatorList = new OperatorList();
		m_fieldsRules[fieldIndex] = operatorList;
	}

	tNumericOperator<float>* numericOp = m_actionInfo->GetOperatorPTRByType(operatorType, conditionVal );

	operatorList->Add(numericOp);
}

void cDataRule::SetOneRuleActionInfo(eActionType actionType, float actionVal, unsigned int fieldIndex)
{
	
	if((actionType == PositiveLinear_e) ||(actionType == NegativeLinear_e))
	{
		m_isLinearRule = true;
	}

	
	cActionInfo* actionInfo = new cActionInfo;
	actionInfo->SetActionInfo(actionType , actionVal, fieldIndex);
	m_actionListinfo.SetAt(m_numOfActions ,actionInfo);
	m_numOfActions++;

}

bool cDataRule::IsTargetValueChancesShouldBeManipulated(float val, unsigned int actionIndex)
{
	return (*(m_actionListinfo.GetAt(actionIndex)))->IsTargetValueChancesShouldBeManipulated(val);
}

bool cDataRule::IsValueMeetsRuleConditions(float* fieldsValues)
{
	for(unsigned int i = 0; i < 1000; i++)
	{
		if(m_fieldsRules[i])
		{
			OperatorList* operatorList = m_fieldsRules[i];
			bool isFieldMeetCondition = false;

			for(unsigned int j = 0; !isFieldMeetCondition && j < operatorList->GetSize(); j++)
			{
				tNumericOperator<float>* numericOp = *(operatorList->GetAt(j));
				if(numericOp->Exacute(fieldsValues[i]))
				{
					isFieldMeetCondition = true;
				}
			}
			if (!isFieldMeetCondition) return false;
		}
	}
	return true;
}

float cDataRule::GetValueAfterRuleAction(float origValue, unsigned int actionIndex)
{
	return (*(m_actionListinfo.GetAt(actionIndex)))->GetActionNewValue(origValue);
	//return m_actionInfo->GetActionNewValue(origValue);
}
unsigned int cDataRule::GetLinearFieldIndex(unsigned int actionIndex)
{
	return (*(m_actionListinfo.GetAt(actionIndex)))->GetLineaRFieldIndex();
	//return m_actionInfo->GetLineaRFieldIndex();
}
unsigned int cDataRule::GetNumberOfRulesActions()
{
	return m_numOfActions;
}


unsigned int cDataRule::GetOneRulePopulationPercentage()
{
	return m_populationPercentage;
}


cDataRulesManager::cDataRulesManager()
{
	m_rules.SetSize(MAX_NUMBER_OF_RULES_UNDER_A_TARGET_FIELD);
	for(unsigned int i=0; i < MAX_NUMBER_OF_RULES_UNDER_A_TARGET_FIELD; i++)
	{
		m_rules.SetAt(i,0);
	}
	m_NumberOfRules = 0;
	m_rulesWeight = 0;
}
cDataRulesManager::~cDataRulesManager()
{
	for(unsigned int i=0; i < MAX_NUMBER_OF_RULES_UNDER_A_TARGET_FIELD; i++)
	{
		if(m_rules[i])
		{
			delete m_rules[i];
		}
	}
}
void cDataRulesManager::AddRule()
{
	m_NumberOfRules++;
}
eOperatorType cDataRulesManager::GetOperatorTypeFromStr(string_m conditionStr)
{
	if(!strcmp(conditionStr.c_str(), "Bigger Than") || !strcmp(conditionStr.c_str(), ">"))
	{
		return BiggerThan_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Bigger Or Equal") || !strcmp(conditionStr.c_str(), ">="))
	{
		return BiggerOrEqual_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Smaller Than") || !strcmp(conditionStr.c_str(), "<"))
	{
		return SmallerThan_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Smaller Or Equal") || !strcmp(conditionStr.c_str(), "<="))
	{
		return SmallerOrEqual_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Equal To") || !strcmp(conditionStr.c_str(), "="))
	{
		return EqualTo_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Not Equal To") || !strcmp(conditionStr.c_str(), "!="))
	{
		return NotEqualTo_e;
	}
	return BiggerThan_e;
}
void cDataRulesManager::SetOneRuleCondition(unsigned int fieldIndex, string_m conditionStr, float conditionVal)
{
	eOperatorType operatorType= GetOperatorTypeFromStr(conditionStr);
	if(!m_rules[m_NumberOfRules])
	{
		m_rules[m_NumberOfRules] = new cDataRule;
	}
	m_rules[m_NumberOfRules]->SetOneFiledCondition(fieldIndex, operatorType , conditionVal);
}

void cDataRulesManager::SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex )
{
	eOperatorType operatorType= GetOperatorTypeFromStr(conditionStr);
	if(!m_rules[m_NumberOfRules])
	{
		m_rules[m_NumberOfRules] = new cDataRule;
	}
	m_rules[m_NumberOfRules]->SetOneRuleTargetCondition(operatorType , conditionVal, actionIndex);
}
eActionType cDataRulesManager::GetActionTypeFromStr(string_m actionStr)
{
	if(!strcmp(actionStr.c_str(), "Increase By") )
	{
		return IncreaseBy_e;
	}
	else if(!strcmp(actionStr.c_str(), "Decrease By"))
	{
		return DecreaseBy_e;
	}
	else if(!strcmp(actionStr.c_str(), "Set To"))
	{
		return SetTo_e;
	}
	else if(!strcmp(actionStr.c_str(), "PositiveLiniar"))
	{
		return PositiveLinear_e;
	}
	else if(!strcmp(actionStr.c_str(), "NegativeLiniar"))
	{
		return NegativeLinear_e;
	}

	return IncreaseBy_e;
}
void cDataRulesManager::SetPopulationPercentage(unsigned int populationPercentage)
{
	if(!m_rules[m_NumberOfRules])
	{
		m_rules[m_NumberOfRules] = new cDataRule;
	}
	m_rules[m_NumberOfRules]->SetPopulationPercentage(populationPercentage);
}
void cDataRulesManager::SetOneRuleAction(string_m actionStr, float actionVal , unsigned int fieldIndex)
{
	eActionType actionType = GetActionTypeFromStr(actionStr);
	if(!m_rules[m_NumberOfRules])
	{
		m_rules[m_NumberOfRules] = new cDataRule;
	}
	m_rules[m_NumberOfRules]->SetOneRuleActionInfo(actionType , actionVal, fieldIndex);
}


bool cDataRulesManager::IsValueMeetsRuleConditions(float* fieldsValues, unsigned int ruleIndex)
{
	return m_rules[ruleIndex]->IsValueMeetsRuleConditions(fieldsValues);
}
bool cDataRulesManager::IsTargetValueChancesShouldBeManipulated(float val, unsigned int ruleIndex, unsigned int actionIndex)
{
	return m_rules[ruleIndex]->IsTargetValueChancesShouldBeManipulated(val, actionIndex);
}
unsigned int cDataRulesManager::GetOneRulePopulationPercentage(unsigned int ruleIndex)
{
	return m_rules[ruleIndex]->GetOneRulePopulationPercentage();
}
float cDataRulesManager::GetValueAfterRuleAction(float origValue, unsigned int ruleIndex, unsigned int actionIndex)
{
	return m_rules[ruleIndex]->GetValueAfterRuleAction(origValue, actionIndex);
}
bool cDataRulesManager::IsLinearRule(unsigned int ruleIndex)
{
	return m_rules[ruleIndex]->IsLinearRule();
}
unsigned int cDataRulesManager::GetLinearFieldIndex(unsigned int ruleIndex, unsigned int actionIndex)
{
	return m_rules[ruleIndex]->GetLinearFieldIndex(actionIndex);
}
unsigned int cDataRulesManager::GetNumberOfRulesActions(unsigned int ruleIndex)
{
	return m_rules[ruleIndex]->GetNumberOfRulesActions();
}

void cDataRulesManager::SetRulesWeight(unsigned int weight)
{
	m_rulesWeight = weight;
}


cSimilarityInfo::cSimilarityInfo() : m_fieldIndex(0)
{	
	m_virtualField = NULL;
	m_internalFieldMapping = NULL;
	m_isFloatVal = false;
}

unsigned short cSimilarityInfo::GetWeight()
{
	return m_weight;
}

unsigned int cSimilarityInfo::GetIndex()
{
	return m_fieldIndex;
}

int cSimilarityInfo::GetMinRange()
{
	return m_minRange;
}

int cSimilarityInfo::GetMaxRange()
{
	return m_maxRange;
}
void cSimilarityInfo::SetVirtualField()
{
	m_virtualField = new cVirtualField;
}
bool cSimilarityInfo::isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues)
{
	return m_virtualField->isMatchedMappingRule(vitualValue, fieldsValues);
}
bool cSimilarityInfo::isMatchedInternalMappingRule(float& target, FloatArray& fieldsValues)
{
	if(!m_internalFieldMapping)
	{
		return false;
	}
	return m_internalFieldMapping->isMatchedMappingRule(target, fieldsValues);
}
bool cSimilarityInfo::isVirtualField()
{
	return (m_virtualField != NULL);
}
bool cSimilarityInfo::isInternalFieldMapping()
{
	return (m_internalFieldMapping != NULL);
}
void cSimilarityInfo::SetSingleMappingRule(string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue)
{
	m_virtualField->SetSingleMappingRule(fieldNameArray,fieldsValues, virtualValue);
}


void cSimilarityInfo::SetInternalMappingRule(float target, string_m_array& fieldNameArray,FloatArray& fieldsValues)
{
	if(m_internalFieldMapping == NULL)
	{
		m_internalFieldMapping = new cVirtualField();
	}
	m_internalFieldMapping->SetSingleMappingRule(fieldNameArray,fieldsValues, target);
}

cPredictiveInfo::cPredictiveInfo()
{
	m_fieldIndex = 0;
	m_virtualField = NULL;
	m_internalFieldMapping = NULL;
}

cPredictiveInfo::~cPredictiveInfo()
{
	if(m_virtualField)
	{
		delete m_virtualField;
	}
	
}

unsigned int cPredictiveInfo::GetIndex()
{
	return m_fieldIndex;
}

int cPredictiveInfo::GetMinRange()
{
	return m_minRange;
}

int cPredictiveInfo::GetMaxRange()
{
	return m_maxRange;
}
void cPredictiveInfo::SetVirtualField()
{
	m_virtualField = new cVirtualField;
}
void cPredictiveInfo::SetInternalMappingRule(float target, string_m_array& fieldNameArray,FloatArray& fieldsValues)
{
	if(m_internalFieldMapping == NULL)
	{
		m_internalFieldMapping = new cVirtualField();
	}
	m_internalFieldMapping->SetSingleMappingRule(fieldNameArray,fieldsValues, target);
}
bool cPredictiveInfo::isMatchedInternalMappingRule(float& target, FloatArray& fieldsValues)
{
	if(!m_internalFieldMapping)
	{
		return false;
	}
	return m_internalFieldMapping->isMatchedMappingRule(target, fieldsValues);
}

bool cPredictiveInfo::isMatchedMappingRule(float& vitualValue, FloatArray& fieldsValues)
{
	return m_virtualField->isMatchedMappingRule(vitualValue, fieldsValues);
}
bool cPredictiveInfo::isVirtualField()
{
	return (m_virtualField != NULL);
}
bool cPredictiveInfo::isInternalFieldMapping()
{
	return (m_internalFieldMapping != NULL);
}
void cPredictiveInfo::SetSingleMappingRule(string_m_array& fieldNameArray,FloatArray& fieldsValues, float virtualValue)
{
	m_virtualField->SetSingleMappingRule(fieldNameArray,fieldsValues, virtualValue);
}

cResultInfoValueData::cResultInfoValueData()
{
	m_similarityIndex = -1;	
}
cResultInfoValueData::~cResultInfoValueData()
{
	
}
void cResultInfoValueData::SetDataInfo(float value, float genAvg, float specificAvg, string_m& type,int similarityIndex )
{
	m_value = value;
	m_genralAvg = genAvg;
	m_specificAvg = specificAvg;
	m_type.assign(type);
	m_similarityIndex = similarityIndex;
}

void cResultInfoValueData::GetDataInfo(float& value, float& genAvg, float& specificAvg,string_m& type, int& similarityIndex )
{
	value = m_value;
	genAvg = m_genralAvg;
	specificAvg = m_specificAvg;
	type.assign(m_type);
	similarityIndex = m_similarityIndex;
}

cResultInfo::cResultInfo() : m_fieldIndex(0), m_dependentFieldIndex(-1), m_type("Average"), m_similarityIndex(-1), m_isDynamicCalculation(false)
{	
}

unsigned int cResultInfo::GetIndex()
{
	return m_fieldIndex;
}

int cResultInfo::GetMinRange()
{
	return m_minRange;
}

int cResultInfo::GetMaxRange()
{
	return m_maxRange;
}


void cResultInfo::SetResultDataInfo(float value, float genAvg, float specificAvg, string_m& type, int similarityIndex)
{
	cResultInfoValueData currentDataInfo;
	currentDataInfo.SetDataInfo(value, genAvg, specificAvg,  type,  similarityIndex);
	m_resultInfoDataArray.Add(currentDataInfo);
}
void cResultInfo::GetDataInfo(float value, float& genAvg, float& specificAvg,string_m& type,int& similarityIndex )
{
	bool isSetData = false;
	for(unsigned int i=0; i <m_resultInfoDataArray.GetSize(); i++ )
	{
		if((*(m_resultInfoDataArray.GetAt(i))).GetValue() == value)
		{
			(*(m_resultInfoDataArray.GetAt(i))).GetDataInfo(value, genAvg, specificAvg,type,similarityIndex);
			isSetData = true;
		}
	}
	if(!isSetData)
	{
		(*(m_resultInfoDataArray.GetAt(0))).GetDataInfo(value, genAvg, specificAvg,type,similarityIndex);
	}
}
cWhatIFVariotionInfo::cWhatIFVariotionInfo() : m_variotionRatio(0), m_variotoinIndex(0)
{
}

cWhatIFVariotionInfo::~cWhatIFVariotionInfo()
{

}

void cWhatIFVariotionInfo::SetVariotionInfo(unsigned int index, unsigned int ratio)
{
	m_variotionRatio = ratio;
	m_variotoinIndex = index;
}

unsigned int cWhatIFVariotionInfo::GetVariotionRatio()
{
	return m_variotionRatio;
}

unsigned int cWhatIFVariotionInfo::GetVariotionIndex()
{
	return m_variotoinIndex;
}

cOneWhatIfinfo::cOneWhatIfinfo() : m_numberOfValues(0), m_fieldIndex(0)
{
	m_values.SetSize(100);
	m_ratio.SetSize(100);
}

cOneWhatIfinfo::~cOneWhatIfinfo()
{

}

void cOneWhatIfinfo::SetOneWhatIfName(char* name, unsigned int index, unsigned int whatIfOrderIndex)
{
	m_fieldName.assign(name);// = name;  OHAD M_STRING
	m_fieldIndex = index;
	m_WhatIFOrederIndex = whatIfOrderIndex;
}

void cOneWhatIfinfo::SetOneWhatIfValue(char* value,unsigned int ValueIndex, unsigned int ratio)
{
	short int val = (short int)atoi(value);
	m_values.SetAt((ValueIndex-1), val);	
	m_ratio.SetAt((ValueIndex-1), ratio);
	m_numberOfValues++;
}

unsigned int cOneWhatIfinfo::GetNumWhatIFValues()
{
	return m_numberOfValues;
}

short int cOneWhatIfinfo::GetValueByIndex(unsigned int index)
{
	return *(m_values.GetAt(index));
}

unsigned  int cOneWhatIfinfo::GetRatioByIndex(unsigned int index)
{
	return *(m_ratio.GetAt(index));
}

cAllWhatIfInfo::cAllWhatIfInfo() : m_numberOFFields(0)
{
	m_whatifInfo.InitHash(100);
	m_whatifname.SetSize(100);
}

cAllWhatIfInfo::~cAllWhatIfInfo()
{/*
	if(m_numberOfFields)
	{
		for (unsigned int i = 0;i <m_numberOfFields;i++)
		{
			delete[] m_whatifname[i];
		}
	}
delete []m_whatifname;*/
}

void cAllWhatIfInfo::AddNewField()
{
//	m_numberOfFields++;
}

void cAllWhatIfInfo::AddNewName(char* name, unsigned int index, unsigned int WhatIFOrderIndex)
{
	cOneWhatIfinfo* oneWhatIfinfo;

	m_whatifname.SetAt((WhatIFOrderIndex-1),name); 
	m_numberOFFields++;
	if(!m_whatifInfo.LookUp(name, oneWhatIfinfo))
	{
		oneWhatIfinfo = new cOneWhatIfinfo;
		oneWhatIfinfo->SetOneWhatIfName(name,(index), WhatIFOrderIndex);
		m_whatifInfo.SetValue(name, oneWhatIfinfo);
	}
}

void cAllWhatIfInfo::AddNewValue(char* value, unsigned int ValueIndex, unsigned int WhatIFOrderIndex, unsigned int ratio)
{
	cOneWhatIfinfo* oneWhatIfinfo;
	//unsigned int index = m_whatifname.GetSize() > 0 ? m_whatifname.GetSize() - 1 : 0;

	if(m_whatifInfo.LookUp(m_whatifname.GetAt((WhatIFOrderIndex - 1))->c_str(), oneWhatIfinfo))
	{
		oneWhatIfinfo->SetOneWhatIfValue(value, ValueIndex, ratio);
	}
}

unsigned int cAllWhatIfInfo::GetNumberOfFields()
{
	//return m_whatifname.GetSize();
	return m_numberOFFields;
}

cOneWhatIfinfo* cAllWhatIfInfo::GetWhatIfFieldInfoByIndex(unsigned int index)
{
	cOneWhatIfinfo* oneWhatIfInfo = 0;
	m_whatifInfo.LookUp(m_whatifname.GetAt(index)->c_str(),oneWhatIfInfo);
	return oneWhatIfInfo;
}

void cAllWhatIfInfo::ValidateWhatIFData(unsigned int numberOfInputFields)
{
	for (unsigned int i = 0; i < GetNumberOfFields(); i++)
	{
		cOneWhatIfinfo* oneWhatIF = GetWhatIfFieldInfoByIndex(i);

		if(!oneWhatIF || (oneWhatIF->GetFieldIndex() == 0 ) || (oneWhatIF->GetFieldIndex() >numberOfInputFields) )
		{
			throw cProfilityException("Problem with WhatIF Fields indexes defintion");
		}

		for (unsigned int j = 0; j < oneWhatIF->GetNumWhatIFValues(); j++)
		{
			short int value = oneWhatIF->GetValueByIndex(j);
			//if(value) need to check what can we set as default values for WHatIF values in order to validate the correctness of the input
			//{
				//Error, Problem with WhatIF values indexes defintion
			//}
		}
	}
}

cOneTargetInfo::cOneTargetInfo() : m_targetFieldIndex(0), m_numberOFSimilarity(0), m_numberOFPredictive(0),
								   m_numberOFResults(0), m_minRange(0), m_maxRange(0), m_numberOFMetaData(0),
								   m_numberOfMetaDataForOutput(0)
{
	m_similarityInfo.SetSize(1000);
	m_PredictiveInfo.SetSize(1000);
	m_ResultInfo.SetSize(1000);
	m_MetaDataInfo.SetSize(1000);

	for (unsigned int i = 0; i < 1000; i++)
	{
		m_similarityInfo.SetAt(i, 0);
		m_PredictiveInfo.SetAt(i, 0);
		m_ResultInfo.SetAt(i, 0);
		m_MetaDataInfo.SetAt(i, 0);
	}
	m_rulesManager = new cDataRulesManager;

	m_PPIType = NoPPI_e;
	m_PPIDependentIndex = -1;
}
cOneTargetInfo::~cOneTargetInfo()
{
	for (unsigned int i = 0; i < m_numberOFSimilarity; i++)
	{
		delete *(m_similarityInfo.GetAt(i));
	}
	for (unsigned int i = 0; i < m_numberOFPredictive; i++)
	{
		delete *(m_PredictiveInfo.GetAt(i));
	}
	for (unsigned int i = 0; i < m_numberOFResults; i++)
	{
		delete *(m_ResultInfo.GetAt(i));
	}
	for (unsigned int i = 0; i < m_numberOFMetaData; i++)
	{
		delete *(m_MetaDataInfo.GetAt(i));
	}

}

void cOneTargetInfo::SetTargetFieldIndex(unsigned int index)
{
	m_targetFieldIndex = index;
}

void cOneTargetInfo::SetTargetFieldName(char* name)
{
	m_fieldName.assign(name);
}

void cOneTargetInfo::SetResultFieldInfo(unsigned int index,  unsigned int resultIndex, int minRange, int maxRange)
{
	//m_ResultFieldIndexes.Add(index);
	cResultInfo* info = new cResultInfo(index, minRange, maxRange,"", -1,-1);
	m_ResultInfo.SetAt((resultIndex - 1),info);
	m_numberOFResults++;
}
void cOneTargetInfo::SetMetaDataFieldDataInfo(float value,float generalAvg,float specifcAvg,string_m& metadataType,unsigned int orderIndex,
	 int similarityIndex)
{
	cResultInfo* info = *(m_MetaDataInfo.GetAt(orderIndex-1));
	info->SetResultDataInfo(value,generalAvg, specifcAvg,metadataType, similarityIndex);
}
void cOneTargetInfo::SetMetaDataFieldInfo(unsigned int index,  unsigned int resultIndex, int minRange, int maxRange,
										  char* type, int dependentIndex, int referenceSimilarityIndex, bool isDynamicCalculation)
{
	//m_ResultFieldIndexes.Add(index);
	cResultInfo* info = new cResultInfo(index, minRange, maxRange,type, dependentIndex, referenceSimilarityIndex,isDynamicCalculation);
	m_MetaDataInfo.SetAt((resultIndex - 1),info);
	m_numberOFMetaData++;
	if(strcmp(type, "Empty"))
	{
		m_numberOfMetaDataForOutput++;
	}
}



void cOneTargetInfo::SetVirtualField(bool isPredictive, unsigned int index)
{
	if(isPredictive)
	{
		cPredictiveInfo* info = GetPredictiveInfoByIndex(index);
		info->SetVirtualField();
	}
	else if(!isPredictive)
	{
		cSimilarityInfo* info = GetSimilarityInfoByIndex(index);
		info->SetVirtualField();
	}
}

void cOneTargetInfo::SetInternalMappingRule(bool isPredictive , unsigned int index , string_m_array& fieldNameArray,
										  FloatArray& fieldsValues, float virtualValue)
{
	if(isPredictive)
	{
		cPredictiveInfo* info = GetPredictiveInfoByIndex(index);
		info->SetInternalMappingRule(virtualValue, fieldNameArray,fieldsValues);
	}
	else if(!isPredictive)
	{
		cSimilarityInfo* info = GetSimilarityInfoByIndex(index);
		info->SetInternalMappingRule(virtualValue, fieldNameArray,fieldsValues);
	}
}
void cOneTargetInfo::SetSingleMappingRule(bool isPredictive , unsigned int index , string_m_array& fieldNameArray,
										  FloatArray& fieldsValues, float virtualValue)
{
	if(isPredictive)
	{
		cPredictiveInfo* info = GetPredictiveInfoByIndex(index);
		info->SetSingleMappingRule(fieldNameArray,fieldsValues, virtualValue);
	}
	else if(!isPredictive)
	{
		cSimilarityInfo* info = GetSimilarityInfoByIndex(index);
		info->SetSingleMappingRule(fieldNameArray,fieldsValues, virtualValue);
	}
}

//Ohad 30.1.17
void cOneTargetInfo::SetSimilarityFieldInfo(unsigned int index, unsigned short weight, 
											unsigned int SimilarityIndex, int minRange, int maxRange,bool isFloatVal, bool isExtanded, bool isPredictedField,
											bool isOutputProfileField,bool IsProfilePriorityOutputField, bool isServiceField,
											unsigned int* dependentIndexArray,bool isToAddToProfile, bool isManualProfileField, bool isPartOfProfile)
{
	cSimilarityInfo* info = new cSimilarityInfo(index, weight, minRange, maxRange,isFloatVal);
	m_similarityInfo.SetAt((SimilarityIndex - 1), info);
	info->SetExtandedField(isExtanded);
	info->SetPredictedField(isPredictedField);
	info->SetProfileOutputField(isOutputProfileField);
	info->SetProfilePriorityOutputField(IsProfilePriorityOutputField);
	info->SetIsServiceField(isServiceField);
	if(dependentIndexArray)
	{
		info->AddDependentField(dependentIndexArray[0]);
	}
	info->SetIsToAddFieldToProfile(isToAddToProfile);
	info->SetIsManualProfileField(isManualProfileField);
	info->SetIsPartOfProfile(isPartOfProfile);
	m_numberOFSimilarity++;
}

unsigned int cOneTargetInfo::GetSimilarityFieldIndexByFieldIndex(unsigned int index)
{
	for(unsigned int i=0; i < GetNumberOfSimilarityFields(); i++)
	{
		cSimilarityInfo* info = GetSimilarityInfoByIndex(i);
		if(info->GetIndex() == index)
		{
			return i;
		}
	}
	return DUMMY_FIELD_INDEX;

}


void cOneTargetInfo::RemoveSimilarityInfo()
{
	m_similarityInfo.Clear();
	m_numberOFSimilarity = 0;
	m_similarityInfo.SetSize(1000);
	

	for (unsigned int i = 0; i < 1000; i++)
	{
		m_similarityInfo.SetAt(i, 0);
	}
}
void cOneTargetInfo::RemovePredictiveInfo()
{
	m_PredictiveInfo.Clear();
	m_numberOFPredictive = 0;
	m_PredictiveInfo.SetSize(1000);
	for (unsigned int i = 0; i < 1000; i++)
	{
		m_PredictiveInfo.SetAt(i, 0);
	}
}

void cOneTargetInfo::SetPPICalcType(char* value,int dependentIndex)
{
	if(!strcmp(value , "BaseValueChange"))
	{
		m_PPIType = DifferenceDividedToBase_e;
		m_PPIDependentIndex = dependentIndex;
	}
	else if(!strcmp(value , "Difference"))
	{
		m_PPIType = Difference_e;
	}

}

unsigned int cOneTargetInfo::GetNumberOfSimilarityFields()
{
	return m_numberOFSimilarity;
}

unsigned short cOneTargetInfo::GetSumOfSimilarityWeights()
{
	unsigned int sum = 0;
	for(unsigned int i = 0; i < m_numberOFSimilarity; i++)
	{
		sum += (*(m_similarityInfo.GetAt(i)))->GetWeight();
	}
	return sum;
}

unsigned int cOneTargetInfo::GetNumberOfPredictiveFields()
{
	return m_numberOFPredictive;
}

unsigned int cOneTargetInfo::GetNumberOfResultFields()
{
	return m_numberOFResults;
}

unsigned int cOneTargetInfo::GetNumberOfMetaDataFields()
{
	return m_numberOFMetaData;
}

unsigned int cOneTargetInfo::GetNumberOfMetaDataFieldsForOutput()
{
	return m_numberOfMetaDataForOutput;
}


void cOneTargetInfo::SetTargetFieldRanges(int minRange, int maxRange)
{
	m_minRange = minRange;
	m_maxRange = maxRange;
}

void cOneTargetInfo::UpdatePredictiveInfo()
{
	if (m_numberOFSimilarity == 0) return;
	if (m_numberOFPredictive > 0) MoveAllPredictiveInfo(m_numberOFSimilarity);

	for(unsigned int i = 0; i < m_numberOFSimilarity; i++)
	{
		SetPredictiveFieldInfo(GetSimilarityInfoByIndex(i)->GetIndex(), (i + 1), 0, 0);
	}
}

void cOneTargetInfo::MoveAllPredictiveInfo(unsigned int moveValue)
{
	for (int i = (int)m_numberOFPredictive - 1; i >= 0; i--)
	{
		m_PredictiveInfo[i+moveValue] = m_PredictiveInfo[i];
		m_PredictiveInfo[i] = 0;
	}
}

void cOneTargetInfo::SetPredictiveFieldInfo(unsigned int index, unsigned int predictiveIndex, int minRange, 
											int maxRange)
{
	cPredictiveInfo* info = new cPredictiveInfo(index, minRange, maxRange);
	m_PredictiveInfo.SetAt((predictiveIndex - 1), info);
	m_numberOFPredictive++;
}

void cOneTargetInfo::SetOneRuleCondition(unsigned int fieldIndex, string_m conditionStr, float conditionVal)
{
	m_rulesManager->SetOneRuleCondition(fieldIndex, conditionStr, conditionVal);
}
void cOneTargetInfo::SetRulesWeight(unsigned int weight)
{
	m_rulesManager->SetRulesWeight(weight);
}
unsigned int cOneTargetInfo::GetRulesWeight()
{
	return m_rulesManager->GetRulesWeight();
}
void cOneTargetInfo::SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex)
{
	m_rulesManager->SetOneRuleTargetCondition(conditionStr, conditionVal, actionIndex);
}
void cOneTargetInfo::SetOneRuleAction(string_m actionStr, float actionVal, unsigned int fieldIndex)
{
	m_rulesManager->SetOneRuleAction(actionStr , actionVal, fieldIndex);
}
void cOneTargetInfo::SetPopulationPercentage(unsigned int populationPercentage)
{
	m_rulesManager->SetPopulationPercentage(populationPercentage);
}
bool cOneTargetInfo::IsValueMeetsRuleConditions(float* fieldsValues, unsigned int ruleIndex)
{
	return m_rulesManager->IsValueMeetsRuleConditions(fieldsValues, ruleIndex);
}
bool cOneTargetInfo::IsTargetValueChancesShouldBeManipulated(float val, unsigned int ruleIndex, unsigned int actionIndex)
{
	return m_rulesManager->IsTargetValueChancesShouldBeManipulated(val, ruleIndex,actionIndex);
}
unsigned int cOneTargetInfo::GetOneRulePopulationPercentage(unsigned int ruleIndex)
{
	return m_rulesManager->GetOneRulePopulationPercentage(ruleIndex);
}
float cOneTargetInfo::GetValueAfterRuleAction(float origValue, unsigned int ruleIndex, unsigned int actionIndex)
{
	return m_rulesManager->GetValueAfterRuleAction(origValue , ruleIndex, actionIndex);
}
bool cOneTargetInfo::IsLinearRule(unsigned int ruleIndex)
{
	return m_rulesManager->IsLinearRule( ruleIndex);
}
unsigned int cOneTargetInfo::GetLinearFieldIndex(unsigned int ruleIndex, unsigned int actionIndex)
{
	return m_rulesManager->GetLinearFieldIndex( ruleIndex,actionIndex);
}

unsigned int cOneTargetInfo::GetNumberOfRulesActions(unsigned int ruleIndex)
{
	return m_rulesManager->GetNumberOfRulesActions( ruleIndex);
}



void cOneTargetInfo::AddRule()
{
	m_rulesManager->AddRule();
}
unsigned int cOneTargetInfo::GetNumberOfRules()
{
	return m_rulesManager->GetNumOfRules();
}

cSimilarityInfo* cOneTargetInfo::GetSimilarityInfoByIndex(unsigned int index)
{
	return *(m_similarityInfo.GetAt(index));
}

cPredictiveInfo* cOneTargetInfo::GetPredictiveInfoByIndex(unsigned int index)
{
	return *(m_PredictiveInfo.GetAt(index));
}

cResultInfo* cOneTargetInfo::GetResultInfoByIndex(unsigned int index)
{
	return *(m_ResultInfo.GetAt(index));
}

cResultInfo* cOneTargetInfo::GetMetaDAtaInfoByIndex(unsigned int index)
{
	return *(m_MetaDataInfo.GetAt(index));
}

cAllTargetsInfo::cAllTargetsInfo(void)
{
	m_targetInfo.InitHash(10);
}

cAllTargetsInfo::~cAllTargetsInfo(void)
{/*
	if(m_numberOfFields)
	{
		
		for (unsigned int i = 0;i <m_numberOfFields;i++)
		{
			delete[] m_targetsName[i];
		}
	}
	delete []m_targetsName;*/
}

void cAllTargetsInfo::AddNewField()
{
//	m_numberOfFields ++;

}

//OHAD TO ASK
void cAllTargetsInfo::addNewName(char* name,unsigned int index, int minRange, int maxRange, int TargetIndex)
{
	cOneTargetInfo* oneTatgetInfo;
	//m_targetsName[m_numberOfFields] = new char[strlen(name)+1];
	if(TargetIndex == -1)
	{
		m_targetsName.Add(name);
	}
	else
	{
		m_targetsName.SetAt(TargetIndex , name);
	}
//	strcpy(m_targetsName[m_numberOfFields] , name);
		
	if(!m_targetInfo.LookUp(name, oneTatgetInfo))
	{
		oneTatgetInfo = new cOneTargetInfo;
		oneTatgetInfo->SetTargetFieldIndex(index);
		oneTatgetInfo->SetTargetFieldName(name);
		oneTatgetInfo->SetTargetFieldRanges(minRange, maxRange);
		m_targetInfo.SetValue(name, oneTatgetInfo);
	}
	else
	{
		oneTatgetInfo->SetTargetFieldIndex(index);
		oneTatgetInfo->SetTargetFieldName(name);
		oneTatgetInfo->SetTargetFieldRanges(minRange, maxRange);
	}
}

void cAllTargetsInfo::SetVirtualField(bool isPredictive, unsigned int index , int inputTargetIndex)
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = inputTargetIndex;
	if(inputTargetIndex == -1)
	{
		targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;
	}
	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetVirtualField(isPredictive, index);
	}
}
void cAllTargetsInfo::SetInternalMappingRule(bool isPredictive , unsigned int index, int inputTargetIndex ,string_m_array& fieldNameArray,
										   FloatArray& fieldsValues, float virtualValue)
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = inputTargetIndex;
	if(inputTargetIndex == -1)
	{
		targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;
	}
	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetInternalMappingRule(isPredictive , index, fieldNameArray,fieldsValues, virtualValue);
	}
}
void cAllTargetsInfo::SetSingleMappingRule(bool isPredictive , unsigned int index, int inputTargetIndex ,string_m_array& fieldNameArray,
										   FloatArray& fieldsValues, float virtualValue)
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = inputTargetIndex;
	if(inputTargetIndex == -1)
	{
		targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;
	}
	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetSingleMappingRule(isPredictive , index, fieldNameArray,fieldsValues, virtualValue);
	}
}
void cAllTargetsInfo::AddPredictiveField(char* name,unsigned int index, unsigned int predictiveIndex,int minRange, int maxRange, int inputTargetIndex)
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = inputTargetIndex;
	if(inputTargetIndex == -1)
	{
		targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;
	}

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetPredictiveFieldInfo(index, predictiveIndex, minRange, maxRange);
	}
	else
	{
		oneTatgetInfo = new cOneTargetInfo;
	}
}

void cAllTargetsInfo::AddResultField(char* name,unsigned int index, unsigned int resultIndex,int minRange, int maxRange)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetResultFieldInfo(index, resultIndex, minRange, maxRange);
	}
}
void cAllTargetsInfo::AddMetaDataFieldDataInfo(float value,float generalAvg,float specifcAvg,string_m& metadataType,unsigned int orderIndex,
	int similarityIndex)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetMetaDataFieldDataInfo(value,generalAvg,specifcAvg,metadataType,orderIndex, similarityIndex);
	}
}
void cAllTargetsInfo::AddMetaDataField(char* name,unsigned int index, unsigned int resultIndex,int minRange, int maxRange,
									   char* type, int dependentIndex,int referenceSimilarityIndex, bool isDynamicCalculation)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetMetaDataFieldInfo(index, resultIndex, minRange, maxRange, type, dependentIndex,referenceSimilarityIndex,  isDynamicCalculation);
	}
}
void cAllTargetsInfo::SetOneRuleCondition(unsigned int fieldIndex, string_m conditionStr, float conditionVal)
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetOneRuleCondition(fieldIndex, conditionStr, conditionVal);
	}
}

void cAllTargetsInfo::SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex )
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetOneRuleTargetCondition( conditionStr, conditionVal,actionIndex);
	}
}
void cAllTargetsInfo::SetRulesWeight(unsigned int weight)
{
	cOneTargetInfo* oneTatgetInfo;
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetRulesWeight(weight);
	}
}
void cAllTargetsInfo::SetOneRuleAction(string_m actionStr, float actionVal, unsigned int fieldIndex)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetOneRuleAction(actionStr, actionVal, fieldIndex);
	}
}
void cAllTargetsInfo::SetPopulationPercentage(unsigned int populationPercentage)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetPopulationPercentage(populationPercentage);
	}
}

void cAllTargetsInfo::SetPPICalcType(char* value, int dependentIndex)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetPPICalcType(value, dependentIndex);
	}
}

void cAllTargetsInfo::AddRule()
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->AddRule();
	}
}



void cAllTargetsInfo::ValidateTargetData(unsigned int numberOfInputFields)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		for(unsigned int i = 0; i < oneTatgetInfo->GetNumberOfPredictiveFields(); i++ )
		{
			cPredictiveInfo* onePredictive = oneTatgetInfo->GetPredictiveInfoByIndex(i);

			if(!onePredictive || /*(onePredictive->GetIndex() == 0) ||*/ (onePredictive->GetIndex() > numberOfInputFields))
			{
				throw cProfilityException("Problem with Predictive Fields indexes defintion");
			}
		}

		for(unsigned int i = 0; i < oneTatgetInfo->GetNumberOfSimilarityFields(); i++ )
		{
			cSimilarityInfo* oneSimilarity = oneTatgetInfo->GetSimilarityInfoByIndex(i);

			if(!oneSimilarity || /*(oneSimilarity->GetIndex() == 0) ||*/ (oneSimilarity->GetIndex() > numberOfInputFields))
			{
				throw cProfilityException("Problem with Similarity Fields indexes defintion");
			}
		}

		for(unsigned int i = 0; i < oneTatgetInfo->GetNumberOfResultFields(); i++ )
		{
			cResultInfo* oneResult = oneTatgetInfo->GetResultInfoByIndex(i);
			
			if(!oneResult || /*(oneResult->GetIndex() == 0) ||*/ (oneResult->GetIndex() > numberOfInputFields))
			{
				throw cProfilityException("Problem with Result Fields indexes defintion");				
			}
		}
	}
}

//Ohad 30.1.17
void cAllTargetsInfo::AddSimilarityField(char* name, unsigned int index, unsigned int weight, unsigned int SimilarityIndex
										 ,int minRange, int maxRange, bool isFloatVal, bool isExtanded,bool isPredictedField, bool isOutputProfileField,
										 bool IsProfilePriorityOutputField, bool isServiceField,unsigned int* dependentIndexArray,
										 bool isToAddToProfile, bool isManualProfileField, bool isPartOfProfile)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->SetSimilarityFieldInfo(index, weight, SimilarityIndex,minRange, maxRange,isFloatVal, isExtanded, isPredictedField, 
			isOutputProfileField,IsProfilePriorityOutputField, isServiceField,dependentIndexArray,isToAddToProfile, isManualProfileField,isPartOfProfile);
	}
}

unsigned int cAllTargetsInfo::GetSimilarityFieldIndexByFieldIndex(unsigned int index)
{
	cOneTargetInfo* oneTatgetInfo;	
	unsigned int targetIndex = m_targetsName.GetSize() > 0 ? m_targetsName.GetSize() - 1 : 0;

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		return oneTatgetInfo->GetSimilarityFieldIndexByFieldIndex(index);
	}
	return DUMMY_FIELD_INDEX;
}

void cAllTargetsInfo::RemoveSimilarityInfo(unsigned int targetIndex)
{
	cOneTargetInfo* oneTatgetInfo;	

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->RemoveSimilarityInfo();
	}
}
void cAllTargetsInfo::RemovePredictiveInfo(unsigned int targetIndex)
{
	cOneTargetInfo* oneTatgetInfo;	

	if(m_targetInfo.LookUp(m_targetsName.GetAt(targetIndex)->c_str(), oneTatgetInfo))
	{
		oneTatgetInfo->RemovePredictiveInfo();
	}
}

unsigned int cAllTargetsInfo::GetNumberOfFields()
{
	return m_targetsName.GetSize();
}

cOneTargetInfo* cAllTargetsInfo::GetTargetFieldInfoByIndex(unsigned int index)
{
	cOneTargetInfo* oneTargetInfo = 0;
//	strCopy(name, m_targetsName.GetAt(index)->c_str());
	m_targetInfo.LookUp(m_targetsName.GetAt(index)->c_str(), oneTargetInfo);
	return oneTargetInfo;
}

cUSerLinksInfo::cUSerLinksInfo()
{
	m_links = new string_m_array;
	m_linksPath = new string_m_array;;
	m_linksDirection = new string_m_array;;
}

cUSerLinksInfo::~cUSerLinksInfo()
{
	delete m_links;
	delete m_linksPath;
	delete m_linksDirection;
}
void cUSerLinksInfo::AddSingleLinkInfo(string_m& link, string_m& singlePath,string_m& singleDirection)
{
	m_links->Add(link);;
	m_linksPath->Add(singlePath);
	m_linksDirection->Add(singleDirection);
}
void cUSerLinksInfo::GetSingleLinkInfo(string_m& link, string_m& singlePath,string_m& singleDirection, unsigned int index)
{
	link.assign(*(m_links->GetAt(index)));
	singlePath.assign(*(m_linksPath->GetAt(index)));
	singleDirection.assign(*(m_linksDirection->GetAt(index)));
}

cResearchProfileInfo::cResearchProfileInfo()
{

}
cResearchProfileInfo::~cResearchProfileInfo()
{

}
bool cResearchProfileInfo::isFieldValuePartOfManualProfile(unsigned int similarityIndex , short int value)
{
	//OHAD 5.9.16

	cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityIndex);
	float multipleir = 1.0f;
	if(similarityInfo->GetIsFloatVal())
	{
		multipleir = 100.0f;
	}
	for(unsigned int i=0 ; i< GetNumOfFieldsInProfile(); i++)
	{
		if((*(m_fieldsIndexArray.GetAt(i))) == similarityIndex)
		{
			if((*(m_fieldsValues.GetAt(i))) == -1.0f || ((short int)((*(m_fieldsValues.GetAt(i))) * multipleir)) == value)
			{
				return true;
			}
		}
	}
	return false;
}
void cResearchProfileInfo::AddSingleFieldInfo(unsigned int fieldIndex, string_m& value)
{
	m_fieldsIndexArray.Add(fieldIndex);
	if(!strcmp((char*)value.c_str() , "AllOptions"))
	{
		m_fieldsValues.Add(-1.0f);
	}
	else
	{
		float numVal = atof((const char*)value.c_str());
		m_fieldsValues.Add(numVal);
	}

}



cConfiguration::cConfiguration(void) : m_numberOfThreads(1), m_midSizeArray(10000), m_smallSizeArray(50000), 
									   m_bigSizeHash(500000), m_idFieldIndex(0), m_maxSimilarityFieldsInProfile(5), m_numOfFilesToSplit(1),
									   m_numOfEntriesPerRecord(100)
{
	m_nameToIndexHash.InitHash(1000);
	m_nameToFieldParametersHash.InitHash(100);
	m_displayNameToIndexHash.InitHash(100);
	m_fieldIndexToFieldNameHash.InitHash(1000);
	m_WhatIFVariotionsHash.InitHash(100);
	m_WhatIFVariotionsIndexHash.InitHash(100);
	m_numberOfDataLines = 1000000;
	m_logType = info_e;
	m_dataVariance = -1.0f;
	m_studyPopulation.assign("Default");
	m_manipulatedDataValuesHash.InitHash(1000);
	m_evolutiontestWeightAdjustment = 0.0f;
	m_evolutionOverallWeightAdjustment = 0.0f;
	m_outputRegressionFlag = false;
	m_IsSpecialCareSettingCalculationMode = false;
	m_CameFromToPatientPathConvert = false;
	m_isCalcExtVariabes = false;
	m_IsWithCancelZeroVarValueForHomog = false;
	m_IsSwitchDateStructure = false;;
	m_IsManualCalibartionSetting = false;
	m_IsManualPRofileExpansion = true;
	m_IsToLiitPerformanceToSpecificPath = true;
	m_isRetrospcetciveTest = true;
	m_isStudyMode = false;
	m_IsPartialSubString = false;
	m_IsNLPRelated = false;
	m_IsSubStringOneWordLimit = false;
	m_isMultiCareSettingCollection = false;
	m_isToSwitchReadmissionQI = true;
	m_IsSingleCareSettingApplciation = false;
	m_IsAllDataForCalibration = false;
	m_numberOfTestCases=0;
	m_numOfIterationForRunTime = 1;
	m_simplePredictionEvaluation = false;
	m_isAdjustErrorReducPerAveControlGrp = false;
	m_lLevelErrorEvaluation = 1.8;
	m_coreVectorWeightChange = 0.1f;
	m_multipleCoreVectorWeightChange = 0.1f;
	m_percentSumAllRegression = 0.93f;
	m_dynamicSeekAddConstant = 0.1f;
	m_ExponentialEditDistanceScoreConst = 1.0f;
	m_PercDelutionPredVars = 0.01f;
	m_ExponensialConstantForPredict = 1.0f;
	m_ExactMatchRatio = 0.9f;
	m_PercSimilarInMidSizeArray = 0.75f;
	m_PercRemoveFrequentExactMatch = 0.0f;
	m_TotalPercRemoveLowPerfomaceSimVars = 0.5f;
	m_MaxEDForNGroupAllowed = 0.0f;
	m_MaxEDForKregGroupAllowed = 0.0f;
	m_AditionalEvolutionVectorValue = 0.2f;
	m_LinearConstEvolution = 1.0f;
	m_TooLowSimVariableThreshold = 0.5f;
	m_MinSizeSimFormForPRofile = 1000;
	m_VectorIncEvolution = 1.0f;
	m_PPIMinThresold = 0.0f;
	m_LongProfileMinThrshold = 0.0f;
	m_predictKCountEvolution = 1000;
	m_predictKCountCohortEvo = 1000;
	m_PredictKEvolutionFinal = 200;
	m_SizeOfLPGroupMedium = 200;
	m_ConstDecreaseScorePreviousSample = 100;
	m_IncreasePredCntForKcountEvoArr = 2;
	m_NumOfVariablesParticipateInTriples = 17;
	m_PredictNConstant = 0.0f;
	m_ExpoValueToDifferentiateTestGroup = 1.5f;
	m_LocalGenVectorEvolution = 0.5;
	m_EXPForCutExtremePredict = 0.95;
	m_EXPForCutExtreme = 0.8;
	m_PercTestStartValue = 1.0f;
	m_PercTestEndValue = 1.0f;
	m_LocalGenVectorWeight = 0.2;
	m_MinSDAllowedForRegression = 0;
	m_MinGroupCountForEvoTest = 50;
	m_NumOfRandomOutputVaiationPerfomanceProcessing = 700;
	m_NumOfVariablesSimFormulaChangeEvolution = 4;
	m_NumberOfManipulationVariables = 2;
	m_predictKCountForMeta = 200;
	m_predictKCount = 400;
	m_isControlGroupStableAcrossGeneration = false;
	m_isSymetricTestAll = false;
	m_IsToSetDefaultSimfromRegBeta = false;
	m_isRegressionBasedCNTRGrpAvgDelta = false;
	m_isFlaggedRequiredForLinearMetaRegression = false;
	m_isCleanFlaggedImpY = false;
	m_IsDynamicResultVal = false;
	m_isWithForcingSim = false;
	m_IsRecoverySmallToBig = false;
	m_ImprovedModeThreshold = -1.0f;
	m_DeclineModeThreshold = 1.0f;
	m_MinDiffToBeImproved = 2.0f;
	m_isAdjustYValuesWithMean = false;
	m_debugProfileProcessing = false;
	m_AdjustPetImpOnlyAllowed = false;
	m_IsRegStatForMSDUniversal = false;
	m_IsSimplePredict = true;
	m_IsCuttingDependentExtreme = true;
	m_IsSimpleMethodOfChildPrediction = true;
	m_IsMeanOnly = true;
	m_IsWithFeatureSelection = true;
	m_IsWithADJSimForKN = false;
	m_IsAddSortToKNForTest = false;
	m_IsDevidingPerfomanceToParentError = true;
	m_IsFullControlGroupEvolution= false;
	m_IsExponUpgradeForTestGroupSimilar = false;
	m_IsDivideByVarEvolution = false;
	m_IsCompareSetToZeroFormula = false;
	m_IsCompareSetToStraightFormula = false;
	m_IsExtremeCutUsingUniversal = false;
	m_IsStandardPredictiveValuesProfileBased = false;
	m_IsWithSubSetTestGroup = false;
	m_IsStartLinearContTestGrpZero = false;
	m_IsWithSemiRandomPredictiveSelection = false;
	m_IsDefaultFormulaByRegression = false;
	m_IsOnlyProfilePrediction = true;
	m_IsToShiftDepPerfByMeanEvolution = false;
	m_IsToIncludePreviousWeightsInCurrentInternReg = false;
	m_IsTestVersion = false;
	m_specialFieldValueCombinationsHash.InitHash(100);
	m_notAllowedMissingFieldsHash.InitHash(100);
	m_treeSimilarityFieldsHash.InitHash(100);
	m_numberOfPercentiles = 10;
	m_AnalyticsIterationJump = 1;
	m_SimilarityTreeLevels = 1;
	m_MaxNumberOfAllowedMissingFields = 1000;
	m_AnalyticsMatchingPercent = 100;
	m_IsReplacedMissingWithAverage = true;
	m_IsReplacedMissingWithEmptyField = false;
	m_IsSmallToBigApp = true;

	m_numberOfValuesForInteligentPrediction = 0;
	m_basicFieldIndex = 0;
	m_numberOfItemsForLongProfile = 20;
	m_numofPrimaryReasonFields = 0;

	m_langaugesIndexesHash.InitHash(100);

	m_isDataRulesMaipulation = false;
	m_isFlatDataRulesMaipulation = false;

	m_isSwitchRulesOrder = false;

	m_applciatioName.assign("No Name");

	m_successRateRules = NULL;
	m_isCategorialFieldHash.InitHash(100);
	m_isSpecialGUI = false;
	m_IsShortCalculationQI = false;
	m_isPublicationMode = false;
	m_isResearchMode = false;
	m_isLOSMode = false;
	//Ohad 6.11.17
	m_AdversOR30DayLOS = 90;
	m_baselineAsse.assign("LongTermPAC");
	m_realTimeFieldToChange.Add(116);;
	m_realTimeMultipler.Add(0.5f);
	m_QIMode = FunctionalImprove_e;
	m_isHistoricalUpdate = false;
	m_IsNewQICalcualtionMode = false;;
	m_IsToAddFieldsHeader = true;
	m_IsAsverseOutcomeFailue = true;
	m_publciationProfieSize= 30;
	m_PublicationExtrnalProfileSize = 20;
	m_PublicationMinHomogScore= 0.1f;
	m_PublicationMinUniqeScore = 0.25f;
	m_ThresholdForRecoveryPotential= 0.25f;
	m_MaxNumOfExtandedItems = 20;
	m_MaxNumOfPublicationProfiles = 10000;

	m_QIToSubPopulationHAsh.InitHash(100);
	string_m_array* optionList = new string_m_array ;
	m_QIToSubPopulationHAsh.SetValue(GENERAL_SUB_POPULATION, optionList);
	m_SubpopulationToValuesHash.InitHash(100);

	m_isComplexSystem=false;
	m_IsTreatSingleWordsInput = false;
	m_IsAndRelationsInRules = true;
	m_isMAxRelationsRules = true;
	m_IsNumericStrRules = false;
	m_IsDataManagerForSingleField = false;
	m_UpdateRelationsFilesBasedONSynonyms = false;
	m_MaxThreadsForComplexSystem = 12;
	
	m_effectFieldsIndexs.Add(8);//insert here the similarity field index
	FloatArray* singleFieldValue = new FloatArray;
	singleFieldValue->Add(0);
	singleFieldValue->Add(100);
	m_effectFieldsValues.Add(singleFieldValue);;	

	m_isPRofileDashboardView = false;
	m_profileLogic.assign("Algoritmic");
	m_minimumSizeOfProfile = 50;
	m_NumberOfAssessmentsDaysfromAddmission = 4;

	m_CMSRatingFileName.assign("CMS Rating.dat");

	m_IsToChangeSignForReport = true;
	m_numOfCalibrationOptions = 0;
	for(unsigned int i=0 ;i < 100; i++)
	{
		string_m_array* ptr = new string_m_array;
		m_calibrationArray.Add(ptr);
	}

	m_calibrationQIs.Add("ADLImprovement");
	m_calibrationQIs.Add("Readmission");
	m_numOfCalibrationQIs = 2;


	m_callibartionCatgeories.Add("Stroke");
	m_callibartionCatgeoriesAvg.Add(36.1);
	m_callibartionCatgeories.Add("Sepsis");
	m_callibartionCatgeoriesAvg.Add(52.7);
	m_callibartionCatgeories.Add("CHF");
	m_callibartionCatgeoriesAvg.Add(86.1);
	m_callibartionCatgeories.Add("Pneumonia");
	m_callibartionCatgeoriesAvg.Add(48.5);
	m_callibartionCatgeories.Add("Bowel");
	m_callibartionCatgeoriesAvg.Add(39.4);

	FillGenralTErmsHash();
}

void cConfiguration::FillGenralTErmsHash()
{
	m_termsHash.InitHash(100);
	int dummy;

	m_termsHash.SetValue("acute",dummy);
	m_termsHash.SetValue("symptoms",dummy);
	m_termsHash.SetValue("lab",dummy);
	m_termsHash.SetValue("labs",dummy);
	m_termsHash.SetValue("upper",dummy);
	m_termsHash.SetValue("right",dummy);
	m_termsHash.SetValue("left",dummy);
	m_termsHash.SetValue("of",dummy);
	m_termsHash.SetValue("or",dummy);
	m_termsHash.SetValue("and",dummy);
	m_termsHash.SetValue("a",dummy);
	m_termsHash.SetValue("an",dummy);
	m_termsHash.SetValue("nec",dummy);
	m_termsHash.SetValue("ca",dummy);
	m_termsHash.SetValue("nos",dummy);
}

cConfiguration::~cConfiguration(void)
{
	const char* variotion;
	cWhatIFVariotionInfo* variotionInfo = 0;
	StringToWhatIfVariotionInfoHash::sPosition *variotionPos = m_WhatIFVariotionsHash.GetFirst(variotion, variotionInfo);

	while(variotionPos)
	{
		delete 	variotionInfo;
		m_WhatIFVariotionsHash.GetNextKey(variotionPos, variotion, variotionInfo);
	}

	DeleteUnsignedIntToStringHash(m_WhatIFVariotionsIndexHash);
	DeleteUnsignedIntToStringHash(m_fieldIndexToFieldNameHash);
}

void cConfiguration::AddCalibrationVal(char* str)
{
	m_calibrationArray[m_numOfCalibrationOptions]->Add(str);
}

unsigned int cConfiguration::GetNumberOfClaibrationCategories()
{
	return m_callibartionCatgeories.GetSize();
}
void cConfiguration::GetCalibartionCategoryByIndex(string_m& category, unsigned int index)
{
	category.assign(*(m_callibartionCatgeories.GetAt(index)));
}

double cConfiguration::GetCalibartionCategoryAvgByIndex( unsigned int index)
{
	return (*(m_callibartionCatgeoriesAvg.GetAt(index)));
}
	

void cConfiguration::GetCalbrationNAmeByIndex(string_m& str, unsigned int index)
{
	for(unsigned int i=0;i<m_calibrationArray[index]->GetSize(); i++)
	{
		str.append(*(m_calibrationArray[index]->GetAt(i))).append("^");
	}
}
bool cConfiguration::IsNAmeMatchCalibrationName(unsigned int& index, string_m& str)
{
	for(unsigned int i=0 ; i<<m_numOfCalibrationOptions; i++ )
	{
		if(!strcmp((char*)((*(m_calibrationArray[i]->GetAt(i))).c_str()) , (char*)str.c_str()))
		{
			index = i;
			return true;
		}
	}
	return false;
}

void cConfiguration::GetCalbrationQIByIndex(string_m& str, unsigned int index)
{
	str.assign(*(m_calibrationQIs.GetAt(index)));
}

void cConfiguration::GetCalbrationOptionByIndex(string_m_array& strArray, unsigned int index)
{
for(unsigned int i=0;i<m_calibrationArray[index]->GetSize(); i++)
	{
		strArray.Add(*(m_calibrationArray[index]->GetAt(i)));
	}
}

void cConfiguration::DeleteUnsignedIntToStringHash(UnsignedIntToStringHash& hash)
{
	unsigned int index;
	const char* var = 0;
	UnsignedIntToStringHash::sPosition *varPos = hash.GetFirst(index, var);

	while(varPos)
	{
		delete[] var;
		hash.GetNextKey(varPos, index, var);
	}
}

void cConfiguration::SetDataVariance(float variance)
{
	m_dataVariance = variance;
}
void cConfiguration::AddSimialrityFieldToAdjust(char* fieldName, float weight, string_m& QIList)
{
	m_similarityFieldsToAdjustIndex.Add(fieldName);
	m_similarityFieldsToAdjustWeights.Add(weight);
	m_similarityFieldsToAdjustIndexQIRelated.Add(QIList);
}
bool cConfiguration::IsPrimaryField(char* name)
{
	for(unsigned int i=0;i < m_primaryFieldsArray.GetSize(); i++)
	{
		if(!strcmp(name, (char*)(*(m_primaryFieldsArray.GetAt(i))).c_str()))
		{
			return true;
		}
	}
	return false;
}
void cConfiguration::GetSingleSimialrityFiledToAdjustData(unsigned int& index, float& weight, unsigned int fieldIndex)
{

	index = GetSimilarityFieldIndexByFieldName((char*)(*(m_similarityFieldsToAdjustIndex.GetAt(fieldIndex))).c_str());
	weight = *(m_similarityFieldsToAdjustWeights.GetAt(fieldIndex));
}

void cConfiguration::GetSingleSimialrityFiledToAdjustDataPerQI(unsigned int& index, float& weight,unsigned int fieldIndex, string_m& QI)
{
	unsigned int counter = 0;
	for(unsigned int i=0; i < m_similarityFieldsToAdjustIndex.GetSize(); i++)
	{
		if(strstr((char*)(*(m_similarityFieldsToAdjustIndexQIRelated.GetAt(i))).c_str(), (char*)QI.c_str()))
		{
			if(counter == fieldIndex)
			{
				return GetSingleSimialrityFiledToAdjustData(index, weight, i);
			}
			counter++;
		}
	}
}
unsigned int cConfiguration::GetNutOfSimilarityFieldsToAdjustPerQI(string_m& QI)
{
	unsigned int counter = 0;
	for(unsigned int i=0; i < m_similarityFieldsToAdjustIndex.GetSize(); i++)
	{
		if(strstr((char*)(*(m_similarityFieldsToAdjustIndexQIRelated.GetAt(i))).c_str(), (char*)QI.c_str()))
		{
			counter++;
		}
	}
	return counter;
}

	
void cConfiguration::SetMidSizeArray(unsigned int size)
{
	m_midSizeArray = size;	
}
void cConfiguration::SetSmallSizeArray(unsigned int size)
{
	m_smallSizeArray = size;	
}
void cConfiguration::NormelizeValue(string_m& value)
{
	char inout[MAX_STRING_LENGTH];
	char output[MAX_STRING_LENGTH];
	strcpy(inout,(char*)value.c_str());
	unsigned int len= strlen(inout);
	for(unsigned int i=0; i < len; i++)
	{
		if ((inout[i] >= 65) && (inout[i] <= 90))
		{
			inout[i] = inout[i] + 32;
		}
       if (!((inout[i] >= 97) && (inout[i] <= 122))  && !((inout[i] >= 48) && (inout[i] <= 57)))
	   {
			inout[i] = 32;
	   }
	}
	bool isPrevSpace = false;
	unsigned int size = 0;
	for(unsigned int i=0; i < len; i++)
	{
		if(inout[i] == 32 && (isPrevSpace || i+1 == len) )
		{
			continue;			
		}
		output[size] = inout[i];
		size++;
		if(inout[i] == 32)
		{
			isPrevSpace = true;
		}
	}
	value.assign(inout);

}

void cConfiguration::SwitchToParentCategoryEPIC(string_m& currName ,const char* name)
{
	if(!strcmp(name , "Abnormal_findings_on_diagnostic_imaging_of_lung"))
	{
		currName.assign("Pulmonary");
		return;
	}

	if(!strcmp(name , "Acute_myocardial_infraction"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Anemia"))
	{
		currName.assign("Medical_Management");
		return;
	}

	if(!strcmp(name , "Bacteremia"))
	{
		currName.assign("Acute_Infections");
		return;
	}

	if(!strcmp(name , "Cervical_Spinal_Fusion"))
	{
		currName.assign("Non_Surgical_Orthopedic/Musculoskeletal");
		return;
	}

	if(!strcmp(name , "Chronic_Obstructive_Pulmonary_disease_Bronchitis_Asthma"))
	{
		currName.assign("Pulmonary");
		return;
	}

	if(!strcmp(name , "Diabetes_melitus"))
	{
		currName.assign("Medical_Management");
		return;
	}

	if(!strcmp(name , "Disorder of liver"))
	{
		currName.assign("Medical_Management");
		return;
	}

	if(!strcmp(name , "Epilepsy_seizures"))
	{
		currName.assign("Medical_Management");
		return;
	}

	if(!strcmp(name , "Hypertensive_diseases"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Ischemic_heart_disease"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	
	if(!strcmp(name , "Major_joint_replacement_and_lower_extremity"))
	{
		currName.assign("Major_Joint_Replacement_or_Spinal_Surgery");
		return;
	}

	if(!strcmp(name , "Metabolic_disorders"))
	{
		currName.assign("Medical_Management");
		return;
	}

	if(!strcmp(name , "Other_diseases_of_the_pleura"))
	{
		currName.assign("Pulmonary");
		return;
	}

	if(!strcmp(name , "Other_diseases_of_the_respiratory_system"))
	{
		currName.assign("Pulmonary");
		return;
	}

	if(!strcmp(name , "Other_diseases_of_urinary_system"))
	{
		currName.assign("Acute_Infections");
		return;
	}

	if(!strcmp(name , "Other_heart_disease"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Outpatient_cardiac_defibrillator"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Pacemaker"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Percutaneous_coronary_intervention"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Peripherial_vascular_disease"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Symcope_collapse"))
	{
		currName.assign("Medical_Management");
		return;
	}


	currName.assign(name);
}

void cConfiguration::SwitchToParentCategory(string_m& currName ,const char* name)
{
	if(!strcmp(name , "Percutaneous_coronary_intervention"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Pacemaker"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Outpatient_cardiac_defibrillator"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "Outpatient_percutaneous_coronary_interventions"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}
	if(!strcmp(name , "Cardiac_defibrillator"))
	{
		currName.assign("Cardiovascular_and_Coagulations");
		return;
	}

	if(!strcmp(name , "BKA"))
	{
		currName.assign("Medical_Management");
		return;
	}
	if(!strcmp(name , "Amputations_Except_BKA"))
	{
		currName.assign("Medical_Management");
		return;
	}
	if(!strcmp(name , "Major_Organ_Transplant"))
	{
		currName.assign("Medical_Management");
		return;
	}

	if(!strcmp(name , "Cervical_Spinal_Fusion"))
	{
		currName.assign("Non_Surgical_Orthopedic/Musculoskeletal");
		return;
	}


	currName.assign(name);

}
void cConfiguration::RemoveChar(char* inout, const char ch, unsigned int& numOfRemovedChars)
{
	unsigned int index = 0;
	unsigned int len = strlen(inout);
	char* temp = new char[len+1];
	strcpy(temp, inout);
	
	numOfRemovedChars = 0;
	unsigned int i;
	for (i = 0; i < len; i++)
	{
		if (temp[i] == ch)
		{
			numOfRemovedChars++;
		}
		else
		{
			inout[index] = temp[i];
			index++;
		}
	}
	inout[index] = '\0';
	delete [] temp;
}
void cConfiguration::FillFieldLanguageSpecification(string_m&  name, char* lanugaeSpecification, string_m& language)
{
	cFieldParameters* fieldInfo;
	if(m_nameToFieldParametersHash.LookUp(name, fieldInfo))
	{
		int index = GetAppLanguageIndex((char*)language.c_str());
		fieldInfo->SetFieldLanguageInfo(lanugaeSpecification,index);
	}
	unsigned int fieldIndex = GetFieldIndexByName((char*)name.c_str());
	char stndName[MAX_STRING_LENGTH];
	strcpy(stndName , (const char*)lanugaeSpecification);
	unsigned int numOfRemovedChars = 0;
	RemoveChar(stndName, ' ', numOfRemovedChars);
	if(!m_displayNameToIndexHash.LookUp(stndName , fieldIndex))
	{
		m_displayNameToIndexHash.SetValue(stndName , fieldIndex);
	}
}
void cConfiguration::SetPrimaryReasonMapping(char* input)
{
	tInputBuffer inFile;
	string_m fileName;
	fileName.assign(input);
	if (!inFile.OpenFile(fileName.c_str()))
	{
		return;
	}
	string_m inputLine;
	string_m_array strs;
	while(inFile.GetStringLine(inputLine))
	{
		size_t numOfFields = inputLine.split_fields(strs, '\t');
		m_primaryReasonInput.Add(strs[0]);
		m_primaryReasonMapping.Add(strs[1]);
	}
}

int cConfiguration::GetPrimaryReasonRiskGroupDetailedList(string_m& input)
{
	int riskGroup = -1;

	if(!strcmp((char*)input.c_str() ,"Sacrococcygeal_Disorders"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Hemolytic_Anemias"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Gangrene"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Malignant_neoplasms_of_lymphoid_hematopoietic_and_related_tissue"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Calculus_of_Ureter"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Cardiac_defibrillator"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Hepatic_Failure"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Chronic_Kidney_Disease_(CKD)_Stages4-5"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Alcoholic_Cirrhosis_of_Liver"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Other_Ascites"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Other_diseases_of_the_respiratory_system"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Percutaneous_coronary_intervention"))
	{
			return 9;
	}
if(!strcmp((char*)input.c_str() ,"Amputations_Except_BKA"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Diarrhea"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Combined_Systolic_and_Diastolic_Heart_Failure"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Other_diseases_of_the_pleura"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Renal_Failure"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Peripheral_vascular_disease"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Peripherial_vascular_disease"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Peripheral_Vascular_Diseases"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Renal_disorders"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Cancer_Primary"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"BKA"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"Other_respiratory_diseases"))
	{
			return 8;
	}
if(!strcmp((char*)input.c_str() ,"CHF"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Solid_malignant_neoplasm"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,""))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Bacteremia"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Endocarditis_and_Heart_Valve_Disorders"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Diastolic_Heart_Failure"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Major_bowel_procedures"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Anemia"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Presence_of_Aortocoronary_Bypass_Graft"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Systolic_Heart_Failure"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Pain_in_Throat_and_Chest"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Gastrointestinal_hemorrhage"))
	{
			return 7;
	}
if(!strcmp((char*)input.c_str() ,"Sepsis"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Nutritional_Anemias"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Cardiac_valve"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Pulmonary"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Chronic_Constructive_Pulmonary_Disease"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Cardiovascular_and_Coagulations"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Hematoma"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Abdominal_and_Pelvic_Pain"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Chronic_ Constructive_Pulmonary_disease_Bronchitis_Asthma"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Acute_Kidney_Failure"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Gynecological_problems"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Acute myocardial infarction"))
	{
			return 6;
	}
if(!strcmp((char*)input.c_str() ,"Complications_of_implanted_device_or_graft"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Dyspnea"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Other_heart_disease"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Hematemesis"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Angina_Pectoris"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Acute_Myocardial_Infarction"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Gastrointestinal_obstruction"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Non_Orthopedic_Surgery"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Hemorrhage_of_Anus_and_Rectum"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Noninfective_Enteritis_and_Colitis"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Intestinal_Obstruction"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Retention_of_Urine"))
	{
			return 5;
	}
if(!strcmp((char*)input.c_str() ,"Acute_Infections"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Ischemic_heart_disease"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Abnormal_findings_on_diagnostic_imaging_of_lung"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Calculus_of_Kidney"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Shortness_of_Breath"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Other_Heart_Failure"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Dizziness_and_Giddiness"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Cardiac_Arrhythmia"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Atrial_Fibrillation_and_Flutter"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Medical_Management"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Kidney_Transplant_Status"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Other_Diseases_of_Esophagus"))
	{
			return 4;
	}
if(!strcmp((char*)input.c_str() ,"Coronary_artery_bypass_graft"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Metabolic_disorders"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Hypertensive_diseases"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Influenza_and_Pneumonia"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Diseases_of_Esophagus_Stomach_and_Duodenum"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Simple_Pneumonia_and_Respiratory_Infection"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Epilepsy_seizures"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Diabetes_melitus"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Asthma"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Melena"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Return to Provider"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Cellulitis"))
	{
			return 3;
	}
if(!strcmp((char*)input.c_str() ,"Hemiplegia_Paraplegia_and_quadriplegia"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Altered_Mental_Status"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Disorder of liver"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Other_disorders_of_the_nervous_system"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"UTI"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Acute_Neurologic"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Cerebrovascular_diseases"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Stroke"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Dysphagia"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Convulsions"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Age_Related_Cataract"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Cerebral_Infartion_Stroke"))
	{
			return 2;
	}
if(!strcmp((char*)input.c_str() ,"Fever_of_Other_and_unknown_Origin"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Other_diseases_of_urinary_system"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Weakness"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Spondylopathies"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Gastro_Esophageal_Reflux_Disease"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Major_Organ_Transplant"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Spondylosis"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Symcope_collapse"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Dorsalgia"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Hyperglycemia"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Parkinson"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Orthopedic_Surgery"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Non_Surgical_Orthopedic/Musculoskeletal"))
	{
			return 1;
	}
if(!strcmp((char*)input.c_str() ,"Radiculopathy_Lumbar_Region"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Fracture_of_rib(s)_sternum_and_thoracic_spine_lumbar_spine_and_pelvis"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Spinal_Stenosis"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Psychiatric_disorders"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Orthopedic_Surgery(Except Major_Joint_Replacement_or_Spinal_Surgery)"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Cervical_Spinal_Fusion"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Hip_&_femur_procedures_except_major_joint"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Fractures_of_the_femur_and_hip_or_pelvis"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Fracture_of_shoulder_and_upper_arm_fracture_at_wrist_and_hand_leve"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Fracture_of_lower_leg"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Periprosthetic_fracture_around_internal_prosthetic_joint"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Arthritis_arthropathies_osteoarthritis"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Spinal_Fusion_(non-Cervical)"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Pacemaker"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Orthopedic_Surgery(Except Fracture_of_rib(s)_sternum_and_thoracic_spine_lumbar_spine_and_pelvis)"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Osteoarthritis_of_Hip"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Major_Joint_Replacement_or_Spinal_Surgery"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Osteoarthritis_of_Knee"))
	{
			return 0;
	}
if(!strcmp((char*)input.c_str() ,"Major joint replacement of lower extremities"))
	{
			return 0;
	}


	return riskGroup;
}

int cConfiguration::GetPrimaryReasonRiskGroup(string_m& input)
{
	int riskGroup = -1;
	
	if(!strcmp((char*)input.c_str() ,"Malignant_neoplasms_of_lymphoid_hematopoietic_and_related_tissue"))
	{
			riskGroup = 4;
	}
	else if(!strcmp((char*)input.c_str() ,"Other_respiratory_diseases"))
	{
			riskGroup = 4;
	}
	else if(!strcmp((char*)input.c_str() ,"Other_diseases_of_urinary_system"))
	{
			riskGroup = 4;
	}
	else if(!strcmp((char*)input.c_str() ,"Other_diseases_of_the_pleura"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Gastrointestinal_hemorrhage"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Metabolic_disorders"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Chronic_Obstructive_Pulmonary_disease_Bronchitis_Asthma"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Other_diseases_of_the_respiratory_system"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Sepsis"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Pulmonary"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Bacteremia"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Renal_Failure"))
	{
			riskGroup = 4;
		}
	else if(!strcmp((char*)input.c_str() ,"Other_heart_disease"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Peripherial_vascular_disease"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Gastrointestinal_obstruction"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Major_bowel_procedures"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Renal_disorders"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"CHF"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Simple_Pneumonia_and_Respiratory_Infection"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Hypertensive_diseases"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Acute_Infections"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Cardiac_Arrhythmia"))
	{
		riskGroup = 3;
	}
	else if(!strcmp((char*)input.c_str() ,"Cancer_Primary"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Diabetes_melitus"))
	{
			riskGroup = 3;
		}
	else if(!strcmp((char*)input.c_str() ,"Abnormal_findings_on_diagnostic_imaging_of_lung"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Epilepsy_seizures"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Anemia"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Disorder of liver"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"UTI"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Other_disorders_of_the_nervous_system"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Cardiovascular_and_Coagulations"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Solid_malignant_neoplasm"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Ischemic_heart_disease"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Medical_Management"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Cardiac_defibrillator"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Return to Provider"))
	{
			riskGroup = 2;
		}
	else if(!strcmp((char*)input.c_str() ,"Non_Orthopedic_Surgery"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Cardiac_valve"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Symcope_collapse"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Orthopedic_Surgery(Except Major_Joint_Replacement_or_Spinal_Surgery)"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Gynecological_problems"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Amputations_Except_BKA"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Cellulitis"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Psychiatric_disorders"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Hip_&_femur_procedures_except_major_joint"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Coronary_artery_bypass_graft"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Fractures_of_the_femur_and_hip_or_pelvis"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Acute_Neurologic"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Parkinson"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Fracture_of_rib(s)_sternum_and_thoracic_spine_lumbar_spine_and_pelvis"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Dorsalgia"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Stroke"))
	{
			riskGroup = 1;
		}
	else if(!strcmp((char*)input.c_str() ,"Cerebrovascular_diseases"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Spondylopathies"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"BKA"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Major_Joint_Replacement_or_Spinal_Surgery"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Fracture_of_lower_leg"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Fracture_of_shoulder_and_upper_arm_fracture_at_wrist_and_hand_leve"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Non_Surgical_Orthopedic/Musculoskeletal"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Pacemaker"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Spinal_Fusion_(non-Cervical)"))
	{
			riskGroup = 0;
		}
	else if(!strcmp((char*)input.c_str() ,"Arthritis_arthropathies_osteoarthritis"))
	{
			riskGroup = 0;
		}


	return riskGroup;
}
void cConfiguration::GetPrimaryFieldNameFromInput(string_m& output, string_m& input)
{
	output.assign(input);
	for(unsigned int i=0;i<m_primaryReasonInput.GetSize();i++)
	{
		if(!strcmp((char*)input.c_str() , (char*)(*(m_primaryReasonInput.GetAt(i))).c_str()))
		{
			output.assign(*(m_primaryReasonMapping.GetAt(i)));
		}
	}
}


bool cConfiguration::IsNonPrimaryReasonDEfintion(char* str)
{
	if(!strcmp(str,"Mosre High Group" ) ||!strcmp(str,"Mosre Mid Group" ) || !strcmp(str,"Mosre Low Group" ) ||!strcmp(str,"Delirium High Risk" ) ||
		!strcmp(str,"Delirium Low Risk" ) ||!strcmp(str,"Pressure Ulcer High Risk" ) ||!strcmp(str,"Pressure Ulcer Low Risk" ) || !strcmp(str,"Pressure Ulcer Medium Risk") ||
		!strcmp(str,"ADL Dependency Level 1" ) || !strcmp(str,"ADL Dependency Level 2" ) || !strcmp(str,"ADL Dependency Level 3" ) || !strcmp(str,"ADL Dependency Level 4" ) || !strcmp(str,"ADL Dependency Level 5" )
		|| !strcmp(str,"ADL Dependency Level 6" ) || !strcmp(str,"ADL Dependency Level 7" ) || !strcmp(str,"ADL Dependency Level 8" )
		|| !strcmp(str,"Walking Dependency Level 1" )|| !strcmp(str,"Walking Dependency Level 2" )|| !strcmp(str,"InfectionRisk 1" )|| !strcmp(str,"InfectionRisk 2" )|| !strcmp(str,"InfectionRisk 3" )
		|| !strcmp(str,"Not Depression" )|| !strcmp(str,"Walking Dependency FIM Level 1" )|| !strcmp(str,"Walking Dependency FIM Level 2" )|| !strcmp(str,"Walking Dependency FIM Level 3" )
		|| !strcmp(str,"Transfer Dependency FIM Level 1" )|| !strcmp(str,"Transfer Dependency FIM Level 2" )|| !strcmp(str,"Transfer Dependency FIM Level 3" )
		|| !strcmp(str,"Fall High Group" )|| !strcmp(str,"Fall Mid Group" )|| !strcmp(str,"Fall Low Group" )|| !strcmp(str,"Not Depression High" )|| !strcmp(str,"Not Depression Mid" )|| !strcmp(str,"Not Depression Low" )
		|| !strcmp(str,"Not Delirium High" )|| !strcmp(str,"Not Delirium Mid" )|| !strcmp(str,"Not Delirium Low" )|| !strcmp(str,"Not Depression High no Medications" )|| !strcmp(str,"Not Depression Low many Medications" )
		|| !strcmp(str,"Calibrated COVID High Group" )|| !strcmp(str,"Calibrated COVID Mid Group" )|| !strcmp(str,"Calibrated COVID Low Group" )
		|| !strcmp(str,"Infection Rule 1" )|| !strcmp(str,"Infection Rule 2" )|| !strcmp(str,"Infection Rule 3" )
		|| !strcmp(str,"Very Low Infection Risk" )|| !strcmp(str,"Low Infection Risk" )|| !strcmp(str,"Mid Infection Risk" )|| !strcmp(str,"High Infection Risk" )
		|| !strcmp(str,"Very High Infection Risk" )|| !strcmp(str,"EPIC RISK GRoup 1" )|| !strcmp(str,"EPIC RISK GRoup 2" )|| !strcmp(str,"EPIC RISK GRoup 3" )
		|| !strcmp(str,"EPIC RISK GRoup 4" )|| !strcmp(str,"EPIC RISK GRoup 5" )|| !strcmp(str,"EPIC RISK GRoup 6" ))

		
		
		

	{
		return true;
	}
	return false;
}


bool cConfiguration::IsPartOfFieldsToOmit(unsigned int index , UIArray& OmitFieldsIndex)
{
	if(OmitFieldsIndex.GetSize() == 0)
	{
		return false;
	}
	for(unsigned  int i=0 ; i < OmitFieldsIndex.GetSize(); i++)
	{
		if(index == *(OmitFieldsIndex.GetAt(i)))
		{
			return true;
		}
	}
	return false;
}


bool cConfiguration::ISMatchRiskProfile(ShortIArray&  realSimilarity , int* dataArray,bool isHigh)
{
	for(unsigned int i=0 ;i <cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetNumberOfSimilarityFields(); i++ )
	{
		if(dataArray[i] >= 0 && (*(realSimilarity.GetAt(i))) >= 0)
		{
			if(isHigh)
			{
				if(dataArray[i] * 100 > (*(realSimilarity.GetAt(i))))
				{
					return false;
				}
			}
			else
			{
				if(dataArray[i] * 100 < (*(realSimilarity.GetAt(i))))
				{
					return false;
				}
			}
		}
	}
	return true;
}

int cConfiguration::CalcEPICRiskValue(ShortIArray&  realSimilarity )
{
	int adlVal = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) / 100;
	int HospitalLOS = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLFollow2"))))/ 100;
	int NumOfCom = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLFollow3"))))/ 100;
	int PrimaryDirection = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLFollow4"))))/ 100;

	int adlScale = 0;
	int LOSScale = 0;
	int comScale = 0;
	
	if(adlVal < 12)
	{
		adlScale = 1;
	}
	else if(adlVal<17)
	{
		adlScale = 0;
	}
	else
	{
		adlScale = 2;
	}

	if(HospitalLOS >= 10)
	{
		LOSScale = 1;
	}

	if(NumOfCom < 2)
	{
		comScale = 0;
	}
	else if(NumOfCom<3)
	{
		comScale = 1;
	}
	else
	{
		comScale = 2;
	}
	int sum = adlScale+LOSScale+comScale + PrimaryDirection;
	return sum;


	//=IF(F3<12,1,IF(F3<17,0,2))  ADL

//=IF(K3<10,0,1)   LOS in Hospital

//=IF(M5<2,0,IF(M5<3,1,2))   num of comorbidites
}

bool cConfiguration::IsPartOFRiskGroup(StringToIntPTRHash& hashToCheck ,StringToIntPTRHash& oppositeHash , ShortIArray&  realSimilarity, bool isHigh)
{
	
	const char* key;
	int* dataArray;
	bool isMAtched = false;;
	StringToIntPTRHash::sPosition *iterator = hashToCheck.GetFirst(key, dataArray);
	while (iterator)
	{
		if(ISMatchRiskProfile(realSimilarity , dataArray, isHigh))
		{
			isMAtched = true;
		}

		hashToCheck.GetNextKey(iterator, key, dataArray);
	}

	iterator = oppositeHash.GetFirst(key, dataArray);
	while (iterator)
	{
		if(ISMatchRiskProfile(realSimilarity , dataArray,!isHigh))
		{
			isMAtched = false;
		}

		oppositeHash.GetNextKey(iterator, key, dataArray);
	}

	
	
	
	return isMAtched;
}

bool cConfiguration::isPartOfInfectionGroup(ShortIArray&  realSimilarity, unsigned int index)
{
	if(index == 0 )
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"IVFeeding")))) == 100 ||
		   //*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"IVMedication")))) == 100 || 
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Dialysis")))) == 100)
		{
			return true;
		}
		return false;
	}
	


	if(index == 1 )
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"BladderIncontinence")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"BowelIncontinence")))) == 100 )
		{
			return true;
		}
		return false;
	}

	if(index == 2 )
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Respiratorytreat")))) == 100 )
		{
			return true;
		}
		return false;
	}
	



	if(index == 3 )
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"HipReplacement")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Kneereplacement")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Surgicalwound")))) == 100)
		{
			return true;
		}
		return false;
	}

	
	if(index == 4 )
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Gastrointestinal")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"otherInfection")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pneumonia")))) == 100||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Septicemia")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Tuberculosis")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Acute_Infections")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Diabetes")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"PulmonaryDisorders")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"KidneyDisorder")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pulcer")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Burns")))) == 100 ||
		   *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Amputation")))) == 100
			  )
		{
			return true;
		}
		return false;
	}



	
	
}
int cConfiguration::CalulateInfectionRisk(ShortIArray&  realSimilarity)
{
	int sum = 0;

	for(unsigned int i=0 ; i < 5 ; i++)
	{
		if(isPartOfInfectionGroup(realSimilarity , i))
		{
			sum++;
		}
	}

	return sum;
}

void cConfiguration::ConvertStrToLowerCase(char* inout)
{
	unsigned int len= strlen(inout);
	for(unsigned int i=0; i < len; i++)
	{
		if ((inout[i] >= 65) && (inout[i] <= 90))
		{
			inout[i] = inout[i] + 32;
		}
        
	}
}


void cConfiguration::SetICDMapping()
{
	tInputBuffer inFile;
	string_m fileName;
	fileName.assign(cConfiguration::GetInstance()->GetWorkingDirectory()).append(SLASH_SIGH).append("ICDMapping.dat");
	
	if (!inFile.OpenFile(fileName.c_str()))
	{
		return ;
	}


	char input[10* MAX_STRING_LENGTH];
	unsigned int numOfRemovedChars;
	
		
	string_m inLine;
	string_m outputLine;
	string_m_array strs;
	string_m outStr;

	m_ICDMappaingHash.InitHash(10000);
	while(inFile.GetStringLine(inLine))
	{

		size_t numOfFields = inLine.split_fields(strs, '	');

		strcpy(input , (char*)(*(strs.GetAt(0))).c_str());
		if(!strcmp("I639", input))
		{
			int ppp=0;
		}
		ConvertStrToLowerCase(input);
		cConfiguration::GetInstance()->RemoveChar(input, '.', numOfRemovedChars);
		int dummy;
		if(m_ICDMappaingHash.LookUp(input , outStr))
		{
			string_m str;
			bool isInsert = false;
			for(unsigned int i=1; i < 10; i++)
			{
				str.assign(input).append("-").appendNum(i);
				if(!m_ICDMappaingHash.LookUp(str , outStr) && !isInsert )
				{
					strcpy(input, (char*)str.c_str());
					m_ICDMappaingHash.SetValue(input , strs[2]);
					isInsert = true;
				}
				
			}
			
		}
		else
		{
			m_ICDMappaingHash.SetValue(input , strs[2]);
		}
		
		
	}


}



bool cConfiguration::IsCOVIDICDMapping(char* fieldStrValues)
{
	//U07.1, J98.8

	if(strstr(fieldStrValues , "U07.1"))
	{
		return true;
	}
	return false;
}

bool cConfiguration::IsMatchICDMapping(string_m& outputField , char* fieldStrValues, unsigned int pI)
{

	unsigned int numOfRemovedChars;
	char inputField[10* MAX_STRING_LENGTH];
	strcpy(inputField , fieldStrValues);
	ConvertStrToLowerCase(inputField);
	cConfiguration::GetInstance()->RemoveChar(inputField, '.', numOfRemovedChars);
	outputField.clear();
	if(pI == 0)
	{
		if(m_ICDMappaingHash.LookUp(inputField , outputField))
		{
			return true;
		}
	}
	else
	{
		string_m inputFieldStr;

		inputFieldStr.assign(inputField).append("-").appendNum(pI);
		strcpy(inputField, (char*)inputFieldStr.c_str());
		if(m_ICDMappaingHash.LookUp(inputField , outputField))
		{
			return true;
		}
	}

	return false;



	//need to convert all the fields to lower case
	//need to read line by line fomr the file
	//check for each line it it is a sub string of one of the fields
	//if yes, assign the relevant field to be output and return true
	//if no match at all return false;

	outputField.clear();

	tInputBuffer inFile;
	string_m fileName;
	fileName.assign(cConfiguration::GetInstance()->GetWorkingDirectory()).append(SLASH_SIGH).append("ICDMapping.dat");
	
	if (!inFile.OpenFile(fileName.c_str()))
	{
		return false;
	}

	char input[10* MAX_STRING_LENGTH];
	
	
		
	
	string_m inLine;
	string_m outputLine;
	string_m_array strs;
	
	int val = atoi(inputField+1);
	
	while(inFile.GetStringLine(inLine))
	{

		size_t numOfFields = inLine.split_fields(strs, '	');

		strcpy(input , (char*)(*(strs.GetAt(0))).c_str());
		int valImput = atoi(input+1);
		if(valImput == val)
		{

			ConvertStrToLowerCase(input);
			cConfiguration::GetInstance()->RemoveChar(input, '.', numOfRemovedChars);

		
			if(strstr(inputField,input) )
			{
				outputField.assign(strs[2]);
				return true;
			}
		}
		
	}

	return false;


}
//Ohad 19.3.20
bool cConfiguration::IsMAtchGRuopDefintion(char* str ,ShortIArray&  realSimilarity, UIArray& OmitFieldsIndex,StringToIntPTRHash& highRiskProfilesHAsh, StringToIntPTRHash& lowRiskProfileHAsh )
{
	if(!strcmp(str,"Very High Infection Risk" ))
	{
		int sum = CalulateInfectionRisk( realSimilarity);
		if(sum == 4  )
		{
			return true;
		}
		return false;
	}
	if(!strcmp(str,"High Infection Risk" ))
	{
		int sum = CalulateInfectionRisk( realSimilarity);
		if(sum == 3  )
		{
			return true;
		}
		return false;
	}
	if(!strcmp(str,"Mid Infection Risk" ))
	{
		int sum = CalulateInfectionRisk( realSimilarity);
		if(sum == 1 || sum == 2 )
		{
			return true;
		}
		return false;
	}
	if(!strcmp(str,"Low Infection Risk" ))
	{
		int sum = CalulateInfectionRisk( realSimilarity);
		if(sum == 0  )
		{
			return true;
		}
		return false;
	}
	if(!strcmp(str,"Very Low Infection Risk" ))
	{
		int sum = CalulateInfectionRisk( realSimilarity);
		if(sum == 0  )
		{
			return true;
		}
		return false;
	}
	
	if(!strcmp(str,"Infection Rule 1" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pneumonia")))) == 100 )
		{
			return true;
		}
		return false;
	}

	if(!strcmp(str,"Infection Rule 2" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pneumonia")))) == 100 )
		{
			return true;
		}
		return false;
	}

	if(!strcmp(str,"Infection Rule 3" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pneumonia")))) == 0 )
		{
			return true;
		}
		return false;
	}
	
	if(!strcmp(str,"Calibrated COVID High Group" ))
	{
		return IsPartOFRiskGroup(highRiskProfilesHAsh ,lowRiskProfileHAsh ,  realSimilarity, true);
	}
	if(!strcmp(str,"Calibrated COVID Low Group" ))
	{
		return IsPartOFRiskGroup(lowRiskProfileHAsh , highRiskProfilesHAsh,  realSimilarity, false);
	}
	if(!strcmp(str,"Calibrated COVID Mid Group" ))
	{
		if(IsPartOFRiskGroup(highRiskProfilesHAsh ,lowRiskProfileHAsh ,  realSimilarity, true) || IsPartOFRiskGroup(lowRiskProfileHAsh , highRiskProfilesHAsh,  realSimilarity, false))
		{
			return false;
		}
		return true;
	}
	if(!strcmp(str,"Fall High Group" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange1")))) == 200 )
		{
			return true;
		}
		return false;
	}
	if(!strcmp(str,"Fall Mid Group" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange1")))) == 100 )
		{
			return true;
		}
		return false;
	}
	if(!strcmp(str,"Fall Low Group" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange1")))) == 0 )
		{
			return true;
		}
		return false;
	}

	if(!strcmp(str,"Mosre High Group" ))
	{
		bool cond1 = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth")))) > 0  || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth"), OmitFieldsIndex);
		bool cond2 = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllast6mths")))) > 0 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllast6mths"), OmitFieldsIndex);
		
		if((cond1 || cond2)	&& *(realSimilarity.GetAt(0)) > 2000)
		{
			return true;
		}
		return false;
	}
	else if(!strcmp(str,"Mosre Mid Group" ))
	{
		bool cond1 = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth")))) > 0  || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth"), OmitFieldsIndex);
		bool cond2 = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllast6mths")))) > 0 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllast6mths"), OmitFieldsIndex);
		if((cond1 || cond2)
			&& *(realSimilarity.GetAt(0)) > 1000 && *(realSimilarity.GetAt(0)) <= 2000)
		{
			return true;
		}
		return false;
	}
	else if(!strcmp(str,"Mosre Low Group" ))
	{
		bool cond1 = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth")))) > 0  || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth"), OmitFieldsIndex);
		bool cond2 = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllast6mths")))) > 0 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllast6mths"), OmitFieldsIndex);
		bool isHIgh = false;
		if((cond1 || cond2)
			&& *(realSimilarity.GetAt(0)) > 2000)
		{
			isHIgh =  true;
		}

		bool isMed = false;
		if((cond1 || cond2)
			&& *(realSimilarity.GetAt(0)) > 1000 && *(realSimilarity.GetAt(0)) <= 2000)
		{
			isMed =  true;
		}
		if(! isHIgh && ! isMed)
		{
			return true;
		}
		return false;
	}
	else if(!strcmp(str,"Delirium High Risk" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Delirium")))) >= 100  ||IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Delirium"), OmitFieldsIndex))
		{
			return true;
		}
		if(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"DeliriumA") != DUMMY_FIELD_INDEX)
		{
			if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"DeliriumA")))) >= 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"DeliriumA"), OmitFieldsIndex))
			{
				return true;
			}
		}
		return false;
	}
	else if(!strcmp(str,"Delirium Low Risk" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Delirium")))) == 0 )
		{
			return true;
		}
		return false;
	}


	else if(!strcmp(str,"Pressure Ulcer High Risk" ))
	{
		bool cond1  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel")))) > 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel"), OmitFieldsIndex);
		bool cond2  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore")))) < 1000 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore"), OmitFieldsIndex);
		bool cond3  =*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pulcer")))) >= 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pulcer"), OmitFieldsIndex);

		//if((*(realSimilarity.GetAt(0)) > 2000 && cond1&& cond2)||cond3)
		if(cond3)
		{
			return true;
		}
		return false;
	}

	else if(!strcmp(str,"Pressure Ulcer Low Risk" ))
	{
		bool cond1  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel"))))<= 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel"), OmitFieldsIndex);
		bool cond2  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore")))) >= 1200 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore"), OmitFieldsIndex);
		

		if(*(realSimilarity.GetAt(0)) < 1500 &&	cond1 && cond2)
		{
			return true;
		}
		return false;
	}
	else if(!strcmp(str,"Pressure Ulcer Medium Risk" ))
	{
		bool highRisk = false;

		bool cond1  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel")))) > 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel"), OmitFieldsIndex);
		bool cond2  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore")))) < 1000 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore"), OmitFieldsIndex);
		bool cond3  =*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pulcer")))) >= 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Pulcer"), OmitFieldsIndex);

		if((*(realSimilarity.GetAt(0)) > 2000 && cond1&& cond2)||cond3)
		{
			highRisk =  true;
		}
		

		bool lowRisk = false;

		
		cond1  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel"))))<= 100 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Bowel"), OmitFieldsIndex);
		cond2  = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore")))) >= 1200 || IsPartOfFieldsToOmit(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Mentalscore"), OmitFieldsIndex);
		

		if(*(realSimilarity.GetAt(0)) < 1500 &&	cond1 && cond2)
		{
			lowRisk =  true;
		}
		


		if(!highRisk &&  ! lowRisk)
		{
			return true;
		}
		return false;
	}
	/*
	else if(!strcmp(str,"ADL Dependency Level 1" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 1000 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 2" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 1500 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 1000 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 3" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 2100 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 1500 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 4" ))
	{
		
		if(	*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 2100 )
		{
			return  true;
		}
		return false;
	}*/
	
	else if(!strcmp(str,"EPIC RISK GRoup 1" ))
	{
		int EPICRiskGroup = CalcEPICRiskValue(realSimilarity);
		if(EPICRiskGroup == 0 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"EPIC RISK GRoup 2" ))
	{
		
		int EPICRiskGroup = CalcEPICRiskValue(realSimilarity);
		if(EPICRiskGroup == 1 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"EPIC RISK GRoup 3" ))
	{
		
		int EPICRiskGroup = CalcEPICRiskValue(realSimilarity);
		if(EPICRiskGroup == 2 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"EPIC RISK GRoup 4" ))
	{
		
		int EPICRiskGroup = CalcEPICRiskValue(realSimilarity);
		if(EPICRiskGroup== 3 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"EPIC RISK GRoup 5" ))
	{
		
		int EPICRiskGroup = CalcEPICRiskValue(realSimilarity);
		if(EPICRiskGroup == 4 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"EPIC RISK GRoup 6" ))
	{
		
		int EPICRiskGroup = CalcEPICRiskValue(realSimilarity);
		if(EPICRiskGroup == 5 )
		{
			return  true;
		}
		return false;
	}
	
	else if(!strcmp(str,"ADL Dependency Level 1" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 300 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 2" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 700 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 300 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 3" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 1100 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 700 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 4" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 1500 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 1100 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 5" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 1900 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 1500 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 6" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 2200 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 1900 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 7" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 2500 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 2200 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"ADL Dependency Level 8" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) <= 2900 &&
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"adlrange")))) > 2500 )
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"Walking Dependency Level 1" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Walking")))) <= 200 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"Walking Dependency Level 2" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Walking")))) > 100 )
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"Walking Dependency FIM Level 1" ))
	{
		int priorFunction = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Ulcertreatment1")))) ;//>=  1400
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Walking")))) < 100  && priorFunction <= 1400)
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"Walking Dependency FIM Level 2" ))
	{
		int priorFunction = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Ulcertreatment1")))) ;//>=  1400
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Walking")))) >= 100 && 
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Walking")))) < 300
			&& priorFunction <= 1400)
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"Walking Dependency FIM Level 3" ))
	{
		int priorFunction = *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Ulcertreatment1")))) ;//>=  1400
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Walking")))) >= 300 
			&& priorFunction <= 1400)
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"Transfer Dependency FIM Level 1" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"state")))) < 100 )
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"Transfer Dependency FIM Level 2" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"state")))) >= 100 && 
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"state")))) < 300)
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"Transfer Dependency FIM Level 3" ))
	{
		
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"state")))) >= 300 )
		{
			return  true;
		}
		return false;
	}


	else if(!strcmp(str,"InfectionRisk 3" ))
	{
		
		bool ind = false;
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"BladderIncontinence")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"BowelIncontinence")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Age")))) >= 8000  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ShortnessOfBreath")))) == 100   )
		{
			ind = true;
		}



		if(ind)
		{
			return  true;
		}
		return false;
	}
	else if(!strcmp(str,"InfectionRisk 2" ))
	{
		bool ind = false;
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"KidneyDisorder")))) == 100  
			)
		{
			ind = true;
		}
		if(ind)
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"InfectionRisk 1" ))
	{
		bool ind = false;
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"BladderIncontinence")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"BowelIncontinence")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Age")))) >= 8000  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ShortnessOfBreath")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Falllastmth")))) == 100  ||
			*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"KidneyDisorder")))) == 100  )
		{
			ind = true;
		}
		if(!ind)
		{
			return  true;
		}
		return false;
	}

	else if(!strcmp(str,"PriorFucntionalLimited" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Ulcertreatment1")))) >=  1400 )
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Depression" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Depression")))) ==  0 )
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Depression High no Medications" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Depression")))) ==  0 
			&& *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange2")))) == 200 
			&& *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Ulcertreatment3")))) < 200)
		{
			return true;
		}
	}



	else if(!strcmp(str,"Not Depression High" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Depression")))) ==  0 && *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange2")))) == 200 )
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Depression Mid" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Depression")))) ==  0 && *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange2")))) == 100)
		{
			return true;
		}
	}
	else if(!strcmp(str,"Not Depression Low" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Depression")))) ==  0 && *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange2")))) == 0)
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Depression Low many Medications" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Depression")))) ==  0
			&& *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange2")))) == 0
			&& *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Ulcertreatment3")))) > 100)
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Delirium High" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Delirium")))) ==  0 && *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange3")))) == 200 )
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Delirium Mid" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Delirium")))) ==  0 && *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange3")))) == 100)
		{
			return true;
		}
	}

	else if(!strcmp(str,"Not Delirium Low" ))
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"Delirium")))) ==  0 && *(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)"ADLChange3")))) == 0)
		{
			return true;
		}
	}

	
	
	if(cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)str) != DUMMY_FIELD_INDEX)
	{
		if(*(realSimilarity.GetAt((cConfiguration::GetInstance()->GetSimilarityFieldIndexByFieldName((char*)str)))) == 100 )
		{
			return true;
		}
	}
	return false;
	
}
unsigned int cConfiguration::GetSimilarityFieldIndexByFieldName(char* name )
{
	unsigned int similarityFieldIndex = DUMMY_FIELD_INDEX;
	unsigned int fieldIndex = GetFieldIndexByName(name);
	if(fieldIndex == DUMMY_FIELD_INDEX)
	{
		return DUMMY_FIELD_INDEX;
	}
	return m_targets.GetSimilarityFieldIndexByFieldIndex(fieldIndex);	

}
void cConfiguration::GetFieldNameByDisplayName(char* name, char* displayName)
{
	unsigned int fieldIndex;
	strcpy(name, displayName);
	char stndName[MAX_STRING_LENGTH];
	strcpy(stndName , (const char*)displayName);
	unsigned int numOfRemovedChars = 0;
	RemoveChar(stndName, ' ', numOfRemovedChars);
	if(m_displayNameToIndexHash.LookUp(stndName , fieldIndex))
	{
		const char* FieldName = GetFieldNameByIndex(fieldIndex);
		strcpy(name , FieldName);
	}
}
void cConfiguration::GetfieldDisplayByLanguage(char* displayName, const char* name, string_m& language)
{
	cFieldParameters* fieldInfo;
	//string_m str;
	//str.assign("0");
	strcpy(displayName , name);
	if(m_nameToFieldParametersHash.LookUp(name, fieldInfo))
	{
		int index = GetAppLanguageIndex((char*)language.c_str());
		if(index != -1)
		{
			strcpy(displayName , (char*)fieldInfo->GetFieldLanguageInfo(index).c_str());
			return;// (char*)fieldInfo->GetFieldLanguageInfo(index).c_str();
		}
	}
	return;// str;
}
void cConfiguration::FillFieldInfo (char* name, unsigned int index)
{
	if (index == 0)
	{
		string_m str;
		str.assign("Field ").append(name).append(" has index 0 which is illegal");
		throw cProfilityException(str);
	}
	if (!m_nameToIndexHash.LookUp(name, index))
	{
		m_nameToIndexHash.SetValue(name, (index - 1));

		char* string = new char[strlen(name) + 1];
		strcpy(string , name);
		m_fieldIndexToFieldNameHash.SetValue((index - 1),string);

	}
	cFieldParameters* fieldInfo;
	if(!m_nameToFieldParametersHash.LookUp(name, fieldInfo))
	{
		fieldInfo = new cFieldParameters;
		fieldInfo->SetFieldIndex(index);
		m_nameToFieldParametersHash.SetValue(name, fieldInfo);
	}
}
void cConfiguration::FillFieldAverage(char* name, float value)
{
	cFieldParameters* fieldInfo;
	if(m_nameToFieldParametersHash.LookUp(name, fieldInfo))
	{
		fieldInfo->SetFieldAverage(value);
	}
}
void cConfiguration::FillFieldMinRange(char* name, float value)
{
	cFieldParameters* fieldInfo;
	if(m_nameToFieldParametersHash.LookUp(name, fieldInfo))
	{
		fieldInfo->SetFieldMinRange(value);
	}

}
void cConfiguration::FillFieldMaxRange(char* name, float value)
{
	cFieldParameters* fieldInfo;
	if(m_nameToFieldParametersHash.LookUp(name, fieldInfo))
	{
		fieldInfo->SetFieldMaxRange(value);
	}
}

bool cConfiguration::IsPriorityProfileField(unsigned int similarityFieldIndex)
{
	cSimilarityInfo* similarityInfo = GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
	if(similarityInfo->isProfilePriorityOutputField())
	{
		return true;
	}
	return false;
}

bool cConfiguration::AddExtansionFieldToProfile(char* name,unsigned int similarityFieldIndex)
{

	cSimilarityInfo* similarityInfo = GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
	if(similarityInfo->isProfileOutputField())
	{
		return true;
	}
	return false;

	if(similarityFieldIndex == 10 || similarityFieldIndex == 11|| similarityFieldIndex == 13||similarityFieldIndex == 14||similarityFieldIndex == 15||
		similarityFieldIndex == 16 || similarityFieldIndex == 17 || (similarityFieldIndex >20 && similarityFieldIndex < 27) ||
		similarityFieldIndex == 29 || similarityFieldIndex == 30 || (similarityFieldIndex >39 && similarityFieldIndex < 41) ||
		(similarityFieldIndex >41 && similarityFieldIndex < 46)
		|| (similarityFieldIndex >52 && similarityFieldIndex < 63)|| similarityFieldIndex == 104)
	{
		return true;
	}
	return false;

	
}
void cConfiguration::IsSwitchValuesForProfileOutput(string_m& outputFieldsNames ,string_m& outputFieldsValues , char* displayName,  
	string_m& outputVal , string_m&  language,unsigned int profileFieldIndex)
{
	outputFieldsNames.assign(displayName);
	outputFieldsValues.assign(outputVal);
	return;
	if(profileFieldIndex != 7 && profileFieldIndex != 8 )
	{
		outputFieldsValues.assign(outputVal);
		return;
	}
	if(!strcmp(displayName , "Walking"))
	{
		int value = atoi((const char*)outputVal.c_str());
		if(value == 0)
		{
			outputFieldsValues.assign("Steady at all times");
		}
		else if(value == 1)
		{
			outputFieldsValues.assign("Not steady/ but able to stabilize without assistance");
		}
		else if(value == 2)
		{
			outputFieldsValues.assign("Not steady/ but able to stabilize with assistance");
		}
		else if(value == 3)
		{
			outputFieldsValues.assign("Activity does not occur");
		}
		
	}
	if(!strcmp(displayName , "Moving"))
	{
		int value = atoi((const char*)outputVal.c_str());
		if(value == 0)
		{
			outputFieldsValues.assign("Steady at all times");
		}
		else if(value == 1)
		{
			outputFieldsValues.assign("Not steady/ but able to stabilize without assistance");
		}
		else if(value == 2)
		{
			outputFieldsValues.assign("Not steady/ but able to stabilize with assistance");
		}
		else if(value == 3)
		{
			outputFieldsValues.assign("Activity does not occur");
		}
		
	}
}
const char* cConfiguration::GetFieldNameBySimilarityIndex(unsigned int SimilarityIndex)
{
	cOneTargetInfo* targetInfo = GetTargetFieldInfoByIndex(0);
	cSimilarityInfo* oneSimilarity = targetInfo->GetSimilarityInfoByIndex(SimilarityIndex);
	return GetFieldNameByIndex(oneSimilarity->GetIndex());
}



//2 5 20 new
bool cConfiguration::IsVariableJFromCatHEART( int varIndex)
{
	const char* name = GetFieldNameBySimilarityIndex(varIndex);
	if(	
		!strcmp(name, "CHF") || !strcmp(name, "SystemicVasculidities") || !strcmp(name, "CardiacDisorders")  || !strcmp(name, "CoronaryArtery") ||  !strcmp(name, "Hypertension" )  ||  !strcmp(name, "AtrialFibrillation")	
		)  		
	{
		return true;
	}
	return false;
}


//2 21 20 new functions


/*- copy from list in "2 21 20 list"
1. Diseases of the circulatory system:
Atrial fibrillation or cardiac dysrhythmias
Hypertension
Coronary artery disease
--------Myocardial infarction----   MISSING
Heart failure/CHF
CVA/stroke
Other vascular diseases
*/


bool cConfiguration::IsVariableJFromCirculatory(int &numOfCirVars, int j)
{
	numOfCirVars = 5;
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "CHF") 
		|| !strcmp(name, "SystemicVasculidities") 
		|| !strcmp(name, "CardiacDisorders") 
		|| !strcmp(name, "CoronaryArtery") 
//		||  !strcmp(name, "Hypertension" )  		
		||  !strcmp(name, "AtrialFibrillation")	
		// ||  !strcmp(name, "myCari")	
		// || !strcmp(name, "Stroke")	
	  )  		
	{
		return true;
	}

	return false;
}


/*
2. Endocrine disorders:
Hyperlipidemia
Diabetes
------Metabolic disease ---- missing
*/
bool cConfiguration::IsVariableJFromEndocrineDisorders(int &totalNumOfEndocVars, int j)
{
	totalNumOfEndocVars=2;
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "Hyperlipidemia") 
		|| !strcmp(name, "Diabetes") 
		//|| !strcmp(name, "Meta") 
	  )
	{
		return true;
	}
	return false;
}


/*
3. Mental disorders:
Dementia
Anxiety
Depression
Schizophrenia
Other psychiatric disorders
*/
bool cConfiguration::IsVariableJFromnMentalDisorders(int j)
{
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "Depression") 
		|| !strcmp(name, "Dementia")
		|| !strcmp(name, "Anxiety")
		|| !strcmp(name, "Schizophrenia")
	//	|| !strcmp(name, "sss")
	  )
	{
		return true;
	}
	return false;
}
/*
4.Infections:
Septicemia
Tuberculosis
Viral hepatitis
Other infectious diseases

WoundInfection  ?? 2 21 20 is this supposed to be here?
*/
bool cConfiguration::IsVariableJFromnInfections(int j )
{
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "Septicemia") 
		|| !strcmp(name, "Tuberculosis")
		|| !strcmp(name, "ViralHepatitis")
		|| !strcmp(name, "OtherThanPneumonia")
		//|| !strcmp(name, "s")
	  )
	{
		return true;
	}
	return false;
}

/*
5.Diseases of the nervous system:
Alzheimer
Parkinson
Other neurological disorders
*/
bool cConfiguration::IsVariableJFromNerologicalDisorders(int &numOfNeorloVars, int j)
{
	numOfNeorloVars=3;
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "Alzheimer") 
		|| !strcmp(name, "Parkinson")
		|| !strcmp(name, "NeurologicalDisorders")
		///|| !strcmp(name, "s")
		//|| !strcmp(name, "s")
	  )
	{
		return true;
	}
	return false;
}

/*
6. Diseases of the respiratory system:
Respiratory failure
Asthma
COPD
Pneumonia
*/
bool cConfiguration::IsVariableJFromPulmonaryDisorders(int &numOfPulmonaryVars, int j)
{
	numOfPulmonaryVars=4;
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "COPD") 
	//	|| !strcmp(name, "Pneumonia")
		|| !strcmp(name, "PulmonaryDisorders")
		|| !strcmp(name, "RespiratoryFailure")
		|| !strcmp(name, "ShortnessOfBreath")
	  )
	{
		return true;
	}
	return false;
}

/*
7. Diseases of the musculatory system:
Osteoporosis
Arthritis
Osteoarthritis ?? 2 21 20?
*/
bool cConfiguration::IsVariableJFromMusculatorySystems( int j)
{
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "Arthritis")  //Osteoarthritis?
		|| !strcmp(name, "Osteoporosis")
	  )
	{
		return true;
	}
	return false;
}

bool cConfiguration::IsVariableJFromBMI( int j)
{
	const char* name = GetFieldNameBySimilarityIndex(j);
	if(	!strcmp(name, "Obesity"))
	{
		return true;
	}
	return false;

	
}


//2 21 20 upd
bool cConfiguration::IsOtherComorbidityField(unsigned int j)
{

	const char* name = GetFieldNameBySimilarityIndex(j);
	if(
		
		!strcmp(name, "Hipfracture") || !strcmp(name, "Falllastmth") || !strcmp(name, "Pulcer") || !strcmp(name, "Surgicalwound")||
		
		!strcmp(name, "SpinalCordInjury") 	|| !strcmp(name, "Amputation") ||		!strcmp(name, "BrainInjury") || !strcmp(name, "Burns") || 
		
		
		 !strcmp(name, "HipReplacement") ||	 !strcmp(name, "Kneereplacement") || !strcmp(name, "OtherOrthopedic") || 
		
		!strcmp(name, "WoundInfection")|| //??
		
		
		!strcmp(name, "Gastrointestinal")
		|| !strcmp(name, "SkinDisorders")  
		|| !strcmp(name, "otherFracture")
		|| !strcmp(name, "Stroke")
//		|| !strcmp(name, "Obesity")
		||	 !strcmp(name, "Osteoarthritis")
		|| 
		
	!strcmp(name, "Anemia") || 
	
	 !strcmp(name, "KidneyDisorder")
		
		)
	{
		return true;
	}
	return false;


}
/*
//2 21 20 delete
bool cConfiguration::IsVariableJFromCatHEART( int varIndex)
{
	const char* name = GetFieldNameBySimilarityIndex(varIndex);
	if(	
		!strcmp(name, "CHF") || !strcmp(name, "SystemicVasculidities") || !strcmp(name, "CardiacDisorders")  || !strcmp(name, "CoronaryArtery") ||  !strcmp(name, "Hypertension" )  ||  !strcmp(name, "AtrialFibrillation")	
		)  		
	{
		return true;
	}
	return false;
}

*/
/*
//2 21 20 upd
bool cConfiguration::IsComorbidityField(unsigned int j)
{
	int temp =0;
	if(IsVariableJFromCirculatory(temp,j))
	{
		return true;
	}
	if( IsVariableJFromEndocrineDisorders( temp, j))
	{
		return true;
	}


	if( IsVariableJFromnMentalDisorders(  j))
	{
		return true;
	}
	if( IsVariableJFromnInfections(  j))
	{
		return true;
	}
	if( IsVariableJFromNerologicalDisorders(temp,  j))
	{
		return true;
	}
	if( IsVariableJFromPulmonaryDisorders(temp,  j))
	{
		return true;
	}
	if( IsVariableJFromMusculatorySystems(  j))
	{
		return true;
	}
	if( IsVariableJFromBMI(  j))
	{
		return true;
	}
	
	if(IsOtherComorbidityField(j))
	{
		return true;
	}


	return false;
}*/



bool cConfiguration::IsComorbidityField(unsigned int SimilarityIndex)
{
	const char* name = GetFieldNameBySimilarityIndex(SimilarityIndex);
	if(!strcmp(name, "Hipfracture") || !strcmp(name, "Falllastmth") || !strcmp(name, "Pulcer") || !strcmp(name, "Surgicalwound") || !strcmp(name, "CHF") || !strcmp(name, "COPD") || !strcmp(name, "Stroke") || !strcmp(name, "SpinalCordInjury") 
		|| !strcmp(name, "Amputation") ||
		!strcmp(name, "BrainInjury") || !strcmp(name, "Burns") || !strcmp(name, "NeurologicalDisorders") || !strcmp(name, "PulmonaryDisorders") || !strcmp(name, "HipReplacement") || !strcmp(name, "Pneumonia") 
		|| !strcmp(name, "Kneereplacement") || !strcmp(name, "OtherOrthopedic") || !strcmp(name, "WoundInfection")|| !strcmp(name, "CoronaryArtery") || !strcmp(name, "Gastrointestinal") || !strcmp(name, "SkinDisorders")  
		|| !strcmp(name, "otherFracture")
		
		|| !strcmp(name, "Obesity") || !strcmp(name, "ShortnessOfBreath") || !strcmp(name, "NeurologicalDisorders")|| !strcmp(name, "Osteoarthritis") || !strcmp(name, "SystemicVasculidities") || !strcmp(name, "CardiacDisorders")
		|| !strcmp(name, "PulmonaryDisorders") || !strcmp(name, "Anemia") || !strcmp(name, "NeurologicalDisorders")|| !strcmp(name, "Anxiety") || !strcmp(name, "Arthritis") || !strcmp(name, "Hypertension")
		|| !strcmp(name, "Osteoporosis") || !strcmp(name, "Alzheimer") || !strcmp(name, "Dementia")|| !strcmp(name, "Parkinson") || !strcmp(name, "Depression") || !strcmp(name, "Schizophrenia")
		|| !strcmp(name, "AtrialFibrillation") || !strcmp(name, "KidneyDisorder")
		
		)
	{
		return true;
	}
	return false;
	
}

const char* cConfiguration::GetFieldNameByIndex(unsigned int fieldIndex)
{
	const char* name;
	if(m_fieldIndexToFieldNameHash.LookUp(fieldIndex , name))
	{
		return name;
	}
	return 0;
}

unsigned int cConfiguration::GetFieldIndexByTypeAndIndex(char* type , unsigned int targetIndex , unsigned int index)
{
	
	cOneTargetInfo* oneTarget = GetTargetFieldInfoByIndex(targetIndex);
	unsigned int fieldIndex = 0;
	if(!strcmp(type , "Similarity"))
	{
		return (oneTarget->GetSimilarityInfoByIndex(index))->GetIndex();
	}
	else if(!strcmp(type , "Predictive"))
	{
		return ((oneTarget->GetPredictiveInfoByIndex(index))->GetIndex());
	}
	else if(!strcmp(type , "Result"))
	{
		return ((oneTarget->GetResultInfoByIndex(index))->GetIndex());
	}
	return fieldIndex;
	
}

void cConfiguration::SetIDField (char* name)
{
	unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		throw cProfilityException("ID Field doesn't exist in the input fields list");
	}

	m_idFieldIndex = index;
}

void cConfiguration::AddTargetField()
{
	m_targets.AddNewField();
}

void cConfiguration::AddTargetName(char* name, int minRange, int maxRange, int TargetIndex)
{	
	unsigned int index;
	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("Target Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}
	
	m_targets.addNewName(name, index, minRange, maxRange, TargetIndex);
	AddResultField(name, 1, 1, 1, false);
}

void cConfiguration::SetVirtualField(bool isPredictive,  unsigned int index, int targetIndex)
{
	/*unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("Predictive Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}*/

	m_targets.SetVirtualField(isPredictive,index,targetIndex);
}
void cConfiguration::SetInternalMappingRule(bool isPredictive , unsigned int index,  string_m_array& fieldNameArray,
										  FloatArray& fieldsValues, float virtualValue, int targetIndex)
{
	m_targets.SetInternalMappingRule(isPredictive, index, targetIndex,fieldNameArray, fieldsValues, virtualValue);
}
void cConfiguration::SetSingleMappingRule(bool isPredictive , unsigned int index,  string_m_array& fieldNameArray,
										  FloatArray& fieldsValues, float virtualValue, int targetIndex)
{
	m_targets.SetSingleMappingRule(isPredictive, index, targetIndex,fieldNameArray, fieldsValues, virtualValue);
}
void cConfiguration::AddPredictiveField(char* name, unsigned int predictiveIndex, int minRange, int maxRange, int targetIndex)
{
	unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("Predictive Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}
	m_targets.AddPredictiveField(name, index, predictiveIndex, minRange, maxRange, targetIndex);
	if(minRange != -10000)
	{
		FillFieldMinRange(name,minRange);
	}
	if(maxRange != 10000)
	{
		FillFieldMaxRange(name,maxRange);
	}
}

void cConfiguration::AddResultField(char* name, unsigned int resultIndex, int minRange, int maxRange, bool isConfigInput)
{
	unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("Result Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}

	if(resultIndex == 1 && isConfigInput)
	{
		throw cProfilityException("the first Result index is saved for the Target field.");
	}

	m_targets.AddResultField(name, index, resultIndex, minRange, maxRange);
}
void cConfiguration::AddMetaDataFieldDataInfo(float value,float generalAvg,float specifcAvg,string_m& metadataType,unsigned int orderIndex, 
	int similarityIndex)
{
	m_targets.AddMetaDataFieldDataInfo(value, generalAvg, specifcAvg, metadataType, orderIndex, similarityIndex);
}
void cConfiguration::AddMetaDataField(char* name, unsigned int resultIndex, int minRange, int maxRange, bool isConfigInput,
									  char* type, int dependentIndex, int referenceSimilarityIndex, bool isDynamicCalculation)
{
	unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("MetaData Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}


	m_targets.AddMetaDataField(name, index, resultIndex, minRange, maxRange, type, dependentIndex,referenceSimilarityIndex,  isDynamicCalculation);
}


void cConfiguration::AddWhatIfField()
{
	m_WhatIfInfo.AddNewField();
}

void cConfiguration::AddWhatIfName(char* name,  unsigned int WhatIFOrderIndex)
{
	unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("WhatIF Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}
	m_WhatIfInfo.AddNewName(name, index, WhatIFOrderIndex);
}

void cConfiguration::AddWhatIfValue(char* value, unsigned int ValueIndex, unsigned int WhatIFOrderIndex, unsigned int ratio)
{
	m_WhatIfInfo.AddNewValue(value, ValueIndex, WhatIFOrderIndex, ratio);
}

void cConfiguration::SetNumberOfThreads(unsigned int numberOfThreads)
{
	m_numberOfThreads = numberOfThreads;
}

void cConfiguration::SetNumOfFilesToSplit(unsigned int num)
{
	m_numOfFilesToSplit = num;
}
void cConfiguration::SetNumOfEntiresPerRecord(unsigned int num)
{
	m_numOfEntriesPerRecord = num;
}

unsigned int cConfiguration::GetNumOfServicesFields()
{
	unsigned int counter = 0;
	for(unsigned int i=0; i <GetNumOfSimilarityVars(0) ; i++ )
	{
		cSimilarityInfo* simialrityInfo =  GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(i);
		if(simialrityInfo->IsServiceField())
		{
			counter++;
		}
	}
	return counter;
}

bool cConfiguration::IsToAddFieldToProfile(unsigned int similarityIndex)
{
	cSimilarityInfo* simialrityInfo =  GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityIndex);
	return simialrityInfo->IsToAddFieldToProfile();
}

bool cConfiguration::IsManualProfileField(unsigned int similarityIndex)
{
	cSimilarityInfo* simialrityInfo =  GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityIndex);
	return simialrityInfo->IsManualProfileField();
}

unsigned int cConfiguration::GetServiceFieldSimialrityIndex(unsigned int serviceIndex)
{
	unsigned int counter = 0;
	for(unsigned int i=0; i <GetNumOfSimilarityVars(0) ; i++ )
	{
		cSimilarityInfo* simialrityInfo =  GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(i);
		if(simialrityInfo->IsServiceField())
		{
			if(serviceIndex == counter)
			{
				return i;
			}
			counter++;
		}
	}
}
	

//Ohad 30.1.17
void cConfiguration::AddSimilarityField(char* name, unsigned int weight, unsigned int SimilarityIndex,int minRange, int maxRange, bool isFloatVal,
	 bool isExtanded,bool isPredictedField,bool isOutputProfileField,bool IsProfilePriorityOutputField,bool isServiceField, unsigned int* dependentIndexArray,
	 bool isToAddToProfile, bool isManualProfileField,bool isPartOfProfile)
{
	unsigned int index;

	if(!m_nameToIndexHash.LookUp(name, index))
	{
		string_m str;
		str.assign("Similarity Field").append(name).append("does not exist in the input fields list.");
		throw cProfilityException(str);
	}
	m_targets.AddSimilarityField(name,index, weight, SimilarityIndex,minRange, maxRange,isFloatVal, isExtanded, isPredictedField,isOutputProfileField,
		IsProfilePriorityOutputField, isServiceField, dependentIndexArray,isToAddToProfile, isManualProfileField,isPartOfProfile);
	if(minRange != -10000)
	{
		FillFieldMinRange(name,minRange);
	}
	if(maxRange != 10000)
	{
		FillFieldMaxRange(name,maxRange);
	}

}
void cConfiguration::RemoveSimilarityInfo(unsigned int targetIndex)
{
	m_targets.RemoveSimilarityInfo(targetIndex);
}
void cConfiguration::RemovePredictiveInfo(unsigned int targetIndex)
{
	m_targets.RemovePredictiveInfo(targetIndex);
}

unsigned int cConfiguration::GetNumOfInputFields()
{
	return (m_nameToIndexHash.GetCount());
}

unsigned int cConfiguration::GetNumberOfTargetFields()
{
	return m_targets.GetNumberOfFields();	
}

void cConfiguration::SetInputFileName(char* fileName)
{
	m_inputFile.assign(fileName);
}
void cConfiguration::SetWorkDir(char* workDir)
{
	m_workingDir.assign(workDir);
}

void cConfiguration::SetGeneralParameterValue(unsigned int value, eGeneralInfoType type)
{
	switch(type)
	{
		case numOfTopSimilarForEditScore_e:
			m_numOfTopSimilarForEditScore = value;
			return;
	
		case Kcount_e:
			m_Kcount = value;
			return;
	
		case KcontrolCount_e:
			m_KcontrolCount = value;
			return;

		case Ncount_e:
			m_Ncount = value;
			return;
	
		case maxCountPerformanceList_e:
			m_maxCountPerformanceList = value; 
			return;
	}
}

void cConfiguration::APplyOutputDependencyRules(bool* isProfileField)
{
	for(unsigned int i=0; i < GetNumOfSimilarityVars(0); i++)
	{
	
	}
}
unsigned int cConfiguration::GetNumOfSimilarityVars(unsigned int targetFieldIndex)
{
	return (m_targets.GetTargetFieldInfoByIndex(targetFieldIndex))->GetNumberOfSimilarityFields();
}

//EEE123
void cConfiguration::SetPPICalcType(char* value, int dependentIndex)
{
	m_targets.SetPPICalcType(value,dependentIndex);
}
ePPICalcType cConfiguration::GetPPICalcType(unsigned int targetFieldIndex)
{
	return (m_targets.GetTargetFieldInfoByIndex(targetFieldIndex))->GetPPICalcType();
}
int cConfiguration::GetPPIDependentIndex(unsigned int targetFieldIndex)
{
	return (m_targets.GetTargetFieldInfoByIndex(targetFieldIndex))->GetPPIDependentIndex();
}
unsigned short cConfiguration::GetSumOfSimilarityWeights(unsigned int targetFieldIndex)
{
	return (m_targets.GetTargetFieldInfoByIndex(targetFieldIndex))->GetSumOfSimilarityWeights();
}

unsigned int cConfiguration::GetNumOfPredictiveVars(unsigned int targetFieldIndex)
{
	return (m_targets.GetTargetFieldInfoByIndex(targetFieldIndex))->GetNumberOfPredictiveFields();
}
unsigned int cConfiguration::GetNumOfResultVars(unsigned int targetFieldIndex)
{
	return (m_targets.GetTargetFieldInfoByIndex(targetFieldIndex))->GetNumberOfResultFields();
}

unsigned int cConfiguration::GetGeneralParameterVlaue(eGeneralInfoType type)
{
	switch(type)
	{
		case numOfTopSimilarForEditScore_e:
			return m_numOfTopSimilarForEditScore;
		
		case Kcount_e:
			return m_Kcount;
	
		case KcontrolCount_e:
			return m_KcontrolCount;

		case Ncount_e:
			return m_Ncount;
	
		case maxCountPerformanceList_e:
			return m_maxCountPerformanceList;
	}
	return 0;
}

void cConfiguration::FillContolledVarsInfo(decisionNodesArray& nodesArray)
{
	UIArray indexArray;
	string_m_array fieldsNames;
	BoolArray singleFieldValue;
	for(unsigned int i=0; i < nodesArray.GetSize(); i++)
	{
		unsigned int index = GetFieldIndexByName((char*)(nodesArray[i].GetName().c_str()));
		indexArray.Add(index);
		fieldsNames.Add(nodesArray[i].GetName());
	}
	m_controlledVarsManager.SetControlledFieldsIndexArray(indexArray, fieldsNames);
	m_controlledVarsManager.FillConfiguration(nodesArray);
	
}
unsigned int cConfiguration::GetNumOfWhatIfVariations()
{
	return m_WhatIFVariotionsHash.GetCount();
}
unsigned int cConfiguration::GetCombinationIndexPerControlledGroup(string_m_array& fields, FloatArray& values)
{
	return m_controlledVarsManager.GetCombinationIndexPerControlledGroup(fields, values);
}
void cConfiguration::FillFieldsValuesBasedOnCombinationIndex(unsigned int index, string_m_array& fields, FloatArray& values)
{

}
unsigned int cConfiguration::GetNumberOfControlledCombinaions()
{
	unsigned int num = 0;
	m_controlledVarsManager.GetNumofTerminalsInTree(num);
	return num;
}

void cConfiguration::CreateVariotionListForSingleWhatIFField()
{
	if(GetNumberOfWhatIfFields() == 0)
	{
		return;
	}
	cOneWhatIfinfo* oneWhatIF =  GetWhatIfInfoByIndex(0);
	short int valueArray[1];
	
	for(unsigned int i=0; i<oneWhatIF->GetNumWhatIFValues(); i++ )
	{
		valueArray[0] = oneWhatIF->GetValueByIndex(i);

		string_m variotion;
		
		CreateWhatIFVariotion(variotion, valueArray);

		cWhatIFVariotionInfo* variotionInfo = new cWhatIFVariotionInfo;
		variotionInfo->SetVariotionInfo(i, oneWhatIF->GetRatioByIndex(i));
		m_WhatIFVariotionsHash.SetValue(variotion.c_str(), variotionInfo);
		char* string = new char[variotion.length() + 1];
		strcpy(string, variotion.c_str());
		m_WhatIFVariotionsIndexHash.SetValue(i,string);
	}
}

/*
void cConfiguration::CreateVariotionList(unsigned int WhatIfFieldNum, short int* valueArray, unsigned int& variotionIndex)
{
	if(WhatIfFieldNum == m_WhatIfInfo.GetNumberOfFields())
	{
		char variotion[1000];// ASK DIma
		variotion[0] = (char)0;
		CreateWhatIFVariotion(variotion, valueArray);
		
		cWhatIFVariotionInfo* variotionInfo = new cWhatIFVariotionInfo;
		variotionInfo->SetVariotionInfo(variotionIndex,(unsigned int)100000);
		m_WhatIFVariotionsHash.SetValue(variotion, variotionInfo);
		variotionIndex++;
		return;
	}
	
	cOneWhatIfinfo* oneWhatIF =  GetWhatIfInfoByIndex(WhatIfFieldNum);
	for(unsigned int j = 0;j < oneWhatIF->GetNumWhatIFValues(); j++ )
	{
		valueArray[WhatIfFieldNum] = oneWhatIF->GetValueByIndex(j); 
		CreateVariotionList((WhatIfFieldNum + 1), valueArray, variotionIndex);
	}
	
	
}
*/

void cConfiguration::CreateWhatIFVariotion(string_m& variotion, short int *whatIfVarArray)
{

	for(unsigned int i = 0; i < m_WhatIfInfo.GetNumberOfFields(); i++)
	{
		if(i > 0)
		{
			variotion.append("!");

		}
		variotion.appendNum(whatIfVarArray[i]);
	}
}

short int* cConfiguration::CreateWhatIFVariotionValues(string_m variotion)
{
	short int* whatIfVar = new short int[GetNumberOfWhatIfFields()];
	string_m_array strs;

	size_t numOfFields = variotion.split_fields(strs, '|');

	if (numOfFields != GetNumberOfWhatIfFields())
	{
		delete[] whatIfVar;
		return 0;
	}

	for(unsigned int i = 0 ;  i < GetNumberOfWhatIfFields(); i++)
	{
		whatIfVar[i] = (short int)atoi(strs[i].c_str());
	}

	return whatIfVar;
}

unsigned int cConfiguration::GetWhatIfVariationIndex(short int* whatIfVarArray)
{
	string_m variotion;

	CreateWhatIFVariotion(variotion, whatIfVarArray);
	cWhatIFVariotionInfo* variotionInfo;

	if(m_WhatIFVariotionsHash.LookUp(variotion.c_str(), variotionInfo))
	{
		return variotionInfo->GetVariotionIndex();
	}
	return 0;
}

cWhatIFVariotionInfo* cConfiguration::GetWhatIFVariotionInfoByIndex(unsigned int variationIndex)
{
	const char* variotionStr;
	cWhatIFVariotionInfo* oneVar;

	if(!m_WhatIFVariotionsIndexHash.LookUp(variationIndex, variotionStr)) return NULL;	
	
	short int* oneVariation = GetWhatIfVariationByIndex(variationIndex);
	if(!m_WhatIFVariotionsHash.LookUp(variotionStr , oneVar))return NULL;

	return oneVar;
}



short int* cConfiguration::GetWhatIfVariationByIndex(unsigned int variationIndex)
{
	const char* variotionStr;

	if(!m_WhatIFVariotionsIndexHash.LookUp(variationIndex, variotionStr)) return NULL;

	string_m variotion;
	variotion.assign(variotionStr);
	return CreateWhatIFVariotionValues(variotion);
}

cOneTargetInfo* cConfiguration::GetTargetFieldInfoByIndex(unsigned int index)
{
	return m_targets.GetTargetFieldInfoByIndex(index);
}

unsigned int cConfiguration::GetNumOfExtentionFields()
{
	unsigned int counter = 0;
	for(unsigned int i=0; i<GetTargetFieldInfoByIndex(0)->GetNumberOfSimilarityFields();i++)
	{
		cSimilarityInfo* similarityInfo = GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(i);
		if(similarityInfo->isExtandedField())
		{
			counter++;
		}
	}
	return counter;
}
	

unsigned int cConfiguration::GetNumberOfWhatIfFields()
{
	return m_WhatIfInfo.GetNumberOfFields();
}

cOneWhatIfinfo* cConfiguration::GetWhatIfInfoByIndex(unsigned int index)
{
	return m_WhatIfInfo.GetWhatIfFieldInfoByIndex(index);
}

//the size of these two arrays is as the number of "what if variations" (not what if vars!) .
//the whatIfArraysCount is the input and the whatifWeights is the output. the algorithm will be based on relative compare
//to the population. if we have 3 what if variations, and you get the population size in the config as 
//1: 100,000, 2: 200,000, 3: 300,000 ,  and if  whatIfArraysCount shows you  1: 1,000, 2: 2,000, 3:2,000 
//than the weights that you should calculate of the different variations
//will be : 1 : (1,000/5,000 ) / (100,000 / 600,000)     =  0.2 / 0.166  = ~ 1.25 .2:3:

void cConfiguration::FillGeneralVariotinWeights(unsigned int* arrayWeight)
{
	const char* variotion;
	cWhatIFVariotionInfo* variotionInfo;
	StringToWhatIfVariotionInfoHash::sPosition *variotionPos = m_WhatIFVariotionsHash.GetFirst(variotion, variotionInfo);
	while(variotionPos)
	{
		arrayWeight[variotionInfo->GetVariotionIndex()] = variotionInfo->GetVariotionRatio();
		m_WhatIFVariotionsHash.GetNextKey(variotionPos, variotion, variotionInfo);
		
	}
}

unsigned int cConfiguration::SumVarionWeight(unsigned int* arrayWeight)
{
	unsigned int sum = 0;
	for(unsigned int i=0; i < GetNumOfWhatIfVariations(); i++)
	{
		sum += arrayWeight[i];
	}
	return sum;
}

void cConfiguration::FillWhatIfVariationWeight(float* whatifVariationWeights, unsigned int* whatIfArraysCount)
{
	unsigned int* generalVariotionsWeights =  new unsigned int[GetNumOfWhatIfVariations() + 1];
	FillGeneralVariotinWeights(generalVariotionsWeights);
	unsigned int SumOFGeneralVarionWeight = SumVarionWeight(generalVariotionsWeights);
	unsigned int SumOFCurrentVarionWeight = SumVarionWeight(whatIfArraysCount);

	for(unsigned int i=0; i < GetNumOfWhatIfVariations(); i++)
	{
		whatifVariationWeights[i] = 
			((float)(whatIfArraysCount[i]) / (float)SumOFCurrentVarionWeight) / 
			((float)(generalVariotionsWeights[i]) / (float)SumOFGeneralVarionWeight);
	}
	delete[] generalVariotionsWeights;
}

unsigned int cConfiguration::GetPredectibilityScoreIndex()
{
	return GetNumOfFieldsIncludingExtra() - 1;
}

unsigned int cConfiguration::GetNumOfExtraFields()
{
	unsigned int numberOfExtraFields = 0;

	for (unsigned int i = 0; i < m_targets.GetNumberOfFields(); i++)
	{
		numberOfExtraFields += (m_targets.GetTargetFieldInfoByIndex(i)->GetNumberOfSimilarityFields() * 2);
	}

	// we are adding 1 for predectibility score and 1 for numID
	return (numberOfExtraFields + 2);
}

unsigned int cConfiguration::GetNumIDFieldIndex()
{
	return GetNumOfFieldsIncludingExtra() - 2;
}

unsigned int cConfiguration::GetNumOfFieldsIncludingExtra()
{
	return GetNumOfExtraFields() + m_nameToIndexHash.GetCount();
}

void cConfiguration::SetNumberOfDataLines(unsigned int value)
{
	m_numberOfDataLines = value;
}

void cConfiguration::ValidateTargetData()
{
	m_targets.ValidateTargetData(GetNumOfInputFields());
}

void cConfiguration::ValidateWhatIFData()
{
	m_WhatIfInfo.ValidateWhatIFData(GetNumOfInputFields());
}
void cConfiguration::OrgenizeConfigurationData()
{
	UpdatePredictiveInfo();
	m_mostUpdatedBinaryFilePath.assign(GetWorkingDirectory()).append(SLASH_SIGH).append("most_updated_profile_binary").append(".bin");
}
void cConfiguration::UpdatePredictiveInfo()
{
	for (unsigned int i = 0; i < m_targets.GetNumberOfFields(); i++)
	{
		m_targets.GetTargetFieldInfoByIndex(i)->UpdatePredictiveInfo();
	}

}
void cConfiguration::SetLogType(char* type)
{
	if(!strcmp(type, "DEBUG_MODE"))
	{
		m_logType = debug_e;
	}
	else
	{
		m_logType = info_e;
	}
}
void cConfiguration::SetOneRuleCondition(string_m fieldName, string_m conditionStr, float conditionVal)
{
	unsigned int index;

	if(m_nameToIndexHash.LookUp(fieldName, index))
	{
		m_targets.SetOneRuleCondition(index, conditionStr, conditionVal);
	
	}
}

void cConfiguration::SetOneRuleTargetCondition(string_m conditionStr, float conditionVal, unsigned int actionIndex )
{
	m_targets.SetOneRuleTargetCondition(conditionStr, conditionVal, actionIndex);
}

void cConfiguration::SetOneRuleAction(string_m actionStr, float actionVal, string_m fieldName)
{
	unsigned int index = 0;
	if(fieldName.c_str())
	{
		m_nameToIndexHash.LookUp(fieldName, index);
	}
	m_targets.SetOneRuleAction(actionStr, actionVal, index);
}
void cConfiguration::SetPopulationPercentage(unsigned int populationPercentage)
{
	m_targets.SetPopulationPercentage(populationPercentage);
}
void cConfiguration::SetRulesWeight(unsigned int weight)
{
	m_targets.SetRulesWeight(weight);
}
void cConfiguration::AddRule()
{
	m_targets.AddRule();
}
unsigned int cConfiguration::GetFieldIndexByName(char* name)
{
	unsigned int index = DUMMY_FIELD_INDEX;
	m_nameToIndexHash.LookUp(name, index);
	return index;
}

float cConfiguration::GetFieldAverageByName(char* name)
{
	float average = 0.0;
	cFieldParameters* fieldInfo = NULL;
	m_nameToFieldParametersHash.LookUp(name, fieldInfo);
	if(fieldInfo)
	{
		average = fieldInfo->GetAverage();
	}
	return average;
}

float cConfiguration::GetFieldMinByName(char* name)
{
	float min = -10000.0f;
	cFieldParameters* fieldInfo = NULL;
	m_nameToFieldParametersHash.LookUp(name, fieldInfo);
	if(fieldInfo)
	{
		min = fieldInfo->GetMinRange();
	}
	return min;
}
float cConfiguration::GetFieldMaxByName(char* name)
{
	float max = 10000.0f;
	cFieldParameters* fieldInfo = NULL;
	m_nameToFieldParametersHash.LookUp(name, fieldInfo);
	if(fieldInfo)
	{
		max = fieldInfo->GetMaxRange();
	}
	return max;
}



void cConfiguration::FillFieldValueForFlatFile(char* value, char* fieldName)
{
	unsigned int fieldIndex = GetFieldIndexByName(fieldName);
	m_data.SetAt(fieldIndex, value);

}
void cConfiguration::AddPersonToFlatFile()
{
	string_m outputLine;
	string_m val;
	for(unsigned int i=0; i < GetNumOfInputFields(); i++)
	{
		outputLine.append((m_data.GetAt(i))->c_str());
		if((i + 1) < GetNumOfInputFields())
		{
			outputLine.append("\t");
		}
		//val.appendNum(0);
		val.assign("0");
		m_data.SetAt(i , val.c_str());
	}
	m_flatFile.AddLine(outputLine.c_str());
	m_flatFile.AddLine("\n");
}
void cConfiguration::SetInfoForFlatCOnversion(string_m& fileName)
{
	m_data.SetSize(GetNumOfInputFields());
	for(unsigned int i=0; i < GetNumOfInputFields(); i++)
	{
		m_data.SetAt(i , "0");
	}
	fileName.assign(GetInputFileName());
	fileName.append(".dat");
	if(!(m_flatFile.OpenFile(fileName.c_str())))
	{
		return;
	}
	
}
void cConfiguration::CloseFlatFile()
{
	m_flatFile.CloseFile();
}


void cConfiguration::SetMediumVarianceRatio(float ratio)
{
	m_mediumVarinaceRatio = ratio;
}
void cConfiguration::SetStrongVarianceRatio(float ratio)
{
	m_strongVarinaceRatio = ratio;
}

void cConfiguration::SetMaxNumberOfSimilarityFieldsInProfile(unsigned int value)
{
	m_maxSimilarityFieldsInProfile = value;
}
void cConfiguration::SetNumberOfPercentilesForOutput(unsigned int value)
{
	m_numberOfPercentiles = value;
}


void cConfiguration::SetDataManipulatedCombination(float source, float target)
{
	short roundedValue = (short)(source * MULTIPLIER);	
	short* roundedTarget;
	if(!m_manipulatedDataValuesHash.LookUp(roundedValue ,roundedTarget))
	{
		roundedTarget = new short;
		*roundedTarget =(short)(target * MULTIPLIER) ;
		m_manipulatedDataValuesHash.SetValue(roundedValue ,roundedTarget);
	}
}
bool cConfiguration::isToManipulateDataValue(float source , float& target)
{
	short roundedValue = (short)(source * MULTIPLIER);
	short* roundedTarget;
	if(m_manipulatedDataValuesHash.LookUp(roundedValue ,roundedTarget))
	{
		target = (float)(*roundedTarget);
		return true;
	}
	return false;
}

void  cConfiguration::SetEvolutionTestWeightAdjustmet(float val)
{
	m_evolutiontestWeightAdjustment = val;
}
void cConfiguration::SetEvolutionOverallWeightAdjustmet(float val)
{
	m_evolutionOverallWeightAdjustment = val;
}

void cConfiguration::SetOutputRegressionFlag(bool flag)
{
	m_outputRegressionFlag = flag;
}

void cConfiguration::SetProfileCalculationMode(char* mode)
{
	strcpy((char*)m_profileCalcMode.c_str(), mode);
}

void cConfiguration::SetExpoTestParameter(string_m& name, string_xl& value)
{
	m_testParametersNames.Add(name);
	m_testParametersVals.Add(value);
}
void cConfiguration::ExpandTestCases(unsigned int index, unsigned int& caseIndex, string_m_array& caseValuesList)
{
	if(index == m_testParametersNames.GetSize())
	{
		SetTestCaseID(caseIndex);
		caseIndex++;
		for(unsigned int i=0; i < m_testParametersNames.GetSize(); i++)
		{
			string_m name = *(m_testParametersNames.GetAt(i));
			string_m value = *(caseValuesList.GetAt(i));
			SetTestCaseParameter(name, value);
		}
		return;
	}
	string_xl allVals = *(m_testParametersVals.GetAt(index));
	string_m currVal;
	unsigned int pos = 0;
	unsigned int numOfValues = GetNumWords((char*)allVals.c_str(), ',');
	char word[1000];
	unsigned int valueIndex = 0;
	for(unsigned int i=0; i < numOfValues; i++)
	{
		
		valueIndex += (1+ GetWord(word , (char*)allVals.c_str(), valueIndex, ','));
		currVal.assign(word);
		caseValuesList.Add(currVal);
		//caseValuesList.SetAt(index, currVal);
		ExpandTestCases(index+1, caseIndex, caseValuesList);
		caseValuesList.RemoveLast();
	}
}

int cConfiguration::GetNumWords(char* array, char delimiter)
{
	int counter = 1;

	for(int i = 0; array[i] != '\0'; i++)
	{
		if(array[i] == delimiter)
		{
			counter++;
		}
	}
	return counter;
}

int cConfiguration::GetWord(char* out, const char* input, int inputStartIndex, char delimiter)
{
	int i;

	for(i = 0; (input[inputStartIndex + i] != delimiter) && (input[inputStartIndex + i] != '\0'); i++)
	{
		out[i] = input[inputStartIndex + i];
	}
	out[i] = '\0';
	return i;
}


bool cConfiguration::IsGeneralTerm(string_m str)
{
	int dummy;
	if(m_termsHash.LookUp(str,dummy))
	{
		return true;
	}
	return false;

}


void cConfiguration::SetTestCaseID(unsigned int id)
{
	cTestCase* testCase = new cTestCase;
	testCase->SetCaseID(id);
	m_testCases.Add(testCase);
	m_numberOfTestCases++;
}
void cConfiguration::AddCareSettingToConsider(char* careSetting)
{
	unsigned int careSettingCode;
	if(!strcmp("SNF",careSetting))
	{
		careSettingCode = SNF_CARE_SETTING_CODE;
	}
	else if(!strcmp("IRF",careSetting))
	{
		careSettingCode = IRF_CARE_SETTING_CODE;
	}
	else if(!strcmp("HH",careSetting))
	{
		careSettingCode = HH_CARE_SETTING_CODE;
	}
	m_careSettingToConsider.Add(careSettingCode);
}
void cConfiguration::SetTestCaseParameter(string_m name, string_m value)
{
	cTestCase* testCase = *(m_testCases.GetAt(m_numberOfTestCases-1));
	testCase->AddParameter(name,value);
}
unsigned int cConfiguration::GetNumberOfTestCases()
{
	return m_numberOfTestCases;
}
cTestCase* cConfiguration::GetASingleTestCAseByIndex(unsigned int index)
{
	return *(m_testCases.GetAt(index));
}

void cConfiguration::SetConfigParameter(string_m& name, string_m value)
{
	if(!strcmp((char*)name.c_str() , "OutputTraditionalRegressionInfo"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetOutputRegressionFlag(val);
	}
	if(!strcmp(name.c_str(), "NumberOFRunTimeIteration"))
	{
		SetNumberOFRUNTIMEIteration((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "SimplePredictionIteration"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetSimplePredictionEvaluation(val);
	}
	if(!strcmp(name.c_str(), "LLevelErrorEvaluation"))
	{
		SetLLevelErrorEvaluation(atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "CoreVectorWeightChange"))
	{
		SetCoreVectorWeightChange((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "IsAdjustErrorReducPerAvgControlGrp"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsAdjustErrorReducPerAveControlGrp(val);
	}
	if(!strcmp(name.c_str(), "MultipleCoreVectorWeightChange"))
	{
		SetMultipleCoreVectorWeightChange((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PercentSumAllRegression"))
	{
		SetPercentSumAllRegression((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "DynamicSeekAddConstant"))
	{
		SetDynamicSeekAddConstant((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "ExponentialEditDistanceScoreConst"))
	{
		SetExponentialEditDistanceScoreConst((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PercDelutionPredVars"))
	{
		SetPercDelutionPredVars((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "ExponensialConstantForPredict"))
	{
		SetExponensialConstantForPredict((float)atof(value.c_str()));
	}
	
	if(!strcmp(name.c_str(), "ExactMatchRatio"))
	{
		SetExactMatchRatio((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PercSimilarInMidSizeArray"))
	{
		SetPercSimilarInMidSizeArray((float)atof(value.c_str()));
	}
	
	if(!strcmp(name.c_str(), "PercRemoveFrequentExactMatch"))
	{
		SetPercRemoveFrequentExactMatch((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "TotalPercRemoveLowPerfomaceSimVars"))
	{
		SetTotalPercRemoveLowPerfomaceSimVars((float)atof(value.c_str()));
	}
	
	if(!strcmp(name.c_str(), "MaxEDForNGroupAllowed"))
	{
		SetMaxEDForNGroupAllowed((float)atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "MaxEDForKregGroupAllowed"))
	{
		SetMaxEDForKregGroupAllowed((float)atof(value.c_str()));
	}

	if(!strcmp(name.c_str(), "AditionalEvolutionVectorValue"))
	{
		SetAditionalEvolutionVectorValue((float)atof(value.c_str()));
	}

	if(!strcmp(name.c_str(), "LinearConstEvolution"))
	{
		SetLinearConstEvolution((float)atof(value.c_str()));
	}

	if(!strcmp(name.c_str(), "VectorIncEvolution"))
	{
		SetVectorIncEvolution((float)atof(value.c_str()));
	}

	
	
	
	
	
	
	if(!strcmp(name.c_str(), "PredictKCountEvolution"))
	{
		SetPredictKCountEvolution((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PredictKCountCohortEvo"))
	{
		SetPredictKCountCohortEvo((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PredictKEvolutionFinal"))
	{
		SetPredictKEvolutionFinal((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PredictNConstant"))
	{
		SetPredictNConstant(atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "SizeOfLPGroupMedium"))
	{
		SetSizeOfLPGroupMedium(atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "ConstDecreaseScorePreviousSample"))
	{
		SetConstDecreaseScorePreviousSample(atoi(value.c_str()));
	}
	
	
	if(!strcmp(name.c_str(), "IncreasePredCntForKcountEvoArr"))
	{
		SetIncreasePredCntForKcountEvoArr(atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "NumOfVariablesParticipateInTriples"))
	{
		SetNumOfVariablesParticipateInTriples(atoi(value.c_str()));
	}
	
	
	if(!strcmp(name.c_str(), "ExpoValueToDifferentiateTestGroup"))
	{
		SetExpoValueToDifferentiateTestGroup(atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "LocalGenVectorEvolution"))
	{
		SetLocalGenVectorEvolution(atof(value.c_str()));
	}
	
	if(!strcmp(name.c_str(), "LocalGenVectorWeight"))
	{
		SetLocalGenVectorWeight(atof(value.c_str()));
	}

	if(!strcmp(name.c_str(), "EXPForCutExtremePredict"))
	{
		SetEXPForCutExtremePredict(atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "EXPForCutExtreme"))
	{
		SetEXPForCutExtreme(atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PercTestStartValue"))
	{
		SetPercTestStartValue(atof(value.c_str()));
	}
	if(!strcmp(name.c_str(), "PercTestEndValue"))
	{
		SetPercTestEndValue(atof(value.c_str()));
	}
	
	
	
	if(!strcmp(name.c_str(), "MinSDAllowedForRegression"))
	{
		SetMinSDAllowedForRegression((unsigned int)atoi(value.c_str()));
	}
	
	if(!strcmp(name.c_str(), "MinGroupCountForEvoTest"))
	{
		SetMinGroupCountForEvoTest((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "NumOfRandomOutputVaiationPerfomanceProcessing"))
	{
		SetNumOfRandomOutputVaiationPerfomanceProcessing((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "NumOfVariablesSimFormulaChangeEvolution"))
	{
		SetNumOfVariablesSimFormulaChangeEvolution((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "NumberOfManipulationVariables"))
	{
		SetNumberOfManipulationVariables((unsigned int)atoi(value.c_str()));
	}

	

	

	
	
	if(!strcmp(name.c_str(), "PredictKCountForMeta"))
	{
		SetPredictKCountForMeta((unsigned int)atoi(value.c_str()));
	}

	if(!strcmp(name.c_str(), "PredictKCount"))
	{
		SetPredictKCount((unsigned int)atoi(value.c_str()));
	}
	if(!strcmp(name.c_str(), "SmallSizeArraySize"))
	{
		SetSmallSizeArray((unsigned int)atoi(value.c_str()));
	}
	
	if(!strcmp(name.c_str(), "MidSizeArraySize"))
	{
		SetMidSizeArray((unsigned int)atoi(value.c_str()));
	}

	if(!strcmp(name.c_str(), "IsControlGroupStableAcrossGeneration"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsControlGroupStableAcrossGeneration(val);
	}

	if(!strcmp(name.c_str(), "IsSymetricTestAll"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsSymetricTestAll(val);
	}
	if(!strcmp(name.c_str(), "IsToSetDefaultSimfromRegBeta"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsToSetDefaultSimfromRegBeta(val);
	}

	
	if(!strcmp(name.c_str(), "IsRegressionBasedCNTRGrpAvgDelta"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsRegressionBasedCNTRGrpAvgDelta(val);
	}
	if(!strcmp(name.c_str(), "IsFlaggedRequiredForLinearMetaRegression"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsFlaggedRequiredForLinearMetaRegression(val);
	}
	if(!strcmp(name.c_str(), "IsCleanFlaggedImpY"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsCleanFlaggedImpY(val);
	}
	if(!strcmp(name.c_str(), "IsAdjustYValuesWithMean"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsAdjustYValuesWithMean(val);
	}
	if(!strcmp(name.c_str(), "AdjustPetImpOnlyAllowed"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetAdjustPetImpOnlyAllowed(val);
	}

	if(!strcmp(name.c_str(), "IsRegStatForMSDUniversal"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsRegStatForMSDUniversal(val);
	}
	if(!strcmp(name.c_str(), "IsSimplePredict"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsSimplePredict(val);
	}
	if(!strcmp(name.c_str(), "IsCuttingDependentExtreme"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsCuttingDependentExtreme(val);
	}
	if(!strcmp(name.c_str(), "IsSimpleMethodOfChildPrediction"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsSimpleMethodOfChildPrediction(val);
	}
	if(!strcmp(name.c_str(), "IsMeanOnly"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsMeanOnly(val);
	}
	if(!strcmp(name.c_str(), "IsWithFeatureSelection"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsWithFeatureSelection(val);
	}
	
	
	if(!strcmp(name.c_str(), "IsWithADJSimForKN"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsWithADJSimForKN(val);
	}

	if(!strcmp(name.c_str(), "IsAddSortToKNForTest"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsAddSortToKNForTest(val);
	}
	if(!strcmp(name.c_str(), "IsDevidingPerfomanceToParentError"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsDevidingPerfomanceToParentError(val);
	}
	if(!strcmp(name.c_str(), "IsFullControlGroupEvolution"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsFullControlGroupEvolution(val);
	}
	
	
	if(!strcmp(name.c_str(), "IsExponUpgradeForTestGroupSimilar"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsExponUpgradeForTestGroupSimilar(val);
	}
	
	if(!strcmp(name.c_str(), "IsDivideByVarEvolution"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsDivideByVarEvolution(val);
	}
	if(!strcmp(name.c_str(), "IsCompareSetToZeroFormula"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsCompareSetToZeroFormula(val);
	}
	if(!strcmp(name.c_str(), "IsCompareSetToStraightFormula"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsCompareSetToStraightFormula(val);
	}
	if(!strcmp(name.c_str(), "IsExtremeCutUsingUniversal"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsExtremeCutUsingUniversal(val);
	}
	if(!strcmp(name.c_str(), "IsStandardPredictiveValuesProfileBased"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsStandardPredictiveValuesProfileBased(val);
	}

	

	if(!strcmp(name.c_str(), "IsWithSubSetTestGroup"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsWithSubSetTestGroup(val);
	}
	if(!strcmp(name.c_str(), "IsStartLinearContTestGrpZero"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsStartLinearContTestGrpZero(val);
	}
	if(!strcmp(name.c_str(), "IsWithSemiRandomPredictiveSelection"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsWithSemiRandomPredictiveSelection(val);
	}
	if(!strcmp(name.c_str(), "IsDefaultFormulaByRegression"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsDefaultFormulaByRegression(val);
	}
	
	
	if(!strcmp(name.c_str(), "IsOnlyProfilePrediction"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsOnlyProfilePrediction(val);
	}
	if(!strcmp(name.c_str(), "IsToShiftDepPerfByMeanEvolution"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsToShiftDepPerfByMeanEvolution(val);
	}

	if(!strcmp(name.c_str(), "IsToIncludePreviousWeightsInCurrentInternReg"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsToIncludePreviousWeightsInCurrentInternReg(val);
	}
	if(!strcmp(name.c_str(), "IsTestVersion"))
	{
		bool val = false;
		if(!strcmp((char*)value.c_str() , "yes"))
		{
			val = true;
		}		
		SetIsTestVersion(val);
	}
	
	
	if(!strcmp(name.c_str(), "SimilarityAndPredictive"))
	{
		RemoveSimilarityInfo(0);
		RemovePredictiveInfo(0);
		char* del;
		char* start;
		char* end;
		char fieldName[1000];
		del = (char*)strstr(value.c_str() , "|");
		start = (char*)value.c_str();
		char similarity[100000];
		char predictive[100000];
		strncpy(similarity, start , (del - start));
		similarity[del - start] = 0;
		strncpy(predictive, del+1 , (strlen(del+1)));
		predictive[strlen(del+1)] = 0;
		
		FillSimilarityAndPredictiveFields(similarity, "similarity");
		FillSimilarityAndPredictiveFields(predictive, "predictive");

		UpdatePredictiveInfo();
	}	
}
void cConfiguration::FillSimilarityAndPredictiveFields(char* input , char* type)
{
	unsigned int index  = 1;
	char* start = input;
	char* end;
	char fieldName[1000];
	while(start)
	{
		unsigned int len = 0;
		end = (char*)strstr(start , "-");
		if(end == NULL)
		{
			len = strlen(start);
		}
		else
		{
			len = end - start;
		}
		if(len == 0)
		{
			break;
		}
		strncpy(fieldName, start , len);
		fieldName[len] = '\0';
		unsigned int fieldIndex = GetFieldIndexByName(fieldName);
		int min = (int)GetFieldMinByName(fieldName);
		int max = (int)GetFieldMaxByName(fieldName);
		if(!strcmp(type , "similarity"))
		{
			//Ohad 30.1.17
			AddSimilarityField(fieldName, 1, index,min, max,false,false,true,false,false,false,NULL,false,false,false);
		}
		else
		{
			AddPredictiveField(fieldName,index,min,max);
		}
		if(end == NULL)
		{
			break;
		}
		start = end+1;
		index++;
	}

}
void cConfiguration::SetNumberOFRUNTIMEIteration(unsigned int value)
{
	m_numOfIterationForRunTime = value;
}

void cConfiguration::SetNumberOfValuesForInteligentPrediction(unsigned int value)
{
	m_numberOfValuesForInteligentPrediction = value;
}

void cConfiguration::SetBasicFieldIndex(unsigned int value)
{
	m_basicFieldIndex = value;
}
void cConfiguration::SetNumberOfItemsForLongProfile(unsigned int value)
{
	m_numberOfItemsForLongProfile = value;
}

void cConfiguration::SetPredictKCountEvolution(unsigned int value)
{
	m_predictKCountEvolution = value;
}
void cConfiguration::SetPredictKCountCohortEvo(unsigned int value)
{
	m_predictKCountCohortEvo = value;
}
void cConfiguration::SetPredictKEvolutionFinal(unsigned int value)
{
	m_PredictKEvolutionFinal = value;
}
void cConfiguration::SetSizeOfLPGroupMedium(unsigned int value)
{
	m_SizeOfLPGroupMedium = value;
}
void cConfiguration::SetConstDecreaseScorePreviousSample(unsigned int value)
{
	m_ConstDecreaseScorePreviousSample = value;
}

void cConfiguration::SetIncreasePredCntForKcountEvoArr(unsigned int value)
{
	m_IncreasePredCntForKcountEvoArr = value;
}

void cConfiguration::SetNumOfVariablesParticipateInTriples(unsigned int value)
{
	m_NumOfVariablesParticipateInTriples = value;
}


void cConfiguration::SetPredictNConstant(float value)
{
	m_PredictNConstant = value;
}
void cConfiguration::SetExpoValueToDifferentiateTestGroup(float value)
{
	m_ExpoValueToDifferentiateTestGroup = value;
}

void cConfiguration::SetLocalGenVectorEvolution(float value)
{
	m_LocalGenVectorEvolution = value;
}
void cConfiguration::SetLocalGenVectorWeight(float value)
{
	m_LocalGenVectorWeight = value;
}
void cConfiguration::SetEXPForCutExtremePredict(float value)
{
	m_EXPForCutExtremePredict = value;
}
void cConfiguration::SetEXPForCutExtreme(float value)
{
	m_EXPForCutExtreme = value;
}

void cConfiguration::SetPercTestStartValue(float value)
{
	m_PercTestStartValue = value;
}
void cConfiguration::SetPercTestEndValue(float value)
{
	m_PercTestEndValue = value;
}


void cConfiguration::SetMinSDAllowedForRegression(unsigned int value)
{
	m_MinSDAllowedForRegression = value;
}

void cConfiguration::SetMinGroupCountForEvoTest(unsigned int value)
{
	m_MinGroupCountForEvoTest = value;
}

void cConfiguration::SetNumOfRandomOutputVaiationPerfomanceProcessing(unsigned int value)
{
	m_NumOfRandomOutputVaiationPerfomanceProcessing = value;
}

void cConfiguration::SetNumOfVariablesSimFormulaChangeEvolution(unsigned int value)
{
	m_NumOfVariablesSimFormulaChangeEvolution = value;
}
void cConfiguration::SetNumberOfManipulationVariables(unsigned int value)
{
	m_NumberOfManipulationVariables = value;
}


unsigned int cConfiguration::GetPredictKCountForMeta()
{
	return m_predictKCountForMeta;
}
void cConfiguration::SetPredictKCountForMeta(unsigned int value)
{
	m_predictKCountForMeta = value;
}
void cConfiguration::SetPredictKCount(unsigned int value)
{
	m_predictKCount = value;
}
void cConfiguration::SetIsControlGroupStableAcrossGeneration(bool value)
{
	m_isControlGroupStableAcrossGeneration = value;
}

void cConfiguration::SetIsSymetricTestAll(bool value)
{
	m_isSymetricTestAll = value;
}
void cConfiguration::SetIsToSetDefaultSimfromRegBeta(bool value)
{
	m_IsToSetDefaultSimfromRegBeta = value;
}



void cConfiguration::SetIsRegressionBasedCNTRGrpAvgDelta(bool value)
{
	m_isRegressionBasedCNTRGrpAvgDelta = value;
}

void cConfiguration::SetIsFlaggedRequiredForLinearMetaRegression(bool value)
{
	m_isFlaggedRequiredForLinearMetaRegression = value;
}
void cConfiguration::SetIsCleanFlaggedImpY(bool value)
{
	m_isCleanFlaggedImpY = value;
}
void cConfiguration::SetIsDynamicResultVal(bool value)
{
	m_IsDynamicResultVal = value;
}
void cConfiguration::SetIsWithForcingSim(bool value)
{
	m_isWithForcingSim = value;
}

void cConfiguration::SetIsAdjustYValuesWithMean(bool value)
{
	m_isAdjustYValuesWithMean = value;
}

void cConfiguration::SetAdjustPetImpOnlyAllowed(bool value)
{
	m_AdjustPetImpOnlyAllowed = value;
}

void cConfiguration::SetIsRegStatForMSDUniversal(bool value)
{
	m_IsRegStatForMSDUniversal = value;
}
void cConfiguration::SetIsSimplePredict(bool value)
{
	m_IsSimplePredict = value;
}

void cConfiguration::SetIsCuttingDependentExtreme(bool value)
{
	m_IsCuttingDependentExtreme = value;
}
void cConfiguration::SetIsSimpleMethodOfChildPrediction(bool value)
{
	m_IsSimpleMethodOfChildPrediction = value;
}
void cConfiguration::SetIsMeanOnly(bool value)
{
	m_IsMeanOnly = value;
}

void cConfiguration::SetIsWithFeatureSelection(bool value)
{
	m_IsWithFeatureSelection = value;
}


void cConfiguration::SetIsWithADJSimForKN(bool value)
{
	m_IsWithADJSimForKN = value;
}

void cConfiguration::SetIsAddSortToKNForTest(bool value)
{
	m_IsAddSortToKNForTest = value;
}


void cConfiguration::SetIsDevidingPerfomanceToParentError(bool value)
{
	m_IsDevidingPerfomanceToParentError = value;
}
void cConfiguration::SetIsFullControlGroupEvolution(bool value)
{
	m_IsFullControlGroupEvolution = value;
}
void cConfiguration::SetIsExponUpgradeForTestGroupSimilar(bool value)
{
	m_IsExponUpgradeForTestGroupSimilar = value;
}
void cConfiguration::SetIsDivideByVarEvolution(bool value)
{
	m_IsDivideByVarEvolution = value;
}
void cConfiguration::SetIsCompareSetToZeroFormula(bool value)
{
	m_IsCompareSetToZeroFormula = value;
}
void cConfiguration::SetIsCompareSetToStraightFormula(bool value)
{
	m_IsCompareSetToStraightFormula = value;
}

void cConfiguration::SetIsExtremeCutUsingUniversal(bool value)
{
	m_IsExtremeCutUsingUniversal = value;
}
void cConfiguration::SetIsStandardPredictiveValuesProfileBased(bool value)
{
	m_IsStandardPredictiveValuesProfileBased = value;
}

void cConfiguration::SetIsWithSubSetTestGroup(bool value)
{
	m_IsWithSubSetTestGroup = value;
}
void cConfiguration::SetIsStartLinearContTestGrpZero(bool value)
{
	m_IsStartLinearContTestGrpZero = value;
}
void cConfiguration::SetIsWithSemiRandomPredictiveSelection(bool value)
{
	m_IsWithSemiRandomPredictiveSelection = value;
}
void cConfiguration::SetIsDefaultFormulaByRegression(bool value)
{
	m_IsDefaultFormulaByRegression = value;
}

void cConfiguration::SetIsOnlyProfilePrediction(bool value)
{
	m_IsOnlyProfilePrediction = value;
}

void cConfiguration::SetIsToShiftDepPerfByMeanEvolution(bool value)
{
	m_IsToShiftDepPerfByMeanEvolution = value;
}

void cConfiguration::SetIsToIncludePreviousWeightsInCurrentInternReg(bool value)
{
	m_IsToIncludePreviousWeightsInCurrentInternReg = value;
}

void cConfiguration::SetIsTestVersion(bool value)
{
	m_IsTestVersion = value;
}



void cConfiguration::SetDebugProfileProcessing(bool value)
{
	m_debugProfileProcessing = value;
}

void cConfiguration::SetSimplePredictionEvaluation(bool value)
{
	m_simplePredictionEvaluation = value;
}

void cConfiguration::SetIsAdjustErrorReducPerAveControlGrp(bool value)
{
	m_isAdjustErrorReducPerAveControlGrp = value;
}

void cConfiguration::SetLLevelErrorEvaluation(double value)
{
	m_lLevelErrorEvaluation = value;
}
void cConfiguration::SetIsProfileDashboardView(bool value)
{
	m_isPRofileDashboardView = value;
}
void cConfiguration::SetCoreVectorWeightChange(float value)
{
	m_coreVectorWeightChange = value;
}
void cConfiguration::SetMultipleCoreVectorWeightChange(float value)
{
	m_multipleCoreVectorWeightChange = value;
}

void cConfiguration::SetPercentSumAllRegression(float value)
{
	m_percentSumAllRegression = value;
}


void cConfiguration::SetDynamicSeekAddConstant(float value)
{
	m_dynamicSeekAddConstant = value;
}
void cConfiguration::SetExponentialEditDistanceScoreConst(float value)
{
	m_ExponentialEditDistanceScoreConst = value;
}
void cConfiguration::SetPercDelutionPredVars(float value)
{
	m_PercDelutionPredVars = value;
}
void cConfiguration::SetExponensialConstantForPredict(float value)
{
	m_ExponensialConstantForPredict = value;
}



void cConfiguration::SetExactMatchRatio(float value)
{
	m_ExactMatchRatio = value;
}
void cConfiguration::SetPercSimilarInMidSizeArray(float value)
{
	m_PercSimilarInMidSizeArray = value;
}


void cConfiguration::SetPercRemoveFrequentExactMatch(float value)
{
	m_PercRemoveFrequentExactMatch = value;
}
void cConfiguration::SetTotalPercRemoveLowPerfomaceSimVars(float value)
{
	m_TotalPercRemoveLowPerfomaceSimVars = value;
}


void cConfiguration::SetMaxEDForNGroupAllowed(float value)
{
	m_MaxEDForNGroupAllowed = value;
}

void cConfiguration::SetMaxEDForKregGroupAllowed(float value)
{
	m_MaxEDForKregGroupAllowed = value;
}

void cConfiguration::SetAditionalEvolutionVectorValue(float value)
{
	m_AditionalEvolutionVectorValue = value;
}

void cConfiguration::SetLinearConstEvolution(float value)
{
	m_LinearConstEvolution = value;
}
void cConfiguration::SetTooLowSimVariableThreshold(float value)
{
	m_TooLowSimVariableThreshold = value;
}
void cConfiguration::SetMinSizeSimFormForPRofile(int value)
{
	m_MinSizeSimFormForPRofile = value;
}

void cConfiguration::SetVectorIncEvolution(float value)
{
	m_VectorIncEvolution = value;
}




void cConfiguration::SetPPIMinThresold(float value)
{
	m_PPIMinThresold = value;
}

void cConfiguration::SetLongProfileMinThrshold(float value)
{
	m_LongProfileMinThrshold = value;
}



void cConfiguration::SetSpecialFieldValueCombination(char* name, char* value)
{
	string_m combination;
	CreateSpecialFieldValueCombination(combination , name, value);
	int dummy;

	if(!m_specialFieldValueCombinationsHash.LookUp((char*)combination.c_str(),  dummy))
	{
		m_specialFieldValueCombinationsHash.SetValue((char*)combination.c_str(),  dummy);
	}
}
void cConfiguration::SetNotAllowedMissingFields(char* name)
{
	int dummy;

	if(!m_notAllowedMissingFieldsHash.LookUp(name,  dummy))
	{
		m_notAllowedMissingFieldsHash.SetValue(name,  dummy);
	}
}
bool cConfiguration::IsNotAllowedMissingFields(char* name)
{
	int dummy;

	if(m_notAllowedMissingFieldsHash.LookUp(name,  dummy))
	{
		return true;
	}
	return false;
}
void cConfiguration::SetMultiCollectionInfo(char* workDir)
{
	m_MultiCollections.Add(workDir);
}
void cConfiguration::SetMultiCollectionName(char* name)
{
	m_MultiCollectionsNames.Add(name);
}

void cConfiguration::SetIndicatorDirection(bool isSmallToBigApplciation)
{
	m_isSmallToBigQIList.Add(isSmallToBigApplciation);
}
bool cConfiguration::isSmallToBigIndicator(unsigned int index)
{
	if(index <  m_QIList.GetSize())
	{
		return *(m_isSmallToBigQIList.GetAt(index));
	}


	unsigned int counter = m_QIList.GetSize();
	for(unsigned int i=0; i < m_QIList.GetSize(); i++)
	{
		string_m_array* subPopulation =  GetQISubPopulationOptions(cConfiguration::GetInstance()->GetQIByIndex(i));
		if(subPopulation)
		{
			for(unsigned int sp = 0; sp < subPopulation->GetSize(); sp++)
			{
				string_m_array* subPopulationValues = cConfiguration::GetInstance()->GetSubPopulationOptionalValues(*(subPopulation->GetAt(sp)));
				for(unsigned int spV = 0; spV < subPopulationValues->GetSize(); spV++)
				{
					if(counter == index)
					{
						return *(m_isSmallToBigQIList.GetAt(i));
					}
					counter++;
				}
			}
		}
	}
}
void cConfiguration::AddSingleQI(char* name)
{
	m_QIList.Add(name);
}
string_m& cConfiguration::GetQIByIndex(unsigned int index)
{
	return *(m_QIList.GetAt(index));
}
void cConfiguration::CreateSubPopulationName(string_m& subPopulationPath,  string_m& QI, string_m& option, string_m& value)
{
	subPopulationPath.assign(QI).append("--").append(option).append("--").append(value);
}
int cConfiguration::GetSubPopulationIndex(string_m& populationName)
{
	string_m option;
	unsigned int counter = m_QIList.GetSize();
	string_m subPopulationList(GENERAL_SUB_POPULATION);
	for(unsigned int i=0; i < m_QIList.GetSize(); i++)
	{
		subPopulationList.assign(*(m_QIList.GetAt(i)));
		string_m_array* subPopulation =  GetQISubPopulationOptions(subPopulationList);
		if(subPopulation)
		{
			for(unsigned int sp = 0; sp < subPopulation->GetSize(); sp++)
			{
				string_m_array* subPopulationValues = cConfiguration::GetInstance()->GetSubPopulationOptionalValues(*(subPopulation->GetAt(sp)));
				for(unsigned int spV = 0; spV < subPopulationValues->GetSize(); spV++)
				{
					//option.assign(*(m_QIList.GetAt(i))).append("--").append(*(subPopulation->GetAt(sp))).append("--").append(*(subPopulationValues->GetAt(spV)));
					CreateSubPopulationName(option,  *(m_QIList.GetAt(i)), *(subPopulation->GetAt(sp)), *(subPopulationValues->GetAt(spV)));
					if(!strcmp((char*)option.c_str(),(char*)populationName.c_str()))
					{
						return counter;
					}
					counter++;
				}
			}
		}
	}
	return -1;
}

string_m_array* cConfiguration::GetQISubPopulationOptions(string_m& QI)
{
	string_m_array* values = NULL;
	m_QIToSubPopulationHAsh.LookUp(QI,values);
	return values; 
}
void cConfiguration::SetSubPopulationListPerQI(string_m& QI, string_m_array& values)
{
	if(values.GetSize() > 0)
	{
		string_m_array* currentValues = new string_m_array;
		for(unsigned int i=0; i <values.GetSize();i++ )
		{
			currentValues->Add(*(values.GetAt(i)));
		}
		m_QIToSubPopulationHAsh.SetValue(QI,currentValues);
	}
	string_m_array* generalList;
	if(m_QIToSubPopulationHAsh.LookUp(GENERAL_SUB_POPULATION,generalList))
	{
		for(unsigned int i=0; i <values.GetSize();i++ )
		{
			bool isToInsert = true;
			for(unsigned int j=0 ; j < generalList->GetSize(); j++ )
			{
				if(!strcmp((char*)(*(values.GetAt(i))).c_str() , (char*)(*(generalList->GetAt(j))).c_str() ))
				{
					isToInsert = false;
				}
			}
			if(isToInsert)
			{
				generalList->Add(*(values.GetAt(i)));
			}
		}
	}
}

string_m_array* cConfiguration::GetSubPopulationOptionalValues(string_m& subPopulation)
{
	string_m_array* values = NULL;
	m_SubpopulationToValuesHash.LookUp(subPopulation,values);
	return values; 
}
void cConfiguration::SetSubPopulationOptionalValues(string_m& subPopulation, string_m_array& values)
{
	if(values.GetSize() > 0)
	{
		string_m_array* currentValues = new string_m_array;
		for(unsigned int i=0; i <values.GetSize();i++ )
		{
			currentValues->Add(*(values.GetAt(i)));
		}
		m_SubpopulationToValuesHash.SetValue(subPopulation,currentValues);
	}
}



void cConfiguration::AddSinglePAssword(char* str)
{
	m_passwordList.Add(str);
}
void cConfiguration::AddSingleUSer(char* name)
{
	m_UserList.Add(name);

	string_m_array list;
	string_m_array listLocation;
	string_m_array listDirections;

	/*list.Add("Variance Table");
	list.Add("QI View");
	list.Add("Personalized Profile");
	listLocation.Add("table.png");
	listLocation.Add("Multiple.png");
	listLocation.Add("personalized.png");
	listDirections.Add("SummaryTable.aspx");
	listDirections.Add("DashBoard.aspx");
	listDirections.Add("Personalized.aspx");
	AddSingleUSerLinksOptions(list,listLocation,listDirections);*/
}
string_m& cConfiguration::GetUserByIndex(unsigned int index)
{
	return *(m_UserList.GetAt(index));
}
unsigned int cConfiguration::GetUserIndex(string_m& userNAme)
{
	for(unsigned int i=0; i < m_UserList.GetSize(); i++ )
	{
		if(!strcmp((char*)((*(m_UserList.GetAt(i))).c_str()) , (char*)(userNAme.c_str())))
		{
			return i;
		}
	}
	return 0;
}
string_m& cConfiguration::GetPasswordByIndex(unsigned int index)
{
	return *(m_passwordList.GetAt(index));
}


void cConfiguration::AddSingleQITimeFrame(char* name)
{
	m_QITimeFrames.Add(name);
}
	
string_m& cConfiguration::GetQITimeFrameByIndex(unsigned int index)
{
	return *(m_QITimeFrames.GetAt(index));
}
float cConfiguration::GetTopFacilitiesThresholdPerQI(string_m& QI, string_m& subPopulation)
{
	if(!strcmp((char*)QI.c_str() , "ADL Improvement"))
	{
		//return 0.51f;
		return 0.517f;
	}
	else if(!strcmp((char*)QI.c_str() , "Walking Improvement"))
	{
		//return 0.407f;
		return 0.388f;
	}
	else if(!strcmp((char*)QI.c_str() , "Pain Improvement"))
	{
		//return 0.55f;
		return 0.51f;
	}
	else if(!strcmp((char*)QI.c_str() , "Depressed Mood Improvement"))
	{
		//return 0.63f;
		//return 0.246f;

		if(strstr((char*)subPopulation.c_str() , "4-30"))
		{
			return 0.56f; // 4-30
		}

		return 0.56f; // 1-3
		
	}
	else
	{
		return 0.51f;
	}
}
bool cConfiguration::IsIndividuaGetMatchedQI(string_m& QI)
{
	for(unsigned int i=0; i < m_IsIndividuaGetMatchedQIList.GetSize(); i++)
	{
		
		if(!strcmp((char*)QI.c_str() , (char*)(*(m_IsIndividuaGetMatchedQIList.GetAt(i))).c_str()))
		{
			return true;
		}
	}
	return false;
}
bool cConfiguration::GetQIindexByQI(unsigned int& index,string_m& QI)
{
	for(unsigned int i=0; i < m_QIList.GetSize(); i++ )
	{
		if(! strcmp((char*)QI.c_str() , (char*)(*(m_QIList.GetAt(i))).c_str()))
		{
			index = i;
			return true;
		}
	}
	index = GetSubPopulationIndex(QI);
	if(index != -1)
	{
		return true;
	}

	return false;
}
unsigned int cConfiguration::GetTimeFrameIndexByName(string_m& timeFrame)
{
	for(unsigned int i=0; i < m_QITimeFrames.GetSize(); i++ )
	{
		if(! strcmp((char*)timeFrame.c_str() , (char*)(*(m_QITimeFrames.GetAt(i))).c_str()))
		{
			return i;
		}
	}
	return 0;
}
void cConfiguration::AddRefereneGroupData(string_m& groupName ,string_m_array& groupItemsList)
{
	m_QIReferenceGroups.Add(groupName);
	string_m_array* currentArray = new string_m_array;
	m_QIReferenceGroupsItemList.Add(currentArray);
	for(unsigned int i=0; i < groupItemsList.GetSize(); i++)
	{
		currentArray->Add(*(groupItemsList.GetAt(i)));
	}
}
void cConfiguration::AddQIList(string_m_array& QIList)
{
	unsigned int numOfUsers  = QIList.GetSize();
	string_m_array* singleUserQI = new string_m_array;
	for(unsigned int i=0; i < QIList.GetSize(); i++)
	{
		singleUserQI->Add(*(QIList.GetAt(i)));
	}
	m_UserQIList.Add(singleUserQI);
}
unsigned int  cConfiguration::GetNumofQIPerUSer(unsigned int index)
{
	return (*(m_UserQIList.GetAt(index)))->GetSize();
}
void cConfiguration::GetSingleUserQIList(string_m_array& list, unsigned int userIndex)
{
	for(unsigned int i=0; i < (*(m_UserQIList.GetAt(userIndex)))->GetSize(); i++)
	{
		list.Add(*((*(m_UserQIList.GetAt(userIndex)))->GetAt(i)));
	}
}

void cConfiguration::AddDataItemsList(string_m_array& list)
{
	
	string_m_array* singleUser = new string_m_array;
	for(unsigned int i=0; i < list.GetSize(); i++)
	{
		singleUser->Add(*(list.GetAt(i)));
	}
	m_DataItemsList.Add(singleUser);
}
unsigned int  cConfiguration::GetNumofDataItemsPerUSer(unsigned int index)
{
	return (*(m_DataItemsList.GetAt(index)))->GetSize();
}
void cConfiguration::GetSingleUserDataItemsList(string_m_array& list, unsigned int userIndex)
{
	for(unsigned int i=0; i < (*(m_DataItemsList.GetAt(userIndex)))->GetSize(); i++)
	{
		list.Add(*((*(m_DataItemsList.GetAt(userIndex)))->GetAt(i)));
	}
}


void cConfiguration::AddSingleUSerLinksOptions(string_m_array& list,string_m_array& listPath,string_m_array& listDirections)
{
	cUSerLinksInfo* linksInfo = new cUSerLinksInfo;
	for(unsigned  int i=0; i < list.GetSize(); i++)
	{
		linksInfo->AddSingleLinkInfo(*(list.GetAt(i)),*(listPath.GetAt(i)),*(listDirections.GetAt(i)));
	}
	m_usersLinksInfo.Add(linksInfo);
}
unsigned int  cConfiguration::GetNumberOfLinksPErUSer(unsigned int index)
{
	return (*(m_usersLinksInfo.GetAt(index)))->GetNumOfLinks();
}
void cConfiguration::GetSingleUserSingleLink(string_m& link,string_m& linkPth,string_m& linkDirection,unsigned int userIndex, unsigned int linkIndex )
{
	(*(m_usersLinksInfo.GetAt(userIndex)))->GetSingleLinkInfo(link,linkPth,linkDirection,linkIndex );
}

void cConfiguration::AddReferenceGroupList(string_m_array& list)
{
	string_m_array* singleUser = new string_m_array;
	for(unsigned int i=0; i < list.GetSize(); i++)
	{
		singleUser->Add(*(list.GetAt(i)));
	}
	m_ReferenceList.Add(singleUser);
}
unsigned int  cConfiguration::GetNumofReferenceGroupPerUSer(unsigned int index)
{
	return (*(m_ReferenceList.GetAt(index)))->GetSize();
}
void cConfiguration::GetSingleUserReferenceGroupList(string_m_array& list, unsigned int userIndex)
{
	for(unsigned int i=0; i < (*(m_ReferenceList.GetAt(userIndex)))->GetSize(); i++)
	{
		list.Add(*((*(m_ReferenceList.GetAt(userIndex)))->GetAt(i)));
	}
}


void cConfiguration::GetSingleReferenceGroupByIndex(string_m& name, string_m_array& ItemsGroup, unsigned int index)
{
	name.assign(*(m_QIReferenceGroups.GetAt(index)));
	for(unsigned int i=0; i < (*(m_QIReferenceGroupsItemList.GetAt(index)))->GetSize(); i++)
	{
		string_m& value = (*(*(m_QIReferenceGroupsItemList.GetAt(index)))->GetAt(i));
		ItemsGroup.Add(value);
	}
}
void cConfiguration::GetSingleReferenceGroupByName(string_m& name, string_m_array& ItemsGroup)
{
	for(unsigned int i=0; i < m_QIReferenceGroups.GetSize(); i++)
	{
		if(!strcmp((char*)name.c_str() , (char*)(*(m_QIReferenceGroups.GetAt(i))).c_str()))
		{
			GetSingleReferenceGroupByIndex(name,  ItemsGroup, i);
		}
	}
}
bool cConfiguration::IsItemAReferenceGroup(string_m& name)
{
	for(unsigned int i=0; i < m_QIReferenceGroups.GetSize(); i++)
	{
		if(!strcmp((char*)name.c_str() , (char*)(*(m_QIReferenceGroups.GetAt(i))).c_str()))
		{
			return true;
		}
	}
	return false;
	
}

void cConfiguration::SetMultiCollectionTimeOut(unsigned int value)
{
	m_multiCollectionsTimeOut = value;
}
string_m& cConfiguration::GetCollectionWorkDirByIndex(unsigned int index)
{
	return *(m_MultiCollections.GetAt(index));
}

string_m& cConfiguration::GetCollectionNameByIndex(unsigned int index)
{
	return *(m_MultiCollectionsNames.GetAt(index));
}

void cConfiguration::SetApplicationLanguge(char* ln)
{
	int index = (int)m_langaugesIndexesHash.GetCount();
	m_langaugesIndexesHash.SetValue(ln,index);
}
int cConfiguration::GetAppLanguageIndex(char* ln)
{
	int index = -1;
	m_langaugesIndexesHash.LookUp(ln, index);
	return index;
}
void cConfiguration::SetMetaDataInfo(float minRange, float MaxRange, string_m& color)
{
	cMetaDatanfo* current = new cMetaDatanfo;
	current->SetInfo(minRange,MaxRange, color);
	m_metaDataMenuList.Add(current);
}
void cConfiguration::SetMetaDatDefaultOutput(char* str)
{
	cMetaDatanfo*& current = *(m_metaDataMenuList.GetAt((m_metaDataMenuList.GetSize()-1)));
	current->SetDefaultOutput(str);
}
void cConfiguration::FillMetaDataMenuLanguageSpecification(char* lanugaeSpecification, string_m& language)
{
	int index = GetAppLanguageIndex((char*)language.c_str());
	cMetaDatanfo*& current = *(m_metaDataMenuList.GetAt((m_metaDataMenuList.GetSize()-1)));
	current->SetFieldLanguageInfo(lanugaeSpecification , index);
}

void cConfiguration::FillSingleMetadataFieldMenu(char* fieldNAme, float min, float max)
{
	cMetaDatanfo*& current = *(m_metaDataMenuList.GetAt((m_metaDataMenuList.GetSize()-1)));
	current->AddSingleFieldRange(fieldNAme, min,  max);
}

void cConfiguration::GetMetaDataMenuInfo(string_m& color, string_m& output, float value, string_m& inputLN,  const char* fieldName)
{
	//need to devide by 100 per config parameter
	value /= 100.f;
	for(unsigned int i=0; i <m_metaDataMenuList.GetSize(); i++ )
	{
		cMetaDatanfo*& current = *(m_metaDataMenuList.GetAt(i));
		if(current->IsInRange(value, fieldName))
		{
			color.assign(current->GetColor());
			int index = GetAppLanguageIndex((char*)inputLN.c_str());
			if(index == -1)
			{
				output.assign(current->GetDefaultOutput());
			}
			else
			{
				output.assign(current->GetFieldLanguageInfo(index));
			}
			return;
		}
	}
}

void cConfiguration::SetTreeSimilarityValue(char* name, char* value)
{
	string_m combination;
	CreateSpecialFieldValueCombination(combination , name, value);
	int dummy;
	
	if(!m_treeSimilarityFieldsHash.LookUp((char*)combination.c_str(),  dummy))
	{
		m_treeSimilarityFieldsHash.SetValue((char*)combination.c_str(),  dummy);
	}
}

void cConfiguration::SetDataRulesManipulationPath(char* path)
{
	m_dataRulesManipulationPath.assign(path);
}
void cConfiguration::SetDataSpeiaclRulesManipulationPath(char* path)
{
	m_dataSpecialRulesManipulationPath.assign(path);
}

void cConfiguration::SetAppllcationName(char* path)
{
	m_applciatioName.assign(path);
}

void cConfiguration::SetISDataRuleManipulation(bool value)
{
	m_isDataRulesMaipulation = value;
}
void cConfiguration::SetISFlatDataRuleManipulation(bool value)
{
	m_isFlatDataRulesMaipulation = value;
}

void cConfiguration::AddInputDataFile(string_m& fileName, string_m_array& id, bool isAllFields,StringToIntHash& fieldsNames, string_m& startDate,
	string_m& endDate, string_m& startDateYear,string_m& startDateMonth,string_m& startDateDay)
{
	tInputBuffer inFile;
	if (!inFile.OpenFile(fileName.c_str()))
	{
		return;
	}
	unsigned int numOfFieldsTillNow = 0;
	for(unsigned int i=0; i < m_inputFilesInfoList.GetSize(); i++)
	{
		numOfFieldsTillNow += (*(m_inputFilesInfoList.GetAt(i)))->GetNumOffieldsInCurrentFile();
	}
	cInputFileInfo* currentFile = new cInputFileInfo(numOfFieldsTillNow);
	currentFile->SetInputfilePath(fileName);
	for(unsigned int i=0; i < id.GetSize(); i++)
	{
		currentFile->SetFileIDTag(*(id.GetAt(i)));
	}
	currentFile->SetFileStartDate(startDate);
	currentFile->SetFileStartDateYear(startDateYear);
	currentFile->SetFileStartDateMonth(startDateMonth);
	currentFile->SetFileStartDateDay(startDateDay);
	currentFile->SetFileEndDate(endDate);
	m_inputFilesInfoList.Add(currentFile);
	string_xxl inLine;
	inFile.GetStringLine(inLine);
	
	string_m_array strs;
	size_t numOfFields = inLine.split_fields(strs, '\t');
	currentFile->SetNumOfFields(numOfFields);
	int dummy;
	char name[MAX_STRING_LENGTH];
	string_m str;
	for(unsigned int i=0; i <numOfFields; i++ )
	{
		if(isAllFields || fieldsNames.LookUp(strs[i], dummy) || !strcmp((char*)strs[i].c_str(), (char*)(*(id.GetAt(0))).c_str()))
		{
			strcpy(name,(char*)strs[i].c_str());
			/*if(i==0)
			{
				strcpy(name, name+3);
			}*/
			if(strstr(name, "BENE_ID"))
			{
				strcpy(name, "BENE_ID");
			}
			str.assign(name);
			
			currentFile->FileInputField(str,i);
		}		
	}
	
}

string_m& cConfiguration::GetInputFilePathByInputIndex(unsigned int index)
{
	return (*(m_inputFilesInfoList.GetAt(index)))->GetInputfilePath();
}

unsigned int cConfiguration::GetInputFileNumberOfFields(unsigned int index)
{
	if(m_inputFilesInfoList.GetSize() > 0)
	{
		return (*(m_inputFilesInfoList.GetAt(index)))->GetNumOffields();
	}
	return 0;
} 

unsigned int cConfiguration::GetNumberOfTotalOutputFields()
{
	unsigned int total = 0;
	for(unsigned int i=0; i < m_inputFilesInfoList.GetSize(); i++)
	{
		total += (*(m_inputFilesInfoList.GetAt(i)))->GetNumOffieldsInCurrentFile();
	}
	return total;
}
unsigned int cConfiguration::GetNumberOfTotalInputFiles()
{
	if(m_inputFilesInfoList.GetSize() == 0)
	{	
		return 1;
	}
	return m_inputFilesInfoList.GetSize();
}
void cConfiguration::UpdateOutputStrBasedOnSingleInputFile(string_xl& outStr, string_xl& inStr, unsigned int fileIndex,
	string_xl_array& inStrs , string_xl_array& outStrs)
{
	if(m_inputFilesInfoList.GetSize() > 0)
	{
		(*(m_inputFilesInfoList.GetAt(fileIndex)))->UpdateOutputstr(outStr, inStr,inStrs , outStrs);
	}
}
int cConfiguration::GetIDFieldIndexBasedOnFileIndex(unsigned int fileIndex, unsigned int idIndex)
{
	return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetIDIndex(idIndex);
}
int cConfiguration::GetStarttDateFieldIndexBasedOnFileIndex(unsigned int fileIndex)
{
	if(m_inputFilesInfoList.GetSize())
	{
		return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetStartDateIndex();
	}
	return -1;
}
int cConfiguration::GetStarttDateFieldYearIndexBasedOnFileIndex(unsigned int fileIndex)
{
	if(m_inputFilesInfoList.GetSize())
	{
		return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetStartDateYearIndex();
	}
	return -1;
}
int cConfiguration::GetStarttDateFieldMonthIndexBasedOnFileIndex(unsigned int fileIndex)
{
	if(m_inputFilesInfoList.GetSize())
	{
		return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetStartDateMonthIndex();
	}
	return -1;
}
int cConfiguration::GetStarttDateFieldDayIndexBasedOnFileIndex(unsigned int fileIndex)
{
	if(m_inputFilesInfoList.GetSize())
	{
		return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetStartDateDayIndex();
	}
	return -1;
}
int cConfiguration::GetEndDateFieldIndexBasedOnFileIndex(unsigned int fileIndex)
{
	return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetEndDateIndex();
}

int cConfiguration::GetFieldIndexByfieldNameAndFileIndex(string_m& name, unsigned int fileIndex)
{
	return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetFieldIndexByName(name);
}
unsigned int cConfiguration::GetNumberOfIDTagsPerFileIndex(unsigned int fileIndex)
{
	if(m_inputFilesInfoList.GetSize() > 0)
	{
		return (*(m_inputFilesInfoList.GetAt(fileIndex)))->GetNumOfIDFields();
	}
	return 0;
}

bool cConfiguration::IsToChangeRealTimeValue(float& multiplier , unsigned index)
{
		
	for(unsigned int i=0; i <m_realTimeFieldToChange.GetSize(); i++)
	{
		if(index == *(m_realTimeFieldToChange.GetAt(i)))
		{
			multiplier = *(m_realTimeMultipler.GetAt(i));
			return true;
		}

	}
	return false;
}
void cConfiguration::SetRealTimeFieldToChange(char* str)
{

}



void cConfiguration::GetQINAmeFromQIMode(string_m& QI,eQIMode QIMode)
{
	if(QIMode == Fall_e)
	{
		QI.assign("Falls");
	}
	else if(QIMode == FunctionalImprove_e)
	{
		QI.assign("ADL Improvement");
	}
	else if(QIMode == WalkingImprovement_e)
	{
		QI.assign("Walking Improvement");
	}
	else if(QIMode == Depression_e)
	{
		QI.assign("Depression");
	}
	else if(QIMode == DepressionSymp_e)
	{
		QI.assign("DepressionSymp");
	}
	else if(QIMode == PressureUlcer_e)
	{
		QI.assign("PressureUlcer");
	}
	else if(QIMode == ADLDep_e)
	{
		QI.assign("ADLDep");
	}
	else if(QIMode == WalkingDep_e)
	{
		QI.assign("WalkingDep");
	}
	else if(QIMode == TransferDep_e)
	{
		QI.assign("TransferDep");
	}
	else if(QIMode == DeliriumDischarge_e)
	{
		QI.assign("	DeliriumDischarge");
	}
	else if(QIMode == WalkingFullDep_e)
	{
		QI.assign("	WalkingFullDep");
	}

	else if(QIMode == TransferFullDep_e)
	{
		QI.assign("TransferFullDep");
	}

	

	

}

void cConfiguration::SetQIMode(char* value)
{
	if(!strcmp(value, "Functional Improvement"))
	{
		m_QIMode = FunctionalImprove_e;
	}
	else if(!strcmp(value, "Discharge Home"))
	{
		m_QIMode = DischargeHome_e;
	}
	else if(!strcmp(value, "Readmission"))
	{
		m_QIMode = Readmission_e;
	}
	else if(!strcmp(value, "Functional Decline"))
	{
		m_QIMode = FunctionalDecline_e;
	}
	else if(!strcmp(value, "Death"))
	{
		m_QIMode = Death_e;
	}

	//Ohad 5.6.19
	else if(!strcmp(value, "Walking Improvement"))
	{
		m_QIMode = WalkingImprovement_e;
	}

	else if(!strcmp(value , "Fall"))
	{
		m_QIMode = Fall_e;
	}
	else if(!strcmp(value , "Depression"))
	{
		m_QIMode = Depression_e;
	}
	else if(!strcmp(value , "DepressionSymp"))
	{
		m_QIMode = DepressionSymp_e;
	}
	else if(!strcmp(value , "PressureUlcer"))
	{
		m_QIMode = PressureUlcer_e;
	}
	else if(!strcmp(value , "Delirium"))
	{
		m_QIMode = Delirium_e;
	}
	else if(!strcmp(value , "ADLDep"))
	{
		m_QIMode = ADLDep_e;
	}
	else if(!strcmp(value , "WalkingDep"))
	{
		m_QIMode = WalkingDep_e;
	}
	else if(!strcmp(value , "DeliriumDischarge"))
	{
		m_QIMode = DeliriumDischarge_e;
	}
	else if(!strcmp(value , "TransferDep"))
	{
		m_QIMode = TransferDep_e;
	}
	else if(!strcmp(value , "Infection"))
	{
		m_QIMode = Infection_e;
	}
	else if(!strcmp(value , "WalkingFullDep"))
	{
		m_QIMode = WalkingFullDep_e;
	}
	else if(!strcmp(value , "TransferFullDep"))
	{
		m_QIMode = TransferFullDep_e;
	}

	

	

	
	
}

eOperatorType cConfiguration::GetOperatorTypeFromStr(string_m& conditionStr)
{
	if(!strcmp(conditionStr.c_str(), "Bigger Than") || !strcmp(conditionStr.c_str(), ">"))
	{
		return BiggerThan_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Bigger Or Equal") || !strcmp(conditionStr.c_str(), ">="))
	{
		return BiggerOrEqual_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Smaller Than") || !strcmp(conditionStr.c_str(), "<"))
	{
		return SmallerThan_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Smaller Or Equal") || !strcmp(conditionStr.c_str(), "<="))
	{
		return SmallerOrEqual_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Equal To") || !strcmp(conditionStr.c_str(), "="))
	{
		return EqualTo_e;
	}
	else if(!strcmp(conditionStr.c_str(), "Not Equal To") || !strcmp(conditionStr.c_str(), "!="))
	{
		return NotEqualTo_e;
	}
	return BiggerThan_e;
}
tNumericOperator<float>* cConfiguration::GetOperatorPTRByType(eOperatorType operatorType, float conditionVal )
{
	tNumericOperator<float>* numericOp = 0;
	if(operatorType == BiggerThan_e) numericOp = new tNumericOperatorGreaterThen<float>(conditionVal);
	else if(operatorType == BiggerOrEqual_e) numericOp = new tNumericOperatorGreaterThenOrEqual<float>(conditionVal);
	else if(operatorType == SmallerThan_e) numericOp = new tNumericOperatorLessThen<float>(conditionVal);
	else if(operatorType == SmallerOrEqual_e) numericOp = new tNumericOperatorLessThenOrEqual<float>(conditionVal);
	else if(operatorType == EqualTo_e) numericOp = new tNumericOperatorEqual<float>(conditionVal);
	else if(operatorType == NotEqualTo_e) numericOp = new tNumericOperatorNotEqual<float>(conditionVal);

	return numericOp;
}

bool cConfiguration::isValueMeetSuccessRateCondition(float value)
{
	if(m_successRateRules)
	{
		OperatorList* operatorList = m_successRateRules;
		tNumericOperator<float>* numericOp = *(operatorList->GetAt(0));
		if(!numericOp->Exacute(value))
		{
			return false;
		}
		return true;
	}

	if(value < 0)
	{
		return true;
	}
	return false;
	
}
void cConfiguration::SetSuccessRatecondition(string_m& operatorStr, float conditionVal)
{
	eOperatorType operatorType = GetOperatorTypeFromStr(operatorStr);
	
	OperatorList* operatorList = m_successRateRules;

	if (!operatorList) 
	{
		operatorList = new OperatorList();
		m_successRateRules = operatorList;
	}

	tNumericOperator<float>* numericOp = GetOperatorPTRByType(operatorType, conditionVal );

	operatorList->Add(numericOp);
}
char* cConfiguration::GetFieldNameByOutputFieldIndex(unsigned int outputFieldIndex)
{
	unsigned int fieldsTillNow = 0;
	for(unsigned int i=0; i <m_inputFilesInfoList.GetSize(); i++ )
	{
		fieldsTillNow += (*(m_inputFilesInfoList.GetAt(i)))->GetNumOffieldsInCurrentFile();
		if(outputFieldIndex < fieldsTillNow)
		{
			return (*(m_inputFilesInfoList.GetAt(i)))->GetfieldNameByOutputIndex(outputFieldIndex);
		}
	}
}

void cConfiguration::SetAnalyticsIterationJump(unsigned int value)
{
	m_AnalyticsIterationJump = value;
}
void cConfiguration::SetSimilarityTreeLevels(unsigned int value)
{
	m_SimilarityTreeLevels = value;
}
void cConfiguration::SetMaxNumberOfAllowedMissingFields(unsigned int value)
{
	m_MaxNumberOfAllowedMissingFields = value;
}


void cConfiguration::SetAnalyticsMatchingPercent(unsigned int value)
{
	m_AnalyticsMatchingPercent = value;
}


void cConfiguration::SetIsToReplaceMissingWithAverage(char* str)
{
	if(!strcmp(str, "yes"))
	{
		m_IsReplacedMissingWithAverage = true;
		return;
	}
	m_IsReplacedMissingWithAverage = false;
}
void cConfiguration::SetIsToReplaceMissingWithEmptyField(char* str)
{
	if(!strcmp(str, "yes"))
	{
		m_IsReplacedMissingWithEmptyField = true;
		return;
	}
	m_IsReplacedMissingWithEmptyField = false;
}

void cConfiguration::SetIsSpecialGUI(bool value)
{
	m_isSpecialGUI = value;
}
void cConfiguration::SetPublicationMode(bool value)
{
	m_isPublicationMode = value;
}
void cConfiguration::SetResearchMode(bool value)
{
	m_isResearchMode = value;
}

void cConfiguration::SetIsAsverseOutcomeFailue(bool value)
{
	m_IsAsverseOutcomeFailue = value;
}

void cConfiguration::SetPublicationExtrnalProfileSize(unsigned int value)
{
	m_PublicationExtrnalProfileSize = value;
}
void cConfiguration::SetPublicationMinHomogScore(float value)
{
	m_PublicationMinHomogScore = value;
}
void cConfiguration::SetPublicationMinUniqeScore(float value)
{
	m_PublicationMinUniqeScore = value;
}
void cConfiguration::SetMaxNumOfExtandedItems(unsigned int value)
{
	m_MaxNumOfExtandedItems = value;
}
void cConfiguration::SetMaxNumOfPublicationProfiles(unsigned int value)
{
	m_MaxNumOfPublicationProfiles = value;
}

void cConfiguration::SetPublciationProfieSize(unsigned int value)
{
	m_publciationProfieSize = value;
}
void cConfiguration::SetIsSmallToBigApp(char* str)
{
	if(!strcmp(str, "yes"))
	{
		m_IsSmallToBigApp = true;
		return;
	}
	m_IsSmallToBigApp = false;
}

bool cConfiguration::isFieldIsPartOfHistogram(unsigned int similarityFieldIndex)
{
	if(m_HistogramFieldsList.GetSize() == 0)
	{
		return true;
	}
	for(unsigned int i=0; i < m_HistogramFieldsList.GetSize(); i++)
	{
		if(GetSimilarityFieldIndexByFieldName((char*)((*(m_HistogramFieldsList.GetAt(i))).c_str())) == similarityFieldIndex)
		{
			return true;
		}
	}
	return false;
	
}
bool cConfiguration::isFieldValuePartOfManualProfileByProfileIndex(unsigned int similarityIndex , short int value, unsigned int profileIndex)
{
	return (*(m_ResearchProfileInfoList.GetAt(profileIndex)))->isFieldValuePartOfManualProfile(similarityIndex , value);
	
}
void cConfiguration::AddSingleManulaProfile()
{
	cResearchProfileInfo* SingleResearchProfile = new cResearchProfileInfo;
	m_ResearchProfileInfoList.Add(SingleResearchProfile);	
}
void cConfiguration::AddSingleManualProfileFieldValuesCombinations(string_m& field, string_m& value)
{
	unsigned int similarityIndex = GetSimilarityFieldIndexByFieldName((char*)field.c_str());
	(*(m_ResearchProfileInfoList.GetAt(m_ResearchProfileInfoList.GetSize()-1)))->AddSingleFieldInfo(similarityIndex, value);
}
unsigned int cConfiguration::GEtResearchFieldSimilarityIndex()
{
	return GetSimilarityFieldIndexByFieldName((char*)m_ResearchField.c_str());
}

unsigned int cConfiguration::GetQIModeIndex()
{
	eQIMode QIMode = GetQIMode();
	{
		if(QIMode == Fall_e)
		{
			return 0;
		}
		if(QIMode == Depression_e)
		{
			return 1;
		}
		if(QIMode == DepressionSymp_e)
		{
			return 2;
		}
		if(QIMode == PressureUlcer_e)
		{
			return 3;
		}
		if(QIMode == Delirium_e)
		{
			return 4;
		}
		if(QIMode == ADLDep_e)
		{
			return 5;
		}
		if(QIMode == WalkingDep_e)
		{
			return 6;
		}
		if(QIMode == DeliriumDischarge_e)
		{
			return 7;
		}
		if(QIMode == TransferDep_e)
		{
			return 8;
		}
		if(QIMode == WalkingFullDep_e)
		{
			return 9;
		}
		if(QIMode == TransferFullDep_e)
		{
			return 10;
		}


		

		
 
	}
}
void cConfiguration::IsToReplaceRefernceData(string_m& output, string_m& input, bool isReference )
{
	output.assign(input);
	//if(isReference && (!strcmp((char*)input.c_str() , "2015") || !strcmp((char*)input.c_str() , "2016")))
	if(isReference &&  (!strcmp((char*)input.c_str() , "2016") || !strcmp((char*)input.c_str() , "2017")|| !strcmp((char*)input.c_str() , "2018")))
	{
		output.assign("2015");
	}
}
void cConfiguration::SetResearchFieldValue(float min, float max, unsigned int mappedGroup,float groupAverage, string_m& groupName)
{
	m_MinResearchFieldGroupValues.Add(min);
	m_MaxResearchFieldGroupValues.Add(max);
	m_GroupMapping.Add(mappedGroup);
	m_GroupAverage.Add(groupAverage);
	m_groupNameList.Add(groupName);
}
void cConfiguration::GetSingleGroupValues(float& min, float& max, unsigned int& mappedValue, unsigned int groupIndex)
{
	min = *(m_MinResearchFieldGroupValues.GetAt(groupIndex));
	max = *(m_MaxResearchFieldGroupValues.GetAt(groupIndex));
	mappedValue = *(m_GroupMapping.GetAt(groupIndex));
}


bool cConfiguration::IsSpecialFieldValueCombination(unsigned int similarityIndex, short int value)
{
	cOneTargetInfo* targetInfo = GetTargetFieldInfoByIndex(0);
	cSimilarityInfo* oneSimilarity = targetInfo->GetSimilarityInfoByIndex(similarityIndex);
	const char* name = GetFieldNameByIndex(oneSimilarity->GetIndex());
	return cConfiguration::GetInstance()->IsSpecialFieldValueCombination((char*)name, value);
}
bool cConfiguration::IsSpecialFieldValueCombination(char* name, short int value)
{
	string_m combination;
	string_m val;
	val.appendNum(value);
	CreateSpecialFieldValueCombination(combination , name, (char*)val.c_str());
	int dummy;

	if(m_specialFieldValueCombinationsHash.LookUp((char*)combination.c_str(),  dummy))
	{
		return true;
	}
	combination.clear();
	CreateSpecialFieldValueCombination(combination , name, "ALL");
	if(m_specialFieldValueCombinationsHash.LookUp((char*)combination.c_str(),  dummy))
	{
		return true;
	}
	if(value > 0)
	{
		combination.clear();
		CreateSpecialFieldValueCombination(combination , name, "BiggerThan0");
		if(m_specialFieldValueCombinationsHash.LookUp((char*)combination.c_str(),  dummy))
		{
			return true;
		}
	}

	return false;
}
bool cConfiguration::IsTreeSimilarityValue(unsigned int similarityIndex, short int value)
{
	cSimilarityInfo* oneSimilarity = GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityIndex);
	const char* fieldName = GetFieldNameByIndex(oneSimilarity->GetIndex());

	string_m combination;
	string_m val;
	val.appendNum(value);
	CreateSpecialFieldValueCombination(combination , (char*)fieldName, (char*)val.c_str());
	int dummy;

	if(m_treeSimilarityFieldsHash.LookUp((char*)combination.c_str(),  dummy))
	{
		return true;
	}
	combination.clear();
	CreateSpecialFieldValueCombination(combination , (char*)fieldName, "ALL");
	if(m_treeSimilarityFieldsHash.LookUp((char*)combination.c_str(),  dummy))
	{
		return true;
	}
	
	if(value > 0)
	{
		combination.clear();
		CreateSpecialFieldValueCombination(combination , (char*)fieldName, "BiggerThan0");
		if(m_treeSimilarityFieldsHash.LookUp((char*)combination.c_str(),  dummy))
		{
			return true;
		}
	}
	return false;
}
float cConfiguration::CreateDiffValueKey(float value1, float value2)
{
	float min = Min(value1, value2);
	float max = Max(value1, value2);

	float key = max*1000+min;
	return key;
}
unsigned int cConfiguration::GetSimialrityNextGroupValue(short int value ,unsigned int similarityFieldIndex, unsigned int optionIndex)
{
	unsigned int groupValue = GetSimialrityGroupValue(value,similarityFieldIndex );

	if(IsMappedSimialrtyVariable(similarityFieldIndex))
	{
		unsigned int currentIndex = 0;
		for(unsigned int i=0 ; i < m_similarityMAppingFieldIndex.GetSize(); i++)
		{
			if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
			{
				currentIndex = i;
				break;
			}
		}
		for(unsigned int i=0; i < (*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetSize(); i++)
		{
		
			if(((*((*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetAt(i))) <= ((float)value / 100.0f)) &&
				((*((*(m_similarityMappingMaxValues.GetAt(currentIndex)))->GetAt(i))) >= ((float)value / 100.0f)))
			{
				if(optionIndex == 0)
				{
					if(i== 0)
					{
						return 	(*((*(m_similarityMappingMappedValues.GetAt(currentIndex)))->GetAt(i+1)));
					}
					else
					{
						return 	(*((*(m_similarityMappingMappedValues.GetAt(currentIndex)))->GetAt(i-1)));
					}
					
				}
				else
				{
					return 	(*((*(m_similarityMappingMappedValues.GetAt(currentIndex)))->GetAt(i+1)));
				}
				
			}
		}
	}
	else
	{
		//Ohad 9.11.17 - the regular code is in this if
		cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
		if(similarityInfo->GetIsFloatVal())
		{
			cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
			unsigned int otherGroupVal =  (similarityInfo->GetMinRange() + optionIndex);
			if(otherGroupVal >= groupValue)
			{
				otherGroupVal+= 1;
			}
			return otherGroupVal;
		}
		else
		{
			if(similarityInfo->GetMinRange() == groupValue )
			{
				
				return groupValue+1;
			}
			if(similarityInfo->GetMaxRange() == groupValue )
			{
				if(similarityFieldIndex == 6 )
				{
					return 4;
				}
				if(similarityFieldIndex == 7 ||similarityFieldIndex == 8)
				{
					return 2;
				}

				return groupValue-1;
			}
			if(optionIndex == 0)
			{
				return groupValue+1;
			}
			return groupValue-1;
		}




		
	}

}
unsigned int cConfiguration::GetNumOfGroupsPerSimilarityField(unsigned int similarityFieldIndex)
{
	if(cConfiguration::GetInstance()->IsMappedSimialrtyVariable(similarityFieldIndex))
	{
		return cConfiguration::GetInstance()->GetNumOfMappingOptions(similarityFieldIndex);
	}
	else
	{
		cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
		if(similarityInfo->GetIsFloatVal())
		{
			return similarityInfo->GetMaxRange() * 100;
		}
		else
		{
			return (similarityInfo->GetMaxRange() - similarityInfo->GetMinRange() +1);//Add(m_profileSimilarityInfoArray[sI].GetNumOfGroups());
		}
	}
}
unsigned int cConfiguration::GetNumOfOptionsPerField(unsigned int similarityFieldIndex , short int value)
{
	if(IsMappedSimialrtyVariable(similarityFieldIndex))
	{
		return GetNumOfAvilablefollowedGroups(similarityFieldIndex , value);
	}
	else
	{
		
		cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
		//Ohad 9.11.17
		if(value / 100 == similarityInfo->GetMaxRange() || value / 100 == similarityInfo->GetMinRange())
		{
			return 1;
		}
		return 2;
		//return(similarityInfo->GetMaxRange() - similarityInfo->GetMinRange() );
	}
}
unsigned int cConfiguration::GetSimialrityGroupValue(short int value,unsigned int similarityFieldIndex )
{
	if(IsMappedSimialrtyVariable(similarityFieldIndex))
	{
		return GetSimialrityMappedValue( value, similarityFieldIndex);
	}
	else
	{
		cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
		if(similarityInfo->GetIsFloatVal())
		{
			return value;
		}
		else
		{
			return((value/100) - similarityInfo->GetMinRange());
		}
		
	}
}
short int cConfiguration::GetFieldValueFromFieldGroup(unsigned int similarityFieldIndex , unsigned int fieldGroup)
{
	cSimilarityInfo* similarityInfo = cConfiguration::GetInstance()->GetTargetFieldInfoByIndex(0)->GetSimilarityInfoByIndex(similarityFieldIndex);
	if(similarityInfo->GetIsFloatVal())
	{
		return fieldGroup;
	}
	
	return (100* ( similarityInfo->GetMinRange() + fieldGroup));
}

short int cConfiguration::GetMappedFieldValueFromFieldGroup(unsigned int similarityFieldIndex , unsigned int fieldGroup)
{
	for(unsigned int i=0 ; i < m_similarityMAppingFieldIndex.GetSize(); i++)
	{
		if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
		{
			return ((*((*(m_similarityMappingMinValues.GetAt(i)))->GetAt(fieldGroup))));
		}
	}
	return DUMMY_GROUP_VAL;
}




unsigned int cConfiguration::GetNumOfAvilablefollowedGroups(unsigned int similarityFieldIndex , unsigned int value)
{
	unsigned int currentIndex = 0;
	for(unsigned int i=0 ; i < m_similarityMAppingFieldIndex.GetSize(); i++)
	{
		if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
		{
			currentIndex = i;
			break;
		}
	}
	unsigned int groupMappedValue = GetSimialrityMappedValue( value,similarityFieldIndex);
	unsigned int groupIndex = 0;
	for(unsigned int i=0; i < (*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetSize(); i++)
	{
		if(groupMappedValue == *((*(m_similarityMappingMappedValues.GetAt(currentIndex)))->GetAt(i)))
		{
			groupIndex = i;
			break;
		}
	}
	if(groupIndex > 0 && groupIndex < (*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetSize() - 1 )
	{
		return 2;
	}
	if((*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetSize() <= 1)
	{
		return 0;
	}
	return 1;
}
void cConfiguration::GetGroupBorders(float& min , float& max , unsigned int  similarityFieldIndex, unsigned int  similarityGroupVal)
{
	for(unsigned int i=0 ; i < m_similarityMAppingFieldIndex.GetSize(); i++)
	{
		if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
		{
			if(similarityGroupVal != DUMMY_FIELD_INDEX)
			{
				min = (*((*(m_similarityMappingMinValues.GetAt(i)))->GetAt(similarityGroupVal)));
				max = (*((*(m_similarityMappingMaxValues.GetAt(i)))->GetAt(similarityGroupVal)));
			}
		}
	}
}
unsigned int cConfiguration::GetSimialrityMappedValue(short int value,unsigned int similarityFieldIndex)
{
	unsigned int currentIndex = 0;
	for(unsigned int i=0 ; i < m_similarityMAppingFieldIndex.GetSize(); i++)
	{
		if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
		{
			currentIndex = i;
			break;
		}
	}
	unsigned int numOfItems = (*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetSize();
	for(unsigned int i=0; i < (*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetSize(); i++)
	{
		
		if(((*((*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetAt(i))) <= ((float)value / 100.0f)) &&
			((*((*(m_similarityMappingMaxValues.GetAt(currentIndex)))->GetAt(i))) >= ((float)value / 100.0f)))
		{
			return 	(*((*(m_similarityMappingMappedValues.GetAt(currentIndex)))->GetAt(i)));
		}
		//Ohad 17.2.18
		if((i + 1) < numOfItems)
		{
			if(((*((*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetAt(i))) <= ((float)value / 100.0f)) &&
			((*((*(m_similarityMappingMinValues.GetAt(currentIndex)))->GetAt(i+1))) > ((float)value / 100.0f)))
			{
				return 	(*((*(m_similarityMappingMappedValues.GetAt(currentIndex)))->GetAt(i)));
			}
		}
	}
	return DUMMY_GROUP_VAL;
}
unsigned int cConfiguration::GetNumOfMappingOptions(unsigned int similarityFieldIndex)
{
	for(unsigned int i=0; i < m_similarityMAppingFieldIndex.GetSize(); i++)
	{
		if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
		{
			return (*(m_similarityMappingMappedValues.GetAt(i)))->GetSize();
		}
	}
}
bool cConfiguration::IsMappedSimialrtyVariable(unsigned int similarityFieldIndex)
{
	for(unsigned int i=0; i < m_similarityMAppingFieldIndex.GetSize(); i++)
	{
		if((*(m_similarityMAppingFieldIndex.GetAt(i)) == similarityFieldIndex))
		{
			return true;
		}
	}
	return false;
}
void cConfiguration::FillSimialrityFieldMapping(float minRange , float maxRange , unsigned int mappedValue, unsigned int similarityFieldIndex)
{
	similarityFieldIndex -= 1;
	unsigned int indexOfCurrentSimilarity = m_similarityMAppingFieldIndex.GetSize();
	if(indexOfCurrentSimilarity == 0  || 
		((*(m_similarityMAppingFieldIndex.GetAt(indexOfCurrentSimilarity-1)) != (similarityFieldIndex))))
	{
		m_similarityMAppingFieldIndex.Add(similarityFieldIndex);
		indexOfCurrentSimilarity++;
	}

	if(indexOfCurrentSimilarity > m_similarityMappingMinValues.GetSize() )
	{
		FloatArray* ptr = new FloatArray;
		m_similarityMappingMinValues.Add(ptr);
		ptr = new FloatArray;
		m_similarityMappingMaxValues.Add(ptr);
		UIArray* uiPtr = new UIArray;
		m_similarityMappingMappedValues.Add(uiPtr);
	}
	(*(m_similarityMappingMinValues.GetAt((m_similarityMappingMinValues.GetSize() - 1))))->Add(minRange);
	(*(m_similarityMappingMaxValues.GetAt((m_similarityMappingMaxValues.GetSize() - 1))))->Add(maxRange);
	(*(m_similarityMappingMappedValues.GetAt((m_similarityMappingMappedValues.GetSize() - 1))))->Add(mappedValue);
}
void cConfiguration::FillFieldValueDistance(unsigned int similarityFieldIndex,float value1, float value2, float dist)
{
	TD_FloatToFloatHash* valuesDiffHash; 
	if(!m_isCategorialFieldHash.LookUp(similarityFieldIndex-1 , valuesDiffHash))
	{
		valuesDiffHash = new TD_FloatToFloatHash;
		valuesDiffHash->InitHash(100);
		m_isCategorialFieldHash.SetValue(similarityFieldIndex-1, valuesDiffHash);
	}
	float key = CreateDiffValueKey(value1, value2);
	valuesDiffHash->SetValue(key, dist);
}
bool cConfiguration::IsCategoricalVariable(unsigned int similarityFieldIndex)
{
	TD_FloatToFloatHash* valuesDiffHash; 
	if(!m_isCategorialFieldHash.LookUp(similarityFieldIndex , valuesDiffHash))
	{
		return false;
	}
	return true;
}
//OHAD March 25 2015
bool cConfiguration::IsCategoricalMissingVariable(unsigned int similarityFieldIndex)
{
	return false;
}
float cConfiguration::CalcualteED(short value1, short value2, unsigned int similarityFieldIndex)
{
	float diff = abs(value1 - value2);
	if(diff == 0)
	{
		return diff;
	}
	TD_FloatToFloatHash* valuesDiffHash; 
	if(!m_isCategorialFieldHash.LookUp(similarityFieldIndex , valuesDiffHash))
	{
		return diff;
	}
	float key = CreateDiffValueKey(value1, value2);
	float defineDiff;
	if(!valuesDiffHash->LookUp(key, defineDiff))
	{
		return 1.0f;
	}
	return defineDiff;
}


void cConfiguration::SetDirectRulesHash(TD_StringToStringHash& rulesHash)
{
	const char* key;
	string_m data;
	TD_StringToStringHash::sPosition *iterator = rulesHash.GetFirst(key, data);
	string_m str;

	m_directRulesHAsh.InitHash(100);
	unsigned int count =0;
	while(iterator)
	{
		m_directRulesHAsh.SetValue(key,data);
		rulesHash.GetNextKey(iterator, key, data);
	}
}

void cConfiguration::SetReverseRulesHash(TD_StringToStringHash& rulesHash)
{
	const char* key;
	string_m data;
	TD_StringToStringHash::sPosition *iterator = rulesHash.GetFirst(key, data);
	string_m str;

	

	m_revereseRulesHAsh.InitHash(1000);
	unsigned int count =0;
	while(iterator)
	{
		m_revereseRulesHAsh.SetValue(key,data);
		rulesHash.GetNextKey(iterator, key, data);
	}
}
bool cConfiguration::isToCovertDirectName(string_m& output, string_m& nameToCheck)
{
	if(m_directRulesHAsh.LookUp(nameToCheck, output))
	{
		return true;
	}
	return false;
}

bool cConfiguration::isToCovertName(string_m& output, string_m& nameToCheck)
{
	if(m_revereseRulesHAsh.LookUp(nameToCheck, output))
	{
		return true;
	}
	return false;
}




void cConfiguration::CreateSpecialFieldValueCombination(string_m& combination ,char* name, char* value)
{
	combination.append(name).append(";").append(value);
}

cMetaDatanfo::cMetaDatanfo()
{
	m_minRange = 0.0f;
	m_maxRange = 0.0f;
	m_fieldsLanguages.SetSize(cConfiguration::GetInstance()->GetNumOfLanguages());
	
}
cMetaDatanfo::~cMetaDatanfo()
{

}
void cMetaDatanfo::SetInfo(float minRange, float MaxRange, string_m& color)
{
	m_minRange = minRange;
	m_maxRange = MaxRange;
	m_color.assign(color);
}
void cMetaDatanfo::SetDefaultOutput(char* str)
{
	m_defaultOutput.assign(str);
}
void cMetaDatanfo::SetFieldLanguageInfo(char* info, unsigned int index)
{
	m_fieldsLanguages.SetAt(index, info);
}
void cMetaDatanfo::GetInfo(float minRange, float MaxRange, string_m& color)
{
	minRange = m_minRange;
	MaxRange = m_maxRange;
	color.assign(m_color);
}
bool cMetaDatanfo::IsInRange(float val,const char* fieldNAme)
{
	for(unsigned int i=0; i <m_RangesPerFIeldsName.GetSize(); i++)
	{
		if(!strcmp((char*)fieldNAme, (char*)((*(m_RangesPerFIeldsName.GetAt(i))).c_str())))
		{
			if(val >= *(m_MinPerField.GetAt(i)) && val < *(m_MaxPerField.GetAt(i)))
			{
				return true;
			}
			return false;
		}
	}
	if(val >= m_minRange && val < m_maxRange)
	{
		return true;
	}
	return false;
}
string_m& cMetaDatanfo::GetFieldLanguageInfo( int index)
{
	return *(m_fieldsLanguages.GetAt(index));
}
void cMetaDatanfo::AddSingleFieldRange(char* fieldNAme, float min, float max)
{
	m_RangesPerFIeldsName.Add(fieldNAme);
	m_MinPerField.Add(min);
	m_MaxPerField.Add(max);
}
cFieldParameters::cFieldParameters()
{
	//m_averageValue = -123321.0f;
	m_averageValue = FIELD_VALUE_TO_IGNORE;
	m_minRange = -10000.0f;
	m_maxRange = 10000.0f;
	m_index = DUMMY_FIELD_INDEX;
	m_fieldsLanguages.SetSize(cConfiguration::GetInstance()->GetNumOfLanguages());
}
cFieldParameters::~cFieldParameters()
{

}
void cFieldParameters::SetFieldAverage(float val)
{
	m_averageValue = val;
}
void cFieldParameters::SetFieldMinRange(float val)
{
	m_minRange = val;
}
void cFieldParameters::SetFieldMaxRange(float val)
{
	m_maxRange = val;
}
void cFieldParameters::SetFieldIndex(unsigned int val)
{
	m_index = val;
}
void cFieldParameters::SetFieldLanguageInfo(char*  info, unsigned int index)
{
	m_fieldsLanguages.SetAt(index, info);
}
string_m& cFieldParameters::GetFieldLanguageInfo(  int index)
{
	return *(m_fieldsLanguages.GetAt(index));
}
cConfigParameterInfo::cConfigParameterInfo()
{
	
}
cConfigParameterInfo::~cConfigParameterInfo()
{
	
}
void cConfigParameterInfo::SetParameterName(char *name)
{
	m_name.assign(name);
}
void cConfigParameterInfo::SetParameterValue(char *value)
{
	m_value.assign(value);
}

cTestCase::cTestCase()
{
	m_numberOfParameters=0;
}
cTestCase::~cTestCase()
{
	for(unsigned int i =0; i <m_numberOfParameters; i++ )
	{
		delete *(m_configParametersList.GetAt(i));
	}
}
void cTestCase::SetCaseID(unsigned int id)
{
	m_id = id;
}
void cTestCase::AddParameter(string_m name, string_m value)
{
	
	cConfigParameterInfo* configParam = new cConfigParameterInfo;
	configParam->SetParameterName((char*)name.c_str());
	configParam->SetParameterValue((char*)value.c_str());
	m_configParametersList.Add(configParam);
	m_numberOfParameters++;
}

cConfigParameterInfo* cTestCase::GetOneParameterByIndex(unsigned int index)
{
	return *(m_configParametersList.GetAt(index));
}

cInputFileInfo::cInputFileInfo()
{

}
cInputFileInfo::cInputFileInfo(unsigned int numOfFieldsPreviousFiles)
{
	m_numberOfFieldsPreviousFiles = numOfFieldsPreviousFiles;
	m_numberOfFieldsCurrentFile = 0;
	m_nameToInputIndexHash.InitHash(MAX_FIELDS_IN_FILE);
	m_nameToOutputIndexHash.InitHash(MAX_FIELDS_IN_FILE);
	m_outputIndexToNameHash.InitHash(MAX_FIELDS_IN_FILE);
}
cInputFileInfo::~cInputFileInfo()
{
	m_numberOfFieldsPreviousFiles = 0;
	m_numberOfFieldsCurrentFile = 0;
	
}
void cInputFileInfo::SetFileIDTag(string_m& id)
{
	m_idTag.Add(id);
}
void cInputFileInfo::SetFileStartDate(string_m& date)
{
	m_startDate.assign(date);
}
void cInputFileInfo::SetFileStartDateYear(string_m& date)
{
	m_startDateYear.assign(date);
}
void cInputFileInfo::SetFileStartDateMonth(string_m& date)
{
	m_startDateMonth.assign(date);
}
void cInputFileInfo::SetFileStartDateDay(string_m& date)
{
	m_startDateDay.assign(date);
}
void cInputFileInfo::SetFileEndDate(string_m& date)
{
	m_endDate.assign(date);
}
void cInputFileInfo::SetNumOfFields(unsigned int num)
{
	m_numOffields = num;
}

void cInputFileInfo::FileInputField(string_m& field,int index)
{
	if(!m_nameToInputIndexHash.LookUp(field, index))
	{
		m_nameToInputIndexHash.SetValue(field, index);
	}
	int outputIndex = m_numberOfFieldsPreviousFiles + m_numberOfFieldsCurrentFile;
	if(!m_nameToOutputIndexHash.LookUp(field, outputIndex))
	{
		m_nameToOutputIndexHash.SetValue(field, outputIndex);
		m_numberOfFieldsCurrentFile++;
		char* name = new char[strlen(field.c_str()) + 1];
		strcpy(name, field.c_str());
		m_outputIndexToNameHash.SetValue(outputIndex, name);
	}
	else
	{
		int ppp=0;
	}
}


void cInputFileInfo::SetInputfilePath(string_m& path)
{
	m_filePath.assign(path);
}
int cInputFileInfo::GetIDIndex(unsigned int idIndex)
{
	return GetFieldIndexByName(*(m_idTag.GetAt(idIndex)));
}
int cInputFileInfo::GetStartDateIndex()
{
	return GetFieldIndexByName(m_startDate);
}
int cInputFileInfo::GetStartDateYearIndex()
{
	return GetFieldIndexByName(m_startDateYear);
}
int cInputFileInfo::GetStartDateMonthIndex()
{
	return GetFieldIndexByName(m_startDateMonth);
}
int cInputFileInfo::GetStartDateDayIndex()
{
	return GetFieldIndexByName(m_startDateDay);
}
int cInputFileInfo::GetEndDateIndex()
{
	return GetFieldIndexByName(m_endDate);
}


int cInputFileInfo::GetFieldIndexByName(string_m& name)
{
	int index = -1;
	m_nameToInputIndexHash.LookUp(name.c_str(),index);
	return index;
}
char* cInputFileInfo::GetfieldNameByOutputIndex(unsigned int index)
{
	const char* data = NULL;
	m_outputIndexToNameHash.LookUp(index , data);
	
	
	return (char*)data;
}
void cInputFileInfo::UpdateOutputstr(string_xl& outStr,string_xl& inStr, string_xl_array& inStrs , string_xl_array& outStrs)
{
	//string_m_array inStrs;
	size_t InnumOfFields = inStr.split_fields(inStrs, '\t');

	//string_m_array outStrs;
	size_t OutnumOfFields = outStr.split_fields(outStrs, '\t');

	const char* key;
	int inputIndex;
	StringToIntHash::sPosition *iterator = m_nameToInputIndexHash.GetFirst(key, inputIndex);
	int outputIndex;
	while(iterator)
	{
		if(!strcmp(key,"Kidney_Disorder"))
		{
			int ppp=0;
		}
		m_nameToOutputIndexHash.LookUp(key,outputIndex);
		//here i need to add the check if the field coming from the seconday file is empty
		float valueToAdd = atof(inStrs[inputIndex]);
		if(valueToAdd != FIELD_VALUE_TO_IGNORE)
		{
			outStrs[outputIndex].assign(inStrs[inputIndex]);
		}
		m_nameToInputIndexHash.GetNextKey(iterator, key, inputIndex);
	}
	outStr.clear();
	for(unsigned int i=0; i <OutnumOfFields; i++ )
	{
		if(i+1< OutnumOfFields)
		{
			outStr.append(outStrs[i]).append("\t");
		}
		else
		{
			outStr.append(outStrs[i]);
		}
	}
		
}


cQuestionnaireQuestionInfo::cQuestionnaireQuestionInfo()
{

}
cQuestionnaireQuestionInfo::~cQuestionnaireQuestionInfo()
{

}
void cQuestionnaireQuestionInfo::SetQuestionData(string_m& name, bool isSingle, string_m_array& values)
{
	m_name.assign(name);
	m_isSingle = isSingle;
	string_m singleValue;
	
	for(unsigned int i=0; i <values.GetSize();i++)
	{
		singleValue.assign(*(values.GetAt(i)));
		m_values.Add(singleValue);
	}
}
void cQuestionnaireQuestionInfo::GetQuestionInfo(string_m& name, bool& isSingle, string_m_array& values)
{
	name.assign(m_name);
	isSingle = m_isSingle;
	string_m singleValue;
	for(unsigned int i=0; i <m_values.GetSize();i++)
	{
		
		singleValue.assign(*(m_values.GetAt(i)));
		values.Add(singleValue);
	}
}
cQuestionnaireCategoryInfo::cQuestionnaireCategoryInfo()
{

}
cQuestionnaireCategoryInfo::~cQuestionnaireCategoryInfo()
{

}
void cQuestionnaireCategoryInfo::SetCategoryName(char* name)
{
	m_name.assign(name);
}
void cQuestionnaireCategoryInfo::AddQuestion(string_m& name, bool isSingle, string_m_array& values)
{
	cQuestionnaireQuestionInfo* singleQuestion = new cQuestionnaireQuestionInfo;
	singleQuestion->SetQuestionData(name, isSingle, values);
	m_questionList.Add(singleQuestion);
}
void cQuestionnaireCategoryInfo::GetSingleQuestionData(string_m& name, bool& isSingle, string_m_array& values, unsigned int qI)
{
	return (*(m_questionList.GetAt(qI)))->GetQuestionInfo(name,  isSingle,  values);
}

cQuestionnaireInfo::cQuestionnaireInfo()
{
	m_multiQuestionsHash.InitHash(100);
}
cQuestionnaireInfo::~cQuestionnaireInfo()
{

}
void cQuestionnaireInfo::AddCategory()
{
	cQuestionnaireCategoryInfo singleCategory;
	m_categoriesList.Add(singleCategory);
}
void cQuestionnaireInfo::SetCategoryName(char* name)
{
	unsigned int currentNumOfCategories = m_categoriesList.GetSize();
	(*(m_categoriesList.GetAt(currentNumOfCategories-1))).SetCategoryName(name);
}
void cQuestionnaireInfo::AddQuestion(string_m& name, bool isSingle, string_m_array& values)
{
	unsigned int currentNumOfCategories = m_categoriesList.GetSize();
	(*(m_categoriesList.GetAt(currentNumOfCategories-1))).AddQuestion(name, isSingle, values);
	if(!isSingle)
	{
		int dummy;
		m_multiQuestionsHash.SetValue(name,dummy);
	}
}
bool cQuestionnaireInfo::isMultiField(const char* name)
{
	int dummy;
	if(m_multiQuestionsHash.LookUp(name, dummy))
	{
		return true;
	}
	return false;
}
void cQuestionnaireInfo::GetCategoryNameByIndex(string_m& name, unsigned int index )
{
	return (*(m_categoriesList.GetAt(index))).GEtCategoryName(name);
}

unsigned int cQuestionnaireInfo::GetNumQuestionsPerCategory(unsigned int categoryIndex)
{
	return (*(m_categoriesList.GetAt(categoryIndex))).GEtNumOfQuestions();
}
void cQuestionnaireInfo::GetSingleQuestionInfo(string_m& name, bool& isSingle, string_m_array& values, unsigned int categoryIndex, unsigned int qIndex)
{
	return (*(m_categoriesList.GetAt(categoryIndex))).GetSingleQuestionData(name, isSingle, values, qIndex);
}