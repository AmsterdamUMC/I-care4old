
#include <iostream>

#include "cSimilarityFormula.h"
#include "cProfileTarget.h"
#include "TargetSort.h"


#include <math.h>
#include "math.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <windows.h>




using std::cout;
using std::endl;

using namespace std;

//////C Functions/////////////////////


//SET UP PROFILES - BUILD  or CALL FROM DISK
//	'B' means "Build"  profiles and then write to disk    
//[ 'A' means "Already built"  when profiles were done befoer and just need now to read profiles from disk


 


void BuildResearcObjectOrLoadFromDist(cResearchObject* researchObj, cGlobals *globals,
									InputVariablesPackageForResearchObj* inputVarObj ,  int depVarIndex)
{
	if(globals->g_profileBuildMode == 'B' || globals->g_profileBuildMode == 'b')
	{
		//OPEN DATA OBJET
		cResearchDataObj* resarchDataObjj = new cResearchDataObj;
		//this one input numberOfVars neeeded from the inputVarObj prepared meta elements for research  object initialization
		resarchDataObjj->m_sizeOfItem = inputVarObj->m_numberOfVariables;
		//GET DATA FROM DISC into the data object
		FileManager::DownloadInputDataFile(  resarchDataObjj ,globals->g_patientLearningFilePAth, depVarIndex,   
										globals->g_endOfLineInSign,globals->g_delimiter, globals );
		
		bool* isPersonInProfSubb = new bool[resarchDataObjj->m_numOfItems];
		for(int i = 0 ; i < resarchDataObjj->m_numOfItems;i++)
		{
			isPersonInProfSubb[i]=false;
			if(DEFINE_FILTER==0)
			{
				if(resarchDataObjj->m_twoDimArray[i][0] == 0)
				{
					isPersonInProfSubb[i]=true;
				}
			}
			else if(DEFINE_FILTER == 1)
			{
				if(resarchDataObjj->m_twoDimArray[i][0] > 0)
				{
					isPersonInProfSubb[i]=true;
				}
			}
			else
			{
				isPersonInProfSubb[i]=true;
			}
		}
		//FillIsInProfSub(bool* isPersonInProfSub,cProfileObject** profileArr, int p,  int x, cResearchDataObj* researchDataObj, bool* isInContext);
		cResearchDataObj* subResObj = new cResearchDataObj(resarchDataObjj, isPersonInProfSubb);




		//UPDATE SCHEME WITH VAR STATS
		researchObj->UpdateVariableValuesPRevelance(subResObj);

		int maxNumOfProfiles =  researchObj->GetMaxNumberOfProfiles();
		//CREATE PROFILES ACCORDING TO APPLCATION DESIGN IN META FILE
		bool*	isTerminalProfileArr = new bool[maxNumOfProfiles];
		for(int tr = 0 ; tr < maxNumOfProfiles ; tr++)
		{
			isTerminalProfileArr[tr] = false; 
		}
		researchObj->BuildResearchElements(subResObj, isTerminalProfileArr, inputVarObj ,*globals);
		delete []isTerminalProfileArr;
		isTerminalProfileArr=NULL;
		//WRITE PROFILES TO DISK TO ENABLE THIS RUN BUT ALSO OTHERS TO CALL OBJET UP READY FOR PREDICTION
		
		double* predArr = new double[subResObj->m_numOfItems];
		bool* isPersonIn = NULL;
		int numOfPerformanceSubGrps = globals->g_NUMBER_OF_CALIBRATION_GRPS;
		double* threshArr = new double[numOfPerformanceSubGrps];
		double* avgDepArr = new double[numOfPerformanceSubGrps];
		int* cntArr = new int[numOfPerformanceSubGrps];
		int modePRed=0;
		bool withExtremeDimension = true;
		bool isThisCaseOfAnchorUniverse7=true;
		bool isWithFineTuning=true;
		researchObj->DFGHJ( threshArr ,   avgDepArr ,  cntArr,	 predArr,NULL,NULL,NULL, isPersonIn,
								subResObj,  globals,  numOfPerformanceSubGrps,
								researchObj->GetProfileListArray(),
									researchObj->GetNumberOfProfiles(),modePRed,withExtremeDimension ,isThisCaseOfAnchorUniverse7  , isWithFineTuning );

		if(false) //to show different tests such as only patients with grp 5 out of the 1-8 groups
		{
			isPersonIn = new bool[ subResObj->m_numOfItems];
			for(int i = 0 ; i < subResObj->m_numOfItems;i++)
			{
				isPersonIn[i] = false;
				if(subResObj->m_twoDimArray[i][2] == 5)
				{
					isPersonIn[i] = false;
				}
			}
			int modePRed=0.0;
			bool isWithFineTuning=true;
			researchObj->DFGHJ( threshArr ,   avgDepArr ,  cntArr,	 predArr,NULL,NULL,NULL, isPersonIn,
								subResObj,  globals,  numOfPerformanceSubGrps,
								researchObj->GetProfileListArray(),
									researchObj->GetNumberOfProfiles() ,modePRed , withExtremeDimension, true,  isWithFineTuning );
			int sdg =0;
		}



	
		/*
		researchObj->Predict ionTasks( predArr,resarchDataObj->m_twoDimArray,  isPersonIn,  
						resarchDataObj->m_numOfItems, resarchDataObj->m_sizeOfItem ,  globals);

		int numOfPerformanceSubGrps = globals->g_NUMBER_OF_CALIBRATION_GRPS;
		double* threshArr = new double[numOfPerformanceSubGrps];
		double* avgDepArr = new double[numOfPerformanceSubGrps];
		int* cntArr = new int[numOfPerformanceSubGrps];
		//6 13 23 call a  function fathers what doing already within the loop and perf tests.
		cProfileObject::CalculateThresholds(threshArr , numOfPerformanceSubGrps, 
										predArr,isPersonIn,resarchDataObj->m_numOfItems);
		double depAvg = 0.0;
		cProfileObject::CreateAvgDepSubGrps(avgDepArr,threshArr ,cntArr, depAvg,
					numOfPerformanceSubGrps,predArr,resarchDataObj->m_depArr, isPersonIn, 
													resarchDataObj->m_numOfItems, *globals);

			*/		
		bool isWriteModeReport=true;
		cArrayFlex* arrayFlexReport = new cArrayFlex("profile_report.txt",isWriteModeReport);
		arrayFlexReport->WriteReadArrayString("number of buckets",isWriteModeReport,*globals);//add a new param sayingn "add "  " or not add to print and sse
		//that it is also ok when reading back
		arrayFlexReport->WriteReadArrayInt(numOfPerformanceSubGrps,isWriteModeReport,*globals);
		arrayFlexReport->WriteReadArrayString("bucket values:",isWriteModeReport,*globals);
		for(int i = 0 ; i < numOfPerformanceSubGrps; i++)
		{
			arrayFlexReport->WriteReadArrayString("   buckets index",isWriteModeReport,*globals, true);
			arrayFlexReport->WriteReadArrayInt(i,isWriteModeReport,*globals);
			arrayFlexReport->WriteReadArrayString("   buckets highThr:",isWriteModeReport,*globals, true);
			arrayFlexReport->WriteReadArrayDouble(threshArr[i],isWriteModeReport,*globals);
			arrayFlexReport->WriteReadArrayString("   buckets value:",isWriteModeReport,*globals, true);
			arrayFlexReport->WriteReadArrayDouble( avgDepArr[i],isWriteModeReport,*globals);
			arrayFlexReport->WriteReadArrayString("   buckets count:",isWriteModeReport,*globals, true);
			arrayFlexReport->WriteReadArrayInt(cntArr[i],isWriteModeReport,*globals);
		}

		delete arrayFlexReport;
	



		if(isPersonIn!= NULL)
		{
			delete []isPersonIn;
			isPersonIn=NULL;
		}
		delete []predArr;
		predArr=NULL;
		delete []threshArr;
		threshArr=NULL;
		delete []avgDepArr;
		avgDepArr=NULL;
		delete []cntArr;
		cntArr=NULL;

		delete []isPersonInProfSubb;
		isPersonInProfSubb=NULL;

		bool isWriteMode=true;
		cArrayFlex* arrayFlex = new cArrayFlex(globals->g_readwriteArraFlex,isWriteMode);
		researchObj->ResObjWriteOrRerad(   arrayFlex , *globals );

		cArrayFlex* arrayFlex2 = new cArrayFlex(TEMP_FILE_PATH_FOR_UPLOAD_TO_DASHBOARD,isWriteMode);
		researchObj->ResObjWriteOrReradMor2(   arrayFlex2 , *globals );


	//	arrayFlex->WriteArrayToDisc();	// ?? maybe no need of previous alrady goes directoy to disck
		delete arrayFlex;
		arrayFlex = NULL;
		
		delete arrayFlex2;
		arrayFlex2=NULL;

		delete subResObj;
		subResObj=NULL;

		//deletes
		delete resarchDataObjj;	
		resarchDataObjj = NULL;

		//PAUSE 
		int sdf=0;
		cin >> sdf;


	}//'A' is to read ready profiles from disk
	else if(globals->g_profileBuildMode == 'A' || globals->g_profileBuildMode == 'a')
	{//12 2 22 *** develop and debug how to get back from disc . only focus on getting profiles back from disk. see that i can 
		//continue with all perofrmance  tests of the calling function flow, so it is the same but only from disk this time
		bool isWriteMode=false;
		cArrayFlex* arrayFlexx = new cArrayFlex(globals->g_readwriteArraFlex, isWriteMode);
		//arrayFlexx->ReadArrayFromDisc();	// ??? maybe no need
		researchObj->ResObjWriteOrRerad(   arrayFlexx, *globals);//read frmo disk

		
		delete arrayFlexx;
		arrayFlexx = NULL;
		//now sleep and check andn sleep, each time check for query file od a patinet and thrugh back a file with predicitons, then go to sleep thenn n see more
		//once getting a certain stop file than exit
	}

} 

