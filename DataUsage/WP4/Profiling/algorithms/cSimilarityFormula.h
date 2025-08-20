//
#include "TargetSort.h"

class cArrayFlex;
class cHistogram;

 

////////////////OTHER DEFINES LESS OR NO CHANGE DRIVEN///////
 

class cGlobals
{
public:
	char g_endOfParagraphOutSign;//'\n';
	char g_endOfParagraphInSign;
	char g_endOfLineInSign ;
	char g_endOfLineOutSign;
	char g_delimiter  ; // 9 is TAB
	bool g_isRemoveExtraSpaces;
	char g_inputFileString[MAX_STRING_LENGTH];
	char g_outputFileString[MAX_STRING_LENGTH];
	char g_applicationType ;//A for "paragraph analytics";
	char g_profileBuildMode ;//B is for buis profiles. relevant when application tpe is   B
	char g_isToEnterRealTimeEndlessLoop;
	
	int g_sizeAndUpToKeepREcursive;
	int g_MAX_LEVELS_IN_PROFILING_EVOLUTION;

	//char g_isToEnterRealTimeParagEndelessLoop;
//	char g_patientRealTimePAragraFilePathIn[MAX_STRING_LENGTH];

	char g_isToConductPerformanceTests;

	char g_patientLearningFilePAth[MAX_STRING_LENGTH];
	char g_patientCalibrationFilePath[MAX_STRING_LENGTH];
	char g_metaFilePath[MAX_STRING_LENGTH];//readwriteArraFlex patientTestFilePath performanceReportFilePath
	char g_readwriteArraFlex[MAX_STRING_LENGTH];
	char g_patientTestFilePath[MAX_STRING_LENGTH];

	char g_performanceReportFilePath[MAX_STRING_LENGTH];
	char g_patientRealTimeFilePathIn[MAX_STRING_LENGTH];
	char g_patientRealTimeFolderPathOut[MAX_STRING_LENGTH];

	char g_internalPerformanceReportFilePath[MAX_STRING_LENGTH];
		
	int g_minSampleSizeIngridient;
	int g_minSampleSizeWhole;

	double m_meanDepValue;
	double m_sdDepValue;

	char g_manuelPhrasesFilePath[MAX_STRING_LENGTH];

	
	int g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE;// 2 00//should be 1500-2000 
	int g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE;//should be 0 ONLY for p aragrpah appliaito and per configuatsion for profiling application
    int g_PROFILE_LIST_MAX_SIZE;// 3000//max number of  profiles to create eventually
	int g_PATIENT_LINES_INPUT_LIST_MAX_NUMBER;
	double g_MAX_VALUE_OF_ABS_SYMETRIC_ODD_RATIO;// 10.0 //
	int g_NUM_OF_SUB_GRPS;// 5
    int g_NUMBER_OF_CALIBRATION_GRPS;// 10

	int	g_minSampleToContinueRecursive;//below this amount we DONT go recursive but stop 
	int	g_maxNumOfLevelsToContinueRecursive;//above this number we DONT continue recusrive but go to profiles
	int g_capOfForkingPredictiveRecursive;
	int g_highestRecurSiveLevelWithFork;


	int g_MIN_SIZE_OF_CATEG_FOR_STRETCH;// 250//inSizeOfCAtegoryForStretch
	double g_STRENGTH_MULT_OF_LONG_STRETCHED_PROFILE;
	double g_MIN_ODD_RATIO_TOJUSTIFIY_OPENING_CHILD_PROFILE;// 0.05
	//bool g_IS_WITH_EVOLUTION_ON_GOING_PERF_TESTING;// false
	bool g_IS_WITH_LONG_STRETCH_PERF_PROCESS;// false
	bool g_IS_PERF_WEGIHT_FOR_BEST_MATCH_MERGE_POWER_BY_2;// true
	bool g_IS_ADVANCED_PERF_FOR_GET_BEST_MATCH;// false
	bool g_IS_ADVANCED_PERF_FOR_GET_BEST_MATCH_EVOLUTION;// true  //during and after creating profiles, will select best match based on stetch score and see the stretch score debeloped

	bool g_IS_TO_DELETE_IS_IN_PROFILE_FOR_MEM_OPTIMIZATION;

	int g_MAX_NUM_OF_ITERATIONS;// 2 //
	int g_SIZE_OF_PROFILE_SIZED_GROUP_FOR_COMPETING_EVOLUTION;// 100
	double g_RATIO_OF_LARGE_GAP_TO_CHABGE_PROFILE_GRP;// 0.85
	int g_NUM_OF_CATG_PERCENTILE_MERGE;
	int g_NUM_OF_TEST_TYPES;// 5
	int g_ONLY_ROOT_PREDIC_MODE;// 0
	int g_ONLY_WP3_EXACT_MULTI_VALUE_PATN_CATEGORY;// 1
	int g_ONLY_WP3_INCLUDED_IN_PATN_CATEGORY;// 2 //here we can include all profiles thatt have at leasat the WP3 categoy as filter, among potentialy other inclusion critera
	int g_ONLY_NON_WP3_PROFILES;// 3
	int g_ALL_PROFILES_CANDIDATES;// 4

	int g_MAX_NUM_OF_PATIENTS_FIRST_RUN_PARAG;

	cHistogram* m_globHist;
	cHistogram* m_globHistWithSizeConsid;

	cGlobals();
	~cGlobals();
	void CommandLineAdjustement();

};


class cPredictionContextObj
{
public:
	int m_profileID ;
	double m_prediction;
	double m_predictionWithInterv;
	double m_preditionWitoutInterv;
	int  m_subGrpIndex;
	double m_weight;

	cPredictionContextObj()
	{
		m_profileID = -1;
		m_prediction = 0.0;
		m_predictionWithInterv = 0.0;
		m_preditionWitoutInterv = 0.0;
		m_subGrpIndex = -1;
		m_weight =0.0;
	}
	void SetObject( int  profileID, int subGrpIndex, double prediction, double predictionWithInterv , 
						 double preditionWitoutInterv, double weight)
	{
		m_profileID = profileID;
		m_prediction = prediction;
		m_predictionWithInterv     = predictionWithInterv;
		m_preditionWitoutInterv = preditionWitoutInterv;
		m_subGrpIndex = subGrpIndex;
		m_weight =weight;
	}


};



class cQuickHash 
{
	bool* m_arr;
	int m_size;

public:

	cQuickHash (int size);

	~cQuickHash ();

	void ClearAllKeys();

	bool LookUpKey(int id);

	void SetKey(int id);


};



 

class  cVariableAndValue
{
public:
	int m_variableIndex;
	double m_value;


	cVariableAndValue()
	{
		m_variableIndex=-1;
		m_value =0.0;
	}

	cVariableAndValue(int var, double val)
	{
		m_variableIndex = var;
		m_value  =  val;
	}

	cVariableAndValue( const cVariableAndValue& other)
	{
		m_variableIndex = other.m_variableIndex;
		m_value = other.m_value;
	}

	cVariableAndValue& operator= ( const cVariableAndValue& other)
	{
		m_variableIndex = other.m_variableIndex;
		m_value = other.m_value;
		return *this;
	}

	bool IsEqualObject( cVariableAndValue& other)
	{
		if(m_variableIndex == other.m_variableIndex)
		{
			if(m_value == other.m_value)
			{
				return true;
			}
		}
		return false;
	}


	void CopyVarValElementsFromElementArray(double* elementArray, int size)
	{
		int index=0;
		m_variableIndex = int(elementArray[index++]);
		m_value = elementArray[index++];
	}
	 

	void VarValObjPrepareArraysToOrFromDisc(cArrayFlex* flexArr, bool isWriteToArray, cGlobals &globals);

	//void cccccc( cArrayFlex* flexArr,  bool isWriteToArray);


	
};

class cVariableAndValueAndPoints
{
public:
	int m_variableIndex;
	double m_value;
	double m_points;
	cVariableAndValueAndPoints()
	{
		m_variableIndex=-1;
		m_value =0.0;
		m_points=0.0;
	}
	cVariableAndValueAndPoints(int varIndex , double value, double points)
	{
		m_variableIndex= varIndex;
		m_value =value;
		m_points=points;
	}

	cVariableAndValueAndPoints(cVariableAndValueAndPoints &other);

	cVariableAndValueAndPoints(cVariableAndValue &temp)
	{
		m_variableIndex = temp.m_variableIndex;
		m_value = temp.m_value;
		m_points = 0.0;
	}

	void		//PrepareArraysToOrFromDisc
		VarValObjPrepareArraysToOrFromDisc(cArrayFlex* flexArr, bool isWriteToArray, cGlobals &globals);
	
	void VarValObjPrepareArraysToOrFromDisc2(
		cArrayFlex* flexArr, bool isWriteToArray, cGlobals &globals, int leadingSpaceNum, int index) ;
	
	void CopyVarValPointElementsFromElementArray(double* elementArray, int size)
	{
		int index=0;
		m_variableIndex = int(elementArray[index++]);
		m_value = elementArray[index++];
		m_points = elementArray[index++];
	}
	


	cVariableAndValueAndPoints& operator= (cVariableAndValueAndPoints &other)
	{
		m_variableIndex= other.m_variableIndex;
		m_value =	other.m_value;
		m_points=	other.m_points;
		return *this;
	}

	bool IsMatchingVariableAndValue(int var, double val)
	{
		if(var== m_variableIndex && val == m_value )
		{
			return true;
		}
		return false;
	}

	static void Swap( cVariableAndValueAndPoints &ob1,  cVariableAndValueAndPoints &ob2)
	{
		cVariableAndValueAndPoints   temp(ob1);
		ob1 = ob2;
		ob2= temp;	
	}
	bool IsEqualObject( cVariableAndValueAndPoints& other)//we dont care aout the points here
	{
		if(m_variableIndex == other.m_variableIndex)
		{
			if(m_value == other.m_value)
			{
				return true;
			}
		}
		return false;
	}
};

 
//this is a schema object for one field. A person that has P fields will have an array of P 
class cVariableSchemaObject
{
public:
	char m_varibleName[100];
	int m_varPosition ;
	bool m_isOrgVar;
	int m_orgIndex;
	int m_tempppp;
	bool m_isPredictiveVariable;
	bool m_isToBeReplaced;
	bool m_isIntervenstion;
	int m_indexOfPropensity;
	
	
	double* m_varValues;
	double* m_varValuePrevlns;
	int m_numberOfValues;

	double m_lowestValue;
	double m_highestValue;

	//double* m_interventionValueList;
	//int m_interventionValueListCount; 

//	bool m_isDecimalValues;
//	bool m_isCategoricalVariable;
//	bool m_isDependentVariable;
	//if this is a predictive var for the logistic, true will be per values that are part of the code 1 ligisti
//	double* m_valuesThatIncluedInLogisticCode1;
//	int m_valuesThatIncluedInLogisticCode1Size;
	//inclusion value list if this var participat in the potential inclusion and if 
	// any values coudl be part of a profile definition for such includsion, since not all could
//	double*  m_inclusionValueList;
//	int m_inclusionValueListSize;
	//ifi this  var that is an intrvetnion var will have this part filled with list of values that represent an intervention


	void SchemaElementReadORwriteObjectToArr( cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals);

	cVariableSchemaObject( int varPosition, bool isPredictiveVariable, bool isOrgVar, bool isIntervention, int indexOfPropensity);
	
	~cVariableSchemaObject();

	 
	void SetName(char* name);

	void SetIsToBeReplaced()
	{
		m_isToBeReplaced = true;
	}

