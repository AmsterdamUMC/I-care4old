#include "cSimilarityFormula.h"
#include "cProfileTarget.h"
#include "TargetSort.h"
#include "cRgression.h"
#include<string.h>
#include <math.h>
#include "math.h"
#include <stdlib.h>




cGlobals::cGlobals()
{
	//paragraph aalytics parametres 
	g_endOfParagraphOutSign = '^';//'\n';
	g_endOfParagraphInSign = '^';
	g_isRemoveExtraSpaces= false;
	strcpy(	g_inputFileString,"paragraph_data.txt");
	strcpy(g_outputFileString, "significant_sub_paragraphs.txt");
	//the following will have a achance to get overrised by the function that reads metadata configuration. that will now only be read during
	//profiling applicationn, nnot paragraph application. for p aragrph these defaults are what being used
	g_isToEnterRealTimeEndlessLoop = 'Y';
	g_isToConductPerformanceTests = 'Y';
	strcpy(g_patientTestFilePath,"paragraph_test_file.txt");
	strcpy(g_performanceReportFilePath,"outReport.txt");// "outReport.txt");//
	strcpy(	g_patientRealTimeFilePathIn,"queryFileIn.txt");
//	strcpy(g_patientRealTimeFilePathIn, "paragraphQueryFileIn.txt");//"queryFileIn.txt");//
	strcpy(g_patientRealTimeFolderPathOut, "paragraphOutQueryFolder//");//"");//
	strcpy(g_readwriteArraFlex, "readWriteArrayFlexFile.txt");
	
	
	//general signes
	g_endOfLineInSign = '\n';
	g_endOfLineOutSign = '\n';
	g_delimiter = 9 ; // 9 is TAB

//APPLICATION TYPE CONTROL	5 17 23
	//g_applicationType = 'B';
	g_applicationType = 'B';//10 1 23

	g_minSampleSizeIngridient =  90; //we set 3 times 60 to be our actual 
	g_minSampleSizeWhole = 170;//g_minSampleSizeIngridient * 5;//
	strcpy( g_metaFilePath, "metadata.txt");
	strcpy(  g_internalPerformanceReportFilePath,  "internalPerformanceReport.txt");

	strcpy(g_manuelPhrasesFilePath, "manualPhrasesInputFile.txt");




///PARAMETERS THAT ARE CONTROLLED BY THE "metadata.txt" CONFIGURATION FILE 
//first getting initielize these and later they will get their value from the configuraito file	
	//profiling definitions default
	//g_isToEnterRealTimeEndlessLoop = 'N';//'N' or 'n', vs. 'Y' or 'y'. Y will  mean that after geetting the calibration objects up we enter
	//a waiting mode for a potential search api, dependds on what api we open in the future
	 //same, here to run the set of tests and print perofmrnace tables to file
	g_profileBuildMode = 'A';//g_profileBuildMode = 'A';
	//12 2 22 *     add versions of data, develop a tool to split a input to learning, calibration and test
	strcpy(	g_patientLearningFilePAth,"");// "data.txt");
	strcpy(g_patientCalibrationFilePath,"");// "data.txt");//need to have a differnet a much smaller file. can be a customer related file 
	//strcpy(g_patientTestFilePath,"");// "data.txt");//need to be also not the same learning file, a separate and maybe smaller than data.txt
	 
	
	g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE = 0;//2 00;//should be 1500-2000 
	g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE= 0;//has to be 0 for the paragraph applicaiton so we can sttand emply buckets
	g_NUMBER_OF_CALIBRATION_GRPS = 0;//10;
	g_minSampleToContinueRecursive=0;//below this amount we DONT go recursive but stop 
	g_maxNumOfLevelsToContinueRecursive=0;//above this number we DONT continue recusrive but go to profiles
	g_capOfForkingPredictiveRecursive=0;
	g_highestRecurSiveLevelWithFork=0;
	g_MIN_SIZE_OF_CATEG_FOR_STRETCH = 0;//250;
	g_IS_WITH_LONG_STRETCH_PERF_PROCESS = false;

	//other initieliztions
	m_meanDepValue=0.0;
	m_sdDepValue=0.0;
	m_globHist = new cHistogram;
	m_globHistWithSizeConsid = new cHistogram;


	

	/////////////// API - HARD CODED TO STAY PARAMETERS VALUES/////////////////////////////////////////
//paragraph projet   
	g_MAX_NUM_OF_PATIENTS_FIRST_RUN_PARAG = 2020;//3 3 23 *** *
//profile proejct
	g_PROFILE_LIST_MAX_SIZE = 50000;//max number of  profiles to create eventually
	g_PATIENT_LINES_INPUT_LIST_MAX_NUMBER = 1000000;// g_MAX_NUM_OF_ITERATIONS  75
	g_MAX_VALUE_OF_ABS_SYMETRIC_ODD_RATIO = 10.0; //
	g_NUM_OF_SUB_GRPS = 5;
	g_MAX_NUM_OF_ITERATIONS = 75 ; //6 9 23 //20
	
	g_sizeAndUpToKeepREcursive = 150000;
	g_MAX_LEVELS_IN_PROFILING_EVOLUTION=5;
	
		g_STRENGTH_MULT_OF_LONG_STRETCHED_PROFILE = 100.0;
	g_MIN_ODD_RATIO_TOJUSTIFIY_OPENING_CHILD_PROFILE = 0.05;
	//g_IS_WITH_EVOLUTION_ON_GOING_PERF_TESTING = false;

	g_IS_PERF_WEGIHT_FOR_BEST_MATCH_MERGE_POWER_BY_2 = true;
	g_IS_ADVANCED_PERF_FOR_GET_BEST_MATCH = true;
	g_IS_ADVANCED_PERF_FOR_GET_BEST_MATCH_EVOLUTION = true ; //during and after creating profiles, will select best match based on stetch score and see the stretch score debeloped
	g_IS_TO_DELETE_IS_IN_PROFILE_FOR_MEM_OPTIMIZATION = true;//12 2 22 *** 
	
	g_NUM_OF_CATG_PERCENTILE_MERGE  = 10;
	g_SIZE_OF_PROFILE_SIZED_GROUP_FOR_COMPETING_EVOLUTION = 100;
	g_RATIO_OF_LARGE_GAP_TO_CHABGE_PROFILE_GRP = 0.85;
	g_NUM_OF_TEST_TYPES = 5;
	g_ONLY_ROOT_PREDIC_MODE = 0;
	g_ONLY_WP3_EXACT_MULTI_VALUE_PATN_CATEGORY = 1;
	g_ONLY_WP3_INCLUDED_IN_PATN_CATEGORY = 2; //here we can include all profiles thatt have at leasat the WP3 categoy as filter, among potentialy other inclusion critera
	g_ONLY_NON_WP3_PROFILES = 3;
	g_ALL_PROFILES_CANDIDATES = 4;


}

cGlobals::~cGlobals()
{
	delete m_globHist;
	m_globHist=NULL;
	delete m_globHistWithSizeConsid;
	m_globHistWithSizeConsid=NULL;
}



// ***************************************************************************************
/////////////////////////////////////cResearchObject//////////////////////////////////////////////
// **********************************************************************************




cResearchObject::cResearchObject(InputVariablesPackageForResearchObj* inputVarObj)
{
	InitializeObject(inputVarObj->m_profileListMaxSize, inputVarObj->m_numberOfSubGrps, inputVarObj->m_thresholdForTerminalProfile,
		inputVarObj->m_numOfRegrEleents,	inputVarObj->m_varValPointsRegWghArr,	inputVarObj->m_guidedInclusionsRuleList, 
		//12 2 22 see that m_isIntervention and m_indexOfPropIntervention are part of tohe research object input and how it is used . see that it is also filled 
		//befoer this call 
			inputVarObj->m_guidedInclusionRuleListSize, inputVarObj->m_isPredictive,  inputVarObj->m_isIntervention,
			inputVarObj->m_indexOfPropIntervention, inputVarObj->m_numberOfVariables);
}




void cResearchObject::DFGHJ(double* threshArr ,  double* avgDepArr , int* cntArr,double* predArr, double* centerPredArr,
	int *grpIndexArr ,double* sumAdvancedPErfWghts,
		bool* isPersonIn,  	cResearchDataObj* reschDatObj, cGlobals* globals, int numOfPerformanceSubGrps, 
		cProfileObject** profileListPtr,int  profileListSize, int modePRed, bool isWithExtremeDimension ,
		bool isThisCaseOfAnchorUniverseIn , bool isWithFineTuning, bool isWithMinAdvancedPerfWeight)
{
	//3 15 24 when i have 7024 profiles than i ican go and find for each if tehre is a copy if it. 

	//	bool* isPersonIn = NULL;
		//researchObj->
	//	bool isWithFineTuning = true;//7 11 23 * 1 test this . was false now it is tr ue  //6 23 23 7 5 23 take it out to control from main function
		//6 23 23 **** use PredictionTasks as a way to send one person at a time and get the get mix of profiles as input into a predition output
		//then i can use that output to calibrate it given that each anchor is assicated with a set of calibrationn objects as here. needs to save these in disk
	bool isToAllowIncludingZeroWeight=true;	
	bool isTargetProfileUsed=false;
	PredictionTasks(isTargetProfileUsed,  predArr,  centerPredArr, sumAdvancedPErfWghts,reschDatObj->m_twoDimArray,  isPersonIn,  
						reschDatObj->m_numOfItems, reschDatObj->m_sizeOfItem ,  globals,
					  profileListPtr,  profileListSize, isWithExtremeDimension,	 isWithFineTuning, isThisCaseOfAnchorUniverseIn,
					  isToAllowIncludingZeroWeight, isWithMinAdvancedPerfWeight, -1);

		//int numOfPerformanceSubGrps = globals->g_NUMBER_OF_CALIBRATION_GRPS;
		//double* threshArr = new double[numOfPerformanceSubGrps];
		//double* avgDepArr = new double[numOfPerformanceSubGrps];
		//int* cntArr = new int[numOfPerformanceSubGrps];
		//6 13 23 call a  function fathers what doing already within the loop and perf tests.
		cProfileObject::CalculateThresholds(threshArr , numOfPerformanceSubGrps, 
										predArr,isPersonIn,reschDatObj->m_numOfItems);
		double depAvg = 0.0;
		cProfileObject::CreateAvgDepSubGrps(grpIndexArr, avgDepArr,threshArr ,cntArr, depAvg,
					numOfPerformanceSubGrps,predArr,reschDatObj->m_depArr, isPersonIn, 
													reschDatObj->m_numOfItems, *globals);

					
	
}

bool cResearchObject::IsGuidedParentExsist(double &val,double &sd,  cVariableAndValue varVal)
{
	val = 0.0;
	for(int i = 0 ; i < m_profileListSize ; i++)
	{
		if( m_profileObjectPtrList[i]->GetInclusionRuleListSize() == 1)
		{
			cVariableAndValueAndPoints obj = m_profileObjectPtrList[i]->GetInclusionRuleList()[0];
			if((obj.m_variableIndex == varVal.m_variableIndex) &&( obj.m_value == varVal.m_value))
			{
				val = m_profileObjectPtrList[i]->GetProfileDepAverage();
				sd = m_profileObjectPtrList[i]->GEtProfileSDofBucket();
				return true;
			}
		}		
	}
	return false;
}

  
//indexOfPrepenField isInrtervention  how do we get these used as part of the research object 
void cResearchObject::InitializeObject(int prifileListMaxSize, int numberOfSubGrps, int thresholdForTerminalProfile,
		int sizeOfLogisticRegressionArr,	cVariableAndValueAndPoints* logisticRegressionVarAndPoints,
			cVariableAndValue*  guidedInclusionsRuleList, 
			int guidedInclusionRuleListSize, bool* isPredictive, bool* isInrtervention, int* indexOfPrepenField, int numberOfVariables)//, char* filePAthReadwrite)
{
	m_prifileListMaxSize = prifileListMaxSize;
	m_numberOfSubGrps = numberOfSubGrps;
	m_profileObjectPtrList = new cProfileObject* [m_prifileListMaxSize];
	for(int i = 0 ; i < m_prifileListMaxSize ; i++)
	{
		m_profileObjectPtrList[i]= NULL;
	}
	m_profileListSize=0;
	m_rootProfile=NULL;

	m_thresholdForTerminalProfile= thresholdForTerminalProfile;

	m_logisticRegressionVarAndPoints = NULL;
	m_sizeOfLogisticRegressionArr=0;
	if(logisticRegressionVarAndPoints != NULL)
	{
		m_sizeOfLogisticRegressionArr = sizeOfLogisticRegressionArr;
		m_logisticRegressionVarAndPoints = new cVariableAndValueAndPoints[m_sizeOfLogisticRegressionArr];
		for(int i = 0 ; i < m_sizeOfLogisticRegressionArr ; i++)
		{
			m_logisticRegressionVarAndPoints[i] = logisticRegressionVarAndPoints[i];
		}
	}

	m_guidedInclusionRuleList = NULL;
	m_guidedInclusionsRuleListSize = 0;
//4 17 22 TO DO 2
	if(guidedInclusionsRuleList!= NULL)
	{
		m_guidedInclusionsRuleListSize = guidedInclusionRuleListSize;
		m_guidedInclusionRuleList = new cVariableAndValue[m_guidedInclusionsRuleListSize];
		for(int ii = 0 ; ii < m_guidedInclusionsRuleListSize ; ii++)
		{
			m_guidedInclusionRuleList[ii] = guidedInclusionsRuleList[ii];//
		}
	}
	
	int maxNumOfVariables = 1000;
	m_schemaArrr = new cVariableSchemaArr(maxNumOfVariables,numberOfVariables,isPredictive,NULL,0);
}


void cResearchObject::CalculateComparativePErfScoreInputTwoSubGrpSet(double* perfArr,
		double* subGrpsDepAvgSet, double* subGrpsReferecneDepAvgSet , int numOfSubGrps, double anchorMean)
{
	for(int x = 0 ; x< numOfSubGrps ; x++)
	{
		double absGap = cVarianceCalc::Abs( subGrpsDepAvgSet[x] - anchorMean );
		double absGatRef = cVarianceCalc::Abs( subGrpsReferecneDepAvgSet[x] - anchorMean );
		perfArr[x] = absGap - absGatRef;
	}
}

/*
for  a given inclusion rule set  / profile unique definition, the function returns if it is found alreadg, by checking across all prof list
*/
bool  cResearchObject::IsThisInclusionRuleSetExistNew(cVariableAndValueAndPoints* inclusionRuleSet, int size,
														cProfileObject** profileArr,int numOfProf)
{
	//return false; //3 17 24
	for( int i = 0 ; i < numOfProf ; i++)
	{
		//return if this incluion rule set/ profile, is same as this one profileArr[i]
		if( cProfileObject::IsSameInclusionRules(profileArr[i],inclusionRuleSet, size))//cVariableAndValueAndPoints* inclusionRuleSet, int size
		{
			return true;
		}
	}
	return false;

}

bool cResearchObject::IsProfileFound(cProfileObject** childProfArrr, int numOfProf , cProfileObject* profile)
{
	 
	for( int i = 0 ; i < numOfProf ; i++)
	{
		if(childProfArrr[i] != NULL && cProfileObject::IsSameInclusionRules(childProfArrr[i],profile))
		{
			return true;
		}
	}
	return false;
}






bool  cResearchObject::IsThisInclusionRuleSetExist(cVariableAndValueAndPoints* inclusionRuleSet, int size)
{
	for(int i = 0 ; i < m_profileListSize  ; i++)
	{
		if(m_profileObjectPtrList[i] != NULL)
		{

			bool isSame = IsEqualInclusionListNew(
				m_profileObjectPtrList[i]->GetInclusionRuleList(),m_profileObjectPtrList[i]->GetInclusionRuleListSize(), 
				inclusionRuleSet, size);
			if(isSame)
			{
				return true;
			}
		}
		else
		{
			int sdg=0;//6 7 23
			cout <<"empty pointer num \n";
			cout << i;
			cout << " \n";
		}
	}
	return false;
}
 

void cResearchObject::KeepRulesThatMakeUniqueExtendedRuleSet(
	cVariableAndValueAndPoints* inclusionRuleListFinalList, int &incListFinalSize, 
	cVariableAndValueAndPoints* inclusionRuleListInitiall, int incListSizeInitiall,
	cProfileObject* thisProfile, cProfileObject** profileArr, int profileNum)
{
	incListFinalSize = 0;
	int movingIndex = 0;
	//3 17 24 create a hash array with apping of randks rules of var and val to have quick elimination of  varValInclusionArr,  before
	//sending it to the heavy fuction IsThisInclusionRuleSetExistNew



	for(int i = 0 ; i < incListSizeInitiall; i++)
	{
		cVariableAndValueAndPoints tmp = inclusionRuleListInitiall[i];

		cVariableAndValueAndPoints* varValInclusionArr=NULL;
		int size=0;
		bool isMustBeRuleMatchs = false;
		bool isUniqueSetOfRules =  CreateInclusionSetForNextLevel(isMustBeRuleMatchs, varValInclusionArr, size,   thisProfile,tmp);
		if(isUniqueSetOfRules)// && isMustBeRuleMatch) //6 9 23 
		{
			if( !(IsThisInclusionRuleSetExistNew( varValInclusionArr,  size, profileArr, profileNum)))
				//IsThisInclusionRuleSetExist(varValInclusionArr,size)))
			{
				inclusionRuleListFinalList[movingIndex++] = tmp;
			}
			else
			{
				int sssss=0;//need to see that we get here 3 16 24
			}
		}
		if(varValInclusionArr != NULL)
		{
			delete []varValInclusionArr;
			varValInclusionArr=NULL;
		}
	}
	incListFinalSize = movingIndex;
}
	


void cResearchObject::CompareProfilePerformanceToReferance( double* comparativePerfScoreArr , 
	double* absGapArrPerSubGrp, double* absGapArrReference, int numberOfSubGroups)
{
	for(int x = 0 ; x < numberOfSubGroups ; x++)
	{
		comparativePerfScoreArr[x] = absGapArrReference[x] - absGapArrPerSubGrp[x] ;
	}
}

 
bool cResearchObject::IsEqualInclusionListNew(cVariableAndValueAndPoints* varValArr1, int size1, 
								cVariableAndValueAndPoints* varValArr2, int size2)
{
	if( size1 != size2)
	{
		return false;
	}
	for(int i = 0 ; i <  size1 ; i++)
	{
		cVariableAndValueAndPoints varVal1 = varValArr1[i];
		bool varVAl1IsFoundInArr2 = false;
		for(int ii = 0 ; ii < size1 ; ii++)
		{
			cVariableAndValueAndPoints varVal2 = varValArr2[ii];
			if(varVal1.IsEqualObject( varVal2))
			{
				varVAl1IsFoundInArr2 = true;
			}
		}
		if(varVAl1IsFoundInArr2 == false) //we did not find varVal1 in anywhere in the varvalArr2
		{
			return false;
		}
	}
	return true;//if we did not end up in any varVal1 not found in arr 2, than here we say that these two are equal
}


  
   

void cResearchObject::UpdateVariableValuesPRevelance  ( cResearchDataObj* resarchDataObj)
	//double**  twoDimArr, int num)
{
	cVariableSchemaArr* obj = GetSchema();
	obj->UpdateSchemaWithVariableValuesPRevelance(resarchDataObj->m_twoDimArray , resarchDataObj->m_numOfItems);
}
		
void cResearchObject::AdjustRegresionListToSizeAndCreatePercentileObjectForRegre (
	  cPercentileCalculationModel*& regPredictiveModel, int numOFCategoriesForPercLogic,
	  cPercentileCalculationModel* rootOddPredictiveModel, cProfileObject* profile )
{
	cVariableAndValueAndPoints* tempVarVal = 
		new cVariableAndValueAndPoints[profile->GetOddRatioListSize()];
	int movingIndex = 0; 
	for(int x=0; x< m_sizeOfLogisticRegressionArr ; x++)
		//m_rootProfile->m_oddRatioPointsListSize ; x++)
	{
		int var = m_logisticRegressionVarAndPoints[x].m_variableIndex;
		double val = m_logisticRegressionVarAndPoints[x].m_value;
		if(rootOddPredictiveModel->IsVarValIncluded(var,val))
		{
			tempVarVal[movingIndex++] = m_logisticRegressionVarAndPoints[x];
		}
		else
		{
			int sssssss=0;
		}
	}
	for(int m = 0 ; m < profile->GetOddRatioListSize() ; m++)
	{
		int var = profile->GetOddRatioList()[m].m_variableIndex;
		double val = profile->GetOddRatioList()[m].m_value;
		if(! (cVarianceCalc::IsVarValExist( tempVarVal,movingIndex, var, val)))
		{
			tempVarVal[movingIndex].m_variableIndex = var;
			tempVarVal[movingIndex].m_value = val;
			tempVarVal[movingIndex].m_points = 0.0;
			movingIndex++;
		}
	}
	if(m_logisticRegressionVarAndPoints != NULL)
	{
		delete []m_logisticRegressionVarAndPoints;
		m_logisticRegressionVarAndPoints = NULL;
	}
	m_sizeOfLogisticRegressionArr = movingIndex;
	if(m_sizeOfLogisticRegressionArr > 0)
	{
		m_logisticRegressionVarAndPoints = 
			new cVariableAndValueAndPoints[m_sizeOfLogisticRegressionArr];
	}
	for(int m = 0 ; m < movingIndex ; m++)
	{
		m_logisticRegressionVarAndPoints[m] = tempVarVal[m];
	}


	
	regPredictiveModel = new cPercentileCalculationModel(profile, numOFCategoriesForPercLogic);
	regPredictiveModel->SetModelObjectArrayAndSize(
		m_logisticRegressionVarAndPoints, m_sizeOfLogisticRegressionArr) ;//; //add this model for schema to allow easy discount when having both
//the analytis are built based on the root profile population and the regression weights
	regPredictiveModel->Analytics();
 
	
}

bool cResearchObject::IsNewInclusionRuleProfile(cVariableAndValueAndPoints* newVarValList, int size)
{
	for(int i = 0 ; i < m_profileListSize ; i++)
	{
		if( m_profileObjectPtrList[i]->IsSameInclusionList(newVarValList,size))////IsSameInclusionList
		{
			 	return false;
		}
	}
	return true;
}

 
//11 28 22 add the performance part accoridng to latest toughts
bool cResearchObject::CreateChildToThisProfilePerInputVarVarListNew(cProfileObject*& childProfile,// double &parentbasedPerformance,
	int proifleID, cProfileObject* thisProfile, cVariableAndValueAndPoints* varValInclusionArr,  int sizeOfVarValObjSet, 
	cResearchDataObj* researchDataObj,	cPercentileCalculationModel* rootOddPredictiveModel,
	cPercentileCalculationModel*  regPredictiveModell, cGlobals &globals, cProfileObject* anchor, bool* isInContext)
{	
	bool isCreated = false;
//	parentbasedPerformance = 0.0;
	childProfile =	new cProfileObject(  this, proifleID,m_rootProfile,varValInclusionArr,sizeOfVarValObjSet,
		researchDataObj , anchor->GetProfileID(), anchor->GetIsInProfileArr());
	if(childProfile->GetProfilePopulationSize() < globals.g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE )
	{
		//11 3 22 check that delete has all deletion of arrays since this will happen a lot
		delete childProfile;
		childProfile=NULL;
	}
	else
	{
		isCreated = true;
		PRepareModelAndAdjustPErRootRegreMOdel(rootOddPredictiveModel, regPredictiveModell,childProfile , globals );
		childProfile->SetPerformanceToDefault( globals );//just to set to nutural before get the real calculation below
			
	/*	double* rootComparePerformance = new double[m_numberOfSubGrps];
		for(int s = 0 ; s< m_numberOfSubGrps ; s++)
		{
			rootComparePerformance[s] = 0.0;
		}
	//	ProfileComparativeReferencePerformacneTest(	rootComparePerformance, childProfile, thisProfile);
	//		double wghtedAvg = 0.0;
	//		double sumWghts = 0.0;
	//		for(int s = 0 ; s< m_numberOfSubGrps ; s++)
	//		{
	//			wghtedAvg += rootComparePerformance[s];
	//			sumWghts += 1.0;//consider replacing with bucket grp count if different
	//		}
	//		wghtedAvg /= sumWghts;
	//		parentbasedPerformance = wghtedAvg;

		delete []rootComparePerformance;
		rootComparePerformance = NULL;
		*/
	}
	
	return isCreated;
			
}



double cResearchObject::CalculateStreth(double &depVal, double* avgDepArr, int* cntArr, int numOfGrps)

{
	depVal=0.0;
	double sumWghts=0.0;
	for(int i = 0 ; i < numOfGrps ; i++)
	{
		double wgh = double(cntArr[i]);
		depVal += wgh *avgDepArr[i];
		sumWghts +=wgh;
	}
	depVal /= sumWghts;
	double avgStretch = CalculateStreth( avgDepArr,  cntArr, depVal,  numOfGrps);
	return avgStretch;
}

double cResearchObject::CalculateStreth(double* avgDepArr, int* cntArr, double depAvg, int numOfGrps)
{
	double avgStretch = 0.0;
	double sumwghts = 0.0;
	for(int i = 0 ; i < numOfGrps ; i++)
	{
		double wgh = double(cntArr[i]);
		avgStretch += wgh * (avgDepArr[i] - depAvg) * (avgDepArr[i] - depAvg);
			//(cVarianceCalc::Abs(avgDepArr[i] - depAvg));
		sumwghts += wgh;
	}
	avgStretch /= sumwghts;
//	avgStretch = pow(avgStretch , 0.5);
	return avgStretch;
}


//11 3 22  
//keep not more than maxNumOfNewChildernPerProfile and if not keeping need to DELETE profiles
//once selecting the group of profiles that stays, need to re distribute the proifleID so that the selected ones are sorted based on that profile ID
//and only the ones which stay get that profile ID
//output  - both thet childProfArray anda outVarValPts get filtered, sorted, afte keeping only the better ones based on score and not more than maxNumOfNewChildernPerProfile
void  cResearchObject::KeepRandomAndTopPerformingProfiles( cProfileObject**childProfArray,cVariableAndValueAndPoints* outVarValPts, int &childIncArrSize,   int maxNumOfNewChildernPerProfile, cProfileObject* thisProfile )
{
	double* scoreArr = new double[childIncArrSize];
	for(int i = 0 ; i < childIncArrSize ; i++)
	{
		double odd = outVarValPts[i].m_points;
		double absOddRatio = cVarianceCalc::Abs(odd);

		double perfAvg = 0.0;
		double sumWghts = 0.0;
		for(int x = 0 ; x < m_numberOfSubGrps ; x++)
		{
			double perf= childProfArray[i]->GetProfilePerformance(x);
			double wgh = double( childProfArray[i]->GetSubBucketCntArr(  x));
			perfAvg += perf * wgh;
			sumWghts += wgh;
		}
		if(sumWghts < 0.0)
		{
			perfAvg/=sumWghts;
		}
		perfAvg = cVarianceCalc::Max(perfAvg , 0.0);
		 
		double sizeReduction = childProfArray[i]->GetProfilePopulationSize()  / m_rootProfile->GetProfilePopulationSize() ;//thisProfile->GetProfilePopulationSize();
		scoreArr[i] = perfAvg * sizeReduction;//size reduction is smaller than 1 and the higher means less reduction and a better score.
	}

}

bool cResearchObject::CreateInclusionSetForNextLevel( bool &isMatchMustBeRule,
	cVariableAndValueAndPoints*& varValInclusionArr,	int &size,
	       cProfileObject* thisProfile, cVariableAndValueAndPoints &obj)
{
	bool isUniqueSetOfRules = true;

	int sizeOFThisProfileInclusionSet = thisProfile->GetInclusionRuleListSize();
	varValInclusionArr = NULL;
	size = sizeOFThisProfileInclusionSet + 1;
	varValInclusionArr=	new cVariableAndValueAndPoints[size ]; //+1 for each chid has one new var/val

	cVariableAndValueAndPoints other(obj.m_variableIndex, obj.m_value, obj.m_points);
	for(int ii = 0 ; ii < sizeOFThisProfileInclusionSet ; ii++)
	{
		varValInclusionArr[ii] = thisProfile->GetInclusionRuleList()[ii];
		if(varValInclusionArr[ii].IsEqualObject(other))
		{
			isUniqueSetOfRules  = false;
		}
	}
	varValInclusionArr[sizeOFThisProfileInclusionSet] = obj;

	//isMatchMustBeRule = (m_guidedInclusionsRuleListSize == 0); // if no must be thn we do have a match
	 
	isMatchMustBeRule = false;
	/*if(m_guidedInclusionsRuleListSize > 0)//6  13 23 heck
	{
		isMatchMustBeRule = false;
		for(int x = 0 ; x < size ; x++)
		{
			cVariableAndValueAndPoints obb = varValInclusionArr[x];
			cVariableAndValue varVAl(obb.m_variableIndex, obb.m_value);
			for(int y = 0 ; y < m_guidedInclusionsRuleListSize; y++)
			{
				if(m_guidedInclusionRuleList[y].IsEqualObject(varVAl))
				{
					isMatchMustBeRule = true;
				}
			}
		}
	}*/

	return isUniqueSetOfRules;
}

 

void  cResearchObject::CreateChildProfileArr(
	cProfileObject** childProfArrr  ,  cProfileObject* thisProfile,  cVariableAndValueAndPoints* varValPts , int numOfObjects,
	cResearchDataObj* researchDataObj, 	cPercentileCalculationModel* rootOddPredictiveModel,
	cPercentileCalculationModel* regPredictiveModell,  cGlobals &globals , cProfileObject* anchor)
{
	//numOfAddedPoteChildren=0;

	for(int g = 0 ; g < numOfObjects ; g++)
	{
		cVariableAndValueAndPoints* varValInclusionArr=NULL;
		int size=0;
		bool isMustBeRuleMatchs = false;
		bool isUniqueInclusionRuleSet = CreateInclusionSetForNextLevel(isMustBeRuleMatchs, 
					varValInclusionArr, size,   thisProfile, varValPts[g]);
		if(!isUniqueInclusionRuleSet)
		{
			int sdg = 0 ; //should not be here since the input for this function is alreadyr validated to be unique inclusion set
		}
		cProfileObject* childProfilee = NULL;
		double parentbasedPerformance =0.0;	
		//it will not crate a child if the size is too small
		if(CreateChildToThisProfilePerInputVarVarListNew(childProfilee, 	m_profileListSize + g,
			thisProfile,varValInclusionArr,	size ,   researchDataObj,	rootOddPredictiveModel,
			regPredictiveModell,  globals, anchor,anchor->GetIsInProfileArr() ))
		{
		//	if( g>0 && IsProfileFound(childProfArrr, g-1 , childProfilee))
		//	{
		//		int iiiii=0;
				//if reached here means that still smthig not right
		//	}

				//delete childProfilee;//3 13 24
				//childProfilee=NULL;
				//childProfArrr[g]=NULL;
			//}
			//else
			//{
			childProfArrr[g]=childProfilee;	
			//}		
		}
		else
		{
			childProfArrr[g]=NULL;
		}		
		 
		delete []varValInclusionArr;
		varValInclusionArr = NULL;
	}
}






//use the proile candidate frmo the list and check to take the ones with :
//higihest size/sample 
//highest per root performance
//highest in the multipication of profie size and performance 
//we can do 1 1 1 or x x x and return how many and not more than maxThisProfileObjs
void cResearchObject::SelectThisProfileIndexesFromAllIndexes(bool* isSelArr, 
	cProfileObject** profileObjectPtrList,  int profileListSize,  int maxThisProfileObjs)
{
	int topPerCategpr= maxThisProfileObjs/3;
	int numOfBigSize = topPerCategpr;
	int numOfPerformnigSize = topPerCategpr;
	int numOfCombination = maxThisProfileObjs -numOfBigSize - numOfPerformnigSize ;

	///get top from each categoy see we do not have an overlapp andn remove in such case
}

bool cResearchObject::AddPotetialChildren(cProfileObject**	poternList, cVariableAndValueAndPoints* outVarValPts  ,
			double* perfArr  ,  double* percOfChildSizeFromParent,	int &indexOfFirstEmptrySpot,
			int maxChildrenToCollect, int potentialChildMaxSize)
{
	//indexOfFirstEmptrySpot is the current next potion to fill and will get updaed wifh each time so caller know
	//do not let t his index reach . the value when returning can be only one less, so if max size is 5 the index of first
	//emply spot is 4 can still be a indext o fill in the potenList, but if we are asked to fill maxChildrenToCollect we may have to 
	//stop and not able to do all if need to step on that index betond limit. return true if filled all and false if less
	return false;

}
			
	

void cResearchObject::IdentifyEachProfileWithItsGroupsIdentfier( 
	int* profileSizedGrpIdentfier, int &numOfGroups,int maxSizeOfProfileGrp,  cGlobals &globals,
	cProfileObject** profArr, int profListSize	)
{
/*target us to give maxSizeOfProfileGrp so that if we select 3/4 winners from each grouop
and the size is 20 0 of one group than it means we select 1-2% each iteration from each group and overall*/
	int* profileSizeArr = new int[profListSize];// 
	for(int i = 0 ; i < profListSize ; i++)
	{
		profileSizeArr[i] = profArr[i]->GetProfilePopulationSize();
	}
	cVarianceCalc::BubbleSortLargeToSmall(profileSizeArr, profListSize);
	int maxNumberOfGrps = profListSize;//teoretical size just since there cannot be more groups than profiles
	int* threArr = new int[maxNumberOfGrps]; //to allow then go over the proifles and associate each with the right "sized" group
	for(int i= 0 ; i < maxNumberOfGrps ; i++)
	{
		threArr[i]=0;
	}
	int indexInThresArr = 0;//will add more threeshlds each time we face a reason to switch to the next group, (size or gap)
//	int lastGrpSize =profileSizeArr[0]; //since the profiles are sorted, the first one for sure is largest and will define the start
	//of the first sized gruop. since it is the root, if all first level cut too much it may be that the gruop will be of 1 item
	threArr[indexInThresArr] =profileSizeArr[0];
	//first threshld defins who enters the first group and we define from the threshld and up. the value lastGrpSize is adjuste
	//as we move along the profile list and set before  we move to a next indexInThresArr
	int accoumlatedNumOfProfilesThisGrp = 1;//so far we "manually" set the root to lead this first gruop and so far it is a 1 item grp
	for(int i = 1 ; i < profListSize ; i++)
	{//i want to change threArr[indexInThresArr] as we move beyond the num of items max or gap and then also increment the index
		if( 
			(profileSizeArr[i] <  (threArr[indexInThresArr] * globals.g_RATIO_OF_LARGE_GAP_TO_CHABGE_PROFILE_GRP))   //gap reason to swith grp 
					||
			(accoumlatedNumOfProfilesThisGrp >  maxSizeOfProfileGrp)
			//num of items per grouop would be above if iwe continue, in the first case it is above 
			//we enter , or before, and item i, which is this item is already set to be part of the next indexInThresArr  grp 
		  )	
		{//if either the count has reached or a gap has establshed than we need to open a new threshldls group
			//so first update the threshld to the i proifle which is the one that makes either the larger gap from the ffirst
			//of th is sied group, or the one that makes the count reach the max than 
			threArr[indexInThresArr++] = profileSizeArr[i-1];//threshld holds the last profile[i-1] size befoer this profile[i] one 
			threArr[indexInThresArr] =  profileSizeArr[i];//a new threshlld has created for the profile[i] size that trigger the change
			accoumlatedNumOfProfilesThisGrp =1;//the profile[i] size is now the first attempt befoe it might change  
		}
		else //want to keep the same group and do not change the 
		{
	 //one more profile enters the same group (do not change indexInThresArr)
			accoumlatedNumOfProfilesThisGrp++;		
			if( i == (profListSize - 1))
			{
				threArr[indexInThresArr] =  profileSizeArr[i];
			}
		}
	}
	//now if we had 5 proifles and the i = 1 created a new threshld, and the rest did not, we have one entry to the "if" and 
	//indexInThresArr = 1 and number of grpus is 2 and the numbre of threshlds is also 2 but the last is less active
	
	//int numOfThreshlds = indexInThresArr;
	numOfGroups = indexInThresArr + 1;

	for(int i = 0 ; i <  profListSize ; i++)
	{
		profileSizedGrpIdentfier[i] = -1;
		int size = profArr[i]->GetProfilePopulationSize();
		bool grpNumIsSet = false;
		for( int x = 0 ; (!grpNumIsSet ) && (x < numOfGroups) ; x++)
		{
			//looking if size is higher or equal to the first threshlds to make group index x, else move one
			if(size >= threArr[x])
			{
				profileSizedGrpIdentfier[i] = x; //x is group number.
				grpNumIsSet= true;
			}
		}
		if(profileSizedGrpIdentfier[i] == -1)
		{
			profileSizedGrpIdentfier[i] = numOfGroups-1;//should not be here. here it is a default of the last gruop bug need to debug if happen
		}
	}
		
	delete []profileSizeArr;
	profileSizeArr=NULL;
	delete []threArr;
	threArr=NULL;


}

//make sure to test the differnet winning alternative but if a winner candiadte is already won or is a terminal we do not even try
//11 28 22 define score of square gpas between a sub group bucket and the univese mean, in universe units of gaps from right or from left
//to the mean of universe (need to use the m_root ) for the winner abs i collect list of square of row odd ratio list with var val that the parent
//accoridng to the order of inclusion list is itelling us loking at the odd ratio at that parent profile 

void cResearchObject::FindWinnersFromDifferentTypes(int &indexOfWinnerLeft,	int &indexOfWinnerRight,  int &indexOfWinnerAbs,
	bool* isIn, bool* isAlreadyWon, bool* isTerminal, cProfileObject** profList, int numOfProfiles,  int maxRuleLength )
			
{
	double highProfileAbsOddPoints = 0.0;//-0.001;//let 0 win the best score when we have only root as our winner
	int indexOfHighAbsOdd = -1;
	for(int i = 0 ; i < numOfProfiles ; i++)
	{
		if(isIn[i] && (!isTerminal[i]) && (!isAlreadyWon[i]) && 
						(i != indexOfWinnerAbs ) && (i != indexOfWinnerLeft) && ( i != indexOfWinnerRight) )
		{
			int ruleLength = 	profList[i]->GetInclusionRuleListSize();
			if(ruleLength  <= maxRuleLength)
			{
				double sumOfAbsInclusionOdds =	profList[i]->GetSumOfAbsInclusionRulePoints();
				if( sumOfAbsInclusionOdds >= highProfileAbsOddPoints)
				{
					highProfileAbsOddPoints = sumOfAbsInclusionOdds;
					indexOfHighAbsOdd = i;
				}
			}
			else
			{
				int sdg=0;
			}
		}
	}
	if(indexOfHighAbsOdd >= 0)
	{
		indexOfWinnerAbs = indexOfHighAbsOdd;
	}
	double meanUniverse = m_rootProfile->GetProfileDepAverage();
	double lowProfileDep = 1000000;//just a high number
	int indexOfLowDepValue = -1;
	for(int i = 0 ; i < numOfProfiles ; i++)
	{
		if(isIn[i] && (!isTerminal[i]) && (!isAlreadyWon[i]) &&
				(i != indexOfWinnerAbs ) && (i != indexOfWinnerLeft) && ( i != indexOfWinnerRight) )
		{
			double depValue = profList[i]->GetProfileDepAverage();
			if(depValue < lowProfileDep)
			{
				lowProfileDep = depValue;
				indexOfLowDepValue = i;
			}		
		}	
	}
	//even if we found an indexx with a low dep, it could be that at some point the lowest
	//is still highr than mean universe . in this case i dont acept the profile as a left
	//winner. that is the reason I want to put the check of abs first so the indexx
	//does not have the Abs not appear
	if(indexOfLowDepValue >= 0)//  &&  (lowProfileDep < meanUniverse))
	{
		indexOfWinnerLeft = indexOfLowDepValue;
	}	
	
	double highProfileDep = 0.0;
	int indexOfHighDepValue = -1;
	for(int i = 0 ; i < numOfProfiles ; i++)
	{
		if(isIn[i] && (!isTerminal[i]) && (!isAlreadyWon[i]) && 
				 (i != indexOfWinnerAbs ) && (i != indexOfWinnerLeft) && ( i != indexOfWinnerRight)  )
		{
			double depValue = profList[i]->GetProfileDepAverage();
			if(depValue > highProfileDep)
			{
				highProfileDep = depValue;
				indexOfHighDepValue = i;
			}		
		}	
	}
	if(indexOfHighDepValue >= 0 )//&& (highProfileDep > meanUniverse))
	{
		indexOfWinnerRight = indexOfHighDepValue ;
	}
}

 
bool cResearchObject::CrerateNewChildProfilesToThisProfile(cProfileObject**& chldProfArr, int &numOfChildren,
	  cProfileObject*  thisProfile,  cPercentileCalculationModel* rootOddPredictiveModel,
	  cPercentileCalculationModel* regPredictiveModell, cResearchDataObj* researchDataObj,
	  InputVariablesPackageForResearchObj* inputVarObj, cGlobals &globals, cProfileObject* anchor,cProfileObject** profileArr, int profileNum)
{
	cVariableAndValueAndPoints* inclusionRuleListInitiall = NULL;
	int incListSizeInitiall = 0;

	//the list will incldue all options that are avaliabile frmo the meta file guidlinles, but minus var/val alredy part of thisProfile 
	//the purpose of these var/val objects is to add each var/val to the "thisProfile" inclusion list and to make a larger version by one, for each
	//new profile. these all profiles can be seen as siblings to this parent. each profile with more than one var/val in ithe inclusino set list
	//will have more than one parent, but these other parents will not be shared between all of thisProfile children
	cout<< "Before CollectAllVarValOptionswithNonZeroOdd \n";

	thisProfile->CollectAllVarValOptionswithNonZeroOdd(inclusionRuleListInitiall, incListSizeInitiall, inputVarObj  , globals);
	bool ret = false;
	chldProfArr=NULL;
	numOfChildren=0;

	cout<< "After CollectAllVarValOptionswithNonZeroOdd \n";

	if(incListSizeInitiall > 0)
	{//here means we had aat leasta one child that is one var/val longer than thisProfile inclusion set
		
		cVariableAndValueAndPoints* inclusionRuleListFinalList = new cVariableAndValueAndPoints[incListSizeInitiall] ;
		//remove options that  are already part off the profiles created so far among m_profileObjectPtrList and have 
		//inclusionRuleListFinalList get a subset of inclusionRuleListInitiall
		int incListFinalSize = 0; 
		cout<< "Before KeepRulesThatMakeUniqueExtendedRuleSet \n";
		KeepRulesThatMakeUniqueExtendedRuleSet(inclusionRuleListFinalList, incListFinalSize, 
											inclusionRuleListInitiall, incListSizeInitiall, thisProfile,profileArr, profileNum );
		cout<< "after KeepRulesThatMakeUniqueExtendedRuleSet \n";
		
		delete []inclusionRuleListInitiall;//dont need this anymore , only the final list
		inclusionRuleListInitiall=NULL;

		if(incListFinalSize > 0)
		{
			//change the functino CreatePot entialChildProfiles below to accept a chldProfArr  and outVarValPts and numOfChildren,
			//already with memery alocation in size of incListFinalSize which is cleaned already and not sure yet what to do wtih the performance
			//leave or the perrfomacne to later? try to alligh the effort of creation of model to the same form of creating the parietn
			//a list of incldino rules to just leave what is left
			numOfChildren = incListFinalSize; //numOfChildren is an output parameters
			chldProfArr = new cProfileObject*[numOfChildren];//chldProfArr is an output parameter and should not get deleted here but outside 
			for(int j = 0 ; j < numOfChildren ; j++)
			{
				chldProfArr[j]=NULL;
			}
			cout<< "Before CreateChildProfileArr\n";
			CreateChildProfileArr(chldProfArr  , thisProfile,  inclusionRuleListFinalList ,  numOfChildren,
					 researchDataObj,  rootOddPredictiveModel, regPredictiveModell,  globals, anchor );
			cout<< "after CreateChildProfileArr\n";
			ret = true;		 
		}
		delete []inclusionRuleListFinalList;
		inclusionRuleListFinalList=NULL;
	}
	return ret;
}




/*
	//sp->UpdateAdvancePerformance(1.0 ); //if stretch is 1.0 it is the max since it is a gap and highest stretch is
//	sp->UpdateAdvancePerformance(stretch - lastStretch );
//return stretch will be saved above as "lastStrech" to send next time this fucttion isi called. 
void cResearchObject::UpdtePredictionArrAndCalculatePerformanceStretch(double &stretch, 
	double* evolutionPredictionArr, int arraySize,bool* isIn,  
	cResearchDataObj* researchDataObj, cGlobals &globals, int numOfStretchCategories)
{
	
	double* predictionArr = new double[arraySize];
	double* predictionWithInArr = new double[arraySize];
	double* predictionWithoutInArr = new double[arraySize];
	for(int index = 0 ; index < arraySize ; index++)
	{
		predictionArr[index] = 0.0;
		predictionWithInArr[index] = 0.0;
		predictionWithoutInArr[index] = 0.0;
		if((isIn == NULL ) || isIn[index] )//5 26 23 change to if isn==NULL || isIn[index][x]
		{
			evolutionPredictionArr[index] = 0.0;//when it is 0.0 the predict will take the effort to calcuate new
		}
	}
	double avgDepArrLocal[100];
	int cntArrLocal[100];
	double depAvgLocal = 0.0;
	 
	//gap between average and extreme who are with 0.0-1.0 of values
	bool isWithCalibration = false;//here this is a performance testing, no need for calibration
	bool isAdvancedPerfGetbEstMatch = true;
	int interventionFieldForPredictionVariations= -1;//12 2 22 add some way to get to an intervention API from the user request API
	
		
	cPredictionContextObj** predictionContextObjArray= NULL;
	int* sizeOfPredContObj=NULL;
	//5 26 23 nly have to call this first time, later for each profile[index][x] i can only
	//just replace the sub group instead, no need to prediction
	PredictPatientSetAndGe tPErformanceELemets( predictionArr,  predictionWithInArr,  predictionWithoutInArr,
		 predictionContextObjArray, sizeOfPredContObj,  avgDepArrLocal, cntArrLocal, depAvgLocal, researchDataObj->m_twoDimArray,
		researchDataObj->m_depArr, arraySize, researchDataObj->m_sizeOfItem,	NULL,  globals.g_ALL_PROFILES_CANDIDATES,
		isWithCalibration, numOfStretchCategories, evolutionPredictionArr,  
		isAdvancedPerfGetbEstMatch,   interventionFieldForPredictionVariations, globals  );
	stretch = Calcul ateStreth(avgDepArrLocal, cntArrLocal,
		depAvgLocal, numOfStretchCategories);
							
	for(int index = 0 ; index< arraySize ; index++)
	{
		evolutionPredictionArr[index] = predictionArr[index];
	}
	delete []predictionArr;
	predictionArr = NULL;
	delete [] predictionWithInArr;
	predictionWithInArr=NULL;
	delete []predictionWithoutInArr;
	predictionWithoutInArr=NULL;

							
}
*/


void cResearchObject::PredictionAndCalculatePerformanceStretch( double &anchorDepForBestMatch, double* threshArr ,double* avgDepArr,	
	int* cntArr,	double &depAvg , 
	double* predictionArr,double* predictionWithInArr  , double* predictionWithoutInArr,   int arraySize,bool* isIn,  
	cResearchDataObj* researchDataObj, cGlobals &globals, int numOfStretchCategories, bool isWithFineTuning,
	 bool* isPersonIn,  double profSubDepAvgTpForce, bool isStragithPRed)
{
	if(isPersonIn == NULL)
	{
		for(int index = 0 ; index < arraySize ; index++)
		{
			predictionArr[index] = 0.0;
			predictionWithInArr[index] = 0.0;
			predictionWithoutInArr[index] = 0.0;
		}
	}

	depAvg = 0.0;
	 
	//gap between average and extreme who are with 0.0-1.0 of values
	bool isWithCalibration = false;//here this is a performance testing, no need for calibration
	bool isAdvancedPerfGetbEstMatch = true;//5 31 23 chek
	int interventionFieldForPredictionVariations= -1;//12 2 22 add some way to get to an intervention API from the user request API
	
	cPredictionContextObj** predictionContextObjArray= NULL;	
	int* sizeOfPredContObj=NULL;
	//5 26 23 nly have to call this first time, later for each profile[index][x] i can only
	//just replace the sub group instead, no need to prediction
	PredictPatientSetAndGetPErformanceELemets(  anchorDepForBestMatch, predictionArr,  predictionWithInArr,  predictionWithoutInArr,
		 predictionContextObjArray, sizeOfPredContObj,  threshArr, avgDepArr, cntArr,
		 depAvg, researchDataObj->m_twoDimArray,
		researchDataObj->m_depArr, arraySize, researchDataObj->m_sizeOfItem,	NULL,  globals.g_ALL_PROFILES_CANDIDATES,
		isWithCalibration, numOfStretchCategories, NULL,  
		isAdvancedPerfGetbEstMatch,   interventionFieldForPredictionVariations, globals,
		isWithFineTuning,  isPersonIn, profSubDepAvgTpForce,isStragithPRed );
						
	
	if(false)
	{
	/*		PredictPatientSetAndGetPErformanceELemets(  anchorDepForBestMatch, predictionArr,  predictionWithInArr,  predictionWithoutInArr,
		 predictionContextObjArray, sizeOfPredContObj,  threshArr, avgDepArr, cntArr,
		 depAvg, researchDataObj->m_twoDimArray,
		researchDataObj->m_depArr, arraySize, researchDataObj->m_sizeOfItem,	NULL,  globals.g_ALL_PROFILES_CANDIDATES,
		isWithCalibration, numOfStretchCategories, NULL,  
		isAdvancedPerfGetbEstMatch,   interventionFieldForPredictionVariations, globals,
		isWithFineTuning, true,isApplyDeltaRangeRestic , isPersonIn, profSubDepAvgTpForce );*/
	}
	
	
	
	
	
	
	
	
	if(predictionContextObjArray != NULL)
	{
		for(int i = 0 ; i < arraySize ; i++)
		{
			if(predictionContextObjArray[i] != NULL)
			{
				delete []predictionContextObjArray[i];
			}
		}
		delete []predictionContextObjArray;
		predictionContextObjArray = NULL;
		delete []sizeOfPredContObj;
		sizeOfPredContObj=NULL;
	}
	

							
}


double cResearchObject::XYZW123(
	double &meanDelta ,	double &sdDelta,
	double* updPredArr , double* predArrB4, bool* isIn,  
	cResearchDataObj* researchDataObj, double*	thrArr, double* avgDepArr, 
	int* cntArrBefore, double depAvg,  int numOfStretchCategories,  cProfileObject* sp, int subGrpIndex)
{//6 11 23 two things to check, the line below, and the power of both complex and adnaed performance scores, 
	double avgAnchor=0.0;
	double sdAnchor=0.0;
	sp->GetDepAverageOfMustBeParentProfile(avgAnchor,sdAnchor, m_guidedInclusionRuleList, m_guidedInclusionsRuleListSize, this);//
	depAvg = avgAnchor;
	double ret = 0.0;
	int numOfItems = researchDataObj->m_numOfItems;
	int numOfElements = researchDataObj->m_sizeOfItem;
	double* depArr = researchDataObj->m_depArr;
	double** predArr =  researchDataObj->m_twoDimArray;
	double* deltaArr = new double[numOfItems];
	double avgPerf = 0.0;
	int count = 0;
	for(int i = 0 ; i < numOfItems; i++)
	{
		deltaArr[i]=0.0;
		if(isIn[i])
		{
			
	//get the actual points to then use threshlds for ratio
			double sumPnt =  sp->CalclaterSumAdjusteddPnts(researchDataObj->m_twoDimArray[i],
						numOfElements,	sp->GetAdjustedOddRateArr(), sp->GetOddRatioListSize());
			int subGrpIndex = sp->GetSubGrpIndex( sumPnt,  sp->GetThresholdArr(), GetNumberOfSubGrps() ) ;
			double ratioDepPerPred = 0.0;
			//double ratioPredPerDep = 0.0;
		//	double pred = sp->GetSubGrouopAvgDepArr[subGrpIndex];
			//5 31 23  this need to come from the above 20 buckets and not othe sp 5 buvkets. 
		 
			//	sp->CalclateRatioDepDeltaPerPredScoreDelta(ratioDepPerPred,
			//	researchDataObj->m_twoDimArray[i] , numOfElements);
			//ratio will say how much an average dep moves when  sumPnt is moving. for that need the average 
			//sum points in a bucket
			//sp-> 
			ratioDepPerPred = 1.0;//5 31 23 temporary
			deltaArr[i] = updPredArr[i] - predArrB4[i];
			//how much need to change the dep for given predDelta
			
			int indexOrSet = cProfileObject::GetSubGrpIndex(predArrB4[i],thrArr,numOfStretchCategories);
			if(indexOrSet >= 0)
			{
				//the value of the dep or avg of one of the 50 groups from an input, seleced using the index or set
				double baseStretcedhDepBucket = avgDepArr[indexOrSet];
				double depDelta = deltaArr[i] * ratioDepPerPred;
				double virtualDepBucket = baseStretcedhDepBucket  + depDelta;
				virtualDepBucket = cVarianceCalc::Max(virtualDepBucket, 0.0);//in case delta would be leading throug 0.0
				//if adding weighted perf, or even having all delta using certain sub profile stronger, i get a virtual dep bucket
				//into whicih the elemet has shifted across the input stretcedh buckets
				//first funtion i need to caclaute how much the base stretched bucket has chanced ints dep avg value
				double middleBetwenBaseAndVirtual = (baseStretcedhDepBucket + virtualDepBucket)/2.0;
				//assume change in perf take one elment from base bucket to another
		 		double updatedBaseBucket =CalculateUpdatedBucketTakingOutOneSpecificItemIandGettingInProbabilityBetweenItem(
					baseStretcedhDepBucket, researchDataObj->m_depArr[i] , middleBetwenBaseAndVirtual);
							
				double updatedVirtualBucket = CalculateUpdatedBucketAddingInOneSpecificItemIandTAkingOutProbalBetweenItem( 
							virtualDepBucket, researchDataObj->m_depArr[i] , middleBetwenBaseAndVirtual);
				double baseSqureGap =     (baseStretcedhDepBucket - depAvg)  * (baseStretcedhDepBucket - depAvg);
				double baseUpdatedSqrGap =    (updatedBaseBucket - depAvg)  * (updatedBaseBucket - depAvg);
				double virSqrGap =    (virtualDepBucket - depAvg)  * (virtualDepBucket - depAvg);
				double virUpdSqrGap =    (updatedVirtualBucket - depAvg)  * (updatedVirtualBucket - depAvg);
				double perf =    baseUpdatedSqrGap - baseSqureGap + virUpdSqrGap - virSqrGap;
					//(baseSqureGap + virSqrGap) -(baseUpdatedSqrGap + virUpdSqrGap );
				if(perf > 0.0)
				{
					int sdg = 0;
				}
				avgPerf += perf;
				count++;
			}
		}
	}
	if(count > 0)
	{
		avgPerf /= count;
	}
	meanDelta = 0.0;
	sdDelta = 0.0;
	double* wghArr = new double[numOfItems];
	for(int i = 0 ; i < numOfItems ; i++)
	{
		wghArr[i]=0.0;
		if(isIn[i])
		{
			wghArr[i]=1.0;
		}
	}
	cVarianceCalc::CalculateMeanAndSD(meanDelta,sdDelta,deltaArr,wghArr, numOfItems);
	//use subGrpIndex to get ratio
	/*
	get the bucket index
	 

	for every is in item, 
	  -get the "bucketIndex" based on input thr array of the original prediction predArrB4
	  -calcualte "ratio" = depAvgDelta / prediDelta , based on up to 2 buckets left and right if exist
	  -calcalte a directional prediction delta which is the updPredArr[i] - predArrB4[i]
	  -crearte virtualBucketValule (left or right of bucketIndex avgDepVal) based  pred delta and ratio
	  -calculate a new avg bucketIndex using assumpitno of 100 count, assume one item "left" and one item
	     got in instead,  assume the one got in has the same dep val as the avg bucket, and the one
		 got out has what the depArr[i] says. 
	  -calcualte a new avg instead of virtualBucketValule assuming that such bucket got a new memebr
	    with what depArr[i] has and one less memebr with a dep value of the virtualBucketValule
	  -using the mean/depAvg calcualte a square gap of each of the above buckets befroer and after 
	    the shift of one person, soo that a larger square gap is a ositive score and so we add/su9bstrc
		 4 items, 2 befero and 2 aftr in the right diretions
	  -the 4 elemetns lead to perf effect due to each isIn item and then  we avgerage all effects on all
	      isIn items to come with an average effect to return as an output of this function
	

	*/
	delete []deltaArr;
	delete []wghArr;
	return avgPerf * 10000.0; //times 10000 just to avoid vey snaller numbers

}




void cResearchObject::LongStretchPerfProcessNew(double** deltaStrchWithSubProfileFocus, double** meanDeltaProfSub,
	double**	sdDeltaProfSub,	     int numOfSubGroups , cResearchDataObj* researchDataObj, cGlobals *globals)
								//	int numOfStretchCategories , int minSizeOfCAtegoryForStretch)
{
	
	cout<< "start long stretch \n";
	
	int patnarrSize = researchDataObj->m_numOfItems;
	int numOfStretchCategories = globals->g_NUMBER_OF_CALIBRATION_GRPS; // minSizeOfCAtegoryForStretch
	//int minSizeOfCAtegoryForStretch = globals->g_MIN_SIZE_OF_CATEG_FOR_STRETCH;
	//int numOfCAgegoriesMax = patnarrSize / minSizeOfCAtegoryForStretch ;
//	numOfStretchCategories = cVarianceCalc::Max(		numOfStretchCategories , numOfCAgegoriesMax);
	//numOfStretchCategories = 10;//try with making a real matter if a pred shit happen to cross a butket out of 20
	double nutrualPerfMultipler = 1.0;
	for(int p = 0 ; p< m_profileListSize; p++)
	{
		cProfileObject* sp = m_profileObjectPtrList[p];
		//5 26 23 update also the basic performance to get a baseline with eualy scores
		sp->UpdatePerformanceArrays(nutrualPerfMultipler ); //default
	}
	double* evolutionPredictionArrBefore = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < patnarrSize ; i++)
	{
		evolutionPredictionArrBefore[i]=0.0;
	}
	double overallStretchBefore=0.0;
	bool C=false;
	bool isWithFineTuning= false;
	
	double* threshArrBefore = new double[numOfStretchCategories];
	double* avgDepArrBefore = new double[numOfStretchCategories];  //avgDepArrBase cntArrBase
	int* cntArrBefore = new int[numOfStretchCategories];
	double depAvgBefore=0.0;
//API TEST RESEARCH
	bool isWithTestPop = false;
	bool isApplyDeltaRangeRestic = false;
	double anchorDepForBestMatch = 0.0;
	//6 11 23 if this is the befoer mst add a flag saying to not use the complex score at all, just straagin, to get the evolutionPredictionArrBefore clean
	cout<< "before PRedictIncludingBuildPerfirmanceArrayn";
	bool isStregithPrediction = true;
	PRedictIncludingBuildPerfirmanceArray(  anchorDepForBestMatch,
		threshArrBefore, avgDepArrBefore,  cntArrBefore,  depAvgBefore,
		evolutionPredictionArrBefore, overallStretchBefore,
		 patnarrSize,	 numOfStretchCategories,	  researchDataObj,  globals , isWithFineTuning,
		 NULL, 0.0,isStregithPrediction );
	cout<< "after  PRedictIncludingBuildPerfirmanceArrayn";
	if(anchorDepForBestMatch == 0.0)
	{
		anchorDepForBestMatch = depAvgBefore;
	}
	//isWithTestPop=true;
///////////////////////////////////
 	double averageProfileAddedStretch = 0.0;
	for(int p = 0 ; p< m_profileListSize ; p++) 
	{ 
		cProfileObject* sp = m_profileObjectPtrList[p];
		for(int x = 0 ; x <  numOfSubGroups ; x++)
		{
			deltaStrchWithSubProfileFocus[p][x]=0.0;
			bool* isInSubGrpPrfile = new bool[patnarrSize];
			int cntOfSubGrp =	FillIsInProfSub(isInSubGrpPrfile , m_profileObjectPtrList, p,  x,  researchDataObj, NULL);
			if(cntOfSubGrp > 0)
			{
				double* updaedPredictionArray = new double [patnarrSize];
				double mean = 0.0;
				
				double errSqrSumAllProf = 0.0;
				double errSqrSumThisPrfSunX = 0.0;
				int movingIndex = 0;
				for(int i = 0 ; i < patnarrSize ; i++)
				{
					updaedPredictionArray[i] = evolutionPredictionArrBefore[i];
					if(isInSubGrpPrfile[i])
					{
						updaedPredictionArray[i] = sp->GetSubGroupAverageDependentArr()[x];
						mean += researchDataObj->m_depArr[i];

						double errorSqrAll = evolutionPredictionArrBefore[i]- researchDataObj->m_depArr[i];
						errorSqrAll *= errorSqrAll;
						errSqrSumAllProf += errorSqrAll;
						
						double errorSqrThisProfSub = updaedPredictionArray[i]- researchDataObj->m_depArr[i];
						errorSqrThisProfSub *= errorSqrThisProfSub;
						errSqrSumThisPrfSunX += errorSqrThisProfSub;
						movingIndex++;
					}
				}
				mean /= cntOfSubGrp;
				//researchDataObj->m_depArr[i];, researchDataObj->m_twoDimArr[i];
				double meanDelta =0.0;
				double sdDelta=0.0;
				double sendingDeAvg = depAvgBefore;
				if(   isWithTestPop)
				{
					sendingDeAvg = 	anchorDepForBestMatch;
				}

				if(movingIndex>0)
				{
					errSqrSumAllProf /= movingIndex;
					errSqrSumThisPrfSunX /= movingIndex;
					if(errSqrSumThisPrfSunX > 0.0)
					{
						deltaStrchWithSubProfileFocus[p][x] = errSqrSumAllProf / errSqrSumThisPrfSunX;
					}
				}

				 
				double temp = 
					XYZW123(meanDelta, sdDelta,  updaedPredictionArray , evolutionPredictionArrBefore,
					isInSubGrpPrfile,  researchDataObj,
					threshArrBefore, avgDepArrBefore,  cntArrBefore,  sendingDeAvg, numOfStretchCategories,
					sp, x);
			//	deltaStrchWithSubProfileFocus[p][x]=temp;
				int sdgdg  =0;
				deltaStrchWithSubProfileFocus[p][x]=temp;
				meanDeltaProfSub[p][x] = meanDelta;
				sdDeltaProfSub[p][x] = sdDelta;
				
				delete [] updaedPredictionArray;
				updaedPredictionArray=NULL;
			}
			delete []isInSubGrpPrfile;
			isInSubGrpPrfile=NULL;
			
		}
	}

	cout<< "after delta process";
	//5 31 23 decide to open or not the if (true) below
	//plan a function thata takes the delta strech and sd and decide to play aroun with both  and set fune tuned values
	//end of this the deltaStrchWithSubProfileFocus, meanDeltaProfSub, sdDeltaProfSub, as are input and output will change
	//to be more optimizsed for best match. also testing fune tune. actually testing the delta perforacne, the sd , and the fune tune
	if(false)
	{//learning on the delta strech parameters, and then adust profiles
		int sizePErStretchGroup = 500;
		int numOFBuckets = patnarrSize / sizePErStretchGroup;
		
		
		MachineLearningAdjustDeltaPerfElementsAndUpdateProfiles(deltaStrchWithSubProfileFocus, meanDeltaProfSub, sdDeltaProfSub,
			m_profileListSize ,  numOfSubGroups,    patnarrSize ,   numOFBuckets,    isWithTestPop, researchDataObj,
			 globals,   isWithFineTuning	); 
	}
	else
	{ //adjust delta paramaters to profiels, just simple with no learning  first
		int sdfg =0;
		for(int p = 0 ; p < m_profileListSize ; p++)
		{
			double* finining = new double[numOfSubGroups];
			int* sampe = new int[numOfSubGroups];
			for(int x = 0  ; x < numOfSubGroups ; x++)
			{
				sampe[x]= GetProfileListArray()[p]->GetSubBucketCntArr()[x];
				finining[x]=deltaStrchWithSubProfileFocus[p][x];
			}
			double* fininingAlt = new double[numOfSubGroups];
			double targetSample = 300.0;
			for(int x = 0  ; x < numOfSubGroups ; x++)
			{
				fininingAlt[x] = finining[x] * double(sampe[x]);
				double sumWeights = double(sampe[x]);
				if(sumWeights < targetSample)
				{
					double altern = 0.0;
					double sumAltWghts = 0.0;
					for(int y = 0 ; y < numOfSubGroups ; y++)
					{
						if( (y!=x)  && (sampe[y]> 50))
						{
							double wgh = 1.0 / ( cVarianceCalc::Abs(x-y) * 2 ) ;
							altern += wgh * finining[y];
							sumAltWghts += wgh;							
						}
					}
					if(sumAltWghts > 0.0)
					{
						altern /= sumAltWghts;
					}
					else
					{
						altern=0.0;
					}
					double extrwgh =  targetSample - sumWeights;
					sumWeights += extrwgh;
					fininingAlt[x]  += (extrwgh * altern);
				}
				fininingAlt[x] /= sumWeights;
			}
			for(int x = 0  ; x < numOfSubGroups ; x++)
			{
				deltaStrchWithSubProfileFocus[p][x] = fininingAlt[x];
			}

			delete[] finining;
			delete[] fininingAlt;
			delete[] sampe;
		}
		
		
		
		
		for(int p = 0 ; p < m_profileListSize ; p++)
		{
			for(int x = 0  ; x < numOfSubGroups ; x++)
			{
				GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = deltaStrchWithSubProfileFocus[p][x];
				GetProfileListArray()[p]->GetSubGrpDeltaFromStrMean()[x] = meanDeltaProfSub[p][x];
				GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] = sdDeltaProfSub[p][x];
			}
		}
	}
	/* 5 31 23 *******
	when reaching here, package all below lilnes so i can call them p profiles * 5 sub roups, 25,000 now and much more later each
	call os actually two calls. first, choose only some of the profiles with certaitn sub gruops that hvaae a positive and good
	//score, if not do not bother . when do selecting , keep original p rediction and stretch score and adding two more calls one
	with higher performacne, much higher to make a diference, and one  with same performance lower or higher performacne 
	and more onarrow sdDelta. for those that got a betetr scroe with perf weight 10 times more, we only double it, and can then
	do another round  of improvement. for those with sd lower better, keep it lower.
	futuer version may be to add some pattern and not just use range filter
	*/
	double* evolutionPredictionArrAfter = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < patnarrSize ; i++)
	{
		evolutionPredictionArrAfter[i]=0.0;
	}
	double overallStretchAfter=0.0;

	double* threshArrAft = new double[numOfStretchCategories];
	double* avgDepArrAft = new double[numOfStretchCategories];  //avgDepArrBase cntArrBase
	int* cntArrAft = new int[numOfStretchCategories];
	double depAvgAft =0.0;
	//isWithTestPop=true;
//	numOfStretchCategories=20;
	isApplyDeltaRangeRestic=false;//isWithTestPop API 5 31 23
	isStregithPrediction = false;
	PRedictIncludingBuildPerfirmanceArray(  anchorDepForBestMatch,
		threshArrAft,avgDepArrAft, cntArrAft, depAvgAft,
		evolutionPredictionArrAfter, overallStretchAfter,
		 patnarrSize,	 numOfStretchCategories,	  researchDataObj,  globals, isWithFineTuning ,
		NULL, 0.0,isStregithPrediction );

	//PRINT COUNT TGRESHOLD AND AVG ARRAYS   5 31 23
/*	bool isForDEbug = true;
	if(isForDEbug)//just to see what comes when sending a smaller num of stretch and performacne distribution
	{
		bool isWithFineTuningLocal = true;
		PRedictIncludingBuildP erfirmanceArray( evolutionPredictionArrAfter, overallStretchAfter,
		 patnarrSize,	 50,	  researchDataObj,  globals, isWithFineTuningLocal, true  );

	}*/

	delete []evolutionPredictionArrBefore;
	evolutionPredictionArrBefore=NULL;
	
/*	PRedictIncludingBuildPerfirmanceArray(  anchorDepForBestMatch,
		threshArrAft,avgDepArrAft, cntArrAft, depAvgAft,
		evolutionPredictionArrAfter, overallStretchAfter,
		 patnarrSize,	 10,	  researchDataObj,  globals, isWithFineTuning ,
		 true,isApplyDeltaRangeRestic, NULL, 0.0 );
	*/
	
	
	delete []evolutionPredictionArrAfter;
	evolutionPredictionArrAfter=NULL;

			
	bool isWriteMode=true;
	cArrayFlex* arrayFlex = new cArrayFlex("profile_report.txt",isWriteMode);
	arrayFlex->WriteReadArrayString("number of buckets",isWriteMode,*globals);
	arrayFlex->WriteReadArrayInt(numOfStretchCategories,isWriteMode,*globals);
	arrayFlex->WriteReadArrayString("bucket values:",isWriteMode,*globals);
	arrayFlex->WriteReadArrayString("BEFORE",isWriteMode,*globals);
	arrayFlex->WriteReadArrayString("Stretch:",isWriteMode,*globals);
	arrayFlex->WriteReadArrayDouble( overallStretchBefore,isWriteMode,*globals);
	for(int i = 0 ; i < numOfStretchCategories; i++)
	{
		arrayFlex->WriteReadArrayString("buckets index",isWriteMode,*globals);
		arrayFlex->WriteReadArrayInt(i,isWriteMode,*globals);
		arrayFlex->WriteReadArrayString("buckets highThr, value, count",isWriteMode,*globals);
		arrayFlex->WriteReadArrayDouble(threshArrBefore[i],isWriteMode,*globals);
		arrayFlex->WriteReadArrayDouble( avgDepArrBefore[i],isWriteMode,*globals);
		arrayFlex->WriteReadArrayInt(cntArrBefore[i],isWriteMode,*globals);
	}
	arrayFlex->WriteReadArrayString("AFTER",isWriteMode,*globals);
	arrayFlex->WriteReadArrayString("Stretch:",isWriteMode,*globals);
	arrayFlex->WriteReadArrayDouble(overallStretchAfter,isWriteMode,*globals);
	for(int i = 0 ; i < numOfStretchCategories; i++)
	{
		arrayFlex->WriteReadArrayString("buckets index",isWriteMode,*globals);
		arrayFlex->WriteReadArrayInt(i,isWriteMode,*globals);
		arrayFlex->WriteReadArrayString("buckets highThr, value, count",isWriteMode,*globals);
		arrayFlex->WriteReadArrayDouble(threshArrAft[i],isWriteMode,*globals);
		arrayFlex->WriteReadArrayDouble( avgDepArrAft[i],isWriteMode,*globals);
		arrayFlex->WriteReadArrayInt(cntArrAft[i],isWriteMode,*globals);
	}
	delete arrayFlex;
	arrayFlex = NULL;

	delete []threshArrBefore;
	delete [] avgDepArrBefore;
	delete [] cntArrBefore;
	delete []threshArrAft;
	delete []avgDepArrAft;
	delete []cntArrAft;
}
 ;
	

int  cResearchObject::FillIsInProfSub(bool* isPersonInProfSub, cProfileObject** profileArr,int p,  int x,
	cResearchDataObj* researchDataObj, bool* isInContext )
{
	return FillIsInProfSub( isPersonInProfSub,profileArr[p],   x, researchDataObj,  isInContext);
}


int  cResearchObject::FillIsInProfSub(bool* isPersonInProfSub,cProfileObject* profile,  int x, 
	cResearchDataObj* researchDataObj, bool* isInContext)
{
	int numOfPersons=researchDataObj->m_numOfItems;
	int cntOfSubGrp =0;
	int cntAllGrps=0;
	for(int i = 0 ; i < numOfPersons ; i++)
	{
		isPersonInProfSub[i] = false;
		if( isInContext == NULL ||  isInContext[i])
		{
			isPersonInProfSub[i] = profile->IsPatientIncluded(researchDataObj->m_twoDimArray[i]);
			if(isPersonInProfSub[i] )//if this patienet is in this profile. 
			{

				double sumPnt =   profile->CalclaterSumAdjusteddPnts(researchDataObj->m_twoDimArray[i],
						researchDataObj->m_sizeOfItem,	profile->GetAdjustedOddRateArr(),
						profile->GetOddRatioListSize()		);
				int subGrpIndex = profile->GetSubGrpIndex( sumPnt,  profile->GetThresholdArr(),
									profile->GetNumberOfSubGroups());
				if(( x >=0 ) && (subGrpIndex  != x ))//6 13 23 check
				{
					isPersonInProfSub[i] = false;					
				}
				else
				{
					int tsdg=0;
				}
				cntAllGrps++;
			}
			if(isPersonInProfSub[i])
			{
				cntOfSubGrp ++;
			}
		}
	}	
	return cntOfSubGrp;
}
/*

*/
void  cResearchObject::MachineLearningAdjustDeltaPerfElementsAndUpdateProfiles(double** deltaStrchWithSubProfileFocus,
	double** meanDeltaProfSub ,  double** sdDeltaProfSub,  int numProfiles, int numSubGrps,
	int numOfPersons, int numberOfStrchBuckets, bool isWithTestPop, cResearchDataObj* researchDataObj,
    cGlobals* globals,  int isWithFineTuning	)
{
	//Updating profiles with latest (here initial ) input
	int profSubNum = numProfiles * numSubGrps;
	double* perfArray = new double[profSubNum];
	int movingPerfIndex=0;
	for(int p = 0 ; p < numProfiles ; p++)
	{
		for(int x = 0  ; x < numSubGrps ; x++)
		{
			GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = deltaStrchWithSubProfileFocus[p][x];
			perfArray[movingPerfIndex++] = deltaStrchWithSubProfileFocus[p][x];
			GetProfileListArray()[p]->GetSubGrpDeltaFromStrMean()[x] = meanDeltaProfSub[p][x];
			GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] = sdDeltaProfSub[p][x];
		}
	}
	double meanPErfForSub = 0.0;
	double sdPErfSofSub=0.0;
	cVarianceCalc::CalculateMeanAndSD(meanPErfForSub, sdPErfSofSub, perfArray,NULL, profSubNum);
	double* evolutionPredictionArr = new double[numOfPersons];
	for(int i = 0 ; i < numOfPersons ; i++)
	{
		evolutionPredictionArr[i]=0.0;
	}
	double baseStretch=0.0;
	//call for the prediction and bucket with cont and avergage prediction
	double* threshArr = new double[numberOfStrchBuckets];
	double* avgDepArr = new double[numberOfStrchBuckets];  //avgDepArrBase cntArrBase
	int* cntArr = new int[numberOfStrchBuckets];
	double depAvg =0.0;
	bool isApplyDeltaRangeRestic=false;
	double anchorDepForBestMatch=0.0;

	bool* isPersonInProfSub = new bool[numOfPersons];
	for(int i = 0 ; i < numOfPersons ; i++)
	{
		isPersonInProfSub[i] = true;
	}
	bool isStregithPrediction=false;
	PRedictIncludingBuildPerfirmanceArray(  anchorDepForBestMatch,	threshArr,avgDepArr, cntArr, depAvg,
		evolutionPredictionArr, baseStretch, numOfPersons,	 numberOfStrchBuckets,	  researchDataObj,  globals, isWithFineTuning ,
		 isPersonInProfSub, 0.0,isStregithPrediction );
	delete []isPersonInProfSub;
	isPersonInProfSub=NULL;
	/*
		thse to be used many times with the loop below and each collets some evidance regarding profile sub gruops perff shiffts
		and sd effect, to then conclude into a new set of perf and sd
	*/
	double* evolutionPredictionTemp = new double[numOfPersons];
	for(int i = 0 ; i < numOfPersons ; i++)
	{
		evolutionPredictionTemp[i]=0.0;
	}
	double tempStretch=0.0;
	//call for the prediction and bucket with cont and avergage prediction
	double* threshArrTemp = new double[numberOfStrchBuckets];
	double* avgDepArrTemp = new double[numberOfStrchBuckets];  //avgDepArrBase cntArrBase
	int* cntArrTemp = new int[numberOfStrchBuckets];
	double depAvgTemp =0.0;
	double anchorDepForBestMatchTemp=0.0;
	//1-get a list of top profile/sub with the most highest performance or even the most higher on each rage of prediction values
	//can start with simple way of selecting most and imprve, just a way to not do oa lot of CPU tine
    //2-prepare an isInProfileSub list to send only the in , each for a 3 evaluations. the firsrt is from the above base call, which
	//is all without adjusting this profie,the second is adjusting just the perf (100 times higher? 10?) and then j ust the sd
	//such as 50% range and less options. Then see calling the exact same PRedictIncludingBuildPerfirmanceArray just getting
	//a moving stretch. keep new stretch in two dim aray to then compare 

	double barForGoodEnoughPer = meanPErfForSub + (sdPErfSofSub/2.0);//give us only the pop better than 1 positie SD. probably only 20%
	//of the profiles sub gruops or much less will actually be used so for now no need to spend CPU on all 


	double** perfTwoDim = new double*[numProfiles];
	for(int p = 0 ; p < numProfiles ; p++)
	{
		perfTwoDim[p]= new double[numSubGrps];
		for(int x = 0  ; x < numSubGrps ; x++)
		{
			perfTwoDim[p][x] = 0.0;
		}

	}


	double sumOfAddedStretch = 0.0;
	double meanCurrentPerf = 0.0;
	int cntOfPastBarCases=0;
	for(int p = 0 ; p < numProfiles ; p++)
	{//5 31 23 add again isIn profile and then a different isIn for each sub grp to be able to send that and inside 
		//calling for prediction will only be for small number of patients. check if i did that befor with the is in sub
		for(int x = 0  ; x < numSubGrps ; x++)
		{
			if(deltaStrchWithSubProfileFocus[p][x] > barForGoodEnoughPer)
			{
				//temporary value for test
			//	GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = 
			//		deltaStrchWithSubProfileFocus[p][x]+(sdPErfSofSub*50);				
				for(int i = 0 ; i < numOfPersons ; i++)
				{
					evolutionPredictionTemp[i]=evolutionPredictionArr[i];
				}

				bool* isPersonInProfSub = new bool[numOfPersons];
				int cntOfSubGrp = FillIsInProfSub(isPersonInProfSub,m_profileObjectPtrList, p,x,researchDataObj, NULL);
				double profSubDepAvgTpForce = GetProfileListArray()[p]->GetSubGroupAverageDependentArr()[x];
				int sampleSizeForForce = GetProfileListArray()[p]->GetSubBucketCntArr()[x];
				if(sampleSizeForForce > 300)//6 8 23 not sure if still i need to heck since i salled in processing time
				{
					PRedictIncludingBuildPerfirmanceArrayNew(
						anchorDepForBestMatchTemp, threshArrTemp,avgDepArrTemp, cntArrTemp, depAvgTemp,
						evolutionPredictionTemp, tempStretch, numOfPersons,	 numberOfStrchBuckets,	  researchDataObj,
						globals, isWithFineTuning ,	 isWithTestPop,isApplyDeltaRangeRestic ,
						isPersonInProfSub, profSubDepAvgTpForce,
							GetProfileListArray()[p]->GetSubGrpDeltaFromStrMean()[x],
							GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] 
					);

				//	PRedictIncludingBuildPerfirmanceArray(anchorDepForBestMatchTemp, threshArrTemp,avgDepArrTemp, cntArrTemp, depAvgTemp,
					//	evolutionPredictionTemp, tempStretch, numOfPersons,	 numberOfStrchBuckets,	  researchDataObj,
					//	globals, isWithFineTuning ,	 isWithTestPop,isApplyDeltaRangeRestic , isPersonInProfSub, profSubDepAvgTpForce);

					for(int i = 0 ; i < numOfPersons ; i++)
					{
						evolutionPredictionTemp[i]=evolutionPredictionArr[i];
					}


				//back to original
					//GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = deltaStrchWithSubProfileFocus[p][x];
					if(tempStretch > baseStretch)
					{
						//applying but not all the way assuming more opporotniy will be 
					//	deltaStrchWithSubProfileFocus[p][x] *= 1.5;//5 31 23 need o add devide by sub group count
						perfTwoDim[p][x] = tempStretch - baseStretch;
						sumOfAddedStretch += perfTwoDim[p][x];
						meanCurrentPerf +=  deltaStrchWithSubProfileFocus[p][x];
						cntOfPastBarCases ++;
					//	GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = deltaStrchWithSubProfileFocus[p][x];
					}
				}
			/*	GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] = sdDeltaProfSub[p][x] / 2.0;// smaller sd so less times per is active;
				PRedictIncludingBuildPerfirmanceArray(anchorDepForBestMatchTemp, threshArrTemp,avgDepArrTemp, cntArrTemp, depAvgTemp,
					evolutionPredictionTemp, tempStretch, numOfPersons,	 numberOfStrchBuckets,	  researchDataObj,
					globals, isWithFineTuning ,	 isWithTestPop,isApplyDeltaRangeRestic, isPersonInProfSub);
				//back to  normal
				GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] = sdDeltaProfSub[p][x];
				if(tempStretch > baseStretch)
				{
					sdDeltaProfSub[p][x] /= 1.1;
				}
				*/
				delete []isPersonInProfSub;
				isPersonInProfSub=NULL;
				//applying and in case one of these ot both change the proifles now have the updated feature value
			 
			}
		}
	}
	
	if(cntOfPastBarCases>0)
	{
		meanCurrentPerf /= cntOfPastBarCases;
	}
	//sumOfAddedStretch = 0.0;
	double sumOfCurrentStretch = meanCurrentPerf*cntOfPastBarCases;
	double addingNewPerfTotal = sumOfCurrentStretch * 2.0;//addingi 200%
	
	for(int p = 0 ; p < numProfiles ; p++)
	{//5 31 23 add again isIn profile and then a different isIn for each sub grp to be able to send that and inside 
		//calling for prediction will only be for small number of patients. check if i did that befor with the is in sub
		for(int x = 0  ; x < numSubGrps ; x++)
		{
			if(deltaStrchWithSubProfileFocus[p][x] > barForGoodEnoughPer)
			{
				double addedPowert= 	addingNewPerfTotal * (perfTwoDim[p][x]/sumOfAddedStretch);
				double averageAdded = addingNewPerfTotal/cntOfPastBarCases;
				addedPowert = cVarianceCalc::Min(addedPowert, averageAdded * 3.0);
				deltaStrchWithSubProfileFocus[p][x] += 	addedPowert;
				GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = deltaStrchWithSubProfileFocus[p][x];
			//	GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] = sdDeltaProfSub[p][x];
			}
		}
	}


//again after adjustement
	for(int p = 0 ; p < numProfiles ; p++)
	{
		for(int x = 0  ; x < numSubGrps ; x++)
		{
			GetProfileListArray()[p]->GetSubGrpPerformanceAdvancedArray()[x] = deltaStrchWithSubProfileFocus[p][x];
			GetProfileListArray()[p]->GetSubGrpDeltaFromStrMean()[x] = meanDeltaProfSub[p][x];
			GetProfileListArray()[p]->GetSubGrpDeltaFromStrSD()[x] = sdDeltaProfSub[p][x];
		}
	}
	
	
	double*	threshArrAft = new double[numberOfStrchBuckets];
	double* avgDepArrAft = new double[numberOfStrchBuckets];
	int* cntArrAft = new int[numberOfStrchBuckets];
	double  depAvgAft =0.0;
	double afterStretch = 0.0;

	if(isPersonInProfSub == NULL)
	{
		isPersonInProfSub = new bool[numOfPersons];
	}

	for(int i = 0 ; i < numOfPersons ; i++)
	{
		isPersonInProfSub[i] = true;
	}
	bool isStragith=false;
	PRedictIncludingBuildPerfirmanceArray(  anchorDepForBestMatch,	threshArrAft,avgDepArrAft, cntArrAft, depAvgAft,
		evolutionPredictionArr, afterStretch, numOfPersons,	 numberOfStrchBuckets,	  researchDataObj,  globals, isWithFineTuning ,
		 isPersonInProfSub, 0.0,isStragith );
	
	delete []isPersonInProfSub;
	isPersonInProfSub=NULL;

	for(int p = 0 ; p < numProfiles ; p++)
	{
		delete []perfTwoDim[p] ;
	}
	delete []perfTwoDim;
	perfTwoDim=NULL;

	
	delete []evolutionPredictionArr;
	evolutionPredictionArr=NULL;
	delete []threshArr;
	threshArr=NULL;
	delete [] avgDepArr ;
	avgDepArr=NULL;
	delete []cntArr;
	cntArr=NULL;

	delete []evolutionPredictionTemp;
	evolutionPredictionTemp=NULL;
	delete []threshArrTemp;
	threshArrTemp=NULL;
	delete []avgDepArrTemp;
	avgDepArrTemp=NULL;
	delete []cntArrTemp;
	cntArrTemp=NULL;

	delete []perfArray;
	perfArray=NULL;

	/* 5 31 23 *******
	when reaching here, package all below lilnes so i can call them p profiles * 5 sub roups, 25,000 now and much more later each
	call os actually two calls. first, choose only some of the profiles with certaitn sub gruops that hvaae a positive and good
	//score, if not do not bother . when do selecting , keep original p rediction and stretch score and adding two more calls one
	with higher performacne, much higher to make a diference, and one  with same performance lower or higher performacne 
	and more onarrow sdDelta. for those that got a betetr scroe with perf weight 10 times more, we only double it, and can then
	do another round  of improvement. for those with sd lower better, keep it lower.
	futuer version may be to add some pattern and not just use range filter
	*/
	

}


void  cResearchObject::PRedictIncludingBuildPerfirmanceArrayNew( double &anchorDepForBestMatch,
	double*	threshArr, double* avgDepArr, int*  cntArr, double &depAvg,
	double* evolutionPredictionArrr, double &overallStretch,
	int ptArrSize,  int numOfStretchCategories, cResearchDataObj*  researchDataObj, cGlobals* globals ,
	bool isWithFineTuning , bool isWithTest, bool	isApplyDeltaRangeRestic, bool* isPersonInProfSub, 
	double profSubDepAvgTpForce,  double profSubMeanDelta, double profSubSDdelta)
{
	//profSubDepAvgTpForce
	//evolutionPredictionArrr
//	isPersonInProfSub
	if((isPersonInProfSub!= NULL) &&( profSubDepAvgTpForce!= 0.0))
	{
		for(int i = 0 ; i < ptArrSize ; i++)
		{
			if((isPersonInProfSub[i]))
			{
				double current = evolutionPredictionArrr[i];
				double suggestedSubStrength = profSubDepAvgTpForce;
				double proposedDireciton = suggestedSubStrength - current;
				double zPropsedDelta = 0.0;
				if(profSubSDdelta!=0.0)
				{
					zPropsedDelta = proposedDireciton / profSubSDdelta;
				}
				if(  (proposedDireciton * profSubMeanDelta) > 0.0)
				{
					if(proposedDireciton<0.0)
					{
						int sdg =0;
					}
					double ratio= cVarianceCalc::Abs(zPropsedDelta) / 2.0;
					ratio= cVarianceCalc::Min(ratio, 1.0);
					double newPrdiction  = current + (proposedDireciton *  ratio ) ;
					evolutionPredictionArrr[i] = newPrdiction;
				}
			}
		}
			//	profSubMeanDelta - this is the direction that made the profile be good in moving. 
	}

	

	cProfileObject::CalculateThresholds(threshArr , numOfStretchCategories, evolutionPredictionArrr,NULL,ptArrSize);

	depAvg = 0.0;
	cProfileObject::CreateAvgDepSubGrps(NULL,avgDepArr,threshArr ,cntArr, depAvg, numOfStretchCategories,evolutionPredictionArrr,
		researchDataObj->m_depArr, NULL, ptArrSize, *globals);

	overallStretch = CalculateStreth(avgDepArr,  cntArr,		depAvg, numOfStretchCategories);
	int sdg=0;
}

void  cResearchObject::PRedictIncludingBuildPerfirmanceArray( double &anchorDepForBestMatch,
	double*	threshArr, double* avgDepArr, int*  cntArr, double &depAvg,
	double* evolutionPredictionArrr, double &overallStretch,
	int ptArrSize,  int numOfStretchCategories, cResearchDataObj*  researchDataObj, cGlobals* globals ,
	bool isWithFineTuning ,bool* isPersonInProfSub, double profSubDepAvgTpForce, bool isWithStragithPRediction)
{
 	double* predictionArr = new double[ptArrSize];
	double* predictionWithInArr = new double[ptArrSize];
	double* predictionWithoutInArr = new double[ptArrSize];
	for(int i = 0 ; i < ptArrSize ; i++)
	{
		predictionArr[i]=0.0;
		predictionWithInArr[i]=0.0;
		predictionWithoutInArr[i]=0.0;
		if(evolutionPredictionArrr!=NULL)
		{
			predictionArr[i]=evolutionPredictionArrr[i];
			predictionWithInArr[i]=evolutionPredictionArrr[i];
			predictionWithoutInArr[i]=evolutionPredictionArrr[i];
		}
		if( (isPersonInProfSub == NULL) || (isPersonInProfSub[i]) )
		{
			predictionArr[i]=0.0;
			predictionWithInArr[i]=0.0;
			predictionWithoutInArr[i]=0.0;
		}
	}
	depAvg=0.0;
	//bool isWithFineTuning = false;
	//5 31 23 get predictionArr with only those that part of the rofile sub grogup and merge with the nput evolutionPredictionArrr 
	//to  a full adjusted evolutionPredictionArrr. do iot by adding a flag frmo above and executing below
	PredictionAndCalculatePerformanceStretch (  anchorDepForBestMatch, threshArr ,avgDepArr, cntArr, depAvg  ,  
		predictionArr, predictionWithInArr, predictionWithoutInArr,		ptArrSize, 		NULL,  
		researchDataObj , *globals, numOfStretchCategories ,isWithFineTuning,isPersonInProfSub, profSubDepAvgTpForce, isWithStragithPRediction);
		
	
	for(int i = 0 ; i < ptArrSize ; i++)
	{
		if(isPersonInProfSub == NULL || (isPersonInProfSub[i]))
		{
			evolutionPredictionArrr[i]=predictionArr[i];
		}
	}
	
	delete []predictionArr;
	predictionArr=NULL;
	delete []predictionWithInArr;
	predictionWithInArr=NULL;
	delete []predictionWithoutInArr;
	predictionWithoutInArr=NULL;

	overallStretch = CalculateStreth(avgDepArr,  cntArr,		depAvg, numOfStretchCategories);
	
}


/*
void cResearchObject::LongStretchPerfProcess(double* evolutionPredictionArrr,double* addedStretchArrr, cResearchDataObj* researchDataObj, cGlobals &globals)
								//	int numOfStretchCategories , int minSizeOfCAtegoryForStretch)
{
	int patnarrSize = researchDataObj->m_numOfItems;
	int numOfStretchCategories = globals.g_NUMBER_OF_CALIBRATION_GRPS; // minSizeOfCAtegoryForStretch
	int minSizeOfCAtegoryForStretch = globals.g_MIN_SIZE_OF_CATEG_FOR_STRETCH;
	int numOfCAgegoriesMax = patnarrSize / minSizeOfCAtegoryForStretch ;
	numOfStretchCategories = cVarianceCalc::Max(		numOfStretchCategories , numOfCAgegoriesMax);
	for(int i = 0 ; i < patnarrSize ; i++)
	{
		evolutionPredictionArrr[i]=0.0;
	}
	double nutrualPerfMultipler = 1.0;
	for(int i = 0 ; i< m_profileListSize; i++)
	{
		cProfileObject* sp = m_profileObjectPtrList[i];
		//5 26 23 update also the basic performance to get a baseline with eualy scores
		sp->UpdateAdvancePerformance(nutrualPerfMultipler ); //default
	}
	double baseOverallStretch = 0.0;
	UpdtePredictionArr AndCalculatePerformanceStretch(
					baseOverallStretch,  evolutionPredictionArrr, patnarrSize, 
					NULL,   researchDataObj , globals, numOfStretchCategories);
	
	double averageProfileAddedStretch = 0.0;
	for(int i = 0 ; i< m_profileListSize; i++)
	{//5 26 23 add a new addedStretchArrrPerSub with all 5 sub gruops to have their own perf.
		//zero addedStretchArrrPerSub[i][x] and add a new for(int x = 0 ; x < 5 ; x++) to get
		//a call for the update prediction funcitn 5 times for each profile. each time i only 
		//touch an isIn that is iboth the profile i and the sub gruop x and so if isIn[i][x]
		//than only update the prediction and then only get the strecch. bette to oepn a new 
		//funtion for that. see to set the predictioon right away use strait copy and no need for
		//best match
		addedStretchArrr[i]=0.0;
		cProfileObject* sp = m_profileObjectPtrList[i];
	//	double savedPerf = sp->GetProfileAdvancedPerformance(0);//for now any index is same
		double overAlltretch = 0.0;
		sp->UpdateAdvancePerformance(  globals.g_STRENGTH_MULT_OF_LONG_STRETCHED_PROFILE ); //if stretch is 1.0 it is the max since it is a gap and highest stretch is
//return stretch will be saved above as "lastStrech" to send next time this fucttion isi called. 
		//12 2 22 *** add an option that if i deleted the GetIsInProfileArr() so it is NULL, so instead of sending NULL and have all predictions
		//done again, i want to create a new isIn by redoing the same function that sets the is in at first. the i eitehtr send the original profile
		//is in or create a new one, do not send NULL as it takes too long
		//to not delete the isIn above, and than have that from sp
		bool* isInProfile =  sp->GetIsInProfileArr();
		bool isCreatedNewIsIn = false;
		if(isInProfile == NULL)
		{
			isInProfile = new bool[patnarrSize];
			isCreatedNewIsIn = true;
			for(int i = 0 ; i < patnarrSize ; i++)
			{
				isInProfile[i] = sp->IsPatientIncluded(researchDataObj->m_twoDimArray[i]);
			}
		}
		
		UpdtePredictionArrAndCalculatePerformanceStretch(
			overAlltretch,  evolutionPredictionArrr, patnarrSize,  
			isInProfile,   researchDataObj , globals, numOfStretchCategories);
		sp->UpdateAdvancePerformance(nutrualPerfMultipler );
		addedStretchArrr[i] = overAlltretch - baseOverallStretch ;
		//addedStretchArr[i] extrac stretch is a resulst of sp->profile popuatio size members that got better predeiction. on average
		addedStretchArrr[i] /= sp->GetProfilePopulationSize(); //even if i configure not to have the isIn active, duue to memort, still the real effect will be
		//divided into the numer of patinets that were hit this profile and had a chance to get better prediction
		averageProfileAddedStretch += addedStretchArrr[i];//even if negative we still add it to have a knowlege about the average (no usage yet of such average)

		if(isCreatedNewIsIn) //nnly if the array was allocating memory in this fuction we delete the memory
		{
			delete []isInProfile;
		}
		isInProfile=NULL;

	}
	averageProfileAddedStretch /= m_profileListSize;

	double meanStre = 0.0;
	double sdStre = 0.0;
	cVarianceCalc::CalculateMeanAndSD(meanStre, sdStre, addedStretchArrr,NULL,m_profileListSize);


	for(int i = 0 ; i< m_profileListSize; i++)
	{
	//	cProfileObject* sp = m_profileObjectPtrList[i];
		double tempp = 1.0;//cVarianceCalc::Max(addedStretchArrr[i], 0.0001);
		if(sdStre > 0.0)
		{
			double zScore= (addedStretchArrr[i] - meanStre)/sdStre;
			if(zScore > 0.0)
			{
				zScore = cVarianceCalc::Min(zScore , 4.0);// +4 will make times 5 in highest case of a good profile
				tempp += zScore;//12 2 22 maybe add a define nwith a division so zScore / DEFINE will be the addition
			}
		}			
		m_profileObjectPtrList[i]->UpdateAdvancePerformance(tempp);
		//12 2 22 *** . first add a way to only make one in here and not have open.
		// then add a define/global to not do delete it here but in the end if there is memory
		m_profileObjectPtrList[i]->DeleteIsInProfile();
	}	 
}
*/
//
void 	cResearchObject::CalcualtePerformanceBuckets(
	 double* depAvgArr, int* cntArr, double &avgDep, 
	 int numOfGrps,   cResearchDataObj* researchDataObj, cProfileObject* profile)
{
	/* using only the profile that is sent as input and all the research data ob pop
	what is the performacne
	
	*/
}

//6 13 23 22
/*
this function will find th next var and will see that it - is not repeated , is better than current, and is best
of all options. i want to temporary open each of the var val set of proifles and th eir stretch, and merger such dep
array into one set of dep array per one var on all its values, and see if that after merrge image can show a better
stretch compare to dep universe . it is that every recursive check will have already a stretchh befoer it finds 
the next var, but not the root which has a 0 stretch as first. it then takes each branch and try to maximize its 
initial stretch compare to the base and to an on going growing streth. at the end of this function i only know 
the next var but it can check all the way. it is the 
*/
int cResearchObject::FindBestNextVarWithPerformCompare(cResearchDataObj* researchDataObj,
	bool* isPredictive, cGlobals* globals, int numOfGrps, cProfileObject* profileBase, double depAvgUniv )
{
	int numOfVariables = researchDataObj->m_sizeOfItem;
	int bestVarIndex = -1;
//	double bestStretch = 0.0;
	
	
	double* depAvgArrBase=new double[numOfGrps];
	int* cntArrBase = new int[numOfGrps];
 
	double* stretchValArr = new  double[numOfVariables];
	double avgDepBase=0.0; 
	//double stretchBase=0.0;
	CalcualtePerformanceBuckets(
	  depAvgArrBase,  cntArrBase, avgDepBase, 
	   numOfGrps,    researchDataObj, profileBase);
	
	double stretchBase= CalculateStreth(	depAvgArrBase,cntArrBase,depAvgUniv, numOfGrps);//depAvgUniv
	      		


	for(int v=0; v< numOfVariables; v++)
	{
		stretchValArr[v]=0.0;
		if(m_schemaArrr->m_schemaArr[v]->m_isPredictiveVariable)
		{
			int numOfValues = m_schemaArrr->m_schemaArr[v]->m_numberOfValues;
		//	double* depAvgArr = new double[numOfValues];
		//	int* sampleArr = new int[numOfValues];
			double** depAvgArrTemp = new double*[numOfValues];
			int** wghArrTemp = new int*[numOfValues];
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				cProfileObject* tempProfile = NULL;
				//6 13 23 22 open new itemporary proifle with preous inclusion rules + this var val
				//CreateProfileWithVarValAdded(previoue profile, var,val, reseeaerOdAtaObj);
				depAvgArrTemp[vl] = new double[numOfGrps];
				wghArrTemp[vl] =  new int[numOfGrps];
				double stretchTemp=0.0;
		
				double avgDepTemp=0.0; 
				double stretch=0.0;
				
				//calcuale the dep array and nsample from this val. then merge all val together
				//CalcualtePerformanceBucketsAndStretch(
				//   stretch, depAvgArrTemp[vl],  wghArrTemp[vl], avgDepTemp, 
				//	     numOfGrps,    researchDataObj, tempProfile);
				



				delete tempProfile;
				tempProfile=NULL;
			}
			double stretchBase=0.0;
			double* depAvgArrMErged=new double[numOfGrps];
			int* cntArrMerrged = new int[numOfGrps];
			//6 13 23 22
		///	MergeTwoDimDepArrayToOneLevelBucletArray(depAvgArrMErged,cntArrMerrged,
		///		depAvgArrTemp,  wghArrTemp, numOfValues, numOfGrps);
			stretchValArr[v] = CalculateStreth(	depAvgArrBase,cntArrBase,depAvgUniv, numOfGrps);
				 
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				delete []depAvgArrTemp[vl];
				depAvgArrTemp[vl]=NULL;
				delete []wghArrTemp[vl];
				wghArrTemp[vl]=NULL;
			}
			delete []depAvgArrTemp;
			depAvgArrTemp=NULL;
			delete []wghArrTemp;
			wghArrTemp=NULL;

			delete []depAvgArrMErged;
			delete []cntArrMerrged;
	
		}
	}
	double hightestStretch = 0.0;
	int varWithHighest = -1;
	for(int v=0; v< numOfVariables; v++)
	{
		if(	stretchValArr[v] > hightestStretch )
		{
			hightestStretch = stretchValArr[v];
			varWithHighest = v;
		}
	}
	if( varWithHighest < 0)
	{
	}
	else
	{
		if(stretchValArr [varWithHighest] > stretchBase)
		{
			bestVarIndex =varWithHighest;
		}
	}

	delete []cntArrBase;
	cntArrBase=NULL;
	delete []depAvgArrBase;
	depAvgArrBase=NULL;
	delete []stretchValArr;
	stretchValArr=NULL;

	return bestVarIndex;
}


void sdfgg()
{
	int asdg = 0 ;
}


bool cResearchObject::IsThisProfileHasChildren( cProfileObject* thisProfToPlayWith,cProfileObject** profList , int numOfProfes)
{
	bool isProfHasChldren = false;
	
	for (int i = 0 ; i < numOfProfes ; i++)
	{//if this proifle rules a sub set of any from the large list that means that that one from the large list is a chiild of this
		if(cProfileObject::IsRightRuleSetChildOfLeft(  
			  thisProfToPlayWith->GetInclusionRuleList(), thisProfToPlayWith->GetInclusionRuleListSize(),
			  profList[i]->GetInclusionRuleList(),  profList[i]->GetInclusionRuleListSize()	  ))
		{	
	//	if( IsLEftInclusionRuleSubSetOfRight( thisProfToPlayWith->GetInclusionRuleList(), thisProfToPlayWith->GetInclusionRuleListSize(),
		//	  profList[i]->GetInclusionRuleList(),  profList[i]->GetInclusionRuleListSize() )
			isProfHasChldren = true;
			return isProfHasChldren;
		}
	}

	return isProfHasChldren;//8 15 23
}

	//if movingSavingTimeArrOut is not toched we keep eit for next time, it is touched when improved only
		//eihter keep both  same - movingSavingTimeArrOut,	movingScore or  update both with higher
		//score and differente pred accordingly to make that highe score//	 FGHHH			
	
//1 14 24 see that for every profile adjustment we do the test again
void cResearchObject::SecondRoundOfMLtry( double* movingSavingTimeArrOutt,double &movingScore, 
		cResearchDataObj* researchDataObj , cProfileObject* root, cProfileObject* anchorForStretch, bool* isPredictive,  cGlobals* globals,
		cVariableSchemaArr* schemaArr,	cPercentileCalculationModel* rootOddPredictiveModel, 
		cPercentileCalculationModel* regPredictiveModell, InputVariablesPackageForResearchObj* inputVarObj, 
		cProfileObject* thisProfToPlayWith, int numOfCalibrationGrps , cEvolutionProfilePAckage**  evolPackage, 
		double* stretArr, bool isThisCaseOfAnchorUniverse6,  double* savingTimeArrInn	)
{
	
	double* calibatedPRed = new double[ researchDataObj->m_numOfItems] ;
	double* calbratedThresArr = new double[numOfCalibrationGrps];//
	double* calbAgDepArr = new double[numOfCalibrationGrps];
	int* calbCntArr  = new int[numOfCalibrationGrps];
	int* bucketIndexArr = new int[researchDataObj->m_numOfItems];
	 
	
	//keep current perf weights befoer doingi anything to get it back if needed
	double advPerfArrCurrent[100];
	thisProfToPlayWith->CopyAdvPerfArrOut(advPerfArrCurrent );
		
	int numOfSubGrps = thisProfToPlayWith->GetNumberOfSubGroups();
	double advPerfNew[100];

	double lastETA = 0.0;
	for(int asd = 0 ; asd < numOfSubGrps ; asd ++)
	{
		bool* isInThisProfSub = new bool[researchDataObj->m_numOfItems];
		int countt = FillIsInProfSub(isInThisProfSub,thisProfToPlayWith, asd, researchDataObj,NULL);
		double* tempPredIn = new double[ researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			tempPredIn[i] = savingTimeArrInn[i] ;
		}
		double currentWeight =  thisProfToPlayWith->GetProfileAdvancedPerformance(asd);
		//1 14 24 
		double* tempPredArr = new double[researchDataObj->m_numOfItems];
		double perf2 = cResearchObject::SwapProfilesWithAnchors2(//NULL,
			tempPredArr,
			 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,
			 researchDataObj,  evolPackage,
						m_profileListSize,   root , anchorForStretch,globals, 0 , stretArr,
						isThisCaseOfAnchorUniverse6, tempPredIn,  true, -1,0,NULL);
		double etaNEW1 = cVarianceCalc::CalcualteETA(tempPredArr , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
		//1 14 24 compare with below after adjustment and adjust movingScore
		if(lastETA != 0.0 && lastETA != etaNEW1)
		{
			int sdgg=0;//shuld not get gere
		}

		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			tempPredIn[i] = savingTimeArrInn[i] ;
			if(isInThisProfSub[i])
			{
				tempPredIn[i]=0.0; 
			}
		}
	
/////////////////////////////
		double multiplier = 2.0;
		thisProfToPlayWith->SetProfileAdvancedPerformance(asd, currentWeight * multiplier );
		double perf0 =  cResearchObject::SwapProfilesWithAnchors2(tempPredArr,
			 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,
			 researchDataObj,  evolPackage,
						m_profileListSize,   root , anchorForStretch,globals, 0 , stretArr,
						isThisCaseOfAnchorUniverse6, tempPredIn,  true, -1,0,NULL);
		double etaNEW2 = cVarianceCalc::CalcualteETA(tempPredArr , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
		if(etaNEW2 > etaNEW1 ){
			//keep the currentWeight * multiplier as tried and succeed
			cout << "improved eta \n";
			cout << etaNEW2;
			cout << " \n";
			
			lastETA = etaNEW2;
			int sdsg=0;
			 
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				if(isInThisProfSub[i])
				{
					savingTimeArrInn[i]=tempPredArr[i]; 
				}
				movingSavingTimeArrOutt[i] = savingTimeArrInn[i] ;
			}
		}
		else
		{
			thisProfToPlayWith->SetProfileAdvancedPerformance(asd, currentWeight );//* (1.0/multiplier) );
		}		
			
		delete []isInThisProfSub;
		isInThisProfSub=NULL;
		delete []tempPredIn;
		tempPredIn=NULL;
		delete []tempPredArr;
		tempPredArr=NULL;
	}
	delete []calibatedPRed;
	calibatedPRed=NULL;
	delete []calbratedThresArr ;
	calbratedThresArr=NULL;
	delete []calbAgDepArr ;
	calbAgDepArr=NULL;
	delete []calbCntArr  ;
	calbCntArr=NULL;
	delete [] bucketIndexArr;
	bucketIndexArr=NULL;
}


void cResearchObject::TestAndScore(cScoreGrpArr &scoresGrp, cProfileObject* profile )
{

}

void cResearchObject::CancelProfSubVAlues(double* predAdd , cProfileObject* profile, int sIndex,int numOfItems,
	                                 cResearchDataObj* researchDataObj, int recommendedSample)
{
	bool* isInThisProfSub = new bool[numOfItems];
	int countt = FillIsInProfSub(isInThisProfSub,profile, sIndex, researchDataObj,NULL);
	//double* tempPredIn = new double[ researchDataObj->m_numOfItems];
	int mode = 1;
	if(recommendedSample < countt)
	{
		mode = countt / recommendedSample;
	}
	int movingIndex = 0;
	int random = rand() % 31 ;//wil allow  ( (movingIndex + random )% mode) to be different each time we get to this profsub. since 
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ;i++)
	{
		//int toEnterr =  ( i % mode) == 0;//if mode is
		if(isInThisProfSub[i])
		{
			bool toIncludeMemberInZeroying =  ( (movingIndex + random )% mode) == 0;//if random is between 0 and 30 (%31)than amount of movingIndex progress
			//is the same but the members getting i will be different. need to check
			movingIndex++;
			if(toIncludeMemberInZeroying)
			{
				predAdd[i]=0.0;
			}
		}
	}
	delete []isInThisProfSub;
}

void cResearchObject::SecondRoundOfMLtry3(// cScoreGrpArr &scoresGrp, 
	double &correlScore ,double*  predArrOutt, 
		cResearchDataObj* researchDataObj , cProfileObject* anchorForStretch, cProfileObject* root,
		cGlobals* globals, 	
		cProfileObject* thisProfToPlayWith, int numOfCalibrationGrps , cEvolutionProfilePAckage**  evolPackage, 
		double* stretArr,   double* savingTimeArrInn,  double startScsore, int sIndex	)
{
 	SwapAndPredictionCover2(correlScore, predArrOutt,  evolPackage,
	 root,  anchorForStretch,  globals,  stretArr,  savingTimeArrInn, researchDataObj,   numOfCalibrationGrps,-1,0,NULL);
}


void cResearchObject::SwapAndPredictionCover2(double &correlScore,double* predArrOutt, cEvolutionProfilePAckage** evolPackage,
	cProfileObject* root, cProfileObject* anchorForStretch, cGlobals* globals, double* stretArr, double* savingTimeArrInn,
	cResearchDataObj* researchDataObj,  int numOfCalibrationGrps, int inputTargetedProfileID , 
	int inputTargetSample	, double* backUpArrWithAllPastPredictions )
{
	double* calibatedPRed = new double[ researchDataObj->m_numOfItems] ;
	double* calbratedThresArr = new double[numOfCalibrationGrps];//
	double* calbAgDepArr = new double[numOfCalibrationGrps];
	int* calbCntArr  = new int[numOfCalibrationGrps];
	int* bucketIndexArr = new int[researchDataObj->m_numOfItems];
	 
		 
	bool isToDoAnyCalibration = false;
	double perf2 = cResearchObject::SwapProfilesWithAnchors2(//NULL,
			predArrOutt,
			 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,
			 researchDataObj,  evolPackage,	m_profileListSize,   root , anchorForStretch,globals, 0 , stretArr,
				false, savingTimeArrInn,  isToDoAnyCalibration,	  inputTargetedProfileID ,  inputTargetSample	,  backUpArrWithAllPastPredictions 	);
	
	correlScore = cVarianceCalc::CalcualteETA(predArrOutt , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	
	delete []calibatedPRed;
	calibatedPRed=NULL;
	delete []calbratedThresArr ;
	calbratedThresArr=NULL;
	delete []calbAgDepArr ;
	calbAgDepArr=NULL;
	delete []calbCntArr  ;
	calbCntArr=NULL;
	delete [] bucketIndexArr;
	bucketIndexArr=NULL;

 }









//1 14 24 see that for every profile adjustment we do the test again
void cResearchObject::SecondRoundOfMLtry2( double* movingSavingTimeArrOutt,double &movingScore, 
		cResearchDataObj* researchDataObj , cProfileObject* root, cProfileObject* anchorForStretch, bool* isPredictive,  cGlobals* globals,
		cVariableSchemaArr* schemaArr,	cPercentileCalculationModel* rootOddPredictiveModel, 
		cPercentileCalculationModel* regPredictiveModell, InputVariablesPackageForResearchObj* inputVarObj, 
		cProfileObject* thisProfToPlayWith, int numOfCalibrationGrps , cEvolutionProfilePAckage**  evolPackage, 
		double* stretArr, bool isThisCaseOfAnchorUniverse6,  double* savingTimeArrInn	)
{
	
	double* calibatedPRed = new double[ researchDataObj->m_numOfItems] ;
	double* calbratedThresArr = new double[numOfCalibrationGrps];//
	double* calbAgDepArr = new double[numOfCalibrationGrps];
	int* calbCntArr  = new int[numOfCalibrationGrps];
	int* bucketIndexArr = new int[researchDataObj->m_numOfItems];
	 
	
	//keep current perf weights befoer doingi anything to get it back if needed
	double advPerfArrCurrent[100];
	thisProfToPlayWith->CopyAdvPerfArrOut(advPerfArrCurrent );
		
	int numOfSubGrps = thisProfToPlayWith->GetNumberOfSubGroups();
	double advPerfNew[100];

	double lastETA = 0.0;

	for(int asd = 0 ; asd < numOfSubGrps ; asd ++)
	{
		double etaNEW0 = cVarianceCalc::CalcualteETA(savingTimeArrInn , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	
		bool* isInThisProfSub = new bool[researchDataObj->m_numOfItems];
		int countt = FillIsInProfSub(isInThisProfSub,thisProfToPlayWith, asd, researchDataObj,NULL);
		double* tempPredIn = new double[ researchDataObj->m_numOfItems];
		
		
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			tempPredIn[i] = savingTimeArrInn[i] ;
			if(isInThisProfSub[i])
			{
				tempPredIn[i]=0.0; 
			}
		}
		double currentWeight =  thisProfToPlayWith->GetProfileAdvancedPerformance(asd);
		//1 14 24 
		thisProfToPlayWith->SetProfileAdvancedPerformance(asd, 0.001);
		double* tempPredArr = new double[researchDataObj->m_numOfItems];
		double perf2 = cResearchObject::SwapProfilesWithAnchors2(//NULL,
			tempPredArr,
			 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,
			 researchDataObj,  evolPackage,
						m_profileListSize,   root , anchorForStretch,globals, 0 , stretArr,
						isThisCaseOfAnchorUniverse6, tempPredIn,  true, -1,0,NULL);
		double etaNEW1 = cVarianceCalc::CalcualteETA(tempPredArr , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
		//1 14 24 compare with below after adjustment and adjust movingScore
		if(lastETA != 0.0 && lastETA != etaNEW1)
		{
			int sdgg=0;//shuld not get gere
		}

		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			tempPredIn[i] = savingTimeArrInn[i] ;
			if(isInThisProfSub[i])
			{
				tempPredIn[i]=0.0; 
			}
		}
	
/////////////////////////////
		double multiplier = 2.0;
		thisProfToPlayWith->SetProfileAdvancedPerformance(asd, 10.0);
		double perf0 =  cResearchObject::SwapProfilesWithAnchors2(tempPredArr,
			 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,
			 researchDataObj,  evolPackage,
						m_profileListSize,   root , anchorForStretch,globals, 0 , stretArr,
						isThisCaseOfAnchorUniverse6, tempPredIn,  true, -1,0,NULL);
		double etaNEW2 = cVarianceCalc::CalcualteETA(tempPredArr , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
		if(etaNEW2 > etaNEW1 ){
			double gap  = (etaNEW2 - etaNEW1) /countt;
			gap*=10;
			thisProfToPlayWith->SetProfileAdvancedPerformance(asd, (currentWeight* gap) + currentWeight);

			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				tempPredIn[i] = savingTimeArrInn[i] ;
				if(isInThisProfSub[i])
				{
					tempPredIn[i]=0.0; 
				}
			}
			double perf10 =  cResearchObject::SwapProfilesWithAnchors2(tempPredArr,
			 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,
			 researchDataObj,  evolPackage,
						m_profileListSize,   root , anchorForStretch,globals, 0 , stretArr,
						isThisCaseOfAnchorUniverse6, tempPredIn,  true, -1,0,NULL);
			double etaNEW3 = cVarianceCalc::CalcualteETA(tempPredArr , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
			if(etaNEW3 > etaNEW0)
			{

				//keep the currentWeight * multiplier as tried and succeed
				cout << "improved eta \n";
				cout << etaNEW3 ;
				cout << " \n";
			
				lastETA = etaNEW3 ;
				int sdsg=0;
			 
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					if(isInThisProfSub[i])
					{
						savingTimeArrInn[i]=tempPredArr[i]; 
					}
					movingSavingTimeArrOutt[i] = savingTimeArrInn[i] ;
				}
			}
			else
			{
				thisProfToPlayWith->SetProfileAdvancedPerformance(asd, currentWeight );//* (1.0/multiplier) );
			}		
		}		
		delete []isInThisProfSub;
		isInThisProfSub=NULL;
		delete []tempPredIn;
		tempPredIn=NULL;
		delete []tempPredArr;
		tempPredArr=NULL;
	}
	delete []calibatedPRed;
	calibatedPRed=NULL;
	delete []calbratedThresArr ;
	calbratedThresArr=NULL;
	delete []calbAgDepArr ;
	calbAgDepArr=NULL;
	delete []calbCntArr  ;
	calbCntArr=NULL;
	delete [] bucketIndexArr;
	bucketIndexArr=NULL;
}

/*
double point_biserial_correlation(int n, double mean1, double mean0, double sd, double sum1, double sum0) {
    double rpb = (mean1 - mean0) * sqrt(n) / (sd * sqrt(sum1 + sum0));
    return rpb;
}

int main() {
    int n = 100;
    double mean1 = 10.5;
    double mean0 = 8.2;
    double sd = 2.5;
    double sum1 = 200;
    double sum0 = 150;

    double rpb = point_biserial_correlation(n, mean1, mean0, sd, sum1, sum0);
    printf("The point-biserial correlation coefficient is: %.4f\n", rpb);

    return 0;
}
*/
/*
double point_biserial_correlation(int n, double mean1, double mean0, double sd, double sum1, double sum0) {
    double rpb = (mean1 - mean0) * pow(double(n), 0.5) / (sd * sqrt(sum1 + sum0));
    return rpb;
}*/


/*
double cResearchObject::CalcualteETA(double* predArr, double* depArr, int size)
{
	
//	LinearRegressionInternalDoubleAPI( double &averageSE, double &variance, double & zeroConstant, 
//		double * betaArr , double& regressionPerformanceScore,double * predicted_dependentArr,
//							double **predictiveArr,	unsigned int N, 
//			unsigned int p,  double * dependentArr, double * predictabilityScores , 
//			unsigned int sizeOfTestGroup, bool isControlGroupp, bool isLogisticReg)

	double* wghArr = new double[size];
	double sum1=0.0;
	double sum0=0.0;
	for(int i = 0 ; i < size ; i++)
	{
		wghArr[i]=0.0;
		if(depArr[i]==0.0)
		{
			wghArr[i]=1.0;
			sum0 += predArr[i];
		}
		sum1 +=  predArr[i];
	}

	double mean0 = 0.0;
	double var0 = 0.0;
	cVarianceCalc::CalculateMeanAndVariance(mean0,var0,predArr,wghArr,size);
	double sd0=pow(var0,0.5);

	
	for(int i = 0 ; i < size ; i++)
	{
		wghArr[i]=0.0;
		if(depArr[i]==1.0)
		{
			wghArr[i]=1.0;
		}
	}
	double mean1 = 0.0;
	double var1 = 0.0;
	cVarianceCalc::CalculateMeanAndVariance(mean1,var1,predArr,wghArr,size);
	double sd1=pow(var1,0.5);
		
	
	double mean = 0.0;
	double var = 0.0;
	cVarianceCalc::CalculateMeanAndVariance(mean,var,predArr,NULL,size);
	double sd=pow(var,0.5);
	
	double eta = cVarianceCalc::point_biserial_correlation(size,  mean1,  mean0, sd, sum1,  sum0);

	return eta;
	*/
	////////////////////////////////////
	/*
	double meanDep = 0.0;
	double varDep = 0.0;
	cVarianceCalc::CalculateMeanAndVariance(meanDep,varDep,depArr,NULL,size);
	double sdDep = pow(varDep,0.5);

	double sumErr=0.0;
	for(int i = 0 ; i < size ; i++ )
	{
		sumErr 	+= (predArr[i]-meanPred)*(depArr[i]-meanDep);
	}
	double avgErr = sumErr / size;

	double eta1= avgErr / (sdPred * sdDep ) ;

	double eta2 = 0.0;
	for(int i = 0 ; i < size ; i++ )
	{


	}
	return eta1;*/
//}


int cResearchObject::ClearAllProfileAdvPerformance(cEvolutionProfilePAckage*  evolPackage)
{
	int numOfLevels = evolPackage->ClearProfilesAdvancedPerfScores(0.0);
	return numOfLevels;
}

void cResearchObject::SetValueToAllProfileAdvPerformance(cEvolutionProfilePAckage*  evolPackag,  double val)
{
	evolPackag->SetProfilesAdvancedPerfScores(val);
}

	

int cResearchObject::ClearAllProfileAdvPerformance(cEvolutionProfilePAckage*  evolPackage, double val)
{
	int numOfLevels = evolPackage->ClearProfilesAdvancedPerfScores(val);
	return numOfLevels;
}

int cResearchObject::FindHighestLevel(cEvolutionProfilePAckage*  evolPackage)
{
	int numOfLevels = evolPackage->FindHieghtsLevel( );
	return numOfLevels;
}



int cResearchObject::CollectProfilesFromLevel( cProfileObject** pArr, int level, int maxProfNum , cEvolutionProfilePAckage*  evolPackage)
{
	int x = evolPackage->CollectProfilesFromLevelInput( pArr,  level,  maxProfNum);
	return x;
}


void cResearchObject::RemoveProfilesWithAllSubGroupsZero(cEvolutionProfilePAckage*  evolPackageObj)
{
	int movingIndex=0;
	for(int i = 0 ; i < evolPackageObj->m_proffListSize ; i++)
	{
		if( i > 0 && evolPackageObj->m_profList[i]->AreAllBucketsZero())
		{
			delete evolPackageObj->m_profList[i];
			evolPackageObj->m_profList[i]=NULL;
		}
		else
		{
			evolPackageObj->m_profList[movingIndex++]= evolPackageObj->m_profList[i];
		}
	}
	evolPackageObj->m_proffListSize = movingIndex;
}

//1  20 24
/* -add input cScoreGrpArr** twoDimScoreGrp array for all levels of profiles. 
-create this befoer callingfirst call it is null. 
-if not null than use this instead  pArr[d]->UpdatePerformanceArrays(1.0) use pArr[d]->UpdatePerformanceArrays(twoDimScoreGrp[l][d]);

*/
void cResearchObject::PlayWithOneLevelWeightAnalytics(cScoreGrpArr** scoresGrpArr, int* perLevelProfNum,
	cEvolutionProfilePAckage* evol  , int l,  int maxProfNum,
	cResearchDataObj* researchDataObj, cProfileObject* anchor,  cProfileObject* root, cGlobals* globals,
	cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps,  double movingScre, double* stretArr, bool isToOnlyCheckPositiveWeights	)
	

{
	cProfileObject** pArr = new cProfileObject*[maxProfNum];
					//cScoreGrpArr* scoresGrp = new cScoreGrpArr[maxProfNum];
	int numOfProfs=  CollectProfilesFromLevel(pArr, l, maxProfNum , evol);
	for(int d=0;d<numOfProfs;d++)
	{
		if(scoresGrpArr != NULL)
		{
			//SetProfileAdvancedPerformance(cScoreGrpArr &scoresGrp)
			pArr[d]->UpdatePerformanceArrays(scoresGrpArr[l][d]);
		}
		else
		{
			pArr[d]->UpdatePerformanceArrays(0.0);
		}
	}				
				
	double* movingSavingTemp = new double[researchDataObj->m_numOfItems];
	double* newPredictionarr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		movingSavingTemp[i]=0.0;//1 20 24 * add that after the first profile from this level of analtics i alread have the all predeidction set to save perf for all sub gruops not only the second
		newPredictionarr[i]=0.0;
	}
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		cScoreGrpArr scoresGrp (pArr[x]);
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			//1 20 24 * call after few levels :: 
			if((!isToOnlyCheckPositiveWeights)  || (pArr[x]->GetProfileAdvancedPerformance(s) > 0.0))
			{// only if true do this whole itration			 
				CancelProfSubVAlues(movingSavingTemp , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);
				pArr[x]->SetProfileAdvancedPerformance(s , 0.0);//1  20 24 * if scoresGrp.scorearr[s]==0.0 already than we dont do this whole work and move to the next s
				double eta0 = 0.0;//TestPerformance();
				double* movingTemp = new double[researchDataObj->m_numOfItems];
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					movingTemp[i]=0.0;
				}
				SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x], 
					numOfCalibrationGrps ,   evolArr, 	stretArr,    movingSavingTemp, movingScre,s	);
				{
					for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
					{
						movingTemp[i]=newPredictionarr[i];
					}
				}					
				double wghCurrentOr1 = 1.0;
				if(scoresGrp.m_scoreArr[s] != 0)
				{
					wghCurrentOr1 = scoresGrp.m_scoreArr[s];
				}
				CancelProfSubVAlues(movingSavingTemp , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);
				pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1);
				double etaCurrenrOr1 =0.0;// 
				SecondRoundOfMLtry3( etaCurrenrOr1, newPredictionarr, researchDataObj ,   anchor,  root,   globals, pArr[x], 
					numOfCalibrationGrps ,   evolArr, 	stretArr,    movingSavingTemp, movingScre,s	);
				
				if(etaCurrenrOr1 > eta0)
				{
					//double* temp = new double[researchDataObj->m_numOfItems];
					for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
					{
						movingTemp[i]=newPredictionarr[i];
					}
					double wghCurrentOr1Times2 = wghCurrentOr1 * 2;
					pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1Times2);
					CancelProfSubVAlues(movingSavingTemp , pArr[x], s,  researchDataObj->m_numOfItems, researchDataObj);
					double etaCurrenrOr2 =0.0;// TestPerformance();
					SecondRoundOfMLtry3( etaCurrenrOr2, newPredictionarr,researchDataObj ,   anchor,  root,   globals, 
						pArr[x],  numOfCalibrationGrps ,   evolArr, stretArr,    movingSavingTemp, movingScre, s	);
					
					if(etaCurrenrOr2 > etaCurrenrOr1)
					{
						pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1Times2);
						for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
						{
							movingTemp[i]=newPredictionarr[i];
						}
						cout << "new eta etaCurrenrOr2 \n";
						cout<< etaCurrenrOr2;
						cout << " \n";
					}
					else
					{
						pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1);
						cout << "new eta etaCurrenrOr1 \n";
						cout<< etaCurrenrOr1;
						cout << " \n";
					}
				}
				else
				{
					pArr[x]->SetProfileAdvancedPerformance(s , 0.0);
					cout << "new eta eta0\n";
					cout<< eta0;
					cout << " \n";
				}
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					movingSavingTemp[i]=movingTemp[i];
				}
				delete []movingTemp;
				movingTemp=NULL;
			}
		}
	}
	delete[]pArr;
	pArr=NULL;
	delete []movingSavingTemp;
	movingSavingTemp=NULL;
	delete []newPredictionarr;
	newPredictionarr=NULL;	


	cout << "end of PlayWithOneLevelWeightAnalytics() \n";
}

double  cResearchObject::RotateProfilePerf(double &outRank,double &points, cResearchDataObj*  researchDataObj,  cProfileObject* profile,  int s,
	 cProfileObject* anchor,   cProfileObject* root, cGlobals*  globals,  int numOfCalibrationGrps, cEvolutionProfilePAckage** evolArr,
	 double*  stretArr, double* predWithZeroedLevelOrNULL,  double  scoreNow,  double scoreNowPlus)//, int movingScre,  cScoreGrpArr &scoreGrpobjstart)
	
	 ///scoreGrpobjAdj gets iniatlied as zero and gets the results of this one rotation
{
	double* newPredictionarr = new double[researchDataObj->m_numOfItems];


//	double scoreOff=0.0;
	profile->SetProfileAdvancedPerformance(s , scoreNow);
	double eta0 = 0.0;//
	double movingScre=0.0;
	SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, profile,  numOfCalibrationGrps ,
				evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
 
//	double scoreOn=1.0;
	profile->SetProfileAdvancedPerformance(s , scoreNowPlus);
	double etaOn = 0.0;//
	SecondRoundOfMLtry3( etaOn, newPredictionarr, researchDataObj ,  anchor,  root,   globals, profile,  numOfCalibrationGrps ,
				evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
	 
	if(etaOn > eta0)
	{
		cout <<"etaOn \n";
		cout<<etaOn;
		cout <<" \n";
		points =   1.0;//1 23 24 conside to have etaOn > eta0 to use for tanking between both calling to analytic level fucntion 
	}	
	else
	{
		points = 0.0;//cVarianceCalc::Max(  ( scoreNow-1.0) , 0.0);
	}

	outRank = etaOn - eta0;

//	profile->SetProfileAdvancedPerformance(s , 0);
	
	delete []newPredictionarr;
	newPredictionarr=NULL;

	double higihtsPErfValue = cVarianceCalc::Max(etaOn, eta0);
	return higihtsPErfValue;
}

/*
void cResearchObject::UpdateProfilesWithOutputWeights(  cScoreGrpArr* scoresGrpArrOut   ,int numOfProfs,  cProfileObject** pArr, 
	double* newPredictionarr,	cEvolutionProfilePAckage** evolArr,   cResearchDataObj* researchDataObj, int numOfCalibrationGrps, 
	double* stretArr,	cGlobals* globals, cProfileObject* anchor, cProfileObject* root)
{
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			pArr[x]->UpdatePerformanceArrays(scoresGrpArrOut[x]) ;
		}
	}

	double correlScore=0.0;
	SwapAndPredictionCover(correlScore, newPredictionarr,  evolArr,
		 root,  anchor,  globals,  stretArr,  NULL, researchDataObj,   numOfCalibrationGrps);
	cout<< "end of one level analytics : ";
	//cout <<l;
	cout << "\n";
	cout << correlScore;
	cout << "\n";
	 
}
*/


double cResearchObject::OneProfsubOrderedProcecss( cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							double* startingPointArrr,  int profIndex,  int s)
	{
		double endOfProcessBP=0.0;
		double* savlingTime = new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			savlingTime[i] = startingPointArrr[i];
		}				
			
			
		CancelProfSubVAlues(savlingTime ,profile, s, researchDataObj->m_numOfItems, researchDataObj);
		double initiValue = 0.0;
		if(oneLevelScoreGro != NULL)
		{
			initiValue = oneLevelScoreGro[profIndex].m_scoreArr[s];
		}
		profile->SetProfileAdvancedPerformance(s , initiValue);
		double  init1Try = 0.0;
		double* prediction1= new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			prediction1[i]=0.0;
		}
		SwapAndPredictionCover2(init1Try, prediction1,  evolArr,
				root,   evol->m_anchor,  globals,  statArr,  savlingTime, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
		double tryValue = initiValue + 1.0;
		profile->SetProfileAdvancedPerformance(s , tryValue);
			
			
		double initial2Try=0.0;
		double* prediction2= new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			prediction2[i]=0.0;
		}			
		SwapAndPredictionCover2(initial2Try, prediction2,  evolArr,
				root,   evol->m_anchor,  globals,  statArr,  savlingTime, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
		
		if(init1Try> initial2Try )
		{
			profile->SetProfileAdvancedPerformance(s , initiValue);
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction1[i];
			}
			endOfProcessBP = init1Try;
		}
		else
		{
			profile->SetProfileAdvancedPerformance(s , tryValue);
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction2[i];
			}
			endOfProcessBP = initial2Try;
			cout << "founs better bp : " ;
			cout<< initial2Try;
			cout << "\n";

		}
		delete []savlingTime;
		delete []prediction1;
		delete []prediction2;
		return endOfProcessBP;
	}


double cResearchObject::OneProfsubOneWeight2(double* prediction, cResearchDataObj* researchDataObj, int s,   double wghValue,  cProfileObject* profile,
	cProfileObject* root,	 cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps, cGlobals* globals,cEvolutionProfilePAckage* evol, 
	 double* statArr, double* savingTimeArr , int profileIdTested, int lowestSampleSizeTest, double* fullPredictionPreviousSet)
{
		profile->SetProfileAdvancedPerformance(s , wghValue);
		double  outVal = 0.0;
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			prediction[i]=0.0;
		}
		SwapAndPredictionCover2(outVal, prediction,  evolArr,
				root,   evol->m_anchor,  globals,  statArr,  savingTimeArr, researchDataObj,   numOfCalibrationGrps, 
				  profileIdTested,  lowestSampleSizeTest,  fullPredictionPreviousSet);
				//-1,0,NULL);
		
		return outVal;
}	

double cResearchObject::OneProfsubOneWeight(double* prediction, cResearchDataObj* researchDataObj, int s,   double wghValue,  cProfileObject* profile,
	cProfileObject* root,	 cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps, cGlobals* globals,cEvolutionProfilePAckage* evol, 
	 double* statArr, double* savingTimeArr)
{
		profile->SetProfileAdvancedPerformance(s , wghValue);
		double  outVal = 0.0;
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			prediction[i]=0.0;
		}
		SwapAndPredictionCover2(outVal, prediction,  evolArr,
				root,   evol->m_anchor,  globals,  statArr,  savingTimeArr, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
		
		return outVal;
}	

double cResearchObject::OneProfsubOrderedProcecss2( cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							double* startingPointArrr,  int profIndex,  int s)
	{
		double endOfProcessBP=0.0;
		double* savlingTime = new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			savlingTime[i] = startingPointArrr[i];
		}				
			
			
		CancelProfSubVAlues(savlingTime ,profile, s, researchDataObj->m_numOfItems, researchDataObj);
	
		
		
		
		double tryValue0 = 0.0;
		if(oneLevelScoreGro != NULL)
		{
			tryValue0 = oneLevelScoreGro[profIndex].m_scoreArr[s];
		}

		double tryval_1 = tryValue0 /2.0;	
		double* prediction_1 = new double[researchDataObj->m_numOfItems ];
		double  i_1Try = 0.0;
		if(tryValue0 > 0.0)
		{
			i_1Try = OneProfsubOneWeight(prediction_1, researchDataObj,  s,    tryval_1,   profile,
				 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 
				 statArr,  savlingTime);
		}
		
		double* prediction0 = new double[researchDataObj->m_numOfItems ];
		double  i0Try =  OneProfsubOneWeight(prediction0, researchDataObj,  s,    tryValue0,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 
			 statArr,  savlingTime);

		double tryValue1 = tryValue0 + 1.0;
		double* prediction1 = new double[researchDataObj->m_numOfItems ];
		double i1Try= OneProfsubOneWeight(prediction1, researchDataObj,  s,    tryValue1,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 	 statArr,  savlingTime);
			
		double tryValue2 = tryValue1 + 1.0;
		double* prediction2 = new double[researchDataObj->m_numOfItems ];
		double i2Try= 0.0;
		if(i1Try> i0Try )
		{
			i2Try = OneProfsubOneWeight(prediction2, researchDataObj,  s,    tryValue2,   profile,
				 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 	 statArr,  savlingTime);
		}
	
		if(i1Try> i0Try )
		{
			if(i2Try> i1Try )
			{	
				profile->SetProfileAdvancedPerformance(s , tryValue2);
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					startingPointArrr[i]=prediction2[i];
				}
				endOfProcessBP = i2Try;
				cout << "found better bp : " ;
				cout<< endOfProcessBP;
				cout << "\n";
			}
			else
			{
				profile->SetProfileAdvancedPerformance(s , tryValue1);
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					startingPointArrr[i]=prediction1[i];
				}
				endOfProcessBP = i1Try;	
				cout << "found better bp : " ;
				cout<< endOfProcessBP;
				cout << "\n";
			}
		}
		else
		{
			if(i_1Try > i0Try)
			{
				profile->SetProfileAdvancedPerformance(s , tryval_1);
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					startingPointArrr[i]=prediction_1[i];
				}
				endOfProcessBP = i_1Try;	
				cout << "found better down bp : " ;
				cout<< endOfProcessBP;
				cout << "\n";
			}
			else
			{
				profile->SetProfileAdvancedPerformance(s , tryValue0);
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					startingPointArrr[i]=prediction0[i];
				}
				endOfProcessBP = i0Try;	
			}
		}
	 
		
		delete []savlingTime;
		delete []prediction0;
		delete []prediction1;
		delete []prediction2;
		return endOfProcessBP;
	}

	
bool cResearchObject::OneProfsubOrderedProcecss3( double &endOfProcessBP , cProfileObject* profile, int* rankArr,  int* rankArrWithSub, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							double* startingPointArrr,  int profIndex,  int s)
	{
		endOfProcessBP=0.0;
		double* savlingTime = new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			savlingTime[i] = startingPointArrr[i];
		}				
			
		CancelProfSubVAlues(savlingTime ,profile, s, researchDataObj->m_numOfItems, researchDataObj,800);
		
		double tryValue0 = 0.0;
		if(oneLevelScoreGro != NULL)
		{
			tryValue0 = oneLevelScoreGro[profIndex].m_scoreArr[s];
		}
		double* prediction0 = new double[researchDataObj->m_numOfItems ];
		double  i0Try =  OneProfsubOneWeight(prediction0, researchDataObj,  s,    tryValue0,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol,  statArr,  savlingTime);

		double tryValue1 = tryValue0 + 1.0;
		double* prediction1 = new double[researchDataObj->m_numOfItems ];
		double i1Try= OneProfsubOneWeight(prediction1, researchDataObj,  s,    tryValue1,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 	 statArr,  savlingTime);
		bool isImproved= false;
		if(i1Try> i0Try )
		{
			isImproved = true;
			profile->SetProfileAdvancedPerformance(s , tryValue1);
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction1[i];
			}
			endOfProcessBP = i1Try;	
			cout << "found better bp : " ;
			cout<< endOfProcessBP;
			cout << "\n";
		}
		else
		{
			profile->SetProfileAdvancedPerformance(s , tryValue0);
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction0[i];
			}
			endOfProcessBP = i0Try;	
		}	 
		
		delete []savlingTime;
		delete []prediction0;
		delete []prediction1;
	//	delete []prediction2;
		return isImproved;
	}


bool cResearchObject::SelectIfToTryInThisCase(double baseValue, bool isFirstGlobalItration, int random)
{
	if(baseValue == 0.0  && (!isFirstGlobalItration ))//3 24 24
		////todo 3 25 24 record profiles that had higher success compare to the size of the population
		//and invest more there
	{
		if((random % 5 ) != 0)
		{	
			return false;
		}//most of the cases will return false, 1 to 5 it will continue and process 
	}
	return true;
}	

bool cResearchObject::OneProfsubOrderedProcecss5( double &endOfProcessBP ,double* startingPointArrr, cProfileObject* profile, 
	int* rankArrr,  int* rankArrWithSubb, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
					int profIndex,  int s,  int iterIndex, double inputMovingPerf, 
					 int levelForPrint, int w, bool isFirstGlobalItration, bool isUp , int globalIterationIndex)
	{
		bool isWeightUpdated = false;
		double baseValue = 0.0;
		baseValue = profile->GetProfileAdvancedPerformance(s);
		int random = ((profIndex + s + iterIndex + w ) * levelForPrint * iterIndex) ;
		bool isToProcess = SelectIfToTryInThisCase(baseValue, isFirstGlobalItration, random);
		if(!isToProcess)
		{
			return false;
		}
		double* savlingTime = new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			savlingTime[i] = startingPointArrr[i];
		}		
		//only   profsub pop, of some of it, will be removed from the savlingTime
		CancelProfSubVAlues(savlingTime ,profile, s, researchDataObj->m_numOfItems, 
												researchDataObj,PROFSUB_RECOMENDED_SAMPLE_SIZE); 
		double tryValue = baseValue;
		if(isUp )
		{
			tryValue += 1.0;
		}
		else
		{
			tryValue -= 1.0;
		}
		double* prediction1 = new double[researchDataObj->m_numOfItems ];
		double i1Try= OneProfsubOneWeight(prediction1, researchDataObj,  s,    tryValue,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 	 statArr,  savlingTime);
		int cntOFDifferenceCases=0;
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			if(prediction1[i] != startingPointArrr[i])
			{
				cntOFDifferenceCases++;
			}
		}

		int minSAmplesizeForProfsubLearningConcousion=20;
		if((cntOFDifferenceCases >= minSAmplesizeForProfsubLearningConcousion) && i1Try> inputMovingPerf ) // >= and not only > since a profile can find that it did not matter to have a higher weigh//and perhaps a next level chance can be easier achived when a progroess of weight 
		{
			isWeightUpdated = true;
			profile->SetProfileAdvancedPerformance(s , tryValue);
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction1[i];
			}
			endOfProcessBP = i1Try;	
			cout << "\nFOUND BETTER BP :  " ;
			cout<< endOfProcessBP;
			cout <<"\n globalIterationIndex: ";
			cout<<globalIterationIndex;
			cout<<"\n level: ";
			cout<<  levelForPrint;//, int w
			cout << "\n internalIterIndex :";
			cout<<iterIndex;
			cout << "\n";
			cout<< "W :";
			cout<<w;
			cout << "\n is up: " ;
			cout << isUp ;
			cout << "\n\n";
		}
		else{
			profile->SetProfileAdvancedPerformance(s , baseValue);
		}
		delete []savlingTime;
		//delete []prediction0;
		delete []prediction1;
		return isWeightUpdated;
	}



bool cResearchObject::OneProfsubOrderedProcecss6(int &cntOFDifferenceCases, double &endOfProcessBP ,double* startingPointArrr, cProfileObject* profile, 
	int* rankArrr,  int* rankArrWithSubb, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
					int profIndex,  int s,  int iterIndex, double inputMovingPerf, 
					 int levelForPrint, int w, bool isFirstGlobalItration, bool isUp , int globalIterationIndex, 
					 int profSubHighestSampleTry, int profileIdTested, int lowestSampleSizeTest,
					 double* fullPredictionPreviousSet, bool isToUPdateProfsubStatusAndPredictionarray, int indexInRaw, int sizeOfRaw)
	{
		bool isWeightUpdated = false;
		double baseValue = profile->GetProfileAdvancedPerformance(s);
		double* savlingTime = new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			savlingTime[i] = startingPointArrr[i];
		}		
		//only   profsub pop, of some of it, will be removed from the savlingTime
		CancelProfSubVAlues(savlingTime ,profile, s, researchDataObj->m_numOfItems, 	researchDataObj,profSubHighestSampleTry); 
		double tryValue = baseValue;
		if(isUp )
		{
			tryValue += 1.0;
		}
		else
		{
			tryValue -= 1.0;
		}
		double* prediction1 = new double[researchDataObj->m_numOfItems ];
		double i1Try= OneProfsubOneWeight2(prediction1, researchDataObj,  s,    tryValue,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 	 statArr,  savlingTime,
			 profileIdTested,	 lowestSampleSizeTest,	 fullPredictionPreviousSet );
		cntOFDifferenceCases=0;
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			if(prediction1[i] != startingPointArrr[i])
			{
				cntOFDifferenceCases++;
			}
		}
		if((i1Try> inputMovingPerf))//|| ( !isUp && (i1Try== inputMovingPerf))) // >= and not only > since a profile can find that it did not matter to have a higher weigh//and perhaps a next level chance can be easier achived when a progroess of weight 
		{
			isWeightUpdated = true;
			//3 30 24 change the below if to this one. the caller function need to open two places where it catch, if that count is low no need to call here again
			//if(isToUPdateProfsubStatusAndPredictionarray || (cntOFDifferenceCases < lowestSampleSizeTest))
			if(isToUPdateProfsubStatusAndPredictionarray)
			{
				profile->SetProfileAdvancedPerformance(s , tryValue);
				if(cntOFDifferenceCases >0)
				{
					for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
					{
						startingPointArrr[i]=prediction1[i];
					}
				}
				endOfProcessBP = i1Try;	
			}
			else
			{	 
				profile->SetProfileAdvancedPerformance(s , baseValue);
			}
			cout << "\nFOUND BETTER BP :  " ;
			cout<< i1Try;
			cout<<"\n count of differences: ";
			cout<<cntOFDifferenceCases;
			cout <<"\n globalIterationIndex: ";
			cout<<globalIterationIndex;
			cout<<"\n level: ";
			cout<<  levelForPrint;//, int w
			cout << "\n internalIterIndex :";
			cout<<iterIndex;
			cout << "\n";
			cout<< "W :";
			cout<<w;
			cout << "\n is up: " ;
			cout << isUp ;
			cout << "\n number of profiles in level :";
			cout << sizeOfRaw  ;//, int sizeOfRaw
			cout << "\n this profile index in level :";
			cout <<  indexInRaw;
			cout << "\n\n";
		}
		else{
			profile->SetProfileAdvancedPerformance(s , baseValue);
			isWeightUpdated=false;
		}
		delete []savlingTime;
		//delete []prediction0;
		delete []prediction1;
		return isWeightUpdated;
	}


	
bool cResearchObject::OneProfsubOrderedProcecss4( double &endOfProcessBP ,double* startingPointArrr, cProfileObject* profile, 
	int* rankArrr,  int* rankArrWithSubb, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro,
							   int profIndex,  int s,  int iterIndex, double inputMovingPerf, 
							   int levelForPrint, int w, bool isToTryGoDown)
	{
		//if(iterIndex == ITERATION_TO_MAKE_STOP_DECISION){
		endOfProcessBP=0.0;
		double tryValue0 = 0.0;
		tryValue0 = profile->GetProfileAdvancedPerformance(s);
		if(tryValue0 == 0.0 && iterIndex > ITERATION_TO_MAKE_STOP_DECISION)//3 24 24
			//1)replace iterIndex > ..  with a 
			//flag that is sent from aabove and if global iteration is more than 0 we will send a true.
			//it is more for speed. a next version of that is that the random below is giving higher chance for profsubs
			//that shows success before to get selected again.
		{//means we have gone through the decision stage and still have weight of 0, in this case we can give up	
			//2 reduce the number of testing patietns to less than 1000 but randomize the selection ibetween tests
			//record profiles that had higher success compare to the size of the population and invest more there
			//get the last score of this function from last time, if it is not 0 than we can save the tryVAlue0 call.
			//can then just call plus 1 and see if any better, then if not try to call one below, see if any better,,  
			//and then we can have eitehr same, more, or less
			//if initialy there is not previous take care and we get perf == 0 than take care of that too
			int random = ((profIndex + s + iterIndex + w ) * levelForPrint * iterIndex) ;
			if((random % 11 ) != 0)
			{
				endOfProcessBP = inputMovingPerf;	
				return false;
			}//most of the cases will return, 1 to 11 it will continue and check 
		}
		double* savlingTime = new double[researchDataObj->m_numOfItems];
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			savlingTime[i] = startingPointArrr[i];
		}				
		CancelProfSubVAlues(savlingTime ,profile, s, researchDataObj->m_numOfItems, researchDataObj,
			PROFSUB_RECOMENDED_SAMPLE_SIZE); 
			//oneLevelScoreGro[profIndex].m_scoreArr[s];
		double tryValue1 = tryValue0 + 1.0;
		if((iterIndex == ITERATION_TO_MAKE_STOP_DECISION)&&(tryValue0 == 0))
		{
			tryValue1 = double(ITERATION_TO_MAKE_STOP_DECISION);//after certain iterations, one can max have that many points
		}
		bool isDown = false;
		if(isToTryGoDown)
		{
			isDown = true;
			if(tryValue0 >=1.0)
			{
				tryValue0 -= 1.0;
				tryValue1 -= 1.0;
			}
		}
		double* prediction0 = new double[researchDataObj->m_numOfItems ];
		double  i0Try =  OneProfsubOneWeight(prediction0, researchDataObj,  s,    tryValue0,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol,  statArr,  savlingTime);

		 
		//bool isStopDecision = true;
		 
		double* prediction1 = new double[researchDataObj->m_numOfItems ];
		double i1Try= OneProfsubOneWeight(prediction1, researchDataObj,  s,    tryValue1,   profile,
			 root,	 evolArr,  numOfCalibrationGrps,  globals, evol, 	 statArr,  savlingTime);
		bool isHigherWeightBetter = false;
		if(i1Try> i0Try ) // >= and not only > since a profile can find that it did not matter to have a higher weigh//and perhaps a next level chance can be easier achived when a progroess of weight 
		{
			if(tryValue0 == 0.0 && tryValue1 > 1.0)
			{
				cout << "success imporved with a ITERATION_TO_MAKE_STOP_DECISION case \n";
			}
			//isImproved = true;//improved or same but withi a higher weight for one more profile, is a progress
			profile->SetProfileAdvancedPerformance(s , tryValue1);
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction1[i];
			}
			endOfProcessBP = i1Try;	
			isHigherWeightBetter = true;
			if(	!isDown)
			{
				cout << "found better bp : " ;
				cout<< endOfProcessBP;
				cout<<"\n level: ";
				cout<<  levelForPrint;//, int w
				cout << "\n";
				cout<"iterIndex :";
				cout<<iterIndex;
				cout << "\n";
				cout<< "W :";
				cout<<w;
				cout << "\n";
			}
		}
		else
		{
			profile->SetProfileAdvancedPerformance(s , tryValue0);//not supposed to matter
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				startingPointArrr[i]=prediction0[i];
			}
			endOfProcessBP = i0Try;	

			if(isDown)
			{
				cout<< "Case of going down and improving while going down :";
				cout << "found better bp : " ;
				cout<< endOfProcessBP;
				cout << "\n";
			}
		}	 
		
		delete []savlingTime;
		delete []prediction0;
		delete []prediction1;
	//	delete []prediction2;
		return isHigherWeightBetter;
	}

double cResearchObject::TryWeighhtByOrderAndKeepBestOPtion2( cProfileObject** pArr, int* rankArr,  int* rankArrWithSub, int numOfProf,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro)
{
 	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		root,  evol->m_anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	
	double rank=0.0;
	double endOfProcessBP=0.0;
	int sizeTwoDim = numOfProf *  evol->m_anchor->GetNumberOfSubGroups();
	int movIndex=0;
	bool* isTaken = new bool[sizeTwoDim];

	for(int i = 0 ; i < sizeTwoDim ; i++)
	{
		int index = rankArrWithSub[i];
		int profIndex = index / evol->m_anchor->GetNumberOfSubGroups(); //i.e 6 / 5 = 1, profile [1], 6 % 5 = 1, x=1 s=1 
		int subIndex = index % evol->m_anchor->GetNumberOfSubGroups();
			//OneProfsubOrderedProcecss
		OneProfsubOrderedProcecss2			
			(  pArr[profIndex],  rankArr,   rankArrWithSub,  numOfProf, evolArr,  statArr,  root,
				 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  oneLevelScoreGro,  startingPointArrr,profIndex,subIndex);
	}
	delete [] startingPointArrr;
	return endOfProcessBP ;
}
				


double cResearchObject::TryWeighhtByOrderAndKeepBestOPtion4( cProfileObject** pArr,  int* rankArrWithSub,
	//double* rankValueArrWithSub, 
	int numOfProf,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, int* rankArr, 
							int requestLbyAboveLoop,  int iterIndex,  int w)//, cScoreGrpArr* oneLevelScoreGro)
{
 	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		root,  evol->m_anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	
	double rank=0.0;
	double endOfProcessBP=0.0;
	int sizeTwoDim = numOfProf *  evol->m_anchor->GetNumberOfSubGroups();
	int movIndex=0;
	//bool* isTakenn = new bool[sizeTwoDim];

	int lowestIndexStillImrpvoed = sizeTwoDim;
	double inputMovingPerf =0.0;
	//double outputMovingPerf =0.0;
	for(int i = sizeTwoDim - 1 ; i >= 0  ; i--)
	{
		int index = rankArrWithSub[i];
		int profIndex = index / evol->m_anchor->GetNumberOfSubGroups(); //i.e 6 / 5 = 1, profile [1], 6 % 5 = 1, x=1 s=1 
		int subIndex = index % evol->m_anchor->GetNumberOfSubGroups();
			//OneProfsubOrderedProcecss
		//OneProfsubOrderedProcecss2	
		bool tryGoDown = false;
		bool impropved = OneProfsubOrderedProcecss4
			(  endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  numOfProf, evolArr, 
			statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
				 iterIndex,inputMovingPerf, requestLbyAboveLoop, w, tryGoDown);
		if(impropved)
		{
			if(true)//3 22 24 faster learning try
			{
				 impropved = OneProfsubOrderedProcecss4(  endOfProcessBP, startingPointArrr, pArr[profIndex], 
					 NULL,   rankArrWithSub,  numOfProf, evolArr,statArr,  root,
					 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL, 
					 profIndex,subIndex, iterIndex,inputMovingPerf,requestLbyAboveLoop, w, tryGoDown);
				 if(false && impropved)
				 {
					 impropved = OneProfsubOrderedProcecss4(  endOfProcessBP, startingPointArrr, pArr[profIndex], 
						 NULL,   rankArrWithSub,  numOfProf, evolArr,statArr,  root,
						 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL, 
						 profIndex,subIndex, iterIndex,inputMovingPerf , requestLbyAboveLoop, w, tryGoDown);
				 }
			}
			inputMovingPerf = endOfProcessBP;
			lowestIndexStillImrpvoed = cVarianceCalc::Min(lowestIndexStillImrpvoed ,i);
		}
		else
		{
			if(  pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) >=1.0)
			{
				tryGoDown = true;
				bool isNotGoDownBetter = OneProfsubOrderedProcecss4(  endOfProcessBP, startingPointArrr, pArr[profIndex], 
					 NULL,   rankArrWithSub,  numOfProf, evolArr,statArr,  root,
					 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL, 
					 profIndex,subIndex, iterIndex,inputMovingPerf,requestLbyAboveLoop, w, tryGoDown);
				int sssss=0;
			}
		}
	}
	delete [] startingPointArrr;
	return endOfProcessBP ;
}
			


double cResearchObject::TryWeighhtByOrderAndKeepBestOPtion6( cProfileObject** pArr,  int* rankArrWithSub,
	int numOfProf, cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
	cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj, int numOfCalibrationGrps, 
	cGlobals* globals, int* rankArr, int requestLbyAboveLoop,  int iterIndex,  int w, int globalIterationIndex,
	int profSubHighestSampleTry, 	int lowestSampleSizeTest, int ratioOfGoingForZeroWghProfsubs)
{
 	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		root,  evol->m_anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	
	double rank=0.0;
	double endOfProcessBP=0.0;
	int sizeTwoDim = numOfProf *  evol->m_anchor->GetNumberOfSubGroups();
	int movIndex=0;
	double inputMovingPerf =0.0;
	for(int i = sizeTwoDim - 1 ; i >= 0  ; i--)
	{
		int index = rankArrWithSub[i];
		int profIndex = index / evol->m_anchor->GetNumberOfSubGroups(); //i.e 6 / 5 = 1, profile [1], 6 % 5 = 1, x=1 s=1 
		int subIndex = index % evol->m_anchor->GetNumberOfSubGroups();
		bool isUp = true;
		bool isFirstGlobalItration = globalIterationIndex ==0;
		bool impropvedDown = false;
		if(pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) >= 1.0){
			isUp = false;
			bool isToUPdateProfsubStatusAndPredictionarray = false;
			int cntOFDifferenceCases=0;
			if( OneProfsubOrderedProcecss6	( cntOFDifferenceCases,  endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  
				numOfProf, evolArr, statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
				 iterIndex,inputMovingPerf, requestLbyAboveLoop, w , isFirstGlobalItration , isUp, globalIterationIndex,
				 profSubHighestSampleTry,  pArr[profIndex]->GetProfileID(),  lowestSampleSizeTest,  
				 startingPointArrr,	isToUPdateProfsubStatusAndPredictionarray, i, sizeTwoDim	 ))
			{
				if( cntOFDifferenceCases < lowestSampleSizeTest){
					int check =0;//check if it is good to add below else, if enter here dont need to call OneProfsubOrderedProcecss6 again
					//impropvedDown=true; //open th is too if else does not get the chance
				}
				isToUPdateProfsubStatusAndPredictionarray=true;
				impropvedDown = OneProfsubOrderedProcecss6	( cntOFDifferenceCases, endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  
						numOfProf, evolArr, statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
						iterIndex,inputMovingPerf, requestLbyAboveLoop, w , isFirstGlobalItration , isUp, globalIterationIndex,
						pArr[profIndex]->GetProfilePopulationSize(),  pArr[profIndex]->GetProfileID(),   pArr[profIndex]->GetProfilePopulationSize(), 
						startingPointArrr, isToUPdateProfsubStatusAndPredictionarray , i, sizeTwoDim );
			}
		}
		bool improved= false;
		if(!impropvedDown)
		{//3 29 24 control both saving zero windowns to not be 100 but more, and the smaller one to also be more, and have these be bery high in the first itration
			isUp = true;
			bool toGo = true;
			int cntOFDifferenceCases=0;
			//if previous iteration or iterations led to still being at 0
			/* todo 3 30 24  RANDOM SMART METHOD change the below:
			if(globalIterationIndex > 0 && pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) == 0.0){
			...
			}
			to new code (make  a new function of this new code) :
			if(globalIterationIndex > 0)
			{
				if(pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) == 0.0)
				{
					toGo=false;
					int random = rand();
					if((random % ratioOfGoingForZeroWghProfsubs)==0) //give a chance, later add more ligic
					{
						toGo = true;
					}
					else if( pArr[profIndex]->DoThisProfsubOrNeigborProfsubHavePositiveWeights(subIndex) )
					{
						if((random % siblingsProfsubRatioForZeroProfusub)==0) //give a chance, later add more ligic
						{
							toGo = true;
						}
					}
					else if(pArr[profIndex]->DoParentsProfilesHostProfsubsThatHavePositiveWeights() )
					{ //parentProfsubRatioForZeroProfusub is not as low as siblingsProfsubRatioForZeroProfusub, the parents have all 5 profsubs to be on, 
					//and with many parents. not so different rate than the just zero. better constant of ratio to only get an input of an average random
					//number of all zeros and foro siblings and parents give ratioOfGoingForZeroWghProfsubs * 0.2 for siblings and 
					//ratioOfGoingForZeroWghProfsubs * 0.5 for parents. perhaps think of a way that 
						if((random % parentProfsubRatioForZeroProfusub)==0) //give a chance, later add more ligic
						{
							toGo = true;
						}
					}
					else if(pArr[profIndex]->WasAlreadyWithPositiveWeight(subIndex) )
					{
						if((random % selfPreviousSuccessRatio)==0) //g
						{
							toGo = true;
						}
					}
				}
				else
				{
					int iiiii=0;//right now just check and keep toGo as true.  need to develop a new threshold based
							//on historical and/or parents success 
				}
			}	
			*/
			if(globalIterationIndex > 0 && pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) == 0.0){
				toGo=false;
				int random = rand();
				if((random % ratioOfGoingForZeroWghProfsubs)==0) //give a chance, later add more ligic
				{
					toGo = true;
				}//5 15 24 add another chance using parent success. 
				if(pArr[profIndex]->IsProfSubRelatedToHigherPerfWeight(   subIndex , evol->m_profList, evol->m_proffListSize) )
				{
					toGo = true;
				}
			}
			if(toGo)
			{
				bool isToUPdateProfsubStatusAndPredictionarray = false;
				if(OneProfsubOrderedProcecss6	( cntOFDifferenceCases, endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  
					numOfProf, evolArr, statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
					 iterIndex,inputMovingPerf, requestLbyAboveLoop, w , isFirstGlobalItration , isUp, globalIterationIndex,
					 profSubHighestSampleTry,  pArr[profIndex]->GetProfileID(),  lowestSampleSizeTest,   startingPointArrr,
					 isToUPdateProfsubStatusAndPredictionarray	, i, sizeTwoDim 	 ))
				{
					if(cntOFDifferenceCases < lowestSampleSizeTest)
					{
						int check;//add an else so that if you come here no need to call the function below again
						//improved=true; //open th is too
					}
					isToUPdateProfsubStatusAndPredictionarray=true;
					improved=	OneProfsubOrderedProcecss6	( cntOFDifferenceCases, endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  
					numOfProf, evolArr, statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
					 iterIndex,inputMovingPerf, requestLbyAboveLoop, w , isFirstGlobalItration , isUp, globalIterationIndex,
					  pArr[profIndex]->GetProfilePopulationSize(),  pArr[profIndex]->GetProfileID(), 
					  pArr[profIndex]->GetProfilePopulationSize(),   startingPointArrr	, isToUPdateProfsubStatusAndPredictionarray	, i, sizeTwoDim  );
				}//5 15 24 XXXXX( pArr[profIndex] ,   subIndex , improved, globalIterationIndex, pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) >= 1.0
		//XXXXX will update the case of this profsub if success, in an up mode, and communnicate it to some data set 
			}//marking here , since we go down, will allow marking children of a profsub. we ma
		}
		inputMovingPerf = endOfProcessBP;
	}
	delete [] startingPointArrr;
	return endOfProcessBP ;
}
double cResearchObject::TryWeighhtByOrderAndKeepBestOPtion5( cProfileObject** pArr,  int* rankArrWithSub,
	int numOfProf, cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
	cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj, int numOfCalibrationGrps, 
	cGlobals* globals, int* rankArr, int requestLbyAboveLoop,  int iterIndex,  int w, int globalIterationIndex)
{
 	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		root,  evol->m_anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	
	double rank=0.0;
	double endOfProcessBP=0.0;
	int sizeTwoDim = numOfProf *  evol->m_anchor->GetNumberOfSubGroups();
	int movIndex=0;
	//bool* isTakenn = new bool[sizeTwoDim];

	int lowestIndexStillImrpvoed = sizeTwoDim;
	double inputMovingPerf =0.0;
	//double outputMovingPerf =0.0;
	//double lastPerfScore = 0.0;
	for(int i = sizeTwoDim - 1 ; i >= 0  ; i--)
	{
		int index = rankArrWithSub[i];
		int profIndex = index / evol->m_anchor->GetNumberOfSubGroups(); //i.e 6 / 5 = 1, profile [1], 6 % 5 = 1, x=1 s=1 
		int subIndex = index % evol->m_anchor->GetNumberOfSubGroups();
		bool isUp = true;
		bool isFirstGlobalItration = globalIterationIndex ==0;
		bool impropved = OneProfsubOrderedProcecss5
			(  endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  numOfProf, evolArr, 
			statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
			 iterIndex,inputMovingPerf, requestLbyAboveLoop, w , isFirstGlobalItration , isUp, globalIterationIndex);
		if( !impropved && pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) >= 1.0)
		{
			isUp = false;
			impropved = OneProfsubOrderedProcecss5
			(  endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  numOfProf, evolArr, 
			statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
			 iterIndex,inputMovingPerf, requestLbyAboveLoop, w , isFirstGlobalItration , isUp, globalIterationIndex);	
		}		
		inputMovingPerf = endOfProcessBP;
		lowestIndexStillImrpvoed = cVarianceCalc::Min(lowestIndexStillImrpvoed ,i);
	}
	delete [] startingPointArrr;
	return endOfProcessBP ;
}
/*
		
	
		//OneProfsubOrderedProcecss
		//OneProfsubOrderedProcecss2	
		bool tryGoDown = false;
		bool impropved = OneProfsubOrderedProcecss4
			(  endOfProcessBP, startingPointArrr, pArr[profIndex],  NULL,   rankArrWithSub,  numOfProf, evolArr, 
			statArr,  root, evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL,  profIndex,subIndex,
				 iterIndex,inputMovingPerf, requestLbyAboveLoop, w, tryGoDown);
		if(impropved)
		{
			if(true)//3 22 24 faster learning try
			{
				 impropved = OneProfsubOrderedProcecss4(  endOfProcessBP, startingPointArrr, pArr[profIndex], 
					 NULL,   rankArrWithSub,  numOfProf, evolArr,statArr,  root,
					 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL, 
					 profIndex,subIndex, iterIndex,inputMovingPerf,requestLbyAboveLoop, w, tryGoDown);
				 if(false && impropved)
				 {
					 impropved = OneProfsubOrderedProcecss4(  endOfProcessBP, startingPointArrr, pArr[profIndex], 
						 NULL,   rankArrWithSub,  numOfProf, evolArr,statArr,  root,
						 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL, 
						 profIndex,subIndex, iterIndex,inputMovingPerf , requestLbyAboveLoop, w, tryGoDown);
				 }
			}
			inputMovingPerf = endOfProcessBP;
			lowestIndexStillImrpvoed = cVarianceCalc::Min(lowestIndexStillImrpvoed ,i);
		}
		else
		{
			if(  pArr[profIndex]->GetProfileAdvancedPerformance(subIndex) >=1.0)
			{
				tryGoDown = true;
				bool isNotGoDownBetter = OneProfsubOrderedProcecss4(  endOfProcessBP, startingPointArrr, pArr[profIndex], 
					 NULL,   rankArrWithSub,  numOfProf, evolArr,statArr,  root,
					 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  NULL, 
					 profIndex,subIndex, iterIndex,inputMovingPerf,requestLbyAboveLoop, w, tryGoDown);
				int sssss=0;
			}
		}
	}
	delete [] startingPointArrr;
	return endOfProcessBP ;
}
*/

double cResearchObject::TryWeighhtByOrderAndKeepBestOPtion3( cProfileObject** pArr, int* rankArr,  int* rankArrWithSub, int numOfProf,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro)
{
 	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		root,  evol->m_anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	
	double rank=0.0;
	double endOfProcessBP=0.0;
	int sizeTwoDim = numOfProf *  evol->m_anchor->GetNumberOfSubGroups();
	int movIndex=0;
	//bool* isTakenn = new bool[sizeTwoDim];

	int lowestIndexStillImrpvoed = sizeTwoDim;
	for(int i = sizeTwoDim - 1 ; i >= 0  ; i--)
	{
		int index = rankArrWithSub[i];
		int profIndex = index / evol->m_anchor->GetNumberOfSubGroups(); //i.e 6 / 5 = 1, profile [1], 6 % 5 = 1, x=1 s=1 
		int subIndex = index % evol->m_anchor->GetNumberOfSubGroups();
			//OneProfsubOrderedProcecss
		//OneProfsubOrderedProcecss2	
		bool impropved = OneProfsubOrderedProcecss3
			(  endOfProcessBP, pArr[profIndex],  rankArr,   rankArrWithSub,  numOfProf, evolArr,  statArr,  root,
				 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  oneLevelScoreGro,  startingPointArrr,profIndex,subIndex);
		if(impropved)
		{
			lowestIndexStillImrpvoed = cVarianceCalc::Min(lowestIndexStillImrpvoed ,i);
		}
	}
	delete [] startingPointArrr;
	return endOfProcessBP ;
}
				




double cResearchObject::TryWeighhtByOrderAndKeepBestOPtion( cProfileObject** pArr, int* rankArr,  int* rankArrWithSub, int size,
				cEvolutionProfilePAckage** evolArr, double* statArr, cProfileObject* root,
				cEvolutionProfilePAckage* evol	, cResearchDataObj* researchDataObj	 , 
							int numOfCalibrationGrps	, cGlobals* globals, cScoreGrpArr* oneLevelScoreGro)
{
 	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		root,  evol->m_anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	
	double rank=0.0;
	double endOfProcessBP=0.0;
	for(int y = 0 ; y < size ; y++)
	{ 
		int x = rankArr[y];
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			 OneProfsubOrderedProcecss(  pArr[x],  rankArr,   rankArrWithSub,  size, evolArr,  statArr,  root,
				 evol	,  researchDataObj	 , numOfCalibrationGrps	,  globals,  oneLevelScoreGro,  startingPointArrr,x,s);
/*				double* savlingTime = new double[researchDataObj->m_numOfItems];
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				savlingTime[i] = startingPointArrr[i];
			}
					
			
			
			CancelProfSubVAlues(savlingTime , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);
			double initiValue = 0.0;
			if(oneLevelScoreGro != NULL)
			{
				initiValue = oneLevelScoreGro[x].m_scoreArr[s];
			}
			pArr[x]->SetProfileAdvancedPerformance(s , initiValue);
			double  init1Try = 0.0;
			double* prediction1= new double[researchDataObj->m_numOfItems];
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				prediction1[i]=0.0;
			}
			SwapAndPredictionCover(init1Try, prediction1,  evolArr,
				 root,   evol->m_anchor,  globals,  statArr,  savlingTime, researchDataObj,   numOfCalibrationGrps);
			double tryValue = initiValue + 1.0;
			pArr[x]->SetProfileAdvancedPerformance(s , tryValue);
			
			
			double initial2Try=0.0;
			double* prediction2= new double[researchDataObj->m_numOfItems];
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				prediction2[i]=0.0;
			}			
			SwapAndPredictionCover(initial2Try, prediction2,  evolArr,
				 root,   evol->m_anchor,  globals,  statArr,  savlingTime, researchDataObj,   numOfCalibrationGrps);
		
			if(init1Try> initial2Try )
			{
				pArr[x]->SetProfileAdvancedPerformance(s , initiValue);
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					startingPointArrr[i]=prediction1[i];
				}
				endOfProcessBP = init1Try;
			}
			else
			{
				pArr[x]->SetProfileAdvancedPerformance(s , tryValue);
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					startingPointArrr[i]=prediction2[i];
				}
				endOfProcessBP = initial2Try;
				cout << "founs better bp : " ;
				cout<< initial2Try;
				cout << "\n";

			}
			delete []savlingTime;
			delete []prediction1;
			delete []prediction2;*/
		}
	}
	delete [] startingPointArrr;
	 
	return endOfProcessBP ;
}
				




void cResearchObject::RotateToSetProfileRank(double* rankValueArr, double* rankValueArrWithSub, cProfileObject** pArr , 
	int size, cEvolutionProfilePAckage** evolArr,
	cResearchDataObj* researchDataObj, cProfileObject* root, cProfileObject* anchor, cGlobals* globals, 
	int numOfCalibrationGrps, double* statArr)
{
	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		startingPointArrr[i]=0.0;
	}

	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		 root,  anchor,  globals,  statArr,  NULL, researchDataObj,   numOfCalibrationGrps , -1,0,NULL);



	for(int x = 0 ; x < size ; x++)
	{
		double rank=0.0;
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			int profSubIndex = ( x*  pArr[x]->GetNumberOfSubGroups()) + s;//for example prof 1 sub gropu 2 is 5 + 1. prof 0 sub 0 is 0. prof 1 sub 0 is 5.
			rankValueArrWithSub[profSubIndex]=0.0;
			double* savlingTime = new double[researchDataObj->m_numOfItems];
			double* prediction= new double[researchDataObj->m_numOfItems];
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				savlingTime[i] = startingPointArrr[i];
				prediction[i]=0.0;
			}
			int recomendedSample = RECOMENDED_SAMPLE_LEARNING_RORATE;
			CancelProfSubVAlues(savlingTime , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj, recomendedSample);//2  28 24 a add max num of elements to be cancled from savlingTime array to avoid long processing. enough 500 max 
	
			pArr[x]->SetProfileAdvancedPerformance(s , 0.0);
			double zeroTry = 0.0;
			SwapAndPredictionCover2(zeroTry, prediction,  evolArr,
				 root,  anchor,  globals,  statArr,  savlingTime, researchDataObj,   numOfCalibrationGrps,
				 pArr[x]-> GetProfileID(), SMALL_LEARNING_SAMPLE, startingPointArrr		 );

			pArr[x]->SetProfileAdvancedPerformance(s , 1.0);
			double oneTry = 0.0;
			SwapAndPredictionCover2(oneTry, prediction,  evolArr,
				 root,  anchor,  globals,  statArr,  savlingTime, researchDataObj,   numOfCalibrationGrps,
				  pArr[x]-> GetProfileID(), SMALL_LEARNING_SAMPLE, startingPointArrr		 );
			pArr[x]->SetProfileAdvancedPerformance(s , 0.0);
			//1 28 24 * a - need to change to true b - 
			
			int sampleS =  pArr[x]->GetSubBucketCntArr(s );
			double gap = 0.0;
			if(sampleS > 0)
			{
					double score0 =( zeroTry * (root->GetSizeOfAllPopulation() / sampleS));
					double score1 =( oneTry * (root->GetSizeOfAllPopulation() /sampleS));
					gap = ( score1 - score0);
			}
			rankValueArrWithSub[profSubIndex]=gap;
			rank +=   gap;
			

			delete []savlingTime;
			savlingTime=NULL;
			delete []prediction;
			prediction=NULL;
		}
		if(rankValueArr!=NULL)
		{
			rankValueArr[x]=rank;
		}
	}
	delete []startingPointArrr;
	startingPointArrr=NULL;
}










void cResearchObject::PlayWithOneLevelWeightAnalytics3(
	double *rank,double* scorePoints,cProfileObject ** pArr, int &numOfProfs, cEvolutionProfilePAckage* evol  , int l,
	cResearchDataObj* researchDataObj, cProfileObject* anchor,  cProfileObject* root, cGlobals* globals,
	cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps,  double movingScre, 
	double* stretArr, bool isToOnlyCheckPositiveWeights	, bool isWeightedLevelAsBase , cScoreGrpArr* initialProfScoreThisLevel,
	bool isAdjustingScoreBasedOnResults,  int* rankArrr)
	//if isWeightedLevelAsBase than keep the weights as being acomulate at start, else zero and get started

{
	double* predWithZeroedLevelOrNULL = new double[researchDataObj->m_numOfItems];
	double* newPredictionarr = new double[researchDataObj->m_numOfItems];
	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		predWithZeroedLevelOrNULL[i]=0.0;//1 20 24 * add that after the first profile from this level of analtics i alread have the all predeidction set to save perf for all sub gruops not only the second
		newPredictionarr[i]=0.0;
		startingPointArrr[i]=0.0;
	}

	numOfProfs=  CollectProfilesFromLevel(pArr, l, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER , evol);
	
	
	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		 root,  anchor,  globals,  stretArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);

	cout<< "end of one level analytics. scoreZeroWeightAllLevel : ";
	cout << scoreZeroWeightAllLevel;
	cout << "\n";

	for(int q= 0 ; q< numOfProfs ; q++)
	{
		if(q==288)
		{
			int dsg=0;
		}
		int x = rankArrr[q];
		rank[x]=0.0;
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			for(int i = 0 ; i < researchDataObj->m_numOfItems; i++)
			{//getting back "before weight change testing" the original prediciton which we keep on changing for every x/s just for one profsub
				predWithZeroedLevelOrNULL[i]=startingPointArrr[i];
			}
			//here predWithZeroedLevelOrNULL gets the sub pop belongs to x s gets prediction 0.0 to get adjusted
			CancelProfSubVAlues(predWithZeroedLevelOrNULL , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);

			//output of the funciton is to fill scoreGrpOneLeveAdj[x] with the  scores only due to change btween 0 and 1
	 	//	double scoreOff=0.0;
			double scoreNow =0.0;
			if(initialProfScoreThisLevel != NULL)
			{
				scoreNow = initialProfScoreThisLevel[x].m_scoreArr[s];
			}

			double addedWeight = 1.0;
			double scorePlus = scoreNow+addedWeight;

		
			double rankS=0.0;
			double resultPoints = 0.0;
			//1 23 24 replace scoroes with gaps? now inpt scorenow is 0 or any number fro past scores, but the output is only 1 or 0
			double poitBis = RotateProfilePerf(rankS, resultPoints,  researchDataObj, pArr[x],    s, anchor,    root,   globals,  
				numOfCalibrationGrps,  evolArr,  stretArr,  predWithZeroedLevelOrNULL,   scoreNow , scorePlus);
			 
			{
			
					pArr[x]->SetProfileAdvancedPerformance(s , 0);
					double eta0 = 0.0;//
					double movingScre=0.0;
					SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
					evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
					int ssss=0;

					pArr[x]->SetProfileAdvancedPerformance(s , 1);
					 eta0 = 0.0;//
					 movingScre=0.0;
					SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
					evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
					int sss=0;


			
			}



			rank[x] += rankS;
			//if there was somethig befoer get it back, else 0
		//	if(initialProfScoreThisLevel != NULL)//if there is a previous score?
		//	{//give pArr[x] back its previous score. dont use the new rotation score for this round yet
		//		pArr[x]->SetProfileAdvancedPerformance(s , initialProfScoreThisLevel[x].m_scoreArr[s]);	
		//	}
		//	else
		//	{
			pArr[x]->SetProfileAdvancedPerformance(s ,scoreNow);


			{
			
					pArr[x]->SetProfileAdvancedPerformance(s , 0);
					double eta0 = 0.0;//
					double movingScre=0.0;
					SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
					evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
					int ssss=0;

					pArr[x]->SetProfileAdvancedPerformance(s , 1);
					 eta0 = 0.0;//
					 movingScre=0.0;
					SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
					evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
					int sss=0;


			
			}


			//}
			//if the succes or failr of the roration is done/updated here than this is trie
			if(isAdjustingScoreBasedOnResults)
			{//update to do the increase or recrase in any case even if we dont have the i nitial , but if selected. other wise just what was
				if(resultPoints > 0.0)
				{
					pArr[x]->AddToAdvancedPerfWeight(addedWeight, s);
					cout<<"new point biserial: ";
					cout<<poitBis;
					cout<<"\n";
				}
				{
			
					pArr[x]->SetProfileAdvancedPerformance(s , 0);
					double eta0 = 0.0;//
					double movingScre=0.0;
					SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
					evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
					int ssss=0;

					pArr[x]->SetProfileAdvancedPerformance(s , 1);
					 eta0 = 0.0;//
					 movingScre=0.0;
					SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
					evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
					int sss=0;


			
			}






			}
		 }
	}
/////////////////////////////////////////
///

	delete []predWithZeroedLevelOrNULL;
	predWithZeroedLevelOrNULL=NULL;
	delete []newPredictionarr;
	newPredictionarr=NULL;	
	delete []startingPointArrr;
	startingPointArrr=NULL;

	cout << "end of PlayWithOneLevelWeightAnalytics() \n";
	
}




/*
caller to this function will fine tune one level l




*/
void cResearchObject::PlayWithOneLevelWeightAnalytics2(cScoreGrpArr** scoresGrpArr, int* perLevelProfNum,
	cEvolutionProfilePAckage* evol  , int l,  int maxProfNum,
	cResearchDataObj* researchDataObj, cProfileObject* anchor,  cProfileObject* root, cGlobals* globals,
	cEvolutionProfilePAckage** evolArr, int numOfCalibrationGrps,  double movingScre, 
	double* stretArr, bool isToOnlyCheckPositiveWeights	, bool isWeightedLevelAsBase)
	//if isWeightedLevelAsBase than keep the weights as being acomulate at start, else zero and get started

{
	double* predWithZeroedLevelOrNULL = new double[researchDataObj->m_numOfItems];
	double* newPredictionarr = new double[researchDataObj->m_numOfItems];
	double* startingPointArrr = new double[researchDataObj->m_numOfItems];
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		predWithZeroedLevelOrNULL[i]=0.0;//1 20 24 * add that after the first profile from this level of analtics i alread have the all predeidction set to save perf for all sub gruops not only the second
		newPredictionarr[i]=0.0;
		startingPointArrr[i]=0.0;
	}

	cProfileObject** pArr = new cProfileObject*[maxProfNum];
	int numOfProfs=  CollectProfilesFromLevel(pArr, l, maxProfNum , evol);
	
	cScoreGrpArr* scoreGrpOneLevelStart = new cScoreGrpArr[numOfProfs];
	cScoreGrpArr* scoreGrpOneLeveAdj = new cScoreGrpArr[numOfProfs];// 	
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		//keep for later
		pArr[x]->CopyOutAdvPerfScores( scoreGrpOneLevelStart[x]); 
		if(scoresGrpArr != NULL )
		{
			scoreGrpOneLevelStart[x].CopyProfArr(	*(scoresGrpArr[x]) );
		}
		//start from 0 frst
		pArr[x]->UpdatePerformanceArrays(0.0);
	}	

	
	double scoreZeroWeightAllLevel= 0.0;//score is when all weights are 0 as initielized
	SwapAndPredictionCover2(scoreZeroWeightAllLevel, startingPointArrr,  evolArr,
		 root,  anchor,  globals,  stretArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);

	cout<< "end of one level analytics. scoreZeroWeightAllLevel : ";
	cout << scoreZeroWeightAllLevel;
	cout << "\n";

 
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				predWithZeroedLevelOrNULL[i]=startingPointArrr[i];
			}
			//here it gets the profsub to null some of the predictions
			CancelProfSubVAlues(predWithZeroedLevelOrNULL , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);
			pArr[x]->SetProfileAdvancedPerformance(s , 0.0);
			double eta0 = 0.0;//
			SecondRoundOfMLtry3( eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
				evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
			double previousOrInirialScore = 0.0;//1.0 is starting point
			if(scoreGrpOneLevelStart[x].m_scoreArr[s] != 0)///iff this is not the first time than 
			{
				previousOrInirialScore = scoreGrpOneLevelStart[x].m_scoreArr[s] ;
			}
			double activeScoreOn = previousOrInirialScore; 
			if(activeScoreOn == 0)
			{
				activeScoreOn =1.0;//try 
			}
			pArr[x]->SetProfileAdvancedPerformance(s , activeScoreOn);
			
			double etaOn = 0.0;//
			SecondRoundOfMLtry3( etaOn, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,
				evolArr, 	stretArr,    predWithZeroedLevelOrNULL, movingScre,s	);
			if(etaOn > eta0)
			{
				cout <<"etaOn \n";
				cout<<etaOn;
				cout <<" \n";
				double newScore = 0.0;
				if(previousOrInirialScore == 0.0)//first
				{
					newScore = activeScoreOn;
				}
				else
				{
					newScore =previousOrInirialScore * LEARNING_MULTIPLIER ; //for example if 1.0 was previous or initrial
				// and if etaOn refleat that 1 or intial, and if multipe is 1.5 than adjusted score gets 1.5, and then later 2.25, etc
				}
				scoreGrpOneLeveAdj[x].m_scoreArr[s] = newScore;
			}
			else
			{
				double newScore=0.0;
				if(previousOrInirialScore == 0.0)//
				{
					newScore=0.0;
				}
				else
				{
					newScore = previousOrInirialScore / LEARNING_MULTIPLIER;
				}
				scoreGrpOneLeveAdj[x].m_scoreArr[s] = newScore;
			}
			pArr[x]->SetProfileAdvancedPerformance(s , 0.0);
		}
	}
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			pArr[x]->UpdatePerformanceArrays(scoreGrpOneLeveAdj[x]) ;
		}
	}
	delete []scoreGrpOneLeveAdj;
	scoreGrpOneLeveAdj=NULL;
	delete []scoreGrpOneLevelStart;
	scoreGrpOneLevelStart=NULL;

	double correlScore=0.0;
	SwapAndPredictionCover2(correlScore, newPredictionarr,  evolArr,
		 root,  anchor,  globals,  stretArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
	cout<< "end of one level analytics : ";
	cout << correlScore;
	cout << "\n";

	
	//1 20 24 d collect all resutls from score grp and copy to profArr all the level
	//1 20 24 e check performacne
	delete[]pArr;
	pArr=NULL;
	delete []predWithZeroedLevelOrNULL;
	predWithZeroedLevelOrNULL=NULL;
	delete []newPredictionarr;
	newPredictionarr=NULL;	
	delete []startingPointArrr;
	startingPointArrr=NULL;

	cout << "end of PlayWithOneLevelWeightAnalytics() \n";
	
}



/*
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		cScoreGrpArr scoresGrp (pArr[x]);
		for(int s = 0 ; s < pArr[x]->GetNumberOfSubGroups() ; s++)
		{
			//set moving saving tetmp with predition either based on weighted level or zeroed level
			//also set the array to not hae prediction for profile [x][s]
			//////hERE
			for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
			{
				movingSavingTemp[i]=startingPointArrr[i];
			}
			CancelProfSubVAlues(movingSavingTemp , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);

			//1 20 24 b only if previous one succeeded or it is lower iterations  
			if((!isToOnlyCheckPositiveWeights)  || (scoresGrpArr[l][x].scoreArr[s] > 0.0))
				//(pArr[x]->GetProfileAdvancedPerformance(s) > 0.0))
			//if(true)// && pArr[x]->GetProfileAdvancedPerformance(s) > 0.0)
		//the reason is that i consider to start from all level is zero and then having a 0 , 1/current,  *2
			{// only if true do this whole itration			 
			//	CancelProfSubVAlues(movingSavingTemp , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);
				pArr[x]->SetProfileAdvancedPerformance(s , 0.0);//1  20 24 * if scoresGrp.scorearr[s]==0.0 already than we dont do this whole work and move to the next s
				double eta0 = 0.0;//TestPerformance();
				double* movingTemp = new double[researchDataObj->m_numOfItems];
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					movingTemp[i]=0.0;
				}
				if(SecondRoundOfMLtry3( // scoresGrp[x],
					eta0, newPredictionarr, researchDataObj ,  anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,   evolArr, 
						stretArr,    movingSavingTemp, movingScre,s	))
				{
					for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
					{
						movingTemp[i]=newPredictionarr[i];
					}
				}					
				double wghCurrentOr1 = 1.0;
				if(scoresGrp.scoreArr[s] != 0)
				{
					wghCurrentOr1 = scoresGrp.scoreArr[s];
				}
				//CancelProfSubVAlues(movingSavingTemp , pArr[x], s, researchDataObj->m_numOfItems, researchDataObj);
				pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1);
				double etaCurrenrOr1 =0.0;// TestPerformance();
				if(SecondRoundOfMLtry3( // scoresGrp[x], 
					etaCurrenrOr1, newPredictionarr,  
							researchDataObj ,   anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,   evolArr, 
						stretArr,    movingSavingTemp, movingScre,s	))
				{
					int qqq=0;
				}
				if(etaCurrenrOr1 > eta0)
				{
					//double* temp = new double[researchDataObj->m_numOfItems];
					for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
					{
						movingTemp[i]=newPredictionarr[i];
					}
					double wghCurrentOr1Times2 = wghCurrentOr1 * 2;
					pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1Times2);
				//	CancelProfSubVAlues(movingSavingTemp , pArr[x], s,  researchDataObj->m_numOfItems, researchDataObj);
					double etaCurrenrOr2 =0.0;// TestPerformance();
					if(SecondRoundOfMLtry3( // scoresGrp[x],
						etaCurrenrOr2, newPredictionarr,  
							researchDataObj ,   anchor,  root,   globals, pArr[x],  numOfCalibrationGrps ,   evolArr, 
						stretArr,    movingSavingTemp, movingScre, s	))
					{
						int sddf=0;
					}

					if(etaCurrenrOr2 > etaCurrenrOr1)
					{
						pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1Times2);
						for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
						{
							movingTemp[i]=newPredictionarr[i];
						}
						cout << "new eta etaCurrenrOr2 \n";
						cout<< etaCurrenrOr2;
						cout << " \n";
					}
					else
					{
						pArr[x]->SetProfileAdvancedPerformance(s , wghCurrentOr1);
						cout << "new eta etaCurrenrOr1 \n";
						cout<< etaCurrenrOr1;
						cout << " \n";
					}
				}
				else
				{
					pArr[x]->SetProfileAdvancedPerformance(s , 0.0);
					cout << "new eta eta0\n";
					cout<< eta0;
					cout << " \n";
				}
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					movingSavingTemp[i]=movingTemp[i];
				}
				delete []movingTemp;
				movingTemp=NULL;
			}
			else
			{
				int sdgg=0;
			}
			//1 20 24 c add for every profile get back to 0 - 	
			scoreGrpOneLevel[x].CopyProfArr(pArr[x]);
			pArr[x]->UpdatePerformanceArrays(0.0);
			//save in a tempo scoreGrp one level all the results
		}
	}
	for(int x= 0 ; x< numOfProfs ; x++)
	{
		pArr[x]->UpdatePerformanceArrays( scoreGrpOneLevel[x]); 
	}
*/
/*	delete []scoreGrpOneLevel;
	scoreGrpOneLevel=NULL;
	delete []scoreGrpOneLevelStart;
	scoreGrpOneLevelStart=NULL;

	double correlScore=0.0;
	SwapAndPredictionCover(correlScore, NULL,  evolArr,
		 root,  anchor,  globals,  stretArr,  NULL, researchDataObj,   numOfCalibrationGrps);
	cout<< "end of one level analytics : ";
	cout << correlScore;
	cout << "\n";

	
	//1 20 24 d collect all resutls from score grp and copy to profArr all the level
	//1 20 24 e check performacne
	delete[]pArr;
	pArr=NULL;
	delete []movingSavingTemp;
	movingSavingTemp=NULL;
	delete []newPredictionarr;
	newPredictionarr=NULL;	
	delete []startingPointArrr;
	startingPointArrr=NULL;

	cout << "end of PlayWithOneLevelWeightAnalytics() \n";*/
//}






void cResearchObject::KeepCurrentWeightsaved2(//cScoreGrpArr *scoresGrpOneLevel, int *&perLevelProfNum, int higestLlevel,  int anchorLevel,
					cScoreGrpArr *scoresGrpOneLevel, int l,
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage*  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter)
{
		//scoresGrp = new cScoreGrpArr*[higestLlevel+1];
	//	perLevelProfNum = new int[higestLlevel+1];
	//	for(int l = 0; l <= higestLlevel ; l++)
	//	{
	//		scoresGrp [l]=NULL;
	//		perLevelProfNum[l]=0;
	//	}
		//for(int l = anchorLevel + 1 ; l <= higestLlevel ; l++)//for example an anchor that is not root has 1 anchorLevel and the learning 
		//2 28 24 note about time saving, once pareint  competition is done put back the weights and no need to care on 0 weights after few iter
	//             also 
		{
			cout << "level num : ";
			cout << l;
			cout << "\n";
			cProfileObject** pArr = new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
			
			int numOfProfs=  CollectProfilesFromLevel(pArr, l, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER ,evolPackage);
			//perLevelProfNum[l] = numOfProfs;
		//	scoresGrp[l]= new cScoreGrpArr [numOfProfs];
			for(int y=0;y< numOfProfs ; y++)//2 28 24 copy only this loop to the 2 28 24 sig and then copy back to the pArr befoer the peer copmetition
			{
				pArr[y]->CopyOutadvancedPerfScores( scoresGrpOneLevel[y]);					
			}
			delete []pArr;
			pArr=NULL;
		}			
}



void cResearchObject::KeepCurrentWeightsaved(cScoreGrpArr **& scoresGrp, int *&perLevelProfNum, int higestLlevel,  int anchorLevel,
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage*  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter)
{
		scoresGrp = new cScoreGrpArr*[higestLlevel+1];
		perLevelProfNum = new int[higestLlevel+1];
		for(int l = 0; l <= higestLlevel ; l++)
		{
			scoresGrp [l]=NULL;
			perLevelProfNum[l]=0;
		}
		for(int l = anchorLevel + 1 ; l <= higestLlevel ; l++)//for example an anchor that is not root has 1 anchorLevel and the learning 
		{
			cout << "level num : ";
			cout << l;
			cout << "\n";
			cProfileObject** pArr = new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
			
			int numOfProfs=  CollectProfilesFromLevel(pArr, l, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER ,evolPackage);
			perLevelProfNum[l] = numOfProfs;
			scoresGrp[l]= new cScoreGrpArr [numOfProfs];
			for(int y=0;y< numOfProfs ; y++)
			{
				pArr[y]->CopyOutadvancedPerfScores( scoresGrp[l][y]);					
			}
			delete []pArr;
			pArr=NULL;
		}			
}





double cResearchObject::GetPointBiserial (	)
{
	double pb=0.0;
/*
	double movingStretch =  cResearchObject::SwapProfilesWithAnchors(
						movingSavingTimeArrOut,	
							calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
							researchDataObj,  evolPackage,
						profileListSizee,   root ,evolPackage[w]->m_profList[0], globals, 0 , stretArr,
						false, NULL, true); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
	pb = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	



	*/
	return pb;
}


void cResearchObject::ParentChildLearning2(//	double* movingSavingTimeArrOut,	
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage**  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter)
{
	cout<< "Learning iteration started \n";
	 

//	double eta0 = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
//	cout<< eta0;
//	cout<< "\n";
	//this is  using previous weights. see if new weights are better at thet end. start with only one iteration for now
//	double movingScre=0.0;
	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			//bool isLearningAlreadyStarted = false;
			//open here a loop with iteration uontil getting to isLearningAlreadyStarted = true
			for(int z = 0 ; z < numOfIter ; z++)
			{	
				cout << "iteration number \n";
				cout << z;
				cout << "\n";


			//	double pb = GetPointBiserial ();
			//	cout << "current point biserial : ";
			//	cout<< pb;
			//	cout << "\n";


				cScoreGrpArr** scoresGrp = NULL;
				int* perLevelProfNum =NULL;
				if( (z >= MIN_ITERAION_INDEX_TO_IGNORE_0_PROFSUBS))
				{
					cout << "removing profiles with all zero \n";
					RemoveProfilesWithAllSubGroupsZero(evolPackage[w]); 
				}
				int higestLlevel = FindHighestLevel(evolPackage[w]);
				int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
				if(z>0)
				{
					KeepCurrentWeightsaved( scoresGrp, perLevelProfNum,  higestLlevel,   anchorLevel,	calbratedThresArr,  bucketIndexArr, 
						calbAgDepArr,   calbCntArr,  	 numOfCalibrationGrps,  calibatedPRed,  researchDataObj,
					  evolPackage[w], 	profileListSizee,   root ,    globals,  stretArr,  numOfIter);				
				}

				SetValueToAllProfileAdvPerformance(evolPackage[w],0.0);
	
				evolPackage[w]->m_anchor->UpdatePerformanceArrays(1.0);
		
				for(int l = anchorLevel + 1 ; l <= higestLlevel ; l++)//for example an anchor that is not root has 1 anchorLevel and the learning 
					//starts from inclusion rules of 2 levels and then more. no check of 1 level since anchor has 1 and other anchors 
				{
					//double pb = GetPointBiserial ();
					cout << "level : ";
					cout<<l;
					cout << "\n";
				//	cout << " current point biserial : ";
				//	cout<< pb;
				//	cout << "\n";

					cProfileObject ** pArr=new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
					int numOfPrfilesInLevel=  CollectProfilesFromLevel(pArr, l, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER , evolPackage[w]);
					double* rankValueArr=new double[numOfPrfilesInLevel];
					double* rankValueArrWithSub=new double[numOfPrfilesInLevel*evolPackage[w]->m_anchor->GetNumberOfSubGroups()];
					RotateToSetProfileRank(	rankValueArr, rankValueArrWithSub, pArr , numOfPrfilesInLevel,evolPackage, researchDataObj,  root,  
															evolPackage[w]->m_anchor, 	globals,  numOfCalibrationGrps,  stretArr);
					int* rankArr = new int[numOfPrfilesInLevel];
					cVarianceCalc::BuildRankingIndexArr ( rankArr,  rankValueArr, numOfPrfilesInLevel);

					//int profSubIndex = ( x*  pArr[x]->GetNumberOfSubGroups()) + s
					int* rankArrWithSub = new int[numOfPrfilesInLevel * evolPackage[w]->m_anchor->GetNumberOfSubGroups()];
					cVarianceCalc::BuildRankingIndexArr (
									rankArrWithSub,  rankValueArrWithSub, numOfPrfilesInLevel * evolPackage[w]->m_anchor->GetNumberOfSubGroups());


					cScoreGrpArr* oneLevelScoreGro = NULL;
					if((scoresGrp != NULL) && (scoresGrp[l]!= NULL))
					{
						oneLevelScoreGro = scoresGrp[l];
					}
					double bestBP = 
						//TryWeighhtByOrderAndKeepBestOPtion
						TryWeighhtByOrderAndKeepBestOPtion2  //1 30 24 try with 2 instead?
						(pArr, rankArr, rankArrWithSub,numOfPrfilesInLevel,	evolPackage, stretArr,
						root,	 evolPackage[w]		, researchDataObj	 , 		numOfCalibrationGrps	, globals, oneLevelScoreGro);

			  
					delete[]pArr;
					pArr=NULL;
					delete []rankArr;
					rankArr=NULL;
					delete []rankValueArr;
					rankValueArr=NULL;
					delete []rankValueArrWithSub;
					rankValueArrWithSub=NULL;
					delete []rankArrWithSub;
					rankArrWithSub=NULL;
				}
				
				for(int u = 0 ; u<= higestLlevel ; u++)
				{
					if(scoresGrp && scoresGrp[u]!= NULL)
					{
						delete []scoresGrp[u];
						scoresGrp[u]=NULL;
					}
				}
				if(scoresGrp!=NULL)
				{
					delete []scoresGrp;
					scoresGrp=NULL;
					delete []perLevelProfNum;
					perLevelProfNum=NULL;
				}
				 
			}
				
		
			double* movingSavingTimeArrOut= new double [ researchDataObj->m_numOfItems];
	
			double movingStretch =  cResearchObject::SwapProfilesWithAnchors2(
						movingSavingTimeArrOut,	
							calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
							researchDataObj,  evolPackage,
						profileListSizee,   root ,evolPackage[w]->m_profList[0], globals, 0 , stretArr,
						false, NULL, true, -1,0,NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
			double eta = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
		
			cout<<"end of achor itration \n";
			cout<<eta;
			cout<< "\n";
		}
	}

	int* predictionValueIndex = new int[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		predictionValueIndex[i] = researchDataObj->m_twoDimArray[i][80];
	}
	double* predicValueMethodBasedOnHSLperIndex = new double[5];
	for(int v = 0 ; v < 5 ; v++)
	{
		predicValueMethodBasedOnHSLperIndex[v] = 0.0;
		int sample = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			if(predictionValueIndex[i] ==v)
			{
				sample++;
				predicValueMethodBasedOnHSLperIndex[v]+= researchDataObj->m_depArr[i];
			}
		}
		predicValueMethodBasedOnHSLperIndex[v] /= sample;
	}
	double* predictionValue = new double[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		int index = researchDataObj->m_twoDimArray[i][80];
		predictionValue[i] = predicValueMethodBasedOnHSLperIndex[index];
	}
				
	double etaHSL = cVarianceCalc::CalcualteETA(predictionValue , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout <"ETA HSL and Here before **************************************************************************\n";
	//cout<< movingScre;
//	cout<<" /n";
	cout<< etaHSL;
	cout<<" /n";

				
	delete []predictionValue;
	predictionValue=NULL;
	delete []predictionValueIndex;
	predictionValueIndex=NULL;
				
	delete []predicValueMethodBasedOnHSLperIndex;
	predicValueMethodBasedOnHSLperIndex=NULL;
				
}
 
void cResearchObject::ParentChildLearning3(//	double* movingSavingTimeArrOut,	
			double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,   cGlobals* globals,
			double* stretArr, int numOfIter,bool isToRepaceToLogisticModeoWeights)
{
	cout<< "Learning iteration started \n";

	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			int* perLevelProfNum =NULL;
			SetValueToAllProfileAdvPerformance(evolPackage[w],0.0);
			evolPackage[w]->m_anchor->UpdatePerformanceArrays(1.0);
			int higestLlevel = FindHighestLevel(evolPackage[w]);
			int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
			for(int l = anchorLevel + 1 ; l <= higestLlevel ; l++)
			{
					cProfileObject** pArr=new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
					int numOfPrfilesInLevel=  CollectProfilesFromLevel(pArr, l, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER , evolPackage[w]);
					// 2 5 24  use the below two functions and members of profile  to replace the weights that a profile has as its ranking fields
					//1)
					if(isToRepaceToLogisticModeoWeights)
					{//2 19 24 to use CalcualteETA and take in and out weights of varibles until we find best set. do the same if we are 
						//in the old var/val/point or the new one copied from regression, either wayy take in and out varibels as a whole upon
						//all their val and see if we get a better point biserial. then the point bierial can get all or only the profile ones

					/*	double** twoDimShortTemporaryArray = new double*[researchDataObj->m_numOfItems];
						for( int r=0; r<researchDataObj->m_numOfItems ; r++)
						{
							twoDimShortTemporaryArray[r] = new double* [researchDataObj->m_sizeOfItem];
							for(int rr = 0 ; rr< researchDataObj->m_sizeOfItem ; rr++)
							{
								twoDimShortTemporaryArray[r][rr]=0.0;
							}
						}	*/					 

						for(int e=0;e<numOfPrfilesInLevel;e++)
						{
							bool* isIn = new bool[researchDataObj->m_numOfItems];
							int count = FillIsInProfSub(isIn,pArr[e], -1, researchDataObj,NULL);
							bool* isPredictive = new bool[researchDataObj->m_sizeOfItem];
							pArr[e]->SetIsPreddictiveBasedOnSizeAndPoints(isPredictive,researchDataObj->m_sizeOfItem );
							pArr[e]->ReplacePredictiveWightsModel(pArr[e],researchDataObj,isPredictive, 
								globals,isIn,count);//, twoDimShortTemporaryArray );
							delete []isPredictive;
							isPredictive=NULL;
							//ReplacePredictiveWightsModel(pArr[e], researchDataObj, isPredictive,globals, isPredictive,  cGlobals* globals);
							delete []isIn;
							isIn = NULL;
						}

						 
					}
					 
					int numOfProfSubs = numOfPrfilesInLevel*evolPackage[w]->m_anchor->GetNumberOfSubGroups();
					double* rankValueArrWithSub=new double[numOfProfSubs];
					RotateToSetProfileRank(	NULL, rankValueArrWithSub, pArr , numOfPrfilesInLevel,evolPackage, researchDataObj,  
													root,  	evolPackage[w]->m_anchor, 	globals,  numOfCalibrationGrps,  stretArr);
					int* rankArrWithSub = new int[numOfProfSubs];
					cVarianceCalc::BuildRankingIndexArr ( rankArrWithSub,  rankValueArrWithSub,  numOfProfSubs);
				
					for	(int i= 0 ; i < numOfIter ; i++)
					{
						cout << "anchor ID :  ";
						cout <<w;
						cout<< "\n";
						cout << "iteration : ";
						cout<< i;
						cout<<  "\n";
						cout << "level : ";
						cout<<l;
						cout << "\n";
						cScoreGrpArr* oneLevelScoreGro = NULL;
						if(i > 0)
						{
							oneLevelScoreGro = new cScoreGrpArr[numOfPrfilesInLevel];//	oneLevelScoreGro = scoresGrp[l];
						
							KeepCurrentWeightsaved2( oneLevelScoreGro, l,	calbratedThresArr, 
									bucketIndexArr, calbAgDepArr,   calbCntArr,  	 numOfCalibrationGrps,  calibatedPRed,  researchDataObj,
														 evolPackage[w], 	profileListSizee,   root ,    globals,  stretArr,  numOfIter);				
						}
						 
						int maxIndexOfNonZeroWgh = 0;
						for(int y=0;y< numOfProfSubs ; y++)
						{
							if( rankValueArrWithSub[y] > 0.0)     //,  numOfProfSubs);
							{
								maxIndexOfNonZeroWgh = 	y;
							}
						}
						double bestBP = 
							//TryWeighhtByOrderAndKeepBestOPtion
							TryWeighhtByOrderAndKeepBestOPtion3  //1 30 24 try with 2 instead?
								(pArr, NULL, rankArrWithSub,numOfPrfilesInLevel,	evolPackage, stretArr,	root,	 evolPackage[w],
			  					researchDataObj ,	numOfCalibrationGrps, globals, oneLevelScoreGro);
						if(oneLevelScoreGro != NULL)
						{
							delete []oneLevelScoreGro;
						}
					}
					delete[]pArr;
					pArr=NULL;
					delete []rankValueArrWithSub;
					rankValueArrWithSub=NULL;
					delete []rankArrWithSub;
					rankArrWithSub=NULL;	
					//delete []predicted_dependentArr;
				//	predicted_dependentArr=NULL;
				//	delete []predictabilityScores;
				//	predictabilityScores=NULL;
				//	delete []betaArr;
					//betaArr=NULL;
			}
				
		
			double* movingSavingTimeArrOut= new double [ researchDataObj->m_numOfItems];
	
			double movingStretch =  cResearchObject::SwapProfilesWithAnchors2(
						movingSavingTimeArrOut,	
							calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
							researchDataObj,  evolPackage,
						profileListSizee,   root ,evolPackage[w]->m_profList[0], globals, 0 , stretArr,
						false, NULL, true,-1,0,NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
			double eta = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
		
			cout<<"end of achor itration \n";
			cout<<eta;
			cout<< "\n";
		}
	}

	int* predictionValueIndex = new int[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		predictionValueIndex[i] = researchDataObj->m_twoDimArray[i][80];
	}
	double* predicValueMethodBasedOnHSLperIndex = new double[5];
	for(int v = 0 ; v < 5 ; v++)
	{
		predicValueMethodBasedOnHSLperIndex[v] = 0.0;
		int sample = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			if(predictionValueIndex[i] ==v)
			{
				sample++;
				predicValueMethodBasedOnHSLperIndex[v]+= researchDataObj->m_depArr[i];
			}
		}
		predicValueMethodBasedOnHSLperIndex[v] /= sample;
	}
	double* predictionValue = new double[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		int index = researchDataObj->m_twoDimArray[i][80];
		predictionValue[i] = predicValueMethodBasedOnHSLperIndex[index];
	}
				
	double etaHSL = cVarianceCalc::CalcualteETA(predictionValue , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout <"ETA HSL and Here before **************************************************************************\n";
	//cout<< movingScre;
//	cout<<" /n";
	cout<< etaHSL;
	cout<<" /n";

				
	delete []predictionValue;
	predictionValue=NULL;
	delete []predictionValueIndex;
	predictionValueIndex=NULL;
				
	delete []predicValueMethodBasedOnHSLperIndex;
	predicValueMethodBasedOnHSLperIndex=NULL;
				
}
 
//3 17 24
void cResearchObject::ProcessOneLevelFromOneAnchorProSet2(
	cScoreGrpArr*& oneLevelScoreGroo ,
	cEvolutionProfilePAckage** evolPackage , int w, cResearchDataObj* researchDataObj,
	 cGlobals* globals, int numOfIter , int l,  bool isToRepaceToLogisticModeoWeights,
	 cProfileObject*   root,  int numOfCalibrationGrps, double* stretArr , double* calbratedThresArr, int* 	bucketIndexArr, 
	 double* calbAgDepArr,   int* calbCntArr, double*  calibatedPRed, int profileListSizee  )
{
	cProfileObject** pArr=new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
	int numOfPrfilesInLevel=  CollectProfilesFromLevel(pArr, l, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER , evolPackage[w]);
	 
	//REPLACE WEIGHTS ACCORDING TO LOGISTIC REGRESSION 3 17 24
	if((oneLevelScoreGroo ==NULL) && isToRepaceToLogisticModeoWeights)
	{
						for(int e=0;e<numOfPrfilesInLevel;e++)
						{
							bool* isIn = new bool[researchDataObj->m_numOfItems];
							int count = FillIsInProfSub(isIn,pArr[e], -1, researchDataObj,NULL);
							bool* isPredictive = new bool[researchDataObj->m_sizeOfItem];
							pArr[e]->SetIsPreddictiveBasedOnSizeAndPoints(isPredictive,researchDataObj->m_sizeOfItem );
							pArr[e]->ReplacePredictiveWightsModel(pArr[e],researchDataObj,isPredictive, 
								globals,isIn,count);//, twoDimShortTemporaryArray );
							delete []isPredictive;
							isPredictive=NULL;
							//ReplacePredictiveWightsModel(pArr[e], researchDataObj, isPredictive,globals, isPredictive,  cGlobals* globals);
							delete []isIn;
							isIn = NULL;
						}		 
	}
	if(oneLevelScoreGroo ==NULL)
	{
		oneLevelScoreGroo = new cScoreGrpArr[numOfPrfilesInLevel];	
	}
	//2 28 24 see who i dont send pArr and num as input for copying the output . then also 
	KeepCurrentWeightsaved2( oneLevelScoreGroo, l,	calbratedThresArr, 	bucketIndexArr, calbAgDepArr,   calbCntArr,  	
				numOfCalibrationGrps,  calibatedPRed,  researchDataObj,	evolPackage[w], profileListSizee, root , globals, stretArr, numOfIter);				
	
					 
	int numOfProfSubs = numOfPrfilesInLevel*evolPackage[w]->m_anchor->GetNumberOfSubGroups();
	double* rankValueArrWithSub=new double[numOfProfSubs];
	RotateToSetProfileRank(	NULL, rankValueArrWithSub, pArr , numOfPrfilesInLevel,evolPackage, researchDataObj,  
													root,  	evolPackage[w]->m_anchor, 	globals,  numOfCalibrationGrps,  stretArr);
	int* rankArrWithSub = new int[numOfProfSubs];
	cVarianceCalc::BuildRankingIndexArr ( rankArrWithSub,  rankValueArrWithSub,  numOfProfSubs);
	//2 28 24 see how after passed the parent competition i copy back to pArr befoer going to the peer competition. 


	//for	(int i= 0 ; i < numOfIter ; i++)
	//{
		cout << "anchor ID :  ";
		cout <<w;
		cout<< "\n";
	//	cout << "iteration : ";
	//	cout<< i;
		cout<<  "\n";
		cout << "level : ";
		cout<<l;
		cout << "\n";
		//cScoreGrpArr* oneLevelScoreGro = NULL;
		//if(oneLevelScoreGro != NULL)
			//(i > 0)
		//{
	//	if(oneLevelScoreGroo ==NULL)
	//	{
	//		oneLevelScoreGroo = new cScoreGrpArr[numOfPrfilesInLevel];	
	//	}
	//	KeepCurrentWeightsaved2( oneLevelScoreGroo, l,	calbratedThresArr, 	bucketIndexArr, calbAgDepArr,   calbCntArr,  	
	//			numOfCalibrationGrps,  calibatedPRed,  researchDataObj,	evolPackage[w], profileListSizee, root , globals, stretArr, numOfIter);				
						 
		int maxIndexOfNonZeroWgh = 0;
		for(int y=0;y< numOfProfSubs ; y++)
		{
			if( rankValueArrWithSub[y] > 0.0)     //,  numOfProfSubs);
			{
				maxIndexOfNonZeroWgh = 	y;
			}
		}
		double bestBP = TryWeighhtByOrderAndKeepBestOPtion3  //1 30 24 try with 2 instead?
				(pArr, NULL, rankArrWithSub,numOfPrfilesInLevel,	evolPackage, stretArr,	root,	 evolPackage[w],
				researchDataObj ,	numOfCalibrationGrps, globals, oneLevelScoreGroo);
		//if(oneLevelScoreGro != NULL)
		//{
		//	delete []oneLevelScoreGro;
		//}
//	}
	delete[]pArr;
	pArr=NULL;
	delete []rankValueArrWithSub;
	rankValueArrWithSub=NULL;
	delete []rankArrWithSub;
	rankArrWithSub=NULL;	
}


void cResearchObject::ParentChildLearning4(//	double* movingSavingTimeArrOut,	
			double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,   cGlobals* globals,
			double* stretArr, int numOfIter,bool isToRepaceToLogisticModeoWeights)
{//todo 2 23 24 see impmortant task with eash dev and much better undersanding. onething to add is when a branch does not ahve neouh prifle
	cout<< "Learning iteration started \n";
		
	int maxHighestLevel = 0;
	int minAnchorLevel = 199;
	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			SetValueToAllProfileAdvPerformance(evolPackage[w],0.0);
			evolPackage[w]->m_anchor->UpdatePerformanceArrays(1.0);

			int higestLlevel = FindHighestLevel(evolPackage[w]);
			int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
			maxHighestLevel = cVarianceCalc::Max(	higestLlevel, maxHighestLevel);
			minAnchorLevel =cVarianceCalc::Min( minAnchorLevel , anchorLevel);
		}
	}		
	
	
	cScoreGrpArr*** oneLevelScoreGroo  = new cScoreGrpArr**[m_profileListSize];
	for(int xxx=0;xxx<m_profileListSize;xxx++)
	{
		oneLevelScoreGroo[xxx]=NULL;
	}
	for(int iterIndex = 0 ; iterIndex < numOfIter ; iterIndex++)
	{
		cout<< "***************************iterIndex************************** : ";
		cout<<iterIndex;
		cout<"*******************************************************************\n";
		for(int requestLbyAboveLoop = minAnchorLevel +1; requestLbyAboveLoop <= maxHighestLevel ; requestLbyAboveLoop++)
		{//set reqeust start with 2 assuming we dont want 
			for(int w = 0 ; w < m_profileListSize ; w++)
			{
				if( (w > 0) ||(m_profileListSize ==1 ))
				{//here cal a funion to do X iterations on cerralin inut level . for example 1 iteration on level 2 . we know 2 is good since we got
					//the w that gives us the highest level. with this we can now only do one iterationn for one level at all the Ws and then assming
					//and need too validat that profiles are keeping their store and we can go and get to a differne W and then go back to the same W.
					//that  just means the num of iter loop is above the loop of the w and that might be the only change. need to test with small saple
					//ust to validate then nthe perm can improve. it is since we are adding weights to profiles from branch X without knowing that they
					//chance the stretch of the person istributin and if you dont exactlyl whhat is the almost final status with all the  changes you 
					//are too surptized and learning on the blidn side. the only risk for this swirh of loops order is that the profiles need to learn
					//ech time starting from what they know alredy and add or remove points . need to see that theyy also  remove when fail . good to 
					//test thie can really get a new score
					int* perLevelProfNum =NULL;
				//	SetValueToAllProfileAdvPerformance(evolPackage[w],0.0);
				//	evolPackage[w]->m_anchor->UpdatePerformanceArrays(1.0);
					int higestLlevel = FindHighestLevel(evolPackage[w]);
					int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
					if(oneLevelScoreGroo[w]==NULL)
					{
						oneLevelScoreGroo[w]=new cScoreGrpArr*[higestLlevel+1];
						for(int d=0;d<=higestLlevel;d++)
						{
							oneLevelScoreGroo[w][d]=NULL;
						}
					}
					int processedLevel = -1;
					for(int l = anchorLevel + 1  ; l <= higestLlevel ; l++)
					{
						if(l == requestLbyAboveLoop)
						{
							processedLevel = l;
							ProcessOneLevelFromOneAnchorProSet2(oneLevelScoreGroo[w][l],	 evolPackage ,  w,  researchDataObj,
									  globals,  1 ,l,   isToRepaceToLogisticModeoWeights,   root,   numOfCalibrationGrps, 
									  stretArr ,  calbratedThresArr,  bucketIndexArr,  calbAgDepArr,    calbCntArr,  calibatedPRed, 
									  profileListSizee );								
							cout <<"processing level :  ";
							cout << processedLevel;
							cout << "\n";
						}
					}					
					double* movingSavingTimeArrOut= new double [ researchDataObj->m_numOfItems];
	
					double movingStretch =  cResearchObject::SwapProfilesWithAnchors2(
								movingSavingTimeArrOut,	
									calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
									researchDataObj,  evolPackage,
								profileListSizee,   root ,evolPackage[w]->m_profList[0], globals, 0 , stretArr,
								false, NULL, true, -1,0,NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
					double eta = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
					cout<<"end of one level one achor set \n";
					cout<<eta;
					cout<< "\n";
				}
			}
		}
	}

	int* predictionValueIndex = new int[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		predictionValueIndex[i] = researchDataObj->m_twoDimArray[i][80];
	}
	double* predicValueMethodBasedOnHSLperIndex = new double[5];
	for(int v = 0 ; v < 5 ; v++)
	{
		predicValueMethodBasedOnHSLperIndex[v] = 0.0;
		int sample = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			if(predictionValueIndex[i] ==v)
			{
				sample++;
				predicValueMethodBasedOnHSLperIndex[v]+= researchDataObj->m_depArr[i];
			}
		}
		predicValueMethodBasedOnHSLperIndex[v] /= sample;
	}
	double* predictionValue = new double[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		int index = researchDataObj->m_twoDimArray[i][80];
		predictionValue[i] = predicValueMethodBasedOnHSLperIndex[index];
	}
				
	double etaHSL = cVarianceCalc::CalcualteETA(predictionValue , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout <"ETA HSL and Here before **************************************************************************\n";
	//cout<< movingScre;
//	cout<<" /n";
	cout<< etaHSL;
	cout<<" /n";

				
	delete []predictionValue;
	predictionValue=NULL;
	delete []predictionValueIndex;
	predictionValueIndex=NULL;
				
	delete []predicValueMethodBasedOnHSLperIndex;
	predicValueMethodBasedOnHSLperIndex=NULL;
				
}
 
void cResearchObject::ParentChildLearning(	double* movingSavingTimeArrOut,	
					double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
					int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj* researchDataObj,
					cEvolutionProfilePAckage**  evolPackage,
				int 	profileListSizee,  cProfileObject* root ,   cGlobals* globals, double* stretArr, int numOfIter)
{
	cout<< "Learning iteration started \n";
	 
	double eta0 = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout<< eta0;
	cout<< "\n";
	//this is  using previous weights. see if new weights are better at thet end. start with only one iteration for now
	double movingScre=0.0;
	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( IS_ADD_CPU_INTENSIVE_PERF_TEST && (w > 0 ||m_profileListSize ==1 ))
		{
			bool isLearningAlreadyStarted = false;
			//open here a loop with iteration uontil getting to isLearningAlreadyStarted = true
			for(int z = 0 ; z < numOfIter ; z++)
			{	
				cout << "iteration number \n";
				cout << z;
				cout << "\n";
				cScoreGrpArr** scoresGrp = NULL;
				int* perLevelProfNum =NULL;
				if(isLearningAlreadyStarted && (z >= MIN_ITERAION_INDEX_TO_IGNORE_0_PROFSUBS))
				{
					cout << "removing profiles with all zero \n";
					RemoveProfilesWithAllSubGroupsZero(evolPackage[w]); 
				}
				int higestLlevel = FindHighestLevel(evolPackage[w]);
				int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
				if(isLearningAlreadyStarted)
				{
					KeepCurrentWeightsaved( scoresGrp, perLevelProfNum,  higestLlevel,   anchorLevel,	calbratedThresArr,  bucketIndexArr, 
						calbAgDepArr,   calbCntArr,  	 numOfCalibrationGrps,  calibatedPRed,  researchDataObj,
					  evolPackage[w], 	profileListSizee,   root ,    globals,  stretArr,  numOfIter);				
				}

				SetValueToAllProfileAdvPerformance(evolPackage[w],0.0);
	
				evolPackage[w]->m_anchor->UpdatePerformanceArrays(1.0);
		
				for(int l = anchorLevel + 1 ; l <= higestLlevel ; l++)//for example an anchor that is not root has 1 anchorLevel and the learning 
					//starts from inclusion rules of 2 levels and then more. no check of 1 level since anchor has 1 and other anchors 
				{
					bool isToOnlyCheckPositiveWeights = z >= MIN_ITERAION_INDEX_TO_IGNORE_0_PROFSUBS;//1 20 24 * add a define instead of iterations 0 1 will be with false means all profsubs will be investigated
					//even 0 perf will be checked in these two levels. 
					bool isWeightedLevelAsBase = false;
					int numOfPrfilesInLevel=0;
				//	cScoreGrpArr* scoreGrpSetPostFirst = neww cProfileObject;
					cProfileObject ** pArr=new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];

					double* rank=new double[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
	
					int* rankArr = new int[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
					for(int gg=0;gg< PROFILE_LIST_PER_ANCHOR_MAX_NUMBER ;gg++)
					{
						rankArr[gg]=gg;
					}
				
					//get  scoreGrpSetPostFirst with local sucess or not and scores for ranking
					//this run does not keep weight on profiles, just checkk and gets back
					bool isAdjustingScoreBasedOnResults = false; //test is to get the outpu andn to use it for ranking
					double* resultPoint1 = new double[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
					PlayWithOneLevelWeightAnalytics3(rank, resultPoint1, pArr, numOfPrfilesInLevel, 
						//perLevelProfNum,
						evolPackage[w]  ,   l,     researchDataObj,  evolPackage[w]->m_anchor,   root,  globals,
						evolPackage,   numOfCalibrationGrps,    movingScre,   stretArr, isToOnlyCheckPositiveWeights,
											isWeightedLevelAsBase, NULL	, isAdjustingScoreBasedOnResults, rankArr);

					double correlScore=0.0;
					double* newPredictionarr = new double[researchDataObj->m_numOfItems];
					SwapAndPredictionCover2(correlScore, newPredictionarr,  evolPackage,
							 root,  evolPackage[w]->m_anchor,  globals,  stretArr,  NULL, researchDataObj,   numOfCalibrationGrps, -1,0,NULL);
					cout<< "end of one level analytics : ";
							//cout <<l;
					cout << "\n";
					cout << correlScore;
					cout << "\n";

					cScoreGrpArr* scoreGrpSetPrevious = NULL;
					if(scoresGrp!= NULL)
					{
						scoreGrpSetPrevious =new cScoreGrpArr[numOfPrfilesInLevel] ;
						for(int www=0;www< numOfPrfilesInLevel ;www++)
						{
							bool isWeight1 = false;
							if(scoresGrp[l][www].m_scoreArr[0] != 0)
							{
								isWeight1 = true;
							}
							scoresGrp[l][www].CopyProfArrOut(scoreGrpSetPrevious[www]);
							bool isWeight2 = false;
							if(scoreGrpSetPrevious[www].m_scoreArr[0] != 0)
							{
								isWeight2 = true;
							}
							if(isWeight1 || isWeight2)
							{
								int ert=0;
							}
						}
					}			
				 //1 22 24 here i can take scoresGrp[l] and adjust scoreGrpSetPostFirst befoer or in between these. need to check
					//this is or the secon iteration it is better to 
					isAdjustingScoreBasedOnResults = true;//test will also adjust profile to initial score plus added if test succeeded
					
					
					//int* rankArr = new int[numOfPrfilesInLevel];
					cVarianceCalc::BuildRankingIndexArr (rankArr, rank, numOfPrfilesInLevel);
					
					double* resultPoint2 = new double[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];;
					PlayWithOneLevelWeightAnalytics3(rank,  resultPoint2,pArr, numOfPrfilesInLevel , 
						//numOfPrfilesInLevel,
						evolPackage[w]  ,   l,     researchDataObj,  evolPackage[w]->m_anchor,   root,  globals,
						evolPackage,   numOfCalibrationGrps,    movingScre,   stretArr, isToOnlyCheckPositiveWeights,
						isWeightedLevelAsBase,scoreGrpSetPrevious,isAdjustingScoreBasedOnResults, rankArr	);

					if(scoreGrpSetPrevious!=NULL)
					{
						delete []scoreGrpSetPrevious;
						scoreGrpSetPrevious=NULL;
					}

					delete []resultPoint2;
					resultPoint2=NULL;
					delete []resultPoint1;
					resultPoint1=NULL;
					 
					delete[]pArr;
					pArr=NULL;

					delete []rankArr;
					rankArr=NULL;
					delete []rank;
					rank=NULL;
				}
				
				for(int u = 0 ; u<= higestLlevel ; u++)
				{
					if(scoresGrp && scoresGrp[u]!= NULL)
					{
						delete []scoresGrp[u];
						scoresGrp[u]=NULL;
					}
				}
				if(scoresGrp!=NULL)
				{
					delete []scoresGrp;
					scoresGrp=NULL;
					delete []perLevelProfNum;
					perLevelProfNum=NULL;
				}
				isLearningAlreadyStarted=true;
			}
				
		
	
			double movingStretch =  cResearchObject::SwapProfilesWithAnchors2(
						movingSavingTimeArrOut,	
							calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
							researchDataObj,  evolPackage,
						profileListSizee,   root ,evolPackage[w]->m_profList[0], globals, 0 , stretArr,
						false, NULL, true, -1,0,NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
			double eta = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
			if(movingScre >eta)
			{
				int sssss=0;		
			}
			else
			{
					int sdggg=0;
			}
			cout<<"end of achor itration \n";
			cout<<eta;
			cout<< "\n";
		}
	}

	int* predictionValueIndex = new int[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		predictionValueIndex[i] = researchDataObj->m_twoDimArray[i][RESEARCH_QUESTION_INDEX];
	}
	double* predicValueMethodBasedOnHSLperIndex = new double[RESEARCH_QUESTION_VAR_VALUE_NUM];
	for(int v = 0 ; v < RESEARCH_QUESTION_VAR_VALUE_NUM ; v++)
	{
		predicValueMethodBasedOnHSLperIndex[v] = 0.0;
		int sample = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			if(predictionValueIndex[i] ==v)
			{
				sample++;
				predicValueMethodBasedOnHSLperIndex[v]+= researchDataObj->m_depArr[i];
			}
		}
		predicValueMethodBasedOnHSLperIndex[v] /= sample;
	}
	double* predictionValue = new double[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		int index = researchDataObj->m_twoDimArray[i][RESEARCH_QUESTION_INDEX];
		predictionValue[i] = predicValueMethodBasedOnHSLperIndex[index];
	}
				
	double etaHSL = cVarianceCalc::CalcualteETA(predictionValue , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout <"ETA HSL and Here before \n";
	cout<< movingScre;
	cout<<" /n";
	cout<< etaHSL;
	cout<<" /n";

				
	delete []predictionValue;
	predictionValue=NULL;
	delete []predictionValueIndex;
	predictionValueIndex=NULL;
				
	delete []predicValueMethodBasedOnHSLperIndex;
	predicValueMethodBasedOnHSLperIndex=NULL;
				
}


void cResearchObject::PostLearningLoop( cResearchDataObj* researchDataObj,
	double* calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int*  calbCntArr, int numOfCalibrationGrps, double* calibatedPRed, 
	cEvolutionProfilePAckage** evolPackage,   int profileListSizee, cProfileObject* root, cGlobals* globals, double* stretArr)
{
	double* movingSavingTimeArrOut= new double [ researchDataObj->m_numOfItems];
	
	int w=0; //place hoodler
	double movingStretch =  cResearchObject::SwapProfilesWithAnchors2(
				movingSavingTimeArrOut,	
					calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed, 
					researchDataObj,  evolPackage,
				profileListSizee,   root ,root,
			//	evolPackage[w]->m_profList[0],
				globals, 0 , stretArr,
				false, NULL, true, -1,0, NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
				
	double eta = cVarianceCalc::CalcualteETA(movingSavingTimeArrOut , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout<<"end of one level one achor set \n";
	cout<<eta;
	cout<< "\n";
	{
		bool* tempBool = new bool[ researchDataObj->m_numOfItems];
		double* predictionTemp = new double[researchDataObj->m_numOfItems];
		int movingIndex = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			tempBool[i]=false;
			if(researchDataObj->m_twoDimArray[i][COUNTRY_POS_INDEX] == COUNTRY_CODE)
			{
				tempBool[i]=true;
				predictionTemp[movingIndex++] = movingSavingTimeArrOut[i];
			}
		}
		cResearchDataObj* tempRse = new cResearchDataObj(researchDataObj, tempBool);
		double etaCountries = cVarianceCalc::CalcualteETA(	predictionTemp , tempRse->m_depArr, tempRse->m_numOfItems);
		cout<<"end of country performance \n";
		cout<<etaCountries;
		cout<< "\n";

	}

	

	int* predictionValueIndex = new int[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		predictionValueIndex[i] = researchDataObj->m_twoDimArray[i][RESEARCH_QUESTION_INDEX];
	}
	double* predicValueMethodBasedOnHSLperIndex = new double[RESEARCH_QUESTION_VAR_VALUE_NUM];
	for(int v = 0 ; v < RESEARCH_QUESTION_VAR_VALUE_NUM ; v++)
	{
		predicValueMethodBasedOnHSLperIndex[v] = 0.0;
		int sample = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			if(predictionValueIndex[i] ==v)
			{
				sample++;
				predicValueMethodBasedOnHSLperIndex[v]+= researchDataObj->m_depArr[i];
			}
		}
		predicValueMethodBasedOnHSLperIndex[v] /= sample;
	}
	double* predictionValue = new double[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		int index = researchDataObj->m_twoDimArray[i][RESEARCH_QUESTION_INDEX];
		predictionValue[i] = predicValueMethodBasedOnHSLperIndex[index];
	}
				
	double etaHSL = cVarianceCalc::CalcualteETA(predictionValue , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	//cout <"\n ETA HSL and Here before **************************************************************************\n";
	//cout<< movingScre;
	cout<<" \n HSL ETA: ";
	cout<< etaHSL;
	cout<<" \n";

				
	delete []predictionValue;
	predictionValue=NULL;
	delete []predictionValueIndex;
	predictionValueIndex=NULL;
				
	delete []predicValueMethodBasedOnHSLperIndex;
	predicValueMethodBasedOnHSLperIndex=NULL;
				

	delete []movingSavingTimeArrOut;


}


void cResearchObject::ParentChildLearning6(	double** rankArrOut, int *numberOfProfSubsOut,   
	double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObjj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,   cGlobals* globals,
			double* stretArr, int iterIndex, bool isToRepaceToLogisticModeoWeights,
			int maxHighestLevel,	int minAnchorLevel, int requestLbyAboveLoop,
			double** rankArrIn,  int globalIterIndex, int  profSubHighestSampleTry,  int  lowestSampleSizeTest,  int ratioOfGoingForZeroWghProfsubs )
{//todo 2 23 24 see impmortant task with eash dev and much better undersanding. onething to add is when a branch does not ahve neouh prifle
	cout<<"";
	cout<<"";
	cout<<"";	
	cout<< "Learning iteration started \n";
	cout<< "NEW ITERATION INDEX  :  ";
	cout << iterIndex;
	cout<<"";

	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			int* perLevelProfNum =NULL;
			int higestLlevel = FindHighestLevel(evolPackage[w]);
			int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
			//if anchor level is 1 , 1 inclusion rule, then need 2 rules to be entering this f unction
			if(requestLbyAboveLoop > anchorLevel && requestLbyAboveLoop <= higestLlevel)//the min is for all branches, here  make sure for this
			{//for given level input, requestLbyAboveLoop, each w will trigger all level of profiles of that w to be collected, copied, zeroed,
				//ranked per parents, and rotate with one another
				cProfileObject** pArr=new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
				int numOfPrfilesInLevel=  CollectProfilesFromLevel(pArr, requestLbyAboveLoop, PROFILE_LIST_PER_ANCHOR_MAX_NUMBER , 	evolPackage[w]);
				if(numOfPrfilesInLevel>0)
				{
					int numOfProfSubs = numOfPrfilesInLevel*evolPackage[w]->m_anchor->GetNumberOfSubGroups();
					int* rankArrWithSubb = new int[numOfProfSubs];
					for(int q=0;q<numOfProfSubs;q++)
					{
						rankArrWithSubb[q]=q;
					}
					cResearchDataObj* flex = researchDataObjj;
					if(researchDataObjj==NULL)
					{
						flex=researchDataObjArr[w];
					}
					double bestBP = TryWeighhtByOrderAndKeepBestOPtion6 (pArr,  rankArrWithSubb, numOfPrfilesInLevel,	evolPackage, stretArr,	root,	
							evolPackage[w],	flex ,	numOfCalibrationGrps, globals,NULL, requestLbyAboveLoop, iterIndex,w, globalIterIndex,
							 profSubHighestSampleTry,   lowestSampleSizeTest, ratioOfGoingForZeroWghProfsubs);
					delete []rankArrWithSubb;
				}
				delete[] pArr;
			}
		}
	}
}





void cResearchObject::ParentChildLearning5(	double** rankArrOut, int *numberOfProfSubsOut,   
	double*	calbratedThresArr, int* bucketIndexArr, double* calbAgDepArr,  int* calbCntArr,  
			int numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObjj,
			cEvolutionProfilePAckage**  evolPackage,  int profileListSizee,  cProfileObject* root ,   cGlobals* globals,
			double* stretArr, int iterIndex, bool isToRepaceToLogisticModeoWeights,
			int maxHighestLevel,	int minAnchorLevel, int requestLbyAboveLoop,
			double** rankArrIn,  int globalIterIndex )
{//todo 2 23 24 see impmortant task with eash dev and much better undersanding. onething to add is when a branch does not ahve neouh prifle
	cout<<"";
	cout<<"";
	cout<<"";	
	cout<< "Learning iteration started \n";
	cout<< "NEW ITERATION INDEX  :  ";
	cout << iterIndex;
	cout<<"";

	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			int* perLevelProfNum =NULL;
			int higestLlevel = FindHighestLevel(evolPackage[w]);
			int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
			//if anchor level is 1 , 1 inclusion rule, then need 2 rules to be entering this f unction
			if(requestLbyAboveLoop > anchorLevel && requestLbyAboveLoop <= higestLlevel)//the min is for all branches, here  make sure for this
			{//for given level input, requestLbyAboveLoop, each w will trigger all level of profiles of that w to be collected, copied, zeroed,
				//ranked per parents, and rotate with one another
				cProfileObject** pArr=new cProfileObject*[PROFILE_LIST_PER_ANCHOR_MAX_NUMBER];
				int numOfPrfilesInLevel=  CollectProfilesFromLevel(pArr, requestLbyAboveLoop, 
												PROFILE_LIST_PER_ANCHOR_MAX_NUMBER , 	evolPackage[w]);
				if(numOfPrfilesInLevel>0)
				{
					int numOfProfSubs = numOfPrfilesInLevel*evolPackage[w]->m_anchor->GetNumberOfSubGroups();
					int* rankArrWithSubb = new int[numOfProfSubs];
					if(globalIterIndex == 0)
					{
						if( rankArrIn != NULL )
						{
							for(int s=0;s<numOfProfSubs;s++)
							{
								rankArrWithSubb[s] = rankArrIn[w][s];
							}
						}
						else
						{
							cResearchDataObj* flex = researchDataObjj;
							if(researchDataObjj==NULL)
							{
								flex=researchDataObjArr[w];
							}
							CalculaterRankOfProfSubParentsPerfValues( rankArrWithSubb,  pArr, numOfProfSubs,
								numOfPrfilesInLevel,  evolPackage,w, flex, root,  globals, 
								numOfCalibrationGrps,  stretArr , requestLbyAboveLoop, iterIndex);
							if( rankArrOut != NULL )// 
							{
								for(int s=0;s<numOfProfSubs;s++)
								{
									rankArrOut[w][s] = rankArrWithSubb[s];
								}
								numberOfProfSubsOut[w] = numOfProfSubs;
							}
						}
					}
					else
					{
						for(int q=0;q<numOfProfSubs;q++)
						{
							rankArrWithSubb[q]=q;
						}
					}
					cResearchDataObj* flex = researchDataObjj;
					if(researchDataObjj==NULL)
					{
						flex=researchDataObjArr[w];
					}
					double bestBP = TryWeighhtByOrderAndKeepBestOPtion5  //1 30 24 try with 2 instead?
						(pArr,  rankArrWithSubb, numOfPrfilesInLevel,	evolPackage, stretArr,	root,	 evolPackage[w],
						flex ,	numOfCalibrationGrps, globals,NULL, requestLbyAboveLoop, 
						iterIndex,w, globalIterIndex);//, NULL);
					delete []rankArrWithSubb;
				}
				delete[] pArr;
			}
		}
	}
}

void cResearchObject::CalculaterRankOfProfSubParentsPerfValues(int* rankArrWithSub, cProfileObject** pArr, 
	int numOfProfSubs,	int numOfPrfilesInLevel, cEvolutionProfilePAckage** evolPackage,int w,
	cResearchDataObj* researchDataObj,	cProfileObject* root, cGlobals* globals, int numOfCalibrationGrps,
	double* stretArr , 	int requestLbyAboveLoop, int iterIndex)
{
	cScoreGrpArr* scoreGrpArr = new cScoreGrpArr[numOfPrfilesInLevel];
	for(int ii=0;ii<numOfPrfilesInLevel;ii++)
	{
		pArr[ii]->CopyOutadvancedPerfScores(scoreGrpArr[ii]);
		pArr[ii]->ZeroAdvancedPerfWeights();
	}
	double* rankValueArrWithSub=new double[numOfProfSubs];
	RotateToSetProfileRank(	NULL, rankValueArrWithSub, pArr , numOfPrfilesInLevel,evolPackage, researchDataObj,  
								root,  	evolPackage[w]->m_anchor, 	globals,  numOfCalibrationGrps,  stretArr);
					 
	cVarianceCalc::BuildRankingIndexArr ( rankArrWithSub,  rankValueArrWithSub,  numOfProfSubs);
	for(int ii=0;ii<numOfPrfilesInLevel;ii++)
	{
		pArr[ii]->CopyInAdvancedPerfScores(scoreGrpArr[ii]);					
	}
	cout << "anchor ID :  ";cout <<w;	cout<< "\n";//	cout << "iteration : ";	//	cout<< i;
	cout<<  "\n";
	cout << "level : ";		cout<<requestLbyAboveLoop;	cout << "\n";
	cout << "iteration index  : " ; cout << iterIndex ; cout <<"\n";
				
	delete []scoreGrpArr;
	delete[] rankValueArrWithSub;				
}

////////////3 17 24 SEE BELow call to ProcessOneLevelFromOneAnchorProSet2 includes calling to the functions needed above as place holder

/*
				int processedLevel = -1;
				for(int l = anchorLevel + 1  ; l <= higestLlevel ; l++)
				{
					if(l == requestLbyAboveLoop)
					{
						processedLevel = l;
						ProcessOneLevelFromOneAnchorProSet2(oneLevelScoreGroo[w][l],	 evolPackage ,  w,  researchDataObj,
									globals,  1 ,l,   isToRepaceToLogisticModeoWeights,   root,   numOfCalibrationGrps, 
									stretArr ,  calbratedThresArr,  bucketIndexArr,  calbAgDepArr,    calbCntArr,  calibatedPRed, 
									profileListSizee );								
						cout <<"processing level :  ";
						cout << processedLevel;
						cout << "\n";
					}
				}	
				*/
		
				
//}


 


 
 
double cResearchObject::SwapProfilesWithAnchors2( double* savlingtieArrOut,
	double* calbratedThresArr, int* bucketIndexArr, double*  calbAgDepArr,  int* calbCntArr,  int numOfCalibrationGrps,
	double* calibatedPRed, cResearchDataObj* researchDataObj, cEvolutionProfilePAckage** evolPackage,
	   int numberOfEvolPrffItems,  cProfileObject* roott  ,cProfileObject* anchorForStretch, cGlobals* globals,  int evoPacackIndexToUpgrade,
	   double* stretArr, bool isThisCaseOfAnchorUniverseIn,   double* savlingtieArrIn, bool isToDEnyCalibration,
	   int inputTargetedProfileID , int inputTargetSample	, double* backUpArrWithAllPastPredictions   ) //objIndex
{
	/*
	8 26 23 
	calibatedPRed -> add an input as lst paramter and a first paramter, and 
	-when there is a first (NO NULL) and no last (NULL), copy all calibatedPRed after the loop to first.  
	when there is a last, and first, copy all the last that are no 0.0 and for the rest calcualted in this function. copy all 
	-array to thte first and above it will decid if need to copy any updated array
	*/  

	bool isToAllowIncludingZeroWeight=false;
	//////////////////from here////////////////////
	int targetSampleTest = researchDataObj->m_numOfItems;
	if(inputTargetSample >= 0 && savlingtieArrIn != NULL)
	{
		targetSampleTest = inputTargetSample;
	}
	int actualySample = 0;
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)//loop abc
	{

		if(savlingtieArrIn != NULL && (savlingtieArrIn[i] != 0.0  || (actualySample >= targetSampleTest && backUpArrWithAllPastPredictions!=NULL)  ))
		{
			if(savlingtieArrIn != NULL && savlingtieArrIn[i] != 0.0)
			{
				calibatedPRed[i] = savlingtieArrIn[i];
			}
			else
			{
				calibatedPRed[i] = backUpArrWithAllPastPredictions[i];
			}
		}
		else
		{
			//m_profileListSize , evolPackage   m_profileListSize  from index i of profile flist , find
			int objIndex = 0;//default is root
	
			for(int p=1;p<numberOfEvolPrffItems; p++)
			{
				if(evolPackage[p]->m_anchor->IsPatientIncluded(researchDataObj->m_twoDimArray[i]) )
				{
					objIndex = p;
				}
			}//GetRightBranchIndex(researchDataObj->m_twoDimArray[i]);
		
			if(numberOfEvolPrffItems > 1 && objIndex ==0)//if there are more than the root, but this is the root  than go here
			{
				calibatedPRed[i] = roott->GetProfileDepAverage() ;//predciton using root. iff i get here more than small cases need to call
				//prediction apip function and use the root model and not just average
			}
			else
			{
				double* predArrOnePers = new double[1];
				double** twoDimOerson = new double*[1];
				twoDimOerson[0] = researchDataObj->m_twoDimArray[i];
				bool isWithExtremeDimension = IS_EXTREME_LAST_SECTION_AND_CALIBRTION;
				bool isWithFineTuning = IS_WITH_FINE_TUNING__LAST_SECTION_AND_CALIBRTION;//6 23 23 phase 6 is in email and phase 7 is to try isWithFineTuning from before we create calibration 
				bool isWithUsingAllProfilesPerAchor =   evoPacackIndexToUpgrade   == objIndex;
				if( (numberOfEvolPrffItems > 1) && (stretArr != NULL))
				{
					isWithUsingAllProfilesPerAchor = stretArr[objIndex] > stretArr[0];
				}


				if(isWithUsingAllProfilesPerAchor)//6 23 23 * here is how i can control and open per control. use only the anchor and open each time only certain anchors 
				{//version false is extlyl like the above base stretch
				 
					bool isWithMinAdvancedPerfWeight = false;
					bool isTargetProfileUsed=false;
					PredictionTasks(isTargetProfileUsed, predArrOnePers, NULL, NULL,twoDimOerson,  NULL,  1,  researchDataObj->m_sizeOfItem , globals, 
						evolPackage[objIndex]->m_profList, evolPackage[objIndex]->m_proffListSize,
						isWithExtremeDimension, 	 isWithFineTuning , isThisCaseOfAnchorUniverseIn, 
						isToAllowIncludingZeroWeight, isWithMinAdvancedPerfWeight, inputTargetedProfileID); // bool &isTargetProfileUsed, //int inputTargetedProfileID
					if(isTargetProfileUsed)
					{
						actualySample++;
					}
					if(isToDEnyCalibration)
					{
						calibatedPRed[i] = evolPackage[objIndex]->Calibrate(*predArrOnePers);
					}
					else
					{
						calibatedPRed[i] = *predArrOnePers;
					}
				}
				else
				{
					int sizeToMathOnlyAnchor = 1;
					bool isWithMinAdvancedPerfWeight=false;
					bool isTargetProfileUsed = false;
					PredictionTasks( isTargetProfileUsed, predArrOnePers, NULL, NULL,twoDimOerson,  NULL,  1,  researchDataObj->m_sizeOfItem , globals, 
						evolPackage[objIndex]->m_profList, sizeToMathOnlyAnchor,  isWithExtremeDimension, 	
						isWithFineTuning , isThisCaseOfAnchorUniverseIn,   isToAllowIncludingZeroWeight, isWithMinAdvancedPerfWeight, -1);
					calibatedPRed[i] = *predArrOnePers;
					//phase 1 see that calibatedPRed is exactly like ppre above. then remove the code with ppre, start with false it
					//phase 2 see what happens if i oepn the if fasle
					if(false)
					{
						calibatedPRed[i] = evolPackage[objIndex]->Calibrate(*predArrOnePers);
					}
					//phase 3 i can check if tunig the calibration also for one profile is any better, or just go to phase 4
					//phase 4 is open isWithUsingAllProfilesPerAchor slectively for certain anchors , and see which ones . move loop abc to a function and call\
					//mulitple times to see which was improving the overall stretch. learn if that relates to how many profiels, or how much it is i the middle.
					//see if any time that it is better not to use the profiles at all
					//see if perhaps frmo that i can decide to gather ancaors or break anchors ,
					//phase 5 is it better to have recursive vars in samem order across differnt anchors ? is it better to add a rule that i dont have a samplepp imite
				//ony number of recursive levels and make it be granty to go all the way, that is when size will make this betetr. in this case
					//i only need to remove the if larger than 30,000 of now and 
				}

				delete [] predArrOnePers;
				predArrOnePers = NULL;
				delete []twoDimOerson;
				twoDimOerson = NULL;
	
			}
		}
	}

	//calbratedThresArr = new double[numOfCalibrationGrps];
	//calbAgDepArr = new double[numOfCalibrationGrps];
//calbCntArr  = new int[numOfCalibrationGrps];

	cProfileObject::CalculateThresholds(calbratedThresArr , numOfCalibrationGrps, 
										calibatedPRed,NULL, researchDataObj->m_numOfItems);
	double depAvgCalibratef = 0.0;

	//bucketIndexArr = new int[researchDataObj->m_numOfItems];
	cProfileObject::CreateAvgDepSubGrps(bucketIndexArr, calbAgDepArr,calbratedThresArr ,calbCntArr, depAvgCalibratef,
					numOfCalibrationGrps,calibatedPRed,researchDataObj->m_depArr, NULL, 
													 researchDataObj->m_numOfItems, *globals);

	double improvedStretchh = StretchLoop(calbAgDepArr,calbCntArr,numOfCalibrationGrps, anchorForStretch->GetProfileDepAverage());


	if(savlingtieArrOut != NULL)
	{
		for(int i = 0 ; i < researchDataObj->m_numOfItems ;i++)
		{
			savlingtieArrOut[i]= calibatedPRed[i];
		}
	}

	return improvedStretchh; 
	/////////////////////////until here
}



void cResearchObject::TemporaryREcursiveCall2( cResearchDataObj* researchDataObj , cProfileObject* root,
												bool* isPredictive,  cGlobals* globals,cVariableSchemaArr* schemaArr,
						cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel* regPredictiveModell	,
											InputVariablesPackageForResearchObj* inputVarObj	)
{
 

	int numOfCalibrationGrps = globals->g_NUMBER_OF_CALIBRATION_GRPS;
	
	double* bucketArr = new double[numOfCalibrationGrps];
	int* cntArr = new int[numOfCalibrationGrps];
	for(int x = 0 ; x< numOfCalibrationGrps ; x++)
	{
		bucketArr[x] = 0.0;
	}
	//int maxNumOfProfes=100000;
	 
	//call to prepare anchors and achive best stretch
	double stretch = 0.0;
	int minSampleToContinueRecursive = globals->g_minSampleToContinueRecursive;//below this amount we DONT go recursive but stop 
	int maxNumOfLevelsToGoRecursive = globals->g_maxNumOfLevelsToContinueRecursive;//above this number we DONT continue recusrive but go to profiles
		//30000;//since no profiles are  here built can go low. when collecting profile ancors
	//once all recursive is done after calling this function below, i ican 
	int movingProfIndex=0;
		 
	cProfileObject** profileList = new  cProfileObject*[m_prifileListMaxSize - 1];//in case it reach that need room for root as a back up for the model
	for(int p = 0 ; p <( m_prifileListMaxSize - 1); p++)
	{
		profileList[p]=NULL;
	}

	int maxNumberOfRulesInDataCollectionSet = SMALL_SAMPLE_TO_START_LEARNING; 
	cInclusionRuleDataSet*	inclusionDataSet = new cInclusionRuleDataSet(maxNumberOfRulesInDataCollectionSet);
	int currentNumOfRecursiveLevels =1;//start with 0 num of recursive levels and each call from recursive to recursive will take 1 more level down
//	bool isTerminalAnchor = 

	bool* isPredictiveRecursive = new bool[researchDataObj->m_sizeOfItem];
	bool* isPredictiveOneLevelUse = new bool[researchDataObj->m_sizeOfItem];
	for(int j=0;j<researchDataObj->m_sizeOfItem;j++)
	{
		isPredictiveRecursive[j] = isPredictiveOneLevelUse[j] = isPredictive[j];
	}
	//int cap = globals->g_capOfForkingPredictiveRecursive;
	researchDataObj->CapIsPredictiveOptionsPerStretch(isPredictiveOneLevelUse, maxNumOfLevelsToGoRecursive, 	root->GetProfileDepAverage());
	for(int j=0;j<researchDataObj->m_sizeOfItem;j++)
	{
	//	isPredictiveRecursive[j] = isPredictiveOneLevelUse[j] ;
	}
	bool isThisCaseOfAnchorUniverse11=true;
	RecursiveProfileBuild(  profileList ,movingProfIndex, bucketArr, cntArr , stretch, 
		m_prifileListMaxSize - 1, numOfCalibrationGrps, researchDataObj,   isPredictiveRecursive,   isPredictiveOneLevelUse,  globals,  
		root->GetProfileDepAverage(), 
		root,  schemaArr , minSampleToContinueRecursive,currentNumOfRecursiveLevels, maxNumOfLevelsToGoRecursive, rootOddPredictiveModel,  regPredictiveModell ,
			inclusionDataSet, isThisCaseOfAnchorUniverse11);
/*	//6 23 23 **** to do summaey-  inclusionDataSet - add a function now to delete all profils that are stored in any created rule set ID, but see two othings - 1 many profiles
	//are repred so first need to creatd a set of only unique profiles so you dont delet these twice. and second, dont delet any profiles that was selected 
	//to be in   profileList , movingProfIndex profiles that were found/created

	//then add for each anchor profile its profiles. create a loop and first use only anchors for a test, try to replaice the output buckets. then add for eachc
	//anchor its profiels and see, then complete

	//the ACGH function can be used here with a smaller set of profiels at first and then more and more.
	//see that the root gets always started with a 0.01 weight in case it meets part of others. in case it is alonw it will be used alone. also see to not use
	//profiles with less than certain size but replace these with root. can do it as part of the AVGH function with one new if

	//try withi both with letting or not the feedom round each bucket

	//add a rule that if the recursive score is lower tha parenet but in a too large sample than always go down. can you the exisiting not used parameter for thats
*/
	
	root->UpdateAdvancePerformance(0.001);//just a back up for if no anchor profile is matched
	m_profileObjectPtrList[0] = root;
	for(int i = 0 ; i < movingProfIndex ; i++)
	{
		profileList[i]->UpdateAdvancePerformance(1.0);
		m_profileObjectPtrList[i+1]= profileList[i];
		m_profileObjectPtrList[i+1]->SetProfileID(i+1);
		m_profileObjectPtrList[i+1]->SetAnchorID(i+1);

	//	GetProfileID(){ return m_profileID;}
//	int GetAnchorID()
	}
	m_profileListSize = movingProfIndex+1;

	double* predArrr = new double[researchDataObj->m_numOfItems];
	double* centerPredArr = new double[researchDataObj->m_numOfItems];
	double* sumAdvancedPErfWghts = new double[researchDataObj->m_numOfItems];
	bool  isWithExtremeDimension = true;//shold not matter for only anchor match but will later so might keep this one true
	int modePRed=0.0;//7 3 23 here waiting to see if the new flexible api to the prediction tasks funciton will crete any better or worse outcomes 
	
	
	
	bool isThisCaseOfAnchorUniverse10 = false;
	double* depAvgArrOut = NULL;
	int* cntArrOut=NULL;
	double* thredArrOut=NULL;
	bool isWithFineTuning= true;

	if(true)
	{
		int sdgg=0;//1 11 24
	}



	double stretchOnlyWithAnchor = ProfileAddingTest( depAvgArrOut, cntArrOut, thredArrOut, predArrr, centerPredArr,  sumAdvancedPErfWghts,	m_profileObjectPtrList ,m_profileListSize,
		researchDataObj,  root->GetProfileDepAverage(),  globals,   modePRed,  numOfCalibrationGrps , NULL, 0, 
		isWithExtremeDimension, isThisCaseOfAnchorUniverse10 ,  isWithFineTuning );
	double* ppre =NULL;
	if(true)
	{
	///////////// want tosee that prediciton ppre is same as predArrr 
		ppre = new double[ researchDataObj->m_numOfItems ];
		int sdfg   =0;
		for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
		{
			int fp = 0;
			for(int p=1;p<m_profileListSize; p++)
			{
				if(m_profileObjectPtrList[p]->IsPatientIncluded(researchDataObj->m_twoDimArray[i]) )
				{
					fp = p;
				}
			}
			cProfileObject** pr = new cProfileObject*[1];
			pr[0] = m_profileObjectPtrList[fp];
			double* predArrOnePers = new double[1];
			int sizeToMathOnlyAnchor = 1;
			bool isWithFineTuning=false;//7 11 23 * 2
			double** twoDimOersonn = new double*[1];
			twoDimOersonn[0] = researchDataObj->m_twoDimArray[i];
			bool isThisCaseOfAnchorUniverse4 = false;
			bool isToAllowIncludingZeroWeight=false;
			bool isWithMinAdvancedPerfWeight=false;
			bool isTargetProfileUsed=false;
			PredictionTasks( isTargetProfileUsed, predArrOnePers, NULL, NULL,twoDimOersonn,  NULL,  1,  researchDataObj->m_sizeOfItem , globals, 
						pr, 1,  isWithExtremeDimension, 	 isWithFineTuning, isThisCaseOfAnchorUniverse4, 
						isToAllowIncludingZeroWeight ,isWithMinAdvancedPerfWeight, -1);			
			ppre[i] = *predArrOnePers;
			
		}
	
	////////////////
	}
	


	cEvolutionProfilePAckage** evolPackage = new cEvolutionProfilePAckage*[m_profileListSize];
	for(int ii = 0 ; ii < m_profileListSize ; ii++)//evolPackage
	{
		 evolPackage[ii]=NULL;
		 if(ii != 0 || m_profileListSize == 1)//0 is root and does not have profiles associated
		 {

			bool* isIn = new bool[researchDataObj->m_numOfItems];
			int sizeOfProff = FillIsInProfSub(isIn,m_profileObjectPtrList, ii, -1,researchDataObj, NULL);//-1 to ask for full proifle
	
			cResearchDataObj* anchorResOBj = new cResearchDataObj(researchDataObj , isIn);
			evolPackage[ii] = new cEvolutionProfilePAckage(m_profileObjectPtrList[ii], anchorResOBj, numOfCalibrationGrps);  //cResearchDataObj* anchorResOBj
			cout<< " /n EvolutionProfilesIncludingPerformanceAdvancte  \n";
			cout << ii;


			EvolutionProfilesIncludingPerformanceAdvancte(evolPackage[ii], inputVarObj,  globals, rootOddPredictiveModel, 
																												regPredictiveModell);

			double* predArrLocal = new double[anchorResOBj->m_numOfItems];
			for(int preIn = 0 ; preIn < anchorResOBj->m_numOfItems ; preIn++)
			{
				predArrLocal[preIn]=0.0; 
			}

			evolPackage[ii]->CleanDeletedProfiles();

			int numOfTiers=3;
			double tierStrucrue[3];
			cProfileObject* flexProf = evolPackage[ii]->m_anchor;
			bool isThisCaseOfAnchorUniverse1 = true;
			if(IS_ANCHOR_UNIVERSE_CROSS_ANCHORS  && isThisCaseOfAnchorUniverse1)//7 6 23 -1
			{
				flexProf = flexProf->GetRootProfile();
			}
			//else
			//{
			flexProf->Prepare3TierValueAbsoloteMode(tierStrucrue);//profileArr[0] is anchor
			//}
			isWithExtremeDimension=IS_EXTREME_LAST_SECTION_AND_CALIBRTION;
			double* depAvgArrOut = NULL;
			int* cntArrOut=NULL;
			double* thredArrOut=NULL;
			bool isWithFineTuning= true;
			double stretchHere =ProfileAddingTest(	depAvgArrOut , cntArrOut, thredArrOut,
				predArrLocal,NULL,NULL, evolPackage[ii]->m_profList ,evolPackage[ii]->m_proffListSize, evolPackage[ii]->m_anchorResOBj,
				flexProf->GetProfileDepAverage(),  globals, modePRed, numOfCalibrationGrps,  tierStrucrue,  
				numOfTiers,  isWithExtremeDimension, isThisCaseOfAnchorUniverse1 ,   isWithFineTuning);
			
			//7 6 23 when trting the non parnets in the comong funciton it also go to the profiels non parents, notice to carefully first add the symetric groiwng 
			evolPackage[ii]->SetCalibrationArraysFromPredArr(predArrLocal,globals);
			//use that ProfileAddingTest () function as a wat to fil predArr with profile based preictions and then fill the dep aray buckets
			cout << " after set calibration arrays \n";
			//then fill the 

			delete []predArrLocal;
			predArrLocal=NULL;
			delete []isIn;
			isIn = NULL;
		}
	}
	
	double* calibatedPRed = new double[ researchDataObj->m_numOfItems] ;

	double* calbratedThresArr = new double[numOfCalibrationGrps];
	double* calbAgDepArr = new double[numOfCalibrationGrps];
	int* calbCntArr  = new int[numOfCalibrationGrps];

//	cProfileObject::CalculateThresholds(calbratedThresArr , numOfCalibrationGrps, 
//										calibatedPRed,NULL, researchDataObj->m_numOfItems);
	double depAvgCalibratef = 0.0;

	int* bucketIndexArr = new int[researchDataObj->m_numOfItems];
//	cProfileObject::CreateAvgDepSubGrps(bucketIndexArr, calbAgDepArr,calbratedThresArr ,calbCntArr, depAvgCalibratef,
//					numOfCalibrationGrps,calibatedPRed,researchDataObj->m_depArr, NULL, 
	//												 researchDataObj->m_numOfItems, *globals);

//	double improvedStretch = StretchLoop(calbAgDepArr,calbCntArr,numOfCalibrationGrps, root->GetProfileDepAverage());



	////////////////////////////////////////////////////////////////////
	
//	int* bucketIndexArr = new int[researchDataObj->m_numOfItems];
//	double* calbratedThresArr = new double[numOfCalibrationGrps];
//	double* calbAgDepArr = new double[numOfCalibrationGrps];
//	int* calbCntArr  = new int[numOfCalibrationGrps];

	bool isThisCaseOfAnchorUniverse6=true;
	double stretArr[1000];
	bool end = false;
	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		stretArr[w] =  cResearchObject::SwapProfilesWithAnchors2(NULL,
				 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,  researchDataObj,  evolPackage,
			    m_profileListSize,   root , root, globals, w , NULL, isThisCaseOfAnchorUniverse6, NULL, false, -1, 0 , NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
	}

	double* movingSavingTimeArrOut = new double[researchDataObj->m_numOfItems];
//	double* savingTimeArrIn = new double[researchDataObj->m_numOfItems];
	
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		movingSavingTimeArrOut[i] = 0.0; 
	//	savingTimeArrIn[i]=0.0;
	}

	double finalStretchh =  cResearchObject::SwapProfilesWithAnchors2(
		movingSavingTimeArrOut,	
		calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,  researchDataObj,  evolPackage,
			    m_profileListSize,   root ,root, globals, 0 , stretArr, isThisCaseOfAnchorUniverse6, NULL, false, -1,0,NULL); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 

	char ch='n';
//	cout<<"enter y if to search for duplicated profiles \n";
//	cin >>ch;
	if(ch == 'y')
	{
		for(int i = 0 ; i < m_profileListSize ; i++)
		{
			int num = 0;
			if(evolPackage[i]!=NULL)
			{
				num = evolPackage[i]->m_proffListSize;
				if(num > 10)
				{
					for(int z = 1 ; z< num ; z++)
					{
						if(evolPackage[i]->m_profList != NULL && evolPackage[i]->m_profList[z]!=NULL)
						{
							if( IsProfileFound( evolPackage[i]->m_profList, z, evolPackage[i]->m_profList[z]))
							{
								delete  evolPackage[i]->m_profList[z];
								evolPackage[i]->m_profList[z]=NULL;
							}
						}
					}
				}
			}
		}
	}

	
	int numberOfGlobalAllGraphItration = 1;//NUMBER_OF_LEARNING_ITERATIONS;
	cout<< "Enter number of numberOfGlobalAllGraphItration:\n";
	cin>>numberOfGlobalAllGraphItration;
	cout<< "Number of learning iteration:\n";
	cout<<numberOfGlobalAllGraphItration;
	cout<< "\n";
	int numberOfInternalIterations = 1;
	cout <<"enter number of internal itrations : ";
	cin >> numberOfInternalIterations;
	cout<< "\n";
	//cout<<"type Y or y to replace to logistic reg mode weights: ";
	bool isToreplaceToLogRegweights = false;
	char chSignToReplace= 'n';
	//cin >> chSignToReplace;
	if(chSignToReplace=='y' || chSignToReplace=='Y')
	{
		isToreplaceToLogRegweights=true;
	}
	cout<<"replace to logistic reg mode weights: ";
	cout << isToreplaceToLogRegweights;
	cout<< "\n";

	//one time only we set all weights to 0 and keep anchors with 1.0 . from that momeny every level 
	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			SetValueToAllProfileAdvPerformance(evolPackage[w],0.0);
			evolPackage[w]->m_anchor->UpdatePerformanceArrays(1.0);
		}
	}
	int maxHighestLevel = 0;
	int minAnchorLevel = 199;
	for(int w = 0 ; w < m_profileListSize ; w++)
	{
		if( (w > 0) ||(m_profileListSize ==1 ))
		{
			int higestLlevel = FindHighestLevel(evolPackage[w]);
			int anchorLevel = evolPackage[w]->m_anchor->GetInclusionRuleListSize();
			maxHighestLevel = cVarianceCalc::Max(	higestLlevel, maxHighestLevel);
			minAnchorLevel =cVarianceCalc::Min( minAnchorLevel , anchorLevel);
		}
	}

//3 26 24 each globacl itervaion cut a different and smaller researchDataObj so the evluation happen quicker	 
	cout<< "total data size is : ";
	cout<< researchDataObj->m_numOfItems;
	cout<< "\n enter small array size for learning repeatition getting started (then it goes up) : ";
	int smallSample= 0;
	cin>>smallSample;
	int mode =  1;
	if(smallSample > 0)
	{
		mode = 	researchDataObj->m_numOfItems / smallSample;
		mode = cVarianceCalc::Max(mode,1);
	}
	cout<<"\n";
	
	for(int a=0;a< numberOfGlobalAllGraphItration ; a++)
	{//3 30 24 todo - add the concept of learning about the whole branches as one, or whether we have more than one center opint. for the BP 
	//in the HOSP question it may be good to have prev hosp 0 and more than 0 as two center points. or just have each branch has its own using just 
		//one new input/control . if said yes, the new research data object will be cut out with an isIs that has only 0 or 1 or 2... when we prepare isIn[w]
		//so hat the poplation will be its own only. using that flag , for IADL for example we now doing all but have a feare of saving and taking ]
		//less overall, having some mode but it is not the same ratio for the same w field, there we take all
		cResearchDataObj** tempDatObj = new  cResearchDataObj*[m_profileListSize];
		for(int w = 0 ; w < m_profileListSize ; w++)
		{
			tempDatObj[w]=NULL;
			if( (w > 0) ||(m_profileListSize ==1 ))
			{
				bool* isIn = new bool [researchDataObj->m_numOfItems];
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					isIn[i] = false;
					int patientBranchIndex =0;// default is root///////////GetRightBranchIndex(researchDataObj->m_twoDimArray[i]);
					if(evolPackage[w]->m_anchor->IsPatientIncluded(researchDataObj->m_twoDimArray[i]) )
					{
						patientBranchIndex = w;
					}
					if(  (patientBranchIndex ==w) || ( (smallSample > 0)&&   ((i+a) % mode ) == 0))
					{
						isIn[i]= true;
					}
				}
				tempDatObj[w] = new cResearchDataObj(researchDataObj , isIn);
				delete [] isIn;
			}
		}

		int  profSubHighestSampleTry=1000;
		int  lowestSampleSizeTest=200;
		int randomChanceForZeroCases = 15;
		if(a>0)
		{
			lowestSampleSizeTest = 150;
		}
		int ratioOfGoingForZeroWghProfsubs = 9;
		cResearchDataObj* flex = NULL;
		int flexLocalIterNumber = numberOfInternalIterations;
		if(	    (a ==( numberOfGlobalAllGraphItration-1)) )//  ||     ( (a>0 ) &&  ( (a%4 )==0 )  )      )
		{
			flex = researchDataObj;
			flexLocalIterNumber = 1;
			profSubHighestSampleTry = 500;
			lowestSampleSizeTest = 100;
			randomChanceForZeroCases = 30;
		}
		 
		LearningIterationsWithinEachLevel2( minAnchorLevel,   maxHighestLevel, flexLocalIterNumber, 
			calbratedThresArr,   
		bucketIndexArr,   calbAgDepArr,    calbCntArr,  numOfCalibrationGrps,  calibatedPRed,  tempDatObj,flex,
		evolPackage,    root ,   globals,  stretArr,  isToreplaceToLogRegweights,   a,   profSubHighestSampleTry,   lowestSampleSizeTest, ratioOfGoingForZeroWghProfsubs);

		//delete [] isIn;
		//delete tempDatObj;
	//	cResearchDataObj** tempDatObj = new  cResearchDataObj[m_profileListSize];
		for(int w = 0 ; w < m_profileListSize ; w++)
		{
			if(tempDatObj && tempDatObj[w]!=NULL)
			{
				delete tempDatObj[w];
			}
		}
		if(tempDatObj )
		{
			delete tempDatObj;
		}

	}

	int* predictionValueIndex = new int[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		predictionValueIndex[i] = researchDataObj->m_twoDimArray[i][RESEARCH_QUESTION_INDEX];
	}
	 int extendingNumOfResearchArraySize = 0;
	if(IS_RESEARCH_INDEX_STARTS_FROM_1)
	{
		extendingNumOfResearchArraySize =1;
	}
	double* predicValueMethodBasedOnHSLperIndex = new double[RESEARCH_QUESTION_VAR_VALUE_NUM + extendingNumOfResearchArraySize];
	for(int v = 0 ; v <( RESEARCH_QUESTION_VAR_VALUE_NUM + extendingNumOfResearchArraySize) ; v++)
	{
		predicValueMethodBasedOnHSLperIndex[v] = 0.0;
		int sample = 0;
		for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
		{
			if(predictionValueIndex[i] ==v)
			{
				sample++;
				predicValueMethodBasedOnHSLperIndex[v]+= researchDataObj->m_depArr[i];
			}
		}
		if(sample >0)
		{
			predicValueMethodBasedOnHSLperIndex[v] /= sample;
		}
	}
	double* predictionValue = new double[ researchDataObj->m_numOfItems];
	for(int i = 0 ; i <  researchDataObj->m_numOfItems ; i++)
	{
		int index = researchDataObj->m_twoDimArray[i][RESEARCH_QUESTION_INDEX];
		index = cVarianceCalc::Min(index , RESEARCH_QUESTION_VAR_VALUE_NUM + extendingNumOfResearchArraySize - 1);
		predictionValue[i] = predicValueMethodBasedOnHSLperIndex[index];
	}
				
	double etaHSL = cVarianceCalc::CalcualteETA(predictionValue , researchDataObj->m_depArr, researchDataObj->m_numOfItems);
	cout <<"\nETA HSL and Here before \n";
	//cout<< movingScre;
	cout<<" \n";
	cout<< etaHSL;
	cout<<" \n";

				
	delete []predictionValue;
	predictionValue=NULL;
	delete []predictionValueIndex;
	predictionValueIndex=NULL;
				
	delete []predicValueMethodBasedOnHSLperIndex;
	predicValueMethodBasedOnHSLperIndex=NULL;
				
	cout<<"wait for enter to continue \n";
	int dd=0;
	cin>>dd;

	PostLearningLoop( researchDataObj, calbratedThresArr, bucketIndexArr, calbAgDepArr,  calbCntArr, numOfCalibrationGrps,  calibatedPRed, 
					evolPackage,    m_profileListSize,  root,   globals,  stretArr);
	
	delete []movingSavingTimeArrOut;
	movingSavingTimeArrOut=NULL;
	//delete []savingTimeArrIn;
//	savingTimeArrIn = NULL;


	//ifi the aabove loop is false final stretch neeed to stay the same
	double finalStretchh2 =  cResearchObject::SwapProfilesWithAnchors2(NULL,
				 calbratedThresArr, bucketIndexArr,  calbAgDepArr,   calbCntArr,  numOfCalibrationGrps, calibatedPRed,  researchDataObj,  evolPackage,
			    m_profileListSize,   root , root, globals, 0 , stretArr, isThisCaseOfAnchorUniverse6, NULL,false,
				-1, 0 , NULL	); //when w is zero i expecte to get same stretch as above improvedStretch. if yes, delete above code 
	if(finalStretchh == finalStretchh2)
	{
		int sdsggggg=0;
	}
	else
	{
		int sdfdfdfd=0;
	}

	cout<<  "performance stretch ";
	cout << finalStretchh;
	cout<< " \n";
	for(int i = 0 ; i < numOfCalibrationGrps ; i++)
	{
		cout<< calbAgDepArr[i];
		cout<< " % \n";
		cout << calbCntArr[i];
		cout<< " \n";
	}
	
	 
	cout<< " IADL, Hosp, Fraily, Cognition, ot Continence: ";
	cout<< "enter any signe :";
	char question = 0;
	char dummy;
	cin>>  dummy;
	 
	int indexOfREsearhPreGrps = -1;
	if(question == 'I' || IS_IADL_RUN)
	{
		indexOfREsearhPreGrps = IADL_RUN_RESEARCH_INDEX;
	}
	if(question == 'H' ||  IS_HOSP_RUN)
	{
		indexOfREsearhPreGrps = HOSP_RUN_INDEX;
	}
	if(question == 'F' ||  IS_FRAILTY_RUN)
	{
		indexOfREsearhPreGrps = FRAILY_RUN_INDEX;
	}
	if(question == 'C' || IS_COGNITION_RUN)
	{
		indexOfREsearhPreGrps = COGNITION_RUN_INDEX;
	}
	if(question == 'T' ||  IS_CONTINENCE_RUN)
	{
		//indexOfREsearhPreGrps = CONTINENCE_RUN_INDEX;
	}
	if(IS_LOCOMOTION_RUN)
	{
		indexOfREsearhPreGrps =  LOCOMOTION_RUN_RESEARCH_INDEX;
	}



	int reduceIn1 = 0;
	
	int min= 1000;
	int max = 0;
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		int x  = int( researchDataObj->m_twoDimArray[i][indexOfREsearhPreGrps]);//1 11 24 change 2 to indexOfREsearhPreGrps
		min = cVarianceCalc::Min(min, x);
		max = cVarianceCalc::Max(max, x);
	}
	int numberOfPreSetValues = max - min + 1;
	if(min > 0)
	{
		reduceIn1 = 1;
	}
	//1 11 24 repalce 8 with numberOfValues


	int* cntEightGrpBuckets = new int[numberOfPreSetValues];
	int** twoDimCnt = new int*[numberOfPreSetValues] ;//8+1
	double** twoDimPerc = new double*[numberOfPreSetValues] ;//8+1
	double** twoDimDepVal = new double*[numberOfPreSetValues] ;//8+1
	for(int e = 0 ; e < numberOfPreSetValues ; e++)
	{
		cntEightGrpBuckets[e]=0;
		twoDimCnt[e] = new int[numOfCalibrationGrps]; 
		twoDimPerc[e] =  new double[numOfCalibrationGrps]; 
		twoDimDepVal[e] =  new double[numOfCalibrationGrps]; 
		for(int x = 0 ; x< numOfCalibrationGrps ; x++)
		{
			twoDimCnt[e][x] = 0;
			twoDimPerc[e][x] = 0.0;
			twoDimDepVal[e][x] = 0.0;
		}
	}
 	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		int eightGroIndex = int( researchDataObj->m_twoDimArray[i][indexOfREsearhPreGrps]) - reduceIn1;
		//1 11 24 change 2 to indexOfREsearhPreGrps . change -1 t0 -  reduceIn1

		if(eightGroIndex >=0 && eightGroIndex < numberOfPreSetValues)
		{
			cntEightGrpBuckets[eightGroIndex]++;
			int algoGrpIndex = bucketIndexArr[i];
			twoDimCnt[eightGroIndex][algoGrpIndex]++;
			twoDimDepVal[eightGroIndex][algoGrpIndex] += researchDataObj->m_depArr[i];
		}
	}
	//1 11 24 replace 8 with numberOfValues
	for(int e = 0 ; e < numberOfPreSetValues ; e++)
	{
		for(int x = 0 ; x< numOfCalibrationGrps ; x++)
		{
			if(twoDimCnt[e][x] > 0)
			{
				twoDimDepVal[e][x] /= twoDimCnt[e][x];
			}
		}
	}

	//1 11 24 replace 8 with numberOfValues
	for(int e = 0 ; e < numberOfPreSetValues ; e++)
	{
		cout<< e;
		cout << "\n";
		for(int x = 0 ; x< numOfCalibrationGrps ; x++)
		{
			if( cntEightGrpBuckets[e] > 0)
			{
				twoDimPerc[e][x] = (double(twoDimCnt[e][x])) /  ( double(cntEightGrpBuckets[e]));
			}
			else  
			{
				int sdffg=0;
			}
			cout<< twoDimPerc[e][x] ;
			cout << "\n";
			cout<< twoDimDepVal[e][x] ;
			cout << "\n";
		}
		cout << "\n";
	}
	int ssdgdg = 0 ;
	cout << "end of report. enter 1 to continue \n";

	int valueInput =1;
	cin>>valueInput;
	cout << valueInput;
	cout << "\n";
	



//remove profiles with only 0 wiegeht of advanced performacne. NULL the profile and delete it. 
	//also send profiles which left to smoothing
	for(int ii = 0 ; ii < m_profileListSize ; ii++)//evolPackage
	{
		if( evolPackage[ii] != NULL)
		{//check to smotth and remove only non anchor
			for(int x = 1 ; x < evolPackage[ii]->m_proffListSize ; x++)
			{
				double tempAdvPerf[100];
				evolPackage[ii]->m_profList[x]->CopyAdvPerfArrOut(tempAdvPerf);
				int numOffSubGrps = evolPackage[ii]->m_profList[x]->GetNumberOfSubGroups();
				bool allSubGrpsAreZero = true;
				for(int eee=0; eee < numOffSubGrps ; eee++)
				{
					if(tempAdvPerf[eee] > 0.0)
					{
						allSubGrpsAreZero  = false;
					}
				}
				if(!allSubGrpsAreZero  )
				{
					if(IS_TO_SMOOTH_ADVANCED_PERF_BUCKET_VALUES)
					{
						evolPackage[ii]->m_profList[x]->SmoothAdvancedPerfWeights();
					}
				}
				else if( IS_TO_REMOVE_ZERO_PERF_PROFILES )
				{
				//	delete evolPackage[ii]->m_profList[x];//8 12 23 check if this is not getting deleted elsewhere only then open
					evolPackage[ii]->m_profList[x] = NULL;
				}
			}
		}
	}

	cProfileObject** tempProfArr = new cProfileObject*[100000];
	int movingProfileIndex = 0;
	tempProfArr[0]=root;
	tempProfArr[0]->SetAnchorID(0);
	tempProfArr[0]->SetProfileID(0);
	movingProfileIndex++;

	if(m_profileListSize == 1)
	{//8 12 23 validate that position 0 is the root so we dont need to copy it  . look at the poiints of root from api
		for(int i = 1 ; i < evolPackage[0]->m_proffListSize ; i++)//evolPackage
		{
			if(evolPackage[0]->m_profList[i] != NULL)
			{
				tempProfArr[ movingProfileIndex] = evolPackage[0]->m_profList[i]; 
				tempProfArr[ movingProfileIndex]->SetAnchorID(0);
				tempProfArr[ movingProfileIndex]->SetProfileID(movingProfileIndex);
				movingProfileIndex++;
			}
		}
	}
	else
	{//ii and m_profileListSize are  here anchors and not all profiles as aboe i and m_profileListSize
		for(int ii = 0 ; ii < m_profileListSize ; ii++)//evolPackage
		{//8 12 23 validate that here ii == 0 is not havint anyhting to add
			if(  ii>0  )
			{
				tempProfArr[ movingProfileIndex] = evolPackage[ii]->m_anchor;
				tempProfArr[ movingProfileIndex]->SetAnchorID(ii );
				tempProfArr[ movingProfileIndex]->SetProfileID(movingProfileIndex);
				movingProfileIndex++;
				for(int x = 1 ; x < evolPackage[ii]->m_proffListSize ; x++)
				{
					if( evolPackage[ii]->m_profList[x] != NULL)
					{
						tempProfArr[ movingProfileIndex] = evolPackage[ii]->m_profList[x]; 
						tempProfArr[ movingProfileIndex]->SetAnchorID(ii );
						tempProfArr[ movingProfileIndex]->SetProfileID(movingProfileIndex);
						movingProfileIndex++;
					}
				}
			}
		}
	}
	m_profileListSize = movingProfileIndex;
	for(int i = 0 ; i <  m_profileListSize ; i++)
	{
		m_profileObjectPtrList[i] = tempProfArr[i];
	}
	delete []tempProfArr;
	tempProfArr=NULL;
	//8 4 23
/*	 evolPackage ,m_profileListSize
   evolPackage[i] is full with list of profiles and then aldo 
   m_profileObjectPtrList[0] has root and evolPackage[0] has a list of all including [0], if m_profileListSize ==0
   if m_profileListSize > 0 than we eget  m_profileObjectPtrList[0] and then evolPackage[i] , i> 0 has set of anchor and all proifles
	   //created to be copied to the m_profileObjectPtrList and m_profileListSize will be updated
*/

	//for each of the original 8 grp desribe the percentage of those that are in the 0-9 10 algorithm gruops.
	// for example i want to see that in grop 1 (index 0) of the orginal i get 60% grop 1 algo, 20% grp 2, etc. know know whic is group 1-8 based on
	//person m_twoDimArray[i][2] ; field 2 index 
	/*double** origArrToAlgo = new double*[8];
	for(int xx = 0 ; xx < 7 ; xx++)
	{
		int grp = researchDataObj->m_twoDimArray[2];
		twoDimCnt[grp] ++;
		allCnt++;






		origArrToAlgo[xx] = new double[numOfCalibrationGrps];
	}
	*/

	delete []bucketIndexArr;
	bucketIndexArr=NULL;

	delete []calibatedPRed;
	calibatedPRed = NULL;
	delete []calbratedThresArr;
	calbratedThresArr=NULL;
	delete []calbAgDepArr;
	calbAgDepArr=NULL;
	delete[]calbCntArr;
	calbCntArr=NULL;

	delete []predArrr;
	predArrr=NULL;
	delete[]centerPredArr;
	centerPredArr=NULL;
	delete []sumAdvancedPErfWghts;
	sumAdvancedPErfWghts=NULL;

	delete []isPredictiveRecursive;
	isPredictiveRecursive=NULL;
	delete []isPredictiveOneLevelUse;
	isPredictiveOneLevelUse=NULL;

	//Copy Profiles to main array profile list
	delete []profileList;
	profileList=NULL;
	delete []bucketArr;
	bucketArr=NULL;

	delete inclusionDataSet;
	inclusionDataSet=NULL;
}


void cResearchObject::LearningIterationsWithinEachLevel(int minAnchorLevel,  int maxHighestLevel, int numberOfInternalIterations,
	double* calbratedThresArr,  int* bucketIndexArr,  double* calbAgDepArr,   int* calbCntArr,  
	int	numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObj,
	cEvolutionProfilePAckage**	evolPackage,  cProfileObject*  root , cGlobals*  globals, 
	double* stretArr,  bool isToreplaceToLogRegweights,  int globalIterIndex)
{
	for(int requestLbyAboveLoop = minAnchorLevel +1; requestLbyAboveLoop <= maxHighestLevel ; requestLbyAboveLoop++)
	{
		int maxPossibleProfSubs = PROFILE_LIST_PER_ANCHOR_MAX_NUMBER  * m_numberOfSubGrps;
		double** rankArrOutAndIn= new double* [m_profileListSize];
		int* numberOfProfSubsOut = new int[m_profileListSize]; 
		for(int ww=0;   ww< 	m_profileListSize ; ww++)
		{
			numberOfProfSubsOut[ww]=0;
			rankArrOutAndIn[ww] = new double[maxPossibleProfSubs];
			for(int i = 0 ; i < maxPossibleProfSubs ; i++)
			{
				rankArrOutAndIn[ww][i]=0.0;
			}
		}
		for(int ss=0; ss< numberOfInternalIterations ; ss++)
		{
			if(ss == 0){
				ParentChildLearning5 (	rankArrOutAndIn, numberOfProfSubsOut,
						calbratedThresArr,  bucketIndexArr,  calbAgDepArr,   calbCntArr,  
						numOfCalibrationGrps,  calibatedPRed,  researchDataObjArr,  researchDataObj,
						evolPackage, m_profileListSize,  root ,    globals, stretArr ,ss, isToreplaceToLogRegweights,
						maxHighestLevel,	 minAnchorLevel, requestLbyAboveLoop, NULL ,globalIterIndex);
			}
			else
			{
				ParentChildLearning5 (	NULL,			 numberOfProfSubsOut,
						calbratedThresArr,  bucketIndexArr,  calbAgDepArr,   calbCntArr,  
						numOfCalibrationGrps,  calibatedPRed,  researchDataObjArr,  researchDataObj,
						evolPackage, m_profileListSize,  root ,    globals, stretArr ,ss, isToreplaceToLogRegweights,
						maxHighestLevel,	 minAnchorLevel, requestLbyAboveLoop, rankArrOutAndIn,globalIterIndex );
			}
		}

		for(int ww=0;ww< 	m_profileListSize ; ww++)
		{
			delete []rankArrOutAndIn[ww];
			rankArrOutAndIn[ww]=NULL;
		}

		delete []rankArrOutAndIn;
		rankArrOutAndIn=NULL;
		delete []numberOfProfSubsOut;
		numberOfProfSubsOut=NULL;
		 
	}
}


void cResearchObject::LearningIterationsWithinEachLevel2(int minAnchorLevel,  int maxHighestLevel, int numberOfInternalIterations,
	double* calbratedThresArr,  int* bucketIndexArr,  double* calbAgDepArr,   int* calbCntArr,  
	int	numOfCalibrationGrps, double* calibatedPRed, cResearchDataObj** researchDataObjArr, cResearchDataObj* researchDataObj,
	cEvolutionProfilePAckage**	evolPackage,  cProfileObject*  root , cGlobals*  globals, 
	double* stretArr,  bool isToreplaceToLogRegweights,  int globalIterIndex, int  profSubHighestSampleTry,  
	int  lowestSampleSizeTest, int ratioOfGoingForZeroWghProfsubs)
{
	for(int requestLbyAboveLoop = minAnchorLevel +1; requestLbyAboveLoop <= maxHighestLevel ; requestLbyAboveLoop++)
	{
		for(int ss=0; ss< numberOfInternalIterations ; ss++)
		{
			ParentChildLearning6 (	NULL, NULL,
						calbratedThresArr,  bucketIndexArr,  calbAgDepArr,   calbCntArr,  
						numOfCalibrationGrps,  calibatedPRed,  researchDataObjArr,  researchDataObj,
						evolPackage, m_profileListSize,  root ,    globals, stretArr ,ss, isToreplaceToLogRegweights,
						maxHighestLevel,	 minAnchorLevel, requestLbyAboveLoop, NULL ,globalIterIndex, profSubHighestSampleTry,  
						lowestSampleSizeTest , ratioOfGoingForZeroWghProfsubs);
		}
	}
}

/*
get the buckets array and stretch using either the input anchorPr and its model or a merge of differnet calls recursibely 
to get the same bucket and stretch out but using a different method


*/
 

void cResearchObject::GetBucketsUsingInputAnchorProfile( double* depBucketAnchorArr, int* depBucketSmpleArr, 
	int numOfCalibrationGrps, cProfileObject* anchorPr ,  cResearchDataObj*	researchDataObj, cGlobals* globals )

{
	double* predArr =new double[ researchDataObj->m_numOfItems];
	for(int i = 0; i < researchDataObj->m_numOfItems ; i++)
	{
		predArr[i]=0.0;
			
		double predictionWithInterv=0.0;
		double preditionWitoutInterv=0.0;
		double performanceReg=0.0;
		double performanceAdv=0.0;	
		int profileID=-1;
		int subGrpIndex=-1;
		bool isWithFineTuning=true;
		bool isAdvancedPerfGetbEstMatch=true;
		
		anchorPr->PredictionElementsNEW( predArr[i] , predictionWithInterv, preditionWitoutInterv,
			performanceReg , performanceAdv, profileID,  subGrpIndex,	researchDataObj->m_twoDimArray[i] ,
			researchDataObj->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
	}

	double* threshArr = new double[numOfCalibrationGrps];
	double depAvg=0.0;
	cProfileObject::CalculateThresholds(threshArr , numOfCalibrationGrps, 
										predArr,NULL,researchDataObj->m_numOfItems);
	
	cProfileObject::CreateAvgDepSubGrps(NULL, depBucketAnchorArr,threshArr ,depBucketSmpleArr, depAvg,
			numOfCalibrationGrps,predArr,researchDataObj->m_depArr, NULL, researchDataObj->m_numOfItems, *globals);


	delete []threshArr;
	threshArr=NULL;
	delete []predArr;
	predArr=NULL;
}


//StretchLoop(double* avgDepArr,  int* cntArr,    int numOfPerformanceSubGrps , double anchorvAluee)
/*double GetStretchVAlueWithInputAnchor(double* depBucketAnchorArr, int* depBucketSmpleArr, int numOfCalibrationGrps, double depAnchor )
{
	double stretch=0.0;

	return stretch;
}*/

//6 23 23 * left to do this function and left to connect the temporary calling to recursive to what is today. 
void cResearchObject::MergerTwoDimDepArraysToOneDim(double* depArrMErged , int*  depArrCntMeged, 
								double**  depArrValueTwoDim, int** depArrValueCntTwoDim , int numOfValues, int numOfCalibGrps)
{
	int lineSize = numOfValues * numOfCalibGrps;
	double* depValInOneLine = new double[lineSize];
	int* depCntnOneLine = new int[lineSize];
	for(int i = 0 ; i <lineSize ; i++)
	{
		depValInOneLine[i] = 0.0;
		depCntnOneLine[i]=0;
	}
	int movingI = 0;
	for(int v = 0 ; v< numOfValues ; v++)
	{
		for(int c = 0 ; c< numOfCalibGrps ; c++)
		{
			depValInOneLine[movingI] = depArrValueTwoDim[v][c];
			depCntnOneLine[movingI] = depArrValueCntTwoDim[v][c];
			movingI++;
		}		
	}
	double* sortedDepValInOneLine = new double[lineSize];
	int* sortedDepCntnOneLine = new int[lineSize];
	bool* isTaken = new bool[lineSize];
	for(int i = 0 ; i <lineSize ; i++)
	{
		isTaken[i]=false;
	}
	for(int i = 0 ; i <lineSize ; i++)
	{
		double lowestDep = 1.0;
		int lowestIndex = -1;
		for(int ii = 0 ; ii < lineSize ; ii++)
		{
			if(isTaken[ii] == false)
			{
				if(depValInOneLine[ii] < lowestDep)
				{
					lowestDep = depValInOneLine[ii];
					lowestIndex = ii;
				}
			}
		}
		if(lowestIndex>=0)
		{
			isTaken[lowestIndex] = true;
			sortedDepValInOneLine[i] = depValInOneLine[lowestIndex];
			sortedDepCntnOneLine[i] = depCntnOneLine[lowestIndex];
		}
		else
		{
			sortedDepValInOneLine[i] = 0.0;
			sortedDepCntnOneLine[i]=0;
		}
	}

	int fullNum = 0;
	for(int i = 0 ; i <lineSize ; i++)
	{
		fullNum += sortedDepCntnOneLine[i];
	}

//	double* depArrMErged , int*  depArrCntMeged, 
	//int movingSourceI = 0;
//	int firstIndexToConsider =0;
	int numCollectedSoFar = 0 ;
	int lowest  = 0;
	int highest= -1;
	for(int x = 0 ; x< numOfCalibGrps ; x++)
	{
	
		int countExpeccted = (fullNum - numCollectedSoFar) / (numOfCalibGrps-x);
		if(countExpeccted >0)
		{
			CollectLowestAndHighestIndexForNextGrp( lowest, highest, sortedDepCntnOneLine ,  lineSize, countExpeccted);
		
			//int numOfBucketsToCollet = (highest - lowest)+1;
			double averg = 0.0;
			double wghtSum = 0.0;
			for(int xx = lowest ; xx <= highest ; xx++)
			{
				averg += sortedDepValInOneLine[xx] *  (double (sortedDepCntnOneLine[xx] ));
				wghtSum +=  (double (sortedDepCntnOneLine[xx] ));
			}
			int counotTakenThisIter = int(wghtSum);
			numCollectedSoFar += counotTakenThisIter;
			if(wghtSum > 0.0)
			{
				averg /= wghtSum;
			}
			depArrMErged[x] = averg;
			depArrCntMeged[x] = counotTakenThisIter;

			lowest = 	highest + 1;

			if(depArrCntMeged[x]==0 && depArrMErged[x]>0.0)
			{
				int sdf=0;
			}
		}
		else
		{
			depArrMErged[x] = 0.0;
			depArrCntMeged[x] = 0;
		}

	}
	cout<<"ISTAKEN \n";
	delete []isTaken;
	isTaken=NULL;
	delete []sortedDepValInOneLine;
	sortedDepValInOneLine=NULL;
	delete []sortedDepCntnOneLine;
	sortedDepCntnOneLine=NULL;
	delete []depValInOneLine;
	depValInOneLine=NULL;
	delete []depCntnOneLine;
	depCntnOneLine=NULL;
}


void cResearchObject::CollectLowestAndHighestIndexForNextGrp( int lowest, int &highest, int* sortedDepCntnOneLine ,
	  int lineSize, int countExpeccted)
{
	bool end= false;
	int sumCollected = 0 ; 
	for(int i = lowest ; i < lineSize && (!end) ; i++)
	{
		sumCollected += sortedDepCntnOneLine[i];
		if(sumCollected >= countExpeccted)
		{
			highest = i;
			end = true;
		}
	}
	if(end == false)
	{
		highest = lineSize-1;
	}

}
	



bool cResearchObject::RecursiveProfileBuild(
	cProfileObject** profileListt, int &movingPrIndexx,	double*  bucketArrOut  , int* bucketCntArrOut, double &stretchOutt,  
	           int maxNumOfProfes, int numOfCalibrationGrps, 	cResearchDataObj* researchDataObj, 
			   bool* isPredictiveRecursive,  bool* isPredictiveOneLevelUse,
	                    cGlobals* globals,   double depAnchorUniv,	 cProfileObject*  anchorPr,
				cVariableSchemaArr* schemaArr, int minSampleToContinueRecursive, int currentNumOfRecursiveLevels, int  maxNumOfLevelsToGoRecursive,
						cPercentileCalculationModel* rootOddPredictiveModel,
						cPercentileCalculationModel* regPredictiveModell	,
						cInclusionRuleDataSet*	inclusionDataSetLocal, bool isThisCaseOfAnchorUniverseIn)
{
//	int maxNumberOfRulesLocal = 10000; 
	//cInclusionRuleDataSet*	inclusionDataSetLocal = new cInclusionRuleDataSet(maxNumberOfRulesLocal);
 


	double maxStretch = 0.0;
	int indexOfNextVar = -1;
	int numOfVars = researchDataObj->m_sizeOfItem;
	double** depArrTdim = new double*[numOfVars];
	int** depArrTdimCnt = new int*[numOfVars];
	for(int v = 0 ; v < numOfVars ; v++)
	{

		depArrTdim[v] = new double[numOfCalibrationGrps];
		depArrTdimCnt[v] = new int[numOfCalibrationGrps];
		for(int x=0;x<numOfCalibrationGrps;x++)
		{
			depArrTdim[v][x]=0.0;
			depArrTdimCnt[v][x]=0;
		}
	}
//threeDimProf is set of profiles coming from one variable and from multiple values combined to be one per variable profile lsit.
	//in the end of the loop the set under the selected varible,  coming from mulitpe values, added, will be copied out.
	//if a value of a varible does is a terminal then the added set of profiles per this varible will be not from the recusrivve but locally evolution
//	int numOfVars = researchDataObj->m_sizeOfItem;
	if(currentNumOfRecursiveLevels ==3)
	{
		int sdg = 0 ;
	}
	double* strechArray = new double[numOfVars];
	bool isWithMinAdvancedPerfWeight = true;

	bool ret = true;

	cProfileObject*** threeDimProff = new cProfileObject**[numOfVars];
	int* movingProfInxx = new int[numOfVars];
	double** varValCnt = new double*[numOfVars]; 
	double* varValOptions = new double[numOfVars];//how mant values per each variale
	for(int v  = 0 ; v< numOfVars ; v++)
	{
		threeDimProff[v] = NULL; 
		movingProfInxx[v]=0;
		strechArray[v]=0.0;
		varValCnt[v] = NULL;
		if(isPredictiveOneLevelUse[v])// using the "one levell use" that h as capped num of predictive varibels. not all has cpu time to get streth
			//but when moving the list of predctive o the next level of recusrive, sending all the options not only the limmited per onoe try
		{
			cout<<v;
			cout<<"\n";
			if(currentNumOfRecursiveLevels==0 && v==0)
			{
				int sdfg=0;
			}
			cout<<123456;
			cout<<"\n";
			threeDimProff[v]  = new cProfileObject*[maxNumOfProfes];
			for(int s=0;s<maxNumOfProfes;s++)
			{
				threeDimProff[v][s]=NULL; 
			}
		//	if(schemaArrr->m_schemaArr[v]->m_isPredictiveVariable)
			int numOfValues = schemaArr->m_schemaArr[v]->m_numberOfValues;
			varValOptions[v]=numOfValues;
			double** depArrValues = new double*[numOfValues];
			int** depArrValueCnt = new int*[numOfValues];
			varValCnt[v] = new double[numOfValues];
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				depArrValues[vl] = new double[numOfCalibrationGrps];
				depArrValueCnt[vl] = new int [numOfCalibrationGrps];
				
				for(int x = 0 ; x< numOfCalibrationGrps ; x++)
				{
					depArrValues[vl][x] = 0.0;
					depArrValueCnt[vl][x]=0;
				}
			}
				 
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				varValCnt[v][vl] = 0;
				if(currentNumOfRecursiveLevels==0 && v==0)
				{
					int sdfsdfg=0;
				}
				cProfileObject** profListPerVal = new cProfileObject*[maxNumOfProfes];
				int movingIndexPervalue = 0;
				double val =  m_schemaArrr->m_schemaArr[v]->m_varValues[vl];
				cout<<1234567;
				cout<<"\n";
				bool* isPersonIn = new bool [researchDataObj->m_numOfItems];
				for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
				{
					isPersonIn[i]=false;
					if(researchDataObj->m_twoDimArray[i][v] == val)
					{
						isPersonIn[i]=true;
					}
				}
				cResearchDataObj* resObj = new cResearchDataObj(  researchDataObj ,   isPersonIn);
				varValCnt[v][vl] = resObj->m_numOfItems;

				int numOfIncliusionRulesAnchor = anchorPr->GetInclusionRuleListSize();
				int numOfNewIncusionRules = numOfIncliusionRulesAnchor+1;
				cVariableAndValueAndPoints* newInclusionArr = new cVariableAndValueAndPoints[numOfNewIncusionRules];
				for(int s = 0 ; s < numOfIncliusionRulesAnchor ; s++)
				{
					newInclusionArr[s] = anchorPr->GetInclusionRuleList()[s];
				}
				cout<<12345678;
				cout<<"\n";
				cVariableAndValueAndPoints newRule(v,val,0.0);
				newInclusionArr[numOfNewIncusionRules-1]= newRule;
				
					
				
				int foundRuleIndex = -1;
				bool isExsitedSameRuleSet =// inclusionDataSet
						            inclusionDataSetLocal->IsAreadyExsistts(
										foundRuleIndex, newInclusionArr , numOfNewIncusionRules );//AddAsExsisted
				if( isExsitedSameRuleSet)
				{
					for(int x = 0 ; x < numOfCalibrationGrps ; x++)
					{
						if( inclusionDataSetLocal->GetDepArr(foundRuleIndex) == NULL)
						{
							int sdgg = 0 ;// woudl we get here? if yes need another solution
						}
						depArrValues[vl][x]= inclusionDataSetLocal->GetDepArr(foundRuleIndex)[x] ;
						depArrValueCnt[vl][x] = inclusionDataSetLocal->GetDepArrCnt(foundRuleIndex)[x]; 
						//6 23 23 **** Solitionn - inclusionDataSet a new member of this recursive function and not as an input from the caller.
						//here need to copy also profiles to the data set, and then copy out when found shared. 
						//open members in inclusionDataSet to  hold these profles per each rule set
						//if what i put in the inclusion data set object is all the profiles i can  open one for every recursive instance
						//if not expansive and just delete all profiles from here at the end of the recusrive. 
					}
					cout<<123456789;
					cout<<"\n";
					// profListPerVal, movingIndexPervalue
					cProfileObject** tempPrfArr = NULL;
						 
					inclusionDataSetLocal->GetProfileArrPErRuleIndex( tempPrfArr, movingIndexPervalue, foundRuleIndex);
					for(int d = 0 ; d < movingIndexPervalue ; d++)
					{
						profListPerVal[d] = tempPrfArr[d];
					}
				}
				else
				{
					cout<<v;
					cout<<"\n";
					cout<<currentNumOfRecursiveLevels;
					cout<<"\n";
					cout<<12345699999;
					cout<<"\n";
					if(currentNumOfRecursiveLevels==2 &&resObj->m_numOfItems==76 && v==17 && vl==3)
					{
						int sdvg=0;//check why below recusrive did not retur any profile set. 
					}

					cProfileObject* root = anchorPr->GetRootProfile();
					cProfileObject* anchorProfileCandidate = new cProfileObject(this,movingPrIndexx,root,
										newInclusionArr , numOfNewIncusionRules, resObj,movingPrIndexx,NULL  );
					PRepareModelAndAdjustPErRootRegreMOdel(rootOddPredictiveModel, regPredictiveModell,anchorProfileCandidate , *globals );
					anchorProfileCandidate->SetPerformanceToDefault( *globals );//just to set to nutural before get the real calculation below


					if(currentNumOfRecursiveLevels ==3 && newInclusionArr[0].m_variableIndex==0 && newInclusionArr[1].m_variableIndex > 0 && v==17	)
					{
						int sdffg=0;
					}


					if(resObj->m_numOfItems < 200)
					{
						int sdg =0;
					}
	
					GetBucketsUsingInputAnchorProfile(  depArrValues[vl], 	depArrValueCnt[vl], numOfCalibrationGrps, 
														anchorProfileCandidate ,	resObj ,globals);
					double anchorPrStretchh = StretchLoop( depArrValues[vl], depArrValueCnt[vl],  numOfCalibrationGrps ,depAnchorUniv);
									
					//bool isAnchorCandidateShiftedFromParientSig =
						//(cVarianceCalc::Abs( anchorProfileCandidate->GetProfileDepAverage() - anchorPr->GetProfileDepAverage() ) > 0.05); 
					bool isProfCandidTerminalAnchor = false;
					if( resObj->m_numOfItems < minSampleToContinueRecursive   ||  currentNumOfRecursiveLevels >= maxNumOfLevelsToGoRecursive)
					{
						isProfCandidTerminalAnchor = true;
					}
					bool isActualTerminal = isProfCandidTerminalAnchor;
					if( !isProfCandidTerminalAnchor)
					{
						double stretchRecursive = 0.0;//not used here


						bool* isPredictiveRecursiveUpdated = new bool[resObj->m_sizeOfItem];
						bool* isPredictiveOneLevelUseUpdated = new bool[resObj->m_sizeOfItem];


						//bool* updatedIsPRedictive = new bool[resObj->m_sizeOfItem];
						for(int e = 0 ; e < resObj->m_sizeOfItem ; e++)
						{
							isPredictiveRecursiveUpdated[e] = isPredictiveRecursive[e]; 
						}
						isPredictiveRecursiveUpdated[v] = false;


						for(int e = 0 ; e < resObj->m_sizeOfItem ; e++)
						{
							isPredictiveOneLevelUseUpdated[e] = isPredictiveRecursiveUpdated[e]; 
						}
						int cap = globals->g_capOfForkingPredictiveRecursive;
						if(currentNumOfRecursiveLevels >=  globals->g_highestRecurSiveLevelWithFork)// 3)  6 23 23 *** added this confoig instead of hard coded
						{
							cap = 1;//6 23 23 ** check
						}
						cout<<12345655555;
						cout<<"\n";
						resObj->CapIsPredictiveOptionsPerStretch(isPredictiveOneLevelUseUpdated, cap, depAnchorUniv);
						
						double* depBucketAnchorArrr = new double[numOfCalibrationGrps];
						int* depBucketSmpleArrr = new int[numOfCalibrationGrps];
						cProfileObject** tempLocalList = new cProfileObject*[1000];
						int tempoMovingIndex = 0;
					
						bool isSuccess = RecursiveProfileBuild( 
							tempLocalList, tempoMovingIndex /* movingIndexPervalue*/, depBucketAnchorArrr,depBucketSmpleArrr ,   stretchRecursive, 
								maxNumOfProfes, numOfCalibrationGrps, resObj, isPredictiveRecursiveUpdated,isPredictiveOneLevelUseUpdated,
								globals,  depAnchorUniv, 
								anchorProfileCandidate,  schemaArr , minSampleToContinueRecursive, currentNumOfRecursiveLevels +1,
								maxNumOfLevelsToGoRecursive,
								rootOddPredictiveModel,  regPredictiveModell,		inclusionDataSetLocal, isThisCaseOfAnchorUniverseIn);
						cout<<1234566666666666;
						cout<<"\n";
						//take tempLocalList, tempoMovingIndex , use that for a predicive echeck with every person in the resObj num of iterms above.
						//if ia person is using profiles and their children perhaps better get all pop gathers under bottom up gruops and get up to crete 
						//a better calibration. for phase 1 start wtih calibration all profiles below in tempLocalList to improved
						//depBucketAnchorArrr,depBucketSmpleArrr and stretch. stretch can make a decision about how string is thisi going down was.
						//when doing this better a person for test usine a mutually exclusive profile from one lvel fown and anothe person from another ersion
						//of one levrl ldowno, the pariente converts their prediction in to the profile parient language.if one person hits a profiel
						//two level dow, a termirnal, low, and in between tehre is only grand paarients, still  can try or make two step calibration


						if(currentNumOfRecursiveLevels==0  && v==0 && vl==0)
						{
							int sdvg=0;//check why below recusrive did not retur any profile set. 
						}
						if(!isSuccess)
						{
							int sdg=0;
						}
							
						if(isSuccess  &&( (stretchRecursive > anchorPrStretchh) || ( resObj->m_numOfItems > globals->g_sizeAndUpToKeepREcursive)))
						{
							movingIndexPervalue=  tempoMovingIndex;
							isActualTerminal = false;
							for(int u = 0 ; u < numOfCalibrationGrps ; u++)
							{
								depArrValues[vl][u] = depBucketAnchorArrr[u];
								depArrValueCnt[vl][u] = depBucketSmpleArrr[u];
							}
							for(int d=0 ; d< movingIndexPervalue ; d++)
							{
								profListPerVal[d] =  tempLocalList[d];
							}
						}
						else
						{
							isActualTerminal = true;
						}
						//6 23 23 **** check do we not need to delete all profiles tempoMovingIndex number since choose to not use these porifels?
						// so if we do use recursive we copy the tempLocalList to profile list , and we delete anchorProfileCandidate and if this is 
						//a terminal than we keep anchorProfileCandidate and delete this list
						delete []tempLocalList;
						tempLocalList=NULL;
							
						delete []depBucketAnchorArrr;
						depBucketAnchorArrr=NULL;
						delete []depBucketSmpleArrr;
						depBucketSmpleArrr=NULL;
							
						delete[]isPredictiveRecursiveUpdated;
						isPredictiveRecursiveUpdated=NULL;
						delete []isPredictiveOneLevelUseUpdated;
						isPredictiveOneLevelUseUpdated=NULL;
					}
					if(isActualTerminal)
					{
						profListPerVal[0] = anchorProfileCandidate;
						movingIndexPervalue = 1;
								//isActualTerminal = true;//even that it was not stoped by stop rule, the perf does not justify a recursive
								//and this will be a termina.
					}
					else
					{
						if(movingIndexPervalue == 0)
						{
							int sdg=0;//should not be here
						}
	//7 6 23 try adding that anchor befoe or after the list camem from below recursive call . it than has another signature c are for parent removal
						//if(true) 
						//      profListPerVal[movingIndexPervalue++] = anchorProfileCandidate;
						delete anchorProfileCandidate;//since this proifles ended up being an intesection profile that should
						anchorProfileCandidate=NULL;
							//not interfer in the prediction process since its children were selected to replace this event
					}
					//end of "elese"  when such profile inlsuion rule was not yet
					int addedRuleIndex = -1;
					inclusionDataSetLocal->AddNewRule(addedRuleIndex, newInclusionArr , numOfNewIncusionRules);
					inclusionDataSetLocal->UpdateRuleDeparrays(addedRuleIndex,  depArrValues[vl], 	depArrValueCnt[vl], numOfCalibrationGrps);
					inclusionDataSetLocal->UpdateRuleProfileSet(addedRuleIndex, profListPerVal, movingIndexPervalue);

						////6 23 23 ****	inclusionDataSet update profiels profListPerVal and movingIndexPervalue size into the 	inclusionDataSet
						//             and then back when recall a repeated case so it can participate when a var seleced. under samem signature
						//find solution for deletion fo profils when are shared
			
					
				}
					
				delete []newInclusionArr;
				newInclusionArr=NULL;
				delete []isPersonIn;
				isPersonIn=NULL;
				delete resObj;
				resObj=NULL;
				int gap = movingProfInxx[v];
				for(int z = 0 ;z < movingIndexPervalue ; z++)
				{
					profListPerVal[z]->IncrementPrfieIDandAnchorID(gap);//6 23 23 += gap for profile id and ahchor id in profile list per val [z]
					threeDimProff[v][movingProfInxx[v]++]= profListPerVal[z];
				}	
				delete []profListPerVal;
				profListPerVal=NULL;


			}
			//when i come here i have set of  threeDimProff movingProfInxx[indexOfNextVar ] nuber of them tht were ollected in either below fucntions
			//or that athis is a 1 termina that coers indexOfNextVar proifle as last rule and no more. eitiher way that profiel or list of proiefs can set 
			//a test with the population under researchDataObj num of items and replace the  depArrTdim[v] , depArrTdimCnt[v] and stretch
			//and get up better 
			if(false)
			{
				MergerTwoDimDepArraysToOneDim(depArrTdim[v] , depArrTdimCnt[v], 
												depArrValues, depArrValueCnt , numOfValues,numOfCalibrationGrps);
			}
			//else  //6 23 23 change to else and remove the aboe true
			{
				//profile list : threeDimProff[indexOfNextVar ] , num of prfiles:  movingProfInxx[indexOfNextVar ], 
				int modePRed=0.0;
				bool* isPersonIn = NULL;
				double* threshArr = new double[numOfCalibrationGrps];
				double* avgDepArr = new double[numOfCalibrationGrps];
				int* cntArr = new int[numOfCalibrationGrps];
				int* grpIndexArrr = NULL;//new int[rschDataAnchor->m_numOfItems];
				double* sumadvancedPErf=NULL;
				int isWithExtremeDimension = false;
				double* predArr = new double[researchDataObj->m_numOfItems];
				double* centerPredArr = new double[researchDataObj->m_numOfItems];
				//	 modePRed -> with extreme based on uninvese (2), with exteme based on person anchor(1), stratig (0)
				//7 6 23 add a cleanup of parents from threeDimProff to only consider profiles that do not have any child. that is meant to be done inslude DFGHJ
				bool isWithFineTuning=true;


				DFGHJ( threshArr ,   avgDepArr ,  cntArr,	 predArr,centerPredArr, grpIndexArrr,sumadvancedPErf,
						isPersonIn,	researchDataObj,  globals,  numOfCalibrationGrps,
								 threeDimProff[v ],   movingProfInxx[v ], modePRed,   isWithExtremeDimension,
								 isThisCaseOfAnchorUniverseIn  , isWithFineTuning, isWithMinAdvancedPerfWeight);
				
				
				for(int j = 0 ; j < numOfCalibrationGrps ; j++)
				{
					depArrTdim[v][j]= avgDepArr[j];
					depArrTdimCnt[v][j]= cntArr[j];
				}

				delete[]avgDepArr;
				delete []cntArr;
				delete []centerPredArr;
				delete [] predArr;
				delete[]threshArr;
				threshArr=NULL;
			
			}
			double stretch = StretchLoop(depArrTdim[v] , depArrTdimCnt[v],    numOfCalibrationGrps ,  depAnchorUniv);
			strechArray[v] = stretch;

				
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				delete []depArrValues[vl] ;
				delete []depArrValueCnt[vl];
			}
			delete []depArrValues;
			depArrValues=NULL;
			delete []depArrValueCnt;
			depArrValueCnt=NULL;
		}
	}
	if(strechArray == NULL)
	{
		int asccf=0;
	}
	int cntMissed = 0; 
	int cntAll=0;
	for(int v = 0 ; v < numOfVars   ; v++)
	{
		if(isPredictiveOneLevelUse[v])
		{
			double percMissed = 0.0;
			int valOptioms = varValOptions[v];
			for(int vl = 0 ; vl < valOptioms ; vl++)
			{
				if(varValCnt[v][vl] < globals->g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE)
				{
					percMissed += (double(varValCnt[v][vl] )) / ( double( researchDataObj->m_numOfItems));
				}
			}
			if(percMissed > 0.03 )
			{//7  6 23 adding the bottom line of all this stoppiong uupgrade   
				//strechArray[v] /= 100.0; //lower the change we choose it
				cntMissed++;
			}
			cntAll++;
		}
			//varValCnt = new double*[numOfVars]; 
//	double* varValOptions

	}
	if(cntMissed == cntAll)
	{
		ret = false;
	}

	if(varValCnt)
	{
		for(int v = 0 ; v< numOfVars ; v++)
		{
			if( varValCnt[v] != NULL)
			{
				delete []varValCnt[v];
			}
		}
		delete []varValCnt;
		varValCnt=NULL;
	}
	if(varValOptions != NULL)
	{
		delete []varValOptions;
		varValOptions=NULL;
	}
				//varValCnt


	for(int v = 0 ; v < numOfVars   ; v++)
	{
		if(currentNumOfRecursiveLevels ==1)
		{
			int sdf=0;
		}
		if(currentNumOfRecursiveLevels ==2)
		{
			int sdf=0;
		}
		if(strechArray[v] > maxStretch)
		{
			maxStretch = strechArray[v];
			indexOfNextVar = v;
		}
	}
	delete []strechArray;
	strechArray=NULL;

	stretchOutt = maxStretch;

	if(indexOfNextVar>=0)
	{
		for(int x = 0 ; x< numOfCalibrationGrps ; x++)
		{
			bucketArrOut[x] = depArrTdim[indexOfNextVar][x];
			bucketCntArrOut[x] = depArrTdimCnt[indexOfNextVar][x];
		}	
	}



	//inclusionDataSetLocal threeDimProff  6 23 23 ****
	//firsrt remvoe inclusionDataSetLocal get back to the univrs strucure
	//before copy from threeDimProff to profileListt check if any  appearance of threeDimProff [indexOfNextVar ] is in inclusionDataSetLocal than NULL it.
	// so it wont get deleted if plan to delete as part of the  inclusionDataSetLocal destructor. 
	//or i can use a univer inclusionDataSetLocal and not local, and delete the threeDimProff that are   not indexOfNextVar and not shared with indexOfNextVar.
	//to know which one is shared i need to just check wtih  threeDimProff and not use inclusionDataSetLocal for delete profiles

	
		//copy this array of proifles from recursive best variable and do not delete these profiles, just the others varibales failed to win
	int gap = movingPrIndexx;
	if(gap>0)
	{
		int sdgsg=0;
	}
	

	////6 23 23 **** here addd a loop to go over threeDimProff[] of the 26 numOfVars and for each over its profiels accoridng to movingProfInxx[]
	//           number of profeils and check which from all the non winning varibles profiles are shred wtih the winning. if any is shared, 
		//       NULL it here before the delete
	
	if(indexOfNextVar >=0)
	{
		for(int o = 0 ; o < movingProfInxx[indexOfNextVar ] ; o++)
		{
			if(threeDimProff [indexOfNextVar ] == NULL)
			{
				int sdgg=0;
			}
			threeDimProff [indexOfNextVar ][o]->IncrementPrfieIDandAnchorID(gap);
			profileListt[movingPrIndexx++] = threeDimProff [indexOfNextVar ][o];
		//	threeDimProff [indexOfNextVar ][o]=NULL;//so it does get deleted in the below loop
		}
	}
	
	if(false)
	{
		if(threeDimProff != NULL)
		{	
			for(int v  = 0 ; v< numOfVars ; v++)
			{
				//if(v != indexOfNextVar 
				if( threeDimProff[v]!=NULL)
				{
					for(int p = 0 ; p < movingProfInxx[v] ; p++)
					{
						if(threeDimProff[v][p] != NULL)
						{
							bool profileSharedWithWinningVarList = IsProfileFoundInList(  threeDimProff[v][p],  threeDimProff[indexOfNextVar], movingProfInxx[indexOfNextVar]);
							if(profileSharedWithWinningVarList && (v != indexOfNextVar) )
							{
								int sdgg = 0 ; 
							}
							if( (v == indexOfNextVar)  ||  profileSharedWithWinningVarList )
							{
								threeDimProff[v][p] = NULL;//so it does not get deleted like all ohter proifles in indexOfNextVar. 
							}
							else
							{
								delete threeDimProff[v][p];
								threeDimProff[v][p]=NULL;
							}
						}
					}
					if(v != indexOfNextVar) //i need that one to stay alive to be checkd in the loop foro shared. will than delet the array after
					{
						delete[] threeDimProff[v];
						threeDimProff[v]=NULL;
					}
				}
			}
			delete[] threeDimProff[indexOfNextVar ];
			threeDimProff[indexOfNextVar ]=NULL;

			delete []threeDimProff;
			threeDimProff=NULL;
			delete[]movingProfInxx;
			movingProfInxx=NULL;
		}
	}
	
	 //6 23 23  ** get it back to not be here but from the caller function, fo now just testing
	//delete inclusionDataSetLocal;
//	inclusionDataSetLocal=NULL;
	//6 23 23 first focus on getting back the universal data rule struc and then the deletion of movingProfInxx to understand the bug. then i can grow to larager
	//than 100,000 input data 
	 
	for(int v = 0 ; v < numOfVars ; v++)
	{
		delete[]depArrTdim[v] ;
		delete[]depArrTdimCnt[v] ;
	}
	delete[]depArrTdim;
	depArrTdim=NULL;
	delete[]depArrTdimCnt;
	depArrTdimCnt=NULL;

	return ret;
}

bool cResearchObject::IsProfileFoundInList( cProfileObject* prof,  cProfileObject** list,int size)
{
	for(int i = 0 ; i < size ; i++)
	{
		if(prof == list[i])
		{
			return true;
		}
	}
	return false;
}
			

int cResearchObject::FindBestNextVar( cResearchDataObj* researchDataObj, 
	   bool* isPredictive, cGlobals* globals,   double depAnchorUniv)
{
	

	int numOfVariables = researchDataObj->m_sizeOfItem;
	int bestVarIndex = -1;
	double bestStretch = 0.0;
	for(int v=0; v< numOfVariables; v++)
	{

		if(m_schemaArrr->m_schemaArr[v]->m_isPredictiveVariable)
		{
			int numOfValues = m_schemaArrr->m_schemaArr[v]->m_numberOfValues;
			double* depAvgArr = new double[numOfValues];
			int* sampleArr = new int[numOfValues];
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				double val =  m_schemaArrr->m_schemaArr[v]->m_varValues[vl];
				int sample = 0;
				double depAvg = 0.0;
				CollectSampleAndDepAverage(depAvgArr[vl], sampleArr[vl], researchDataObj, v, val);
			}

			int sizeThres = globals->g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE;

			int highestSample = 0;
			int populationThatReachDE = 0;
			int allSample = 0;
			for(int vl = 0 ; vl < numOfValues; vl++)
			{
				if(sampleArr[vl] < sizeThres)
				{
					populationThatReachDE += sampleArr[vl];
				}
				allSample += sampleArr[vl];
				highestSample = cVarianceCalc::Max(highestSample , sampleArr[vl]);
			}
			double ratioDE = double(populationThatReachDE) / double(allSample);
			if(ratioDE < 0.02) //then only contiue check for odd
			{
				if(/*highestSample*/ researchDataObj->m_numOfItems > globals->g_sizeAndUpToKeepREcursive)//both 0.02 and 60000 need to be config, 60000 is a value that is good for the loop
				{
					//if(
					//double avgStretch = CalculateStreth( avgDepArr,  cntArr, depVal,  numOfGrps);
					double depVal = 0.0;
					double stretch = cResearchObject::CalculateStreth(depVal, depAvgArr,  sampleArr, numOfValues);
				//test want to do is whether 
					//double stretch = cResearchObject::CalculateStreth( depAvgArr,  sampleArr, depAnchorUniv, numOfValues);
					
					if(stretch > bestStretch )
					{
						bestStretch = stretch;
						bestVarIndex = v;
					}
				}
				else
				{
					int sdg =0;
				
				}

			}
			delete[] depAvgArr;
			depAvgArr=NULL;
			delete[] sampleArr;
			sampleArr=NULL;
		}

	}
	return bestVarIndex;
}

void cResearchObject::CollectSampleAndDepAverage(double &depAvg, int &sample, cResearchDataObj* researchDataObj, int var, double val)
{
	sample=0;
	depAvg=0.0;
	for(int i = 0 ; i < researchDataObj->m_numOfItems ; i++)
	{
		if(researchDataObj->m_twoDimArray[i][var] == val)
		{
			depAvg += researchDataObj->m_depArr[i];
			sample++;
		}
	}
	if(sample>0)
	{
		depAvg /= sample;
	}
}


//4 17 22 TO DO Debug - see if anything m issing for developmoent of phase one with only root profile need to be ready
//add isTerminal to the logic
void cResearchObject::BuildResearchElements( cResearchDataObj* researchDataObjj, bool* isTerminalProfileArrr,
	InputVariablesPackageForResearchObj* inputVarObj ,  cGlobals &globals)
{
	 

	cPercentileCalculationModel* rootOddPredictiveModel=NULL; 
	cPercentileCalculationModel* regPredictiveModell=NULL;

	m_profileListSize=0;

	cVariableAndValueAndPoints* inclusionSet = NULL;//root has emeplty rule set
	int inclusionRuleSize=0;//sending NULL in the third paramater instead of pointer to root profile, to mark that this is root

	m_rootProfile = new cProfileObject(
			this, m_profileListSize,NULL,inclusionSet,inclusionRuleSize, researchDataObjj,m_profileListSize, NULL); 
//root, and anchors, get their anchor ID to be its own profile, so any performance test will be meassured against the profile mean

	PRepareModelAndAdjustPErRootRegreMOdel(rootOddPredictiveModel, regPredictiveModell,m_rootProfile ,  globals );

	m_rootProfile->SetPerformanceToDefault( globals );//11 28 22 most importaht start from what is performacne adn what is its nutural value for a default

	//7 2 23 added from below 6 23 23 *
	m_rootProfile->SetInterventionMembers(inputVarObj->m_isIntervention, 
			inputVarObj->m_indexOfPropIntervention,     researchDataObjj->m_sizeOfItem);
	
	//then decide if root needs or  need not a performance score . it is anot if it is the definitino of nutural, but not sure
	//m_rootProfile->DeleteIsInProfile();
	
	int numOfVariables = researchDataObjj->m_sizeOfItem;
	bool* isPredictive = new bool[numOfVariables];
	for(int v=0; v< numOfVariables; v++)
	{
		isPredictive[v]=false;
		if(m_schemaArrr->m_schemaArr[v]->m_isPredictiveVariable)
		{
			isPredictive[v]=true;
		}
	}

	if(true)
	{
		TemporaryREcursiveCall2(  researchDataObjj ,m_rootProfile,isPredictive,  &globals,m_schemaArrr, rootOddPredictiveModel,  regPredictiveModell, inputVarObj);
		int enddd =0;
	}
	else
	{
	/////////////////////

		m_profileObjectPtrList[m_profileListSize++]=m_rootProfile;
	//	m_rootProfile->SetInterventionMembers(inputVarObj->m_isIntervention, 
	//		inputVarObj->m_indexOfPropIntervention,     researchDataObj->m_sizeOfItem);
		int numberOfPatients = researchDataObjj->m_numOfItems;

		bool isWithCalibration = false;
		bool isAdvancedPerfGetbEstMatch = false;//at this point i dont have any referecn predictions for an advanced performance so sending simple.
		isAdvancedPerfGetbEstMatch = globals.g_IS_ADVANCED_PERF_FOR_GET_BEST_MATCH_EVOLUTION;

 		int maxNumberOfProfiles = 100000;
	//	double depAnchor  =0.0;
	//	double depAnchorIn  =0.0;
		double depAnchorUniv =  m_rootProfile->GetProfileDepAverage();
		int bestVarIndex = FindBestNextVar( researchDataObjj, isPredictive,&globals, depAnchorUniv);
	//	6 13 23 22 
		//bestVarIndex = FindBestNextVarWithPerformCompare(researchDataObj,
	//	        isPredictive, globals,   numOfGrps, m_rootProfile)
 
		if(bestVarIndex >=0)
		{
			for(int vl = 0 ; vl < m_schemaArrr->m_schemaArr[bestVarIndex]->m_numberOfValues ; vl++)
			{
				cVariableAndValueAndPoints* inclusionArrCAller = NULL; //since this is root
				int inclusionArrayCallerSize = 0;//0 since this is root 
				int nextVarIndex = bestVarIndex;
				double varVal = m_schemaArrr->m_schemaArr[bestVarIndex]->m_varValues[vl];
				bool* isIn = new bool[numberOfPatients];
				for(int i = 0 ; i < numberOfPatients ; i++)
				{
					isIn[i]=false;
					if(researchDataObjj->m_twoDimArray[i][bestVarIndex]==varVal )
					{
						isIn[i]=true;
					}
				}
				cResearchDataObj* resObj = new cResearchDataObj(researchDataObjj , isIn);
			//	cProfileObject** profilePtrArr = new  cProfileObject*[maxNumberOfProfiles];
				int movingProfleIndex=0;
				RecursiveEvolution(	 //profilePtrArr, movingProfleIndex, 
					maxNumberOfProfiles, inclusionArrCAller ,  inclusionArrayCallerSize , bestVarIndex,varVal,
						 resObj, isPredictive , &globals,	
						 rootOddPredictiveModel,  regPredictiveModell, inputVarObj,  depAnchorUniv);
				delete resObj;
				delete []isIn;
			}
		}
		else
		{
			int sdg =0;
		}

	}
	//	anchor->DeleteIsInProfile();


	cout<< "after build loops \n";

 
	if(rootOddPredictiveModel != NULL)
	{
		delete rootOddPredictiveModel;
		rootOddPredictiveModel=NULL;
	}
	if(regPredictiveModell != NULL)
	{
		delete regPredictiveModell;
		regPredictiveModell=NULL;
	}

	delete []isPredictive;
	isPredictive=NULL;

}

void cResearchObject::RecursiveEvolution(
	//cProfileObject** profilePtrArr, int &movingProfleIndex, 
	int maxNumOfProfiles,
	cVariableAndValueAndPoints*   inclusionArrCaller , int sizeOfInclusArrCaller , int thisNewVar, double newVarVal,
						cResearchDataObj* resObj , bool* isPredictive, cGlobals* globals,
				cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel*  regPredictiveModell,
				InputVariablesPackageForResearchObj* inputVarObj, double depAnchorUniv		)
{
	//prepare the incusion array for this intermidiate step.
	//this could be used as an input to the call to the same recursive function as  the caller incusion array 
	//or used to open an anchor in a terminal case
	int sizeOfInclusionSet = sizeOfInclusArrCaller+1;
	cVariableAndValueAndPoints* inclusionSet = new cVariableAndValueAndPoints[sizeOfInclusionSet];
	for(int i = 0 ; i < sizeOfInclusArrCaller ; i++)
	{
		inclusionSet[i] = inclusionArrCaller[i];
	}
	inclusionSet[sizeOfInclusArrCaller].m_variableIndex = thisNewVar;
	inclusionSet[sizeOfInclusArrCaller].m_value = newVarVal;
	inclusionSet[sizeOfInclusArrCaller].m_points=0.0;//6 13 23 see how to use the odd each step aadded by a new inclusion obj
 // m_rootProfile->GetProfileDepAverage()
	int bestVarIndex = FindBestNextVar(resObj, isPredictive,globals,  depAnchorUniv);
	//cProfileObject* potentialAnchor =  new cProfileObject( ()// a nd delete if not found as positive index
	//bestVarIndex = FindBestNextVarWithPerformCompare(resObj,
//	        isPredictive, globals,   numOfGrps,  potentialAnchor)
	
	
	if(bestVarIndex < 0)//one of the conditions we triggered to now allow further recursive calls, this is the last one
	{
		int profileID = m_profileListSize ;
		cProfileObject* anchor = new cProfileObject( 	this, profileID,m_rootProfile,
							inclusionSet,sizeOfInclusionSet, resObj,profileID, NULL);// profile ID here also the anchor ID -this is the anchor
		PRepareModelAndAdjustPErRootRegreMOdel(rootOddPredictiveModel, regPredictiveModell,anchor ,  *globals );
		//6 13 23 think khow to keep the is in health when sneding on
		anchor ->SetPerformanceToDefault( *globals );
		anchor->SetInterventionMembers(inputVarObj->m_isIntervention, 
				inputVarObj->m_indexOfPropIntervention,     resObj->m_sizeOfItem);
		if(anchor->GetProfilePopulationSize() < globals->g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE )
		{
			delete anchor;//this should happen only less than for 2% of the population by defintion of how selected the new variable
		}
		else
		{
			int leftRoomForProfiles = m_prifileListMaxSize - m_profileListSize;
			cProfileObject** profilePtrArr = new cProfileObject*[leftRoomForProfiles];//
			int movingProfleIndex=0;
			profilePtrArr[movingProfleIndex++] = anchor;
			int maxRuleLength = profilePtrArr[0]->GetInclusionRuleListSize()+globals->g_MAX_LEVELS_IN_PROFILING_EVOLUTION;
			BuildResearchElementsWhileLoop(	 profilePtrArr,movingProfleIndex,
					resObj,	 inputVarObj ,  *globals, globals->g_MAX_NUM_OF_ITERATIONS ,   leftRoomForProfiles, 
								anchor,	 rootOddPredictiveModel,  regPredictiveModell,  depAnchorUniv, maxRuleLength );
			int numPrflsAnchorAndDown = movingProfleIndex;
			bool isThisCaseOfAnchorUniverse99 = false;
			FillProfileListObjectsWothAdvancedPerformanceNew2(profilePtrArr,numPrflsAnchorAndDown, anchor,
				resObj,  globals, m_numberOfSubGrps,  depAnchorUniv, isThisCaseOfAnchorUniverse99);
			 
			for(int ii = 0 ; ii < numPrflsAnchorAndDown;ii++)
			{
				if(profilePtrArr[ii] != NULL)
				{
					if(m_profileListSize < m_prifileListMaxSize)
					{
						profilePtrArr[ii]->DeleteIsInProfile();
						m_profileObjectPtrList[m_profileListSize++] = profilePtrArr[ii];
					}
					else
					{
						delete  profilePtrArr[ii];
						profilePtrArr[ii]=NULL;
					}
				}
				else
				{
					int sdg = 0;//see that the performance function was able to delete profiles that are not effecitive
				}
			}
			delete []profilePtrArr;
			profilePtrArr=NULL;
		}
	}
	else //continue with recursive call
	{
		for(int vl = 0 ; vl < m_schemaArrr->m_schemaArr[bestVarIndex]->m_numberOfValues ; vl++)
		{
			double varVal = m_schemaArrr->m_schemaArr[bestVarIndex]->m_varValues[vl];
			bool* isIn = new bool[resObj->m_numOfItems];
			for(int i = 0 ; i < resObj->m_numOfItems ; i++)
			{
				isIn[i]=false;
				if(resObj->m_twoDimArray[i][bestVarIndex]== varVal)
				{
					isIn[i]=true;
				}
			}
			cResearchDataObj* resObjNext = new cResearchDataObj(resObj , isIn);
			//cProfileObject** profilePtrArr = new  cProfileObject*[maxNumOfProfiles];
 
			RecursiveEvolution(	 //profilePtrArr, movingProfleIndex, 
				maxNumOfProfiles,
							inclusionSet , sizeOfInclusionSet , bestVarIndex,varVal, 		 resObjNext, isPredictive,	
					 globals,	rootOddPredictiveModel,  regPredictiveModell, inputVarObj,depAnchorUniv );
			
			//delete []profilePtrArr;
			//profilePtrArr=NULL;
			delete resObjNext;
			resObjNext=NULL;
			delete []isIn;
			isIn=NULL;
		}
	}
	delete [] inclusionSet;
}




 //6 13 23 *** tuirn this to status and see if compiles
void cResearchObject::FillProfileListObjectsWothAdvancedPerformance(	cProfileObject** profileArr,
			int numberOfProfiles,cProfileObject* anchor, cResearchDataObj*   rschDataAnchor,
			cGlobals* globals, int numOfSubGrps)
{
	/*
	int personNum = 
	-grouop 1 - take all person set that meet a profile we meassure its value
	-group univer - alsoo take all the ones in anchor->IsInProfile()[i]
	-for the anchor gruop create prediction based on the anchor, perhaps with fine tuned appraoch, and get a number of buckets
	so that it will be at east 2% in performance . not easy to know h ow but start with 20 groups
	-for the gruop 1, copy the universe predidciton array and replace the is in proifle ones with the profsub or with the fine tuned
	version coming frmo the profile.
	-then count the plus or minus of stretch and add per prof sub in the profile advanced perormance 
		*/

	//int sizeOfAnchorPop = rschDataAnchor->m_numOfItems;
	double* sumPntsArr = new double[rschDataAnchor->m_numOfItems];
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems ; i++)
	{
		sumPntsArr[i] =  cProfileObject::CalclaterSumAdjusteddPnts(		rschDataAnchor->m_twoDimArray[i],
			rschDataAnchor->m_sizeOfItem, anchor->GetAdjustedOddRateArr(), anchor->GetOddRatioListSize());
	}

	int potenNumOfStretchGrps = anchor->GetNumberOfSubGroups();
	int minSizeBucket = 400;
	int bucketSize = rschDataAnchor->m_numOfItems / potenNumOfStretchGrps;
	int finalNumOfGrps = potenNumOfStretchGrps;
	if(bucketSize < minSizeBucket)
	{
		finalNumOfGrps = rschDataAnchor->m_numOfItems / minSizeBucket;
		finalNumOfGrps = cVarianceCalc::Max(finalNumOfGrps, 3);
	}

	double* predSet = new double[rschDataAnchor->m_numOfItems];
	int* grpIndexArr= new int[rschDataAnchor->m_numOfItems];
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems ; i++)
	{
		predSet[i]=0.0; 
		grpIndexArr[i]=-1;
	}
	//6 13 23 20 extract for ech prediciton of the prediciton set that pred group index it was part of out of finalNumOfGrps  options
	//int* indexArra = new int[rschDataAnchor->m_numOfItems];
	ConvertPointsToPredictions(predSet, grpIndexArr, finalNumOfGrps,  sumPntsArr, rschDataAnchor->m_depArr, NULL,
		rschDataAnchor->m_numOfItems, globals);


	double* threArr = new double[finalNumOfGrps];
	double* depAvgArr = new double[finalNumOfGrps];;
	int* subPopSize=new int[finalNumOfGrps];;
	double avgDep=0.0;
	
	double stretchScoreBase = ConvertPredictionsToDepAvgBucketsAndCalcStretch(
		threArr,  depAvgArr, subPopSize, avgDep,	predSet,rschDataAnchor->m_depArr,NULL,
									  rschDataAnchor->m_numOfItems,        finalNumOfGrps ,  globals, NULL);
	
	
	/*every person has apperance in certain number oof profiles , and can be then be seen nby isInProfSub()
	so i can then calcualte how the person gets prediction by any of these options and which was the best one. so if i 
	
	
	
	*/
	
	
	
	
	for(int p = 0 ; p < numberOfProfiles ; p++)
	{//6 13 23 call to FillIsInProfSub with isInAll input to get the isInProfile as output and send that one 5 times for the profsub
		bool* isInProff = new bool[rschDataAnchor->m_numOfItems];
		int sizeOfProff = FillIsInProfSub(isInProff,profileArr, p,-1,rschDataAnchor, NULL);//-1 to ask for full proifle
		
		for(int s = 0 ; s <  numOfSubGrps ; s++)
		{
			double profSubDepVal = profileArr[p]->GetSubGroupAverageDependentArr()[s];
			int profSubSample = profileArr[p]->GetSubBucketCntArr()[s];
			bool* isInProfSub = new bool[rschDataAnchor->m_numOfItems];
			int sizeOfProfSubPop = FillIsInProfSub(isInProfSub,profileArr, p,s,rschDataAnchor,isInProff);// isInAll);
			double* predSetLocal = new double[rschDataAnchor->m_numOfItems];
			int checkingCnt = 0;
			int numOfCasesWithSigChange = 0.0;
			double sigChange = 0.02;
			double avgGaps = 0.0;
		
			double avgSqrStretchBase = 0.0;
			double avgSqrStretchSub = 0.0;
			int sumCntSub = 0;

			double* movingArrPredBase = new double[rschDataAnchor->m_numOfItems];
			double* movingArrDep = new double[rschDataAnchor->m_numOfItems];
			int* movingIndexArr = new int[rschDataAnchor->m_numOfItems]; //grpIndexArr
			int movingIndex = 0;
			double avgAnchorDep =anchor->GetProfileDepAverage();
			for(int i = 0 ; i < rschDataAnchor->m_numOfItems ; i++)
			{
				
				predSetLocal[i] = predSet[i];
				if(isInProfSub[i] )
				{
					sumCntSub++;
					avgSqrStretchBase += (predSet[i]-avgAnchorDep )*(predSet[i]-avgAnchorDep );
					avgSqrStretchSub += (profSubDepVal-avgAnchorDep )*(profSubDepVal-avgAnchorDep );
					predSetLocal[i] = profSubDepVal;
					checkingCnt++;

					movingArrPredBase[movingIndex]= predSet[i];
					movingArrDep [movingIndex] = rschDataAnchor->m_depArr[i] ;
					movingIndexArr[movingIndex] = grpIndexArr[i];
					//6 13 23 20 add another moving index for the grp index value come for each anchor prediction
					movingIndex++;
				}
			}
			if(sumCntSub > 0)
			{
				avgSqrStretchBase /= sumCntSub;
				avgSqrStretchSub   /= sumCntSub;
			}

			//6 13 23 20 i can now group movingArrPredIndexBase using the index array indexArra and take the movingArrDep
			//to calcualte the stretch only on behalf the profsub people . and see how take this stretch to an alternative works



			
			double beefitPErPAtient = 0.0;
			double betweenValues = (avgSqrStretchSub + avgSqrStretchBase) / 2.0;
			if(avgSqrStretchBase > 0.0)
			{
				beefitPErPAtient=	(avgSqrStretchSub - avgSqrStretchBase) /  betweenValues ;
			}
			if(beefitPErPAtient > 0.0)
			{
				int sdg=0;
			}

			int numOfSubGrps= profileArr[p]->GetNumberOfSubGroups();
			int potentialSizeOfGrp = movingIndex / numOfSubGrps;
			if(potentialSizeOfGrp < globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE)
			{
				numOfSubGrps = movingIndex / globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE;
				numOfSubGrps = cVarianceCalc::Max(numOfSubGrps, 2);
				// explain about the '2' . Need to give the moving arr from the anchor model to vary at the m in,
				//up to the ogriginal anchor profile model (5) but not for sure ifi there is less ample we go for as low as 2
			}
			double* thrarr = new  double[numOfSubGrps];
			double* depavgArr= new  double[numOfSubGrps];
			cProfileObject::CalculateThresholds(thrarr,numOfSubGrps,movingArrPredBase,NULL,movingIndex);
			int* cntArrr = new int[numOfSubGrps];
			double depAvvvg=0.0;
			cProfileObject::CreateAvgDepSubGrps(NULL,depavgArr,thrarr,cntArrr,depAvvvg,numOfSubGrps,movingArrPredBase,
				                 movingArrDep, NULL,movingIndex,*globals);
			double avgSqrStretchAnchor = 0.0;
			double sumWeights = 0.0;
		//	double avgAnchorDep =anchor->GetProfileDepAverage();
			for(int x = 0 ; x< numOfSubGrps;x++)
			{
				double sqrESerror = (avgAnchorDep - depavgArr[x]) *  (avgAnchorDep - depavgArr[x])  ;
				double wgh = double(cntArrr[x]);
				avgSqrStretchAnchor+=  wgh*sqrESerror;
				sumWeights += wgh;
			}
			if(sumWeights>0.0)
			{
				avgSqrStretchAnchor /= sumWeights;
			}
			//avgSqrStretchAnchor /= numOfSubGrps;
			double sqrStretchSub = (profSubDepVal - avgAnchorDep)* (profSubDepVal - avgAnchorDep);
			double betweenStretchValues = (sqrStretchSub +   avgSqrStretchAnchor)/2.0;
			beefitPErPAtient = 0.0;

			double proxiVarAnchor = avgAnchorDep *(1.0-avgAnchorDep);
			if(betweenStretchValues > 0.0)
			{
				beefitPErPAtient = 	(sqrStretchSub -   avgSqrStretchAnchor)/proxiVarAnchor  ;
			}
			profileArr[p]->GetSubGrpPerformanceAdvancedArray()[s]= beefitPErPAtient;
		
			
			delete[]thrarr;
			delete []depavgArr;
			delete[]cntArrr;

			delete []movingArrPredBase;
			movingArrPredBase=NULL;
			delete[]movingArrDep;
			movingArrDep=NULL;
	
			delete []	movingIndexArr;
			movingIndexArr=NULL;
			delete []predSetLocal;
			delete []isInProfSub;
		//	delete []threArrProfSub ;
		//	delete [] depAvgArrProfSub;
		//	delete []subPopSizeProfSub;
		
		}
		double weightedAvgPErfAdvanstage = 0.0;
		double sumWeights = 0.0;
		for(int s = 0 ; s < numOfSubGrps ; s++)
		{
		//	double profSubDepVal = profileArr[p]->GetSubGroupAverageDependentArr()[s];
			int profSubSample = profileArr[p]->GetSubBucketCntArr()[s];
			double perfAdvanced = profileArr[p]->GetSubGrpPerformanceAdvancedArray()[s];
			weightedAvgPErfAdvanstage += (double(profSubSample) ) * perfAdvanced;
			sumWeights +=  (double(profSubSample) );
		}
		weightedAvgPErfAdvanstage  /= sumWeights;
		for(int s = 0 ; s < numOfSubGrps ; s++)
		{
			double perfAdvanced = profileArr[p]->GetSubGrpPerformanceAdvancedArray()[s];
			int profSubSample = profileArr[p]->GetSubBucketCntArr()[s];
			if(profSubSample < globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE)
			{
				int gap =  globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE - profSubSample;
				double wghSub = (double(profSubSample)) /  globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE;
				double wghOther = 1.0 - wghSub;
				perfAdvanced = wghSub * perfAdvanced + wghOther * weightedAvgPErfAdvanstage;
				profileArr[p]->GetSubGrpPerformanceAdvancedArray()[s] = perfAdvanced;
			}
			double tempVal = profileArr[p]->GetSubGrpPerformanceAdvancedArray()[s];
		//	tempVal *= 10000;//get less zeros trailed
			tempVal = cVarianceCalc::Max( tempVal ,  0.00001);
			profileArr[p]->GetSubGrpPerformanceAdvancedArray()[s] = tempVal;
		}
		delete []isInProff;
		isInProff=NULL;
		///delete profData;
		//profData=NULL;
	}

	delete []grpIndexArr;
	grpIndexArr=NULL;
	delete []predSet; 
	delete  []sumPntsArr;
	delete [] threArr ;
	delete[] depAvgArr;
	delete [] subPopSize;
}
	


double cResearchObject::PreictionAndStretch(
	double* depAvgArr ,	int* subPopSize,double &avgDep,
	
	double* predSet, int* grpIndexArr,cProfileObject* anchor, cResearchDataObj* rschDataAnchor,
	cGlobals* globals, int numOfStretchGrps  , double depAnchorUniv)
{	 

	//double* predSet = new double[rschDataAnchor->m_numOfItems];
//	int* grpIndexArr= new int[rschDataAnchor->m_numOfItems];
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems ; i++)
	{
		predSet[i]=0.0; 
		grpIndexArr[i]=-1;
		
		double predictionWithInterv=0.0;
		double preditionWitoutInterv=0.0;
		double performanceReg=0.0;
		double performanceAdv=0.0;	
		int profileID=-1;
		bool isWithFineTuning=false;//7 11 23 
		bool isAdvancedPerfGetbEstMatch=true;
		
		anchor->PredictionElementsNEW( predSet[i] , predictionWithInterv, preditionWitoutInterv,
			performanceReg , performanceAdv, profileID,  grpIndexArr[i],	rschDataAnchor->m_twoDimArray[i] ,
			rschDataAnchor->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
	}
//	double* depAvgArr = new double[numOfStretchGrps];
//	int* subPopSize=new int[numOfStretchGrps];
	//double avgDep=0.0;
	avgDep=0.0;
	for(int x = 0 ; x <numOfStretchGrps ; x++)
	{

		depAvgArr[x] = 0.0;
		subPopSize[x]=0;
	}
	
	 
	int countForAllIn=0;
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems ; i++)
	{
		if(grpIndexArr[i] >=0)
		{
			depAvgArr[grpIndexArr[i]] += rschDataAnchor->m_depArr[i];
			subPopSize[grpIndexArr[i]]++;
			avgDep += rschDataAnchor->m_depArr[i];
			countForAllIn++;
		}
	}
	avgDep/=countForAllIn;
	
	for(int x = 0 ; x <numOfStretchGrps ; x++)
	{
		if(subPopSize[x] > 0)
		{
			depAvgArr[x] /= subPopSize[x] ;
		}		 
	}
 
//	double anchorvAlue = anchor->GetProfileDepAverage();
	double strertchTestBase = 0.0;
	double sumWghts = 0.0;
	for(int z = 0 ; z < numOfStretchGrps ; z++)
	{
		double gap = depAvgArr[z] - depAnchorUniv;
		strertchTestBase += gap * gap* subPopSize[z];
		sumWghts += double(subPopSize[z]);
	}
	strertchTestBase /= sumWghts;

	return strertchTestBase;


}

 

 double cResearchObject::StretchCalculation(double* thredArrOut,double* predArr , cResearchDataObj*  rschData, double  anchorvAluee,
	  cGlobals* globals, 		  int modePRed, int numOfPerformanceSubGrps,double* thredArrIn)
 {
	 double temp = StretchCalculation(thredArrOut, predArr , rschData->m_depArr,  rschData->m_numOfItems,   anchorvAluee,
					  globals, 		   modePRed,  numOfPerformanceSubGrps ,thredArrIn);
	//double  fake =   StretchCalculation(thredArrOut, predArr , rschData->m_depArr,  rschData->m_numOfItems,   anchorvAluee,
			//		  globals, 		   modePRed,  numOfPerformanceSubGrps ,thredArrIn);

	return temp;
 }

 double cResearchObject::StretchLoop(double* avgDepArr,  int* cntArr,    int numOfPerformanceSubGrps , double anchorvAluee)
 {
	double sumWghts=0.0;
	double strertchFullTest = 0.0;
	double prevVal = 0.0;
	for(int z = 0 ; z < numOfPerformanceSubGrps ; z++)
	{
		//avgDepArr[z] = cVarianceCalc::Max(prevVal , avgDepArr[z]);//7 28 23 deleted two lines
		//prevVal = avgDepArr[z];

		double gap = avgDepArr[z] - anchorvAluee;//333 b depAnchorUniv;
		gap	 *= gap;
		strertchFullTest += gap * (double(cntArr[z]));
		sumWghts += double(cntArr[z]);
	}
	strertchFullTest /= sumWghts;
	return strertchFullTest;
 }

 double cResearchObject::StretchCalculation(double* thredArrOut, double* predArr , double* depArr, int numOfItems, double  anchorvAluee,
	  cGlobals* globals, 		  int modePRed, int numOfPerformanceSubGrps,double* thredArrIn)
 {
 
	double* threshArr = new double[numOfPerformanceSubGrps];
	if(thredArrIn != NULL)
	{
		for( int x = 0 ; x < numOfPerformanceSubGrps; x++)
		{
			threshArr[x] = thredArrIn[x];
		}
	}
	else
	{
		cProfileObject::CalculateThresholds(threshArr , numOfPerformanceSubGrps, 
										predArr,NULL,numOfItems);
	}

	if(thredArrOut != NULL)
	{
		for( int x = 0 ; x < numOfPerformanceSubGrps; x++)
		{
			thredArrOut[x] = threshArr[x];
		}
	}

	double* avgDepArr = new double[numOfPerformanceSubGrps];
	int* cntArr = new int[numOfPerformanceSubGrps];
	double depAvg = 0.0;
	cProfileObject::CreateAvgDepSubGrps(NULL, avgDepArr,threshArr ,cntArr, depAvg,
					numOfPerformanceSubGrps,predArr,depArr, NULL, numOfItems, *globals);

	double strertchFullTest = StretchLoop(avgDepArr,   cntArr,    numOfPerformanceSubGrps ,  anchorvAluee);
  
	/*
		cProfileObject::CalculateThresholds(threshArr , numOfPerformanceSubGrps, 
										predArr,NULL,numOfItems);
	
		cProfileObject::CreateAvgDepSubGrps(NULL, avgDepArr,threshArr ,cntArr, depAvg,
					numOfPerformanceSubGrps,predArr,depArr, NULL, numOfItems, *globals);

	
	
	
	double sumWghts=0.0;
	double strertchFullTest = 0.0;
	double prevVal = 0.0;
	for(int z = 0 ; z < numOfPerformanceSubGrps ; z++)
	{
		avgDepArr[z] = cVarianceCalc::Max(prevVal , avgDepArr[z]);
		prevVal = avgDepArr[z];

		double gap = avgDepArr[z] - anchorvAluee;//333 b depAnchorUniv;
		gap	 *= gap;
		strertchFullTest += gap * (double(cntArr[z]));
		sumWghts += double(cntArr[z]);
	}
	strertchFullTest /= sumWghts;*/

 
	delete []threshArr;
	delete []avgDepArr;
	delete []cntArr;


	return strertchFullTest;
 }










double cResearchObject::ProfileAddingTest(double* depAvgArrrOut,  int* cntAvgArrOut,double* thredArrOut, double* predArr, double* centerPredArr, double* sumAdvancedPErfWghts,
	cProfileObject** profArr ,int numOfProfiles,
	      cResearchDataObj*   rschDataAnchor, double anchorvAlueee, cGlobals* globals, 
		  int modePRed, int numOfPerformanceSubGrps , double*  tierStrucrue, int numOfTiers, 
		  bool  isWithExtremeDimension, bool isThisCaseOfAnchorUniverseIn ,  bool isWithFineTuning)

{

	//int numOfPRefGrpssEnd = globals->g_NUMBER_OF_CALIBRATION_GRPS;
	bool* isPersonIn = NULL;
	double* threshArr = new double[numOfPerformanceSubGrps];
	double* avgDepArr = new double[numOfPerformanceSubGrps];
	int* cntArr = new int[numOfPerformanceSubGrps];
	int* grpIndexArrr = NULL;//new int[rschDataAnchor->m_numOfItems];
	
	//	 modePRed -> with extreme based on uninvese (2), with exteme based on person anchor(1), stratig (0)
	DFGHJ( threshArr ,   avgDepArr ,  cntArr,	 predArr,centerPredArr, grpIndexArrr,sumAdvancedPErfWghts,
		isPersonIn,	rschDataAnchor,  globals,  numOfPerformanceSubGrps,
								profArr, numOfProfiles, modePRed,   isWithExtremeDimension, isThisCaseOfAnchorUniverseIn ,  isWithFineTuning);
	double sumWghts=0.0;
	double strertchFullTest = 0.0;
	for(int z = 0 ; z < numOfPerformanceSubGrps ; z++)
	{
		double gap = avgDepArr[z] - anchorvAlueee;//333 b depAnchorUniv;
		gap	 *= gap;
		strertchFullTest += gap * (double(cntArr[z]));
		sumWghts += double(cntArr[z]);
	}
	strertchFullTest /= sumWghts;

	if(depAvgArrrOut != NULL)
	{
		for( int z = 0 ; z < numOfPerformanceSubGrps;z++)
		{
			depAvgArrrOut[z] = avgDepArr[z];
		}
	}
	if(cntAvgArrOut != NULL)
	{
		for( int z = 0 ; z < numOfPerformanceSubGrps;z++)
		{
			cntAvgArrOut[z] = cntArr[z];
		}
	}
	if(thredArrOut != NULL)
	{
		for( int z = 0 ; z < numOfPerformanceSubGrps;z++)
		{
			thredArrOut[z] = threshArr[z];
		}
	}



	delete []threshArr;
	delete []avgDepArr ;
	delete []cntArr;

	return strertchFullTest;
}



 //6 13 23 *** tuirn this to status and see if compiles
void cResearchObject::FillProfileListObjectsWothAdvancedPerformanceNew(	cProfileObject** profileArrr,
			int numberOfProfiles,cProfileObject* anchor, cResearchDataObj*   rschDataAnchor,
			cGlobals* globals, int numOfSubGrps,  double depAnchorUnivvv, bool isThisCaseOfAnchorUniverseIn)
{
		 
	int smallGrpSize = globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE;
	int numOfPerfGrps = rschDataAnchor->m_numOfItems / smallGrpSize;
	numOfPerfGrps  = cVarianceCalc::Max(numOfPerfGrps , 2);
	numOfPerfGrps  = cVarianceCalc::Min(numOfPerfGrps , 50);

	double anchorvAluee = anchor->GetProfileDepAverage();
		if(IS_ANCHOR_UNIVERSE_CROSS_ANCHORS  && isThisCaseOfAnchorUniverseIn)
	{
		anchorvAluee = anchor->GetRootProfile()->GetProfileDepAverage();
	}//7 6 23 remove anchor from input send only anchor value or uivers value per logic but no need for the profiles
	int modePred=0;
	
///////////////////////////////////////	PRepare First Zero Step New Profiles ////////////////////
	//tempArr holds only profiles that passed a first test positivly. it starts with root as given.
	cProfileObject** finalProfileArr = new cProfileObject*[numberOfProfiles]; 
	//6 22 23 move tempArr definition to caller function as a result set and delete others input proifles
	for(int p = 0 ; p < numberOfProfiles ; p++)
	{
		finalProfileArr[p]=NULL;
	}
	finalProfileArr[0] = profileArrr[0];
	double standardProfileWgh = 1.0;
	finalProfileArr[0]->FillAdvancedPerfAllSubGrps(standardProfileWgh);//put in all 5 sub groups a 1.0 weight 


	//add befoer each test iteration provigin perf scores for each profile. then adding code to take our parients
	//in prediction tasks so get less competition for a new profile 
	double * predArr = new double [ rschDataAnchor->m_numOfItems];
	double* sumMAtchedProfileWeights = new double[rschDataAnchor->m_numOfItems];
	int* numOfProfilesMatched = new int[rschDataAnchor->m_numOfItems];
	double* sumPrdictionsMatched= new double [ rschDataAnchor->m_numOfItems];
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems; i++)
	{
		sumMAtchedProfileWeights[i]=standardProfileWgh;
		numOfProfilesMatched[i]=1;
		
		double predictionWithInterv=0.0;
		double preditionWitoutInterv=0.0;
		double performanceReg=0.0;
		double performanceAdv=0.0;	
		int profileID=-1;
		bool isWithFineTuning=false;//7 11 23 
		bool isAdvancedPerfGetbEstMatch=true;
		int grpIndex = -1;
		profileArrr[0]->PredictionElementsNEW( predArr[i] , predictionWithInterv, preditionWitoutInterv,
			performanceReg , performanceAdv, profileID, grpIndex,	rschDataAnchor->m_twoDimArray[i] ,
			rschDataAnchor->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
		
		sumPrdictionsMatched[i]=predArr[i]*standardProfileWgh;//weighted predcitions 
	}

	double strertchFullTestBase = StretchCalculation(NULL,predArr ,  rschDataAnchor, anchorvAluee, globals,  modePred, numOfPerfGrps,NULL);
	double* stretchArr = new double[numberOfProfiles];
	stretchArr[0] = strertchFullTestBase;

	int movingProfCnt = 1;

	double movingHighestStretch = strertchFullTestBase;
	for(int p = 1 ; p < numberOfProfiles ; p++)
	{
	//	double tierSt rucrue[3];
	//	int numO fTiers = 3;
	//	profileA rr[p]->Prepar e3TierValueAbsoloteMode(tierStrucrue);

		profileArrr[p]->FillAdvancedPerfAllSubGrps(standardProfileWgh);
		bool* isInProff = new bool[rschDataAnchor->m_numOfItems];
		int sizeOfProff = FillIsInProfSub(isInProff,profileArrr, p,-1,rschDataAnchor, NULL);//-1 to ask for full proifle
		double* tempPReArr = new double[ rschDataAnchor->m_numOfItems];
		double* tempExtremeBucketPReArr = new double[ rschDataAnchor->m_numOfItems];
		double* tempSumMAtcProfWghts = new double[rschDataAnchor->m_numOfItems];
		int* tempNumOfMatched = new int[rschDataAnchor->m_numOfItems];
		double* tempSumPrdicMatched= new double [ rschDataAnchor->m_numOfItems];
		int countOfExtremeChanges=0;
		for(int i=0;i<rschDataAnchor->m_numOfItems;i++)
		{
			tempPReArr[i] = predArr[i];
			tempExtremeBucketPReArr[i] = predArr[i];
			tempSumMAtcProfWghts[i]=sumMAtchedProfileWeights[i];
			tempNumOfMatched[i]=numOfProfilesMatched[i];
			tempSumPrdicMatched[i]=sumPrdictionsMatched[i];
			if(isInProff[i])
			{
				double preditionProfileP = 0.0;
				double predictionWithInterv=0.0;
				double preditionWitoutInterv=0.0;
				double performanceReg=0.0;
				double performanceAdv=0.0;	
				int profileID=-1;
				bool isWithFineTuning=false;//7 11 23
				bool isAdvancedPerfGetbEstMatch=true;
				int grpIndex = -1;
				profileArrr[p]->PredictionElementsNEW(preditionProfileP , predictionWithInterv, preditionWitoutInterv,
					performanceReg , performanceAdv, profileID, grpIndex,	rschDataAnchor->m_twoDimArray[i] ,
					rschDataAnchor->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
	
				tempPReArr[i] = CalcUpdatedPredWithaccommulativeSums(predArr[i], sumMAtchedProfileWeights[i],
					numOfProfilesMatched[i], 	sumPrdictionsMatched[i], preditionProfileP, 	standardProfileWgh);
				
				//double valLEftbucet = 
				bool isIndexMostextreme =  profileArrr[p]->IsIndexMostExtreme(grpIndex, anchorvAluee);
				
				//GetSubGroupAverageDependentArr()[0] 
				int sample =  profileArrr[p]->GetSubBucketCntArr()[grpIndex];
				//6 24 23 ** add logic that firsst set what is extreme from the anchor profileArr[0] and then maybr  both sides 
				//can enter even if the one most extreme is not grpIndex but the oter one it can still be extreme here
				if(isIndexMostextreme &&(sample >= globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE))
				{
					tempExtremeBucketPReArr[i]=tempPReArr[i];
					countOfExtremeChanges ++;
				}
				tempSumMAtcProfWghts[i] += standardProfileWgh;
				tempNumOfMatched[i]++;
				tempSumPrdicMatched[i] += (standardProfileWgh *preditionProfileP);
			}
		}
		//6 24 23 * add an option to check back once in a while and use previous thredholds. then replcae NULL base and here accordlingly
		double tempStretch =  StretchCalculation(NULL,tempPReArr ,  rschDataAnchor, anchorvAluee, globals,  modePred, numOfPerfGrps,NULL);
		stretchArr[p] = tempStretch;
		double extremeStreetch=StretchCalculation(NULL,tempExtremeBucketPReArr, rschDataAnchor, anchorvAluee, globals, modePred, numOfPerfGrps,NULL);
			//tempExtremeBucketPReArr[i]=tempPReArr[i];
		//			countOfExtremeChanges ++;
		if((tempStretch > movingHighestStretch) || (extremeStreetch > movingHighestStretch) )
		{
			if(tempStretch<movingHighestStretch)
			{
				int sdg=0;
			}


			movingHighestStretch = tempStretch;
			finalProfileArr[movingProfCnt] = profileArrr[p];
			finalProfileArr[movingProfCnt]->FillAdvancedPerfAllSubGrps(standardProfileWgh);
			movingProfCnt++;
						
			delete[] predArr;
			predArr = tempPReArr;
			tempPReArr=NULL;
			delete [] sumMAtchedProfileWeights;
			sumMAtchedProfileWeights = tempSumMAtcProfWghts;
			tempSumMAtcProfWghts = NULL;
			delete []numOfProfilesMatched;
			numOfProfilesMatched = tempNumOfMatched;
			tempNumOfMatched = NULL;
			delete []sumPrdictionsMatched;
			sumPrdictionsMatched= tempSumPrdicMatched;
			tempSumPrdicMatched = NULL;
		}
		else
		{// keep memory of proifle p to delete
			delete []tempPReArr;
			tempPReArr=NULL;
			delete []tempSumMAtcProfWghts;
			tempSumMAtcProfWghts=NULL;
			delete []tempNumOfMatched;
			tempNumOfMatched=NULL;
			delete []tempSumPrdicMatched;
			tempSumPrdicMatched = NULL;
			delete profileArrr[p];
			profileArrr[p]=NULL;
		}


		if(isInProff != NULL)
		{
			delete []isInProff;
			isInProff=NULL;
		}
		if(tempPReArr)
		{
			int sss=0;//should not come here
		}
		if(tempExtremeBucketPReArr != NULL)
		{
			delete []tempExtremeBucketPReArr;
			tempExtremeBucketPReArr=NULL;
		}

	}
	{
		double endStretchBeforeWeigting0 =  StretchCalculation(NULL,predArr ,  rschDataAnchor, anchorvAluee,
			globals,  modePred, numOfPerfGrps, NULL);

		//int sdggg=0;
	//	double endStretchBeforeWeigting10 =  StretchCalculation(NULL,predArr ,  rschDataAnchor, anchorvAluee,
	//		globals,  modePred, 10, NULL);
		int rtt=0;
	}
	//addded weight goes towars a profile by that rate portion way. then, if that goes well on average across all persons and stretch
	//than multiper goes and increase the imporotance of a profile. a multipier is than effecting the advanced performacne which can be 
	double addedWeightPortion = 1.0;//actually this makes the profile to be 100% more strong
	double multiplerr = 1.25;//ProfileAd dingTest might consider an advancde perofoacne with pow(2) or 3. 
	
	double stretchArrView[25];
	bool end = false;
	int cntOfDecreaseingIterations = 0;
	for(int z = 0 ; z < 25 && (!end) ; z++)
	{
		double* predArrAfter = new double[rschDataAnchor->m_numOfItems];	
		double* sumAdvancedPErfWghts =  new double[rschDataAnchor->m_numOfItems];	
		double* predCenterArr = new double[rschDataAnchor->m_numOfItems];
		int modePRed=0.0;
		bool isWithExtremeDimension = true;

		double tierStrucrue[3];
		int numOfTiers = 3;
		if(IS_ANCHOR_UNIVERSE_CROSS_ANCHORS  && isThisCaseOfAnchorUniverseIn)
		{
			finalProfileArr[0]->GetRootProfile()->Prepare3TierValueAbsoloteMode(tierStrucrue);
		}
		else
		{
			finalProfileArr[0]->Prepare3TierValueAbsoloteMode(tierStrucrue);//profileArr[0] is anchor
		}
		double* depAvgArrOut = NULL;
		int* cntArrOut=NULL;
		double* thredArrOut=NULL;
		bool isWithFineTuning=true;
		double endStretchDEbug=ProfileAddingTest(depAvgArrOut,cntArrOut, thredArrOut, predArrAfter,predCenterArr,sumAdvancedPErfWghts, finalProfileArr ,movingProfCnt, rschDataAnchor,
			anchorvAluee,  globals, modePRed, numOfPerfGrps,  tierStrucrue,  numOfTiers,  isWithExtremeDimension , isThisCaseOfAnchorUniverseIn  , isWithFineTuning);

	//	BASE FOR COMPARE	endStretchBase is the base to comapre below regarding success increse of a profile weight
		 
		double* thredArrBase = new double[numOfPerfGrps];
		double endStretchBase =  StretchCalculation(thredArrBase,
			predArrAfter ,  rschDataAnchor, anchorvAluee, globals,  modePred, numOfPerfGrps, NULL);
		stretchArrView[z] = endStretchBase;
		if( (z > 1) && (stretchArrView[z] <= stretchArrView[z-1]))
		{
			cntOfDecreaseingIterations++;
			if(cntOfDecreaseingIterations >= 3)
			{
				end = true;
			}
		}
		else
		{
			//cntOfDecreaseingIterations =0;
		}
		//6 24 23 add this call
		double* thredArrCenterBase = new double[numOfPerfGrps];
		double centerStretchBase = StretchCalculation(
			thredArrCenterBase,predCenterArr ,  rschDataAnchor, anchorvAluee, globals,  modePred, numOfPerfGrps,NULL);

		double* profileScores = new double[movingProfCnt]; 
		double meanProfScores = 0.0;
		for(int p = 0 ; p < movingProfCnt;  p++)
		{
		 
			 			 
			bool* isInProff = new bool[rschDataAnchor->m_numOfItems];
			int sizeOfProff = FillIsInProfSub(isInProff,finalProfileArr , p,-1,rschDataAnchor, NULL);//-1 to ask for full proifle
	
			bool isImproved = false;
			double* localPRediction = new double [rschDataAnchor->m_numOfItems];
			double* localCenterPRediction = new double [rschDataAnchor->m_numOfItems];
			double* movingGenerPrediction = new double [rschDataAnchor->m_numOfItems];
			double* movingSumAdvancedPErfWeights= new double [rschDataAnchor->m_numOfItems];
			double* movingProfilePrediction = new double [rschDataAnchor->m_numOfItems];
			double* movingDeparr  = new double [rschDataAnchor->m_numOfItems];
			int movingGenPredIndex = 0;
			for(int i = 0 ; i <rschDataAnchor->m_numOfItems ; i++)
			{
				localPRediction[i] = predArrAfter[i];
				localCenterPRediction[i] = predCenterArr[i];
				if(isInProff[i])
				{
					double preditionProfileP = 0.0;
					double predictionWithInterv=0.0;
					double preditionWitoutInterv=0.0;
					double performanceReg=0.0;
					double performanceAdv=0.0;	
					int profileID=-1;
					bool isWithFineTuning=false;//7 11 23
					bool isAdvancedPerfGetbEstMatch=true;
					int grpIndex = -1;
					finalProfileArr[p]->PredictionElementsNEW(preditionProfileP , predictionWithInterv, preditionWitoutInterv,
						performanceReg , performanceAdv, profileID, grpIndex,	rschDataAnchor->m_twoDimArray[i] ,
					   rschDataAnchor->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
					movingGenerPrediction[movingGenPredIndex] = predArrAfter[i];
					//movingSumAdvancedPErfWeights 
					movingSumAdvancedPErfWeights[movingGenPredIndex]= sumAdvancedPErfWghts[i];
					movingProfilePrediction[movingGenPredIndex] = 0.9* preditionProfileP  + 0.1*predArrAfter[i];//keep some range for testing 
					movingDeparr[movingGenPredIndex]= rschDataAnchor->m_depArr[i];
					movingGenPredIndex++;
					double currentPortionOfSumWghts = performanceAdv / sumAdvancedPErfWghts[i];
					double newAddedPortion = currentPortionOfSumWghts* (addedWeightPortion);
					newAddedPortion = cVarianceCalc::Min(newAddedPortion , 1.0);
					newAddedPortion = cVarianceCalc::Max(newAddedPortion , 0.0);
					newAddedPortion = cVarianceCalc::Max(newAddedPortion,0.2);
					newAddedPortion=0.2;//test fixed value
					//6 24 23 * 3 this change of the local prediction, as well as the one below, should only be done if the profile 
					//preditionProfileP is int he same tier or more than the localPRediction[i] wh ich is already a m ix of exteme and perfomrance ogic 
				
					bool isIndexMostextreme2=false;
					if(true)
					{
						if(p==50)
						{
							int sdfg =0;
						}
						isIndexMostextreme2 =  //profileArr
								finalProfileArr[p]->IsPredictionExtreme(localPRediction[i],anchorvAluee, tierStrucrue,
						                               numOfTiers, preditionProfileP);
						double gapCurrent =   cVarianceCalc::Abs(localPRediction[i]-anchorvAluee);
						double gapProfileP = cVarianceCalc::Abs(preditionProfileP-anchorvAluee);
						//isIndexMostextreme = gapProfileP > gapCurrent;
					}	
					if(true)//isIndexMostextreme)//6 26 23 consider smoothing the prediciotn test function and here chancing the filter
					//in to be not hard tier but just more extreme assuming that if went in it wil presever that filter in a soft
					{//consoider pow 2 for extreme but trhen so that the rate is not too low out of 1 to make the niddle move in test
						double rate = GetExtremePredictionWght(preditionProfileP,anchorvAluee,  tierStrucrue,  numOfTiers );
						//newAddedPortion = 0.2;
					//	double portionOfAction = 1.0;
					//	double extre = cVarianceCalc::Abs( preditionProfileP - anchorvAluee);
					//	double portion = extre / (tierStrucrue[0] + tierStrucrue[1]) ;//getting both as sum to aim for a larger ragne
						//to make a 1.0 portion of action
					//	portion =  cVarianceCalc::Min(portion , 1.0);
						rate *= newAddedPortion;
						localPRediction[i] = (rate * preditionProfileP) + ((1.0-rate) *localPRediction[i]);
					}
					double centerProfilePred = finalProfileArr[p]->GetProfileDepAverage();
					 //for center based test go more
					localCenterPRediction[i] =  (newAddedPortion * centerProfilePred) + ((1.0-newAddedPortion) *localCenterPRediction[i]);
//6 24 23 * add check about cancel parients, fine tuning,  and mosst importaht extreme in the after will be with anchor or univrese
				}
			}
			if(p==0)
			{
				int sdg=0;//check to see if anything strage with strertch with one  prediciton value only
			}
			//collect i=0 to N and if isInProff update predArrAfter
			double endStretchPerProfCheck =  StretchCalculation(NULL,localPRediction ,  rschDataAnchor, anchorvAluee,
																			globals,  modePred, numOfPerfGrps, thredArrBase);
			//sizeOfProff
		 


			double centerStrechProfChecl =  StretchCalculation(NULL,localCenterPRediction ,  rschDataAnchor, anchorvAluee,
																	globals,  modePred, numOfPerfGrps, thredArrCenterBase);
	 
//function compares predeiciton of profiile poppuatliu using either that profile itself as prediciton via movingProfilePrediction
	//or the mix of all profiles via movingGenerPrediction. since thhe profie has only certain sub grps use a small num of grps here
			profileScores[p] = CalclateAnchorStretch(movingGenerPrediction,movingProfilePrediction, 
				movingGenPredIndex, anchorvAluee  , movingDeparr ,finalProfileArr[p]->GetNumberOfSubGroups() ,  globals,  modePred)	;
			meanProfScores += profileScores[p];

			double points = 0.0;
			double fullTest = endStretchPerProfCheck - endStretchBase; 
			fullTest *= (rschDataAnchor->m_numOfItems / sizeOfProff);
			double centerGap = centerStrechProfChecl - centerStretchBase;
			centerGap *= (rschDataAnchor->m_numOfItems / sizeOfProff);
		

			if(fullTest > 0.0)
			{
				isImproved = true;
				finalProfileArr[p]->IncreaseAdvPerfAllSubGrps(multiplerr);
			 
			}			 
			else
			{
			//	tempArr[p]->IncreaseAdvPerfAllSubGrps( 1.0 / multiplerr);
			}
			/*else if(   (centerGap+profileScores[p]+fullTest )   > 0.0   )
			{
				//isImproved = true;
				//points +=1.0;
				int sdgg =0;
			}*/
				

			delete []isInProff;
			isInProff=NULL;
			delete []localPRediction;
			localPRediction=NULL;
			delete []localCenterPRediction;
			localCenterPRediction=NULL;
			
			delete [] movingGenerPrediction ;
			delete [] movingProfilePrediction;

			delete []movingSumAdvancedPErfWeights;

			delete [] movingDeparr ;
		}
		meanProfScores /= movingProfCnt;
		for(int p = 0 ; p < movingProfCnt;  p++)
		{
			if(profileScores[p] > meanProfScores)
			{
				//tempArr[p]->IncreaseAdvPerfAllSubGrps(multipler);//if open here close above
				int sdg=0;
			}
		}


		if(predCenterArr != NULL )
		{
			delete []predCenterArr;
			predCenterArr=NULL;
		}
		if(predArrAfter != NULL)
		{
			delete []predArrAfter;
			predArrAfter=NULL;
		}
		if(sumAdvancedPErfWghts != NULL)
		{
			delete [] sumAdvancedPErfWghts;
			sumAdvancedPErfWghts=NULL;
		}
		if(profileScores != NULL)
		{
			delete []profileScores;
			profileScores=NULL;
		}
		if(	thredArrBase)
		{
			delete []thredArrBase;
			thredArrBase=NULL;
		}
		if(thredArrCenterBase)
		{
			delete[]thredArrCenterBase;
			thredArrCenterBase=NULL;
		}
		if(z==10)
		{
			int ooo=0;	
		}
	} 
	if(finalProfileArr)
	{
		delete []finalProfileArr;
		finalProfileArr = NULL;
	}
	if(stretchArr)
	{
		delete []stretchArr;
		stretchArr = NULL;
		stretchArr = NULL;
	}
	if(sumMAtchedProfileWeights)
	{
		delete []sumMAtchedProfileWeights;
		sumMAtchedProfileWeights = NULL;
	}
	if(numOfProfilesMatched)
	{
		delete []numOfProfilesMatched;
		numOfProfilesMatched = NULL;
	}
	if(predArr)
	{
		delete []predArr;
		predArr = NULL;
	}
	if(sumPrdictionsMatched)
	{
		delete []sumPrdictionsMatched;
		sumPrdictionsMatched = NULL;
	}

}


void cResearchObject::ProfSubPErsonAnalytics(  cProfileObject** profileArrr,  int numberOfProfiles, cResearchDataObj* rschDataAnchor,  double* predArrAfter,	
	int numOfPerfGrps, double* thredArrBase,  int modePred, double anchorvAluee, double stretchBase,  double multiplerr,	  
	   cGlobals* globals , double* depAvgArrIn, int* cntAvgArrIn, bool isWithDecreasedScores, bool isWithFineTuning) //thredArrBase numOfPerfGrps
{

	double* avgBenefitPt = new double[rschDataAnchor->m_numOfItems];
	int* hitCount = new int[rschDataAnchor->m_numOfItems];
	double* weightedAvgBenefit = new double[rschDataAnchor->m_numOfItems];
	double* sumWghtsArr = new double[rschDataAnchor->m_numOfItems];
	for(int i = 0 ; i <rschDataAnchor->m_numOfItems ; i++)
	{
		avgBenefitPt[i]=0.0;
		hitCount[i]=0;
		weightedAvgBenefit[i]=0.0;
		sumWghtsArr[i]=0.0;
	} 

	double** subGrpInfo = new double*[numberOfProfiles];
	for(int p = 0 ; p < numberOfProfiles;  p++)
	{
		subGrpInfo[p] = new double[ profileArrr[p]->GetNumberOfSubGroups()];
		for(int s = 0 ; s< profileArrr[p]->GetNumberOfSubGroups() ; s++)
		{
			subGrpInfo[p][s] = 0.0;
		}
	}

		
	for(int p = 0 ; p < numberOfProfiles;  p++)
	{
			 			 
		bool* isInProff = new bool[rschDataAnchor->m_numOfItems];
		int sizeOfProff = FillIsInProfSub(isInProff,profileArrr , p,-1,rschDataAnchor, NULL);//-1 to ask for full proifle
		for(int s = 0 ; s < profileArrr[p]->GetNumberOfSubGroups() ; s++)
		{
			bool isImproved = false;
			double* localPRediction = new double [rschDataAnchor->m_numOfItems];
			bool* isInProffSub = new bool[rschDataAnchor->m_numOfItems];
			int sizeOfProffSub = FillIsInProfSub(isInProffSub,profileArrr , p,s,rschDataAnchor, isInProff);//-1 to ask for full proifle

			    //potentially call this funcitonn with all 5 s is in arrays for one p to have some time saving as part of it is the same.
			if(IS_WITH_CLEAN_PARENT_FROM_BEST_MATCH)
			{
				AdjustIsInAndSizeConsideringChildProfiles(isInProffSub,sizeOfProffSub, rschDataAnchor, profileArrr,numberOfProfiles , p,s);
			}
			if(IS_WITH__CALC_FULL_TEST_METHOD)
			{
				subGrpInfo[p][s] = CalcualteFullTest(rschDataAnchor , localPRediction,  predArrAfter,   isInProffSub,  sizeOfProffSub,
					 profileArrr,  p,   thredArrBase ,    depAvgArrIn,   cntAvgArrIn,   numOfPerfGrps, anchorvAluee ,	 stretchBase,  globals  , isWithFineTuning);
			}
			else
			{
				subGrpInfo[p][s] = ABCDEFG( rschDataAnchor ,  localPRediction,  predArrAfter,   isInProffSub,  sizeOfProffSub,
					 profileArrr,  p,   thredArrBase ,   depAvgArrIn,   cntAvgArrIn,   numOfPerfGrps, anchorvAluee ,	 stretchBase,  globals);
			}
			double profSubWeight = profileArrr[p]->GetProfileAdvancedPerformance(s);
			for(int i = 0 ; i <rschDataAnchor->m_numOfItems ; i++)
			{
				if(isInProffSub[i])
				{
					avgBenefitPt[i]+=subGrpInfo[p][s] ;
					hitCount[i]++;
					weightedAvgBenefit[i] += profSubWeight * subGrpInfo[p][s] ;
					sumWghtsArr[i] += profSubWeight;
				}
			}		
			delete []isInProffSub;
			isInProffSub=NULL;
			delete []localPRediction;
			localPRediction=NULL;
		}
		delete []isInProff;
		isInProff=NULL;
	
	}

	
	for(int i = 0 ; i <rschDataAnchor->m_numOfItems ; i++)
	{
		if(hitCount[i]>0)
		{
			avgBenefitPt[i]  /=   hitCount[i];
			weightedAvgBenefit[i] /= sumWghtsArr[i];
		}
	} 

	double meanPerBen = 0.0;
	double sdPerBen = 0.0;
	cVarianceCalc::CalculateMeanAndSD(meanPerBen, sdPerBen, avgBenefitPt,NULL,rschDataAnchor->m_numOfItems);
		
	for(int p = 0 ; p < numberOfProfiles;  p++)
	{
		bool* isInProff = new bool[rschDataAnchor->m_numOfItems];
		int sizeOfProff = FillIsInProfSub(isInProff,profileArrr , p,-1,rschDataAnchor, NULL);//-1 to ask for full proifle
		for(int s = 0 ; s < profileArrr[p]->GetNumberOfSubGroups() ; s++)
		{
			bool* isInProffSub = new bool[rschDataAnchor->m_numOfItems];
			int sizeOfProffSub = FillIsInProfSub(isInProffSub,profileArrr , p,s,rschDataAnchor, isInProff);//-1 to ask for full proifle
			double avgBenefitDelta = 0.0;
			double avgWeghtedScore =0.0;
			int cntHere = 0;
			for(int i = 0 ; i <rschDataAnchor->m_numOfItems ; i++)
			{
				if(isInProffSub[i])
				{
					double avgScore = 0.0;
					if(hitCount[i]>0)
					{
						avgScore =  avgBenefitPt[i];//  / hitCount[i];
						avgBenefitDelta +=avgScore;
						avgWeghtedScore +=	weightedAvgBenefit[i];
						cntHere++;
					}
				}
			}
			if(cntHere>0)
			{
				avgBenefitDelta /= cntHere;
				avgWeghtedScore  /= cntHere;
				double gap = subGrpInfo[p][s] - avgBenefitDelta;
				if(IS_ML_WITH_WEIGHTED_PROFILES)
				{
					gap = subGrpInfo[p][s] - avgWeghtedScore;
				}
				if(IS_WITH_REDUCED_TEST_BY_SIM_PROF_PERF)
				{
					gap = subGrpInfo[p][s] ;
				}
				if(gap > 0.0)
				{
					gap /= sdPerBen;
					double localMuilti = ((multiplerr-1.0)*gap)+1.0;
					profileArrr[p]->IncreaseAdvPerfAllSubGrps(localMuilti,s);
				}
				else if(gap < 0.0)
				{
					gap*=-1;
					gap /= sdPerBen;
					double localMuilti = ((multiplerr-1.0)*gap)+1.0;
					if(isWithDecreasedScores)
					{
						profileArrr[p]->IncreaseAdvPerfAllSubGrps(1.0/localMuilti,s);
					}				
				}
			}
			delete []isInProffSub;
			isInProffSub=NULL;
		}
		delete []isInProff;
		isInProff=NULL;
	}	

	delete []avgBenefitPt;
	avgBenefitPt=NULL;
	delete []hitCount;
	hitCount=NULL;
	delete []weightedAvgBenefit;
	weightedAvgBenefit=NULL;
	delete []sumWghtsArr;
	sumWghtsArr=NULL;

	if(subGrpInfo != NULL)
	{
		for(int p = 0 ; p < numberOfProfiles;  p++)
		{
			delete []subGrpInfo[p];
		}
		delete []subGrpInfo;
		subGrpInfo = NULL;
	}
}


double	cResearchObject::CalcualteFullTest( cResearchDataObj* rschDataAnchorr , double* localPRediction, double* predAll,  bool* isInProffSub, int sizeOfProffSub,
	cProfileObject** profileArrr, int p, double*  thredArrBase , double*   depAvgArrIn,  int* cntAvgArrIn,  int numOfGrps,
	double anchorvAluee ,	double stretchBase, cGlobals* globals, bool isWithFineTuning)
{
	double ret = 0.0;
	cResearchDataObj* localResObj = new cResearchDataObj(rschDataAnchorr , isInProffSub );

	if( localResObj->m_numOfItems > 200)
	{
		double* predAllLocal = new double[ localResObj->m_numOfItems];
		int mocingIndex = 0;
		for(int allindex = 0 ; allindex < rschDataAnchorr->m_numOfItems ; allindex++)
		{
			if(isInProffSub[allindex])
			{
				predAllLocal[mocingIndex++] = predAll[allindex];
			}
		}
		
		double* predProfP = new double[ localResObj->m_numOfItems];
		for(int i = 0 ; i < localResObj->m_numOfItems ; i++)
		{
		
		
			double preditionProfileP = 0.0;
			double predictionWithInterv=0.0;
			double preditionWitoutInterv=0.0;
			double performanceReg=0.0;
			double performanceAdv=0.0;	
			int profileID=-1;
			
			bool isAdvancedPerfGetbEstMatch=true;
			int grpIndex = -1;
			profileArrr[p]->PredictionElementsNEW(preditionProfileP , predictionWithInterv, preditionWitoutInterv,
						performanceReg , performanceAdv, profileID, grpIndex,	localResObj->m_twoDimArray[i] ,
						localResObj->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
			predProfP[i] = preditionProfileP;

		}	
		double stretch = GetLocalStretchValues( predAllLocal,predProfP,  anchorvAluee , numOfGrps , localResObj , thredArrBase,	depAvgArrIn, cntAvgArrIn, globals);
	
		delete []predAllLocal;
		predAllLocal=NULL;
		delete []predProfP;
		predProfP=NULL;
		
		ret= stretch;
	}
	delete localResObj;
	localResObj=NULL;
	return ret;
}



/*
output - value of how mjch  , double* predArrP  is getting bettetr stretch than predArrAll as a source

for each prediciton array giving same conditions

for i want to create a version of the  depArrIn that is only the profSub pop
that version is done by hiting the deparrIn with prediciotn array, post threshold, and getting a coucnt tapping up
therefore, the weights on the sub weighted dep arra in will be differnett when we use the pred all through thre threehold or thr pred P throug the trhedho  ,
getting different buckets , sometimes,
we also want to then see in these diffrnet versions of the buckets, what are the dep array of the pop.
then we do stretch.
again - 

double depLocalBaesedOnALL[100];
CollectWeieghtedDepArr(depLocalBaesedOnALL ,  predArrAll , threshIn , numOfGrps
double depLocalBaesedOnP[100]


method



each member of predArrAll will get its bucket in depAvgArrIn, using the thredoldArr and the predArr[i] as input.
\
then we also know the different relevant buckets it got hit . for each calcualte the avg avg dep for the local object. for example, have 30 buckets in the thriIn
and the local array prediction fo these profsub persons hit buckets 3-9 with certain sample size for each. we then calcualte the current stretch of these 
buckets with the sample size of the probsub persons, get a base stretch, as it relates to the input anchor value. 
as of now i know what is the stretch of these elements by creating a sub set of the inpt dep array, or a weighted one so 0 count is still a sub set on weight.
having the sub set sets the stage for asking the question are we better mixing some stretch on behalf of othese persons. while the base dep array version is set
b hitting the predAll values on the thresholn and getting the depAvIn, now the local depArr is base on the predArr as base using all profiles .

the question we can ask is how a predP may imrpove the stretch.

for, for the so far algo the steps are:


input :
of the local probSub pop only.
steps:
take each predArrAll[i] and get the right depArrIn




then, predArr will be turned into a calPred[i] which is after using the threshold in and depArrIn, and that is since we dont want the support of the acualy
dep array to take it iout of the test. then, the calPred[i] can gr grouped and 
we will then have the depAvvgArrIn[index] usin the index matched by the predArr[i] iput, 



divide the pred array to num of grps using the prediciton value only. 

prediction array values will get divided into x groups 

*/

void	cResearchObject::CollectWeieghtedDepArr(
							double* depLocal ,int* cntLocal, double*  predArr , double* threshArr ,	int numOfGrps,cResearchDataObj* rschDataAnchor)
{
	for(int x = 0 ; x< numOfGrps;x++)
	{
		depLocal[x]=0.0;
		cntLocal[x]=0.0;
	}
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems; i++)
	{
		int subGrpIndex = cProfileObject::GetSubGrpIndex(predArr[i], threshArr, numOfGrps);
		cntLocal[subGrpIndex]++;
		depLocal[subGrpIndex] += rschDataAnchor->m_depArr[i];
	}
	for(int x = 0 ; x< numOfGrps;x++)
	{
		if(cntLocal[x] > 0)
		{
			depLocal[x] /= cntLocal[x];
		}
	}

}





double cResearchObject::GetLocalStretchValues( double* predArrAll, double* predArrP ,  double anchor  , int numOfGrps, 
					cResearchDataObj* subPopObject, 	double* threshIn,	double* depArrIn, int* cntArrIn,	cGlobals* globals)
{
	double strertch1 = cResearchObject::StretchLoop(depArrIn,   cntArrIn,    numOfGrps ,  anchor);

	int sizeOfProffSub = subPopObject->m_numOfItems;
	int sizeOfAllPop = 0;
	for(int s=0;s < numOfGrps;s++)
	{
		sizeOfAllPop += cntArrIn[s];
	}
	 
	double depLocalBaesedOnALL[100];
	int cntLocalBasedOnAll[100];
	CollectWeieghtedDepArr(depLocalBaesedOnALL ,cntLocalBasedOnAll,  predArrAll , threshIn , numOfGrps, subPopObject);
	double ret=0.0;
	if(IS_METHOD_ML_TYPE_SIMPLE)
	{
		double meanProfSub = 0.0;
		int cntProffSub=0;
		for(int s=0;s < numOfGrps;s++)
		{
			meanProfSub  +=  cntLocalBasedOnAll[s] * depLocalBaesedOnALL[s];
			cntProffSub  +=  cntLocalBasedOnAll[s];
		}
		meanProfSub /= cntProffSub;
		for(int s=0;s < numOfGrps;s++)
		{
			if( cntLocalBasedOnAll[s] > 0)
			{
				depLocalBaesedOnALL[s] = meanProfSub;//in case many buckets and small sample, i herer share the mean of progsub across all bucket apperance
			}
		}

		double temppVal[100];
		int tempCnt[100];
		bool isToAdd = true;
		AddOrRemoveSubPoopulationsFromDepArr( temppVal, tempCnt , depArrIn , cntArrIn, depLocalBaesedOnALL, cntLocalBasedOnAll, numOfGrps, isToAdd);
		double strertch2 = cResearchObject::StretchLoop(temppVal, /*tempCnt*/ cntArrIn, numOfGrps, anchor);
		ret = strertch2 - strertch1; //if adding/doubeling the profsub popluatlino importance, merging that same weight that they currently alreay ahve within

	//	strertch1 = cResearchObject::StretchLoop(depArrIn, cntArrIn, numOfGrps, anchor);
	//	strertch2 = cResearchObject::StretchLoop(temppVal, tempCnt, numOfGrps, anchor);
		
		
		
		
		//certain buckets and adding another chunk, same size to the mix, to the same buckets , then we get stretch2. the more the stretch2 is highgegr means we selected 
//a profsub population that togethetr show the path to a more distance bucket/prdiciton that goes wit stretch and adding weight to such prof sub would increase streth
//if a prfsub carry many peope that all get more than average or less tthan average of associated profiles that claim to deserve an increased weight, than the
	//weight of such will be calibrted
	
	}
	else
	{

		double reducedDepArr[100];
		int reducedCntArr [100];
		bool isToAdd = false;// first want to get from stretch1 to stretch2 by removing the profsub pop. later,  for getting to 3 , we want isToAdd to be true
		AddOrRemoveSubPoopulationsFromDepArr   (  reducedDepArr, reducedCntArr ,  depArrIn , cntArrIn  , depLocalBaesedOnALL , cntLocalBasedOnAll , numOfGrps , isToAdd);

		double strertch2 = cResearchObject::StretchLoop(reducedDepArr,   reducedCntArr ,    numOfGrps ,  anchor);

		double depLocalBaesedOnP[100];
		int cntLocalBasedOnP[100];
		CollectWeieghtedDepArr(depLocalBaesedOnP ,cntLocalBasedOnP,  predArrP  , threshIn , numOfGrps, subPopObject);

		double insteadedDepArr[100];
		int increasdedCntarr[100];
		isToAdd = true;
		AddOrRemoveSubPoopulationsFromDepArr   (  insteadedDepArr, increasdedCntarr ,  reducedDepArr , reducedCntArr  , 
																		depLocalBaesedOnP , cntLocalBasedOnP , numOfGrps , isToAdd);
		
		double strertch3 = cResearchObject::StretchLoop(insteadedDepArr,   increasdedCntarr ,    numOfGrps ,  anchor);
		ret = strertch3 - strertch1;
	}
	ret  *= (((double)sizeOfAllPop ) / ((double)sizeOfProffSub));//
	return ret;
	 
}
	/*

	double stretchP = 0.0;
	double cntPbased = 0;
	
	for(int s = 0 ; s < numOfGrps ; s++)
	{
		if(cntLocalBasedOnP[s] > 0)
		{
			double streth = (depLocalBaesedOnP[s] - anchor) * (depLocalBaesedOnP[s] - anchor);
			stretchP += streth * cntLocalBasedOnP[s];
			cntPbased +=  cntLocalBasedOnP[s];
		}		
	}
	if(cntPbased>0)
	{
		stretchP /= cntPbased;
	}

	return stretchP - stretchAll;
	*/
	/////////////////////////////////
	/*double* predGrpsAvgValue = new double[numOfGrps];
	double* depArravgValue= new double[numOfGrps];
	int* arrCnt = new int[numOfGrps];
//	DividePredicitonArryToPRedctionGroups( predGrpsAvgValue  , depArravgValue,arrCnt,  numOfGrps , predArr, rschDataAnchor->m_depArr, rschDataAnchor->m_numOfItems);

	//the higher a gap that means prediditon does not behave like dep
	double avgGapOfStretchedValues = 0.0;
	int totlCnt = 0;
	for(int x = 0 ; x < numOfGrps ; x++)
	{
		double gaptest = predGrpsAvgValue[x] -  depArravgValue[x];


		double stretcPredFromAchor = ( predGrpsAvgValue[x] - anchor);
		stretcPredFromAchor *= stretcPredFromAchor;

		double stretchDepFromAchor = ( depArravgValue[x] - anchor);
		stretchDepFromAchor *= stretchDepFromAchor;

		double gap = cVarianceCalc::Abs(stretcPredFromAchor - stretchDepFromAchor);


		avgGapOfStretchedValues += gap* arrCnt[x];
		totlCnt +=  arrCnt[x];
	}
	avgGapOfStretchedValues /= totlCnt;

	//double modePred=0.0;
	//double tempStretch =  StretchCalculation(NULL,predArr ,  rschDataAnchor, anchor, globals,  modePred, numOfGrps,NULL);
	
	delete []predGrpsAvgValue;
	predGrpsAvgValue = NULL;
	delete []depArravgValue;
	depArravgValue=NULL;
	delete []arrCnt;
	arrCnt=NULL;

	return avgGapOfStretchedValues;*/


void cResearchObject::AddOrRemoveSubPoopulationsFromDepArr   (  double* depArrNew, int* cntarrNew ,  double* depArrCur , int* cntArrCur  , 
																	double* subDepArr , int* cntSubDepArr , int numOfGrps , bool isToAdd)
{
	/*
	*/
	for(int x = 0 ; x < numOfGrps ; x++)
	{
		AddOrRemoveSubBucketsOfDepValues(depArrNew[x], cntarrNew[x],  depArrCur[x], cntArrCur[x], subDepArr[x] , cntSubDepArr[x], isToAdd);
	}
}


double	cResearchObject::ABCDEFG(  cResearchDataObj* rschDataAnchor , double* localPRediction, double* predArrAfter,  bool* isInProffSub, int sizeOfProffSub,
	cProfileObject** profileArrr, int p, double*  thredArrBase , double*   depAvgArrIn,  int* cntAvgArrIn,  int numOfGrps,
	double anchorvAluee ,	double stretchBase, cGlobals* globals	)
 {
//7 11 23 * 15 add ceck and remove / false for each person that is true under this profsub validate if any other profile match that this p s and 
				//that profile is its sub set in regards to its inclusion rulres. other words if it has a child , the patients match that child and the prof sub are
				//removed from the prob sub. at that point i need the test to have an enough sample, else, dont send a profile for test and it will restore its 
				//current score. make sure in the predArrAfter that is our base there was no parent . make sure profiles are large
	double actRateUsed = 0.0;
	int cntRate = 0;
	for(int i = 0 ; i <rschDataAnchor->m_numOfItems ; i++)
	{
		localPRediction[i] = predArrAfter[i];//7 11 23 * 15 will get the prediction ater with an "no parents" feature from the get best match area
		//that will allow also here to learn about how a profsub supports pereformance more accurately as i dont consider any person that has
		//a child during learning. need larger profiles for avodiong the support of sample size fro this new approach and then  parent is good for 
		//only those that did not get any more specific 
		if(isInProffSub[i])
		{
				double preditionProfileP = 0.0;
				double predictionWithInterv=0.0;
				double preditionWitoutInterv=0.0;
				double performanceReg=0.0;
				double performanceAdv=0.0;	
				int profileID=-1;
				bool isWithFineTuning=false;//7 11 23 * 3
				bool isAdvancedPerfGetbEstMatch=true;
				int grpIndex = -1;
				profileArrr[p]->PredictionElementsNEW(preditionProfileP , predictionWithInterv, preditionWitoutInterv,
					performanceReg , performanceAdv, profileID, grpIndex,	rschDataAnchor->m_twoDimArray[i] ,
					rschDataAnchor->m_sizeOfItem,  isAdvancedPerfGetbEstMatch, 	-1, *globals,  isWithFineTuning);
				double maxRate = 1.0;// GetExtremePredictionWght(preditionProfileP,anchorvAluee,  tierStrucrue,  numOfTiers );
						
				if(!IS_FLEXIBLE_RATE_STRETCH_TEST)//7 11 23 * 55
				{
					localPRediction[i] = (maxRate * preditionProfileP) + ((1.0-maxRate) *localPRediction[i]);
				}
				else
				{
					double rate = 0.0;
					double predictionMixed=0.0;
					MoveSmallStepIfRateAllows( rate,  predictionMixed,
						localPRediction[i] ,preditionProfileP, thredArrBase,	depAvgArrIn,  cntAvgArrIn,maxRate ,numOfGrps,anchorvAluee); //thredArrBase numOfPerfGrps
							 
					if(rate > 1.0)
					{
						if(rate >2.0)
						{
							int sdgh=0;
						}
						rate = 1.0;
					}

					if(preditionProfileP > localPRediction[i])
					{
						double gap  = preditionProfileP - localPRediction[i];
						predictionMixed = cVarianceCalc::Min(predictionMixed ,   localPRediction[i] + gap * maxRate);
					}
					else
					{
						double gap  = localPRediction[i] -preditionProfileP  ;
						predictionMixed = cVarianceCalc::Max(predictionMixed ,   localPRediction[i] - gap * maxRate);
					}

					localPRediction[i] = predictionMixed;
					actRateUsed += rate;
					cntRate++;
				}
						 
					
		}
	}
	if(cntRate > 0)
	{
		actRateUsed /= cntRate;
	}
	double modePred=0.0;
	double endStretchPerProfCheck =  StretchCalculation(NULL,localPRediction ,  rschDataAnchor, 
								anchorvAluee, globals,  modePred, numOfGrps, thredArrBase);
	double fullTest = endStretchPerProfCheck - stretchBase; 
	if(sizeOfProffSub > 200)
	{
		if(IS_FLEXIBLE_RATE_STRETCH_TEST)//7 11 23 * 55
		{
			fullTest *= (rschDataAnchor->m_numOfItems / (sizeOfProffSub* actRateUsed));//7 11 23 * 55 -> fullTest *= (rschDataAnchor->m_numOfItems / sizeOfProffSub)
		}
		else
		{
			fullTest *= (rschDataAnchor->m_numOfItems / sizeOfProffSub);//7 11 23 * 55 -> fullTest *= (rschDataAnchor->m_numOfItems / sizeOfProffSub)
		}							
	}
	return fullTest;

}



/*
7 11 23 * 15  1 - call and perpare AdjustIsInAndSizeConsideringChildProfiles. 2 - open cancel of parnets in get best match. 3- increase profile size
for each person i  that IS isInProffSub[i]==true AND  that IS included in the profile P and group s, check if there is any other profile not != P
that is a child of P and that person i is in that .
good to first find all chilrder of proifle p and then ony go one by one on the peopl

every p profilei gets this function to take care of p. we first go for all large to small inclusion rule and not 0 to numOfProfiles. We also keep saved
each p outcomes to support the parents. a profile is scores as a mix of all chldren and this profile to have a one predictive model for its members. therefore
the score is for getting into a profile regardless which way you get your prediction by this or its childrer. if so, in GBM time we want to have a way to see
a profile and its children 


*/
void	cResearchObject::AdjustIsInAndSizeConsideringChildProfiles(bool* isInProffSub,  int &sizeOfProffSub, 
					   cResearchDataObj*   rschDataAnchor, cProfileObject** profileArrr,  int numberOfProfiles , int p,  int s)
{
//potentilly 
	int asdgg=0;
	bool* isChild = new bool[numberOfProfiles];
	for(int x = 0 ; x < numberOfProfiles;x++)
	{
		isChild[x]=false;
		cVariableAndValueAndPoints* ruleSetChild = 
						profileArrr[x]->GetInclusionRuleList();
		int ruleChildSize = profileArrr[x]->GetInclusionRuleListSize();

		cVariableAndValueAndPoints* ruleSetParent = profileArrr[p]->GetInclusionRuleList();
		int ruleParentSize = profileArrr[p]->GetInclusionRuleListSize();
		if(  
			(x!=p)
			&& 
			(ruleChildSize > ruleParentSize)
			&&
			( cProfileObject::IsRightRuleSetChildOfLeft(	ruleSetParent,ruleParentSize, ruleSetChild,ruleChildSize)	)
		  )
		{
			isChild[x]=true;
		}
	}

	int newCntOfInIn = 0;
	for(int i = 0 ; i < rschDataAnchor->m_numOfItems ; i++)
	{
		if(isInProffSub[i])
		{
			for(int x = 0 ; (x < numberOfProfiles)&&(isInProffSub[i]);x++)
			{
				if(isChild[x])
				{//7 11 23 777777777777777
					if(profileArrr[x]->IsPatientIncluded( rschDataAnchor->m_twoDimArray[i]))
					{
						isInProffSub[i]=false;
					}
				}
			}
			if(	isInProffSub[i])
			{
				newCntOfInIn++;
			}
		}
	}
	sizeOfProffSub = newCntOfInIn;

	delete []isChild;
	isChild=NULL;
}

	 
void	cResearchObject::MoveSmallStepIfRateAllows( double &rateUsed, double &predictionMixed,	
		double currentPRed     ,double suggestedPRediction,
		double* thresholdArrIn,	double* depAvgArrIn, int* cntAvgArrIn,  double maxRate, int numOfPerfGrps , double anchorVal) //thredArrBase numOfPerfGrps
	{
		int currentIndex = cProfileObject::GetSubGrpIndex(currentPRed, thresholdArrIn, numOfPerfGrps);
	//	double curentDep = depAvgArrIn[currentIndex];

	//	double gap = suggestedPRediction - currentPRed

		int  potentialIndex = cProfileObject::GetSubGrpIndex(suggestedPRediction, thresholdArrIn, numOfPerfGrps);
	
		predictionMixed = currentPRed;
		if(cntAvgArrIn[potentialIndex]>0)
		{
			predictionMixed=	suggestedPRediction;//default is that we get a full rate and 
		}
		rateUsed = 1.0;
		if(potentialIndex > currentIndex)
		{
			if(depAvgArrIn[potentialIndex] < depAvgArrIn[currentIndex])
			{
				//mking sure if i shift to the right i have to get a consistenet higher dep, or if not at least dont change the predition so 
				//no negative loop crated
				predictionMixed = currentPRed;
			}
			int movingIndex = currentIndex+1;
			bool ending=false;
			while(movingIndex <= potentialIndex && !ending)
			{
				if((depAvgArrIn[movingIndex]>  depAvgArrIn[currentIndex]) &&  (cntAvgArrIn[movingIndex]>0 ))
				{
					predictionMixed = thresholdArrIn[movingIndex] - 0.001;
					if(( suggestedPRediction-currentPRed) != 0.0)
					{
						rateUsed = cVarianceCalc::Abs( (predictionMixed-currentPRed) /(  suggestedPRediction-currentPRed));
					}
					ending=true;
				}
				movingIndex++;
			}
		}
		else if(potentialIndex < currentIndex)
		{
			if(depAvgArrIn[potentialIndex] >   depAvgArrIn[currentIndex])
			{
				//mking sure if i shift to the right i have to get a consistenet higher dep, or if not at least dont change the predition so 
				//no negative loop crated
				predictionMixed = currentPRed;
			}
			int movingIndex = currentIndex-1;
			bool ending=false;
			while(movingIndex >= potentialIndex && !ending)
			{
				if((depAvgArrIn[movingIndex]< depAvgArrIn[currentIndex]) &&  (cntAvgArrIn[movingIndex]>0 ))
				{
					predictionMixed = thresholdArrIn[movingIndex] - 0.001;
					if(( suggestedPRediction-currentPRed) != 0.0)
					{
						rateUsed = cVarianceCalc::Abs( (predictionMixed-currentPRed) /(  suggestedPRediction-currentPRed));
					}
					ending=true;
				}
				movingIndex--;
			}
		}
	}


 //6 13 23 *** tuirn this to status and see if compiles
void cResearchObject::FillProfileListObjectsWothAdvancedPerformanceNew2(	cProfileObject** profileArrr,
			int numberOfProfiles,cProfileObject* anchor, cResearchDataObj*   rschDataAnchor,
			cGlobals* globals, int numOfSubGrps,  double depAnchorUnivvv, bool isThisCaseOfAnchorUniverseIn)
{

	for(int p = 0 ; p < numberOfProfiles;p++)
	{
		profileArrr[p]->SetPerformanceToDefault(1.0);
	}
	if(numberOfProfiles<3)
	{
		return;
	}
		 

	//7 11 23 * 55 change small grp to double size to prevent unequal buckets and too much taking from other near by buckets	 
	//change to : int smallGrpSize = globals->g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE*2 ; // instead of nexxt line

	int smallGrpSize = globals->g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE;//7 11 23 * 55 changine frmo bucket sampel size to full profile
	int numOfPerfGrps = rschDataAnchor->m_numOfItems / smallGrpSize;
	numOfPerfGrps  = cVarianceCalc::Max(numOfPerfGrps , 2);
	numOfPerfGrps  = cVarianceCalc::Min(numOfPerfGrps , 20); //7 11 23 * changed frmo 30 to 20

	double anchorvAluee = anchor->GetProfileDepAverage();
	int modePred=0;
	double addedWeightPortion = 1.0;//actually this makes the profile to be 100% more strong
	double multiplerr = 1.25;//ProfileAd dingTest might consider an advancde perofoacne with pow(2) or 3. 
	double stretchArrView[NUMBER_OF_MA_STEPS_PER_ANCHOR];
	bool end = false;
	int cntOfDecreaseingIterations = 0;
	bool isWithDecreasedScores = IS_WITH_DECREASED_SCORES_ML;//7 11 23 * 55
	for(int z = 0 ; z < NUMBER_OF_MA_STEPS_PER_ANCHOR && (!end) ; z++)
	{
		double* predArrAfter = new double[rschDataAnchor->m_numOfItems];	
		double* sumAdvancedPErfWghts =  new double[rschDataAnchor->m_numOfItems];	
		double* predCenterArr = new double[rschDataAnchor->m_numOfItems];
		int modePRed=0.0;
		bool isWithExtremeDimension = false;

		double tierStrucrue[3];
		int numOfTiers = 3;
		profileArrr[0]->Prepare3TierValueAbsoloteMode(tierStrucrue);//profileArr[0] is anchor
	
		double depAvgArrr[100];
		int cntAvgArr[100];
		double thredArrOut[100];
		bool isWithFineTuning=false;//true;
		double endStretchDEbug=ProfileAddingTest(depAvgArrr,cntAvgArr, thredArrOut, predArrAfter,predCenterArr,sumAdvancedPErfWghts, 
			profileArrr ,numberOfProfiles, rschDataAnchor,
			anchorvAluee,  globals, modePRed, numOfPerfGrps,  tierStrucrue,  numOfTiers,  isWithExtremeDimension , isThisCaseOfAnchorUniverseIn  , isWithFineTuning);
		//7 11 23 * 15 add for the call to above function a flag saying no parents 
	 
		double* thredArrBase = new double[numOfPerfGrps];
		double stretchBase =  StretchCalculation(thredArrBase, predArrAfter ,  rschDataAnchor, anchorvAluee, globals,  modePred, numOfPerfGrps, NULL);
		stretchArrView[z] = stretchBase;
		if( (z > 1) && ( stretchArrView[z] <= stretchArrView[z-1]))
		{
			multiplerr = ((multiplerr-1.0) * 0.8)+1.0;
			cntOfDecreaseingIterations++;
			isWithDecreasedScores = false;
			if(cntOfDecreaseingIterations >= 3)
			{
				end = true;
			}
		}
		double hightest = 0.0;
		for(int h=0;h<=z;h++)
		{
			if(stretchArrView[h]>hightest)
			{
				hightest = stretchArrView[h];
			}
		}
		if(  stretchArrView[z]>= hightest )
		{
			cntOfDecreaseingIterations = cVarianceCalc::Min(cntOfDecreaseingIterations , 1);//if we are at pick, the cntOfDecreaseingIterations should come down
		}
		if(!end)
		{//thredArrOut
			ProfSubPErsonAnalytics(  profileArrr,   numberOfProfiles,  rschDataAnchor, predArrAfter,numOfPerfGrps,/* thredArrBase*/ thredArrOut,  modePred, anchorvAluee, 
							stretchBase,   multiplerr,			  globals , depAvgArrr, cntAvgArr,isWithDecreasedScores  , isWithFineTuning );
		}


		/////////////////////

		if(predCenterArr != NULL )
		{
			delete []predCenterArr;
			predCenterArr=NULL;
		}
		if(predArrAfter != NULL)
		{
			delete []predArrAfter;
			predArrAfter=NULL;
		}
		if(sumAdvancedPErfWghts != NULL)
		{
			delete [] sumAdvancedPErfWghts;
			sumAdvancedPErfWghts=NULL;
		}
	
		if(	thredArrBase)
		{
			delete []thredArrBase;
			thredArrBase=NULL;
		}
		
	} 

	

}



double cResearchObject::CalclateAnchorStretch(double* generPrediction, double* profilePrediction,  
	  int numOfPts, double anchorvAluee,  double* depArr, int numOfPerformanceSubGrps, cGlobals* globals, int modePRed)
{
	double strechGenAvg = StretchCalculation(NULL,generPrediction ,  depArr, numOfPts,    anchorvAluee,
	   globals, 		   modePRed,  numOfPerformanceSubGrps, NULL);
	double stretchProfeAvg = StretchCalculation(NULL,profilePrediction ,  depArr, numOfPts,    anchorvAluee,
	   globals, 		   modePRed,  numOfPerformanceSubGrps,NULL);
	double score = stretchProfeAvg  - strechGenAvg;//    
	return score;
 
}		
		///////////////////////////////////////////////////////////////	
	
	




void cResearchObject::ConvertPointsToPredictions(double* predSet, int* grpIndexArr, int numOfStretchGrps, 
	        double* sumPntsArr, double* depArr, bool*  isInAll, int size,  cGlobals*  globals)
{
	
	double* threArr  = new double[numOfStretchGrps]; 
	cProfileObject::CalculateThresholds(threArr,numOfStretchGrps,  sumPntsArr, isInAll, size);
	//double* predArray = 
	double* depAvgArr = new double[numOfStretchGrps]; 
	int* subPopSize = new int[numOfStretchGrps]; 
	double avgDep = 0.0;

	cProfileObject::CreateAvgDepSubGrps(NULL,depAvgArr,threArr,subPopSize,avgDep,numOfStretchGrps, sumPntsArr,
										depArr,       isInAll, size, *globals); 

	for(int i = 0 ; i < size; i++)
	{
		predSet[i]=0.0;
		grpIndexArr[i] = -1;
		if(isInAll == NULL || isInAll[i])
		{
			 int grpIndex = cProfileObject::GetSubGrpIndex( sumPntsArr[i], threArr , numOfStretchGrps);
			 predSet[i] = depAvgArr[grpIndex];
			 grpIndexArr[i] = grpIndex;
		}
	}


	delete []threArr;

	delete []depAvgArr;
	delete []subPopSize;


}

double cResearchObject::ConvertPredictionsToDepAvgBucketsAndCalcStretch(  
	double* threArr, double* depAvgArr, int* subPopSize, double &avgDep,
	
	double* predSet,double* depArr, bool* isIn,
	                    int size,         int numOfStretchGrps , cGlobals* globals, double* givenThreshold)
{
	//threArr  = new double[numOfStretchGrps]; 

	if(givenThreshold != NULL)
	{
		for(int x = 0 ; x < numOfStretchGrps; x++)
		{
			threArr[x] = givenThreshold[x];
		}
	}
	else
	{
		cProfileObject::CalculateThresholds(threArr,numOfStretchGrps,  predSet, isIn, size);
	}
	//double* predArray = 
	//depAvgArr = new double[numOfStretchGrps]; 
	//subPopSize = new int[numOfStretchGrps]; 
	avgDep = 0.0;

	cProfileObject::CreateAvgDepSubGrps(NULL,depAvgArr,threArr,subPopSize,avgDep,numOfStretchGrps, predSet,
										depArr,       isIn, size, *globals); 

	double stretch =  CalculateStreth(depAvgArr,subPopSize,avgDep, numOfStretchGrps);
	//delete []threArr;
	//delete []depAvgArr;
	//delete []subPopSize;

	return stretch;

}

 
void cResearchObject::BuildResearchElementsWhileLoop(
	cProfileObject** tempProfileArr,int &profileMovingIndex,
	cResearchDataObj* researchDataObj,  
	InputVariablesPackageForResearchObj* inputVarObj ,  cGlobals &globals, 	int maxItneration, int  maxNmberOfProfiles,
	//cVariableAndValueAndPoints* inclusionRulesSet,   int sizeOfEachInclusionSet,
	cProfileObject* anchor,	cPercentileCalculationModel* rootOddPredictiveModel,
	cPercentileCalculationModel* regPredictiveModell, double depUnivv, int maxNiumOfRuleToAchive)
{//7 6 23 depUnivv does not get used. anchor only get used by serving the anchor id, and something lese which is not used. change
	bool end = false;
	int counter = 0;//move up to maxItneration
//	profileMovingIndex=0;//move up to maxNmberOfProfiles
	bool isEndOfProfileList = false;
	bool* isAlreadyWon =  new bool[maxNmberOfProfiles];
	bool* isTerminal = new bool[maxNmberOfProfiles];
	for(int i = 0 ; i < maxNmberOfProfiles ; i++)
	{
		isAlreadyWon[i]=false;
		isTerminal[i]=false;
	}

	while(!end)//5 20 23 find where do we cancel profiles unde certein sample befoe they get here to be added
	{
		cout << "one iteration start \n ";
		cout << counter;
		cout << "\n";
		cout << "number of profiles at start loop \n ";
	//	cout<<m_profileListSize;
		cout << "\n";
		int* profileSizedGrpIdentfier = new int[profileMovingIndex];
		for(int i = 0 ; i < profileMovingIndex;i++)
		{
			profileSizedGrpIdentfier[i] = -1;
		}
		int maxSizeOfProfileGrp = globals.g_SIZE_OF_PROFILE_SIZED_GROUP_FOR_COMPETING_EVOLUTION;//define 
		int numOfGroups = 0;
		IdentifyEachProfileWithItsGroupsIdentfier( profileSizedGrpIdentfier, 
			numOfGroups,  maxSizeOfProfileGrp, globals, tempProfileArr, profileMovingIndex);

			//////////////////11 24 22 //
			/*
			from each group, numOfGroups is retrend, take 3 or 4 winners - one profile that has most extreem sub group buckoet 
			on the left, same on the right, and one that has most changes as you go along the inclusion rule set and that 
			shows perhaps contradicting direction .in a way left or right are also a result of profie mean shift. only somtimes
			shifts happen in differnet direction.
			 
			3-each profile when compelting to the 3 winners of the sized group will get a list of sum of var fources, once in absolute
			and once with direction. the winner can be max absolute, max right shoft directional, min let shift directional. when adding 
			shifts on the absoute maybe we need to look at the  root units to not add the same units 

			*/
		int* listOfWinnerIndexes = new int[profileMovingIndex];
		int winnerIndexsMovingIndex = 0;


		for(int g = 0 ; g < numOfGroups ; g++)
		{

			cout<< "number of grouops and index \n ";
			cout<<numOfGroups;
			cout<< "  \n ";
			cout<<g;
			cout<< "  \n ";
			if(g< 0)
			{
				int sdg=0;
			}
			//fofr group g i will see whi is in such group  
			bool* isIn = new bool[profileMovingIndex];
			for(int ii = 0 ; ii< profileMovingIndex; ii++)
			{
				isIn[ii] = false;
				if(profileSizedGrpIdentfier[ii] == g)
				{
					isIn[ii] = true;
				}
			}
			//will go voer m_profileListSize optoins and per isIn true make a competion and selet one ore more
			int indexOfWinnerLeft = -1;
			int indexOfWinnerRight = -1;
			int indexOfWinnerAbs = -1;
		//	int parentRuleLegnt = 
		//	int currentRule = parentRuleLegnt+1;
			FindWinnersFromDifferentTypes(indexOfWinnerLeft, indexOfWinnerRight, indexOfWinnerAbs,
				isIn, isAlreadyWon,  isTerminal, tempProfileArr, profileMovingIndex, maxNiumOfRuleToAchive );//7 6 23 add an input max iclusion  rulse w hic will be base plus change
			   //that allows in t his function. the input will then be sent to this FindWinner function in the end and have no winner found from more than 
			//that input rule size max length. it allows to inclurease the counter as much as needed and h ave a mroe symetric method
			if(indexOfWinnerLeft >= 0)
			{
				listOfWinnerIndexes[winnerIndexsMovingIndex++] =indexOfWinnerLeft;
				isAlreadyWon[indexOfWinnerLeft]=true;
			} 
			if( (indexOfWinnerRight >= 0 ))//no need, checked in FindWinner() ://  && (indexOfWinnerRight != indexOfWinnerLeft) )
			{
				listOfWinnerIndexes[winnerIndexsMovingIndex++] = indexOfWinnerRight;
				isAlreadyWon[indexOfWinnerRight]=true;
			}
			if((indexOfWinnerAbs >= 0 ) )//no need also here: && (indexOfWinnerAbs != indexOfWinnerLeft) && (indexOfWinnerAbs  != indexOfWinnerRight))
			{
				listOfWinnerIndexes[winnerIndexsMovingIndex++] = indexOfWinnerAbs;
				isAlreadyWon[indexOfWinnerAbs]=true;
			}

			delete []isIn;
			isIn=NULL;
		}
		int numOfNewProfilesCreatePerOneIter = 0;
		for(int ii = 0 ;( (ii< winnerIndexsMovingIndex) && (!isEndOfProfileList)) ; ii++)
		{
			cout<< " num of winners  and index \n ";
			cout<<winnerIndexsMovingIndex;
			cout<< "  \n ";
			cout<< ii;
			cout<< "  \n ";

			int numOfChildren = 0;
			cProfileObject** chldProfArr = NULL;//
			//crate new profiles should include all you need including the regression adustment objects
			//and all that i can find below to make a list of childrenr under this profile 
			cProfileObject* thisProfile = NULL;
			if(tempProfileArr[	listOfWinnerIndexes[ii]] != NULL)
			{//tempProfileArr, profileMovingIndex
				thisProfile = tempProfileArr[	listOfWinnerIndexes[ii]] ;

				bool isCreated = CrerateNewChildProfilesToThisProfile(chldProfArr,numOfChildren, thisProfile, rootOddPredictiveModel,
					regPredictiveModell,  researchDataObj,  inputVarObj, globals, anchor,	tempProfileArr, profileMovingIndex  );
//3 16 24 added "tempProfileArr" anchor/branch list of all profiles created so far andn their number to only create uniquie profiles moving forwad
				int cntOFactualCreated = 0; //it could be that isCreatedIncludes only created unique but too small of profils to fill them. 
			/*
				for(int k = 1 ; k < numOfChildren ; k++)
				{
					if(chldProfArr[k]!=NULL)
					{
						bool isProffFound = IsProfileFound(chldProfArr, k  ,chldProfArr[k]);
						if(isProffFound)
						{
							delete chldProfArr[k];
							chldProfArr[k]=NULL;
						}
					}
				}*/
				cout<< "Before isCreated if. num of children :\n";
				
				if(isCreated)
				{
					cout << numOfChildren;
					for(int iii = 0 ; iii < numOfChildren ; iii++)
					{
						cout<< "child index :\n";
						cout<<iii;
						cout<< "\n";
				
						if(chldProfArr[iii] != NULL)
						{
							if(profileMovingIndex < maxNmberOfProfiles)//maxNmberOfProfiles
							{
								cProfileObject* sp = chldProfArr[iii];
								sp->SetProfileID(   m_profileListSize +profileMovingIndex);
								tempProfileArr[profileMovingIndex++] =sp;
								cntOFactualCreated++;
								//12 2 22 find how to add the porpensiey info here and 
								sp->SetInterventionMembers(inputVarObj->m_isIntervention, inputVarObj->m_indexOfPropIntervention,
														 researchDataObj->m_sizeOfItem);
								
								cout<< "123456  \n";
								chldProfArr[iii]->DeleteIsInProfile();
								cout<< "654321 \n";
							
							}
							else
							{
								delete chldProfArr[iii];
								chldProfArr[iii] = NULL;
								isEndOfProfileList = true;
							}
						}
					}
					if(chldProfArr != NULL)
					{
						delete []chldProfArr;
						chldProfArr=NULL;
					}
				}

				cout<< "after  isCreated if.  \n";
				if(  (!isCreated) ||( cntOFactualCreated==0   ))
				{
					isTerminal[listOfWinnerIndexes[ii]]=true;
				}
				numOfNewProfilesCreatePerOneIter += cntOFactualCreated;

				cout<< "after  isCreated if  2.  \n";
			}
		}

		cout<< "vvvvvvvvvv.  \n";
		delete []profileSizedGrpIdentfier;
		profileSizedGrpIdentfier=NULL;

		delete []listOfWinnerIndexes;
		listOfWinnerIndexes=NULL;
	//	delete []profileSizedGrpIdentfier;
		//profileSizedGrpIdentfier=NULL;

		counter++;
		if(counter >= maxItneration)// globals.g_MAX_NUM_OF_ITERATIONS) //future it will be large number and with breaks for 
			//learning using a long version of performance analytics. now it will start small
			//and grow
		{
			end = true;
		}
		if(numOfNewProfilesCreatePerOneIter == 0)// in this iteration through all groups and all winners per group, none was able to get any child
			//into the list than of course need to stop. shouold only happen in a narrow case scenario with no so many varible value options
		{
			int ddg =0;
		//	end = true;//this does not mean end, can be we selected 3 winners per certain group or all   gruops here, 
			//with no enough sample or something for all, yet there is a chance for other but very small.
			//why need to try selct others next iteration
		}
		if(isEndOfProfileList)
		{
			end = true;
		}
		for(int i=0; i <  profileMovingIndex ; i++)
		{// 
			if(tempProfileArr[i]==NULL)
			{
				cout<<"empty profile \n";
				cout<< i;
				cout<<"profile size  \n";
				cout<< tempProfileArr;
				cout<<"  \n";
			}
		}

		cout<< "end of loop iteration  \n";
	}
	delete [] isAlreadyWon ;
	isAlreadyWon=NULL;
	delete [] isTerminal ;
	isTerminal=NULL;
}





//10 24 22 add a parameter that deals with how to test performance. one mode is fo root is to j ust set ot to nutural. another mode if for a simple
//performance test when you take the profile population cut in half and compare with the root model which model gives bette predictions for a test populatiot that
//is actully the same as the profile we messure. another option for performacne is for a cmopare with all parents as comparing each like we do with root
//but this is actually in addition and some cases a model is good but not more than the parents. a profile with x y z, where each is a var/val inclduiong
//rule, has a parent of x y, and a parent of x z and y z. when adding a child to x y making an x y z we will check if it is not already there and if it is
//we are not adding, regardless, when we do performacne we want to see that x y z is helping comparing to all parients, else a person that is an x y z
//mighht better go to x y or y z or x z  for a prediction . we do want to provide for all performacne options score for each bucket of test patients 
//using such copare and even if the buckets of test are not getting same hit in the model bucket of parents or root, it could be that all our 5 equal
//buckets on the profile test side hit mostly the higher risk buckets on the parent profile or root profile, yet the score is  how did we do getting these 
//test patient in bucket B get their predictions 10 24 22 need to move all the performacne checkk out of this function to the calling one

//11 3 22 add before effort to do the mode, add the check of sample size and if not jusst keep the profilei mean and think how to do another appraoch to the perforamcne
void  cResearchObject::PRepareModelAndAdjustPErRootRegreMOdel(
	cPercentileCalculationModel*& rootOddPredictiveModel, 
		cPercentileCalculationModel*& regPredictiveModell, cProfileObject* profile ,  cGlobals &globals )
{
	profile->PrepareModel( globals );
	
	//10 20 22 open percentile logic, one instance for odd and one forr regression, all to later below adjust the odd. move al this
	//to be a function of reserach object so the construccture is cleaner
	//the first 3 next lines will stay. then the creataion of regression percetntila will move to a function. then
	//the adjustment will remain. so a 
	int numOFCategoriesForPercLogic = globals.g_NUM_OF_CATG_PERCENTILE_MERGE;
	if(rootOddPredictiveModel == NULL)
	{//sending "profile" as input is probably going to be only ROOT profile , when rootOddPredictiveModel  == NULL. 
		//same for regresion predictive mode below. potentially if needed it can also  be used otherwise 
		rootOddPredictiveModel=new cPercentileCalculationModel(profile,numOFCategoriesForPercLogic);
		rootOddPredictiveModel->Analytics();
	}
	if(regPredictiveModell == NULL)
	{//see comment aabove for the input "profile" which is representing root only when the iput is NULL entering this if
		AdjustRegresionListToSizeAndCreatePercentileObjectForRegre(
			regPredictiveModell, numOFCategoriesForPercLogic , rootOddPredictiveModel,profile);
	}
	profile->SetAdjustedOddModel(rootOddPredictiveModel, regPredictiveModell);
	//10 20 22 between 
	profile->CompleteModel( globals );
	 

}





cResearchObject::~cResearchObject()
	{
		if(m_profileObjectPtrList != NULL)
		{
			for(int i = 0 ; i < m_profileListSize ; i++)
			{
				delete m_profileObjectPtrList[i];
			}
			delete []m_profileObjectPtrList;
		}
		if(m_schemaArrr != NULL)
		{
			delete []m_schemaArrr;
		}
		if(m_guidedInclusionRuleList != NULL)
		{
			delete []m_guidedInclusionRuleList;
		}
		if( m_logisticRegressionVarAndPoints != NULL)
		{
			delete []m_guidedInclusionRuleList;
		}
	}

	
	void	cResearchObject::FillIsInProfileForEval(bool* isProfileIn, int testRunMode , cGlobals &globals )
	{
		if(testRunMode == globals.g_ONLY_ROOT_PREDIC_MODE )
		{
			isProfileIn[0]=true;
			for(int i = 1 ; i < m_profileListSize ; i++)
			{
				isProfileIn[i] = false;
			}
		}
		if(testRunMode == globals.g_ONLY_WP3_EXACT_MULTI_VALUE_PATN_CATEGORY )//5 31 23 add aks only 1-8 profiles?
		{
			isProfileIn[0]=true;
			for(int i = 1 ; i < m_profileListSize ; i++)
			{
				isProfileIn[i] = false;
				if(	m_profileObjectPtrList[i]->GetInclusionRuleListSize() == 1)
				{
					for(int x = 0 ; x < m_guidedInclusionsRuleListSize ; x++)
					{
						int var = m_guidedInclusionRuleList[x].m_variableIndex;
						double val = m_guidedInclusionRuleList[x].m_value;
						if( var == m_profileObjectPtrList[i]->GetInclusionRuleList()[0].m_variableIndex )
						{
							if(val == m_profileObjectPtrList[i]->GetInclusionRuleList()[0].m_value)
							{
								isProfileIn[i] = true;	
							}
						}
						//IsVarValExactMatch
					}
				}
			}
		}
		if(  testRunMode  ==  globals.g_ONLY_WP3_INCLUDED_IN_PATN_CATEGORY)//6 9 23 try this fix with the 1-8
		{
			isProfileIn[0]=true;
			for(int i = 1 ; i < m_profileListSize ; i++)
			{
				isProfileIn[i] = false;
				for(int x = 0 ; x < m_guidedInclusionsRuleListSize ; x++)
				{
					int var = m_guidedInclusionRuleList[x].m_variableIndex;
					double val = m_guidedInclusionRuleList[x].m_value;
					if(	m_profileObjectPtrList[i]->IsVarValIncludedInInclusionRuleSet(var,val))
					{
						isProfileIn[i]=true;
					}
				}
			}
		}
		if( testRunMode  == globals.g_ONLY_NON_WP3_PROFILES )
		{
			isProfileIn[0]=true;
			for(int i = 1 ; i < m_profileListSize ; i++)
			{
				isProfileIn[i] = true;
				for(int x = 0 ; x < m_guidedInclusionsRuleListSize ; x++)
				{
					int var = m_guidedInclusionRuleList[x].m_variableIndex;
					double val = m_guidedInclusionRuleList[x].m_value;
					if(	m_profileObjectPtrList[i]->IsVarValIncludedInInclusionRuleSet(var,val))
					{
						isProfileIn[i]=false;
					}
				}
			}
		}
		if(  testRunMode  == globals.g_ALL_PROFILES_CANDIDATES )
		{
			for(int i = 0 ; i < m_profileListSize ; i++)
			{
				isProfileIn[i] = true;
			}		
		}
	}




int	cResearchObject::GetTierLevelPrediction3levels(double prediction, double anchor, double* tierStrucrue )
{
	int tier = 2; //defcault, weakest when doing 3 tier
	double shift = cVarianceCalc::Abs( prediction - anchor);
	if(shift >=  tierStrucrue[1])
	{
		tier = cVarianceCalc::Min(tier , 1);
	}
	if(shift >=  tierStrucrue[0])
	{
		tier = cVarianceCalc::Min(tier , 0);
	}
	return tier;
}	
//7 5 23  improve te functin so that below if prediction is lower than anchor gets a boost simlar to who 10 to 9 is a 0.9 odd or 1/0.9 abs value andn 
//10 to 11 up is 1.1 odd which is less than 1/0.9 even that moved in both cases 1% away fromo 10
double cResearchObject::GetExtremePredictionWght(double prediction, double anchor, double* tierStructure,  int numOfTiers )
{
	double largeRange = tierStructure[0] + tierStructure[1] ;
	double stretch = cVarianceCalc::Abs(prediction - anchor);
	double rate = stretch / largeRange;
	rate =  cVarianceCalc::Min(rate , 1.0);
	return rate;
}


cProfileObject* cResearchObject::FindWhichIsAnchor(cProfileObject**  profileListPtr,int listSize,bool* isPSPs,int numOfPSPs)
{
	cProfileObject* anchor = NULL;
	for(int p = 0 ; p < listSize ; p++)
	{
		if(isPSPs[p])
		{
			if( profileListPtr[p]->IsAnchor())
			{
				 return profileListPtr[p];
			}
		}
	}
	return NULL;//shoult not be here since when a profile matchs a person the anchor is also in isPSPs[] due struc inclsion definition
}

double cResearchObject::CalculateAvgPredictWithExtremetPredictionFocus2(cProfileObject** profileListPtr, int  listSize,
					double* predArr,double* wghArr, bool* isPSPs,int numOfPSPs, bool isThisCaseOfAnchorUniverseIn)
{
	double max = 0.0;
	for(int i = 0 ; i < listSize;i++)
	{
		if(isPSPs[i])
		{
			max = cVarianceCalc::Max(max , wghArr[i]);
		}
	}

	for(int i = 0 ; i < listSize;i++)
	{
		if(isPSPs[i])
		{
			if( wghArr[i] < max)
			{
				isPSPs[i]=false;
			}
		}
	}
	double summmWgh=0.0;
	double preeedi=0.0;
	for(int i = 0 ; i < listSize;i++)
	{
		if(isPSPs[i])
		
		{
			preeedi += predArr[i] *  wghArr[i];
			summmWgh += wghArr[i];
		}
	}
	if(summmWgh > 0.0)
	{
		preeedi /= summmWgh;
	}
 
	return preeedi;
}
	

double cResearchObject::CalculateAvgPredictWithExtremetPredictionFocus(cProfileObject** profileListPtr, int  listSize,
					double* predArr,double* wghArr, bool* isPSPs,int numOfPSPs, bool isThisCaseOfAnchorUniverseIn)
{
	//collect anchor
	double tierStrucrue[3];
	int numOfTiers = 3;
	//6 23 23 consider this as a way to check if a local strech with universe is better for a univers test than multipe local anchors
	//6 23 23    7 5 23  see how finding which is anchor might change here if we allow parient ancahors, it does not matter if we chose the anchor and then here
	cProfileObject* anchorProf = FindWhichIsAnchor(  profileListPtr, listSize, isPSPs, numOfPSPs);
	if(anchorProf == NULL)
	{
		anchorProf = profileListPtr[0];
	}
	if(IS_ANCHOR_UNIVERSE_CROSS_ANCHORS  && isThisCaseOfAnchorUniverseIn)
	{
		if(anchorProf->GetRootProfile() != NULL)
		{
			anchorProf = anchorProf->GetRootProfile();
		}
	}

	anchorProf->Prepare3TierValueAbsoloteMode(tierStrucrue);//profileArr[0] is anchor - check in debug time
	double anchor =  anchorProf->GetProfileDepAverage();
	//tier 0 is the highers, then tier 1, then 2
	//double shift = cVarianceCalc::Abs( prediction - profileListPtr[0]->GetProfileDepAverage());//anchor
	int mostExtremeTier = 2;//from a 3 options, 2 is low, 1, mid, and tier 0 is best
	double* extremWghArr= new double[listSize];
	for( int p = 0 ; p < listSize ; p++)
	{
		extremWghArr[p]=0.0;
		if(isPSPs[p])
		{
		//	int tier = GetTierLevelPrediction3levels(predArr[p],   anchor,tierStrucrue );
		//	mostExtremeTier = cVarianceCalc::Min(mostExtremeTier, tier);
			double anchorHere = anchor;
		//	if(IS_ANCHOR_UNIVERSE_CROSS_ANCHORS)
		//	{
		//		if(anchorProf->GetRootProfile() != NULL)
		//		{
		//			anchorHere = anchorProf->GetRootProfile()->GetProfileDepAverage();
		//		}
		//	}
			extremWghArr[p] = GetExtremePredictionWght(predArr[p],   anchorHere,tierStrucrue,numOfTiers );
		}
	}

	double  avgPred = 0.0;
	double sumWghts = 0.0;
	for( int p = 0 ; p < listSize ; p++)
	{
		if(isPSPs[p])
		{
		//	int tier = GetTierLevelPrediction3levels(predArr[p],   anchor,tierStrucrue );
		//	if(tier <=  mostExtremeTier)
			{//7 6 23  i multiplpe extreme with how good the profile was in an nextreme. i can be that this is n ot an extreme cse but getting a perf score due to being good either as is ior due to some cases of sub grops that made this profile 
				double wgh = wghArr[p] * extremWghArr[p] ;
				avgPred +=  (wgh * predArr[p]);
				sumWghts  += wgh;
			}
		}
	}
	if(sumWghts > 0.0)
	{
		avgPred /= sumWghts;
	}

	delete []extremWghArr;
	return avgPred;
}
		


void cResearchObject::CleanPSPsThatAreParentsToOtherrPSPs(bool* isPSPs , cProfileObject** profileObjectPtrList , int profileListSize)
{//1 20 24 changedn i=0to i=1. check that indeed i=0  is the anchor
	for(int i=1; i < profileListSize ; i++)
	{
		if(isPSPs[i])
		{
			cVariableAndValueAndPoints* ruleSetI = profileObjectPtrList[i]->GetInclusionRuleList();
			int ruleSetSizeI = profileObjectPtrList[i]->GetInclusionRuleListSize();
			for(int ii=0;  (ii < profileListSize )&&(isPSPs[i]) ; ii++)
			{
				if(  (i!=ii) &&  isPSPs[ii])
				{
					//if both i and ii are candidates, if ii is a child of i we remove i
					cVariableAndValueAndPoints* ruleSetII = 
						profileObjectPtrList[ii]->GetInclusionRuleList();
					int ruleSetSizeII = profileObjectPtrList[ii]->GetInclusionRuleListSize();
					if( cProfileObject::IsRightRuleSetChildOfLeft(
									ruleSetI,ruleSetSizeI, ruleSetII,ruleSetSizeII))
					{
						isPSPs[i] = false;
					}
				}
			}	
		}
	}
}
		

	//fill isPSPs array with true only for profiles that are exact match to the person
	//do not consider a profile that is not true in isProfileIn
	void cResearchObject::CollectPSPsForOnePatient(
		bool* isPSPs, int &numfOfPSPs, double* ptArr,bool* isProfileIn, cProfileObject** profileArr, int profileArrSize, bool isToAllowIncludingZeroWeight)
	{
		numfOfPSPs=0;
		for(int i=0; i <  profileArrSize ; i++)
		{
			isPSPs[i]=false;
			if(isProfileIn[i])
			{
				cProfileObject* prf =  profileArr[i];
				bool isMatch = true;
				cVariableAndValueAndPoints* incRuleSet = prf->GetInclusionRuleList();
				int ruleSetSize= prf->GetInclusionRuleListSize();
				for(int r = 0 ; r< ruleSetSize ; r++)
				{
					int ruleVar =  	incRuleSet[r].m_variableIndex;
					double ruleValue = incRuleSet[r].m_value;
					double ptnValue = ptArr[ruleVar];
					if(ptnValue != ruleValue)
					{
						isMatch=false;//enough one time for no match to have a false
					}
				}

				 //we dont know for sure yet if the bucket of the person is non zero and since we dont know the bucket yet so keep it false
				bool isBucketPerfScorePositive = false;
				//so we need to check
				bool needToCheck = true;
				//but if we know that all buckets are zero than we can keep the fasle.
				if(prf->AreAllBucketsZero())
				{
					needToCheck = false;
					isBucketPerfScorePositive =  false;//re confirm the fasle
				}
				if(prf->AreAllBucketsNonZero())
				{
					needToCheck = false;
					isBucketPerfScorePositive =  true;
				}
				if(needToCheck )
				{
					double scaleSum = 0.0;
					prf->GetPatientScaleValue( scaleSum, ptArr);
					int subGrpIndex = -1;
				//	profileID = m_profileID;
				//	GetPredictedValuesFromScaleVAlue 
					double prediction=0.0;
					prf->GetPredictedValuesFromScaleVAlueWithFineTuning	(prediction, subGrpIndex, scaleSum ,false);
					isBucketPerfScorePositive = (prf->GetSubGrpPerformanceAdvancedArray()[subGrpIndex]) >0.0 ;
				}
				//if all buckts are zero than need to match the profile if isMatch since it means we are not in the stage of scores set yet
				//later once we do have need of scores and develop advanced performance scores we remove a profile if it is all zeroes
				
				//bool doAllowIncludingZeroWeight is input means if true than even if bucket is not p ositive 
				bool isValid = isBucketPerfScorePositive || isToAllowIncludingZeroWeight;// (
				if(isToAllowIncludingZeroWeight == false)
				{
					int sg=0;
				}
				if(!isBucketPerfScorePositive)
				{
					int sg=0;
				}
				if(!isValid)
				{
					int sg=0;
				}
				if((isValid )  && isMatch)
				{
					isPSPs[i]=true;
					numfOfPSPs++;
				}
			}
		}
	}
			


/*
void cResearchObject::PredictRaws(
	double* predArr, double* predArrWI, double* predArrWOI,
	     cPredictionContextObj** predictionContextObjArray, int* sizeOfPredContObj,
	double** twoDimArr,  int size, int numOffVars, int testRunMode, double* evolutionPredictionArr, 
	bool isAdvancedPerfGetbEstMatch , 		
	int interventionFieldForPredictionVariations,  cGlobals &globals, bool isWithFineTuning )
{
	//
	for(int i = 0 ; i < size ; i++)
	{
	//	predictionContextObjArray[i]=NULL;
	//	sizeOfPredContObj[i] = 0;
		if((evolutionPredictionArr == NULL) || (evolutionPredictionArr[i] == 0.0 ))
		{
			bool* isProfileIn = new bool[m_profileListSize];
			for(int p=0; p < m_profileListSize ; p++)
			{
				isProfileIn [p] = true;	
			}
		//er rthe iput test run mode, a specific uttn of the isProfileIn array isi prepared and allows different tests to be condoucted
			FillIsInProfileForEval(isProfileIn, testRunMode , globals );
			predArr[i]=0.0; 
			bool* isPSPs = new bool[m_profileListSize];
			for(int p=0; p < m_profileListSize ; p++)
			{
				isPSPs [p] = false;
			}
			int numfOfPSPs = 0;
				//fill isPSPs array with true only for profiles that are exact match to the person 
			CollectPSPs ForOnePatient(isPSPs, numfOfPSPs,twoDimArr[i],isProfileIn);
			//CleanPSPsThatAreParentsToOtherrPSPs(isPSPs);//5 31 23 remove this line andn

			int finalNumOfPSPs = 0;
			for(int p=0; p < m_profileListSize ; p++)
			{
				if(isPSPs [p])
				{
					finalNumOfPSPs++;
				}
			}
			if((predictionContextObjArray != NULL) &&  (finalNumOfPSPs > 0))
			{
				predictionContextObjArray[i]= new cPredictionContextObj[finalNumOfPSPs];
				sizeOfPredContObj[i] = finalNumOfPSPs;
			}

			double avgPReStr=0.0;
			double sumWghtsReg = 0.0;
			double avgPredReg= 0.0;
			double avgPredWithInReg = 0.0;//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
			double avgPredWithoutInReg = 0.0;
			double sumWghtsAdv = 0.0;
			double avgPredAdv = 0.0;
			double avgPredWithInAdv = 0.0;//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
			double avgPredWithoutInAdv = 0.0;
			
			int movingPRedCpontextObjIndex = 0;
			for(int p=0; p < m_profileListSize ; p++)
			{
				if(isPSPs [p])
				{
					double prediction = 0.0;
					//double performance = 0.0;
					double performanceReg=0.0;
					double performanceAdv=0.0;
					double predictionWithInterv=0.0;
					double preditionWitoutInterv=0.0;
			//12 2 22 **** 
					//1-profileID, subGrpIndex add these as output from PredictionElementsNEW
					//2- add flexible is in profile
					//3 do a new file path for the calibration report and not same performacne
					
					int profileID = -1;
					int subGrpIndex = -1;
					m_profileObjectPtrList[p]->PredictionElementsNEW( prediction , predictionWithInterv,
						preditionWitoutInterv, performanceReg ,performanceAdv,
						profileID,subGrpIndex,	twoDimArr[i], numOffVars, isAdvancedPerfGetbEstMatch ,
						interventionFieldForPredictionVariations, globals,  isWithFineTuning);
					//if(performance == globals.g_STRENGTH_MULT_OF_LONG_STRETCHED_PROFILE)
					//{//only in processing time in case of long stretch tests
						//so it means we want to have this profile take over all wieght, andn a max weight is 
				//	double minScore = 0.000000001;
				//	if(m_profileObjectPtrList[p]->GetSubBucketCntArr()[subGrpIndex] > 300)
						//5 31 23 change both 200 above and 5 below to onfig. 
					//{
						performanceAdv = cVarianceCalc::Max(performanceAdv , 0.0);
						performanceAdv = pow(performanceAdv,5);
					//	performanceAdv = cVarianceCalc::Max(performanceAdv , minScore);//5 31 23 check that most scores
						//even after power(5) are more than the detault min score .
					//}
					//else//if the issue was the sample,  add in the else a way to compensatet and not just jump to min score
					//{
					//	performanceAdv =minScore;
					//}
				//	else if(  globals.g_IS_PERF_WEGIHT_FOR_BEST_MATCH_MERGE_POWER_BY_2)
				//	{
				//		performance *= performance;
				//	}
					avgPredReg += (prediction * performanceReg);
					avgPredWithInReg  += (predictionWithInterv * performanceReg);
					avgPredWithoutInReg  += (preditionWitoutInterv * performanceReg);
					sumWghtsReg += performanceReg;//wgh;
					avgPredAdv += (prediction * performanceAdv);
					avgPredWithInAdv  += (predictionWithInterv * performanceAdv);
					avgPredWithoutInAdv  += (preditionWitoutInterv * performanceAdv);
					sumWghtsAdv += performanceAdv;

					if((predictionContextObjArray != NULL) && 	(sizeOfPredContObj[i] > 0))
					{
						predictionContextObjArray[i][movingPRedCpontextObjIndex++].SetObject(
						 profileID, subGrpIndex, prediction, predictionWithInterv , 
						 preditionWitoutInterv, performanceAdv);
					}
				}
			}
			if(    isAdvancedPerfGetbEstMatch      &&     (sumWghtsAdv > 0.0)   )
			{
				avgPredAdv  /=  sumWghtsAdv;
				avgPredWithInAdv /=  sumWghtsAdv;
				avgPredWithoutInAdv /=  sumWghtsAdv;
				predArr[i] = avgPredAdv;

			}
			else if(sumWghtsReg > 0.0)
			{
				avgPredReg  /=  sumWghtsReg;
				avgPredWithInReg /=  sumWghtsReg;
				avgPredWithoutInReg /=  sumWghtsReg;
				predArr[i] = avgPredReg;				
			}
			delete []isPSPs ;
			isPSPs =NULL;
			delete []isProfileIn;
			isProfileIn=NULL;
		}
		else
		{
			predArr[i] = evolutionPredictionArr[i];
		}
	}
}
*/
//6 8 23 add output list of tier 1 proifles only 
//the input patinet its list of isps and their subGrpIndex relates the person, their prediction and performanceAdv
//then i can have a patient relats to list of isps and provide the rage as the gap between two extem predictions in the output
//we then combine an average range and calling atain i give a list of profiles set to tohet perfo regression
//in the second call after leanring i add this to the perf regrssion and 
void cResearchObject::ASDFGH(double &avgPReStr,	double &sumWghts ,	double &avgPredWghted,
			double &avgPredWithIn ,//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
			double &avgPredWithoutIn,
			bool* isPSPs,double** twoDimArr,int persIndex,
			 int  numOffVars, bool isAdvancedPerfGetbEstMatch ,
					int	interventionFieldForPredictionVariations,  cGlobals* globals, bool isWithFineTuning,
					double strePRed, double deltaa,
					cPredictionContextObj** predictionContextObjArray,
					int* sizeOfPredContObj, bool isStragiht 	)
{
	avgPReStr = 0.0;
	sumWghts = 0.0;
	double sumWghtsStr = 0.0;
	avgPredWghted = 0.0;
	avgPredWithIn = 0.0;//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
	avgPredWithoutIn = 0.0;
	int cnt =0;		
	int movingPRedCpontextObjIndex = 0;

	double hightestPredWeight = 0.0;
	double predicWithHighestWeight = 0.0;
	for(int p=0; p < m_profileListSize ; p++)
	{
		if(isPSPs [p])
		{
			double prediction = 0.0;
					//double performance = 0.0;
			double performanceReg=0.0;
			double performanceAdvv=0.0;
		//	double prefrExtreme = 0.0;
			//double prediExtreme=0.0;
			double predictionWithInterv=0.0;
			double preditionWitoutInterv=0.0;
			//12 2 22 **** 
					//1-profileID, subGrpIndex add these as output from PredictionElementsNEW
					//2- add flexible is in profile
					//3 do a new file path for the calibration report and not same performacne
					
			int profileID = -1;
			int subGrpIndex = -1;
			m_profileObjectPtrList[p]->PredictionElementsNEW( prediction , predictionWithInterv,
						preditionWitoutInterv, performanceReg ,performanceAdvv,
						profileID,subGrpIndex,	twoDimArr[persIndex], numOffVars, isAdvancedPerfGetbEstMatch ,
						interventionFieldForPredictionVariations, *globals,  isWithFineTuning);
			double minScore = 0.000000001;

			double complexWeight =m_profileObjectPtrList[p]->GetAvgPopGapWhenBestMatch()[subGrpIndex] ;
			//6 9 23 changed 1 to 0.5.
		//	complexWeight = pow(complexWeight,0.5);//6 9 23 - test this 0.5, the 3.0, and test removing parents from best matmch
			complexWeight = cVarianceCalc::Max(  complexWeight,  minScore);//in case is the ROOT and there is no other match it has to have a score
			performanceAdvv = cVarianceCalc::Max(performanceAdvv , minScore);//performoanceAdv can also be negative if not found important
			performanceAdvv = pow(performanceAdvv,3.0);//6 9 23 cnanged 2.0 to 3.0 check 1:31
			complexWeight *=performanceAdvv;
			complexWeight = cVarianceCalc::Max(  complexWeight,  minScore);
			complexWeight = pow(complexWeight, 1.0);// some way to proxi a max weight func or tier 1
			if(complexWeight >  hightestPredWeight )
			{
				predicWithHighestWeight = prediction;
				hightestPredWeight = complexWeight;
			}
			
			
			if(isStragiht)
			{
				complexWeight = 1.0;//6 11 23
			}
			
			
			avgPReStr += complexWeight*prediction;
			sumWghts += complexWeight;
			avgPredWghted += complexWeight * prediction;
			avgPredWithIn += complexWeight * prediction;//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
			avgPredWithoutIn += complexWeight * prediction;
			cnt++;
			if((predictionContextObjArray != NULL) && 	(sizeOfPredContObj[persIndex] > 0))
			{
					predictionContextObjArray[persIndex][movingPRedCpontextObjIndex++].SetObject(
					 profileID, subGrpIndex, prediction, predictionWithInterv , 
					 preditionWitoutInterv, complexWeight);//performanceAdvv);
		
			}
		}
	}
	if(sumWghts > 0.0)   
	{

		avgPReStr /= sumWghts;
		avgPredWghted  /=  sumWghts;
		avgPredWithIn /=  sumWghts;
		avgPredWithoutIn /=  sumWghts;
		if(false)//6 9 23
		{
			avgPReStr = avgPredWghted = avgPredWithIn = avgPredWithoutIn = predicWithHighestWeight;
		}
	}
	 
}

//6 13 23 call this from after resarch evolution and then call to the threshold and performance analytics
//maybe convert the threeshld and dep average of advanced performacne to be used after calling this function

			
//6 24 23 * if is with extreem thatn fist for every person, onceo getting a list of matched profiles, find anchor.
	//then prepare frmo anchor the tierr structure
			 //then select of all potential profiles matched whic is the highest tier, and kep only that tier as candidates
					//then of that tier, select a mix of advanced performacne weighted predictions
					//6 23 23 7 5 23 here is where i need to check for parients to not show if new desig tells us
void cResearchObject::PredictionTasks( bool &isTargetProfileUsed, //int inputTargetedProfileID
	double* predArrOut, double* centerPredArr, double* sumAdvPErwghts, double** twoDimArr,   
	bool* isPersonIn,  	int sizeOfPop, int numOfVariables , cGlobals* globals, cProfileObject** profileListPtr,
										int  profileListSize, bool isWithExtremeDimension, 
										bool isWithFineTuning, bool isThisCaseOfAnchorUniverseIn ,
										bool isToAllowIncludingZeroWeight, bool isWithMinAdvancedPerfWeight,  int inputTargetedProfileID)//= false;//6 23 23 move this to few functions above where there is a differnet decision)
{
	for(int i = 0 ; i < sizeOfPop ; i++)
	{
		predArrOut[i] = 0.0;
		if(centerPredArr != NULL)
		{
			centerPredArr[i]=0.0;
		}
		if(sumAdvPErwghts != NULL)
		{
			sumAdvPErwghts[i]=0.0;
		}
		if(  isPersonIn == NULL ||   isPersonIn[i])
		{
			bool* isProfIn = new bool[profileListSize];
			for(int p=0; p < profileListSize ; p++)
			{
				isProfIn [p] = true;	
			}
			bool* isPSPs = new bool[profileListSize];
			for(int p=0; p < profileListSize ; p++)
			{
				isPSPs [p] = false;
			}
			int numfOfPSPs = 0;
				//fill isPSPs array with true only for profiles that are exact match to the person 
			CollectPSPsForOnePatient(isPSPs, numfOfPSPs,twoDimArr[i],isProfIn,
				 profileListPtr,  profileListSize , isToAllowIncludingZeroWeight);

			if(IS_WITH_CLEAN_PARENT_FROM_BEST_MATCH)//7 11 23 * 15
			{
				CleanPSPsThatAreParentsToOtherrPSPs(isPSPs, profileListPtr , profileListSize);//7 6 23 this plus other areas with same signature to allow at the end a more clmplex seletion of path
			}
			int currentNumOfPSPs = 0;
			for(int p=0; p < profileListSize ; p++)
			{
				if(isPSPs [p])
				{
					currentNumOfPSPs++;
					if(profileListPtr[p]->GetProfileID() == inputTargetedProfileID)
					{
						isTargetProfileUsed = true;
					}
				}
			}
						 
			 
			/*if((predictionContextObjArray != NULL) &&  (finalNumOfPSPs > 0))
			{
				predictionContextObjArray[i]= new cPredictionContextObj[finalNumOfPSPs];
				sizeOfPredContObj[i] = finalNumOfPSPs;
			}*/
			double avgPredction = 0.0;
			double sumWghts = 0.0;
		
			double avgCenterPRed = 0.0;
			double sumWghtsCenter = 0.0;


			double* predArr = new double[profileListSize];
			double* wghArr  = new double[profileListSize];

		//	double* predictionArr =  new double[profileListSize];
			for(int p=0; p < profileListSize ; p++)
			{
				predArr[p]=0.0;
				wghArr[p]=0.0;
			///	predictionArr[p]=0.0;
				if(isPSPs [p])
				{
					double prediction=0.0;
					double predictionWithInterv=0.0;
					double preditionWitoutInterv=0.0;
					double performanceReg=0.0;
					double performanceAdvv=0.0;
					int profileID=-1;
					int subGrpIndex=-1;
				 
					//in processing time and performance check and in real time
					int interventionFieldForPredictionVariations = -1;
					profileListPtr[p]->PredictionElementsNEW( prediction , predictionWithInterv,
						preditionWitoutInterv, performanceReg ,performanceAdvv,
						profileID,subGrpIndex,	twoDimArr[i], numOfVariables, true ,
						interventionFieldForPredictionVariations, *globals,  isWithFineTuning);
					
					if(sumAdvPErwghts != NULL)
					{
						sumAdvPErwghts[i] += performanceAdvv;
					}
					double minScore = 0.01;
					if(p==0)
					{
						int sdg=0;//	performanceAdvv = minScore;
					}
					if(isWithMinAdvancedPerfWeight)
					{
						performanceAdvv = cVarianceCalc::Max(performanceAdvv, minScore);
					}
					//performanceAdvv = cVarianceCalc::Max(performanceAdvv, minScore);
					//performanceAdvv = pow(performanceAdvv , 1.0);//6 23 23 config
					avgPredction += performanceAdvv * prediction;
					sumWghts += performanceAdvv;
					predArr[p] = prediction;
					wghArr[p]=performanceAdvv;


					double wgh = profileListPtr[p]->GetProfileCenterAdvancedPerformance();
					double profCeter = profileListPtr[p]->GetProfileDepAverage();
					avgCenterPRed += wgh * profCeter;
					sumWghtsCenter += wgh;


				}
			}




			isWithExtremeDimension=true;
			if(isWithExtremeDimension)
			{
				//avgPredction = ClearPSPsThatAreNotTier1Extreme( profileListPtr,  profileListSize, 
				//	predArr, wghArr,	isPSPs, currentNumOfPSPs		);		
				avgPredction = CalculateAvgPredictWithExtremetPredictionFocus2( profileListPtr, profileListSize,
					 predArr, wghArr,  isPSPs, currentNumOfPSPs, isThisCaseOfAnchorUniverseIn);
			}
			else
			{
				avgPredction /= sumWghts;
			}
			if(avgPredction > 1.0)
			{
				int sssss=0;
			}
			predArrOut[i] = avgPredction;
			avgCenterPRed /= sumWghtsCenter;
			if(centerPredArr != NULL)
			{
				centerPredArr[i]=avgCenterPRed;
			}					 
			delete []isPSPs ;
			isPSPs =NULL;
			delete []isProfIn;
			isProfIn=NULL;

			delete []predArr ;
			predArr=NULL;
			delete [] wghArr;
			wghArr=NULL;
		}
	}
}

/*
void cResearchObject::PredictRawsNew(
	double* predArr, double* predArrWI, double* predArrWOI,
	     cPredictionContextObj** predictionContextObjArray, int* sizeOfPredContObj,
	double** twoDimArr,  int size, int numOffVars, int testRunMode, double* evolutionPredictionArr, 
	bool isAdvancedPerfGetbEstMatch , 		
	int interventionFieldForPredictionVariations,  cGlobals &globals, bool isWithFineTuning,
	 double anchorDepForProfileMatchh , bool* isPersonIn,  double profSubDepAvgTpForcee, bool isStragiht)
{
	//m_profileObjectPtrList[p]->GetAvgPopGapWhenBestMatch()[subGrpIndex] 
	
	
	if(true)
	{
		bool endLoop = false;
		double* patientProfPRedVarianceArr = new double [size];
		double* patientPredStrArr = new double [size];
		for(int p = 0 ; p< m_profileListSize && !endLoop ; p++)
		{
			for(int ii = 0 ; ii < m_numberOfSubGrps;ii++)
			{
				if(m_profileObjectPtrList[p]->GetAvgPopGapWhenBestMatch()[ii]  != 0.0)
				{
					endLoop = true;
				}
			}
		}

		for(int i = 0 ; i < size && !endLoop ; i++)
		{
			int sdg =0;	
		}
		//double mean

		for(int i = 0 ; i < size && !endLoop ; i++)
		{
			patientProfPRedVarianceArr[i]=0.0;
			patientPredStrArr[i]=0.0;
			bool* isProfileIn = new bool[m_profileListSize];
			for(int p=0; p < m_profileListSize ; p++)
			{
				isProfileIn [p] = true;	
			}
		//er rthe iput test run mode, a specific uttn of the isProfileIn array isi prepared and allows different tests to be condoucted
		
			//6 9 23 open this fui nction here FillIsInProfileForEval and check, also open the  cancel of parents in get best match.
			//move in the meta data config that the 1-8 are the must have profiles, now they are hospital but are not even predcitive
			//and maybe causing issues. if moving parnet cancel do in more than one place. prepare a test file with 
			//only gruop 5 and themm remove the field index 2 in the meta predictivei and remoe the must have fields also.
			//also use test mode to only go with these must be fields as an option
			//FillIsInProfileForEval(isProfileIn, testRunMode , globals );
	
			bool* isPSPs = new bool[m_profileListSize];
			for(int p=0; p < m_profileListSize ; p++)
			{
				isPSPs [p] = false;
			}
			int numfOfPSPs = 0;
					//fill isPSPs array with true only for profiles that are exact match to the person 
			CollectPSPsForOnePatient(isPSPs, numfOfPSPs,twoDimArr[i],isProfileIn,cProfileObject** profileArr, int profileArrSize);
			double lower = 1000;
			double higher = 0.0;
			
			double  meanPred=0.0;
			double meanPredSquared=0.0;
			int countPRedicitons=0;
			double* arraForVar = new double[m_profileListSize];
			double* wghArr= new double[m_profileListSize];
			for(int p = 0 ; p<m_profileListSize; p++)
			{
				arraForVar[p]=0.0;
				wghArr[p]=0.0;
				if(isPSPs[p])
				{
					//patinet gets prediction and sub group from the profile p
					//profile p sub has an agerage range

					double prediction = 0.0;
					double performanceReg =0.0;
					double performanceAdv=0.0;
					int profileID=-1;
					int subGrpIndex=-1;
					m_profileObjectPtrList[p]->PredictionElementsNEW( prediction , prediction,
						prediction, performanceReg ,performanceAdv,
						profileID,subGrpIndex,	twoDimArr[i], numOffVars, isAdvancedPerfGetbEstMatch ,
						interventionFieldForPredictionVariations, globals,  isWithFineTuning);
					double anachorDep =0.0;
					double sdAnchor=0.0;
					m_profileObjectPtrList[p]->GetDepAverageOfMustBeParentProfile(anachorDep,sdAnchor,
											m_guidedInclusionRuleList,	m_guidedInclusionsRuleListSize,  this);
					if( prediction < lower)//6 11 23 add an sd output from the dep average function loking at the root or guiding anchor sub grps
					{
						lower = prediction;
					}
					if(prediction > higher)
					{
						higher  = prediction;
					}
					meanPred+= prediction;
					meanPredSquared += (prediction*prediction);
					countPRedicitons++;
					
					arraForVar[p]=sdAnchor;// anachorDep*(1.0 - anachorDep); //  (prediction-anachorDep);
					wghArr[p]=1.0;
					if(p==0)
					{
						wghArr[p]=0.001;//since it doe not have an anchor dont want to have the gap bias the variance
					}
				}
			}
			meanPred /= countPRedicitons;
			meanPredSquared/= countPRedicitons;
			patientPredStrArr[i]=meanPred;
			double var = cVarianceCalc::Abs(meanPredSquared - (meanPred * meanPred));
			double meanP=0.0;
			double sD = 0.0;
			if(countPRedicitons > 1)
			{
				cVarianceCalc::CalculateMeanAndSD(meanP,sD,arraForVar, wghArr,m_profileListSize);
			}
			var = meanP;//sD * sD; arraForVar is full with anachorDep times 1-anachorDep. that is a proxi of variance for a world with certan prob
			//the meanP of the array of variane is actualy the mean variance and which will be set here
			delete[] arraForVar;
			arraForVar=NULL;
			delete[] wghArr;
			wghArr=NULL;

		//	double higherOdd = (higher - anchorDepForProfileMatch)/ anchorDepForProfileMatch;
		// 	double lowerOdd =  (lower -anchorDepForProfileMatch)/anchorDepForProfileMatch;
			patientProfPRedVarianceArr[i] = var;
			//set var to lower bar to 1- aavoid vidive by zer if happens and 2- avoid divide by a very low number for the delta score
			patientProfPRedVarianceArr[i]= cVarianceCalc::Max(patientProfPRedVarianceArr[i],0.0001); 

			delete []isProfileIn;
			isProfileIn=NULL;
			delete []isPSPs;
			isPSPs=NULL;
		}
		cout<< "After first learning loop prediction variance per patinet \n";
		double** rangesArray = new double*[m_profileListSize];
		int** rangeCntArr = new int*[m_profileListSize];
		for(int p = 0 ; p< m_profileListSize && !endLoop ; p++)
		{
			rangesArray[p] = new double[m_numberOfSubGrps];
			rangeCntArr[p] = new int[m_numberOfSubGrps];
			for(int ii = 0 ; ii < m_numberOfSubGrps;ii++)
			{
				rangesArray[p][ii]= 0.0;
				rangeCntArr[p][ii]=0;
			}
		}


		for(int i = 0 ; i < size && !endLoop ; i++)
		{
			 
			bool* isProfileIn = new bool[m_profileListSize];
			for(int p=0; p < m_profileListSize ; p++)
			{
				isProfileIn [p] = true;	
			}
			bool* isPSPs = new bool[m_profileListSize];
			for(int p=0; p < m_profileListSize ; p++)
			{
				isPSPs [p] = false;
			}
			int numfOfPSPs = 0;
					//fill isPSPs array with true only for profiles that are exact match to the person 
			CollectPSPsForOnePatient(isPSPs, numfOfPSPs,twoDimArr[i],isProfileIn,cProfileObject** profileArr, int profileArrSize);
			for(int p = 0 ; p<m_profileListSize; p++)
			{
				if(isPSPs[p])
				{
					//patinet gets prediction and sub group from the profile p
					//profile p sub has an agerage range
					//patinet i 
					double prediction = 0.0;
					double predWI=0.0;
					double predWOT=0.0;
					double performanceReg =0.0;
					double performanceAdv=0.0;
					int profileID=-1;
					int subGrpIndex=-1;
					m_profileObjectPtrList[p]->PredictionElementsNEW( prediction , predWI,
						predWOT, performanceReg ,performanceAdv,
						profileID,subGrpIndex,	twoDimArr[i], numOffVars, isAdvancedPerfGetbEstMatch ,
						interventionFieldForPredictionVariations, globals,  isWithFineTuning);
					double anachorDep = 0.0;
					double sdAnchor = 0.0;
					m_profileObjectPtrList[p]->GetDepAverageOfMustBeParentProfile(anachorDep,sdAnchor,
										m_guidedInclusionRuleList,	m_guidedInclusionsRuleListSize,  this);
					double deltaPred = cVarianceCalc::Abs(anachorDep - prediction);// * (anachorDep - prediction);
					//double predOdd = prediction / anchorDepForProfileMatch; 
					//if(predOdd < 1.0)
					//{
					//	predOdd = 1.0 / predOdd;
					//}
						
					//	*(patientPredStrArr[i]-anchorDepForProfileMatch));
				//	double sqrReachPredictionPsub =  
					//    (anchorDepForProfileMatch-prediction) * (anchorDepForProfileMatch-prediction);
						
					//double XXX = (anchorDepForProfileMatch-prediction) * (anchorDepForProfileMatch-prediction);
					//double YYY = (anchorDepForProfileMatch-prediction) * (anchorDepForProfileMatch-prediction);
				//	double thisProfPredDeltaFromAllsqr = 
						//cVarianceCalc::Abs
						//(patientPredStrArr[i]- prediction)*(patientPredStrArr[i]- prediction);//
					//*(patientPredStrArr[i]- prediction);
						//(anchorDepForProfileMatch-prediction) * (anchorDepForProfileMatch-prediction);
						//prediction / anchorDepForProfileMatch;
									//(prediction -anchorDepForProfileMatch)/anchorDepForProfileMatch;
					//double personPRedSD = pow(patientProfPRedVarianceArr[i],0.5);
					double deltaScore =( deltaPred / patientProfPRedVarianceArr[i]);
					rangesArray[p][subGrpIndex ] += deltaScore;
					rangeCntArr[p][subGrpIndex] ++;
				}
			}	
			
			delete []isProfileIn;
			isProfileIn=NULL;
			delete []isPSPs;
			isPSPs=NULL;
		}
		cout<< "After second learning loop prediction variance per patinet \n";
		for(int p = 0 ; p< m_profileListSize && !endLoop ; p++)
		{
			for(int ii = 0 ; ii < m_numberOfSubGrps;ii++)
			{
				if(rangeCntArr[p][ii] >0)
				{
					rangesArray[p][ii] /= rangeCntArr[p][ii];
					m_profileObjectPtrList[p]->GetAvgPopGapWhenBestMatch()[ii] = rangesArray[p][ii]  ;
				}
				if(p==0)
				{
					m_profileObjectPtrList[p]->GetAvgPopGapWhenBestMatch()[ii]=0.0;
				}
			}
		}
		cout<< "rtttttyhhgh \n";
		delete []patientPredStrArr;
		patientPredStrArr=NULL;
		delete []patientProfPRedVarianceArr;
		patientProfPRedVarianceArr=NULL;

		for(int p = 0 ; p< m_profileListSize && !endLoop ; p++)
		{
			delete []rangesArray[p];
			delete []rangeCntArr[p] ;
		}
		delete []rangesArray;
		rangesArray=NULL;
		delete []rangeCntArr;
		rangeCntArr=NULL;

		cout<< "ryete  \n";
	}





	///////////////////////////////////////////////6 8 23 re write this to keep two loops and keep tier one performing profies
	double* deltaArr = new  double[size];
	for(int i = 0 ; i < size ; i++)
	{//5 31 23 add if( isPersonInTestGrp[i] as an input and only build arrays frmo this one above.
		deltaArr[i]=0.0;
		if(  isPersonIn == NULL ||   isPersonIn[i])
		{
			predArr[i]=0.0; //5 31 23 
			if(false)//	(isPersonIn!=NULL) && (isPersonIn[i] )&& (profSubDepAvgTpForce != 0.0))
			{
			//	predArr[i] = profSubDepAvgTpForce;
			//	predArrWI[i]=profSubDepAvgTpForce ;
			//	predArrWOI[i]=profSubDepAvgTpForce;
			}
			else
			{
				bool* isProfileIn = new bool[m_profileListSize];
				for(int p=0; p < m_profileListSize ; p++)
				{
					isProfileIn [p] = true;	
				}
		//er rthe iput test run mode, a specific uttn of the isProfileIn array isi prepared and allows different tests to be condoucted
				FillIsInProfileForEval(isProfileIn, testRunMode , globals );
	
				bool* isPSPs = new bool[m_profileListSize];
				for(int p=0; p < m_profileListSize ; p++)
				{
					isPSPs [p] = false;
				}
				int numfOfPSPs = 0;
					//fill isPSPs array with true only for profiles that are exact match to the person 
				CollectPSPsForOnePatient(isPSPs, numfOfPSPs,twoDimArr[i],isProfileIn, cProfileObject** profileArr, int profileArrSize);
				//CleanPSPsThatAreParentsToOtherrPSPs(isPSPs);//5 31 23 remove this line andn

				int finalNumOfPSPs = 0;
				for(int p=0; p < m_profileListSize ; p++)
				{
					if(isPSPs [p])
					{
						finalNumOfPSPs++;
					}
				}
				if((predictionContextObjArray != NULL) &&  (finalNumOfPSPs > 0))
				{
					predictionContextObjArray[i]= new cPredictionContextObj[finalNumOfPSPs];
					sizeOfPredContObj[i] = finalNumOfPSPs;
				}

				double avgPReStr=0.0;
				
				double sumWghtsAdv = 0.0;
				double avgPredAdv = 0.0;
				double avgPredWithInAdv = 0.0;//12 2 22 place holder, not used outside, as the next one. only the avgPred is ann ouput into predArr
				double avgPredWithoutInAdv = 0.0;
		
			
				ASDFGH( avgPReStr,  sumWghtsAdv, avgPredAdv, avgPredWithInAdv ,	avgPredWithoutInAdv,
					isPSPs,	twoDimArr, i, numOffVars, isAdvancedPerfGetbEstMatch ,
						interventionFieldForPredictionVariations, &globals, 
						isWithFineTuning,0.0, 0.0,NULL,NULL, isStragiht );
				deltaArr[i] = avgPredAdv - avgPReStr;///delta fofr this person using all profiles in isPSPs matched the person
		
				double sendstregPred = avgPReStr;
				double sendDelta = deltaArr[i];
				//if(!isApplyDeltaRangeRestic)
				//{
				//	sendstregPred = sendDelta = 0.0;
				//}
			 
				predArr[i]=avgPredAdv;
				predArrWI[i]=avgPredWithInAdv;
				predArrWOI[i]=avgPredWithoutInAdv;	
						 
				delete []isPSPs ;
				isPSPs =NULL;
				delete []isProfileIn;
				isProfileIn=NULL;
			}
		}
		else
		{			
			//predArr[i]=evolutionPredictionArr[i];
		//	predArrWI[i]=evolutionPredictionArr[i];
			//predArrWOI[i]=evolutionPredictionArr[i];		
		}
	}

	delete []deltaArr;
}
*/


/*
void cResearchObject::Predic tRawsNew(
	double* predArr, double* predArrWI, double* predArrWOI,
	     cPredictionContextObj** predictionContextObjArray, int* sizeOfPredContObj,
	double** twoDimArr,  int size, int numOffVars, int testRunMode, double* evolutionPredictionArr, 
	bool isAdvancedPerfGetbEstMatch , 		
	int interventionFieldForPredictionVariations,  cGlobals &globals, bool isWithFineTuning )
{
	double** profSubPred = new double*[m_profileListSize];
	double** profSubPredWeighted= new double*[m_profileListSize];
	double** profSubPerf = new double*[m_profileListSize];
	double** profSubPredDelta = new double*[m_profileListSize];
	int** profSubCnt = new int*[m_profileListSize];
	for(int p = 0 ; p < m_profileListSize ; p++)
	{
		profSubPredWeighted[p]=new double[m_numberOfSubGrps];
		profSubPred[p]=new double[m_numberOfSubGrps]; 
		profSubPerf[p] = new double[m_numberOfSubGrps]; 
		profSubPredDelta[p] = new double[m_numberOfSubGrps]; 
		profSubCnt[p]= new int[m_numberOfSubGrps];
		for(int x = 0 ; x< m_numberOfSubGrps; x++)
		{
			profSubPred[p][x]=0.0;
			profSubPredWeighted[p][x]=0.0;
			profSubPerf[p][x]=0.0;
			profSubPredDelta[p][x]=0.0;
			profSubCnt[p][x]=0;
		}
	}
//	every person i contributes to the delta of the profiles it mathed by having mix proifles avgg against 
	//one in buiding time, here every 
	for(int i = 0 ; i < size ; i++)
	{
		bool* isProfileIn = new bool[m_profileListSize];
		for(int p=0; p < m_profileListSize ; p++)
		{
			isProfileIn [p] = true;	
		}
		//er rthe iput test run mode, a specific uttn of the isProfileIn array isi prepared and allows different tests to be condoucted
		FillIsInProfileForEval(isProfileIn, testRunMode , globals );
		predArr[i]=0.0; 
		bool* isPSPs = new bool[m_profileListSize];
		for(int p=0; p < m_profileListSize ; p++)
		{
			isPSPs [p] = false;
		}
		int numfOfPSPs = 0;
				//fill isPSPs array with true only for profiles that are exact match to the person 
		CollectPSPsForOnePatient(isPSPs, numfOfPSPs,twoDimArr[i],isProfileIn);
		if(false)//5 31 23 check and config
		{
			CleanPSPsThatAreParentsToOtherrPSPs(isPSPs);//5 31 23 remove this line andn
		}
		int finalNumOfPSPs = 0;
		for(int p=0; p < m_profileListSize ; p++)
		{
			if(isPSPs [p])
			{
				finalNumOfPSPs++;
			}
		}
		if((predictionContextObjArray != NULL) &&  (finalNumOfPSPs > 0))
		{
			predictionContextObjArray[i]= new cPredictionContextObj[finalNumOfPSPs];
			sizeOfPredContObj[i] = finalNumOfPSPs;
		}
	 
	//	double* predArrayStr = new double[m_profileListSize];
		double* predArrayPerProf = new double[m_profileListSize];
		double* predWIArrayPerProf = new double[m_profileListSize];
		double* predWOIArrayPerProf = new double[m_profileListSize];
		double* perfArrayAdvProf = new double[m_profileListSize];
		int movingPRedCpontextObjIndex = 0;

		for(int p=0; p < m_profileListSize ; p++)
		{
		//	predArrayStr[p]=0.0;
			predArrayPerProf[p]=0.0;
			predWIArrayPerProf[p]=0.0;
			predWOIArrayPerProf[p]=0.0;
			perfArrayAdvProf[p]=0.0;
			if(isPSPs [p])
			{
				double prediction = 0.0;
				double performanceReg=0.0;
				double performanceAdv=0.0;
				double predictionWithInterv=0.0;
				double preditionWitoutInterv=0.0;
			//12 2 22 **** 
					//1-profileID, subGrpIndex add these as output from PredictionElementsNEW
					//2- add flexible is in profile
					//3 do a new file path for the calibration report and not same performacne
					
				int profileID = -1;
				int subGrpIndex = -1;
				m_profileObjectPtrList[p]->PredictionElementsNEW(		predArrayPerProf[p] , 	predWIArrayPerProf[p],
					//	prediction, predictionWithInterv, preditionWitoutInterv ,
					predWOIArrayPerProf[p],
						performanceReg ,//performanceAdv,
						perfArrayAdvProf[p],
						profileID,subGrpIndex,	twoDimArr[i], numOffVars, isAdvancedPerfGetbEstMatch ,
						interventionFieldForPredictionVariations, globals,  isWithFineTuning);
				double minScore = 0.000000001;
				int count = m_profileObjectPtrList[p]->GetSubBucketCntArr()[subGrpIndex] ;
				if(count < 200)
						//5 31 23 change both 200 above and 5 below to onfig. 
				{
					perfArrayAdvProf[p]=minScore;
				}

				//predArrayStr[p]+=prediction;
			//	predArrayPerProf+= prediction*perfArrayAdvProf[p];//dummerie streithi predi
			//	profSubCnt[p]++;//stregith count
			//	profSubPredWeighted[p][subGrpIndex]+= prediction*performanceAdv;//using perf as weight
			//	profSubPerf[p][subGrpIndex]+=performanceAdv;//firsit used as susm of wieghts and then avg perfo
	 		}
		}

	

	}

	for(int p=0; p < m_profileListSize ; p++)
	{
		if(isPSPs [p])
		{
		
		}
	}


	////	profSubPred[p][subGrpIndex]+= prediction;//dummerie streithi predi
	//			profSubCnt[p][subGrpIndex]++;//stregith count
	//			profSubPredWeighted[p][subGrpIndex]+= prediction*performanceAdv;//using perf as weight
	//			profSubPerf[p][subGrpIndex]+=performanceAdv;//firsit used as susm of wieghts and then avg perfo
	for(int p = 0 ; p < m_profileListSize ; p++)
	{
	 	for(int x = 0 ; x< m_numberOfSubGrps; x++)
		{
			if(profSubPerf[p][x]>0.0)
			{
				profSubPredWeighted[p][x] /= profSubPerf[p][x];
			}
			if(profSubCnt[p][x] > 0)
			{
				profSubPerf[p][x] /= profSubCnt[p][x];
				profSubPred[p][x]/= profSubCnt[p][x];
			}
			//profSubPerf[p][x]
			profSubPredDelta[p][x] = profSubPredWeighted[p][x] - profSubPred[p][x];
				//pred delta is how  muc the weighted pred minus the straigt. delta is directialna
			 
		}
	}
	 

	delete [] profSubPerf;
	delete [] profSubPredDelta;
	delete [] profSubCnt;




					else//if the issue was the sample,  add in the else a way to compensatet and not just jump to min score
					{
						performanceAdv =minScore;
					}
				//	else if(  globals.g_IS_PERF_WEGIHT_FOR_BEST_MATCH_MERGE_POWER_BY_2)
				//	{
				//		performance *= performance;
				//	}
					avgPredReg += (prediction * performanceReg);
					avgPredWithInReg  += (predictionWithInterv * performanceReg);
					avgPredWithoutInReg  += (preditionWitoutInterv * performanceReg);
					sumWghtsReg += performanceReg;//wgh;
					avgPredAdv += (prediction * performanceAdv);
					avgPredWithInAdv  += (predictionWithInterv * performanceAdv);
					avgPredWithoutInAdv  += (preditionWitoutInterv * performanceAdv);
					sumWghtsAdv += performanceAdv;

					if((predictionContextObjArray != NULL) && 	(sizeOfPredContObj[i] > 0))
					{
						predictionContextObjArray[i][movingPRedCpontextObjIndex++].SetObject(
						 profileID, subGrpIndex, prediction, predictionWithInterv , 
						 preditionWitoutInterv, performanceAdv);
					}
				}
			}
			if(    isAdvancedPerfGetbEstMatch      &&     (sumWghtsAdv > 0.0)   )
			{
				avgPredAdv  /=  sumWghtsAdv;
				avgPredWithInAdv /=  sumWghtsAdv;
				avgPredWithoutInAdv /=  sumWghtsAdv;
				predArr[i] = avgPredAdv;

			}
			else if(sumWghtsReg > 0.0)
			{
				avgPredReg  /=  sumWghtsReg;
				avgPredWithInReg /=  sumWghtsReg;
				avgPredWithoutInReg /=  sumWghtsReg;
				predArr[i] = avgPredReg;				
			}
			delete []isPSPs ;
			isPSPs =NULL;
			delete []isProfileIn;
			isProfileIn=NULL;
			delete []predArrayStr;
			delete []predArrayPerProf ;
			delete [] predWIArrayPerProf;
			delete [] predWOIArrayPerProf;
			delete [] perfArrayAdvProf;
		}
		else
		{
			predArr[i] = evolutionPredictionArr[i];
		}
		
	}
}
*/







//for a given input two dim patients we produce the prdeiction, and after using calib mapping
//tuen inut data object to be breakdown of paramer and then i can also have a list of 1 to be prediction and no need for more function
void cResearchObject::PreparePostCalibPredictions(  double* predictionArr, double* predictionWithInArr, double* predictionWithoutInArr,
	cPredictionContextObj** predictionContextObjArray, int* sizeOfPredContObj,
	double** twoDimArr, double* depArr, int size,int numOfVars,
		int testRunMode ,cCalibrationContextObj* calbObj,  bool isAdvancedPerfGetbEstMatch , 
		int interventionFieldForPredictionVariations,cGlobals &globals,bool isWithFineTuning)
{
	double* rawPredArr = new double [size];
	double* rawPpredArrWI  = new double [size];
	double* rawPpredArrWOI = new double [size];


	//5 31 23 change to predict raws new and cancerl predeicti raws. consider using this new function also as a prediciton in real time by 
	//sending only one person instead of a list
	/*PredictRaws( rawPredArr, rawPpredArrWI, rawPpredArrWOI,
		    predictionContextObjArray,  sizeOfPredContObj,
		twoDimArr,  size ,numOfVars,  testRunMode, NULL,
		isAdvancedPerfGetbEstMatch ,    interventionFieldForPredictionVariations, globals ,isWithFineTuning);*/
	calbObj->ConvertToPostRawPredictions(predictionArr, rawPredArr, size);
	calbObj->ConvertToPostRawPredictions(predictionWithInArr, rawPpredArrWI, size);
	calbObj->ConvertToPostRawPredictions(predictionWithoutInArr, rawPpredArrWOI, size);
	delete []rawPredArr;	
	delete []rawPpredArrWI;
	delete []rawPpredArrWOI;
}


void cResearchObject::PredictPatientSetAndGetPErformanceELemets( double &anchorDepForBestMatch, double* predictionArr, double* predictionWithInArr, double* predictionWithoutInArr,
	
	cPredictionContextObj** predictionContextObjArray, 	int* sizeOfPredContObj, double* threshArr ,double* avgDepArr, int* cntArr,  double &depAvg,
	double** twoDimArr, double* depArr, int size, int numOfVars,	cCalibrationContextObj* calbObj,  
	int testRunMode, bool isWithCalibration, int numOfPerformanceSubGrps, double* evolutionPredictionArr, bool isAdvancedPerfGetbEstMatch ,
	    int interventionFieldForPredictionVariations,   cGlobals &globals, bool isWithFineTuning ,
		 bool* isPersonIn, double profSubDepAvgTpForce, bool isStragihtPRed)
{
	
	//cPredictionContextObj** predictionContextObjArray= NULL;
	//int* sizeOfPredContObj=NULL;


	//double* predictionArr, double* predictionWithInArr, double* predictionWithoutInArr,
	bool* isInTest = new bool[size];
	double avgDepTest = 0.0;
	int countTest=0;
	double generalAvgDep=0.0;
	for ( int i = 0 ; i < size; i ++)
	{
		isInTest[i]=true;
	//	bool belong = (twoDimArr[i][1] == 5);
		
			//((twoDimArr[i][1] == 4 )|| (twoDimArr[i][1] == 5));
	//	if(isWithTest)
	//	{
	////		if(!belong)//5 31 23
		//	{
		//		isInTest[i]= false;
		//	}
		//}
	//	if(belong)
	//	{
		//	avgDepTest += depArr[i];
	//		countTest++;
	//	}
		generalAvgDep+=depArr[i];

	}
	generalAvgDep/=size;
	//if(countTest>0)
	//{
//		avgDepTest /= countTest;
//	}
//	if(isWithTest)
//	{
//		anchorDepForBestMatch=avgDepTest;
	//}
	//else
	//{
		anchorDepForBestMatch = generalAvgDep;
		avgDepTest = generalAvgDep;
	//}
	
	if(isWithCalibration && (calbObj != NULL))
	{
		PreparePostCalibPredictions( predictionArr,  predictionWithInArr,  predictionWithoutInArr,			
	     predictionContextObjArray,  sizeOfPredContObj, 
			twoDimArr,  depArr,  size, numOfVars, testRunMode , calbObj, 
			isAdvancedPerfGetbEstMatch ,    interventionFieldForPredictionVariations,  globals, isWithFineTuning );
	}
	else
	{
		int sdg = 0 ;
		//PredictRaws
		/*PredictRawsNew
			(  predictionArr,  predictionWithInArr,  predictionWithoutInArr,
			 predictionContextObjArray ,  sizeOfPredContObj, 
			twoDimArr,  size ,numOfVars,  testRunMode,  evolutionPredictionArr,  isAdvancedPerfGetbEstMatch ,   
			         interventionFieldForPredictionVariations,      globals,  
					 isWithFineTuning, anchorDepForBestMatch, isPersonIn, profSubDepAvgTpForce,isStragihtPRed);
*/

	}
	 
	
	cProfileObject::CalculateThresholds(threshArr , numOfPerformanceSubGrps, predictionArr,isInTest,size);

	depAvg = 0.0;
	cProfileObject::CreateAvgDepSubGrps(NULL,avgDepArr,threshArr ,cntArr, depAvg, numOfPerformanceSubGrps,predictionArr,depArr, isInTest, size, globals);

	delete []isInTest;
}

 

int cResearchObject::SelectTopPerformingProfileIndex(int* terminalIndexList, int sizeOfTerminalList, 
		  int* indexList, int indexListSize)
{
	double maxPerf = 0.0;
	int maxPErformingIndex = -1;
	for(int i = 0 ; i < sizeOfTerminalList ; i++)
	{
		int index = terminalIndexList[i];
		double per = m_profileObjectPtrList[index]->GetRootBasedPerformace();//thhis is a temporry performacnec 
			                                                            //while building the tre, not for real time
		if(per> maxPerf)
		{
			if( !( Is_IndexAlreadyInArray( indexList, indexListSize, index)))
			{
					maxPerf = per;
					maxPErformingIndex = index;
			}
		}

	}
	return maxPErformingIndex;
}

bool cResearchObject::Is_IndexAlreadyInArray( int* indexList, int size, int index)
{
	bool isIn = false;
	for(int i = 0 ; i < size ; i++)
	{
		if(index == indexList[i])
		{
			return true;
		}
	}
	return false;
}


int  cResearchObject::CollectRandomIndexe( int size)
{
	int random =  rand();
	int randomInxe = random % size   ;//i.e. if random is larger than listi size 
	return randomInxe;
}
 
/*
{
  "Number of Profiles": 413,
  "profiles": {
    "Profile ID": 0,
    "Anchor ID": 0,


*/






void cResearchObject::ResObjWriteOrReradMor2( cArrayFlex* arrayFlex , cGlobals &globals)
{
	char msgStr[1000];
	bool isWrite =  arrayFlex->GetIsWriteMode();
//{	
	strcpy(msgStr, "{");
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

//"Number of Profiles:" P,
	int leadingSpacesNum = 2;
	cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger(msgStr, "Number of Profiles", m_profileListSize,leadingSpacesNum, true );
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

// "profiles": {
	cVarianceCalc::StrCptWithDoubleQuotesAndColonAndOpeningSquare(msgStr, "profiles", leadingSpacesNum,  true);
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);
	leadingSpacesNum += 2;
	for(int i = 0 ; i < m_profileListSize ; i++)
	{
		cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "{", leadingSpacesNum,  false);
		arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals);
		if(i > 0)
		{
			m_profileObjectPtrList[i]->SetRootProfile(m_profileObjectPtrList[0]);
		}
		leadingSpacesNum+=2;
		m_profileObjectPtrList[i]->PrfObjPrepareArraysToOrFromDisc2(arrayFlex, 
											arrayFlex->GetIsWriteMode(), globals, leadingSpacesNum, i );
		leadingSpacesNum-=2;
		cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "}", leadingSpacesNum,  false);
		arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals);
		if(i < (m_profileListSize-1) )
		{
			cVarianceCalc::StrCptWithDoubleQuotes(msgStr, ",", leadingSpacesNum,  false);
			arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals);
		}
	}
	leadingSpacesNum -= 2;
	cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "]", leadingSpacesNum,  false);
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

	leadingSpacesNum -= 2;
	strcpy(msgStr, "}");
	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

}



void cResearchObject::ResObjWriteOrRerad( cArrayFlex* arrayFlex , cGlobals &globals)
{
	int leadingZeros = 0;
	char msgStr[1000];
	//strcpy(msgStr, "Number of Profiles");
	cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "Number of Profiles",leadingZeros, false);
	arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals,true);
	
	arrayFlex->WriteReadArrayInt(m_profileListSize ,  arrayFlex->GetIsWriteMode() ,  globals);
		//isWriteToArray);

	
	if(!arrayFlex->GetIsWriteMode())
	{
		//m_profileObjectPtrList = new cProfileObject*[m_profileListSize];
		for( int i = 0 ; i < m_profileListSize ; i++)
		{
			cVariableAndValueAndPoints* inclusionRuleSet = NULL;//root has emeplty rule set
			int inclusionRuleSetSize=0;//these two are just to make clear story input, instead of sending NULL and 0.
			cProfileObject* root = NULL;//for the actual real root we want to have the root as NULL to mark that this is root
			int profileID = -1;// 
			//cProfileObject* root = NULL;
			double** patientsDataSet = NULL;
			double* depArr = NULL;
			int numberOfPatients=0;
			int numberOfAugmentedVars =0;
			int numberOfSubGrps=0;
			cVariableSchemaArr* schemaArr = NULL;
			cResearchDataObj* researchDataObj = NULL;
			int anchorID = -1;
				
			m_profileObjectPtrList[i] = new cProfileObject(
			this, profileID, root, inclusionRuleSet,inclusionRuleSetSize, researchDataObj,anchorID, NULL);
			//root, numberOfSubGrps,  schemaArr, profileID, 0,NULL); 

		}
	}
	leadingZeros +=2;
	for(int i = 0 ; i < m_profileListSize ; i++)
	{
	//	strcpy(msgStr, "{");
		cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "{",leadingZeros, false);
		arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals);
		m_profileObjectPtrList[i]->PrfObjPrepareArraysToOrFromDisc( arrayFlex,  arrayFlex->GetIsWriteMode(), globals);
		if(i > 0)
		{
			m_profileObjectPtrList[i]->SetRootProfile(m_profileObjectPtrList[0]);
		}
		//strcpy(msgStr, "}");
		cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "}",leadingZeros, false);
		arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals);
		if(i < (m_profileListSize-1) )
		{
			//strcpy(msgStr, ",");
			cVarianceCalc::StrCptWithDoubleQuotes(msgStr, ",",leadingZeros, false);
			arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),globals);
		}
	}
	leadingZeros -= 2;
	if(!arrayFlex->GetIsWriteMode())
	{
		m_rootProfile = m_profileObjectPtrList[0];
	}	
}




/////////////////HARD CODED CONFIG REPLACEMENT////////////////////////////////////



	cVariableSchemaObject::~cVariableSchemaObject()
	{
		if(m_varValues != NULL)
		{
			delete[] m_varValues;
		}
		if(m_varValuePrevlns != NULL)
		{
			delete []m_varValues;
		}
 
//		if(m_interventionValueList != NULL)
		{
		//	delete[] m_interventionValueList;
		}
	}
	 
	void cVariableSchemaObject::SetName(char* name)
	{
		strcpy_s(m_varibleName,name);
	}

	void cVariableSchemaObject::SchemaElementReadORwriteObjectToArr( cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals)
	{
	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_varPosition) ,  sizeof(int), isWriteToArray);
		arrayFlex->WriteReadArrayInt( m_varPosition ,  isWriteToArray ,  globals);
		
//		arrayFlex->WriteReadArray( (unsigned char*)(&m_isOrgVar) ,  sizeof(bool), isWriteToArray);
		arrayFlex->WriteReadArrayBool( m_isOrgVar ,   isWriteToArray ,  globals);

	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_orgIndex) ,  sizeof(int), isWriteToArray);
		arrayFlex->WriteReadArrayInt( m_orgIndex ,  isWriteToArray ,  globals);
	
		
//		arrayFlex->WriteReadArray( (unsigned char*)(&m_isPredictiveVariable) ,  sizeof(bool), isWriteToArray);
		arrayFlex->WriteReadArrayBool( m_isPredictiveVariable ,  isWriteToArray, globals);
		
	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_isIntervenstion) ,  sizeof(bool), isWriteToArray);
		arrayFlex->WriteReadArrayBool( m_isIntervenstion ,  isWriteToArray, globals);



	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_indexOfPropensity) ,  sizeof(int), isWriteToArray);
		arrayFlex->WriteReadArrayInt( m_indexOfPropensity ,  isWriteToArray ,  globals);
	
		
	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_isToBeReplaced) ,  sizeof(bool), isWriteToArray);
		arrayFlex->WriteReadArrayBool( m_isToBeReplaced ,  isWriteToArray ,  globals);
	
//		arrayFlex->WriteReadArray( (unsigned char*)(&m_numberOfValues) ,  sizeof(int), isWriteToArray);	
		arrayFlex->WriteReadArrayInt( m_numberOfValues ,  isWriteToArray ,  globals);


	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_lowestValue) ,  sizeof(double), isWriteToArray);
		arrayFlex->WriteReadArrayDouble( m_lowestValue ,   isWriteToArray, globals);
	
	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_highestValue) ,  sizeof(double), isWriteToArray);	
		arrayFlex->WriteReadArrayDouble( m_highestValue ,  isWriteToArray, globals);
	
		if(!isWriteToArray)
		{
			if(m_numberOfValues > 0)
			{
				m_varValues = new double[m_numberOfValues];
				m_varValuePrevlns = new double[m_numberOfValues];
			}
		}
		for(int i = 0 ; i < m_numberOfValues ; i++)
		{
		//	arrayFlex->WriteReadArray( (unsigned char*)(&(m_varValues[i])) ,  sizeof(double), isWriteToArray);
			arrayFlex->WriteReadArrayDouble( m_varValues[i],  isWriteToArray , globals);
		}
		for(int i = 0 ; i < m_numberOfValues ; i++)
		{
		//	arrayFlex->WriteReadArray( (unsigned char*)(&(m_varValuePrevlns[i])) ,  sizeof(double), isWriteToArray);
			arrayFlex->WriteReadArrayDouble(m_varValuePrevlns[i] ,  isWriteToArray, globals);
		}
	}
	
	bool cVariableSchemaObject::IsNameOfVariable(char* str)
	{
		int x = strcmp(m_varibleName, str);
		if(x==0)
		{
			return true;
		}
		return false;
	} 
	cVariableSchemaObject::cVariableSchemaObject( int varPosition, bool isPredictiveVariable, bool isOrgVar, bool isIntervenstion, int indexOfPropensity)
	{
	
		m_varibleName[0]=0;
		m_varPosition = varPosition;
		m_isOrgVar = isOrgVar;

		m_isPredictiveVariable = isPredictiveVariable;
		m_isToBeReplaced = false;

		m_isIntervenstion = isIntervenstion;
		m_indexOfPropensity = indexOfPropensity;

		m_varValues=NULL;
		m_varValuePrevlns=NULL;
		m_numberOfValues=0;
		
		m_lowestValue=0;
		m_highestValue=0;

	//	m_interventionValueList=NULL;
	//	m_interventionValueListCount=0; 

	/*	m_isDecimalValues=true;
		m_isCategoricalVariable=true;
		m_isDependentVariable=false;
		
		m_valuesThatIncluedInLogisticCode1=NULL;
		m_valuesThatIncluedInLogisticCode1Size=0;

		m_inclusionValueList=NULL;
		m_inclusionValueListSize=0;

		*/
	}




 

	void cVariableSchemaArr::SchemaReadORwriteObjectToArr(  cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals)
	{
	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_maxNumberOfObjects) ,  sizeof(int), isWriteToArray);
		arrayFlex->WriteReadArrayInt(m_maxNumberOfObjects ,  isWriteToArray ,  globals);


	//	arrayFlex->WriteReadArray( (unsigned char*)(&m_orgNumOfVars) ,  sizeof(int), isWriteToArray);
		arrayFlex->WriteReadArrayInt( m_orgNumOfVars ,   isWriteToArray ,  globals);
	
		
		
		//	arrayFlex->WriteReadArray( (bool*)(&m_augmentedNumOfVars) ,  sizeof(int), isWriteToArray);
	
		if(!isWriteToArray)
		{
			if(m_maxNumberOfObjects > 0)
			{
				m_schemaArr = new cVariableSchemaObject*[m_maxNumberOfObjects];
				for(int i = 0 ; i < m_maxNumberOfObjects ; i++)
				{//12 2 22 find how to get from meta data file to having the right input of intervention and propensity here and then having the input flow into the profile 
					m_schemaArr[i]=new cVariableSchemaObject(i, false , false, false, -1);//int varPosition, bool isPredictiveVariable, bool isOrgVar
				}
			}
			
		}
		for(int i = 0 ; i < m_maxNumberOfObjects ; i++)
		{
			m_schemaArr[i]->SchemaElementReadORwriteObjectToArr(   arrayFlex,  isWriteToArray, globals);
		}
		//9 13 22
		//m_regModel->SchemaElementReadORwriteObjectToArr(   arrayFlex,  isWriteToArray);
		//cPredictiveModel* m_regModel;

	}


cVariableSchemaArr::cVariableSchemaArr(int maxNumberOfObjects, int orgNumOfVars, bool* isPredictive,
														double** patientOrgArr, int numOfPatients)
{
	m_maxNumberOfObjects=maxNumberOfObjects;
	m_orgNumOfVars= orgNumOfVars;
	//m_augmentedNumOfVars=m_orgNumOfVars;//if there is augmentation it can grow up, else it stays, the functions stay

	m_schemaArr = NULL;
	if(m_maxNumberOfObjects > 0)
	{
		m_schemaArr = new cVariableSchemaObject*[m_maxNumberOfObjects];
		for(int i = 0 ; i < m_maxNumberOfObjects ; i++)
		{
			bool isPRedictive = false;
			bool isOrgVar= i < m_orgNumOfVars;
			if(isOrgVar)
			{
				if(isPredictive[i])
				{
					isPRedictive = true;
				}
			}
			m_schemaArr [i]=new cVariableSchemaObject(i, isPRedictive, isOrgVar, false, -1) ;
			//cVariableSchemaObject( int varPosition, bool isPredictiveVariable, bool isOrgVar)
		}		
	}	 
}




/*
//4 17 22 TO DO 0
void cVariableSchemaArr::AugmentPatient(double * augmentedPatientArr , double* orgPatientArr)
{
	//using schema and follow directions

	for(int j = 0 ; j < m_orgNumOfVars ; j++)
	{
		augmentedPatientArr[j]=orgPatientArr[j];
	}
	for(int j = m_orgNumOfVars ; j < m_augmentedNumOfVars ; j++)
	{
		augmentedPatientArr[j] = 0.0;
		if(m_schemaArr[j]->m_isPredictiveVariable)
		{
			augmentedPatientArr[j] = CalcualteAugmentedValue(orgPatientArr, j);  
		}
	}
}
*/

//4 17 22 TO DO 1 *  add some fields as a function to see if any of the below need to be part of the augmented ones , 
/* PRIMARY_RISK_CODE_FIELD_INDEX    HOSPITAL_LOS_PRED_INDEX     PRIMARY_RISK_CODE_FIELD_INDEX 
 COMORBIDITIES_PRED_INDEX  BMI_INDEX LIVE_WITH_INDEX  ADL_LONG_INDEX COGNITION_INDEX  PRIOI?
 */

/*
void cVariableSchemaArr::AddHardCodedRules()
{
	if(IS_WITH_AUGMENTED_FIELDS)
	{
		int indexOfNewObject = m_orgNumOfVars;

		AgeScale(indexOfNewObject++);
		//prmary, comorbidities, etc.

		m_augmentedNumOfVars = indexOfNewObject;//AgeScale is just one example and after adding all we can set the full 
		//nunber of orignial and augmented variables to be as the moving index is 
	}
}
*/

/*
void cVariableSchemaArr::AgeScale(int index)
{
	m_schemaArr[index]->m_isPredictiveVariable = true;
	m_schemaArr[index]->SetName("AgeScale");
	int ageOrgVarIndex = AGE_INDEX;
	m_schemaArr[index]->SetOrgIndex(ageOrgVarIndex);//ageOrgVarIndex);
	m_schemaArr[index]->SetIsOrgIndex(index < m_orgNumOfVars);
	m_schemaArr[ageOrgVarIndex]->SetIsToBeReplaced();
}
*/

//4 17 22 TO DO Debug
double cVariableSchemaArr::ConvertOriginalAgeToAgeScale(double orgAge)
{
	double ageScel = 0;
	//if(IS_TO_DIVIDE_BY_100 && orgAge > 100.0)
	{
	//	orgAge /= 100.0;
	}

	if(orgAge <40.0)
	{
		ageScel = 0;
	}
	if(orgAge <50.0)
	{
		ageScel = 1;
	}
	if(orgAge <60.0)
	{
		ageScel = 2;
	}
	if(orgAge <70.0)
	{
		ageScel = 3;
	}
	if(orgAge <80.0)
	{
		ageScel = 4;
	}
	if(orgAge >= 80.0)
	{
		ageScel = 5;
	}
	return ageScel;

}

/*
double cVariableSchemaArr::CalcualteAugmentedValue(double* orgPatientArr, int varIndex)
{
	//we got a list of hard coded augmentation. age scale, and more will come, such as comorbidities, etc. 
	//in come cases like age scale we also set the orignial variable to be "set tob e replaced"
	double augmentedValue = 0;
	if(m_schemaArr[varIndex]->IsNameOfVariable("AgeScale"))
	{
		int orgVarIndex = m_schemaArr[varIndex]->m_orgIndex;
		augmentedValue = ConvertOriginalAgeToAgeScale(orgPatientArr[orgVarIndex]);
	}
	return augmentedValue;	
}
*/
	




	cQuickHash ::cQuickHash (int size)
	{
		m_size = size;
		m_arr = new bool[m_size];
		
		ClearAllKeys();

	}

	cQuickHash::~cQuickHash ()
	{
		delete []m_arr;
	}


	void cQuickHash::ClearAllKeys()
	{
		for(int i = 0 ; i < m_size ; i++)
		{
			m_arr[i] = false; 
		}
	}

	bool cQuickHash::LookUpKey(int id)
	{
		int temp = id % m_size;
		if(m_arr[temp] )
		{
			return true;
		}
		return false;
	
	}

	void cQuickHash::SetKey(int id)
	{
		int temp = id % m_size ;
		m_arr[temp] = true;
	}
	
	 
	
	void cVariableAndValue::VarValObjPrepareArraysToOrFromDisc(cArrayFlex* flexArr, bool isWriteToArray, cGlobals &globals) //cArrayFlex *& array
	{
	//	flexArr->WriteReadArray( (unsigned char*)(&m_variableIndex),  sizeof(int), isWriteToArray);
		flexArr->WriteReadArrayInt( m_variableIndex, isWriteToArray ,  globals);
	
	//	flexArr->WriteReadArray( (unsigned char*)(&m_value),  sizeof(double), isWriteToArray);
		flexArr->WriteReadArrayDouble(m_value,   isWriteToArray, globals);
 	}

	
	cVariableAndValueAndPoints::cVariableAndValueAndPoints(cVariableAndValueAndPoints &other)
	{
		m_variableIndex= other.m_variableIndex;
		m_value =	other.m_value;
		m_points=	other.m_points;
	}



	void cVariableAndValueAndPoints::VarValObjPrepareArraysToOrFromDisc2(
		cArrayFlex* arrayFlex, bool isWriteToArray, cGlobals &globals,  int leadingSpaceNum, int index) //cArrayFlex *& array
	{
		int sdggg=0;

		char msgStr[1000];
		bool isWrite = true;
		//   "Variable Index": m_variableIndex,
		cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger(msgStr,  "Variable Index", m_variableIndex,
													leadingSpaceNum , true);
		arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

		cVarianceCalc::CreateStringWithCulumnAndQuotesAndDouble(msgStr, "Variable Value", 	m_value,  leadingSpaceNum,   true);
		arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);
	
		//COMA 
		//	cVarianceCalc::CreateStringFromIntegerAndComa(msgStr, 	m_variableIndex,  leadingSpaceNum ,true);
	//	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);



	//	cVarianceCalc::CreateStringFromIntegerAndComa(msgStr, 	m_value,  leadingSpaceNum ,true);
	//	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

	//	cVarianceCalc::CreateStringFromIntegerAndComa(msgStr, 	m_points,  leadingSpaceNum );
	//	arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);

		cVarianceCalc::CreateStringWithCulumnAndQuotesAndDouble(msgStr, "Value (Symetric) Odd Score", 
																	m_points,  leadingSpaceNum,   false);
		arrayFlex->WriteReadArrayString(msgStr, isWrite , globals);
	}

	void cVariableAndValueAndPoints::VarValObjPrepareArraysToOrFromDisc(cArrayFlex* flexArr, bool isWriteToArray, cGlobals &globals) //cArrayFlex *& array
	{
	//	flexArr->WriteReadArray( (unsigned char*)(&m_variableIndex),  sizeof(int), isWriteToArray);
		flexArr->WriteReadArrayInt( m_variableIndex , isWriteToArray ,  globals);


	//	flexArr->WriteReadArray( (unsigned char*)(&m_value),  sizeof(double), isWriteToArray);
		flexArr->WriteReadArrayDouble( m_value  , isWriteToArray, globals);

	//	flexArr->WriteReadArray( (unsigned char*)(&m_points),  sizeof(double), isWriteToArray);
		flexArr->WriteReadArrayDouble(  m_points , isWriteToArray, globals);
 	}
/*
//9 13 22 *  not ready
void	cPredictiveModel::SchemaElementReadORwriteObjectToArr( cArrayFlex* arrayFlex, bool isWriteToArray)
{
	arrayFlex->WriteReadArray( (bool*)(&m_temp) ,  sizeof(int), isWriteToArray);
}*/


double cPercentileCalculationModel::LookOutPointsFromArrayOfVarVarPoints(
	cVariableAndValueAndPoints*	weights,  int ratesListSize, int var, double val)
{
	double points=0.0;
	for(int i = 0 ; i < ratesListSize ; i++)
	{
		if((weights[i].m_variableIndex == var) && (weights[i].m_value == val))
		{
			points = weights[i].m_points;
			return points;
		}
	}
	return points;//should not be here
}
/*
double cPercentileCalculationModel::CalculatedAdjustedPoints(double odddChildModelPoints, 
	int grpNumberRootOddModel, int grpNumberRegModel, int numOfModelGrps)
{
	double adjustedPnts = odddChildModelPoints;
	double centerCatIndex = (double(numOfModelGrps-1)) / 2.0;
	if(odddChildModelPoints > 0.0)
	{
		double oddModelPositValue =  ((double)grpNumberRootOddModel ) - centerCatIndex ;
		double regModelPositValue =  ((double)grpNumberRegModel ) - centerCatIndex ;

		if( oddModelPositValue > 0.0 && regModelPositValue > 0.0 )
		{
			double ratio = regModelPositValue / oddModelPositValue;
			ratio =  cVarianceCalc::Max(ratio,0.4);
			ratio = cVarianceCalc::Min(ratio , 2.0);
			adjustedPnts = odddChildModelPoints * ratio;
		}
	
	}
	if(odddChildModelPoints < 0.0)
	{
		double oddModelNegVarl =  ((double)grpNumberRootOddModel ) - centerCatIndex ;
		double gerModelNegValue = ((double)grpNumberRegModel ) - centerCatIndex ;
		if(oddModelNegVarl<0.0 && gerModelNegValue<0.0)
		{
			double ratio = gerModelNegValue / oddModelNegVarl;
			ratio =  cVarianceCalc::Max(ratio,0.33);
			ratio = cVarianceCalc::Min(ratio , 3.0);
			adjustedPnts = odddChildModelPoints * ratio;
		}
	}
	

	return adjustedPnts;
}
*/
/*
double cPercentileCalculationModel::CalculatedAdjustedPointsNew(
	double odddChildModelPoints, 
	int grpNumberRootOddModel, int grpNumberRegModel, int numOfModelGrps)
{
	double adjustedPnts = odddChildModelPoints;
//	double centerCatIndex = (double(numOfModelGrps-1)) / 2.0;
	//int positiveBucketIndex = 
	if(odddChildModelPoints > 0.0)
	{
		int positiveOddBucketIndexRate = GetPositiveBucketIndex(
		double oddModelPositValue =  ((double)grpNumberRootOddModel ) - centerCatIndex ;
		double regModelPositValue =  ((double)grpNumberRegModel ) - centerCatIndex ;

		if( oddModelPositValue > 0.0 && regModelPositValue > 0.0 )
		{
			double ratio = regModelPositValue / oddModelPositValue;
			ratio =  cVarianceCalc::Max(ratio,0.4);
			ratio = cVarianceCalc::Min(ratio , 2.0);
			adjustedPnts = odddChildModelPoints * ratio;
		}
	
	}
	if(odddChildModelPoints < 0.0)
	{
		double oddModelNegVarl =  ((double)grpNumberRootOddModel ) - centerCatIndex ;
		double gerModelNegValue = ((double)grpNumberRegModel ) - centerCatIndex ;
		if(oddModelNegVarl<0.0 && gerModelNegValue<0.0)
		{
			double ratio = gerModelNegValue / oddModelNegVarl;
			ratio =  cVarianceCalc::Max(ratio,0.33);
			ratio = cVarianceCalc::Min(ratio , 3.0);
			adjustedPnts = odddChildModelPoints * ratio;
		}
	}
	

	return adjustedPnts;
}

*/




//9 13 22 **
/* 
each child odd model var val will search for the paralle root odd and reg models and be adjsuted

*/

int cPercentileCalculationModel::CalculatePositiveBucketIndex(int grpNumberModel)
{
//	int lowestPositiveBucketIndex = 0;
	for(int i = 0 ; i < m_numOfCgrs ; i++)
	{
		if(m_categThrs[i] > 0.0)
		{
			int ret = grpNumberModel -i;
			ret = cVarianceCalc::Max(ret , 0);
			return ret;
		}
	}
	return 0;
}


double cPercentileCalculationModel::GetSuggestedChangeInOdd( int grpNumberModel, int bucketIndexGap)
{
	double oddChageRet = 0.0;
	int otherBucketIndex = grpNumberModel + bucketIndexGap;
	if((otherBucketIndex >=0) && (otherBucketIndex < m_numOfCgrs))
	{
		if(  (m_categoriesValues[otherBucketIndex] != 0.0) && (m_categoriesValues[grpNumberModel] != 0.0))
		{
			oddChageRet =  m_categoriesValues[otherBucketIndex] -  m_categoriesValues[grpNumberModel];
		}
	}
	return oddChageRet;
}



void cPercentileCalculationModel::BuildAdjustedModel(
	cVariableAndValueAndPoints* adjustedChildRates, cVariableAndValueAndPoints* baseeChildRates,
	//cVariableAndValueAndPoints* rootOddWeightss,	cVariableAndValueAndPoints* regWeightss,
	int ratesListSize, 
	cPercentileCalculationModel* rootOddPredictiveModel, 
	cPercentileCalculationModel* regPredictiveModel)
{
	//double center = ((double)rootOddPredictiveModel->m_numOfCgrs ) / 2.0 ; 


	for(int i = 0 ; i < ratesListSize ; i++)
	{
		int var = baseeChildRates[i].m_variableIndex;
		double val = baseeChildRates[i].m_value;
		//points of this var val at the child profile odd model and base rates (before adjust)
		adjustedChildRates[i].m_points = baseeChildRates[i].m_points;
		double odddChildModelPoints = baseeChildRates[i].m_points;
		if(odddChildModelPoints != 0.0)
		{
			//odd points at root
			double rootOddPoints = LookOutPointsFromArrayOfVarVarPoints(
				rootOddPredictiveModel->m_varAndPoints,		ratesListSize, var, val);
			double regModelPoints = LookOutPointsFromArrayOfVarVarPoints(
				regPredictiveModel->m_varAndPoints,  ratesListSize, var, val);
			//for the same var val point of regreeeion model
			int numOfModelGrps = rootOddPredictiveModel->m_numOfCgrs;
			//grp number index for the odd model points based on percetile model
			int grpNumberRootOddModel = rootOddPredictiveModel->GetCategrIndex(rootOddPoints);
			int grpNumberRegModel = regPredictiveModel->GetCategrIndex(regModelPoints);
			double adjustePoits = odddChildModelPoints;
		//	if( (rootOddPoints != 0.0) && (regModelPoints != 0.0))
			if((regModelPoints != 0.0)&& (rootOddPoints > 0.0) && (regModelPoints > 0.0))
			{//given a category 5 should be 
				//for xample if root odd bucket is 7 and 5 is the frist one to be positve than we got postiive index 7-5 = 2
				int positveOddBucketIndex = rootOddPredictiveModel->CalculatePositiveBucketIndex(grpNumberRootOddModel);
				//if the we got buckt 5 only for the regression, still positve, but 2 down than
				int positveRegBucketIndex = regPredictiveModel->CalculatePositiveBucketIndex(grpNumberRegModel);
				//than bucket gap is 2, and it can also be -2 or any index gap
				int bucketGap = positveRegBucketIndex - positveOddBucketIndex;//for exmaple odd gets 5 and reg 6 than 6-5=1
				//if buckt gap is 2 or -2 we firt find the change around the odd group bucket gap from near by bucket (in the right
				///direction) and we then do 2 * X  where x is that angled per bucket gap to near by bucket
				double cangeSuggestInOdd = rootOddPredictiveModel->GetSuggestedChangeInOdd( grpNumberRootOddModel, bucketGap);
				if(cangeSuggestInOdd!= 0.0)
				{
					int asdg = 0 ;
				}
				adjustePoits = rootOddPoints + cangeSuggestInOdd;
				adjustePoits = cVarianceCalc::Min(adjustePoits , rootOddPoints * 2.0);
				adjustePoits = cVarianceCalc::Max(adjustePoits , rootOddPoints * 0.5);
			
				//adjustePoits = CalculatedAdjustedPoints(odddChildModelPoints, 
				//	grpNumberRootOddModel,	grpNumberRegModel, numOfModelGrps);
			}
			else
			{
				int ssdf = 0;
			}
			adjustedChildRates[i].m_points = adjustePoits;
		}
	}


}



cPercentileCalculationModel::cPercentileCalculationModel(
							cProfileObject* profile, int numOfCatgs )
    //  m_rootProfile->GetvarValPointsOddModel(), m_rootProfile->GetVarValPointsOddMOdelSize());
	
		//cVariableAndValueAndPoints* varAndPoints, int size)
	{
		m_varAndPoints = profile->GetOddRatioList();
		m_sizeOfModelArr= profile->GetVarValPointsOddMOdelSize();
		m_itemArr = profile->GetTwoDimPopulationArr();
		m_isIn = profile->GetIsInProfileArr();
		m_depArr = profile->GetDependentArray();
		m_numberOFItems = profile->GetSizeOfAllPopulation();

		m_numOfCgrs = numOfCatgs;
		m_categoriesValues = new double[m_numOfCgrs];
		m_categThrs = new double[m_numOfCgrs];
		m_samplePerCat = new int[m_numOfCgrs];

		for(int i = 0 ; i < m_numOfCgrs ; i++)
		{
			m_categoriesValues[i] = m_categThrs[i] = 0.0;
			m_samplePerCat[i]=0;
		}

		//Analytics();
	}
	

/*
	9 13 22 **
	here i am building a scale of 10 buckets with 10% of the oplation in each. a popuation
	is a list of person/variable/value  and the  points/odd rate that each member of this 
	population gets is based on the variable/value study of either odd ratio or regression
	the odd ratio calculated was stronger in potential for smaller set of persons that have
	a more rare value in some varibale. 
	it is important to put in a bcket as many as the patietns that have any var val points 
	that falls into that bucket range. the range will be such to captre 10% population so 





*/


bool cPercentileCalculationModel::IsItemPattenred(double &points, int itemIndex, int m)
{
	//m_itemArr[itemIndex]
	bool isMatch = false;
	points = 0.0;
	int modelVar = m_varAndPoints[m].m_variableIndex;
	double personValueForThisVar = m_itemArr[itemIndex][modelVar];
	double modelvalue = m_varAndPoints[m].m_value;
	if(personValueForThisVar  ==  m_varAndPoints[m].m_value )
	{
		isMatch = true;
		points = m_varAndPoints[m].m_points;
	}
	return isMatch;
}

int cPercentileCalculationModel::GetCategrIndex(double points)
{
	for(int i = 0 ; i < m_numOfCgrs ; i++)
	{
		if(points <= m_categThrs[i])
		{
			return i;
		}
	}
	return m_numOfCgrs -1;
}

void cPercentileCalculationModel::Analytics()
{
	double* pntArr = new double[m_sizeOfModelArr];
	double* wghArr = new double[m_sizeOfModelArr];
	for(int m = 0 ; m < m_sizeOfModelArr ; m++)
	{
		wghArr[m] = 0.0;
		pntArr[m] = m_varAndPoints[m].m_points;
		int var = m_varAndPoints[m].m_variableIndex;
		double val = m_varAndPoints[m].m_value;
		for(int i = 0 ; i < m_numberOFItems ; i++)
		{
			if(  (m_isIn == NULL) || (m_isIn[i] ) )
			{
				double  patnVal = m_itemArr[i][var];
				if(patnVal == val)
				{
					wghArr[m]+= 1.0; 
				}
			}
		}
	}
	double meanPnts= 0.0;
	double sdPnts = 0.0;
	cVarianceCalc::CalculateMeanAndSD(meanPnts, sdPnts, pntArr,wghArr,m_sizeOfModelArr);
	double center = ((double) (m_numOfCgrs -1)) / 2.0;
	int indexOFCEnter = -1;
	if(m_numOfCgrs == 10)
	{
		indexOFCEnter = 4;//
		for(int x = 0 ; x< m_numOfCgrs ; x++)
		{
			int gap = x - indexOFCEnter;
			m_categThrs[x] = gap * sdPnts;
		}
	}
	else
	{
		for(int x = 0 ; x< m_numOfCgrs ; x++)
		{
			double shift = double(x) - center;//if center is 4.5 than 
			//if ( ((shift ) ) < 1.0) 
			m_categThrs[x] = shift * sdPnts;   //+ 0.5;
			//0: -4,  1: -3, 2: -2, 3: -1, 4: -0, 5:1, 
		}
	}

//	cVarianceCalc::PrepareMapOfValuesForDecilesGrouping(
	//	 m_categThrs ,  m_numOfCgrs , pntArr,	 ,  m_sizeOfModelArr);

//for each item / patient, from the data, and then for each model ovbject
//that match this person (specific var val) we then push sample cases with
	//such points to create a map of points categories and their threshod
	//and average points witin each (not sure why i need the avg points)
	for(int i = 0 ; i < m_numberOFItems ; i++)
	{
		if(  (m_isIn == NULL) || (m_isIn[i] ) )
		{
			for(int m = 0 ; m < m_sizeOfModelArr ; m++)
			{
				double points = 0.0;
				bool isRelevant = IsItemPattenred(points,  i,  m);
				if(isRelevant)
				{
					int catIndex = GetCategrIndex(points);
					m_categoriesValues[catIndex] += points;
					m_samplePerCat[catIndex]++;
				}
			}
		}
	}
	for(int x = 0 ; x < m_numOfCgrs ; x++)
	{
		if(m_samplePerCat[x] > 0)
		{
			m_categoriesValues[x] /= m_samplePerCat[x] ;
		}
	}

	delete []pntArr;
	delete []wghArr;

}





void cInterventionObject::FillInterventionMemebers( double** twoDim, double* depArr, bool* isIn, int size,
		cProfileObject* profile, int numOfSubGrps)
{
	
		m_sizeOfProfilePop = 0;
		m_sizeOFProfileIntervePop=0;
		m_numOfSubGrps=  numOfSubGrps;
		m_interventionAdjustArr=new double[m_numOfSubGrps];
		double* alternativeAvgDepArraWithInter = new double[m_numOfSubGrps];
		double* alternativeAvgDepArraWithOutInter = new double[m_numOfSubGrps];
		double* alternativeAvgDepWghArraWith = new double[m_numOfSubGrps];
		double* alternativeAvgDepWghArraWithout = new double[m_numOfSubGrps];

		for(int x = 0 ; x< m_numOfSubGrps ; x++)
		{
			m_interventionAdjustArr[x]=0.0;
			alternativeAvgDepArraWithInter[x] = 0.0;
			alternativeAvgDepArraWithOutInter[x]=0.0;
			alternativeAvgDepWghArraWith [x] = 0.0;
			alternativeAvgDepWghArraWithout[x] = 0.0;
		} 
		for(int i = 0 ; i < size ; i++)
		{
			if(isIn == NULL  || isIn[i])
			{
				m_sizeOfProfilePop++;
				if(twoDim[i][m_interventionVariableIndex] > 0.0)
				{
					m_sizeOFProfileIntervePop++;
					bool isWithFineTuning = false;
					int subGrpIndexForThisPt = profile->GetPatientIndexFromPatinetData( twoDim[i],isWithFineTuning);
					double wgh = twoDim[i][m_interventionVarPropsIndex];
					alternativeAvgDepWghArraWith [subGrpIndexForThisPt] += wgh;
					alternativeAvgDepArraWithInter[subGrpIndexForThisPt] += wgh * depArr[i];
					if(depArr[i]>0.0)
					{
						int sdfg = 0;
					}
				}// 
				else
				{
					bool isWithFineTuning = false;
					int subGrpIndexForThisPt = profile->GetPatientIndexFromPatinetData( twoDim[i], isWithFineTuning);
					double wgh = twoDim[i][m_interventionVarPropsIndex];
					alternativeAvgDepWghArraWithout [subGrpIndexForThisPt] += wgh;
					alternativeAvgDepArraWithOutInter[subGrpIndexForThisPt] += wgh * depArr[i];
					if(depArr[i]>0.0)
					{
						int sdfg = 0;
					}
				}
			
			}
		}
/* i have the avg dep per sub grp x for all 5 group
i also have a tendency/propensity per person for those that got or did not get intervention
so with that i can weight those that are wtih a yes, according to their porpensity, 
as well as weight those that are with a no, speararly
		
		alternativeAvgDepArra[x] after divided by the sum weights under sub grop x
		i get a weighted avg dep for those that 
		
		*/

		for(int x = 0 ; x< m_numOfSubGrps ; x++)
		{
			if(alternativeAvgDepWghArraWith[x] > 0.0)
			{
				alternativeAvgDepArraWithInter[x] /= alternativeAvgDepWghArraWith [x] ;
			}
			if(alternativeAvgDepWghArraWithout[x] > 0.0)
			{
				alternativeAvgDepArraWithOutInter[x] /= alternativeAvgDepWghArraWithout [x] ;
			}
			m_interventionAdjustArr[x] = 0.0;
			double bucketavgDepValue = profile->GetSubGroupAverageDependentArr()[x];
			if(bucketavgDepValue > 0.0)
			{
				double interventionGap =  0.0;
				if((alternativeAvgDepArraWithInter[x] > 0.0) && (alternativeAvgDepArraWithOutInter[x] > 0.0))
				{
					interventionGap =      alternativeAvgDepArraWithInter[x] -
						                       alternativeAvgDepArraWithOutInter[x];
					m_interventionAdjustArr[x] = 	interventionGap / bucketavgDepValue;
				}
			}
		}//12 2 22 check how we bypass this area of there is no any intervetnion in the metadata
		

		delete []alternativeAvgDepArraWithInter;
		alternativeAvgDepArraWithInter=NULL;
		delete []alternativeAvgDepArraWithOutInter ;
		alternativeAvgDepArraWithOutInter =NULL;
		delete []alternativeAvgDepWghArraWith;
		alternativeAvgDepWghArraWith=NULL;
		delete []alternativeAvgDepWghArraWithout;
		alternativeAvgDepWghArraWithout=NULL;

}
	




	int cResearchDataObj::GetBestStretch(double* stretchArr ,  bool* isTaken,  int size)
	{
		int bestIndex=-1;
		double maxVal=0.0;
		for(int j = 0 ; j < size ; j++)
		{
			if(!isTaken[j])
			{
				if(stretchArr[j] > maxVal)
				{
					maxVal = stretchArr[j];
					bestIndex = j;
				}
			}
		}
		return bestIndex;	
	}

	double cResearchDataObj::CalcVariableStretch( int indexToStretch, double anchorVal)
	{
		double avgDepPerDepVal[10];
		int cntArr[10];
		int lenth = 10;
		for(int j = 0 ; j < lenth ; j++)
		{
			avgDepPerDepVal[j]=0.0;
			cntArr[j]=0;
		}
		for(int i = 0 ; i < m_numOfItems ; i++)
		{
			double val = m_twoDimArray[i][indexToStretch];
			int intVal = int(val);
			if(intVal < lenth)
			{
				avgDepPerDepVal[intVal] += m_depArr[i];
				cntArr[intVal] ++;
			}
			else
			{
				avgDepPerDepVal[lenth-1] += m_depArr[i];
				cntArr[lenth-1] ++;
			}
		}
		double depAvg = 0.0;
		double totalCnt = 0;
		for(int j = 0 ; j < lenth ; j++)
		{
			if(cntArr[j]>0)
			{
				avgDepPerDepVal[j]  /= cntArr[j];
				depAvg += (avgDepPerDepVal[j]*cntArr[j]);
				totalCnt += cntArr[j];
			}
		}
		depAvg /= totalCnt;

		double stretch= cResearchObject::StretchLoop( avgDepPerDepVal,  cntArr,   lenth , anchorVal);
		return stretch ;
	}
	void cResearchDataObj::CapIsPredictiveOptionsPerStretch(bool* isPedictive, int cap, double anchorVal)
	{
		int numPred = 0;
		for(int j = 0 ; j < m_sizeOfItem ; j++)
		{
			if(isPedictive[j])
			{
				numPred++;
			}
		}
		if(cap >= numPred)
		{
			return;
		}
		double* stretch = new double[m_sizeOfItem];
		for(int j = 0 ; j < m_sizeOfItem ; j++)
		{
			stretch[j]=0.0;
			if(isPedictive[j])
			{
				stretch[j] = CalcVariableStretch(j, anchorVal);
			}
		}
		bool* newPredSet = new bool[m_sizeOfItem];
		bool* isTaken = new bool[m_sizeOfItem];
		for(int j = 0 ; j < m_sizeOfItem ; j++)
		{
			newPredSet[j]=false;
			isTaken[j]=false;
		}
		for(int k = 0 ; k < cap ; k++)
		{
			int best = GetBestStretch( stretch ,isTaken,  m_sizeOfItem);
			isTaken[best] = true;
			newPredSet[best]=true;
		}
		for(int j = 0 ; j < m_sizeOfItem ; j++)
		{
			isPedictive[j] = newPredSet[j];
		}

		delete []isTaken;
		isTaken=NULL;
		delete []newPredSet;

		delete []stretch;
		stretch=NULL;

	}
 

	cEvolutionProfilePAckage::cEvolutionProfilePAckage(cProfileObject* anchor, cResearchDataObj* anchorResOBj, int numOfGrps)
	 {
		m_anchor = anchor;
		m_anchorResOBj = anchorResOBj;
		m_proffListMaxSize = PROFILE_LIST_PER_ANCHOR_MAX_NUMBER;//just in case //7 11 23 * 12 changed 1000 to 5000
		m_proffListSize = 0;
		m_profList = new cProfileObject*[m_proffListMaxSize];
		for(int p = 0 ; p > m_proffListMaxSize ; p++)
		{
			m_profList[p] = NULL;
		}
		m_profList[m_proffListSize++]=m_anchor;
		m_numOfGrps = numOfGrps;
		m_degAvgArr = new double[m_numOfGrps];
		m_thresArr = new double[m_numOfGrps];
		m_cntArr = new int[m_numOfGrps];
		for(int x = 0 ; x< m_numOfGrps ; x++)
		{
			m_degAvgArr[x] = m_thresArr[x] = 0.0;
			m_cntArr[x] =0;
		}
	 }


	
double cEvolutionProfilePAckage::Calibrate(double predRAw)
{
	int bucketIndex = cProfileObject::GetSubGrpIndex(predRAw , m_thresArr, m_numOfGrps);
	double calibratedPRediction = m_degAvgArr[bucketIndex];
	return calibratedPRediction;
}


int cEvolutionProfilePAckage::CollectProfilesFromLevelInput( cProfileObject** pArr, int level, int maxProfNum  )
{
	int movingIndex=0;
	for(int i = 0 ; i < m_proffListSize ; i++)
	{
		if( m_profList[i]->GetInclusionRuleListSize()==level)
		{
			pArr[movingIndex++]=m_profList[i];
		}
	}
	return movingIndex;
}


int cEvolutionProfilePAckage::FindHieghtsLevel( )
{
	int  highestLEvel = 0;
	for(int i = 0 ; i < m_proffListSize ; i++)
	{
		if( m_profList[i] != NULL)
		{
			highestLEvel = cVarianceCalc::Max(highestLEvel , m_profList[i]->GetInclusionRuleListSize());
		}
	}
	return highestLEvel;
}


void  cEvolutionProfilePAckage::SetProfilesAdvancedPerfScores(double val)
{
	for(int i = 0 ; i < m_proffListSize ; i++)
	{
		if( m_profList[i] != NULL)
		{
			m_profList[i]->SetProfilesAdvancedPerfScores(val);
		}
	}
}

int cEvolutionProfilePAckage::ClearProfilesAdvancedPerfScores(double val)
{

	int  highestLEvel = 0;
	for(int i = 0 ; i < m_proffListSize ; i++)
	{
		if( m_profList[i] != NULL)
		{
			m_profList[i]->ClearAdvancedPerformance(val);
			highestLEvel = cVarianceCalc::Max(highestLEvel , m_profList[i]->GetInclusionRuleListSize());
		}
	}
	return highestLEvel;
}


void cEvolutionProfilePAckage::SetCalibrationArraysFromPredArr(double* predArr, cGlobals* globals)
{
	cProfileObject::CalculateThresholds(m_thresArr , m_numOfGrps, predArr,NULL,  m_anchorResOBj->m_numOfItems);
	double depAvg = 0.0;
	//6 23 23 * debug and see if i actually get the 0 to m_numOfGrps-1 options for the output bucket index  ?
	int* bucketIndexArr = new int[m_anchorResOBj->m_numOfItems];
	cProfileObject::CreateAvgDepSubGrps(bucketIndexArr, m_degAvgArr,m_thresArr ,m_cntArr, depAvg,
					m_numOfGrps,predArr,m_anchorResOBj->m_depArr, NULL,  m_anchorResOBj->m_numOfItems, *globals);
	
}

void cResearchObject::EvolutionProfilesIncludingPerformanceAdvancte(cEvolutionProfilePAckage* evolPackag, InputVariablesPackageForResearchObj* inputVarObj,
	                cGlobals* globals, cPercentileCalculationModel* rootOddPredictiveModel, cPercentileCalculationModel*  regPredictiveModell)
{
	 //take cProfileObject**   m_profList, size m_proffListSize , and extend. keep m_proffListMaxSize in mind
	int edg=0;

		//EvolutionProfilesIncludingPerformanceAdvancte(evolPackage[ii]->,);

	int currenRuleLength =  evolPackag->m_profList[0]->GetInclusionRuleListSize();
	int maxNiumOfRuleToAchive = currenRuleLength + globals->g_MAX_LEVELS_IN_PROFILING_EVOLUTION;//7 6 23

	double anchrHere=  evolPackag->m_anchor->GetProfileDepAverage();
	bool isThisCaseOfAnchorUniverse2 = false;
	if(IS_ANCHOR_UNIVERSE_CROSS_ANCHORS  && isThisCaseOfAnchorUniverse2)//7 6 23 -2
	{
		anchrHere = evolPackag->m_anchor->GetRootProfile()->GetProfileDepAverage();
	}

	BuildResearchElementsWhileLoop(	 evolPackag->m_profList,evolPackag->m_proffListSize,
		evolPackag->m_anchorResOBj,	 inputVarObj ,  *globals, globals->g_MAX_NUM_OF_ITERATIONS ,  
		evolPackag->m_proffListMaxSize - evolPackag->m_proffListSize , 
		evolPackag->m_anchor,	 rootOddPredictiveModel,  regPredictiveModell, anchrHere,maxNiumOfRuleToAchive );
			//int numPrflsAnchorAndDown = movingProfleIndex;
	//FillProfileListObjectsWothAdvancedPerformanceNew2(evolPackag->m_profList,evolPackag->m_proffListSize, 	evolPackag->m_anchor,
	//			evolPackag->m_anchorResOBj,  globals, m_numberOfSubGrps,  anchrHere, isThisCaseOfAnchorUniverse2);
	 

	for(int i=0; i<	evolPackag->m_proffListSize ; i++)
	{
		evolPackag->m_profList[i]->SetPerformanceToDefault(1.0);
		//	SetProfileAdvancedPerformance(

	}

}

	cScoreGrpArr::cScoreGrpArr(cProfileObject* prof)
	{
		CopyProfArr(prof);	 
	}

	
	void cScoreGrpArr::CopyProfArr(cProfileObject* prof)
	{
		for(int i = 0 ; i < SCORE_GRP_NUM ; i++)
		{
			m_scoreArr[i]=prof->GetProfileAdvancedPerformance(i);
		}	
	}
	