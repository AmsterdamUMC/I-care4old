


class cArrayFlex;
class cResearchObject;
class cVariableSchemaArr;
class cVariableAndValue;
class cVariableAndValueAndPoints;
class cInterventionObject;

////////////////////////////////PROFILE OBJECT//////////////////////////////////////////////////////


class cCalibrationContextObj
{
public:
	int m_numOfGrps;
	double* m_grpsThres;
	double* m_grpsAvgArr;
	int* m_grpPopSize;


	cCalibrationContextObj(int numOfGrps)
	{
		m_numOfGrps = numOfGrps;
		m_grpsThres = new double[m_numOfGrps ];
		m_grpsAvgArr =  new double[m_numOfGrps ];
		m_grpPopSize= new int[m_numOfGrps];
		for(int i = 0 ; i < m_numOfGrps  ; i++)
		{
			m_grpsThres[i] = 0.0;
			m_grpsAvgArr[i] = 0.0;
			m_grpPopSize[i]=0;
		}
	}

	~cCalibrationContextObj()

	{
		delete []m_grpsThres ;
		m_grpsThres =NULL;
		delete[]m_grpsAvgArr;
		m_grpsAvgArr=NULL;
		delete []m_grpPopSize;
		m_grpPopSize=NULL;
	}

	void PrepareCalibrationElements(double* predArr, double* depArr, int size, cGlobals &globals);
	void ConvertToPostRawPredictions(double* predictionArr, double* rawPredArr, int size);


};


class cGlobals;


//Profile Object
class cProfileObject
{
	//global for all profiles
//	char m_dependentVaribleName[100]; //for debug
//	int m_depVarIndex;//for debug
	
	cVariableSchemaArr* m_schemaObjArr; //a copy of the pointer  of the array but without opening any new memoery
//	cVariableSchemaObject* m_schema;//just copy the pointer when intielizing.
//	int m_sizeOfScemaObjectList;

	int m_profileID;//when getting born, we need an ID that can be later used to save in disk and get it back
	//up for keeping patient chidl raltion
	 


	cProfileObject* m_rootProfile;//if this is the root itselc keep the root pointer as NULL
	
//	cProfileObject** m_childProfilePtrArr;
//	int m_sizeOfChildPrfArr;

//	bool m_underThresholdFlag;
	
	//INCLUSION//////
	//pair of varible index and value/value code. it can be more mthan one value of the same varibale in this list
	//a profile with all poulation poplating the profile values has an empty list
	cVariableAndValueAndPoints* m_inclusionRuleList;
	int m_inclusionRuleListSize; //how many inclusion rules are in this profile


	//how many persons participated in this profile analysis,
	//which is only those that passed the inclusion critera
	int m_sizeOfProfilePopulation; 
	int m_sizeOfResearchPopulation;
	double** m_fullPopulation;
	double* m_depArray ;
	int m_numberOfVariables;
	bool* m_isInProfile;
	

	double m_profileDependentAverage; //full profile pattern  
	//double m_profilePerformance; //full profile predictive power score.  needed If no sub groups
//	double m_profilePatientBasedPerformance;
	double m_profileRootBasedPerformance;



//////////////////////////PREDICTION SCALES/////////////////////
	//each variable index and point value represent thepower of a code 1 of the varible. a code 1 defined in the schema
//	int m_numberOFVariblesWithLogisticRegressionValues;
//	cVariableAndValue* m_variablesAndLogRegValues;//better copy the content and not just the pointer
	//4 17 22 TO DO 2//design where the odd ratio live. proably first agument and then have odd ratio for all var all val as part of the 
	//schema. then for each profile, root or any, have another repeated odd ratio calucaiton but there we only keep the signifiacnt odd ratio
	//as part of a predictive model and not all odd ratios can be seen there. also when adjusting the model using any method, adjustment
	//will be on the sub list only. that will be phase 2, first start with odd ratio 
	int m_oddRatioPointsListSize;  //size of this list
	cVariableAndValueAndPoints* m_oddRatioAlgoRates;//a profile has an odd ratio arr using the Profile population. the root has the universe odd rat
	cVariableAndValueAndPoints* m_adjustedPointRates;//then the profile will have an adjsuted version of that
	//for prediction, the point list, and that takes into consideration the local odd algo rates, the universe odd
	//algo rate, and the universe logistic regression. also the division/rate between universe odd alog and adjuted
	//point is directly a way to divide a locl odd ratio. see dedicated function
	 
	double m_scaleMean;
	double m_scaleSD;

	// 

	double* m_subGroupThresholdList; //match a person into a sub group using predictive points
	double* m_subGroupAverageDependent; //sub group pattern
	int* m_subGroupPopulationSize ;//
	double* m_subGroupPerformanceScore; //after testing predictive power and scoring the success 
	double* m_subGrpBestMatchGapAvg;
	double* m_subGroupAdvncPErfScore;
	double* m_meanDeltaProfSub;
	double* m_sdDeltaProfSub;

	int m_numberOfSubGrps; //how many sub groups

	int m_anchorID; 
 
	 
/////////////////////////INTERVENTIONS//////////////////////////////////////
	cInterventionObject* m_interventionObjectList;//
	int m_interventionObjectListSize; //x side



	
		void GetPredictedValuesFromScaleVAlue(double &predicdtion, int &riskGrpIndex, double patientScaleValue);
	
	
	 

