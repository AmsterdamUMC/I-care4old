#if !defined(_TARGET_SORT_H_INCLUDED_)
#define _TARGET_SORT_H_INCLUDED_

 
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <stdio.h>

#include <math.h>
#include "math.h"
#include <string.h>
#include <fstream>
#include <sstream>
 

#include <windows.h>

#include <string>
 
using namespace std;



//#include <iostream>
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::endl;


#define IS_ADD_CPU_INTENSIVE_PERF_TEST true //8 11 23 8 12 23
#define IS_TO_REMOVE_ZERO_PERF_PROFILES true//8 11 23 8 12 223
#define IS_TO_SMOOTH_ADVANCED_PERF_BUCKET_VALUES true//8 11 23 8 12 223
#define TEMP_FILE_PATH_FOR_UPLOAD_TO_DASHBOARD "dashboard_profiles_file_path.txt"




//1 11 24
///////////////////////////////////////////CONTROL MUTIPLE RESEARCH QUESTIONS BOARD/////////////
#define COUNTRY_POS_INDEX 1
#define COUNTRY_CODE 2 //0 is if no interest in any specific report. 1 and up are per countries
//#define COUNTRY_NAME_FOR_REPORT "CANADA"//USA_MA 
 

#define PROFILE_LIST_PER_ANCHOR_MAX_NUMBER 500   /// 5 30 24 //try 2 23 24 instead of 5000
 


#define RESEARCH_QUESTION_INDEX 26//80// 225///81
#define RESEARCH_QUESTION_VAR_VALUE_NUM  8//10//5 //8//10
#define IS_RESEARCH_INDEX_STARTS_FROM_1 true//false

#define IS_LOCOMOTION_RUN false //true
#define LOCOMOTION_RUN_RESEARCH_INDEX  123
#define LOCOMOTION_RUN_RESEARCH_VAR_SIZE  16
#define LOCOMOTION_IS_RESEARCH_INDEX_STARTS_FROM_1 false

#define IS_IADL_RUN false
#define IADL_RUN_RESEARCH_INDEX 80
#define IADL_RUN_RESEARCH_VAR_SIZE 5
#define IADL_IS_RESEARCH_INDEX_STARTS_FROM_1 false

#define IS_HOSP_RUN true
#define HOSP_RUN_INDEX 26
#define HOSP_RUN_RESEARCH_VAR_SIZE 8
#define HOSP_IS_RESEARCH_INDEX_STARTS_FROM_1 true

#define IS_COGNITION_RUN false
#define COGNITION_RUN_INDEX 81
#define COGNITION_RUN_RESEARCH_VAR_SIZE 10
#define COGNITION_IS_RESEARCH_INDEX_STARTS_FROM_1 true

#define IS_CONTINENCE_RUN false
#define CONTINENCE_RUN_INDEX 225
#define CONTINENCE_RUN_RESEARCH_VAR_SIZE 8
#define CONTINENCE_IS_RESEARCH_INDEX_STARTS_FROM_1 false


#define	IS_FRAILTY_RUN false
#define FRAILY_RUN_INDEX 12
#define FRAILY_RUN_RESEARCH_VAR_SIZE 9
#define FRAILTY_IS_RESEARCH_INDEX_STARTS_FROM_1 true
 
///////////////////////////////////////////////////////


#define IS_IADL_RUN_CROSSWALK false

#define ITERATION_TO_MAKE_STOP_DECISION 3

#define HIGHEST_VAR_VAL_ACCEPTED 20.0
#define ILEGAL_VARIABLE_VALUE_SIGH 999.0

#define IS_SET_LOGISTIC_REG true
#define MAX_GAP_OF_LOW_HIGH_PREDICTIVE_SAMPLE 0.97

#define IS_ANCHOR_UNIVERSE_CROSS_ANCHORS false
#define DEFINE_FILTER 2

#define IS_EXTREME_LAST_SECTION_AND_CALIBRTION  false
#define IS_WITH_FINE_TUNING__LAST_SECTION_AND_CALIBRTION true//false
#define SMALL_LEARNING_SAMPLE  30

#define IS_WITH__CALC_FULL_TEST_METHOD false  //// try 1 -  7 28 tend to true
#define IS_METHOD_ML_TYPE_SIMPLE false  //7 28 23 - 1  
#define IS_ML_WITH_WEIGHTED_PROFILES false // try 3 -  8 6 23 false to true
#define IS_WITH_REDUCED_TEST_BY_SIM_PROF_PERF false //  /// try 1 -  8 6 23 false to true

#define IS_FLEXIBLE_RATE_STRETCH_TEST true
#define IS_WITH_DECREASED_SCORES_ML true
#define NUMBER_OF_MA_STEPS_PER_ANCHOR 25

#define IS_WITH_CLEAN_PARENT_FROM_BEST_MATCH true //7 11 23 * 15 - wokring dir and change 1 are with this as false. 2 and 3 are trie. dif between dir and 1 and between 2 and 3 are in the confi re 0/1 anchor. 
//next step is to have that same define control the learning without parient fucntion

#define MAX_WEIGHT_ADVANCED_PERF_PROFSUB 30.0

#define NUMBER_OF_LEARNING_ITERATIONS 10
#define MIN_ITERAION_INDEX_TO_IGNORE_0_PROFSUBS 4
#define LEARNING_MULTIPLIER 1.5


#define MAX_STRING_LENGTH 300

class cHistogram;
class cGlobals;


/////////////////////BYPASS PARAGRAPH DEFINE LIST///////////////////////////////
//more changagle list
#define NULL 0
//#define NUM_OF_CATG_PERCENTILE_MERGE 10
#define MAX_STRING_LENGTH 300


#define IS_TO_WRITE_HISTOGRAM_TO_FILE false
#define IS_TO_REMOVE_DANGEROUS_STRINGS true
#define SIG_DEVIATION_IN_SD 0.5
#define SIG_REDUCTION_IN_SD 0.4
#define MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN 100//60 //11 26 22
#define MAX_SAMPLE_TO_CARE_FOR_SAME_PT_DUP 10000 //if a string is not a rare one, happen enough times, than multiple 
#define IS_TWO_FIELDS_INPUT_FILE false
 
#define SIZE_OF_HASH 50000000 //70 million
#define SIZE_OF_INITIAL_HASH 80000000//two  hundreed million
//#define SIZE_OF_SUB_STR_PATIENT_DUPLICATION 100000000
#define SIZE_OF_PATIENT_STR_DUPLICATION_ARR 200000000
#define PERC_THRES_EXCLUSIVE_GRP 0.9


#define RECOMENDED_SAMPLE_LEARNING_RORATE 100
#define PROFSUB_RECOMENDED_SAMPLE_SIZE 100
#define SMALL_SAMPLE_TO_START_LEARNING 50000
 
//#define PATIENT_LINES_INPUT_LIST_MAX_NUMBER  100000


//Less flexible list 
#define MAX_NUM_OF_CHARS_PER_SUBSTRING 100
#define FREQUENT_SUBSTRING_PERC 0.25 //if a sub string appears 0.25 / 25% or  more of the total number of sub strings than it is frequent

 
//BYPASS
#define STRONG_PERC_OF_APPERANCE 0.85
#define MIN_PERC_OF_APPEARENCE 0.75
#define STRONG_ODD_RATIO_FOR_PATTERN_TO_BYPASS 0.2//0.25//4.0 //11 26 22
#define MIN_ODD_RATIO_FOR_PATTERN_TO_BYPASS 0.3//0.4//2.5  // 11 26 22

#define PATIENT_GROUPS_NUMBER_FOR_PREVENTING_SAME_PATIENT_MULTI_SUB_STRINGS 1000000


class cVariableAndValueAndPoints;


class cArrayFlex
{
	bool* m_arr;
	int m_size;
	int m_readMovingIndex;
	char m_filePAth[200];
	bool m_isWriteMode;
	ofstream* m_outfilePtr ;
	ifstream* m_infilePtr;

 


public:
	cArrayFlex(char* filePath, bool isWriteMode);
	~cArrayFlex();

	int GetSize() {return m_size;}
	bool* GetArr() { return m_arr;}
	bool GetIsWriteMode(){ return m_isWriteMode;}
	
//	void WriteReadArray( unsigned char* arr, int size, bool isWriteToArray);
	void WriteReadArrayDouble( double &item, bool isWriteToArray,  cGlobals &globals);
	void WriteReadArrayInt( int &item, bool isWriteToArray, cGlobals &globals);
	void WriteReadArrayChar(char &item, bool isWriteToArray, cGlobals &globals);
	void WriteReadArrayBool( bool &item, bool isWriteToArray, cGlobals &globals);
 	void WriteReadArrayString(char* str, bool isWriteToArray, cGlobals &globals, bool isToAddDoubleQuaotes = false);
	 
	void Enter(  bool isWriteToArray, char endOfLineSign );
	

	void SetReadIndexToStart()
	{
		m_readMovingIndex=0;
	}
	void WriteArrayToDisc();
	void ReadArrayFromDisc();
};

//#define NUM_OF_MEAN_BUCKETS 100

class cHistogram;

class cVarianceCalc
{
	double** m_table;
	unsigned int m_bucketsNum;
	unsigned int m_buckMaxLen;
	
public:
	cVarianceCalc(unsigned int bucketsNum, 	unsigned int buckMaxLen)
	{
		m_bucketsNum = bucketsNum;
		m_buckMaxLen = buckMaxLen;
		m_table = new double*[m_bucketsNum];
		for(unsigned int i = 0 ; i < m_bucketsNum ; i++)
		{
			m_table[i] = new double[m_buckMaxLen];
			for(unsigned int ii = 0 ; ii < m_buckMaxLen ; ii++)
			{
				m_table[i][ii] = 0 ; 
			}
		}
		
	}
	
	~cVarianceCalc()
	{
		for(unsigned int i = 0 ; i < m_bucketsNum ; i++)
		{
			delete []m_table[i];
		}
		delete []m_table;
	
	}

	
	static int Max(int val1, int val2)
	{
		if(val1 > val2)
		{
			return val1;
		}
		return val2;
	}


	static void StringAppend(char* inOutStr , char* addedStr)
	{
		int inOutLen = strlen(inOutStr);
		int addLen = strlen(addedStr);
		for(int i = 0 ; i < addLen ; i++)
		{
			inOutStr[inOutLen+i] = addedStr[i];
		}
		int newLen = inOutLen + addLen;
		inOutStr[newLen ]=0;
	}

	static void StrCptWithDoubleQuotesAndColonAndOpeningSquare(char* outStr, char* inStr,  int leadingSpaces, 
													bool isAddingDoubleQuotes)
	{
		StrCptWithDoubleQuotes( outStr,  inStr,   leadingSpaces, isAddingDoubleQuotes);
		StringAppend(outStr , ":  ");
		StringAppend(outStr , "[");
	}

	

	static void JasonPringSimpleArray(char* msgStr,  char* titleIn, 
	int leadingSpacesNum , cArrayFlex* arrayFlex, cGlobals* globals,  int integerIn, 
	                   double* valArr, bool isComa);

	
	static void JasonPringSimpleArray(char* msgStr,  char* titleIn, 
	int leadingSpacesNum , cArrayFlex* arrayFlex, cGlobals* globals,  int integerIn, 
	                   int* cntArr, bool isComa);

	static void BuildRankingIndexArr (int* rankArr, double* rank, int size)
	{
		bool* isTaken = new bool[size];
		for(int i = 0 ; i < size ; i++)
		{
			isTaken[i] = false;
		}
		for(int i = 0 ; i < size ; i++)
		{
			rankArr[i]=-1;
			int f = FindMaxScore(rank, isTaken, size);
			if(f>=0)
			{
				rankArr[i] = f;
				isTaken[f]=true;
			}
		}
		delete []isTaken;
	}
		
	static int FindMaxScore(double* rank, bool* isTaken, int size)
	{
		int foundIndex = -1;
		double max=-1000.0;
		for(int i = 0 ; i < size ; i++)
		{
			if((!isTaken[i]) && (rank[i] > max))
			{
				max = rank[i];
				foundIndex = i;
			}			
		}
		return foundIndex;
	}

	static void StrCptWithDoubleQuotes(char* outStr, char* inStr,  int leadingSpaces, 
													bool isAddingDoubleQuotes)
	{
		int movingIndex = 0;
		for(int x = 0 ; x< leadingSpaces ; x++)
		{
			outStr[movingIndex++] = ' ';
		}
		int len = strlen(inStr);
		if(isAddingDoubleQuotes)
		{
			outStr[movingIndex++]='"';
		}
		for(int i = 0 ; i < len ; i++)
		{
			outStr[movingIndex++] = inStr[i];
		}
		if(isAddingDoubleQuotes)
		{
			outStr[movingIndex++] = '"';
		}
		outStr[movingIndex++] =  0;	
	}

	

	static void CreateStringWithCulumnAndQuotesAndDouble(char* strOut, char* strIn, 
		double doubleIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
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
		strOut[movingIndex++] = ':';
		strOut[movingIndex++] = ' ';

		char tempStr[100];
		sprintf(tempStr, "%f",doubleIn  );
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] =',';
		}
		strOut[movingIndex++] =0;

	}


	static void CreateStringFromIntegerAndComa
		(char* strOut, 	int integertIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
	{
		int movingIndex = 0;
		for(int x = 0 ; x< leadingSpacesNum ; x++)
		{
			strOut[movingIndex++]=' ';
		}
		char tempStr[100];
		sprintf(tempStr, "%d", integertIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] = ',';
		}
		strOut[movingIndex++] =0;
	}
	
	static void CreateStringFromDoubleAndComa
		(char* strOut, 	double doubleIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
	{
		int movingIndex = 0;
		for(int x = 0 ; x< leadingSpacesNum ; x++)
		{
			strOut[movingIndex++]=' ';
		}
		char tempStr[100];
		sprintf(tempStr, "%f", doubleIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] = ',';
		}
		strOut[movingIndex++] =0;
	}

	
	static void CreateStringFromIntAndComa
		(char* strOut, 	int cntIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
	{
		int movingIndex = 0;
		for(int x = 0 ; x< leadingSpacesNum ; x++)
		{
			strOut[movingIndex++]=' ';
		}
		char tempStr[100];
		sprintf(tempStr, "%d", cntIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] = ',';
		}
		strOut[movingIndex++] =0;
	}




	/*
	static void CreateStringWithCulumnAndQuotesAndDouble(char* strOut, char* strIn, 
		double doubleIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
		// "Profile ID": profileIndex,
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
		strOut[movingIndex++]=': ';
		char tempStr[100];
		sprintf(tempStr, "%f", doubleIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
	
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] = ',';
		}
		strOut[movingIndex++] =0;
	}
	*/


	static void CreateStringWithCulumnAndQuotesAndInteger(char* strOut, char* strIn, 
		int integertIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
		// "Profile ID": profileIndex,
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
		strOut[movingIndex++]=':';
		strOut[movingIndex++]=' ';
		char tempStr[100];
		sprintf(tempStr, "%d", integertIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
	
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] = ',';
		}
		strOut[movingIndex++] =0;
	}
	
	/*
	static void CreateStringWithCulumnAndQuotesAndDouble(char* strOut, char* strIn, 
		double doubleIn,  int leadingSpacesNum, bool isAddComaInEnd = false)
		// "Profile ID": profileIndex,
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
		strOut[movingIndex++]=':';
		strOut[movingIndex++]=' ';
		char tempStr[100];
		sprintf(tempStr, "%d", integertIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}
	
		if(isAddComaInEnd)
		{
			strOut[movingIndex++] = ',';
		}
		strOut[movingIndex++] =0;
	}
	*/

	static void CreateStringWithQuotesAndIntegerAndColunAndSquareQuotes(char* strOut, char* strIn, 
		int integertIn,  int leadingSpacesNum)
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
		
		char tempStr[100];
		sprintf(tempStr, "%d", integertIn) ;
		int intStLen = strlen(tempStr);
		for(int i = 0 ; i < intStLen ; i++)
		{
			strOut[movingIndex++] = tempStr[i];
		}

		strOut[movingIndex++]='"';
		strOut[movingIndex++] = ':';
		strOut[movingIndex++] = ' ';

		strOut[movingIndex++] ='[';
		
		strOut[movingIndex++] =0;
	//	sprintf(str, "Number of Profiles: %d", d);//8 10 23
 

	}






	static double Max(double val1, double val2)
	{
		if(val1 > val2)
		{
			return val1;
		}
		return val2;
	}


	static int Min(int val1, int val2)
	{
		if(val1 < val2)
		{
			return val1;
		}
		return val2;
	}


	static double Min(double val1, double val2)
	{
		if(val1 < val2)
		{
			return val1;
		}
		return val2;
	}


	static int  Abs(int val )
	{
		if(val < 0)
		{
			return -1 * val;
		}
		return  val;
	}
	static double Abs(double val )
	{
		if(val < 0.0)
		{
			return -1.0 * val;
		}
		return  val;
	}

	static int  FindLowestIndexNotSelectedAlready(double* valArr,  bool* isIn, int size);

	
	static void FillArrWithLowestValue(bool* isIn, double* valArr, int size, int numOfSelcted);


