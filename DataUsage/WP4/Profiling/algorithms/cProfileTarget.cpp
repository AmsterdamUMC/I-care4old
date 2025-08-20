#include "cSimilarityFormula.h"
#include "cProfileTarget.h"
#include "TargetSort.h"
#include "cRgression.h" 
#include<string.h>
#include <math.h>
#include "math.h"
#include <stdlib.h>




//////////////////////////////////////////////////


cProfileObject::cProfileObject( cResearchObject* resObj, int profileID, 
		cProfileObject* rootProfile, cVariableAndValueAndPoints* inclusionRuleSet , int inclusionRuleSetSize,
						cResearchDataObj* dataObj ,  int anchorID, bool* isInContext)	
{
	m_anchorID = anchorID;
	m_schemaObjArr = resObj->GetSchema();//just copy the pointer when intielizing.
	m_profileID = profileID;//when getting born, we need an ID that can be later used to save in disk and get it back
//up for keeping patient chidl raltion

	m_rootProfile = rootProfile;//if this is the root itselc keep the root pointer as NULL//
//	m_childProfilePtrArr = NULL;
//	m_sizeOfChildPrfArr=0;

//	m_underThresholdFlag = false;

	//INCLUSION//////
	//pair of varible index and value/value code. it can be more mthan one value of the same varibale in this list
	//a profile with all poulation poplating the profile values has an empty list
	//	m_inclusionRuleList = inclusionRuleSet;
	m_inclusionRuleListSize = inclusionRuleSetSize ; //how many inclusion rules are in this profile
	m_inclusionRuleList=NULL;
	if(m_inclusionRuleListSize > 0)
	{
		m_inclusionRuleList = new cVariableAndValueAndPoints[m_inclusionRuleListSize];
		{
			for(int i = 0 ; i < m_inclusionRuleListSize ; i++)
			{
				m_inclusionRuleList[i]= inclusionRuleSet[i];//inclusionRuleSetSize
			}
		}
	}

	//sum of the objects input will be given *such as whicih are the values to annalysie (and some will be calcualted 
	//12 2 22 *** INTERVENTION - new project and code around all interventsion
	m_interventionObjectList=NULL; //open only after preparing model. if we have for emaxple 10 intervension, each object will have the var indexe, 
	m_interventionObjectListSize=0;

	//how many persons participated in this profile analysis,
	//which is only those that passed the inclusion critera
	m_sizeOfResearchPopulation = 0;//->GetNumberOfPatients();//numberOfPatients;
	m_fullPopulation = NULL;//dataObj->m_twoDimArray;//:patientsDataSet;
	m_depArray = NULL;// dataObj->m_depArr;//->GetDependentArray();//depArr;
	m_numberOfVariables = 0;//dataObj->m_sizeOfItem;//->GetNumberOfAugmentedVars();// numberOfAugmentedVars;
	m_isInProfile=NULL;
	m_sizeOfProfilePopulation =0;
	if(dataObj != NULL)
	{
		m_sizeOfResearchPopulation = dataObj->m_numOfItems;//->GetNumberOfPatients();//numberOfPatients;
		m_fullPopulation = dataObj->m_twoDimArray;//:patientsDataSet;
		m_depArray = dataObj->m_depArr;//->GetDependentArray();//depArr;
		m_numberOfVariables = dataObj->m_sizeOfItem;//->GetNumberOfAugmentedVars();// numberOfAugmentedVars;
	//	m_isInProfile=NULL;
		//m_sizeOfProfilePopulation =0;
	}
	else
	{
		int sdgf =0;
	}
	if(m_sizeOfResearchPopulation>0)
	{
		m_isInProfile = new bool[m_sizeOfResearchPopulation];
		for(int i = 0 ; i < m_sizeOfResearchPopulation ; i++)
		{
			m_isInProfile[i]=false;
		}
	}

	SetProfilePopoulationFromResearchPopulation(isInContext);//m_isInProfile m_sizeOfProfilePopulation
	//will adjust isIn array to have true for profile memebrs and m_sizeOfProfilePopulation
		
	/*
 add to build or constructure  function of research object

	take iput all full population and cut accoriding to incusion, but if there is no inclusion, or if even aftetr 
	inclusino we still have a large more than 10,000 than select randomm population to avoid long processes

	get w hich are the input inlcusio list, logistic regression, scema, and input varibles.
	if no shema we have an option to create some by calcuation and some bt hard coding
	if hard coding it will also create the augmrnet fields according to such hard code rules
	if no inclusion list of which var val are good for profile inclusion, than we have to add a hard coded func
	if no logistic regression we have a differenrt odd ratio adjisutment fuction
	
	*/



	m_profileDependentAverage=0.0; //full profile pattern  

	//m_profilePatientBasedPerformance=0.0;
	m_profileRootBasedPerformance=0.0;

	
	 

//////////////////////////PREDICTION SCALES/////////////////////
//each variable index and point value represent thepower of a code 1 of the varible. a code 1 defined in the schema

	m_oddRatioPointsListSize=0;  //size of this list
	m_oddRatioAlgoRates=NULL;
	m_adjustedPointRates=NULL;
	
	m_numberOfSubGrps =resObj->GetNumberOfSubGrps();// numberOfSubGrps;
	m_subGroupPerformanceScore=NULL;
	m_subGroupAdvncPErfScore=NULL;
	m_subGrpBestMatchGapAvg=NULL;
	m_meanDeltaProfSub=NULL;
	m_sdDeltaProfSub=NULL;
	m_scaleMean = 0.0;
	m_scaleSD=0.0;

	if(m_numberOfSubGrps>0)
	{
		m_subGroupPerformanceScore = new double[m_numberOfSubGrps];
		m_meanDeltaProfSub= new double[m_numberOfSubGrps];
		m_sdDeltaProfSub= new double[m_numberOfSubGrps];
		m_subGroupAdvncPErfScore = new double[m_numberOfSubGrps];
		m_subGrpBestMatchGapAvg= new double[m_numberOfSubGrps];
		m_subGroupThresholdList = new double[m_numberOfSubGrps]; //match a person into a sub group using predictive points
		m_subGroupAverageDependent= new double[m_numberOfSubGrps]; //sub group pattern
		m_subGroupPopulationSize = new int[m_numberOfSubGrps] ;//
		for(int ii=0;ii< m_numberOfSubGrps;ii++)
		{
			m_subGroupThresholdList[ii]=0.0;
			m_meanDeltaProfSub[ii]=0.0;
			m_sdDeltaProfSub[ii]=0.0;
			m_subGroupAverageDependent[ii]=0.0;
			m_subGroupPopulationSize[ii]=0;
			m_subGroupPerformanceScore[ii]=0.0;
			m_subGroupAdvncPErfScore[ii]=1.0;
			m_subGrpBestMatchGapAvg[ii]=0.0;
		}
	}

}

 
cProfileObject::~cProfileObject()
{
	if(	m_inclusionRuleList != NULL)
	{
		delete []m_inclusionRuleList;
		m_inclusionRuleList=NULL;
	}
	if(m_isInProfile != NULL)
	{
		delete []m_isInProfile;
		m_isInProfile=NULL;
	}
	if( m_oddRatioAlgoRates != NULL)
	{
		delete []m_oddRatioAlgoRates ;
		m_oddRatioAlgoRates = NULL;
	}
	if(m_adjustedPointRates != NULL)
	{
		delete []m_adjustedPointRates ;
		m_adjustedPointRates =NULL;
	}

	if(m_subGroupThresholdList!= NULL)
	{
		delete []m_subGroupThresholdList;
		m_subGroupThresholdList=NULL;
	}

	if(m_subGroupAverageDependent!= NULL)
	{
		delete []m_subGroupAverageDependent;
		m_subGroupAverageDependent=NULL;
	}
	if(m_subGroupPopulationSize != NULL)
	{
		delete []m_subGroupPopulationSize ;
		m_subGroupPopulationSize =NULL;
	}
	if(m_subGroupPerformanceScore!= NULL)
	{
		delete []m_subGroupPerformanceScore;
		m_subGroupPerformanceScore=NULL;
	}
	if(m_subGrpBestMatchGapAvg!=NULL)
	{
		delete[]m_subGrpBestMatchGapAvg;
		m_subGrpBestMatchGapAvg=NULL;
	}
	if(m_subGroupAdvncPErfScore!= NULL)
	{
		delete []m_subGroupAdvncPErfScore;
		m_subGroupAdvncPErfScore=NULL;
	}
	if(m_meanDeltaProfSub!=NULL)
	{
		delete []m_meanDeltaProfSub;
		m_meanDeltaProfSub=NULL;
	}
	if(m_sdDeltaProfSub!=NULL)
	{
		delete[] m_sdDeltaProfSub;
		m_sdDeltaProfSub=NULL;
	}
	if(m_interventionObjectList != NULL)
	{
		delete []m_interventionObjectList;
		m_interventionObjectList=NULL;
	}
	
}
 


 
//4 17 22 TO DO 2 - adjust this fusnction so that if profile population isi too large dont fill the is in 
//output with all patients, take random 10,000
void cProfileObject::SetProfilePopoulationFromResearchPopulation(bool* isInContext)
{
 	int foundCnt = 0;
	for(int i = 0 ; i < m_sizeOfResearchPopulation ; i++)
	{
		m_isInProfile[i]=false;
		//bool* sdf;
		if(   isInContext == NULL || isInContext[i] == true)
		{
	 		bool isIn = true;
			for(int ii = 0 ; ii< m_inclusionRuleListSize ;ii++)
			{
				cVariableAndValueAndPoints varValPnts = m_inclusionRuleList[ii];
				cVariableAndValue tmp(varValPnts.m_variableIndex, varValPnts.m_value);
				bool isVarValInPatient = IsVarValInPatient( m_fullPopulation[i], m_numberOfVariables, tmp);
				if(!(isVarValInPatient))
				{
					isIn = false;
				}
			}
			m_isInProfile[i] = isIn;
			if(isIn)
			{
				foundCnt ++;
			}
		}
	}
	m_sizeOfProfilePopulation = foundCnt;
}