	double GetPAtientZscore( double scaleSum)
	{
		double z = 0.0;
		if(m_scaleSD > 0.0)
		{
			z = (scaleSum - m_scaleMean) / m_scaleSD;
		}	
		return z;
	}

	 

	void ConvertToSymetricOddRatio(double &oddOrign ,  cGlobals &globals );
	
	




public:

	
	cProfileObject( cResearchObject* resObj, int profileID, cProfileObject* rootProfile ,
		cVariableAndValueAndPoints* inclusionRuleSet , int inclusionRuleSetSize,
		cResearchDataObj* researchDataObj, int anchorID, bool* isInContext);		
	~cProfileObject();

	///////////////////GET FUNCTIONS ////////////////////////////////////////
	double* GetDependentArray()	{	return m_depArray;	}
	double GetProfileDepAverage() { return m_profileDependentAverage; }
	int GetOddRatioListSize()	{		return m_oddRatioPointsListSize;  	}
	cVariableAndValueAndPoints* GetOddRatioList()	{		return m_oddRatioAlgoRates;}
	//a profile has an odd ratio arr using the Profile population. the root has the universe odd rat
	int GetSizeOfAllPopulation(){	return m_sizeOfResearchPopulation ;	}
	bool* GetIsInProfileArr()	{		return m_isInProfile ;	}
	double** GetTwoDimPopulationArr()	{		return m_fullPopulation;	}
	cVariableAndValueAndPoints* GetAdjustedOddRateArr()	{	return m_adjustedPointRates;	}
	int GetVarValPointsOddMOdelSize()	{	return  m_oddRatioPointsListSize;	}
	cProfileObject* GetRootProfile()
	{
		if(m_rootProfile != NULL)
		{
			return m_rootProfile;
		}
		else
		{
			return this;
		}
	}
	void GetPatientScaleValue(  double &patientScaleValue, double *augmentedPatientArr);
	void GetPredictedValuesFromScaleVAlueWithFineTuning(double &predicdtion, int &riskGrpIndex, 
		double patientScaleValue,  bool isWithFineTuning);
	
 
	void IncrementPrfieIDandAnchorID(int gap)
	{
		m_profileID += gap;
		m_anchorID += gap;
	}

	void SetRootProfile(cProfileObject* root) {  m_rootProfile = root; }
	cVariableAndValueAndPoints* GetInclusionRuleList(){return m_inclusionRuleList;}
	int GetInclusionRuleListSize() { return m_inclusionRuleListSize; }
//	cProfileObject** GetChildProfilesArray(){ return m_childProfilePtrArr;}
 	double GetRootBasedPerformace() { return m_profileRootBasedPerformance;}
	int* GetSubBucketCntArr() { return m_subGroupPopulationSize;}
	
	double* GetThresholdArr() { return m_subGroupThresholdList;}
	double* GetSubGroupAverageDependentArr(){		return m_subGroupAverageDependent;	}
	int GetNumberOfSubGroups(){ return m_numberOfSubGrps;}
	static double CalclaterSumAdjusteddPnts(	double* personArr, 
		int numberOfVariables, cVariableAndValueAndPoints* pointRates, int size);

	bool IsAnchor()
	{
		if(m_rootProfile != NULL ) //that means this is not the root 
		{
			if( m_profileID == m_anchorID )
			{
				//this is the anchor profile
				return true;
			}
		}
		return false;
	}