	void  SetOrgIndex(int  orgIndex)
	{
		m_orgIndex = orgIndex;
		//m_isOrgVar = isOrgVar;
	}
	void SetIsOrgIndex(bool isOrgVar)
	{
		m_isOrgVar = isOrgVar;
	}
	
	

	bool IsNameOfVariable(char* str);


	int GetIndexWithPreviousApprecancePositionOfValue(double val, double* uniqueValueOptions, int size)
	{
		int foundIndex = -1;
		for(int v = 0 ; v< size ; v++)
		{
			if(val == uniqueValueOptions[v])
			{
				foundIndex = v;//int(val);
			}
		}
		return foundIndex;
	}
		

	//	this will be calsled fro m_sc hemaArr->UpdateSchemaWithV ariableValuesPRevelance(m_patientsDataSet, m_numberOfPatients)
	// so the patinet data set is already augmented and is predictive and not m_isToBeReplaced 
#define MAX_UNIQUE_VALUE_OPTIONS_LOCAL 100
	void UpdateOneVariableObjectWithPrevelenace(double** patientsDataSet, int numberOfPatients, int varIndex)
	{
		//go voer all patinet data, for this vrible index only, and collect distric values. each time we get a new add to the 
		//list of optoins
		double uniqueValueOptions[MAX_UNIQUE_VALUE_OPTIONS_LOCAL];
		int prevelanceOfValues[MAX_UNIQUE_VALUE_OPTIONS_LOCAL];
		int numOfUniqueValuesDiscovered = 0;
		for(int i  = 0 ; i < numberOfPatients ; i++)
		{
			double val = patientsDataSet[i][varIndex];
			int indexWithExistingVal = GetIndexWithPreviousApprecancePositionOfValue(val, uniqueValueOptions, numOfUniqueValuesDiscovered);
			//if( IsNewUniqueVal( val, uniqueValueOptions, numOfUniqueValuesDiscovered)
			if(indexWithExistingVal == (-1) ) //-1 when this val has not appear yet and it is a new uinqie val
				//if yes that means the val is not yet in the arr
			{
				if(numOfUniqueValuesDiscovered < MAX_UNIQUE_VALUE_OPTIONS_LOCAL)
				{
					uniqueValueOptions[numOfUniqueValuesDiscovered] = val;
					prevelanceOfValues[numOfUniqueValuesDiscovered] = 1;// new appreacen, so means 1 for now
					numOfUniqueValuesDiscovered++;
				}
			}
			else
			{
				prevelanceOfValues[indexWithExistingVal]++;
			}
		}
		if(numOfUniqueValuesDiscovered>0)
		{
			m_numberOfValues = numOfUniqueValuesDiscovered;
			m_varValues = new double[m_numberOfValues];
			m_varValuePrevlns= new double[m_numberOfValues];
			int totalPrevelance = 0;
			for(int v = 0 ; v < m_numberOfValues ; v++)
			{
				m_varValues[v] = uniqueValueOptions[v];
				m_varValuePrevlns[v] = (double)(prevelanceOfValues[v]);
				totalPrevelance += prevelanceOfValues[v] ;
			}
			for(int v = 0 ; v < m_numberOfValues ; v++)
			{
				m_varValuePrevlns[v] /= ((double) totalPrevelance);
			}		
		}	
	}
};

class cProfileObject;

//m_logisticRegressionVarAndPoints, m_sizeOfLogisticRegressionArr
//9 13 22
class cPercentileCalculationModel
{
public:
	cVariableAndValueAndPoints* m_varAndPoints;
	int m_sizeOfModelArr;
	
	double** m_itemArr;
	bool* m_isIn;
	double* m_depArr;
	int m_numberOFItems;

	double* m_categoriesValues;
	double* m_categThrs;
	int* m_samplePerCat; 
	int m_numOfCgrs;

	
	int GetCategrIndex(double points);
	bool IsItemPattenred(double &points, int itemIndex,  int m);

	
	static double CalculatedAdjustedPoints(double odddChildModelPoints, 
		int grpNumberRootOddModel, int grpNumberRegModel, int numOfModelGrps);



	cPercentileCalculationModel( cProfileObject* profile ,  int numOfCatgrs);
    

	~cPercentileCalculationModel()
	{
		delete []m_categoriesValues;
		delete []m_categThrs;
		delete []m_samplePerCat;
	}


	void Analytics();

	void SetModelObjectArrayAndSize(cVariableAndValueAndPoints* varValAndPoints, int sizeOfVarValPntObj) //; //add this model for schema to allow easy discount when having both
	{
		m_varAndPoints = varValAndPoints;
		m_sizeOfModelArr = sizeOfVarValPntObj;
	}

	bool IsVarValIncluded(int var, double val)
	{
		for(int i = 0 ; i < m_sizeOfModelArr ; i++)
		{
			if(m_varAndPoints[i].IsMatchingVariableAndValue(var,val))
			{
				return true;
			}
		}
		return false;
	}

	static 	void BuildAdjustedModel(
		cVariableAndValueAndPoints* adjustedRates, cVariableAndValueAndPoints* baseRates,
	//	cVariableAndValueAndPoints* rootOddWeights,	cVariableAndValueAndPoints* regWeights,
		int ratesListSize,
		cPercentileCalculationModel* rootOddPredictiveModel,  cPercentileCalculationModel* regPredictiveModel);
	static double LookOutPointsFromArrayOfVarVarPoints(
		cVariableAndValueAndPoints*	regWeights,  int ratesListSize, int var, double val);

	int CalculatePositiveBucketIndex(int grpNumberModel);

	double GetSuggestedChangeInOdd( int grpNumberModel, int bucketIndexGap);


};

//class cVariableSchemaObject;

class cVariableSchemaArr
{
public:
	cVariableSchemaObject** m_schemaArr;
	int m_maxNumberOfObjects;
	int m_orgNumOfVars;
//	int m_augm entedNumOfVars;

	//m_sche maArr-SetRegressionModel(cPredict iveModel*& regModel);
	//cPre dictiveModel* m_regModel;
	
//	int m_indexOfDepObject;

	//4 17 22 TO DO 2 - add a configuraiton file instead of some manual 
	cVariableSchemaArr(int maxNumberOfObjects, int orgNumOfVars, bool* isPredictive,
														double** patientOrgArr, int numOfPatients);
	void AddHardCodedRules();
//	void AgeScale(int index);

	double CalcualteAugmentedValue(double* orgPatientArr, int varIndex);

	//4 17 22 Done
	void SchemaReadORwriteObjectToArr(  cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals);

	void AugmentPatient(double * augmentedPatientArr,  double* orgPatientArr);

	double  ConvertOriginalAgeToAgeScale(double orgAge);

	
	void UpdateSchemaWithVariableValuesPRevelance(double** patientsDataSet, int numberOfPatients)
	{
		//int m_augme ntedNumOfVars;//m_sc hemaArr
		for(int j = 0 ; j < m_orgNumOfVars ; j++)
		{
			if(m_schemaArr[j]->m_isPredictiveVariable)
			{
				if(!(m_schemaArr[j]->m_isToBeReplaced))
				{
					m_schemaArr[j]->UpdateOneVariableObjectWithPrevelenace( patientsDataSet,  numberOfPatients, j);
				}			
			}
		}
	}

};
 

class cResearchDataObj
{
	//cResearchDataObj* resObtLocal = new cResearchDataObj( );
	void MigratePointersFromOtherWithInclusionArray(cResearchDataObj* researchDataObj, bool* isInAnchor)
	{
		int size = researchDataObj->m_numOfItems;
		int movingIndex=0;
		for(int i = 0 ; i < size ; i++)
		{
			if(isInAnchor == NULL || isInAnchor[i])
			{
				movingIndex++;
			}
		}
		double** twoDim = new double*[movingIndex];
		double* depArr = new double[movingIndex];
		movingIndex=0;
		for(int i = 0 ; i < size ; i++)
		{
			if(isInAnchor == NULL || isInAnchor[i])
			{
				twoDim[movingIndex] = researchDataObj->m_twoDimArray[i];
				depArr[movingIndex] = researchDataObj->m_depArr[i];
				movingIndex++;
			}
		}
		m_numOfItems=movingIndex;
		m_sizeOfItem = researchDataObj->m_sizeOfItem ;
		m_twoDimArray = twoDim;
		m_depArr = depArr;
	}
	
	void ReleasePointersToPersons()
	{
		for(int i = 0 ; i < m_numOfItems ; i++)
		{
			m_twoDimArray[i]=NULL;
		}
	}
public:
	int m_numOfItems;
	int m_sizeOfItem;
	double** m_twoDimArray;
	double* m_depArr;
	bool m_isPointersToItemsCreatedHere;


	cResearchDataObj()
	{
		m_numOfItems=0;
		m_sizeOfItem=0;
		m_twoDimArray=NULL;
		m_depArr=NULL;
		m_isPointersToItemsCreatedHere = false;

	}
	cResearchDataObj(int num, int size)
	{
		m_numOfItems=num;
		m_sizeOfItem = size;
		m_twoDimArray= new double*[m_numOfItems];
		m_depArr= new double[m_numOfItems];
		for(int i = 0 ; i < m_numOfItems; i++)
		{
			m_twoDimArray[i] = new double[m_sizeOfItem];
			for(int j = 0 ; j < m_sizeOfItem ; j++)
			{
				m_twoDimArray[i][j]=0.0;
			}
			m_depArr[i]=0.0;
		}
		m_isPointersToItemsCreatedHere=true;
	}

	cResearchDataObj( cResearchDataObj* researchDataInput ,  bool* isInAnchor)
	{
		MigratePointersFromOtherWithInclusionArray(researchDataInput,  isInAnchor);
		m_isPointersToItemsCreatedHere = false;
	}

	
	~cResearchDataObj()
	{
		if(!m_isPointersToItemsCreatedHere)
		{
			ReleasePointersToPersons();
		}
		if(m_twoDimArray != NULL)
		{
			for(int i = 0 ; i < m_numOfItems ; i++)
			{
				if(m_twoDimArray[i] != NULL)
				{
					delete [] m_twoDimArray[i];
					m_twoDimArray[i]=NULL;
				}
			}
			delete []m_twoDimArray;
		}
		if(m_depArr != NULL)
		{
			delete []m_depArr;
		}
	}

	int GetBestStretch(double* stretchArr ,  bool* isTaken,  int size);
	double CalcVariableStretch( int indexToStretch, double anchorVal);
	void CapIsPredictiveOptionsPerStretch(bool* isPedictive, int cap, double anchorVal);
	 
};

//a profilei object will have a member which is a list of this object, each member of the list if an intervention object 
//such as "nursing time" for those who get nurse visit at home, and the intervention index wil stay where in the long
//array of variables can we find the nursing time.
class cInterventionObject
{
public:
	int m_interventionVariableIndex;
	int m_interventionVarPropsIndex;
	int m_sizeOfProfilePop;
	int m_sizeOFProfileIntervePop;
	int m_numOfSubGrps;
	double* m_interventionAdjustArr;//



	cInterventionObject()
	{
		m_interventionVariableIndex = -1;
		m_interventionVarPropsIndex= -1;
		m_sizeOfProfilePop = 0;
		m_sizeOFProfileIntervePop=0;
		m_numOfSubGrps=0;
		m_interventionAdjustArr=NULL;
	}