//12 2 22 *** ***
void PrintPredictionsAndPerformanceReportToFile( cArrayFlex &arrayFlex, int profilePerfTestMode, double* avgDepArr , int* cntArr,
				cCalibrationContextObj* calibObj,int numOfCallibrationGrps, double* predArr,
				cPredictionContextObj** predictionContextObjArray,	int* sizeOfPredContObj,
				int arrSize , cGlobals &globals , bool isToPrintPredictionArray )
{
	arrayFlex.WriteReadArrayString(  "test mode number: " , true, globals );
	//print int profilePerfTestMode 
	arrayFlex.WriteReadArrayInt(profilePerfTestMode,true ,  globals);
	arrayFlex.Enter(true, globals.g_endOfLineInSign);
	//print string with "number of persons"
	arrayFlex.WriteReadArrayString(  "number of persons: " , true, globals );
	//print arrSize
	arrayFlex.WriteReadArrayInt(arrSize,true ,  globals);
	arrayFlex.Enter(true, globals.g_endOfLineInSign);
	if(isToPrintPredictionArray)
	{
		arrayFlex.WriteReadArrayString(  "prediction list start:" , true, globals );
		for(int i = 0 ; i < arrSize ; i++)
		{
			arrayFlex.WriteReadArrayString(  "person index:" , true, globals );
			arrayFlex.WriteReadArrayInt(i ,true, globals);
			arrayFlex.WriteReadArrayString(  "this person prediction:" , true, globals ); 
			arrayFlex.WriteReadArrayDouble(predArr[i],true, globals);
		//	arrayFlex.Enter(true, globals.g_endOfLineInSign);
			if(predictionContextObjArray != NULL && predictionContextObjArray[i] != NULL)
			{
				arrayFlex.WriteReadArrayString(  "profile ID list that matched this person, size: " , true, globals ); 
				arrayFlex.WriteReadArrayInt(sizeOfPredContObj[i] ,true, globals);
				for (int x = 0 ; x< sizeOfPredContObj[i] ; x++)
				{
					arrayFlex.WriteReadArrayString(  "profile ID: " , true, globals ); 
					arrayFlex.WriteReadArrayInt(predictionContextObjArray[i][x].m_profileID,true, globals);
					arrayFlex.WriteReadArrayString(  "this profile based prediction: " , true, globals ); 
					arrayFlex.WriteReadArrayDouble(predictionContextObjArray[i][x].m_prediction,true, globals);
					arrayFlex.WriteReadArrayString(  "sub risk group index: " , true, globals ); 
					arrayFlex.WriteReadArrayInt(predictionContextObjArray[i][x].m_subGrpIndex,true, globals);
					arrayFlex.WriteReadArrayString(  "profile weight: " , true, globals ); 
					arrayFlex.WriteReadArrayDouble(predictionContextObjArray[i][x].m_weight,true, globals);
				}
			}
			else
			{
				int sdgg = 0 ;
			}
			arrayFlex.Enter(true, globals.g_endOfLineInSign);
		}
		arrayFlex.WriteReadArrayString(  "prediction list end:" , true, globals );
	}
	arrayFlex.Enter(true, globals.g_endOfLineInSign);
	arrayFlex.WriteReadArrayString(  "numbre of risk groups: " , true, globals ); 
	arrayFlex.WriteReadArrayInt(numOfCallibrationGrps,true ,  globals);
	arrayFlex.Enter(true, globals.g_endOfLineInSign);
	arrayFlex.WriteReadArrayString(  "population size per each risk group: " , true, globals ); 
	for(int j = 0 ; j < numOfCallibrationGrps ; j++)
	{
		arrayFlex.WriteReadArrayInt(cntArr[j],true, globals);
		//arrayFlex.WriteReadArrayChar( globals.g_delimiter, true, globals);
	}
	arrayFlex.Enter(true, globals.g_endOfLineInSign);
	arrayFlex.WriteReadArrayString(  "value per each risk group: " , true, globals ); 
	for(int j = 0 ; j < numOfCallibrationGrps ; j++)
	{
		arrayFlex.WriteReadArrayDouble(avgDepArr[j],true, globals);
		//arrayFlex.WriteReadArrayChar(  globals.g_delimiter, true, globals);
	}
	arrayFlex.Enter(true, globals.g_endOfLineInSign);
	 
}