//	void SetValue(double meanGrpInSD , double data)
	//{
	//}

//	void  BuildBucketsMeanAndSDofVariance()
//	{
	
//	}

//10 10 22
	/*
	static bool IsPAtternAssociationMeanAndSDsignifciant(
				double	avg, double sd,double universMean, double universSD)
	{
		//if( cVarianceCalc::Abs( (avg - universMean ) / universSD)  > SIG_DEVIATION_IN_SD )
		
		double meanScore =0.0;
		if(universSD > 0.0)
		{
			meanScore=cVarianceCalc::Abs( (avg - universMean ) / universSD)  ;
		}
		
		double sdScore = 0.0;//universSD - sd;
		if(universSD > 0.0)
		{
			sdScore =( universSD - sd) / universSD;
		}

		bool ret=false;
		if( (meanScore  > SIG_DEVIATION_IN_SD) || (sdScore > SIG_REDUCTION_IN_SD) )
		{
			ret = true;
		}
		return ret;
	}
	*/

	static bool IsVarValExist( cVariableAndValueAndPoints* varValArr, int size, int var, double val);


//	if(! IsVarValExist( tempVarVal,movingIndex, var, val))
		


	
//10 20 18 * new V
	static int GetOneRandomSelectedIndexFromActiveFlagsWithPriority(bool* arr, bool* isPriority,  int size);



	void LookUpMeanAndSD(double &meanVariaince, double &sdVariance , double meanGrpInSD )
	{
	
	}


	//cVarianceCalc
	static void   CalculateMeanAndSD(double &mean, double &sd, double* arr,
		                                     double* weightArr, unsigned int count);

	static void CalculateMeanAndSD(double &mean, double &sd, char* valArr, int* cntArr, int size);

	static void CalculateMeanAndSdScoresFromIndexes(double &mean, double &sd,
							int* indexArr , int count , double* profileScoreArr);
	static int GetPositionOfHighestAvaliableScore(bool* taken, double* scoreArr, int count);

//	static double UpdateOneVAlueFromStringAndValueArrays(char* tempStr,  char** strs , double* valueArr, int numOfItems,StringToIntHash& FieldNAmeToIndexHash );
	static double UpdateOneVAlueFromStringAndValueArrays(char* tempStr,  char** strs , double* valueArr, int numOfItems );
	static int FindIndexOfStringInStringArray(char* tempStr,  char** strs , int numOfItems );


	//6 22 17
	static double CalculateMostFrequentValue ( double* arr , int numOfItems, bool* isIn)
	{
		double* wghArr = new double[numOfItems];
		for(int i = 0 ; i < numOfItems ; i ++)
		{
			wghArr [i] = 0.0;
			if(isIn == NULL || isIn[i])
			{
				wghArr [i] = 1.0;
			}
		}
		double meanVal=0.0; 
		double sdVal=0.0;
		CalculateMeanAndSD(meanVal, sdVal, arr,  wghArr,numOfItems);

		int sizeOfFreqArr = (int)(meanVal + (3* sdVal)) ; 
		double* frequencyCount = new double[sizeOfFreqArr ];
		for(int in = 0 ; in < sizeOfFreqArr ; in++)
		{
			frequencyCount[in] = 0.0;		
		}
		//6 22 17 missing here filling the frequency array with values around 0.5 +- each index. how many patients had dep arr value between index and range
	
		double multipler = 0.5;
		double difFromCenter = sdVal * multipler;
		int difFromCenterInInt = int(difFromCenter) ;
		for(int i = 0 ; i < numOfItems ; i++)
		{
			int centerVal = int(arr[i]);
			for(int pos = (centerVal - difFromCenterInInt) ; pos <= (centerVal + difFromCenterInInt)  ; pos++)
			{
			//	int temp = pos;
				if( (pos >= 0) && (pos < sizeOfFreqArr))
				{
					double absDifFromCenter = Abs(centerVal - pos);
					double weight = 1.0 / (difFromCenter + absDifFromCenter );//difFromCenter as base represent that once you get to either 
													//side along 0.5 sd you get to 2  times less the value. 
					weight *= wghArr [i];
					frequencyCount[pos] += weight;
				}			
			}
		}


		int indexOfMAxValue =0;
		double maxValue = 0;
		GetIndexOfMaxValueInArr(indexOfMAxValue , maxValue ,  frequencyCount, sizeOfFreqArr);
		delete []wghArr ;
		delete []frequencyCount;

		double mostFrequentVAlue = double(indexOfMAxValue);
		return mostFrequentVAlue;
	}


	static 	void FindNextIndex (int &movingIsInIndex , bool* isIn, int cnt)
	{
		for(int j = (movingIsInIndex+1) ; j < cnt ; j++)
		{
			if(isIn[j])
			{
				movingIsInIndex = j;
				return;
			}
		}
		
	}


	//7 18 17 new function
	static double CalculateMostFrequentValueNew ( double* arr , int numOfItems, bool* isIn , int numOfBuckets);

//6 22 17
	static void GetIndexOfMaxValueInArr(int &indexOfMAxValue , double &maxValue ,  double* arr, int size)
	{
		maxValue = 0.0;
		indexOfMAxValue = 0;
		for(int i = 0 ; i < size ; i++)
		{
			if(arr[i] > maxValue)
			{
				maxValue = arr[i];
				indexOfMAxValue = i;
			}
		}	 
	}


	
		//6 2 16
static void CreateValueInSDarray (double* coreValInSD , double* coreProfValues, double* wghArr, int size)
{
	double meanVal=0;
	double sdVal=0;
	CalculateMeanAndSD(meanVal, sdVal, coreProfValues, wghArr, size);

	for( int i= 0 ; i < size ; i++)
	{
		coreValInSD[i] = 0.0;
		if(sdVal > 0.0)
		{
			coreValInSD[i]  = (coreProfValues[i]-meanVal) / sdVal;
		}
	}
}





//12 1 19 new 
static void BucketSort(double* arr , int size , int maxVal , double shift)
{
	
	int** twoDarr = new int*[maxVal+1];
	int* arrCnt = new int[maxVal+1];
	for(int x = 0 ; x <= maxVal ;x++)
	{
		twoDarr[x] = NULL;
		arrCnt[x]=0;
	}

	for(int i = 0 ; i < size ; i++)
	{
		int bucketI = int(arr[i] + shift);
		bucketI = Max(bucketI, 0);
		bucketI = Min(bucketI , maxVal );
		if(twoDarr[bucketI] == NULL)
		{
			twoDarr[bucketI] = new int[size];
		}
		twoDarr[bucketI][arrCnt[bucketI]]=i;
		arrCnt[bucketI]++;
	}
	double* tempSorted = new double[size];
	for(int i = 0 ; i < size ; i++)
	{
		tempSorted[i]=0;
	}
	int movingIndex = 0;
	for(int x = 0 ; x <= maxVal ;x++)
	{
		if(twoDarr[x] != NULL)
		{
			for(int index = 0 ; index < arrCnt[x] ; index++)
			{
				tempSorted[movingIndex++] = arr[twoDarr[x][index]] ;//- shift;
			}
		}
	}
	for(int i = 0 ; i < size ; i++)
	{
		arr[i] = (tempSorted[i]);
	}


	for(int x = 0 ; x <= maxVal ;x++)
	{
		if(twoDarr[x] != NULL)
		{
			delete []twoDarr[x];
		}
	}
	delete []twoDarr;
	delete []arrCnt;
	delete []tempSorted;
}




/*

static void SortArray(double* arr, int size)
{
	int* maxArray = new  int[10001];
	for(  int i=0; i <10001;i++ )
	{
		maxArray[i] = -1;
	}

	for(  int i=0; i <size;i++ )
	{
		int indexToUpdate = (  int)(arr[i]*100.0);
		maxArray[indexToUpdate] ++;
	}
	unsigned int outIndex = 0;
	for(unsigned int i=0; i <10001;i++ )
	{
		while(maxArray[i] >=0)
		{
			arr[outIndex] = (double)i/100.0;
			outIndex++;
			maxArray[i]--;
		}
	}


	delete[] maxArray;
}

*/



static void BubbleSortLargeToSmall(  int* intArr, int size)
{
	double* arr = new double[size];
	for(int i = 0 ; i < size; i ++)
	{
		arr[i] = double(intArr[i]);
	}
	BubbleSort( arr,  size);
	for(int i = 0 ; i < size; i ++)
	{	
		intArr[i] = int(arr[size-1-i]); //i.e. size is 10 than inrArr[0] = arr[9], or intArr[4] = arr[10-1-4] = arr[5]
	}
	delete []arr;
}




//1 5 20 new
static void BubbleSort(double* arr, double* wghArr , int size)
{
	  bool swapped = true;
      int j = 0;
      double tmp;
      while (swapped)
	  {
            swapped = false;
            j++;
            for (int i = 0; i < size - j; i++)
			{
                  if (arr[i] > arr[i + 1]) 
				  {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;

						tmp = wghArr[i];
						wghArr[i]  = wghArr[i + 1];
						wghArr[i + 1] = tmp;

                        swapped = true;
                  }
            }
      }
}