	void SetIndexOfInter( int intervVarindex , int interVarPropIndex)
	{
		m_interventionVariableIndex = intervVarindex; //this means that in this index of the patients array we can find whether 0 or 1 is the answer
		//whether the person has oro not the intervention that is associated with this index 
		m_interventionVarPropsIndex = interVarPropIndex;//that means that for the intervention flagged in m_interventionVariableIndex, the propensity score
		//of the same intervention can be found in m_interventionVarPropsIndex .
	}
	

	cInterventionObject(int intervVarindex, int interVarPropIndex)
	{
		SetIndexOfInter(  intervVarindex ,  interVarPropIndex);
		m_sizeOfProfilePop = 0;
		m_sizeOFProfileIntervePop=0;
		m_numOfSubGrps=0;
		m_interventionAdjustArr=NULL;	
	}


	~cInterventionObject()
	{
		if(m_interventionAdjustArr!=NULL)
		{
			delete []m_interventionAdjustArr;
		}
	}
	/*
	12 2 22 *** match with all intervetnion notes
	when calling this function we get purpose of taking a candidate intervetnion index
	and see if it survives. else we condense the intervention list to kkeep only what makes sense
	*/

	//fucntion that calls intervetnion
	////void XXXXX( int howManyInteventions)
	//{
		//get list of intevention from meta data , inclueds
		//how many
		//call 
	   //m_interventionObjectListSize = howManyInteventions;
		//m_interventionObjectListSize = new cInterventionObject[  m_interventionObjectListSize]
	//for each object fill the two indexxes
	//then call to process the patients  FillInterventionMemebers()

	void FillInterventionMemebers( double** twoDim, double* depArr, bool* isIn, int size,
		cProfileObject* profile, int numOfSubGrps);
	

};




////////////////////////////////PROFILE OBJECT//////////////////////////////////////////////////////


class cResearchObject;
class InputVariablesPackageForResearchObj;
class cCalibrationContextObj;
class cVariableAndValueAndPoints;
/////////////////////////////RESEARCH OBJECT////////////////////////////////////////////////


class	cInclusionRuleDataSet
{
	int m_maxNumOfRules;
	int m_numOfRules;
	int* m_ruleSizeArr;
	cVariableAndValueAndPoints** m_rulesArr;

	cProfileObject*** m_3DimProfArr;
	int* m_numOfProflePerRule;

	//	inclusionDataSet->UpdateRuleDeparrays(addedRuleIndex,  depArrValues[vl], 	depArrValueCnt[vl], numOfCalibrationGrps);
						
	double** m_depArrHolder ;
	int** m_depCntArrHolder ;


	bool IsRuleElementFound(  cVariableAndValueAndPoints &ruleElemetn, cVariableAndValueAndPoints* rule2, int size)
	{
		for(int i = 0 ; i < size ; i++)
		{
			if(ruleElemetn.m_variableIndex    == rule2[i].m_variableIndex )
			{
				if(ruleElemetn.m_value == rule2[i].m_value )
				{
					return true   ;
				}
			}
		}
		return false;
	}
	bool IsSameRuleSet(cVariableAndValueAndPoints* rule1, int ruleSize1,  cVariableAndValueAndPoints* rule2,    int ruleSize2)
	{
		if(ruleSize1 != ruleSize2)
		{
			return false;
		}
		for(int i = 0 ; i < ruleSize1 ; i++)
        {
			bool isFoundElement = IsRuleElementFound(   rule1[i], rule2, ruleSize2);
			if(! isFoundElement )
            { 
				return false;
			}
		}
		return true;
	}
	
	

	



public:

	cInclusionRuleDataSet(int maxNumOfRulesSets)
	{
		m_maxNumOfRules = maxNumOfRulesSets;
		m_numOfRules=0;
		m_rulesArr = new cVariableAndValueAndPoints* [m_maxNumOfRules];
		m_ruleSizeArr = new int[m_maxNumOfRules];

		m_depArrHolder = new double*[maxNumOfRulesSets] ;
		m_depCntArrHolder = new int*[maxNumOfRulesSets] ;

		m_3DimProfArr  = new cProfileObject**[maxNumOfRulesSets];
		m_numOfProflePerRule = new int[maxNumOfRulesSets];
		for(int i = 0 ; i < maxNumOfRulesSets ; i++)
		{
			m_rulesArr[i]= NULL;
			m_ruleSizeArr[i]=0;
			m_depArrHolder[i]=NULL;
			m_depCntArrHolder[i]=NULL;
			m_3DimProfArr[i]=NULL;
			m_numOfProflePerRule[i]=0;
		}

	}

	


	~cInclusionRuleDataSet()
	{
		for( int i = 0 ; i < m_numOfRules ; i++)
		{
			delete []m_rulesArr [i];
			delete []m_3DimProfArr[i];
		}
		delete []m_rulesArr ;
		m_rulesArr=NULL;
		delete []m_3DimProfArr;
		m_3DimProfArr=NULL;
		delete []m_numOfProflePerRule;
		m_numOfProflePerRule=NULL;
		delete []	m_depArrHolder ;
		m_depArrHolder=NULL;
		delete [] m_depCntArrHolder;
		m_depCntArrHolder=NULL;


	}

	void UpdateRuleDeparrays( int ruleIndex, double* depArrIn, 	int* depArrCntIn,  int numOfCalibrationGrps)
	{
		if(m_depArrHolder[ruleIndex] == NULL)
		{
			m_depArrHolder[ruleIndex]= new double[numOfCalibrationGrps];
			m_depCntArrHolder[ruleIndex]= new int[numOfCalibrationGrps];
		}
		for( int x = 0 ; x< numOfCalibrationGrps ; x++)
		{
			m_depArrHolder[ruleIndex][x] = depArrIn[x];
			m_depCntArrHolder[ruleIndex][x] = depArrCntIn[x];
		}		
	}

	void UpdateRuleProfileSet( int ruleIndex, cProfileObject** profArr, int numOfProfes)
	{
		if(	m_3DimProfArr[ruleIndex]==NULL)
		{
			m_3DimProfArr[ruleIndex] = new cProfileObject*[numOfProfes];
			for(int x = 0 ; x< numOfProfes ; x++)
			{
				m_3DimProfArr[ruleIndex][x] = profArr[x];
			}
			m_numOfProflePerRule[ruleIndex] = numOfProfes;
		}
	}

	void GetProfileArrPErRuleIndex( cProfileObject**& profArr, int &size,  int ruleIndex  )
	{
		profArr = m_3DimProfArr[ruleIndex];
		size = m_numOfProflePerRule[ruleIndex] ;
	}

	double* GetDepArr(int ruleIndex)
	{
		return m_depArrHolder[ruleIndex];
	}

	int* GetDepArrCnt(int ruleIndex)
	{
		return m_depCntArrHolder[ruleIndex];
	}


//
//	bool IsExsisted(cVariableAndValueAndPoints* newInclusionArr ,  int numOfNewIncusionRules );//
//	void AddAsExsisted ( cVariableAndValueAndPoints* newInclusionArr ,  int numOfNewIncusionRules );//
	bool IsAreadyExsistts(int &foundRuleIndex , cVariableAndValueAndPoints* rule, int ruleSize)
	{
		for( int i = 0 ; i < m_numOfRules ; i++)
		{
			bool isSameRule = IsSameRuleSet(rule, ruleSize, m_rulesArr[i], m_ruleSizeArr [i]);
			if(     isSameRule )
			{
				foundRuleIndex =i;
				return true;    
			}
		}
		return false;
	}
	void AddNewRule( int &addedRuleIndex , cVariableAndValueAndPoints* ruleSet, int ruleSetSize)
	{
		if(m_numOfRules < m_maxNumOfRules)
		{
			cVariableAndValueAndPoints* temp = new cVariableAndValueAndPoints [ruleSetSize];
			for(int c = 0 ; c< ruleSetSize;c++)
			{
				temp[c] = ruleSet[c];
			}
			m_ruleSizeArr[m_numOfRules ] = ruleSetSize;
			m_rulesArr[m_numOfRules ] =temp;
			addedRuleIndex = m_numOfRules;
			m_numOfRules++;
		}
	}
};



class cEvolutionProfilePAckage
{
public:
	 cProfileObject* m_anchor;
	 cResearchDataObj* m_anchorResOBj;
	 cProfileObject** m_profList;
	 int m_proffListMaxSize;
	 int m_proffListSize;
	 int m_numOfGrps;
	 double* m_degAvgArr;
	 double* m_thresArr;
	 int* m_cntArr;

	 cEvolutionProfilePAckage(cProfileObject* anchor, cResearchDataObj* anchorResOBj, int numOfGrps);
	
	

	 ~cEvolutionProfilePAckage()
	 {
	 //6 23 23 ** decide how to manage profiels, if to delete or are they used elsewhere, keep open until usage code done
	 }

	double Calibrate(double predRAw);

	void SetCalibrationArraysFromPredArr(double* predArr,   cGlobals* globals);

	void CleanDeletedProfiles()
	{
		int movIndex=0;
		for(int i = 0 ; i < m_proffListSize ; i++)
		{
			if( m_profList[i] != NULL)
			{
				m_profList[movIndex++] = m_profList[i];
			}
		}
		m_proffListSize= movIndex;
	}

	void SetProfilesAdvancedPerfScores(double val);
	int ClearProfilesAdvancedPerfScores(double val);
	int FindHieghtsLevel( );

	int CollectProfilesFromLevelInput( cProfileObject** pArr, int level, int maxProfNum  );
 
	

};


#define SCORE_GRP_NUM 5

class cScoreGrpArr
{
public:
	double m_scoreArr[SCORE_GRP_NUM];

	cScoreGrpArr()
	{
		for(int i = 0 ; i < SCORE_GRP_NUM ; i++)
		{
			m_scoreArr[i]=0.0;
		}
	}
	cScoreGrpArr(cProfileObject* prof);

	void CopyProfArr(cProfileObject* prof);

	void CopyProfArr(cScoreGrpArr &obj)
	{
		for(int i = 0 ; i < SCORE_GRP_NUM ; i++)
		{
			m_scoreArr[i] = obj.m_scoreArr[i];
		}
	}

	 

	void CopyProfArrOut(cScoreGrpArr &obj)
	{
		for(int i = 0 ; i < SCORE_GRP_NUM ; i++)
		{
			obj.m_scoreArr[i] = m_scoreArr[i];
		}
	}










	void AddToProfWeights(cScoreGrpArr &obj)
	{
		for(int i = 0 ; i < SCORE_GRP_NUM ; i++)
		{
			m_scoreArr[i] += obj.m_scoreArr[i];
		}
	}

	void SetToZero()
	{
		for(int i = 0 ; i < SCORE_GRP_NUM ; i++)
		{
			m_scoreArr[i] =0.0;
		}
	}
};




class cResearchObject
{
//	char m_filePathNameForDisk[MAX_STRING_LENGTH];

	cProfileObject** m_profileObjectPtrList;
	int m_prifileListMaxSize;//so it is easier to open one long arry an just add 
	int m_profileListSize;


	//general thresholds to be read from the schema after initializing the schema
	int m_numberOfSubGrps;
	double m_thresholdForTerminalProfile;//after initielizing the schema, we override the defauly define

//Processing Engine Main Function
	cProfileObject* m_rootProfile;
	//cVariableSchemaObject* m_schema;
	cVariableSchemaArr* m_schemaArrr; 

	int m_sizeOfLogisticRegressionArr; //4 17 22 TO DO 2 load from configuration files and add as input to contr
	cVariableAndValueAndPoints* m_logisticRegressionVarAndPoints;//the value set with code 1 of logistic is int he schema
	