	void CopyAdvPerfArrOut(double* advPerfArr )
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			advPerfArr[i] = m_subGroupAdvncPErfScore[i];
		}
	}


	void CopyAdvPerfArrIn(double* advPerfArr )
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			m_subGroupAdvncPErfScore[i] = advPerfArr[i] ;
		}
	}

	bool AreAllBucketsZero()
	{
		bool ret= true;
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			if(m_subGroupAdvncPErfScore[i] != 0.0)
			{
				ret=false;
			}
		}
		return ret;
	}

	bool AreAllBucketsNonZero()
	{
		bool ret= true;
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			if(m_subGroupAdvncPErfScore[i] == 0.0)
			{
				ret=false;
			}
		}
		return ret;
	}




	void SmoothAdvancedPerfWeights()
	{
		int sdfg=0;//8 13 23

	}


	bool IsIndexMostExtreme(int grpIndex, double anchorvAluee)
	{
		if((grpIndex == 0) || (grpIndex == (m_numberOfSubGrps-1) ))
		{
			double valLect = m_subGroupAverageDependent[0];
			double leftGap = cVarianceCalc::Abs( valLect - anchorvAluee);
			
			double valRight = m_subGroupAverageDependent[(m_numberOfSubGrps-1)];
			double rightGap = cVarianceCalc::Abs(valRight   - anchorvAluee);
			if(rightGap > leftGap)
			{
				if(grpIndex == (m_numberOfSubGrps-1))
				{
					return true;
				}
			}
			else
			{
				if(grpIndex == 0)
				{
					return true;
				}
			}
			return false;
			
		}
	}

	static bool IsPredictionExtreme(double predGeneral, double anchorvAluee, double* tierStrucrue, int numOfTiers, double  preditionProfileP)
	{
		double currentPredShift = cVarianceCalc::Abs( predGeneral - anchorvAluee);
		int currentTier = 2;
		if(currentPredShift > tierStrucrue[1])
		{
			currentTier = 1;
		}
		if(currentPredShift > tierStrucrue[0])
		{
			currentTier = 0;
		}
		double predShift  =   cVarianceCalc::Abs( preditionProfileP - anchorvAluee);
		int predTier = 2;
		if(predShift >= tierStrucrue[1])
		{
			predTier = 1;
		}
		if(predShift >= tierStrucrue[0])
		{
			predTier = 0;
		}

		if(predTier <= currentTier)
		{
			return true;
		}

		return false;
	}
	

	bool IsPArientMustBeProfile(double &depAvg,double &sdOut, cVariableAndValue* guidedInclusionRuleList, 
		int guidedlistSize,  cResearchObject* resObj)
	{
		bool ret = false;
		depAvg=0.0;

		for(int i = 0 ; i < m_inclusionRuleListSize ; i++)
		{
			cVariableAndValueAndPoints obj = m_inclusionRuleList[i];
			for(int ii = 0 ; ii <  guidedlistSize ; ii++)
			{
				if((obj.m_variableIndex == guidedInclusionRuleList[ii].m_variableIndex )&&
					(obj.m_value == guidedInclusionRuleList[ii].m_value))
				{
					double val = 0.0;
					double sd=0.0;
					if(resObj->IsGuidedParentExsist(val, sd,guidedInclusionRuleList[ii]))
					{
						depAvg = val;
						sdOut = sd;
						return true;
					}
				}
			}

		}
		return false;//6 9 23 ****
	}

	int GetProfileID(){ return m_profileID;}
	int GetAnchorID() { return m_anchorID;}

	void GetDepAverageOfMustBeParentProfile(
		double &avgAnchor, double &sdAnchor,
		cVariableAndValue* guidedInclusionRuleList,  int listSize,
		cResearchObject* researcObj		)
	{
		avgAnchor = GetProfileDepAverage();
		sdAnchor= GEtProfileSDofBucket();
		if(m_rootProfile!=NULL)
		{
			avgAnchor = m_rootProfile->GetProfileDepAverage();
			sdAnchor= m_rootProfile->GEtProfileSDofBucket();
		}
		double tempDepAvg = 0.0;
		double sd = 0.0;
		if( IsPArientMustBeProfile(tempDepAvg,sd,  guidedInclusionRuleList,  listSize, researcObj))
		{
			avgAnchor = tempDepAvg;
			sdAnchor = sd;
		}
		
	}

	bool  IsProfSubRelatedToHigherPerfWeight(  int  subIndex, cProfileObject** arr, int size  );

	void FillAdvancedPerfAllSubGrps(double wgh)
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			m_subGroupAdvncPErfScore[i]=wgh;
		}	
	}

	void IncreaseAdvPerfAllSubGrps(double multipler)
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			m_subGroupAdvncPErfScore[i] *= multipler ;
		}	
	}
	void IncreaseAdvPerfAllSubGrps(double multipler, int index)
	{
		m_subGroupAdvncPErfScore[index] *= multipler ;
	}

	double* GetAvgPopGapWhenBestMatch() { return m_subGrpBestMatchGapAvg;}
	double* GetSubGrpPerformanceAdvancedArray() { return m_subGroupAdvncPErfScore ; }
	double* GetSubGrpDeltaFromStrMean(){ return m_meanDeltaProfSub;}// 
	double* GetSubGrpDeltaFromStrSD(){ return m_sdDeltaProfSub;}
		
	static bool IsRightRuleSetChildOfLeft(
		cVariableAndValueAndPoints*	ruleSetI, int ruleSetSizeI, 
		cVariableAndValueAndPoints*	ruleSetII,int ruleSetSizeII);
	
	void UpdateAdvancePerformance(double stretchGap)
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			m_subGroupAdvncPErfScore[i] = stretchGap;
		}
	}

	double GetProfileCenterAdvancedPerformance()
	{
		double avgPEr = 0.0;
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			avgPEr += m_subGroupAdvncPErfScore[i] ;
		}
		avgPEr /= m_numberOfSubGrps;
		return avgPEr;
	}

	
	void UpdatePerformanceArrays( cScoreGrpArr &obj  )
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			m_subGroupAdvncPErfScore[i] = obj.m_scoreArr[i] ;
		}
	}

	void CopyOutAdvPerfScores( cScoreGrpArr &obj  )
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			 obj.m_scoreArr[i]  =m_subGroupAdvncPErfScore[i] ;
		}
	}

	void UpdatePerformanceArrays(double stretchGap)
	{
		for(int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			m_subGroupAdvncPErfScore[i] = stretchGap;
		//	m_subGroupPerformanceScore[i] = stretchGap;
		}
	}


	static int GetSubGrpIndex(double sum,double* threshArr,  int numOfSubGrps)
	{
		for(int x = 0 ; x < numOfSubGrps; x++) //how many sub groups
		{
			if(sum <= threshArr[x] )
			{
				return x;
			}
		}
		return numOfSubGrps-1;
///////
	}

	
	void DeleteIsInProfile()
	{
		if(m_isInProfile != NULL)
		{
			delete [] m_isInProfile;
			m_isInProfile = NULL;
		}
	}

	void SetProfileID(int id)
	{
		m_profileID = id;
	}
	void SetAnchorID(int id)
	{
		m_anchorID = id;
	}
	////////////////////////////////////////////////////

	
	double GEtProfileSDofBucket();
		//9 26 22 ***
	static void FillPntArrFromAdjustedModel(double* pntArr, double** testData, bool* isIn, int numOfTestItems,
							int numOfVars,cVariableAndValueAndPoints* pointRatesArr, int pointRateArrSize);

	static void CalculateThresholds(double* threshArr, int numOfSubGrps, double* pntArr, bool* isIn,  int numOfTestItems);

	bool IsVarValIncludedInInclusionRuleSet(int var, double val)
	{
		for(int i = 0 ; i < m_inclusionRuleListSize ; i++)
		{
			if((m_inclusionRuleList[i].m_variableIndex == var )  && ( m_inclusionRuleList[i].m_value == val ) )
			{
				return true;
			}
		}
		return false;
	}
	//5 31 23 ***
	void CalclateRatioDepDeltaPerPredScoreDelta(double &ratioDepPerPred,
		double* predArr, int numOfElements)
	{
		double sumPnt =  CalclaterSumAdjusteddPnts(predArr,
						numOfElements,	GetAdjustedOddRateArr(),GetOddRatioListSize()		);
		int subGrpIndex = GetSubGrpIndex( sumPnt,  GetThresholdArr(), m_numberOfSubGrps ) ;
		// depAvgDelta / prediDelta , based on up to 2 buckets left and right if exist

		 
	}

	static void CreateAvgDepSubGrps(int* grpIndexArr, double* subGrpsDepAvgSet, double* threshArr,int* subGroupPopulationSize, double &profileAvgDep,
						int numOfSubGrps, double* pntArr,double* depArr, bool* isIn, int numOfTestItems, cGlobals &globals);

	void CollectAllVarValOptionswithNonZeroOdd( 
		cVariableAndValueAndPoints*& childPotetialInclusionArr,
		int &childInclusionArrSize, InputVariablesPackageForResearchObj* metaReseacObj,  cGlobals &globals);

	//12  2 22 to complete with regression input
	bool IsVarValGoodForChildOPening(cVariableAndValueAndPoints &obj,
		InputVariablesPackageForResearchObj* metaResearcObj,  cGlobals &globals);


	
	double GetProfileMean()
	{
		if(m_profileDependentAverage == 0.0)
		{
			double mean = 0.0;
			int cnt = 0;
			for(int i = 0 ; i < m_sizeOfResearchPopulation ; i++)
			{
				if(m_isInProfile == NULL  || m_isInProfile[i])
				{
					mean += m_depArray[i];
					cnt++;
				}
			
			}
			if(cnt > 0)
			{
				mean /= cnt;
			}
			m_profileDependentAverage =  mean;
		}
		return m_profileDependentAverage;
	}

	
	void CopyPerformanceArray(double* performanceArr)
	{
		for(int x= 0 ; x< m_numberOfSubGrps ; x++)
		{
			m_subGroupPerformanceScore[x] = performanceArr[x];
		}
	}

	/*
	12 2 22 addition for intervetnion
	given a new API with :  int interventionModifierIndex 
	given we get an input intervenetion index of 2 , means a field positin 2 is not a predictive 
	but an interventin, and out of more than one potential field from the patinet array, only this
	call will onl triger one intervenion at a time and given 2 we go for the 2 interventino postion
	then, the prediction will get two additional conditionas of with or without 
	*/ 

	//PREDICTION API 
	//5 31 23 - regarding isWithFineTuning, chek and play with what is better for real time, with or without fine tuing.
	//for processing evaluating performance time, keep with non fine tuning 
	void PredictionElementsNEW( double &prediction , double &predictionWithInterv, double &preditionWitoutInterv,
		double &performanceReg , double &performanceAdv,
		 int &profileID,  int &subGrpIndex,
		double* ptArr, int numOfVars, bool isAdvancedPerfGetbEstMatch, 
		int interventionFieldIndexToModify, cGlobals &globals, bool isWithFineTuning)
	{
		double scaleSum = 0.0;
		GetPatientScaleValue( scaleSum, ptArr);
		subGrpIndex = -1;
		profileID = m_profileID;
	//	GetPredictedValuesFromScaleVAlue 
		GetPredictedValuesFromScaleVAlueWithFineTuning	(prediction, subGrpIndex, scaleSum ,isWithFineTuning);
		performanceReg = GetSubGroupAbsAccomultedPerformance(subGrpIndex,   false, globals);
		performanceAdv = GetSubGroupAbsAccomultedPerformance(subGrpIndex,   true, globals);
		predictionWithInterv = prediction;
		preditionWitoutInterv = prediction;

		if(interventionFieldIndexToModify >=0)
		{
			for(int x = 0 ; x < m_interventionObjectListSize ; x++)
			{
				if(m_interventionObjectList[x].m_interventionVariableIndex == interventionFieldIndexToModify)
				{
/* 
PA - average predcition 
PS - predcition stretch is the gap between predtion with and without
WW - weight with
WWO - eight without

Pw - predction withi
Pwo - predion witout

Pw *  WW + Pwo * WWO = PA
PS = Pw  - Pwo

Pw = PS + Pwo
(PS + Pwo) * WW + Pwo * WWO = PA
PS*WW + Pwo * WW + Pwo * WWO = PA
Pwo (WW+WWO) = PA - (PS*WW)

Pwo   = (PA - PS*WW )  /  (WW+WWO);
Pw = Pwo + PS ;  

*/
					//this can be foro exmale a 20% effect between yes and no intervention. 
					//just need to know if the prediction with assuming mostly with or without
					double PS = m_interventionObjectList[x].m_interventionAdjustArr[subGrpIndex];
					double PA = prediction;
 
					double WW = m_interventionObjectList[x].m_sizeOFProfileIntervePop / 
						m_interventionObjectList[x].m_sizeOfProfilePop ;
					double WWO = 1.0 - WW;
					preditionWitoutInterv   = (PA - PS*WW )  /  (WW+WWO);
					predictionWithInterv = preditionWitoutInterv + PS ;  
			 
				}
			}
		}
	}

	void SetAdjustedPointRateArray(  double** valueWeights, int* numOfVarValues, bool* isPredictive, int size );

	int GetPatientIndexFromPatinetData(double* ptArr, bool isWithFineTuning)
	{
		double scaleSum = 0.0;
		GetPatientScaleValue( scaleSum, ptArr);
		int subGrpIndex=-1;
		double prediction=0.0;
		GetPredictedValuesFromScaleVAlueWithFineTuning	(prediction, subGrpIndex, scaleSum ,isWithFineTuning);
		return subGrpIndex;
	}
	