static void BubbleSort(double* arr, int size)
{
	
      bool swapped = true;
      int j = 0;
      double tmp;
      while (swapped)
	  {
            swapped = false;
            j++;
            for (int i = 0; i < size - j; i++)
			{
                  if (arr[i] > arr[i + 1]) 
				  {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}



static double GetMedian(double* arr, int size)
{
	BubbleSort(arr, size);
	int index=0;
	if((size % 2 ) != 0) //odd
	{
		index = size / 2;
		return arr[index];
	}
	else
	{
		int index1 = (size / 2) - 1;
		index1 = Max(index1 , 0);
		double val1 = arr[index1];
		int index2 = (size / 2);
		double val2 = arr[index2];
		return (val1+val2) / 2.0;
	}
}

//static void FillHighThreshods( cMinMaxMap &twoDmap ,  int numOfBuckets,  double* localArr , int size);

static void AddPrefixstring(	char* inOutStr  ,  char* prefix);

static void ConcatPrefixStringToEachString ( char** strArr, int indexToStartFilling, int numOfFilled , char* prefix);

	static int FindHighestScoreNotInFlagArray( double*	wghtArr , int N, bool*	isIn );
	

	
//11 4 18 * new two fuhnctions
static 	bool CollectTopProfilesWithSimilarDepVAlue(bool* isIn , double* arr, int num, double anchorVal, double valueSD  ,  int numOfSampleCases);
static int CollectTopProfilesWithSimilarDepVAlueFixedMAxDistance(bool* isIn , double* arr, int num, double anchorVal, double valueSD  , double maxDiffInSD, int minOfSampleCases);


	
//5 21 14 three new  functinos
	static void   CalculateMeanAndVariance(double &mean, double &variance, double* arr,
		                                     double* weightArr, unsigned int count);
	

//	static void PrepareMapOfValuesForDecilesGrouping( cMinMaxMap &twoDmap, int numOfBuckets ,double* arr,
	//																					bool* isIn, int arrSize);
	static void PrepareMapOfValuesForDecilesGrouping( double* thresholdArr,  int numOfBuckets ,double* arr,
																						bool* isIn, int arrSize);

	

	void static FillHistorgam( cHistogram *hist, double* valArr, int size);

	
	void static FillHistorgamWithLineLengthInConsidetion( cHistogram *hist, double* valueArr, double* lineSizeArr, int size );
 

	static  int FindLowestIndexFromInputStartIndex(int* arr, int num, int startIndex)
	{
		 
		int lowestValue = 10000000;
		int lowestValIndex = -1;
		for(int i = startIndex ; i < num ; i++)
		{
			if(arr[i] < lowestValue)
			{
				lowestValue = arr[i];
				lowestValIndex = i;
			}
		}
		return lowestValIndex;
	}
	//1 5 20
	static void PrepareWeightedMapOfValuesForDecilesGrouping( double* threshldArr ,int numOfGrps ,double* arr, double* wghArr, bool* isIn,int N);

	static void JsonPrintVarValPonts(char* msgStr, char* stringTitle, 
			cVariableAndValueAndPoints* inclusionRuleList, 	int numInteger, int leadingSpacesNum, 
	   bool isAddComma, cGlobals * globals, cArrayFlex* arrayFlex);
	//8 21 17
	static double CalcualteTopLOSbucketValue (double* arr, int num, int numOfBuckets);

	
	static int GetGrpIndex(double scaleVal, double* thresholdList, int numberOfSubGrps);

	static void FillValuesOfBuckets( double* bucketVal, int numOfBuckets, double* valArr , bool* isIn, int size );

	//7 3 17
	static void TurnArrToSdValues(double* arr , double* wghtArr, int size)
	{
		double mean = 0.0;
		double sd = 0.0;
		CalculateMeanAndSD(mean, sd, arr, wghtArr, size);
		for(int i = 0 ; i < size ; i++)
		{
			if(  (wghtArr == NULL)  || ( wghtArr[i] > 0.0))
			{
				double temp = 0.0;
				if(sd > 0)
				{
					temp = 	(arr[i] - mean) / sd;
				}
				arr[i] = temp;
			}
		
		}

	}

	//2 11 18 * new fuction
static void FillPErsonAsedAcactiveProfileCountWithInputVaribleIncluded(int* cntOfObojectsPerVariable, bool* isObjectActive, 
		 double** variableWghPerObject,  int numOfObjects,   int varCnt)
{
	//for every varibel first check is there is at leas one profile with that varible index. stor the count 
	for(int j = 0 ; j < varCnt ; j++)	
	{
		int cnt = 0;
		for(int ii = 0 ; ii< numOfObjects ; ii++)
		{
			if( isObjectActive[ii] )
			{
				//varWghProfile has for every profile , does it have var j as profile inclusion rule? 
				// we need to count ++ for var j so that we know that var j is active and has profiles with it
				if(variableWghPerObject[ii][j] > 0.0)
				{
					cnt++;
				}
			}
		}
		cntOfObojectsPerVariable[j]=cnt;
	}
}

//2 11 18 * new fuction
static void MeassureSDofPredictionsForVAriableMatchedGroupsOfObjects(double* sdArrPerVar,bool* isObjectActive,double** variableWghPerObject,
													int numOfObjects,   int varCnt,int* cntOfObojectsPerVariable, double* predictionValues)
{
	for(int j = 0 ; j < varCnt ; j++)
	{
//  now we want for every of such var j that is active, its sd . the sd will be from only profies with var j, vs the base sd 
 //which was from all profiels,  so the gap in its positive form will be set at sdPositiveDeltaPerVar
		sdArrPerVar[j]=0.0;
		
		if(cntOfObojectsPerVariable[j] > 1)
		{
			double* localWghArr = new double [numOfObjects];
			for(int ii = 0 ; ii< numOfObjects ; ii++)
			{
				localWghArr[ii]=0.0;
				if(  isObjectActive[ii] )
				{
					if(variableWghPerObject[ii][j] > 0.0)
					{
						localWghArr[ii]=1.0;
					}
				}
			}
			double mean=0.0;
			cVarianceCalc::CalculateMeanAndSD(mean, sdArrPerVar[j] ,predictionValues, localWghArr,numOfObjects);
			
			delete []localWghArr;
		}
	}
}
 

//2 12 18 * new fuction
static double	CalculateScoreBasedOnREductionOfSDfromBaseSD( double**  varWghPerObject, int mustBeOn1, int mustBeOn2, double* predictionArr, 
	bool* isIn, int numOfObjects,  double baseSD);

//2 18 18 *  updted
static void CreateRegreionDetalisTwoPredictiveVaribles(double** twoDim, double*& depArr, int &regCnt, 
			double** varWghPerObject, double* predictionArr, bool* isIn, int* cntOfObojectsPerVariable,
			int numOfObjects, int varCnt, double baseMean, double baseSD,   int typeOfScore, bool isWithOneDim, bool isWithTwoDim);

//2 22 18 * new fuction
//2 28 18 * updated
static double	ComplexChangeInMeanPerInputVar(double* valueArr, bool* isIn,	 double**	varWghPerObj, 
													double** varWghPerObjFullObj,	double* profileScoreArr, int numOfObjects, int varCnt, int j);



static double point_biserial_correlation(int n, double mean1, double mean0, double sd, double sum1, double sum0);
//{
 //   double rpb = (mean1 - mean0) * pow(double(n), 0.5) / (sd * sqrt(sum1 + sum0));
//    return rpb;
//}
static double CalcualteETA(double* predArr, double* depArr, int size);

/*
double LogisticRergression(double &averageSE, double &variance, double & zeroConstant, 	double * betaArr , 
		double& regressionPerformanceScore,double **predictiveArr,	unsigned int N, unsigned int p,  double * dependentArr );
*/

//2 22 18 * new function ?
static double	CalcualtedMeanOfTopSimilarObjectsWithNoVarJ( double* valueArr, bool* isIn,int numOfObjects, 
			double** varWghPerObj, double** varWghPerObjFullObj,	int i,int varCnt, int j );


//2 18 18 * updated  fuction
static void GivingVariblesHomogeniryScoresBasedOnCombinedVaribles(double* homogenityScorePerPositiveSDdeltaPerVarwithRegressionn,
		double* predictionValues,	bool* isIn, double** varWghPerObject, int numOfObjects, int varCnt, 
		int* cntOfObojectsPerVariable, 	bool isAddingOneDimm , bool isAddingTwoDmm, int typeOfScore,double baseMean, double baseSd);

//2 18 18 * new header
static double	CalculateScoreBasedOnSignificantChangeInMean( double**  varWghPerObject, int mustBeOn1, int mustBeOn2, double* predictionArr, 
	bool* isIn, int numOfObjects,  double baseMean);

//2 15 18 * new two functions
static void CalcalteProfileHomogenity(double &mean, double &sd,double* profileHomogenityScore, bool* activeProfileSet, 	double** varWghPerProfile,  float* varScores, int numOfProfiles,  int numOfVaribles);
static void SelectedTopHighScoredProfilesAndBestOne(int &bestProfileIndex ,bool* isProfileIn,  double* profileHomogenityScore, int numberOfProfile);


static int GetOneRandomSelectedIndexFromActiveFlags(bool* indexActiveArr,  int size);


};

 

class cVariableAndValue;
class cVariableAndValueAndPoints;
class cResearchDataObj;




class FileManager
 {
	 static bool DownloadInputDataFile(double**& personsDataSet, double*& depArr, int &numberOfPatients, 
		     int numOfVariables, 	char* inputPatientFilePAth, 
			 int depVarIndex, char endOfPAragSign, char delimiter ,  cGlobals* globals);
	 
	


public:
	FileManager(){}

	static bool ReadOneLine(char* line, ifstream &inFile,  char endOfParagraphInSign);
	static int ReadOneLineFlexibleEndOfLine( char* line, 
		ifstream &inFile, char endOfParagraphInSign, char delimiter);
	static bool ReadOneBlock(unsigned char* arr,  ifstream &inFile,  int size);
	//static bool WriteString(  ofstream &outFile, char* str);
	
	static bool WriteString(  ofstream &outFile, char* str, int len);
	static bool ReadString(char* str,  ifstream &inFile);
	static bool ReadString(char* str , int len, ifstream &inFile);
	bool static IsLegalLine(char* line, char delimiter);
	bool static IsLegalLineWith3sections(char* line, char delimiter) ;


	

	bool static IsRenameReadAndWriteToComunicationFile(char* extendedComunicIn,		
		char* extractedString,  char* prefixExt,
		cGlobals* globals, char* filePAthIn,  char endOffParagInSign);

	void static FillExtendedFilePath(  char* extendedComunicIn, char* prefixExtension, char* inFilePath );

 
	static int CountFields(char* oneLine, char delimiter);

	static bool WriteOneLine(ofstream &outfile, char* outStr ,char endOfParagraphOutSign);
	static bool WriteOneBlock(ofstream &outfile, unsigned char* outStr, int size);
	 
	static bool	DownloadInputDataFile(cResearchDataObj* resarchDataObj, char* inputPatientFilePAth, int depVarIndex ,
		char endOfPAragSign, char delimiter,   cGlobals* globals);	

	static void CopyFieldsFromString(double* personOneArr, char* oneLine, int numberOfVars);

	static void 	GetWordFromString(char* ward, char* strr , char delmiter);

	static double	ConvertWordToDouble(char* word);
	static int		ConvertWordToInt(char* word);

	static bool ConvertDelimtedStringToFieldsArr(double*& fieldArr,
		int &numOfFieldss, char* oneLine , char delimiter);

	static bool DownloadPersonTwoDimFile(	cGlobals &globals,
	bool*& isPredictiveVar, 
	//double*& depArr,
	int &numberOfOrgVariabless ,	int &depVarIndex ,
	//	int &numberOfPatients ,
		
		cVariableAndValueAndPoints*& regresValueWeightsArr, int &numOfRegreWeightElements,	
		cVariableAndValue*&  guidedInclusionsRuleList, 	int &guidedInclusionRuleListSize,
			int &numberOfIntervention,
			int*& indexOfInterventionField,
			int*& indexOfPropoensityCorresField,
			bool*& isInterventionVarArray, int*& indexOfPropCoresVar);//,
		//char* inputPatientFilePAth, 
	//	char* inputMetaFilePath  ,  char endOfPAragSign,  char delimiter);

	
	 
};


#define MAX_NUMBER_OF_VALUE_PER_HISTOGRAM  10
class cHistogram
{
public:
	char* m_valArr;//[MAX_NUMBER_OF_VALUE_PER_HISTOGRAM];
	int* m_cntArr;//[MAX_NUMBER_OF_VALUE_PER_HISTOGRAM];
 

	char m_histMaxSize;
	char m_currentSize;

	cHistogram();
	~cHistogram();
	void AddValue(char value);
	bool GetMostLikelyValue(char &pattern, int &cnt, double &percFromAll,cHistogram* globalHist);
	
	double GetRateOffApperance( char val);

	void CalulcateWeightedMeanAndSD(double &mean, double &sd);
	int GetCountForInputValue(char val);
	int GetTotalCount();
	void Sort();
	void	FindLowestVal(int &lowestValIndex, int indexToStartFrom);
	
};





class cHashStrChainObj
{
public:
	cHashStrChainObj* m_next;
	char* m_str;
	cHistogram* m_hist;
	int m_strSize;//for a string of 10 letter the strLen is 11 to have the NULL in the end of line


	cHashStrChainObj()
	{
		m_next=NULL;
		m_str=NULL;
		m_hist = NULL;
		m_strSize = 0;
	}
	~cHashStrChainObj();

	void Initialize(char* str,  char value);
	

	void AddStrAppearance(  char value);
	

//	void AddPointersToSignifantObjectsRec(	cHashStrChainObj** sigHashChainObjs, int &indexInOutArray, cGlobals* globals); 
	int CountSignificantChainObjsRec(cHashStrChainObj** sigHashChainObjsTest, int &testCoiunter, cGlobals* globals);
		//double universeMean,  double universSD);

	bool IsStrFoundAlongChainRecursive(cHashStrChainObj*& chainObj, char* str);

	void PrepareStringAndPattern(char* outStr,char &pattern, char delimiter,cGlobals* globals);
	void PrepareString(char* outStr);
	
	void PrepareStringAndPatternExtended(char* outStr,char &pattern, char delimiter,cGlobals* globals);
	
	bool IsSignificantStringLink(char pattern,  int cnt,  double percFromAll, double universeMean, double universSD);
	bool IsSignificantStringLinkNew(cGlobals* globals );
	bool IsDangerousStringAsPAttern(cGlobals* globals);
	
	double CalculateOddRatioHistogram( double &percFromAll , 
		int &sumCnts, cHistogram* globalHist );
	void ConvertToStr(char* str, int &strLen, int num);

	static bool IsPAtternAssociationMeanAndSDsignifciantLocal(
				double	avg, double sd,double universMean, double universSD)
	{
		//if( cVarianceCalc::Abs( (avg - universMean ) / universSD)  > SIG_DEVIATION_IN_SD )
		
		double meanScore =0.0;
		if(universSD > 0.0)
		{
			meanScore=cVarianceCalc::Abs( (avg - universMean ) / universSD)  ;
		}
		
		double sdScore = 0.0;//universSD - sd;
		if(universSD > 0.0)
		{
			sdScore =( universSD - sd) / universSD;
		}

		bool ret=false;
		if( (meanScore  > SIG_DEVIATION_IN_SD) || (sdScore > SIG_REDUCTION_IN_SD) )
		{
			ret = true;
		}
		return ret;
	}

	
};

 

class cHashObject
{
public:
	int m_numOfHits;
	int m_sumOfValues;
	int m_sumSqrValues;
	bool m_isSig;
	cHashStrChainObj* m_hashStrChainObj;


	cHashObject();
	~cHashObject();


	void Add(char value)
	{
		m_numOfHits++;
		m_sumOfValues += int(value);
		m_sumSqrValues += (  int(value) * int(value)  );	
		if(m_numOfHits > 40)
		{
			int sdfff=0;
		}
	}

	bool IsStrFoundAlongChain(cHashStrChainObj*&  matchedObj,  char* str);
	void CreateNewChainElement(char* str , char value);

	void AddStr(char* str, char value);

	void CalcAvgAndSD (double &mean, double &sd);

	//void AddPointersToSignifantObjects(	cHashStrChainObj** sigHashChainObjs, int &indexInOutArray); 
	//int CountSignificantChainObjsRec();

	

};
 

class cHashObjectArray
{
public:
	int m_size;
	cHashObject* m_arr;

	int m_sizeOfInitialHash;
	int* m_initialArr;
	int m_numOfParagraphs;
	int m_totalNumOfInitialSubstrings;
	 


	cHashObjectArray(int size, int initialHashSize);
	~cHashObjectArray();
	
	void Push( char* str, char value, int pushMode);//0 1 2 steps    
	//11 1 22 replace the int to unsigned int the return 
	static unsigned int  Hashfunction(char* str, int hashSize); 

	void CalcualteSignificance(double universMean, double universSD);

	
	void ExtractPointersOfSignificantHashChainObjects(cHashStrChainObj**& sigHashChainObjs, int &numOfObjects ,cGlobals *globals);

	int GetstringSampleBucketNum(char* str);

	void CalcualteTotalInitialHashStringNum()
	{
		m_totalNumOfInitialSubstrings = 0;
		for(int i = 0 ; i < m_sizeOfInitialHash ; i++)
		{
			m_totalNumOfInitialSubstrings += m_initialArr[i];
		}
	}
	void SetNumberOfInutFileParagraphs(int num)
	{
		m_numOfParagraphs = num;
	}
	

	 
};

class cStringHistogram
{
	char** m_valueArr;
	int m_size;
	int* m_cntArr;
public:

	cStringHistogram()
	{
		m_valueArr = NULL;
		m_size = 0;
		m_cntArr = NULL;
	}

	~cStringHistogram()
	{
		if(m_valueArr != NULL)
		{
			for(int i = 0 ; i < m_size ; i++)
			{
				if(m_valueArr[i]!= NULL)
				{
					delete []m_valueArr[i];
					m_valueArr[i]=NULL;
				}
			}
			delete []m_valueArr;
			m_valueArr=NULL;
			delete []m_cntArr;
			m_cntArr=NULL;
		}
	}


//4 27 23 BBB
	void ReadWriteHistObject(cArrayFlex* arrayFlex  , cGlobals* globals)
	{
		bool isWrite = arrayFlex->GetIsWriteMode();
		char str[200];
		strcpy(str,"size of hist");
		arrayFlex->WriteReadArrayString(str, isWrite, *globals);

		arrayFlex->WriteReadArrayInt(m_size,isWrite,*globals);
		if(!isWrite)
		{
			m_valueArr = new char*[m_size];
			m_cntArr = new int[m_size];
		}
		for(int i = 0 ; i < m_size ; i++)
		{
			strcpy(str," hist bucket index string and count:");
			arrayFlex->WriteReadArrayString(str, isWrite, *globals);

			if(isWrite)
			{
				arrayFlex->WriteReadArrayString(  m_valueArr[i], isWrite, *globals);
			}
			else
			{
				arrayFlex->WriteReadArrayString(str,   isWrite,*globals);//4 27 23 add memory alocation for the pharase
				int len = strlen(str);
				m_valueArr[i]  = new char[len+1];
				strcpy(m_valueArr[i], str);
			}
			arrayFlex->WriteReadArrayInt(m_cntArr[i],isWrite, *globals);
		}
	}





	int GetSize()
	{
		return m_size;
	}
	char* GetValueArr(int valStrIndex)
	{
		return m_valueArr[valStrIndex];
	}

	int GetStrValIndex(char* str)
	{
		for(int i = 0 ; i < m_size; i++)
		{
			if(! strcmp(str, m_valueArr[i]) )
			{
				return i;
			}
		}
		return -1;
	}

	int* GetCntArray()
	{
		return m_cntArr;	
	}

	int GetTotalSample()
	{
		int sum = 0;
		for(int i = 0 ; i < m_size ; i++)
		{
			sum += m_cntArr[i];
		}
		return sum;
	}

	void SortHistrogramStringsAndCntArrays()
	{
		for(int i = 0 ; i < (m_size -1) ; i++)
		{
			for(int ii = i+1 ; ii < m_size ; ii++)
			{
				int v = strcmp(m_valueArr[i],m_valueArr[ii]);
				if(v > 0 )
				{
					char* tempStr = m_valueArr[i];
					m_valueArr[i] = m_valueArr[ii];
					m_valueArr[ii] = tempStr ;
					int tempCnt = m_cntArr[i];
					m_cntArr[i] = m_cntArr[ii];
					m_cntArr[ii] = tempCnt;
				}
			}
		}	
	}



	void AddHistValue(char* valStr)
	{
		bool isFound = false;
		for(int i = 0 ; i < m_size ; i++)
		{
			if( !strcmp(m_valueArr[i] , valStr))
			{
				isFound = true;
				m_cntArr[i]++;
			}
		}
		if(!isFound)
		{
			int newSize = m_size + 1;
			char** strArr = new char*[newSize];
			int* cntArr = new int[newSize];
			for( int i = 0 ; i < m_size ; i++)
			{
				strArr[i] = m_valueArr[i];
				cntArr[i] = m_cntArr[i];
			}
			char* newValStr = new char[strlen(valStr)+1];
			strcpy(newValStr,valStr);
			strArr[m_size] = newValStr;
			cntArr[m_size]=1;
			if(m_valueArr != NULL)
			{
				delete []m_valueArr;
				m_valueArr=NULL;
				delete []m_cntArr;
				m_cntArr=NULL;
			}
			m_valueArr = strArr;
			m_cntArr = cntArr;
			m_size++;
			SortHistrogramStringsAndCntArrays();
		}
	}
};

class cHashObj
{
	char* m_phrase;
	cStringHistogram m_hist;
	cHashObj* m_next;
	
public:
	cHashObj()
	{
		m_phrase = NULL;
		m_next=NULL;
	}
	cHashObj(char* phrase, char* val)
	{
		int len = strlen(phrase);
		m_phrase = new char[len+1];
		m_next=NULL;
		strcpy(m_phrase, phrase);
		UpdateData(val);
	}

	void WriteReadHashObject(cArrayFlex* arrayFlex  , cGlobals* globals)
	{
		char str[200];
		bool isWrite = arrayFlex->GetIsWriteMode();
		strcpy(str, "startOneHashObj");
		arrayFlex->WriteReadArrayString(str, isWrite,*globals);
		strcpy(str, "object phrase:");
		arrayFlex->WriteReadArrayString(str, isWrite,*globals);

		if(isWrite)
		{
			arrayFlex->WriteReadArrayString(m_phrase,   isWrite,*globals);//4 27 23 add memory alocation for the pharase
		}
		else
		{
			arrayFlex->WriteReadArrayString(str,   isWrite,*globals);//4 27 23 add memory alocation for the pharase
			int len = strlen(str);
			m_phrase = new char[len+1];
			strcpy(m_phrase, str);		
		}
			//in read time 

		if(!isWrite)
		{
			m_next = NULL;
		}
		strcpy(str, "histrogram:");
		arrayFlex->WriteReadArrayString(str, isWrite,*globals);
	//4 27 23 a complete this 
		m_hist.ReadWriteHistObject( arrayFlex  , globals);
		 
		strcpy(str, "end of hash object:");
		arrayFlex->WriteReadArrayString(str, isWrite,*globals);
	
	}



	int GetHistTotalCnt()
	{
		return m_hist.GetTotalSample();
	}

	bool IsManualObject(char* valStr)
	{
		if( (GetPhrase()[0] == '~' ) &&  (GetHistTotalCnt()==1))
		{
			if( ! strcmp( m_hist.GetValueArr(0),valStr)) 
			{
				return true;
			}
		}
		return false;
	}
			
 


	int CountRecursizeNumberOfObjects()
	{
		int ret = 1; //this one
		int otherCnt = 0;
		if( m_next != NULL)
		{
			otherCnt = m_next->CountRecursizeNumberOfObjects();
			ret += otherCnt;
		}
		return ret;		
	}

	void UpdateData(char* valStr)
	{
		m_hist.AddHistValue(valStr);
	}
	void SetNext(cHashObj* next)
	{
		m_next = next;	
	}
	char* GetHistValueArr(int i)
	{
		return m_hist.GetValueArr(i);
	}
	
	char* GetPhrase()
	{
		return m_phrase;
	}


	int GetStringvAlueIndex(char* valStr)
	{
		return m_hist.GetStrValIndex(valStr);
	}

	int GetHistrogramCnt( int index)
	{
		return m_hist.GetCntArray()[index];
	}

	cHashObj* GetNext()
	{
		return m_next;
	}

	 
	~cHashObj()
	{
		if(m_next != NULL)
		{
			delete m_next;
			m_next = NULL;
		}
		if(m_phrase != NULL)
		{
			delete []m_phrase;
			m_phrase = NULL;
		}
	}
	
	/*
	everey value, i.e 0 and 1. or yes and no, will have sig for the yes and one for the no
	the odd raio calcualtion for the 
	*/
	void CalculateValueArrSignificance(char** valuStrArr, double* sigArr,
		int numOfValues, cStringHistogram* globalHistogram)
	{
		 
		for(int i = 0 ; i < numOfValues ; i++)
		{
			char* valArr = globalHistogram->GetValueArr(i);
			valuStrArr[i] = new char[strlen(valArr) +1];
			
			//copy the string of value and then followed by scores
			strcpy(valuStrArr[i]  , valArr);
		    //how many this value is a univer average, i.e. 10% yes for Vent of all. then , how many times of this value in this
			//hash obj h istogram, is it more likely than 10% or less. so it can be  0.2 / 0.1 if with a phrase we would get 
			int cntThisValueGlobal =	globalHistogram->GetCntArray()[i];
			double globalValPercFromAll  = (double(cntThisValueGlobal)) / (double(globalHistogram->GetTotalSample()));
		//	int cntOtherValuesGlobal = globalHistogram->GetTotalSample() - cntThisValueGlobal ;
			//int cntThisValThisPhrase = 0;
			int stringValueIndexThisHash = GetStringvAlueIndex(valArr);
			int cntThisValueThisHashObj =0;
			if(stringValueIndexThisHash >= 0)
			{
				cntThisValueThisHashObj = m_hist.GetCntArray()[stringValueIndexThisHash];
			}
			double thisPhrasePErcFromAll = 0.0;
			if(m_hist.GetTotalSample() > 0.0)
			{
				thisPhrasePErcFromAll = double(cntThisValueThisHashObj) / double (m_hist.GetTotalSample());
			}
			double ratio = 1.0;
			if(m_hist.GetTotalSample() < 150)
			{
				int sdg = 0 ; 
			}
			if(globalValPercFromAll > 0.0)
			{
			//	ratio = thisPhrasePErcFromAll / globalValPercFromAll;//so 0.2 / 0.1 will give 2 and 0.05  / 0.1 wll give 0.5
				ratio = CalculateOddRatioParag(  thisPhrasePErcFromAll ,  globalValPercFromAll);
			}
			sigArr[i] = ratio;
			//sigArr[i] = Max(sigArr[i] , 0.1);
			//highestSig = cVarianceCalc::Max(highestSig , ratio);
		}
	
	}

	static double CalculateOddRatioParag( double thisPhrasePErcFromAll , double globalValPercFromAll)
	{
		double odd = 1.0;
		//if(globalValPercFromAll > 0.0)
		{
			if(  globalValPercFromAll > 0.0 && globalValPercFromAll < 0.5)
			{
			//	if(thisPhrasePErcFromAll < globalValPercFromAll)
			//	{
				odd = thisPhrasePErcFromAll / globalValPercFromAll;//for exa 0.1, 0.3 -> 0.33 odd ratio which is strong
			//	}
			//	else
			//	{
			//		odd =  thisPhrasePErcFromAll / globalValPercFromAll;//for exa 0.6, 0.3 ->2.0,  odd ratio, above 1, also strong almost as much
			//	}
			}
			else //if (globalValPercFromAll < 1.0)
			{
				double compThisPhrPerc = 1.0 - thisPhrasePErcFromAll;
				double compGlobalPerc = 1.0 - globalValPercFromAll;

				//if(thisPhrasePErcFromAll < globalValPercFromAll)
			//	{
				double tempOdd = 1.0;
				if(compGlobalPerc > 0.0)
				{
					tempOdd = compThisPhrPerc / compGlobalPerc;//for exa 0.9, 0.8 -> 0.1, 0.2 -> 0.5 -> 2.0. 0.33 odd ratio which is strong
					if( tempOdd != 0.0)//4 21 23
					{
						tempOdd = 1.0 / tempOdd;
						odd = tempOdd;
					}
				}
			}	
		}
		return odd;	
	}


		
/*
	bool GetHistogramNumberOfValues()
	{
		return m_hist.GetSize();
	}
*/


	double GetOddPerInputValue(char* valStr, cStringHistogram* globalHistogram)
	{
		double ret = 1.0;
		int numOfValues = globalHistogram->GetSize();
		char** strs = new char*[numOfValues];
		double* sigArr = new double[numOfValues];
		for(int i = 0 ; i < numOfValues ; i++)
		{
			strs[i] = NULL;
			sigArr[i] = 1.0;
		}
		CalculateValueArrSignificance(strs, sigArr, numOfValues, globalHistogram);
		int thisValIndex = globalHistogram->GetStrValIndex(valStr);
		if(thisValIndex >=0)
		{
			ret =  sigArr[thisValIndex];
		}

		if(strs!=NULL)
		{
			for(int i  = 0 ; i < numOfValues ; i++)
			{
				if(strs[i]!=NULL)
				{
					delete []strs[i];
					strs[i] = NULL;
				}
			}
			delete []strs;
			strs=NULL;
		}
		if(sigArr != NULL)
		{
			delete []sigArr;
			sigArr = NULL;
		}

		return ret;
	}

	bool IsToBeRemovedBasedOnSignificanceRecursive(
		cStringHistogram* globalHistogram, double  minSig, int minSmpleToClean)
	{
		bool ret = false;
		int numOfValues = globalHistogram->GetSize();
		char** strs = new char*[numOfValues];
		double* sigArr = new double[numOfValues];
		for(int i = 0 ; i < numOfValues ; i++)
		{
			strs[i] = NULL;
			sigArr[i] = 1.0;
		}
	
		//strs is set of strings of values that patiets could get in a varible of subjet. sigArr will show for each value string
		//what is the signifciance of this object 
		CalculateValueArrSignificance(strs,sigArr,  numOfValues, globalHistogram);
		//3 3 23 go to where we 
		/*
		if i have a 90/10 no vent / vent and i have a phrase that supports no vent, it wil get a 95 / 5 means that the histogram
		will have a 0.95/0.9 = 1.04 odd ratio for the value 0/no vent. in that same h istogram, we also ahve the value 1, since htis 
		is a phrase that goes with the no vent, it will be  now 10% global and 5% this, so 0.05/0.1 is 0.5
		*/
		double highestAbsOddRAto = 1.0;
		for(int i = 0 ; i < numOfValues ; i++)
		{
			double x = sigArr[i];
			if(x < 1.0)
			{
				x = 1.0 / x;
			}
			highestAbsOddRAto = cVarianceCalc::Max(highestAbsOddRAto , x);
		}
		
		
		if( highestAbsOddRAto < minSig )
		{
			int sample = m_hist.GetTotalSample();//need certain sample to set a decision about no significanct 
			if(sample >= minSmpleToClean)//need a lot to prove not signiciant across diffrnert values
			{
				ret = true;
			}
		}
		if(m_next != NULL)
		{
			if(m_next->IsToBeRemovedBasedOnSignificanceRecursive(globalHistogram, minSig, minSmpleToClean))
			{
				cHashObj* temp = m_next;
				m_next = m_next->GetNext();
				temp->SetNext(NULL);
				delete temp;
				temp=NULL;
			}
		}
		if(strs!=NULL)
		{
			for(int i  = 0 ; i < numOfValues ; i++)
			{
				if(strs[i]!=NULL)
				{
					delete []strs[i];
					strs[i] = NULL;
				}
			}
			delete []strs;
			strs=NULL;
		}
		if(sigArr != NULL)
		{
			delete []sigArr;
			sigArr = NULL;
		}
		return ret;
	}
			
	bool IsToBeRemovedBasedOnSampleRecursive(int minSample);
	 

	bool IsLookUp(cHashObj *&localData, char* phrase)
	{
		if(m_next != NULL)
		{
			if( m_next->IsLookUp(localData, phrase))
			{
				return true;
			}
		}
		if( !(strcmp(m_phrase, phrase)))
		{
			localData = this;
			return true;
		}
		return false;
	}	
};


class cGlobals;

class cPhraseHash
{
	int m_size;
	cHashObj** m_arr;
	int m_numOfObjects;
	int* m_numberOFObjectArr;

public:
	cPhraseHash(int size)
	{
		m_size = size;
		m_numOfObjects=0;
		m_numberOFObjectArr = new int[size];
		m_arr = new cHashObj*[size];
		for(int i = 0 ; i < size ; i++)
		{
			m_arr[i] = NULL;
			m_numberOFObjectArr[i]=0;
		}
	}
	cPhraseHash()
	{
		m_size = 0;
		m_numOfObjects=0;
		m_numberOFObjectArr = NULL;
		m_arr = NULL;
	}
	~cPhraseHash()
	{
		DeleteHashContent();
		if(m_arr != NULL)
		{
			delete []m_arr;
			m_arr=NULL;
		}
	}

	//4 27 23 b - call the function that operate the entire call from disc
	void	ConvertChainToArray(cHashObj** arrayOut , cHashObj* firstLink, int numberOFIterms)
	{
		cHashObj* temp = firstLink;
		for(int i = 0 ; i < numberOFIterms;i++)
		{
			arrayOut[i] = temp;
			temp = temp->GetNext();
		}
	}

	void ReadWriteHash( cArrayFlex* arrayFlex, cGlobals* globals);

	void AddShadowObjects();

	int GetSize()
	{
		return m_size;
	}
	cHashObj** GetArray()
	{
		return m_arr;
	}

	
	//3 3 23
	static void Delete(cHashObj *&obj)
	{
		obj->SetNext(NULL);
		//delete obj;
		obj = NULL;
	}

	void DeleteHashContent()
	{
		if(m_arr != NULL)
		{
			for(int i = 0 ; i < m_size ; i++)
			{
				if(m_arr[i] != NULL)
				{
					delete m_arr[i];
					m_arr[i] = NULL;
					m_numberOFObjectArr[i]=0;
				}
			}
			m_numOfObjects=0;
		}
	}


	int GetNumberOfHashObjects()
	{
		int num = 0 ; 
		for(int i = 0 ; i < m_size ; i++)
		{
			if((m_arr != NULL) && (m_arr[i] != NULL))
			{
				int localSpotNum = m_arr[i]->CountRecursizeNumberOfObjects();
				num += localSpotNum ;
			}
		}
		if(num != m_numOfObjects)
		{
			int sdf=0;
		}
		return num;
	}

	void CopyOnHashChain(cHashObj** objArray , int &movingIndex, cHashObj* firstObj)
	{
		objArray[movingIndex++] = firstObj;
		cHashObj* next = firstObj->GetNext();
		while( next != NULL)
		{
			objArray[movingIndex++] = next;
			next = next->GetNext();
		}
	}




	void ExportHashToArray(cHashObj **&objArray , int &numOfHashObjects);
	/*{
		numOfHashObjects = GetNumberOfHashObjects();
		objArray = new cHashObj*[numOfHashObjects];
		int movingIndex = 0;
		for(int i = 0 ; i < m_size ; i++)
		{
			if(m_arr[i] != NULL)
			{
				CopyOnHashChain(objArray , movingIndex, m_arr[i] );
				m_arr[i] = NULL;
				//objArray[movingIndex] = m_arr[i] ;
			}
		}
		if(!(movingIndex == numOfHashObjects))
		{
			int sdg = 0 ;
		}
		for(int i = 0 ; i < numOfHashObjects ; i++)
		{
			objArray[i]->SetNext(NULL);
		}
		for(int i = 0 ; i < numOfHashObjects ; i++)
		{
			bool isIsubstr = false;
			for(int ii = 0 ; (ii < numOfHashObjects ) && (ii != i); ii++)
			{
				if(  ( objArray[ii]  != NULL) &&
					(cParagraphAnalytics::IsLeftStrSubStringOfRightStr( objArray[i]->GetPhrase(), objArray[ii]->GetPhrase())))
					
				{
					isIsubstr = true;
				}
			}
			if(isIsubstr)
			{
				delete objArray[i] ;
				objArray[i] = NULL;
			}
		}
		int movingIndex = 0;
		for(int i = 0 ; i < numOfHashObjects ; i++)
		{
			if(objArray[i] != NULL)
			{
				objArray[movingIndex++] = objArray[i];
			}
		}
		numOfHashObjects = movingIndex;
	}*/



	void CleanBasedOnSignificance(cStringHistogram* globalHistogram, double minSig, int minSmpleToClean)
	{
		for(int i = 0 ; i < m_size ; i++)
		{
			if(m_arr[i] != NULL)
			{
				if(	m_arr[i]->IsToBeRemovedBasedOnSignificanceRecursive( globalHistogram, minSig,minSmpleToClean))
				{
					cHashObj* temp = m_arr[i];
					m_arr[i] = m_arr[i]->GetNext();
					temp->SetNext(NULL);
					delete temp;
					temp=NULL;
					m_numOfObjects--;
					m_numberOFObjectArr[i]--;
				}
			}
		}
	}



	void CleanBasedOnSample(int minSample)
	{
		for(int i = 0 ; i < m_size ; i++)
		{
			if(m_arr[i] != NULL)
			{
				if(	m_arr[i]->IsToBeRemovedBasedOnSampleRecursive(minSample))
				{
					cHashObj* temp = m_arr[i];
					m_arr[i] = m_arr[i]->GetNext();
					Delete(temp);
					m_numOfObjects--;
					m_numberOFObjectArr[i]--;
				}
			}
		}
	}
	 

	void SetValue(cHashObj *data, char* phrase, bool isAllPtHash)
	{
		int index = (int)(cHashObjectArray::Hashfunction(phrase, m_size));
		if(index == 351 && isAllPtHash)
		{
			int dfg=0;
		}

		if(m_arr[index] != NULL)//no need for this if, anyway it goes
		{
			data->SetNext( m_arr[index]);
		}
		m_arr[index] = data;
		m_numOfObjects++;
		m_numberOFObjectArr[index]++;
	}
	

	bool AddManualPhrases(char* manuelPhrasesFilePath, cGlobals* globals);


	//cHashObjectArray::unsigned int  Hashfunction(char* str, int hashSize);
	bool IsLookUp(cHashObj *&data, char* phrase)
	{
		data=NULL;
		int index = (int)(cHashObjectArray::Hashfunction(phrase, m_size));
		if(m_arr[index] != NULL)
		{
			cHashObj *localData=NULL;
			if( m_arr[index]->IsLookUp(localData, phrase))
			{
				data = localData;
				return true;
			}
		}
		return false;
	}
};


class cPatientMapElements
{
public:
	int  m_numOfvalues;
	double* m_highestOddThisValArr ;
	double* m_highestOddAnyOtherValToThisValArr;
	cHashObj** m_highestOddThisVarObj;
	cHashObj** m_highestOddAnyOtherValObj;

	cHashObj** m_manualObj;

	double* m_highestOddSumInThisValContextArr;
	double* m_thirdDimArr;
	double* m_forthDimArr;
	cHashObj** m_phraseObjArray ;// new  cHashObj*[numOfHashObjects ];
	int m_numOfPhraseHashObjects ;
	char m_valueStr[100];

	cPatientMapElements(int numOfvalues)
	{
		m_numOfvalues= numOfvalues;
		m_highestOddThisValArr = new double[m_numOfvalues];
		m_highestOddAnyOtherValToThisValArr  = new double[m_numOfvalues];

		m_highestOddThisVarObj = new cHashObj*[m_numOfvalues];
		m_highestOddAnyOtherValObj  = new cHashObj*[m_numOfvalues];
		
		m_manualObj = new cHashObj*[m_numOfvalues];

		m_highestOddSumInThisValContextArr = new double [m_numOfvalues];
		m_thirdDimArr = new double [m_numOfvalues];
		m_forthDimArr = new double [m_numOfvalues];
		 
		for(int index= 0 ; index < numOfvalues ; index++)
		{
			m_highestOddThisValArr[index]=0.0;
			m_highestOddAnyOtherValToThisValArr[index]=0.0;
			m_highestOddThisVarObj [index] = NULL;
			m_highestOddAnyOtherValObj[index]=NULL;
			m_manualObj[index]=NULL;
			m_highestOddSumInThisValContextArr[index]=0.0;
			m_thirdDimArr[index]=0.0;
			m_forthDimArr[index]=0.0;
		}
		m_phraseObjArray = NULL;
		m_numOfPhraseHashObjects = 0;
		m_valueStr[0]=0;

	}
	~cPatientMapElements()
	{
		if(m_phraseObjArray != NULL)
		{
			for(int i = 0 ; i < m_numOfPhraseHashObjects ; i++)
			{
				delete m_phraseObjArray [i];
			}
			delete[] m_phraseObjArray ;
		}
		delete []m_highestOddThisValArr;
		delete []m_highestOddAnyOtherValToThisValArr;
		delete []m_highestOddThisVarObj;
		delete[] m_highestOddAnyOtherValObj;
		delete []m_manualObj;
		delete[] m_highestOddSumInThisValContextArr;
		delete[] m_thirdDimArr;
		delete[] m_forthDimArr;
		//delete []m_highestOddSumAnyValueArr;
	}

	void CopyValueString(char* str)
	{
		strcpy(m_valueStr,str);
	}

	void FillThreeDimensions(double &firstDim, double  &secondDim, double &thirdDim , double &forthDim , int valueIndex)
	{
		firstDim = m_highestOddThisValArr[valueIndex];
		secondDim =	m_highestOddAnyOtherValToThisValArr[valueIndex];
		thirdDim = m_thirdDimArr[valueIndex];
		forthDim = m_forthDimArr[valueIndex];
			//m_highestOddSumInThisValContextArr[valueIndex];
	}
};



class InputVariablesPackageForResearchObj
{
public:
	int m_numberOfSubGrps;//; //within each profile we got risk groups, cacn do a 5 or 3 
	int m_profileListMaxSize;
	int m_thresholdForTerminalProfile;
	int m_numberOfVariables;

//double** m_personsDataSet;
//	int m_numberOfPatients;
//int m_numberOfOrgVariables;
	//double* m_depArr;
	bool* m_isPredictive; //personsDataSet depArr
	bool* m_isIntervention;
	int* m_indexOfPropIntervention; //if not -1 than the value of the field will be the one that has the intervention bool flag. the index of position of this will be where the popensity is
	cVariableAndValueAndPoints* m_varValPointsRegWghArr; 
	int m_numOfRegrEleents;
	cVariableAndValue*  m_guidedInclusionsRuleList;
	int m_guidedInclusionRuleListSize;


	int m_numberOfIntervention;
	int*  m_indexOfInterventionField;
	int* m_indexOfPropoensityCorresField;




	InputVariablesPackageForResearchObj();
	~InputVariablesPackageForResearchObj();

	 
	
	bool PrepareMetaDataElements(	  int &depVarIndex,  cGlobals &globals);
	bool PrepareInputDataSetElements(int &depVarIndex,	char* inputPatientFilePAth, char endOfParagraphInSign, char delimiter	 );


	bool IsVarIncludes( int var);
	bool IsVarVAlHasNonZeroPoints(int var,  double val);
	bool IsVarHasAnyValWithNonZeroPnts( int var);
		 
};

class cGlobals;



class cPatientRecordObject 
{
	//unique patient ID object, 
	int* m_paragIndexList;
	int m_sizeOfAllocatedIndexList;
	int m_numberOfActualIndexes;
	char m_patientIDstr[100];
	char m_patientValueStr[100];

	cHashObj** m_phraseObjArray;
	int m_numOfPhraseHashObjects;
	//cHistogram m_hist;
public:
	cPatientRecordObject()
	{
		m_paragIndexList=NULL;
		m_sizeOfAllocatedIndexList=0;
		m_numberOfActualIndexes=0;
		m_patientIDstr[0]=0;
		m_patientValueStr[0]=0;
		m_phraseObjArray=NULL;
		m_numOfPhraseHashObjects=0;
	}
	cPatientRecordObject(char* idStr)
	{
		m_paragIndexList=NULL;
		m_sizeOfAllocatedIndexList=0;
		m_numberOfActualIndexes=0;
		strcpy((char*)m_patientIDstr,idStr);
		m_patientValueStr[0]=0;
		m_phraseObjArray=NULL;
		m_numOfPhraseHashObjects=0;
	}

	~cPatientRecordObject()
	{
		if(m_paragIndexList != NULL)
		{
			delete []m_paragIndexList;
		}
		if(m_phraseObjArray != NULL)
		{
			for( int i = 0 ; i < m_numOfPhraseHashObjects ; i++)
			{
				if(m_phraseObjArray[i] != NULL)
				{
					delete m_phraseObjArray[i];
				}
			}
			delete m_phraseObjArray;
		}
	}

	void CreateArrayAndCollectListOfPAragraphs(
						char **&listOfParagraphOfOnePatient, int &numberOFPAragraphs, char** globalParagrArray)
	{
		numberOFPAragraphs = m_numberOfActualIndexes;
		listOfParagraphOfOnePatient = new char*[numberOFPAragraphs];
		for(int i = 0 ; i < numberOFPAragraphs ; i++)
		{
			listOfParagraphOfOnePatient[i] = globalParagrArray[m_paragIndexList[i]];
		}
	}

	void AddPhraseObjArray(cHashObj** phraseObjArray , int numOfPhraseHashObjects)
	{
		m_phraseObjArray= phraseObjArray;
		m_numOfPhraseHashObjects = numOfPhraseHashObjects;
	}


	int GetNumberOfActualIndexes () 
	{
		return m_numberOfActualIndexes;
	}

	int* GetParagIndexArr ()
	{
		return	m_paragIndexList;
	}

	bool IsPatientID(char* ptIDstr)
	{
		bool ret =  (strcmp(m_patientIDstr,ptIDstr) == 0)	;
		return ret;
	}

	char* GetValueStr()
	{
		return m_patientValueStr;
	}



	bool SetValueString(char* valStr)
	{
		bool isConflictValue = false;
		if(m_patientValueStr[0]!=0 && (strcmp(m_patientValueStr,valStr)))
		{
			isConflictValue = true ;
		}
		strcpy(m_patientValueStr, valStr);
		return isConflictValue;
	}

	//3 3 23 ***? see that we add new index to the array only of the paraag str is not same as other paragraphs this patient owns
	void AddParagraphIndex(int paragIndex, char** paragStr)
	{
		bool isSimilarToAnotherParag = false;
		for(int i = 0 ; i < m_numberOfActualIndexes && (!isSimilarToAnotherParag) ; i++)
		{
			char* str = paragStr[m_paragIndexList[i]];
			if( ! strcmp(paragStr[paragIndex], str))
			{
				isSimilarToAnotherParag = true;
			}
		}
		if(!isSimilarToAnotherParag)
		{
			m_sizeOfAllocatedIndexList++;
			int* temp = new int[m_sizeOfAllocatedIndexList];
			for(int ii = 0 ; ii <( m_numberOfActualIndexes); ii++)
			{
				temp[ii] = m_paragIndexList[ii];
			}
			temp[m_numberOfActualIndexes++] = paragIndex;
			if(m_paragIndexList != NULL)
			{
				delete []m_paragIndexList;
			}
			m_paragIndexList = temp;
		}
	}
};


#define NUM_OF_PARAG_THIRD_DIM_BUCKETS 5

#define LOCAL_NUMBER_OF_BUCKETS 3
#define LOCAL_TWO_DIM_BUCKET_NUM 9

class cTableBucket
{
public:
	double m_value;
	double m_avgOddFirst;
	double m_avgOddSecond;
	int m_cnt;
	double m_percentageSample;
	double m_firstDimLowZ;
	double m_firstDimUpperZ;
	double m_secondDimLowerZ;
	double m_secondDimUpperZ;

	double m_thirdValArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double m_thirdOddArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double m_forthValArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double m_forthOddArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	int m_thirdCntArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	int m_forthCntArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];


	double m_virtualValue;
	
	double m_thirdThresholdArrLocal[LOCAL_NUMBER_OF_BUCKETS];
	double m_thirdValArrLocal[LOCAL_NUMBER_OF_BUCKETS];
	double m_thirdOddArrLocal[LOCAL_NUMBER_OF_BUCKETS];
	int m_thirdCntArrLocal[LOCAL_NUMBER_OF_BUCKETS];

	double m_forthThresholdArrLocal[LOCAL_NUMBER_OF_BUCKETS];
	double m_forthValArrLocal[LOCAL_NUMBER_OF_BUCKETS];
	double m_forthOddArrLocal[LOCAL_NUMBER_OF_BUCKETS];
	int m_forthCntArrLocal[LOCAL_NUMBER_OF_BUCKETS];

	double m_twoDimThirForthBucketVal[LOCAL_TWO_DIM_BUCKET_NUM];
	int m_twoDimThirForthBucketCnt[LOCAL_TWO_DIM_BUCKET_NUM];
	double m_avgThirdDimArr[LOCAL_TWO_DIM_BUCKET_NUM];
	double m_avgForthDimArr[LOCAL_TWO_DIM_BUCKET_NUM];





	void WriteReadObjectBucket(cArrayFlex* arrayFlex ,  cGlobals *globals)
	{
		bool isWrite = arrayFlex->GetIsWriteMode();
		char str[200];
		strcpy(str,"value and virtual value");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayDouble(m_value, isWrite, *globals);
		arrayFlex->WriteReadArrayDouble(m_virtualValue, isWrite, *globals);
		strcpy(str,"odd fisrt and odd second,");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayDouble(m_avgOddFirst, isWrite, *globals);
		arrayFlex->WriteReadArrayDouble(m_avgOddSecond, isWrite, *globals);
		strcpy(str,"count and percentage sample");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayInt( m_cnt , isWrite ,  *globals);
 		arrayFlex->WriteReadArrayDouble(m_percentageSample , isWrite, *globals);
		strcpy(str,"first dim low and uppoer, second dim lower and upper");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayDouble(m_firstDimLowZ , isWrite, *globals);
		arrayFlex->WriteReadArrayDouble( m_firstDimUpperZ, isWrite, *globals);
		arrayFlex->WriteReadArrayDouble( m_secondDimLowerZ, isWrite, *globals);
		arrayFlex->WriteReadArrayDouble( m_secondDimUpperZ, isWrite, *globals);

		strcpy(str,"number of sub buckets");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		int numOfBuckets = NUM_OF_PARAG_THIRD_DIM_BUCKETS;
		arrayFlex->WriteReadArrayInt( numOfBuckets , isWrite ,  *globals);
		for(int i = 0 ; i < numOfBuckets ; i++)
		{
			strcpy(str,"thirdVal of sub bucket");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_thirdValArray[i], isWrite, *globals);
			strcpy(str,"third Odd  of sub bucket");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_thirdOddArray[i], isWrite, *globals);
			strcpy(str,"forth val of sub bucket");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_forthValArray[i], isWrite, *globals);
			strcpy(str,"forth Odd  of sub bucket");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_forthOddArray[i], isWrite, *globals);
			 
			strcpy(str,"third cnt  of sub bucket");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
			arrayFlex->WriteReadArrayInt( m_thirdCntArray[i] , isWrite ,  *globals);
			strcpy(str,"forth cnt  of sub bucket");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);			
			arrayFlex->WriteReadArrayInt( m_forthCntArray[i] , isWrite ,  *globals);
	 	}

		char tempStr[200];
		strcpy(tempStr,"number of local sub buckets");
		arrayFlex->WriteReadArrayString(tempStr,isWrite,*globals);
		int numOfLocalBuckets = LOCAL_NUMBER_OF_BUCKETS;
		arrayFlex->WriteReadArrayInt( numOfLocalBuckets, isWrite ,  *globals);
		for(int x=0;x< numOfLocalBuckets ; x++)
		{
			arrayFlex->WriteReadArrayDouble(	m_thirdThresholdArrLocal[x], isWrite, *globals);
			arrayFlex->WriteReadArrayDouble(m_thirdValArrLocal[x], isWrite, *globals);
			arrayFlex->WriteReadArrayDouble(	m_thirdOddArrLocal[x], isWrite, *globals);
			arrayFlex->WriteReadArrayInt(		m_thirdCntArrLocal[x], isWrite, *globals);
	
			arrayFlex->WriteReadArrayDouble(	m_forthThresholdArrLocal [x], isWrite, *globals);
			arrayFlex->WriteReadArrayDouble(	m_forthValArrLocal [x], isWrite, *globals);
			arrayFlex->WriteReadArrayDouble(	m_forthOddArrLocal [x], isWrite, *globals);
			arrayFlex->WriteReadArrayInt(	m_forthCntArrLocal [x], isWrite, *globals);
		}
		strcpy(tempStr,"number of two dim sub buckets");
		arrayFlex->WriteReadArrayString(tempStr,isWrite,*globals);
		int numOfTwoDimBuckets = LOCAL_TWO_DIM_BUCKET_NUM ;
		arrayFlex->WriteReadArrayInt( numOfTwoDimBuckets, isWrite ,  *globals);
		for(int x=0;x< numOfTwoDimBuckets; x++)
		{
			arrayFlex->WriteReadArrayDouble(	m_twoDimThirForthBucketVal [x], isWrite, *globals);
			arrayFlex->WriteReadArrayInt( m_twoDimThirForthBucketCnt [x], isWrite, *globals);
			arrayFlex->WriteReadArrayDouble(	m_avgThirdDimArr [x], isWrite, *globals);
			arrayFlex->WriteReadArrayDouble(	m_avgForthDimArr [x], isWrite, *globals);
		}	
	}

	//0,0 - > 0. 0,1 -> 1.  0,2 -> 2. 1,0 -> 3. 1,1->4, 1,2->5, 2,0->6,2,1->7,2,2->8
	static int GetTwoDimIndexFromTwoIndexes(int i, int ii, int sizeOneDim)
	{//5  5 23
		return (i*sizeOneDim) + ii;
	}

	/* 
	void SetInternalValues(double avgLeft,double avgThirdLEft, int cntLEft, double avgRight,double avgThirdRight, int cntRight, double avgZscoreThirdDim)
	{
		m_avgLeft = avgLeft;
		m_avgThirdLEft = avgThirdLEft;
		m_cntLEft= cntLEft;
		m_avgRight= avgRight;
		m_avgThirdRight = avgThirdRight;
		m_cntRight = cntRight;
		m_avgZscoreThirdDim = avgZscoreThirdDim;
	}
	*/

	cTableBucket()
	{
		m_value=0.0;
		m_virtualValue=0.0;
		m_avgOddFirst=0.0;
		m_avgOddSecond=0.0;
		m_cnt=0;
		m_percentageSample;
		m_firstDimLowZ=0.0;
		m_firstDimUpperZ=0.0;
		m_secondDimLowerZ=0.0;
		m_secondDimUpperZ=0.0;
		Clear();
	}


	void Clear()
	{
//		m_value=0.0;
	//	m_cnt=0;
		for(int i = 0 ; i < NUM_OF_PARAG_THIRD_DIM_BUCKETS ; i++)
		{
			m_thirdValArray[i]=0.0;
			m_thirdOddArray[i]=0.0;
			m_forthValArray[i]=0.0;
			m_forthOddArray[i]=0.0;
			m_thirdCntArray[i]=0;
			m_forthCntArray[i]=0;
		}
	}
		
	void AddPatientInfo( int thirdDimBucketIndex,double thirdDimOdd, int forthDimBucketIndex, 
															double forthDimOdd,double depVal)
	{
		m_thirdValArray[thirdDimBucketIndex] += depVal;
		m_thirdOddArray[thirdDimBucketIndex] += thirdDimOdd;
		m_thirdCntArray[thirdDimBucketIndex]++;
		m_forthValArray[forthDimBucketIndex] += depVal;
		m_forthOddArray[forthDimBucketIndex] += forthDimOdd;
		m_forthCntArray[forthDimBucketIndex]++;
	//	m_value += depVal;
	//	m_cnt++;
	}

	void SetBucketPatietnInfo()
	{
		if(m_cnt > 0)
		{
			//m_value /= m_cnt;
			for(int i = 0 ; i < NUM_OF_PARAG_THIRD_DIM_BUCKETS   ; i++)
			{
				if(m_thirdCntArray[i] > 0)
				{
					m_thirdValArray[i] /= m_thirdCntArray[i];
					m_thirdOddArray[i] /= m_thirdCntArray[i];
				}

				if(m_forthCntArray[i] > 0)
				{
					m_forthValArray[i] /= m_forthCntArray[i];
					m_forthOddArray[i] /= m_forthCntArray[i];
				}
			}
		
		}
	}