	cVariableAndValue*	m_guidedInclusionRuleList ; //list of "one level" profile or profile prefix, such that we 
	//have to have as a stand alone and a better chance to start a next child level from already must have one step
	//a future version will allow a guided rule set where each rule can be multipe var/val guiding path combinations
	int	m_guidedInclusionsRuleListSize;//m_guidedInclusionRuleList


//	double** m_patientsDataSet;
//  double* m_depArr;
//  int m_numberOfPatients;
//	int m_numberOfOriginalVars;
//	int m_numberOfAugmentedVars;


//	static void PerformanceTest( double* subGrpsDepAvgSet, double* threshArr ,	double** testData,	double* depArr,
	//	bool* isIn,	int numOfTestItems, int numOfVariables, int numOfSubGrps, cProfileObject* testedProfile);
//using comparative performacne test. taking the actulay test profile population and having that proifle model compete
	//another version of that will be with an external test data

	void ProfileComparativeReferencePerformacneTest(
		double* perfScoreArr,  cProfileObject* testedProfile, cProfileObject* refncProfile);

	
	int ClearAllProfileAdvPerformance(cEvolutionProfilePAckage*  evolPackage);

	void SetValueToAllProfileAdvPerformance(cEvolutionProfilePAckage*  evolPackag,  double val);

	
	int FindHighestLevel(cEvolutionProfilePAckage*  evolPackage);

	 
	int  CollectProfilesFromLevel( cProfileObject** pArr, int level, int maxProfNum , cEvolutionProfilePAckage*  evolPackage);

	//void UpdatedAugmentedNumberOfVariablesAndSchameaMembers(double** personsDataSet, double* depArr, bool* isPredictive);
	void SetPatientDataSet(double** personsDataSet , double* depArr);//two dim array of person value for each varible
   
//	static void PerformanceTestWithReferenceProfile( double* perfScoreArr,
//	double** testData,double* depArr,	bool* isIn, int numOfTestItems, int numOfVariables, int numOfSubGrps,
//			 cProfileObject* testedProfile, cProfileObject* refncProfile, double anchorMean);

	void CollectAllTemporaryTerminals(int* terminalIndexList, int &sizeOfTerminalList);
	 
	int  CollectRandomIndexe( int size);

//	bool IsEqualInclusionList(cVariableAndValue* varValArr1, cVariableAndValue* varValArr2, int size);
	
	bool IsEqualInclusionListNew(cVariableAndValueAndPoints* varValArr1, int size1, cVariableAndValueAndPoints* varValArr2, int size2);

	int SelectTopPerformingProfileIndex(int* terminalIndexList, int sizeOfTerminalList,  int* indexList, int indexListSize);

	bool Is_IndexAlreadyInArray( int* indexList, int size, int index);
	void CancelProfSubVAlues(double* predAdd , cProfileObject* profile, int sIndex,int numOfItems,
	                                 cResearchDataObj* researchDataObj, int recommendedSample = 1000000);
	
	void RemoveProfilesWithAllSubGroupsZero(cEvolutionProfilePAckage*  evolPackageObj);
	
bool IsProfileFound(cProfileObject** childProfArrr, int numOfProf , cProfileObject* profile);
	
//bool IsNewProfile(cProfileObject** childProfArrr, int numOfProf , cProfileObject* profile);


	
	int ClearAllProfileAdvPerformance(cEvolutionProfilePAckage*  evolPackage, double val);
	/*collect both ramdon and performacne based indexes of proifles but only select profiles with NO chidern list 
	then add a new list . 4 16 22 need to fix the functio nto ahave a wh ie and not a for to continue until the random 
	or performance is 
	*/
	void CollectListOfIndexesRAndomBestProfilesNoChildArrCoonneted(
		        int* indexList, int &numOfActualyProfilesWithNoChldConnected, int numOfRerquestedProfiles);

	void PRepareModelAndAdjustPErRootRegreMOdel(	cPercentileCalculationModel*& rootOddPredictiveModel, 
		cPercentileCalculationModel*& regPredictiveModell , cProfileObject* profile ,  cGlobals &globals );

	void KeepRandomAndTopPerformingProfiles( cProfileObject**childProfArray,cVariableAndValueAndPoints* outVarValPts, int &childIncArrSize,   
		int maxNumOfNewChildernPerProfile, cProfileObject* thisProfile );

	//4 17 22 TO DO 2 related to hard coded project first
	bool IsSignificantOddRAtio(cVariableAndValue &childInculsionAlternatives)
	{
		//go to schema obje which is a member and see that for every var val there was already a calculation on odd
		//ratio. then use that odd ratio and decide that between 0.9 and 1.1 we dont touch.
		//the threholds are per configuraiton or define

		return false;
	}


	static double CalculateStreth(double* avgDepArr, int* cntArr, double depAvg, int numOfGrps);

	static double CalculateStreth(double &depVal, double* avgDepArr, int* cntArr, int numOfGrps);

	//check if the inclusion list of a candiadte new proifle alreay cretaed an exacet inclusion list in any profile, 
	//in that case the found out proifle is the connected child that we do not need to crete any new profile
//	bool IsChildPotentialProfileExist( cProfileObject*& childPofile, 
	//	                 cVariableAndValueAndPoints* childInclusionList , int childInclusionListSize);
 
bool  IsThisInclusionRuleSetExistNew(cVariableAndValueAndPoints* inclusionRuleSet, int size,
cProfileObject** profileArr,int profileNum);

	bool IsThisInclusionRuleSetExist(cVariableAndValueAndPoints* inclusionRuleSet, int size);
	
	void KeepRulesThatMakeUniqueExtendedRuleSet(
		cVariableAndValueAndPoints* inclusionRuleListFinalList, int &incListFinalSize, 
		cVariableAndValueAndPoints* inclusionRuleListInitiall, int incListSizeInitiall, cProfileObject* thisProfile,
		cProfileObject** profileArr, int profileNum);


	 


	void CopyOriginalPatient(double* orgPatientArr , int &size, int patientIndex);
	
	
	void ConvertbEstMAtchZscoreToAnchorZscore(
		double &amchorBAsedzscore,		
		double	bestMAtchZscore, int bestMatchSubGrpIndex,		double* depArrBEstMAtch, double* depArrAnchorProfile,
		double	bmMean, double bmSD,	 double anchorMean, double anchorSD);
	
		
	void GetBestMatchResearchObj( cProfileObject  *&bestMatch , cVariableAndValue* inclusionSet,
														int sizeOfInclusionSet , double* patientArr);


	static void CalculateComparativePErfScoreInputTwoSubGrpSet(double* perfArr,
		double* subGrpsDepAvgSet, double* subGrpsReferecneDepAvgSet , int numOfSubGrps, double anchorMean);
	
	void CompareProfilePerformanceToReferance( double* comparativePerfScoreArr , 
		double* absGapArrPerSubGrp, double* avgGaparrReference, int numberOfSubGroups);


public:	
	
	cResearchObject(InputVariablesPackageForResearchObj* inputVarObj);
	
	~cResearchObject();

	cProfileObject**  GetProfileListArray(){ return m_profileObjectPtrList;}
	
	void PerformanceReport(char* performanceReportFilePath,cResearchDataObj* testDataObj )
	{
		int ssddf = 0;
	}
	 	
	void InitializeObject(int prifileListMaxSize, int numberOfSubGrps, int thresholdForTerminalProfile,
		int sizeOfLogisticRegressionArr,	cVariableAndValueAndPoints* logisticRegressionVarAndPoints,
	cVariableAndValue*  guidedInclusionsRuleList, 	int guidedInclusionRuleListSize,
	bool* isPredictive, bool* isIntervention, int* indexOfPrepField, int numberOfVariables);//, char* filePAthReadwrite)

	void EvolutionProfilesIncludingPerformanceAdvancte(cEvolutionProfilePAckage* evolPackag, InputVariablesPackageForResearchObj* inputVarObj,
	                cGlobals* globals, cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel*  regPredictiveModell);
	static void DFGHJ(double* threshArr ,  double* avgDepArr , int* cntArr,double* predArr, double* centerPredArr, int *grpIndexArr ,double* sumAdvancedPErfWghts,
		bool* isPersonIn,  	cResearchDataObj* reschDatObj, cGlobals* globals, int numOfPerformanceSubGrps, 
		cProfileObject** profileListPtr,int  profileListSize, int modePRed, bool isWithExtremeDimension,  
		bool isThisCaseOfAnchorUniverseIn , bool isWithFineTuning, bool isWithMinAdvancedPerfWeight = false);
	
	bool IsGuidedParentExsist(double &val, double &sd,  cVariableAndValue varVal);
	
	void ASDFGH(double &avgPReStr,	double &sumWghts ,	double &avgPred,
			double &avgPredWithIn ,//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
			double &avgPredWithoutIn,
			bool* isPSPs,
			double** twoDimArr,int persIndex,int  numOffVars, bool isAdvancedPerfGetbEstMatch ,
					int	interventionFieldForPredictionVariations,  cGlobals* globals, bool isWithFineTuning, 
					double strePRed,double delta, cPredictionContextObj** predictionContextObjArray,	int* sizeOfPredContObj, bool isStragith);
	
void PredictRawsNew(
	double* predArr, double* predArrWI, double* predArrWOI,
	     cPredictionContextObj** predictionContextObjArray, int* sizeOfPredContObj,
	double** twoDimArr,  int size, int numOffVars, int testRunMode, double* evolutionPredictionArr, 
	bool isAdvancedPerfGetbEstMatch , 		
	int interventionFieldForPredictionVariations,  cGlobals &globals, bool isWithFineTuning,
	 double anchorDepForProfileMatchh , bool* isPersonIn,  double profSubDepAvgTpForcee, bool isStragiht);



void PredictRaws(
	//cCalibrationContextObj* calbObj,
	double* predArr, double* predArrWI, double* predArrWOI,
	     cPredictionContextObj** predictionContextObjArray, int* sizeOfPredContObj,
	double** twoDimArr,  int size, int numOffVars, int testRunMode, double* evolutionPredictionArr, 
	bool isAdvancedPerfGetbEstMatch , 		int interventionFieldForPredictionVariations,  cGlobals &globals , bool isWithFineTuning);


	void	FillIsInProfileForEval(bool* isProfileIn, int testRunMode, cGlobals &globals);

	
	static double CalclateAnchorStretch(double*generPrediction, double* profilePrediction,   
		int numOfPts, double anchorvAluee,  double* depArr, int numOfPerformanceSubGrps, cGlobals* globals, int modePRed);
	
	/*static void PredictionTasks(double* predArrOut,double* centerPredArr, double* sumAdvPErwghts, double** twoDimArr,   bool* isPersonIn,  
		int sizeOfPop, int numOfVariables , cGlobals* globals , cProfileObject** profileListPtr,
		int  profileListSize, bool isWithExtremeDimension, 	bool isWithFineTuning, bool isThisCaseOfAnchorUniverseIn,
		bool isToAllowIncludingZeroWeight, bool isWithMinAdvancedPerfWeight);*/

	static void PredictionTasks(bool &isTargetProfileUsed, double* predArrOut,double* centerPredArr, double* sumAdvPErwghts, double** twoDimArr,   bool* isPersonIn,  
		int sizeOfPop, int numOfVariables , cGlobals* globals , cProfileObject** profileListPtr,
		int  profileListSize, bool isWithExtremeDimension, 	bool isWithFineTuning, bool isThisCaseOfAnchorUniverseIn,
		bool isToAllowIncludingZeroWeight, bool isWithMinAdvancedPerfWeight, int inputTargetedProfileID);
	