/*
//4 17 22 TO DO 2 - adjust this fusnction so that if profile population isi too large dont fill the is in 
//output with all patients, take random 10,000
void cProfileObject::SetGrpPopoulation(
	bool* isInGrpOut, int &sizeOfProfilePopulation,  double** fullPopulation,	int sizeOfResearchPopulation, 
	int numberOfVariables,		cVariableAndValueAndPoints* inclusionRuleList,	
	int inclusionRuleListSize,	bool* isInContext)
{
 	int foundCnt = 0;
	for(int i = 0 ; i < sizeOfResearchPopulation ; i++)
	{
		isInGrpOut[i]=false;
		//bool* sdf;
		if(   isInContext == NULL || isInContext[i] == true)
		{
	 		bool isIn = true;
			for(int ii = 0 ; ii< inclusionRuleListSize ;ii++)
			{
				cVariableAndValueAndPoints varValPnts = inclusionRuleList[ii];
				cVariableAndValue tmp(varValPnts.m_variableIndex, varValPnts.m_value);
				bool isVarValInPatient = IsVarValInPatient( fullPopulation[i], numberOfVariables, tmp);
				if(!(isVarValInPatient))
				{
					isIn = false;
				}
			}
			isInGrpOut[i] = isIn;
			if(isIn)
			{
					double sumPnt =   m_profileObjectPtrList[p]->CalclaterSumAdjusteddPnts(researchDataObj->m_twoDimArray[i],
					researchDataObj->m_sizeOfItem,	m_profileObjectPtrList[p]->GetAdjustedOddRateArr(),
					m_profileObjectPtrList[p]->GetOddRatioListSize()		);
			int subGrpIndex = m_profileObjectPtrList[p]->GetSubGrpIndex( sumPnt,  m_profileObjectPtrList[p]->GetThresholdArr(),
				m_numberOfSubGrps   ) ;
			if( subGrpIndex  != x )
			{
				isPersonInProfSub[i] = false;					
			}
			}
			if(isIn)
			{
				foundCnt ++;
			}
		}
	}
	sizeOfProfilePopulation = foundCnt;
}
*/

//4 17 22 TO DO 0
void cProfileObject::CalculateOddRatio( double &oddRAtio , double &popPercent, int varIndex, double valueForOdd)//check
{
	int cntThisValue = 0;
	int cntAllVAlue = 0;
	int cntOtherValues=0;
	double percOfCasesWitnNoZeroForThis = 0.0;


	double avgDepThisVAlue = 0.0;
	double avgDepAllValue = 0.0;
	double avgDepOtherValues = 0.0;
	oddRAtio = 1.0; //default
	popPercent = 0.0;

	for(int i = 0 ; i < m_sizeOfResearchPopulation ; i++)
	{
		if(m_isInProfile[i])
		{
			
			double dep = m_depArray[i];
			avgDepAllValue += dep;
			cntAllVAlue++;

			double patientValue = m_fullPopulation[i][varIndex];
			if(patientValue == valueForOdd)
			{
				avgDepThisVAlue += dep;
				cntThisValue++;
				if(dep > 0.0)
				{
					percOfCasesWitnNoZeroForThis +=1.0; //if we got 
				}
			}
			else{
				avgDepOtherValues += dep;
				cntOtherValues++;
			}
		}
	
	}


	if(cntThisValue > 0.0)
	{
		avgDepAllValue /= cntAllVAlue;
		percOfCasesWitnNoZeroForThis /= cntThisValue;

		if( (percOfCasesWitnNoZeroForThis * cntThisValue) > 20.0) //we got enough sample, i.e 100 count and 20% rate
		{
		//now we divide 
			avgDepOtherValues /= cntOtherValues ;
			avgDepThisVAlue /= cntThisValue;
			if(avgDepOtherValues > 0.0)
			{
				oddRAtio = //avgDepThisVAlue / avgDepAllValue;
				    CalculaterRawOdd( avgDepThisVAlue, avgDepOtherValues);//3 10 24 repalaced avgDepAllValue
						//m_subGroupAverageDependent[i], avg);
			}
		}
		popPercent = ((double) cntThisValue) /  ((double) cntAllVAlue);
	}
	 //1 is the detaul. using m_fullPopulation, m_sizeOfResearchPopulation size, m_isInProfile for sub set,
		               //m_fullPopulation for predictive data and m_depArr for dep so we can calcaulte the odd of this value
						//under this var compared with all values in regads to the chane of haivng certain avg dep value
}


	
 bool cProfileObject::IsRightRuleSetChildOfLeft(
		cVariableAndValueAndPoints*	ruleSetI, int ruleSetSizeI, 
		cVariableAndValueAndPoints*	ruleSetII,int ruleSetSizeII)
 {
	//if right is a child thann it is longer
	bool isRightAchild = false;
	if(ruleSetSizeII > ruleSetSizeI)
	{
		//if II is longer, it is many a c hild, and need to see that each of the I parient rules is includedin II
		bool isFullRulesetMatch = true;
		for(int i = 0 ; i < ruleSetSizeI ; i++)
		{
			int var = ruleSetI[i].m_variableIndex;
			double value = ruleSetI[i].m_value;
			bool isThisVarValIncluded = false;
			for(int ii = 0 ; ii< ruleSetSizeII ; ii++)
			{
				if((ruleSetII[ii].m_variableIndex == var ) &&(ruleSetII[ii].m_value == value))
				{
					isThisVarValIncluded=true;
				}
			}
			if(!isThisVarValIncluded)
			{
				isFullRulesetMatch = false;
			}
		}
		if(isFullRulesetMatch)
		{
			isRightAchild=true;
		}
	}
	return isRightAchild;
 }

void cProfileObject::PrepareModel( cGlobals &globals )//cPredictiveModel* rootOddPredictiveModel, 
	                                    //   cPredictiveModel* regPredictiveModel)
{
	PrepareOddRatioStructure( globals );//rootOddPredictiveModel, regPredictiveModel);
}

//2 5 24*
void cProfileObject::CreatePErcetileGrpsFromInputDataItems(double* subGrpsDepAvgSet,double* threshArr,
	int* subGroupPopulationSize, double  &profileAvgDep,
		double** testData,double* depArr,	bool* isIn ,	
		int numOfTestItems, int numOfVariables, int numOfSubGrps, cVariableAndValueAndPoints* pointRatesArr, int pointRateArrSize, cGlobals &globals)
{
	/*
	fiven an input test data, and request number of sub groups, output will be these sub groups averages.
	also the threshlds that are created to support such 
	*/

	double* pntArr = new double[numOfTestItems];
	FillPntArrFromAdjustedModel(pntArr,testData, isIn, numOfTestItems, numOfVariables, pointRatesArr,  pointRateArrSize);

	CalculateThresholds(threshArr,numOfSubGrps, pntArr,isIn,numOfTestItems);

	profileAvgDep = 0.0;
	CreateAvgDepSubGrps(NULL,subGrpsDepAvgSet,threshArr,subGroupPopulationSize, profileAvgDep, numOfSubGrps,pntArr,depArr, isIn, numOfTestItems, globals);
	 
	delete []pntArr;
}


//12 2 22 ** consider change the odd ratio if bias to left or right
double cProfileObject::CalculaterRawOdd(double grpDepVal, double profileDepVal)
{
	grpDepVal = cVarianceCalc::Max(grpDepVal , profileDepVal / 20.0);//grpDepVal should not be smaller  than 20 times smaller than the  profile dep val
	//GetProfileMean
	double ret  = grpDepVal / profileDepVal;
	return ret;
}



	
double cProfileObject::GetSumOfAbsInclusionRulePoints()//each element in the inclusin list has the algo odd ratio points turned
{
	double sum = 0.0;
	for(int x = 0 ; x < m_inclusionRuleListSize ; x++)
	{
		double pnts = m_inclusionRuleList[x].m_points;
		sum += cVarianceCalc::Abs(pnts);	
	}
	return sum;
}
double cProfileObject::GetSubGroupAbsAccomultedPerformance(int index, bool isAdvancedPerfGetbEstMatch,  cGlobals &globals)
{//12 2 22 ***  figuer out if instead of summary of two elemetn it can be better to directly calculate the perfromacne
	//of a profile from the root - skiiping the two steps of profiles shift and then the sub grp bucket. it cann be that
	//i find that shift left and than right should or shoudl not add to the absInclusionSetSumScores and the sub grp
	//can be gapped from the avg root and not avag profile
	double absInclusionSetSumScores = GetSumOfAbsInclusionRulePoints();
	double absSubGrpPerfScore = cVarianceCalc::Abs(m_subGroupPerformanceScore[index]);
	double ret = absInclusionSetSumScores + absSubGrpPerfScore;

	if(isAdvancedPerfGetbEstMatch)
	{
		ret = m_subGroupAdvncPErfScore[index];
		/*if(m_subGroupAdvncPErfScore[index] == globals.g_STRENGTH_MULT_OF_LONG_STRETCHED_PROFILE)
		{
			ret = globals.g_STRENGTH_MULT_OF_LONG_STRETCHED_PROFILE;//using this as a flag to say "this profile takes all"
		}
		else
		{
			ret *= m_subGroupAdvncPErfScore[index];
		}*/
	}
	return ret;
}