//5  5 23
	void CalcualteMeanVirtualProfile(bool* isIn, double* depArr, int numOffPatients);

	void CalcaulteThresholdsAndBycketsForThirdAndForthDimensions(bool* isIn, double* depLikeArr, 
		double* thirdDim, double* forthDim,    int numOffPatients, cGlobals* globals);
	












	

	bool AreIndexesMatch( double firstDim,  double secondDim)
	{
		if(   (firstDim >= 	m_firstDimLowZ  ) && 
						(firstDim < m_firstDimUpperZ) &&
					(secondDim   >= m_secondDimLowerZ ) &&
					(secondDim  < m_secondDimUpperZ ))
		{
			return true;
		}
		return false;
	}	
	 //5  5 23 see who calls this and do i need to add the virtual element too
	cTableBucket(double value, double avgOddFirst, double avgOddSecond,  int cnt,
		double firstDimLowZ, double firstDimUpperZ, double secondDimLowerZ, double secondDimUpperZ)
	{
		m_value = value;
		m_virtualValue=0.0;
		m_avgOddFirst = avgOddFirst;
		m_avgOddSecond = avgOddSecond;
		m_cnt = cnt;
		m_percentageSample = 0.0;
		m_firstDimLowZ= firstDimLowZ;
		m_firstDimUpperZ = firstDimUpperZ;
		m_secondDimLowerZ = secondDimLowerZ;
		m_secondDimUpperZ = secondDimUpperZ;
	///	m_avgThirdLEft=0.0;
	//	m_cntLEft=0;
	//	m_avgRight=0.0;
	//	m_cntRight=0;
	//	m_avgZscoreThirdDim=0.0;
	//	m_avgThirdRight=0.0; 
		
	}
	//m_avgOddFirst
	
	double GetAbsGapOfFirst( int &directionOfProfileGap, double first)
	{
		double ret = cVarianceCalc::Abs(first - m_avgOddFirst);
		directionOfProfileGap = 0;
		if( m_avgOddFirst > first )
		{
			directionOfProfileGap=1;
		}
		if( first > m_avgOddFirst  )
		{
			directionOfProfileGap = -1;
		}
		return ret;
	}

	/*	directionOfProfileGap=0;
		double gap  = 0.0;
		if(first < m_firstDimLowZ )
		{
			gap =  m_firstDimLowZ - first;
			directionOfProfileGap=1;
		}
		else if (first > m_firstDimUpperZ)
		{
			gap = first - m_firstDimUpperZ;
			directionOfProfileGap = -1;
		}
		return gap;
	}*/
	
	double GetAbsGapOfSecond(  int &directionOfProfileGap, double second)
	{
		double ret = cVarianceCalc::Abs(second - m_avgOddSecond);
		directionOfProfileGap = 0;
		if( m_avgOddSecond > second )
		{
			directionOfProfileGap=1;
		}
		if( second > m_avgOddSecond  )
		{
			directionOfProfileGap = -1;
		}
		return ret;
	}


	/*

		directionOfProfileGap=0;
		double gap  = 0.0;
		if(second < m_secondDimLowerZ )
		{
			gap =  m_secondDimLowerZ - second;
			directionOfProfileGap = 1;
		}
		else if (second > m_secondDimUpperZ)
		{
			gap = second - m_secondDimUpperZ;
			directionOfProfileGap=-1;
		}
		return gap;
	}*/