/////////////////EVOLUTION ENHANCEMENTS (and other general changes)  /////////////////////////////////////////
//  1- add a new isIn param that if it is not NULL it supports to predict only for test patients that have any 
//        relevant profile added. when doing that , and when that isIn is not NULL,  and a  reason to even do any predict process .
//  2-here, send pre calcuualed prediciton array to those with isIn[i] = false, to complete a full predeictionArr, and to then
//be used as an input in the PrepareCalibrationElements() to 
//have the calbObj full with perf elements and viewed out

//3- use the calblObj created, if senet as NULL, to be the performance meassure in evolution time. 
// after calling to PredictPatientS etAndGetPErformanceELemets( , , , isIn) with the new isIn , it will collect the 

// 4- collecting all "numOFCalibrationGrps" as an above api
//        to have a higher sensitivity to small changes as one profile . cancel the define and replace from the object and to
//   the function input to be flexible, use higiher number in evolution and check sum of stretch of all grps and from the avg of 
// all patients. see that each grp is at least 500 size for low rate dependent cases 
//5- add to cCalibrationContextObj object  a funcion to memassure the stretch of the calibration gruops from the  middle using the
//sample size array of each grups to have a weighted average and weighted stretch




bool OpenDataObjAndPerformQueriesAndReport(	cCalibrationContextObj*& calbObj, char* dataFilePAthhIn, 
	  InputVariablesPackageForResearchObj* inputVarObj,	
	int depVarIndex, char endOfLineSign, char delimiter,  cResearchObject* researchObj,
	int profileInclusionMode, bool isWithCalibration , cGlobals &globals ,
					   cArrayFlex &arrayFlexx, 
					   bool isToPrintPredictionArray, bool isWithFineTuning//, ios::out);//21 2 12 get nput from above so can apend each print with new test in one same file.
	)