//6 22 23 add maxSampleSizeTarget as input and a large number will make this be ignored
void cProfileObject::CalculateThresholds(double* threshArr, int numOfSubGrps, double* pntArr, bool* isIn,  int numOfTestItems)
{
	int count = 0;
	for(int i  = 0 ; i < numOfTestItems ; i++)
	{
		if(isIn == NULL || isIn[i])
		{
			count++;
		}
	}
	int maxSampleSizeTarget = 15000;//7 11 23 * 55
	if(count > maxSampleSizeTarget)
	{
		int mode = count / maxSampleSizeTarget;
		bool* newIsIn = new bool[numOfTestItems];
		int check =0;
		for(int i  = 0 ; i < numOfTestItems ; i++)
		{
			newIsIn[i] = false;
		
			if(isIn == NULL || isIn[i])
			{
				if((i % mode) == 0)
				{
					newIsIn[i] = true;
					check++;
				}
			}
			int sdsgg=0;
		}
		cVarianceCalc::PrepareMapOfValuesForDecilesGrouping( threshArr, numOfSubGrps, pntArr,newIsIn,numOfTestItems );
		delete []newIsIn;
	}
	else
	{
		cVarianceCalc::PrepareMapOfValuesForDecilesGrouping( threshArr, numOfSubGrps, pntArr,isIn,numOfTestItems );
	}
}


bool  cProfileObject::IsProfSubRelatedToHigherPerfWeight(  int  subIndex, cProfileObject** arr, int size  )
 {
	/* 5 15 24  check in parents which are the highest related profsubs.  check avg weight. maintain a threshold that above means that this profsub
	is related to a higher perf cases.
	it can be an input of perc that if we pass it we retur true
	builiding the data structure allos us to add for each profsub how many patients and a list of profsub parents that are removed in get best matc
	these removed are per a patient. we have then one evidancne about profsub and parents share same profsub patient. if any of these have a weight
	we can maintain a list of such parent profsubs or check if any neigbor sub index to make it simple
	then just check of if any parent of prof and a subIndex, or subIndex-1, or subIndex+1, have a weight >= 1.0
 
 */
	 int thisInclusionListSize = GetInclusionRuleListSize();
	 bool isParentWeightFound = false;
	 for(int i = 0 ; i < size  && !isParentWeightFound; i++)
	 {
		if(arr[i] != NULL)
		{
			if(arr[i]->GetInclusionRuleListSize() == (thisInclusionListSize - 1))
			{
				bool isWithWeight = false;
				if( arr[i]->GetProfileAdvancedPerformance(subIndex ) >= 1.0)
				{
					isWithWeight=true;
				}
				if(subIndex > 0 &&  arr[i]->GetProfileAdvancedPerformance(subIndex -1) >= 1.0)
				{
					isWithWeight=true;
				}
				if(subIndex < (GetNumberOfSubGroups()-1 ) &&  arr[i]->GetProfileAdvancedPerformance(subIndex + 1) >= 1.0)
				{
					isWithWeight=true;
				}
				if(isWithWeight )
				{
					if( cProfileObject::IsRightRuleSetChildOfLeft(arr[i]->GetInclusionRuleList() ,arr[i]->GetInclusionRuleListSize(),
						GetInclusionRuleList(),GetInclusionRuleListSize()))
					//	IsRightRuleSetIsSubsetOfLeft  (prof->GetInclusionRuleList() , arr[i]->GetInclusionRuleList() )
					{
						isParentWeightFound = true;
					}
				}
			}
		}
	 }
	 return isParentWeightFound;
 }
		

	double cProfileObject::GEtProfileSDofBucket()
	{
		double avg = GetProfileDepAverage();
		double var = 0.0;
		double sumWghts = 0.0;
		for (int i = 0 ; i < m_numberOfSubGrps ; i++)
		{
			double gap = m_subGroupAverageDependent[i] - avg;
			double gapSqr = gap*gap;
			double wgh = double(m_subGroupPopulationSize[i]);
			sumWghts+=wgh;
			var += wgh*gapSqr;
		}
		var /= sumWghts;
		double sd = pow(var, 0.5);
		return sd;
	}



void cProfileObject::FillPntArrFromAdjustedModel(double* pntArr, double** testData, bool* isIn, int numOfTestItems, 
	int numOfVars, cVariableAndValueAndPoints* pointRatesArr, int pointRateArrSize)
	{
		
//	double* sumPnts = new double[m_sizeOfResearchPopulation];
		for(int i = 0 ; i < numOfTestItems ; i++)
		{
			pntArr[i] = 0.0;
			if(isIn == NULL || isIn[i])
			{
				pntArr[i] = CalclaterSumAdjusteddPnts(
					testData[i],numOfVars,
						//cVariableAndValueAndPoints* 
						pointRatesArr, pointRateArrSize)  ;
			}
		}
	
	}


void cProfileObject::CreateAvgDepSubGrps(int* grpIndexArr, double* subGrpsDepAvgSet, double* threshArr,int* subGroupPopulationSizee, double &profileAvgDep,
						int numOfSubGrps, double* pntArr,double* depArr, bool* isIn, int numOfTestItems, cGlobals &globals)
	{
	//	int* cntArr = new int[numOfSubGrps];
		for(int x = 0 ; x < numOfSubGrps ; x++)
		{
			subGrpsDepAvgSet[x]=0.0;
			subGroupPopulationSizee[x]=0;
		}
		for(int i = 0 ; i < numOfTestItems ; i++)
		{
			if(grpIndexArr != NULL)
			{
				grpIndexArr[i] = -1;
			}
			if(isIn == NULL || isIn[i])
			{
				//Predict ionAPI(double* personArr, int varListSize)
				double sum = pntArr[i];
					//CalclaterSumAdjusteddPnts(	 personArr, 
				//	m_numberOfVariables, m_adjustedPointRates,  m_oddRatioPointsListSize);

				int subGrpIndex = GetSubGrpIndex(sum, threshArr, numOfSubGrps);
				subGrpsDepAvgSet[subGrpIndex ] += depArr[i];
				subGroupPopulationSizee[subGrpIndex ]++;

				if(grpIndexArr != NULL)
				{
					grpIndexArr[i] = subGrpIndex;
				}

			}
		}
	
		double avgg = 0.0;
		int cntt=0;
		bool isAtLEastOneBucketTooSmall = false;
		for(int x = 0 ; x < numOfSubGrps ; x++)
		{
			if(subGroupPopulationSizee[x] > 0)
			{
				subGrpsDepAvgSet[x] /= subGroupPopulationSizee[x];
				avgg += subGrpsDepAvgSet[x] * subGroupPopulationSizee[x];
				cntt += subGroupPopulationSizee[x];
			}
			if(subGroupPopulationSizee[x] <  globals.g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE)
			{
				isAtLEastOneBucketTooSmall = true;
			}
		}
		avgg /= cntt;
		profileAvgDep = avgg;
		if(false)//7 11 23 * 55
		{
			double* altenativeAvgArr = new double [numOfSubGrps];
			for(int x = 0 ; x < numOfSubGrps ; x++)
			{
				altenativeAvgArr[x] = 0.0;
				double sumWghs = 0.0;
				for(int y = 0 ; y < numOfSubGrps ; y++)
				{
					double wgh = 1.0;
					double gap = cVarianceCalc::Abs(x-y);
					gap *= gap;
					gap += 0.5; //
					wgh /= gap; //if x==y than wgh is 2. if x-y == 1 than wgh is 0.66. if x-y==2  than wgh is 0.4
					wgh *= subGroupPopulationSizee[y] ;
					altenativeAvgArr[x] += wgh * subGrpsDepAvgSet[y];
					sumWghs += wgh;
				}
				altenativeAvgArr[x] /= sumWghs;

				if( isAtLEastOneBucketTooSmall)
				{
					subGrpsDepAvgSet[x] = altenativeAvgArr[x];
				}
			}
			delete []altenativeAvgArr;
			altenativeAvgArr=NULL;
		}
		else
		{
			for(int x = 0 ; x < numOfSubGrps ; x++)
			{
				if(subGroupPopulationSizee[x] <  globals.g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE) 
				{ // only in this case do all these lines for this iteration. if the size is equal or more than the threshld than dont do this and no need to u pdate subGrpsDepAvgSet[x] as it is already full 
					double altenativeAvg = 0.0;
					double sumWghs = 0.0;
					double missingWgh =  globals.g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE - subGroupPopulationSizee[x] ;
					for(int y = 0 ; y < numOfSubGrps ; y++)
					{
						if(x!=y)
						{
							double wgh = 1.0;
							double gap = cVarianceCalc::Abs(x-y);
							gap *= gap;
							gap += 0.2;//a gap of 2 between x and y makes 4.2 devision to the wgh.
						           //a gap of 1 makes 1.2 and a gap of 3 makes 9.2 division 
							wgh /= gap; //if x==y than wgh is 2. if x-y == 1 than wgh is 0.66. if x-y==2  than wgh is 0.4
							wgh *= subGroupPopulationSizee[y] ;
							altenativeAvg += wgh * subGrpsDepAvgSet[y];
							sumWghs += wgh;
						}
					}
					altenativeAvg /= sumWghs;
			
					if(false)//7 11 23 freezing out this line of code below in order not to make any adajustment to the
//subGrpsDepAvgSet once it is set with the data processing to allow a clean analytics of delicate changes to happen.
					{
						subGrpsDepAvgSet[x] =  ((subGroupPopulationSizee[x] * subGrpsDepAvgSet[x]) +
				     (( globals.g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE - subGroupPopulationSizee[x])*  altenativeAvg ) )
                               /      globals.g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE;
					}
				}
			}
		}
	}
	