/*	//5  5 23 use virtual value and other for a new prediciton f ucntion
	bool GetPredictionNew(double &prediction,   int &predSample, double* thirdBucketArray , 
		double* thirdOddArray, 		int* thirdBcketSample, 
		double* forthBucketArry,  double* forthOddArray,
		int* forthBcketSample)//,  double thirdDim, double  forthDim)
	{
		prediction = m_value;
		//oddFirst = m_avgOddFirst;
		predSample = m_cnt;
		for(int i = 0 ; i < NUM_OF_PARAG_THIRD_DIM_BUCKETS ; i++)
		{
			thirdBucketArray[i] = m_thirdValArray[i];
			thirdOddArray[i] = m_thirdOddArray[i];
			thirdBcketSample[i] = m_thirdCntArray[i];
			forthBucketArry[i] = m_forthValArray[i];
			forthOddArray[i] = m_forthOddArray[i];
			forthBcketSample[i] = m_forthCntArray[i];
		}
		if(predSample >= 1)
		{
			return true;
		}
		return false;
	}
	*/
/*
	bool GetPrediction(double &prediction,  int &predSample, double &predictionWithThird, int &predWithThirdSample, double thirdDim)
	{  
		prediction = m_value;
		predSample = m_cnt;
		if(thirdDim > m_avgZscoreThirdDim)
		{
			predictionWithThird = m_avgRight;
			predWithThirdSample = m_cntRight;
		}
		else
		{
			predictionWithThird = m_avgLeft;
			predWithThirdSample = m_cntLEft;
		}
		if(predSample >= 1)
		{
			return true;
		}
		return false;
	}	
*/
 
};