	void PreparePostCalibPredictions(double* predictionArr, double* predictionWithInArr, double* predictionWithoutInArr,
		cPredictionContextObj** predictionContextObjArray,  int* sizeOfPredContObj, 
	double** twoDimArr, double* depArr, int size, int numOFVars, int testRunMode ,cCalibrationContextObj* calbObj,
	bool isAdvancedPerfGetbEstMatch , int interventionFieldForPredictionVariations, cGlobals &globals, bool isWithFineTuning);


	static void 	CleanPSPsThatAreParentsToOtherrPSPs(bool* isPSPs , cProfileObject** profileObjectPtrList , int profileListSize);
	
	static double CalculateAvgPredictWithExtremetPredictionFocus(cProfileObject** profileListPtr, int  listSize,
												double* predArr,double* wghArr, bool* isPSPs,int numOfPSPs, bool isThisCaseOfAnchorUniverseIn);

	 static int GetTierLevelPrediction3levels(double prediction, double anchor, double* tierStructure);

	 static double GetExtremePredictionWght(double prediction, double anchor, double* tierStructure,  int numOfTiers );
		
	//fill isPSPs array with true only for profiles that are exact match to the person
	//do not consider a profile that is not true in isProfileIn
	static void CollectPSPsForOnePatient(	bool* isPSPs, int &numfOfPSPs, double* ptArr,bool* isProfileIn,
		cProfileObject** profileArr, int profileArrSize , bool isToAllowIncludingZeroWeight);


	void PredictPatientSetAndGetPErformanceELemets( double &anchorDepForBestMatch,double* predictionArr, double* predictionWithInArr, double* predictionWithoutInArr, 
		cPredictionContextObj** predictionContextObjArray,	int* sizeOfPredContObj,double* threshArr,
		double* avgDepArr, int* cntArr, double &depAvg,
		double** twoDimArr,
		double* depArr, int size, int numOFVars,cCalibrationContextObj* calbObj,   int testRunmode,
		bool isWithCalibration,  int numOfPerforancesubGrps , double* evolutionPredictionArr,
		bool isAdvancedPerfGetbEstMatch , int interventionFieldForPredictionVariations,cGlobals &globals , bool isWithFineTuning ,
		 bool* isPersonIn, double profSubDepAvgTpForce, bool isStragith);


			
	/*	->m_profileListMaxSize,
		inputVarObj->m_numberOfSubGrps,
		inputVarObj->m_thresholdForTerminalProfile,inputVarObj->m_numOfRegrEleents,
		inputVarObj->m_varValPointsRegWghArr,   inputVarObj->m_personsDataSet , inputVarObj->m_depArr,  
		inputVarObj->m_numberOfPatients ,	  inputVarObj->m_numberOfOrgVariables,	  //x and y dimensions
		 inputVarObj->m_guidedInclusionsRuleList,   inputVarObj->m_guidedInclusionRuleListSize,
		 inputVarObj->m_isPredictive,  filePAthReadwritee	);*/

	//will take each person from data objet and call the prediction api getting output the followiong:
	//predciton, which is the average bucket of the best match profile 
	//profile inclusion rules/var/val, averge dep of the profile and bucket gruop of the profile 
	//weights . top eighs, of vars/vals that the person had and gave high weight on the person scasle and then effectint the bucket. together with the profile variables these will be the ones to present
	//sine we are uere presenting a file and not a person analytics the top vars mathed per persons will get summarized and presneted on the global 
	//also the 5 buckets of predictio per study will be presnted
	///also a way to sho per each of the 5 gruops how with intervention was any differnet than the without. use only profiles in these 5 groups that had a designated profiles that are an aloed context
	//to certain intervetion and that haave the intervention and othes profile that do not have the interention. that will be done when we asked for profiles inclusion we get var val, not only var, then we can get both
	//0 and 1 for interention varibles and fo othes we may only het the 1, depends. need to see that i am getting var val
	//an easy way is to use the guildlnes and to add intervention to these must be . for example we get 20 interventions with 2 optionns each, comunicated through var/val in the config and in the input data file,
	//and 5 wp3 var/val options, all together we get first line of 45 . then we can configure in the incusions also pairs and get actually the wp both separate and under all 20. then we dont need to evolution with intere
	//but just let intervention be first under the root and then do for eacah what we do toda for root. matbe open different research objects, but when we open intervension "wound clean" we by definition get this filter plus all releant context filter
	//by meta config and add to the inclusino rules two vars on the price of one. it can be a must or ust algo but due to given meta data dependancies they always go together . in matter of order, first the intervenetion
	//and under a list of children that are releant for such, and then let the algo start only. this means implementin first and secondn flow design and configuring for same input data differnet folders , 20 of them, and
	//they will then have just differnert nreports, then we can copy reports to slides.
	//the engine then just need to do that seond / pairs 
	//bette start with one level of 45 as in this example and then 
	
 
	//////GET FUNCTIONS /////////////////
	cProfileObject* GetRootProfile(){return m_rootProfile;}
//	int GetGuidedIncludionRulesSetSize(){	return m_guidedInclusionsRuleListSize;	}
//	cVariableAndValue* GetGuidedInclusionRuleSet(){		return m_guidedInclusionRuleList;	}
//	int GetNumberOfPatients(){		return m_numberOfPatients;		}
//double** GetPatientDataSet()	{ 		return m_patientsDataSet;}
//double* GetDependentArray()	{		return m_depArr;	}
//	int GetNumberOfAugmentedVars()	{		return m_numberOfAugmentedVars;	}
	int GetNumberOfSubGrps()	{		return m_numberOfSubGrps;	}
	int GetNumberOfProfiles() { return m_profileListSize; }

	int GetMaxNumberOfProfiles() { return  m_prifileListMaxSize; }
//	double* GetPatientIdataSet(int index)	{		return m_patientsDataSet[index];	}
	cVariableSchemaArr* GetSchema ()	{	return m_schemaArrr;	}
/////////////////////////////////////////////
	void MachineLearningAdjustDeltaPerfElementsAndUpdateProfiles(double** deltaStrchWithSubProfileFocus,
	double** meanDeltaProfSub ,  double** sdDeltaProfSub , int numProfiles, int numSubGrps,  
	int numOfPersons , int numberOfStrchBuckets,  bool isWithTestPop, cResearchDataObj* researchDataObj,
	    cGlobals* globals,  int isWithFineTuning	);
		
	void  PRedictIncludingBuildPerfirmanceArray( double &anchorDepForBestMatch, double*	threshArr, double* avgDepArr,  int* cntArr,  double &depAvg,
		double* evolutionPredictionArrr, double &baseOverallStretch,
	int ptArrSize,  int numOfStretchCategories, cResearchDataObj*  researchDataObj, cGlobals* globals,bool isWithFineTuning,
	 bool* isPersonInProfSub, double profSubDepAvgTpForce, bool isStregithPrediction);

	
void  PRedictIncludingBuildPerfirmanceArrayNew( double &anchorDepForBestMatch,
	double*	threshArr, double* avgDepArr, int*  cntArr, double &depAvg,
	double* evolutionPredictionArrr, double &overallStretch,
	int ptArrSize,  int numOfStretchCategories, cResearchDataObj*  researchDataObj, cGlobals* globals ,
	bool isWithFineTuning , bool isWithTest, bool	isApplyDeltaRangeRestic, bool* isPersonInProfSub, 
	double profSubDepAvgTpForce,  double profSubMeanDelta, double profSubSDdelta);

	
	void FindWinnersFromDifferentTypes(int &indexOfWinnerLeft, int &indexOfWinnerRight,  int & indexOfWinnerAbs,
				bool* isIn, bool* isAlreadyWon, bool* isTerminal ,  cProfileObject** profList, int numOfProfiles,  int maxRuleLength );

	void IdentifyEachProfileWithItsGroupsIdentfier(
		int* profileSizedGrpIdentfier, int &numOfGroups,int maxSizeOfProfileGrp,  cGlobals &globals, cProfileObject** profArr, int profListSize);
	
	void BuildResearchElements(cResearchDataObj* researchDataObj, bool* isTerminalProfileArr,
		InputVariablesPackageForResearchObj* inputVarObj, cGlobals &globals);


	
	void RecursiveEvolution(
	//cProfileObject** profilePtrArr, int &movingProfleIndex,
	int maxNumOfProfiles,
	cVariableAndValueAndPoints*   inclusionArrCaller , int sizeOfInclusArrCaller , int nextVar, double varVal,
						cResearchDataObj* resObj , bool* isPredictive, cGlobals* globals,
							cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel*  regPredictiveModell,
							InputVariablesPackageForResearchObj* inputVarObj, double depAnchorUniv
						);