double GetVarValuePErInputIndex(int var, int valIndex);
void updateArrWithValue(double* valArr, int &currentCnt, double newValue, int naxNumOfVals);

	
int GetNumberOfModelVarValues(int var );

	void SetAdjustedPointRateArrayAndSetThresholdsAndBuckets( double** valueWeights,double** values,  int* numOfVarValues, bool* isPredictive,
		 cGlobals &globals,	double** fullPopulation, double* depArray,	bool* isInProfile ,	int sizeOfResearchPopulation);
	
	void ReplacePredictiveWightsModel(   cProfileObject* profile,   cResearchDataObj* researchDataObj,bool* isPredictive,
														cGlobals* globals, bool* isInProf,int count);
	
	void SetIsPreddictiveBasedOnSizeAndPoints(bool* isPredictive,int P );
	
	
	bool VarValIsFound(double &foundWeight, double* valueWeights, double* values,	int numOfVarValues, double valIn );

	void CoptProfilePopPointers(double** testPop  ,double* depArr)
	{
		int index=0;
		for(int i = 0 ; i < m_sizeOfResearchPopulation ; i++)\
		{
			if(m_isInProfile == NULL  || m_isInProfile[i] )
			{
				depArr[index] = m_depArray[i];
				testPop[index] = m_fullPopulation[i];
				index++;
			}
		}	
	}

	
	//4 17 22 TO DO 2 and see that we have our real time covered with this new plan
	void  GetBestMatchProfile(/* proifle, patient */);//of real time, not of the one that calculated the deept, the real time 
		//will be based on the depp performance and not on this one
	int GetProfilePopulationSize() { return m_sizeOfProfilePopulation;}
	double CalcualteSimplePerformanceCompareToOtherModel ( cProfileObject* other);

	void GetSubGrouopAvgDepArr( double*& avgDepArr, int &numberOfSubGrps,  double &mean, double &sd);

	//4 17 22 TO DO 2 all checks around root, parent, andn deep performance testing and strategy
	double GetProfilePerformance(int riskGrpIndex)
	{
		if(m_subGroupPerformanceScore != NULL)
		{
			return m_subGroupPerformanceScore[riskGrpIndex];
		}
		return 0.0;	 
	}
	double GetProfileAdvancedPerformance(int riskGrpIndex)
	{
		if(m_subGroupAdvncPErfScore != NULL)
		{
			return m_subGroupAdvncPErfScore[riskGrpIndex];
		}
		return 0.0;	 
	}
	void SetProfileAdvancedPerformance(int riskGrpIndex, double wgh )
	{
		if(m_subGroupAdvncPErfScore != NULL)
		{
			m_subGroupAdvncPErfScore[riskGrpIndex]=wgh;
		}	
	}
	void AddToAdvancedPerfWeight(double addedWeight, int s)
	{
		m_subGroupAdvncPErfScore[s]+=addedWeight;
	}

	
	void ClearAdvancedPerformance(double val)
	{
		for(int s=0; s < m_numberOfSubGrps ; s++)
		{
			m_subGroupAdvncPErfScore[s]=val;
		}
	}

	void  SetProfilesAdvancedPerfScores(double val)
	{
		for(int s=0; s < m_numberOfSubGrps ; s++)
		{
			m_subGroupAdvncPErfScore[s]=val;
		}
	}

	void SetProfileAdvancedPerformance(cScoreGrpArr &scoresGrp)
	{
		for(int s=0; s < m_numberOfSubGrps ; s++)
		{
			m_subGroupAdvncPErfScore[s]=scoresGrp.m_scoreArr[s];
		}
	}

	void CopyOutadvancedPerfScores(cScoreGrpArr &scoresGrp)
	{
		for(int s=0; s < m_numberOfSubGrps ; s++)
		{
			scoresGrp.m_scoreArr[s] = m_subGroupAdvncPErfScore[s];
		}
	}

	void CopyInAdvancedPerfScores(cScoreGrpArr &scoresGrp)
	{
		for(int s=0; s < m_numberOfSubGrps ; s++)
		{
			m_subGroupAdvncPErfScore[s] = scoresGrp.m_scoreArr[s];
		}
	}

	void ZeroAdvancedPerfWeights()
	{
		for(int s=0; s < m_numberOfSubGrps ; s++)
		{
			m_subGroupAdvncPErfScore[s] = 0.0;
		}
	}
	 
	void Prepare3TierValueAbsoloteMode(double* tierStrucrue)
	{
		tierStrucrue[0]=0.0;
		tierStrucrue[1]=0.0;
		tierStrucrue[2]=0.0;
		for(int i=0; i < m_numberOfSubGrps ; i++)
		{
			if(i== 0) 
			{
				tierStrucrue[0] = cVarianceCalc::Max(tierStrucrue[0], cVarianceCalc::Abs( m_subGroupAverageDependent[i]-m_profileDependentAverage));
			}	
			else if(i== (m_numberOfSubGrps-1)) 
			{
				tierStrucrue[0] = cVarianceCalc::Max(tierStrucrue[0], cVarianceCalc::Abs( m_subGroupAverageDependent[i]-m_profileDependentAverage));
			}	
			else if(i == 1)
			{
				tierStrucrue[1] = cVarianceCalc::Max(tierStrucrue[1], cVarianceCalc::Abs( m_subGroupAverageDependent[i]-m_profileDependentAverage));
			}
			else if(i == (m_numberOfSubGrps-2))
			{
				tierStrucrue[1] = cVarianceCalc::Max(tierStrucrue[1], cVarianceCalc::Abs( m_subGroupAverageDependent[i]-m_profileDependentAverage));
			}
			else
			{
				int sdg  = 0 ;
			}			
		}
	}


	int GetSubBucketCntArr(int riskGrpIndex)
	{
		if(m_subGroupPopulationSize != NULL)
		{
			return m_subGroupPopulationSize[riskGrpIndex];
		}
		return 0;
	}