void cProfileObject::CompleteModel( cGlobals &globals  )//double** fullPopulation, bool* isInProfile, int sizeOfResearchPopulation)
{
	CreatePErcetileGrpsFromInputDataItems( m_subGroupAverageDependent, m_subGroupThresholdList,
		m_subGroupPopulationSize, m_profileDependentAverage,
		 m_fullPopulation, m_depArray,	 m_isInProfile ,	
		 m_sizeOfResearchPopulation, m_numberOfVariables,  m_numberOfSubGrps, m_adjustedPointRates, m_oddRatioPointsListSize ,  globals );
}

bool cProfileObject::IsVarValGoodForChildOPening(cVariableAndValueAndPoints &obj,
	InputVariablesPackageForResearchObj* metaResearcObj,  cGlobals &globals)
{
	bool ret =  true;
	if(obj.m_points == 0.0)
	{
		ret = false;
		return ret;
	}
	if(    (cVarianceCalc::Abs( obj.m_points)) < globals.g_MIN_ODD_RATIO_TOJUSTIFIY_OPENING_CHILD_PROFILE)
	{
		ret = false;
		return ret;
	}
	//2- if the object variable is part of the regression input but this specific value 
	//is a zero weight on the regression input than this is a fasle 
	int var = obj.m_variableIndex;
	double val = obj.m_value;

	bool isVarIncludesInRegreweghts = metaResearcObj->IsVarIncludes(var);
	if(isVarIncludesInRegreweghts)
	{
		bool isVarValHasNonzeroPoints = metaResearcObj->IsVarVAlHasNonZeroPoints(var,val);
		if( !isVarValHasNonzeroPoints) //not non zero meand a zero points var val
		{
			//if this is a zero points val than if thre is another val in the same var
			//with non zery points than we set ret to false
			bool isVarHasAnyNonZeroPoints = 
				metaResearcObj->IsVarHasAnyValWithNonZeroPnts(var);
			if(isVarHasAnyNonZeroPoints)
			{
			//here we are at a situation with a real regresion points for at least one of 
			//values of this subject varible but that this subject value is a zero. 
				//this case we do not want to contihue
				ret = false;
				return ret;	
			}
		}
	}
	
	return ret;
}

/*
this function will 
1-look at all var val that has any odd looking at the var/var list

2-remove any subject var/val that has a var with at least one val with a regression value associoated that is != 0.0 but that 
this subject var/val had a 0 regression value, that means we do not want to take this var val to be a member of the profile 
inclusion set.
EXAMPLE in case of hosptilizatsion, make sure we do not get a regression value at all for hospitilization so we 
have both yes and no as separate profile inclusion set candidates. since these both will be also odd ratio as this has all options
than we will select these a lot before other options

3-if we dont have any reg weight for any of the vals of this var or that we do have a reg wieght for this val than we take the var/val

4-we will not find any var/val that is already in the inclusion set since it would not have had an odd ratio (check when debug)
 
NOTE:the list will incldue all options that are avaliabile frmo the meta file guidlinles, minus var/val alredy part of thisProfile 
the purpose of these var/val objects is to add each var/val to the "thisProfile" inclusion list and to make
a larger version by one element, for each new profile. these all profiles can be seen as siblings to this parent. 
each profile with more than one var/val in ithe inclusino set list will have more than one parent, 
but these other parents will not be shared between all of thisProfile children
*/
void cProfileObject::CollectAllVarValOptionswithNonZeroOdd( 
	cVariableAndValueAndPoints*& childPotetialInclusionArr, int &childInclusionArrSize,
	InputVariablesPackageForResearchObj* metaResearcObj,  cGlobals &globals)
{
	childPotetialInclusionArr = NULL;
	childInclusionArrSize = 0;

	int cnt = 0;
	for(int i = 0 ; i < m_oddRatioPointsListSize ; i++)
	{
		cVariableAndValueAndPoints temp = m_oddRatioAlgoRates[i];
		int var = temp.m_variableIndex;
		double val = temp.m_value;
		if(IsVarValGoodForChildOPening(temp, metaResearcObj, globals))
		{
			cnt++;
		}
	}
	childInclusionArrSize = cnt;
	if(childInclusionArrSize > 0)
	{
		childPotetialInclusionArr = new cVariableAndValueAndPoints[childInclusionArrSize];
		cnt = 0;
		for(int ii = 0 ; ii < m_oddRatioPointsListSize ; ii++)
		{
			cVariableAndValueAndPoints temp = m_oddRatioAlgoRates[ii];
			int var = temp.m_variableIndex;
			double val = temp.m_value;
			if(IsVarValGoodForChildOPening(temp,metaResearcObj , globals))
			{
				childPotetialInclusionArr[cnt++]=temp;
			}
		}
	}
}
  


double cProfileObject::CalclaterSumAdjusteddPnts(	double* personArr, 
	int numberOfVariabless, cVariableAndValueAndPoints* pointRates, int size)
{
	double sum = 0.0;
	for(int m = 0 ; m < size ; m++)
	{
		int var = pointRates[m].m_variableIndex;
		double val = pointRates[m].m_value;
		if(personArr[var] == val)
		{
			sum += pointRates[m].m_points;
		}
	}
	return sum;
}




void cProfileObject::ConvertToSymetricOddRatio(double &oddOrign,  cGlobals &globals )
{
	if(oddOrign >= 1.0)
	{
		oddOrign -= 1.0;
		oddOrign = cVarianceCalc::Min(oddOrign , globals.g_MAX_VALUE_OF_ABS_SYMETRIC_ODD_RATIO);
	}
	else if(oddOrign > 0.0)// between 0 and 1 but not 0 nor 1
	{
		oddOrign = 1.0 / oddOrign;
		oddOrign -= 1.0;
		oddOrign = cVarianceCalc::Min(oddOrign ,  globals.g_MAX_VALUE_OF_ABS_SYMETRIC_ODD_RATIO);
		oddOrign *= (-1.0);		
	}
	else
	{
		int rty = 0;
	}
}

void cProfileObject::PrepareOddRatioStructure( cGlobals &globals )
//	cPredictiveModel* rootOddModel, cPredictiveModel* regPredictiveModell)
{
	int rrty = 0;
	
	cVariableAndValueAndPoints* tempVarValPontArr = new cVariableAndValueAndPoints[1000];//large enough
	cVariableAndValueAndPoints* tempVarValPercetArr = new cVariableAndValueAndPoints[1000];//large enough
		 
	int movingindex = 0;
	int numOfVars = m_schemaObjArr->m_orgNumOfVars;
	for(int j = 0 ; j < numOfVars ; j++)
	{
		if( (m_schemaObjArr->m_schemaArr[j]->m_isPredictiveVariable) &&
			(!m_schemaObjArr->m_schemaArr[j]->m_isToBeReplaced))
		{
			for(int v = 0 ; v < m_schemaObjArr->m_schemaArr[j]->m_numberOfValues ; v++)
			{
				double value = m_schemaObjArr->m_schemaArr[j]->m_varValues[v];
				double oddRAtio = 1.0;
				double popPercent = 0.0;
				CalculateOddRatio( oddRAtio , popPercent,  j, value);//check
				ConvertToSymetricOddRatio(oddRAtio ,  globals );
				cVariableAndValueAndPoints varValPointsObj(j,  value, oddRAtio);
				cVariableAndValueAndPoints varValPerctObj(j,  value, popPercent);
				tempVarValPontArr[movingindex] = varValPointsObj;//check
				tempVarValPercetArr[movingindex] = varValPerctObj;
				movingindex++;

			}
		}
	}
		
	m_oddRatioPointsListSize = movingindex;  //size of this list
	m_oddRatioAlgoRates = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];//a profile has an odd ratio arr using the Profile population. the root has the universe odd rat
	m_adjustedPointRates = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];//then the profile will have an adjsuted version of that
	for(int x = 0 ; x < m_oddRatioPointsListSize ; x++)
	{
		m_adjustedPointRates[x] = m_oddRatioAlgoRates[x] = tempVarValPontArr[x];
	}
	delete []tempVarValPontArr;
	delete []tempVarValPercetArr;
		 
}


//9 13 22 *
void cProfileObject::SetAdjustedOddModel(
	cPercentileCalculationModel* rootOddPredictiveModel, 
	cPercentileCalculationModel* regPredictiveModel)//
{
	cPercentileCalculationModel::BuildAdjustedModel(m_adjustedPointRates,m_oddRatioAlgoRates,
		m_oddRatioPointsListSize, rootOddPredictiveModel,regPredictiveModel);
	//output: m_adjustedPointRates 
	//input - thw root odd ratio mode,
	//         the root regression model
	//         the proifle odd model, to then look at the root gap between the odd and the reg
	//         and adjust the profile odd model as output of this fuction
	
	
	
	//is getting adjsuted and be then different than the m_oddRatioAlgoRates
	//m_adjustedPointRates is now same as regrular odd point rates. this function takes the 
	//ratio or gap between the odd model and the regression odel of the root proifle and 
	//adjust accordingly the points of the profile , any proifle, oddRarilAlgoRAte into adjustedPointRates
}
	