class cParagraphPredModel
{
	int m_numOffPatients;
	double* m_firstDim;
	double* m_secondDim;
	double* m_thirdDim;
	double* m_forthDim;

	double** m_valTable;
	int** m_cntTable;
	double** m_firstOddTable;
	double** m_secondOddTable;
	int m_twoDimTableSize;

	cTableBucket** m_bucketArr;




	int m_queueSize ;
	double*  m_valArr;
	int* m_cntArr;
	double* m_firstDimLowerZ;
	double* m_firstDimUpperZ;
	double* m_secondDimLowerZ;
	double* m_secondDimUpperZ;





	int	m_valueIndex;

	double m_firsMeann ;
	double m_firstSDd;
	double m_secMeann ;
	double m_secSDd;
	double m_thiMeann;
	double m_thiSDd ;
	double m_forthMeann;
	double m_forthSDd ;

	char m_valueStr[100];
	double m_thirdThresArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double m_thirdValueArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	int m_thirdCntArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double m_forthThresArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double m_forthValueArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	int m_forthCntArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
 


	double* m_depLikeArr;



	double InternalPredictBasedOnBuckets(
		double* valBucketArr, double* oddBucketArr, int* sampleBucketArr, int numOfBuckets,
		int indexToPredict,double patientValue, double predAvg)
	{
		int sdg = 0 ;
		double patientValueMean = 0.0;
		double depvalueMean = 0.0;
		int cntSum = 0;
		for(int i = 0 ; i < numOfBuckets ; i++)
		{
			patientValueMean += oddBucketArr[i] * sampleBucketArr[i];
			depvalueMean += valBucketArr[i] *  sampleBucketArr[i];
			cntSum += sampleBucketArr[i];
		}
		if(cntSum>0)
		{
			patientValueMean /= cntSum;
			depvalueMean /=	cntSum;
		}

		double sumChangeInDepPerOdd = 0.0;
		double sumWghts = 0.0;
		int numOfPersonsPArticipateInModel = 0;
		int countOfOddBelowMean = 0;
		int countOfOddAboveMean = 0;
		for(int i = 0 ; i < numOfBuckets ; i++)
		{
//the stretch on the patients group away from the mean, iiin terms of odd values 
			double chageInOdd = (oddBucketArr[i] - patientValueMean);
			if(chageInOdd < 0.0)
			{
				countOfOddBelowMean += sampleBucketArr[i];
			}
			else
			{
				countOfOddAboveMean += sampleBucketArr[i];
			}
			double changeInDep =  (valBucketArr[i] - depvalueMean);
			double wgh = double(sampleBucketArr[i]);

			//double changeInDepPer
			if((chageInOdd != 0) &&(wgh >= 1.0))//wgh starts with sample of patients and less than 3 0 can get extrem scores
			{
				numOfPersonsPArticipateInModel += sampleBucketArr[i];
				double changeInDepPerOdd = changeInDep / chageInOdd;
				wgh *= (cVarianceCalc::Abs( chageInOdd ));//firther away from a mean patient odd gives more reason to a signicaint weight for the patetrn learning
				sumChangeInDepPerOdd += wgh * changeInDepPerOdd;
				sumWghts += wgh;
			}
		}
		if(sumWghts > 0.0)
		{
			sumChangeInDepPerOdd /= sumWghts;
		}
		double delta= (patientValue - patientValueMean) * sumChangeInDepPerOdd;
		double maxAbsEffect = 0.2;
		if(  delta  > maxAbsEffect )
		{
			delta = maxAbsEffect;
		}
		if(delta < (maxAbsEffect * (-1.0)) )
		{
			delta  = (maxAbsEffect * (-1.0));
		}
		double predictionOutput = depvalueMean + delta;
		predictionOutput = cVarianceCalc::Min(predictionOutput, 1.0);
		predictionOutput = cVarianceCalc::Max(predictionOutput, 0.0);

		//if(  cVarianceCalc::Abs(predictionOutput


		//see that the depValueMean is the same as the input average pre value that is sent in the funciton input
		//api, and  which is the prediction based on a profile with no loking at the effect off the third or forth
		//dimensions
		///try to find limits to how mjch 
		
		int minSample = 50;//4 27 23 150;//or gett an input
		double ret = predictionOutput;

		int sampleLowerCount = cVarianceCalc::Min(	 countOfOddBelowMean, countOfOddAboveMean );
	
		if(sampleLowerCount < minSample)
		{
			ret = (
				      (
			             	 (     sampleLowerCount                   *   predictionOutput  )    +
			             	 (    (minSample-sampleLowerCount)        *    depvalueMean      )
			          )
				        /           (minSample)
				  );
		}
		return ret;
	}




public:

	cParagraphPredModel()
	{
		m_numOffPatients=0;

		m_valTable=NULL;
		m_firstOddTable=NULL;
		m_secondOddTable=NULL;
		m_cntTable=NULL;
		m_twoDimTableSize=0;
		m_queueSize=0; ;
		m_valArr=NULL;
		m_cntArr=NULL;
		m_firstDimLowerZ=NULL;
		m_firstDimUpperZ=NULL;
		m_secondDimLowerZ=NULL;
		m_secondDimUpperZ=NULL;

		m_valueIndex=-1;
		m_valueStr[0]=0;
		m_bucketArr=NULL;
		m_depLikeArr=NULL;

		m_firsMeann = 0.0;
		m_firstSDd = 0.0;
		m_secMeann = 0.0 ;
		m_secSDd = 0.0;
		m_thiMeann = 0.0;
		m_thiSDd = 0.0;
		m_forthMeann = 0.0;
		m_forthSDd = 0.0;
	}

	void WriteReadObject(cArrayFlex* arrayFlex ,  cGlobals *globals)
	{
		bool isWrite = arrayFlex->GetIsWriteMode();
		char str[200];
		strcpy(str,"start - predictive model value string:");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayString(m_valueStr,isWrite,*globals);//m_valueStr is a m_valueStr[200] so no need for mem
	
		strcpy(str,"writing  number of profiles:");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayInt(m_queueSize,isWrite,*globals);
		if(!isWrite)
		{
			m_bucketArr = new cTableBucket*[m_queueSize];
			for(int i = 0 ; i < m_queueSize ; i++)
			{
				m_bucketArr[i] = new cTableBucket();
			}
		}
		for(int i = 0 ; i < m_queueSize ; i++)
		{
			strcpy(str,"profile start ");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
			m_bucketArr[i]->WriteReadObjectBucket( arrayFlex , globals);
			strcpy(str,"profile end ");
			arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		}
		
		strcpy(str,"threshdls and values for buckets gruops:");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		strcpy(str,"number of bucket gruops:");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		int numOfBuckets = NUM_OF_PARAG_THIRD_DIM_BUCKETS;
		arrayFlex->WriteReadArrayInt(numOfBuckets , isWrite,*globals);
		for(int ii = 0 ; ii < numOfBuckets; ii++)
		{
			arrayFlex->WriteReadArrayDouble(m_thirdThresArr[ii] , isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_thirdValueArr[ii] , isWrite,*globals);
			arrayFlex->WriteReadArrayInt(m_thirdCntArr[ii] , isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_forthThresArr[ii] , isWrite,*globals);
			arrayFlex->WriteReadArrayDouble(m_forthValueArr[ii] , isWrite,*globals);
			arrayFlex->WriteReadArrayInt(m_forthCntArr[ii] , isWrite,*globals);
		}

		strcpy(str,"end  - ");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
	
	}





	cParagraphPredModel(int numberOfPatients , cPatientMapElements** patientMapArray   , 
		int valueIndex, char* valueStr,  cGlobals* global);

	void BuildTwoDimTables(int size);

	
	int GetBucketIndex(int ptIndex);

	cTableBucket** GetTableBucket()  //GetNumberOfBuckets
	{
		return m_bucketArr;
	}

	int GetNumberOfBuckets()
	{
		return m_queueSize;
	}

	
	bool AdjustPerSamle(double &adjusted, int dimI, int dimII);


	/*void SetTables(double** valTable, int** cntTable, int size)
	{
		m_valTable = valTable;
		m_cntTable = cntTable;
		m_twoDimTableSize = size;
	}*/

/*	void SortFromSmallToLargeValue()
	{
	
	}
	*/

	void FillInCirclePerInputSize(bool* isIn, double sensitivityForFirst , double sensitivityForSecond,
		   int minProfileSize, int profileBucketIndex)
	{
		double thisProfileFirstOdd = m_bucketArr[profileBucketIndex]->m_avgOddFirst;
		double thisProifleSecondOdd = m_bucketArr[profileBucketIndex]->m_avgOddSecond;
		double* editDisArr = new double[m_numOffPatients];
		for(int i = 0 ; i < m_numOffPatients ; i++)
		{
			double gapInFirstOdd = m_firstDim[i] - thisProfileFirstOdd;
			double gapConvertedToDepValFirst = gapInFirstOdd * sensitivityForFirst;
			double gapInSecondOdd = m_secondDim[i] - thisProifleSecondOdd;
			double gapConvetedToDepValSecond = gapInSecondOdd * sensitivityForSecond;
			double distance = gapConvertedToDepValFirst + gapConvetedToDepValSecond;
			double absDistance = cVarianceCalc::Abs(distance) + cVarianceCalc::Abs(gapConvertedToDepValFirst) +  cVarianceCalc::Abs(gapConvetedToDepValSecond);
			editDisArr[i] = absDistance;
		}
		cVarianceCalc::FillArrWithLowestValue(isIn, editDisArr, m_numOffPatients,minProfileSize);
		delete []editDisArr;
		editDisArr = NULL;
	}
		


