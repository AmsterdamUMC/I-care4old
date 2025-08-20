//#include "cSimilarityFormula.h"
//#include "cProfileTarget.h"
#include "TargetSort.h"

#include <math.h>
#include "math.h"
#include <string.h>
#include <stdlib.h>


		
#include <iostream>

#include "cSimilarityFormula.h"
#include "cProfileTarget.h"
//#include "TargetSort.h"
/*
#include <string.h>
#include <stdlib.h>


		
#include <iostream>
*/
   
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::cout;
using std::endl;


using namespace std;



	cArrayFlex::cArrayFlex(char* filePath, bool isWriteMode)
	{
		m_arr=NULL;
		m_size=0;
		m_readMovingIndex=0;
		m_filePAth[0]=0;
		m_outfilePtr=NULL;
		m_infilePtr = NULL;
		if(filePath != NULL)
		{
			strcpy_s(m_filePAth , filePath);
			if(isWriteMode)
			{
				m_outfilePtr = new ofstream(m_filePAth);//, ios::out);
				//if(!(m_outfilePtr->is_open()))
				{
					int sdf = 0 ;
				}
				//else
				{
					int asdf = 0 ;
				}
			}
			else
			{
				m_infilePtr  = new  ifstream (m_filePAth);
				//if(!(m_infilePtr->is_open()))
				{
					int sdf = 0 ;
				}
				//else
				{
					int asdf = 0 ;
				}
			}
		}
		m_isWriteMode = isWriteMode;

	
	//if(!(outfile.is_open()))
//	{
	//	return false;
	//}


	}
	cArrayFlex::~cArrayFlex()
	{
		if(m_arr != NULL)
		{
			delete []m_arr;
			m_arr = NULL;
			m_size=0;
			m_readMovingIndex=0;
		}
		if(m_outfilePtr != NULL)
		{
			delete m_outfilePtr;
			m_outfilePtr=NULL;
		}
		if(m_infilePtr != NULL)
		{
			delete m_infilePtr;
			m_infilePtr=NULL;
		}
	}
 
	/*
	void cArrayFlex::WriteReadArray( unsigned char* arr, int size, bool isWriteToArray)
	{
		if(isWriteToArray)
		{
			if(true)
			{
				bool ret = FileManager::WriteOneBlock((*m_outfilePtr),arr, size);
			}
			else
			{
				bool* newArr = new bool[m_size + size];
				for(int i = 0 ; i < m_size ; i++)
				{
					newArr[i] = m_arr[i];
				}
				for(int i = 0 ; i < size ; i++)
				{
					newArr[m_size + i] = arr[i];
				}
				m_size += size;
				if(m_arr != NULL)
				{
					delete []m_arr;
				}
				m_arr = newArr;
			}
		}
		else
		{
			if(true)
			{
				bool ret = FileManager::ReadOneBlock(arr,(*m_infilePtr), size);
			}
			else
			{
				int ssssdf=0;
				for(int i = 0 ; i < size ; i++)
				{
					arr[i] = m_arr[m_readMovingIndex+i];
				}
				m_readMovingIndex += size;
			}
		}
		
	}
*/

	

	// it reads or writes an enter by reading or writing an empy string as a line
void cArrayFlex::Enter(  bool isWriteToArray, char endOfLineSign )
{
	char str[2];
	str[0]=0;
	if(isWriteToArray)
	{
		FileManager::WriteOneLine(*m_outfilePtr, str, endOfLineSign);
	}
	else
	{
		FileManager::ReadOneLine(str, *m_infilePtr,endOfLineSign);// (string)  
	}

}

//8 4 23
void cArrayFlex::WriteReadArrayString(char* str, bool isWriteToArray, cGlobals &globals, bool isToAddDoubleQuaotes)
{
	if(isWriteToArray)
	{
		if(isToAddDoubleQuaotes)
		{
			int len = strlen(str);
			int newLen = len+2;
			char* str2 = new char[newLen +1];//+1 1 like any string and two more for " befre and after
			str2[0]= '"';
			for(int i=0; i < len ; i++)
			{
				str2[i+1]= str[i];
			}
			str2[len+1] = '"';
			str2[len+2] = 0;
			FileManager::WriteOneLine(*m_outfilePtr, str2, globals.g_endOfLineInSign);
			delete [] str2;
			str2=NULL;
		}
		else
		{
			FileManager::WriteOneLine(*m_outfilePtr, str, globals.g_endOfLineInSign);
		}
	}
	else
	{
		if(isToAddDoubleQuaotes)
		{
			char str2[300];
			FileManager::ReadOneLine(str2, *m_infilePtr,globals.g_endOfLineInSign);// 
			int newLen = strlen(str2);
			int len = newLen-2;
			for(int i = 0 ; i < len ; i++)
			{
				str[i] = str2[i+1];
			}
			str[len] = 0;	
		}
		else
		{
			FileManager::ReadOneLine(str, *m_infilePtr,globals.g_endOfLineInSign);// (string)  
		}
	}

}




	void cArrayFlex::WriteReadArrayBool( bool &item, bool isWriteToArray, cGlobals &globals)
	{
		if(isWriteToArray)
		{
			

		//	bool ret = FileManager::WriteOneBlock((*m_outfilePtr),(unsigned char*)(&item), sizeof(bool));

			int intItem =(int)( item );
			WriteReadArrayInt(intItem, isWriteToArray, globals);
	
		}
		else
		{
			//bool ret = FileManager::ReadOneBlock((unsigned char*)(&item),(*m_infilePtr), sizeof(bool));
		//	bool ret = FileManager::ReadOneBlock(arr,(*m_infilePtr), sizeof(int));
			int intItem = 0;
			WriteReadArrayInt(intItem, isWriteToArray, globals);
			//bool ret = FileManager::ReadOneBlock((unsigned char*)(&intItem),(*m_infilePtr), sizeof(int));
			item = bool(intItem);
		}		

	}

/*		 
	void cArrayFlex::WriteReadArrayInt( int &item, bool isWriteToArray)
	{
		if(isWriteToArray)
		{
			bool isPositive = true;
			if(item < 0 )
			{
				isPositive = false;
				item *= (-1);
			}
			char strOfValue[100];
			//int radix=0;
			//char str[ENOUGH];
			sprintf(strOfValue, "%d", item);
			int len = strlen(strOfValue);
			char strOfLength[100];
			sprintf(strOfLength, "%d", len);
			int lengthIffStringgOfLength = strlen(strOfLength);
			if(lengthIffStringgOfLength == 1)
			{
				strOfLength[2]=0; 
				strOfLength[1] = strOfLength[0];
				strOfLength[0] = '0';
			}
			//itoa(item, str, radix);
			char strSign[100];
			strSign[0] = '+';
			strSign[1] = 0; 
			bool ret = FileManager::WriteString( *m_outfilePtr, strSign, 1);
			ret = FileManager::WriteString( *m_outfilePtr, strOfLength, 2);
			if(!isPositive)
			{
				strSign[0] = '-';
			}
			ret = FileManager::WriteString( *m_outfilePtr, strSign, 1);
			ret = FileManager::WriteString( *m_outfilePtr, strOfValue , len);
		}
		else
		{
			char strSign[100];
			bool ret = FileManager::ReadString(strSign , 1, *m_infilePtr);
			char strOfLength[100];
			int lengthOfStringOfLen = 2; //we dont have strings more than 99
			ret = FileManager::ReadString(strOfLength , lengthOfStringOfLen, *m_infilePtr);
			int len = atoi(strOfLength);
			ret = FileManager::ReadString(strSign , 1, *m_infilePtr);
			bool isPositive = false;
			if(strSign[0] == '+')
			{
				isPositive = true;
			}
			char strOfValue[100];
			ret = FileManager::ReadString(strOfValue , len, *m_infilePtr);
			item = atoi(strOfValue);
			if(!isPositive )
			{
				item *= (-1);
			}
		//	char str[100];
		//	bool ret = FileManager::ReadString(str);
		//	item = stoi(str);
		//	bool ret = FileManager::ReadOneBlock((unsigned char*)(&item),(*m_infilePtr), sizeof(int));
		//	bool ret = FileManager::ReadOneBlock(arr,(*m_infilePtr), sizeof(int));
		}
	
	}
*/
			 
	void cArrayFlex::WriteReadArrayInt( int &item, bool isWriteToArray, cGlobals &globals)
	{
		if(isWriteToArray)
		{
			long long longItem = long long(item);
		 	string s = std::to_string(longItem);
			int len = s.length();
			char str[200];
			for(int ii = 0 ; ii < len ; ii++)
			{
				str[ii] = s[ii];
			}
			str[len] = 0;
			WriteReadArrayString(str,isWriteToArray,globals);
			/////////////
/*
			//int radix=0;
			//char str[ENOUGH];
			sprintf(strOfValue, "%d", item);
			int len = strlen(strOfValue);
			char strOfLength[100];
			sprintf(strOfLength, "%d", len);
			int lengthIffStringgOfLength = strlen(strOfLength);
			if(lengthIffStringgOfLength == 1)
			{
				strOfLength[2]=0; 
				strOfLength[1] = strOfLength[0];
				strOfLength[0] = '0';
			}
			//itoa(item, str, radix);
			char strSign[100];
			strSign[0] = '+';
			strSign[1] = 0; 
			bool ret = FileManager::WriteString( *m_outfilePtr, strSign, 1);
			ret = FileManager::WriteString( *m_outfilePtr, strOfLength, 2);
			if(!isPositive)
			{
				strSign[0] = '-';
			}
			ret = FileManager::WriteString( *m_outfilePtr, strSign, 1);
			ret = FileManager::WriteString( *m_outfilePtr, strOfValue , len);
		*/
		}
		else
		{
			char str[200];
			WriteReadArrayString(str,isWriteToArray,globals);
			item = stoi(str);

			/*

			char strSign[100];
			bool ret = FileManager::ReadString(strSign , 1, *m_infilePtr);
			char strOfLength[100];
			int lengthOfStringOfLen = 2; //we dont have strings more than 99
			ret = FileManager::ReadString(strOfLength , lengthOfStringOfLen, *m_infilePtr);
			int len = atoi(strOfLength);
			ret = FileManager::ReadString(strSign , 1, *m_infilePtr);
			bool isPositive = false;
			if(strSign[0] == '+')
			{
				isPositive = true;
			}
			char strOfValue[100];
			ret = FileManager::ReadString(strOfValue , len, *m_infilePtr);
			item = atoi(strOfValue);
			if(!isPositive )
			{
				item *= (-1);
			}
		//	char str[100];
		//	bool ret = FileManager::ReadString(str);
		//	item = stoi(str);
		//	bool ret = FileManager::ReadOneBlock((unsigned char*)(&item),(*m_infilePtr), sizeof(int));
		//	bool ret = FileManager::ReadOneBlock(arr,(*m_infilePtr), sizeof(int));
		*/
		}
	
	}

	
	void cArrayFlex::WriteReadArrayDouble( double &item, bool isWriteToArray, cGlobals &globals)
		//unsigned char* arr, int size, bool isWriteToArray, )
	{
		double multipler = 1000.0;
		if(isWriteToArray)
		{
			char str[200];
			int intItem =(int)( item * multipler);
			long double dValue = ((double) (intItem)) / multipler;
			string s = std::to_string(dValue);
			int len = s.length();
			for(int ii = 0 ; ii < len ; ii++)
			{
				str[ii] = s[ii];
			}
			str[len] = 0;
			WriteReadArrayString(str,isWriteToArray,globals);
		}
		else
		{
			char str[200];
			WriteReadArrayString(str,isWriteToArray,globals);
			item = stod(str);
		}		
	}

	void  cArrayFlex::WriteReadArrayChar(char &item, bool isWriteToArray  , cGlobals &globals)
	{
		if(isWriteToArray)
		{
			int intItem =(int)( item );
			WriteReadArrayInt(intItem, isWriteToArray ,  globals);
		}
		else
		{
			int intItem = 0;
			WriteReadArrayInt(intItem, isWriteToArray, globals);
			item = char(intItem);
		}		
	}

	 



	void cArrayFlex::WriteArrayToDisc()//
	{
	//open file, assume the file path is updated already in the object
	//-write m_size to the file
	//-writhe the m_arr size m_size to file  
	//-m_readMovingIndex - dont touch, dont writhe
	//close file
	}
	void cArrayFlex::ReadArrayFromDisc()
	{
	//open file
	//read m_size from disck and updae the object
	//open in memory m_arr as member of object
	// read m_size bites and copy to bool array  m_arr
	//close file

		SetReadIndexToStart(); ////set m_readMovingIndex to 0
	}
		
		
	





	int cVarianceCalc::FindHighestScoreNotInFlagArray( double*	wghtArr , int N, bool*	isIn )
	{
		int highestPos = -1 ;
		double highestScore = -1000000;
		for(int i = 0 ; i < N ; i++)
		{
			if((!isIn[i]) && (wghtArr[i] > highestScore ) )
			{
				highestScore = wghtArr[i];
				highestPos = i;
				
			}
		}
		return highestPos;
	}
	


	  //7 18 17  new function
	 //7 20 17  updated function 
 double cVarianceCalc::CalculateMostFrequentValueNew ( double* arr , int numOfItems, bool* isIn, int numOfBuckets)
	{
	//	int numOfBuckets=NUM_OF_DECILES;
		double* thredholdArr = new double[numOfBuckets];
		cVarianceCalc::PrepareMapOfValuesForDecilesGrouping(thredholdArr , numOfBuckets ,arr, isIn , numOfItems);
		int* decileNum = new int[numOfItems];
		for(int i = 0 ; i < numOfItems ; i ++)
		{
			decileNum[i] = -1;
			if((isIn == NULL ) || (isIn[i]))
			{
				int gropNum = cVarianceCalc::GetGrpIndex (arr[i] , thredholdArr, numOfBuckets);//, double  multiplier)
				decileNum[i] = gropNum;
			}
		}

		double* wghArr = new double[numOfItems];
		for(int i = 0 ; i < numOfItems ; i ++)
		{
			wghArr [i] = 1.0;
			
			bool isNotIn = (isIn != NULL ) &&  (!(isIn[i])); //if there is an array to limit and it is not in the array
			bool isExtremeCase = false;
			if( ! isNotIn ) //if is in
			{
				isExtremeCase = //( (decileNum[i] == 0 ) ||  (decileNum[i] == 9 )   );
					( (decileNum[i] == 0 ) || (decileNum[i] == 1 ) || (decileNum[i] == 8 ) || (decileNum[i] == 9 )   );
			}
			if( isNotIn  || isExtremeCase)
			{
				wghArr [i] = 0.0;
			}
		}
	
		double meanVal=0.0; 
		double sdVal=0.0;
		CalculateMeanAndSD(meanVal, sdVal, arr,  wghArr,numOfItems);

		delete []wghArr ;
		delete []decileNum;

		delete []thredholdArr;

		return meanVal;
	}



	
//5 21 14 three new  functinos
 void   cVarianceCalc::CalculateMeanAndVariance(double &mean, double &variance, double* arr,
		                                     double* weightArr, unsigned int count)
	{
		mean=0;
		double sumWeights=0;
		for(unsigned int i=0 ; i < count ; i ++)
		{
			double wgh = 1.0;
			if(weightArr != NULL)
			{
				wgh = weightArr[i];
			}
			mean += wgh* arr[i];
			sumWeights += wgh;
		}
		if(sumWeights > 0.0)
		{
			mean /= sumWeights ;
		}
		variance=0;
		for(unsigned int i=0 ; i < count ; i ++)
		{
			double wgh = 1.0;
			if(weightArr != NULL)
			{
				wgh = weightArr[i];
			}
			double dif =  arr[i] - mean;
			variance += (dif*dif*wgh);
		}
		if(sumWeights > 0.0)
		{
			variance /= sumWeights ;
		}
		//sd = pow(sd, 0.5);
	}




/*
//10 8 16 to do two functions 
void cVarianceCalc::PrepareMapOfValuesForDecilesGrouping( double* thresholdArr , int numOfBuckets ,double* arr,
																						bool* isIn, int arrSize)
{
	double* localArr = new double[arrSize];
//	int actualCnt = 0;
	int cleanIndex = 0;
	for(int i = 0 ; i < arrSize ; i++)
	{
		localArr[i] = 0.0;
		if( (isIn == NULL) || (isIn[i]) )
		{
			localArr[cleanIndex ] = arr[i] ;

			cleanIndex ++;
		}
	}

	//Ohad 1.12.19
	//SortArray(localArr , cleanIndex);
	BubbleSort( localArr , cleanIndex);

	string_m log;
	log.assign("min Value bubble sort ").appendNum(localArr[0]).append(" Max Value Bubble Sort ").appendNum(localArr[cleanIndex-1]);
	cLogManagement::GetInstance()->AddToLogFile((char*)log.c_str(), debug_e);

	int jump = cleanIndex / numOfBuckets;
	int posInArr = 0;
	for(int x = 0 ; x < numOfBuckets ; x++)
	{
		posInArr += jump;
		if(x == ( numOfBuckets - 1))
		{
			posInArr = cleanIndex -1;
		}
		
		thresholdArr[x] = localArr[posInArr ];
	
	}


	delete []localArr;
}
*/



 void cVarianceCalc::FillHistorgam( cHistogram *hist, double* valArr, int size)
 {
	//double mean=0.0;
	//double sd=0.0;
	///CalculateMeanAndSD(mean,sd,valArr, NULL, size);
	for(int i = 0 ; i < size ; i++)
	{
		hist->AddValue(char(valArr[i]));
	}
	hist->Sort();

 }

 //10 24 22
 //when adding a case of a paragrph with a value of V, and the count of how many times V appeared loking at how many paragphs, if we change this to be 
 //words/lettes that are here thn the size would make us want to push add the paragaph value more times. 
 //so every time we add a value hist->AddValue(valArr[i]), we can add this times strLen 
 void cVarianceCalc::FillHistorgamWithLineLengthInConsidetion( cHistogram *hist, double* valueArr, double* lineSizeArr, int size )
 { 
	for(int i = 0 ; i < size ; i++)
	{
		double incrasedSampleRate = pow(lineSizeArr[i] , 0.6);
		int numOfAddingValueIterations = (int(incrasedSampleRate))+1;
		for(int ii = 0 ; ii < numOfAddingValueIterations ; ii++)
		{
			hist->AddValue(char(valueArr[i]));
		}
	}
	hist->Sort();
 }






//12 1 19
void cVarianceCalc::PrepareMapOfValuesForDecilesGrouping(
	double* thresholdArr , int numOfBuckets ,double* arr,	bool* isIn, int arrSize)
{
	double* localArr = new double[arrSize];
//	int actualCnt = 0;
	int cleanIndex = 0;
	double lowestVAlue = 0.0;//5  5 23 check if perhpas starts from a h igher value since anyway there is no less than 0.0
	double highestValue = 0.0;
	for(int i = 0 ; i < arrSize ; i++)
	{
		localArr[i] = 0.0;
		if( (isIn == NULL) || (isIn[i]) )
		{
			localArr[cleanIndex ] = arr[i] ;
			lowestVAlue = Min(lowestVAlue , localArr[cleanIndex ] );
			highestValue = Max(highestValue , localArr[cleanIndex ] );

			cleanIndex ++;
		}
	}

	bool isBucketSortGood = true;
	double gap  = highestValue  - lowestVAlue ;
//	if( 	lowestVAlue < 0.0 || highestValue > 100.0 || gap < 15.0  )
	if( 	gap > 99.0 || gap < 15.0  )
	{
		isBucketSortGood = false;
	}

	if(false)//	isBucketSortGood )
	{
		BucketSort(localArr , cleanIndex , 100,  lowestVAlue * -1.0 );
	}
	else
	{
		BubbleSort( localArr , cleanIndex);
	}

	int jump = cleanIndex / numOfBuckets;
	int posInArr = 0;
	for(int x = 0 ; x < numOfBuckets ; x++)
	{
		posInArr += jump;
		if(x == ( numOfBuckets - 1))
		{
			posInArr = cleanIndex -1;
		}
		
		thresholdArr[x] = localArr[posInArr ];
	
	}


	delete []localArr;
}


void cVarianceCalc::JasonPringSimpleArray(char* msgStr,  char* titleIn, 
	int leadingSpacesNum , cArrayFlex* arrayFlex, cGlobals* globals,  int integerIn, 
	                   int* cntArr, bool isComa)
{
	cVarianceCalc::StrCptWithDoubleQuotesAndColonAndOpeningSquare(msgStr, titleIn,
		                                                     leadingSpacesNum,  true);
	arrayFlex->WriteReadArrayString(msgStr, true , *globals);
 	leadingSpacesNum+=2;
	for(int s=0; s< integerIn ; s++)
	{
		bool isComa = true;
		if(s == (integerIn - 1) )
		{
			isComa = false;
		}
		//cVarianceCalc::CreateStringFromIntegerAndComa(msgStr, 	 ,  leadingSpaceNum ,isComa);
		cVarianceCalc::CreateStringFromIntAndComa(msgStr, cntArr[s],  leadingSpacesNum ,isComa);
		arrayFlex->WriteReadArrayString(msgStr, true , *globals);
	}
	leadingSpacesNum -=2;
	cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "]",leadingSpacesNum, false);
	if(isComa)
	{
		cVarianceCalc::StringAppend(msgStr , ",");
	}
	arrayFlex->WriteReadArrayString(msgStr, true , *globals);

}





void cVarianceCalc::JasonPringSimpleArray(char* msgStr,  char* titleIn, 
	int leadingSpacesNum , cArrayFlex* arrayFlex, cGlobals* globals,  int integerIn, 
	                   double* valArr, bool isComa)
{
	cVarianceCalc::StrCptWithDoubleQuotesAndColonAndOpeningSquare(msgStr, titleIn,
		                                                     leadingSpacesNum,  true);
	arrayFlex->WriteReadArrayString(msgStr, true , *globals);
 	leadingSpacesNum+=2;
	for(int s=0; s< integerIn ; s++)
	{
		bool isComa = true;
		if(s == (integerIn - 1) )
		{
			isComa = false;
		}
		//cVarianceCalc::CreateStringFromIntegerAndComa(msgStr, 	 ,  leadingSpaceNum ,isComa);
		cVarianceCalc::CreateStringFromDoubleAndComa(msgStr, valArr[s],  leadingSpacesNum ,isComa);
		arrayFlex->WriteReadArrayString(msgStr, true , *globals);
	}
	leadingSpacesNum -=2;
	cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "]",leadingSpacesNum, false);
	if(isComa)
	{
		cVarianceCalc::StringAppend(msgStr , ",");
	}
	arrayFlex->WriteReadArrayString(msgStr, true , *globals);
}


//"Inclusion Rules" - stringTitle
void cVarianceCalc::JsonPrintVarValPonts(char* msgStr, char* stringTitle, 
	cVariableAndValueAndPoints* inclusionRuleList, 	int numInteger, int leadingSpacesNum, 
	   bool isAddComma, cGlobals * globals, cArrayFlex* arrayFlex)
{
	char messageIn[100];
	strcpy(messageIn, "Number Of ");
	StringAppend(messageIn, stringTitle);
	bool isWrite = true;
	cVarianceCalc::CreateStringWithCulumnAndQuotesAndInteger(msgStr, messageIn, numInteger,
		                           leadingSpacesNum, isAddComma );
	arrayFlex->WriteReadArrayString(msgStr,  isWrite, *globals);
	cVarianceCalc::StrCptWithDoubleQuotesAndColonAndOpeningSquare(msgStr, stringTitle ,leadingSpacesNum,  true);
	arrayFlex->WriteReadArrayString(msgStr, isWrite , *globals);
	leadingSpacesNum += 2;
	for(int i = 0 ; i < numInteger; i++)
	{
		cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "{",leadingSpacesNum, false);
		arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),*globals);
	 	leadingSpacesNum += 2;
		inclusionRuleList[i].VarValObjPrepareArraysToOrFromDisc2(
			arrayFlex,  arrayFlex->GetIsWriteMode(), *globals, leadingSpacesNum, i );
		leadingSpacesNum -= 2;
		cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "}",leadingSpacesNum, false);
//		strcpy(msgStr, "}");
		arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),*globals);
	
		if(i < (numInteger-1) )
		{
			//strcpy(msgStr, ",");
			cVarianceCalc::StrCptWithDoubleQuotes(msgStr, ",",leadingSpacesNum, false);
			arrayFlex->WriteReadArrayString(msgStr, arrayFlex->GetIsWriteMode(),*globals);
		}		
	}
	leadingSpacesNum -= 2;
	cVarianceCalc::StrCptWithDoubleQuotes(msgStr, "]",leadingSpacesNum, false);
	cVarianceCalc::StringAppend(msgStr , ",");
	arrayFlex->WriteReadArrayString(msgStr, isWrite , *globals);
}




//1 5 20  new
void cVarianceCalc::PrepareWeightedMapOfValuesForDecilesGrouping(  double* threshldArr ,int numOfGrps ,
													double* arr, double* wghArr, bool* isIn,int N) 
{

	double* localArr = new double[N];
	double* localWghArr = new double[N];
//	int actualCnt = 0;
	int cleanIndex = 0;
	double lowestVAlue = 0.0;
	double highestValue = 0.0;
	for(int i = 0 ; i < N ; i++)
	{
		localArr[i] = 0.0;
		localWghArr[i]=0.0;
		if( (isIn == NULL) || (isIn[i]) )
		{
			localArr[cleanIndex ] = arr[i] ;
			
			lowestVAlue = Min(lowestVAlue , localArr[cleanIndex ] );
			highestValue = Max(highestValue , localArr[cleanIndex ] );

			localWghArr[cleanIndex]= 1.0;
			if(wghArr != NULL)
			{
				localWghArr[cleanIndex]= wghArr[i];
			}

			cleanIndex ++;
		}
	}

	
	
	BubbleSort( localArr ,localWghArr, cleanIndex);

	double sumWghts=0.0;
	for(int i = 0 ; i < cleanIndex ; i++)
	{
		sumWghts += localWghArr[i];
	}

	for(int x = 0 ; x < numOfGrps ; x++)
	{
		threshldArr[x] = localArr[cleanIndex-1];
	}

	double gap = sumWghts / numOfGrps;

	double sumWghts2=0.0;
	double gapMoving = gap;
	int grpIndex = 0;
	for(int i = 0 ; i < cleanIndex ; i++)
	{
		sumWghts2 += localWghArr[i];

		if(grpIndex ==  (numOfGrps - 1))
		{
			threshldArr[grpIndex] = localArr[cleanIndex-1] ;
		}
		else
		{
			if((sumWghts2 > gapMoving) )
			{
				gapMoving += gap;
				threshldArr[grpIndex++] = localArr[i] ;
			}
		}
	}

	delete []localArr;
	delete []localWghArr;
}




//8 21 17
double cVarianceCalc::CalcualteTopLOSbucketValue (double* arr, int arrSize, int numOfBuckets)
{
	
	//cMinMaxMap twoDmap( numOfBuckets  ); 
	double* threshold = new double[numOfBuckets];
	cVarianceCalc::PrepareMapOfValuesForDecilesGrouping( threshold,  numOfBuckets, arr,NULL, arrSize);
	//	,predictionValues,NULL,  dataProfiles.GetProfilesList()->GetSize());
	double ret = threshold[numOfBuckets-2];
	return ret;
}

int  cVarianceCalc::FindLowestIndexNotSelectedAlready(double* valArr,  bool* isIn, int size)
{
	int lowestIndex = -1;
	double lowestVal = 1000000;
	for(int i = 0 ; i < size ; i++)
	{
		if(!( isIn[i]))
		{
			if(valArr[i] < lowestVal)
			{
				lowestVal = valArr[i] ; 
				lowestIndex = i;
			}		
		}	
	}
	return lowestIndex;
}
	

void cVarianceCalc::FillArrWithLowestValue(bool* isIn, double* valArr, int size, int numOfSelcted)
{
	//bool* isTaken = new bool[size];
	for(int i = 0 ; i < size ; i++)
	{
		isIn[i] = false;	
	}
	for(int s = 0 ; s < numOfSelcted ; s++)
	{
		int index = FindLowestIndexNotSelectedAlready(valArr, isIn, size);
		if(index >=0)
		{
			isIn[index] = true;
		}
	}	
}

bool cVarianceCalc::IsVarValExist( cVariableAndValueAndPoints* varValArr, int size, int var, double val)
{
	bool ret = false;
	for(int i  = 0 ; i < size ; i++)
	{
		if(  (varValArr[i].m_variableIndex == var ) &&  (varValArr[i].m_value == val )  )
		{
			ret = true;
			return ret;
		}
	}
	return ret;
}




int cVarianceCalc::GetGrpIndex(double scaleVal, double* thresholdList, int numberOfSubGrps)
{
//	int grpNum = numberOfSubGrps - 1;
	for (int i = 0 ; i < numberOfSubGrps ; i++)
	{
		if(scaleVal < thresholdList[i])
		{
			//grpNum = i;
			return i;
		}
	}
	return  numberOfSubGrps - 1;
}

void cVarianceCalc::FillValuesOfBuckets( double* bucketVal, int numOfBuckets, double* arr , bool* isIn, int arrSize )
{
	double* localArr = new double[arrSize];
//	int actualCnt = 0;
	int cleanIndex = 0;
	for(int i = 0 ; i < arrSize ; i++)
	{
		localArr[i] = 0.0;
		if( (isIn == NULL) || (isIn[i]) )
		{
			localArr[cleanIndex ] = arr[i] ;

			cleanIndex ++;
		}
	}
	BubbleSort( localArr , cleanIndex);

	int jump = cleanIndex / numOfBuckets;
	int posInArr = 0;
	for(int x = 0 ; x < numOfBuckets ; x++)
	{
		double* tempArr = localArr + posInArr;

		{
			double val1 = *tempArr;
			double val2 = (localArr[posInArr]);
			int sdfg = 0 ; 
		}

		posInArr += jump;
		double mean=0.0;
		double sd = 0.0;
		CalculateMeanAndSD(mean, sd, tempArr, NULL, jump);	
		bucketVal[x] = mean;	
	}


	delete []localArr;


}



int cVarianceCalc::FindIndexOfStringInStringArray(char* tempStr,  char** strs , int numOfItems )
{ //8 5 16 TO DO //8 7 16
	for( int i=0; i <numOfItems ; i++)
	{
		if(!strcmp(tempStr, strs[i]))
		{
			return i;
		}
	}
	return -1;
}


/*
double cVarianceCalc::UpdateOneVAlueFromStringAndValueArrays(char* tempStr,  char** strs , double* valueArr, int numOfItems,StringToIntHash& FieldNAmeToIndexHash )
{

	double retValu = 0.0;
	
	int indexInArray = -1;//FindIndexOfStringInStringArray(tempStr,  strs , numOfItems );
	FieldNAmeToIndexHash.LookUp(tempStr,indexInArray);
	if( indexInArray >= 0)
	{
		retValu = valueArr[indexInArray];
	}

	return retValu;

}
*/
double cVarianceCalc::UpdateOneVAlueFromStringAndValueArrays(char* tempStr,  char** strs , double* valueArr, int numOfItems)
{

	double retValu = 0.0;
	
	int indexInArray = FindIndexOfStringInStringArray(tempStr,  strs , numOfItems );
	if( indexInArray >= 0)
	{
		retValu = valueArr[indexInArray];
	}

	return retValu;

}





//11 4 18 ** new 
//11 25 18 * updated 
int cVarianceCalc::CollectTopProfilesWithSimilarDepVAlueFixedMAxDistance(bool* isIn , double* arr, int num, double anchorVal, double valueSD  , double maxDiffInSD, int maxNumToFill)
{
	int cntOfFound = 0 ;
	for(int i = 0 ; i < num ; i++)
	{
		isIn[i] = false;	
		double diff = Abs(arr[i] - anchorVal );
		double diffInSD = diff / valueSD;
		if((/*cntOfFound < maxNumToFill */true) && ( diffInSD < maxDiffInSD ))
		{
			cntOfFound ++;
			isIn[i] = true;
		}
	}
	return cntOfFound;
}

//11 23 18 ** new 
bool cVarianceCalc::CollectTopProfilesWithSimilarDepVAlue(bool* isIn , double* arr, int num, double anchorVal, double valueSD  ,  int minOfSampleCases)
{
	if(valueSD <= 0.0 )
	{
		return false;
	}

	double maxDiffInSD = 0.05;
	int cnt = CollectTopProfilesWithSimilarDepVAlueFixedMAxDistance(isIn , arr,  num,  anchorVal,  valueSD  ,  maxDiffInSD, minOfSampleCases);
	if(cnt >= minOfSampleCases)
	{
		return true;
	}
	maxDiffInSD = 0.1;
	cnt = CollectTopProfilesWithSimilarDepVAlueFixedMAxDistance(isIn , arr,  num,  anchorVal,  valueSD  ,  maxDiffInSD, minOfSampleCases);
	if(cnt >= minOfSampleCases)
	{
		return true;
	}
	maxDiffInSD = 0.25;
	cnt = CollectTopProfilesWithSimilarDepVAlueFixedMAxDistance(isIn , arr,  num,  anchorVal,  valueSD  ,  maxDiffInSD, minOfSampleCases);
	if(cnt >= minOfSampleCases)
	{
		return true;
	}
	maxDiffInSD = 0.5;
	cnt = CollectTopProfilesWithSimilarDepVAlueFixedMAxDistance(isIn , arr,  num,  anchorVal,  valueSD  ,  maxDiffInSD, minOfSampleCases);
	if(cnt >= minOfSampleCases)
	{
		return true;
	}

	//not enough matched in a reonble sd away from anchor profile dep vlaue. removing all matched aand returning false
	for(int i = 0 ; i < num ; i++)
	{
		isIn[i] = false;	
	}
	return false;
}
			


void cVarianceCalc::CalculateMeanAndSD(double &mean, double &sd, char* valArr, int* cntArr, int size)
{
	double* whgArr = new double[size];
	double* arr = new double[size];
	for(int i = 0 ; i < size ; i++)
	{
		whgArr[i] = double(cntArr[i]);
		arr[i] = double(valArr[i]);
	}
	CalculateMeanAndSD(mean, sd,arr,whgArr, size);

	delete []whgArr;
	delete []arr;
}


//6 17 16  new function
void cVarianceCalc::CalculateMeanAndSdScoresFromIndexes(double &mean, double &sd,
							int* indexArr , int count , double* profileScoreArr)
	{
		double* arr = new double[count];
		for(int i = 0 ; i < count ; i++)
		{
			arr[i] = profileScoreArr[indexArr[i]];
		}
		CalculateMeanAndSD(mean, sd,  arr,    NULL, count);
		delete []arr;
	}

//6 17 16 new function
int cVarianceCalc::GetPositionOfHighestAvaliableScore(bool* taken, double* scoreArr, int count)
{
	int highstIn = -1;
	double maxScore = -1.0;
	for( int i = 0 ; i < count ; i++)
	{
		if(!(taken[i]))
		{
			if(scoreArr[i] > maxScore)
			{
				maxScore = scoreArr[i] ;
				highstIn = i;
			}
		}
	}
	return highstIn;

}


void cVarianceCalc::AddPrefixstring(	char* inOutStr  ,  char* prefix)
{
	
	/*string_m str;
	str.assign(prefix).append(inOutStr);
	strcpy(inOutStr , (char*)str.c_str());*/
	
	int prefixLen = strlen(prefix);
	int originalStLen = strlen(inOutStr);
	int totalLen = prefixLen  + originalStLen ;

	char temp[MAX_STRING_LENGTH];
	strcpy_s(temp, prefix);
	for(int i = 0 ; i < originalStLen ; i++)
	{
		temp[prefixLen + i] = inOutStr[i];
	}
	temp[totalLen] = 0;
	strcpy(inOutStr , temp);
	//strcpy_s(temp , temp);

}

void cVarianceCalc::ConcatPrefixStringToEachString ( char** strArr, int indexToStartFilling, int numOfFilled , char* prefix)
{
	//7 19 16
	for(int i = indexToStartFilling ; i <  (indexToStartFilling +  numOfFilled) ; i++)
	{
		AddPrefixstring(	strArr[i] , prefix);
	}

 }


 

//2 18 18 * new fuction
double	cVarianceCalc::CalculateScoreBasedOnSignificantChangeInMean( double**  varWghPerObject, int mustBeOn1, int mustBeOn2, double* predictionArr, 
	bool* isIn, int numOfObjects,  double baseMean)
{
	double* localWghArr = new double [numOfObjects];
	for(int ii = 0 ; ii< numOfObjects ; ii++)
	{
		localWghArr[ii]=0.0;
		if(  isIn[ii] )
		{
			if((varWghPerObject[ii][mustBeOn1] > 0.0) && (varWghPerObject[ii][mustBeOn2] > 0.0))
			{
				localWghArr[ii]=1.0;
			}
		}
	}
	double mean=0.0;
	double sd=0.0;
	cVarianceCalc::CalculateMeanAndSD(mean, sd ,predictionArr, localWghArr,numOfObjects);
	double score = Abs( mean - baseMean) ;
	
	delete []localWghArr;
	return score;
}


//2 12 18 * new fuction
double	cVarianceCalc::CalculateScoreBasedOnREductionOfSDfromBaseSD( double**  varWghPerObject, int mustBeOn1, int mustBeOn2, double* predictionArr, 
	bool* isIn, int numOfObjects,  double baseSD)
{
	double* localWghArr = new double [numOfObjects];
	for(int ii = 0 ; ii< numOfObjects ; ii++)
	{
		localWghArr[ii]=0.0;
		if(  isIn[ii] )
		{
			if((varWghPerObject[ii][mustBeOn1] > 0.0) && (varWghPerObject[ii][mustBeOn2] > 0.0))
			{
				localWghArr[ii]=1.0;
			}
		}
	}
	double mean=0.0;
	double sd=0.0;
	cVarianceCalc::CalculateMeanAndSD(mean, sd ,predictionArr, localWghArr,numOfObjects);
	double score = baseSD - sd;
	score= cVarianceCalc::Max(score , 0.0);

	delete []localWghArr;
	return score;
}



double cVarianceCalc::point_biserial_correlation(int n, double mean1, double mean0, double sd, double sum1, double sum0)
{
    double rpb = (mean1 - mean0) * pow(double(n), 0.5) / (sd * sqrt(sum1 + sum0));
    double total = (sum1 + sum0);
	double productOfSumsDividBySquareTotal =  (sum1*sum0) / ( total*total);
	double rpb2 =      ((mean1-mean0) / sd)     *   (pow (productOfSumsDividBySquareTotal , 0.5 ));
	return rpb2;
}


double cVarianceCalc::CalcualteETA(double* predArr, double* depArr, int size)
{
	/*
	LinearRegressionInternalDoubleAPI( double &averageSE, double &variance, double & zeroConstant, 
		double * betaArr , double& regressionPerformanceScore,double * predicted_dependentArr,
							double **predictiveArr,	unsigned int N, 
			unsigned int p,  double * dependentArr, double * predictabilityScores , 
			unsigned int sizeOfTestGroup, bool isControlGroupp, bool isLogisticReg)
*/
	double* wghArr = new double[size];
	double sum1=0.0;
	double sum0=0.0;
	for(int i = 0 ; i < size ; i++)
	{
		wghArr[i]=0.0;
		if(depArr[i]==0.0)
		{
			wghArr[i]=1.0;
			sum0 += 1.0;// predArr[i];
		}
		sum1 += 1.0;// predArr[i];
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


	delete []wghArr;
	wghArr=NULL;

	return eta;

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
}


/* 1 14 24 open this
double cVarianceCalc::LogisticRergression(double &averageSE, double &variance, double & zeroConstant, 
		double * betaArr , double& regressionPerformanceScore, double **predictiveArr,	unsigned int N,
		unsigned int p,  double * dependentArr )
{
	bool isLogisticReg = true;
	bool isControlGroup = false;
	unsigned int sizeOfTestGroup = N;
	double * predictabilityScores = new double[N];
	for(int i = 0 ; i < N i++)
	{
		predictabilityScores[i]=1.0;
	}
	cStatisticStructure::LinearRegressionInternalDoubleAPI( averageSE, variance, zeroConstant, 
		 betaArr ,  regressionPerformanceScore, predictabilityScores,predictiveArr,	 N, 
			 p,   dependentArr,  predictabilityScores ,  sizeOfTestGroup,  isControlGroupp,  isLogisticReg);
}
*/










//2 28 18 * 
//3 5 18 * updted due to bug
double	cVarianceCalc::CalcualtedMeanOfTopSimilarObjectsWithNoVarJ( double* valueArr, bool* isIn, int numOfObjects,
																				double** varWghPerObj,double** varValuePerObjFullObj, int i, int varCnt, int j )
{
	double* simScores = new double[numOfObjects];
	double maxScore =0.0;
	for(int ii = 0 ; ii < numOfObjects ; ii++)
	{
		simScores[ii]=0.0;
		if(isIn[ii])
		{
			if(varWghPerObj[ii][j] == 0.0)
			{
				for(int jj = 0 ; jj < varCnt ; jj++)
				{
					if( //either the var jj is ppart of profiles i and ii and is mathcing to the person in both i and ii profiles (so equal or similar) ,
						 //or  is it not mathcing to the person in both but it is the same value in both (without proximit for now, just exact) 
						(  (varWghPerObj[ii][jj] > 0.0) &&  (varWghPerObj[i][jj] > 0.0 )    )
						||
						 (   ( varValuePerObjFullObj[ii][jj] >= 0 )&&
						      ( varValuePerObjFullObj[ii][jj]  ==  varValuePerObjFullObj[i][jj]  )      )
					  )
					{
						simScores[ii] += 1.0;
					}
				}
			}
		}
		maxScore = Max(maxScore ,simScores[ii]);
	}
	

	double thres = maxScore  * 0.8 ; 
	int count=0;
	for(int ii = 0 ; ii < numOfObjects ; ii++)
	{
		if(simScores[ii] >= thres)
		{
			count ++;
		}
	}
	if(count < 20)
	{
		 thres *= 0.9;
	}
	count=0;
	for(int ii = 0 ; ii < numOfObjects ; ii++)
	{
		if(simScores[ii] >= thres)
		{
			count ++;
		}
	}
	if(count < 20)
	{
		 thres *= 0.7;
	}
	

	for(int ii = 0 ; ii < numOfObjects ; ii++)
	{
		if(simScores[ii] < thres)
		{
			simScores[ii]=0.0;
		}
		if(isIn[ii])
		{
			simScores[ii] = Max(simScores[ii], 0.0001);
		}
	
	}

	double meanTopSim = 0.0;
	double sd=0;
	CalculateMeanAndSD(meanTopSim ,sd, valueArr, simScores, numOfObjects);

	delete []simScores;
	return meanTopSim;
}

//2 22 18 * new function
//2 28 18 *  updated
//3 5 18 * updated
double	cVarianceCalc::ComplexChangeInMeanPerInputVar(double* valueArr, bool* isIn,	 double**	varWghPerObj,
															double** varValuePerObjFullObj, double* profileScoreArr, int numOfObjects, int varCnt, int j)
{
	/*
	for input var j i want to measure for each profile that j is includd, then for each k inlucded in that profile, look at all profiles that k incluedd 
	with and witout var j and see how different is the mean, and then calcuater Abs mean change between j and k . then calculte average of such abs change
	of all k!=j and that will be the value reporting for j.
	*/

	
	int cnt=0;
	for(int i=0; i< numOfObjects ; i++)
	{
		if(isIn[i])
		{
			if( varWghPerObj[i][j] > 0.0) //2 22 18 ** add anothe condition instead so that not only varWghPerObj[i][j]>0 but also only some i selected randmoy to not have morme than 20 profiles per var j
			{
				cnt++;
			}
		}
	}

	if(cnt == 0 )
	{
		return 0.0;		
	}

	cnt =0;

	bool* isInAndSimilarAndRepresentingVarJPErsValue = new bool[numOfObjects];
	for(int i=0; i< numOfObjects ; i++)
	{
		isInAndSimilarAndRepresentingVarJPErsValue[i] = false;
	}

	for(int x = 0 ; x < 20 ; x++)
	{
		double maxscore = 0.0;
		int bestScoredIdex = -1;
		for(int i=0; i< numOfObjects ; i++)
		{
			if(isIn[i])
			{
				if( varWghPerObj[i][j] > 0.0) 
				{
					if(isInAndSimilarAndRepresentingVarJPErsValue[i] == false)
					{
						if(	 profileScoreArr[i] > maxscore )
						{
							maxscore = profileScoreArr[i];
							bestScoredIdex = i;
						}
					}
				}
			}
		}
		if(bestScoredIdex >= 0)
		{
			isInAndSimilarAndRepresentingVarJPErsValue[bestScoredIdex]= true;
			cnt++;
		}
	}

	

	double ret = 0.0;
	double sumWghts=0.0;
	for(int i=0; i< numOfObjects ; i++)
	{
		if(isInAndSimilarAndRepresentingVarJPErsValue[i])
		{
			double meanSimilarObjectWithNoVarJ= CalcualtedMeanOfTopSimilarObjectsWithNoVarJ( valueArr, isIn, numOfObjects, 
																		varWghPerObj,varValuePerObjFullObj,i,varCnt, j );
			double cngInMean = Abs(valueArr[i] - meanSimilarObjectWithNoVarJ);
			double wgh = profileScoreArr[i];
			wgh *= wgh;
			ret += cngInMean * wgh;
			sumWghts += wgh;
		}
	}
	if(sumWghts >0.0)
	{
		ret /= sumWghts;
	}

	delete []isInAndSimilarAndRepresentingVarJPErsValue;
	return ret;
}

//cVarianceCalc
	void  cVarianceCalc::CalculateMeanAndSD(double &mean, double &sd, double* arr,
		                                     double* weightArr, unsigned int count)
	{
		CalculateMeanAndVariance(mean, sd,  arr, weightArr,  count);
		sd = pow( sd , 0.5);

	}



//2 12 18 *  updated function
 //2 18 18 * updated
//2 22 18 * updated
	/*
 void cVarianceCalc::CreateRegreionDetalisTwoPredictiveVaribles(double** twoDim, double*& depArr, int &regCnt, 
			double** varWghPerObject, double* predictionArr, bool* isIn, int* cntOfObojectsPerVariable,
			int numOfObjects, int varCnt, double baseMean, double baseSD,  int typeOfScore, bool isWithOneDim, bool isWithTwoDim)

	
 {
	

	int index=0;
	for(int j = 0 ; j < varCnt ; j++)
	{
		if(cntOfObojectsPerVariable[j] > 0)
		{
			if(isWithOneDim)
			{
				twoDim[index]= new double[varCnt];
				for(int l = 0 ; l < varCnt ; l++)
				{
					twoDim[index][l]=0.0;
				}
				twoDim[index][j]=1.0;

				depArr[index] =0.0;
				if((typeOfScore == REDUCTION_IN_SD_AS_HOMONENITY ) )// ABSOLUTE_CHANGE_IN_MEAN_AS_HOMONENITY;// 2;////1 means caculating SD of preidction values for each varible and then reducing sd from base sd. this will effect the depArr value
	//typeOfScore = REDUCTION_IN_SD_AS_HOMONENITY)
				{
					if(cntOfObojectsPerVariable[j] == 1)
					{
						depArr[index] = baseSD;
					}
					else
					{			
						depArr[index] =	CalculateScoreBasedOnREductionOfSDfromBaseSD( varWghPerObject,j,j, predictionArr, isIn, numOfObjects,baseSD);
					}
				}
				else if((typeOfScore == ABSOLUTE_CHANGE_IN_MEAN_AS_HOMONENITY)  ||( typeOfScore == COMPLEX_CHANGE_IN_MEAN_AS_HOMONENITY))
				{
					
					//2 18 18 * xxxxx - add dep 1 or 0 and change the regression code to be logistic. 		send a new 	
					 //the score for the return value will be an absolute change in mean . can be even a 1 sample
						depArr[index] =	CalculateScoreBasedOnSignificantChangeInMean( varWghPerObject,j,j, predictionArr, isIn, numOfObjects,baseMean);
					
				}
				index++;
			}
			if(isWithTwoDim)
			{
				
				{

					for(int k = j+1 ; k < varCnt ; k++)
					{
						if(cntOfObojectsPerVariable[k] > 1)
						{
							int cnt = 0;
							for(int ii = 0 ; ii< numOfObjects ; ii++)
							{
								if(  isIn[ii] )
								{
									if((varWghPerObject[ii][j] > 0.0) && (varWghPerObject[ii][k] > 0.0))
									{
										cnt++;
									}
								}
							}
							if(   ((typeOfScore == REDUCTION_IN_SD_AS_HOMONENITY ) && (cnt >=2)  ) || 
												( (typeOfScore == ABSOLUTE_CHANGE_IN_MEAN_AS_HOMONENITY )&& (cnt >=1) ) )
							{
								twoDim[index]= new double[varCnt];
								for(int l = 0 ; l < varCnt ; l++)
								{
									twoDim[index][l]=0.0;
								}
								twoDim[index][j]=twoDim[index][k]=1.0;
								depArr[index] =0.0;
								if(typeOfScore == REDUCTION_IN_SD_AS_HOMONENITY)
								{
									depArr[index] =	CalculateScoreBasedOnREductionOfSDfromBaseSD( varWghPerObject,j,k, predictionArr, isIn, numOfObjects,baseSD);
								}
								else //if(typeOfScore == ABSOLUTE_CHANGE_IN_MEAN_AS_HOMONENITY)
								{
									//2 18 18 * xxxxx - 
							 //the score for the return value will be an absolute change in mean 
									depArr[index] =	CalculateScoreBasedOnSignificantChangeInMean( varWghPerObject,j,k, predictionArr, isIn, numOfObjects,baseMean);
								}

								index++;
							}
					
						}
					}
				}
			}
		}
	}

	regCnt = index;
}

*/

  //2 15 18 * updated
 //2 18 18 * updated
 //2 22 18 * updated
/*
void cVarianceCalc::GivingVariblesHomogeniryScoresBasedOnCombinedVaribles(double* homogenityScore,
		double* valuesArr,	bool* isIn, double** varWghPerObject, int numOfObjects, int varCnt, 
		int* cntOfObojectsPerVariables, 	bool isAddingOneDimm , bool isAddingTwoDmm, int typeOfScore,double baseMean, double baseSd)
{
	
	double** twoDim =NULL;//= new double*[maxSize];
	double* depArr =NULL;//= new double[maxSize];
	int regCntt = 0;

	int maxSize = varCnt*varCnt ; //to allow case of all full two dim . one dim is inluded as a j==k
	twoDim = new double*[maxSize];
	depArr = new double[maxSize];
	for(int i = 0 ; i < maxSize ; i++)
	{
		twoDim[i] = NULL;
		depArr[i] = 0.0;
	}
	 
	//2 22 18 ** need to change back to true and debug so that the varibels now look good sing logistic regression
	isAddingTwoDmm = false;
	CreateRegreionDetalisTwoPredictiveVaribles(twoDim, depArr, regCntt,  varWghPerObject, valuesArr, isIn,  cntOfObojectsPerVariables,
														 numOfObjects,  varCnt,   baseMean, baseSd,  typeOfScore ,  isAddingOneDimm ,  isAddingTwoDmm);
	if(!isAddingTwoDmm)
	{
		double tempStr[MAX_NUM_OF_PREDICTIVE_VARIABLES];
		for(int j = 0 ; j < varCnt ; j++)
		{
			tempStr[j] = 0.0;
		}
		for(int i = 0 ; i < regCntt ; i++)
		{
			for(int j = 0 ; j < varCnt ; j++)
			{
				if(twoDim[i][j] > 0.0)
				{
					tempStr[j]=depArr[i];
				}
			}
		}

		cSimilarityFormula temp(tempStr, varCnt);
		temp.AdjustPositiveValSum(1.0);
		for(int j = 0 ; j < varCnt ; j++)
		{
			homogenityScore[j] = temp.GetWeights()[j];
		}
	}
	else
	{
	
		bool isAllowedVaribles [MAX_NUM_OF_PREDICTIVE_VARIABLES];//= new bool[varCnt];
		for(int j = 0 ; j < varCnt ; j++)
		{
			isAllowedVaribles[j] = false;
		}
		int cntPerVArForREgression[MAX_NUM_OF_PREDICTIVE_VARIABLES];
		int threshld = regCntt / 200;
		threshld = Max(threshld, 1);
		for(int l = 0 ; l < varCnt ; l++)
		{
			cntPerVArForREgression[l] = 0;
		}
		for(int i = 0 ; i<regCntt ; i++)
		{
			for(int l = 0 ; l < varCnt ; l++)
			{
				if(twoDim[i][l] > 0.0)
				{
					cntPerVArForREgression[l]++;
					if(cntPerVArForREgression[l] >= threshld)
					{
						isAllowedVaribles[l] = true;
					}
				}
			}
		}
		

		//int regIndexOrg = 0 ;
		int shift =0;
		for( int rIndex = 0 ; rIndex < regCntt ; rIndex ++)
		{
			bool isWithAtLeastOne = false;
			for(unsigned int j = 0 ; j< varCnt ;j++)
			{
				if(	(twoDim[rIndex][j] > 0.0) &&(isAllowedVaribles[j]))
				{
					isWithAtLeastOne = true;
				}
			}
			if(isWithAtLeastOne )
			{
				for(unsigned int j = 0 ; j< varCnt ;j++)
				{
					twoDim[rIndex +shift][j] = twoDim[rIndex ][j];
				}
				depArr[rIndex  + shift] = depArr[rIndex ] ;
			}
			else
			{
				shift--;
			}
		}
		int adjustedRegCount = regCntt + shift;
	//	actualRegSize += shift;


		bool isLogisticRegresion = true;
		double averageSE=0.0;
		double variance=0.0;
		double zeroConstant=0.0;
		double betaArr[MAX_NUM_OF_PREDICTIVE_VARIABLES];
		double tempPerformanceScore=0;
		double* predicted_dependentArr = new double[adjustedRegCount];
		double* regWeightArr = new double[adjustedRegCount];

		double meanDepVAlues = 0;
		for(int i = 0 ; i < adjustedRegCount ; i++)
		{
			meanDepVAlues += depArr[i];
		}
		meanDepVAlues /= adjustedRegCount;
		for(int i = 0 ; i < adjustedRegCount ; i++)
		{
			if(depArr[i] >  meanDepVAlues)
			{
				depArr[i]=1.0;
			}
			else
			{
				depArr[i]= 0.0;
			}
		}
	
		for(int i = 0 ; i < adjustedRegCount ; i++)
		{
			predicted_dependentArr[i] = 0.0;
			regWeightArr [i] = 1.0;
		}
		cProfileList::LinearRegressionDoubleAPIwithShifts( averageSE, variance, zeroConstant, 
				betaArr, tempPerformanceScore,predicted_dependentArr,
							twoDim,	adjustedRegCount, varCnt ,  
							depArr, regWeightArr ,   
							adjustedRegCount, false, isAllowedVaribles, isLogisticRegresion);

		for(int j = 0 ; j < varCnt ; j++)
		{
			betaArr[j] = Max(betaArr[j] , 0.0);
		}

		cSimilarityFormula temp(betaArr, varCnt);
		temp.AdjustPositiveValSum(1.0);
		for(int j = 0 ; j < varCnt ; j++)
		{
			homogenityScore[j] = temp.GetWeights()[j];
		}
		delete []predicted_dependentArr;
		delete []regWeightArr;

	}

//	delete []sdArrPerVar;
///	delete []sdPositiveDeltaPerVar;
//	delete []varWgh;
	for(int i = 0 ; i < regCntt ; i++)
	{
		delete []twoDim[i];
	}
	delete []twoDim;
	delete []depArr;
	
//	delete []isAllowedVaribles;
	//////////////////



}
*/

//2 15 18 * new two functions
//4 10 18 * updated
void cVarianceCalc::CalcalteProfileHomogenity(double &mean, double &sd,double* profileHomogenityScore, bool*  activeProfileSet, double** varWghPerProfile, float* varScores, int numOfProfiles,  int numOfVaribles)
{
//	mean=0;
//	sd=0.0;
//	double sumWghts=0.0;
	double* wghArr = new double[numOfProfiles];
	for(int ii = 0 ; ii< numOfProfiles ; ii++)
	{
		profileHomogenityScore[ii] = 0.0;
		wghArr[ii]=0.0;
		if(activeProfileSet[ii])
		{
			for(int j = 0 ; j < numOfVaribles ; j++)
			{
				if(varWghPerProfile[ii][j] > 0.0)
				{
					profileHomogenityScore[ii] +=    varScores[j];
				
				}
			}
			wghArr[ii]=1.0;
		//	sumWghts +=	wghArr[ii];
		//	mean += 	wghArr[ii]*profileHomogenityScore[ii];

		}
	}
	cVarianceCalc::CalculateMeanAndSD(mean,sd,profileHomogenityScore,wghArr,numOfProfiles);
}



//10 20 18 * new V
/*
int cVarianceCalc::GetOneRandomSelectedIndexFromActiveFlagsWithPriority(bool* arr, bool* isPriority,  int size)
{
 
	
	if(NUM_OF_TRIYING_TO_GET_SCALE < 1)
	{
		return GetOneRandomSelectedIndexFromActiveFlags( arr,   size);
	}
	int tryIndex= 0;
	int ret=-1;
	while( tryIndex++ < NUM_OF_TRIYING_TO_GET_SCALE)
	{
		
		ret = GetOneRandomSelectedIndexFromActiveFlags( arr,   size);
		if(ret >= 0)
		{
			if(isPriority[ret] )
			{
				return ret;
			}	
		}	
	}

	return ret;
}
*/



int cVarianceCalc::GetOneRandomSelectedIndexFromActiveFlags(bool* arr,  int size)
{
	int cntActive=0;
	for(int i = 0 ; i < size ; i++)
	{
		if(arr[i])
		{
			cntActive++;
		}
	}
	if(cntActive ==0)
	{
		return -1;
	}
	int* activeArr = new int[cntActive];
	int movingIndex = 0;
	for(int i = 0 ; i < size ; i++)
	{
		if(arr[i])
		{
			activeArr[movingIndex++]=i;
		}
	}
	int randVal = rand();
	int indexOfIndex = randVal % cntActive;
	int ret = activeArr[indexOfIndex];
	return ret;	

}


/*
example of read using char by char
#include <fstream>

*/

bool FileManager::ReadOneLine(char* line, ifstream &inFile, char endOfParagraphInSign)
{
	char noDelimiter = -1; //we dont use this function the same . if delimter is positive we look for 
	//string to be legal
	
	int retStatus = ReadOneLineFlexibleEndOfLine( line, inFile,endOfParagraphInSign , -1);
	if(retStatus == 1)
	{
		return true;
	}
	return false;




	line[0]=0;
	if(!(inFile.good()))
	{
		return false;
	}

	string str;
//	char abc[300];
	line[0]=0;
	if(std::getline(inFile,str))
	{
		int size = str.size();//.size;
		for(int j = 0 ; j < size ; j++)
		{
			line[j] = str[j];
		}
		line[size]=0;
		if(size > 0)
		{
			return true;
		}
		else
		{
			int ssdg=0;
		}
	}
	
	return false;
}

/*
int main()
{
   cout << "filename: ";
   string file_name;
   cin >> file_name;

   //open a file copy.out for input
   ifstream inFile(file_name.c_str() );

   if (! inFile)
   {
      cerr << "unable to open input file: "
	   << file_name << " --bailing out! \n";
      return -1;
   }

   char ch;
   while (inFile.get(ch))
      cout.put(ch);
}

*/

//10 27 22  change the legal line to get two delimiters and 
bool FileManager::IsLegalLine(char* line, char delimiter) 
{
	bool ret = false;
	int len = strlen(line);
	int indexOfDelimiter = -1;
	int delimiterCnt = 0 ;
	for(int i = 0 ; i < len ; i++)
	{
		if(line[i] == delimiter)
		{
			delimiterCnt ++;
			indexOfDelimiter = i;
		}
	}
	if(delimiterCnt == 1)
	{
		bool isLegalVAlue = true;
		bool atLeastOneDigit = false;
		for(int j = (indexOfDelimiter + 1) ; j< len ; j++)
		{
			if( (cParagraphAnalytics::IsDigit(line[j])))
			{
				atLeastOneDigit=true;
			}
			else
			{
				isLegalVAlue = false;
			}
		}
		if(isLegalVAlue && atLeastOneDigit)
		{
			ret = true;
		}
	}
	return ret;

}

//10 27 22  change the legal line to get two delimiters and 
bool FileManager::IsLegalLineWith3sections(char* line, char delimiter) 
{
	bool ret = false;
	int len = strlen(line);
//	int indexOfDelimiter = -1;
	int delimiterCnt = 0 ;
	int deliniterIndex1 = -1;
	int deliniterIndex2 = -1;


	for(int i = 0 ; i < len ; i++)
	{
		if(line[i] == delimiter)
		{
			delimiterCnt ++;
			if(deliniterIndex1 < 0)
			{
				deliniterIndex1 = i;
			}
			else
			{
				deliniterIndex2 = i;
			}
		}
	}
	if(delimiterCnt == 2)
	{
		bool isLegalVAlue = true;
		bool atLeastOneDigit = false;
		for(int j = (deliniterIndex1 + 1) ; j< deliniterIndex2 ; j++)
		{
			if( (cParagraphAnalytics::IsDigit(line[j])))
			{
				atLeastOneDigit=true;
			}
			else
			{
				isLegalVAlue = false;
			}
		}
		if(isLegalVAlue && atLeastOneDigit)
		{
			ret = true;
		}
	}
	return ret;

}

bool FileManager::WriteString(  ofstream &outFile, char* str, int len)
{
	if(!(outFile.good()))
	{
		return false;
	}
	for(int i = 0 ; i < len ; i++)
	{
		char ch = str[i];
		if(outFile.put(ch))
		{
			int sdfg=0;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/*
bool FileManager::WriteString(  ofstream &outFile, char* str)
{
	if(!(outFile.good()))
	{
		return false;
	}

	int len = strlen(str);
	itoa(len

	return true;
}*/

bool FileManager::ReadString(char* str , int len, ifstream &inFile)
{
	for(int i = 0 ; i < len ; i++)
	{
		char ch=0;
		if(inFile.get(ch))
		{
			str[i] = ch;
		}
		else
		{
			return false;
		}
	}
	str[len]=0;
	return true;
}

/*
bool FileManager::ReadString(char* str ,  ifstream &inFile)
{
	if(!(inFile.good()))
	{
		return false;
	}
	int lengthLen = 2; //we dont have strings more than 99
	bool ret = ReadString(str , lengthLen, inFile);
	int len = stoi(str);
	ret = ReadString(str , len, inFile);
	
	return true;
}
	*/
/*
bool FileManager::ReadOneBlock(unsigned char* arr,  ifstream &inFile,  int size)
{
	if(!(inFile.good()))
	{
		return false;
	}
	for(int i = 0 ; i < size ; i++)
	{
		char ch=0;
		if(inFile.get(ch))
		{
			arr[i] = (unsigned char)ch;
		}
		else
		{
			return false;
		}
	}
	return true;
}
	*/

//return 1 when ok, 0 when end of file, and -1 for ilegal line
int FileManager::ReadOneLineFlexibleEndOfLine(
	 char* line, ifstream &inFile, char endOfLineDelimiter, char delimiter)
{//function will look at the end of line delimted to mark end o parag
	//and will replace that sign delimter with a 0 NULL as end of string
	// '/n' could be found within thetext
	int retValue = -1;
	
	
	line[0]=0;
	if(!(inFile.good()))
	{
		return false;
	}

//	string str;
//	char abc[300];
	line[0]=0;
	bool endOfLine = false;
	bool endOfFile = false;
	int indexInOutLine = 0;
	while(!endOfLine && !endOfFile)
	{
		char ch=0;
		if(inFile.get(ch))
		{
			if(ch == endOfLineDelimiter)
			{
				endOfLine = true;
				line[indexInOutLine++] = 0;//end of str 
				retValue = 1;
				
				if( delimiter > 0)
				{
					bool isLEgalLine = false;
					if( IS_TWO_FIELDS_INPUT_FILE)
					{
						isLEgalLine = IsLegalLine(line, delimiter);
					}
					else
					{
						isLEgalLine = IsLegalLineWith3sections(line, delimiter);
					}
					if ( !(isLEgalLine ))
					{
						retValue = -1;
					}
				}
			}
			else
			{
				line[indexInOutLine++] = ch;
			}
		}
		else
		{
			endOfFile = true;
			retValue = 0;
		}
	}
	return retValue;
}



/*

int main()
{
   //open a file copy.out for output
   ofstream outFile("copy.out");

   if (! outFile)
   {
      cerr << "cannot open \"copy.out\" for output\n";
      return -1;
   }

   char ch;
   while (cin.get(ch))
      outFile.put(ch);
}

*/
 

bool FileManager::WriteOneLine(ofstream &outfile, char* outStr, char endOfParagraphOutSign)
{
	if(!(outfile))//.good()))
	{
		return false;
	}
	 
	int size = strlen(outStr);
	//string str;
	
	
	for(int j = 0 ; j < size ; j++)
	{
		char ch = outStr[j];
		outfile.put(ch);
	}
	char endOFParagragpLineChar = endOfParagraphOutSign;//10 11 22
	outfile.put(endOFParagragpLineChar);
	
	return true;
}



bool FileManager::WriteOneBlock(ofstream &outfile, unsigned char* outStr, int size)
{
	if(!(outfile))//.good()))
	{
		return false;
	}
	 
	for(int j = 0 ; j < size ; j++)
	{
		char ch = (char) outStr[j];
		outfile.put(ch);
	}
 
	return true;
}


void FileManager::FillExtendedFilePath(  char* extendedComunicIn, char* prefixExtension, char* inFilePath )// cGlobals &globals)
{
	char temp[300];
	strcpy(temp,prefixExtension);
//	strcpy(extendedComunicIn,prefixExtension);
	int len =strlen (temp);
	strcpy(temp + len, inFilePath);
	strcpy(	extendedComunicIn, temp);
}

	

bool FileManager::
	IsRenameReadAndWriteToComunicationFile
	(
	char* extendedComunicIn,
	char* extractedString,  char* prefixExt, cGlobals* globals, char*  patientRealTimeFilePathInn, char endOfParagInSign)
{
	//char extendedComunicIn[MAX_STRING_LENGTH];
	FillExtendedFilePath(   extendedComunicIn, prefixExt,   patientRealTimeFilePathInn);//globals.g_patientRealTimeFilePathIn );
	if(/*	Deletes the file if exists */
		rename(patientRealTimeFilePathInn, extendedComunicIn) != 0)
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
			//3 28 23 check if need to have here the input end of paragraphs 
			FileManager::ReadOneLine(extractedString, realTimeComFile, globals->g_endOfLineInSign);// (string) : "num of fields "
			realTimeComFile.close();
			ofstream outfile;
			outfile.open(extendedComunicIn,  ios::out);
			FileManager::WriteOneLine(outfile,"",globals->g_endOfLineInSign);
			outfile.close();
		//	if(/*	Deletes the file if exists */
		//	     rename(extendedComunicIn, patientRealTimeFilePathIn) != 0)
		//	{
		//		return false ;
		//	}
		//	else
		//	{
		//		int asdf =0;
		//	}
						
		}
	}
	return true;
}





int FileManager::CountFields(char* oneLine, char delimiter)// 
{
	int len = strlen(oneLine);
	int count =0;
	for (int i = 0 ; i < len ; i++)
	{
		if(oneLine[i]==delimiter)//couning how many TABs assming only tab delimited support for now
		{
			count++;
		}
	}
	count+=1; //if we count 3 TABs (for example) it means there are 4 words, so one more
	return count;
}

void FileManager::CopyFieldsFromString(double* personOneArr, char* oneLine, int numberOfVars)
{
	int ssss=0;
}

void 	FileManager::GetWordFromString(char* ward, char* strr , char delmiter)
{
	bool end = false;
	int index=0;
	while(!end)
	{
		if( (strr[index] == delmiter) || 
			//(strr[index] ==  '\n' ) || 
							(strr[index] == 0))
		{
			ward[index]= 0;
			end = true;
		}
		else
		{
			ward[index]= strr[index];
			index++;
		}
	}

}

double	FileManager::ConvertWordToDouble(char* word)
{
	std::string str = word;
	double num = std::stod(str);
	return num;
}

int	FileManager::ConvertWordToInt(char* word)
{
	double num = ConvertWordToDouble(word);
	return int(num);
}

//10 11 22 ** check if replace the '\n' with configu at the fucntion GetWordFromString
bool FileManager::ConvertDelimtedStringToFieldsArr(double*& fieldArr,
	int &numOfFieldss, char* oneLine, char delimiter )
{
	numOfFieldss=0;
	fieldArr=NULL;
	numOfFieldss = CountFields(oneLine, delimiter);//CountFields , word to double/int, 
	fieldArr= new double[numOfFieldss];
	int movingIndex= 0;
	for(int j = 0 ; j < numOfFieldss ; j++)
	{
		//fieldArr[j] = 
			char word[100];
			GetWordFromString(word, oneLine + movingIndex, delimiter);
			int len = strlen(word);
			bool isAllDigits = len>0;
			for(int l = 0 ; l < len ; l++)
			{
				bool isDigit = cParagraphAnalytics::IsDigit(word[l]);
				if(! isDigit)
				{
					isAllDigits = false;
				}
			}
			if(isAllDigits )
			{
				fieldArr[j] = 	ConvertWordToDouble(word);
			}
			else
			{
				fieldArr[j] = 999.0; //if a non digit in an input it is an error or missing varibale and i can use this value as a sign for such
			}

			if(j==COUNTRY_POS_INDEX)
			{
				fieldArr[j] = 0.0;//base for all data set
				                //if COUNTRY_CODE is selected COUNTRY_CODE
				if(strcmp(word, "CANADA_AB") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_BC") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_MB") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_NL") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_NS") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_ON") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
			}
		
			movingIndex += strlen(word);
			movingIndex++;//for the delimiter

	}
	return true;

}

bool FileManager::DownloadInputDataFile( cResearchDataObj* resarchDataObj , 
	char* inputPatientFilePAth, int depVarIndex, char endOfPAragSign, char delimiter,   cGlobals* globals)
{
	bool ret = DownloadInputDataFile(resarchDataObj->m_twoDimArray, resarchDataObj->m_depArr, 
		resarchDataObj->m_numOfItems, resarchDataObj->m_sizeOfItem,
		inputPatientFilePAth, depVarIndex, endOfPAragSign, delimiter, globals);
	return ret;
}
	

//10 8 22
bool FileManager::DownloadInputDataFile(double**& personsDataSet, double*& depArr, 
	int &numberOfPatients, int numOfVariables,char* inputPatientFilePAth,
	int depVarIndex,  char endOfPAragSign, char delimiter, cGlobals* globals)
{
	if(inputPatientFilePAth != NULL)
	{
		ifstream inFile;
		inFile.open(inputPatientFilePAth, ios::in);
		if(!(inFile.is_open()))
		{
			return false;
		}


		char oneLine[10000];
		numberOfPatients = 0;
		bool endOfFile = false;
		while(!endOfFile)
		{
			if(	FileManager::ReadOneLine(oneLine, inFile, endOfPAragSign))
			{
		 
				numberOfPatients++;
			}
			else
			{
				endOfFile =true;
			}
		}
		inFile.close();
		inFile.open(inputPatientFilePAth, ios::in);
		if(!(inFile.is_open()))
		{
			return false;
		}
		personsDataSet = new double*[numberOfPatients];

		int maxNumfLines = globals->g_PATIENT_LINES_INPUT_LIST_MAX_NUMBER;
		int mode = 1;
		if(numberOfPatients > maxNumfLines)
		{
			mode = numberOfPatients / maxNumfLines;
		}
		

	//	numberOfOrgVariables=0;
		int movingIndex = 0;
		for(int x = 0 ; x<numberOfPatients;x++)
		{
			FileManager::ReadOneLine(oneLine, inFile,endOfPAragSign);
			if( (x % mode ) == 0)
			{
				double* fieldArr = NULL;
				int numOfFieldss = 0;
				if(ConvertDelimtedStringToFieldsArr(fieldArr, numOfFieldss, oneLine ,   delimiter ))
				{
				//	numberOfOrgVariables = cVarianceCalc::Max( numOfFieldss,numberOfOrgVariables);
					if(numOfFieldss == numOfVariables)
					{
						int sssss=0; //for debug if that happens, should not happen
						personsDataSet[movingIndex] = new double[numOfVariables];
						for(int j = 0 ; j < numOfVariables ; j++)
						{
							personsDataSet[movingIndex][j] = fieldArr[j];
						}
						movingIndex++;
					}
				}	
			}
		}
		numberOfPatients = movingIndex;
		inFile.close();
	//now after one round on file to get the num of patients, and one to get the actually personsDataSet ** we are all set.
	 
		depArr = new double [numberOfPatients];	 
		for(int i = 0 ; i < numberOfPatients ; i++)
		{
			depArr[i] = 0.0;
			if(depVarIndex >= 0 && depVarIndex < numOfVariables)
			{
				depArr[i] = personsDataSet[i][depVarIndex];
			}
		}
		int movingIndex2 = 0;
		double avgg=0.0;
		for(int i = 0 ; i < numberOfPatients ; i++)
		{
			if(depArr[i] == 0.0 || depArr[i] == 1.0)
			{
				depArr[movingIndex2] = depArr[i];
				avgg   += depArr[i];
				 
				//1 11 24  move parameter to define and use also in the end when coparing two  methods
				//check that it is better. see if that helps kaing 2 recursive paraveters
				//debug theh test 4 why it falls. breakpoint here is ready when not opening et this isDataIADLdecline 
				bool isDataIADLdecline = IS_IADL_RUN_CROSSWALK;
				if( isDataIADLdecline)//78 and 79 are the most important elements and the stretch is finding so as well
				{
					if(personsDataSet[i][78] == 0.0 || personsDataSet[i][78] == 1.0)
					{
						personsDataSet[i][78] = 2.0;
					}
					if(personsDataSet[i][78] == 2.0 || personsDataSet[i][78] == 3.0  || personsDataSet[i][78] == 4.0)
					{
						personsDataSet[i][78] = 1.0;
					}
					if(personsDataSet[i][78] == 5.0 || personsDataSet[i][78] == 6.0)
					{
						personsDataSet[i][78] = 0.0;
					} 

					if(personsDataSet[i][79] == 0.0 || personsDataSet[i][79] == 1.0)
					{
						personsDataSet[i][79] = 0.0;
					}
					if(personsDataSet[i][79] == 2.0 || personsDataSet[i][79] == 3.0  || personsDataSet[i][79] == 4.0)
					{
						personsDataSet[i][79] = 1.0;
					}
					if(personsDataSet[i][79] == 5.0 || personsDataSet[i][79] == 6.0)
					{
						personsDataSet[i][79] = 2.0;
					}
				}

				for(int ss=0;ss< numOfVariables ; ss++)
				{
					if((personsDataSet[i][ss] < 0.0 ) || (personsDataSet[i][ss] > HIGHEST_VAR_VAL_ACCEPTED ))
					{
						if(personsDataSet[i][ss] == 999.0)
						{
							int sdfg=0;
						}
						else
						{
							int sdg=0;
						}
						personsDataSet[i][ss] = ILEGAL_VARIABLE_VALUE_SIGH;
					}
				}

				personsDataSet[movingIndex2] = personsDataSet[i];

				movingIndex2++;
			}
			else
			{
				int asdg=0;
			}
		}
		numberOfPatients = movingIndex2;
		avgg /= movingIndex2;
		int sdg=0;
	}

	cout<<"done with crosswalk and adjusting input file \n";
	return true;
}


/*
if(j==COUNTRY_POS_INDEX)
			{
				fieldArr[j] = 0.0;//base for all data set
				                //if COUNTRY_CODE is selected COUNTRY_CODE
				if(strcmp(word, "CANADA_AB") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_BC") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_MB") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_NL") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_NS") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
				if(strcmp(word, "CANADA_ON") == 0)
				{
					fieldArr[j] =COUNTRY_CODE;
				}
			}
			
*/


bool FileManager::DownloadPersonTwoDimFile(
	//double**& personsDataSet,
	cGlobals &globalss,
	bool*& isPredictiveVar, 
	//double*& depArr,
	int &numberOfOrgVariabless ,	int &depVarIndex ,
	//	int &numberOfPatients ,
		
		cVariableAndValueAndPoints*& regresValueWeightsArr, int &numOfRegreWeightElements,	
		cVariableAndValue*&  guidedInclusionsRuleList, 	int &guidedInclusionRuleListSize,
			int &numberOfIntervention,
			int*& indexOfInterventionField,
			int*& indexOfPropoensityCorresField,
			bool*& isInterventionVarArray, int*& indexOfPropCoresVar)//,
 
		//char* inputMetaFilePathh , char endOfPAragSignn,  char delimiterr)
{

	///get metadata  num of varibels, position of depentnat, positionged of predictive varibles
	char endOfLineSign = '\n';
	ifstream metaInFile;
	metaInFile.open(globalss.g_metaFilePath, ios::in);
	if(!(metaInFile.is_open()))
	{
		return false;
	}
	char meatLine[1000];
	//number of fields extraction
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);// (string) : "num of fields "
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);// (value) : the number of fields (in integer form)
	numberOfOrgVariabless =  ConvertWordToInt(meatLine);//(conversion) assuming (temporary until an 
	     //exml version) that the line is only dedicated for one word which is this. 

	//depenent varible figures
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(string) : "dependenet variable index"
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(value)  index of dependent field ( integer )
	depVarIndex =  ConvertWordToInt(meatLine); //conversion of string to integer

	//predeictive fields figures
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(string) : "predictive fields indexes" 
	FileManager::ReadOneLine(meatLine, metaInFile, endOfLineSign);//(value) 
	//(value) : list of indexes that host predictive variables according to the designer. 
		//the list is a sub set of all indexes in the file

	int numOfPRedIndexes = 0;
	double* predIndexArray = NULL;//consider replacing with a new functin thay does the sane with int in addition to this one for double
	ConvertDelimtedStringToFieldsArr(predIndexArray, numOfPRedIndexes, meatLine,
												globalss.g_delimiter);

	isPredictiveVar = new bool [numberOfOrgVariabless];
	for(int j = 0 ; j < numberOfOrgVariabless ; j++)
	{
		isPredictiveVar[j] = false;
	}
	for(int x = 0 ; x < numOfPRedIndexes ; x++)
	{
		int index = int(predIndexArray[x]);
		isPredictiveVar[index] = true;
	}
	delete []predIndexArray;
	predIndexArray=NULL;


	//44556
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(string) : "number of regression elements"
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(value)
	numOfRegreWeightElements = ConvertWordToInt(meatLine);
	regresValueWeightsArr = NULL;
	if(numOfRegreWeightElements > 0)
	{
		regresValueWeightsArr= 	new cVariableAndValueAndPoints[numOfRegreWeightElements];
		FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(string) : "regression elements"
		for(int i = 0 ; i < numOfRegreWeightElements ; i++)
		{
			FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(value): one line with variable index / variable value/ reg weight 
			int numOfLineElements = 0;
			double* elementArray = NULL;
			ConvertDelimtedStringToFieldsArr(elementArray, numOfLineElements, meatLine ,  
				globalss.g_delimiter);
			regresValueWeightsArr[i].CopyVarValPointElementsFromElementArray(
				elementArray , numOfLineElements);
		
			if(elementArray!= NULL)
			{
				delete []elementArray;
				elementArray=NULL;
			}
		}
	}
	FileManager::ReadOneLine(meatLine, metaInFile , endOfLineSign);//(string) : "number of single elements for profie inclusion"
	FileManager::ReadOneLine(meatLine, metaInFile, endOfLineSign);//(value)
	guidedInclusionRuleListSize = ConvertWordToInt(meatLine);
	guidedInclusionsRuleList = NULL;
	if(guidedInclusionRuleListSize >0)
	{
		guidedInclusionsRuleList=new cVariableAndValue[guidedInclusionRuleListSize];
	}
	//twe text lines
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(string) : " "
	FileManager::ReadOneLine(meatLine, metaInFile, endOfLineSign);//(string) : " "
	
	for(int i = 0 ; i < guidedInclusionRuleListSize ; i++)
	{
		FileManager::ReadOneLine(meatLine, metaInFile, endOfLineSign);//(value): one line with variable index / variable value/ reg weight 
		int numOfLineElements = 0;
		double* elementArray = NULL;
		ConvertDelimtedStringToFieldsArr(elementArray, numOfLineElements, meatLine,
			globalss.g_delimiter);
		guidedInclusionsRuleList[i].CopyVarValElementsFromElementArray(
			elementArray, numOfLineElements);
	//	cVariableAndValue*&  guidedInclusionsRuleList, 	int &guidedInclusionRuleListSize,
		delete []elementArray;
		elementArray=NULL;
	}
	//number of intervention fields
	FileManager::ReadOneLine(meatLine, metaInFile, endOfLineSign);//(string) : " "
	//actual number
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//
	

//	int numberOfIntervention = ConvertWordToInt(meatLine);//	int* indexOfInterventionField indexOfPropoensityCorresField
	numberOfIntervention = 0;
	indexOfInterventionField = NULL;
	indexOfPropoensityCorresField = NULL;
	isInterventionVarArray = NULL;
	indexOfPropCoresVar = NULL;

//12 2 22 move to be output of this function	
	numberOfIntervention = ConvertWordToInt(meatLine);//	int* indexOfInterventionField indexOfPropoensityCorresField
	isInterventionVarArray = new bool[numberOfOrgVariabless];
	indexOfPropCoresVar = new int[numberOfOrgVariabless];
	for(int z = 0 ; z< numberOfOrgVariabless ; z++)
	{
		isInterventionVarArray [z] = false;
		indexOfPropCoresVar[z] = -1;
	}
	
	FileManager::ReadOneLine(meatLine, metaInFile, endOfLineSign);//(value): one line with variable index / variable value/ reg weight 
	if(numberOfIntervention >0)
	{
		indexOfInterventionField = new int[numberOfIntervention];
		indexOfPropoensityCorresField = new int[numberOfIntervention];
		//text lilne
		for(int i = 0 ; i < numberOfIntervention ; i++)
		{
			//line by line number input
			FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//(value): one line with variable index / variable value/ reg weight 
			int numOfLineElements = 0;
			double* elementArray = NULL;
			ConvertDelimtedStringToFieldsArr(elementArray, numOfLineElements, meatLine,
				globalss.g_delimiter);
			indexOfInterventionField[i] = elementArray[0];//3 3 23 *** warninig - waht is the intetntion
			indexOfPropoensityCorresField[i] = elementArray[1];
			delete []elementArray;
			elementArray = NULL;
		}
		for(int z = 0 ; z< numberOfOrgVariabless ; z++)
		{
			for(int w= 0 ; w < numberOfIntervention ; w++)
			{
				if(indexOfInterventionField[w] == z)
				{
					isInterventionVarArray [z] = true;
					indexOfPropCoresVar[indexOfPropoensityCorresField[w]] = z;//if intervention is index / var position 5, and propensity 6, 
					//                      than in the two dim array var 5 is a 0/1 flag for intervetnion and var 6 per patient has the index 5
					//                       in the meta data objet and per patinet we have the 0-1 range popensity value
				}
			}		 
		}
	}

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_isToEnterRealTimeEndlessLoop = meatLine[0];
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_isToConductPerformanceTests  = meatLine[0];

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_profileBuildMode  = meatLine[0];

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_patientLearningFilePAth, meatLine);

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_patientCalibrationFilePath, meatLine); 

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_patientTestFilePath, meatLine); 

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_readwriteArraFlex, meatLine); 


	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_performanceReportFilePath, meatLine); 

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_patientRealTimeFilePathIn, meatLine); 
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	strcpy(globalss.g_patientRealTimeFolderPathOut, meatLine); 
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE = stoi(meatLine);//200
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_THRESHOLD_FOR_MIN_BUCKET_WEIGHTED_SIZE = stoi(meatLine);//


	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_NUMBER_OF_CALIBRATION_GRPS = stoi(meatLine);//






	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	globalss.g_MIN_SIZE_OF_CATEG_FOR_STRETCH = stoi(meatLine);//
		
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string lf value
	int stretchTestMode = stoi(meatLine);//
	if(stretchTestMode == 0)
	{
		globalss.g_IS_WITH_LONG_STRETCH_PERF_PROCESS = false;
	}
	else
	{
		globalss.g_IS_WITH_LONG_STRETCH_PERF_PROCESS = true;
	}

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text - maximum number of input lines
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale- maximum number of input lines
	globalss.g_PATIENT_LINES_INPUT_LIST_MAX_NUMBER = stoi(meatLine);//
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text - maximum number of evolution iterations
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale- maximum number of evolution iterations
	globalss.g_MAX_NUM_OF_ITERATIONS = stoi(meatLine);//
	
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//when building profiles how many new inclusuion rules/levels max 
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale-  
	globalss.g_MAX_LEVELS_IN_PROFILING_EVOLUTION = stoi(meatLine);//
	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of text - g_sizeAndUpToKeepREcursives
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale- maximum number of evolution iterations
	globalss.g_sizeAndUpToKeepREcursive = stoi(meatLine);//

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//text - below this size we DONT go recursive but stop 
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale- maximum number of evolution iterations
	globalss.g_minSampleToContinueRecursive = stoi(meatLine);//

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//text - above this number we DONT continue recusrive but go to profiles 
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale-  
	globalss.g_maxNumOfLevelsToContinueRecursive = stoi(meatLine);//

	
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//evolution recur - max num of preditive variables to try and fork 
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale-  
	globalss.g_capOfForkingPredictiveRecursive = stoi(meatLine);//

	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//recursive level with no more forking 
	FileManager::ReadOneLine(meatLine, metaInFile,endOfLineSign);//string of vale-  
	globalss.g_highestRecurSiveLevelWithFork = stoi(meatLine);//
 

	 
	 

	int ssss=0;

	metaInFile.close();
 	return true;
}


cHashObject::cHashObject()
{
	m_numOfHits=0;
	m_sumOfValues=0;
	m_sumSqrValues=0;
	m_isSig = false;
	m_hashStrChainObj = NULL;
}
cHashObject::~cHashObject()
{
	if(m_hashStrChainObj != NULL)
	{
		delete m_hashStrChainObj;
		m_hashStrChainObj = NULL;
	}
}

bool cHashObject::IsStrFoundAlongChain(cHashStrChainObj*&  matchedObj,  char* str)
	{
		matchedObj = NULL;
		cHashStrChainObj* tempChainObj = NULL;
		if( m_hashStrChainObj != NULL && m_hashStrChainObj->IsStrFoundAlongChainRecursive(tempChainObj, str) )
		{
			matchedObj = tempChainObj;
			return true;
		}
		return false;
		
	}
	void cHashObject::CreateNewChainElement(char* str , char value)
	{
	//
		cHashStrChainObj* newElement = new cHashStrChainObj();
		newElement->Initialize(str,value);
		cHashStrChainObj* temp = m_hashStrChainObj;
		m_hashStrChainObj = newElement;
		newElement->m_next = temp;
	}

	void cHashObject::AddStr(char* str, char value)
	{
		cHashStrChainObj* matchedObj = NULL;
		if(IsStrFoundAlongChain(matchedObj,   str))
		{
			matchedObj->AddStrAppearance(  value);
		}
		else
		{
			CreateNewChainElement( str , value);
		}		 
	}

	void cHashObject::CalcAvgAndSD (double &mean, double &sd)
	{
		mean = sd = 0.0;
		if(m_numOfHits > 0)
		{
			mean = double(m_sumOfValues) /  double(m_numOfHits);
			double variavce =    (  double(m_sumSqrValues) / double(m_numOfHits)  )    -      (mean * mean);
			sd = pow(variavce, 0.5);
		}
		
	}

	 



cHashObjectArray::cHashObjectArray(int size, int initialHashSize)
{
	m_size = size;
	m_arr = new cHashObject[m_size];
	m_sizeOfInitialHash = initialHashSize;
	m_initialArr= new int[m_sizeOfInitialHash];
	for(int i = 0 ; i < m_sizeOfInitialHash ; i++)
	{
		m_initialArr[i]=0;
	}
	m_totalNumOfInitialSubstrings=0;
	//m_numOfParagraphss=0;
	m_numOfParagraphs=0;

}
cHashObjectArray::~cHashObjectArray()
	{
		if(	m_arr)
		{
			delete []m_arr;
		}
	}
//11 1 22  - change return value to be "unsigned int". 
//         - create a convertion to "unsigned int" for both the "hash" and the "hashSize", talk with each other and with the ret val
unsigned int cHashObjectArray::Hashfunction(char* str,  int hashSize)
{
	unsigned long seed = 131; 
	unsigned long hash = 0;
	int len = strlen(str);
	for(int i = 0; i < len ; i++)
	{
		hash = (hash * seed) + ((unsigned long )str[i]);
	}
	return ((unsigned int)hash)  %  ((unsigned int)hashSize);
}

int cHashObjectArray::GetstringSampleBucketNum(char* str)
{
	unsigned int hashIndexInitial = Hashfunction(str, m_sizeOfInitialHash);
	int ret = m_initialArr[hashIndexInitial];
	return ret;
}

void cHashObjectArray::Push( char* str, char value, int pushMode )
{
	int debugStr = 0;
	if(cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr("Patient Isolation Status",str) )
	{
		int sdfg = 0 ;
	}
	if(cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr(
		"Patient Isolation Status\nIsolation",str) )
	{
		int sdfg = 0 ;
		if(str[0] == 'P')
		{
			int sfgg=0;
			debugStr=1;
		}
	}//Ht: 1.778 m (
	if(cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr(
		"Ht: 1.778 m (",str) )
	{
		int sdfg = 0 ;
		if(str[0] == 'H')
		{
			int sfgg=0;
			debugStr=1;
		}
	}

	if(pushMode == 0)
	{//11 1 22 change int to unsigned int. potentially change m_sizeOfInitialHash to also be unsigned int
		unsigned int hashIndexInitial = Hashfunction(str, m_sizeOfInitialHash);
		m_initialArr[hashIndexInitial]++;//46721067  
	}
	else if(pushMode == 1)
	{//11 1 22 int to unsigned int
		if(debugStr ==1)
		{
			int sdg =0;
		}
		unsigned int hashIndexInitial = Hashfunction(str, m_sizeOfInitialHash);
		if(m_initialArr[hashIndexInitial] < (m_numOfParagraphs * FREQUENT_SUBSTRING_PERC) && (m_initialArr[hashIndexInitial] > MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN)) 
		{//11 1 22 int to unsigned int
			unsigned int hashIndex = Hashfunction(str, m_size);
			m_arr[hashIndex].Add(value);
		}
		else
		{
			int neverHere=0;//see which words come here if any
		}
	}
	else
	{//11 1 22 unsigned 
		if(debugStr ==1)
		{
			int sdg =0;
		}
		unsigned int hashIndex = Hashfunction(str, m_size);
		if(hashIndex == 12810)
		{
			int sdff=0;
		}
		if(m_arr[hashIndex].m_isSig)
		{
			m_arr[hashIndex].AddStr(str, value);//hash obj has a ptr to a list of strings and values, need to open or add str and adjut its histogram
		}
	}
}
void cHashObjectArray::CalcualteSignificance(double universMean, double universSD)
	{
		double overallAvg = 0.0;
		double overallSD = 0.0;
		for(int i = 0 ; i < m_size ; i++)
		{
			if(m_arr[i].m_numOfHits > MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN)
			{
				double avg = 0.0;
				double sd = 0.0;
				m_arr[i].CalcAvgAndSD (avg, sd);
				if( cHashStrChainObj::IsPAtternAssociationMeanAndSDsignifciantLocal(avg, sd, universMean,  universSD))
					//cVarianceCalc::IsPAtternAssociationMeanAndSDsignifciant(avg, sd, universMean,  universSD))
				{
					m_arr[i].m_isSig= true;
				}
			}
		}
	}


void cHashObjectArray::ExtractPointersOfSignificantHashChainObjects(cHashStrChainObj**& sigHashChainObjs, int &numOfObjects ,cGlobals *globals)
{
	
	int numOfMaybeSignStrings =0;
	int tempSize = 50000;
	cHashStrChainObj** sigHashChainObjsTest = new cHashStrChainObj*[tempSize];//50,000 is large enough in case we found many
	for(int i = 0 ; i < tempSize ; i++)
	{
		sigHashChainObjsTest[i]=NULL;
	}
	numOfObjects = 0;//output parametre
	int foundStrCnter = 0;//temporary counter need to be set to numOfObject for output at the end
	for(int i = 0 ; i < m_size ; i++)
	{
		if(m_arr[i].m_isSig)
		{
			numOfMaybeSignStrings++; //how many passed just the primilarry short cut hash test. btw i can open it to be allow more since we dont have timing issue
		//	cout<<numOfMaybeSignStrings;
		//	cout<<'\n';
			if(m_arr[i].m_hashStrChainObj != NULL)
			{
				int cnt = m_arr[i].m_hashStrChainObj->CountSignificantChainObjsRec(sigHashChainObjsTest, foundStrCnter, globals);
				if(cnt > 1)
				{
					int sdsf=0;
				}
				numOfObjects += cnt;
				if(numOfObjects != foundStrCnter)
				{
					int ssdg=0;
				}
				if(numOfObjects > foundStrCnter)
				{
					int ss=0;
				}
				if(foundStrCnter == 100 || foundStrCnter == 500)
				{
					int sdg = 0 ;
				}
			}
		}
	}
	if(numOfObjects != foundStrCnter)
	{
		int ssdg=0;
	}
	
	sigHashChainObjs = sigHashChainObjsTest;//		NULL;
	numOfObjects = foundStrCnter;
 
}





	cHashStrChainObj::~cHashStrChainObj()
	{
		if(m_str != NULL)
		{
			delete []m_str;
			m_str=NULL;
		}
		if(m_hist != NULL)
		{
			delete m_hist;
		}
		if(m_next != NULL)
		{
			delete m_next;
		}
	}
	void cHashStrChainObj::Initialize(char* str,  char value)
	{
		m_next=NULL;
		m_strSize = strlen(str) + 1;
		m_str = new char[m_strSize];
		strcpy(m_str,str);
		m_hist = new cHistogram();
		m_hist->AddValue(value);
	}
	void cHashStrChainObj::AddStrAppearance(  char value)
	{
		m_hist->AddValue(value);
	}

	/*
	void cHashStrChainObj::AddPointersToSignifantObjectsRec(	cHashStrChainObj** sigHashChainObjs, int &indexInOutArray, cGlobals* globals)
		//double universeMean,  double universSD)
	{
		if(m_next)
		{
			AddPointersToSignifantObjectsRec(	sigHashChainObjs, indexInOutArray, globals);
		}
		char pattern=-1;
		int cnt=0;
		double percFromAll=0.0;

		//10 21 22 take these two lines and make it one with flexible o ption to look at mean and sd as now or even  histoggram for close values
		bool isValueFound = m_hist->GetMostLi kelyValue( pattern,  cnt,  percFromAll);
		if(isValueFound && IsSignificantStringLink(pattern,  cnt,  percFromAll,  globals->m_meanDepValue,  globals->m_sdDepValue))
		{
			sigHashChainObjs[indexInOutArray++]=this;
		}
	}	*/
	
	int cHashStrChainObj::CountSignificantChainObjsRec(cHashStrChainObj** sigHashChainObjsTest, int &testCoiunter, 	cGlobals* globals)
	{
		
		int retCount = 0;
		if(m_next)
		{
			retCount = m_next->CountSignificantChainObjsRec(sigHashChainObjsTest, testCoiunter, globals);
		}
		
		char pattern=-1;
		int cnt=0;
		double percFromAll=0.0;

//10 21 22 also here replace these two lines with an upgrade of getting not the most liely but the entire h istogram put side by side with the global one
		//m_hist->GetMo stLikelyValue( pattern,  cnt,  percFromAll);//10 21 22 calcalte a  more flexible perc with near by
		//if(IsSignificantStringLink(pattern,  cnt,  percFromAll,  globals->m_meanDepValue ,globals->m_sdDepValue))
		m_hist->Sort();
		if(IsSignificantStringLinkNew(globals))
		{
			retCount++;
			sigHashChainObjsTest[testCoiunter++]=this;
		}


		return  retCount;
	}

	//double mean = 0.0;
	//	double sd = 0.0;
	//	m_hist->CalulcateWeightedMeanAndSD(mean, sd);

	//10 24 22 //instead of globals send the new version of hist and of sd and remvoe globals at all from input
	double cHashStrChainObj::CalculateOddRatioHistogram(
		double &percFromAll , int &sumCnts, cHistogram* globalHist )
	{
		double meanGlobalHistogram = 0.0;
		double sdGlobalHistogram = 0.0;
		globalHist->CalulcateWeightedMeanAndSD(meanGlobalHistogram, sdGlobalHistogram);

		char pattern=-1;
		int cnt=0;
		percFromAll=0.0;
		m_hist->GetMostLikelyValue( pattern,  cnt,  percFromAll, globalHist);//10 21 22 calcalte a  more flexible perc with near by
		if(cnt == 0)
		{
			return 1.0;//odd ratio 1.0 has nutural meaning
		}
		double sumZgap = 0.0;
		double sumZgapsGlobal = 0.0;
		double sumWhts = 0.0;
		double sumWghtsGlobals = 0.0;
		sumCnts = 0;
		int sumCntsGlobal=0;
		for(int i = 0 ; i < m_hist->m_currentSize ; i++)
		{
			double val = m_hist->m_valArr[i];
			double wgh = double( m_hist->m_cntArr[i]);
			sumCnts +=  m_hist->m_cntArr[i];
			double gap = cVarianceCalc::Abs( (double(pattern)) - val);
			double zGap = 0.0;
			if(sdGlobalHistogram > 0.0)
			//	globals->m_sdDepValue > 0.0)
			{
				zGap = 	gap / sdGlobalHistogram;// globals->m_sdDepValue;
			}
			sumZgap += (wgh * zGap);
			sumWhts += wgh;
		}
		double avgSDgaps = sumZgap / sumWhts;
			
		for(int i = 0 ; i < globalHist->m_currentSize ; i++)
		{
			double val = globalHist->m_valArr[i];
			double wgh = double( globalHist->m_cntArr[i]);
			sumCntsGlobal +=  globalHist->m_cntArr[i];
			double gap = cVarianceCalc::Abs( (double(pattern)) - val);
			double zGap = 0.0;
			if(sdGlobalHistogram > 0.0)
			{
				zGap = 	gap /sdGlobalHistogram;
					//globals->m_sdDepValue;
			}
			sumZgapsGlobal += (wgh * zGap);
			sumWghtsGlobals += wgh;
		}
		double avgSDgapsGlobal = sumZgapsGlobal / sumWghtsGlobals;
		//bool isCentered = false;
		double oddRatio = avgSDgaps / avgSDgapsGlobal ;
		return oddRatio;
	}



	bool cHashStrChainObj::IsDangerousStringAsPAttern(cGlobals* globals)
	{
		int strLen = strlen(m_str);
		bool ret = false;
		if(strLen < 8)
		{
			ret = true;
		}
		int letterCnt = 0;
		int spaceCnt = 0;
		for(int i = 0 ; i < strLen ; i++)
		{
			if(cParagraphAnalytics::IsLetter( m_str[i]))
			{
				letterCnt++;
			}
			if(m_str[i] == ' ')
			{
				spaceCnt++;
			}
		}
		if(letterCnt == 0)
		{
			ret = true;//if not letter than only signs or digits may be out of the scope of desired patterns and can be "dangrous"
		}
		if(  ( letterCnt  )  == strLen)
		{
			ret = true;//that is for example a case of only letter  - one word, no spaces, etc. need to add a case of a word and spaces before or in the end with only one word after.
			//of larger strings of multi words or signs, etc
		}
		return ret;
	}
	
	//10 24 22 
	bool cHashStrChainObj::IsSignificantStringLinkNew( cGlobals* globals )
	{
		 
		double percFromAll =0.0;
		int sumCnts=0;
		double oddRatioo = CalculateOddRatioHistogram( percFromAll, sumCnts, globals->m_globHistWithSizeConsid );
		bool isCentered=false;
		if( oddRatioo < STRONG_ODD_RATIO_FOR_PATTERN_TO_BYPASS)
		{
			if(percFromAll > MIN_PERC_OF_APPEARENCE)
			{
				isCentered = true;
			}
		}
		if(oddRatioo < MIN_ODD_RATIO_FOR_PATTERN_TO_BYPASS)
		{
			if(percFromAll > STRONG_PERC_OF_APPERANCE  )
			{
				isCentered = true;
			}
		}

		if(IS_TO_REMOVE_DANGEROUS_STRINGS && IsDangerousStringAsPAttern(globals))
		{
			if((sumCnts < 200 ) || (percFromAll < 0.98) || (oddRatioo >  STRONG_ODD_RATIO_FOR_PATTERN_TO_BYPASS))
			{
				isCentered = false;
			}
		}


		//11 7 22 DEBUG SPECIFIC PROBLEMATIC STRINGS
		if(true)//isCentered)  //11 8 22 
		{
			int cnttt=0;
			int strLEn = strlen(m_str);

			if(cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr("Droplet Isolation",m_str) )
			{
				int sss=0;
			}
			if(cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr("Patient Isolation Status",m_str) )
			{
				int sss=0;
			}
			if(cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr("Isolation",m_str) )
			{
				int sss=0;
			}
			
			if(true)//strLEn > 16 && strLEn < 21)
			{
				for(int i = 0 ; i < (int)(strlen(m_str) ); i++)
				{
					if(m_str[i]== ')')
					{
						cnttt++;
					}
					if(m_str[i]== 'P')
					{
						cnttt++;
					}
					if(m_str[i]== 'r')
					{
						cnttt++;
					}
					if(m_str[i]== 'i')
					{
						cnttt++;
					}
					if(m_str[i]== 'n')
					{
						cnttt++;
					}
					if(m_str[i]== 't')
					{
						cnttt++;
					}
					if(m_str[i]== 'e')
					{
						cnttt++;
					}
					if(m_str[i]== 'B')
					{
						cnttt++;
					}
					if(m_str[i]== 'A')
					{
						cnttt++;
					}
					if(m_str[i]== 'R')
					{
						cnttt++;
					}
					if(m_str[i]== ',')
					{
						cnttt++;
					}

				}
			}
			if(cnttt > 10)
			{
				int assdf = 0;
			}
		}


		
		
		double mean = 0.0;
		double sd = 0.0;
		m_hist->CalulcateWeightedMeanAndSD(mean, sd);
		bool isSgniicantPerMeanOrSDshift =cHashStrChainObj::IsPAtternAssociationMeanAndSDsignifciantLocal(
															mean, sd, globals->m_meanDepValue, globals->m_sdDepValue);
			//cVarianceCalc::IsPAtternAssociationMeanAndSDsignifciant(mean, sd, globals->m_meanDepValue, globals->m_sdDepValue);
			
		int sumAllObCnts = m_hist->GetTotalCount();
		if((sumAllObCnts >= MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN) && isSgniicantPerMeanOrSDshift )
		{
			if( 
				//(percFromAll > MIN_PERC_OF_APPEARENCE ) || 
				isCentered )
			{//10 21 22 add an otion to say percFromAll big enough or take the perc of near by and convert it to higher percentage
				return true;
			}
		}
	
		return false;
	}
	//STRONG_ODD_RATIO_FOR_PATTERN_TO_BYPASS 4.0
// MIN_ODD_RATIO_FOR_PATTERN_TO_BYPASS 2.5


 
	bool cHashStrChainObj::IsSignificantStringLink(char pattern,  int cnt,  double percFromAll, double universeMean, double universSD)
	{
		double mean = 0.0;
		double sd = 0.0;
		m_hist->CalulcateWeightedMeanAndSD(mean, sd);
		bool isSgniicantPerMeanOrSDshift = //cVarianceCalc::IsPAtternAssociationMeanAndSDsignifciant(mean, sd, universeMean, universSD);
				cHashStrChainObj::IsPAtternAssociationMeanAndSDsignifciantLocal(mean, sd, universeMean, universSD);
		if(cnt >= MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN && percFromAll > MIN_PERC_OF_APPEARENCE  && isSgniicantPerMeanOrSDshift)
		{//10 21 22 add an otion to say percFromAll big enough or take the perc of near by and convert it to higher percentage
			return true;
		}
		return false;
	}

	void cHashStrChainObj::PrepareString(char* outStr)
	{
		for(int i = 0 ; i < m_strSize ;i++)
		{
			outStr[i]= m_str[i];
		}
	}
	//
	//PrepareStringAndPattern(outStr2 , pattern2  , delimiter);
	void cHashStrChainObj::PrepareStringAndPattern(char* outStr,char &pattern, char delimiter,cGlobals* globals)
		//cHistogram* globalHist)
	{
		for(int i = 0 ; i < m_strSize ;i++)
		{
			outStr[i]= m_str[i];
		}
		outStr[m_strSize-1] = delimiter;

	//	char pattern= -1;
		int cnt = 0;
		double percFromAll = 0.0;
		m_hist->GetMostLikelyValue( pattern,  cnt,  percFromAll,  globals->m_globHist);
		int intPAttern = int(pattern);
		char patternStr[MAX_STRING_LENGTH];
		_itoa_s(intPAttern, patternStr, 10);
		int patternStrLen = strlen(patternStr);
		for(int  i = 0 ; i < ( patternStrLen) ;i++)
		{
			outStr[m_strSize+i] = patternStr[i];
		}
		outStr[m_strSize+patternStrLen]= 0;

	}


	
	void cHashStrChainObj::ConvertToStr(char* str, int &strLen, int num)
	{		
		char patternStr[MAX_STRING_LENGTH];
		_itoa_s(num, patternStr, 10);
		strLen = strlen(patternStr);
		for(int  i = 0 ; i < strLen ;i++)
		{
			str[i] = patternStr[i];
		}
		str[strLen]=0;
	}




	void cHashStrChainObj::PrepareStringAndPatternExtended(char* outStr,char &pattern,char delimiter,cGlobals* globals)
	{	
		for(int i = 0 ; i < m_strSize ;i++)
		{
			outStr[i]= m_str[i];
		}
		outStr[m_strSize-1] = delimiter;
		int movingIndex = m_strSize;//first char for movoign forward.
	//	char pattern= -1;
		int cnt = 0;
		double percFromAll = 0.0;
		m_hist->GetMostLikelyValue( pattern,  cnt,  percFromAll, globals->m_globHist);
		char tempStr[MAX_STRING_LENGTH];
		int tempStrLen=0;
		ConvertToStr(tempStr, tempStrLen, int(pattern));
		for(int i = 0 ;i < tempStrLen;i++)
		{
			outStr[movingIndex++]=tempStr[i];
		}
		if(!IS_TO_WRITE_HISTOGRAM_TO_FILE)
		{
			outStr[movingIndex++]=0;
		}
		else
		{//m_hist
			outStr[movingIndex++]=delimiter;
			ConvertToStr(tempStr, tempStrLen, int(cnt));
			for(int i = 0 ;i < tempStrLen;i++)
			{
				outStr[movingIndex++]=tempStr[i];
			}
			outStr[movingIndex++]=delimiter;
			ConvertToStr(tempStr, tempStrLen, int(percFromAll*100));
			for(int i = 0 ;i < tempStrLen;i++)
			{
				outStr[movingIndex++]=tempStr[i];
			}
			double percFromAll=0.0;
			int sumCnts=0;
			double oddRatio = CalculateOddRatioHistogram(percFromAll , sumCnts, globals->m_globHistWithSizeConsid );
			outStr[movingIndex++]=delimiter;
			ConvertToStr(tempStr, tempStrLen, int(oddRatio*100));
			for(int i = 0 ;i < tempStrLen;i++)
			{
				outStr[movingIndex++]=tempStr[i];
			}
			int histSize = globals->m_globHist->m_currentSize;
			for(int i = 0 ; i <  histSize ; i++)
			{
				char val = globals->m_globHist->m_valArr[i];
				outStr[movingIndex++]=delimiter;
				outStr[movingIndex++]=val;
				int cnt = m_hist->GetCountForInputValue(val);
					//globals->m_globHist->m_cntArr[i];
				outStr[movingIndex++]=delimiter;
				ConvertToStr(tempStr, tempStrLen,cnt);
				for(int i = 0 ;i < tempStrLen;i++)
				{
					outStr[movingIndex++]=tempStr[i];
				}
			}	
			outStr[movingIndex++]=0;
		}
	}

	bool cHashStrChainObj::IsStrFoundAlongChainRecursive(cHashStrChainObj*& chainObj, char* str)
	{
		bool isSameStr = !( strcmp(str ,m_str ) );
		if(isSameStr)
		{
			chainObj = this;
			return isSameStr;
		}
		else if(m_next == NULL)
		{
			return false;
		}
		else
		{
			return m_next->IsStrFoundAlongChainRecursive(chainObj,str);
		}
	}
	



cHistogram::cHistogram()
	{
		m_histMaxSize = MAX_NUMBER_OF_VALUE_PER_HISTOGRAM;
		m_currentSize=0;
		m_valArr = new char[m_histMaxSize];
		m_cntArr  = new int[m_histMaxSize];
		for(int i = 0 ; i < m_histMaxSize ; i++)
		{
			m_valArr[i] = -1;
			m_cntArr[i] = 0;
		}
	}
	cHistogram::~cHistogram()
	{
		if(m_valArr != NULL)
		{
			delete []m_valArr;
			m_valArr = NULL;
		}
		if(m_cntArr != NULL)
		{
			delete []m_cntArr;
			m_cntArr=NULL;
		}
	}
	void cHistogram::AddValue(char value)
	{
		//m_currentSize
		bool existValue = false;
		for(int i = 0 ; i < m_currentSize ; i++)
		{
			if(value == m_valArr[i])
			{
				m_cntArr[i]++;
				existValue=true;
			}
		}
		if( ! existValue)
		{
			if(m_currentSize < m_histMaxSize)
			{
				m_valArr[m_currentSize] = value;
				m_cntArr[m_currentSize] = 1;
				m_currentSize++;
			}
		}
	}

	void cHistogram::CalulcateWeightedMeanAndSD(double &mean, double &sd)
	{
		cVarianceCalc::CalculateMeanAndSD(mean, sd, m_valArr, m_cntArr, m_currentSize);
	}



	void cHistogram::Sort()
	{
		for(int i = 0 ; i <  (m_currentSize -1); i++)
		{
			int lowestValIndex = 0;
			FindLowestVal( lowestValIndex, i);
			int tempCnt = m_cntArr[i];
			char tempVal = m_valArr[i];
			m_cntArr[i] = m_cntArr[lowestValIndex];
			m_valArr[i] = m_valArr[lowestValIndex];
			m_cntArr[lowestValIndex]= tempCnt;
			m_valArr[lowestValIndex]=tempVal;

		}
	}

	void cHistogram::FindLowestVal(int &lowestValIndex, int indexToStartFrom)
	{
		lowestValIndex = indexToStartFrom;
		char lowestValue = 99;
		for(int i = indexToStartFrom ; i <  m_currentSize ; i++)
		{
			if(m_valArr[i] < lowestValue)
			{
				lowestValue = m_valArr[i];
				lowestValIndex = i;
			}
		}
		 
	}
	
	int cHistogram::GetTotalCount()
	{
		int ret = 0 ;
		for(int i = 0 ; i <  m_currentSize ; i++)
		{
			ret += m_cntArr[i];
		}
		return ret;
	}

	int cHistogram::GetCountForInputValue(char val)
	{
		int ret = 0 ; 
		for(int i = 0 ; i <  m_currentSize ; i++)
		{
			if(m_valArr[i] == val)
			{
				return m_cntArr[i];
			}
		}
		return ret;
	}


	double cHistogram::GetRateOffApperance( char val)
	{
		int cntThisval = GetCountForInputValue( val);
		int cntAll = 0;
		for(int i = 0 ; i <  m_currentSize ; i++)
		{
			cntAll += m_cntArr[i];
		}
		double ret =  ( double(cntThisval)) / (double(cntAll));
		return ret;
	}


	bool cHistogram::GetMostLikelyValue(char &pattern, int &cnt, double &percFromAll,cHistogram* globalHist)
	{
		bool ret = false;
		int totalSample=0;
		for(int i = 0 ; i < m_currentSize ; i++)
		{
			totalSample += m_cntArr[i];
		}
		double highestPerc = 0.0;
		int highestPos = 0;
		for(int i = 0 ; i < m_currentSize ; i++)
		{
			double perc = 0.0;
			if(true)
			{
				double rateOfApp = globalHist->GetRateOffApperance( m_valArr[i]);
				double rateOFREst = 1.0 - rateOfApp;
				double multiplier = rateOFREst  / rateOfApp;
				int extrapulateCnt = int (m_cntArr[i] *multiplier ) ;
				int extrapulatedTotalSample = totalSample + (extrapulateCnt - m_cntArr[i]);			
				perc = double(extrapulateCnt)/ double(extrapulatedTotalSample);
			}
			else
			{
				 perc = double(m_cntArr[i]) / double(totalSample);
			}

			if( 
				//m_cntArr[i] > MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN  &&
				perc > highestPerc)
			{
				 highestPerc = perc;
				 highestPos = i;
			}
		}
		percFromAll = highestPerc;
		int extendedCnt =  m_cntArr[highestPos];
		if(globalHist->m_currentSize >= 5)
		{
			if(highestPos > 0 )
			{
				extendedCnt += 0.33 * m_cntArr[highestPos-1];
			}
			if(highestPos < (m_currentSize-1) )
			{
				extendedCnt += ((int)(0.33 * ((double) m_cntArr[highestPos+1])));
			}
		}

		if(   (highestPerc == 0.0)  ||    (extendedCnt < MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN))
		{
			cnt=0;
			pattern = -1;
			ret = false;
		}
		else
		{
			cnt = m_cntArr[highestPos];
			pattern = m_valArr[highestPos];
			ret = true;
		}
		return ret;
	}

InputVariablesPackageForResearchObj::InputVariablesPackageForResearchObj()
	{
		m_numberOfSubGrps=0;//; //within each profile we got risk groups, cacn do a 5 or 3 
		m_profileListMaxSize =0;
		m_thresholdForTerminalProfile=0;
		m_numberOfVariables=0;
		m_isIntervention=NULL;
		m_indexOfPropIntervention=NULL;
		m_isPredictive=NULL; //personsDataSet depArr
		m_varValPointsRegWghArr = NULL; 
		m_numOfRegrEleents = 0;
		m_guidedInclusionsRuleList=NULL;
		m_guidedInclusionRuleListSize=0;
		m_numberOfIntervention=0;
		m_indexOfInterventionField=NULL;
		m_indexOfPropoensityCorresField=NULL;
	}	
	
	InputVariablesPackageForResearchObj::~InputVariablesPackageForResearchObj()
	{
		if(m_isPredictive != NULL)
		{
			delete []m_isPredictive;
		}
		if(m_isIntervention != NULL)
		{
			delete []m_isIntervention;
			m_isIntervention=NULL;
		}
		if(m_indexOfPropIntervention != NULL)
		{
			delete []m_indexOfPropIntervention;
			m_indexOfPropIntervention=NULL;		
		}

		if(m_varValPointsRegWghArr != NULL)
		{
			delete []m_varValPointsRegWghArr;
			m_varValPointsRegWghArr=NULL;
		}
		if(m_guidedInclusionsRuleList != NULL)
		{
			delete []m_guidedInclusionsRuleList;
			m_guidedInclusionsRuleList=NULL;
		}
		if( m_indexOfInterventionField!=NULL)
		{
			delete []m_indexOfInterventionField ;
			m_indexOfInterventionField=NULL;
		}
		if(m_indexOfPropoensityCorresField != NULL)
		{
			delete []m_indexOfPropoensityCorresField;
			m_indexOfPropoensityCorresField=NULL;
		}
	}

 
bool InputVariablesPackageForResearchObj::IsVarIncludes( int var)
{
	for(int i = 0 ; i < m_numOfRegrEleents ; i++)
	{
		int varI = m_varValPointsRegWghArr[i].m_variableIndex; 
		if(varI == var)
		{
			return true;
		}
	}
	//int m_numOfRegrEleents;
	return false;
}

bool InputVariablesPackageForResearchObj::IsVarVAlHasNonZeroPoints(int var,  double val)
{
	for(int i = 0 ; i < m_numOfRegrEleents ; i++)
	{
		int varI = m_varValPointsRegWghArr[i].m_variableIndex; 
		if(varI == var)
		{
			double valI = m_varValPointsRegWghArr[i].m_value;
			if(valI == val)
			{
				//now in a case with a same value
				double pnts = m_varValPointsRegWghArr[i].m_points;
				if(pnts != 0.0) //same var and same val and ponts are not 0.0 is a true
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;//this is a case with no evidene of a non zero but actually not the variable at all

}
bool InputVariablesPackageForResearchObj::IsVarHasAnyValWithNonZeroPnts( int var)
{
	for(int i = 0 ; i < m_numOfRegrEleents ; i++)
	{
		int varI = m_varValPointsRegWghArr[i].m_variableIndex; 
		if(varI == var)
		{
			//need to look at all values and if any has any points
			//so i donto care which value, if this is the vartiable, just look at the points
			double pnts = m_varValPointsRegWghArr[i].m_points;
			if(pnts != 0.0) //same var and same val and ponts are not 0.0 is a true
			{
				return true;
			}
		}
	}
	return false; //either no such varible or that all of this variable values have asociated 0 points
}


	//char* inputPatientFilePAth, 
bool InputVariablesPackageForResearchObj::PrepareMetaDataElements(
	 int &depVarIndex, cGlobals &globals)//	char* inputMetaFilePath	 , char endOfParagraphInSign, char delimiter)
{
 
	m_numberOfSubGrps =  globals.g_NUM_OF_SUB_GRPS;//
	m_profileListMaxSize =  globals.g_PROFILE_LIST_MAX_SIZE;//max number of  profiles to create eventually
	m_thresholdForTerminalProfile =  globals.g_THRESHOLD_FOR_TERMINAL_PROFILE_PER_SAMPLE_ZIZE;
	//input meta data parameters and data from files
	bool ret1 = false;
//	m_numberOfOrgVariables = 0;
	//int numOfVariables = 0;
	depVarIndex=0;

	if(	FileManager::DownloadPersonTwoDimFile(globals, m_isPredictive,  m_numberOfVariables ,	depVarIndex ,
		 	 m_varValPointsRegWghArr , m_numOfRegrEleents, 
			 m_guidedInclusionsRuleList,  m_guidedInclusionRuleListSize, 		m_numberOfIntervention,
			 m_indexOfInterventionField,		m_indexOfPropoensityCorresField,
			 m_isIntervention, m_indexOfPropIntervention))//,
			// globals.g_metaFilePath,   globals.g_endOfLineInSign,  globals.g_delimiter))
	{
		ret1 = true;
	}
	//bool ret2 = false;

	/*if(FileManager::DownloadInputDataFile(m_personsDataSet,  m_depArr, m_numberOfPatients, 
						 inputPatientFilePAth,  numOfVariables, 		 depVarIndex))
	{
		ret2 = true;
	}*/

	
	//cout<< "hello" << endl;

	/* ofstream myfile;
	 myfile.open("newFile.txt");
	 myfile << "1 2 33 5	0";
	 myfile << "1 3 44 6	0";
	 myfile << "2 2 \n3 3";

	 int rrrrrr=0;
	 myfile.close();*/
	return ret1 ;//&& ret2;

}
 

/*

cPatientRecordObject 
  
 
once distributing pargraphs into patinets list, remove paragraphs that appear more than once per patient

 

cUniverseRecords
this class also has the access to the list of patient record object and all together we can then calculate how many paragraphs and go over patients to also calculate universal histogram which is a summary of the patient objects values, each patient contributed one value and the universe has a histogram

Build Phrase Dictionary
go patient by patient, since the paragraphs are mutually exclusive, and already cleaned, and for each patient create all phrases, unique/duplicated free, 5-40 length only, and  do so for 10% of the patients, randomly. Make sure a keyword only comes once from a patient. 
The function of build phrase starts with one patient, than goes and merges all patients.
At the one patient level we just list the phrases, their paragraphr index they belong to at the patient order, where in the paragraph, and at the phrase dictionary we add to the histogram each patient value that had this phrase. 

After going ovr only 10% of patients we can know a lot about phrases to be removed from sample or sig
 
Now with less phrases we go and esstablsh a more accurate phrase scoring going over all the patients
  

Build Patient Record  objects per patient()

The action of creating a patient phrase happen again on all patients and wit smaller set of phrases. 
We here collect for each patient first the map of phrases, and then we go back and add the phrase ratio score that was calculated using all patients. Now as we already have the smaller list of phrass and we caclautte its core, we anyway extract each  phrase per person and can learn of a good strutue to hold the phrases associated with certain paragraphs. We then can score a paragraph and sort . we can also score all paragraphs.




*/

bool cParagraphAnalytics::AreSimilarPhrases(
		int &potentialUpgradePos,		char* str1, char* str2, int sample1, int sample2, 
		int pos1,	int pos2, double odd1, double odd2 , cGlobals* globals)
	{
		potentialUpgradePos=-1;
		char leftStr1[MAX_STRING_LENGTH];
		char rightStr1[MAX_STRING_LENGTH];
		BreakPhrase(leftStr1, rightStr1, str1);

		char leftStr2[MAX_STRING_LENGTH];
		char rightStr2[MAX_STRING_LENGTH];
		BreakPhrase(leftStr2, rightStr2, str2);

		bool isCoreStr1SubSetOfCorestr2 = IsLeftStrSubStringOfRightStr(leftStr1,leftStr2);
		bool isCoreStr2SubSetOfCorestr1 = IsLeftStrSubStringOfRightStr(leftStr2,leftStr1);
		bool isOneCoreSubSetOFAnother = isCoreStr1SubSetOfCorestr2 || isCoreStr2SubSetOfCorestr1;
		if(isCoreStr1SubSetOfCorestr2)
		{
			if((sample1 >= globals->g_minSampleSizeWhole) && (sample2  < globals->g_minSampleSizeWhole))
			{
				if(odd2 > odd1)
				{
					potentialUpgradePos = pos2;
				}
			}
		}
		if(isCoreStr2SubSetOfCorestr1)
		{
			if((sample2 >= globals->g_minSampleSizeWhole) && (sample1  < globals->g_minSampleSizeWhole))
			{
				if(odd1 > odd2)
				{
					potentialUpgradePos = pos1;
				}
			}
		}
		 
 
		if( 
			( isOneCoreSubSetOFAnother)		||
			 (  
			 ( rightStr1[0] != 0 ) &&  ( rightStr2[0] != 0 ) &&
			 IsOneStringsSubSetOfTheOther(  leftStr1, rightStr2)&&
				 IsOneStringsSubSetOfTheOther(  leftStr2, rightStr1)
			 )
			 )
		{
			 return true;
		}
		return false;
	}

cParagraphAnalytics::cParagraphAnalytics(char* inputFilePath, int numOfVariables, int valueFFieldIndex)
	{
		//m_paragPRedModel =NULL;

		m_paragPRedMode = NULL;



		strcpy(m_filePath, inputFilePath);
		m_numOfVars = numOfVariables;
		m_valueFieldIndex = valueFFieldIndex;

		m_paragrArray=NULL ;//= new char*[maxNumberOfParagraphs];
		m_valueArray=NULL;// = new char*[maxNumberOfParagraphs];
		m_ptIDarray=NULL;
		m_numberOfParagraphs=0;

		m_patientRecorsObjectList = NULL;
		m_maxNumberOfPatients = 0;
		m_actualyNumberOfPatients = 0;

	}


	cParagraphAnalytics::~cParagraphAnalytics()
	{
		if(m_paragrArray != NULL)
		{
			for(int i = 0 ; i < m_numberOfParagraphs ; i++)
			{
				if(m_paragrArray[i] != NULL)
				{
					delete []m_paragrArray[i];
					m_paragrArray[i]=NULL;
				}
				if(m_valueArray[i] != NULL)
				{
					delete []m_valueArray[i];
					m_valueArray[i]=NULL;
				}
				if(m_ptIDarray[i] != NULL)
				{
					delete []m_ptIDarray[i];
					m_ptIDarray[i]=NULL;
				}		
			}
			delete []m_paragrArray;
			m_paragrArray=NULL;
			delete []m_valueArray;
			m_valueArray=NULL;
			delete []m_ptIDarray;
			m_ptIDarray=NULL;
		}
		if(m_patientRecorsObjectList != NULL)
		{
			for(int i = 0 ; i < m_maxNumberOfPatients;i++)
			{
				if(m_patientRecorsObjectList[i]!= NULL)
				{
					delete []m_patientRecorsObjectList[i];
				}
			}
			delete []m_patientRecorsObjectList;
		}
	
	}


	// 3 3 23 take thet strings from hashObjArr m_phrase and see about their correlation when adding a new object with its phrase
	// then if low correlation than we can add most of that sample, or add less with higher correlation. for now assume 70 50 3 0%
	//
/*
	double cParagraphAnalytics::CalculateAverageOddForAtLEastInputSamlple( int &actualUsedSample,
		int*	posOddSampleArray, 
		double* posOddArray, cHashObj** hashObjArr, int size  , cGlobals *globals)
		//globals->g_minSampleSizeWhole;);
			
	{
		actualUsedSample=0;
		int sumSampleee = 0;
		int effectiveSumSample = 0;
		double avg = 0.0;
		double discountForPartialInfoo = 1.0;
		for(int i = 0 ; i < size ; i++)
		{
			sumSampleee += posOddSampleArray[i];
			
			int effectiveCount = posOddSampleArray[i] * discountForPartialInfoo;

			int leftSample = minRerquestedSample  - effectiveSumSample ;
			leftSample = cVarianceCalc::Max(leftSample , 0);
			effectiveCount = cVarianceCalc::Min(effectiveCount, leftSample);

			avg += effectiveCount * posOddArray[i];
			effectiveSumSample += effectiveCount;

			if(effectiveSumSample >= minRerquestedSample)
			{
				avg /= effectiveSumSample;
				actualUsedSample = effectiveSumSample;
				return avg;
			}
			discountForPartialInfoo *= 0.7;
		}
		if(effectiveSumSample > 0)
		{
			avg /= effectiveSumSample;
			actualUsedSample = effectiveSumSample;		
		}
		return avg;
	}
*/	


	bool cParagraphAnalytics::IsEligibleAsIngridient(double odd, int sample, cHashObj** obArr, int index, int size)
	{
		cHashObj* thisObj = obArr[index];

		for(int i = 0 ; i < index; i++)
		{
			char* str = 	obArr[i]->GetPhrase();
			if ( !(AreTwoStringsMutuallyExclusive( thisObj->GetPhrase() , str)))
			{
				return false;
			}
		}

		if((odd > 3 )||( sample > 50 && odd > 2.5 ) || ( sample > 80 && odd > 2) )
		{
			return true;
		}
		return false;

	
	}

	void cParagraphAnalytics::Shadow(char* shadowStr, char* str)
	{
		char temp[100];
		int len = strlen(str) ;
		int movingI = 0;
		for(int i = 0 ; i <len ; i++)
		{
			if(IsLetter(str[i]))
			{
				char ch = LowerLetter(str[i]);
				temp[movingI++] = ch;
			}
			else if(( IsDigit(str[i])) || ( str[i] == ':') )
			{
				temp[movingI++] = str[i];
			}		
		}
		temp[movingI]=0;
		shadowStr[0] = '~';
		strcpy((char*)(shadowStr+1), (char*)temp);
	}
	
	double cParagraphAnalytics::CalculateAverageOddForAtLEastInputSamlpleNew( int &indexOfMatchedObject,
		int &actualUsedSample,cHashObj*& outMatchedObj, cHashObj*&  outManualHashObj,
		int*	oddSampleArray, double* oddArray, cHashObj** hashObjArr, int size  , cGlobals *globals,
		int maxCombinedObjects,  cPhraseHash* finalHash, char* valStrr , cStringHistogram* globalHistogram)
		//globals->g_minSampleSizeWhole;);
			
	{
		actualUsedSample = 0;
		double avg = 1.0;
		outMatchedObj=NULL;
		if(maxCombinedObjects == 1)
		{
		//here i can upgraxe the list of odd array and sample array and to give some a push/upgraxe from shadown others.
			//the push will alwys be from a low samlpe to a high. that means i do not remove lower sample as much
			//but also it means that more will fall in this sample check of options 1 or options 2 with muleiple.
			//notice that when i upgrade phrase i due to other phrases IIs, i do not keep IIs alive independent but 
			//if used to updae i then hide
			
			double maxOdd = 0.0;
			int maxOddIndex = -1;
			bool isShadow = false;
			for(int i = 0 ; i < size ; i++)
			{
				int sampleItem =oddSampleArray[i];
				//3 3 23 *** add that if sample item is less than g_minSampleSizeWhole but more than the ingridient than if the obj 
				//phrase is an extended version of another one within this "size" size options that is above the whole sample, and if
				char* tempStr = hashObjArr[i]->GetPhrase();
				bool isSecondLevelOrMoreShadow = false;
				if(  (strlen(tempStr) > 2 ) && (tempStr[0] == '~') && (tempStr[1] == '~' ))
				{
					isSecondLevelOrMoreShadow = true;//4 5 23
				}
				if(
					(sampleItem >= globals->g_minSampleSizeWhole)//5 5 23  * opened the || to allow more to enter
					//now cancler this || optios .4 27 23 check again
					  //||		(	isSecondLevelOrMoreShadow &&( sampleItem >= globals->g_minSampleSizeIngridient  ))
					)
				{
					if(  oddArray[i] >    maxOdd)
					{
						maxOdd =   oddArray[i];
						maxOddIndex = i;
						isShadow = false;
						actualUsedSample = sampleItem;
						avg = oddArray[i];
						cHashObj* temp = NULL;
						if(finalHash->IsLookUp(temp , hashObjArr[i]->GetPhrase()))
						{
							outMatchedObj = temp;
						}
					}
				}
				cHashObj* temp = NULL;
				if(finalHash->IsLookUp(temp , hashObjArr[i]->GetPhrase()))
				{
					if( temp->IsManualObject(valStrr))
					{
						outManualHashObj = temp;
					}
				}
			}


			if(maxOddIndex >= 0)
			{
				indexOfMatchedObject = maxOddIndex ;
			}
		}
		else
		{
		//	int sumSampe = 0;

			for(int i = 0 ; i < size ; i++)
			{
				int sampleItem =oddSampleArray[i];
				if(sampleItem >= globals->g_minSampleSizeIngridient)
				{
					if((actualUsedSample < globals->g_minSampleSizeWhole)&&
							(	IsEligibleAsIngridient(oddArray[i],sampleItem,hashObjArr, i, size)))
					{
						avg += sampleItem * oddArray[i];
						actualUsedSample += sampleItem;
					}
				}
			}
			if(actualUsedSample >0)
			{
				avg /= actualUsedSample;
				return avg;
			}			
		}
		return avg;
	}


	//API PREDICT  PARAGRAPH RESULT
void cParagraphAnalytics::PredictParagraphResult(
	double*& predArr, double*& referanceDistriArr,char**& strValueArr ,
	cHashObj**& hashObjOut, cHashObj**& manualObjOut, double*& oddRatioArr,
	
	int &numOfValues,
	
	char** listOfParagraphOfOnePatient, int numberOFPAragraphs,
	cPhraseHash* finalPhraseHash, cGlobals* globals,  cStringHistogram* globalHistrogram)
{
	numOfValues = globalHistrogram->GetSize();



	int numberOfPatientss = 1;
	cPatientMapElements** patientMapArray = new cPatientMapElements*[numberOfPatientss];//we are predictiong here only one patinet 
	//or we can download here the patinet from the disk
	patientMapArray[0] = new cPatientMapElements(numOfValues);

	
	char valueStr[100];
	valueStr[0]=0;

	int levelOfShadow = 2;
	cPhraseHash* onePAtinetHash = new cPhraseHash(100000);
	cParagraphAnalytics::CollectPatientProfileParagraphs( patientMapArray[0],
			listOfParagraphOfOnePatient , numberOFPAragraphs,  finalPhraseHash, 
			globalHistrogram, valueStr, onePAtinetHash  , finalPhraseHash,  globals,  levelOfShadow);

	predArr = new double[numOfValues];
	referanceDistriArr = new double[numOfValues];
	strValueArr = new char*[numOfValues];
	hashObjOut = new cHashObj*[numOfValues];
	oddRatioArr = new double[numOfValues];
	manualObjOut = new cHashObj*[numOfValues];



	bool isPRedeSuccess = true;
	for(int i = 0 ; i < numOfValues ; i++)
	{
		predArr[i] = 0.0;
		referanceDistriArr[i]=0.0;
		strValueArr[i] = new char[100];
		strcpy(strValueArr[i], globalHistrogram->GetValueArr(i));
		referanceDistriArr[i] = globalHistrogram->GetCntArray()[i];

		double firstDim =0.0;
		double secondDim=0.0;
		double thirdDim = 0.0;
		double forthDim =0.0;
	 	patientMapArray[0]->FillThreeDimensions(firstDim,secondDim, thirdDim,forthDim, i);

		hashObjOut[i] = patientMapArray[0]->m_highestOddThisVarObj[i] ;
		oddRatioArr[i] =  patientMapArray[0]->m_highestOddThisValArr[i];
		manualObjOut[i] = patientMapArray[0]->m_manualObj[i];


	//see the 
		bool successPRed =  m_paragPRedMode[i]->FindScoreAndThenPredictionThreeDimensions(
			predArr[i],	firstDim,secondDim, thirdDim,forthDim,   globalHistrogram, i,   globals);
		//	FindScoreAndThenPrediction(predArr[i],
		//	firstDim,secondDim);
		if(!successPRed)
		{
			isPRedeSuccess = false;
		}
		//find for each first dima dns second dim the z score and then get the prediction
		//GetTableDims12

		 //copy from the pred model
	}
	double sumPre = 0.0;
	double sumRef = 0.0;
	for(int i = 0 ; i < numOfValues ; i++)
	{
		sumPre += predArr[i] ;
		sumRef += referanceDistriArr[i];
	}
	for(int i = 0 ; i < numOfValues ; i++)
	{
		if(sumPre > 0.0)
		{
			predArr[i] *= (1.0 / sumPre);
		}
		if(sumRef > 0.0)
		{
			referanceDistriArr[i] *= (  1.0 / sumRef );
		}
	}
	if(!isPRedeSuccess)
	{
		for(int i = 0 ; i < numOfValues ; i++)
		{
			predArr[i] = referanceDistriArr[i];
		}
	}


	delete onePAtinetHash;
	onePAtinetHash=NULL;
	delete patientMapArray[0];
	patientMapArray[0] = NULL;
	delete []patientMapArray;
	patientMapArray = NULL;
	
}
	
	//make logic so that regardless of an ovject be or not b the one we had for first and second diensino, just go over the obects and take frmo 
//	every 
	void cParagraphAnalytics::CalculateSumOfOddThirdOrForthDimensions(
		double &maxValue ,int &maxIndex,	int &potentialUpgradePosOut,
		double &sumSymOdds, double* oddArray, int* sampleArr,  
		int size , cHashObj** hashObjArr, cGlobals* globals)
	{
		maxValue = 1.0;
		maxIndex = -1;
		potentialUpgradePosOut=-1;
	//	int indexOfHighestPotentialUpgrade = -1;
		double hightestSymetricOddOfUpgrade = 0.0;
	//	double maxNeg = 0.0;
		sumSymOdds = 0.0;
		for(int s = 0 ; s < size ; s++)
		{
			if( oddArray[s] >= maxValue)
			{
				maxValue =  oddArray[s];
				maxIndex = s;
			}
			//hashObjPositiveArr[s]
			bool isSimilarToPrevious = false;//4 23 23 add only the gap of a first time an element is a sub string or extendde str than first index and for that need to add the call for "are similar phrases()" also when the odd is more and not only lelss 
			//since if it is more but the index 0 had a sub string of that it is only for us to add rthe gap. do the ame also with the negative
			double maxAddedsymetricOdd = 30.0;//just  a high number. in case it is relevant and ahs a max tha that max is a low value
			for(int dd = 0 ; dd< s ; dd++)//4 23 23 collect from all grou of sub strings the max odd and sum with another group max odd. or just lookk for a max with any sample
			{                        //if an element s 
				/* 4 27 23 have the AreSimilarPhrases or another fuction return not only one kind of is simlar note, but more.
				firt see what exactly is the defintin
				of the current similar and add one that is - is one string a sub set of another and has full sample, and the other string has
				no full sample but higher odd, than thake the higer odd object and odd to replace the first or second dimeison
				*/
				int potentialUpgradePos = -1;
				bool areSimilarPhreases =  AreSimilarPhrases(
				 	potentialUpgradePos, hashObjArr[s]->GetPhrase(),  hashObjArr[dd]->GetPhrase(),sampleArr[s],sampleArr[dd],
								s,dd, oddArray[s],oddArray[dd],  globals		);	
				if( areSimilarPhreases)
				{
					if(potentialUpgradePos >=0)
					{
						double symettric = Symetric(oddArray[potentialUpgradePos]);
						//	hightestSymetricOddOfUpgrade
						if(symettric > hightestSymetricOddOfUpgrade)
						{
							hightestSymetricOddOfUpgrade = symettric;
							potentialUpgradePosOut = potentialUpgradePos;
						}
					}
					if(    oddArray[s] <= oddArray[dd])//if dd as previoius object has higher odd and if s isi lower and is simiar to dd than 
					{
						isSimilarToPrevious = true;
					}
					else
					{
	//4 27 23 new ss has a higher odd . if the previous one dd has a higih sample the s can form a new thread of an alternatie first or second sim
						//and the output of such winner, if any, will be a new output of this fuction
					//4 24 23 chck to see that this is done right . if preioius ojbect was less it was the firs or second eimsions and if these are similar p hrpspe i want just to add the difference
						double symeetricIndexS = Symetric(oddArray[s]);
						double symeetricIndexDD = Symetric(oddArray[dd]);
						maxAddedsymetricOdd = cVarianceCalc::Min(maxAddedsymetricOdd , symeetricIndexS - symeetricIndexDD);//this is a case when the DD is the first or second object and we are adding a gap odd
					}
				}
			}
		//	double posOddd = posOddArray[s];
			if(! isSimilarToPrevious)
			{
				double symetricODd = Symetric(oddArray[s]);
				symetricODd = cVarianceCalc::Min( maxAddedsymetricOdd, symetricODd);
				sumSymOdds += symetricODd;
			}
		}
		//maxSymetricValue = Symetric( maxSymetricValue);
		//,int &maxIndex
	}
	








//4 1 23 if getting hrere from the real time or even test internal perf, extract the phrases that made the score even as part
//of shadow to color each 
void cParagraphAnalytics::CollectPatientProfileParagraphs( 
	cPatientMapElements* patientMapArray,
		char**	listOfParagraphOfOnePatient , int numberOFPAragraphs, 
		cPhraseHash* finalPhraseHash, cStringHistogram* globalHistogram, 
		char* valueStr, cPhraseHash* onePAtinetHash, cPhraseHash* finalHash, cGlobals* globals, int levelOfShadow)
{

	BuildPatientsPhraseMap(patientMapArray->m_phraseObjArray, 
			patientMapArray->m_numOfPhraseHashObjects,
			finalPhraseHash ,   globalHistogram,
			listOfParagraphOfOnePatient,numberOFPAragraphs, valueStr,  onePAtinetHash, globals, levelOfShadow);
	cHashObj* data = NULL;
	 
	int sdfg=0;
	/*
	"Isolation: Contact for MRSA"
	finalPhraseHash->IsLookUp(data, "Isolation Precautions");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions;");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions;");
	*/
	
	patientMapArray->CopyValueString(valueStr);
	for(int ii = 0 ; ii < patientMapArray->m_numOfvalues ; ii++)
	{
		patientMapArray->m_highestOddThisValArr[ii] = 0.0;
		patientMapArray->m_highestOddAnyOtherValToThisValArr[ii] = 0.0;
		patientMapArray->m_highestOddThisVarObj[ii] = NULL;
		patientMapArray->m_manualObj[ii] = NULL;
		patientMapArray->m_highestOddAnyOtherValObj[ii] = NULL;
		patientMapArray->m_highestOddSumInThisValContextArr[ii] = 0.0;
		patientMapArray->m_thirdDimArr[ii] = 0.0;
		patientMapArray->m_forthDimArr[ii] = 0.0;
	 
	}

	if(	patientMapArray->m_numOfPhraseHashObjects > 0)
	{
		for(int ii = 0 ; ii < patientMapArray->m_numOfvalues ; ii++)
		{
			char* valStrr = globalHistogram->GetValueArr(ii);
			cHashObj* highestOddObjThisVal=NULL;
			double highesstOddThisVal =0.0;
			cHashObj* highestOddObjAnyOtherVal = NULL;
			double highesstOddAnyOtherVal = 0.0;
		
			bool* isTaken = new bool[patientMapArray->m_numOfPhraseHashObjects];
			for(int t = 0 ; t < patientMapArray->m_numOfPhraseHashObjects ; t++)
			{
				isTaken[t] = false;
			}
	
			cHashObj** hashObjPositiveArr = new cHashObj*[patientMapArray->m_numOfPhraseHashObjects];
			cHashObj** hashObjNegativeArr = new cHashObj*[patientMapArray->m_numOfPhraseHashObjects];
			double* posOddArray = new double[patientMapArray->m_numOfPhraseHashObjects];
			double* negOddArray = new double[patientMapArray->m_numOfPhraseHashObjects];
			int* posOddSampleArray = new int[patientMapArray->m_numOfPhraseHashObjects];
			int* negOddSampleArray = new int[patientMapArray->m_numOfPhraseHashObjects];

			for(int s = 0 ; s < patientMapArray->m_numOfPhraseHashObjects ; s++)
			{
				hashObjPositiveArr[s] = hashObjNegativeArr[s] = NULL;
				posOddArray[s] = negOddArray[s] = 1.0;
				posOddSampleArray[s] = negOddSampleArray[s] = 0;
			}
		
			double sumSymeetricScoress = 0.0;
			int movingPos=0;
			int comulateSamplePos = 0;
			int comulativeSampleNeg = 0;
			int movingNeg=0;
			int maxNumOfIterations = 200;//4 22 23  increase since most of thse that arrive are duplications. or clearn duplications at that time inside and not outside
			//an not negative no problem
			maxNumOfIterations = cVarianceCalc::Min(maxNumOfIterations, patientMapArray->m_numOfPhraseHashObjects );
			
			for(int index = 0 ; index < maxNumOfIterations ; index++)
			{
				cHashObj* highestOddObjThisValTemp=NULL;
				double highesstOddThisValTemp =1.0;
				cHashObj* highestOddObjAnyOtherValTemp = NULL;
				double highesstOddAnyOtherValTemp = 1.0;

				cHashObj* dataa=NULL;
				finalPhraseHash->IsLookUp(dataa, "~isolationprecautionsnone");
				int bbb =0;



				int minSampleSizeForGetingInclded = globals->g_minSampleSizeWhole;
				bool isOnlyHigherLevelShadow = false;
				bool isOnlyNamualRules = false;
				if((index > 0))// && (index > (maxNumOfIterations / 3)))
				{
					minSampleSizeForGetingInclded = globals->g_minSampleSizeIngridient;
					//if(index < (maxNumOfIterations / 2))
					//{
					//	isOnlyHigherLevelShadow=true;
					//}
				//	else 
					if(index == (maxNumOfIterations-1))
					{
						isOnlyNamualRules = true;
					}
				}

				//for every interation go catch best odd obj this valStr and best otherValstr. use a minimu of small size
				//globals->g_minSampleSizeWho
				GetObjectWithHighestOddForInputStr( highestOddObjThisValTemp, 	highesstOddThisValTemp,  
			      highestOddObjAnyOtherValTemp	, 	highesstOddAnyOtherValTemp, isTaken,   valStrr,  
				  patientMapArray->m_phraseObjArray, patientMapArray->m_numOfPhraseHashObjects,  globalHistogram,
				  finalPhraseHash,  globals ,  minSampleSizeForGetingInclded, isOnlyHigherLevelShadow, isOnlyNamualRules);//globals->g_minSampleSizeIngridient));
				//add in additio to posOddArray and negavie array, for each member a samle size it coverd rom the hist
				//of the final hash object. then we complete to a first dimension an average of multipe hash objectss with
				//more than one phrase on the posiive, and same on the negavie. dont add a full sample, only sub set of it
				if(highestOddObjThisValTemp != NULL)
				{
					cHashObj* tempData = NULL;
					if(finalHash->IsLookUp(tempData,  highestOddObjThisValTemp->GetPhrase()))
					{
//3 3 23 *** if highestOddObjThisValTemp is in final hash per input phrase among the list of phrases per patient than its shadow 
//is too . the function will check if samle can be enhanced assuming that the odd is consistent
						//int shadowSample = finalHash->GetSampleSizeOfShadowObj(highestOddObjThisValTemp);
						int thisSample = tempData->GetHistTotalCnt();
						if(thisSample > 150)
						{
							int aaaa=0;
						}
						//thisSample = cVarianceCalc::Max(thisSample, shadowSample);
						comulateSamplePos += thisSample;
						posOddArray[movingPos] = highesstOddThisValTemp;
						posOddSampleArray[ movingPos] = thisSample;
						hashObjPositiveArr[movingPos] = highestOddObjThisValTemp;
						movingPos++;
					}
				}
				if(highestOddObjAnyOtherValTemp != NULL)
				{
					cHashObj* tempData = NULL;
					if(finalHash->IsLookUp(tempData,  highestOddObjAnyOtherValTemp->GetPhrase()))
					{
						//int shadowSample = finalHash->GetSampleSizeOfShadowObj(	highestOddObjAnyOtherValTemp);
						int thisSample = tempData->GetHistTotalCnt();
						//thisSample = cVarianceCalc::Max(thisSample, shadowSample);
						comulativeSampleNeg += thisSample;
						negOddArray[ movingNeg] = highesstOddAnyOtherValTemp;
						negOddSampleArray[ movingNeg] = thisSample;
						hashObjNegativeArr[movingNeg] = highestOddObjAnyOtherValTemp;
						movingNeg++;
					}
				}
			}
	//		CalculateAverageOddForAtLEastInputSamlple( int &actualUsedSample, int*	posOddSampleArray, 
	//	double* posOddArray, int size , int minRerquestedSample
			int actualUsedSamplePosOne = 0;
		//	double posOdd = CalculateAverageOddForAtLEastInputSamlple(actualUsedSamplePos,	posOddSampleArray,
			//								posOddArray, hashObjPositiveArr, movingPos, globals);//, enoughSample);

			double posOddOne = 1.0;
			cHashObj* posHashMatchedObj=NULL;//negHashMatchedObj
			cHashObj*  outManualHashObj=NULL;
			int indexMatchedFirstDim = -1;
			if(movingPos > 0)
			{
			
				double x = CalculateAverageOddForAtLEastInputSamlpleNew( 	
					      indexMatchedFirstDim,      actualUsedSamplePosOne ,posHashMatchedObj,	outManualHashObj,
					posOddSampleArray, posOddArray, hashObjPositiveArr,movingPos   , globals,1,finalHash,valStrr,  globalHistogram);
				if(x>1.0)//make sure we get a reply at all. 0 is when the fuction recurn an odd that cannot be and that is a no found sign
				{
					posOddOne = x;
				}
			}
			else
			{
				int sfg=0;
			}
			int actualUsedSamplePosGroup = 0;
			double posOdd =  posOddOne;
			int actualUsedSampleNegOne = 0 ;
			
			double negOdd = 1.0;
			double negOddOne = 1.0;
			cHashObj* negHashMatchedObj=NULL;
			cHashObj*  outManualHashObjNeg=NULL;
			int indexMatchedSecondDim = -1;
			if(movingNeg>0)
			{
				
				double x = CalculateAverageOddForAtLEastInputSamlpleNew(
					indexMatchedSecondDim, actualUsedSampleNegOne,  negHashMatchedObj,outManualHashObjNeg,
			    	negOddSampleArray, negOddArray, hashObjNegativeArr,movingNeg, globals, 1,finalHash, valStrr, globalHistogram);
				if(x > 1.0)
				{
					negOddOne = x;
				}
				else
				{
					int sdg=0;
				}
			}

			int actualUsedSampleNegGrp=0;
			negOdd = negOddOne;
			int positivePotentialUpgradePos=-1;
			int nehativePotentialUpgradePos=-1;
			double maxSymetricValuePos =0.0;
			int maxIndexPos = 0;
			double maxSymetricValueNeg =0.0;
			int maxIndexNeg = 0;	
			{
				double sumPosSym = 0.0;
				//int maxOddIndexPositiveSet = -1;
				//4 27 23 use this and the negative one to chllange the firstr and second dimensions
				CalculateSumOfOddThirdOrForthDimensions(
					 maxSymetricValuePos , maxIndexPos,
					positivePotentialUpgradePos, sumPosSym,  posOddArray, posOddSampleArray,
			     	movingPos ,  hashObjPositiveArr, globals);
				double sumNegSym = 0.0;
				CalculateSumOfOddThirdOrForthDimensions(maxSymetricValueNeg , maxIndexNeg,
					nehativePotentialUpgradePos, sumNegSym,  negOddArray, negOddSampleArray,
					movingNeg ,  hashObjNegativeArr , globals);
		
				patientMapArray->m_highestOddSumInThisValContextArr[ii] =  sumPosSym - sumNegSym;
				patientMapArray->m_thirdDimArr[ii] = sumPosSym;
				patientMapArray->m_forthDimArr[ii] = sumNegSym;
			}
			//if(maxSymetricValuePos > higestPos)
			{
				int  sdfg=0;
			}

			double largeOdd = 2.5;
			if(ii == 0)
			{
			//5 17 23	largeOdd = 4.0;
			}
			int midSample = (globals->g_minSampleSizeWhole + globals->g_minSampleSizeIngridient )/2;



			{
				int positiveUpgradePos=-1;//4 27 23 turn to the real positive first dimenison if differnet than -1
				double firstDimOdd = 0.0;
				if(positivePotentialUpgradePos >=0 )
				{
					double oddPotential = Symetric( posOddArray[positivePotentialUpgradePos]);
					double currentOdd = 0.0;
					if(	indexMatchedFirstDim >= 0)
					{
						currentOdd = Symetric( posOddArray[indexMatchedFirstDim]);
					}
					if(oddPotential > currentOdd )
					{
						positiveUpgradePos = positivePotentialUpgradePos;
						firstDimOdd = oddPotential;
						if(true)//5 17 23 b upgrade 4 27 23  remove false if proven right and also down in the negative section
						{
							posOdd =  posOddArray[positivePotentialUpgradePos];
							posHashMatchedObj =  hashObjPositiveArr [positivePotentialUpgradePos];
						}
					}
				}
				if(true) //5 17 23
				{
					double oddPosTry = posOddArray[maxIndexPos];
					if(oddPosTry > posOdd)
					{//5 17 23 see if for value we can have in the histogram which odd is good enouh for allowoing a small sample 
						if( oddPosTry > largeOdd && posOddSampleArray[maxIndexPos] > midSample)//place holder for osaying false for now
						{
							posOdd = oddPosTry;
							posHashMatchedObj =   hashObjPositiveArr [maxIndexPos];
						}
					}
				}


				int nehativeUpgradePos=-1;//4 27 23 turn to the real positive first dimenison if differnet than -1
				double secondDimOdd = 0.0;
				if(nehativePotentialUpgradePos >=0 )
				{
					double oddPotential = Symetric( negOddArray[nehativePotentialUpgradePos]);
					double currentOdd = 0.0;
					if(	indexMatchedSecondDim >= 0)
					{
						currentOdd = Symetric( negOddArray[indexMatchedSecondDim]);
					}
					if(oddPotential > currentOdd )
					{
						nehativeUpgradePos = nehativePotentialUpgradePos;
						secondDimOdd = oddPotential;
						if(true)//5 17 23 b upgrade 4 27 23  remove false if proven right  
						{
							negOdd =  negOddArray[nehativePotentialUpgradePos];
							negHashMatchedObj =  hashObjNegativeArr [nehativePotentialUpgradePos];
						}
					}
				}
				if(true)
				{
					double oddNegTry = negOddArray[maxIndexNeg];
					if(oddNegTry > negOdd)
					{//5 17 23 see if for value we can have in the histogram which odd and value and pos/neg is good enouh for
						//allowoing a small sample 
						if( oddNegTry > largeOdd && negOddSampleArray[maxIndexNeg] >midSample)//place holder for osaying false for now
						{
							negOdd = oddNegTry;
							negHashMatchedObj =   hashObjNegativeArr [maxIndexNeg];
						}
					}
				}
			}
			patientMapArray->m_highestOddThisValArr[ii] = 	Symetric(posOdd);
			patientMapArray->m_highestOddThisVarObj[ii] = posHashMatchedObj;  
			patientMapArray->m_manualObj[ii] = outManualHashObj;
			patientMapArray->m_highestOddAnyOtherValToThisValArr[ii] =  Symetric( negOdd);
			patientMapArray->m_highestOddAnyOtherValObj[ii] = negHashMatchedObj;

			delete[]isTaken;
			isTaken=NULL;
			delete [] hashObjPositiveArr  ;
			delete [] hashObjNegativeArr ;
			delete[] posOddArray ;
			delete []negOddArray 	;
			delete []posOddSampleArray;
			delete []negOddSampleArray;
		}
	}
}


 	
	
bool cParagraphAnalytics::IsLeftInputStrIsAsubSetOfRightInputStr (    char* leftStr  , char* rightStr)
{
	int strLenL = strlen(leftStr);   
	int strLenR = strlen(rightStr);  
	for(int i = 0 ; i < strLenR - strLenL + 1; i++)
	{
		if(IsExactCharectersArray(leftStr,rightStr+i,strLenL ))
		{
			return true;
		}
	}
	return false;
}


bool cParagraphAnalytics::IsExactCharectersArray(char* arr1,  char* arr2, int num )
{
	for(int i = 0 ; i < num ; i++)
	{
		if(arr1[i] != arr2[i])
		{
			return false;
		}
	}
	return true;
}
			

void cParagraphAnalytics::SortChainLinkObjectsByShorterStringsFirst( 
						cHashStrChainObj** sigHashChainObjs, int numOfObjects)
{
	int* lenArr = new int[numOfObjects];
	for(int i = 0 ; i < numOfObjects ; i++)
	{
		char str[MAX_STRING_LENGTH];
		sigHashChainObjs[i]->PrepareString(str);
		lenArr[i] = strlen(str);
	}
	for(int i = 0 ; i < numOfObjects ; i++)
	{
		int lowestIndex = cVarianceCalc::FindLowestIndexFromInputStartIndex(lenArr, numOfObjects, i);
		int tempInt = lenArr[i];
		lenArr[i] = lenArr[lowestIndex];
		lenArr[lowestIndex]=tempInt;
		cHashStrChainObj* tempObj = sigHashChainObjs[i];
		sigHashChainObjs[i] = 	sigHashChainObjs[lowestIndex];
		sigHashChainObjs[lowestIndex] = tempObj;
	}
	delete []lenArr;

}
/*
void cParagraphAnalytics::CollectPo tentialChildStringList(
	bool* isInCollectedChldrenList , int &numOfSubStrings,
	cHashStrChainObj** sigHashChainObjs, int numOfObjects, int indexStartSearch)
{
	
}
*/

/*
finding children to strI means strI is a sub set of such potential children. the function is left input a sub set of right string
needs then the parent to be on the left and to be a sub set of the children on the right, potentially. the parent is strI
*/
void cParagraphAnalytics::CollectPotentialChildStringList(bool* isInCollectedChldrenList, int &numColleted, 
		char* strI, char patternI, int cntI, double perfOfPatternI,cHashStrChainObj** sigHashChainObjs, 
		int numOfObjects, int startIndexToTry, bool* isAnOption,cHistogram* globalHist)
{
	numColleted=0;
	for(int ii = startIndexToTry ; ii < numOfObjects ;  ii++)
	{
		if(  (isAnOption == NULL ) || isAnOption[ii] )
		{
			char strC[MAX_STRING_LENGTH];
			sigHashChainObjs[ii]->PrepareString(strC);
			char patternC=-1;
			int cntC=0;
			double perfOfPatternC=0.0;
			sigHashChainObjs[ii]->m_hist->GetMostLikelyValue(patternC, cntC, perfOfPatternC, globalHist);
		
			if(  (patternI ==  patternC )  && IsLeftInputStrIsAsubSetOfRightInputStr ( strI  ,  strC))//	sigHashChainObjs[ii]->PrepareString(outStr2);
			{
				isInCollectedChldrenList[ii]=true;
				numColleted++;
			}
		}
	}
}


void cParagraphAnalytics::FindGrandChildrenList(bool* isGgranChild, int &numColletedd,
			char* strI, char patternI, int cntI, double perfOfPatternI,	cHashStrChainObj**	sigHashChainObjs, 
			int numOfObjects, bool* isInCollectedChldrenList,cGlobals* globals )
{
	for(int ii = 0 ; ii < numOfObjects ; ii++)
	{
		if(isInCollectedChldrenList[ii] && (!isGgranChild[ii]) ) // is a potential child to strI since strI was found as a sub set of it.
			//now i want to see if any other str can be a sub set of string ii and not only strI 
		{
			//if(strII is a sub string of 
			char strC[MAX_STRING_LENGTH];
			sigHashChainObjs[ii]->PrepareString(strC);
			char patternC=-1;
			int cntC=0;
			double perfOfPatternC=0.0;
			sigHashChainObjs[ii]->m_hist->GetMostLikelyValue(patternC, cntC, perfOfPatternC,  globals->m_globHist);
			bool* isInGrandChildLocalList=new bool[numOfObjects];
			for(int iii = 0 ; iii < numOfObjects ; iii++)
			{
				isInGrandChildLocalList[iii] = false;
			}
			int numCollectedGClocal = 0;	
			CollectPotentialChildStringList( isInGrandChildLocalList, numCollectedGClocal, 
				strC,  patternC, cntC, perfOfPatternC, sigHashChainObjs,  numOfObjects,  ii+1,isInCollectedChldrenList ,globals->m_globHist) ;

			if(numCollectedGClocal>0)
			{//there is one other object with a string that strC child isi a child of which makes string C a grand child
			//	isInCollectedChldrenList[ii]=false;
				for(int iii = 0 ; iii < numOfObjects ; iii++)
				{
					if(isInGrandChildLocalList[iii])//meand these iii children are childern of item ii and not only of i
					{
						//isInCollectedChldrenList[iii] = false;
						//numColleted--;
						if(isGgranChild[iii]==false)
						{
							isGgranChild[iii]= true;
							numColletedd++;
						}
					}
				}
			
			}
			delete []isInGrandChildLocalList;
		}
	}

}

int cParagraphAnalytics::CalculatehighestSumOfMutuallyExclusiceObjectsSample(
	      bool* isInCollectedChldrenList ,cHashStrChainObj**	sigHashChainObjs, int numOfObjects,cGlobals* globals)
{
	int returnSum = 0;
	
	int maxGrpSampleSize = 0;
	int indexOfMaxGrpReresent = -1;
	for(int ii = 0 ; ii < numOfObjects ; ii++)
	{
		if(isInCollectedChldrenList[ii]) // is a potential child to strI since strI was found as a sub set of it.
		{//10 16 22  change the way we design this function and call it "Find sum of mutual exclusive group including str ii
			//
			int sumOfSsampleSize =	FindSamppleSizeOfMutualuExclusiveStrGrpForInputCore( isInCollectedChldrenList,
															sigHashChainObjs, 	ii, numOfObjects, globals);
			if(sumOfSsampleSize > maxGrpSampleSize)
			{
				maxGrpSampleSize = 	sumOfSsampleSize;
				indexOfMaxGrpReresent = ii;
			}
		}
	}
	if(indexOfMaxGrpReresent >= 0)
	{
		int sumOfSsampleSize =	FindSamppleSizeOfMutualuExclusiveStrGrpForInputCore( 
			isInCollectedChldrenList, 	sigHashChainObjs, indexOfMaxGrpReresent,numOfObjects,globals);
		returnSum = sumOfSsampleSize;
	}

	
	return returnSum;
}
/*
 xy is mutually eclusive with xz since there is no string that has one x and has both xy and xz
 but  xy is not exclusie with wx or wx since we can have a string wxy that both are sub string of and do have at least one common leter
  can we takee str1 and str2 and find a way to put themm one on top of each other with at least one commong letter and that they both
 are fully inclued?



*/

bool cParagraphAnalytics::IsLeftStrOverlapRightStrFromLeftSide(char* strL, char *strR)
{
	int rLen = strlen(strR) ;
	int lLen = strlen(strL);
	for(int i = 0 ; i < rLen ; i++)//ty to cover letter 0, 0+1, 0+1+2, etc. of right string, until try to cover rLen-1 (even that it is not 
		//possible since we dont have sub set).
	{
		//cover 0 to i
		int overlappedStrlen = i+1;//for example if abc covers cxy than covered string is "c" length 1 w hich is whe i =0 
		//since we got the over lapp str lenth we know to get the tail of strL with the same size. 
		if( lLen >= overlappedStrlen) 
		{
			char* newStrL = strL + (lLen - overlappedStrlen);
			if(IsExactCharectersArray(newStrL,strR,overlappedStrlen))
			{
				return true;
			}
		}
	}
	return false;
}


bool cParagraphAnalytics::IsLeftStrOverlapRightStrFromRightSide(char* strL, char *strR)
{
	return false;
}

//the strings are mutually exclusive if they do not have any overlapp
bool cParagraphAnalytics::AreTwoStringsMutuallyExclusive(char* str1, char* str2)
{
	bool a =IsLeftStrOverlapRightStrFromLeftSide(str1, str2);
//	bool b= IsLeftStrOverlapRightStrFromRightSide(str1, str2); // 
	bool c =IsLeftStrOverlapRightStrFromLeftSide(str2, str1);
//	bool d =IsLeftStrOverlapRightStrFromRightSide(str2, str1);

	if( a || c  )//if any of these overlapp happend than not strings are not exclusive
	{
		return false;
	}
	return true;

}

int cParagraphAnalytics::FindSamppleSizeOfMutualuExclusiveStrGrpForInputCore( 
	bool* isInCollectedChldrenList,  cHashStrChainObj**	sigHashChainObjs, int	coreIndex, int numOfObjects,cGlobals* globals)
{
	bool* outGrp = new bool[numOfObjects];
	for(int g = 0 ; g < numOfObjects ; g++)
	{
		outGrp[g]=false;
	}
	 	
	int sumOfSsampleSize=0;
	for(int g = coreIndex  ; g < numOfObjects ; g++)
	{
		if(isInCollectedChldrenList[g])
		{
			char str[MAX_STRING_LENGTH];
			sigHashChainObjs[g]->PrepareString(str);
			bool isInGrp = true;
			for(int k = coreIndex ; k < g ; k++)//for core index and up , if potential child than find from core to g so that 
				//we can  propose any added string to the first and core to be allowed and when each 
			{
				if(outGrp[k])
				{
					char prevStr[MAX_STRING_LENGTH];
					sigHashChainObjs[k]->PrepareString(prevStr);
					if( ! ( AreTwoStringsMutuallyExclusive(str, prevStr)))
					{
						isInGrp = false;
					}
				}
			}
			if(isInGrp)
			{
				char pattern=-1;
				int cnt=0;
				double perfOfPattern=0.0;
				sigHashChainObjs[g]->m_hist->GetMostLikelyValue(pattern, cnt, perfOfPattern,globals->m_globHist);
				sumOfSsampleSize+=cnt;
				outGrp[g] = true;
			}
		}
	}
	delete[] outGrp;
	return sumOfSsampleSize;
}
	




	/*	char outStrI[MAX_STRING_LENGTH];
		char patternI=-1;
		int cntI=0;
		double perfOfPatternI=0.0;
		sigHashChainObjs[i]->m_hist->GetMostLikelyValue(patternI, cntI, perfOfPatternI);
		sigHashChainObjs[i]->PrepareString(outStrI);
*/

bool cParagraphAnalytics::IsLeftStrSubStringOfRightStr( char* lStr, char* rStr)
{
	bool isSubSet = false;
	int leftLen = strlen(lStr);
	int rightLen = strlen(rStr);
	for(int i = 0 ; i < rightLen ; i++)
	{
		if(     leftLen <= (rightLen-i))
		{
			if(  IsExactCharectersArray(lStr , rStr + i, leftLen))
			{
				isSubSet =  true;
			}
		}
	}
	return isSubSet;
}



//10 8 22
bool cParagraphAnalytics::WriteStringsToOutFile(char* outputFile, cHashStrChainObj** sigHashChainObjs, int numOfObjects, 
	char endOfPAragOutSignn, 	char delimiter, cGlobals* globals)
{
	ofstream outfile(outputFile);//, ios::out);
	if(!(outfile.is_open()))
	{
		return false;
	}
	
	SortChainLinkObjectsByShorterStringsFirst( sigHashChainObjs,  numOfObjects);
	bool*  isToWriteOut = new bool[numOfObjects];
	for(int i = 0 ; i < numOfObjects ; i++)
	{
		isToWriteOut[i] = true;
	}
	for(int i = 0 ; i < numOfObjects ; i++)
	{
		char outStrI[MAX_STRING_LENGTH];
		char patternI=-1;
		int cntI=0;
		double perfOfPatternI=0.0;
		sigHashChainObjs[i]->m_hist->GetMostLikelyValue(patternI, cntI, perfOfPatternI,globals->m_globHist);
		sigHashChainObjs[i]->PrepareString(outStrI);

		bool* isInCollectedChldrenList = new bool[numOfObjects];
		for(int dd=0 ; dd < numOfObjects ; dd++)
		{
			isInCollectedChldrenList[dd] = false;//still are not sub strings proved
		}
		int numOfChildCandicated = 0;
		CollectPotentialChildStringList(isInCollectedChldrenList , numOfChildCandicated,
			outStrI,patternI,cntI,perfOfPatternI,	sigHashChainObjs, numOfObjects, i+1, NULL, globals->m_globHist);
	//iput has list if indexes in the output array with how many sub strings of optential children werew found
		//output has that list of indexes filled with a smaller set and smaller numOfSubstrings 
		//the question we ask etween these two functions is collect childre and for each create
		//its own childern and keep only thoese that wer rnot hit by another parient.
		bool* isGgranChildToStrI = new bool[numOfObjects];
		for(int gr = 0 ; gr < numOfObjects ; gr++)
		{
			isGgranChildToStrI [gr] = false;
		}	 		
		int numOfGrandChildren = 0;
		FindGrandChildrenList( isGgranChildToStrI, numOfGrandChildren  ,
						outStrI,patternI,cntI,perfOfPatternI,sigHashChainObjs, numOfObjects, isInCollectedChldrenList,globals);
		for(int gr = 0 ; gr < numOfObjects ; gr++)
		{
			if(isGgranChildToStrI [gr])
			{
				if(isInCollectedChldrenList[gr])
				{
					isInCollectedChldrenList[gr] = false;
					numOfChildCandicated--;
				}
			}
		}	

		int outSumOfSsampleSize = CalculatehighestSumOfMutuallyExclusiceObjectsSample(
			isInCollectedChldrenList ,  sigHashChainObjs, numOfObjects, globals);
	
		double outSampeSizeDouble= double(outSumOfSsampleSize);
		if(outSampeSizeDouble > (((double)cntI) * PERC_THRES_EXCLUSIVE_GRP) )//if the children cover the parent I sample we take parenet out
		{
			isToWriteOut[i] = false;
		}
		else
		{
			int sdg  = 0 ;
		}
		delete []isInCollectedChldrenList;
		delete []isGgranChildToStrI ;
	}
	
	int cntToWrite =0;
	for(int i = 0 ; i < numOfObjects ; i++)
	{
		if(isToWriteOut[i])
		{
			cntToWrite++;
			char outStr[MAX_STRING_LENGTH];
			char pattern=-1;
			sigHashChainObjs[i]->PrepareStringAndPatternExtended( outStr,pattern, delimiter, globals);
		//	AdditionalStatiticalElimination
			FileManager::WriteOneLine(outfile, outStr, endOfPAragOutSignn);
		}
	}
	int yyy=0;
	delete []isToWriteOut;

	outfile.close();
	return true;
}

void  cParagraphAnalytics::ExtractPatientIDstring(char* patientIDstr, char* inputStr)
{
	int asd = 0 ;
	int indexOfLastTilda = -1 ;
	int inputStrLen = strlen(inputStr);
	for(int i = 0 ; i < inputStrLen ; i++)
	{
		if(inputStr[i] == '~')
		{
			indexOfLastTilda = i;
		}
	}
	strcpy(patientIDstr, inputStr + indexOfLastTilda + 1);
	int sdf=0;
}

void  cParagraphAnalytics::BuildPatientRecordObjects(int &maxNumberOfPatients,cPatientRecordObject**& patientRecorsObjectList,
	int &actualyNumberOfPatients,   int numberOfParagraphs, char** ptIDarray,
	    char** paragraphValueArray, char** paragrArray)
{
	maxNumberOfPatients = 1000000;
	patientRecorsObjectList  = new cPatientRecordObject*[maxNumberOfPatients];
	actualyNumberOfPatients=0;
	for(int i = 0 ; i < maxNumberOfPatients;i++)
	{
		patientRecorsObjectList[i] = NULL;
	}
	for(int p = 0 ; p < numberOfParagraphs ; p++)
	{
		char tempStr[100];
		ExtractPatientIDstring(tempStr, ptIDarray[p]);
		int ptIndex = GetExsistingOrOpenNewPatientObject(patientRecorsObjectList, actualyNumberOfPatients,tempStr);
		bool isConflictValue = patientRecorsObjectList[ptIndex]->SetValueString(paragraphValueArray[p]);
		//add this paragr to the patinet owns it, if patietn does not have it already.
		//send this paragrph
		if(!isConflictValue)
		{
			patientRecorsObjectList[ptIndex]->AddParagraphIndex( p, paragrArray);
		}
		//AddParagraphIndex(int paragIndex)
	}

}

//void cParagraphAnalytics::XXXX(int &numOfParaghs , ifstream* inFile, char endOfParagInSign, char delimiter,
//	bool isRemoveSpaces	,char**  paragrArray, char** valueArray, char** m_ptIDarray)


void cParagraphAnalytics::CollectAllParagraphs(char**  paragrArray, char** valueArray, char** ptIDarray,int &numOfParaghs ,
		ifstream* inFile, char endOfParagInSign, char delimiter, bool isRemoveSpaces		)
{

	int movingParagIndex = 0;
	bool endOfFile = false;
	while(!endOfFile)
	{
		//if(FileManager::ReadOneLine(oneLine, inFile))
		//-1 for ilegal line, 0 for end of fline, 1 for success getting a new line
		char oneFullLine[20000];
		int retValue =  FileManager::ReadOneLineFlexibleEndOfLine(oneFullLine, *inFile,   endOfParagInSign, delimiter);
		if(retValue == 1)
		{
			char* paragrStr = NULL;
			char* valueStr = NULL;//-1;
			char* ptIDstr = NULL;

			bool isExtracted = false;
		//	int patinetID = -1;
		 	isExtracted = ExtractDictionaryValueFromThreeFieldsLineNEW(paragrStr, valueStr,ptIDstr, 
				oneFullLine, delimiter ,  isRemoveSpaces);//takes one line few char shorter to end the line befoe the value.
				                                                                                          //extext the value separate 
			if(isExtracted)//ExtractDictionaryValueFromLine(value, oneLine, delimiter ,  isRemoveSpaces))//takes one line few char shorter to end the line befoe the value. extext the value separate 
			{
				paragrArray[ movingParagIndex]= paragrStr;
				valueArray[ movingParagIndex]= valueStr;
				ptIDarray[ movingParagIndex]= ptIDstr;
				movingParagIndex++;//
			}
		}
		else if(retValue == 0)
		{
			endOfFile =true;
		}
	}
	numOfParaghs = movingParagIndex;
}



bool cParagraphAnalytics::BuildArraysOfParagaphsValueAndPtID(
 char**& paragrArray , char**& valueArray , char**& ptIDarray , int &numOfParags,
	char endOfParagInSign , char delimiter,  bool isRemoveSpaces, 
	char* filePath)
{
	ifstream inFile;
	paragrArray = valueArray = ptIDarray = NULL;
	numOfParags=0;
	char tempStr[100];
	FileManager::FillExtendedFilePath(   tempStr, "prefixExt", filePath );
	
	if(
		rename(filePath,tempStr  ) != 0)
	{
		int sdg = 0 ;
				//	perror("Error renaming file"); //error
		return false;
	}
	else
	{
		
		inFile.open(tempStr, ios::in);
		if(!(inFile.is_open()))
		{
			return false;
		}
	
	
	//int numberOfSubStringssAllRun = 0;
	//bool endOfFile = false;

//3  3 23 turn these 4 param to parag analytic smembers 
		int maxNumberOfParagraphs = 1000000;
		paragrArray = new char*[maxNumberOfParagraphs];
		valueArray = new char*[maxNumberOfParagraphs];
		ptIDarray = new char*[maxNumberOfParagraphs];
		for(int i = 0 ; i < maxNumberOfParagraphs ; i++)
		{
			paragrArray[i] = valueArray[i] = ptIDarray[i] = NULL;
		}

		numOfParags = 0;
		//XXXX(m_numberOfParagraphs );
		CollectAllParagraphs(paragrArray,valueArray,ptIDarray, numOfParags,
								&inFile,  endOfParagInSign,  delimiter,  isRemoveSpaces		);
		inFile.close();

		//m_numberOfParagraphs = movingParagIndex;

	//	delete []arrayOfPatinetSubStringFlaging;
		if(
			rename(tempStr,filePath  ) != 0)
		{
			int sdg = 0 ;
				//	perror("Error renaming file"); //error
			return false;
		}
		else
		{
			int sdg = 0 ; 
		}
	}
	return true;
}




/*
bool cParagraphAnalytics::GoOverHashArrAndAct(double* lineArrr , double* strlenArr, cHashObjectArray &hashArr,
	int &actualyLineIndexx , int pushMode , char endOfParagInSign , char delimiter,  bool isRemoveSpaces)
{
	ifstream inFile;
	inFile.open(m_filePath, ios::in);
	if(!(inFile.is_open()))
	{
		return false;
	}
	
	char oneLine[20000];
	int numberOfSubStringssAllRun = 0;
	bool endOfFile = false;
	actualyLineIndexx = 0;
	//11 1 22 delete this and replace with a new class strPatienetDup. use below for the exsist question.
	cStringAndIntDupCheck strPtnDup;

	
	

	int tooSmaleOrTooLargeCnt=0;
	int setExistCnt=0;
	int isExistCnt=0;
	while(!endOfFile)
	{
		//if(FileManager::ReadOneLine(oneLine, inFile))
		//-1 for ilegal line, 0 for end of fline, 1 for success getting a new line
		int retValue =  FileManager::ReadOneLineFlexibleEndOfLine
			(oneLine, inFile,   endOfParagInSign, delimiter);
		if(retValue == 1)
		{
			char value = -1;
			bool isExtracted = false;
			int patinetID = -1;
			if(IS_TWO_FIELDS_INPUT_FILE)
			{
				isExtracted = ExtractDictionaryValueFromLine(value, oneLine, delimiter ,  isRemoveSpaces);//takes one line few char shorter to end the line befoe the value.
				                                                                                          //extext the value separate 
			}
			else
			{
				isExtracted = ExtractDictionaryValueFromThreeFieldsLine(patinetID, value, oneLine, delimiter ,  isRemoveSpaces);//takes one line few char shorter to end the line befoe the value.
				                                                                                          //extext the value separate 
			}
			if(isExtracted)//ExtractDictionaryValueFromLine(value, oneLine, delimiter ,  isRemoveSpaces))//takes one line few char shorter to end the line befoe the value. extext the value separate 
			{
				if(lineArrr != NULL)
				{
					int strLen = strlen(oneLine);
					strlenArr[actualyLineIndexx] = strLen;
					lineArrr[actualyLineIndexx]= double(value);
				}
				actualyLineIndexx++;
				char** stss = NULL;
				int* posStartArr=NULL;
				int* lenArr = NULL;
				int numOfSubStrsOnePAragraph = 0;
				CalculateMultipleSubStrings( stss, posStartArr, lenArr, numOfSubStrsOnePAragraph, oneLine ,  globals);
				if(stss != NULL)
				{
					for(int x = 0 ; x < numOfSubStrsOnePAragraph; x++)
					{
						bool isToPush = true;
						if( (( pushMode == 1) || (pushMode == 2) ) && (!IS_TWO_FIELDS_INPUT_FILE) && (patinetID >= 0  )) //that menas we have the thrid field patinet Id to remove sub strin duplications
						{//11 1 22 change to a class function return exist or not wih the iput of the string and patient id. do not modify the patient id frmo befoer
							bool isExist = strPtnDup.IsExist(stss[x],patinetID);
						 	if(isExist)// || isStringWithTooSmallSample )
							{
								isToPush = false;
								isExistCnt++;
							}
							else
							{
								bool isStringWithTooSmallSample = ( hashArr.GetstringSampleBucketNum(stss[x]) < MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN) ;
								bool isStringWithTooLargeSample = ( hashArr.GetstringSampleBucketNum(stss[x]) > MAX_SAMPLE_TO_CARE_FOR_SAME_PT_DUP) ;
								if(isStringWithTooSmallSample || isStringWithTooLargeSample)
								{
									tooSmaleOrTooLargeCnt++;//setExistCnt
								}
								else
								{
									strPtnDup.SetExist(stss[x],patinetID);
									setExistCnt++;
								}
							}
						}
						if(isToPush)
						{
							hashArr.Push(stss[x], value , pushMode);//			
							numberOfSubStringssAllRun++;
						}
						delete []stss[x];
						stss[x]=NULL;
					}
					delete []stss;
				}

			}
		}
		else if(retValue == 0)
		{
			endOfFile =true;
		}
	}
	inFile.close();

//	delete []arrayOfPatinetSubStringFlaging;
	return true;

}
 */

	double cParagraphPredModel::CreateSensitivityMeassureFirstDimSecond(int i, cGlobals* globals)
	{
		double lowerFirstDim = m_bucketArr[i]->m_firstDimLowZ;
		double upperFirstDim = m_bucketArr[i]->m_firstDimUpperZ;
		bool* isIn= new bool[m_numOffPatients];
	 	int cnt=0;
		GetGroupWithMinSizeAndOddCenter(isIn, cnt, m_firstDim,   m_numOffPatients,
			lowerFirstDim , upperFirstDim , 1000);	
		

		double threshodArr[7];
		double valArr[7];
		int cntArr[7];
		double avgDep =0.0;
		cProfileObject::CalculateThresholds(threshodArr,7,m_secondDim,isIn,m_numOffPatients);
		cProfileObject::CreateAvgDepSubGrps(NULL,valArr,threshodArr ,cntArr, avgDep, 7,
					m_secondDim,  m_depLikeArr, isIn, m_numOffPatients, *globals);

		double oddArr[7];
		double tempAvgOdd=0.0;
		cProfileObject::CreateAvgDepSubGrps(NULL,oddArr,threshodArr ,cntArr, tempAvgOdd, 7,
					m_secondDim,  m_secondDim, isIn, m_numOffPatients, *globals);


		double effectAvg = 0.0;
		double sumWeight = 0.0;
		for(int x = 0  ; x < 7 ; x++)
		{
			double deltaOdd = oddArr[x] - tempAvgOdd;
			double deltaDep = valArr[x] - avgDep;
			if(deltaOdd != 0.0)
			{
				double senst = deltaDep / deltaOdd;
				effectAvg += (senst* cntArr[x]);
				sumWeight += (double(cntArr[x]));
			}
		}
		if(sumWeight > 0.0)
		{
			effectAvg /= sumWeight;
		}	
		
	////////////////////

		delete []isIn;
		
		return effectAvg;
	
	}
	void cParagraphPredModel::CreateSubBucketAnaysis( cGlobals* globals )//, 		int valueIndex, char* valueStringg)
	{
		for(int i = 0 ; i < m_queueSize;i++)
		{
			//AddInternalMOdel(i ,  patientMapArray,	 numberOfPatients);// , valueIndex,  valueStringg);
			AddInternalMOdelNew  ( i );
		}
		for(int i = 0 ; i < m_queueSize;i++)
		{
			/*get the profile mean odd
			m_avgOddFirst and the second are the average center profilef. useing this for the ci rcly
			*/
			//keep second sim stady and play with first
			//sensitiviy meand how much (directional) change in dep ratio for a positive change of 1.0 Symetric odd
			double sensitivityForFirst =  CreateSensitivityMeassureDimFirst(i, globals);
			//keep first  sim stady and play with second
			double sensitivityForSecond =  CreateSensitivityMeassureFirstDimSecond(i,globals);
			
			bool* isIn = new bool[m_numOffPatients];
			for(int p = 0 ; p < m_numOffPatients ; p++)
			{
				isIn[p]=false;
			}
			int minProfileSize = globals->g_minSampleSizeWhole;
			FillInCirclePerInputSize(isIn, sensitivityForFirst , sensitivityForSecond, minProfileSize,i);

			m_bucketArr[i]->CalcualteMeanVirtualProfile(isIn, m_depLikeArr, m_numOffPatients);
			minProfileSize *= 6;
			FillInCirclePerInputSize(isIn, sensitivityForFirst , sensitivityForSecond, minProfileSize,i);
			m_bucketArr[i]->CalcaulteThresholdsAndBycketsForThirdAndForthDimensions(isIn, m_depLikeArr, m_thirdDim,
									m_forthDim,m_numOffPatients,globals);

			//sensitivitty for second is defined with how much positive change in the second effects the value
			//of the profile/population
			delete []isIn;
		}
		 
	}



//sensitiviy meand how much (directional) change in dep ratio for a positive change of 1.0 Symetric first dim odd
	double cParagraphPredModel::CreateSensitivityMeassureDimFirst(int i,cGlobals* globals)
	{//keep second dim stary

		double lowerSecondDim = m_bucketArr[i]->m_secondDimLowerZ;
		double upperSecondDim = m_bucketArr[i]->m_secondDimUpperZ;
		bool* isIn= new bool[m_numOffPatients];
	 	int cnt=0;
		GetGroupWithMinSizeAndOddCenter(isIn, cnt, m_secondDim,   m_numOffPatients,
			lowerSecondDim , upperSecondDim , 1000);	
		
		double threshodArr[7];
		double valArr[7];
		int cntArr[7];
		double avgDep =0.0;
		cProfileObject::CalculateThresholds(threshodArr,7,m_firstDim,isIn,m_numOffPatients);
		cProfileObject::CreateAvgDepSubGrps(NULL,valArr,threshodArr ,cntArr, avgDep, 7,
					m_firstDim,  m_depLikeArr, isIn, m_numOffPatients, *globals);

		double oddArr[7];
		double tempAvgOdd=0.0;
		cProfileObject::CreateAvgDepSubGrps(NULL,oddArr,threshodArr ,cntArr, tempAvgOdd, 7,
					m_firstDim,  m_firstDim, isIn, m_numOffPatients, *globals);


		double effectAvg = 0.0;
		double sumWeight = 0.0;
		for(int x = 0  ; x < 7 ; x++)
		{
			double deltaOdd = oddArr[x] - tempAvgOdd;
			double deltaDep = valArr[x] - avgDep;
			if(deltaOdd != 0.0)
			{
				double senst = deltaDep / deltaOdd;
				effectAvg += (senst* cntArr[x]);
				sumWeight += (double(cntArr[x]));
			}
		}
		if(sumWeight > 0.0)
		{
			effectAvg /= sumWeight;
		}	
		
		delete []isIn;
		
		return effectAvg;
	}



int cParagraphPredModel::GetBucketIndex(int ptIndex)
{
//	int iIndex = GetTableDims12(m_firstDim[ptIndex], m_twoDimTableSize );
//	int jIndex = GetTableDims12( m_secondDim[ptIndex], m_twoDimTableSize);
	for(int i = 0 ; i < m_queueSize ; i++)
	{
		if(m_bucketArr[i]->AreIndexesMatch(m_firstDim[ptIndex], m_secondDim[ptIndex]))
		{
			return i;
		}
	}
	return -1;
}

void cParagraphPredModel::AddInternalMOdelNew  (int bucketIndex )//, 		int valueIndex, char* valueStringg)
	{
		m_bucketArr[bucketIndex]->Clear();//AddPatientInfo(m_thirdDim[i], m_forthDim[i]);
		int numOfPatientsThisBucket = 0;
		for(        int i = 0      ;         i < m_numOffPatients ;      i++        )
		{
			if( GetBucketIndex(i) == bucketIndex)
			{
				int  thirdDimBucketIndex= cProfileObject::GetSubGrpIndex(
									m_thirdDim[i], m_thirdThresArr, NUM_OF_PARAG_THIRD_DIM_BUCKETS);
				int forthDimBucketIndex = cProfileObject::GetSubGrpIndex(
									m_forthDim[i], m_forthThresArr, NUM_OF_PARAG_THIRD_DIM_BUCKETS);
				m_bucketArr[bucketIndex]->AddPatientInfo(    thirdDimBucketIndex, m_thirdDim[i], forthDimBucketIndex,  m_forthDim[i], m_depLikeArr[i]);
			}
		}
		m_bucketArr[bucketIndex]->SetBucketPatietnInfo();
	}


//4 27 23 do BOTH fucntion together and ndelete these as separe so it complites at the caller side.  as one functino with an ocliidic idistance
//using some method of evaluting the relation between first dim m, first dim gap, and the change in value
double  cParagraphPredModel::GetPenaltyInGapFirst(double gapFirst,double  firstDim)
{
	return gapFirst;//5 5 23 divide by an SD of each first or second and save also in disc for oreal time. this
	//will ensure that penalry is symetric. sd is by going over all buckets and checng their count or weight and 
	//odd avg first and second for value.
}
double cParagraphPredModel::GetPenaltyInGapSecond(double gapSecond,  double  secondDim)
{
	return gapSecond;
}

bool cParagraphPredModel::FindScoreAndThenPredictionThreeDimensions(double &predOut, double firstDim,  
	double secondDim, double thirdDim,  double forthDim, cStringHistogram* globalHistogram,
	int valueIndex , cGlobals* globals)
{
	double* scoreArr = new double [m_queueSize];
	int indexLowestGap = 0;
	double lowestGap = 1000000;
	for(int i = 0 ; i < m_queueSize ; i++)
	{
		scoreArr[i]=0.0;
		int directionOfProfileGap = 0;
		int directionGapFirst = 0;
		double gapFirst =  m_bucketArr[i]->GetAbsGapOfFirst(directionGapFirst, firstDim);//4 27 23 call a new penalry function wtih both 
				//gaps and find an oclidic disctance and that has penalty values means effect on the value is the common denominator
		double gapFFirstPenaly = GetPenaltyInGapFirst(gapFirst, firstDim);//4 26 23 look at gaps across all m_queueSize options and use the bucket
		int directionGapSecond = 0;
		double gapSecond = m_bucketArr[i]->GetAbsGapOfSecond(directionGapSecond, secondDim);
		double gapSecondPenaly = GetPenaltyInGapSecond(gapSecond, secondDim);//4 26 23 look at gaps across all   m_queueSize options and use the bucket
		//i is where we are and the seroundings to have penalry based on gaps from the value.
		double sumPenalty = gapFFirstPenaly + gapSecondPenaly;
		gapFirst = gapFFirstPenaly;
		gapSecond = gapSecondPenaly;
		
		
		double sumGaps = gapFirst + gapSecond;
		double reducedGap = 0.0;
		if( gapSecond > 0.0 && gapFirst > 0.0)
		{
			if(		
			(directionGapFirst * directionGapSecond) == 1)//same direction means going further. 1 is when both dimension go higher so some of it cancels  
			{
				double minGap = cVarianceCalc::Min(gapFirst, gapSecond);
				reducedGap = 0.5 * minGap;
			}
		}
		scoreArr[i] = sumGaps   - reducedGap;
		if( scoreArr[i] < lowestGap )
		{
			lowestGap = scoreArr[i];
			indexLowestGap = i;
		}
	}
	//start frmo here a new tyep fo function. take only the best match and work with it.
	//int index = GetClosestProfile(scoreArr, m_queueSize, isTaken);
	delete []scoreArr;
	scoreArr=NULL;
	
	
	int thridDimIndex = cProfileObject::GetSubGrpIndex(
					thirdDim, m_bucketArr[indexLowestGap]->m_thirdThresholdArrLocal,LOCAL_NUMBER_OF_BUCKETS);
	int forthDimIndex = cProfileObject::GetSubGrpIndex(
					forthDim,  m_bucketArr[indexLowestGap]->m_forthThresholdArrLocal,LOCAL_NUMBER_OF_BUCKETS);
	int twoDimIndex = cTableBucket::GetTwoDimIndexFromTwoIndexes(thridDimIndex, forthDimIndex, LOCAL_NUMBER_OF_BUCKETS);
	 
	double bucketValue = m_bucketArr[indexLowestGap]->m_twoDimThirForthBucketVal[twoDimIndex];//   >m_twoDimThirForthBucketVal;
	
	double thirdBucketValue =  m_bucketArr[indexLowestGap]->m_thirdValArrLocal[thridDimIndex];
	int thirdBucketCnt  =m_bucketArr[indexLowestGap]->m_thirdCntArrLocal[thridDimIndex];
	double forthBucketValue =  m_bucketArr[indexLowestGap]->m_forthValArrLocal[forthDimIndex];
	int forthBucektCnt =  m_bucketArr[indexLowestGap]->m_forthCntArrLocal[forthDimIndex];

	int sampleSize = m_bucketArr[indexLowestGap]->m_twoDimThirForthBucketCnt[twoDimIndex];
	if(sampleSize ==0)
	{
		int sdg =0;
	}

	 
	double wghArr[LOCAL_TWO_DIM_BUCKET_NUM];
	for(int w = 0 ; w< LOCAL_TWO_DIM_BUCKET_NUM;w++)
	{
		wghArr[w] = double(m_bucketArr[indexLowestGap]->m_twoDimThirForthBucketCnt[w]);
	}

	//two options - m_bucketArr[indexLowestGap]->m_virtualValue  and finalVal 
	double meanTwoDimValBuckets = 0.0;
	double sdTwoDimmValBuckts=0.0;
	cVarianceCalc::CalculateMeanAndSD(meanTwoDimValBuckets, sdTwoDimmValBuckts, 
		m_bucketArr[indexLowestGap]->m_twoDimThirForthBucketVal,
		wghArr,   LOCAL_TWO_DIM_BUCKET_NUM);
	
		//bucketValue
	double virtualSmal = m_bucketArr[indexLowestGap]->m_virtualValue;
	double virtualLArge = meanTwoDimValBuckets;
	
	double virtualWithTwoDim = bucketValue;
	double portion  = ((double)sampleSize )/ ((double)globals->g_minSampleSizeWhole);
	portion = cVarianceCalc::Min( portion , 1.0);



	double wghThr[LOCAL_NUMBER_OF_BUCKETS];
	double wghForth[LOCAL_NUMBER_OF_BUCKETS];
	for(int i = 0 ; i < LOCAL_NUMBER_OF_BUCKETS ; i++)
	{
		wghThr[i] = double(m_bucketArr[indexLowestGap]->m_thirdCntArrLocal[i]);
		wghForth[i] = double(m_bucketArr[indexLowestGap]->m_forthCntArrLocal[i]);
	}


	double meanThird=0.0;
	double sdThird = 0.0;
	cVarianceCalc::CalculateMeanAndSD(meanThird , sdThird, m_bucketArr[indexLowestGap]->m_thirdValArrLocal,
		wghThr,LOCAL_NUMBER_OF_BUCKETS);
	double meanForth = 0.0;
	double sdForth = 0.0;
	cVarianceCalc::CalculateMeanAndSD(meanForth , sdForth, m_bucketArr[indexLowestGap]->m_forthValArrLocal,
		wghForth,LOCAL_NUMBER_OF_BUCKETS);
	
	double oneDimvalues = ((sdThird *thirdBucketValue )+(sdForth* forthBucketValue )) / (sdThird + sdForth);
	virtualWithTwoDim =  (virtualWithTwoDim * portion ) + (oneDimvalues *(1.0-portion));
	//5 5 23 if we dont have enohg sample checkk the large cirtual  for the one dim thrid or forth models
	//double wghTwoDim = sdTwoDimmValBuckts;
	//double wghSmall = cVarianceCalc::Abs( virtualSmal - virtualLArge);

	double complexResult =virtualWithTwoDim;// ( (wghTwoDim * virtualWithTwoDim) + (wghSmall * virtualSmal)) /(wghTwoDim + wghSmall);
	if(IsOnSameSide(complexResult, virtualSmal , virtualLArge))
	{
		if(complexResult < virtualLArge )
		{
			complexResult = cVarianceCalc::Min(complexResult, virtualSmal);
		}
		else
		{
			complexResult = cVarianceCalc::Max(complexResult, virtualSmal);
		}
	}
	else
	{
		int sdg = 0;
	}	
	if(false)//5 5 23 change to false
	{
		
		double result1GapFromWall = 1.0 - virtualSmal;
		result1GapFromWall = cVarianceCalc::Min(result1GapFromWall , (virtualSmal - 0.0));
		double wghSmall = 1.0-result1GapFromWall;
		wghSmall *= wghSmall;

		double result2GapFromWall = 1.0 - virtualWithTwoDim;
		result2GapFromWall = cVarianceCalc::Min(result2GapFromWall , (virtualWithTwoDim-0.0));
		double wghTwoDim = 1.0-result2GapFromWall;
		wghTwoDim *= wghTwoDim;

		complexResult = ((wghSmall* virtualSmal) + (wghTwoDim * virtualWithTwoDim)) / (wghSmall + wghTwoDim);

/*
		if(result1GapFromWall < result2GapFromWall)//the small focused profile is closer to the left or right (0/1 ) 
//and we take prediction from that profile. closer = more signifciant -< it is less likely to get an extreme score
		{
			resultOut = result1*  + ;
		}
		else
		{
			resultOut = result2;
		}*/
	}





	/*double deltaPerTwoDim = virtualWithTwoDim - virtualLArge;
	double portion  = ((double)sampleSize )/ ((double)globals->g_minSampleSizeWhole);
				portion = cVarianceCalc::Min( portion , 1.0);
	deltaPerTwoDim *= portion;


			


	double result1 = virtualSmal;
	double result1GapFromWall = 1.0 - result1;
	result1GapFromWall = cVarianceCalc::Min(result1GapFromWall , (result1 - 0.0));
	
	  //bucket value is from the two dim bucket array with the sample of "sampleSize"
*/
	/*double thirdBucketValue   	
	int thirdBucketCnt  
	double forthBucketValue 
	int forthBucektCnt*/
	/*
	if( globals->g_minSampleSizeWhole >  sampleSize )
	{
		result2 =
			(
			(result2 * sampleSize )+
		
			
			(result1 * ( globals->g_minSampleSizeWhole - sampleSize )) ) / 
				                                     globals->g_minSampleSizeWhole ;
	}
	double resultOut = result2;


	if(false)
	{
		
		double result2GapFromWall = 1.0 - result2;
		result2GapFromWall = cVarianceCalc::Min(result2GapFromWall , (result2-0.0));
	
		if(result1GapFromWall < result2GapFromWall)//the small focused profile is closer to the left or right (0/1 ) 
//and we take prediction from that profile. closer = more signifciant -< it is less likely to get an extreme score
		{
			resultOut = result1;
		}
		else
		{
			resultOut = result2;
		}
	}
	if(true)// 5 5 23 a open and check
	{
		if(IsOnSameSide(bucketValue, virtualSmal , virtualLArge))
		{
			double gapVirt = virtualSmal - virtualLArge;
			double gapBucket = bucketValue - virtualLArge;
			if( cVarianceCalc::Abs(gapVirt) > cVarianceCalc::Abs(gapBucket))
			{
				resultOut = virtualSmal;
			}
			else
			{
				double portion  = ((double)sampleSize )/ ((double)globals->g_minSampleSizeWhole);
				portion = cVarianceCalc::Min( portion , 1.0);
				double shift1 = gapVirt;
				double shift2 = gapBucket - gapVirt;
				shift2 *= portion;
				//result = virtualSmal;
				resultOut = virtualLArge + shift1 + shift2;
			}
		}
		else
		{
			double gapBucket = bucketValue - virtualLArge;
			double portion  = ((double)sampleSize )/ ((double)globals->g_minSampleSizeWhole);
			portion = cVarianceCalc::Min( portion , 1.0);
			gapBucket *= portion;
			resultOut = virtualSmal + gapBucket;
		}
	}*/
	predOut = complexResult;//5 5 23



//		if(//   take the further one
	//   if the further one is the bucketValue than take portion of the extra part using the sample size of total
//	}
		//else
	//   if no other side than use a portion of the shift between bucket and virtual large to shift the virtual small 
	//gggggg


//-virtual and shifted bucket are  both on the same side of the large virtual mean :
	//take the further one from the large virtual, but if the bucket is the one passing the virtual than on that passing section take only a portion per what sample we got
//-virtual and bucket value on other sides of the large virtual: use the shift between bucket and large virtual to shift the virtual. if the sample is low use only portion of that shift

	/*
	double zShiftOfVirtual = cVarianceCalc::Abs( (m_bucketArr[indexLowestGap]->m_virtualValue - meanTwoDimValBuckets) /
		                             sdTwoDimmValBuckts);
	if(zShiftOfVirtual>0.5)
	{
		int sdf=0;
	}
	double wghtOfFinal = 1.0;
	double finalVal = ((finalVal*wghtOfFinal) + (m_bucketArr[indexLowestGap]->m_virtualValue * zShiftOfVirtual) ) / 
		(wghtOfFinal + zShiftOfVirtual);

	if(sampleSize < globals->g_minSampleSizeWhole )
	{
		finalVal = (
			(finalVal * sampleSize) +
			(m_bucketArr[indexLowestGap]->m_virtualValue * ( globals->g_minSampleSizeWhole - sampleSize)   )  
		  ) 
		  / 
		  (globals->g_minSampleSizeWhole);
	}
	predOut = finalVal;
	*/
	return true;
}
/*

		//	m_twoDimThirForthBucketVal[twoDimIndex] 
		//	m_avgThirdDimArr[twoDimIndex]
		//	m_avgForthDimArr[twoDimIndex]
		//	m_twoDimThirForthBucketCnt[twoDimIndex] 







	///////////////////////////////////////
	bool* isTaken = new bool[m_queueSize];
	for(int i = 0 ; i < m_queueSize ; i++)
	{
		isTaken[i]=false;	
	}
	bool end = false;
	
	int requireSampleSize = 300;


	double predAvg = 0.0;
	int predSumSample=0;
	double predAvgWithThird = 0.0;
	int predSumSampleWithThird = 0;

	double thirdBucketArrayComplete[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double thirdOddArrayComplete[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	int thirdBcketSampleComplete[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double forthBucketArryComplete[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	double forthOddArryComplete[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	int forthBcketSampleComplete[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	//4 22 23 open one more third and one more forth that do not get cut by the below mutpleirer, and keep to the end calculation
	for(int ii = 0 ; ii < NUM_OF_PARAG_THIRD_DIM_BUCKETS; ii++)
	{
		thirdBucketArrayComplete[ii] =0.0;
		thirdOddArrayComplete[ii]=0.0;
		thirdBcketSampleComplete[ii]=0;
		forthBucketArryComplete[ii] =0.0;
		forthOddArryComplete[ii]=0.0;
		forthBcketSampleComplete[ii] =0;
	}


	while(!end)
	{
		int index = GetClosestProfile(scoreArr, m_queueSize, isTaken);
		if(index == -1)
		{
			end = true;
		}
		else
		{
			isTaken[index]=true;

			double prediction =0.0;
			int predSample = 0;
			double predictionWithThird = 0.0;
			int predWithThirdSample = 0;
		//returns true if bucket has at least sample size of 1
			double thirdBucketArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
			double thirdOddArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
			int thirdBcketSample[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
			double forthBucketArry[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
			double forthOddArray[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
			int forthBcketSample[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
			if(m_bucketArr[index]->GetPredictionNew(
				prediction,predSample,thirdBucketArray ,thirdOddArray,thirdBcketSample   , forthBucketArry,forthOddArray,forthBcketSample))  
			{
				int potentialSumSample = predSumSample + predSample;
				int missingSample = requireSampleSize - potentialSumSample;
				double discSampleMulti = 1.0;
				if(missingSample <= 0)
				{
					end = true;
					if(missingSample < 0)
					{
						discSampleMulti = ( 1.0 - (-1.0 * ((double)missingSample )) / ((double)predSample));	
						predSample =requireSampleSize;			 
					}
				}
				predAvg += (prediction * predSample);
				predSumSample += predSample;
				for(int ii = 0 ; ii < NUM_OF_PARAG_THIRD_DIM_BUCKETS; ii++)
				{
					thirdBcketSample[ii]*=discSampleMulti;
					forthBcketSample[ii]*=discSampleMulti;

					thirdBucketArrayComplete[ii] += (thirdBucketArray[ii]*((double)thirdBcketSample[ii]));
					thirdOddArrayComplete[ii] += (thirdOddArray[ii]*((double)thirdBcketSample[ii]));
					thirdBcketSampleComplete[ii] += thirdBcketSample[ii];
					forthBucketArryComplete[ii] += 	(forthBucketArry[ii]* ((double)forthBcketSample[ii]));
					forthOddArryComplete[ii]+= (forthOddArray[ii]* ((double)forthBcketSample[ii]));
					forthBcketSampleComplete[ii]  += forthBcketSample[ii];
				}
			}
		}
			
	}
	if(predSumSample >0)
	{
		predAvg /= predSumSample;
	}
	
	for(int ii = 0 ; ii < NUM_OF_PARAG_THIRD_DIM_BUCKETS; ii++)
	{
		if(thirdBcketSampleComplete[ii] > 0.0)
		{
			thirdBucketArrayComplete[ii] /= thirdBcketSampleComplete[ii]  ;
			thirdOddArrayComplete[ii] /= thirdBcketSampleComplete[ii]  ;
		}
		if(forthBcketSampleComplete[ii] > 0)
		{
			forthBucketArryComplete[ii] /= forthBcketSampleComplete[ii];
			forthOddArryComplete[ii] /= forthBcketSampleComplete[ii];
		}
	}

	predOut = predAvg;
	int goodSampleWithThird = 50;//150; //5 2 23
	
	int indexThurd = cProfileObject::GetSubGrpIndex(thirdDim, m_thirdThresArr, NUM_OF_PARAG_THIRD_DIM_BUCKETS);
//	double predWithThirdCons = thirdBucketArrayComplete[indexThurd];
	double predWithThirdCons = InternalPredictBasedOnBuckets(thirdBucketArrayComplete,thirdOddArrayComplete,
		thirdBcketSampleComplete, NUM_OF_PARAG_THIRD_DIM_BUCKETS, indexThurd,thirdDim, predAvg);
//	int sampleWithThird = thirdBcketSampleComplete[indexThurd];
//	if(sampleWithThird < goodSampleWithThird)
//	{//4 2 23 see how to make the sample higher or an oval method. also see why most third dim values are 6 and up
//		predWithThirdCons =( (predWithThirdCons*sampleWithThird)  + (predOut* (goodSampleWithThird - sampleWithThird)))/
//			    goodSampleWithThird;
//	}
	
	int indexForth =  cProfileObject::GetSubGrpIndex(forthDim, m_forthThresArr, NUM_OF_PARAG_THIRD_DIM_BUCKETS);
//	double predWithForthCons = forthBucketArryComplete[indexForth];
	double predWithForthCons = InternalPredictBasedOnBuckets(forthBucketArryComplete,forthOddArryComplete,forthBcketSampleComplete,
		NUM_OF_PARAG_THIRD_DIM_BUCKETS, indexForth, forthDim,predAvg);
	
//	int sampleWithForth = forthBcketSampleComplete[indexForth];
//	if(sampleWithForth < goodSampleWithThird)
//	{
//		predWithForthCons =( (predWithForthCons*sampleWithForth)  + (predOut* (goodSampleWithThird - sampleWithForth)))/
//			    goodSampleWithThird;
//	}

	double globalPercentage = ((double)globalHistogram->GetCntArray()[valueIndex]) /
												((double) globalHistogram->GetTotalSample());

	double gapThird = cVarianceCalc::Abs(globalPercentage - predWithThirdCons);
	double gapFortth = cVarianceCalc::Abs(globalPercentage - predWithForthCons);
	if(gapThird > gapFortth)
	{
		predOut = predWithThirdCons;
	}
	else
	{
		predOut = predWithForthCons;
	}

	delete []scoreArr;
	delete []isTaken;

	if(predSumSample >= requireSampleSize)
	{
		return true;
	}
	return false;
 
}
*/


void cParagraphPredModel::BuildTwoDimTables(int sizee)
{
	//3 3 23 bild threshlds and avg groups accordingly
	//int size = 12;
	m_twoDimTableSize = sizee;
	m_valTable = new double*[m_twoDimTableSize];
	m_firstOddTable = new double*[m_twoDimTableSize];
	m_secondOddTable= new double*[m_twoDimTableSize];
	m_cntTable = new int*[m_twoDimTableSize];
	//SetTables(m_valTable, m_cntTable, m_twoDimTableSize);
	for(int i = 0 ; i < m_twoDimTableSize ; i++)
	{
		m_valTable[i] = new double[m_twoDimTableSize];
		m_firstOddTable[i] = new double[m_twoDimTableSize];
		m_secondOddTable[i] = new double[m_twoDimTableSize];
		m_cntTable[i] = new int[m_twoDimTableSize];
		for(int ii = 0 ; ii < m_twoDimTableSize; ii++)
		{
			m_valTable[i][ii] = 0.0;
			m_firstOddTable[i][ii] = 0.0;
			m_secondOddTable[i][ii] = 0.0;
			m_cntTable[i][ii] = 0;
		}
	}
	for(int i = 0 ; i < m_numOffPatients ; i++)
	{
		 //paragPRedModel->CalculateStretch();
		if(m_twoDimTableSize == 24)
		{
			int iIndex =  GetTableDims24(m_firstDim[i], m_twoDimTableSize );
			int jIndex = GetTableDims24( m_secondDim[i], m_twoDimTableSize);
			if(iIndex >=0 && jIndex>=0)
			{
				m_valTable[iIndex][jIndex] += m_depLikeArr[i];
				m_firstOddTable[iIndex][jIndex]+= m_firstDim[i];
				m_secondOddTable[iIndex][jIndex]+= m_secondDim[i];
				m_cntTable[iIndex][jIndex]++;
			}
		}
		else
		{
			int sdg=0;
		}
	}
	for(int i = 0 ; i < m_twoDimTableSize ; i++)
	{
		for(int ii = 0 ; ii < m_twoDimTableSize; ii++)
		{
			if(m_cntTable[i][ii] > 0)
			{
				m_valTable[i][ii] /=  m_cntTable[i][ii];
				m_firstOddTable[i][ii] /=  m_cntTable[i][ii];
				m_secondOddTable[i][ii] /=  m_cntTable[i][ii];
			}
		}
	}
	/*double** adjustedValArr = new double*[m_twoDimTableSize];

	for(int i = 0 ; i < m_twoDimTableSize ; i++)
	{
		adjustedValArr[i] = new double[m_twoDimTableSize]; 
	 	for(int ii = 0 ; ii < m_twoDimTableSize; ii++)
		{
			adjustedValArr[i][ii] = m_valTable[i][ii];
			double adjustedVal = adjustedValArr[i][ii] ;
			if(AdjustPerSamle(adjustedVal, i , ii))
			{
				adjustedValArr[i][ii] = adjustedVal;
			}
		}
	}
	for(int i = 0 ; i < m_twoDimTableSize ; i++)
	{
	//	adjustedValArr[i] = new double[m_twoDimTableSize]; 
	 	for(int ii = 0 ; ii < m_twoDimTableSize; ii++)
		{
			m_valTable[i][ii] = adjustedValArr[i][ii];
		}
		delete []adjustedValArr[i];
		adjustedValArr[i]=NULL;
	}
	delete []adjustedValArr;
	adjustedValArr=NULL;*/
}

 
bool cParagraphPredModel::AdjustPerSamle( double &adjusted,int dimI, int dimII)
{
	int cnt = m_cntTable[dimI][dimII];
	double avg = m_valTable[dimI][dimII] * cnt;
	int targetCnt = 180;
	if(cnt > 0 && cnt < targetCnt)
	{
		for(int i = 0 ; i < m_twoDimTableSize ; i++)
		{
	 		for(int ii = 0 ; ii < m_twoDimTableSize; ii++)
			{
				if( i != dimI  || ii != dimII )
				{
					if(cnt< targetCnt)
					{
						int gapI = cVarianceCalc::Abs( i - dimI ) ;
						int gapII = cVarianceCalc::Abs( ii - dimII ) ;
						int additionalCnt = (int)((m_cntTable[i][ii]) * ( (double) (  1.0 / ( 1 + gapI + gapII))));
						additionalCnt = cVarianceCalc::Min(additionalCnt , targetCnt - cnt);
						cnt += additionalCnt;
						avg += m_valTable[i][ii] * additionalCnt;
					}
				}
			}
		}
	}
	if(cnt > 0)
	{
		avg /= cnt;
		adjusted = avg;
		return true;
		//m_valTable[dimI][dimII] = avg;
	}
	return false;
}

cParagraphPredModel::cParagraphPredModel(int numberOfPatients , cPatientMapElements** patientMapArray   ,
	int valueIndex, char* valueStr,  cGlobals* globals)
{
	m_bucketArr = NULL;
	m_numOffPatients = numberOfPatients;
	m_firstDim = new double[numberOfPatients];
	m_secondDim= new double[numberOfPatients];
	m_thirdDim= new double[numberOfPatients];
	m_forthDim = new double[numberOfPatients];
	m_valueIndex = valueIndex;

	for(int i = 0 ; i < numberOfPatients ; i++)
	{
		patientMapArray[i]->FillThreeDimensions(m_firstDim[i],m_secondDim[i], m_thirdDim[i],m_forthDim[i],valueIndex);
	}

	m_firsMeann = 0.0;
	m_firstSDd = 0.0;
	cVarianceCalc::CalculateMeanAndSD(m_firsMeann,  m_firstSDd, m_firstDim,NULL, numberOfPatients);
	m_secMeann = 0.0;
	m_secSDd = 0.0;
	cVarianceCalc::CalculateMeanAndSD(m_secMeann,  m_secSDd, m_secondDim,NULL, numberOfPatients);
	m_thiMeann = 0.0;
	m_thiSDd = 0.0;
	cVarianceCalc::CalculateMeanAndSD(m_thiMeann,  m_thiSDd, m_thirdDim,NULL, numberOfPatients);
	m_forthMeann = 0.0;
	m_forthSDd = 0.0;
	cVarianceCalc::CalculateMeanAndSD(m_forthMeann,  m_forthSDd, m_forthDim,NULL, numberOfPatients);


	strcpy( m_valueStr, valueStr);

	m_depLikeArr =  new double[numberOfPatients];
	for(int i = 0 ; i < numberOfPatients ; i++)
	{
	//	m_firstDim[i] =  (m_firstDim[i] - m_firsMean) / m_firstSD;
	//	m_secondDim[i]=	 (m_secondDim[i] - m_secMean)/ m_secSD;
	//	m_thirdDim[i] = (m_thirdDim[i] - m_thiMean) / m_thiSD;
		m_depLikeArr[i] = 0.0;
		if(  !strcmp(patientMapArray[i]->m_valueStr, m_valueStr))
		{
			m_depLikeArr[i] = 1.0;
		}
	}


	//m_thirdThresArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	//m_forthThresArr

//	double m_thirdThresArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
	//double m_thirdValueArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
//	double m_forthThresArr[NUM_OF_PARAG_THIRD_DIM_BUCKETS];
//	double m_forthValueArr


	double avgThir = 0.0;
	cProfileObject::CalculateThresholds(m_thirdThresArr , NUM_OF_PARAG_THIRD_DIM_BUCKETS, m_thirdDim,NULL,numberOfPatients);
	cProfileObject::CreateAvgDepSubGrps(NULL,m_thirdValueArr,m_thirdThresArr ,m_thirdCntArr, avgThir, NUM_OF_PARAG_THIRD_DIM_BUCKETS,
					m_thirdDim,m_depLikeArr, NULL, numberOfPatients, *globals);

	double avgForth = 0.0;
	cProfileObject::CalculateThresholds(m_forthThresArr , NUM_OF_PARAG_THIRD_DIM_BUCKETS, m_forthDim,NULL,numberOfPatients);
	cProfileObject::CreateAvgDepSubGrps(NULL,m_forthValueArr,m_forthThresArr ,m_forthCntArr, avgForth, NUM_OF_PARAG_THIRD_DIM_BUCKETS,
					m_forthDim,  m_depLikeArr, NULL, numberOfPatients, *globals);


}


void cParagraphAnalytics::CreateParagPredModel( cPatientMapElements** patientMapArray,	
				int numberOfPatients , 		int valueIndex, char* valueStringg, cGlobals* globals)//, cStringHistogram* globalHistogram)
{
	m_paragPRedMode[valueIndex] = new cParagraphPredModel( numberOfPatients ,  patientMapArray   ,valueIndex,  valueStringg, globals);
	//3 3 23 bild threshlds and avg groups accordingly
	int size = 24;
	m_paragPRedMode[valueIndex] ->BuildTwoDimTables(size);
	m_paragPRedMode[valueIndex] ->ConvertToQueue();

	m_paragPRedMode[valueIndex]->CreateSubBucketAnaysis(//patientMapArray,	
		                  globals);// ,  valueIndex,  valueStringg);
	
}


void cParagraphAnalytics::GetTopNobjectsWithHighestOddToAnyValue(cHashObj** topObjs, double* oddArr, 
		int &actualyTopObjNumber, int maxNumOfTopObjs,
		cHashObj** phraseObjArray, int numOfPhraseHashObjects,  cStringHistogram* globalHistogram)
{

}

/*	
double cParagraphAnalytics::GetSumOfTopOddRatioObjects( cPatientMapElements* patientMapArray )
{
	int maxNumOfTopObjs = 7;
	cHashObj** topObjs = new cHashObj*[maxNumOfTopObjs];
	double* oddArr = new double[maxNumOfTopObjs];
	for(int iii = 0 ; iii < maxNumOfTopObjs; iii++)
	{
		topObjs[iii] =  NULL;
		oddArr[iii]=0.0;
	}
	int actualyTopObjNumber = 0;
	int numOfTopObjs = 7;
	GetTopNobjectsWithHighestOddToAnyValue(
			topObjs,  oddArr, actualyTopObjNumber, maxNumOfTopObjs,
			patientMapArray->m_phraseObjArray, patientMapArray->m_numOfPhraseHashObjects);
	double sumOfSymetricTopAbsSig = 0.0;
	for(int iii = 0 ; iii < actualyTopObjNumber ; iii++)
	{
		double s = Symetric(oddArr[iii]);
		sumOfSymetricTopAbsSig += s;
	}
	//patientMapArray->m_highestOddSumAnyValueArr = sumOfSymetricTopAbsSig;
	delete []topObjs;
	topObjs=NULL;
	delete[] oddArr;
	oddArr=NULL;
	return sumOfSymetricTopAbsSig;
}
*/


void cParagraphAnalytics::GetObjectWithHighestOddForInputStr(
		cHashObj *&highestOddObjThisVall, double &highesstOddThisVall, cHashObj *&highestOddObjOtherVall, double &highesstOddOtherVall, bool* isTaken,
		char* valStr, cHashObj** phraseObjArray, int numOfPhraseHashObjects, cStringHistogram* globalHistogram ,  
		cPhraseHash* finalHash, cGlobals* globals, int minSampleSizeForGetingInclded, 
		bool isOnlyHigherLevelShadow, bool  isOnlyNamualRules)//globals->g_minSampleSizeIngridient))
{
	double* firstDim = new double[numOfPhraseHashObjects];
	double* secondDim = new double[numOfPhraseHashObjects];
	for(int i = 0 ; i < numOfPhraseHashObjects ; i++)
	{
		firstDim[i] = 1.0;
		secondDim[i] = 1.0;
		cHashObj* obj = phraseObjArray[i];
		//int numOfValuesThisObj = //obj->GetHistNumberOfValues();
		int numOfValues = globalHistogram->GetSize();
		char** strs = new char*[numOfValues];
		double* sigArr = new double[numOfValues];
//		char** strsShadow = new char*[numOfValues];
//		double* sigArrShadow = new double[numOfValues];
		for(int v = 0 ; v < numOfValues ; v++)
		{
			strs[v] = NULL;
//			strsShadow[v]=NULL;
			sigArr[v] = 1.0;
	//		sigArrShadow[v]=1.0;
		}
		cHashObj* objDictionary = NULL;
		char* phraseStr = obj->GetPhrase();
		if(   (  strlen(phraseStr) > 5    ) &&  (finalHash->IsLookUp(objDictionary    , phraseStr)) )
		{
			int objectSample = objDictionary->GetHistTotalCnt();
			double oddThisValue = 1.0;
			double oddForAnyOtherValueWithMore = 1.0;
			bool isObjectPassedFilter = false;
			if(  objectSample >  minSampleSizeForGetingInclded)
			{
				isObjectPassedFilter = true;
			}
			if(isOnlyHigherLevelShadow)
			{
				if(   (strlen(objDictionary->GetPhrase()) > 2) && (objDictionary->GetPhrase()[0] == '~' )&&
					   (objDictionary->GetPhrase()[1] == '~' ))
				{
					isObjectPassedFilter = true;
				}
				else
				{
					 int dfg=0;
				}
			}
			else if(isOnlyNamualRules)//4 5 23 no nneed for this since the filter true does not give us anyway an odd.
			{
				if(objDictionary->IsManualObject(valStr))
				{
					isObjectPassedFilter = true;
				}
			}
			if( isObjectPassedFilter)//globals->g_minSampleSizeIngridient) 
			{
				objDictionary->CalculateValueArrSignificance(strs,sigArr,  numOfValues, globalHistogram);
		 		int valIndexInObjectToBaseValue = -1;
				//double oddForAnyOtherValueWithMore = 1.0;
				for(int ii = 0 ; ii <numOfValues ; ii++)
				{
				//char* str = obj->GetHistValueArr(ii);
					if(!strcmp(strs[ii], valStr))
					{
						valIndexInObjectToBaseValue = ii;
					}
					else
					{
						oddForAnyOtherValueWithMore = cVarianceCalc::Max(oddForAnyOtherValueWithMore , sigArr[ii]);
					}
				}
				if(valIndexInObjectToBaseValue >= 0)
				{
					oddThisValue = cVarianceCalc::Max( oddThisValue, sigArr[valIndexInObjectToBaseValue]);
				}
			}
			firstDim[i] = oddThisValue;
			secondDim[i] = oddForAnyOtherValueWithMore;
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
	
		delete []sigArr;
//		delete []sigArrShadow;
	}

	highesstOddThisVall = 1.0;
	int maxIndexThis = -1;
	highestOddObjThisVall = NULL;
	for(int i = 0 ; i < numOfPhraseHashObjects ; i++)
	{
		if( ! ( isTaken[i]))
		{
			if(firstDim[i] > highesstOddThisVall)
			{
				highesstOddThisVall = firstDim[i];
				maxIndexThis = i;
				highestOddObjThisVall =  phraseObjArray[i];
			}
		}
	}
	if(maxIndexThis>=0)
	{
		isTaken[maxIndexThis] = true;
	}

	highesstOddOtherVall = 1.0;
	highestOddObjOtherVall = NULL;
	int maxIndexOther = -1;
	for(int i = 0 ; i < numOfPhraseHashObjects ; i++)
	{
		if( ! ( isTaken[i]))
		{
			if(secondDim[i] > highesstOddOtherVall)
			{
				highesstOddOtherVall = secondDim[i];
				maxIndexOther=i;
				highestOddObjOtherVall =  phraseObjArray[i];
			}
		}
	}
	if(maxIndexOther>=0)
	{
		isTaken[maxIndexOther] = true;
	}
//3  3 23 add  for the second dim and also take both hash objects out as output. do a simlar method fo the thid dim as well.


	delete []firstDim;
	firstDim = NULL;
	delete []secondDim;
	secondDim = NULL;
}
	
 
	


void	cParagraphAnalytics::FillAllStringsOnePatient(cPhraseHash* onePatientHash, cPhraseHash* dictionaryHash,
	 char** paragrArray,cPatientRecordObject* ptRecord , bool isGettingFinalHashFilled,cGlobals* globals, int levelOfShadow )//, cPhraseHash* allPatientsHash)
	//int ptIndex )
// m_paragrArray   m_patientRecorsObjectList[ptIndex];
{
	//cPatientRecordObject* ptRecord =  m_patientRecorsObjectList[ptIndex];
	for(int i =0; i < ptRecord->GetNumberOfActualIndexes() ; i++)
	{
		FillAllStringsOnePatientOneParag(
			onePatientHash,  dictionaryHash,   paragrArray, 
			ptRecord->GetParagIndexArr()[i], ptRecord->GetValueStr() ,
			isGettingFinalHashFilled, globals, levelOfShadow);
//	CalculateMultipleSubStrings( stss, numOfSubStrsOnePAragraph, oneLine);
		 

	}
			
}


void cParagraphAnalytics::MergeHash(cPhraseHash* allPatientsHash, cPhraseHash* onePatientHash)
{
	for(int i = 0 ; i < onePatientHash->GetSize() ; i++)
	{
		cHashObj* next = onePatientHash->GetArray()[i];
	
	//	bool end = onePatientHash->GetArray()[i] == NULL;
		while(next != NULL)
		{
			char* phrase = next->GetPhrase();
			char* value = next->GetHistValueArr(0);

			cHashObj* data = NULL;
			if(allPatientsHash->IsLookUp(data, phrase))
			{
				data->UpdateData(value);
			}
			else
			{
				data = new cHashObj( phrase, value);
				allPatientsHash->SetValue(data, phrase, true);
			}
			next = next->GetNext();
			//allPatientsHash->SetValue(data, phrase);
		}
	}
}


void cParagraphAnalytics::FillAllStringsOnePatientOneParag(
				cPhraseHash* onePatientHash, cPhraseHash* dictionaryHash, 
				char** paragrArray, int pargIndex, char* valStr , 
				bool isGettingFinalHashFilled, cGlobals* globals, int levelOfShadow)
{
	char** stss = NULL;
	char* parag = paragrArray[pargIndex];
	int numOfSubStrsOnePAragraph = 0;
	int* posStartArr = NULL;
	int* lenArr = NULL;
	CalculateMultipleSubStrings( stss,posStartArr,lenArr, numOfSubStrsOnePAragraph, parag, globals);
	//4 1 23 add for stss the position array for each phrase. 
	//CalculateMultipleSubStrings( stss,posStartArr, lenArr,  numOfSubStrsOnePAragraph, parag);

	if(stss != NULL)
	{
		for(int i = 0 ; i < numOfSubStrsOnePAragraph ; i++)
		{
			cHashObj* data = NULL;
			char shadowstr[100];
			Shadow(shadowstr,stss[i]); 
			if(   (dictionaryHash == NULL) )
			{
				//this is the case when i get started and build the ver first patinet hash that will turn into dictiona
				//i want to add only a shadow and i dont need to check any discionary o course
				if(onePatientHash->IsLookUp(data,  shadowstr))
				{
					data->UpdateData(valStr);
				}
				else
				{
					data = new cHashObj( shadowstr, valStr);
					onePatientHash->SetValue(data,shadowstr, false);
					data = NULL;
				}
			}
			else if (isGettingFinalHashFilled)
			{
				if  (dictionaryHash->IsLookUp(data, shadowstr))
				{//this case is when there is a dictionary and i am filling final hash. need to 
				//fill both 
				//i want to add here both the orignal and shadow to try go for both but only if shadow is in dictioannry
					if(onePatientHash->IsLookUp(data,  stss[i]))
					{
						data->UpdateData(valStr);
					}
					else
					{
						data = new cHashObj( stss[i], valStr);
						onePatientHash->SetValue(data,stss[i], false);
						data = NULL;
					}		
					data=NULL;
					if(onePatientHash->IsLookUp(data,  shadowstr))
					{
						data->UpdateData(valStr);
					}
					else
					{
						data = new cHashObj( shadowstr, valStr);
						onePatientHash->SetValue(data,shadowstr, false);
						data = NULL;
					}
				}
			}
			else
			{
				if  (dictionaryHash->IsLookUp(data, shadowstr))
				{//this case is when there is a dictionary and i am filling final hash. need to 
				//fill both 
				//i want to add here both the orignal and shadow to try go for both but only if shadow is in dictioannry
					if(onePatientHash->IsLookUp(data,  shadowstr))
					{
						data->UpdateData(valStr);
					}
					else
					{
						data = new cHashObj(shadowstr, valStr);
						onePatientHash->SetValue(data,shadowstr, false);
						data = NULL;
					}		
				}
				if  (dictionaryHash->IsLookUp(data, stss[i]))
				{
					if(onePatientHash->IsLookUp(data,  stss[i]))
					{
						data->UpdateData(valStr);
					}
					else
					{
						data = new cHashObj( stss[i], valStr);
						onePatientHash->SetValue(data,stss[i], false);
						data = NULL;
					}
				}		
			}
		}
	//	cHashObj** hashObjArr = NULL;
		int numOfObjects =0;
		if(levelOfShadow >= 2 && dictionaryHash != NULL)
		{
			//onePatientHash->ExportHashToArray(hashObjArr, numOfObjects);
			//bool* isIn = new bool[numOfSubStrsOnePAragraph];
			char** shadowedElements = new char*[numOfSubStrsOnePAragraph];
			int* shadowedStartPos = new int[numOfSubStrsOnePAragraph];
			int* shadowedStrLen  = new int[numOfSubStrsOnePAragraph];
			cHashObj** shadowedHashObjArr= new cHashObj*[numOfSubStrsOnePAragraph];
			int movingPos = 0;
			for(int i = 0 ; i < numOfSubStrsOnePAragraph ; i++)
			{
			//	isIn[i] = false;
				char shadowstr[100];
				Shadow(shadowstr,stss[i]); 
				cHashObj* dataa = NULL;
				if  (dictionaryHash->IsLookUp(dataa, shadowstr))
				{
					shadowedElements[movingPos] = dataa->GetPhrase();
					shadowedStartPos[movingPos] =posStartArr[i];
					shadowedStrLen [movingPos] = lenArr[i];
					shadowedHashObjArr[movingPos] = dataa;
					movingPos++;
				}
				//onePatientHash->KeepOnlyShadows(hashObjArr, numOfObjects);
			}
			int shadowStringsLength = movingPos;
			for(int i = 0 ; i < shadowStringsLength ; i++)
			{
				if(shadowedHashObjArr[i]->GetHistTotalCnt() > globals->g_minSampleSizeWhole )
				{
					int* pairedOptionSet = NULL;
					int numOfPairdOptions = 0;
					FindPotenetialPairedShadowed(pairedOptionSet, numOfPairdOptions, shadowedStartPos, shadowedStrLen,
						i, shadowStringsLength);
					for(int ii = 0 ; ii < numOfPairdOptions ; ii++)
					{
						char complexShadow[MAX_STRING_LENGTH];
						CreateComplexShadow( complexShadow, shadowedElements[i],  shadowedElements[pairedOptionSet[ii]]  );
						
						bool isInDictionary = false;
						cHashObj* temoObj = NULL;
						if( dictionaryHash->IsLookUp(temoObj, complexShadow))
						{
							isInDictionary=true;
						}
						if(isGettingFinalHashFilled || isInDictionary)
						{
							cHashObj* tempData = NULL;
							if(onePatientHash->IsLookUp(tempData, complexShadow))
							{
								tempData->UpdateData(valStr);
							}
							else
							{
								tempData = new cHashObj(complexShadow, valStr);
								onePatientHash->SetValue(tempData,complexShadow, false);
								tempData = NULL;
							}
						}
					}
				}
			}

			delete[]	shadowedElements;
			delete[]	shadowedStartPos;
			delete[]	shadowedStrLen;
			delete []shadowedHashObjArr;
		}



		for(int i  = 0 ; i < numOfSubStrsOnePAragraph ; i++)
		{
			if(stss[i]!= NULL)
			{
				delete []stss[i];
				stss[i] = NULL;
			}
		}
		delete []stss;
		stss=NULL;
		if( posStartArr != NULL)
		{
			delete []posStartArr ;
			posStartArr =NULL;
		}
		if(lenArr != NULL)
		{
			delete []lenArr;
			lenArr=NULL;
		}
		
	}
}

void cParagraphAnalytics::	RemoveSubSetPhrases(cHashObj** phraseObjArray , int numOfPhraseHashObjects)
{
	int tyu=0;//3 3 23 *** first remove per sample and then   per sub string. if only ieft 0 phrases need to check
}

 
//	paragArray->AddPhraseObjArray( phraseObjArray ,   numOfPhraseHashObjects);
	
void cParagraphAnalytics::BuildPatientsPhraseMap(cHashObj **&phraseObjArray, int &numOfPhraseHashObjects,
	cPhraseHash* phraseHash , cStringHistogram*  globalHistogram, char** paragArray, 
	int numOfParags,  char* valueStr,  cPhraseHash* onePAtinetHash, cGlobals* globals, int levelOfShadow)
{
//	cPhraseHash* onePatientHash = new cPhraseHash(100000);
//	FillAllStringsOnePatient( onePatientHash, phraseHash ,paragArray, ptRecord );
	bool isGettingFinalHashFilled = false;//this fucntion is given we already ahve
	// the final hash called here the phraseHash with already original and shadow
	//strings. since it is not getting filled here, we ony captre strings
	//orignian or shadows only if alreday are in the phrase hash/ final hash

	for(int i =0; i <numOfParags ; i++)
	{
		//if phrase hash is full than one patine hash gets potentially both original and shadow phrase objets
		FillAllStringsOnePatientOneParag(
		     onePAtinetHash,  phraseHash,   paragArray, i,
		    valueStr,isGettingFinalHashFilled, globals, levelOfShadow );
//	CalculateMultipleSubStrings( stss, numOfSubStrsOnePAragraph, oneLine);
	}


	//int numOfHashObjects = onePatientHash->GetNumberOfHashObjects();
	phraseObjArray = NULL;// new  cHashObj*[numOfHashObjects ];
	numOfPhraseHashObjects = 0;
	onePAtinetHash->ExportHashToArray(phraseObjArray , numOfPhraseHashObjects);//3 3 23 cancel the sub string here to aftere sample

	//if any phrase object is a sub phrase of another , delete the smaller one. if a larger one happen to be found for the same
	//patient, even if it is a different score, lower or oppisite, the larger wins. if we did not have the larger since it is now
	//exist or not a pattern than ok. if there is a larger one with less or different but we dont have the sample size, it will
	//be better later
	//RemoveSubSetPhrases(phraseObjArray , numOfPhraseHashObjects);

	onePAtinetHash->DeleteHashContent();
}
//	}
/*	the cHashObj** objArray is a set of phrases that can be input for predictive model of patinet, first send to some 
	mean and sd reltions for many patients sets and then do the prediction. 
	for each value of the global universe values we build calibration model her. the output will be a histogram with probabilities for different values

	we then take for each value string, thinking what are the evidence to support a value of 0 or of 1, and then collect dimeniso

	one dimension is the phrase withi the max support odd fofr this value. here we start with all patients max phrase for this
	value and we give each their z score

	second dmension is the phrase with hightest odd for the other value or values. for exmaple if we goto for a person 1 one phras
	supporting any other value, not this value, and having a 1.5 odd for that, than 0/5 is a symetric score that will get to play a z

	this dimension, is the total significant symeric phrase score =, for example a person has 5 most syig to be 
	-1,2,0.5, -0.5, 1 than sum thne to be 2 .

	This patinet get a category which derived frmo a sym 2 sum of top phrases, z score of what 2 would be, and z score of -1

	go over all patinets and get these 3 values from each so we can get a z mean andn sd and go over all patients again
	for a test
	
	stthie value gt the highest odd symetricall. most paients will have some prase with 1.x but patient
	with no real tendenc for a 1 might have less. others wll have larger ones and then using symetri value it will be easier to havae
	sd for that. 
	
	
	need a map of phrases and their function reasl to collect certain value 
	out of the set of values and to get an input of value and the map of patinets to get categories. need to go voer a
	need a patinet map to collect the array and open more
*/

//	for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
//	{
		//m_patientRecorsObjectList[i]->;
//	}

//}




/*
bool cParagraphAnalytics::BuildPhraseDictionary(cPhraseHash* finalPhraseHash ,cStringHistogram*  globalHistogram, cGlobals* globals)
{
	int maxNumberOfPatientsFirstRun = 	globals->g_MAX_NUM_OF_PATIENTS_FIRST_RUN_PARAG  ;
  //3 3 23 *** put as low just to get test the features. rplace with 10000
	int mode = 1;
	if(m_actualyNumberOfPatients > maxNumberOfPatientsFirstRun)
	{
		mode = m_actualyNumberOfPatients / maxNumberOfPatientsFirstRun;
	}
	cPhraseHash* allPatientsHash  = new cPhraseHash(10000000);
	
	int subSetSampleSize = 0 ;
	for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
	{
		if( (i % mode) == 0 )
		{
			cPhraseHash* onePatientHash = new cPhraseHash(100000);
			cPhraseHash* dictionaryHash = NULL;
			FillAllStringsOnePatient( onePatientHash, dictionaryHash, m_paragrArray, m_patientRecorsObjectList[i] );
		
			MergeHash(allPatientsHash,onePatientHash);

			delete onePatientHash;
			onePatientHash = NULL;

			subSetSampleSize++;
		}
	}

	//

	double mutiSamle = ((double)( m_actualyNumberOfPatients )) /((double)(subSetSampleSize));
	double minSampleForSig = 50; //a small number to get chance 
	int effectiveSampleRequired =(int)( minSampleForSig / mutiSamle);
	effectiveSampleRequired = cVarianceCalc::Max(effectiveSampleRequired , 2);//just a local requiremets, not iportaht as to just cleaner
	allPatientsHash->CleanBasedOnSample(effectiveSampleRequired);
	allPatientsHash->AddShadowObjects();//for each remainded phrase use Shadow(str) and add
	//either a new hadh object or just adjust histgoram.
	//all patient hash will then allow final hash to get filled also due to shadows
	//int minSizeToBaseSigCleanFrom = 250;
	//allPatientsHash->CleanBasedOnSignificance(globalHistogram, 1.5,minSizeToBaseSigCleanFrom);//3 3 23 send( effectiveSampleRequired * 5) as min to have to remove 
//	cPhraseHash* finalPhraseHash  = new cPhraseHash(1000000);//3 3 23 remove the above clean . add a sample clean for final
	
 	for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
	{
		cPhraseHash* onePatientHash = new cPhraseHash(100000);
		FillAllStringsOnePatient( onePatientHash, allPatientsHash , m_paragrArray, m_patientRecorsObjectList[i] );
		MergeHash(finalPhraseHash,onePatientHash);

		delete onePatientHash;
		onePatientHash = NULL;

		
	}
	cHashObj* data= NULL;
	finalPhraseHash->IsLookUp(data, "airborne precautions maintained");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions;");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions;");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions;\n");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions;\nNone");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions:\nNone");
	finalPhraseHash->IsLookUp(data, "Isolation Precautions: airborne precautions maintained");
	finalPhraseHash->IsLookUp(data, "airborne precautions maintained");
	int sdgg=0;
	



	finalPhraseHash->CleanBasedOnSample(globals->g_minSampleSizeIngridient);
	//now we got the final and which is the same in the phrases but more content in the data so no need for the old allPatientHash
	delete allPatientsHash;
	allPatientsHash=NULL;

	return true;
	////////
}
*/



void cParagraphAnalytics::FindPotenetialPairedShadowed(int*& pairedOptionSet, int &numOfPairdOptions, 
					int* shadowedStartPos, int* shadowedStrLen,	int subectPhraseIndex,  int shadowStringsLength)
{

	int sdg=0;
	numOfPairdOptions = 0;
	pairedOptionSet = NULL;
	
	int posStartSubject = shadowedStartPos[ subectPhraseIndex];
	int posEndSubject = posStartSubject  + shadowedStrLen[ subectPhraseIndex] - 1;

	int maxGapForCombinations = 25;//30 charetectrs between the pos start to the left ragne


	int leftRangeLEft = posStartSubject - maxGapForCombinations;
	int leftRangeRight = posStartSubject - 1;
	int rightRangeLeft= posEndSubject +1;
	int rightRangeRight = posEndSubject + maxGapForCombinations;

	int movingPos = 0;
	for(int i = 0 ; i < shadowStringsLength ;i++)
	{
		if(subectPhraseIndex != i)
		{
			int posStartI = shadowedStartPos[i];
			int posEndI =  posStartI  + shadowedStrLen[ i] - 1;
			if (				(( posStartI >= leftRangeLEft) && (posEndI <=leftRangeRight)  )  ||
				(( posStartI >= rightRangeLeft  ) && ( posEndI <=  rightRangeRight ))  )
			{
			
				if(pairedOptionSet != NULL)
				{
					pairedOptionSet[movingPos] = i;
				}
				movingPos++;
			}
		
		}
	}
	numOfPairdOptions = movingPos;
	if(numOfPairdOptions > 0)
	{
		pairedOptionSet = new int[numOfPairdOptions];
		movingPos =0;
		for(int i = 0 ; i < shadowStringsLength ;i++)
		{
			if(subectPhraseIndex != i)
			{
				int posStartI = shadowedStartPos[i];
				int posEndI =  posStartI  + shadowedStrLen[ i] - 1;
				if (				(( posStartI >= leftRangeLEft) && (posEndI <=leftRangeRight)  )  ||
					(( posStartI >= rightRangeLeft  ) && ( posEndI <=  rightRangeRight ))  )
				{
			
					if(pairedOptionSet != NULL)
					{
						pairedOptionSet[movingPos] = i;
					}
					movingPos++;
				}
		
			}
		}
	}
}
		
void cParagraphAnalytics::CreateComplexShadow(char* complexShadowOut, char* subjectShadowed,  char* shadowedElement   )
{
	int sdf=0;
	complexShadowOut[0] = '~';
	strcpy(complexShadowOut+1 , subjectShadowed);
	int len = strlen(complexShadowOut);
//	complexShadowOut[len++]='~';
	strcpy(complexShadowOut+len,  shadowedElement);
}
					





int cParagraphAnalytics::BuildPhraseDictionaryNew(cPhraseHash* outHash , cPhraseHash* dictionHash ,
				 bool* isPatientIn,	cStringHistogram*  globalHistogram, cGlobals* globals,  int levelOfShadow)
{
	int subSetSampleSize=0;
	cPhraseHash* onePatientHash = new cPhraseHash(100000);
	bool isGettingFinalHashFilled = true;
	for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
	{
		if(isPatientIn == NULL || isPatientIn[i])
		{
	
			FillAllStringsOnePatient( onePatientHash, dictionHash, 
				m_paragrArray, m_patientRecorsObjectList[i], isGettingFinalHashFilled, globals, levelOfShadow );
			//"Isolation Precautions: airborne"
			cHashObj* data=NULL;
			if(dictionHash && dictionHash->IsLookUp(data, "Isolation"))
			{
				int sdg = 0 ; 
			}
			if(outHash->IsLookUp(data, "~isolationprecautions:"))
			{
				int sdg = 0 ; 
			}	
			if(outHash->IsLookUp(data, "~isolation"))
			{
				int sdg = 0 ; 
			}
			
			if(outHash->IsLookUp(data, "Isolation Precautions"))
			{
				int sdg = 0 ; 
			}
			if(outHash->IsLookUp(data, "Isolation"))
			{
				int sdg = 0 ; 
			}
			MergeHash(outHash,onePatientHash);
			 
			if(outHash->IsLookUp(data, "Isolation/Precautions:\nNone"))
			{
				int sdg = 0 ; 
			}
			if(outHash->IsLookUp(data, "Isolation"))
			{
				int sdg = 0 ; 
			}


			onePatientHash->DeleteHashContent();
			//onePatientHash = NULL;
			if(outHash->IsLookUp(data, "Isolation Precautions: airborne"))
			{
				int sdg = 0 ; 
			}


			subSetSampleSize++;
		}
	}
	cHashObj* data=NULL;
	if(outHash->IsLookUp(data, "Isolation/Precautions:\nNone"))
			{
				int sdg = 0 ; 
			}
	if(outHash->IsLookUp(data, "~isolationprecautionsnone"))
			{
				int sdg = 0 ; 
			}
	
	if(outHash->IsLookUp(data, "~isolation:contactformrsa"))
			{
				int sdg = 0 ; 
			}

	if(outHash->IsLookUp(data, "~isolation:contactfor"))
			{
				int sdg = 0 ; 
			}



	delete onePatientHash;
	onePatientHash = NULL;
	return subSetSampleSize;
}






/*
	ifstream inFile;
	inFile.open(m_filePath, ios::in);
	if(!(inFile.is_open()))
	{
		return false;
	}
	
	char oneLine[20000];
	int numberOfSubStringssAllRun = 0;
	bool endOfFile = false;
	actualyLineIndexx = 0;
	//11 1 22 delete this and replace with a new class strPatienetDup. use below for the exsist question.
	cStringAndIntDupCheck strPtnDup;

	

	int tooSmaleOrTooLargeCnt=0;
	int setExistCnt=0;
	int isExistCnt=0;
	while(!endOfFile)
	{
		//if(FileManager::ReadOneLine(oneLine, inFile))
		//-1 for ilegal line, 0 for end of fline, 1 for success getting a new line
		int retValue =  FileManager::ReadOneLineFlexibleEndOfLine
			(oneLine, inFile,   endOfParagInSign, delimiter);
		if(retValue == 1)
		{
			char value = -1;
			bool isExtracted = false;
			int patinetID = -1;
			if(IS_TWO_FIELDS_INPUT_FILE)
			{
				isExtracted = ExtractDictionaryValueFromLine(value, oneLine, delimiter ,  isRemoveSpaces);//takes one line few char shorter to end the line befoe the value.
				                                                                                          //extext the value separate 
			}
			else
			{
				isExtracted = ExtractDictionaryValueFromThreeFieldsLine(patinetID, value, oneLine, delimiter ,  isRemoveSpaces);//takes one line few char shorter to end the line befoe the value.
				                                                                                          //extext the value separate 
			}
			if(isExtracted)//ExtractDictionaryValueFromLine(value, oneLine, delimiter ,  isRemoveSpaces))//takes one line few char shorter to end the line befoe the value. extext the value separate 
			{
				if(lineArrr != NULL)
				{
					int strLen = strlen(oneLine);
					strlenArr[actualyLineIndexx] = strLen;
					lineArrr[actualyLineIndexx]= double(value);
				}
				actualyLineIndexx++;
				char** stss = NULL;
				int numOfSubStrsOnePAragraph = 0;
				CalculateMultipleSubStrings( stss, numOfSubStrsOnePAragraph, oneLine);
				if(stss != NULL)
				{
					for(int x = 0 ; x < numOfSubStrsOnePAragraph; x++)
					{
						bool isToPush = true;
						if( (( pushMode == 1) || (pushMode == 2) ) && (!IS_TWO_FIELDS_INPUT_FILE) && (patinetID >= 0  )) //that menas we have the thrid field patinet Id to remove sub strin duplications
						{//11 1 22 change to a class function return exist or not wih the iput of the string and patient id. do not modify the patient id frmo befoer
							bool isExist = strPtnDup.IsExist(stss[x],patinetID);
						 	if(isExist)// || isStringWithTooSmallSample )
							{
								isToPush = false;
								isExistCnt++;
							}
							else
							{
								bool isStringWithTooSmallSample = ( hashArr.GetstringSampleBucketNum(stss[x]) < MIN_SAMPLE_SIZE_FOR_SUB_STR_PATTERN) ;
								bool isStringWithTooLargeSample = ( hashArr.GetstringSampleBucketNum(stss[x]) > MAX_SAMPLE_TO_CARE_FOR_SAME_PT_DUP) ;
								if(isStringWithTooSmallSample || isStringWithTooLargeSample)
								{
									tooSmaleOrTooLargeCnt++;//setExistCnt
								}
								else
								{
									strPtnDup.SetExist(stss[x],patinetID);
									setExistCnt++;
								}
							}
						}
						if(isToPush)
						{
							hashArr.Push(stss[x], value , pushMode);//			
							numberOfSubStringssAllRun++;
						}
						delete []stss[x];
						stss[x]=NULL;
					}
					delete []stss;
				}

			}
		}
		else if(retValue == 0)
		{
			endOfFile =true;
		}
	}
	inFile.close();

//	delete []arrayOfPatinetSubStringFlaging;
	return true;

}
*/






//10 27 22
bool   cParagraphAnalytics::ExtractDictionaryValueFromThreeFieldsLineNEW(
	        	char*& paragrStr, char*& valueString, char*& ptIDstr, 
				char* oneLine, char delimiter, bool isRemoveSpaces)//takes one line few char shorter to end the line befoe the value.
{
	int numOfFields = FileManager::CountFields( oneLine, delimiter);// 
	if( (numOfFields == 3)  )
	{
		int strLenght = strlen(oneLine);
		int indexOfDelimited1 = -1;
		int indexOfDelimited2 = -1;
		for(int j = 0 ; j < strLenght ; j++)
		{
			if(oneLine[j] == delimiter)
			{
				if(indexOfDelimited1 < 0)
				{
					indexOfDelimited1 = j;
				}
				else
				{
					indexOfDelimited2 = j;
				}
			}
		}
		int valStrLen = indexOfDelimited2 - indexOfDelimited1 - 1;//for example "3-4-9" if - is delimied than 3 - 1 - 1 = 1,  1 is our value string len with the digit 4
		
		valueString = new char[valStrLen+1];
	//	char valueStr[100];
		for(int j = 0 ; j< valStrLen ; j++)
		{
			valueString[j] = oneLine [indexOfDelimited1 + 1 + j];
		}
		valueString[valStrLen]=0;

	//	value = char(  FileManager::ConvertWordToInt(valueStr));

		int patinetIDstrLen = strLenght - indexOfDelimited2 - 1;
		ptIDstr = new char[patinetIDstrLen+1];
		strcpy(ptIDstr, oneLine + indexOfDelimited2 + 1);
		//patinetID =// FileManager::ConvertWordToInt(patIdStr);
		//		cHashObjectArray::Hashfunction(patIdStr, PATIENT_GROUPS_NUMBER_FOR_PREVENTING_SAME_PATIENT_MULTI_SUB_STRINGS);

		int newOneLineLenth = indexOfDelimited1; // for example if i got 3-4-9^ when - is delimiter and ^ end of line than first - is in index 1 and string len of digit 3 is also 1
		oneLine[newOneLineLenth] = 0;
		paragrStr = new char[newOneLineLenth+1];
		strcpy(paragrStr, oneLine);


		//remove spaces when needed
		StandartizationRemoveSpacecs(paragrStr, newOneLineLenth , delimiter, isRemoveSpaces);
		paragrStr[newOneLineLenth] = 0;
		return true;
	}
	return false;
}



//10 27 22
bool   cParagraphAnalytics::ExtractDictionaryValueFromThreeFieldsLine(int &patinetID, char &value,   char* oneLine, char delimiter, bool isRemoveSpaces)//takes one line few char shorter to end the line befoe the value.
{
	int numOfFields = FileManager::CountFields( oneLine, delimiter);// 
	if( (numOfFields == 3)  )
	{
		int strLenght = strlen(oneLine);
		int indexOfDelimited1 = -1;
		int indexOfDelimited2 = -1;
		for(int j = 0 ; j < strLenght ; j++)
		{
			if(oneLine[j] == delimiter)
			{
				if(indexOfDelimited1 < 0)
				{
					indexOfDelimited1 = j;
				}
				else
				{
					indexOfDelimited2 = j;
				}
			}
		}
		int valStrLen = indexOfDelimited2 - indexOfDelimited1 - 1;//for example "3-4-9" if - is delimied than 3 - 1 - 1 = 1,  1 is our value string len with the digit 4
		char valueStr[100];
		for(int j = 0 ; j< valStrLen ; j++)
		{
			valueStr[j] = oneLine [indexOfDelimited1 + 1 + j];
		}
		value = char(  FileManager::ConvertWordToInt(valueStr));

		int patinetIDstrLen = strLenght - indexOfDelimited2 - 1;
		char patIdStr[100];
		strcpy(patIdStr, oneLine + indexOfDelimited2 + 1);
		patinetID =// FileManager::ConvertWordToInt(patIdStr);
				cHashObjectArray::Hashfunction(patIdStr, PATIENT_GROUPS_NUMBER_FOR_PREVENTING_SAME_PATIENT_MULTI_SUB_STRINGS);

		int newOneLineLenth = indexOfDelimited1; // for example if i got 3-4-9^ when - is delimiter and ^ end of line than first - is in index 1 and string len of digit 3 is also 1
		oneLine[newOneLineLenth] = 0;
		//remove spaces when needed
		StandartizationRemoveSpacecs(oneLine, newOneLineLenth , delimiter, isRemoveSpaces);
		oneLine[newOneLineLenth] = 0;
		return true;
	}
	return false;
}
		
//standardization function
bool cParagraphAnalytics::ExtractDictionaryValueFromLine( char &value,   char* oneLine, char delimiter, bool isRemoveSpaces)
{
	int numOfFields = FileManager::CountFields( oneLine, delimiter);// 
	if( (numOfFields == 2)  )
	{
		int strLenght = strlen(oneLine);
		int indexOfDelimited = -1;
		for(int j = 0 ; j < strLenght ; j++)
		{
			if(oneLine[j] == delimiter)
			{
				indexOfDelimited = j;
			}
		}
		int secondStrLen = strLenght - indexOfDelimited - 1;//for example "3-4" if - is delimied than str len is 3 and index of delimited is 1 so 3-1-1 = 1 which is the len of 4
		char valueStr[100];
		strcpy(valueStr, oneLine + indexOfDelimited + 1);//to copy the "4" only too valueStr
			
		value = char(  FileManager::ConvertWordToInt(valueStr));
	
		int newOneLineLenth = strLenght - secondStrLen - 1;
		oneLine[newOneLineLenth] = 0;
		//remove spaces when needed
		StandartizationRemoveSpacecs(oneLine, newOneLineLenth , delimiter, isRemoveSpaces);
		oneLine[newOneLineLenth] = 0;
		return true;
	}

	return false;
}
void cParagraphAnalytics::StandartizationRemoveSpacecs(char* oneLine, int &newOneLineLenth, char delimiter, bool isRemoveSpaces)
{ 
	if(!isRemoveSpaces )
	{
		return;//no need to remove spaces if that shows
	}
	int targetIndex = 0;
	for(int x = 0 ; x < newOneLineLenth ; x++)
	{
//logic:
//if this x is not a space than move on and copy it, or
//it is a space abd the bext one is not a space than move / copy
//or if it is a space and next one is not end of str than move / copy too
		bool isToCopy = true;
		if( x==0 && oneLine[x] == ' ')
		{
			isToCopy = false;//if the first char is space
		}
		if( x>0 && oneLine[x] == ' ' && oneLine[x-1] == '\n' )
		{
			isToCopy = false;//if the first char is space
		}
		if( oneLine[x] == ' ' && oneLine[x+1] == ' ')
		{
			isToCopy = false;//with two spaces we need only one so we do not copy this one if one after is a space
		}
		if( oneLine[x] == ' ' && oneLine[x+1] == '\n')
		{
			isToCopy = false;//with a  spaces and one after an end of line than do not copy this space
		}
		if( oneLine[x] == ' ' && (x == newOneLineLenth -1)  )//last char is space
		{
			isToCopy = false;//with a  spaces and one after end of string
		}
		if( oneLine[x] == ' ' && oneLine[x+1] == delimiter )
		{
			isToCopy = false;//with a  spaces and one after an end of line than do not copy this space
		}
		if(isToCopy)
		{
			oneLine[targetIndex++] = oneLine[x];
		}	
	}
	newOneLineLenth = targetIndex;
	
}




//10 8 22 t 
/*
start with input moving index + 1 (we dont get same as last time to have new start) and stop according to what can be a first char. 
if we got xxx yyy  than arr[3] is space so if input first char is 3 than 4 can be the first new char since 4 is a first word letter. so need to check
that the next char or other is a first letter 

*/
void cParagraphAnalytics::CollectNextFirstChar(bool &isFound, bool &isEnd, int &movingIndexFirstChar,  char* line, int len)
{
	int index = movingIndexFirstChar +1;
	isFound = false;
	isEnd = false;
	while(!isFound && !isEnd)
	{
		if(index>= len)
		{
			isEnd = true;
		}
		else if(  (index == 0 ) && IsValidAsFirstChar(line[index]) ) //if this char is a valid to start
		{
				isFound = true;
		}		
		else if(  ( line[index - 1] == ' ') && IsValidAsFirstChar(line[index]))
			//if last char before that was space, or this is the first char
		{
			isFound = true;
		}
		else if(  ( line[index - 1] == '\n') && IsValidAsFirstChar(line[index]))
			//if last char before that was space, or this is the first char
		{
			isFound = true;
		}
		else if( IsSign(line[index - 1]) && IsValidAsFirstChar(line[index])) //if this char is a valid to start
		{
			isFound = true;
		}		
		else if( IsDigit(line[index-1]) && IsLetter(line[index]))
		{
			isFound = true;
		}
		else if( IsLetter(line[index-1]) && IsDigit(line[index]))
		{
			isFound = true;
		}
		if(isFound )
		{
			movingIndexFirstChar = index;
		}
		index++;
	}
	 
}

void cParagraphAnalytics::CollectNextLastChar(
	bool &isFound, bool &isEnd,
	int &movingIndexFirstChar, int &movingIndexLastChar, int maxSize, char* line, int len)
{
	int index = movingIndexLastChar +1;
	isFound = false;
	isEnd = false;
	while(!isEnd && !isFound)
	{
		if(  (index >= len) || (index >=  ( movingIndexFirstChar + maxSize ) ))
		{
			isEnd = true;
		}
		bool isGoodLastChar = false;
		if( IsSign(line[index] ))
		{
			isGoodLastChar  = true;
		}
		if(IsLetter(line[index] ) && (!IsLetter(line[index+1])))
		{
			isGoodLastChar  = true;
		}
		if(IsDigit(line[index] ) && (!IsDigit(line[index+1])))
		{
			isGoodLastChar  = true;
		}
		if(!IsValidAsFirstChar(line[index]))//if it is not a sign or letter or digit than each such unknwon char can try its way to be last
		{
			if(line[index] != ' ')
			{
				isGoodLastChar  = true;
			}
		}
		if(isGoodLastChar)
		{
			isFound = true;
			movingIndexLastChar = index;
		}
		index++;
	}

}


void cParagraphAnalytics::MultiStringManipulation(char** stss,int *posStartArr, int &numOfSubStrs,
	char* oneLine, int len, int maxSubStrSizee)
{
	int movingIndexFirstChar = -1;//we always try to find a ward from one after the last start word index. so first call get the 0 index 
	numOfSubStrs=0;
	bool end = false;
	int maxNumOfStrings = 10000;
	char** localStss = new char*[maxNumOfStrings];//1000000];
	int localStrIndex = 0;//localStss
	while(!end)
	{
		bool isFound = false;
		bool isEnd = false;
		CollectNextFirstChar(isFound, isEnd, movingIndexFirstChar,oneLine, len );//first call output should be 0
		bool nEnd = false;
		if(isEnd || !isFound)//if we are done with the line or not able to find anymore than all is set and go out
		{
			end = true;
		}
		int movingIndexLastChar = movingIndexFirstChar;//it will then have to be at least one after the first char
		while(!end && !nEnd)
		{
			bool nextIsFound = false;
			bool nextIsEnd = false;
			CollectNextLastChar(nextIsFound, nextIsEnd,movingIndexFirstChar, movingIndexLastChar, maxSubStrSizee, oneLine, len);
			if(nextIsEnd || !nextIsFound)
			{
				nEnd = true;
			}
			
			if(!nEnd  )
			{
				
				int subStrLength = (movingIndexLastChar - movingIndexFirstChar ) + 1;;
				localStss[localStrIndex] = new char[subStrLength+1];
				for(int j = 0 ; j < subStrLength; j++)
				{
					localStss[localStrIndex][j] = oneLine[movingIndexFirstChar + j];
				}
				localStss[localStrIndex][subStrLength] = 0;
				
				bool isFirsstTimeStr = true;
				for(int ii = 0 ; ii<localStrIndex ; ii++)//sinsce i did not yet increment the
												//localStrIndex i am not checking the actual this one
				{
					if(!strcmp(localStss[ii],localStss[localStrIndex]))
					//if(false)
					{
						isFirsstTimeStr = false;
					}
					else
					{
						int sss=0;
					}
				}
				if(isFirsstTimeStr)
				{
					if(stss != NULL)
					{
						stss[numOfSubStrs]=	 new char[subStrLength+1];
						for(int j = 0 ; j < subStrLength+1; j++)
						{
							stss[numOfSubStrs][j] = localStss[localStrIndex][j]; 
						}
						posStartArr[numOfSubStrs] = movingIndexFirstChar;
					}
					numOfSubStrs++;
				}
				localStrIndex++;
				if(localStrIndex == maxNumOfStrings)
				{
					end = true;
				}

			}
			else
			{
				nEnd = true;
			}
		}
	}

	for(int i = 0 ; i < localStrIndex ; i++)
	{
		delete []localStss[i];
	}
	delete []localStss;
}

void cParagraphAnalytics::CalculateMultipleSubStrings(char**& stss, int*& posStartArr, int*& lenArr,  
													int &numOfSubStrs, char* oneLine,  cGlobals* globals)
{
	int len = strlen(oneLine);
	bool end = false;
	numOfSubStrs=0;
	int maxSubStrSize = MAX_NUM_OF_CHARS_PER_SUBSTRING;

	int numOfStrs=0;
	MultiStringManipulation(NULL, NULL,numOfStrs,   oneLine,  len,  maxSubStrSize);
	numOfSubStrs = numOfStrs;
	
	stss = new char*[numOfSubStrs];
	posStartArr = new int[numOfSubStrs];
	lenArr = new int[numOfSubStrs];
	numOfStrs=0;
	MultiStringManipulation(stss, posStartArr, numOfStrs,   oneLine,  len,  maxSubStrSize);

	for(int i = 0 ; i < numOfStrs ; i++)
	{
		lenArr[i] = strlen(	stss[i]);
	}


	int* indexArrOfNegativePhrases = new int[numOfStrs];
	bool* isNegativeArr = new bool[numOfStrs];
	FillIsNegativeStrings(isNegativeArr, stss, numOfStrs);
	int movingNumOfNegIndexes = 0;
	for(int i = 0 ; i < numOfStrs ; i++)
	{
		if(	isNegativeArr[i])
		//	IsStringgNegative(stss[i]))
		{
			indexArrOfNegativePhrases[movingNumOfNegIndexes++] = i;
		}
	}

	bool* isIn = new bool[numOfStrs];
	for(int i = 0 ; i < numOfStrs ; i++)
	{
		isIn[i] = true;
	}
	for(int x = 0 ; x < movingNumOfNegIndexes ; x++)
	{
		int negStartPos = posStartArr[ indexArrOfNegativePhrases[x]];
		int negLen = lenArr[ indexArrOfNegativePhrases[x]];
		int negEndPos = negStartPos + negLen - 1;
	//	int posStillInNegativeArea = negEndPos + 20;//4 5 23 need to move to better m ethod and contrtol. problem is if the next
		
		int maxNegReachedPos =  negEndPos +1;
		
		bool end = false;
		while((maxNegReachedPos < len) && (!end))//(maxNegReachedPos <( negEndPos + 30)) )
		{
			if(maxNegReachedPos >= ( negEndPos + 40) )
			{
				end = true;
			}
			if(oneLine[maxNegReachedPos] == '.' ||  oneLine[maxNegReachedPos] == '?'||
				oneLine[maxNegReachedPos] == globals->g_endOfLineInSign ||  oneLine[maxNegReachedPos] == globals->g_delimiter )
			{
				end = true;
			}
			maxNegReachedPos++;
		}
		
		//oneLine len

		
		int posStillInNegativeArea = maxNegReachedPos;
		
		
		//words are structured that has longer and sub set of that down the  string, these may be more than this 20 but their longer
		//version
		for(int ii = 0 ; ii < numOfStrs ; ii++)
		{
			int posEndCandidatePhrase =  posStartArr[ii] + lenArr[ii] - 1;
			if(
				(posStartArr[ii] > negEndPos) &&
				( posEndCandidatePhrase <= posStillInNegativeArea )&&
				(   posStartArr[ii]  < posStillInNegativeArea     )
				
				)
			{
				isIn[ii] = false;
			}
		}
	}
	int movingNumOfStrs = 0;
	for(int i = 0 ; i < numOfStrs ; i++)
	{
		if(isIn[i])
		{
			stss[movingNumOfStrs] =  stss[i];
			posStartArr[movingNumOfStrs] =    posStartArr[i];
			lenArr[movingNumOfStrs] =    lenArr[i];
			movingNumOfStrs++;
		}
		else
		{
			delete []stss[i];
			stss[i]=NULL;
			posStartArr[i] = -1;//just temporary default values untill overriden by higher indexes at the compress time
			lenArr[i]=0;
		}
	}
	numOfSubStrs = movingNumOfStrs;



	delete []indexArrOfNegativePhrases;
	delete []isIn;
	delete []isNegativeArr;
}

//predTwoDimArray[ii][i],  depTwoDimArray[ii][i],
//					patientMapObj->m_valueStr,	globalHistogram->GetValueArr(ii), predArr , strValueArr, numOfValues
//double cParagraphAnalytics:: GetRelevantPredictionAndDependent(double &pred, double &dep,char* valStrThisPatient,
//    char* valStrOfModel, double* predArr , strValueOfPRedictionArr, numOfValues);


double cParagraphAnalytics::GetRelevantPrediction( 
						char* globalValStr, double* predArr , char** strValueArr, int numOfValues)
{
	for(int i = 0 ; i < numOfValues ; i++)
	{
		if(   !strcmp(globalValStr, strValueArr[i]))
		{
			return predArr[i];
		}
	}
	return 0.0;
}
 

bool cParagraphAnalytics::AnalyticsProcess(	cGlobals *globals)
{
	char hashInDiscFileName[200];
	strcpy(hashInDiscFileName , "hashInDiscFileName.txt");
	char tempHashInDiscFileName[200];
	strcpy(tempHashInDiscFileName , "tempHashInDiscFileName.txt");
	
	bool isHashAlreadyBuild= false;
	cPhraseHash* finalPhraseHash  = NULL;
	cArrayFlex* arrayFlexHashAndHistogram = NULL;
	cStringHistogram*  globalHistogram = NULL;//new cStringHistogram();
	if( rename (hashInDiscFileName, tempHashInDiscFileName) != 0) //4 26 23 change and fix the code here
	{
		isHashAlreadyBuild = false;
	}
	else
	{
		isHashAlreadyBuild=true; //the rename is succesful
	}
	if(isHashAlreadyBuild )
	{
		arrayFlexHashAndHistogram = new cArrayFlex(tempHashInDiscFileName,false);//fasle for not write mode, means Read mode
		finalPhraseHash = new cPhraseHash(); 
		globalHistogram =new cStringHistogram();
		finalPhraseHash->ReadWriteHash( arrayFlexHashAndHistogram  ,  globals);
		globalHistogram->ReadWriteHistObject(arrayFlexHashAndHistogram,globals);
		delete arrayFlexHashAndHistogram;

		if( rename (tempHashInDiscFileName, hashInDiscFileName) != 0) //4 26 23 change and fix the code here
		{
			bool iiiii = false;
		}
		else
		{
			bool iiiiisss =true; //the rename is succesful
		}	
	}
	else
	{
		arrayFlexHashAndHistogram  = new cArrayFlex(hashInDiscFileName,true);
		finalPhraseHash  = new cPhraseHash(1000000);
		globalHistogram =new cStringHistogram();

		int actualyLineIndex=0;	
		BuildArraysOfParagaphsValueAndPtID(
			m_paragrArray, m_valueArray, m_ptIDarray,m_numberOfParagraphs   ,	globals->g_endOfParagraphInSign,
			globals->g_delimiter , globals->g_isRemoveExtraSpaces, m_filePath);
		BuildPatientRecordObjects(m_maxNumberOfPatients,m_patientRecorsObjectList,m_actualyNumberOfPatients,
			m_numberOfParagraphs, m_ptIDarray,  m_valueArray, m_paragrArray);
	 
		for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
		{
			char* valuStr = m_patientRecorsObjectList[i]->GetValueStr();
			globalHistogram->AddHistValue(valuStr);
		}
	
		int maxNumberOfPatientsFirstRun = globals->g_MAX_NUM_OF_PATIENTS_FIRST_RUN_PARAG  ;
	  //3 3 23 *** put as low just to get test the features. rplace with 10000
		int mode = 1;
		if(m_actualyNumberOfPatients > maxNumberOfPatientsFirstRun)
		{
			mode = m_actualyNumberOfPatients / maxNumberOfPatientsFirstRun;
		}
		
		bool* isPatientIn = new bool[m_actualyNumberOfPatients];
		for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
		{
			isPatientIn[i] = false;
			if((i % mode) == 0 )
			{
				isPatientIn[i] = true;
			}
		}
		
		cPhraseHash* allPatientsHash  = new cPhraseHash(10000000);
		int levelOfShadow = 0;
		//this time sending with no dictionary hash and so the allPatientsHash is only filled with shadows - check
		int subSetSampleSize = BuildPhraseDictionaryNew(allPatientsHash ,  NULL  , isPatientIn, globalHistogram,  globals, levelOfShadow);
		cHashObj* data = NULL;
		double mutiSamle = ((double)( m_actualyNumberOfPatients )) /((double)(subSetSampleSize));
		double minSampleForSig = globals->g_minSampleSizeIngridient / 3; //a smaller number to get chance 
		int effectiveSampleRequired =(int)( minSampleForSig / mutiSamle);
		effectiveSampleRequired = cVarianceCalc::Max(effectiveSampleRequired , 4);//3 3 23 *** replace 1 with a golbal parameter 
		//and make it more than 1 when having larger data set just a local requiremets, not iportaht as to just cleaner
	
		allPatientsHash->CleanBasedOnSample(effectiveSampleRequired);
		cPhraseHash* tempFinalPhraseHashh  = new cPhraseHash(1000000);
		levelOfShadow = 1;
		BuildPhraseDictionaryNew(tempFinalPhraseHashh ,  allPatientsHash  , NULL, globalHistogram,  globals, levelOfShadow);
		
		tempFinalPhraseHashh->CleanBasedOnSample(globals->g_minSampleSizeIngridient);//3 3 23 reduce sig to lower
		tempFinalPhraseHashh->CleanBasedOnSignificance(globalHistogram,1.5,globals->g_minSampleSizeIngridient);
		levelOfShadow = 2;
		BuildPhraseDictionaryNew(finalPhraseHash ,  tempFinalPhraseHashh  , NULL, globalHistogram,  globals, levelOfShadow );
		finalPhraseHash->CleanBasedOnSample(globals->g_minSampleSizeIngridient);
		//4 1 23 here need to clean the leanin and 
		finalPhraseHash->CleanBasedOnSignificance(globalHistogram,1.5,globals->g_minSampleSizeIngridient);
		//add list of ruels with ~ shaow sign but have no sample size and no odd ratio therefore. so it will fall 
		//during prediction, unless adding a ru le there saying that shwdow with 1 smale lsize is a manual lrule
		finalPhraseHash->AddManualPhrases(globals->g_manuelPhrasesFilePath, globals);

		delete tempFinalPhraseHashh;
		tempFinalPhraseHashh=NULL;

		finalPhraseHash->ReadWriteHash( arrayFlexHashAndHistogram  ,  globals);
		globalHistogram->ReadWriteHistObject(arrayFlexHashAndHistogram,globals);
		delete arrayFlexHashAndHistogram;
		arrayFlexHashAndHistogram=NULL;
	}

	int numOfValues = globalHistogram->GetSize();
	
	bool isAlreadyMOdelBult = false;
	char tempFileFlex[100];
	strcpy(tempFileFlex , "tempReadWriteFromDiscFile.txt");

 	if( rename (globals->g_readwriteArraFlex, tempFileFlex) != 0) //4 26 23 change and fix the code here
	{
		isAlreadyMOdelBult = false;
	}
	else
	{
		isAlreadyMOdelBult=true; //the rename is succesful
	}
	
	if(isAlreadyMOdelBult)//4 26 23 add a check if able to rename the "flex read write file" to something than it means we have it ready from before. if 
		//not, than it is like the "true" here, and if it is a case of rename, it is a false and 
	{
		bool isWriteMode = false;
		cArrayFlex* arrayFlex = new cArrayFlex(tempFileFlex,isWriteMode);
		WriteOrReadToDiscPAragraphModel(arrayFlex, 	m_paragPRedMode , numOfValues, globals);
		delete arrayFlex;
		arrayFlex = NULL;
		if( rename (tempFileFlex , globals->g_readwriteArraFlex) != 0) //4 26 23 change and fix the code here
		{
			int sdfg=0.0;//error
		}
		else
		{
			int sdgg =0;
		}
	}
	else
	{
		cPatientMapElements** patientMapArrayy= new cPatientMapElements* [m_actualyNumberOfPatients];

		for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
		{
			patientMapArrayy[i] = new cPatientMapElements(numOfValues);
		}
		cPhraseHash* onePAtinetHash = new cPhraseHash(10000);
		for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
		{
			char** listOfParagraphOfOnePatient = NULL;
			int numberOFPAragraphs = 0;
			m_patientRecorsObjectList[i]->CreateArrayAndCollectListOfPAragraphs(
								listOfParagraphOfOnePatient, numberOFPAragraphs, m_paragrArray);
		//3 3 23 *** make this the way to accept real time patinet and get map and all needed for sort paragraphs
			int levelOfShadow = 2;
			CollectPatientProfileParagraphs( patientMapArrayy[i],
				listOfParagraphOfOnePatient , numberOFPAragraphs,  finalPhraseHash, 
				globalHistogram, m_patientRecorsObjectList[i]->GetValueStr(), onePAtinetHash  , finalPhraseHash, 
																		globals, levelOfShadow );
	
			if(listOfParagraphOfOnePatient!= NULL)
			{
				delete []listOfParagraphOfOnePatient;
				listOfParagraphOfOnePatient= NULL;
			}
		}
		delete onePAtinetHash;
		onePAtinetHash = NULL;

		int numOfValues = globalHistogram->GetSize();
		m_paragPRedMode = new cParagraphPredModel*[numOfValues];

		
		ofstream outfile;  
		outfile.open(globals->g_internalPerformanceReportFilePath ,  ios::out);
		FileManager::WriteOneLine(outfile,"Internal Performance Data: ",globals->g_endOfLineInSign);
		for(int x = 0 ; x < numOfValues ; x++)//Create
		{//3 3 23 *** missing code
			FileManager::WriteOneLine(outfile,"value string: ",globals->g_endOfLineInSign);
			FileManager::WriteOneLine(outfile,globalHistogram->GetValueArr(x),globals->g_endOfLineInSign);
			CreateParagPredModel(  patientMapArrayy,	m_actualyNumberOfPatients ,x, globalHistogram->GetValueArr(x), globals);
			double stretch = m_paragPRedMode[x]->CalculateStretch();
			char stretchStr[100];
			sprintf(stretchStr, "%f", stretch);
			FileManager::WriteOneLine(outfile,"Stretch: ",globals->g_endOfLineInSign);
			FileManager::WriteOneLine(outfile, stretchStr , globals->g_endOfLineInSign);
			//FileManager::WriteOneLine(outfile,"",globals.g_endOfLineInSign);
			for(int y = 0 ; y < m_paragPRedMode[x]->GetNumberOfBuckets()  ; y++)
			{
				WriteParagraoPredOneBcket(m_paragPRedMode[x]->GetTableBucket()[y], &outfile,  globals  );  //GetNumberOfBuckets()[y], &outfile );
			}
			FileManager::WriteOneLine(outfile, "" , globals->g_endOfLineInSign);
			FileManager::WriteOneLine(outfile, "" , globals->g_endOfLineInSign);
			FileManager::WriteOneLine(outfile, "" , globals->g_endOfLineInSign);
			FileManager::WriteOneLine(outfile, "" , globals->g_endOfLineInSign);
			int sdg=0;
		}
		outfile.close();
		bool isWriteMode=true;
		cArrayFlex* arrayFlex = new cArrayFlex(globals->g_readwriteArraFlex,isWriteMode);
		WriteOrReadToDiscPAragraphModel(arrayFlex, 	m_paragPRedMode , numOfValues, globals);
		delete arrayFlex;
		arrayFlex=NULL;

		for(int i = 0 ; i < m_actualyNumberOfPatients ; i++)
		{
			delete patientMapArrayy[i];
			patientMapArrayy[i]=NULL;
		}
		delete []patientMapArrayy;
		patientMapArrayy=NULL;

	}

	if((globals->g_isToConductPerformanceTests == 'Y')||(globals->g_isToConductPerformanceTests == 'y'))
	{
		cPhraseHash* onePAtinetHash = new cPhraseHash(10000);
		int numberOfParagraphs=0;
		char** ptIDarray=NULL;
		char** valueArray=NULL;
		char** paragrArray=NULL;
		BuildArraysOfParagaphsValueAndPtID(
			paragrArray, valueArray, ptIDarray,numberOfParagraphs   ,
			globals->g_endOfParagraphInSign,
			globals->g_delimiter , globals->g_isRemoveExtraSpaces, globals->g_patientTestFilePath);

		cPatientRecordObject** patientRecorsObjectList = NULL;
		int actualyNumberOfPatients=0;
		BuildPatientRecordObjects(m_maxNumberOfPatients,patientRecorsObjectList,actualyNumberOfPatients,
			numberOfParagraphs, ptIDarray,  valueArray, paragrArray);
	
		double** predTwoDimArray = new double*[globalHistogram->GetSize()];
		double** depTwoDimArray =  new double*[globalHistogram->GetSize()];
		for(int v = 0 ; v < globalHistogram->GetSize() ; v++)
		{
			predTwoDimArray[v] = new double[actualyNumberOfPatients];
			depTwoDimArray[v]= new double[actualyNumberOfPatients];
			for(int i = 0 ; i < actualyNumberOfPatients ; i++)
			{
				predTwoDimArray[v][i] = 0.0;
				depTwoDimArray[v][i]=0.0;
			}
		
		}
		for(int i = 0 ; i < actualyNumberOfPatients ; i++)
		{
			if(i==129)//10 1 23 fist step collect all patient paragraphs in one two dim arrary
			{
				int sdg = 0 ; 
			}
			char** listOfParagraphOfOnePatient = NULL;
			int numberOFPAragraphss = 0;
			patientRecorsObjectList[i]->CreateArrayAndCollectListOfPAragraphs(
							listOfParagraphOfOnePatient, numberOFPAragraphss, paragrArray);
	//3 3 23 *** make this the way to accept real time patinet and get map and all needed for sort paragraphs
			cPatientMapElements* patientMapObj = new cPatientMapElements(globalHistogram->GetSize());
			int levelOfShadow=2;
			CollectPatientProfileParagraphs( patientMapObj,
				listOfParagraphOfOnePatient , numberOFPAragraphss,  finalPhraseHash, 
				globalHistogram, patientRecorsObjectList[i]->GetValueStr(), onePAtinetHash  , finalPhraseHash, 
																	globals, levelOfShadow );
			double* predArr=NULL;
			double* referanceDistriArr=NULL;
			char** strValueArr=NULL;
			int numOfValues=0;
			double highestOddRAtio=0.0;
			CollectResultsAndPrint(		predArr, referanceDistriArr,strValueArr,numOfValues,
					highestOddRAtio,  listOfParagraphOfOnePatient ,  numberOFPAragraphss,	 finalPhraseHash,  globals,
					globalHistogram, NULL, NULL); //when queryInFilePAth is NULL than we dont print
		
			onePAtinetHash->DeleteHashContent();
			for(int ii = 0 ; ii < numOfValues ; ii++)
			{
				predTwoDimArray[ii][i] =  GetRelevantPrediction( 
						globalHistogram->GetValueArr(ii), predArr , strValueArr,  numOfValues);
				depTwoDimArray[ii][i] = 0.0;
				if(  !strcmp(patientMapObj->m_valueStr, 	globalHistogram->GetValueArr(ii)))
				{
						depTwoDimArray[ii][i] = 1.0;
				}
				//GetRelevantPredictionAndDependent(predTwoDimArray[ii][i],  depTwoDimArray[ii][i],
				//	patientMapObj->m_valueStr,	globalHistogram->GetValueArr(ii), predArr , strValueArr, numOfValues);
			}		
			
			for(int ii = 0 ; ii < numOfValues ; ii++)
			{
				if(	(strValueArr  != NULL ) && (strValueArr[ii]!= NULL))
				{
					delete []strValueArr[ii];
					strValueArr=NULL;
				}
			}
			if(strValueArr  != NULL )
			{
				delete []strValueArr;
				strValueArr=NULL;
			}		
			if(predArr != NULL)
			{
				delete []predArr;
				predArr=NULL;
			}
			if(referanceDistriArr != NULL)
			{
				delete []referanceDistriArr;
				referanceDistriArr=NULL;
			}
			delete []	listOfParagraphOfOnePatient	;
	
			delete patientMapObj;

		}

		char endOfParagraphInSign = globals->g_endOfParagraphInSign;
		globals->g_endOfParagraphInSign = '\n';
		char endOfLineInSign  = globals->g_endOfLineInSign;
		globals->g_endOfLineInSign = '\n';
	
		char endOfParagraphOutSign = globals->g_endOfParagraphOutSign;
		globals->g_endOfParagraphOutSign = '\n';
		char endOfLineOutSign = globals->g_endOfLineOutSign;
		globals->g_endOfLineOutSign ='\n';
		cArrayFlex* arrayFlexx = new cArrayFlex("performance summary file.txt",true);
		arrayFlexx->WriteReadArrayString("performane count and value array",true, *globals);
	//	globals->g_endOfParagraphInSign
		for(int v = 0 ; v < globalHistogram->GetSize() ; v++)
		{
			int numOfPerformanceSubGrps = 20;
			double threshArr[100];
			cProfileObject::CalculateThresholds(threshArr , numOfPerformanceSubGrps,
														predTwoDimArray[v],NULL,actualyNumberOfPatients);

			double depAvg = 0.0;
			double avgDepArr[100];
			int cntArr[100];
			cProfileObject::CreateAvgDepSubGrps(NULL,avgDepArr,threshArr ,cntArr, depAvg, numOfPerformanceSubGrps,
					predTwoDimArray[v],depTwoDimArray[v], NULL, actualyNumberOfPatients, *globals);

			int iiiiii=0;

			arrayFlexx->WriteReadArrayString("value for model index : ",true, *globals);
			arrayFlexx->WriteReadArrayInt(v,true, *globals);
			arrayFlexx->WriteReadArrayString(" ",true, *globals);
			
			arrayFlexx->WriteReadArrayInt(numOfPerformanceSubGrps,true, *globals);
			for ( int i = 0 ; i < numOfPerformanceSubGrps ; i++)
			{
				arrayFlexx->WriteReadArrayDouble(avgDepArr[i],true, *globals);
				arrayFlexx->WriteReadArrayString(" ",true, *globals); //threshArr
				arrayFlexx->WriteReadArrayDouble(threshArr[i],true, *globals);
				arrayFlexx->WriteReadArrayString(" ",true, *globals); // 
				arrayFlexx->WriteReadArrayInt(cntArr[i],true, *globals);
				arrayFlexx->WriteReadArrayString(" ",true, *globals);
			}
			arrayFlexx->WriteReadArrayString("End of Model",true, *globals);
		}
		delete arrayFlexx;
		arrayFlexx = NULL;
		globals->g_endOfParagraphInSign = endOfParagraphInSign;
		globals->g_endOfParagraphOutSign = endOfParagraphOutSign;
		globals->g_endOfLineInSign = endOfLineInSign;
		globals->g_endOfLineOutSign = endOfLineOutSign;
		 
		for(int v = 0 ; v < globalHistogram->GetSize() ; v++)
		{
			delete []predTwoDimArray[v];
			delete []depTwoDimArray[v];
		}
		delete []predTwoDimArray;
		predTwoDimArray = NULL;
		delete []depTwoDimArray;
		depTwoDimArray=NULL;

		for(int i = 0 ; i < actualyNumberOfPatients ; i++)
		{
	//		delete []patientRecorsObjectList[i];
		}
	//	delete []patientRecorsObjectList;
		patientRecorsObjectList=NULL;
		//g_performanceReportFilePath

		//collect patient two dimensional paragarph array to be ready for prediction
	}

	if((globals->g_isToEnterRealTimeEndlessLoop == 'Y' ) || (globals->g_isToEnterRealTimeEndlessLoop == 'y'))
	{
	/*	double endOfParagraphInSign = globals->g_endOfParagraphInSign;
		globals->g_endOfParagraphInSign = '\n';
		double endOfLineInSign  = globals->g_endOfLineInSign;
		globals->g_endOfLineInSign = '\n';
	
		double endOfParagraphOutSign = globals->g_endOfParagraphOutSign;
		globals->g_endOfParagraphOutSign = '\n';
		double endOfLineOutSign = globals->g_endOfLineOutSign;
		globals->g_endOfLineOutSign ='\n';
	
 */
		ParagraphPredict( finalPhraseHash,  globals, globalHistogram);
	
		/*
		globals->g_endOfParagraphInSign = endOfParagraphInSign;
		globals->g_endOfParagraphOutSign = endOfParagraphOutSign;
		globals->g_endOfLineInSign = endOfLineInSign;
		globals->g_endOfLineOutSign = endOfLineOutSign;
*/
	}	
	
 	

	delete finalPhraseHash;
	finalPhraseHash=NULL;


	delete globalHistogram;
	globalHistogram=NULL;
	
	
	return true;
}

//4 24 23
void cParagraphAnalytics::WriteOrReadToDiscPAragraphModel(cArrayFlex* arrayFlex, 	cParagraphPredModel**& paragPRedModel , 
		int &numOfValues, cGlobals *globals)
{
	bool isWrite = arrayFlex->GetIsWriteMode();
	char strMesage[200];
	strcpy(strMesage, "num of values");//even if it is a real case iti does not hurt to put it in 
	arrayFlex->WriteReadArrayString(strMesage,  isWrite, *globals);
	arrayFlex->WriteReadArrayInt( numOfValues, isWrite ,  *globals);
	if(!isWrite)
	{
		paragPRedModel = new cParagraphPredModel*[numOfValues];
		for(int i = 0 ; i < numOfValues ; i++)
		{
			paragPRedModel[i] = new cParagraphPredModel();
		}
	}
	 
	for(int x = 0 ; x < numOfValues ; x++)//Create
	{
		char strr[200];
		strcpy(strr,"value index and string");
		arrayFlex->WriteReadArrayString(strr,  isWrite, *globals);
		int indexx = x;
		arrayFlex->WriteReadArrayInt( indexx , isWrite ,  *globals);
		paragPRedModel[x]->WriteReadObject(arrayFlex ,  globals);
	}
	strcpy(strMesage, "end of write or read predictive model");
	arrayFlex->WriteReadArrayString(  strMesage,  isWrite, *globals);
}

	
void cParagraphAnalytics::WriteParagraoPredOneBcket(cTableBucket* bucket , ofstream* outFile, cGlobals* globals  )
{
	int sdg = 0 ; 
	char tempStr[100];
	FileManager::WriteOneLine(*outFile,"Bucket Sample: ",globals->g_endOfLineInSign);
	sprintf(tempStr, "%d", bucket->m_cnt);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile,"Bucket % Sample: ",globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_percentageSample);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile,"Bucket Value: ",globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_value);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Lower and Higher First Z dimension:" , globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_firstDimLowZ);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_firstDimUpperZ);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Lower and Higher Second Z dimension:" , globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_secondDimLowerZ);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_secondDimUpperZ);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "" , globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Internal modfiers:" , globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Number of Internal Buckets:" , globals->g_endOfLineInSign);
	sprintf(tempStr, "%d", NUM_OF_PARAG_THIRD_DIM_BUCKETS);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Third Dimension:", globals->g_endOfLineInSign);
	for(int i = 0 ; i < NUM_OF_PARAG_THIRD_DIM_BUCKETS ; i++)
	{
		FileManager::WriteOneLine(*outFile, "value:", globals->g_endOfLineInSign);
		sprintf(tempStr, "%f", bucket->m_thirdValArray[i]);
		FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
		FileManager::WriteOneLine(*outFile, "odd:", globals->g_endOfLineInSign);
		sprintf(tempStr, "%f", bucket->m_thirdOddArray[i]);
		FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
		FileManager::WriteOneLine(*outFile, "sample:", globals->g_endOfLineInSign);
		sprintf(tempStr, "%d", bucket->m_thirdCntArray[i]);
		FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	}
	FileManager::WriteOneLine(*outFile, "Forth Dimension:", globals->g_endOfLineInSign);
	for(int i = 0 ; i < NUM_OF_PARAG_THIRD_DIM_BUCKETS ; i++)
	{
		FileManager::WriteOneLine(*outFile, "value:", globals->g_endOfLineInSign);
		sprintf(tempStr, "%f", bucket->m_forthValArray[i]);
		FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
		FileManager::WriteOneLine(*outFile, "odd:", globals->g_endOfLineInSign);
		sprintf(tempStr, "%f", bucket->m_forthOddArray[i]);
		FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
		FileManager::WriteOneLine(*outFile, "sample:", globals->g_endOfLineInSign);
		sprintf(tempStr, "%d", bucket->m_forthCntArray[i]);
		FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	}
	FileManager::WriteOneLine(*outFile, "" , globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "" , globals->g_endOfLineInSign);
/*	FileManager::WriteOneLine(*outFile, "Average Probability Left Bucket", globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_avgLeft);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Sample Left Bucket", globals->g_endOfLineInSign);
	sprintf(tempStr, "%d", bucket->m_cntLEft);
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Average Probability Right Bucket", globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_avgRight );
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "Sample Right Bucket", globals->g_endOfLineInSign);
	sprintf(tempStr, "%d", bucket->m_cntRight );
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "thirdDimThr", globals->g_endOfLineInSign);
	sprintf(tempStr, "%f", bucket->m_avgZscoreThirdDim  );
	FileManager::WriteOneLine(*outFile,tempStr,globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "" , globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile, "" , globals->g_endOfLineInSign);*/
}
	

//4 5 23 add hashObjOut,  cHashObj** manualObjOut , double* oddRatioArr print per value.
void cParagraphAnalytics::WritePredElements(double* predArr, double* refPRedArr  , char** strValueArr,
		cHashObj** hashObjOut,  cHashObj** manualObjOutt , double* oddRatioArr,	int numOfValues,
						ofstream* outFile, cGlobals* globals, double* highestOddRAtioArr, int numberOfParagraphs  )
{
	FileManager::WriteOneLine(*outFile, "Prediction set for the different potential values" , globals->g_endOfLineInSign);
	char tempStr[100];
	FileManager::WriteOneLine(*outFile,"number of values: ",globals->g_endOfLineInSign);
	sprintf(tempStr, "%d",numOfValues);
	FileManager::WriteOneLine(*outFile, tempStr , globals->g_endOfLineInSign);
	for(int i = 0 ; i < numOfValues ; i++)
	{
		FileManager::WriteOneLine(*outFile, strValueArr[i] , globals->g_endOfLineInSign);
		FileManager::WriteOneLine(*outFile, "probability:" , globals->g_endOfLineInSign);
		sprintf(tempStr, "%f",predArr[i]);
		FileManager::WriteOneLine(*outFile, tempStr , globals->g_endOfLineInSign);
		FileManager::WriteOneLine(*outFile, "general probability:" , globals->g_endOfLineInSign);
		sprintf(tempStr, "%f",refPRedArr[i]);
		FileManager::WriteOneLine(*outFile, tempStr , globals->g_endOfLineInSign);
		if(hashObjOut[i] != NULL)
		{
			FileManager::WriteOneLine(*outFile, "highest odd phrase:" , globals->g_endOfLineInSign);
			FileManager::WriteOneLine(*outFile, hashObjOut[i]->GetPhrase() , globals->g_endOfLineInSign);
		}
		FileManager::WriteOneLine(*outFile, "highest odd value:" , globals->g_endOfLineInSign);
		sprintf(tempStr, "%f",oddRatioArr[i]);
		FileManager::WriteOneLine(*outFile, tempStr , globals->g_endOfLineInSign);
		
		if((manualObjOutt!= NULL) && (manualObjOutt[i] != NULL ))
		{
			FileManager::WriteOneLine(*outFile, "Found a manual rule phrase:" , globals->g_endOfLineInSign);
			FileManager::WriteOneLine(*outFile, manualObjOutt[i]->GetPhrase() , globals->g_endOfLineInSign);
		}
		FileManager::WriteOneLine(*outFile,"",globals->g_endOfLineInSign);

	}
	FileManager::WriteOneLine(*outFile,"end of values",globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile,"",globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile,"paragraphs performance scores:",globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile,"number of paragraphs:",globals->g_endOfLineInSign);
	sprintf(tempStr, "%d",numberOfParagraphs);
	FileManager::WriteOneLine(*outFile, tempStr , globals->g_endOfLineInSign);
	FileManager::WriteOneLine(*outFile,"list of scores:",globals->g_endOfLineInSign);
	for(int xx = 0 ; xx < numberOfParagraphs ; xx++)
	{
		sprintf(tempStr, "%f",	highestOddRAtioArr[xx]);
		FileManager::WriteOneLine(*outFile, tempStr , globals->g_endOfLineInSign);
	}	 
	int sdg = 0 ; 
}

bool cParagraphAnalytics::ParagraphPredict( cPhraseHash* finalHash, cGlobals *globals, cStringHistogram* globalHistogram)
	//TEST 3 3 23 ***
{
		//API PREDICT PARAGRAPH RESULT
	bool end = false;
	bool ret = true;
	while(!end)
	{
		Sleep(1000); //two seconds
		char queryInFilePath[100];
		char extendedComunicIn[100];
		if( FileManager::IsRenameReadAndWriteToComunicationFile(
			extendedComunicIn, queryInFilePath, "prefixExt", globals, globals->g_patientRealTimeFilePathIn, globals->g_endOfParagraphInSign))
				////nnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
		{
			if( strcmp(queryInFilePath, "end") == 0)
			{
				end = true;
			}
			else if(   strlen(queryInFilePath) > 0  )
			{
			//	char filePath[100];
				int sdg = 0 ;
				char** paragrArray=NULL;
				char** valueArray = NULL;
				char** ptIDarray = NULL;
				int numOfParags=0;
				bool isSuccss = BuildArraysOfParagaphsValueAndPtID(
					paragrArray , valueArray , ptIDarray , numOfParags,
					globals->g_endOfParagraphInSign,globals->g_delimiter , 
					globals->g_isRemoveExtraSpaces, queryInFilePath);

	
				if(isSuccss)
				{//4 5 23 call a function to get all  under this if. use the follwoing predArr and other as input param to tuis func
					//then have a way here after callojg this func as the number of paragraphs , collect predArr alternatives
					//and other output such as the hash objectde matched to build a sorting method and then all that will be pritned
					//and not only one set of predArr and others.
					
				//	char* printFilePath = NULL;//queryInFilePath;
					double* highestOddRAtioArr = new double[numOfParags];
					for(int x = 0 ; x < numOfParags ; x++)
					{
						highestOddRAtioArr[x] = 0.0;
						char** tempParagarPtr = &(paragrArray[x]);
						double* predArr=NULL;//highestOddRAtioArr = new double[numOfParags];
						double* referanceDistriArr=NULL;
						char** strValueArr=NULL;
						int numOfValues=0;
						CollectResultsAndPrint(
							predArr, referanceDistriArr,strValueArr,numOfValues,
							highestOddRAtioArr[x],  tempParagarPtr ,  1,	 finalHash,  globals,
							globalHistogram, NULL, NULL); //when queryInFilePAth is NULL than we dont print
						for(int ii = 0 ; ii < numOfValues ; ii++)
						{
							if(	(strValueArr  != NULL ) && (strValueArr[ii]!= NULL))
							{
								delete []strValueArr[ii];
								strValueArr=NULL;
							}
						}
						if(strValueArr  != NULL )
						{
							delete []strValueArr;
							strValueArr=NULL;
						}		
						if(predArr != NULL)
						{
							delete []predArr;
							predArr=NULL;
						}
						if(referanceDistriArr != NULL)
						{
							delete []referanceDistriArr;
							referanceDistriArr=NULL;
						}
					}
				//	printFilePath = queryInFilePath;
					double highestOddRatio = 0.0;
					double* predArr=NULL;
					double* referanceDistriArr=NULL;
					char** strValueArr=NULL;
					int numOfValues=0;
					CollectResultsAndPrint(predArr,referanceDistriArr,strValueArr,numOfValues,
						highestOddRatio, paragrArray ,  numOfParags,	 finalHash,  globals,
							globalHistogram, queryInFilePath, highestOddRAtioArr);
				
					
					for(int ii = 0 ; ii < numOfValues ; ii++)
					{
						if(	(strValueArr  != NULL ) && (strValueArr[ii]!= NULL))
						{
							delete []strValueArr[ii];
							strValueArr=NULL;
						}
					}
					if(strValueArr  != NULL )
					{
						delete []strValueArr;
						strValueArr=NULL;
					}		
					if(predArr != NULL)
					{
						delete []predArr;
						predArr=NULL;
					}
					if(referanceDistriArr != NULL)
					{
						delete []referanceDistriArr;
						referanceDistriArr=NULL;
					}
						
					delete []highestOddRAtioArr;
					highestOddRAtioArr=NULL;
				}
			}
			if(/*	Deletes the file if exists */
					rename(extendedComunicIn , globals->g_patientRealTimeFilePathIn) != 0)
			{
				int sdg = 0 ;
				//	perror("Error renaming file"); //error
				ret= false;
			}
		}		
		//end = true;//temporary
	}
	return ret;
}

/*
No
Not
Deny
Denies
Without
Negative
monitor for
possible
unless
precautions
never had
high risk for
additional testing including
deceased due to
neg
mother:
father:
denied
mom died
dad died
screen
screening
family history
FH
F/H
FAM HX
FAHX
Ddx:
*/

void cParagraphAnalytics::FillIsNegativeStrings(bool* isNegativeArr, char** stss, int numOfStrs)
{
	int size= 300;//just as large en ough
	char** negPhrases = new char*[size];
	for(int i = 0 ; i < size ; i++)
	{
		negPhrases[i] = new char[100];
		negPhrases[i][0]=0;
	}
	int movingIndex = 0 ;
	strcpy(negPhrases[movingIndex++],"no");
	strcpy(negPhrases[movingIndex++],"not");
	strcpy(negPhrases[movingIndex++],"deny");
	strcpy(negPhrases[movingIndex++],"denies");
	strcpy(negPhrases[movingIndex++],"without");
	strcpy(negPhrases[movingIndex++],"negative");
	strcpy(negPhrases[movingIndex++],"monitor for");
	strcpy(negPhrases[movingIndex++],"possible");
	strcpy(negPhrases[movingIndex++],"unless");
	strcpy(negPhrases[movingIndex++],"precautions");
	strcpy(negPhrases[movingIndex++],"never had");
	strcpy(negPhrases[movingIndex++],"high risk for");
	strcpy(negPhrases[movingIndex++],"additional testing including");
	strcpy(negPhrases[movingIndex++],"deceased due to");
	strcpy(negPhrases[movingIndex++],"neg");
	strcpy(negPhrases[movingIndex++],"mother:");
	strcpy(negPhrases[movingIndex++],"father:");
	strcpy(negPhrases[movingIndex++],"denied");
	strcpy(negPhrases[movingIndex++],"mom died");
	strcpy(negPhrases[movingIndex++],"dad died");
	strcpy(negPhrases[movingIndex++],"screen");
	strcpy(negPhrases[movingIndex++],"screening");
	strcpy(negPhrases[movingIndex++],"family history");
	strcpy(negPhrases[movingIndex++],"fh");
	strcpy(negPhrases[movingIndex++],"f/h");
	strcpy(negPhrases[movingIndex++],"fam hx");
	strcpy(negPhrases[movingIndex++],"fahx");
	strcpy(negPhrases[movingIndex++],"ddx");
	int numOfNegPhrases = movingIndex;

	for(int i = 0 ; i < numOfStrs  ; i++)
	{
		isNegativeArr[i]=false;
		char lowerCaseStr[50];
		lowerCaseStr[0]=0;
		//char ch = LowerLetter(str[i]);
		int len = strlen(stss[i]);
		if(len < 49)
		{
			for(int l = 0 ; l < len ; l++)
			{
				lowerCaseStr[l] =  LowerLetter(stss[i][l]);
			}
			lowerCaseStr[len]=0;
		}

		
		for(int n = 0 ; n < numOfNegPhrases ; n++)
		{
			if( !strcmp(lowerCaseStr, negPhrases[n]))
			{
				isNegativeArr[i] = true;
			}
		}
	}



	
	for(int i = 0 ; i < size ; i++)
	{
		delete []negPhrases[i];
	}
	delete []negPhrases;

}





bool cParagraphAnalytics::IsStringgNegative(char* str)
{
	bool ret = false;
	int size= 300;//just as large en ough
	char** negPhrases = new char*[size];
	for(int i = 0 ; i < size ; i++)
	{
		negPhrases[i] = new char[100];
		negPhrases[i][0]=0;
	}
	int movingIndex = 0 ;
	strcpy(negPhrases[movingIndex++],"no");
	strcpy(negPhrases[movingIndex++],"not");
	strcpy(negPhrases[movingIndex++],"deny");
	strcpy(negPhrases[movingIndex++],"denies");
	strcpy(negPhrases[movingIndex++],"without");
	strcpy(negPhrases[movingIndex++],"negative");
	strcpy(negPhrases[movingIndex++],"monitor for");
	strcpy(negPhrases[movingIndex++],"possible");
	strcpy(negPhrases[movingIndex++],"unless");
	strcpy(negPhrases[movingIndex++],"precautions");
	strcpy(negPhrases[movingIndex++],"never had");
	strcpy(negPhrases[movingIndex++],"high risk for");
	strcpy(negPhrases[movingIndex++],"additional testing including");
	strcpy(negPhrases[movingIndex++],"deceased due to");
	strcpy(negPhrases[movingIndex++],"neg");
	strcpy(negPhrases[movingIndex++],"mother:");
	strcpy(negPhrases[movingIndex++],"father:");
	strcpy(negPhrases[movingIndex++],"denied");
	strcpy(negPhrases[movingIndex++],"mom died");
	strcpy(negPhrases[movingIndex++],"dad died");
	strcpy(negPhrases[movingIndex++],"screen");
	strcpy(negPhrases[movingIndex++],"screening");
	strcpy(negPhrases[movingIndex++],"family history");
	strcpy(negPhrases[movingIndex++],"fh");
	strcpy(negPhrases[movingIndex++],"f/h");
	strcpy(negPhrases[movingIndex++],"fam hx");
	strcpy(negPhrases[movingIndex++],"fahx");
	strcpy(negPhrases[movingIndex++],"ddx");






	char lowerCaseStr[100];
	lowerCaseStr[0]=0;
	//char ch = LowerLetter(str[i]);
	int len = strlen(str);
	if(len < 99)
	{
		for(int l = 0 ; l < len ; l++)
		{
			lowerCaseStr[l] =  LowerLetter(str[l]);
		}
		lowerCaseStr[len]=0;
	}

	int numOfNegPhrases = movingIndex;
	for(int i = 0 ; i < numOfNegPhrases ; i++)
	{
		if( !strcmp(lowerCaseStr, negPhrases[i]))
		{
			ret = true;
		}
	}

	for(int i = 0 ; i < size ; i++)
	{
		delete []negPhrases[i];
	}
	delete []negPhrases;

	return ret;
}
void cParagraphAnalytics::CollectResultsAndPrint(
	double*& predArr,	double*& referanceDistriArr,	char**& strValueArr,	int &numOfValues,
	double &highestOddRAtio, char** paragrArray , int  numOfParags,
	cPhraseHash* finalHash, cGlobals* globals, cStringHistogram* globalHistogram, 
	char* queryInFilePath, double* highestOddRAtioArr)
{
//and not only one set of predArr and others.
	predArr = NULL;
	referanceDistriArr=NULL;
	strValueArr = NULL;
	numOfValues=0;

	cHashObj** hashObjOut=NULL;
	cHashObj** manualObjOut=NULL;
	double* oddRatio=NULL;
	 
//	char** listOfParagraphOfOnePatientt = NULL;
//	int numberOFPAragraphss = 0;
//		m_patientRecorsObjectList[i]->CreateArrayAndCollectListOfPAragraphs(
//						listOfParagraphOfOnePatientt, numberOFPAragraphss, m_paragrArray);
	
	PredictParagraphResult(predArr,   referanceDistriArr, strValueArr ,hashObjOut,  manualObjOut, oddRatio,
		numOfValues, paragrArray ,   numOfParags, finalHash, globals, globalHistogram);
	
	highestOddRAtio = 0.0;
	for(int v = 0 ; v < numOfValues ; v++)
	{
		highestOddRAtio = cVarianceCalc::Max(highestOddRAtio, oddRatio[v]);
	}

	bool isSuccesPrint = false;
	if(queryInFilePath != NULL)
	{
		isSuccesPrint = true;
		char quesryFilePathOutTemp[MAX_STRING_LENGTH];
		strcpy(quesryFilePathOutTemp, queryInFilePath);
		FileManager::FillExtendedFilePath(  quesryFilePathOutTemp,"prefixExtOut", queryInFilePath );
		ofstream outFilee;
		outFilee.open(quesryFilePathOutTemp, ios::out);
		WritePredElements(  predArr,   referanceDistriArr, strValueArr ,
			hashObjOut,  manualObjOut, oddRatio, numOfValues,    &outFilee, globals, highestOddRAtioArr,numOfParags);	
		outFilee.close();
		char quesryFilePathOut[MAX_STRING_LENGTH];
		FileManager::FillExtendedFilePath(  quesryFilePathOut,globals->g_patientRealTimeFolderPathOut, queryInFilePath );
		if(	rename(quesryFilePathOutTemp, quesryFilePathOut) != 0)
		{
			int sdg = 0 ;
						//	perror("Error renaming file"); //error
			isSuccesPrint = false;
		}
		else
		{
 			int sdfg = 0 ; 
		}
	}


		//PRINT TO FILE


	if(hashObjOut !=NULL)
	{
		delete []hashObjOut;
		hashObjOut=NULL;
	}
	if(  manualObjOut != NULL)
	{
		delete [] manualObjOut;
		manualObjOut=NULL;

	}
	if(oddRatio !=NULL)
	{
		delete []oddRatio;
		oddRatio=NULL;
	}
}


	void cPhraseHash::ExportHashToArray(cHashObj **&objArray , int &numOfHashObjects)
	{
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
			for(int ii = 0 ; (ii < numOfHashObjects ) ; ii++)
			{
				if( false) 
				
				//	(ii != i) &&   ( objArray[ii]  != NULL) &&
				//	(cParagraphAnalytics::IsLeftStrSubStringOfRightStr( objArray[i]->GetPhrase(), objArray[ii]->GetPhrase())))
					
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
		int movingObjectIndex = 0;
		for(int i = 0 ; i < numOfHashObjects ; i++)
		{
			if(objArray[i] != NULL)
			{
				objArray[movingObjectIndex++] = objArray[i];
			}
		}
		numOfHashObjects = movingObjectIndex;
	}


 			
	bool cHashObj::IsToBeRemovedBasedOnSampleRecursive(int minSample)
	{
		bool ret = false;
		int sample = m_hist.GetTotalSample();
		if(sample < minSample)
		{
			ret = true;
		}
		else
		{
			int sssdf=0;
		}
		if(m_next != NULL)
		{
			if(m_next->IsToBeRemovedBasedOnSampleRecursive(minSample))
			{
				cHashObj* temp = m_next;
				m_next = m_next->GetNext();
				cPhraseHash::Delete(temp);
			}
		}
		return ret;
	}





	bool cPhraseHash::AddManualPhrases(char* manuelPhrasesFilePath, cGlobals* globals)
	{
		ifstream inFile;
		inFile.open(globals->g_manuelPhrasesFilePath, ios::in);
		if(!(inFile.is_open()))
		{
			return false;
		}
		char inLine[1000];
		bool end = false;
		while(!end)
		{
			if(FileManager::ReadOneLine(inLine, inFile, globals->g_endOfLineInSign))// (string) : "num of fields "
			{
				char temp[MAX_STRING_LENGTH];
				strcpy(temp,inLine);
				int len = strlen(temp);
				if(len>1)//
				{
					int newLen = len;
					char value[MAX_STRING_LENGTH];
					value[0]=0;
					for(int i = 0 ; i < len ; i++)
					{
						if( temp[i] == globals->g_delimiter )
						{
							temp[i] = 0;// globals->g_endOfLineInSign;
							newLen = i;
							strcpy(value, temp + i + 1);
						}
					}
					if(newLen < len)
					{
						char shadow[MAX_STRING_LENGTH];
						cParagraphAnalytics::Shadow(shadow, temp);
						cHashObj* data=NULL;				 
						if(!IsLookUp(data,shadow))
						{
							data = new cHashObj(shadow, value);

							SetValue(data,shadow,false);
						}
					}
				}
			}
			else
			{
				end = true;
			}
		}	
		return true;
	}


	
	 //4 27 23 open function . fill in how to do hash obects and with next 
	void cPhraseHash::ReadWriteHash(cArrayFlex* arrayFlex  , cGlobals* globals)
	{
		bool isWrite = arrayFlex->GetIsWriteMode();
		char str[200];
		strcpy(str,"writing hash size");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		arrayFlex->WriteReadArrayInt(m_size, isWrite, *globals);
		if(!isWrite)
		{
			m_arr = new cHashObj*[m_size];
			for(int i = 0 ; i < m_size ; i++)
			{
				m_arr[i] = NULL;
				//int temp = int(m_arr[i]);
			}
		}
		for(int i = 0 ; i < m_size ; i++)
		{
			int temp = int(m_arr[i]);
			arrayFlex->WriteReadArrayInt(temp, isWrite, *globals);
			if(!isWrite)
			{
				m_arr[i] = (cHashObj*)(temp);//if reading i only need to know where to stop in the next loop, when there is any object
			}
		}
		for(int i = 0 ; i < m_size ; i++)
		{
			if(m_arr[i] != NULL)
			{
				if(i==1188)
				{
					int sdg =0;
				}
				strcpy(str,"writing hash one bucket object set");
				arrayFlex->WriteReadArrayString(str,isWrite,*globals);
				strcpy(str,"bucketIndexInHashArray:");
				arrayFlex->WriteReadArrayString(str,isWrite,*globals);
				arrayFlex->WriteReadArrayInt(i, isWrite, *globals);
				strcpy(str,"number of objects in set:");
				arrayFlex->WriteReadArrayString(str,isWrite,*globals);

				int numOfObjectPerBucket = 0;
				if(isWrite)
				{
					numOfObjectPerBucket = m_arr[i]->CountRecursizeNumberOfObjects();
				}
				arrayFlex->WriteReadArrayInt(numOfObjectPerBucket, isWrite, *globals);
				//cHashObj* hashObj = m_arr[i];
				cHashObj** tempArray = new cHashObj*[numOfObjectPerBucket];
				if(isWrite)
				{
					ConvertChainToArray(tempArray , m_arr[i], numOfObjectPerBucket);
				}
				else
				{
					for(int ii = 0 ; ii < numOfObjectPerBucket ; ii++)
					{
						tempArray[ii] = new cHashObj();//5 5 23 add ++ too thhe hash counter. and check if it is zero when it does 
						this->m_numOfObjects++;
					}
				}
				for(int ii = 0 ; ii < numOfObjectPerBucket ; ii++)
				{
				//writes or reads one hash object and ignore the next pointer
					tempArray[ii]->WriteReadHashObject(arrayFlex  ,  globals); //read and write only this not next
					//4 27 23 find a way to read or write with same loop 	
				}
				if(!isWrite)
				{
					
					//cHashObj* tempObj = m_arr[i];//->GetNext();
					for(int ii = 1 ; ii < (numOfObjectPerBucket ); ii++)
					{ 
						tempArray[ii-1]->SetNext(tempArray[ii]);
					}
					tempArray[numOfObjectPerBucket-1]->SetNext(NULL);
					m_arr[i] = tempArray[0];
				}
				strcpy(str,"end of one hash bucket");
				arrayFlex->WriteReadArrayString(str,isWrite,*globals);	
				delete []tempArray;
			}
		}
		strcpy(str,"end of hash");
		arrayFlex->WriteReadArrayString(str,isWrite,*globals);
		

	//int m_size;
	//cHashObj** m_arr;
//	int m_numOfObjects;
//	int* m_numberOFObjectArr;
	}



void cTableBucket::CalcualteMeanVirtualProfile(bool* isIn, double* depArr, int numOfPatients)
{
		double mean  = 0.0;
		int cnt = 0;
		for(int i = 0 ; i < numOfPatients ; i++)
		{
			if(isIn[i])
			{
				mean += depArr[i];
				cnt++;
			}
		}
		if(cnt > 0)
		{
			mean /= cnt;
		}
		m_virtualValue = mean;
}


//5 5 23  see to build the exsisting 
void cTableBucket::CalcaulteThresholdsAndBycketsForThirdAndForthDimensions(bool* isIn, double* depLikeArr, 
		double* thirdDim, double* forthDim,    int numOffPatients,		cGlobals* globals)
{
	int numOfBuckets = LOCAL_NUMBER_OF_BUCKETS;
	for(int i = 0 ; i < numOfBuckets;i++)
	{
		m_thirdThresholdArrLocal[i]= 0.0;
		m_thirdValArrLocal[i]=0.0;
		m_thirdOddArrLocal[i]=0.0;
		m_thirdCntArrLocal[i]=0;

		m_forthThresholdArrLocal[i]=0.0;
		m_forthValArrLocal[i]=0.0;
		m_forthOddArrLocal[i]=0.0;
		m_forthCntArrLocal[i]=0;
	}

	cProfileObject::CalculateThresholds(m_thirdThresholdArrLocal,numOfBuckets,thirdDim,isIn,numOffPatients);
	double profileAvgDep1 = 0.0;
	cProfileObject::CreateAvgDepSubGrps(NULL,m_thirdValArrLocal,m_thirdThresholdArrLocal ,m_thirdCntArrLocal, profileAvgDep1,
							numOfBuckets,thirdDim,depLikeArr, isIn, numOffPatients,  *globals);
	double oddAvg = 0.0;
	int cntttTemp[LOCAL_NUMBER_OF_BUCKETS];
	cProfileObject::CreateAvgDepSubGrps(NULL,m_thirdOddArrLocal,m_thirdThresholdArrLocal ,cntttTemp, oddAvg,
							numOfBuckets,thirdDim,thirdDim, isIn, numOffPatients,  *globals);

	
	cProfileObject::CalculateThresholds(m_forthThresholdArrLocal,numOfBuckets, forthDim,isIn,numOffPatients);
	double profileAvgDep2 = 0.0;
	cProfileObject::CreateAvgDepSubGrps(NULL,m_forthValArrLocal,m_forthThresholdArrLocal ,m_forthCntArrLocal, profileAvgDep2,
							numOfBuckets,forthDim,depLikeArr, isIn, numOffPatients,  *globals);
	cProfileObject::CreateAvgDepSubGrps(NULL,m_forthOddArrLocal,m_forthThresholdArrLocal ,cntttTemp, oddAvg,
							numOfBuckets,forthDim,forthDim, isIn, numOffPatients,  *globals);


	int numOfTwoDimBuckets = LOCAL_TWO_DIM_BUCKET_NUM;
	 
	for(int i = 0 ; i < numOfTwoDimBuckets ; i++)
	{
		m_twoDimThirForthBucketVal[i]=0.0;
		m_twoDimThirForthBucketCnt[i]=0;
		m_avgThirdDimArr[i]=0.0;
		m_avgForthDimArr[i]=0.0;
	}

	for(int p = 0 ; p < numOffPatients; p++)
	{
		if(isIn[p])
		{
			double third = thirdDim[p];
			double forth = forthDim[p];

			int thridDimIndex = cProfileObject::GetSubGrpIndex(third,m_thirdThresholdArrLocal,numOfBuckets);
			int forthDimIndex = cProfileObject::GetSubGrpIndex(forth,m_forthThresholdArrLocal,numOfBuckets);
			int twoDimIndex = GetTwoDimIndexFromTwoIndexes(thridDimIndex, forthDimIndex, numOfBuckets);

			m_twoDimThirForthBucketVal[twoDimIndex] += depLikeArr[p];
			m_avgThirdDimArr[twoDimIndex]+= thirdDim[p];
			m_avgForthDimArr[twoDimIndex]+= forthDim[p];
			m_twoDimThirForthBucketCnt[twoDimIndex] ++;
		}
	}
	
	for(int i = 0 ; i < numOfTwoDimBuckets ; i++)
	{
		if(m_twoDimThirForthBucketCnt[i] > 0)
		{
			m_twoDimThirForthBucketVal[i]  /= m_twoDimThirForthBucketCnt[i];
			m_avgThirdDimArr[i] /= m_twoDimThirForthBucketCnt[i];
			m_avgForthDimArr[i] /= m_twoDimThirForthBucketCnt[i];
		}
	}
	double meanThird = 0.0;
	double sdThird = 0.0;
//	cVarianceCalc::CalculateMeanAndSD(meanThird,sdThird,m_avgThirdDimArr,m_twoDimThirForthBucketCnt,numOfTwoDimBuckets);
	double meanForth = 0.0;
	double sdForth = 0.0;
//	cVarianceCalc::CalculateMeanAndSD(meanForth,sdForth,/*m_avgForthDimArr*/ ,(int*)m_twoDimThirForthBucketCnt,numOfTwoDimBuckets);
	int totalCnt = 0;
	for(int x = 0 ; x  < numOfTwoDimBuckets ; x++)
	{
		meanThird += m_avgThirdDimArr[x] * m_twoDimThirForthBucketCnt[x];
		meanForth += m_avgForthDimArr[x] * m_twoDimThirForthBucketCnt[x];
		totalCnt += m_twoDimThirForthBucketCnt[x];
	}
 	meanThird /= totalCnt;
	meanForth /= totalCnt;
	for(int x = 0 ; x  < numOfTwoDimBuckets ; x++)
	{
		sdThird += (meanThird - m_avgThirdDimArr[x])* (meanThird - m_avgThirdDimArr[x])*  m_twoDimThirForthBucketCnt[x];
		sdForth += (meanForth - m_avgForthDimArr[x])* (meanForth - m_avgForthDimArr[x])*  m_twoDimThirForthBucketCnt[x];
	}
	sdThird /= totalCnt;
	sdForth  /= totalCnt;

	for(int i = 0 ; i < numOfTwoDimBuckets ; i++)
	{
		if(m_twoDimThirForthBucketCnt[i] > 0)
		{
			int thisCnt = m_twoDimThirForthBucketCnt[i];
			if(thisCnt < globals->g_minSampleSizeWhole)
			{
				double  editDisArr[LOCAL_TWO_DIM_BUCKET_NUM];
				double weightMissing = globals->g_minSampleSizeWhole - thisCnt;
				double sumWeights = double (thisCnt);
				double newAvg = (double (thisCnt)) * m_twoDimThirForthBucketVal[i];
				int indexMin =-1;
				double minDis = 1000000;
				for(int ii = 0 ; ii < numOfTwoDimBuckets ; ii++)
				{
					editDisArr[ii] = 0.0;
					if( i != ii)
					{
						double deltaThird =  cVarianceCalc::Abs(m_avgThirdDimArr[i] - m_avgThirdDimArr[ii]);
						double deltaForth =  cVarianceCalc::Abs(m_avgForthDimArr[i] - m_avgForthDimArr[ii]);
						editDisArr[ii] = (deltaThird / sdThird ) + (  deltaForth / sdForth  );
						if(editDisArr[ii] < minDis)
						{
							minDis = editDisArr[ii];
							indexMin = ii;						
						}
					}
				}			
				
				double addedWeight = double(m_twoDimThirForthBucketCnt[indexMin]);
				addedWeight = cVarianceCalc::Min(addedWeight , weightMissing);
				newAvg += addedWeight * m_twoDimThirForthBucketVal[indexMin];
				sumWeights +=addedWeight;
				m_twoDimThirForthBucketCnt[i] = int(sumWeights);
				newAvg /= sumWeights;
				m_twoDimThirForthBucketVal[i] = newAvg;
			}
		}
	}

}