//	void SetRootBasedPerformanceScore( double comparedUniversePerformance) {m_profileRootBasedPerformance = comparedUniversePerformance;}
	//m_profileRootBasedPerformance=comparedUniversePerformance;

	/*void SetChildPtrArr(cProfileObject ** childArr, int size)
	{
		m_childProfilePtrArr=childArr;
		m_sizeOfChildPrfArr=size;
	}
	void SetProfileAsFinalTerminal() { m_underThresholdFlag = true;}
	bool IsProfileFinalTerminal() { return m_underThresholdFlag;}
	*/
	/*
	double GetPointss(cVariableAndValue &temp)
	{
		for(int x = 0 ; x < m_oddRatioPointsListSize ; x++)
		{
			if(	  m_oddRatioAlgoRates[x].m_variableIndex == temp.m_variableIndex) &&(m_oddRatioAlgoRates[x].m_value == temp.m_value))
			{
				return m_oddRatioAlgoRates[x].m_points;
			}
		}
		return 0.0;
	}
 */
	
	bool IsSameInclusionList( cVariableAndValueAndPoints* inclusionSet,	int sizeOfInclusionSet);

	bool IsInclusionsIncludedInProfileRules(cVariableAndValueAndPoints* inclusionSet,	int sizeOfInclusionSe);

	bool IsVarValIncluded(cVariableAndValueAndPoints &varVal);

	
	bool IsPatientIncluded(double* patientArr);

	//void CalcualteParentBasedPerformance (double &simplePerfOfChildComparedToParent, cProfileObject* patienetProfile);