	static void GetGroupWithMinSizeAndOddCenter(bool* isIn, int &cnt, double* dimArr,  int numOffPatients,
			double lower, double upper, int recomednedCount)
	{
		cnt =0;
		for(int i = 0 ; i < numOffPatients ; i++)
		{
			isIn[i] = false;
			if((dimArr[i] >= lower ) && (dimArr[i] < upper ))
			{
				isIn[i] = true;
				cnt++;
			}
		}
		if(cnt < 1000)
		{
			
			double gap  = upper - lower;
			lower -= (gap / 2.0);
			lower  = cVarianceCalc::Max(lower , 0.0);
			upper += (gap / 2.0);
			cnt = 0;
			for(int i = 0 ; i < numOffPatients ; i++)
			{
				isIn[i] = false;
				if((dimArr[i] >= lower ) && (dimArr[i] < upper ))
				{
					isIn[i] = true;
					cnt++;
				}
			}
		}
	}
	
//sensitiviy meand how much (directional) change in dep ratio for a positive change of 1.0 Symetric first dim odd
	double CreateSensitivityMeassureDimFirst(int i,cGlobals* globals); 
//keep first  sim stady and play with second
	double CreateSensitivityMeassureFirstDimSecond(int i , cGlobals* globals);

	//4 11 23
	//open a new member with z score for thir dimention, find one cut middle and provide two scores per bucket and not one
	void CreateSubBucketAnaysis( cGlobals* globals );
	/*
	void AddInternalMOdel  (int bucketIndex, cPatientMapElements** patientMapArray,	int numberOfPatients )//, 		int valueIndex, char* valueStringg)
	{
		double avgZscoreThirdDim = 0.0;
		double avgScoreForthDim=0.0;
		int numOfPatientsThisBucket = 0;
		for(int i = 0 ; i < numberOfPatients;i++)
		{
			if( GetBucketIndex(i) == bucketIndex)
			{
			//	double zThird = //(	patientMapArray[i]->m_highestOddSumInThisValContextArr[valueIndex]  - 
			//		(m_thirdDim[i] - m_thiMean) / m_thiSD;
				avgZscoreThirdDim += m_thirdDim[i];
				avgScoreForthDim += m_forthDim[i];
				numOfPatientsThisBucket++;
			}
		
		}
		if(numOfPatientsThisBucket>0)
		{
			avgZscoreThirdDim /= numOfPatientsThisBucket;
			avgScoreForthDim /= numOfPatientsThisBucket;
		}
		double avgLeft = 0.0;
		double avgThirdLEft=0.0;
		int cntLeft= 0;
		double avgRight = 0.0;
		double avgThirdRight = 0.0;
		int cntRight = 0;
		for(int i = 0 ; i < numberOfPatients;i++)
		{
			if(	GetBucketIndex(i) == bucketIndex)
			{
			//	double zThird = //(	patientMapArray[i]->m_highestOddSumInThisValContextArr[valueIndex]  - 
			//		(m_thirdDim[i] - m_thiMean) / m_thiSD;
				if(m_thirdDim[i] > avgZscoreThirdDim)
				{
					avgRight += m_depLikeArr[i];
					avgThirdRight += m_thirdDim[i];
					cntRight++;
				}
				else
				{
					avgLeft += m_depLikeArr[i];
					avgThirdLEft += m_thirdDim[i];
					cntLeft++;
				}
			}
		}
		if(cntRight>0)
		{
			avgRight /= cntRight;
			avgThirdRight  /= cntRight;
		}
		if(cntLeft > 0)
		{
			avgLeft /= cntLeft;
			avgThirdLEft /= cntLeft;
		}
		if(false)//  (cntRight + cntLeft) > 0  )
		{
			double avgAll = (avgRight*cntRight +  avgLeft * cntLeft) / (cntRight + cntLeft);
			if(avgAll > 0)
			{
				double multi = m_bucketArr[bucketIndex]->m_value / avgAll;
				avgRight *= multi;
				avgLeft *= multi;
				avgRight = cVarianceCalc::Min(avgRight , 1.0);
			}
		}

		m_bucketArr[bucketIndex]->SetInternalValues(
			avgLeft,avgThirdLEft, cntLeft, avgRight,avgThirdRight, cntRight, avgZscoreThirdDim);


	
	}
	*/

	//4 21 23
	//clearn, 
	//add patinet info, 
	//remove first and second dims from third and forth calcuation 
	void AddInternalMOdelNew  (int bucketIndex );


	void ConvertToQueue()
	{
		m_queueSize = m_twoDimTableSize * m_twoDimTableSize;
		m_valArr = new double[m_queueSize];
		m_cntArr = new int[m_queueSize];
		m_firstDimLowerZ=new double[m_queueSize];
		m_firstDimUpperZ=new double[m_queueSize];
		m_secondDimLowerZ=new double[m_queueSize];
		m_secondDimUpperZ=new double[m_queueSize];


		double* firstOdd =new double[m_queueSize];
		double* secondOdd =new double[m_queueSize];

		m_bucketArr = new cTableBucket*[m_queueSize];
		int movingIndex = 0;
		for(int i = 0 ; i < m_twoDimTableSize ; i++)
		{
			for(int ii = 0 ; ii < m_twoDimTableSize ; ii++)
			{
				m_valArr[movingIndex] = m_valTable[i][ii];
				m_cntArr[movingIndex] = m_cntTable[i][ii];
				firstOdd[movingIndex] = m_firstOddTable[i][ii];
				secondOdd[movingIndex] = m_secondOddTable[i][ii];
				LowerUper24mode( m_firstDimLowerZ[movingIndex] ,  m_firstDimUpperZ[movingIndex], i);
			//	m_firstDimLowerZ[movingIndex]  = Lower(i);
			//	m_firstDimUpperZ[movingIndex] = Upper(i);
				LowerUper24mode( m_secondDimLowerZ[movingIndex]  , m_secondDimUpperZ[movingIndex] , ii);
			//	m_secondDimLowerZ[movingIndex] = Lower(ii);
			//	m_secondDimUpperZ[movingIndex] = Upper(ii);

				m_bucketArr[movingIndex] =  new cTableBucket(m_valArr[movingIndex], 
					firstOdd[movingIndex], secondOdd[movingIndex],
					m_cntArr[movingIndex], 
					m_firstDimLowerZ[movingIndex], m_firstDimUpperZ[movingIndex], m_secondDimLowerZ[movingIndex] , m_secondDimUpperZ[movingIndex]);
				movingIndex++;
			}
		}
	
	//	for(int i = 0 ; i < movingIndex ; i++)
	//	{
	//		if(m_bucketArr[i]->m_cnt  > 0)
	//		{
	//			m_bucketArr[i]->m_value  /= m_bucketArr[i]->m_cnt ;
	//		}
	//	}
		int newMovingIndex = 0;
		for(int i = 0 ; i < movingIndex ; i++)
		{
			if(m_bucketArr[i]->m_cnt  > 0)
			{
				m_bucketArr[newMovingIndex++] = m_bucketArr[i];
			}
			else
			{
				delete m_bucketArr[i];
				m_bucketArr[i]=NULL;
			}
		}
		m_queueSize = newMovingIndex;
		for(int i = 0 ; i < newMovingIndex ; i++)
		{
			double lowest = 100000.0;
			int lowestIndex = i;
			for(int ii = i ; ii < newMovingIndex ; ii++)
			{
				if(m_bucketArr[ii]->m_cnt < lowest)//m_queueSize
				{
					lowest = m_bucketArr[ii]->m_cnt;//4 26 23
						//m_bucketArr[ii]->m_value;
					lowestIndex  = ii;
				}
			}
			cTableBucket* temp = m_bucketArr[i];
			m_bucketArr[i] = m_bucketArr[lowestIndex];
			m_bucketArr[lowestIndex] = temp;				
		}
		double allSampleWght = 0.0;
		for(int i = 0 ; i < m_queueSize ; i++)
		{
			allSampleWght += (double)( m_bucketArr[i]->m_cnt);
		}
		for(int i = 0 ; i < m_queueSize ; i++)
		{
			int cntt =  m_bucketArr[i]->m_cnt;
			double wgh = (double(cntt) ) / allSampleWght;
			m_bucketArr[i]->m_percentageSample = wgh;
		}

		delete []	firstOdd;
		delete [] secondOdd ;


		//SortFromSmallToLargeValue();

	}


int GetClosestProfile(double* scoreArr, int size, bool* isTaken)
{
	double min = 1000.0;
	int index = -1;
	for(int i = 0 ; i < size ; i++)
	{
		if(!isTaken[i])
		{
			if(  scoreArr[i]  < min)
			{
				min = scoreArr[i];
				index = i;
			}
		}
	}
	return index;
}

bool IsOnSameSide(double val1, double  val2 , double target)
{
	if(val1 >= target && val2 >= target )
	{
		return true;
	}
	if(val1 <= target && val2 <= target )
	{
		return true;
	}
	return false;
}



bool FindScoreAndThenPredictionThreeDimensions(double &predOut, double firstDim,  
	double secondDim, double thirdDim,  double forthDim, cStringHistogram* globalHistogram, int valueIndex , cGlobals* globals);

double  GetPenaltyInGapFirst(double gapFirst,double  firstDim);
double GetPenaltyInGapSecond(double gapSecond,  double  secondDim);


	bool FindScoreAndThenPrediction(double &pred, double firstDim,   double secondDim)
	{
		//double zFirst = ( firstDim -  m_firsMean ) / m_firstSD;
		//double zSecond = (secondDim - m_secMean ) / 	m_secSD;

		int x =  GetTableDims24(firstDim , m_twoDimTableSize );
		int y = GetTableDims24(secondDim , m_twoDimTableSize );

		if(m_cntTable[x][y] > 0)
		{
			pred = m_valTable[x][y];
			return true;
		}
		else
		{
			pred = 0.0; 
			return false;
		}
	}

	
void	LowerUper24mode( double &lower,  double &upper, int index)
{
	if(index == 0)
	{
		lower = 0.0;;// -100;
		upper = 0.2;//-2.5;
	}
	if(index == 1)
	{
		lower = 0.2;// -2.5;
		upper = 0.4;// -2.0;
	}
	if(index == 2)
	{
		lower = 0.4;//-2.0;
		upper = 0.6;//-1.5;
	}
	if(index == 3)
	{
		lower = 0.6;// -1.5;
		upper = 0.8;//-1.25;
	}
	if(index == 4)
	{
		lower = 0.8;// -1.25;
		upper = 1.0;//-1.0;
	}
	if(index == 5)
	{
		lower =1.0;// -1.0;
		upper = 1.1;//-0.5;
	}
	if(index == 6)
	{
		lower = 1.1;//-0.5;
		upper = 1.2;//-0.25;
	}
	if(index == 7)
	{
		lower = 1.2;//-0.25;
		upper = 1.35;//0.00;
	}
	if(index == 8)
	{
		lower = 1.35;//0.0;
		upper = 1.5;//0.2;
	}
	if(index == 9)
	{
		lower = 1.5;//0.2;
		upper = 1.7;//0.4;
	}
	if(index == 10)
	{
		lower = 1.7;//0.4;
		upper = 1.9;//0.6;
	}
	if(index == 11)
	{
		lower = 1.9;//0.6;
		upper = 2.2;//0.8;
	}
	if(index == 12)
	{
		lower = 2.2;//0.8;
		upper = 2.6;//1.0;
	}
	if(index == 13)
	{
		lower = 2.6;
		upper = 3.0;//;
	}
	if(index == 14)
	{
		lower = 3.0;
		upper = 3.7;
	}
	if(index == 15)
	{
		lower = 3.7;
		upper = 4.5;
	}
	if(index == 16)
	{
		lower = 4.5;
		upper = 5.3;
	}
	if(index == 17)
	{
		lower = 5.3;
		upper = 6.0;
	}
	if(index == 18)
	{
		lower = 6.0;
		upper = 7.5;
	}
	if(index == 19)
	{
		lower = 7.5;
		upper = 8.8;
	}
	if(index == 20)
	{
		lower = 8.8;
		upper = 10.0;
	}
	if(index == 21)
	{
		lower = 10.0;
		upper = 12.0;
	}
	if(index == 22)
	{
		lower = 12.0;
		upper = 15.0;
	}
	if(index == 23)
	{
		lower = 15.0;
		upper = 100.0;
	}
}

/*
double	Lower( int index)
{
	if(index == 0)
	{
		return -100.0;//basically any number
	}
	if(index == 1)
	{
		return  -2.5;
	}
	if(index == 2)
	{
		return  -2.0;
	}
	if(index == 3)
	{
		return  -1.5;
	}
	if(index == 4)
	{
		return  -1.0;
	}
	if(index == 5)
	{
		return  -0.5;
	}
	if(index == 6)
	{
		return  -0.2;
	}
	if(index == 7)
	{
		return  0.2;
	}
	if(index == 8)
	{
		return  0.5;
	}
	if(index == 9)
	{
		return  1.0;
	}
	if(index == 10)
	{
		return  1.5;
	}
	if(index == 11)
	{
		return  2.0;
	}
}
double Upper( int index)
{
	if(index == 0)
	{
		return -2.5;
	}
	if(index == 1)
	{
		return  -2.0;
	}
	if(index == 2)
	{
		return  -1.5;
	}
	if(index == 3)
	{
		return  -1.0;
	}
	if(index == 4)
	{
		return  -0.5;
	}
	if(index == 5)
	{
		return  -0.2;
	}
	if(index == 6)
	{
		return  0.2;
	}
	if(index == 7)
	{
		return  0.5;
	}
	if(index == 8)
	{
		return  1.0;//
	}
	if(index == 9)
	{
		return  1.5; 
	}
	if(index == 10)
	{
		return  2.0; 
	}
	if(index == 11)
	{
		return 100;//basically any high pos number
	}
	
}
*/
/*
	//3 3 23 *** replace with objet that has threshld of lower and higher bar as part of the multiple profiles
int GetTableDims12(double zVal, int size )
{
	for(int i = 0 ; i < size ; i++)
	{
		if(  (zVal > Lower(i)) && (zVal <= Upper(i)))
		{
			return i;
		}
	}

}*/
	
	//3 3 23 *** replace with objet that has threshld of lower and higher bar as part of the multiple profiles
int GetTableDims24(double zVal, int size )
{
	for(int i = 0 ; i < size ; i++)
	{
		double l =0.0;
		double u=0.0;
		LowerUper24mode( l,  u , i);
		if(  (zVal >= l) && (zVal < u))
		{
			return i;
		}
	}
	return -1;

}
	


	double CalculateStretch()
	{
		double avg=0.0;
		int cnt = 0;
		for(int i = 0 ; i < m_twoDimTableSize ; i++)
		{
			for(int ii = 0 ; ii < m_twoDimTableSize ; ii++)
			{
				avg += m_valTable[i][ii]    * m_cntTable[i][ii];
				cnt += m_cntTable[i][ii];
			}		
		}
		if(cnt > 0)
		{
			avg /= cnt;
		}
		double stretch = 0.0;
		for(int i = 0 ; i < m_twoDimTableSize ; i++)
		{
			for(int ii = 0 ; ii < m_twoDimTableSize ; ii++)
			{
				stretch += (m_valTable[i][ii] - avg  ) * (m_valTable[i][ii] - avg  )*  m_cntTable[i][ii];
			}		
		}
		stretch /= cnt;
		stretch = pow(stretch , 0.5);
	 
		return stretch;
	 }




};
 

class cParagraphAnalytics
{
	char m_filePath[MAX_STRING_LENGTH];
	int m_numOfVars;
	int m_valueFieldIndex;


	char** m_paragrArray ;//= new char*[maxNumberOfParagraphs];
	char** m_valueArray;// = new char*[maxNumberOfParagraphs];
	char** m_ptIDarray;
	int m_numberOfParagraphs;

	cPatientRecordObject** m_patientRecorsObjectList;
	int m_maxNumberOfPatients;
	int	m_actualyNumberOfPatients;
	
	cParagraphPredModel** m_paragPRedMode;

	static void BuildPatientRecordObjects(int &maxNumberOfPatients,cPatientRecordObject**& patientRecorsObjectList,
	int &actualyNumberOfPatients,   int numberOfParagraphs, char** ptIDarray,   char** paragraphValueArray, char** paragrArray);
	
	static void  ExtractPatientIDstring(char* patientIDstr, char* inputStr);