{

	cResearchDataObj* testDataObj = new cResearchDataObj;
	testDataObj->m_sizeOfItem =  inputVarObj->m_numberOfVariables;
	FileManager::DownloadInputDataFile(  testDataObj , dataFilePAthhIn,  depVarIndex, 
		endOfLineSign, delimiter, &globals);
	int numOfPredictionItems = testDataObj->m_numOfItems;
	double* predictionArr = new double[numOfPredictionItems];
	double* predictionWithInArr = new double[numOfPredictionItems];
	double* predictionWithoutInArr = new double[numOfPredictionItems];
	double thresArr[100];
	double avgDepArr[100];
	int cntArr[100];
	double depAvg = 0.0;
	bool isAdvancedPerfGetbEstMatch = globals.g_IS_ADVANCED_PERF_FOR_GET_BEST_MATCH;
	int indexOfIntervetionFieldToAdjustPrediction = -1; //12 2 22 *** connect with a case when we do want to have an intervetnion call either a file or real time
	
	cPredictionContextObj** predictionContextObjArray= NULL;
	int* sizeOfPredContObj=NULL;
	if(isToPrintPredictionArray)
	{
		predictionContextObjArray = new cPredictionContextObj*[numOfPredictionItems];
		sizeOfPredContObj = new int[numOfPredictionItems];
		for(int i = 0 ; i < numOfPredictionItems ; i++)
		{
			predictionContextObjArray[i] = NULL;
			sizeOfPredContObj[i] = 0;
		}
	}
		
	double anchorDepForBestMatch=0.0;//no need just api , when isWithTest is false
	bool isWithTest = false;
	bool isStragiht = false;
	researchObj->PredictPatientSetAndGetPErformanceELemets(anchorDepForBestMatch, predictionArr,  
		predictionWithInArr,  predictionWithoutInArr,
		 predictionContextObjArray,   sizeOfPredContObj,	thresArr,	avgDepArr, cntArr,depAvg,	
				testDataObj->m_twoDimArray,	testDataObj->m_depArr, 	numOfPredictionItems,testDataObj->m_sizeOfItem,	calbObj, 
					profileInclusionMode , 	isWithCalibration, globals.g_NUMBER_OF_CALIBRATION_GRPS, NULL, 
					isAdvancedPerfGetbEstMatch, 
					indexOfIntervetionFieldToAdjustPrediction, globals, 
					isWithFineTuning, NULL  ,0.0, isStragiht);

	if(calbObj == NULL)
	{
		int numOfCallibrationGrps = globals.g_NUMBER_OF_CALIBRATION_GRPS;
		calbObj = new cCalibrationContextObj(numOfCallibrationGrps);
		calbObj->PrepareCalibrationElements(
			predictionArr, testDataObj->m_depArr, numOfPredictionItems,  globals);
	}
	bool ret = true;

	PrintPredictionsAndPerformanceReportToFile(
			arrayFlexx, profileInclusionMode, avgDepArr , cntArr,  
			calbObj, globals.g_NUMBER_OF_CALIBRATION_GRPS, predictionArr,
			 predictionContextObjArray,  sizeOfPredContObj,
				numOfPredictionItems ,globals, isToPrintPredictionArray);	


	if(predictionContextObjArray != NULL)
	{
		for(int i = 0 ; i < numOfPredictionItems ; i++)
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
	

	delete testDataObj;
	testDataObj=NULL;


	delete []predictionArr;
	predictionArr = NULL;
	delete []predictionWithInArr;
	predictionWithInArr = NULL;
	delete []predictionWithoutInArr;
	predictionWithoutInArr=NULL;

	return ret;
		
}
		

/*
bool IsRenameReadAndWriteToCo municationFileAndRenameBack(char* extractedString, cGlobals &globals, char* prefixExt)
{
	char extendedComunicIn[MAX_STRING_LENGTH];
	FillExtendedFilePath(   extendedComunicIn, prefixExt, globals.g_patientRealTimeFilePathIn );
	if(
		rena me(globals.g_patientRealTimeFilePathIn, extendedComunicIn) != 0)
	{
		int sdg = 0 ;
				//	perror("Error renaming file"); //error
		return false;
	}
	else
	{
		//	cout << "File renamed successfully";
		ifstream realTimeComFile;
		realTimeComFile.open(extendedComunicIn,  ios::in);
		if(realTimeComFile.is_open())
		{
			//char queryFilePath[1000];
	//number of fields extraction
			FileManager::ReadOneLine(extractedString, realTimeComFile, globals.g_endOfLineInSign);// (string) : "num of fields "
			realTimeComFile.close();
			ofstream outfile;
			outfile.open(extendedComunicIn,  ios::out);
			FileManager::WriteOneLine(outfile,"",globals.g_endOfLineInSign);
			outfile.close();
			if( 
			     rena me(extendedComunicIn, globals.g_patientRealTimeFilePathIn) != 0)
			{
				return false ;
			}
			else
			{
				int asdf =0;
			}
						
		}
	}
	return true;
}
*/




//10 1 23

	/*
	the function will retrurn isUsedPhrase array with true or false next to each phrase. then, sending in a larger amount of phrases and we can then only use a sub set of these
	in the logic where we find such phrases on top of patinet paragrphs. lets phrases mean quicker. 
	Target is to aim for hundreeds instead of tens of thousands, and around 1% less
	*/

	/*intput
	char** phraseArr, int numberOfPhrases   - doctors phrases
	paragphList, nuber - patinet has maybe 20 paragrphs and within each could be phrases hiding that match the input doctor pharase arra
	
	output:
	isUsedPhrase has mostly no and sometimes yes, to show the called which pharse to be used
	
	method:
	open a large bollean array with at last 20-30 times larger size than number of phrases
	set a hash function
	convert each phrase to an integere using tht hahs function and mark no for all indexes and tyes for those that meet at least one phrsae hash function

	*/

/*
void FlagOnlyCandidatePhrasesRelevantForOnePatienttParagSet(
	 //output
	 bool* isPhraseCandidateForPatient,  //size of numberOfPhrases
	 //input
	 //all doctor phrases manually edited list and their number
	 char** doctorEditedPhraseArr, int numberOfPhrases, 
	 //one input patinet paragrph list, two dimenison string array with number of paragraphs
	 char** paragList, int numberOfParagraphs    )
	 
{
	//update the output array to mark relevant phrases vs not relevant phrases to be the output
 
	for(int i = 0 ; i < numberOfPhrases ; i++)
	{
		isPhraseCandidateForPatient[i]=false; //befoer updating, defauly all to be not a phrase
	}

	 
	
	for(int x = 0 ; x < numberOfParagraphs ; x++)
	{
		int sizeOfHashArray = numberOfPhrases * 20;
		bool* patientCandidatePhraseFlagArr = new bool[sizeOfHashArray];
		for(int f = 0 ; f < sizeOfHashArray ; f++)
		{
			patientCandidatePhraseFlagArr[f]=false;
		}
		//given a paragarph, all words combination create candiate phrase will be hashe and add a flag of true if an integer is mached
		//AGREE  on the mormalizationn of these flags as well as doctor phase below just before we call the hashCode function in side
		//NormeizleStr(str); //remove spaces? to be used within this function
		MarkAllCandidatePhraseCombinationInTheirIntegerAppearcheAsOutputFlagArr (patientCandidatePhraseFlagArr, sizeOfHashArray,  paragList[x] );
		int cntTrue = 0 ; 
		int cntFalse = 0;
		for(int i = 0 ; i < numberOfPhrases ; i++)
		{
			String str = doctorEditedPhraseArr[i];
			NormeizleStr(str); //remove spaces? 
			int bucketIndex = HashCode(str);
			bucketIndex = bucketIndex % sizeOfHashArray;
			if(patientCandidatePhraseFlagArr[bucketIndex])
			{
				isPhraseCandidateForPatient[i] = true;
				cntTrue++;
			}
			else
			{
				int ssddf=0;
				cntFalse++;
			}
		}
	}
}
*/





int main()
{
//PREPARE GLOBAL PARAMETERS THAT CAN BE GOOD FOR MULTIPLE APPLIAITONS, OR BE GOOD FOR SOME AND NOT RELEVANT FOR OTHERS.
//SOME OF THESE ARE CONTROLLED BY COMMAND LINE. SOME CAN BE MOVED TO A CONFIGURATION FILE
	cGlobals globals; //12 2 22 find the stretch area and see that it is divided per sample person that made the stretch
	//globals.CommandLineAdjustement();
	     //PARAGRAPH DISCOVERY PATTERNS APPLICATION  - 'A' for paragraph patterns and 'B' for profiles 
	if(globals.g_applicationType == 'A' ||  globals.g_applicationType == 'a' )
	{
		globals.g_endOfLineInSign = '^';
		globals.g_endOfLineOutSign = '^';
		cParagraphAnalytics paragAnats (globals.g_inputFileString, 2, 1);//see global initielize func to get the file name needed
		paragAnats.AnalyticsProcess(&globals);
		return 0;
	}
//potentially we can get the input data and metadat from argv argc. right now it is hard coded
	if(globals.g_applicationType == 'B' || globals.g_applicationType == 'b')// 'B' for profiles 
	{
//OPEN cResearchObject OBJECT to collect META DATA
		InputVariablesPackageForResearchObj* inputVarObj = new InputVariablesPackageForResearchObj;
	 	int depVarIndex=-1;// output - not part of the research object since it does store separatae array with that and do not use original two dim array for the dep value after
		//12 2 22 *** add depVarIndex as a member to inputVarObj so we reduce parameters
		bool isSuccess = inputVarObj->PrepareMetaDataElements( depVarIndex, globals);//.g_metaFilePath, globals.g_endOfParagraphInSign, globals.g_delimiter);
		cResearchObject* researchObj = new cResearchObject(inputVarObj);//, 
//BUILD or LOAD FROM DISK to have all profiles up, then either save, save and run tests, or be ready for prediction one by one
		BuildResearcObjectOrLoadFromDist(researchObj, &globals, inputVarObj ,   depVarIndex);
//OPEN CALIBRATION DATA OBJET and calibration arrays. advantage of calibration vs. just raw prediction is that 1- the raw is more sensitive to if we weigiht multiple
		//profiles in some way or do we tend to look for extreme. the multiple may cause smaller range on the raw but not on the post calibration. and 2- can be 
		//used to take any model and firt run the calibration from a specific world of appication with poplation a bit different than the one frmo the learning. 
		int numberOfTestsToPerform = globals.g_NUM_OF_TEST_TYPES;//this can be moved to globals to define per run which tests we want. 
/* for each of these defined tests, run a test and dedicated a section in the performance output file:
 0 - ONLY_ROOT_PREDIC_MODE,   1 - ONLY_WP3_EXACT_MULTI_VALUE_PATN_CATEGORY,   2 - ONLY_WP3_INCLUDED_IN_PATN_CATEGORY,
 3 - ONLY_NON_WP3_PROFILES,   4 - ALL_PROFILES_CANDIDATES  */
		cCalibrationContextObj** calbObjArrayss = new cCalibrationContextObj*[numberOfTestsToPerform];
	
		{
		//	ofstream perfOutfile(globals.g_performanceReportFilePath);//, ios::out);//21 2 12 get nput from above so can apend each print with new test in one same file.
			cArrayFlex arrayFlexx(globals.g_internalPerformanceReportFilePath,true);
			char strTemp[100];
			strcpy(strTemp , "number of tests:");
			arrayFlexx.WriteReadArrayString(strTemp, true , globals);
			arrayFlexx.WriteReadArrayInt(numberOfTestsToPerform,true,globals);
			bool isToPrintPredictionArray = true;
			for(int i = 0 ; i < numberOfTestsToPerform ; i ++)
			{
				calbObjArrayss[i]= NULL;// 
				bool isWithCalibration = false;
			//	strcpy(strTemp , "test number:");
				//arrayFlexx.WriteReadArrayString(strTemp, true , globals);
			//	arrayFlexx.WriteReadArrayInt(i,true,globals);
				bool isWithFineTuning = true;
				OpenDataObjAndPerformQueriesAndReport(//predictionArr, numOfPredictionItems, 
					calbObjArrayss[i],//new cCalibrationContextObj(numOfCallibrationGrps);
					globals.g_patientCalibrationFilePath,   inputVarObj, 
						 depVarIndex, globals.g_endOfLineInSign, globals.g_delimiter,
					researchObj,   i,  isWithCalibration, globals,arrayFlexx, 
					isToPrintPredictionArray , isWithFineTuning);	
			}
		}
		if((globals.g_isToEnterRealTimeEndlessLoop == 'Y' ) || (globals.g_isToEnterRealTimeEndlessLoop == 'y'))
		{
			bool end = false;
			while(!end)
			{
				Sleep(2000); //two seconds
				char queryInFilePath[100];
				char extendedComunicIn[MAX_STRING_LENGTH];
				if( FileManager::IsRenameReadAndWriteToComunicationFile(
					extendedComunicIn,
					queryInFilePath,
					"prefixExt", &globals, globals.g_patientRealTimeFilePathIn,globals.g_endOfLineInSign ))
				////nnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
				{
					if( strcmp(queryInFilePath, "end") == 0)
					{
						end = true;
					}
					else if(strlen(queryInFilePath) == 0)
					{
						int sdg=0;
					}
					else
					{

						char quesryFilePathOut[MAX_STRING_LENGTH];
						FileManager::FillExtendedFilePath(  quesryFilePathOut,globals.g_patientRealTimeFolderPathOut, queryInFilePath );
						cArrayFlex arrayFlexRT(quesryFilePathOut ,true);
						bool isToPrintPredictionArray = true;
						bool isWithCalibration =true ; //for real time  we can play with true or false, start clean first
						int defaultProfileSetType = globals.g_ALL_PROFILES_CANDIDATES;//ONLY_ROOT_PREDIC_MODE
						bool isWithFineTuning=true;
						OpenDataObjAndPerformQueriesAndReport(calbObjArrayss[defaultProfileSetType], queryInFilePath, inputVarObj,  depVarIndex, 
								globals.g_endOfLineInSign, globals.g_delimiter,   researchObj,   defaultProfileSetType,  isWithCalibration, globals,
								 arrayFlexRT, isToPrintPredictionArray,isWithFineTuning );
					}
					if(/*	Deletes the file if exists */
					rename(extendedComunicIn ,globals.g_patientRealTimeFilePathIn) != 0)
					{
						int sdg = 0 ;
				//	perror("Error renaming file"); //error
						//ret= false;
					}
			//12 2 22 *** temporary to stop after one queriy file. develop how to continue
			//need to take care of mulitpe files same name and on going continuation				
				}
			}
		}
		if( (globals.g_isToConductPerformanceTests == 'Y') ||(globals.g_isToConductPerformanceTests == 'y'))
		{
			
		//1 . first task to prepare tool to place best matched profiles average into a group and prediction
		//open a calibration test file using research data object
		//12 2 22 *** open file with write permission - look in paragraph analtics
			//outfile
		//	ofstream perfOutfile(globals.g_performanceReportFilePath);//, ios::out);//21 2 12 get nput from above so can apend each print with new test in one same file.
			cArrayFlex arrayFlexTest(globals.g_performanceReportFilePath,true);
			bool isToPrintPredictionArray = false;
			for(int i = 0 ; i < numberOfTestsToPerform ; i ++)
			{//12 2 22 improve the confiiguration of test tpe , make it prediciton profile type and use in search timem also
				//in a way that is easy to manage
				bool isWithCalibration =false ; //for test we can play with true or false, start clean first
				char outPerfReportFilePath[MAX_STRING_LENGTH];
				strcpy(outPerfReportFilePath, globals.g_performanceReportFilePath);
			//	char extention[MAX_STRING_LENGTH];//find a way to get the i into string and apend to the filt path/ 12 2 22 ***
				//apend extention at end of outPerfReportFilePath
				bool isWithFineTuning = true;
			 	OpenDataObjAndPerformQueriesAndReport(	calbObjArrayss[i],
					globals.g_patientTestFilePath,  
					inputVarObj,  depVarIndex, globals.g_endOfLineInSign, globals.g_delimiter,
					researchObj,  i,  isWithCalibration, globals ,arrayFlexTest, 
					isToPrintPredictionArray, isWithFineTuning);	 
			}
		}
	 	if(calbObjArrayss!=NULL)
		{
			for(int i = 0 ; i < numberOfTestsToPerform ; i ++)
			{
				if(calbObjArrayss[i] != NULL)
				{
					delete calbObjArrayss[i];
				}
			}
			delete []calbObjArrayss;
		}
		delete inputVarObj;
		inputVarObj = NULL;

		delete researchObj;
		researchObj = NULL;
	}

	return 0;
}