/*
void cProfileObject::PreparePredictiveModel()//size of profile populatio will be calcualted here
{
	
	{	
		cVariableAndValueAndPoints* tempVarValPontArr = new cVariableAndValueAndPoints[1000];//large enough
		cVariableAndValueAndPoints* tempVarValPercetArr = new cVariableAndValueAndPoints[1000];//large enough
		 
		int movingindex = 0;
		int numOfVars = m_schemaObjArr->m_orgNumOfVars;
		for(int j = 0 ; j < numOfVars ; j++)\
		{
			if( (m_schemaObjArr->m_schemaArr[j]->m_isPredictiveVariable) && (!m_schemaObjArr->m_schemaArr[j]->m_isToBeReplaced))
			{
				for(int v = 0 ; v < m_schemaObjArr->m_schemaArr[j]->m_numberOfValues ; v++)
				{
					double value = m_schemaObjArr->m_schemaArr[j]->m_varValues[v];
					double oddRAtio = 1.0;
					double popPercent = 0.0;
					CalculateOddRatio( oddRAtio , popPercent,  j, value);//check
					cVariableAndValueAndPoints varValPointsObj(j,  value, oddRAtio);
					cVariableAndValueAndPoints varValPerctObj(j,  value, popPercent);
					tempVarValPontArr[movingindex] = varValPointsObj;//check
					tempVarValPercetArr[movingindex] = varValPerctObj;
					movingindex++;

				}
			}
		}
		
	 	double threArr[5];
		int numOfGrps = 5;
		CrerateAdjustedPoints( threArr, numOfGrps, tempVarValPontArr,  tempVarValPercetArr, movingindex);

		 
		m_oddRatioPointsListSize = movingindex;  //size of this list
		m_oddRatioAlgoRates = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];//a profile has an odd ratio arr using the Profile population. the root has the universe odd rat
		m_adjustedPointRates = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];//then the profile will have an adjsuted version of that
		for(int x = 0 ; x < m_oddRatioPointsListSize ; x++)
		{
			m_adjustedPointRates[x] = m_oddRatioAlgoRates[x] = tempVarValPontArr[x];
			m_adjustedPointRates[x].m_points = (double) ConvertOddToOddGrp(  
								threArr, numOfGrps, m_adjustedPointRates[x].m_points   );

		}

		
		double* wghArr = new double [m_sizeOfProfilePopulation];
		double* scaleArr = new double[m_sizeOfProfilePopulation];
		for(int i = 0 ; i < m_sizeOfProfilePopulation ; i++)
		{
			wghArr[i]=0.0;
			if(m_isInProfile[i])
			{
				wghArr[i]=1.0;
				scaleArr[i]=0.0;
				GetPatientScaleValue( scaleArr[i], m_fullPopulation[i]);
			}			
		}
		cVarianceCalc::CalculateMeanAndSD(m_scaleMean,m_scaleSD,scaleArr,wghArr,m_sizeOfProfilePopulation);

		PrepareThresholdsAndRiskGrpParameters(scaleArr);

		//4 17 22 TO DO 2
		//now run all profile population or some of it against thie model and the root and calcaulte some performance

		delete []scaleArr;
		delete []wghArr;
		delete []tempVarValPontArr;
		delete []tempVarValPercetArr;
		delete []tempVarValPontArr ;
		delete[] tempVarValPercetArr;
	}


}
*/
/*
void cProfileObject::GetGrpIndex(double val)
{
	//m_subGroupThresholdList, m_numberOfSubGrps);
	for(int x = 0 ; x < m_numberOfSubGrps ; x++)
	{
		
	}
}*/

//4 17 22 TO DO Debug
/*
void cProfileObject::PrepareThresholdsAndRiskGrpParameters(double* scaleArr)
{
	
	// take care to fill all these 
	 
//	cVarianceCalc::PrepareMapOfValuesForDecilesGrouping( threshold,  numOfBuckets, arr,NULL, arrSize);
//FillValuesOfBuckets( double* bucketVal, int numOfBuckets, double* arr , bool* isIn, int arrSize )
	
	
	cVarianceCalc::PrepareMapOfValuesForDecilesGrouping( m_subGroupThresholdList,  m_numberOfSubGrps, scaleArr,
		m_isInProfile, m_sizeOfResearchPopulation);
	for(int x = 0 ; x < m_numberOfSubGrps ; x++)
	{
		m_subGroupAverageDependent[x]=0.0;
		m_subGroupPopulationSize[x]=0;
		m_subGroupPerformanceScore[x]=0.0;

	}
	for(int i = 0 ; i < m_sizeOfResearchPopulation ; i++)
	{
		if(m_isInProfile[i])
		{
	
			int grpIndex =  cVarianceCalc::GetGrpIndex(scaleArr[i],m_subGroupThresholdList, m_numberOfSubGrps);
	


			m_subGroupAverageDependent[grpIndex] += m_depArray[i];
			m_subGroupPopulationSize[grpIndex]++;
		}
	}
	for(int x = 0 ; x < m_numberOfSubGrps ; x++)
	{
		if(m_subGroupPopulationSize[x]>0)
		{
			m_subGroupAverageDependent[x] /= m_subGroupPopulationSize[x];
		}
	}
	//cVarianceCalc::FillValuesOfBuckets( double* bucketVal, int numOfBuckets, double* arr , bool* isIn, int arrSize )
}
*/
 
int cProfileObject::ConvertOddToOddGrp(  	double* threArr, int numOfGrps, double oddVal  )
{
	int oddGrp = -1;
	for(int x = 0 ; x < numOfGrps ; x++)
	{
		if(oddVal < threArr[x])
		{
			return x;
		}
	}
	return numOfGrps -1;
}
//sort tempVarValPontArr  ans tempVarValPercetArr per the points order, have odd with smaller/negative first
//sort the other togethe to stay assocaited
//then count the plcae with 20% 40% ... (if 5 groups) and what is the odd ther, to set the threshllds, 
void cProfileObject::CrerateAdjustedPoints(double* threArr, int numOfGrps,
			cVariableAndValueAndPoints* tempVarValPontArr,	cVariableAndValueAndPoints*  tempVarValPercetArr, 
			int size)
{

	//bouble sort
	for(int i = 0 ; i < (size-1) ; i++)
	{
		for(int ii = 0; ii < (size-i-1) ; ii++)
		{
			if(tempVarValPontArr[ii].m_points     >   tempVarValPontArr[ii+1].m_points)
			{
				cVariableAndValueAndPoints::Swap((tempVarValPontArr[ii] ), (tempVarValPontArr[ii+1]));
				cVariableAndValueAndPoints::Swap((tempVarValPercetArr[ii] ), (tempVarValPercetArr[ii+1]));
			}
		}
	}

	double sumPerc = 0.0;
	for(int i = 0 ; i < size ; i++)
	{
		sumPerc += tempVarValPercetArr[i].m_points;
	}

	double divisionGap = sumPerc / numOfGrps;
	
	double oneGrpSum = 0.0;
	int indexInThresArr = 0;
	for(int i = 0 ; i < size ; i++)
	{
		oneGrpSum += tempVarValPercetArr[i].m_points;
		if(oneGrpSum > divisionGap)
		{
			oneGrpSum -= divisionGap;
			if(indexInThresArr < numOfGrps)
			{
				threArr[indexInThresArr++] = tempVarValPontArr[i].m_points;
			}
		}
	}
  

}

bool cProfileObject::VarValIsFound(double &foundWeight, double* valueWeights, double* values,
																	int numOfVarValues, double valIn )
{
	foundWeight=0.0;
	for(int v = 0 ; v < numOfVarValues ; v++)
	{
		if(values[v] == valIn)
		{
			foundWeight = valueWeights[v];
			return true;
		}
	}
	return false;
}

/*
	foundWeight=0.0;
	bool ret=false;
	for(int j = 0 ; j < m_numberOfVariables ; j++)
	{
		if(isPredictive && isPredictive[j] && numOfVarValues[j] > 0)
		{
			for(int v = 0 ; v < numOfVarValues[j] ; v++)
			{
				int var = m_adjustedPointRates[j].m_variableIndex;
				double value = m_adjustedPointRates[j].m_value;
				if((var== varIn ) && (value == valIn))
				{
					double points = valueWeights[j][v];
					foundWeight = points;	
					ret = true;
				}
			}
		}
	}
	return ret;
}*/
		
//2 6 24
void cProfileObject::ReplacePredictiveWightsModel(cProfileObject* profile, cResearchDataObj* researchDataObj,
	bool* isPredictive,  cGlobals* globals, bool* isInProf, int countInProf)