double GetSumOfAbsInclusionRulePoints();//each element in the inclusin list has the algo odd ratio points turned

double GetSubGroupAbsAccomultedPerformance(int index, bool isAdvancedPerfGetbEstMatch, cGlobals &globals);

void CalcualteParentAndUniverseBasedPerformance (
				double &comparedParentSimplePerformance,
				double &comparedUniversePerformance, cProfileObject* profile);

	double CalculaterRawOdd(double grpDepVal, double profileDepVal);

	// m_subGroupAdvncPErfScore[i]=0.0;
	void SetPerformanceToDefault( double val )
	{
		for(int i = 0 ; i < m_numberOfSubGrps;i++)
		{
			m_subGroupAdvncPErfScore[i]=val;
		}
	}
//a profile object will call this function, as a universe, and as a chiod to take the internal odd ratio
//output, after profile internal proesssing, and the root odd ratio and the root logisti iregresion and adapt
//a logistic regrssion for the profile. 
	void SetPerformanceToDefault( cGlobals &globals )
	{
		if((m_subGroupPerformanceScore ==NULL) && (m_numberOfSubGrps > 0))
		{
			m_subGroupPerformanceScore = new double[m_numberOfSubGrps];
		}
		if((m_subGrpBestMatchGapAvg == NULL) &&  (m_numberOfSubGrps > 0))
		{
			m_subGrpBestMatchGapAvg= new double[m_numberOfSubGrps];
		}
		if((m_subGroupAdvncPErfScore ==NULL) && (m_numberOfSubGrps > 0))
		{
			m_subGroupAdvncPErfScore = new double[m_numberOfSubGrps];
		}
		if((m_meanDeltaProfSub )==NULL &&(m_numberOfSubGrps > 0))
		{
			m_meanDeltaProfSub  = new double[m_numberOfSubGrps];
			m_sdDeltaProfSub = new double[m_numberOfSubGrps];
		}
		// m_subGroupAdvncPErfScore[i]=0.0;
		for(int i = 0 ; i < m_numberOfSubGrps;i++)
		{
			m_subGroupPerformanceScore[i] = 0.0;
			m_meanDeltaProfSub[i]=0.0;
			m_sdDeltaProfSub[i]=0.0;
			m_subGroupAdvncPErfScore[i]=0.0;//the advanced sub gruop performane will be evalated in the end or after getting profiles
			m_subGrpBestMatchGapAvg[i]=0.0;
			//up from disk later. it is then in get best match when looking for performacne score to look first if the advanced performance
			//is ready. a reminder -  a perf scor simple is sub of abs odd ratio across the profile inclusion rule set, and then added the sub
			//group odd ratio away from the perofile center. a perf scor advanced is how much a profile sub group is useful so that each time it
			//participates in a patient prediction that event is being stored twice, once with that sub group support and once without, we get 
			//eventually one perf test with each profile sub set has sample of inclused patients and their two predictions and one actual. 
			//with a list of n cases ofo test patients that are included in a proflie and in its sub gruop, and for each of the n we got 
			//two predictions and one actualy so we can make a competition by which two pairs of pred andn actual make better seperation
			//into 5 risk groups
		}
		m_profileRootBasedPerformance  = GetSumOfAbsInclusionRulePoints();//each element in the inclusin list has the algo odd ratio points turned
		//into 
		double sumWghts = 0.0;
		double avg = 0.0;
		for(int i = 0 ; i < m_numberOfSubGrps;i++)
		{//12  2 22 copy the cntArr  from the fuction that calcualteds m_subGroupAverageDependent to m_subGroupPopulationSize once ready
			avg += (m_subGroupPopulationSize[i]*m_subGroupAverageDependent[i]);
			sumWghts += m_subGroupPopulationSize[i];
		}
		avg /= sumWghts;
		for(int i = 0 ; i < m_numberOfSubGrps;i++)
		{
			double rawOdd = CalculaterRawOdd( m_subGroupAverageDependent[i], avg);
			ConvertToSymetricOddRatio(rawOdd   , globals );
			m_subGroupPerformanceScore[i] = rawOdd;//
		}
	}


	bool IsInclusionRuleFound( cVariableAndValueAndPoints &obj)
	{
		for(int i = 0 ; i < m_inclusionRuleListSize;i++)
		{
			if(  obj.m_variableIndex == m_inclusionRuleList[i].m_variableIndex && obj.m_value == m_inclusionRuleList[i].m_value )
			{
				return true;
			}
		}
		return false;
	}

	//returns if this input rule set is same as the one the prof holds
	static bool  IsSameInclusionRules( cProfileObject* prof, cVariableAndValueAndPoints* inclusionRuleSet, int size)
	{
		if(prof->m_inclusionRuleListSize != size)
		{
			return false;//if the size is not the same they cant be the same
		}
		for(int i = 0 ; i < size;i++)
		{
			//do we have our first rule in any of the  rules that prof holds? if not, a reason to return false
			if(! prof->IsInclusionRuleFound(inclusionRuleSet[i]))
												//prof1->m_inclusionRuleList[i]))
			{
				return false;
			}
		}
		return true;//want to seee that we get here
	
	}
	



	static bool IsSameInclusionRules(  cProfileObject* prof1, cProfileObject* prof2)
	{
		if(prof1->m_inclusionRuleListSize != prof2->m_inclusionRuleListSize)
		{
			return false;
		}
		for(int i = 0 ; i < prof1->m_inclusionRuleListSize;i++)
		{
			if(! prof2->IsInclusionRuleFound(prof1->m_inclusionRuleList[i]))
			{
				return false;
			}
		}
		return true;
	}

	static bool IsVarValInPatient(double* predArr, int numberOfVariables, cVariableAndValue varVal)
	{
		int var = varVal.m_variableIndex;
	//	int personVal = predArr[var];
		if(varVal.m_value == predArr[var])
		{
			return true;
		}	
		return false;
	}

	
	void CalcualteDeepPerformanceValues();

	void CompileAdjustedLocalOddRatioPointsWithLogReg( /*adjustedOddRAtioList*/ );
										  //originalOddRatioList, rootLogistRegression)
	

	//will be calld by a profile, root or any, to follow th odd ratio calcualteion wth an adajustment
	void CompoileAdjustedLocalOddRatioPoints( );


	//9 26 22 
	//adjuste the model creatin to be genric and use this also here
	static void CreatePErcetileGrpsFromInputDataItems(double* subGrpsDepAvgSet,
		double* threshArr, int* subGroupPopulationSize, double  &profileAvgDep,
		double** testData, double* depArr,	bool* isIn, int numOfTestItems, int numOfVariables, 
		int numOfSubGrps, cVariableAndValueAndPoints* pointRatesArr, int pointRateArrSize,  cGlobals &globals);
	
	void SetProfilePopoulationFromResearchPopulation(bool* isInContext);