	void 	CalcualtePerformanceBuckets(
	  double* depAvgArr, int* cntArr, double &avgDep, 
	 int numOfGrps,   cResearchDataObj* researchDataObj, cProfileObject* profile);


	
bool IsThisProfileHasChildren( 
	cProfileObject* thisProfToPlayWith,cProfileObject** profList , int numOfProfes);


void SecondRoundOfMLtry( double* movingSavingTimeOut,
	double &movingScore,  cResearchDataObj* researchDataObj , cProfileObject* root, cProfileObject* anchorProfile,
									bool* isPredictive,  cGlobals* globals,cVariableSchemaArr* schemaArr,
							cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel* regPredictiveModell	,
								InputVariablesPackageForResearchObj* inputVarObj, cProfileObject* thisProfToPlayWith,
	int numOfCalibrationGrps , cEvolutionProfilePAckage**  evolPackage, 
	double* stretArr, bool isThisCaseOfAnchorUniverse6, double* saivingTimeIn	);

void SecondRoundOfMLtry2( double* movingSavingTimeArrOutt,double &movingScore, 
		cResearchDataObj* researchDataObj , cProfileObject* root, cProfileObject* anchorForStretch, bool* isPredictive,  cGlobals* globals,
		cVariableSchemaArr* schemaArr,	cPercentileCalculationModel* rootOddPredictiveModel, 
		cPercentileCalculationModel* regPredictiveModell, InputVariablesPackageForResearchObj* inputVarObj, 
		cProfileObject* thisProfToPlayWith, int numOfCalibrationGrps , cEvolutionProfilePAckage**  evolPackage, 
		double* stretArr, bool isThisCaseOfAnchorUniverse6,  double* savingTimeArrInn	);

void SecondRoundOfMLtry3(//cScoreGrpArr &scoresGrp, 
	double &correlScore ,double*  predArrOutt, 
		cResearchDataObj* researchDataObj , cProfileObject* anchorForStretch, cProfileObject* root,
		cGlobals* globals, 	cProfileObject* thisProfToPlayWith, int numOfCalibrationGrps , cEvolutionProfilePAckage**  evolPackage, 
		double* stretArr,   double* savingTimeArrInn,  double startScsore,  int  sIndex);

double RotateProfilePerf(double &outRank, double &points, cResearchDataObj*  researchDataObj,  cProfileObject* profile,  int s,
	 cProfileObject* anchor,   cProfileObject* root, cGlobals*  globals,  int numOfCalibrationGrps, cEvolutionProfilePAckage** evolArr,
	 double*  stretArr, double* predWithZeroedLevelOrNULL,   double scoreOff, double scoreOn);
	

void CalculaterRankOfProfSubParentsPerfValues(int* rankArrWithSub, cProfileObject** pArr, int numOfProfSubs,
	int numOfPrfilesInLevel, cEvolutionProfilePAckage** evolPackage, int w, cResearchDataObj* researchDataObj,
	cProfileObject* root, cGlobals* globals, int numOfCalibrationGrps, double* stretArr , 
	int requestLbyAboveLoop, int iterIndex);


double TryWeighhtByOrderAndKeepBestOPtion4( cProfileObject** pArr,  int* rankArrWithSub,
	//double* rankValueArrWithSub, 
	int numOfProf,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals,int* rankArr, 
							int requestLbyAboveLoop, int iterIndex,  int w);//, cScoreGrpArr* oneLevelScoreGro);

double TryWeighhtByOrderAndKeepBestOPtion5( cProfileObject** pArr,  int* rankArrWithSub,
	int numOfProf, cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
	cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj, int numOfCalibrationGrps, 
	cGlobals* globals, int* rankArr, int requestLbyAboveLoop,  int iterIndex,  int w, int globalIterationIndex);


bool OneProfsubOrderedProcecss5( double &endOfProcessBP ,double* startingPointArrr, cProfileObject* profile, 
	int* rankArrr,  int* rankArrWithSubb, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							   int profIndex,  int s,  int iterIndex, double inputMovingPerf, 
							   int levelForPrint, int w, bool isFirstGlobalItration, bool isUp, int globalIterationIndex );

bool OneProfsubOrderedProcecss6( int &cntOFDifferenceCases, double &endOfProcessBP ,double* startingPointArrr, cProfileObject* profile, 
	int* rankArrr,  int* rankArrWithSubb, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
					int profIndex,  int s,  int iterIndex, double inputMovingPerf, 
					 int levelForPrint, int w, bool isFirstGlobalItration, bool isUp , 
					 int globalIterationIndex,
	int profSubHighestSampleTry, int profileIdTested, int lowestSampleSizeTest, 
	double* fullPredictionPreviousSet, bool isToUPdateProfsubStatusAndPredictionarray, int indexInRaw, int sizeOfRaw);

double OneProfsubOneWeight2(double* prediction, cResearchDataObj* researchDataObj, int s,   double wghValue,  cProfileObject* profile,
	cProfileObject* root,	 cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps, cGlobals* globals,cEvolutionProfilePAckage* evol, 
	 double* statArr, double* savingTimeArr ,  int profileIdTested, 
	 int lowestSampleSizeTest, double* fullPredictionPreviousSet);

double TryWeighhtByOrderAndKeepBestOPtion6( cProfileObject** pArr,  int* rankArrWithSub,
	int numOfProf, cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
	cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj, int numOfCalibrationGrps, 
	cGlobals* globals, int* rankArr, int requestLbyAboveLoop,  int iterIndex,  int w, int globalIterationIndex,
	int profSubHighestSampleTry, int lowestSampleSizeTest , int ratioOfGoingForZeroWghProfsubs);

void LearningIterationsWithinEachLevel2(int minAnchorLevel,  int maxHighestLevel, int numberOfInternalIterations,
	double* calbratedThresArr,  int* bucketIndexArr,  double* calbAgDepArr,   int* calbCntArr,  
	int	numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObj,
	cEvolutionProfilePAckage**	evolPackage,  cProfileObject*  root , cGlobals*  globals, 
	double* stretArr,  bool isToreplaceToLogRegweights,  int globalIterIndex, 
	int  profSubHighestSampleTry,  int  lowestSampleSizeTest,  int ratioOfGoingForZeroWghProfsubs);

void ParentChildLearning6(	double** rankArrOut, int *numberOfProfSubsOut,   
	double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObjj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,   cGlobals* globals,
			double* stretArr, int iterIndex, bool isToRepaceToLogisticModeoWeights,
			int maxHighestLevel,	int minAnchorLevel, int requestLbyAboveLoop,
			double** rankArrIn,  int globalIterIndex, int profSubHighestSampleTry,
			int lowestSampleSizeTest , int ratioOfGoingForZeroWghProfsubs);

void SwapAndPredictionCover2(double &correlScore,double* predArrOutt, cEvolutionProfilePAckage** evolPackage,
	cProfileObject* root, cProfileObject* anchorForStretch, cGlobals* globals, double* stretArr, double* savingTimeArrInn,
	cResearchDataObj* researchDataObj,  int numOfCalibrationGrps, int inputTargetedProfileID , 
	int inputTargetSample	, double* backUpArrWithAllPastPredictions );

double SwapProfilesWithAnchors2( double* savlingtieArrOut,
	double* calbratedThresArr, int* bucketIndexArr, double*  calbAgDepArr,  int* calbCntArr,  int numOfCalibrationGrps,
	double* calibatedPRed, cResearchDataObj* researchDataObj, cEvolutionProfilePAckage** evolPackage,
	   int numberOfEvolPrffItems,  cProfileObject* roott  ,cProfileObject* anchorForStretch, cGlobals* globals,  int evoPacackIndexToUpgrade,
	   double* stretArr, bool isThisCaseOfAnchorUniverseIn,   double* savlingtieArrIn, bool isToDEnyCalibration,
	   int inputTargetedProfileID , int inputTargetSample	, double* backUpArrWithAllPastPredictions   ) ;

bool SelectIfToTryInThisCase(double baseValue, bool isFirstGlobalItration, int random);

void LearningIterationsWithinEachLevel(int minAnchorLevel,  int maxHighestLevel, int numberOfInternalIterations,
	double* calbratedThresArr,  int* bucketIndexArr,  double* calbAgDepArr,   int* calbCntArr,  
	int	numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObj,
	cEvolutionProfilePAckage**	evolPackage,  cProfileObject*  root , cGlobals*  globals, 
	double* stretArr,  bool isToreplaceToLogRegweights,  int globalIterIndex);

bool OneProfsubOrderedProcecss4( double &endOfProcessBP , double* startingPointArrr, cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							  int profIndex,  int s, int iterIndex,  double inputMovingPerf, 
							  int levelForPrint, int w, bool tryGoDown);

bool OneProfsubOrderedProcecss3( double &endOfProcessBP,  cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,	cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 	int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro, double* startingPointArrr,  int profIndex,  int s);

void PlayWithOneLevelWeightAnalytics3(double* outRank, double* scorePoints,cProfileObject ** pArr, int &numOfProfs,
	//	int* perLevelProfNum,
	cEvolutionProfilePAckage* evol  , int l,//  int maxProfNum,
	cResearchDataObj* researchDataObj, cProfileObject* anchor,  cProfileObject* root, cGlobals* globals,
	cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps,  double movingScre, 
	double* stretArr, bool isToOnlyCheckPositiveWeights	, bool isWeightedLevelAsBase , cScoreGrpArr* scoresGrpArrIn, bool isAdjustingScoreBasedOnResults, int* rankArr);

void UpdateProfilesWithOutputWeights(  cScoreGrpArr* scoresGrpArrOut   ,int numOfProfs,  cProfileObject** pArr,  double* newPredictionarr,
	cEvolutionProfilePAckage** evolArr,   cResearchDataObj* researchDataObj, int numOfCalibrationGrps, double* stretArr,
	cGlobals* globals, cProfileObject* anchor, cProfileObject* root);

void KeepCurrentWeightsaved(cScoreGrpArr **& scoresGrp, int *&perLevelProfNum, int higestLlevel,  int  anchorLevel,
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage*  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter);



void KeepCurrentWeightsaved2(//cScoreGrpArr *scoresGrpOneLevel, int *&perLevelProfNum, int higestLlevel,  int anchorLevel,
					cScoreGrpArr *scoresGrpOneLevel, int l,
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage*  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter);

double OneProfsubOrderedProcecss2( cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							double* startingPointArrr,  int profIndex,  int s);

 

void ProcessOneLevelFromOneAnchorProSet2( cScoreGrpArr*& oneLevelScoreGro ,  cEvolutionProfilePAckage** evolPackage , int w, cResearchDataObj* researchDataObj,
	 cGlobals* globals, int numOfIter , int l,  bool isToRepaceToLogisticModeoWeights,
	 cProfileObject*   root,  int numOfCalibrationGrps, double* stretArr , double* calbratedThresArr, int* 	bucketIndexArr, 
	 double* calbAgDepArr,   int* calbCntArr, double*  calibatedPRed, int profileListSizee  );


double TryWeighhtByOrderAndKeepBestOPtion3( cProfileObject** pArr, int* rankArr,  int* rankArrWithSub, int numOfProf, cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 	int numOfCalibrationGrps	,
				cGlobals* globals, cScoreGrpArr* oneLevelScoreGro);

void ParentChildLearning3(	double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage**  evolPackage,   int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter,  bool isToRepaceToLogisticModeoWeights);


void ProcessOneLevelFromOneAnchorProSet(cEvolutionProfilePAckage** evolPackage , int w, cResearchDataObj* researchDataObj,
	 cGlobals* globals, int numOfIter , int l,  bool isToRepaceToLogisticModeoWeights,  cProfileObject*   root,  int numOfCalibrationGrps, double* stretArr , double* calbratedThresArr, int*	bucketIndexArr,
	 double* calbAgDepArr, int*  calbCntArr,  double*  calibatedPRed, int profileListSizee );

void ParentChildLearning4(//	double* movingSavingTimeArrOut,	
			double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,   cGlobals* globals,
			double* stretArr, int numOfIter,bool isToRepaceToLogisticModeoWeights);



void PostLearningLoop( cResearchDataObj* researchDataObj,
	double* calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int*  calbCntArr, int numOfCalibrationGrps, double* calibatedPRed, 
	cEvolutionProfilePAckage** evolPackage,   int profileListSizee, cProfileObject* root,  cGlobals* globals, double* stretArr);

void ParentChildLearning5(double** rankArrOut, int *numberOfProfSubsOut,   
	double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,  
			cGlobals* globals,	double* stretArr, int iterIndex, bool isToRepaceToLogisticModeoWeights,
			int maxHighestLevel,	int minAnchorLevel, int requestLbyAboveLoop, double** rankArrIn, int globalIterIndex);

double OneProfsubOneWeight(double* prediction, cResearchDataObj* researchDataObj, int s,   double wghValue,  cProfileObject* profile,	cProfileObject* root,	 cEvolutionProfilePAckage** evolArr,
												int numOfCalibrationGrps, cGlobals* globals,cEvolutionProfilePAckage* evol, 	 double* statArr, double* savingTimeArr);


static double CalculateAvgPredictWithExtremetPredictionFocus2(cProfileObject** profileListPtr, int  listSize, double* predArr,double* wghArr, bool* isPSPs,int numOfPSPs, bool isThisCaseOfAnchorUniverseIn);

double TryWeighhtByOrderAndKeepBestOPtion( cProfileObject** pArr, int* rankArr,  int* rankArrWithSub, int size,	cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 	int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro);

double TryWeighhtByOrderAndKeepBestOPtion2( cProfileObject** pArr, int* rankArr,  int* rankArrWithSub, int numOfProf,	cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 		int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro);

double OneProfsubOrderedProcecss( cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,	cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 	int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro, double* startingPointArrr,  int profIndex,  int s);

void TestAndScore(cScoreGrpArr  &scoresGrp, cProfileObject* profile);

void RotateToSetProfileRank(double* rankValueArr, double* rankValueArrWithSub, cProfileObject** pArr , int size, cEvolutionProfilePAckage** evolArr,
	cResearchDataObj* researchDataObj, cProfileObject* root, cProfileObject* anchor, cGlobals* globals, int numOfCalibrationGrps, double* statArr);

double GetPointBiserial (	);

/*double movingStretch =  cResearchObject::SwapProfilesWithAnchors(
						movingSavingTimeArrOut,	
							calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
							researchDataObj,  evolPackage,
						profileListSizee,   root ,evolPackage[w]->m_profList[0], globals, 0 , stretArr,
						false, NULL, true); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
			double eta = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	);*/

void ParentChildLearning2(//	double* movingSavingTimeArrOut,	
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage**  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter);

//void SwapAndPredictionCover(double &correlScore,double* predArrOutt, cEvolutionProfilePAckage** evolPackage,
//	cProfileObject* root, cProfileObject* anchorForStretch, cGlobals* globals, double* stretArr, double* savingTimeArrInn,
//	cResearchDataObj* researchDataObj,  int numOfCalibrationGrps);

void PlayWithOneLevelWeightAnalytics2(cScoreGrpArr** scoresGrpArr, int* perLevelProfNum,
	cEvolutionProfilePAckage* evol  , int l,  int maxProfNum,
	cResearchDataObj* researchDataObj, cProfileObject* anchor,  cProfileObject* root, cGlobals* globals,
	cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps,  double movingScre, double* stretArr,
	bool isToOnlyCheckPositiveWeights	, bool isWeightedLevelAsBase);

void PlayWithOneLevelWeightAnalytics(cScoreGrpArr** scoresGrpArr, int* perLevelProfNum,
	cEvolutionProfilePAckage* evol  , int l,  int maxProfNum,
	cResearchDataObj* researchDataObj, cProfileObject* anchor,  cProfileObject* root, cGlobals* globals,
	cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps,  double movingScre, double* stretArr, bool isToOnlyCheckPositiveWeights);

void ParentChildLearning(	double* movingSavingTimeArrOut,	
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage**  evolPackage,
				int 	profileListSize,  cProfileObject* root ,   cGlobals* globals, double* stretArr,  int numOfIter);



//double CalcualteETA(double* predArr, double* depArr, int size);


//6 23 23 
void TemporaryREcursiveCall2(cResearchDataObj* researchDataObj , cProfileObject* root, 	bool* isPredictive,
		cGlobals* globals , cVariableSchemaArr* schemaArr,
		cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel* regPredictiveModell,
		InputVariablesPackageForResearchObj* inputVarObj
		);


//6 23 23 
void TemporaryREcursiveCall1(cResearchDataObj* researchDataObj , cProfileObject* root, 	bool* isPredictive,
		cGlobals* globals , cVariableSchemaArr* schemaArr,
		cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel* regPredictiveModell,
		InputVariablesPackageForResearchObj* inputVarObj
		);
	