//	pArr[e],researchDataObj,isInThisProfSub,count
{
	double** profSubTwoD = new double*[countInProf];
	double* profSubDep = new double[countInProf];
	int movIndex=0;
	for(int k = 0 ; k <  researchDataObj->m_numOfItems ; k++)
	{
		if(isInProf[k])
		{
			profSubTwoD[movIndex] = researchDataObj->m_twoDimArray[k];
			profSubDep[movIndex]= researchDataObj->m_depArr[k];
			movIndex++;
		}	
	}
					//2) 
	double averageSE=0.0;
	double variance=0.0;
	double zeroConstant=0.0;
	double * betaArr= new double[researchDataObj->m_sizeOfItem];
	for(int j=0;j< researchDataObj->m_sizeOfItem;j++)
	{
		betaArr[j]=0.0;
	}
	double regressionPerformanceScore=0.0;
	double * predicted_dependentArr = new double[movIndex ];
	double * predictabilityScores = new double[movIndex];
	bool* isInP = new bool[movIndex];
	for(int i=0;i< movIndex;i++)
	{
		predicted_dependentArr[i]=0.0;
		predictabilityScores[i]=1.0;
		isInP[i]=true;
	}
	/*LinearRegressionInternalDoubleAPI( averageSE, variance,  zeroConstant, 
			betaArr ,  regressionPerformanceScore, predicted_dependentArr,	profSubTwoD,
			movIndex ,  researchDataObj->m_sizeOfItem,       profSubDep,
			predictabilityScores ,         movIndex,        false,       true)
*/
		
	cStatisticStructure  regObject(1);
	//regObject.SetData(unsigned int count, unsigned int numOfPredictiveVars, unsigned int numOfControlledVars, unsigned int kCount, 
		//									unsigned int kControlCount, cStatisticStructure * parentStat);
	
	double perforanceScore=0.0;
	//float * similarityflags=NULL;
//	double* allListVarianceArr = NULL;
	bool isLogistic=true;
	bool isSuccess = regObject.LinearRegression2_7_24(betaArr, averageSE ,variance,perforanceScore,profSubTwoD, profSubDep,
					researchDataObj->m_sizeOfItem,     isPredictive ,   movIndex, isLogistic);//, twoDimShortTemporaryArray);
	if(isSuccess)
	{
		double** valueWeights = new double* [researchDataObj->m_sizeOfItem];
		double** values = new double* [researchDataObj->m_sizeOfItem];
		int* numOfVarValues = new int [researchDataObj->m_sizeOfItem];
		for(int j = 0 ; j < researchDataObj->m_sizeOfItem ; j++)
		{
			numOfVarValues[j] =  GetNumberOfModelVarValues(j);
			valueWeights[j] = NULL;
			values[j]=NULL;
			if(isPredictive[j] && numOfVarValues[j] > 0)
			{
				valueWeights[j] = new double[numOfVarValues[j]];
				values[j] = new double[numOfVarValues[j]];
				for(int jj=0;jj< numOfVarValues[j] ; jj++)
				{
					values[j][jj] = GetVarValuePErInputIndex(j, jj);
					valueWeights[j][jj]= values[j][jj] * betaArr[j];
				}
			}
		}

		profile->SetAdjustedPointRateArrayAndSetThresholdsAndBuckets(valueWeights, values, numOfVarValues,
							isPredictive, *globals,	profSubTwoD, profSubDep,	isInP ,movIndex);
	
		for(int j = 0 ; j < researchDataObj->m_sizeOfItem ; j++)
		{
			delete []valueWeights[j];
			valueWeights[j]=NULL;
		}
		delete []valueWeights;
		valueWeights= NULL;
		delete []numOfVarValues;
		numOfVarValues=NULL;
	}
	delete []betaArr;
	betaArr=NULL;
	delete []predicted_dependentArr;
	predicted_dependentArr=NULL;
	delete[]predictabilityScores;
	predictabilityScores=NULL;
	delete []profSubTwoD;
	profSubTwoD=NULL;
	delete []profSubDep;
	profSubDep=NULL;
}


double cProfileObject::GetVarValuePErInputIndex(int varIn, int valIndex)
{
	int currentCnt=0;
	int naxNumOfVals = 20;
	double* valArr = new double[naxNumOfVals];
	for(int q=0;q<naxNumOfVals;q++)
	{
		valArr[q] = -1.0;
	}
	for(int x = 0 ; x < m_oddRatioPointsListSize; x++)
	{
		int var = m_adjustedPointRates[x].m_variableIndex;
		if(var == varIn)
		{
			double newValue = m_adjustedPointRates[x].m_value;
			updateArrWithValue(valArr, currentCnt, newValue, naxNumOfVals);
		}
	}
	return valArr[valIndex];	 
}
void cProfileObject::updateArrWithValue(double* valArr, int &currentCnt, double newValue, int naxNumOfVals)
{
	bool isFound = false;

	for(int v = 0 ; v< naxNumOfVals ; v++)
	{
		if(valArr[v]>=0)
		{
			if(valArr[v] == newValue)
			{
				isFound=true;
			}
		}
	}
	if(!isFound)
	{
		valArr[currentCnt++]=newValue;
	}

}
	
int cProfileObject::GetNumberOfModelVarValues(int varIn )
{
	int currentCnt=0;
	int naxNumOfVals = 20;
	double* valArr = new double[naxNumOfVals];
	for(int q=0;q<naxNumOfVals;q++)
	{
		valArr[q] = -1.0;
	}
	for(int x = 0 ; x < m_oddRatioPointsListSize; x++)
	{
		int var = m_adjustedPointRates[x].m_variableIndex;
		if(var == varIn)
		{
			double newValue = m_adjustedPointRates[x].m_value;
			updateArrWithValue(valArr, currentCnt, newValue, naxNumOfVals);
		}
	}
	int ret = 0 ;
	for(int q=0;q<20;q++)
	{
		if(	valArr[q]>=0.0)
		{
			ret++;
		}
	}
	return ret;
		
}

void cProfileObject::SetIsPreddictiveBasedOnSizeAndPoints(bool* isPredictive,int P )
{
	for(int j = 0 ; j < P ; j++)
	{
		isPredictive[j] =false;
	}

	for(int x = 0 ; x < m_oddRatioPointsListSize; x++)
	{
		int var = m_adjustedPointRates[x].m_variableIndex;
		double value = m_adjustedPointRates[x].m_value;
		if(m_adjustedPointRates[x].m_points != 0.0)
		{
			isPredictive[var] = true;
		}
	}
}



void cProfileObject::SetAdjustedPointRateArrayAndSetThresholdsAndBuckets(  double** valueWeights, double** values,
	int* numOfVarValues, bool* isPredictive, cGlobals &globals,	double** fullPopulation, double* depArray,
	bool* isInProfile ,	int sizeOfResearchPopulation)
{
	for(int x = 0 ; x < m_oddRatioPointsListSize; x++)
	{
		int var = m_adjustedPointRates[x].m_variableIndex;
		double value = m_adjustedPointRates[x].m_value;
		if(isPredictive[var])//m_adjustedPointRates[x].m_points != 0.0)
		{
			m_adjustedPointRates[x].m_points = 0.0;
			double foundWeight=0.0;
			int var = m_adjustedPointRates[x].m_variableIndex;
			//if(isPredictive[var])
		//	{//2 15 24 check here 1,2,4,8 values for var 61 why dont they get the weight of the 
				if( (value < 20.0) && 
					(VarValIsFound( foundWeight, valueWeights[var],values[var], numOfVarValues[var],  value )))
				{
					m_adjustedPointRates[x].m_points = foundWeight;
				}
		//	}
		}
	}
	CreatePErcetileGrpsFromInputDataItems( m_subGroupAverageDependent, m_subGroupThresholdList, m_subGroupPopulationSize,
		m_profileDependentAverage, fullPopulation, depArray,	 isInProfile ,	 sizeOfResearchPopulation,
		  m_numberOfVariables,  m_numberOfSubGrps, m_adjustedPointRates, m_oddRatioPointsListSize ,  globals );
}






void cProfileObject::GetPatientScaleValue(  double &patientScaleValue, double *augmentedPatientArr)
{
	double pointSummary=0.0;
	/* for every item in the m_adjustedPointRates, if var val found, adding points to the total points
	*/
	for(int x = 0 ; x < m_oddRatioPointsListSize; x++)
	{
		int var = m_adjustedPointRates[x].m_variableIndex;
		double value = m_adjustedPointRates[x].m_value;
		double patientValueThisVar = augmentedPatientArr[var];
		if(patientValueThisVar == value)//the patient has a value in this var that lead to adding certin points
		{
			pointSummary += m_adjustedPointRates[x].m_points;
		}
	}

	patientScaleValue = pointSummary;
}


void cProfileObject::GetPredictedValuesFromScaleVAlueWithFineTuning(double &predicdtion, int &riskGrpIndex,
	double patientScaleValue,  bool isWithFineTuning)
{
	//riskGrpIndex = cVarianceCalc::GetGrpIndex (patientScaleValue ,m_subGroupThresholdList, m_numberOfSubGrps);	
	
	int test = GetSubGrpIndex(patientScaleValue,m_subGroupThresholdList, m_numberOfSubGrps);
	riskGrpIndex = test;//6 21 23


	//i expect patientScaleValue to be in the middle between two threshlds . calcalte the range and the % on that range our scale value is at. if different nthan
	//the  middle of the range 
	

	double rightOfRange = m_subGroupThresholdList[riskGrpIndex];
	if(riskGrpIndex == (m_numberOfSubGrps-1))
	{
		double gap  = (m_subGroupThresholdList[riskGrpIndex-1] - m_subGroupThresholdList[riskGrpIndex-2]);
		rightOfRange = m_subGroupThresholdList[riskGrpIndex-1] + gap;
	}

	double leftOfRange = 0.0;
	if(riskGrpIndex > 0)
	{
		leftOfRange = m_subGroupThresholdList[riskGrpIndex-1];
	}
	else
	{
		double gap = m_subGroupThresholdList[riskGrpIndex+1] - m_subGroupThresholdList[riskGrpIndex]; 
		leftOfRange = m_subGroupThresholdList[riskGrpIndex] - gap;
	}


	double range = rightOfRange - leftOfRange;
	double percentile = (patientScaleValue - leftOfRange) / range;
	percentile = cVarianceCalc::Max(percentile , 0.0);
	percentile = cVarianceCalc::Min(percentile , 1.0);


	double gapInDepFromLeft = 0.0;
	if(riskGrpIndex == 0)
	{
		gapInDepFromLeft = 	(m_subGroupAverageDependent[riskGrpIndex+1] - m_subGroupAverageDependent[riskGrpIndex]);//a proxi of such gap
	}
	else
	{
		gapInDepFromLeft = 	(m_subGroupAverageDependent[riskGrpIndex] - m_subGroupAverageDependent[riskGrpIndex-1]);

	}

	double gapInDepToRight = 0.0;
	if(riskGrpIndex == (m_numberOfSubGrps-1))
	{
		gapInDepToRight = (m_subGroupAverageDependent[riskGrpIndex] - m_subGroupAverageDependent[riskGrpIndex-1]);//a proxi of such gap
	}
	else
	{
		gapInDepToRight = (m_subGroupAverageDependent[riskGrpIndex+1] - m_subGroupAverageDependent[riskGrpIndex]);
	}
	predicdtion = m_subGroupAverageDependent[riskGrpIndex];

	if(isWithFineTuning)
	{
		if(percentile > 0.5)
		{
			predicdtion +=  ((percentile - 0.5) * (gapInDepToRight / 2.0)  );
		}
		if(percentile < 0.5)
		{
			predicdtion -= ((0.5 - percentile) * (gapInDepFromLeft / 2.0) );
		}
	}

}