	static bool IsExsisting(int &indexExsist, char* ptIDstr,cPatientRecordObject** patientRecorsObjectList, int actualyNumberOfPatients)
	{
		indexExsist = -1;
		for(int i = 0 ; i < actualyNumberOfPatients ; i++)
		{
			if(patientRecorsObjectList[i]->IsPatientID(ptIDstr))
			{
				indexExsist = i;
				return true;
			}
		}
		return false;
	}

	static int GetExsistingOrOpenNewPatientObject(cPatientRecordObject** patientRecorsObjectList, int &actualyNumberOfPatients,
		char* ptIDstr)
	{
		int indexExsist=-1;
		//nt &indexExsist, char* ptIDstr,cPatientRecordObject** patientRecorsObjectList, int actualyNumberOfPatients
		bool isFound = IsExsisting(indexExsist,  ptIDstr,patientRecorsObjectList,actualyNumberOfPatients);
		if(!isFound )
		{
			cPatientRecordObject* temp = new cPatientRecordObject(ptIDstr);
			patientRecorsObjectList[actualyNumberOfPatients] = temp;
			indexExsist = actualyNumberOfPatients;
			actualyNumberOfPatients++;
		}
		else
		{
			int sdg = 0;
		}
		return indexExsist;
	}

	static bool IsOneStringsSubSetOfTheOther(char* str1, char* str2)
	{
		 if(
			 IsLeftStrSubStringOfRightStr( str1, str2)||
			 (IsLeftStrSubStringOfRightStr( str2, str1)))
		 {
			return true;
		 }
		 return false;

	}



	static void BreakPhrase(char* left, char* right,  char* str)
	{
		left[0]=right[0]=0;
		int len = strlen(str);
		int movingIndex=0;
		bool isEndOfLeft = false;
		int rightStrStartPos =0;
		for(int i = 0 ; i < len && (!isEndOfLeft ) ; i++)
		{
			if(str[i] == '~')
			{
				if(i > 2)
				{
					isEndOfLeft = true; 
					rightStrStartPos = 1+1;
				}
			}
			else
			{
				char ch = str[i];
				if(IsLetter(ch))
				{
					ch = LowerLetter(ch);
				}
				if(ch != ' ')
				{
					left[movingIndex++] = ch;
				}
			}
		}
		left[movingIndex]=0;

		if(rightStrStartPos > 2)
		{
			int movingIndexRight = 0;
			for(int ii = rightStrStartPos ; ii < len ; ii++)
			{
				if(str[ii] != '~')
				{
					right[movingIndexRight++]= str[ii];
				}
			}
			right[movingIndexRight]=0;
		}
	
	}



//cParagraphAnalytics::

	static bool AreSimilarPhrases(
		int &potentialUpgradePos,		char* str1, char* str2, int sample1, int sample2, 
		int pos1,	int pos2, double odd1, double odd2 , cGlobals* globals);




public:
	cParagraphAnalytics(char* inputFilePath, int numOfVariables, int valueFFieldIndex);

	~cParagraphAnalytics();

	cParagraphPredModel** GetParagraPredMOdel()
	{
		return m_paragPRedMode;
	}

	
	static void FillAllStringsOnePatientOneParag(	cPhraseHash* onePatientHash, cPhraseHash* dictionaryHash, 
	  char** paragrArray, int pargIndex, char* valStr , 
	  bool isGettingFinalHashFilled, cGlobals* globals, int levelOfShadow);


	static void CollectAllParagraphs(char**  paragrArray, char** valueArray, char** m_ptIDarray,int &numOfParaghs ,
		ifstream* inFile, char endOfParagInSign, char delimiter,
	bool isRemoveSpaces		);

//	void GetRelevantPredictionAndDependent(double &pred, double &dep,char* valStrThisPatient, char* valStrOfModel,
	//				patientMapObj->m_valueStr,	globalHistogram->GetValueArr(ii), predArr , strValueArr, numOfValues);
		
	double GetRelevantPrediction(	char* valStr, double* predArr , char** strValueArr, int numOfValues);
	void WriteOrReadToDiscPAragraphModel( cArrayFlex* arrayFlex, 	cParagraphPredModel**& paragPRedModel , 
		int &numOfValues, cGlobals *globals);

	bool AnalyticsProcess(	cGlobals *globals);
		//char* outFile, char endOfParagInSign,  char endOfPAragOutSignn, 	char delimiter, bool isRemoveSpaces);
	bool ParagraphPredict( cPhraseHash* finalHash, cGlobals *globals, cStringHistogram* globalHistogram);
	void WriteParagraoPredOneBcket(cTableBucket* bucket,  ofstream* outFile  , cGlobals* globals   );
	void WritePredElements(double* predArr, double* refPRedArr  , char** strValueArr,
		cHashObj** hashObjOut,  cHashObj** manualObjOut , double* oddRatioArr,
		int numOfValues,	ofstream* outFile , cGlobals* globals , double*  highestOddRAtioArr, int numberOfParagraphs );

	static bool IsStringgNegative(char* str);
	static void FillIsNegativeStrings(bool* isNegativeArr, char** stss, int numOfStrs);

	void CollectResultsAndPrint(
		double*& predArr,	double*& referanceDistriArr,	char**& strValueArr,	int &numOfValues,		
				double &highestOddRAtio, char** paragrArray , int  numOfParags,
	cPhraseHash* finalHash, cGlobals* globals, cStringHistogram* globalHistogram, char*  queryInFilePath, double* highestOddRAtioArr);

	
//	void CreateParagPredModel(cParagraphPredModel *&paragPRedModel,  cPatientMapElements** patientMapArray,	
	//	int numberOfPatients , 					int valueIndex, char* valueStringg);
	
	static bool BuildArraysOfParagaphsValueAndPtID(
			char**& paragrArray , char**& valueArr, char**& ptIDarray ,int &numOfParags,
			char endOfParagInSign , char delimiter,  bool isRemoveSpaces, 
			char* filePath);
	
	static void BuildPatientsPhraseMap(cHashObj **&phraseObjArray, int &numOfPhraseHashObjects,
	cPhraseHash* phraseHash , cStringHistogram*  globalHistogram, char** paragArray , int numOfParags,  char* valueStr, 
	cPhraseHash* onePAtinetHash,  cGlobals* globals, int levelOfShadow);
	
	static void RemoveSubSetPhrases(cHashObj** phraseObjArray , int numOfPhraseHashObjects);

//	double* lineArrr , double* strlenArr, cHashObjectArray &hashArr,
//	int &actualyLineIndexx , int pushMode , char endOfParagInSign , char delimiter,  bool isRemoveSpaces);
	
	void MergeHash(cPhraseHash* allPatientsHash, cPhraseHash* onePatientHash);

	void PredictParagraphResult(double*& predArr,  double*& referanceDistriArr,
		char**& strValueArr , cHashObj**& hashObjOut,  cHashObj**& manualObjOut, double*& oddRatio,	int &numOfValues,
		char** listOfParagraphOfOnePatient, int numberOFPAragraphs,
	    cPhraseHash* finalPhraseHash, cGlobals* globals,  cStringHistogram* globalHistrogram);

	static void CalculateSumOfOddThirdOrForthDimensions(double &maxSymetricValue ,int &maxIndex, int &potentialUpgradePos,
		double &sumSymOdds, double* oddArray, int* sampleArr,  
		int size , cHashObj** hashObjArr, cGlobals* globals);



	static void CollectPatientProfileParagraphs(
		cPatientMapElements* patientMapArray,
				char**	listOfParagraphOfOnePatient , int numberOFPAragraphs, 
		cPhraseHash* finalPhraseHash, cStringHistogram* globalHistogram, char* valStr  , cPhraseHash* onePAtinetHash   , 
		cPhraseHash* finalHash,  cGlobals* globals, int levelOfShadow);

	static bool IsEligibleAsIngridient(double odd, int sample, cHashObj** obj, int index, int size);
	
	static void Shadow(char* shadowStr, char* str);
	
	static double CalculateAverageOddForAtLEastInputSamlpleNew( int &indexOfMatchedObject, int &actualUsedSample, 
		cHashObj*& outMatchedObj,cHashObj*&  outManualHashObj,
		int*	oddSampleArray, 		double* oddArray, cHashObj** hashObjArr, 
		int size  , cGlobals *globals,int maxCombinedObjects,  cPhraseHash* finalHash, char* valStrr ,
		cStringHistogram* globalHistogram);
	

	static double CalculateAverageOddForAtLEastInputSamlple(int &actualUsedSample, int*	posOddSampleArray, double* posOddArray, 
	   cHashObj** hashObjArr,int size , cGlobals *globals);//,globals->g_minSampleSizeWhole;);
	


	static void GetObjectWithHighestOddForInputStr(
		cHashObj *&highestOddObjThisVal, double &highesstOddThisVal,cHashObj *&highestOddObjOtherVall, double &highesstOddOtherVall, bool* isTaken,
			char* valStr, cHashObj** phraseObjArray, int numOfPhraseHashObjects, cStringHistogram* globalHistogram, 
			cPhraseHash* finalHash , cGlobals* globals  , int minSampleSizeForGetingInclded,
			bool isOnlyHigherLevelShadow, bool isOnlyNamualRules);//globals->g_minSampleSizeIngridient));
		
	static void GetObjectWithHighestOddForAnyOtherValThanInputStr(
		cHashObj *&highestOddObjAnyOtherVal, double &highesstOddAnyOtherVal,
		char* valStr,cHashObj** phraseObjArray, int numOfPhraseHashObjects, cStringHistogram* globalHistogram);

	static void GetTopNobjectsWithHighestOddToAnyValue(cHashObj** topObjs, double* oddArr, 
		int &actualyTopObjNumber, int maxNumOfTopObjs,
		cHashObj** phraseObjArray, int numOfPhraseHashObjects, cStringHistogram* globalHistogram);
	
static double GetSumOfTopOddRatioObjects( cPatientMapElements* patientMapArray );

 

void CreateParagPredModel(     cPatientMapElements** patientMapArray,	 
	int numberOfPatients , int valueIndex , char* valueString,  cGlobals* globals );
	

 


	static double Symetric(double s)
	{
		if(s< 1.0)
		{
			s = 1.0 / s;
			s -= 1.0;
			s = -1 * s;
		}
		else
		{
			s -= 1.0;
		}
		return s;
	}
	
	static void FillAllStringsOnePatient(cPhraseHash* onePatientHash, cPhraseHash* dictionaryHash, char** paragrArray,
		cPatientRecordObject* ptRecord, bool isGettingFinalHashFilled, cGlobals* globals, int levelOfShadow );//, cPhraseHash* allPatientsHash);
		      //        m_patientRecorsObjectList[ptIndex];
		//int ptIndex );
	
	static void FindPotenetialPairedShadowed(int*& pairedOptionSet, int &numOfPairdOptions, int* shadowedStartPos, int* shadowedStrLen,
		int subectPhraseIndex,  int shadowStringsLength);
		
	static void	CreateComplexShadow(char* complexShadowOut, char* subjectShadowed,  char* shadowedElement   );
					

	
int BuildPhraseDictionaryNew(cPhraseHash* outHash , cPhraseHash* dictionHash ,	 bool* isPatientIn,	
	    cStringHistogram*  globalHistogram, cGlobals* globals ,  int levelOfShadow);

	bool BuildPhraseDictionary(cPhraseHash* finalPhraseHash ,
	//	double* lineArrr , double* strlenArr, cHashObjectArray &hashArr,
	//	int &actualyLineIndexx , int pushMode , char endOfParagInSign ,
		//char delimiter, 
		//bool isRemoveSpaces,  
		cStringHistogram*  globalHistogram, cGlobals* globals);

	
	
	bool GoOverHashArrAndAct(double* lineArr , double* strlenArr, cHashObjectArray &hashArr, int &actualyLineIndex , int  pushMode ,
		char endOfParagInSign, char dellimiter, bool isRemoveSpaces );
	
	static void CalculateMultipleSubStrings(char**& stss, int*& posStartArr, int*& lenArr, int &numOfSubStrs, char* oneLine,  cGlobals* globals);
		
	bool ExtractDictionaryValueFromLine( char &value,   char* oneLine  , char delimiter , bool isRemoveSpaces);

	
	static bool   ExtractDictionaryValueFromThreeFieldsLineNEW(   	char*& paragrStr, char*& valueString, char*& ptIDstr,  char* oneLine, char delimiter, bool isRemoveSpaces);


	bool ExtractDictionaryValueFromThreeFieldsLine(int &patinetID, char &value,   char* oneLine, char delimiter, bool isRemoveSpaces);

	static void StandartizationRemoveSpacecs(char* oneLine, int &newOneLineLenth , char delimiter, bool isRemoveSpaces);

	static void MultiStringManipulation(char** stss, int* posStartArr, int &numOfSubStrs,  char* oneLine, int len, int maxSubStrSize);

	static void CollectNextFirstChar(bool &isFound, bool &isEnd, int &movingIndexFirstChar,  char* line, int len);

	static void CollectNextLastChar(bool &isFound, bool &isEnd, int &movingIndexFirstChar, int &movingIndexLastChar, int maxSize, char* line, int len);

	static bool IsLeftInputStrIsAsubSetOfRightInputStr ( char* leftStr  , char* rightStr);

	static bool IsExactCharectersArray(char* arr1,  char* arr2, int num );


	static bool AreTwoStringsMutuallyExclusive(char* str1, char* str2);
	
	static bool IsLeftStrSubStringOfRightStr( char* lStr, char* rStr);
	
	static bool IsLeftStrOverlapRightStrFromLeftSide(char* strL, char *strR);

	static bool IsLeftStrOverlapRightStrFromRightSide(char* strL, char *strR);


	int FindSamppleSizeOfMutualuExclusiveStrGrpForInputCore( 
		bool* isInCollectedChldrenList,  cHashStrChainObj**	sigHashChainObjs, int	coreIndex, int numOfObjects,cGlobals* globals);
	
	void CollectPotentialChildStringList(bool* isInCollectedChldrenList, int &numColleted, 
		char* strI, char patternI, int cntI, double perfOfPatternI,cHashStrChainObj** sigHashChainObjs,
		int numOfObjects, int startIndexToTry,  bool* isAnOption,cHistogram* globalHist);

	void FindGrandChildrenList(bool* isGgranChild, int &numColleted,
			char* strI, char patternI, int cntI, double perfOfPatternI,	cHashStrChainObj**	sigHashChainObjs, 
			int numOfObjects, bool* isInCollectedChldrenList, cGlobals* globals);

	int CalculatehighestSumOfMutuallyExclusiceObjectsSample(bool* isInCollectedChldrenList ,
														cHashStrChainObj**	sigHashChainObjs, int numOfObjects,cGlobals* globals);
	
	bool WriteStringsToOutFile(char* outFile, cHashStrChainObj** sigHashChainObjs, int numOfObjects ,
		char endOfPAragOutSignn, 	char delimiter, cGlobals* globals);

	void SortChainLinkObjectsByShorterStringsFirst( cHashStrChainObj** sigHashChainObjs, int numOfObjects);
	
	static bool   IsSign(char ch) 
	{
		if( ch == '!' || ch == '~' || ch == '@'|| ch == '#'|| ch == ':'|| ch == '.'|| ch == ','|| ch == '(' || ch == ')' || ch == '%' || ch == '*'|| ch == '?'|| ch == '<'|| ch == '>')
		{
			return true;
		}
		return false;
	}	
	static bool	  IsLetter(char ch)
	{
		if(  (ch >= 'a' && ch <= 'z' )  ||(ch >= 'A' && ch <= 'Z' ) )
		{
			return true;
		}
		return false;
	}
	static char LowerLetter(char ch)
	{
		if( (ch >= 'a') &&( ch <= 'z') )
		{
			return ch;
		}
		else if (ch >= 'A' && ch <= 'Z' )
		{
			char gap  = 'a' - 'A';//if ch is cAPITAL letter than to shift fro an A to an a can be added to a so a + a - A . ir any letter
			char x = ch + gap;//x is any letter with the lower case value of the ch capital version
			return x;//retrn the lower case version of ch
		}
		return ch;//error
	}

	static bool IsDigit(char ch)
	{
		if(ch >= '0' && ch <='9')
		{
			return true;
		}
		return false;
	}
	static bool IsValidAsFirstChar(char ch)
	{
		if( IsSign(ch) || IsLetter(ch) || IsDigit(ch))
		{
			return true;
		}
		return false;
	}

};
		 
 

#endif