	void GetBucketsUsingInputAnchorProfile( double* depBucketAnchorArr, int* depBucketSmpleArr, 
			int numOfCalibrationGrps, cProfileObject* anchorPr ,  cResearchDataObj*	researchDataObj , cGlobals* globals );




//	static double SwapProfilesWithAnchors(double* savlingtieArrOut,
//	double* calbratedThresArr, int* bucketIndexArr, double*  calbAgDepArr,  int* calbCntArr,  int numOfCalibrationGrps,
//	double* calibatedPRed, cResearchDataObj* researchDataObj, cEvolutionProfilePAckage** evolPackage,
//	   int numberOfEvolPrffItems,  cProfileObject* root  , cProfileObject* anchorForStretch, cGlobals* globals,  int evoPacackIndexToUpgrade,
//	   double* stretArr, bool isThisCaseOfAnchorUniverseIn,   double* savlingtieArrIn, bool isToDEnyCalibration = false); //objIndex);

	static cProfileObject* FindWhichIsAnchor(cProfileObject**  profileListPtr,int listSize,bool* isPSPs,int numOfPSPs);
	
	static void MergerTwoDimDepArraysToOneDim(double* depArrMErged , int*  depArrCntMeged, 
								double**  depArrValueTwoDim, int** depArrValueCntTwoDim , int numOfValues, int numOfCalibGrps);
	
	static void CollectLowestAndHighestIndexForNextGrp( int lowest, int &highest, int* sortedDepCntnOneLine ,
	  int lineSize, int countExpeccted);

	bool RecursiveProfileBuild(
		cProfileObject** profileList, int &movingPrIndex,	double*  bucketArrOut  , int* bucketCntArrOut, double &stretchOut,  
	     int maxNumOfProfes, int numOfCalibrationGrps, 	cResearchDataObj* researchDataObj,  bool* isPredictiveRecursive,  bool* isPredictiveOneLevelUse,
	                cGlobals* globals,   double depAnchorUniv,	 cProfileObject*  anchorPr,
					cVariableSchemaArr* schemaArr, int minSampleToContinueRecursive,  int currentNumOfRecursiveLevels, int maxNumOfLevelsToGoRecursive,
					cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel* regPredictiveModell,
					cInclusionRuleDataSet*	inclusionDataSet, bool isThisCaseOfAnchorUniverseIn);
	 			
	
	bool IsProfileFoundInList( cProfileObject* prof,  cProfileObject** list,int size);

	int FindBestNextVarWithPerformCompare(cResearchDataObj* researchDataObj,
					bool* isPredictive, cGlobals* globals, int numOfGrps, cProfileObject* profileBase, double depAvgUniv);
	int FindBestNextVar(cResearchDataObj* researchDataObj, bool* isPredictive, cGlobals* globals,  double depAnchorUniv);
	void CollectSampleAndDepAverage(double &depAvg, int &sample, cResearchDataObj* researchDataObj, int var, double val);
	void BuildResearchElementsWhileLoop(cProfileObject** tempProfileArr,int &profileMovingIndex,	cResearchDataObj* researchDataObj,  	
		InputVariablesPackageForResearchObj* inputVarObj ,  cGlobals &globals, 		int maxItneration, int  maxNmberOfProfiles,
		cProfileObject* anchor,	cPercentileCalculationModel* rootOddPredictiveModel,
		cPercentileCalculationModel* regPredictiveModell,  double depUniv, int maxNiumOfRuleToAchive);

	static void ConvertPointsToPredictions(double* predSet, int* grpIndexArr, int numOfStretchGrps, double* sumPntsArr, double* depArr, bool*  isInAll,  int size, cGlobals*  globals);

	static double ConvertPredictionsToDepAvgBucketsAndCalcStretch(
		double* threArr, double* depAvgArr, int* subPopSize, double &avgDep,
			double* predSet,double* depArr, bool* isIn, int size,
	                             int numOfStretchGrps , cGlobals* globals,   double* givenThreshold);
	static double CalcUpdatedPredWithaccommulativeSums( double predValBaseForDEbug, double sumWhtsMatchedProfiles, int numOfProfilesMatched, 
		double sumWeightedPRedictionsMatched, double addedPrediction, 		double newWght)
	{
		double testAvg = sumWeightedPRedictionsMatched /sumWhtsMatchedProfiles ;
		//test avg sh uld be like the predValBaseForDebug
		double newPrediction = (sumWeightedPRedictionsMatched +  (addedPrediction * newWght)) / (sumWhtsMatchedProfiles + newWght);
		return newPrediction;
	}
	
	
 static double StretchLoop(double* avgDepArr,  int* cntArr,    int numOfPerformanceSubGrps , double anchorvAluee);
 
	static double StretchCalculation(double* thredArrOut,double* predArr , double* depArr, int numOfItems, double  anchorvAluee,
	  cGlobals* globals, 		  int modePRed, int numOfPerformanceSubGrps, double* thredArrIn);


	static double StretchCalculation(double* thredArrOut,double* predArr , cResearchDataObj*  rschDataAnchor, double  anchorvAluee,
	  cGlobals* globals, 		  int modePRed, int numOfPerformanceSubGrps,double* thredArrIn);

	static double ProfileAddingTest(double* depAvgArrr,  int* cntAvgArr, double* thredArrOut,double* predArr,  double* centerPredArr, double* sumAdvancedPErfWghts,
	cProfileObject** profArr ,int numOfProfiles,
	      cResearchDataObj*   rschDataAnchor, double anchorvAlueee, cGlobals* globals, 
		  int modePRed, int numOfPerformanceSubGrps ,  double*  tierStrucrue, int numOfTiers, bool  isWithExtremeDimension, 
		  bool isThisCaseOfAnchorUniverseIn , bool isWithFineTuning);

	static void CollectWeieghtedDepArr(double* depLocal ,int* cntLocal, double*  predArr , double* threshArr ,	int numOfGrps,cResearchDataObj* rschDataAnchor);


	
	static void ProfSubPErsonAnalytics( cProfileObject** profileArrr,  int numberOfProfiles, cResearchDataObj* rschDataAnchor,
	   double* predArrAfter,	int numOfPerfGrps, double* thredArrBase,  int modePred, double anchorvAluee, 
	   double stretchBase,  double multiplerr,	   cGlobals* globals,  double* depAvgArrr,   int* cntAvgArr, bool isWithDecreasedScores,  bool isWithFineTuning  );


	static double GetLocalStretchValues( double* predArr , double* predArrP , double anchor  , int numOfGrps, cResearchDataObj* rschDataAnchor, 
							double* threshIn,		double* depArrIn, int* cntArrIn,	cGlobals* globals);

	static double	CalcualteFullTest( cResearchDataObj* rschDataAnchor , double* localPRediction, double* predArrAfter,  bool* isInProffSub, int sizeOfProffSub,
		cProfileObject** profileArrr, int p, double*  thredArrBase , double*   depAvgArrIn,  int* cntAvgArrIn,  int numOfGrps,
		double anchorvAluee ,	double stretchBase, cGlobals* globals,  bool isWithFineTuning);


	static void AddOrRemoveSubPoopulationsFromDepArr   (  double* depArrNew, int* cntarrNew ,  double* depArrCur , int* cntArrCur  , 
																	double* subDepArr , int* cntSubDepArr , int numOfGrps , bool isToAdd);


	static void AddOrRemoveSubBucketsOfDepValues(double &depNew, int &cntNew ,  double depCur , int cntCur  ,	double subDep, int cntSubDep,   bool isToAdd)
	{
	/* 
	if this is a substrct case, if( isToAdd == false)
		depCur =  ( depNew * wghNew  + subDep * wghSub ) /  	(wghNew + wghSub)
		depCur * 	(wghNew + wghSub) =  ( depNew * wghNew  + subDep * wghSub ) 
		(depCur * 	(wghNew + wghSub) ) - (subDep * wghSub ) = depNew * wghNew  
		depNew = ( (depCur * 	(wghNew + wghSub) ) - (subDep * wghSub ) ) / wghNew  
	
	if this is a adding  case, if( isToAdd == true)
	    depNew = (depCur * cntCut + subDep * cntSubDep ) / (cntCur + cntSubDep) 


	*/
		double wghCur  = double(cntCur);
		double wghSub = double(cntSubDep);
		double wghNew = 0.0; 
		if( isToAdd == false)//a case of substructing
		{
			wghNew = wghCur -  wghSub;
			wghNew = cVarianceCalc::Max(wghNew ,0.0);
			cntNew = int(wghNew);
			depNew = 0.0;
			if(wghNew  >0.0)
			{
				depNew  = ( (depCur * 	(wghNew + wghSub) ) - (subDep * wghSub ) ) / wghNew  ;
			}
		}
		else
		{
			wghNew = wghCur +  wghSub;
			cntNew = int(wghNew);
			depNew = 0.0;
			if( (wghCur + wghSub)  > 0.0 )
			{
				depNew = (depCur * wghCur + subDep * wghSub ) / (wghCur + wghSub);
			}
		}	
	}
		














static double ABCDEFG(  cResearchDataObj* rschDataAnchor , double* localPRediction, double* predArrAfter,  bool* isInProffSub, int sizeOfProffSub,
		cProfileObject** profileArrr, int p, double*  thredArrBase , double*   depAvgArrIn,  int* cntAvgArrIn,  int numOfGrps,
	double anchorvAluee ,	double stretchBase, cGlobals* globals);

static void	AdjustIsInAndSizeConsideringChildProfiles(bool* isInProffSub,  int &sizeOfProffSub, 
     cResearchDataObj*   rschDataAnchor, cProfileObject** profileArrr,  int numberOfProfiles , int p,  int s);