void cProfileObject::GetPredictedValuesFromScaleVAlue(double &predicdtion, int &riskGrpIndex, double patientScaleValue)
{
	/* a patient gets its scale value from the profile and the profilie has sub groups that lead to prdition
	based on averge value of the sub grouop. 
	*/

	//int GetGrpIndex(double val);
	riskGrpIndex = cVarianceCalc::GetGrpIndex (patientScaleValue ,m_subGroupThresholdList, m_numberOfSubGrps);	
 
	predicdtion = m_subGroupAverageDependent[riskGrpIndex];

}

//4 17 22 TO DO 2
void cProfileObject::CompileAdjustedLocalOddRatioPointsWithLogReg( /*adjustedOddRAtioList*/ )
										  //originalOddRatioList, rootLogistRegression)
{
	/*
	if this is the root than we take the original root /this odd ratio and adjust it with the below logic. 
	in the profile object we can keep the original and when the adjusted is needed send to this function.

	the odd ratio orignial and the l ogist regression root are members of each profile
	the adjuted can be saved or can be just calcualted in real time

	logic:
	for all varibles that have at least one value which is code 1 and part of odd mode
	take the list of values with overlapp under the varible, to represent the varible so that they relate to 
	another varible with any such overlapp and adjust the odd ratio accodingly.
	that isi for the root . again - log reg ratio of values will be the target of the odd ratio between vars
	but the within vars are kept per the odd ratioi findings 
	for the children, a bit differnt. use the ratio of the root between two varibles to apply on the local odd ratio
	of the child and not on the root odd ratio values. 
	if there are positive and negative log reg we keep them in the groups with pos or neg odd ratios
	the adjutment will be between two or somehow with al
	for odd ratio values that are not part of the overlapp, use the pos or negatie avergae shift
	for odd ratio variables that are not part of the logisti regression, use the averge shift pos or negagi of the varibl

	*/

}

	//will be calld by a profile, root or any, to follow th odd ratio calcualteion wth an adajustment
//4 17 22 TO DO 1/2
void cProfileObject::CompoileAdjustedLocalOddRatioPoints( )
{
		/*
		here the logic is to find grouops/domains such as ADLs or home related, or cardio issues and try to look at
		all as an item that gets points in an sub lenear way of its elements. then we can adjust some . a correlation
		can be a good way to see but complicated
		*/
}


//4 17 22 TO DO 2
double cProfileObject::CalcualteSimplePerformanceCompareToOtherModel ( cProfileObject* other)
{
	return 0.0;
}

//4 17 22 TO DO 2 
/*
	comparedParentSimplePerformance = CalcualteSimplePerformanceCompareToOtherModel ( pareintProfile);
	comparedUniversePerformance =CalcualteSimplePerformanceCompareToOtherModel ( m_rootProfile);
	m_profileRootBasedPerformance=comparedUniversePerformance;

	//this function will fill this performoane to be used in a simple way to enable a deeper perforance. basically
	//it is calling to the parent module (either with or without going to the sub group level) and to the child/this
	//and use the half child and all parent as competition to predidct to the half child test patients. again,
	//do it on the full or per sub group of the child and parient test and learing data sets.
	//sae thing we do with the parient and with the root . then we use the root for best match temporary until
	//a depper one is coming, and the parient we use in real time when builidng the tree
 */
void cProfileObject::CalcualteDeepPerformanceValues()
{

}




void cProfileObject::GetSubGrouopAvgDepArr( double*& avgDepArr, int &numberOfSubGrps,  double &mean, double &sd)
{
	mean =0.0;// m_scaleMean;
	sd=0.0;//m_scaleSD;
	cVarianceCalc::CalculateMeanAndSD(mean,sd,m_subGroupAverageDependent,NULL,m_numberOfSubGrps);
	
	avgDepArr = m_subGroupAverageDependent;
	numberOfSubGrps = m_numberOfSubGrps;
}

 




void cProfileObject::PrfObjPrepareArraysToOrFromDisc2(
			cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals, int leadingSpacesNum, int proileIndx )
{
	char msgStr[1000];
	bool isWrite = true;
//   "Profile ID": profileIndex,
	cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger(msgStr,  "Profile ID", m_profileID,leadingSpacesNum , true);
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);
	//   "Anchor ID": 0,
	cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger(msgStr,  "Anchor ID", m_anchorID,leadingSpacesNum, true );
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);
	
	cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger(
					msgStr,  "Size Of Profile Population", m_sizeOfProfilePopulation,leadingSpacesNum, true );
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

	cVarianceCalc::CreateStringWithCulumnAndQuotesAndDouble(
		msgStr,  "Profile Dependent Value Average", m_profileDependentAverage, leadingSpacesNum, true );
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);



//"Inclusion Rules" - stringTitle
	cVarianceCalc::JsonPrintVarValPonts( msgStr, "Inclusion Rules", m_inclusionRuleList, 	m_inclusionRuleListSize, leadingSpacesNum, 
	   true,  &globals,  arrayFlex);



	cVariableAndValueAndPoints* tempVVP = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];
	int movingTemIndex=0;
	for (int i = 0 ; i < m_oddRatioPointsListSize ; i++)
	{
		if(m_adjustedPointRates[i].m_points != 0.0)
		{
			tempVVP[movingTemIndex++] = m_adjustedPointRates[i];
		}
	}
//"Odd Symetric Score List"	
	cVarianceCalc::JsonPrintVarValPonts( msgStr, "Odd Symetric Score Set", 
				tempVVP  , movingTemIndex 	/*m_adjustedPointRates, 	m_oddRatioPointsListSize*/, 
											leadingSpacesNum,    true,  &globals,  arrayFlex);
	delete []tempVVP ;
	tempVVP=NULL;


	cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger( msgStr, "Number Of Risk Groups", m_numberOfSubGrps,leadingSpacesNum, true );
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

	bool isComaa = true;
	cVarianceCalc::JasonPringSimpleArray( msgStr,   "Risk Groups Thresholds Array" , leadingSpacesNum , arrayFlex, 
		&globals,  m_numberOfSubGrps, m_subGroupThresholdList, isComaa );

	cVarianceCalc::JasonPringSimpleArray( msgStr,   "Risk Groups Dependent Value Array" , leadingSpacesNum , arrayFlex, 
		&globals,  m_numberOfSubGrps, m_subGroupAverageDependent, isComaa );

	cVarianceCalc::JasonPringSimpleArray( msgStr,   "Risk Groups Performance Score Array" , leadingSpacesNum , arrayFlex, 
		&globals,  m_numberOfSubGrps, m_subGroupAdvncPErfScore , isComaa );

	isComaa = false;

	cVarianceCalc::JasonPringSimpleArray( msgStr,   "Risk Groups Sample Size Array" , leadingSpacesNum , arrayFlex, 
		&globals,  m_numberOfSubGrps, m_subGroupPopulationSize , isComaa );



}