//	static void SetGrpPopoulation(	bool* isInGrpOut,  int &sizeOfProfilePopulation, double** fullPopulation,	
	//	int sizeOfResearchPopulation, 	int numberOfVariables,cVariableAndValueAndPoints* inclusionRuleList,	
		//					int inclusionRuleListSize,	bool* isInContext);

	static void SetProfilePopoulationFromResearchPopulationStatic(bool* isInContext);
	//4 17 22 TO DO 2 //hard coded schema
	//use the scehma to select only potential var val alternative that have a significant odd ratio, higher or lower.
	//the schema is an input to the profile object constructure. we can look at the predictive model tht was built and see that the 
	//child candidates are also having certain points for debug. 
	//check for a var/val alternative that it is not already in the parient inclusion list. choose the alternative
	//for the child profile added inclusion, only if a var val is not already in the parient inclusion path
	
	//4 17 22 TO DO 2 new comment- make sure we dont choose candidates to be
	//1-is of a variable that has a predicitive false, or 
	//2-of a variable that has a be replaced or 
	//3-with value that has odd ratio that is not significant. or 
	//4 witih valrue with too less prevelance or
	//5-the combinatio nof var val is already in the pareint incusion list
	//6 - not in the top MAX allowed alternatives in terms of odd ratio signficiance. 
	//  odd ratio based on parient model - see that we first complete the model, for here original odd ratio is better
	void CollectNextVarValCandidates(cVariableAndValue *&proposedChildList, int &actualSize, int maxSize,
		cVariableAndValueAndPoints* parentInclusionList, int parentInclusionListSize)
	{
	//algorithm: 
		//assumption - the prflie patient for which we are adding child list has its predictive model built
		//note:  using the odd ratio here can be from the profile so that is after model is built
		//first collect all restrictions and prepare a sub set of candidates and count
		//if after reoving 1-5 if there are still more than max than for 6 we sort and get best of odd ratio 
		//for 4, need to look at the profile/this/parent population count and the prevelance on the shema to 
		//then comapre with a min profile size and see if we even want to bother
	}
		
	 
	void PrfObjPrepareArraysToOrFromDisc(cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals);

	void PrfObjPrepareArraysToOrFromDisc2(	
		cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals, 
		int leadingSpacesNum,  int profileIndex );
	
	int ConvertOddToOddGrp( double* threArr, int numOfGrps, double oddVal  );

	void PrepareThresholdsAndRiskGrpParameters(double* scaleArr);
	 
	void 	CalculateOddRatio( double &oddRAtio , double &popPercent, int j, double value);//check
	//void CrerateAdjustedPoints();