	//7 11 23 * 55
	static void	MoveSmallStepIfRateAllows( double &rateUsed, double &predictionMixed,	
		double currentPRed     ,double suggestedPRediction,
		double* thresholdArrIn,	double* depAvgArrIn, int* cntAvgArrIn,  double maxRate, int numOfPerfGrps , double anchorVal);


 //6 13 23 *** tuirn this to status and see if compiles
void FillProfileListObjectsWothAdvancedPerformanceNew2(	cProfileObject** profileArrr,
			int numberOfProfiles,cProfileObject* anchor, cResearchDataObj*   rschDataAnchor,
			cGlobals* globals, int numOfSubGrps,  double depAnchorUnivvv, bool isThisCaseOfAnchorUniverseIn);

	static void FillProfileListObjectsWothAdvancedPerformanceNew(	cProfileObject** profileArr,
			int numberOfProfiles,cProfileObject* anchor, cResearchDataObj*   rschDataAnchor,
			cGlobals* globals, int numOfSubGrps , double depAnchorUniv, bool isThisCaseOfAnchorUniverseIn);
	static double PreictionAndStretch(double* depAvgArr,int* subPopSize, double &avgDep,
		double* predSet, int* grpIndexArr, cProfileObject* anchor, cResearchDataObj* rschDataAnchor,
		cGlobals* globals, int numOfStretchGrps , double depAnchorUniv);
	 

	static void FillProfileListObjectsWothAdvancedPerformance(	cProfileObject** profileArr,	int numberOfProfiles,
										cProfileObject* anchor,cResearchDataObj*   researchDataObj,cGlobals* globals , int numOfSubGrps);

//	void LongStretchPerfProcess(double* evolutionPredictionArr,double* addedStretchArr, cResearchDataObj* researchDataObj,  cGlobals &globals);
	
	void LongStretchPerfProcessNew(double** addedStretchArrr, double** meanDeltaProfSub, double**	sdDeltaProfSub,
												 int numOfSubGroups, cResearchDataObj* researchDataObj, cGlobals *globals);
	
	//void  FillIsInProfSub(bool* isPersonInProfSub,int numOfPersons,int p,  int x);
	
	static int  FillIsInProfSub(bool* isPersonInProfSub,cProfileObject** profileArr, int p,  int x, cResearchDataObj* researchDataObj, bool* isInContext);
	static int  FillIsInProfSub(bool* isPersonInProfSub,cProfileObject* profile,  int x, cResearchDataObj* researchDataObj, bool* isInContext);
	
	
	void PredictionAndCalculatePerformanceStretch( double &anchorDepForBestMatch,double* threshArr ,double* avgDepArrLocal,	int* cntArrLocal,	double &depAvgLocal , 
	double* predictionArr,double* predictionWithInArr  , double* predictionWithoutInArr,   int arraySize,bool* isIn,  
	cResearchDataObj* researchDataObj, cGlobals &globals , int numOfStretchCategories, bool isWithFineTuning, 
	bool* isPersonIn, double profSubDepAvgTpForce, bool isStragithPRed);

//	void UpdtePredictionArrAndCalculatePerformanceStretch(double &stretch, double* evolutionPredictionArr, int arraySize,
//	bool* isIn,  cResearchDataObj* researchDataObj, cGlobals &globals,  int numOfStretchCategories);
	
	void  CreatePotentialChildProfiles(cProfileObject** childProfArr  , cVariableAndValueAndPoints* outVarValPts , double*	parentbasedPerformanceArr, int &numOfAddedPoteChildren,
		cProfileObject* thisProfile, cVariableAndValueAndPoints* inclusionRuleList, 
			int incListSize,cResearchDataObj* researchDataObj,  cPercentileCalculationModel* rootOddPredictiveModel,
			cPercentileCalculationModel* regPredictiveModell);
	
	void CreateChildProfileArr( cProfileObject** childProfArrr  ,  cProfileObject* thisProfile,  cVariableAndValueAndPoints* varValPts , int numOfObjects,
	cResearchDataObj* researchDataObj, 	cPercentileCalculationModel* rootOddPredictiveModel,
	cPercentileCalculationModel* regPredictiveModell, cGlobals &globals, cProfileObject* anchor);

	
	bool CreateInclusionSetForNextLevel(
	  bool  &isMatchMustBeRule,	cVariableAndValueAndPoints*& varValInclusionArr, int &size,    cProfileObject* thisProfile, cVariableAndValueAndPoints &obj);

	bool CrerateNewChildProfilesToThisProfile(cProfileObject**& chldProfArr, int &numOfChildren,
	   cProfileObject*  thisProfile,  cPercentileCalculationModel* rootOddPredictiveModel,
    	cPercentileCalculationModel* regPredictiveModell, cResearchDataObj* researchDataObj,
		InputVariablesPackageForResearchObj* inputVarObj ,  cGlobals &globals, cProfileObject* anchor,
		cProfileObject** profileArr, int profileNum)  ;

	
	bool AddPotetialChildren(cProfileObject**	poternList, cVariableAndValueAndPoints* outVarValPts  ,
		double* perfArr,  double* percOfChildSizeFromParent,int &indexOfFirstEmptrySpot, 
		int maxChildrenForOneThisProfile, int potentialChildMaxSize);

	
	void SelectThisProfileIndexesFromAllIndexes(bool* isSelArr, 
	cProfileObject** profileObjectPtrList,  int profileListSize,  int maxThisProfileObjs);
	
	bool IsNewInclusionRuleProfile(cVariableAndValueAndPoints* newVarValList, int size);

	bool CreateChildToThisProfilePerInputVarVarListNew(cProfileObject*& childProfile,//double &parentbasedPerformance, 
		int profileID, cProfileObject* thisProfile, cVariableAndValueAndPoints* varValInclusionArr,  int sizeOfGuidedVarValObj,
		cResearchDataObj* researchDataObj,  cPercentileCalculationModel* rootOddPredictiveModel,
		cPercentileCalculationModel* regPredictiveModell,  cGlobals &globals,  cProfileObject* anchor, bool* isInContext);//

	bool CreateChildToThisProfilePerInputVarVarList(cProfileObject*& childProfile,double &parentbasedPerformance, int profileID, cProfileObject* thisProfile, cVariableAndValue* varValInclusionArr,  int sizeOfGuidedVarValObj,
		cResearchDataObj* researchDataObj,  cPercentileCalculationModel* rootOddPredictiveModel,cPercentileCalculationModel* regPredictiveModell);//
	
	
	
	
	void AdjustRegresionListToSizeAndCreatePercentileObjectForRegre( cPercentileCalculationModel*& regPredictiveModel, 
		int numOFCategoriesForPercLogic, cPercentileCalculationModel* rootOddPredictiveModel,cProfileObject* profile   );

	void UpdateVariableValuesPRevelance(cResearchDataObj* resarchDataObj);

	//	double** personsDataSet,  double* depArr,  int numberOfPatients)	;
//	void AllocateNewProfileAndCompleteProfileModel(cProfileObject*& profile , int profileID,
//	 cVariableAndValue*  varValInclusionArr, int sizeOfVarValPntArr , cResearchDataObj* researchDataObj);

	void ResObjWriteOrRerad( cArrayFlex* arrayFlex, cGlobals &globals);

	void ResObjWriteOrReradMor2( cArrayFlex* arrayFlex , cGlobals &globals);
 
	double  XYZW123(double &meanDelta ,	double &sdDelta,double* updPredArr , double* predArrB4, bool* isIn,  
		cResearchDataObj* researchDataObj, double*	thrArr, double* avgDepArr, int* cntArrBefore, double depAvg, 
		int numOfStretchCategories, cProfileObject* sp, int subGrpIndex);


	double CalculateUpdatedBucketTakingOutOneSpecificItemIandGettingInProbabilityBetweenItem(
		double baseDepBucket, double takingOutSpecificItem, double gettingInProbBetweenItem)
	{ //probably the first, taking out, works fine, need to improve the second function taking in 
		double updatedDep = baseDepBucket;
		
		//old version
	/*	if(takingOutSpecificItem == 0)
		{
				updatedDep = 
					//what avg dep made of the 100 is onl due to 99
					(((baseDepBucket * 100.0 ) / 99.0)* 0.99) +
					//the one left was 0 and the one  in is a probability of 
					 (gettingInProbBetweenItem *0.01 ) ;
			//	updatedDep /= 100.0;
		}
		else
		{
				updatedDep = (((baseDepBucket * 100.0 ) - 1.0) *0.99)+
					           (gettingInProbBetweenItem *0.01 );//getting in
				updatedDep /= 100.0;
		}*/
			
		/*
			baseDepBucket = 0.99 * valOf99 + 0.01*takingOutSpecificItem;
			valOf99 = (baseDepBucket - 0.01*takingOutSpecificItem) / 0.99;
			updatedDep = (0.99 * valOf99) + (0.01 * gettingInProbBetweenItem);
		
		*/
		//new version - check same
		double	valOf99 = (baseDepBucket - 0.01*takingOutSpecificItem) / 0.99;
		updatedDep = (0.99 * valOf99) + (0.01 * gettingInProbBetweenItem);
		

		return updatedDep;
	
	}

	double CalculateUpdatedBucketAddingInOneSpecificItemIandTAkingOutProbalBetweenItem( 
		double baseDepBucket, double addingInSpecificItem, double gettingOurProbBetweenItem)
	{
		double updatedVal  =baseDepBucket;
			//now the clcualtion for added a  0 and getting out a gettingOurProbBetweenItem
			//firsti take out the gettingOurProbBetweenItem
			//gettingOurProbBetweenItem * 0.01 + x * 0.99 = baseDepBucket;
			//x = (baseDepBucket  - gettingOurProbBetweenItem * 0.01) / 0.99
		double avgDepOf99itemsLeft = (baseDepBucket  - gettingOurProbBetweenItem * 0.01) / 0.99;

		updatedVal = (0.99 * avgDepOf99itemsLeft) +(0.01* addingInSpecificItem);

		return updatedVal;
	}

					


	double CalculateUpdatedBucket(	double baseDepBucket, double itemDep)//5 31 23 add a double gettingIn with half wa between base and virtual, to suport
		//the fcat that the new will be a border case and it
	{
		double updatedDep = baseDepBucket;
		if(itemDep == 0)
		{
				updatedDep = 
					//what avg dep made of the 100 is onl due to 99
					(((baseDepBucket * 100.0 ) / 99.0)* 0.99) +
					//the one left was 0 and the one  in is a probability of 
					 (baseDepBucket *0.01 ) ;
			//	updatedDep /= 100.0;
		}
		else
		{
				updatedDep = (((baseDepBucket * 100.0 ) - 1.0) *0.99)+
					           (baseDepBucket *0.01 );//getting in
				updatedDep /= 100.0;
		}
		return updatedDep;
	}



};