void cProfileObject::PrfObjPrepareArraysToOrFromDisc(cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals)
{	
	char strMesage[1000];
	strMesage[0]=0;
	strcpy(strMesage, "Profile ID");//even if it is a real case iti does not hurt to put it in 
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	arrayFlex->WriteReadArrayInt(m_profileID, isWriteToArray ,  globals);
	 
	strcpy(strMesage, "Anchor ID");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	arrayFlex->WriteReadArrayInt(m_anchorID, isWriteToArray ,  globals);

	strcpy(strMesage, "number of profile population inclusion rules");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	arrayFlex->WriteReadArrayInt( m_inclusionRuleListSize, isWriteToArray, globals);

	if(!isWriteToArray)
	{
		if(m_inclusionRuleListSize > 0)
		{
			m_inclusionRuleList = new cVariableAndValueAndPoints[m_inclusionRuleListSize];
		}
	}
	for(int i = 0 ; i < m_inclusionRuleListSize ; i++ )
	{
		m_inclusionRuleList[i].VarValObjPrepareArraysToOrFromDisc(arrayFlex, isWriteToArray, globals); //cArrayFlex *& array
	}

	strcpy(strMesage, "size of research population");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayInt(  m_sizeOfResearchPopulation, isWriteToArray ,  globals);
	
	strcpy(strMesage, "size of profile population");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayInt(  m_sizeOfProfilePopulation, isWriteToArray ,  globals);

	strcpy(strMesage, "number of variables");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayInt(  m_numberOfVariables,isWriteToArray ,  globals);

	strcpy(strMesage, "profile dependent average");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayDouble(  m_profileDependentAverage, isWriteToArray,globals);

	strcpy(strMesage, "profile root performance");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayDouble( m_profileRootBasedPerformance  , isWriteToArray, globals);

	strcpy(strMesage, "number of odd ratio elements");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayInt( m_oddRatioPointsListSize, isWriteToArray ,  globals);
	if(!isWriteToArray)
	{
		if(m_oddRatioPointsListSize > 0)
		{
			m_oddRatioAlgoRates = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];
			m_adjustedPointRates = new cVariableAndValueAndPoints[m_oddRatioPointsListSize];
		}
	}

	for(int i = 0 ; i < m_oddRatioPointsListSize ; i++ )
	{ 
		strcpy(strMesage, "  {");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals);

		strcpy(strMesage, "  odd ratio algo element:");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
		m_oddRatioAlgoRates[i].VarValObjPrepareArraysToOrFromDisc(arrayFlex, isWriteToArray, globals);

		strcpy(strMesage, "  }");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals);

	}

	for(int i = 0 ; i < m_oddRatioPointsListSize ; i++)
	{
		strcpy(strMesage, "  {");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals);

		strcpy(strMesage, "    adjusted odd ratio element:");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
		m_adjustedPointRates[i].VarValObjPrepareArraysToOrFromDisc(arrayFlex, isWriteToArray, globals);

		strcpy(strMesage, "  }");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals);
	}

	strcpy(strMesage, "number of sub groups");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	arrayFlex->WriteReadArrayInt( m_numberOfSubGrps , isWriteToArray ,  globals);
	
	strcpy(strMesage, "scale mean");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	arrayFlex->WriteReadArrayDouble(  m_scaleMean, isWriteToArray, globals);

	strcpy(strMesage, "scale Std");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	arrayFlex->WriteReadArrayDouble(  m_scaleSD, isWriteToArray,globals);
 
	if(!isWriteToArray)
	{
		if(m_numberOfSubGrps > 0)
		{
			m_subGroupThresholdList = new double[m_numberOfSubGrps];
			m_subGroupAverageDependent = new double[m_numberOfSubGrps];
			m_subGroupPopulationSize = new int[m_numberOfSubGrps];
			m_subGroupPerformanceScore = new double[m_numberOfSubGrps];
			m_subGroupAdvncPErfScore = new double[m_numberOfSubGrps];
			m_subGrpBestMatchGapAvg = new double[m_numberOfSubGrps];
			m_meanDeltaProfSub= new double[m_numberOfSubGrps];
			m_sdDeltaProfSub= new double[m_numberOfSubGrps];
		}
	}
	
	strcpy(strMesage, "sub groups threshold array:");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	for(int i = 0 ; i < m_numberOfSubGrps; i++ )
	{
		arrayFlex->WriteReadArrayDouble( m_subGroupThresholdList[i],isWriteToArray,globals);
	}
	strcpy(strMesage, "sub group average dependent array");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,true);
	for(int i = 0 ; i < m_numberOfSubGrps ;i++)
	{
		arrayFlex->WriteReadArrayDouble( m_subGroupAverageDependent[i]  , isWriteToArray, globals);
	}
	int iii = 0;
	strcpy(strMesage, "sub group population size array:");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals,  true);
	
	for(int i = 0 ; i < m_numberOfSubGrps ;i++)
	{
		arrayFlex->WriteReadArrayInt( m_subGroupPopulationSize[i], isWriteToArray ,  globals);
	}
	strcpy(strMesage, "sub group performance score array");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	for(int i = 0 ; i < m_numberOfSubGrps ;i++)
	{
		arrayFlex->WriteReadArrayDouble(m_subGroupPerformanceScore[i], isWriteToArray, globals);
	}
	strcpy(strMesage, "sub group advanced performance score array and mean and sd of  delta:");
	arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
	for(int i = 0 ; i < m_numberOfSubGrps ;i++)
	{
		strcpy(strMesage, "  {");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals);

		strcpy(strMesage, "    subGrpBestMatchGapAvg:");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
		arrayFlex->WriteReadArrayDouble( m_subGrpBestMatchGapAvg[i], isWriteToArray,  globals);
		
		strcpy(strMesage, "    subGroupAdvncPErfScore:");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
		arrayFlex->WriteReadArrayDouble( m_subGroupAdvncPErfScore[i], isWriteToArray,  globals);
		
		strcpy(strMesage, "    meanDeltaProfSub:");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
		arrayFlex->WriteReadArrayDouble( m_meanDeltaProfSub[i], isWriteToArray,  globals);
		
		strcpy(strMesage, "    sdDeltaProfSub:");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals, true);
		arrayFlex->WriteReadArrayDouble( m_sdDeltaProfSub[i], isWriteToArray,  globals);

		strcpy(strMesage, "  }");
		arrayFlex->WriteReadArrayString(strMesage,  isWriteToArray, globals);

	}
	arrayFlex->Enter(isWriteToArray,globals.g_endOfLineInSign);

	//22 2 12 add read write for intervention
	 

 

/*
*****************************************************************************************************
////////////////////these aribale are in the profile object but will not be writen to disc////////////////////////////
	
	cProfileObject* m_rootProfile;//will be complefed after read from file using another function. root itself will be 
	cProfileObject** m_childProfilePtrArr;//will be compelted after read using anothe method going through a ggraph
	int m_sizeOfChildPrfArr;//same
	int m_sizeOfResearchPopulation//not needed
	double** m_fullPopulation;//not needed

*****************************************************************************************************
/////////////these vairbles are also in the profile and are not writen to array/disc but will be added later/////
	
	int m_numberOFVariblesWithLogisticRegressionValues;
	cVariableAndValue* m_variablesAndLogRegValues;
	cInterventionObject * m_interventionObjectList;
	int m_interventionObjectListSize; /
	
	*/
}



bool cProfileObject::IsPatientIncluded(double* patientArr)
{
	for(int i = 0 ; i < m_inclusionRuleListSize ; i++)
	{
		int var = m_inclusionRuleList[i].m_variableIndex;
		if(patientArr[var] ==  m_inclusionRuleList[i].m_value)
		{
			int ssss = 0 ;//
		}
		else
		{
			return false;
		}
	}
	return true;
}




bool cProfileObject::IsSameInclusionList( cVariableAndValueAndPoints* inclusionSet,	int sizeOfInclusionSet)
{
	if(m_inclusionRuleListSize  == sizeOfInclusionSet )
	{
		if(IsInclusionsIncludedInProfileRules( inclusionSet, sizeOfInclusionSet))
		{
			return true;
		}
	}
	return false;
}

//		if( m_profileObjectPtrList[i]->IsInclusionsIncludedInProfileRules(newVarValList,size))//// 

bool cProfileObject::IsInclusionsIncludedInProfileRules(cVariableAndValueAndPoints* inclusionSet,	int sizeOfInclusionSe)
{
	bool isSub = true;
	for(int i = 0 ; i < sizeOfInclusionSe ; i++)
	{
		if(! IsVarValIncluded(inclusionSet[i]))
		{
			isSub = false;
		}
	}
	return isSub;
}


 
bool cProfileObject::IsVarValIncluded(cVariableAndValueAndPoints &varVal)
{
	for(int i = 0 ; i < m_inclusionRuleListSize   ; i++)
	{
		if(m_inclusionRuleList[i].IsEqualObject(  varVal ))
		{
			return true;
		}
	}
	return false;
}


	cStringAndIntDupCheck::cStringAndIntDupCheck()
	{
		m_size = SIZE_OF_PATIENT_STR_DUPLICATION_ARR;//
		m_arr = new bool[m_size];
		for(unsigned int i =0;i< m_size ; i++)
		{
			m_arr[i]=false;
		}
	}
	cStringAndIntDupCheck::~cStringAndIntDupCheck()
	{
		delete []m_arr;	
	}
	bool cStringAndIntDupCheck::IsExist(char* str, unsigned int num)
	{
		unsigned int hash = cHashObjectArray::Hashfunction( str,  m_size );
		unsigned long temp = hash * num;
		unsigned int ret = ((unsigned int( temp)) % m_size);
		return m_arr[ret];
	}
	void cStringAndIntDupCheck::SetExist(char* str, unsigned int num)
	{
		unsigned int hash = cHashObjectArray::Hashfunction( str,  m_size );
		unsigned long temp = hash * num;
		unsigned int index = ((unsigned int( temp)) % m_size);
		m_arr[index] = true;
	}


	void  cCalibrationContextObj::ConvertToPostRawPredictions(double* predictionArr, double* rawPredArr, int size)
	{
		for(int  i = 0 ; i < size; i++)
		{
			int index = cProfileObject::GetSubGrpIndex(rawPredArr[i],m_grpsThres,  m_numOfGrps );
			double pred = m_grpsAvgArr[index];
			predictionArr[i] = pred;
		}	
	}



	void cCalibrationContextObj::PrepareCalibrationElements(double* predArr,double* depArr, int size, cGlobals &globals)
	{
		bool* isIn = new bool[size];
		for(int i = 0 ; i < size ; i++)
		{
			isIn[i] = true;
		}
	//	double threshArr[100];
		cProfileObject::CalculateThresholds(m_grpsThres , m_numOfGrps, predArr,isIn,size);

		double profileAvgDep = 0.0;
		cProfileObject::CreateAvgDepSubGrps(NULL,m_grpsAvgArr,m_grpsThres ,m_grpPopSize, profileAvgDep, m_numOfGrps,predArr,depArr, isIn, size,  globals);
	 
		delete [] isIn;
		isIn= NULL;
	}





 


/*
	static void CreateStringWithQuotesAndIntegerAndColunAndSquareQuotes(
				char* msgStr, char* str, int integer, int leadingSpacesNum )
	{
		int inLen = strlen(strIn);
		int movingIndex = 0;
		for(int x = 0 ; x< leadingSpacesNum ; x++)
		{
			strOut[movingIndex++]=' ';
		}
		strOut[movingIndex++]='"';
		for(int i = 0 ; i < inLen ; i++)
		{
			strOut[movingIndex++] = strIn[i];
		}
		strOut[movingIndex++]='"';
	
	}
	*/	