//	void Prepar ePredictiveModel();//size of profile populatio will be calcualted here

	
	void SetAdjustedOddModel(cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel* regPredictiveModel);//

	void PrepareModel( cGlobals &globals );//cPredictiveModel* rootOddPredictiveModel , cPredictiveModel* regPredictiveModel); 
	void CompleteModel( cGlobals &globals );
	void PrepareOddRatioStructure( cGlobals &globals );//cPredictiveModel* rootOddModel, cPredictiveModel* regWghtsModel);


	void AdjustModelBasedOnInputLearningPopulation(double** ptnVarArr, double* depArr,int numOfPtns);
	///////////////////////
	
	void CrerateAdjustedPoints(double* threArr, int numOfGrps,
			cVariableAndValueAndPoints* tempVarValPontArr,	cVariableAndValueAndPoints*  tempVarValPercetArr, int size);

	//12 2 22 add theporpensize matihng list 
	void SetInterventionMembers(bool* isIntervention, int* indexOfPropIntervention, int numOfVars)//, cResearchDataObj* researchDataObj)
	{
		m_interventionObjectListSize=0;
		for(int x = 0 ; x < numOfVars ; x++)
		{
			if(isIntervention[x])
			{
				m_interventionObjectListSize++;		
			}
		}

		//12 2 22 
		//cInterventionObject* m_interventionObjectList;//
		m_interventionObjectList=NULL;
		int lastNotTested = 0;
		int index = 0;
		if(m_interventionObjectListSize > 0)
		{
			m_interventionObjectList = new cInterventionObject[m_interventionObjectListSize];
			for(int i = 0 ; i < m_interventionObjectListSize ; i++)
			{
				bool isFound = false;
				for(int ii = lastNotTested ; ii < numOfVars && (!isFound) ; ii++)
				{
					if(isIntervention[ii])
					{
					 	//12 2 22 add input the inof of prpo like th eone for is intervention. have isPropensiyyInterevenion	
						for(int iii = 0 ; iii < numOfVars ; iii++)
						{
							if(indexOfPropIntervention[iii] == ii)
							{
								m_interventionObjectList[i].SetIndexOfInter(ii,iii);
							}
						}
						//	//researchDataObj->m_twoDimArray, researchDataObj->m_depArr, patnarrSize, researchDataObj->m_sizeOfItem

						m_interventionObjectList[i].FillInterventionMemebers(m_fullPopulation,m_depArray,
							m_isInProfile, m_sizeOfResearchPopulation, this, m_numberOfSubGrps );//add the input and calc what are the memebres
						isFound = true;
						lastNotTested = ii+1;
					}				
				}
			}
		}
	}


};
 




class cStringAndIntDupCheck
{
public:
	unsigned int m_size;
	bool* m_arr;

	cStringAndIntDupCheck(); 
	~cStringAndIntDupCheck();
	bool IsExist(char* str, unsigned int num);
	void SetExist(char* str, unsigned int num);
};
