//#include "stdafx.h"
#include "cRgression.h"
#include "cSimilarityFormula.h"
//#include "cPerformance.h"
#include "cProfileTarget.h"
#include "TargetSort.h"
//#include "cProfileList.h"


// Functions for performing linear regression 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>





cStatisticStructure::~cStatisticStructure()
{//6-5-12
	if(m_parentStat == NULL)
	{
		delete [] m_predictiveArr[0];
		delete [] m_subPredictiveArr[0];//10 7 13
		for(unsigned int i = 0 ; i < m_count ; i++)
		{
			//delete [] m_predictiveArr[i];
			//delete [] m_subPredictiveArr[i];
		}
		delete [] m_subPredictiveArr;
	}
	delete [] m_predictiveArr;
	
	delete [] m_predictabilityScores;
	delete [] m_predScoresAlt;
	delete [] m_dependentArr;
	delete [] m_regressionBetaWeightArray;
	//	delete [] m_regressionSensitivityCoefficient;
	if(m_controlledVarsSensativity)
	{
		delete []m_controlledVarsSensativity;
	}
	delete [] m_pValueArray;
	//	delete [] m_regressionBetaZeroConstantTermWeightArray;
	delete [] m_predicted_dependentArr;
	delete [] m_predictive_set;
	m_count = 0 ;
	m_numOfPredictiveVars =0;
	if (m_kPositionList)
	{
		delete [] m_kPositionList;
		m_kPositionList= NULL;
	}
	if ( m_kControlPositionList)
	{
		delete [] m_kControlPositionList;
		m_kControlPositionList = NULL;
	}
	if(m_controlPredictErrArr)
	{
		delete []m_controlPredictErrArr ;
	}
	if(m_kControlProfileIdArr)
	{
		delete []m_kControlProfileIdArr;
	}
	m_kCount = m_kControlCount = 0;
	
	if(m_meanArr)
	{
		delete [] m_meanArr;
	}
	if(m_sdArr)
	{
		delete []m_sdArr;
	}
	
	if(m_meanEdCtoS )
	{
		delete []m_meanEdCtoS ;
	}
	if(m_sdEdCtoS  )
	{
		delete m_sdEdCtoS  ;
	}

//	if(	m_buckets)
//	{
//		delete []m_buckets;
//	}
	
}

void cStatisticStructure::SetData(unsigned int count, unsigned int numOfPredictiveVars,
				unsigned int numOfControlledVars,  unsigned int kCount, 	
				unsigned int kControlCount,	cStatisticStructure * parentStat)
{
	//regression inputs
	m_count = count; //x count
	m_numOfPredictiveVars = numOfPredictiveVars; //y count
	m_numOfControlledVars = numOfControlledVars;

	m_predictiveArr = new short int* [m_count]; //PRAR - opening two dimensional array, size of m_count
	m_parentStat = parentStat;
	if(m_parentStat ==NULL)
	{
		//int* innnn = new int[1000000];//6 28 14
		m_subPredictiveArr = new double*[m_count];
		double * allocationnnBufer= new double[m_count * numOfPredictiveVars];
		for(unsigned int i = 0 ; i < m_count ; i++)
		{
			m_subPredictiveArr[i] = allocationnnBufer + (numOfPredictiveVars * i);
				 //new double [numOfPredictiveVars];
		}
	}
	else
	{
		m_subPredictiveArr = m_parentStat->m_subPredictiveArr; 
	}

	m_predictabilityScores = new float [m_count];
	m_predScoresAlt = new float[m_count];
	m_dependentArr = new short int[m_count];
	
	m_predictive_set = new short int[numOfPredictiveVars]; // allocate new variable 
	
	if(m_parentStat == NULL )
	{
		short int* allocationBufer= new short int[m_count * numOfPredictiveVars];
		for(unsigned int i = 0 ; i < m_count ; i++)
		{
			m_predictiveArr[i] = allocationBufer + (numOfPredictiveVars * i);
								//new short int[numOfPredictiveVars];
		}
	}
//regression outputs
	m_regressionPerformanceScore = 0.0;
	//m_regressionSensitivityCoefficient = new float[m_numOfPredictiveVars];
	if(m_numOfControlledVars > 0)
	{
		m_controlledVarsSensativity = new float[m_numOfControlledVars ];
		for (unsigned int i = 0 ; i < m_numOfControlledVars ; i ++)
		{
			m_controlledVarsSensativity [i] = 0 ;
		}
	}
	m_regressionBetaWeightArray = new float [m_numOfPredictiveVars];
	m_pValueArray = new float [m_numOfPredictiveVars];
	for (unsigned int i =0; i < m_numOfPredictiveVars ; i++)
	{
		m_regressionBetaWeightArray[i] = m_pValueArray[i] = 0.0;//m_regressionBetaZeroConstantTermWeightArray[i] = 0.0;
		m_predictive_set [i] = 0;
	}
	
	
	//m_regressionBetaZeroConstantTermWeightArray = new float[m_numOfPredictiveVars];
	m_predicted_dependentArr = new double  [m_count];

	for (unsigned int i=0; i< m_count ; i++)
	{
	//	m_predi ctiveArr[i] = NULL; //PRAR - initielizing the two dimensional array to NULL, size of m_count
		m_predictabilityScores[i] = 1.0f;
		m_predScoresAlt[i] = 1.0f;
		m_dependentArr [i] = 0;
		m_predicted_dependentArr[i] = 0.0f;
	}

	


	//K-N algorith input and output
	m_kCount = kCount; //the K group are the first K items in the m_count list.
	m_kControlCount = kControlCount; //this is the count of the Control Group. 

	m_KNperformanceScore = EMPTY_KN_PERFORMANCE_SCORE;

	m_kPositionList = NULL ;
	m_kControlPositionList = NULL ;
	m_controlPredictErrArr = NULL;	
	if(m_kCount != 0)
	{
		m_kPositionList = new unsigned int[m_kCount];
		for (unsigned   int i = 0 ; i < m_kCount ; i++)
		{
			//just initielizing till get filled. perhaps need a more natural default such as m_count, higher than max
			m_kPositionList[i] = 0; 
		}
	}
	if(m_kControlCount != 0)
	{
		m_kControlPositionList = new unsigned int[m_kControlCount];
		m_controlPredictErrArr = new float [m_kControlCount];
		m_kControlProfileIdArr = new unsigned int [m_kControlCount];

		for (unsigned  int i = 0 ; i < m_kControlCount ; i++)
		{
			//just initielizing till get filled. perhaps need a more natural default such as m_count
			m_kControlPositionList[i] = 0;
			m_controlPredictErrArr[i] = 0.0;
			m_kControlProfileIdArr[i] = 0;
		}
	}

	m_meanEdCtoS =NULL;
	m_sdEdCtoS  =NULL;
	m_meanArr =NULL;
	m_sdArr =NULL;


//	m_buckets = NULL;
//	m_numOfEDbuckets = 0 ;

}


//9 11 13  
void cStatisticStructure::ConsiderEfficientPredictoinVariables(
												bool* predictiveSignificantSample , unsigned int testGroupCount )
{
	double exactMAtchRatio [MAX_NUM_OF_PREDICTIVE_VARIABLES];
	double tempBetaSet[MAX_NUM_OF_PREDICTIVE_VARIABLES];

//cehck if we can actually call this and outside call again with an adjsuted preditiv esignicant array
	double averageSE=0;
	double variance=0;
	double predictiveVariance=0;
	LinearRegression(averageSE,variance,predictiveVariance,NULL,0,  //9 11 13
			NULL,predictiveSignificantSample , testGroupCount, false, true);

	
	//LinearRegresion... ( beta..
	for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		exactMAtchRatio[j] = tempBetaSet[j] =  m_regressionBetaWeightArray[j];
	}

	
	
	int *posArr = new int[m_numOfPredictiveVars];
	for(unsigned int j=0; j< m_numOfPredictiveVars; j++)
	{
		posArr[j] = j;
	}
	bool swapped = true;
	unsigned int jIndex = 0 ;
	while(swapped)
	{
		swapped = false;
		jIndex ++;
		for(unsigned int i = 0 ; i < m_numOfPredictiveVars-jIndex ; i++)
		{
			if(cVarianceCalc::Abs(exactMAtchRatio[i]) > cVarianceCalc::Abs(exactMAtchRatio[i+1]))
			{
				double tempScore = exactMAtchRatio[i];
				exactMAtchRatio[i] = exactMAtchRatio[i+1];
				exactMAtchRatio[i+1] = tempScore ;
				int tempPos = posArr[i];
				posArr[i] = posArr[i+1];
				posArr[i+1] = tempPos;
				swapped = true;
			}
		}
	}

	unsigned int numToRemove =(unsigned int) (((double)m_numOfPredictiveVars )* PERC_DELUTION_PRED_VARS);
	
	for(unsigned i=0;i< numToRemove ;i++ )
	{
		//allowedVariable[posArr[simCount - i-1]]=false;
		predictiveSignificantSample[posArr[i]]=false;
	}

	delete []posArr;

}




void cStatisticStructure::SortPositionArr_9_14_13(int* posArr,
							const float* inputBetaSet, unsigned int size)
{
	for(unsigned int j=0; j< size; j++)
	{
		posArr[j] = j;
	}

	float tempBetaSet [MAX_NUM_OF_PREDICTIVE_VARIABLES];
	for(unsigned int j= 0 ; j < size ;j++)
	{
	
		tempBetaSet[j] = inputBetaSet[j];
	}

	bool swapped = true;
	unsigned int jIndex = 0 ;
	while(swapped)
	{
		swapped = false;
		jIndex ++;
		for(unsigned int i = 0 ; i < size-jIndex ; i++)
		{
			if(cVarianceCalc::Abs(tempBetaSet[i]) >cVarianceCalc:: Abs(tempBetaSet[i+1]))
			{
				float tempScore = tempBetaSet[i];
				tempBetaSet[i] = tempBetaSet[i+1];
				tempBetaSet[i+1] = tempScore ;
				int tempPos = posArr[i];
				posArr[i] = posArr[i+1];
				posArr[i+1] = tempPos;
				swapped = true;
			}
		}
	}

}

//9 11 13  
/*
void cStatisticStructure::ConsiderEfficientPredictoinVariables_9_13_13( bool* predictiveSignificantSamp ,unsigned int testGroupCount )
{


//fisrt we run a linear regressson per the original predicti signiicant array.
	float averageSEstart=0;
	float varianceStart=0;
	float exVarStart=0; //this will be the base line ex var before we try alternatives.

//	we start with copying predicive sig sample array to a new one, to explore the opportnities and eventually to copy it back to th tinput

	bool predSigStart [MAX_NUM_OF_PREDICTIVE_VARIABLES];
	for(unsigned int j=0; j< m_numOfPredictiveVars ; j++ )
	{
		predSigStart[j] = predictiveSignificantSamp[j];
	}

	
	//linera regression will get the input first k members to be the test group
	LinearRegression(averageSEstart,varianceStart,exVarStart,NULL,0,  //9 11 13
										NULL,predSigStart, testGroupCount, false, true);


	//sort	
	int posArrFromBeta [MAX_NUM_OF_PREDICTIVE_VARIABLES];//= new int[m_numOfPredictiveVars];
	
	
	SortPositionArr_9_14_13(posArrFromBeta, m_regressionBetaWeightArray, m_numOfPredictiveVars);

	

	float effArr [MAX_NUM_OF_PREDICTIVE_VARIABLES];//= new int[m_numOfPredictiveVars];
	
	for(unsigned int j=0; j< m_numOfPredictiveVars ; j++ )
	{
		effArr[j] = 1; //1 is like 100% exalined varince. those who will not be tested will be sorted later lasts
	}

	unsigned int numToRemove = (unsigned )( ((double)m_numOfPredictiveVars )* PERC_DELUTION_PRED_VARS);
	
	unsigned  int numToScore = numToRemove * 2 ;
	numToScore = Min( numToScore , m_numOfPredictiveVars );

	ScoringEfficiencyArray( effArr, posArrFromBeta,numToScore,predSigStart, testGroupCount ,exVarStart);

	int posArrFromEffCheck[MAX_NUM_OF_PREDICTIVE_VARIABLES];//= new int[m_numOfPredictiveVars];

	SortPositionArr_9_14_13(posArrFromEffCheck, effArr, m_numOfPredictiveVars);

	for(unsigned i=0;i< numToRemove ;i++ )
	{
	                       	//allowedVariable[posArr[simCount - i-1]]=false;
	//	predictiveSignificantSamp[posArrFromEffCheck[i]]=false;

		predictiveSignificantSamp[posArrFromBeta[i]]=false;

	}

//	delete []posArr;

}
*/

void cStatisticStructure::CheckExVarWithAdjustedSigArr(float &adjPerScore, bool* predSigStart, 
													   int posToCheckRemived, unsigned int testGroupCount)
{
	
}


void cStatisticStructure::ScoringEfficiencyArray( float* effArr, int* posArrFromBeta,	unsigned int numToScore ,
								bool* predSigStart, 	unsigned int testGroupCount, float exVarStart)
{
	for(unsigned j=0;j< numToScore ;j++ )
	{
		//allowedVariable[posArr[simCount - i-1]]=false;
		float adjPerScore=0;
		if(predSigStart[posArrFromBeta[j]]) //if it is already a false than we dont ned to spend time. the specific
					//array of bolean for regression will remain fasle and the effArr[posArrFromBeta[j]] will get
					//a 0 value.
		{
			CheckExVarWithAdjustedSigArr(adjPerScore, predSigStart, posArrFromBeta[j], testGroupCount);
			effArr[posArrFromBeta[j]]= exVarStart - adjPerScore;//the bigger this gap that means that when inclujding the 
							//varible (exVarStart) before it is remoed in adjPreScore, it was better due to this variable
		}
		else
		{
			effArr[posArrFromBeta[j]]=false;
		}
	}
}




/*
//	we can decide how much we compremise for and balance the formula until we get as 
//		many as possible varibles with tha compreize. for xmaple, 8 varibels with 80% or so.
	//this will be done in the predict count. here too we can firs do this algorityhm,
	//then decide on the varibres, zero their predictive reg array. 
input - a ready aqfter regression statistic struture 
caclaute during the k average the diff betwen the averge of the k group and the avrage
on general, which is 0 as we standard all. the diff between the person minus the 0, 
and the person minus the k group , is like the value of the k group average per varible.
that value 


algorithm:
sort by edit distance
look for those varibels figures after the sort, who are the top ones but not those 
who passed the threshold.
promote those a bit, instead of all others eqaualty.
resort by edit discants 
the meassurments to perform are the diff between the erson and the group, times 
the beta, which is the effect happens if we keep reg in the game.
the target is to get rid of reg so this varible will have somem values thta means 
no need push anymore, need push , and need to much push. we will focus on the pushing 
the middle group up. 

do iterative algorithm.


in addition to finding the optimized set of similarity forfmula it wi ll also output
the formula and the set of varibels to not use. or if we call this function before the old check 
allowed varibales function then we dont need to output this from here.


gop one by one down from the similarit formula, as given , for each decide if needs extra percentage 
and give it as a porpotion. for exmaple 10% will bring a sim formula weight 4% to 4.4%.
but we only give that to those who need . if one is in the 10 or less, of reg ED score, dont
give. better, multiple by beta and sort that portion, of ed times beta, and don't give 
the top value (find out what value). we will not give below value, and above we wi ll give 
per the sim score. the input will be the predict k count.
if one is 


once changes the sim formula, it iwll be used for genration, and later for predict. but will nt touch the original

take care to update the current formjua before the adjusted score function. but need more 
adjustement within the function


if we calcualge per each varible the ed times beta we get a high score for more ed and more 
beta, and low score for less ed. then if we just update the sim formula by 10% we can 
get a set of delta formula . we can stgsrt doing it only befor predict. then try tyo 
use it also before evolution but after upate the adjust score func


the morem percentave we give, 

assuming that we have either mean or reg

the more we increase some one that has high beta we hurt the beta potential. so the higher beta
we need 

we acatully compeeting between the beta and ed and the percentge of sim.
the higher the percentage means the stronger the mean effect. but the higher the beta and the 
higher the ed still is we don't want to close the opporotunity for mean.

so we want  to increase sim of a varible when ever for one percent dif if m ore simimilarity
we gain more change in ed in the area that is matter, means from predict k couont, 
and if possible also more change of ed times beta. so if we run p scorings on the same k predict count
with 1 percent dif for each time, we can collect p values of ed times beta



we can de decide from the p varibel which is sim and which is reg.

the output will be a new 


/////////////////////9 17 13

the score for best mean is in the sim formula.

the score for best reg player is the combinatio of averge var times beta.

we want to try and remove reg player by adding more percentage to those who have low



the price we pay for a varibel of increase its score is the mutipication of ed times beta
that is chaned due to one percent sim move.

for xemape, we play with p varbiels , ncreae one by one in one percent the sim formula.

then we get an array of p values of ed times beta. all is already per one perent sim change.

we look at which is is the best to convert . conversion means adding a sim percenta

first dimension:
the benefit of adding is in the nominator, and it is the openingo sim formjula wegiht of that
varible. adding more percentage is good as the sim formula mentioninig that. 
second:
as we changed and have an array of effect of sim change, the effect is in languas of ed times bveta
change. the smaller the change, the less we want to chyange. 
we get the benefit of having someting as regression. 


example. a varible is already in the ed =0. ed times beta is also 0. 
sim for start is 3%. 3% times 0 is 0, will have a weight 0 and not get any increase.

it is actually an update to the functi before the Pre dict.
every iteration will have ipening value of last sim. and the scores of all manipulations as
today, using these for the sim weight. sim weight of less than 0 will not get any weight. 
in additio to this we will also get that 

go check in the code if we do square or polinomial in the evolution test.

///////////////summary 9 17:
input:
average of real performance scores of sim.
input sim formula.
save the last parent statistic structfure . if no genrations ?
linear regression with parent was already build there. try to remove logici of removing reg 
varibels during that function .
from the k group peform the variatgions for delta.
create manipulations. collect array of change in ed times beta.
build a multipication of strength of sim times 




output: adjusted sim formula. as todday.




output will be an updtaed sim formula to be used before parent stat is setting the stage 
for evolution, for the nalso before running the predict. but the 


each genreation we collectthe power of mean. but we have a price of loosing . we can meassure 
this by taking each chang ein mean, in the feunction that deal with one by one contgrol group
and meassure the change in predict minus the effect on the regression.

for example, if we have parent regression 

in the place where we set the predict for  mean o nly, we should actually
look at the parent reg and calculate a new method. the predict functio wi ll hae another 
mode with two scenarios. one with parent k group mean and one with ch ild. then look at var aveg 
using parent and child and get : 

1: diff of parent k average and child k average of one control item .

for i = 0 to k count 
   sum of dep parent
   sum of dep child

predict based on child will be the parent plus the change

every 



cal dif of avg child minus parent

2: diff of parent p var avg and child p var avg 



*/


//BoubleSort code to use 11 7 13

/*
void cStatisticStructure::PrepareStructureOfSimAndReg_9_16_13(
			bool* allowedVariableReg , 
							bool* allowedVariableSim,   unsigned int simCount, unsigned int kCount )
{
	double * exactMAtchRatio = new double[simCount];
	double* avgEDarrSim = new double[simCount];
	double * avgEDtimesBetaArrReg = new double[simCount];
//	unsigned int *countArr = new double[simCount];

	//unsigned int kCount = cConfiguration::GetInstance()->GetPred ictKCountCohortEvo();
	for(unsigned int j = 0 ; j < simCount ; j++)
	{
		double wegihtSumSim =0;
		double weigihtSumReg =0;
		avgEDarrSim[j]=0;
		avgEDtimesBetaArrReg[j]=0;
		for(unsigned int i=0 ;i < m_count ; i++)// m_count ; i++)
		{
			wegihtSumSim += m_predictabilityScores[i];
			double ed = Abs( (m_predictiveArr[i][j]- m_predictive_set[j]));
			avgEDarrSim[j] += ( m_predictabilityScores[i] * ed);
			if( i< kCount )
			{
				weigihtSumReg += m_predictabilityScores[i] ;
				//double regAbsBeta = Abs(m_regressionBetaWeightArray[j]); 
				avgEDtimesBetaArrReg[j] += ( m_predictabilityScores[i] * ed );//* regAbsBeta);
			}
		}
		avgEDtimesBetaArrReg[j] /= weigihtSumReg;
		avgEDarrSim[j] /= wegihtSumSim;

		exactMAtchRatio[j]= avgEDarrSim[j] ;
	}
	for(unsigned int j=0; j< simCount; j++)
	{
		if(avgEDarrSim[j] < cConfiguration::GetInstance()->GetMaxEDForNGroupAllowed())//(0.1*100))
		{
			allowedVariableSim[j]=false;
		}
		if(avgEDtimesBetaArrReg[j] < cConfiguration::GetInstance()->GetMaxEDForKregGroupAllowed())//(0.1*100))
		{
			allowedVariableReg[j]=false;
		}
	}
	*/

/*

	int *posArr = new int[simCount];
	for(unsigned int j=0; j< simCount; j++)
	{
		posArr[j] = j;
	}
	bool swapped = true;
	unsigned int jIndex = 0 ;
	while(swapped)
	{
		swapped = false;
		jIndex ++;
		for(unsigned int i = 0 ; i < simCount-jIndex ; i++)
		{
			if(exactMAtchRatio[i] > exactMAtchRatio[i+1])
			{
				double tempScore = exactMAtchRatio[i];
				exactMAtchRatio[i] = exactMAtchRatio[i+1];
				exactMAtchRatio[i+1] = tempScore ;
				int tempPos = posArr[i];
				posArr[i] = posArr[i+1];
				posArr[i+1] = tempPos;
				swapped = true;
			}
		}
	}
//	BoubleSort()

//	unsigned int realSimCount=0;
//	for(unsigned int j=0; j< simCount; j++)
//	{
//		if(allowedVariableSim[j])
//		{
//			realSimCount++;
//		}
//	}

	unsigned int numToRemove = cConfiguration::GetInstance()->GetPercRemoveFrequentExactMatch() * simCount;
	
	for(unsigned i=0;i< numToRemove ;i++ )
	{
		//allowedVariable[posArr[simCount - i-1]]=false;
		allowedVariableSim[posArr[i]]=false;
	}
*/

/*
//	delete []posArr;
	delete []avgEDtimesBetaArrReg;
	delete []exactMAtchRatio;
	delete []avgEDarrSim ;

	
}

*/

/*

void cStatisticStructure::PrepareAllowedVariablesForCollectionVariations_9_6_13(bool* allowedVariableReg , 
			bool* allowedVariableSim,  		unsigned int simCount, 
			unsigned int kCount , cSimilarityFormula &simFormula)
{
	double * exactMAtchRatio = new double[simCount];
	double* avgEDarrSim = new double[simCount];
	double * avgEDarrReg = new double[simCount];
//	unsigned int *countArr = new double[simCount];

	//unsigned int kCount = cConfiguration::GetInstance()-> GetPr edictKCountCohortEvo();
	for(unsigned int j = 0 ; j < simCount ; j++)
	{
		double wegihtSumSim =0;
		double weigihtSumReg =0;
		avgEDarrSim[j]=0;
		avgEDarrReg[j]=0;
		for(unsigned int i=0 ;i < m_count ; i++)// m_count ; i++)
		{
			wegihtSumSim += m_predictabilityScores[i];
			double ed =cVarianceCalc:: Abs( (m_predictiveArr[i][j]- m_predictive_set[j]));
			avgEDarrSim[j] += ( m_predictabilityScores[i] * ed);
			if( i< kCount )
			{
				weigihtSumReg += m_predictabilityScores[i] ;
				avgEDarrReg[j] += ( m_predictabilityScores[i] * ed);
			}
		}
		avgEDarrReg[j] /= weigihtSumReg;
		avgEDarrSim[j] /= wegihtSumSim;

		exactMAtchRatio[j]= avgEDarrSim[j] ;
	}
	int countregLimit=0;

	double testEdRegArr[MAX_NUM_OF_PREDICTIVE_VARIABLES];
	double testSimFormula[MAX_NUM_OF_PREDICTIVE_VARIABLES];
	for(unsigned int j=0; j< simCount; j++)
	{
		testEdRegArr[j]= avgEDarrReg[j] ;
		testSimFormula[j]= simFormula.GetWeights()[j];
	}


	for(unsigned int j=0; j< simCount; j++)
	{
		if(avgEDarrSim[j] < cConfiguration::GetInstance()->GetMaxEDForNGroupAllowed())//(0.1*100))
		{
			allowedVariableSim[j]=false;
		}
		if(avgEDarrReg[j] < cConfiguration::GetInstance()->GetMaxEDForKregGroupAllowed())//(0.1*100))
		{
			allowedVariableReg[j]=false;//9 18 13
			countregLimit++;
		}
	}
	int yyyy=0;	
*/
/*

	int *posArr = new int[simCount];
	for(unsigned int j=0; j< simCount; j++)
	{
		posArr[j] = j;
	}
	bool swapped = true;
	unsigned int jIndex = 0 ;
	while(swapped)
	{
		swapped = false;
		jIndex ++;
		for(unsigned int i = 0 ; i < simCount-jIndex ; i++)
		{
			if(exactMAtchRatio[i] > exactMAtchRatio[i+1])
			{
				double tempScore = exactMAtchRatio[i];
				exactMAtchRatio[i] = exactMAtchRatio[i+1];
				exactMAtchRatio[i+1] = tempScore ;
				int tempPos = posArr[i];
				posArr[i] = posArr[i+1];
				posArr[i+1] = tempPos;
				swapped = true;
			}
		}
	}
//	BoubleSort()

//	unsigned int realSimCount=0;
//	for(unsigned int j=0; j< simCount; j++)
//	{
//		if(allowedVariableSim[j])
//		{
//			realSimCount++;
//		}
//	}

	unsigned int numToRemove = cConfiguration::GetInstance()->GetPercRemoveFrequentExactMatch() * simCount;
	
	for(unsigned i=0;i< numToRemove ;i++ )
	{
		//allowedVariable[posArr[simCount - i-1]]=false;
		allowedVariableSim[posArr[i]]=false;
	}
*/
//	delete []posArr;
//	delete []avgEDarrReg;
////	delete []exactMAtchRatio;
//	delete []avgEDarrSim ;
//
	
//}


/*
after we calcualte the average predictive value , we count how many times a predictivei value is different
than that averarge in more than VALUE_FOR_SIGNIFICANT_PREDICTIVE_SIFF which is now 50.  that means that  if
we got 1000 items of 0 and 500 of -50  and 500 of 50 than we have 1000 cases where we diff with 50 and 
we need 15 cases only.
if not we don't have enough of that, we have any fallback to catch diff of 50/2 but with 3 times larger sample size

*/



bool cStatisticStructure::IsAlmost0edCohort(unsigned int predictiveIndex,
	double minSDforAllowedRegVar, unsigned int countToCheckSig)
{
	double sumBC = 0;
	double sumWeightsBC=0;
	for (unsigned int i = 0 ; i <  countToCheckSig ; i++)
	{
		double ed = cVarianceCalc::Abs  (m_predictive_set[predictiveIndex] - m_predictiveArr[i][predictiveIndex]);
		sumBC += ed  * m_predictabilityScores[i];
		sumWeightsBC += m_predictabilityScores[i];
	}
	double averageBC = sumBC / sumWeightsBC;

	double sumVarianceBC = 0 ;
	//	double distant1 = 0 ;//	double near1 = 0 ;
	for (unsigned int i = 0 ; i <  countToCheckSig ; i++)
	{
		double ed = cVarianceCalc::Abs  (m_predictive_set[predictiveIndex] - m_predictiveArr[i][predictiveIndex]);
		double temp = (ed- averageBC  );
		sumVarianceBC += temp* temp *m_predictabilityScores[i];
	}
	double varianceBC  = sumVarianceBC / sumWeightsBC;
	double sdBC = pow (varianceBC,0.5);

	if(averageBC <minSDforAllowedRegVar )
	{
		return true;
	}
	else
	{
		int fff=0;
	}
	if(sdBC <50 )
	{
		int rrrr=0;
	}

	return false;

}


/*


bool cStatisticStructure::IsSignificantSampleSizeOnePredictive(unsigned int predictiveIndex,
	double minSDforAllowedRegVar, double sdDep)//, unsigned int countToCheckSig)
{
//	return true;
	//related to vector with the same thinking, then do the fine tu ned k average 
	if(!IS_CHECK_FOR_SAMPLE_SIZE_REGRESSION)
	{
	//	return true;
	}
	
	//return true;
	double sumBC = 0;
	double sumWeightsBC=0;
	for (unsigned int i = 0 ; i <  m_count ; i++)
	{
		sumBC += m_predictiveArr[i][predictiveIndex] * m_predictabilityScores[i];
		sumWeightsBC += m_predictabilityScores[i];
	}
	double averageBC = sumBC / sumWeightsBC;

	double sumVarianceBC = 0 ;
	//	double distant1 = 0 ;//	double near1 = 0 ;
	for (unsigned int i = 0 ; i <  m_count ; i++)
	{
		double temp = (m_predictiveArr[i][predictiveIndex]- averageBC  );
		sumVarianceBC += temp* temp *m_predictabilityScores[i];
	}
	double varianceBC  = sumVarianceBC / sumWeightsBC;
	double sdBC = pow (varianceBC,0.5);


	if(sdBC <minSDforAllowedRegVar )//7 2 14 incr ths value
	{
		//return false;
	}
	double sumWeightsLow =0;
	double sumWeightsHigh =0;
	int countLow = 0 ;
	int countHigh = 0 ;
	double meanDepHigh=0;
	double meanDepLow=0;
	for (unsigned int i = 0 ; i <  m_count ; i++)
	{
		if(m_predictiveArr[i][predictiveIndex] <  averageBC )
		{
			sumWeightsLow += m_predictabilityScores[i] ;
			countLow ++;
			meanDepLow += m_dependentArr[i];
		}
		else if(m_predictiveArr[i][predictiveIndex] >  averageBC)
		{
			sumWeightsHigh  += m_predictabilityScores[i] ;
			countHigh++;
			meanDepHigh += m_dependentArr[i];
		}
	}
	if(sumWeightsLow == 0 || sumWeightsHigh ==0 || countHigh < MIN_SAMPLE_FOR_HIGH_OR_LOW_REG ||
		            countLow < MIN_SAMPLE_FOR_HIGH_OR_LOW_REG)
	{
		return false;
	}
	double ratioHighToLowGrps = sumWeightsLow / sumWeightsHigh;
	if(ratioHighToLowGrps  < 1.0 )
	{
		ratioHighToLowGrps = 1.0 / ratioHighToLowGrps ;
	}
	if(ratioHighToLowGrps >= 100 )
	{
		return false;
	}

	meanDepLow /= countLow ;

	meanDepHigh /= countHigh ;

	double gap = cVarianceCalc::Abs(meanDepHigh - meanDepLow );
	if(    gap < (MIN_SD_RATIO_FOR_PREDIC_POWER * sdDep))
	{
		return false;
	}

	return true;

	if(sdBC <30 )
	{
		int rrrr=0;
	}
	double avgPreInSDlow = 0 ;
	double  wghtPredInSDlow = 0 ;
	double avgPreInSDhigh = 0 ;
	double  wghtPredInSDhigh = 0 ;
	int countThoseWithHighPRedInSD = 0 ;

	for (unsigned int i = 0 ; i <  m_count ; i++)
	{
		double predValueInSD = 
		     cVarianceCalc:: Abs(m_predictiveArr[i][predictiveIndex] - averageBC) / sdBC;
		if(predValueInSD <=1 )
		{
			avgPreInSDlow += m_predictabilityScores[i] * predValueInSD;
			wghtPredInSDlow += m_predictabilityScores[i];
		}
		else
		{
			avgPreInSDhigh += m_predictabilityScores[i] * predValueInSD;
			wghtPredInSDhigh += m_predictabilityScores[i] ;
		}

	}

	if( wghtPredInSDlow >0)
	{
		avgPreInSDlow /= wghtPredInSDlow;
	}
	if( wghtPredInSDhigh >0)
	{
		avgPreInSDhigh /= wghtPredInSDhigh;
	}
	if( avgPreInSDlow == 0 || wghtPredInSDhigh==0)
	{
		return false;
	}
	double ratio = avgPreInSDlow / avgPreInSDhigh;
	if(ratio < 1 )
	{
		ratio = 1 / ratio;
	}
	if(ratio > 50)
	{
		double ratioWeights = wghtPredInSDlow / wghtPredInSDhigh;
		if(ratioWeights < 1)
		{
			ratioWeights = 1.0 / ratioWeights;
		}
		if(ratioWeights > 50)
		{
			return false;
		}
	}

	return true;


	bool* isIn = new bool[m_count];

		for (unsigned int i = 0 ; i < m_count ; i++)
		{
			isIn[i] = true;
			//double temp = (m_predictiveArr[i][predictiveIndex]- averageBC  );
			double localSD = (m_predictiveArr[i][predictiveIndex]- averageBC  )/sdBC;
			if(  (cVarianceCalc::Abs(localSD)) > 3)
			{
				isIn[i] = false;
			}
			else
				int fffff=0;
//		sumVarianceBC += temp* temp *m_predictabilityScores[i];
		}

//	double sumSDs = 0 ;

	
	double sumAC = 0;
	double sumWeightsAC=0;
	for (unsigned int i = 0 ; i < m_count ; i++)
	{
		if(isIn[i])
		{
			sumAC += m_predictiveArr[i][predictiveIndex] * m_predictabilityScores[i];
			sumWeightsAC += m_predictabilityScores[i];
		}
	}
	double averageAC = sumAC / sumWeightsAC;

	double sumVarianceAC = 0 ;
//	double distant1 = 0 ;//	double near1 = 0 ;
	for (unsigned int i = 0 ; i < m_count ; i++)
	{
		if(isIn[i])
		{
			double temp = (m_predictiveArr[i][predictiveIndex]- averageAC  );
			sumVarianceAC += temp* temp *m_predictabilityScores[i];
		}
	}
	double varianceAC  = sumVarianceAC / sumWeightsAC;
	double sdAC = pow (varianceBC,0.5);
	

	//#define MIN_SD_ALLOWED_FOR_REGRESSION  0 //9 3 13
	if(sdAC <= minSDforAllowedRegVar)
	{
		delete []isIn ;
		return false;

	}
	else
	{
		delete []isIn ;
		return true;	
	}

	if(varianceBC  == 0)
	{
		//this for loop is for for debug only
		for (unsigned int i = 0 ; i < m_count ; i++)
		{
			if(isIn[i])
			{
				double temp = (m_predictiveArr[i][predictiveIndex]- averageAC  );
				sumVarianceAC += temp* temp *m_predictabilityScores[i];
			}
		}
		delete []isIn ;
		return false;
	}
	delete []isIn ;
	double changeInVariance = varianceAC  / varianceBC  ;
	
	if(changeInVariance < 0.08)
	{
		//return false;
		int ddddd=0;
	}

//	

	double sumExact = 0 ;
	double sumAll=0;
	for(unsigned int i = 0 ; i < m_count; i++)
	{
		double temp = m_predictiveArr[i][predictiveIndex]- m_predictive_set[predictiveIndex]  ;
 		if(temp == 0)
		{
			sumExact += m_predictabilityScores[i];
		}
		sumAll += m_predictabilityScores[i];
	}
	if(sumExact > (cConfiguration::GetInstance()->GetPercentSumAllRegression()* sumAll))
	{
		return false;
	}


///////////////iiiiiiiiiiiiii
	double sumWeightH=0;
	double sumWeightL=0;
	for(unsigned int i = 0 ; i < m_count  ; i++)
	{
		double temp = m_predictiveArr[i][predictiveIndex]- averageBC  ;
 		if(temp > 0)
		{
			sumWeightH += m_predictabilityScores[i];
		}
		else
		{
			sumWeightL +=m_predictabilityScores[i];
	
		}
	}
	double weightHighPerALL = sumWeightH / (sumWeightH+sumWeightL); 
	double weightLowPerALL = sumWeightL / (sumWeightH+sumWeightL); 
	double thresholdConservative = 
		THRESHOLD_FOR_PER_WEIGHT_DISTRIBUTION_FOR_REG_PRED_VALIDITY;//0.1;
	double thresholdForMinoritySP = 
		THRESHOLD_FOR_PER_WEIGHT_DISTRIBUTION_FOR_EXACT_MATCH_REG_PRED_VALIDITY ;
		
	double thres = thresholdConservative;
	if(m_predictive_set[predictiveIndex] > 	averageBC) //sp is on the higher pred value side
	{
		if(weightHighPerALL < weightLowPerALL) //and if that higher group is the smaller one
		{
			thres = thresholdForMinoritySP;
		}
	}
	else //sp on the lower side
	{
		if(weightHighPerALL > weightLowPerALL) //and if that lower  group is the smaller one
		{
			thres = thresholdForMinoritySP;
		}
	}
	
	if(!((weightHighPerALL > thres) && (weightHighPerALL < (1-thres) )))
	{
		return false;//send.abc.mail@gm
	}
	//assuming that the weight of  high 
	return true;
}	
*/
	/*
4 30 13
	hree we will count the weigiht of those who have positive above mean of prdictive balue, 
	and those with negative. the  relation between weights will be a bad thing. 90% and 10% means
	a 9 mutiple. we will put the max devide by the minimum weight and pass only those with less than
	9 multiple





	mean 9 sd 3.
	-3, 0.33, 0.33 ...
	mean 0 var 10 sd around 3. 

	0,0,0,0,0,10,10,10,10,10,
	mean 5. var 25. sd around 5.
	-1,-1,-1,-1,-1,1,1,1,1,1
	mean 0 var 1 sd 1



	
	*/
	
/*	
	double extremeWeight=0;
	unsigned int extremeCount=0;
	unsigned int effectiveCount=0;
	for (unsigned int i = 0 ; i < m_count ; i++)
	{
		double temp = Abs(m_predictiveArr[i][predictiveIndex]- average  );
		temp /= sd;
		sumSDs += temp * m_predictabilityScores[i];
		if(m_predictabilityScores[i] > 0)
		{
			effectiveCount ++;
			if( (temp > 0.5) &&(m_predictabilityScores[i]))
			{
				extremeWeight += m_predictabilityScores[i];
				extremeCount ++;
			}
		}
	}
	sumSDs /= sumWeights;
	double extremWeigtPerc=extremeWeight /sumWeights ; 
	double  extremeCountPerc = ((double)extremeCount)/((double)effectiveCount );
	if((extremWeigtPerc < 0.01) || (  extremeCountPerc < 0.01     ))
	{
		//return false;
	}



//	if(   (distant1 / (distant1+near1)) <0.01   )
//		return false;
//	else if(   (distant1 / (distant1+near1)) > 0.99   )
//		return false;

	return true;
*/	
	/*unsigned int sigDifCount =0;
	unsigned int lightSigDifCount = 0 ;
	for (unsigned int i = 0 ; i < m_count ; i++)
	{
		float dif = ABS (m_predictiveArr[i][predictiveIndex] - average);
		if(dif >= VALUE_FOR_SIGNIFICANT_PREDICTIVE_SIFF)
		{
			sigDifCount ++;
		}
		else if (dif >= VALUE_FOR_SIGNIFICANT_PREDICTIVE_SIFF / 2)
		{
			lightSigDifCount ++;
		}
	}
	//we have two softer options to make it gray and not black/white decision. we potentially could research this further and find best pracative varible
	if((sigDifCount >= Max((unsigned int)SAMPLE_SIZE_FOR_SIGNIFICANT_PREDICTIVE_DIFF, (unsigned int)(m_count /30)))||
				(lightSigDifCount >= Max((unsigned int)(SAMPLE_SIZE_FOR_SIGNIFICANT_PREDICTIVE_DIFF * 3),
																				(unsigned int)(m_count / 10))))
	{
		return true;
	}
	return false;
*/


/*
1. target to meassure for all variables the average sqr.
2.	And a breakdown first: for each variable, count the current weight, which is the average sqr dif from mean.
We allow such sqr dif to be only 20% of the orginal eqr of that variable. That we will do by looking at the
entire profile list using a constructor function. profile list will have a function that returns mean and
variance of a variable.  We will want our variance of the regression to be at least 20% of the big profile 
list variance. , for example of we have 0.5 variance total than 0.05  will be only  10% variance than we will
need e 0.05 variance missing. That 0.05 will be then multiple by size of regression predictiblity weight .
for total contribution to such variance by all regression items. 
3.	and same for all variables, each that has some missing will have the total variance and the missing value 
to reach the 20%/ .. 
4.	Sum of total variables missing variancet (cigma of each variavle,  p iterations)
5.	Now count each item how much it would add to total variance of predictive variables that has that need. 
Each item gets that sum and gets multiple by predictiblity score. that will be the contribution value per now
6.	All this Sum of N assessments contributions will server as a weight for an item. 
7.	That sum, as a nominator will have a denomimator which is the current variance
8.	Now we will look at the sum of need, from 4 above, and distribute it per this weight from 6. That sum 
will also be in percentage from current variance, so we will have a multiple
9.	Now we will look at the sum of contriution which is 6 and multiple  from 8. The diff will be what is needed
to multiple the predictiblity score with. We then do’t need the weiht? Now, just when we count c urrent 
contrigiution and also sum of weights times missing vaiance. 
10.	Sum of weight times missing variance, sum of weihts times current average variance, sum of weights 
times each item contriution, we will see  how much is missing. 
11.	Add some rules where you cannot increase  one more than…
12.	Breakdown for every assessment, its sum of p variable contribution to the missing weight
13.	N



*/
//this function will fill true in all, unless false when found a non significant preeictive so that sample too low.
void cStatisticStructure::AdjustPredictiblityPerFrequency(float &predictiveVariance, double  *allListVariableVariance , bool *predictiveSignificantSample)
{
	float * meanArr = new float[m_numOfPredictiveVars];
	float * varianceArr = new float[m_numOfPredictiveVars];
	float * missingVarianceArr = new float[m_numOfPredictiveVars];
	float * sumOfMissingVariances = new float[m_numOfPredictiveVars];
	float * itemsContributionToVariacne = new float[m_count];
	
	//calculate s um of preditiblity score, replacement of N in a weights enviorment
	float sumOfPredictWeights = 0;
	for( unsigned int i = 0 ; i< m_count ; i++)
	{
		sumOfPredictWeights+= m_predictabilityScores[i];
	}
	unsigned int iterIndex = 0 ;
	unsigned int numOfIterations = 3;
	float allVariableSumMissingVariance=0;
		
	while(iterIndex++ < numOfIterations)
	{
	//	float averageIncreaseWeightBefore = 0;
	allVariableSumMissingVariance=0;
	CalculateMissingVarianceData( allVariableSumMissingVariance, meanArr, varianceArr , missingVarianceArr , 
														sumOfMissingVariances ,sumOfPredictWeights,allListVariableVariance,
													predictiveSignificantSample,  (float(numOfIterations)+1.0f)) ;
		//123456 roadmap : 
		//in the fucntion that guard us to not have less than 15% per varinace, also make sure those who are similar to 
		//our subject person are at least x% weight from the value. 
		//in thta same funtion, instead of 15% do half of anything less than 30%. so, if we have 
		//20%, we miss 10%, we add 5% which is ihafl than 10% and keep 25%. . if we have 10%, we miss 20 and add 
		//10 so we get 20. in that way, if we have 20 we stay with 25, have 10 stay with 20%, have 5% stay with 17%.
		//update score we save to be from the more compliated group and not partial flagged group.
		//all list variances. 
		//flexible edit distance consant (100 of today) ,  
		//mutatio - all variables
		//ontology.	
		//controlled variavles 
		//profile view, with interactions/corelations as roy suggested
		//(add what if in the configuration only and an array of links to some predictive variables. then we have
		//two option, reverse on small amount and dif, or regression),
		float sumOfAllContribution=0;
		CalculateItemsContributionToVariance(sumOfAllContribution ,	itemsContributionToVariacne,
							meanArr, varianceArr, missingVarianceArr);
		
	//	AdjustPredictiblityPerContributionWeight(unitOfItemShare, sumOfWeights);
		AdjustPredictiblityPerContributionWeight( itemsContributionToVariacne, sumOfAllContribution,  
													allVariableSumMissingVariance , sumOfPredictWeights);

#ifdef DEBUG1
	//	CalculateMissingVarianceData( allVariableSumMissingVariance, meanArr, varianceArr , missingVarianceArr , 
//sumOfMissingVariances ,sumOfPredictWeights,allListVariableVariance,
			//										predictiveSignificantSample, 1.0f/ (float(numOfIterations))) ;
		
#endif 
	}
	//only for the below input of predictive variance
	CalculateMissingVarianceData( allVariableSumMissingVariance, meanArr, varianceArr , missingVarianceArr , 
														sumOfMissingVariances ,sumOfPredictWeights,allListVariableVariance,
													predictiveSignificantSample,  (float(numOfIterations)+1.0f)) ;
	predictiveVariance=0;//allVariableSumMissingVariance;
	for(unsigned int j = 0 ; j <m_numOfPredictiveVars;  j ++)
	{
		predictiveVariance+=varianceArr[j];
	}
	predictiveVariance /= m_numOfPredictiveVars;

	delete []meanArr;	delete []varianceArr; delete []missingVarianceArr;  delete []sumOfMissingVariances;
	delete []itemsContributionToVariacne;
}
//this will be how much per each contribiution it will get responsiblity to share the additional increase.
	//for example, if average incrase is 0.1 and average contribution is 0.2  than 0.5 is average increase per
	//contribution. . than, if an item gets contribution x , and if it had average contrbiution it will need to get its
	//predictilbity score get increased by 50%. but if it has a higher contribution than average, than to the extent of 
	//how much higher, it will go in addition to that 50% or less.
	
//qq	float percVarIncPerContribution = ( averageIncreaseWeightBefore  / averageContribution );
	//for example if total m issing is 20 and sum of current contribvuition if 40 than we got 0.5 w hich is
	//like 50% in addition or a 1.5 multiple. 
	/* but how will this 20 get distributed to all items? 
	*/
	//this multipe is going to be used as follows:


	//for debug, check new status:
//	float averageIncreaseWeightAfter = 0;
//	CalculateMissingVarianceData( averageIncreaseWeightAfter , meanArr,  varianceArr , missingVarianceArr , 
//						sumOfMissingVariances ,sumOfWeights, allListVariableVariance, predictiveSignificantSample) ;




void cStatisticStructure::AdjustPredictiblityPerContributionWeight(float *itemsContributionToVariacne,
							float sumOfAllContribution, float allVariableSumMissingVariance ,   float sumOfPredictWeights)
{
	float averageContribution = sumOfAllContribution / m_count;
	float averagePredicWeight = sumOfPredictWeights / m_count;
	
	float combinedWeightsSum = 0 ;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		float tempCombinedWeight = ((m_predictabilityScores[i]/averagePredicWeight)* 
								(itemsContributionToVariacne[i]/averageContribution));
		combinedWeightsSum+= tempCombinedWeight;//*averagePredicWeight;
	}
//qq	float averageContribution = sumOfAllContribution /  sumOfWeights;
//	float totalMissingVar = averageIncreaseWeightBefore * sumOfWeights;
	float unitOfItemShare = 0 ;
	if (combinedWeightsSum > 0) 
	{
		unitOfItemShare = allVariableSumMissingVariance /  combinedWeightsSum;
	}
	for( unsigned int i = 0 ; i< m_count ; i++)
	{
	//	here we are looking to find how based on what is now and how much total multiple to know what is ia new predictility.
	//	itemsContributionToVariacne[i] ; this is the person contribution. 
		/*if we know that we need more 
		*/	
		if( itemsContributionToVariacne[i]!=0)
		{
			//float averagePredicWeight = sumOfWeights / m_count;
			float combinedWeight = ((m_predictabilityScores[i]/averagePredicWeight)*
									(itemsContributionToVariacne[i]/averageContribution));
		//	weight*=averagePredicWeight;
			float contribution = combinedWeight * unitOfItemShare;
			float mult = 1+(contribution / (itemsContributionToVariacne[i]*m_predictabilityScores[i]));

			//	combinedWeights+= temp*averagePredicWeight;
		//qq	float itemWeightedContrib = itemsContributionToVariacne[i] / m_p redictabilityScores[i];
		//qq	float itemShiftFromAverageContribution = (itemWeightedContrib / averageContribution);
		//	float mult = (1+ (unitOfItemShare* itemsContributionToVariacne[i])
			if(i>=1392)
				int ggg=0;
			mult = cVarianceCalc::Min (mult, 3.0f);
			m_predictabilityScores[i] *= mult;
			float maxScore = sumOfPredictWeights / 100.0f;
			m_predictabilityScores[i] = cVarianceCalc::Min(m_predictabilityScores[i] , maxScore );
			//(percVarIncPerContribution * itemShiftFromAverageContribution));
			//float itemIncreaseVariance = averageIncreaseWeight * increaseWeight * m_pr edictabilityScores[i];
		}
	}
}

void cStatisticStructure::CalculateItemsContributionToVariance(float &sumOfAllContribution ,
					float* itemsContributionToVariacne , float *meanArr, float *varianceArr, float *missingVarianceArr)
{
	for( unsigned int i = 0 ; i< m_count ; i++)
	{
		itemsContributionToVariacne[i]=0;
		for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
		{
			float value = 0;
			if(missingVarianceArr[j] !=0)
			{
				float temp =0;
				
				
				temp = //m_predict abilityScores[i]* 
								(m_predictiveArr[i][j] - meanArr[j]) * (m_predictiveArr[i][j] - meanArr[j]);
				if (temp > varianceArr[j])
				{
					value = temp;
				}
			}
			
			itemsContributionToVariacne[i] += value;//(value*m_ predictabilityScores[i]);
		}
	//	float itemWeightedContrib = itemsContributionToVariacne[i] / m_pr edictabilityScores[i];
	//	float itemShiftFromAverageContribution = (itemWeightedContrib / averageContribution);
		sumOfAllContribution += itemsContributionToVariacne[i];
		//sumOfWeights+= m_predicta bilityScores[i];
	}	
}

void cStatisticStructure::CalculateVariableMeanAndVariance(float * meanArr , float *varianceArr , unsigned int j )
{
	float sum = 0 ;
	float sumWeights = 0 ;
	for (unsigned int i = 0 ; i < m_count ; i++)
	{//checkcheck
		sum += (m_predictiveArr[i][j] * m_predictabilityScores[i]) ;
		sumWeights += m_predictabilityScores[i];
	}
	meanArr[j] = sum / sumWeights ;

	float sumVariance = 0;
	for (unsigned int i = 0 ; i < m_count ; i++)
	{
		sumVariance +=  ((m_predictiveArr[i][j]- meanArr[j]) * (m_predictiveArr[i][j]- meanArr[j]) *
																			m_predictabilityScores[i]) ;
	}
	varianceArr[j] = sumVariance / sumWeights;

}
	


void cStatisticStructure::CalculateMissingVarianceData(float &allVariableSumMissingVariance, float *meanArr, 
			float *varianceArr , float * missingVarianceArr ,   float * sumOfMissingVariances ,float sumOfWeights, 
						 double *allListVariableVariance,  bool *predictiveSignificantSample, float progresStrength)
{
	allVariableSumMissingVariance = 0 ;
	for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
	{
		//will fill the two arrays in the J position with the mean and variance of the WEIGHTED regression 
		//predictive values. take the predictiblity score as the weight when doing mean and variance
		CalculateVariableMeanAndVariance(meanArr , varianceArr , j );	
		double targetVariance = PERC_TARGET_4_REGR_VALIDATION * allListVariableVariance[j];
		if ((varianceArr[j] < targetVariance )&&(predictiveSignificantSample[j]))
		{
			missingVarianceArr[j] = (float)((targetVariance - varianceArr[j])/ progresStrength) ; //for now 1, latger 0.5 and multi iteration.
				/*
	now that we have the missing variance, in order to get it up we need each missing to get all population change.
	since we evantually devide sum of diff from value minus mean to the population, we have to add each missing value
	N times, or actually total weights times, to get that missing value.
	*/	
			sumOfMissingVariances[j] = missingVarianceArr[j] * sumOfWeights;
			allVariableSumMissingVariance += sumOfMissingVariances[j];
		}
		else
		{
			missingVarianceArr[j] = sumOfMissingVariances[j] = 0 ;
		}
	}
//	averageIncreaseWeight = allVariableSumMissingVariance / sumOfWeights ;

}


/*

void cStatisticStructure::CheckSampleSizeNew(bool *isSignificant)
{
	for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
	{
		if( isSignificant[j])
		{
			if(j==32 ||j==55)
				int dfg = 0 ; 
			isSignificant[j] = IsSignificantSampleSizeOnePredictive(j,
				cConfiguration::GetInstance()->GetMinSDAllowedForRegression(), 0);			
		}
		//else it means that it is cancled from the input api and no need to test check sampl size
	}
}
*/

/*

void cStatisticStructure::CheckSampleSize(bool *isSignificant)
{
	for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
	{
		isSignificant[j] = IsSignificantSampleSizeOnePredictive(j,
			cConfiguration::GetInstance()->GetMinSDAllowedForRegression() , 0);			
	}
}
*/

//IsSignificantSampleSizeOnePredictive(unsigned int predictiveIndex, double minSDforAllowedRegVar)


/*
	
	according to the predictiveSignificantSample[], we will create a new two dimension predictiv array./
	
	*/
void cStatisticStructure::TrasferToSubSet(   short int **predictveArr  ,	  bool * predictiveSignificantSample)
{
	for (unsigned int i=0 ; i < m_count ; i++)
	{
		int shift = 0;
		for ( unsigned int fullIndex = 0 ; fullIndex < m_numOfPredictiveVars ; fullIndex++)
		{
			if(predictiveSignificantSample[fullIndex])
			{
				predictveArr[i][fullIndex+shift] = m_predictiveArr[i][fullIndex];
			}
			else
			{
				shift--;//for exmaple, if fullIndex is 0 and ther is no significance on 0 variabvle
				     //then the 0 position on the  predictiveArr is waiting perhaps for the 1 position on the
					//m_predictiveArr. shift will be now pending to -1 from 1 to 0. 
			}
		}
	}

}

void cStatisticStructure::TrasferToSubSet_2_7_24( 
  double** twoDimArrShort,	bool*   isPredictive, double** twoDimArr, int N, int P, double* meanPredArr)
{
	for (unsigned int i=0 ; i < N ; i++)
	{
		int shift = 0;
		for (  int fullIndex = 0 ; fullIndex < P ; fullIndex++)
		{
			if(isPredictive[fullIndex])
			{
				double valueToInput  = (double)twoDimArr[i][fullIndex];
				if(valueToInput > 20.0)
				{
					valueToInput = meanPredArr[fullIndex];
				}
				twoDimArrShort[i][fullIndex+shift] = valueToInput;
			}
			else
			{
				shift--;//for exmaple, if fullIndex is 0 and ther is no significance on 0 variabvle
				     //then the 0 position on the  predictiveArr is waiting perhaps for the 1 position on the
					//m_predictiveArr. shift will be now pending to -1 from 1 to 0. 
			}
		}
	}

}



void cStatisticStructure::TrasferToSubSet( bool * predictiveSignificantSample)
{
	for (unsigned int i=0 ; i < m_count ; i++)
	{
		int shift = 0;
		for ( unsigned int fullIndex = 0 ; fullIndex < m_numOfPredictiveVars ; fullIndex++)
		{
			if(predictiveSignificantSample[fullIndex])
			{
				m_subPredictiveArr[i][fullIndex+shift] = (double)m_predictiveArr[i][fullIndex];
			}
			else
			{
				shift--;//for exmaple, if fullIndex is 0 and ther is no significance on 0 variabvle
				     //then the 0 position on the  predictiveArr is waiting perhaps for the 1 position on the
					//m_predictiveArr. shift will be now pending to -1 from 1 to 0. 
			}
		}
	}

}
	



/*
this functin will copy back to our  regressionBetaWeightArray and  pValueArray to our corrersponding 
class members and according to the direction of predictiveSignificantSample;
algoroithm:


*/

void cStatisticStructure::TrasferBackToFullSet_2_7_24(double* orgBetaArr , double*  regressionBetaAray,
	  bool*  isPredictive, int sigCount,   double** twoDimArrShort,   double** twoDimArr, int N, int P)
{
	for ( unsigned int j = 0 ; j < P ; j++)
	{
		orgBetaArr[j]=0;
	}
	int shift = 0;
	for ( unsigned int fullIndex = 0 ; fullIndex < P ; fullIndex++)
	{
		if(isPredictive[fullIndex])
		{
			orgBetaArr[fullIndex] = regressionBetaAray[fullIndex + shift];
		}
		else
		{
 			shift--;
		}
	}
}
	
void cStatisticStructure::TrasferBackToFullSet(float *regressionBetaWeightArray ,float *pValueArray, 
				bool *predictiveSignificantSample	, unsigned int simCount)
{
	for ( unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		m_regressionBetaWeightArray[j]=0;
	}//bug, 50 , improve decision making. gap means success in direction. flagged means success in value.
	
	int shift = 0;
	for ( unsigned int fullIndex = 0 ; fullIndex < m_numOfPredictiveVars ; fullIndex++)
	{
		if(predictiveSignificantSample[fullIndex])
		{
			m_regressionBetaWeightArray[fullIndex] = regressionBetaWeightArray[fullIndex + shift];
			m_pValueArray[fullIndex] = pValueArray[fullIndex + shift];  
			//predictveArr[i][fullIndex+shift] = m_predictiveArr[i][fullIndex];
		}
		else
		{
 			shift--;//for exmaple, if fullIndex is 0 and ther is no significance on 0 variabvle
			     //then the 0 position on the  predictiveArr is waiting perhaps for the 1 position on the
				//m_predictiveArr. shift will be now pending to -1 from 1 to 0. 
		}
	}
}
	


// Perform simple weighted linear regression 
// (Current implementation ignores the X100 issue)
//
// Input: 
// *stat - a pointer to class cStatisticStructure. The following fields are used as input: 
//	unsigned int m_count; // number of ??? (individuals?) YES, OUR 2,000 OR SO ARRY 
//	unsigned int m_numOfPredictiveVars; // number of total variables
//	short int ** m_predictiveArr; // 2D array of predictive variables X individuals. YES, X HERE IS m_count. short int 16bit (st.d. * 100)
//	float * m_predictabil ityScores; // array of predicatbility score for each individual assessment. 1 is average. Use as weights for weighted average  
//	short int * m_dependentArr; // the dependent variable (vector)
//	short int * m_predictive_set; // (part of regression output) array of predictive variables (addition to m_predictiveArr, one more individuals. The individual itself)
//
//
// Output: f
// *stat - a pointer to class cStatisticStructure. The following fields are changed: 
//	float m_regressionPerformanceScore; //  performace of regression:  "total explained variance" .
//								//What is this number in terms of regression success? between 0 and 1 - fraction of variance explained 
//	// array of regression coefficients for all variables. the size is of m_numOfPredictiveVars
//	float * m_regressionBetaWeightArray; // coefficients of regression. Beta's, excluding the constant coefficient
//	float m_regressionBetaZeroConstantTermWeightArray; // constant coefficient of regression beta0, including the constant
//	float * m_pValueArray; //NEW . same size of m_regressionBetaWeightArray, each beta weight will have a p value
//	// NEW VARIABLES: For the target individual 

//
//
//

void cStatisticStructure::FillPerGapBetweenHihgestLowestVariable(double* gapBetweenPercLowToHighVar, double* meanPredArr,
	bool* isPredictivee, double** predictiveArr,   int N,   int simVarCount)
{
	for( int p = 0; p < simVarCount ; p++)
	{
		gapBetweenPercLowToHighVar[p]=0.0;
		meanPredArr[p]=0.0;
		if(isPredictivee[p])
		{
			int actualN=0;
			double mean = 0.0;
			for(int i = 0 ; i < N ; i++)
			{
				int asdf=0;
				if (predictiveArr[i][p]<=20.0)
				{
					mean+= predictiveArr[i][p];
					actualN ++;
				}

			}
			mean /= actualN;
			meanPredArr[p]=mean;
			double meanLow= 0.0;
			int sLow=0;
			double meanHigh = 0.0;
			int sHigh=0;
			for(int i = 0 ; i < N ; i++)
			{
				if (predictiveArr[i][p]<=20.0)
				{
					if( predictiveArr[i][p] > mean)
					{
						meanHigh += predictiveArr[i][p];
						sHigh++;
					}
					else
					{
						meanLow+= predictiveArr[i][p];
						sLow++;
					}
				}
			}
			 
			//i.e avg high 8 of 1 person and avg low is 3 of 9 persons makes it 27 on low and 8 of high
			//or 27-8 / 35 = 20/35.   but 1 person on 3 and 9 of 8 is  72-3/75 = 69/75 
			if(sHigh > 0)
			{
				meanHigh /= sHigh;
			}
			if(sLow >0)
			{
				meanLow /= sLow;
			}
			double highRate = (double(sHigh)) /  (double(actualN));
			double lowRate = (double(sLow)) /  (double(actualN));
			
			
			
		//	double highGGap =  cVarianceCalc::Abs(meanHigh - mean);
		//	double lowGap = cVarianceCalc::Abs( meanLow - mean);

			//double weightedGap = sHigh * actualN - 
				//((highGGap  * highRate) - (lowGap *lowRate)) / 
								//		((highGGap  * highRate) + (lowGap *lowRate));
			
			gapBetweenPercLowToHighVar[p] = cVarianceCalc::Abs(highRate - lowRate);
			//if(true)
		//	{
			//	gapBetweenPercLowToHighVar[p] = weightedGap;
			//}
			for(int i = 0 ; i < N ; i++)
			{
				if (predictiveArr[i][p]>20.0)
				{
					predictiveArr[i][p] = mean;
				}
			}
		}
	}
}


bool cStatisticStructure::LinearRegression2_7_24(double* betaArr, double &averageSE ,
	double &variance, double &perforanceScore, double** twoDimArr, double*depArr,
	unsigned int simVarCount,    bool *isPredictivee, unsigned int N,bool isLogReg)
{
	bool ret= false;

	unsigned int sigCount = 0;
	for (unsigned int j = 0 ; j < simVarCount ; j++)
	{
		if(	isPredictivee[j])
		{
			sigCount++;
		}
	}
	if(sigCount > 0 )
	{
		double** twoDimShortTemporaryArray = new double*[N];
		for( int r=0; r<N  ; r++)
		{
			twoDimShortTemporaryArray[r] = new double[simVarCount];
			for(int rr = 0 ; rr< simVarCount ; rr++)
			{
				twoDimShortTemporaryArray[r][rr]=twoDimArr[r][rr];
			}
		}


		double* gapBetweenPercLowToHighVar = new double[simVarCount];
		double* meanPredArr = new double[simVarCount];
		bool* isPredictvedAdjusted = new bool[simVarCount];
		FillPerGapBetweenHihgestLowestVariable(gapBetweenPercLowToHighVar,  meanPredArr,
												isPredictivee, twoDimShortTemporaryArray,N,simVarCount);
		sigCount = 0;
	//for (unsigned int j = 0 ; j < simVarCount ; j++)
//	{
//		if(	isPredictivee[j])
	//	{
	//		sigCount++;
//		}
//	}

		for(int x = 0 ; x < simVarCount ; x++)
		{
			isPredictvedAdjusted[x] = false;
			if(isPredictivee[x])
			{			
				if(gapBetweenPercLowToHighVar[x] < MAX_GAP_OF_LOW_HIGH_PREDICTIVE_SAMPLE)
				{
					isPredictvedAdjusted[x] = true;
					sigCount++;
				}
			}
		}
		if(sigCount > 0)
		{

	//2 7 24 add new funciton like the one now with twoDimArr replacing members. make it static
			TrasferToSubSet_2_7_24(  twoDimShortTemporaryArray,   isPredictvedAdjusted,twoDimArr,N, simVarCount ,   meanPredArr);
	
			double *regressionBetaWeightArray = new double[sigCount];
			//	float *regressionSensitivityCoefficient = new float[sigCount];
			//float *pValueArray = new float[sigCount];
			for(unsigned int i = 0 ; i< sigCount ; i++)
			{
				regressionBetaWeightArray[i]=0.0;
			
			}
			double* D = new double[N]; 
			double* W = new double[N]; 
			for(unsigned int i=0; i< N ; i++)
			{
				D[i]= depArr[i];
				W[i]=1.0;
			}
	
			averageSE=0; 
			variance=0;
			double regressionPerformanceScore=0;
			double tempZeroConst=0;
		//	sizeOfTestGroup=3000;
			cStatisticStructure::LinearRegressionInternalDoubleAPI( averageSE, variance,  tempZeroConst, //nowww
				 regressionBetaWeightArray , regressionPerformanceScore, m_predicted_dependentArr,
					 twoDimShortTemporaryArray,	N, sigCount ,   D, 	 W,  N, false, true);
			//m_regressionBetaZeroConstantTermWeight = (float) tempZeroConst;
			//2 7 24 add new funciton like the one now with twoDimArr replacing members. make it static
			TrasferBackToFullSet_2_7_24(betaArr , regressionBetaWeightArray,
								 isPredictvedAdjusted, sigCount, twoDimShortTemporaryArray,  twoDimArr, N, simVarCount);
			perforanceScore = (float)regressionPerformanceScore;
		
			delete []regressionBetaWeightArray;
			delete []D;
			delete []W;
							 
			 
			ret = true;
		}
		for( int r=0; r<N ; r++)
		{
			delete []twoDimShortTemporaryArray[r] ;
		}
		delete []twoDimShortTemporaryArray;
		delete []gapBetweenPercLowToHighVar ;
		gapBetweenPercLowToHighVar=NULL;
		delete [] isPredictvedAdjusted;
		isPredictvedAdjusted=NULL;		
		delete []meanPredArr;
		meanPredArr=NULL;
	}

	return ret;

}



void cStatisticStructure::LinearRegression( double &averageSE ,double &variance,double &perforanceScore,
					   float * similarityflags , unsigned int simVarCount,
					   double *allListVarianceArr, bool *predictiveSignificantSample , 
					   unsigned int sizeOfTestGroup, bool isControlGroup,bool  isSetStraightReg)
					 //  = new bool [m_numOfPredictiveVars]; )
{

	unsigned int sigCount = 0;
	for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		if(	predictiveSignificantSample[j])
		{
			sigCount++;
		}
	}
	if(sigCount > 0 )
	{
	
		if(m_parentStat ==NULL)
		{
			TrasferToSubSet(     predictiveSignificantSample);
		}
		double *regressionBetaWeightArray = new double[sigCount];
		//	float *regressionSensitivityCoefficient = new float[sigCount];
		//float *pValueArray = new float[sigCount];
		for(unsigned int i = 0 ; i< sigCount ; i++)
		{
			regressionBetaWeightArray[i] = 0 ;
		}
		double* D = new double[m_count]; 
		double* W = new double[m_count]; 
		for(unsigned int i=0; i< m_count ; i++)
		{
			D[i]= m_dependentArr[i];
			W[i]=m_predictabilityScores[i];
			if(isSetStraightReg && (m_predictabilityScores[i]!=0))
			{
				W[i]=1;
			}
		}
	
		averageSE=0; 
		variance=0;
		double regressionPerformanceScore=0;
		double tempZeroConst=0;
	//	sizeOfTestGroup=3000;
		cStatisticStructure::LinearRegressionInternalDoubleAPI( averageSE, variance,  tempZeroConst, //nowww
			 regressionBetaWeightArray , regressionPerformanceScore, m_predicted_dependentArr,
				 m_subPredictiveArr,	m_count, sigCount ,   D, 	 W,  sizeOfTestGroup, isControlGroup, IS_LOGISTIC_REGRESSION);
		m_regressionBetaZeroConstantTermWeight = (float) tempZeroConst;
		TrasferBackToFullSet(m_regressionBetaWeightArray , regressionBetaWeightArray,
			                   predictiveSignificantSample,   m_numOfPredictiveVars);
		perforanceScore = (float)regressionPerformanceScore;

		delete []regressionBetaWeightArray;
		delete []D;
		delete []W;
	}
	else
	{
		double mean = 0 ;
		double sumWeights = 0 ;
		for(unsigned int i=0; i< m_count ; i++)
		{
			mean += m_predictabilityScores[i] * m_dependentArr[i];
			sumWeights += m_predictabilityScores[i] ;
		}
		mean /= sumWeights;
		m_regressionBetaZeroConstantTermWeight = mean;
		for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
		{
			m_regressionBetaWeightArray[j] = 0 ;
		}
	}




//	delete []allListVariableVariance;
//	delete [] predictiveSignificantSample;

	m_predictedResult = m_regressionBetaZeroConstantTermWeight; 
	for (unsigned int j=0; j <m_numOfPredictiveVars; j++) 
	{
		m_predictedResult += m_regressionBetaWeightArray[j] * m_predictive_set[j]; 
	}

}



void cStatisticStructure::TrasferBackToFullSet(float* betaArr , double* regressionBetaWeightArray, 
										bool* allowedVariable	, unsigned int P)
{
//	void cStatisticStructure::TrasferBackTo FullSet(float *regressionBetaWeightArray ,float *pValueArray, 
//				bool *predictiveSignificantSample	, unsigned int sigCount)

	for ( unsigned int j = 0 ; j < P ; j++)
	{
		betaArr[j]=0;
	}//bug, 50 , improve decision making. gap means success in direction. flagged means success in value.
	
	int shift = 0;
	for ( unsigned int fullIndex = 0 ; fullIndex < P ; fullIndex++)
	{
		if(allowedVariable[fullIndex])
		{
			betaArr[fullIndex] = (float) regressionBetaWeightArray[fullIndex + shift];
			//m_pValueArray[fullIndex] = pValueArray[fullIndex + shift];  
			//predictveArr[i][fullIndex+shift] = m_pre dictiveArr[i][fullIndex];
		}
		else
		{
 			shift--;//for exmaple, if fullIndex is 0 and ther is no significance on 0 variabvle
			     //then the 0 position on the  predictiveArr is waiting perhaps for the 1 position on the
				//m_predi ctiveArr. shift will be now pending to -1 from 1 to 0. 
		}
	}
}
	




//rIS_NORMELIZE_DPENDENT
//IS_CUTTING_DEPENDENT_EXTREME

void cStatisticStructure::NormelizeDependent_7_26_14()
{
	double sumWeights = 0 ;
	double meanDep=0;
	double sdDep=0;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		meanDep += (m_dependentArr[i] * m_predictabilityScores[i]   );	
		sumWeights += m_predictabilityScores[i];
	}
	meanDep /= sumWeights;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		sdDep += ((m_dependentArr[i]-meanDep)*(m_dependentArr[i]-meanDep)*  m_predictabilityScores[i]);	
	}
	sdDep /= sumWeights;
	sdDep = pow(sdDep,(double )0.5);

	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		double localSD =  (m_dependentArr[i] - meanDep )/  sdDep;
		m_dependentArr[i] =(localSD *100);
	}

	double meanDepTest=0;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		meanDepTest += (m_dependentArr[i] * m_predictabilityScores[i]   );	
	}
	meanDepTest /= sumWeights;
	int gggg=0;

}


void cStatisticStructure::NormelizeAndCutExtremeDependent()
{
	
	double sumWeights = 0 ;
	double meanDep=0;
	double sdDep=0;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		meanDep += (m_dependentArr[i] * m_predictabilityScores[i]   );	
		sumWeights += m_predictabilityScores[i];
	}
	meanDep /= sumWeights;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		sdDep += ((m_dependentArr[i]-meanDep)*(m_dependentArr[i]-meanDep)*  m_predictabilityScores[i]);	
	}
	sdDep /= sumWeights;
	sdDep = pow(sdDep,(double )0.5);

	short int uppoerLimit= (short)(meanDep + (3*sdDep));
	short int lowerLimit = (short)(meanDep - (3*sdDep));
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		if(IS_CUTTING_DEPENDENT_EXTREME)
		{
			if(m_dependentArr[i] > uppoerLimit)
			{
				m_dependentArr[i] = uppoerLimit;	
			}
			if(m_dependentArr[i]  < lowerLimit)
			{
				m_dependentArr[i] = lowerLimit;
			}
		}
	}
	
	m_meanDependent=0;
	m_sdDependent=0;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		m_meanDependent += (m_dependentArr[i] * m_predictabilityScores[i]   );	
	}
	m_meanDependent /= sumWeights;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		m_sdDependent += ((m_dependentArr[i]-m_meanDependent)*
										(m_dependentArr[i]-m_meanDependent)*(m_predictabilityScores[i]));	
	}
	m_sdDependent /= sumWeights;
	m_sdDependent = pow(m_sdDependent,(double )0.5);

	
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		double localSD =  (m_dependentArr[i] - m_meanDependent )/  m_sdDependent;
		if(IS_NORMELIZE_DPENDENT)
		{
			m_dependentArr[i] =(localSD *100);
		}
	}
}



void MatrixMultiplication( double** mOut, int rOut, int cOut, double** mIn1, int r1, int c1, 
	                       double** mIn2, int r2, int c2  )

{
	
	if(c1 != r2) 
	{
		return;
	}

	/*
	cOut = c2;
	rOut = r1;
	*/

	for(int r = 0 ; r < rOut ; r++)
	{
		for(int c = 0 ; c < cOut ; c++)
		{
			double sum = 0 ;
			for( int ix = 0 ; ix < c1 ; ix++)
			{
				sum+= mIn1[r][ix] * mIn2 [ix][c]; 	
			}
			mOut[r][c] = sum;
		}
	}
}


//3 11 17 updated function
void  MatrixCstror(double** &mOut,  int rOut , int cOut, bool* memoryBlock, int memoryBlockSize, int &memoryBlockIndex )
{

	
	int sizeOfPnt = sizeof (double*);
	int howMuchSizeNeededForArrOfPinters = sizeOfPnt * rOut;

	int sizeOfDouble = sizeof(double);
	int howMuchSizeNeededForDoubleArrList = sizeOfDouble * rOut * cOut;

	int totalSizeNeeded = howMuchSizeNeededForArrOfPinters + howMuchSizeNeededForDoubleArrList;
	
	int sizeLEftInMemBlock = memoryBlockSize - memoryBlockIndex;

	int checkingPreviousIndex = memoryBlockIndex;

	if((memoryBlock != NULL) && (sizeLEftInMemBlock >= totalSizeNeeded) )
	{
		mOut = (double**) (&(memoryBlock[memoryBlockIndex]));//new double*[rOut];
		memoryBlockIndex += howMuchSizeNeededForArrOfPinters;

		for(int r = 0 ; r< rOut ; r++)
		{
			mOut[r] = (double*) (&(memoryBlock[memoryBlockIndex]));// new double[cOut];
			memoryBlockIndex += (sizeOfDouble *  cOut);
			for(int c = 0 ; c < cOut ; c++)
			{
				mOut[r][c] = 0.0; 
			}
		}
		{
			int howMuchWeMovied = memoryBlockIndex -  checkingPreviousIndex ;
			if(howMuchWeMovied  == totalSizeNeeded)
			{
				int sdf = 0 ; 
			}
			else
			{
				int sdfgg = 0 ;  //we dont want to get here
			}
		}
		return;
	}



	mOut = new double*[rOut];
	for(int r = 0 ; r< rOut ; r++)
	{
		mOut[r] = new double[cOut];
		for(int c = 0 ; c < cOut ; c++)
		{
			mOut[r][c] = 0.0; 
		}
	}
}


//3 11 17
void MatrixCstruAndCopyAndShiftedExtraCulumn( double** &mOut , double** mIn, int rIn, int cIn,
										bool* memoryBlock, int memoryBlockSize, int &memoryBlockIndex )
{
	MatrixCstror(mOut,  rIn , cIn+1,  memoryBlock,  memoryBlockSize, memoryBlockIndex );



//	mOut = new double*[rIn];
	for(int r = 0 ; r< rIn ; r++)
	{
		//mOut[r] = new double[cIn +1];
		mOut[r][0] = 1.0;
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c+1] = mIn[r][c]; 
		}
	}
	
}


//devision of element by element 
void MatrixDivision (double** mOut, double** mInDno, double** mInDdem, int rIn , int cIn)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = mInDno[r][c] / mInDdem[r][c];
		}
	}

}

//Multiplicatio of element by element 
void MatrixMultiplicatioElement (double** mOut, double** mIn1, double** mIn2, int rIn , int cIn)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = mIn1[r][c] * mIn2[r][c];
		}
	}

}

//Addition of element by element 
void MatrixAdditionElement (double** mOut, double** mIn1, double** mIn2, int rIn , int cIn)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = mIn1[r][c] + mIn2[r][c];
		}
	}

}

void  MatrixCopy(double** mOut, double** mIn,  int rIn , int cIn)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = mIn[r][c];
		}
	}
}


void MatrixSubstruction ( double** mOut  , double** mInBase , 
											double** mInSub ,  int rIn ,int cIn)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = mInBase[r][c] - mInSub[r][c];
		}
	}
}
			//normDep = , dep - probMatTemp




void MatrixInitilizeFromArr(double** mOut,  int rIn , double* arr)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		mOut[r][0] = arr[r];
	}
}



void MatrxCopyAndAddConst(double** mOut, double** mIn,  int rIn , int cIn, double addCnst)
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = mIn[r][c] + addCnst;
		}
	}
}

bool CheckIfAnyElementExtreme(double** mIn,  int rIn , int cIn , double thr)
{
	bool isExtrment = false;
	for(int r = 0 ; r< rIn && (!isExtrment) ; r++)
	{
		for(int c = 0 ; c < cIn && (!isExtrment) ; c++)
		{
			if(	    (mIn[r][c] *(1.0 - mIn[r][c]) ) <  thr)
			{
				isExtrment = true;
			}
		}
	}
	return isExtrment;

}

bool  CheckConvergance(double** mat, double** matOld, int rIn, int cIn, double convcrit     )
{
	bool isExtrment = true;
	for(int r = 0 ; r< rIn && (isExtrment) ; r++)
	{
		for(int c = 0 ; c < cIn && (isExtrment) ; c++)
		{
			if(	   (cVarianceCalc::Abs (mat[r][c] - matOld[r][c])) >  (convcrit * (cVarianceCalc::Abs(matOld[r][c]) ) ))
			{
				isExtrment = false;
			}
		}
	}
	return isExtrment;
}






void  MatrixExp(double** mOut, double** mIn, int rIn , int cIn )
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = exp( mIn[r][c]);
		}
	}
}

void InverseMatrixPtimesOneMinusP(	double** mOut, double** mIn,  int rIn , int cIn )
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] = 1.0 / ( mIn[r][c] * (1.0 - mIn[r][c]));
		}
	}
}


void MatrixPtimesOneMinusP(	double** mOut, double** mIn,  int rIn , int cIn )
{
	for(int r = 0 ; r< rIn ; r++)
	{
		for(int c = 0 ; c < cIn ; c++)
		{
			mOut[r][c] =  ( mIn[r][c] * (1.0 - mIn[r][c]));
		}
	}
}







void  MatrixDistr(double**mOut,  int rOut)
{
	
	for(int r = 0 ; r< rOut ; r++)
	{
		delete []mOut[r] ;
	}
	delete [] mOut;
}


#define MEMORY_BLOCK_SIZE_LOGISTIC_REG 100 //1 14 24


//3 11 17
void LogisticRegression(double &betaZero, double * betaArr , 
			double **predictiveArr,	double * dependentArr, int samSize, int p)
{
	//p = 3;
	/*
	-crate predictiveArrExt with one more variable, and push 1 as first predidctive across all items.
	-also, create pExt = p+1
	*/

	double** predictiveArrExt = NULL;

	int memoryBlockSize= MEMORY_BLOCK_SIZE_LOGISTIC_REG;
	bool* memoryBlock= NULL;
	if(memoryBlockSize > 0)
	{
		memoryBlock = new bool[memoryBlockSize];
	}
	int memoryBlockIndex=0 ;

	MatrixCstruAndCopyAndShiftedExtraCulumn( predictiveArrExt , predictiveArr, samSize, p,  memoryBlock,  memoryBlockSize, memoryBlockIndex );



	int pExt = p+1;

	

	double** betaMat = NULL;
	//number of rows is pExt . the change between culumn number and row nubmer is for the consistancy of matxi multiplication
	MatrixCstror(betaMat,  pExt , 1, memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** betaMatOld = NULL;
	//number of rows is pExt . the change between culumn number and row nubmer is for the consistancy of matxi multiplication
	MatrixCstror(betaMatOld ,  pExt , 1, memoryBlock,  memoryBlockSize, memoryBlockIndex);


	
	double** 	preBetaMat = NULL;
	//number of rows is pExt . the change between culumn number and row nubmer is for the consistancy of matxi multiplication
	MatrixCstror(	preBetaMat ,  pExt , 1, memoryBlock,  memoryBlockSize, memoryBlockIndex);


		 
//% algorithm parameters

	
	int iterMax=100; //iter=0;
	double convcrit = pow( 10.0, (-6.0));

	bool endMainLoop = false;
	int iter = 0 ;
	double** probMat = NULL;
	MatrixCstror(probMat ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** xTimesBetaMatOld = NULL;
	MatrixCstror(xTimesBetaMatOld ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);




	double** probMatTemp = NULL;
	MatrixCstror(probMatTemp ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** inverseProb = NULL;
	MatrixCstror(inverseProb ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** prob = NULL;
	MatrixCstror(prob ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** dep = NULL;
	MatrixCstror(dep ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	MatrixInitilizeFromArr(dep , samSize , dependentArr);

	double** normDep = NULL;
	MatrixCstror(normDep ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** probZ = NULL;
	MatrixCstror(probZ ,  samSize , 1,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** inverseMat = NULL;
	MatrixCstror(inverseMat, pExt, pExt,  memoryBlock,  memoryBlockSize, memoryBlockIndex);

	double** mOut = NULL;
	MatrixCstror(mOut, pExt, samSize,  memoryBlock,  memoryBlockSize, memoryBlockIndex);


	
	while(!endMainLoop)
	{
		MatrixCopy(betaMatOld, betaMat,  pExt, 1);

		MatrixMultiplication( xTimesBetaMatOld, samSize,1 , predictiveArrExt, samSize, pExt,  betaMatOld, pExt,  1  );
		
	
		MatrixExp(probMat, xTimesBetaMatOld,  samSize , 1 );

		MatrxCopyAndAddConst (probMatTemp, probMat, samSize , 1,  1.0 );

		MatrixDivision (probMatTemp, probMat, probMatTemp, samSize , 1);

		double thres = pow(10.0 , (-10.0));
		bool isAnyElmExtreme = CheckIfAnyElementExtreme(probMatTemp, samSize , 1, thres);
		
		if(isAnyElmExtreme)
		{
			endMainLoop = true;
		}
		else
		{
			MatrixPtimesOneMinusP(	prob, probMatTemp, samSize , 1);
			InverseMatrixPtimesOneMinusP(	inverseProb, probMatTemp, samSize , 1);

			MatrixSubstruction ( normDep  , dep , probMatTemp ,samSize , 1);
			//normDep = , dep - probMatTemp

			MatrixMultiplicatioElement (probZ, inverseProb, normDep, samSize , 1);
			MatrixAdditionElement (probZ, probZ, xTimesBetaMatOld, samSize , 1);
			//z = xTimesBetaMatOld  + inverseProb * normDep 
		
			// ProbZ = Prob *z :Dim:  samSize x 1
			//MatrixMultiplicatioElement (probZ, prob, probZ, samSize , 1);
			//inv( predictiveArrExt'*Prob * predictiveArrExt)  * Prob *z

			// mOut = predictiveArrExt'*Prob: Dim:  ???? (samSize x pExt)' x samSize  = samSize x 1
			// the out put is transpose (marked with the ' ) of the formal matrix multiplication result.
			for(int r = 0 ; r < samSize ; r++)
			{
				for(int c = 0 ; c < pExt ; c++)
				{
					mOut[c][r] = predictiveArrExt [r][c]*prob[r][0];
				}
			}
				
			// mOut2 = mOut *  predictiveArrExt
			MatrixMultiplication( inverseMat, pExt,pExt , mOut, pExt, samSize,  predictiveArrExt, samSize, pExt);

			//C = (X'*W*X)^(-1) :Dim: (pExt x pExt)^-1 = pExt x pExt
			cStatisticStructure::SymmetricMatrixInvert(inverseMat, pExt);

			// D = (mOut)'xProbz :Dim: (samSize x pExt)' x pExt x 1  = pExt x 1
			MatrixMultiplication( preBetaMat, pExt,1 , mOut, pExt, samSize,  probZ, samSize, 1 );

			// E = C * D  :Dim: pExt x pExt  x pExt x 1 =pExt x 1   
			MatrixMultiplication( betaMat, pExt,1 , inverseMat, pExt, pExt,  preBetaMat, pExt, 1 );


			endMainLoop = CheckConvergance(betaMat, betaMatOld, pExt, 1, convcrit     );
		}
	

	
	//}
	// W=diag(p.*(1-p)); not implemented as is, since it should be a diagonal matrix of samSize x samSize
	//z= X*b_old+W^(-1)*(y-p);
	//b = (X'*W*X)^(-1)*X'*W*z;

     //% Check stopping conditions
/*
%     if (~any(abs(b-b_old) > convcrit * max(seps, abs(b_old)))), break; end

    if (~any(abs(b-b_old) > convcrit * abs(b_old))), break; end
	*/



 
		iter ++;
		if( iter == iterMax)
		{
			endMainLoop = true;
		}




		
	}
	int dddddd=0;

	betaZero = betaMat[0][0];
	for(unsigned int j = 0 ; j < p ; j++)
	{
		betaArr[j] = betaMat[j+1][0];
	}
	//betaMat
	int dfg=0;

		//deletes

	if(memoryBlock != NULL)
	{
		delete []memoryBlock;
		return;
	}
	MatrixDistr(predictiveArrExt ,samSize);
	MatrixDistr(betaMat,  pExt);
	MatrixDistr(betaMatOld ,  pExt);
	MatrixDistr(preBetaMat,  pExt);
	MatrixDistr(probMat,  samSize);
	MatrixDistr(xTimesBetaMatOld , samSize);
	MatrixDistr(probMatTemp , samSize);
	MatrixDistr( inverseProb , samSize);
	MatrixDistr( prob , samSize);
	MatrixDistr(dep , samSize);
	MatrixDistr(normDep , samSize);
	MatrixDistr(probZ , samSize);
	MatrixDistr(inverseMat , pExt);
	MatrixDistr(mOut ,pExt);//note

}	

	

/*	
	int rOut = r1;
	int cOut = c2;
	double** mOut = NULL;
	MatrixCstror(mOut,  rOut , cOut);
	MatrixMultiplication(  mOut,  rOut,  cOut, mIn1,  r1,  c1, mIn2,  r2,  c2   );

*/




	// MatrixDistr(double**mOut,  int rOut);




	/*
	
	*/





	//function B = logit_fit(X,y)

//[n,p]=size(X);

   /*
% initial values

b = zeros(p,1);

while iter<iterMax,

    iter = iter +1;

    b_old = b;

    p = exp(X*b_old)./(1+exp(X*b_old));

    if any(p.*(1-p)<10^-10), disp('perfect separation'); break;end

    W=diag(p.*(1-p));

    z= X*b_old+W^(-1)*(y-p);

    b = (X'*W*X)^(-1)*X'*W*z;

     % Check stopping conditions

%     if (~any(abs(b-b_old) > convcrit * max(seps, abs(b_old)))), break; end

    if (~any(abs(b-b_old) > convcrit * abs(b_old))), break; end

 

end

if iter >= iterMax

    warning(message('logit_fit:fit did not converge:IterationLimit'));

end

B=b;

}
*/



void cStatisticStructure::LinearRegressionInternalDoubleAPI( double &averageSE, double &variance,
	double & zeroConstant, 
		double * betaArr , double& regressionPerformanceScore,double * predicted_dependentArr,
							double **predictiveArr,	unsigned int N, 
			unsigned int p,  double * dependentArr, double * predictabilityScores , 
			unsigned int sizeOfTestGroup, bool isControlGroupp, bool isLogisticReg)

{
	//two outputs for the logistic regression:
	   //zeroConstant  beta zero const 
	   //betaArr list of 0 to p-1 weights 
	
	if( isLogisticReg)
	{
		//2 13 24
		 
		LogisticRegression(zeroConstant,  betaArr , 
			predictiveArr,	 dependentArr, N,  p); 
	
	//	double & zeroConstant, 	double * betaArr , 
		//	double **predictiveArr,	unsigned int N, 
			//unsigned int p,  double * dependentArr, double * predictabilityScores , 
		//	unsigned int sizeOfTestGroup, bool isControlGroupp);
		 
		return;
	}
	
	
	unsigned int i,j,k;
	//unsigned int N = m_count; // shorter names for # of points
//	unsigned int p = m_numOfPredictiveVars; // shroter name for # of predictive variables 
	double r_square = 0; // the error in the regression 
	unsigned int target_index = 0; // index of the target individual (how is it determined?? set as zero for now) 	
	double  *B = new double [p + 1]; // array holding X^T * Y . new includng constant in 0 positoin
	double  **V = new double *[p+1]; // Internal Matrix used in the regression. Holding X^T*X and it's inverse 
	double  *beta = new double[p+1]; // regression coefficients 
	// Allocate memory for internal variables 
	for(i=0; i< (p + 1); i++) // loop on  variables
	{
		V[i] = new double [p +1]; 
	}

	


		//summerize the predictivlity weights of all N profiles
		//taking care of all 0 raw and 0 culumn to get a 1 value. can be done in one loop but more clear in two
		for ( i=0 ; i < (p+1) ; i++ )
		{
			V[i][0] = 1; V[0][i] = 1;
		}
		//
		double weightsSum=0.0; // sum of predictability weights over all individuals in k group
		for(k=0; k< N; k++) // loop on k group
		{
			weightsSum += predictabilityScores[k]; //DIMAjan i see 360 out of 540 with 0.  it is 66%, not 75. shoulf ber mode 4    not 3.
		}
	
		for(i=0; i<p; i++) // loop on  variables //
		{
			B[i+1] = 0;
			for(j=0; j<p; j++) // loop on variables again
			{
				V[i+1][j+1] = 0;
			}
		}

		for(k=0; k< N ; k++) // loop on individuals
		{
			if( predictabilityScores [k] >0)
			{
				for(i=0; i<p; i++) // loop on  variables //
				{
					for(j=0; j<p; j++) // loop on variables again
					{
					
				
							//PRAR-READ here you can see how the V[][] is reading from the m_predictiveArr
							V[i+1][j+1] += predictabilityScores [k] * //[i] *  //EREZ why we choose i and not k? i changed. also to be our main and in regards to predictibality score?
							(   (predictiveArr[k][i])) * (  (predictiveArr[k][j])); // add weights (perform weighted regression) 
						
					}
					//	V[i+1][j+1] += m_pred ictabilityScores [N-1] * 
					//		( double  (m_predictiveArr[N-1][i]+1)) * (double  (m_predictiveArr[N-1][j]+1));  // +1 and all of this line is to avoid matrix function to collapse
					//	if(predictiveSignificantSample[
					B[i+1] += predictabilityScores[k] * predictiveArr[k][i] * dependentArr[k]; // add weights (perform weighted regression) 
				}
			}
		}
		for(i=0; i<p; i++) // loop on  variables //
		{
			for(j=0; j<p; j++) // loop on variables again
			{
				V[i+1][j+1] /= weightsSum;
			}
			B[i+1] /= weightsSum;
		}


		
	
		//taking care of the first 0 position in B, which is a different calculation outside the above triple loop
		B[0] = 0;
		for (k=0; k<N; k++) //EREZEREZ open B bigger in 1 and to i+1
		{
			B[0] += predictabilityScores[k] * dependentArr[k]; // add weights (perform weighted regression) 
		}
		B[0] /= weightsSum;

	

		//	p + 1 including the constant first raw and first culumn
		SymmetricMatrixInvert(V, p +1); // invert matrix (inverted matrix stored in the same array V)

	
		for (i=0; i<  (p + 1) ; i++) // loop over predictive variables and compute the regression coefficients 
		{
			beta[i] = 0;
			for (j=0; j < (p + 1); j++) // loop on variables
				beta[i] += V[i][j] * B[j]; //
		}


		{
		//	sizeOfTestGroup = N;
			double weightsTestsum = 0 ;
			sizeOfTestGroup = cVarianceCalc::Min((int)sizeOfTestGroup , N);
			for(i=0; i<sizeOfTestGroup; i++) // loop on individuals and compute the predicted value by the regression 
			{
				double tempWeight =predictabilityScores[i];
				if(isControlGroupp)
				{
					if(predictabilityScores[i]==0)
					{
						tempWeight =1;
					}
					else
					{
						tempWeight =0;
					}
				}
				weightsTestsum += tempWeight ;//predictabilityScores[i];///////llllllllllll
				//stat->m_predicted_dependentArr[i] = 0; 
				double tempFloat = beta[0];
				for (j=0; j <p; j++) 
				{
					tempFloat += beta[j+1] * predictiveArr[i][j]; 
				}  
				predicted_dependentArr[i] =  tempFloat; 
				double tempDif = (predicted_dependentArr[i] - dependentArr[i]);//EREZ
			
				//tempDif ;
 				r_square += (tempDif * tempDif *tempWeight );//* predictabilityScores[i]);
					//(m_predicted_dependentArr[i] - m_dependentArr[i]);	// Compute r^2 - the regression error: (observed-expected)^2 
			} 
			//float tempX = r_. 0square / N; 
			if(weightsTestsum > 0)
			{
				r_square /= (weightsTestsum);
			}
			
			double meanDependent = 0; 
			double varDependenat = 0;
			for(i = 0 ; i<  sizeOfTestGroup ; i++)
			{
				double tempWeight =predictabilityScores[i];
				if(isControlGroupp)
				{
					if(predictabilityScores[i]==0)
					{
						tempWeight =1;
					}
					else
					{
						tempWeight =0;
					}
				}
				double dep = dependentArr[i];// /100.0f;
				meanDependent += (dep*tempWeight  );//*predictabilityScores[i]);
			//	varDependenat += (dep*dep * predictabilityScores[i]);	
			}
			if(weightsTestsum > 0)
			{
				meanDependent /= weightsTestsum; 
			}
		//	varDependenat -= (meanDependent*meanDependent);
			for(i = 0 ; i<  sizeOfTestGroup ; i++)
			{
				double tempWeight =predictabilityScores[i];
				if(isControlGroupp)
				{
					if(predictabilityScores[i]==0)
					{
						tempWeight =1;
					}
					else
					{
						tempWeight =0;
					}
				}
				double temp = dependentArr[i]-meanDependent ;// /100.0f;
				//meanDependent += (dep *predictabilityScores[i]);
				varDependenat += (temp*temp*tempWeight );//* predictabilityScores[i]);	
			}
			if(weightsTestsum >0)
			{
				varDependenat /= weightsTestsum;
			}


			averageSE = r_square ;
			variance = varDependenat;
			if(variance)
			{
				regressionPerformanceScore= (variance-averageSE)/variance;
			}
		}
/*			r_square /= varDependenat;
			float sigma_square = 0;
			if ((N - p - 1) != 0)
			{
				sigma_square = r_square / (N - p - 1); // get sigma^2 = RSS / (N-p-1) //EREZ ??? p - 1?
			}
			int t_df = N-p-1; // set degrees of freedom for t-test 

		*/

			// Assign regression outputs (they also serve as input for K-N algorithm)
		//	regressionPerformanceScore = r_square / N ; // regresson perfomrnac eis  "total explained variance" .
			
	for(i=0; i< p; i++) // copy beta values
	{
		betaArr[i] = beta[i+1]; //  * HUNDRED; // coefficients of regression. Beta's, excluding the constant coefficient
	}
	zeroConstant = beta[0]; // constant coefficient of regression beta0, 

	
	

	// Free memory for internal variables of the regression 
	for(i=0; i< (p + 1); i++)
		delete [] V[i]; 
	delete []V; delete []B; delete []beta; 

}



void cStatisticStructure::LinearRegressionInternal( float &averageSE ,float &variance,		
	float & regressionBetaZeroConstantTermWeight, 
		float * regressionBetaWeightArray , float& regressionPerformanceScore,double * predicted_dependentArr,
						float *pValueArray,	short int **predictiveArr,	unsigned int N, 
			unsigned int p,  short int * dependentArr, float * predictabilityScores,  short int regression_type)//(cStatisticStructure *stat)
{
	int dddd=0;
	unsigned int i,j,k;
	//unsigned int N = m_count; // shorter names for # of points
//	unsigned int p = m_numOfPredictiveVars; // shroter name for # of predictive variables 
	float r_square = 0; // the error in the regression 
	unsigned int target_index = 0; // index of the target individual (how is it determined?? set as zero for now) 	
	double  *B = new double [p + 1]; // array holding X^T * Y . new includng constant in 0 positoin
	double  **V = new double *[p+1]; // Internal Matrix used in the regression. Holding X^T*X and it's inverse 
	double  *beta = new double[p+1]; // regression coefficients 
	// Allocate memory for internal variables 
	for(i=0; i< (p + 1); i++) // loop on  variables
	{
		V[i] = new double [p +1]; 
	}

	switch (regression_type) // choose which regression to use 
	{
	case LINEAR: //,LINEAR_TWO_STEPS: // run linear regression 
		{
			//summerize the predictivlity weights of all N profiles
			//taking care of all 0 raw and 0 culumn to get a 1 value. can be done in one loop but more clear in two
			for ( i=0 ; i < (p+1) ; i++ )
			{
				V[i][0] = 1; V[0][i] = 1;
			}
			//
			double weights_sum=0.0; // sum of predictability weights over all individuals in k group
			for(k=0; k< N; k++) // loop on k group
			{
				weights_sum += predictabilityScores[k]; //DIMAjan i see 360 out of 540 with 0.  it is 66%, not 75. shoulf ber mode 4    not 3.
			}


			for(i=0; i<p; i++) // loop on  variables //
			{
				for(j=0; j<p; j++) // loop on variables again
				{
					V[i+1][j+1] = 0;
					for(k=0; k< N ; k++) // loop on individuals
					{
						//PRAR-READ here you can see how the V[][] is reading from the m_predictiveArr
						V[i+1][j+1] += predictabilityScores [k] * //[i] *  //EREZ why we choose i and not k? i changed. also to be our main and in regards to predictibality score?
						( double  (predictiveArr[k][i])) * (double  (predictiveArr[k][j])); // add weights (perform weighted regression) 
					}
				//	V[i+1][j+1] += m_pred ictabilityScores [N-1] * 
				//		( double  (m_predictiveArr[N-1][i]+1)) * (double  (m_predictiveArr[N-1][j]+1));  // +1 and all of this line is to avoid matrix function to collapse
				//	if(predictiveSignificantSample[
					V[i+1][j+1] /= weights_sum;
				}
				B[i+1] = 0;
				for (k=0; k<N; k++) //EREZEREZ open B
				{
					B[i+1] += predictabilityScores[k] * predictiveArr[k][i] * dependentArr[k]; // add weights (perform weighted regression) 
				} 
				B[i+1] /= weights_sum;
			}
			
			//taking care of the first 0 position in B, which is a different calculation outside the above triple loop
			B[0] = 0;
			for (k=0; k<N; k++) //EREZEREZ open B bigger in 1 and to i+1
			{
				B[0] += predictabilityScores[k] * dependentArr[k]; // add weights (perform weighted regression) 
			}
			B[0] /= weights_sum;
			//	p + 1 including the constant first raw and first culumn
			SymmetricMatrixInvert(V, p +1); // invert matrix (inverted matrix stored in the same array V)

			for (i=0; i<  (p + 1) ; i++) // loop over predictive variables and compute the regression coefficients 
			{
				beta[i] = 0;
				for (j=0; j < (p + 1); j++) // loop on variables
					beta[i] += V[i][j] * B[j]; //
			}

			for(i=0; i<N; i++) // loop on individuals and compute the predicted value by the regression 
			{
				//stat->m_predicted_dependentArr[i] = 0; 
				double tempFloat = beta[0];
				for (j=0; j <p; j++) 
				{
					tempFloat += beta[j+1] * predictiveArr[i][j]; 
				}   
				predicted_dependentArr[i] =  tempFloat; 
				double tempDif = (predicted_dependentArr[i] - ((double)dependentArr[i]));//EREZ
				tempDif /= 100.0f;
				//tempDif ;
				r_square += (tempDif * tempDif * ((double)predictabilityScores[i]));
					//(m_predicted_dependentArr[i] - m_dependentArr[i]);	// Compute r^2 - the regression error: (observed-expected)^2 
			} 
			//float tempX = r_square / N; 
			r_square /= ((float)weights_sum);
			
			
			
			float meanDependent = 0; 
			float varDependenat = 0 ;
			for(i = 0 ; i<  N ; i++)
			{
				float dep = dependentArr[i] /100.0f;
				meanDependent += (dep *predictabilityScores[i]);
				varDependenat += (dep*dep * predictabilityScores[i]);	
			}
			meanDependent /= (float)weights_sum; 
			varDependenat /= (float)weights_sum;
			varDependenat -= (float)(meanDependent*meanDependent);
	
			averageSE = r_square ;
			variance = varDependenat;
			
			r_square /= varDependenat;
			float sigma_square = 0;
			if ((N - p - 1) != 0)
			{
				sigma_square = r_square / (N - p - 1); // get sigma^2 = RSS / (N-p-1) //EREZ ??? p - 1?
			}
			int t_df = N-p-1; // set degrees of freedom for t-test 

			for (i=0; i<p; i++) // loop over predictive variables and compute p-value for each beta coefficient 
			{
				// (RSS/(p-1))/s2;      // Compute F statistic for regression
				//z_score =  beta[i+1] / sqrt( sigma_square * V[i][i] ); // EREZ : deleted two lines . Compute t-statistic for each coefficient
				//stat->m_pValueArray[i] = 2 * MAX(t_Distribution(z_score, t_df), 1-t_Distribution(z_score, t_df));  // use two-sided t-test 
				pValueArray[i] =1.0; //EREZ added this line instead temporary
			}

			// Assign regression outputs (they also serve as input for K-N algorithm)
			regressionPerformanceScore = r_square / N ; // regresson perfomrnac eis  "total explained variance" .
			
			for(i=0; i< p; i++) // copy beta values
			{
				regressionBetaWeightArray[i] = (float)beta[i+1]; //  * HUNDRED; // coefficients of regression. Beta's, excluding the constant coefficient
			}
			regressionBetaZeroConstantTermWeight = (float) beta[0]; // constant coefficient of regression beta0, 



			break; // switch case linear regression
		}
	case STEPWISE: // Note: Currently the step-wise regression ignores the weights (predictability). The linear regression above uses the weights 
		{
			float * Y = new float[N];
			beta[0] = 0; 
			for(i=0; i<N; i++) // copy dependent variable
			{
				Y[i]=  dependentArr[i];
				beta[0] += Y[i]; // set regression constant
			}
			beta[0] /= N;
			for(i=0; i< p; i++) // loop on variables according to input order and regress them one by one 
			{ //simple_linear_regression(float *Y, short int **X, unsigned int pIndex, unsigned int N, 
													//					float *r_square, float *pval)

			//	beta[i+1] = simple_linear_regression(Y, predictiveArr, i , N, &r_square, &pValueArray[i]); // perform simple linear regression with the adjusted variable 
				for(j=0; j<N; j++) // adjust output variable by removing the contribution of current input variable 
					Y[j] = Y[j] - beta[i+1] * predictiveArr[j][i]; 
				regressionBetaWeightArray[i] = beta[i+1]; 
			}
			delete []Y;
		
		break;
		}

	case LOGISTIC:
		{
		
		// Yet to fill 
		break;
		}
	} // close switch statement chooding regression type 

 
	float sumOfBeta=0;
	for(i=0; i<p; i++) // Compute sensitivity parameter for each variable 
	{
		sumOfBeta += ABS(regressionBetaWeightArray[i]);
	}
	for(i=0; i<p; i++) // Compute sensitivity parameter for each variable 
	{//
	}   //

	// Free memory for internal variables of the regression 
	for(i=0; i< (p + 1); i++)
		delete [] V[i]; 
	delete []V; delete []B; delete []beta; 
	/////////////////////////////////////////////////////////////////////////////////////
	// Option: use a p-value cutoff - include only variables with p-value < cutoff 
	// Angela: Normalization + Regression document
	// Update .doc on my two functions
	// Write interactions for Erez paragraph
	//	return 0; 
}


// Perform the k-n algorithm 
// 
// Input: 
// *stat - a pointer to class cStatisticStructure. The following fields are used as input: 
//	unsigned int m_kCount; // number of individuals in the k group. a prefix set of the m_count.
//	unsigned int m_kControlCount; // number of individuals in the control group  
//	unsigned int * m_kPositionList ; // array of indices for the group of k individuals out of the array. Look in m_predictiveArr
//	unsigned int * m_kControlPositionList ; // array of indices for the control group of k_ctrl individuals out of the array m_predictiveArr
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Output: 
// *stat - a pointer to class cStatisticStructure. The following fields are changed: 
//	//NEW .m_controlPredictErrArr - Control Prediction Error Array.
//	//here we want the list of differences between predicted value and real dependent value from dependant array. 
//	//the size of the array will be m_kControlCount. 
//	//position i in the m_controlPredictErrArr will store the value in  m_predictiveArr[m_kControlPositionList[i]] compute using k-n algorithm minus m_dependentArr
//	short int * m_controlPredictErrArr; // length is m_kControlCount 
//	float m_KNperformanceScore; // performance of the k-n algorithm (?) YES, average of squared error


 
void cStatisticStructure::CalculateKgroupStatisticsNEW(float &kAverage, float *weighted_var_average, 
													   float * editDistanceScores)
{//1310
	float weights_sum=0.0; // sum of predictability weights over all individuals in k group
	//float scoreSum = 
	kAverage = 0.0;
	for(unsigned int i=0; i<m_kCount; i++) // loop on k group to count the predictivlity sum of weights
	{
		float scoreWeight = 1 / (40  + editDistanceScores[i]);
		float combinedWeight = m_predictabilityScores[m_kPositionList[i]] * scoreWeight;
		kAverage += m_dependentArr[m_kPositionList[i]]* combinedWeight;
		weights_sum += combinedWeight;
	}
	kAverage /= weights_sum;

//CALCUALTE PREDICTIVE AVERAGE VALUES of  THE MAIN K GROUP
//	float *weighted_var_average = new float[p]; // weighted average of each variable in control group
 	for(unsigned int j=0; j< m_numOfPredictiveVars; j++) // Compute weighted average for each predictive variable
	{
		weighted_var_average[j] = 0;
		for(unsigned int i=0; i< m_kCount; i++) // loop on k-control group individuals
		{ //here we will have average (weights) of predictive var across all kCount sample.
			float scoreWeight = 1 / (40  + editDistanceScores[i]);
			float combinedWeight = m_predictabilityScores[m_kPositionList[i]] * scoreWeight;
				float xx = (combinedWeight * m_predictiveArr[m_kPositionList[i]][j]);
			weighted_var_average[j] += xx;		
		}
		weighted_var_average[j] /= weights_sum;  //EREZ copy this same line
	}

}


 



	//sort with method of bubble sort according to what are we predicting as the predictionArr[i] value.
//sort in an accensing order
void 	cStatisticStructure::SortThreeArraysPerPredictionValue( float *predictionArr,   short int * dependentVals,  
																									unsigned int count)
{
	bool flag = true;// set flag to 1 to start first pass
	float temp = 0; //for swap
	for(unsigned int index = 0; (index < count) && flag; index++)
	{
		flag = 0;
        for (unsigned int j=0; j < (count -1); j++)
        {
			if (predictionArr[j+1] < predictionArr[j])      // ascending order simply changes to <
            { 
				temp = predictionArr[j];             // swap elements
                predictionArr[j] = predictionArr[j+1];
                predictionArr[j+1] = temp;

				temp = (float )dependentVals[j];             // swap elements
                dependentVals[j] = dependentVals[j+1];
                dependentVals[j+1] = (short)temp;

				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
}
	//fill flexibleError with nextStep number of errors. 
		//these will be aveagre predictionArr items and dependentVals itmes.
//doing that, you assume for all that group same average prediction and same real future values. 
void 	cStatisticStructure::CalculateGroupPreidctionOld(float * errorArray, float *predictionArr, 
					 short int * dependentVals, unsigned int startIndex, unsigned int count)
{
	float averagePrediction = 0;
	float averageDependent = 0;

	for (unsigned int i = 0 ; i < count ; i++)
	{
		averagePrediction += predictionArr[startIndex + i];
		averageDependent += dependentVals[startIndex + i];
	}
	averagePrediction /= count;
	averageDependent /= count;

	for (unsigned int i = 0 ; i < count ; i++)
	{
		errorArray[startIndex + i] = averagePrediction - averageDependent;
	}
}



//will fill flexibleError with nextStep number of errors. 
		//these will be aveagre predictionArr items and dependentVals itmes.
//doing that, you assume for all that group same average prediction and same real future values. 
void 	cStatisticStructure::CalculateGroupPreidction(float * errorArray, float *predictionArr, 
					  short int * dependentVals, unsigned int startIndex, unsigned int count,cSimilarityFormula &kDistribution)
{
	float averagePrediction = 0;
	float averageDependent = 0;

	for (unsigned int i = 0 ; i < count ; i++)
	{
		averagePrediction += predictionArr[startIndex + i];
		averageDependent += dependentVals[startIndex + i];
	}
	averagePrediction /= count;
	averageDependent /= count;

	for (unsigned int i = 0 ; i < count ; i++)
	{
		errorArray[startIndex + i] = averagePrediction - averageDependent;
	}
}




// An auxillary function: 
// Inverts a symmetric matrix 
// Input: 
// V - a 2d square array representing a matrix in double 
// N - length of matrix 
// 
// Output: 
// V - a 2d square array representing the inverse of the matrix in double
//
bool cStatisticStructure::SymmetricMatrixInvert(double **V, unsigned int predictedVariableNum)
{
//	int N = (int)Math.Sqrt(V.Length); // This assumes that the input is already given in array whose size we know 
	double* t = new double[predictedVariableNum];
	double* Q = new double[predictedVariableNum];
	double* R = new double[predictedVariableNum];
	double AB;
	unsigned int K, L, M;

	// Invert a symetric matrix in V
	for (M = 0; M < predictedVariableNum; M++) R[M] = 1;

	K = 0;
	for (M = 0; M < predictedVariableNum; M++)
	{
		double Big = 0;
		for (L = 0; L < predictedVariableNum; L++)
		{
			AB = ABS(V[L][L]);
			if ((AB > Big) && (R[L] != 0))
			{
				Big = AB;
				K = L;
			}
		}
		if (Big == 0)
		{
			delete []t;
			delete []Q;
			delete []R;
			return false;
		}
		R[K] = 0;
		Q[K] = 1 / V[K][K];
		t[K] = 1;
		V[K][K] = 0;
		if (K != 0)
		{
			for (L = 0; L < K; L++)
			{
				t[L] = V[L][K];
				if (R[L] == 0) Q[L] = V[L][K] * Q[K];
				else Q[L] = -V[L][K] * Q[K];

				V[L][K] = 0;
			}
		}
		if ((K + 1) < predictedVariableNum)
		{
			for (L = K + 1; L < predictedVariableNum; L++)
			{
				if (R[L] != 0) t[L] = V[K][L];
				else t[L] = -V[K][L];

				Q[L] = -V[K][L] * Q[K];
				V[K][L] = 0;
			}
		}
		for (L = 0; L < predictedVariableNum; L++)
			for (K = L; K < predictedVariableNum; K++)
				V[L][K] = V[L][K] + t[L] * Q[K];
	}

	M = predictedVariableNum;
	L = predictedVariableNum - 1;
	for (K = 1; K < predictedVariableNum; K++)
	{
		M = M - 1;
		L = L - 1;
		for (unsigned int J = 0; J <= L; J++)
			V[M][J] = V[J][M];
	}
	delete []t;
	delete []Q;
	delete []R;
	return true;
}
// simple_linear_regression(float *Y, short int **X, unsigned int pIndex, unsigned int N, 
//							
//float *r_square, float *pval)


// Perform simple linear regression with one input variable 
float cStatisticStructure::simple_linear_regression(float *Y, short int **X, unsigned int pIndex, unsigned int N, 
																		float *r_square, float *pval)
{
	float beta=0; // this is the linear coefficient (does not include the constant term)
	float denominator=0;
	unsigned int i;

	for(i=0; i<N; i++)
	{
		beta += X[i][pIndex]*Y[i];
		denominator += (float(X[i][pIndex]))* (float(X[i][pIndex]));
	}
	beta = beta / denominator; // normalize 
	*r_square = 0; //EREZ do we want to add that? or is the suare for all varibles together? added initilization. or do we want some contnuatin from other cases?
	for(i=0; i<N; i++) // compute r-square
		*r_square += (Y[i] - beta* X[i][pIndex])*(Y[i] - beta* X[i][pIndex]);
	float sigma_square = *r_square / (N-1); 
	float z_score =  beta / sqrt( sigma_square / denominator ); // Compute t-statistic for each coefficient
//	*pval = 2 * MAX(t_Distribution(z_score, N-1), 1-t_Distribution(z_score, N-1));  // compute p-value. Use two-sided t-test 
	*pval = 1.0;//EREZ
	return beta;
}

/*
	here we will add a float as a return value, and return the value of cigma of
	j = 0 to variale count, Abs(matchingSet[j] - coreSet[j]) / sd[j]. sd is the standard deviation
	per variable taken from the for the entire universal array of sd.
	now we will have to count the entire loop for both cases of true or false.
	loop of flags, by 
	*/
	
/*
bool cStatisticStructure::IsMatchingAllFlagsNew(float & flaggedDistance, float & nonFlaggedDistance, short int * matchingSet,
												short int * coreSet, cSimilarityFormula & newFormula)
{
	//PPPPPP  add so that if it is multi flags we open a new loop, we execute the logic of abs(abs(pos1-..) - abs(pos2-po..))
	flaggedDistance =0;
	//nonFlaggedDistance = 0 ;
	bool flag = true;
//	float tempDisVal = 0 ;
	unsigned int matchedFlagsCount = 0 ;
	for (unsigned int j = 0 ; j < newFormula.GetCount() ; j++)
	{//PRIORITY0  change value for significant similarity score siff, so that if we do values in SD it will match
		//if the flag mentioned a key variable and it is diffentn more than a given value we don't want this matchingSet
		if((newFormula.GetFlag(j)) != 0)
		{ 
			float temp = (Abs(matchingSet[j] - coreSet[j]));
			//flaggedDistance += temp;
			flaggedDistance = Max(flaggedDistance, temp);
			matchedFlagsCount ++;
			if (temp > VALUE_FOR_SIGNIFICANT_SIMILARITY_SCORE_SIFF)
			{
				flag =  false;
			}
		}
	//	else
	//	{
	//		float temp = (Abs(matchingSet[j] - coreSet[j]));
	//		nonFlaggedDistance += temp;
	//	}
	}
//	if(matchedFlagsCount > 1)
//	{
//		flaggedDistance *= flaggedDistance ; 
//	}
	return flag;
}
*/

 
void cStatisticStructure::CalculatedRegressionConstantsNEW(float &constantRecommendFlagged, 
			float & constantRecommendOthers, float &constantRecomendControl,
			bool * partialFlagged,bool * others, unsigned int kConstant, bool isFlagged, bool isUseSameWeightsInKcount)//bool *flagged)
{
	constantRecommendFlagged=0;constantRecommendOthers=0;constantRecomendControl=0;
	float weightOfDeltaFlagged = 0 ;float weightOfDeltaOthers = 0 ;
	float weightOfDeltaControl = 0 ;
	unsigned int controlCount = 0;
	for( unsigned int i=0; (i< m_parentThis->m_count );i++) 
//	for( unsigned int i=1; (i< m_parentThis->m_count );i+=2) 
	{
		float predictiveEffect=0;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			predictiveEffect += m_regressionBetaWeightArray[j] * (*m_predictiveArrSamplePtr)[i][j]; 
		}   
		const float tempAdjustedVal = (*m_dependentArrSamplePtr)[i] - predictiveEffect;
	
		
		//ADD A MAX COUNT 
	//	bool isMattched = false;
	//	if (IsMatching AllFlags(  (*m_predictiveArrSamplePtr)[i], m_predictive_set,	childDeltaFlags )) //( flagged[i])
		if(partialFlagged[i])	
		//( isMattched = IsMatc hingAllFlags(  (*m_predictiveArrSamplePtr)[i], m_predictive_set,	childFlags  ))
				//												&&(flaggedIndex ++ < kCount ))//K_COUNT_EVOLUTION. and in GetC0unt
		{
			//tempAdjustedVal *= m_parentThis->m_predictabilityScores[i];//flaggedScores[i];//m_parentThis->m_predictabilityScores[i];
			constantRecommendFlagged += (tempAdjustedVal*m_parentThis->m_predictabilityScores[i]); 
			weightOfDeltaFlagged+= m_parentThis->m_predictabilityScores[i]; //flaggedScores[i];//m_parentThis->m_predictabilityScores[i];
		//	sumOfTotalWeights+=
		}//else if( childFlags.IsSameFlags(parentFlags))||
		else if(others[i])//if ( !isMattched )//EREZ 12/3/11 used to be : else  if(  ( childFlags.IsSameFlages(parentFlags))||			
			//( IsMatc hingAllFlags(  (*m_predictiveArrSamplePtr)[i], m_predictive_set,	parentFlags  )))//if( (weightOfOthers < bigEnoughSampeOthers))
		{
		//	tempAdjustedVal *=m_parentThis->m_predictabilityScores[i]; //othersScores[i];
			constantRecommendOthers += (tempAdjustedVal*m_parentThis->m_predictabilityScores[i]);
			weightOfDeltaOthers+=m_parentThis->m_predictabilityScores[i];//othersScores[i];
		}
		if(i< kConstant)//flagged[i])   here we don't look at the parent, only at the self. check the effect of our K from KN
		{
			float predEffect=0;
			for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
			{
				predEffect += m_regressionBetaWeightArray[j] * m_predictiveArr[i][j]; 
			} 
			float weight = 0;//1.0f;
			if(isFlagged) //from analytic processing
			{
				weight = m_predictabilityScores[i];
			}
			else if (m_predictabilityScores[i] > 0) //that means now we are from constant seek and we are NOT a control item
			{
				if(isUseSameWeightsInKcount)
				{
					weight = 1.0f;
				}
				else
				{
					weight = m_predictabilityScores[i];
				}

			}
			const float tempAdjVal = m_dependentArr[i] - predEffect;
			constantRecomendControl +=tempAdjVal*weight; 
			controlCount++;
			weightOfDeltaControl+=weight; //flaggedScores[i];//m_parentThis->m_predictabilityScores[i];
		}
	//	else
	//	{
	//		sumOfEmptyWeights+=m_parentThis->m_predictabilityScores[i];
	//	}
	}
//	sumOfTotalWeights = weightOfDeltaFlagged + weightOfDeltaOthers;// + sumOfEmptyWeights;
	//ADD CASE OF NOT ENOUGH 
	if(weightOfDeltaFlagged!=0)
	{
		constantRecommendFlagged /= weightOfDeltaFlagged;//-3
	}
	if(weightOfDeltaOthers!=0)
	{
		constantRecommendOthers /= weightOfDeltaOthers;//-5
	}
	if(weightOfDeltaControl > 0)
	{
		constantRecomendControl /= weightOfDeltaControl;//controlCount;// weightOfDeltaControl ;
	}

}

///////////////////////77777
//FUNCTION_CATEGORY_PARENT_BETA 1
void cStatisticStructure::CalculatedRegressionConstantsNEW12345678(float &constantRecomendControl,
									   float &totalControlWeightSelf, 
			 unsigned int kConstant,   int functionCategory )
			 //constantType - if =1 than .... if =2 than 
{
	totalControlWeightSelf = 0 ;
	constantRecomendControl=0;
	float weightOfDeltaControl = 0 ;
	unsigned int controlCount = 0;
	for( unsigned int i=0; (i< kConstant );i++) 
	{
		float predictiveEffect=0;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			if(functionCategory == FUNCTION_CATEGORY_PARENT_BETA )
			{
				predictiveEffect += m_parentThis->m_regressionBetaWeightArray[j] * m_predictiveArr[i][j]; 
			}
			else if (functionCategory == FUNCTION_CATEGORY_SELF_BETA )//need to reach here now
			{
				predictiveEffect += m_regressionBetaWeightArray[j] * m_predictiveArr[i][j];//(*m_predictiveArrSamplePtr)[i][j]; 
			}
		}   
		const float diffVal = m_dependentArr[i] - predictiveEffect;
		float weight = 0;
		if((functionCategory == FUNCTION_CATEGORY_PARENT_BETA ))
		{
			weight = m_predictabilityScores[i];//if betas are form parent, k group should stay stady of self scores
		}
		else if((functionCategory == FUNCTION_CATEGORY_SELF_BETA ))
		{
			weight = m_parentThis->m_predictabilityScores[i];//here we are playing with the k couut/weights 
		}
		constantRecomendControl += diffVal*weight; 
		//controlCount++;
		weightOfDeltaControl+=weight; //flaggedScores[i];//m_parentThis->m_predictabilityScores[i];
	}
	if(weightOfDeltaControl > 0)
	{
		constantRecomendControl /= weightOfDeltaControl;//controlCount;// weightOfDeltaControl ;
	}
}




/*
void cStatisticStructure::AdjustKFirstMembersScoresNEW(unsigned int numToAdjust, float nConstant,
										float exponentialKconst,double kConstant, bool isCreatingKscore)
{
	return;//PPPPPP   8 7 12
//	double kConstant = DEFAULT_K_CONSTANT_EVOLUTION;//DEFAULT_K_CONSTANT_N_SEEK;//0.3;
//	exponentialKconst = 1.3;
	////PRIORITY1
	numToAdjust = Min(numToAdjust , m_count);
	for (unsigned int i = 0 ; i < numToAdjust ; i++)
	{
			//original formula for score, from taget sort score is:
			//tempScore  = 	1/(1+ (scoreArr[i] * constantScoreWeight ));
		float tempScore = m_predictabilityScores[i] ; 
			//if temp score was calculated basced on the above than it will be :
		if (tempScore ==0)
		{
			tempScore = m_predScoresAlt[i];
		}
			
		if(tempScore > 0 )//.4545, .2173. 2.091.  0.2941, .1219 : 2.41
		{
			double originalScore =  1 ;
			double newScore =0;
			if ( isCreatingKscore )
			{
				if( nConstant  > 0)
				{//cStatisticStructure::Calcul atePredScoreFromEditDisScore(float editScore, float knExpConstant,  float knConstant )

					originalScore  = (1 - tempScore) / ( tempScore * nConstant );
				//	originalScore  /= 100 ;
					newScore = CalculatePredSco reFromEditDisScore(originalScore, exponentialKconst, kConstant,0,0);
						// ( ((double)1) / ( 10 + (    pow(  (double)originalScore  , (double)exponentialKconst  )  )));
							//	 1 / ( 1 + (kConstant  *( pow((double)originalScore  ,(double) exponentialKconst  ))));
				//	newScore = 	1/(1+ (originalScore * kConstant ));
				}
			}
			else //movnig backwords from K to N
			{
	//		newScore =    1 / ( 1 + (constant *( pow(originalScore  , exponentialKconst  )))
	//		  newScore * (1 + (constant * pow()))= 1
	//		  newSccore + constant * pow()* newscore = 1;
	//		  pow() = (1 -  newScore) / (newScore*constant)
	//		  originalScore = pow((1 -  newScore) / (newScore*constant), 1/exponentialKconst)
	//		 
				if((exponentialKconst > 0 )&&(nConstant > 0))
				{
//					cStatisticStructure::Calculat ePredScoreFromEditDisScore(float editScore, float knExpConstant,  float knConstant )
					
			
					originalScore = pow((double)((1 -  tempScore) / (tempScore*kConstant )), (double)1/exponentialKconst);
					//originalScore = pow((double)((1 - (10* newScore)) / newScore), (double)(1/exponentialKconst));
					//originalScore *=100;
					newScore = CalculatePred ScoreFromEditDisScore(originalScore, 1.0f, nConstant,0,0);
					//newScore = 	1/(1+ (originalScore * nConstant ));
				}
			}
		//	float newScore = 	1/(1+ (originalScore * kConstant ));
			if (m_predictabilityScores[i]==0)//if yes means that this one is a controlled item and has its representatice in the altenatic earray score
			{
				m_predScoresAlt[i] = (float)newScore; // 7 31 12  BUG fix added this if so the alternatice score will get similar weights as was supposed to get the main one
			}
			else
			{
				m_predictabilityScores[i] = (float)newScore;
			}
		}
	}
}
*/



/////////////////////678
/*

void cStatisticStructure::CalculateNflagged_5_10_12 ( 	float &partialFlaggedSE, float &partialFlaggedVar, 
	float &partialFllagedWegiht,float &otthersSE , float & otthersVar,	float & othersWegiht,	
	cSimilarityFormula &childDeltaFlags,unsigned int maxFlaggedCount)
{
	unsigned int countFlags = childDeltaFlags.CountFlags();
	
	//4 groups bool arrays
	bool * partialFlagged = new bool[m_parentThis->m_count ]; //will be meassured by basic regression constant
	bool * others = new bool[m_parentThis->m_count ];
//	bool * kControlflagged = new bool[m_parentThis->m_count ];//will be meassured by control k/n constant method.
//	bool * controlOthers = new bool[m_parentThis->m_count ];//to compare control group to most similr others, small group

	//4 groups count parameters
	unsigned int partialFlaggedCount = 0;unsigned int othersCount = 0;
	for( unsigned int i=0; (i< m_parentThis->m_count );i++) 
	{
		partialFlagged[i] = false; others[i] = false;  
		if(childDeltaFlags.IsFlagged())//come here
		{
		
			if ( (IsMatchingAllFlags(  (*m_predictiveArrSamplePtr)[i], m_predictive_set,	childDeltaFlags , 40 )))	
			{
				partialFlagged[i] = true;
				partialFlaggedCount++;
				//totalPartialFlagedWeight +=m_parentThis->m_predictabilityScores[i];
			}
			else if( 
				(countFlags==1)
				||
				((countFlags==2)&&(IsMatchingAnyFlag(  (*m_predictiveArrSamplePtr)[i], m_predictive_set,	childDeltaFlags ) )) 
				   )//if (othersCount < testGroupCount)
			{
				others[i]=true;
				othersCount++;
			}
		}
		else 
		{
			if (partialFlaggedCount< maxFlaggedCount)	
			{
				if((!IS_N_SEEK_K_CONTROL_GROUP_ZERO_CLEAN)||(m_parentThis->m_predictabilityScores[i]==0))
				{			
					partialFlagged[i] = true;
					partialFlaggedCount++;
				}
					//totalPartialFlagedWeight +=m_parentThis->m_predictabilityScores[i];
			}
			else //if (othersCount < testGroupCount)
			{
				if((!IS_N_SEEK_K_CONTROL_GROUP_ZERO_CLEAN)||(m_parentThis->m_predictabilityScores[i]==0))
				{	
					others[i]=true;
					othersCount++;
				}
			}
		
		}
		
	}
////////COUNTS AND WEIGHTS//////////////
//we will zero these two  but will define a wegihted variable instead for each , see below:
	partialFlaggedCount = 0; othersCount = 0;
//do do need for pFlagged and others, weighted calculation:
	float pFllaggedWeight =0;float otherrsWeight =0;
//
//////////SE, MEAN, VAR ////////////////// 
	//pFlagged
	float sumOfPflaggedSE = 0 ;	float meanPflagged = 0 ;
	partialFlaggedSE =0;partialFlaggedVar=0;//two outputs
    //others
    float sumOfOthersSE = 0; float meanOthers = 0;
	otthersSE=0;otthersVar=0; //two outputs
    
	for( unsigned int i=0; (i<  m_parentThis->m_count ); i++)//i+=2)//+)// &&XXXXXXXXXXXXXXXXXXXX
			//((weightOfFlagged < bigEnoughSampeFlagged )||(weightOfOthers < bigEnoughSampeOthers)); i++) // loop on individuals and compute the predicted value by the regression 
	{
		float predictionFromBetas = 0;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			predictionFromBetas += m_regressionBetaWeightArray[j] * (*m_predictiveArrSamplePtr)[i][j];//0.5/0.56, 0.7/0.63  0.31/0.15
		}
		float weightedScore = m_parentThis->m_predictabilityScores[i];
		if((weightedScore ==0))//&&(  (i+1) < m_parentThis->m_count  ) )
		{
			weightedScore = m_parentThis->m_predScoresAlt[i];//m_parentThis->m_predictabilityScores[i+1];
		}
	
		if ( partialFlagged[i])
		{
				float prediction = m_regressionBetaZeroConstantTermWeight  + predictionFromBetas;
			//	float reconstructedConstant =	( 	(totalPartialFlagedWeight*constantRecommendPartialFlagged ) - 
			//			( ((*m_dependentArrSamplePtr)[i] - predictionFromBetas)* m_parentThis->m_predictabilityScores[i] )
			//		)  			/ 
			//		(totalPartialFlagedWeight-m_parentThis->m_predictabilityScores[i]);
				const float tempDif = prediction -  (*m_dependentArrSamplePtr)[i]; 
				const float r_square = (tempDif/100.0f)*(tempDif/100.0f);
			
				//if(childDeltaFlags.IsFlagged())
				
				float temp = r_square * weightedScore;//m_parentThis->m_predictabilityScores[i];
				sumOfPflaggedSE += temp;
				pFllaggedWeight+= weightedScore;//m_parentThis->m_predictabilityScores[i];//XXXXXXXXXXXXXXXXXXX
			
				float depVal = (float(m_parentThis->m_dependentArr[i])/100.0f);// 12345 
				meanPflagged += (depVal * weightedScore);//m_parentThis->m_predictabilityScores[i] );
				partialFlaggedVar += (depVal * depVal * weightedScore);// m_parentThis->m_predictabilityScores[i]) ;
		}
		else if(others[i]) //if (  ( childFlags.IsSameFlages(parentFlags))||
			//(IsMatchingAll Flags(  (*m_predictiveArrSamplePtr)[i], m_predictive_set,	parentFlags)))// if (weightOfOthers < bigEnoughSampeOthers)
		{
				float prediction = m_regressionBetaZeroConstantTermWeight + predictionFromBetas;
				const float tempDif = prediction -  (*m_dependentArrSamplePtr)[i]; 
				const float r_square = (tempDif/100.0f)*(tempDif/100.0f);
				float temp = r_square * weightedScore;//m_parentThis->m_predictabilityScores[i];
				
				sumOfOthersSE+= temp;
				otherrsWeight+= weightedScore;//m_parentThis->m_predictabilityScores[i];
			//	sumOfCoreOthersSE +=coreRsquare;
				float depVal = (float(m_parentThis->m_dependentArr[i])/100.0f);//12345
				meanOthers += (depVal * weightedScore);// m_parentThis->m_predictabilityScores[i]);
				otthersVar += (depVal * depVal * weightedScore);// m_parentThis->m_predictabilityScores[i]);
		}
	} 
	if(pFllaggedWeight>0)
	{		meanPflagged /= pFllaggedWeight;
		partialFlaggedVar /= pFllaggedWeight;
		partialFlaggedVar -= (meanPflagged * meanPflagged) ;//0.73
		partialFlaggedSE   =sumOfPflaggedSE/pFllaggedWeight;
	}
//	meanOthersDependent = varOthersDependent = 0 ;
	if(otherrsWeight>0)
	{
		meanOthers /= otherrsWeight;
		otthersVar /= otherrsWeight;
		otthersVar -= (meanOthers*meanOthers);//0.59
		otthersSE=sumOfOthersSE/otherrsWeight;
	}
	partialFllagedWegiht = pFllaggedWeight ; //setting output
	othersWegiht = otherrsWeight;//setting outputs


	delete [] partialFlagged;delete [] others ;
}
*/

//////////////////////678end


//////////////////////////////////57575757575

///////////////////////////////////051112

//from target sort it was:
	//predictiblityScore  = 	1/(1+ (editScore * constant )) 
	//to go back from predictiblityScore :
	//predictiblityScore * (1+ (editScore * constant )) = 1;
	//predictiblityScore * 1 + predictiblityScore * (editScore * constant ) = 1
	//predictiblityScore + predictiblityScore * editScore * constant = 1 ;
//predictiblityScore * editScore * constantScoreWeight  = 1 - predictiblityScore
	//editScore =( 1 - predictiblityScore ) / (predictiblityScore * constant )
	
double 	cStatisticStructure::CalculateEditDistanceScoreFromPredictabilityScore(double predictiblityScore,  double constant )
{
	double temp = ( 1 - predictiblityScore ) / (predictiblityScore * constant );
	return temp;
}

/*
Count parent strex
Count child st
Each is Sim of deviation from avg, avg is calculated per coll
Dif of pardent to child, per
Dif is spread to all members and all child zmbers wil carry the burden to match 
dif to be zero. The match update will be by relation so if total dif is xxx and in 
noth pos and negative tofether, the weight that is Used a zzz a bassis to spread
the matching nurden is nu substraction of an item from avg (total weight devide by count) .
So an item that got one per more than avg will take double more change than an item.  

*/



///////////////////new strech function////////////////////3 8 13 

 
/*
lets assume 
constant 1.
collectino ed : 10 20 30
parent pred score : 1/10, 1/20/ 1/30 = 0.1, 0.05, 0.033   (sum 0.1833)
parent pa :  0.1/0.1833, 0.05/0.1833, 0.033/0.1833  = 0.5455, 0.2772, 0.181

Abs(0.5455-0.333) + Abs (0.2772-0.333)+Abs(0.181-0.333)= 0.2125+ 0.0558+ 0.152= 0.042


constant 0.5
collectino ed : 10 20 30
parent pred score : 1/(10*0.5), 1/(20*0.5) , 1/(30*0.5 ) = 0.2, 0.1, 0.066   (sum 0.3666)
parent pa :  same .... = 0.5455, 0.2772, 0.181

Abs(0.5455-0.333) + Abs (0.2772-0.333)+Abs(0.181-0.333)= 0.2125+ 0.0558+ 0.152= 0.042


*/

double  cStatisticStructure::CalculatedStrechnessChildOverParent(cStatisticStructure* parentStat,
																 cStatisticStructure* childStat)
{
	//calcualte the sum of weightws of all members of parent collection.
	double sumOfWeightsParent = 0 ;
	//also calcualte the coll count.
	unsigned int colCount =0;
	for(unsigned int i = 0 ; i < parentStat->m_count ; i++)
	{
		if(parentStat->m_predictabilityScores[i] > 0)
		{
			sumOfWeightsParent += parentStat->m_predictabilityScores[i] ;
			colCount ++;
		}
	}
	//calcualte sum of weights child collection
	double sumOfWeightsChild = 0 ;
	for(unsigned int i = 0 ; i < parentStat->m_count ; i++)
	{
		if(parentStat->m_predictabilityScores[i] > 0)
		{
			sumOfWeightsChild += childStat->m_predictabilityScores[i] ;
		}
	}

	double avgPercOneItem = ((double)1 ) / ((double)colCount);

	double sumOfPosstreChildOverParent = 0 ;
	double sumOfNegStreChildOverParent  =0;
	for(unsigned int i = 0 ; i < parentStat->m_count ; i++)
	{
		if(parentStat->m_predictabilityScores[i] > 0)
		{
			double itemPercPArent = parentStat->m_predictabilityScores[i] / sumOfWeightsParent;
			//in case the parent item is a positive streched item
			if(itemPercPArent > avgPercOneItem) 
			{
				double itemPercChild = childStat->m_predictabilityScores[i] / sumOfWeightsChild;
				double posStrechChildOverPArent = itemPercChild - itemPercPArent;
				if(posStrechChildOverPArent > 0 )
				{
					int dddd=0;
				}
				else
				{
					int dddd=0;
				}
				sumOfPosstreChildOverParent += posStrechChildOverPArent ;
			}
			else
			{
				double itemPercChild = childStat->m_predictabilityScores[i] / sumOfWeightsChild;
				double negStrechChildOverPArent = itemPercChild - itemPercPArent;
				if(negStrechChildOverPArent > 0 )
				{
					int dddd=0;
				}
				else
				{
					int dddd=0;
				}
				sumOfNegStreChildOverParent += negStrechChildOverPArent ;
			}
		}
	}
	return sumOfPosstreChildOverParent;
}

/*

double  cStatisticStructure::CalculatedStrechnessChildOverParent2(cStatisticStructure* parentStat,
																 cStatisticStructure* childStat)
{
	//calcualte the sum of weightws of all members of parent collection.
	double sumOfWeightsParent = 0 ;
	//also calcualte the coll count.
	unsigned int colCount =0;
	for(unsigned int i = 0 ; i < parentStat->m_count ; i++)
	{
		if(parentStat->m_predictabilityScores[i] > 0)
		{
			sumOfWeightsParent += parentStat->m_predictabilityScores[i] ;
			colCount ++;
		}
	}
	//calcualte sum of weights child collection
	double sumOfWeightsChild = 0 ;
	for(unsigned int i = 0 ; i < parentStat->m_count ; i++)
	{
		if(parentStat->m_predictabilityScores[i] > 0)
		{
			sumOfWeightsChild += childStat->m_predictabilityScores[i] ;
		}
	}

	double sumOfPosstreChildOverParent = 0 ;
	double sumOfNegStreChildOverParent  =0;
	for(unsigned int i = 0 ; i < parentStat->m_count ; i++)
	{
		if(parentStat->m_predictabilityScores[i] > 0)
		{
			double itemPercPArent = parentStat->m_predictabilityScores[i] / sumOfWeightsParent;
			//in case the parent item is a positive streched item
			if(itemPercPArent > avgPercOneItem) 
			{
				double itemPercChild = childStat->m_predictabilityScores[i] / sumOfWeightsChild;
				double posStrechChildOverPArent = itemPercChild - itemPercPArent;
				if(posStrechChildOverPArent > 0 )
				{
					int dddd=0;
				}
				else
				{
					int dddd=0;
				}
				sumOfPosstreChildOverParent += posStrechChildOverPArent ;
			}
			else
			{
				double itemPercChild = childStat->m_predictabilityScores[i] / sumOfWeightsChild;
				double negStrechChildOverPArent = itemPercChild - itemPercPArent;
				if(negStrechChildOverPArent > 0 )
				{
					int dddd=0;
				}
				else
				{
					int dddd=0;
				}
				sumOfNegStreChildOverParent += negStrechChildOverPArent ;
			}
		}
	}
	return sumOfPosstreChildOverParent;
}
*/


void   cStatisticStructure::CalculateMeanAndSumWeightsWithExp(double &mean, double &sumWeights, double &var, double exp)
{
	mean=0;
	sumWeights=0;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double weight =  pow(double(m_predictabilityScores[i]),exp);
		mean += weight* ((double) m_dependentArr[i]);
		sumWeights += weight;
	}
	mean /= sumWeights ;
	var=0;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double weight =  pow(double(m_predictabilityScores[i]),exp);
		double dif =  ((double) m_dependentArr[i]) - mean;
		var += (dif*dif*weight);
	}
	var /= sumWeights ;

}



void   cStatisticStructure::CalculateMeanAndSumWeights(double &mean, double &sumWeights, double &var)
{
	mean=0;
	sumWeights=0;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		mean += m_predictabilityScores[i]* ((double) m_dependentArr[i]);
		sumWeights += m_predictabilityScores[i];
	}
	mean /= sumWeights ;
	var=0;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double dif =  ((double) m_dependentArr[i]) - mean;
		var += (dif*dif*m_predictabilityScores[i]);
	}
	var /= sumWeights ;

}


double cStatisticStructure::CacuaultePredictionValueWithIgnore(  double meanGroup, double sumWeightsGroup  , double itemValueToIgnore,  
			                            float weightOfItemToIgnore)
{

	/*
	m = (mo*wo + vi*wi)/ wg

	m= (mo*(wg-wi)  + vi*wi) / wg
	
	m*wg = (mo*(wg-wi)  + vi*wi)
	m*wg - vi*wi = mo(wg-wi)
	(m*wg - vi*wi ) / (wg-wi) = mo
	
	*/
	//mo is mean of others but the input item
	double mo = ((meanGroup*sumWeightsGroup)  - (itemValueToIgnore*weightOfItemToIgnore )) / (sumWeightsGroup-weightOfItemToIgnore) ;
	return mo;
}

//returns child ex var improvemet caclualteint sqr erro using parentn vs child mean. 
void cStatisticStructure::FindThoseWhoGainWeight(bool* isGainArr)
{
	double basicPercentage = ((double)1) / m_count;
	double sumWeigihts =0;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		sumWeigihts += m_predictabilityScores[i];
	}
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double perc = m_predictabilityScores[i] / sumWeigihts ;
		if( perc >= basicPercentage )
		{
			isGainArr[i] = true;
		}
		else
		{
			if(IS_SUB_GROUP_TESTT)
			{
				isGainArr[i]=false;//
			}
			else
			{
				isGainArr[i]=true;//2 4 14 test false;
			}
		}
	}


}


void cStatisticStructure::CopyDependentArray(cStatisticStructure* parentStat)
{
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		m_dependentArr[i] = parentStat->m_dependentArr[i];
	}

}



/*
//2 24 14 get  mean and var  as input 
//double meanUniverse , double varianceUniverse, threshodForCenter, expVal // SDs_THRESHOLD_FOR_EXTREMET
/*
	double sd = pow(varianceUniverse, 0.5);
	double highCenterVal= meanUniverse + (threshodForCenter*sd);
	double lowCenterVal = meanUniverse - (threshodForCenter*sd);
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double val = (double) m_dependentArr[i];
		if(val > highCenterVal)
		{
			double gap = val - highCenterVal;
			gap = pow(gap , expVal);//0.75);
			val = highCenterVal + gap;
		}
		if(val < lowCenterVal)
		{
			double gap = Abs(val - lowCenterVal);
			gap = pow(gap ,expVal);
			val = lowCenterVal - gap;
		}


		//val = Min( maxVal, val);
		//val = Max(minVal, val);
		m_dependentArr[i] = short int(val);
	}



*/



/*
void cStatisticStructure::CutExtremtePre dValuesToThreshold(
	 double meanUniverse , double varianceUniverse, double threshodForCenter, double expVal )
{
	double sdUniv = pow(varianceUniverse, 0.5);
	

	double mean= 0;//meanUniverse ;
	double sumWeights= 0 ;
	double var = 0;//varianceUniverse;
	
	CalculateMeanAndSumWeights(mean, sumWeights, var);
	double sd = pow(var, 0.5);
	//double maxVal= mean + (SDs_THRESHOLD_FOR_EXTREMET*sd2);
	//double minVal = mean - (SDs_THRESHOLD_FOR_EXTREMET*sd2);
	
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double val = (double) m_dependentArr[i];
		double absDisFromMean = Abs((val - mean));// / sd);
		double adjAbsDisFromMean = pow( absDisFromMean , EXP_ FOR_CUT_EXTREME);
		if(val > mean)
		{
			val = mean + adjAbsDisFromMean ;
		}
		else
		{
			val = mean - adjAbsDisFromMean ;
		}
		//val = Min( maxVal, val);
		//val = Max(minVal, val);
		m_dependentArr[i] = short int(val);
	}

	

}
*/


#define AVERAGE_PERC_CUT_FROM_EXP 0.04


/*	


void cStatisticStructure::CutExtremteP redValuesToThreshold(
	 double meanUniverse , double varianceUniverse, double threshodForCenter, double expVal )
{
	double sd = pow(varianceUniverse, 0.5);
	double highCenterVal= meanUniverse + (threshodForCenter*sd);
	double lowCenterVal = meanUniverse - (threshodForCenter*sd);
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		double val = (double) m_dependentArr[i];
		if(val > highCenterVal)
		{
			double gap = val - highCenterVal;
			gap = pow(gap , expVal);//0.75);
			val = highCenterVal + gap;
		}
		if(val < lowCenterVal)
		{
			double gap = Abs(val - lowCenterVal);
			gap = pow(gap ,expVal);
			val = lowCenterVal - gap;
		}
		m_dependentArr[i] = short int(val);
	}
}
*/

/*
double cStatisticStructure::CalculateErrorComareTpParent(double meanParent, double sumWeightParent, 
						double varParent,                  cStatisticStructure* parentStat )
{
	double sumWeightsParentTest = 0;
	double sumweightsChildTest = 0 ;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		sumWeightsParentTest += parentStat->m_predictabilityScores[i];
		sumweightsChildTest += m_predictabilityScores[i];
	}



	double meanChildCohort = 0 ;
	double sumWeightsChildCohort= 0 ;
	double varChildCohort = 0;
	
	bool* isGainArr = new bool [m_count];
	FindThoseWhoGainWeight(isGainArr);

	CalculateMeanAndSumWeights(meanChildCohort, sumWeightsChildCohort, varChildCohort);


	double meanChildTest = 0 ;
	double sumWeightsChildTest= 0 ;
	double varChildTest = 0;


	double sqrErrUsingParent = 0 ;
	double sqrErrPrnt = 0 ;
	double  sumWeightsPArt = 0 ;
	unsigned int testCount = 0 ;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		if(isGainArr[i])
		{
			double predValUsingParent = CacuaultePredictionValueWithIgnore(  meanParent, sumWeightParent  ,  ((double) m_dependentArr[i]),  
											parentStat->m_predictabilityScores[i]   );
			double dif = predValUsingParent - ((double) m_dependentArr[i]);
			double adjustedPredScore =0;
			//delete  two above line of : adjustedPredScore = pow(adjustedPredScore, EXPO_VALUE _TO_DIFFERENTIATE_TEST_GROUP);
			{	
				//add the following:
				//calc the ratio between how much more or less is the child percentage related to parent of same item:
				double percWeihtChild = ((double) m_predictabilityScores[i]) / sumweightsChildTest;
				double percWeihtParent = ((double) parentStat->m_predictabilityScores[i]) / sumWeightsParentTest;
				double ratio = percWeihtChild / percWeihtParent;
				if(ratio > 2.7)
					int ddddd=0;
				if(ratio < 0.4 )
					int ggggg=0;
				//this ratio can be 1.xxx or 0.9xxx or 0.8 ... means can be more or less than 1. mroe than 1 means this item was
				//upgradeded due to vector weight and similarity to basic.
				//1.1 will be more likre 1.2 and 0.9 to 0.8 ..
				double adjustedRatio = pow(ratio , (double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
				double adjustedPercWeightChild = adjustedRatio * percWeihtParent;
				
				if(cConfiguration::GetInstance()->GetIsExponUpgradeForTestGroupSimilar())
				{
					adjustedPredScore = adjustedPercWeightChild * sumweightsChildTest;
				}
				//ALTERNTIVE balacned
				else
				{
					adjustedPredScore = pow((double) m_predictabilityScores[i], (double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
				}
				///		do the same in the below function using parent predcition
				//double difInPerc = percWeihtChild - percWeihtParent;
				//double adjustedDiffInPerc = difInPerc * INC_SETRENTGH_OF_TEST_GROUP
			}

			sqrErrUsingParent += (dif*dif*adjustedPredScore );  
			
			sqrErrPrnt += (dif*dif*(parentStat->m_predictabilityScores[i] ) );  
			sumWeightsPArt += (parentStat->m_predictabilityScores[i] ) ;

			if(testCount==5)
				int fff=0;

			meanChildTest += (((double) m_dependentArr[i])*  adjustedPredScore  );
			sumWeightsChildTest += adjustedPredScore  ;
			testCount++;
		}
	}
	if(sumWeightsChildTest > 0 )
	{
		sqrErrUsingParent /= sumWeightsChildTest;
		meanChildTest /= sumWeightsChildTest;
	}
	if(sumWeightsPArt > 0 )
	{
		sqrErrPrnt /= sumWeightsPArt;
	}

	double sqrErrUsingChild = 0 ;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		if(isGainArr[i])
		{
			double predValUsingChild = CacuaultePredictionValueWithIgnore( 
				meanChildCohort, sumWeightsChildCohort ,  ((double) m_dependentArr[i]),  
											m_predictabilityScores[i]   );

			double dif = predValUsingChild -  ((double) m_dependentArr[i]);
			
			double adjustedPredScore =0;
			
								
				//delete  two above line of : adjustedPredScore = pow(adjustedPredScore, EXPO_VALUE_ TO_DIFFERENTIATE_TEST_GROUP);
			{	
				//add the following:
				//calc the ratio between how much more or less is the child percentage related to parent of same item:
				double percWeihtChild = ((double) m_predictabilityScores[i]) / sumweightsChildTest;
				double percWeihtParent = ((double) parentStat->m_predictabilityScores[i]) / sumWeightsParentTest;
				double ratio = percWeihtChild / percWeihtParent;
				if(ratio > 2.7)
					int ddddd=0;
				if(ratio < 0.4 )
					int ggggg=0;
				//this ratio can be 1.xxx or 0.9xxx or 0.8 ... means can be more or less than 1. mroe than 1 means this item was
				//upgradeded due to vector weight and similarity to basic.
				//1.1 will be more likre 1.2 and 0.9 to 0.8 ..
				double adjustedRatio = pow(ratio , (double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
				double adjustedPercWeightChild = adjustedRatio * percWeihtParent;
				
				if(cConfiguration::GetInstance()->GetIsExponUpgradeForTestGroupSimilar())
				{
					adjustedPredScore = adjustedPercWeightChild * sumweightsChildTest;
				}
				//ALTERNTIVE balacned
				else
				{
					adjustedPredScore = pow((double) m_predictabilityScores[i], (double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
				}
				///		do the same in the below function using parent predcition
				//double difInPerc = percWeihtChild - percWeihtParent;
				//double adjustedDiffInPerc = difInPerc * INC_SETRENTGH_OF_TEST_GROUP
			}

			
					
		//	double adjustedPredScore = (double) m_predictabilityScores[i];
		//	adjustedPredScore = pow(adjustedPredScore, EXPO_VALUE_TO_DIFFERENTIATE_TEST_GROUP);

			sqrErrUsingChild += (dif*dif*adjustedPredScore );  

			double shifotFromTestMean = ((double) m_dependentArr[i]) - meanChildTest;
			varChildTest += (shifotFromTestMean*shifotFromTestMean*adjustedPredScore );


		}
	}
	if(sumWeightsChildTest > 0 )
	{
		sqrErrUsingChild /= sumWeightsChildTest;
		varChildTest /= sumWeightsChildTest;
	}

	double improInErr = sqrErrUsingParent - sqrErrUsingChild;




	double imprInExVar = improInErr ;/// 
	if(cConfiguration::GetInstance()->GetIsDivideByVarEvolution() && (varChildTest >0))
	{
		imprInExVar /= 	varChildTest;
	}

	if(IS_CENTER_EVOLUTION)
	{
		//imprInExVar = 
		double exVarPrt = 	(varParent- sqrErrPrnt) / varParent;
		double exVarChd = 	(varChildTest - sqrErrUsingChild) / varChildTest ;
		imprInExVar = exVarChd - exVarPrt;
	}
	if(IS_TWO_DIOMENSION_EVOLUTION )
	{
		double dimVar =  (varParent -varChildTest) / varParent ;
		double temp = Max(imprInExVar, 0.0) * Max(dimVar, 0.0);
		imprInExVar = temp;

	//	double exVarUsingPAr = (varChildTest - sqrErrUsingParent ) / varChildTest ;
	//	double exVarUsingChd = (varChildTest - sqrErrUsingChild) / varChildTest ;
	//	imprInExVar = exVarUsingChd -exVarUsingPAr ;
	//	int fff=0;
	//	double childErr = (varChildTest - sqrErrUsingChild) / varChildTest ;

	//	double dimCenter = (varChildTest - sqrErrUsingChild) / varChildTest ;
	//	double dimErr = (sqrErrUsingParent - sqrErrUsingChild) / sqrErrUsingParent ;
	//	double dimVar =  (varParent  - varChildTest) / varParent  ;
	//	imprInExVar =0;// Max(dimErr,0.0) * Max( dimVar ,0.0);
			//(dimErr* PERCENTAGE_ERR_DIM_EVO ) + 
						//	(dimVar * (1.0 - PERCENTAGE_ERR_DIM_EVO ));
	}
	
	
	
	
	
	if(testCount < 10)
	{
		imprInExVar = 0 ;
	}

	delete []isGainArr;
	return imprInExVar;


}

*/

//CalculateErrorPerInputCntrGrp_2_28_14 . 2 28 14 add .h prototue to this fucntion. 

double cStatisticStructure::CalculateErrorPerInputCntrGrp_2_28_14( cStatisticStructure* ctrGrpStat, double exp)
{
	double meanChildCohort = 0 ;
	double sumWeightsChildCohort= 0 ;
	{
		double varChildCohort = 0;
		CalculateMeanAndSumWeightsWithExp(meanChildCohort, sumWeightsChildCohort, varChildCohort,exp);
	}
	double sqrErrUsingChild = 0 ;
	double sumWeightsCtr = 0;
	double meanCtr = 0 ;	
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
			double predValUsingChild = CacuaultePredictionValueWithIgnore( 
				meanChildCohort, sumWeightsChildCohort ,  ((double) m_dependentArr[i]),  
										pow(double(m_predictabilityScores[i]) , exp )  );
			double dif = predValUsingChild -  ((double) m_dependentArr[i]);
			double adjustedPredScore = //(double) ctrGrpStat->m_predictabilityScores[i];
				pow((double) ctrGrpStat->m_predictabilityScores[i], exp);
					//		(double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
			sumWeightsCtr += adjustedPredScore ;
			sqrErrUsingChild += (dif*dif*adjustedPredScore );  
			meanCtr += adjustedPredScore *((double) m_dependentArr[i]);
		//	double shifotFromTestMean = ((double) m_dependentArr[i]) - meanCtr;
		//	varCtr += (shifotFromTestMean*shifotFromTestMean*adjustedPredScore );


		
	}
	if(sumWeightsCtr > 0 )
	{
		sqrErrUsingChild /= sumWeightsCtr;
		meanCtr /= sumWeightsCtr;
	//	varCtr /= sumWeightsCtr;
	}

	double varCtr = 0 ;	
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
		
			double adjustedPredScore = //(double) ctrGrpStat->m_predictabilityScores[i];
				pow((double) ctrGrpStat->m_predictabilityScores[i], exp);
					//		(double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
			double shifotFromTestMean = ((double) m_dependentArr[i]) - meanCtr;
			varCtr += (shifotFromTestMean*shifotFromTestMean*adjustedPredScore );
		
	}
	if(sumWeightsCtr > 0 )
	{
		varCtr /= sumWeightsCtr;
	}

	double exVar = (varCtr - sqrErrUsingChild) / varCtr;
	return exVar;


	return sqrErrUsingChild;

//	double improInErr = sqrErrUsingParent - sqrErrUsingChild;
	
//	double imprInExVar = improInErr ;/// 
//	if(cConfiguration::GetInstance()->GetIsDivideByVarEvolution() && (varCtr >0))
//	{
//		imprInExVar /= 	varCtr;
//	}

//	return imprInExVar;
	
}

/*

double cStatisticStructure::CalculateErrorComareTpParent_2_27_14(double meanParent, double sumWeightParent, 
						double varParent,     cStatisticStructure* parentStat , 
						cStatisticStructure* ctrGrpStat, double expp)
{


	
//	double exp =  (double)(cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());


	double meanCtr = 0 ;
	double sqrErrUsingParent = 0 ;
	double sumWeightsCtr = 0;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
			double predValUsingParent = CacuaultePredictionValueWithIgnore(  meanParent, sumWeightParent  , 
										((double) m_dependentArr[i]),  	parentStat->m_predictabilityScores[i]   );
			double dif = predValUsingParent - ((double) m_dependentArr[i]);
			double adjustedPredScore =0;
			adjustedPredScore =// cntGrpStat->m_predictabilityScores[i];
				 pow((double) ctrGrpStat->m_predictabilityScores[i], expp);
				 //(double)cConfiguration::GetInstance()->GetExpoValueToDifferentiateTestGroup());
			sqrErrUsingParent += (dif*dif*adjustedPredScore );  
			sumWeightsCtr += adjustedPredScore ;//ctrGrpStat->m_predictabilityScores[i];

			meanCtr += (((double) m_dependentArr[i])*  adjustedPredScore  );
	}
	if(sumWeightsCtr > 0 )
	{
		sqrErrUsingParent /= sumWeightsCtr;
		meanCtr /= sumWeightsCtr;
	}
	
	double meanChildCohort = 0 ;
	double sumWeightsChildCohort= 0 ;
	{
		
		
		double varChildCohort = 0;
	
//	bool* isGainArr = new bool [m_count];
//	FindThoseWhoGainWeight(isGainArr);

		CalculateMeanAndSumWeights(meanChildCohort, sumWeightsChildCohort, varChildCohort);//,  exp  );
	}
	double varCtr = 0;
	double sqrErrUsingChild = 0 ;
	for(unsigned int i=0 ; i < m_count ; i ++)
	{
			double predValUsingChild = CacuaultePredictionValueWithIgnore( 
				meanChildCohort, sumWeightsChildCohort ,  ((double) m_dependentArr[i]), (double)m_predictabilityScores[i]); 
								//	pow(	(double)m_predictabilityScores[i], exp   ));
			double dif = predValUsingChild -  ((double) m_dependentArr[i]);
			double adjustedPredScore =  pow((double) ctrGrpStat->m_predictabilityScores[i], expp);
		
			sqrErrUsingChild += (dif*dif*adjustedPredScore );  

			double shifotFromTestMean = ((double) m_dependentArr[i]) - meanCtr;
			varCtr += (shifotFromTestMean*shifotFromTestMean*adjustedPredScore );


		
	}
	if(sumWeightsCtr > 0 )
	{
		sqrErrUsingChild /= sumWeightsCtr;
		varCtr /= sumWeightsCtr;
	}

//	double exVarUsingParnt = (varCtr - sqrErrUsingParent) / varCtr;
//	double exVarUsingChild = (varCtr - sqrErrUsingChild) / varCtr;

//	double imprInExVar = exVarUsingChild - exVarUsingParnt;

	double improInErr = sqrErrUsingParent - sqrErrUsingChild;
	
	double imprInExVar = improInErr ;/// 
	if(cConfiguration::GetInstance()->GetIsDivideByVarEvolution() && (varCtr >0))
	{
		imprInExVar /= 	varCtr;
	}
	
	return imprInExVar;
	
}

*/







double  cStatisticStructure::CalculatedStrechness()
{
	//calcualte the sum of weightws of all members of parent collection
	double sumOfWeights = 0 ;
	unsigned int colCount =0;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		if(m_predictabilityScores[i] > 0)
		{
			sumOfWeights += m_predictabilityScores[i] ;
			colCount ++;
		}
	}
	double sumOfWeightsInPerc = 0 ;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		if(m_predictabilityScores[i] > 0)
		{
			double weightInPerc = ((double)(m_predictabilityScores[i]) )/ sumOfWeights ;
			sumOfWeightsInPerc += weightInPerc;
		}
	}
	double avgWeightInPerc = sumOfWeightsInPerc / colCount;
	double sumOfstrechness = 0 ;
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		if(m_predictabilityScores[i] > 0)
		{
			double weightInPerc = ((double)(m_predictabilityScores[i]) )/ sumOfWeights ;
			//sumOfWeightsInPerc += weightInPerc;
			sumOfstrechness += cVarianceCalc::Abs(weightInPerc - avgWeightInPerc);
		}
	}
	double temp = sumOfstrechness / colCount;
	return temp;
	
	//return 1;

}

double 	cStatisticStructure::CalculatePredScoreFromEditDisScore
			(double editScore, double knExpConstant,double knConstant )//, double memanScoreArr, double sdmScoreArr )
{
	//from initielize statistic structure it ws same.
	//from adjust score, there was in two directions, including the exponensiaon.
	//
/*	double tempScoreInSD = (editScore - meanScoreArr) / sdScoreArr ;

	//we turn small ed to positive.
	tempScoreInSD *= (-1);
	//we shift c contatnt to thje right
	tempScoreInSD += 2.0;
	//we set these  negative , (when orignally smaller than -c), to be 0. 
	//we dont want to treat differently 
	tempScoreInSD = Max(tempScoreInSD ,(double) 1);
	tempScoreInSD= pow(tempScoreInSD,  knConstant);
	return tempScoreInSD/(double(10)) ;
*/	
	
	
	
	if(editScore ==0)
		int fff=0;

	//if(editScore < MIN_EDIT_DISTANCE)//12 5 12
//	{
	//	editScore = MIN_EDIT_DISTANCE;
//	}
//	if(editScore < 0.1)
//	{
//		editScore =0.1 ;
//	}
	

	double temp = 0;
	if(knExpConstant == 1.0)
	{
		temp = 1 / ( CONSTANT_ADD_WEIGHT_CALC + (knConstant  *editScore  ));
		//temp = 1 / (knConstant  *editScore  );
	}
	else
	{
		temp = 1 / ( CONSTANT_ADD_WEIGHT_CALC + (knConstant  *( pow(editScore  , knExpConstant  ))));
	}
	return temp;
}
	//sp 0,0	//per1 0, 200    and per2 100, 100. 
//initial perfenct is same, 100 average and  0.0099. if we increase dim 1 in 10%, 60/40, than avrage ed is 
//per1 gets 80 ed and per2 gets same 100. the scores are then 0.012345 , 0.0099 . 0.00244 dif
//if we do dim 2 60/40 than person 1 gets 120 and person 2 100, and the scores are 0.0082 and 0.0099. dif 0.0016

//START NEW CODE 8 15 12


/*

void cStatisticStructure::AlocateMatchingGroups(bool *kControlflagged, unsigned int & controlFlaggedCount, 
												bool * controlOthers, unsigned int &controlOthersCount, 
									unsigned int	count, unsigned int maxFlaggedCount,  float matchDis, cSimilarityFormula& childDeltaFlags)
		
{	
	controlFlaggedCount = 0 ;
	controlOthersCount = 0 ;

	for( unsigned int i=0; (i<count );i++) 
	{
		kControlflagged[i]=false;	controlOthers[i]= false; 
	//	{ //12345 67 
		if(childDeltaFlags.IsFlagged())//childDeltaFlags, m_parentThis->m_predictiveArr[i]
		{
			if	( IsMatchingAllFlags( m_parentThis->m_predictiveArr[i],  m_predictive_set,	childDeltaFlags,matchDis  )) 
			{	//#define IS_ANALYTIC_K_CONTROL _GROUP_ZERO_CLEAN		
				if (
					((!IS_ANALYTIC_K_CONTROL_GROUP_ZERO_CLEAN)||(m_parentThis->m_predictabilityScores[i]==0))
					//[1]=0.056179769
				//	&&
				//	(controlFlaggedCount<kControlCount)
				   )
				{
					kControlflagged[i]=true;
					controlFlaggedCount++;		//shouold not get here yet	

				}
			}
			else
			{ 
				if (
					(   (!IS_ANALYTIC_K_CONTROL_GROUP_ZERO_CLEAN)||(m_parentThis->m_predictabilityScores[i]==0)  )
			//		&&
				//	(controlOthersCount<kControlCount)
				   )
				{
					controlOthers[i]= true;
					controlOthersCount++;
				}
			}
		} 

		else 
		{//PRIORITY1 change also so we have the option of not clean frm n seek
		//	if (m_parentThis->m_predictabilityScores[i]==0)
			if(controlFlaggedCount < maxFlaggedCount)// (m_parentThis->m_predictabilityScores[i]==0) )//&&(controlFlaggedCount< kControlCount))//K_CONTROL_COUNT))
			{	
				if((!IS_N_SEEK_K_CONTROL_GROUP_ZERO_CLEAN)||(m_parentThis->m_predictabilityScores[i]==0))
				{
					kControlflagged[i]=true;
					controlFlaggedCount++;
				}
				else //if(controlOthersCount  < flaggedCount)
				{
					if((!IS_N_SEEK_K_CONTROL_GROUP_ZERO_CLEAN)||(m_parentThis->m_predictabilityScores[i]==0))
					{
						controlOthers[i]= true;
						controlOthersCount++;	//289	
					}
				}
			}
		}

	}
	int sss=0;
}
*/



/*
void cStatisticStructure::CalculateFlagged_SE_AND_VAR__05_11_12 ( 
	
		float &predictionShift, float &sumOfEditDistanceFlaggedToOthers,
		float &controllFlagedSE, float & controlFlaggedVar, float &cFlaggedWeightt,
		float &controlOthersSE, float &controlOthersVar, float & cOthersWeigiht,
		cSimilarityFormula &childDeltaFlags, unsigned int kConstant, 	unsigned int  kControlCount, 
		unsigned int maxFlaggedCount, 
		int functionCategory, float curNconstant, float defaultKconstant)
{
	unsigned int countFlags = childDeltaFlags.CountFlags();
			
	bool * kControlflagged = new bool[m_parentThis->m_count ];//will be meassured by control k/n constant method.
	bool * controlOthers = new bool[m_parentThis->m_count ];//to compare control group to most similr others, small group
	unsigned int controlFlaggedCount=0;
	unsigned int controlOthersCount=0;
	unsigned int count = Min(m_parentThis->m_count, kControlCount);//-1 in case below we use the next predictivlity scor when t his one is 0
	float matchingDis = VALUE_TO_START_EDIT_THRESHOLD;
	float bestMatchDis = matchingDis;
//	float bestGroupingScore = 0 ;
//	bool end = false;
	int bestDisControl = 10000; //big enough
	int bestDisOthers = 10000 ;
	float interCount = 0;
	while (interCount++ < 6)// controlFlaggedCount < 
	
	{
		AlocateMat chingGroups(kControlflagged,controlFlaggedCount, controlOthers, controlOthersCount, 
			count, maxFlaggedCount,matchingDis, childDeltaFlags);
		int disControlScore = Max( ( int)0,( int)(300 - controlFlaggedCount));
		int disOthersScore = Max((  int)0,( int )(300- controlOthersCount));

		if(	((disControlScore < bestDisControl) &&  (disOthersScore <= bestDisOthers)) 	||
			((disControlScore <= bestDisControl) &&  (disOthersScore < bestDisOthers)) 	)
		{
			bestMatchDis = matchingDis;		bestDisControl = disControlScore;		bestDisOthers = disOthersScore;
		}
		matchingDis *= 1.7;
	}
	AlocateMatch ingGroups(kControlflagged,controlFlaggedCount, controlOthers, controlOthersCount, 
				count,maxFlaggedCount, bestMatchDis, childDeltaFlags);

	//float * predictionArr = new float [count];
	unsigned int extremeCount = 0 ;		
	unsigned int extremeCountPos = 0 ;		
	unsigned int extremeCountNeg = 0 ;		
	if(false)
	{
		for( unsigned int i=0; (i<count );i++) 
		{
			float predictiveEff=0;
			for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
			{
				float betaWeight =m_parentThis->m_regressionBetaWeightArray[j];			
				predictiveEff += (betaWeight *  (m_parentThis->m_predictiveArr[i][j]));
			}  
			//float prediction = predictiveEffectKN + kAverage;//
			float prediction = predictiveEff + m_parentThis->m_regressionBetaZeroConstantTermWeight;
		//	predictionArr[i] = prediction;
			float revVal = m_parentThis->m_dependentArr[i] - predictiveEff;
			if ((Abs(revVal)) >MAX_DISTANCE_BETWEEN_REV_VAL_TO_PREDICTION)
			{
				if(kControlflagged[i])
				{
					kControlflagged[i] = false;
					controlFlaggedCount --;
					
				}
				else if(controlOthers[i])
				{
					controlOthers[i] = false;
					controlOthersCount --;
					
				}
				if(revVal>0)
					extremeCountNeg ++;
				else
					extremeCountPos ++;
			}

		}
	}


		
	
	
	////////////////K_N_algo//////////////	
	float kAverage = 0 ;
	float * weightedVarAvg = new float[m_numOfPredictiveVars];
	if((functionCategory==FUNCTION_CATEGORY_PARENT_BETA)||(functionCategory==FUNCTION_CATEGORY_SELF_ALL))
	{
	//	float currentConstant = curNconstant;
	//	float newConstant = defaultKconstant;
	//	AdjustKFirstMe mbersScores(50000, DEFAULT_N_CONSTANT_EVOLUTION, DEFAULT_K_CONSTANT_EVOLUTION);
		//A djustKFirstMembersScores(w50000, curNconstant, defaultKconstant);//DEFAULT_N_CONSTANT_EVOLUTION, DEFAULT_K_CONSTANT_EVOLUTION);
		CalculateKaverageAnd WeightedVarAvg(kAverage, weightedVarAvg, kConstant, NULL);
		
	//	predictionShift = CalculateAndRec omendShiftInPrediction( SHIFT_CHECK_K_COUNT, weightedVarAvg, kAverage );

		//A djustKFirstMembersScores(50000, defaultKconstant, curNconstant); 2.055, 17.437
		
	}
	else if(functionCategory ==FUNCTION_CATEGORY_SELF_BETA)//here we should call from n constant seek, get the 
	{
	//	m_parentThis->A djustKFirstMembersScores(50000,  curNconstant, defaultKconstant);
		m_parentThis->CalculateKa verageAndWeightedVarAvg(kAverage, weightedVarAvg, kConstant, NULL);
	//	m_parentThis->A djustKFirstMembersScores(50000, defaultKconstant,  curNconstant);
	}
	else
	{
		int fffff=0;//we should not get here -2.65, 0.9238
	}

    //controlFlagged
	float sumOfCflagged = 0; float meanCflagged = 0;
	controllFlagedSE=0; controlFlaggedVar=0; //two outputs
    //controlOthers
	float sumOfCothers = 0 ; float meanCothers = 0;
	controlOthersSE=0; controlOthersVar=0; //two outputs
	float weightOfControlFlaggged = 0 ; float weightOfControlOthers = 0 ;
 ///FFFFFFFFFFFFF   
	unsigned int simCount = childDeltaFlags.GetCount();
	float *flaggedSumSimVariablesValArr = new float[simCount];
	float *othersSumSimVariablesValArr = new float[simCount];
	for(unsigned int j=0; j< simCount ; j++)
	{
		flaggedSumSimVariablesValArr[j]=0;
		othersSumSimVariablesValArr[j]=0;
	}


	for( unsigned int i=0; (i<  (count ) ); i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		float predictiveEffectKN=0;
		float predictiveEffectFull=0;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			float betaWeight =0;
			if(functionCategory == FUNCTION_CATEGORY_PARENT_BETA )
			{
				betaWeight=m_parentThis->m_regressionBetaWeightArray[j];
				//predictiveEffect += m_parentThis->m_regressionBetaWeightArray[j] * m_parentThis->m_predictiveArr[i][j]; 
			}
			else if ((functionCategory == FUNCTION_CATEGORY_SELF_BETA )||(functionCategory == FUNCTION_CATEGORY_SELF_ALL))
			{
				betaWeight=m_regressionBetaWeightArray[j];
				//predictiveEffect += m_regressionBetaWeightArray[j] * m_parentThis->m_predictiveArr[i][j];//(*m_predictiveArrSamplePtr)[i][j]; 
			}
			predictiveEffectKN += (betaWeight * ( (m_parentThis->m_predictiveArr[i][j])-(weightedVarAvg[j] )   )    );
			predictiveEffectFull += (betaWeight * (m_parentThis->m_predictiveArr[i][j]));
		}  
		//float prediction = predictiveEffectKN + kAverage;//
		float prediction = predictiveEffectFull + m_regressionBetaZeroConstantTermWeight;
	//***	
		//PPPPPPPPP prediction = predictiveEffectFull + constRecomeFlags;
		//float reversEnjVal = prediction - predictiveEffectFull;
		//now taking this and converting to traditoinal featrue, than adding back the predictiv eeffect full?
		const float tempDif = (prediction - m_parentThis->m_dependentArr[i])/100.0f;// (*m_dependentArrSamplePtr)[i]; 
		const float r_square = (tempDif)*(tempDif);
		float weightOfControlItem = m_parentThis->m_predictabilityScores[i];
		if((weightOfControlItem == 0.0f))// && ((i+1) < count ))
		{
			//weightedScore = m_parentThis->m_predScoresAlt[i];
			weightOfControlItem = m_parentThis->m_predScoresAlt[i];//m_predictabilityScores[i+1];
		}	
		float temp = r_square * weightOfControlItem; //123456 4-8-12
		float depVal = (float(m_parentThis->m_dependentArr[i])/100.0f);// 12345 
		if (( kControlflagged[i] ))//&&(i< (m_parentThis->m_count-1)))//&& (kControlCount < K_CONTROL_COUNT))
		{
			sumOfCflagged += temp;
			weightOfControlFlaggged+=weightOfControlItem;//m_parentThis->m_predictabilityScores[i];//XXXXXXXXXXXXXXXXXXX 
			meanCflagged += (depVal*weightOfControlItem);// *m_parentThis->m_predictabilityScores[i] ); //123456 4-8-12
			controlFlaggedVar += (depVal * depVal*weightOfControlItem);// * m_parentThis->m_predictabilityScores[i]) ; //123456 4-8-12
			UpdateFlaggedVarialbeVals(flaggedSumSimVariablesValArr, childDeltaFlags,
				m_parentThis->m_predictiveArr[i],weightOfControlItem);
		}//FFFFFFFFFFFFFFFFFF
		else if (( controlOthers[i] ))//&&(i< (m_parentThis->m_count-1)))//&& (kControlCount < K_CONTROL_COUNT))
		{
			sumOfCothers += temp;
			weightOfControlOthers+=weightOfControlItem;//m_parentThis->m_predictabilityScores[i];//XXXXXXXXXXXXXXXXXXX 
			meanCothers+= (depVal*weightOfControlItem);// *m_parentThis->m_predictabilityScores[i] ); //123456 4-8-12
			controlOthersVar += (depVal * depVal*weightOfControlItem);	
			UpdateFlaggedVarialbeVals(othersSumSimVariablesValArr, childDeltaFlags,
										m_parentThis->m_predictiveArr[i],weightOfControlItem);
		}
		else
		{
			int GGG=0;
		}
	} 

	if( weightOfControlFlaggged>0)//31.8
	{
	//	kControlSE  /= controlFlaggedCount;// 
		meanCflagged /= weightOfControlFlaggged;//weightOfKcontrol; //123456 4-8-12
		controlFlaggedVar /= weightOfControlFlaggged;//weightOfKcontrol; //123456 4-8-12
		controlFlaggedVar -= (meanCflagged*meanCflagged);
		controllFlagedSE =sumOfCflagged / weightOfControlFlaggged;
		for(unsigned int j=0; j< simCount ; j++)//,,,flaggedSumSimVariablesValArr[j]
		{
			flaggedSumSimVariablesValArr[j]/= weightOfControlFlaggged;
		}//FFFFFFFFFFFFFFFFFFF
	}
	if( weightOfControlOthers>0)
	{
	//	kControlSE  /= controlOthersCount;// 
		meanCothers /= weightOfControlOthers;//weightOfKcontrol; //123456 4-8-12
		controlOthersVar /= weightOfControlOthers;//weightOfKcontrol; //123456 4-8-12
		controlOthersVar-= (meanCothers*meanCothers);
		controlOthersSE	=sumOfCothers / weightOfControlOthers;
		for(unsigned int j=0; j< simCount ; j++)//,,,flaggedSumSimVariablesValArr[j]
		{
			othersSumSimVariablesValArr[j]/= weightOfControlOthers;
		}//FFFFFFFFFFFFFFFFFFFFFFFFFFFF
	}
//
//	float sumOfMeanDistance=0;//FlaggedToOthers = 0 ;
	
	for(unsigned int j=0; j< simCount ; j++)//,,,flaggedSumSimVariablesValArr[j]
	{
		float temp = Abs(flaggedSumSimVariablesValArr[j] - othersSumSimVariablesValArr[j]);
		sumOfEditDistanceFlaggedToOthers += temp;// Abs(flaggedSumSimVariablesValArr[j] - othersSumSimVariablesValArr[j]);
		//sumOfMeanDis +=temp;//106
	}//PPPPP FFFFFFFFFFFFFFFFFFFFFFF
	


	//outputs:
	cFlaggedWeightt = weightOfControlFlaggged ;  
	cOthersWeigiht = weightOfControlOthers; 
	delete [] flaggedSumSimVariablesValArr;
	delete [] othersSumSimVariablesValArr;
	
	delete [] controlOthers ;delete []kControlflagged; 
	delete []weightedVarAvg;
//	delete []predictionArr;
}
*/

/*
void cStatisticStructure::CalculatePopData( double & percContFlaggedWgt, double & percContOthersWgt, unsigned int totalCount)
{
	totalCount = Min(totalCount, m_count);
//	bool *controlflagged = new bool[totalCount];
//	unsigned int controlFlaggedCount=0;
//	bool * controlOthers = new bool[totalCount];
//	unsigned int controlOthersCount=0;

//	AlocateMatchingGrou ps8_15_12(controlflagged , controlFlaggedCount,  controlOthers, controlOthersCount, totalCount);

	double sumOfContFlaggedWgt = 0 ;
	double sumOfContOthersWgt = 0 ;
	for(unsigned int i = 0 ; i < totalCount ; i++)
	{
		if(i< (cConfiguration::GetInstance()->GetPre dictKCountEvolution()))//controlflagged[i])
		{
			double score = m_predictabilityScores[i];
			sumOfContFlaggedWgt += score;
		}
		else //if(controlOthers[i])
		{
			double score = m_predictabilityScores[i];
			sumOfContOthersWgt += score;
			
		}
	}
	percContFlaggedWgt = sumOfContFlaggedWgt  / (sumOfContFlaggedWgt + sumOfContOthersWgt);
	percContOthersWgt = sumOfContOthersWgt  / (sumOfContFlaggedWgt + sumOfContOthersWgt);

//	delete []controlflagged;
//	delete []controlOthers;
}
*/


/*
void cStatisticStructure::AlocateMatchingGroups8_15_12(bool *kControlflagged, unsigned int &controlFlaggedCount, 
				  bool * controlOthers, unsigned int &controlOthersCount,unsigned int count)
{
	controlFlaggedCount = 0 ;	controlOthersCount = 0 ;
	count = Min(count, m_count);
	for( unsigned int i=0; (i<count );i++) 
	{
		kControlflagged[i]=false;	controlOthers[i]= false; 
		cStatisticStructure * stat = m_parentThis;
		if(stat == NULL)
		{
			stat = this;
		}
		if (  (!IS_ANALYTIC_K_CONTROL_GROUP_ZERO_CLEAN) ||  (stat->m_predictabilityScores[i]==0)  )
		{
			//if (controlFlaggedCount < PRED ICT_K_COUNT ) //EREZ 8 16 12
			if (i < (cConfiguration::GetInstance()->GetPredictKCou ntEvolution()))
			{
				kControlflagged[i]=true;
				controlFlaggedCount++;		//shouold not get here yet	
			}
			else
			{ 
				controlOthers[i]= true;
				controlOthersCount++;
			}
		} 
	}
}
*/

float cStatisticStructure::CalculateVar(unsigned int flagPos, float mean)
{
	float sumOfWeights = 0;
	float sumOfSQ = 0 ;
	for( unsigned int i=0; (i<m_count );i++) 
	{
		float weight= m_predictabilityScores[i];
		sumOfWeights += weight;
		float val = m_predictiveArr[i][	flagPos];
		val /= 100.0f;
		val = ((val - mean))*((val-mean));
		sumOfSQ += val;
	}
	sumOfSQ /= sumOfWeights;
	return sumOfSQ;

}

float cStatisticStructure::CalculateMeanVal(unsigned int flagPos)
{
	float sumOfWeights = 0;
	float sumOfWeightedValues=0;
	for( unsigned int i=0; (i<m_count );i++) 
	{
		float weight= m_predictabilityScores[i];
		sumOfWeights += weight;
		float val = m_predictiveArr[i][	flagPos];
		val /= 100.0f;
		sumOfWeightedValues += (val * weight);
	}
	sumOfWeightedValues /= sumOfWeights;
	return sumOfWeightedValues;

}


//////////////////////////////////8 15 12 start


	

/*

void cStatisticStructure::Calculate Flagged_SE_AND_VAR__08_25_12 ( 	float &controllFlagedSE,
						float & controlFlaggedVar, float &cFlaggedWeightt,	float &controlOthersSE, 
								float &controlOthersVar, float & cOthersWeigiht,
					cPopChangeInWeight & popChgObj,	
								double * predictedValArr, double * realValArr)
{
	////////////////K_N_algo//////////////	
	float kAverage = 0 ;
	float * weightedVarAvg = new float[m_numOfPredictiveVars];
	
	CalculateKaverageAndWeight edVarAvg(kAverage, weightedVarAvg, 50000 , &popChgObj);//PREDICT_K_COUNT    );//popChgObj.GetKcount());
	

    //controlFlagged
	float sumOfCflagged = 0; float meanCflagged = 0;
	controllFlagedSE=0; controlFlaggedVar=0; //two outputs
    //controlOthers
	float sumOfCothers = 0 ; float meanCothers = 0;
	controlOthersSE=0; controlOthersVar=0; //two outputs
	float weightOfControlFlaggged = 0 ; float weightOfControlOthers = 0 ;
    
//	unsigned int simCount = childDeltaFlags.GetCount();

	for( unsigned int i=0; (i<  popChgObj.GetCount() ); i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		float predictiveEffectKN=0;
		float predictiveEffectFull=0;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			float 	betaWeight=m_regressionBetaWeightArray[j];
			predictiveEffectKN += (betaWeight * ( (m_parentThis->m_predictiveArr[i][j])-(weightedVarAvg[j] )   )    );
			predictiveEffectFull += (betaWeight * (m_parentThis->m_predictiveArr[i][j]));
		}  
		double prediction = 0;
		if(SIMPLE_PREDICTIO N_EVPLUTION)
		{
			prediction = predictiveEffectFull + m_regressionBetaZeroConstantTermWeight; //EREZ 8 16 12
		}
		else
		{
			prediction = predictiveEffectKN + kAverage;
		}

		
		const double tempDif = (prediction - m_parentThis->m_dependentArr[i])/100.0f;// (*m_dependentArrSamplePtr)[i]; 
		const double r_square = (tempDif)*(tempDif);
		float weightOfControlItem = m_parentThis->m_predictabilityScores[i];
		if((weightOfControlItem == 0.0f))// && ((i+1) < count ))
		{
			//weightedScore = m_parentThis->m_predScoresAlt[i];
			weightOfControlItem = m_parentThis->m_predScoresAlt[i];//m_predictabilityScores[i+1];
		}	
		double temp = r_square * weightOfControlItem; //123456 4-8-12
		double depVal = (float(m_parentThis->m_dependentArr[i])/100.0f);// 12345 
		if (( popChgObj.GetControlFlag(i) ))//&&(i< (m_parentThis->m_count-1)))//&& (kControlCount < K_CONTROL_COUNT))
		{
			sumOfCflagged += temp;
			weightOfControlFlaggged+=weightOfControlItem;//m_parentThis->m_predictabilityScores[i];//XXXXXXXXXXXXXXXXXXX 
			meanCflagged += (depVal*weightOfControlItem);// *m_parentThis->m_predictabilityScores[i] ); //123456 4-8-12
			controlFlaggedVar += (depVal * depVal*weightOfControlItem);// * m_parentThis->m_predictabilityScores[i]) ; //123456 4-8-12
		
			realValArr[i] = ((double)m_parentThis->m_dependentArr[i]) ;
			predictedValArr[i] = prediction;
		}
		else if ( popChgObj.GetControlOthers(i))//&&(i< (m_parentThis->m_count-1)))//&& (kControlCount < K_CONTROL_COUNT))
		{
			sumOfCothers += temp;
			weightOfControlOthers+=weightOfControlItem;//m_parentThis->m_predictabilityScores[i];//XXXXXXXXXXXXXXXXXXX 
			meanCothers+= (depVal*weightOfControlItem);// *m_parentThis->m_predictabilityScores[i] ); //123456 4-8-12
			controlOthersVar += (depVal * depVal*weightOfControlItem);	
			
		}
	
	} 

	if( weightOfControlFlaggged>0)//31.8
	{
	//	kControlSE  /= controlFlaggedCount;// 
		meanCflagged /= weightOfControlFlaggged;//weightOfKcontrol; //123456 4-8-12
		controlFlaggedVar /= weightOfControlFlaggged;//weightOfKcontrol; //123456 4-8-12
		controlFlaggedVar -= (meanCflagged*meanCflagged);
		controllFlagedSE =sumOfCflagged / weightOfControlFlaggged;
	
	}
	if( weightOfControlOthers>0)
	{
	//	kControlSE  /= controlOthersCount;// 
		meanCothers /= weightOfControlOthers;//weightOfKcontrol; //123456 4-8-12
		controlOthersVar /= weightOfControlOthers;//weightOfKcontrol; //123456 4-8-12
		controlOthersVar-= (meanCothers*meanCothers);
		controlOthersSE	=sumOfCothers / weightOfControlOthers;
	
	}
	cFlaggedWeightt = weightOfControlFlaggged ;  
	cOthersWeigiht = weightOfControlOthers; 
	delete []weightedVarAvg;
}
*/


/*
prediction child will replace preidction on genral for thie child case.

the value will be:   prdeiciton poarent plus change.

change will be :  

input: (parent stast)
		parent regression beta array
		parent prdictive array and prdictility scores
calcualte
       1: k averge of child 
	   2: k averge of parent
	   3: var aerge parent array 
	   4: var aveerage childl array

that was on the collectin level.

now for every control item, we want to see how much it benefits from the child k only model.
that is assuming we have an al gotith mof k couond with parent regression.

every time you 








	   for j = 0 to numof vars ; j++
		  varAvgChilf[j]
	   diff between 





*/


//9 27  13 es consider remove this function if no call to it

//9 22  13 : if an item is not in the near part per varIndex variable, it will get its score reduced.

/*
void cStatisticStructure:: AdjustPerEDAllowed(bool**	edB asedAllowedItems, 
		      unsigned int kCount , unsigned int varIndex)
{
	kCount = Min(kCount , m_count);
	unsigned int countActive=0;

	for (unsigned int i = 0 ; i< kCount ; i++)
	{
		if( edBasedAllowedItems[i][varIndex])
		{
			countActive ++;
		}
		else
		{
			m_predictabilityScores[i] /=2;//= 0;
		}
		
	}
	

}
*/


//9 27 13  es check what is this fuction exactly doing and how it needs to be upgraded for the double arrayh

/*

void cStatisticStructure::FillEDbasedAllowedItems( bool**	edBasedAllowedItems, 
												  unsigned int kCount, unsigned int numOfSim)
{
	kCount = Min(kCount , m_count);
	for(unsigned int j = 0 ; j < numOfSim ; j++)
	{
		double avgVarEd = 0;
		double weightSum=0;
		for (unsigned int i = 0 ; i< kCount ; i++)
		{
			double weight = Max( m_predictabilityScores[i], m_predScoresAlt[i]);
			double ed = Abs( m_predictiveArr[i][j] - m_predictive_set[j]);
			if(ed >0)
				int rrr=0;
			if(i==400)
				int sddd=0;
			
			avgVarEd += ed *weight;//m_predictabilityScores[i] * m_predictiveArr[i][varIndex];
			weightSum += weight;
		}
		if(weightSum > 0 )
		{
			avgVarEd /= weightSum ;
		}


		for (unsigned int i = 0 ; i< kCount ; i++)
		{
			double ed = Abs( m_predictiveArr[i][j] - m_predictive_set[j]);
			if(ed <= avgVarEd)
			{
				edBasedAllowedItems[i][j]=true;
			}
			else
			{
				edBasedAllowedItems[i][j]=false;
			}
		}

	
	}


}
*/


void cStatisticStructure::CalculatedMeanSDweighted(double &mean, double &variance,
							 short int* arr, unsigned int count, float* predScores, double lLevel)
{
	double* doubeArr = new double[count];
	for(unsigned int i=0; i< count ; i++)
	{
		doubeArr [i]= (double)arr[i];
	}
	CalculatedMeanSDweighted(mean, variance,doubeArr, count, predScores, lLevel);

	delete []doubeArr;

}


void cStatisticStructure::CalculatedMeanSDweighted(double &mean, double &variance,
							   double* arr, unsigned int count, float* predScores, double lLevel)
{
	mean =0; variance=0;
	double sumWeights = 0 ;
	for(unsigned int i = 0 ; i< count ; i++)
	{
		sumWeights += predScores[i];
		mean += predScores[i]* arr[i];
	}
	mean /= sumWeights ;
	for(unsigned int i = 0 ; i< count ; i++)
	{
		double absGap = cVarianceCalc::Abs(arr[i]-mean);
		double expoVal = lLevel;// cConfiguration::GetInstance()->GetLL evelErrorEvaluation();
		variance += predScores[i]* pow(absGap,expoVal);
	}
	variance /= sumWeights;
	
}



void cStatisticStructure::FillPredictionCalculations(double &exVarMeanCohort,
								double &exVarRegOnlyCohort,double &multipleRegOnlyEffect,
						unsigned int cohortSize,float* cleanWeightedVarAvera, double lLevel)
{


	double meanUnivers = 0 ;
	double varUnivers = 0;
	double meanDepCohort = 0;  //input. see that it is geeting the k averge 
	double varDepCohort =0;//see that it is getting the k var dependent

	CalculatedMeanSDweighted(meanUnivers, varUnivers ,m_dependentArr, m_count, 
												m_predictabilityScores , lLevel);

	CalculatedMeanSDweighted(meanDepCohort, varDepCohort ,m_dependentArr, cohortSize, 
		m_predictabilityScores , lLevel);

	//	double spRegOnlyEffect = 0 ;
	//	double sdDep = 0;
	double sqrErrMeanKNCohort = 0 ; //sqr error of kn as
	double sqrErrorVarianceKNcohort = 0 ;
	//calcualte average error, which is the prediction minus real for each item.
	double* errArr = new double[cohortSize];
	double* regEffect = new double[cohortSize];
	for(unsigned int i=0; i< cohortSize ; i++)
	{
		double prediction = 0;//meanDepCohort;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			double 	betaWeight= (double)m_regressionBetaWeightArray[j];
			double tempPredValueDir = (betaWeight * 
				( (m_predictiveArr[i][j])-(cleanWeightedVarAvera[j] )   )    ); 
			prediction += tempPredValueDir ;
		}
		regEffect[i]= prediction ;
		prediction += meanDepCohort;

		double absErr = cVarianceCalc::Abs((prediction - m_dependentArr[i]));
		double expoVal = lLevel;// cConfiguration::GetInstance()->GetLLevelErro rEvaluation();
		errArr [i]= pow(absErr , expoVal);
			//(prediction - m_dependentArr[i])*(prediction - m_dependentArr[i]);
	}
	CalculatedMeanSDweighted(sqrErrMeanKNCohort , sqrErrorVarianceKNcohort ,
		             errArr, cohortSize, m_predictabilityScores, lLevel);

	double varinceRegOnlyEffect=0;
//	CalculatedMeanSDweig hted(meanRegOnlyEffect , varinceRegOnlyEffect,
//		             regEffect, cohortSize, m_predictabilityScores);

	double* absRegEffect = new double [cohortSize];
	for(unsigned int i=0; i<cohortSize ; i++)
	{
		absRegEffect [i] = cVarianceCalc::Abs(regEffect[i]);
	}

	double meanAbsRegEffect = 0;
	CalculatedMeanSDweighted(meanAbsRegEffect , varinceRegOnlyEffect,
		             absRegEffect, cohortSize, m_predictabilityScores, lLevel);

	double absKavergeEffect = cVarianceCalc::Abs(meanDepCohort -meanUnivers );
	double sqErrMeanCohort = varDepCohort ; //sqr error of mean is like guessnig the average/mean
	                                          //and that is equalt to the varaince of dependent
	double exVarKNcohort = (varUnivers- sqrErrMeanKNCohort ) / varUnivers;
	exVarMeanCohort = (varUnivers- sqErrMeanCohort ) / varUnivers;
	exVarRegOnlyCohort  = exVarKNcohort -  exVarMeanCohort ;//(varDep - sqrErrKN)/varDep;//ex var kn munis ex var mean.

	double meanWeight = cVarianceCalc::Max(exVarMeanCohort , double(0));
	double regOnlyWeight = cVarianceCalc::Max(exVarRegOnlyCohort , double(0));
//the meanAbsRegEffect and the absKaverge should relate as the weights:
	//absKaveragre / adjustedMeanAbsRegEffect = meanWeight / regOnlyWeight;
//the more the 
	double adjustedMeanAbsRegEffect = meanAbsRegEffect;
	if((meanWeight > 0 ))//&&(meanWeight > (regOnlyWeight *0.25) )) 
	{
		adjustedMeanAbsRegEffect = 	(absKavergeEffect *(regOnlyWeight /meanWeight));
	}

	multipleRegOnlyEffect = adjustedMeanAbsRegEffect  / meanAbsRegEffect;

	multipleRegOnlyEffect=cVarianceCalc::Min(multipleRegOnlyEffect,double(1));


	double decrEffct = 1 - multipleRegOnlyEffect;
	decrEffct = decrEffct *  (meanWeight   / (meanWeight+regOnlyWeight));
	multipleRegOnlyEffect = 1 - decrEffct;



	delete []absRegEffect;
	delete []errArr;
	delete []regEffect ;
}



/////////////////////////////
/*	float * weightedVarAvg = new float[m_numOfPredictiveVars];
	//PREDICT_K _COUNT_EVOLUTION 12 6 12 TO DO  1 10 13 add isInSimGroup as i n put for CalculateK averageAndWeightedVarAvg
	double sumOfCohortScores = 0 ; float kAverage=0;
	CalculateKaverageAndWeightedVarAvg(kAverage, weightedVarAvg, sumOfCohortScores , cohortCount, NULL);
	delete [] weightedVarAvg ;
*/







/////////////////////////////



/*
/////////new fill array function 10 18 13

//10 18 13 draft for nrew fill array...
	the sd of the reg  only s hould be related to the mean of dep (k average)
	in multiep of the weights.
	//the weights are the ex var of each  factor, mena and reg, where the error is vs. the real
	//and the variance is of the k group. 
	find two separate PT arrays, mean and reg only. calcualte ex var for each, weihted/ how?
	use a  new input array for predict filling. , one for only reg PT. 
	use kn ex var and mean ex var to do an on ly reg ex var. 
	then go b ack to the reg only pt and adjust the predictions so that the 
	sd ( pow(erErr, 1/ l level) of oreg only relats to the sd of mean dep as the ex var
	relats between reg only (kn minus mean ex var) to the mean .
*/


/*
double  cStatisticStructure::FillPredictionArr10_18_13(
	                           double* preditiveValueArrr,
	                               bool* isCntrOut,  
								   double &meanDep,
								   double &varDep ,   double &spPTps , double * PT,
										bool *ISc , unsigned int cohortCount, 
										unsigned int testGroupCount, 
							bool isToPredictOnlyMean , 
							cStatisticStructure* parentStatForTest , bool isFullTestCase,
							 bool isRegOnly, double lLevel )
{


	
	//call new funciton to go over the univers and the k group to fill the below all varibles
	//output is ...

	cohortCount = Min(cohortCount, m_count);
	testGroupCount = Min(testGroupCount, m_count);
	
///////////////////////


	/////////////////////////////////////

	//to implement in this function below
	//firsit fill this array 
	double* regOnlyEffect = new double[testGroupCount]; //fill withint the below kn option
	//after calcualrting all PT[] and ex var (both) and sp prediction
	double spRegOnlyEffect =0;


	double** preditiveValueArrTD = new double*[testGroupCount];
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		regOnlyEffect[i]=0;
		preditiveValueArrTD[i]= new double[m_numOfPredictiveVars];
		for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
		{
			preditiveValueArrTD[i][j]=0;
		}
	}

	float kAverage = 0 ;
	float * weightedVarAvg = new float[m_numOfPredictiveVars];

	if(isRegOnly)
	{
		for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
		{
			PT[i]=0;
			if(ISc[i])//m_predictabilityScores[i]==0)
			{
				double prediction = m_regressionBetaZeroConstantTermWeight;
				for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
				{
					double 	betaWeight = (double) m_regressionBetaWeightArray[j];
					double tempPredValueDir = (betaWeight * 
							((double)parentStatForTest->m_predictiveArr[i][j]));
					prediction += tempPredValueDir ;
					preditiveValueArrTD[i][j]= tempPredValueDir; 
				}
				PT[i] = prediction;
			}
		}
		double predictionSP = m_regressionBetaZeroConstantTermWeight;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			double 	betaWeight = (double) m_regressionBetaWeightArray[j];
			double temp = (betaWeight * ((double)m_predictive_set[j]));
			predictionSP += temp ;
			preditiveValueArrr[j] = Abs( temp);

		}
		spPTps = predictionSP;
		//return;
	}
	else
	{


		kAverage = 0 ; //TODAY
		//PREDICT_K _COUNT_EVOLUTION 12 6 12 TO DO  1 10 13 add isInSimGroup as i n put for CalculateK averageAndWeightedVarAvg
		double sumOfCohortScores = 0 ;
		CalculateKaverageAndWeightedVarAvg(kAverage, weightedVarAvg, sumOfCohortScores , cohortCount, NULL);
			//cConfiguration::GetInstance()->GetPr edictKCount(), NULL);
			//(cConfiguration::GetInstance()->GetPredictKC ountEvolution()), NULL);//PREDICT_K_COUNT    );//popChgObj.GetKcount());
		
	
		
		for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
		{
			regOnlyEffect[i]=0;
			PT[i]=0;
			if  (ISc[i])
			//m_predictabilityScores[i]==0)
			{
				float cleanWeightedVarAvera[MAX_NUM_OF_PREDICTIVE_VARIABLES];
				double cleanKaverage=0;
				GetCleanAverage ( cleanKaverage , cleanWeightedVarAvera,
						sumOfCohortScores,kAverage, weightedVarAvg,
						m_predictabilityScores[i],
						m_dependentArr[i], m_predictiveArr[i]);
			
				float predictionRegOnly= 0;//cleanKaverage;//  kAverage;
					

				{
					for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
					{
						double 	betaWeight= (double)m_regressionBetaWeightArray[j];
						double tempPredValueDir = (betaWeight * 
							( (parentStatForTest->m_predictiveArr[i][j])-
							          (cleanWeightedVarAvera[j] )   )    ); 
						predictionRegOnly += tempPredValueDir ;
						//for regresion predictiv epower
					//	double onlyRegPredValDir = (betaWeight * 
					//		((double)parentStatForTest->m_predictiveArr[i][j]));
						preditiveValueArrTD[i][j]= tempPredValueDir;//onlyRegPredValDir; 
							
					}
				}
				if(isToPredictOnlyMean)
				{
					PT[i]= cleanKaverage;
				}
				else
				{
					regOnlyEffect[i] = predictionRegOnly;
					PT[i]= predictionRegOnly+cleanKaverage;
				}
				//spRegOnlyEffect regOnlyEffect
			}
			else
				int ddddd=0;
		}//genration zero flag, sd score, size of k evolution count  10 5 13

		double predictionSPRegOnly = 0;//kAverage;
		//if(!isToPredictOnlyMean)
		{
			for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
			{
				double 	betaWeight = (double) m_regressionBetaWeightArray[j];
				double temp = (betaWeight * ( (m_predictive_set[j])-(weightedVarAvg[j] )   )    );
				predictionSPRegOnly +=  temp;
				preditiveValueArrr[j] = Abs( temp);
			}
			spRegOnlyEffect = predictionSPRegOnly ;
			//predictionSP += kAverage;
		}
		if(isToPredictOnlyMean)
		{
			spPTps = kAverage;
		}
		else
		{
			spPTps = predictionSPRegOnly +kAverage;
		}
	//	delete []weightedVarAvg;
	}

	//10 19 13
	if( (!isRegOnly)&&(!isToPredictOnlyMean))
	{
		double exVarMeanCohort=0;
		double exVarRegOnlyCohort=0;
		double meanRegOnlyEffect=0;
		double multipleRegOnlyEffect=0;
		FillPredictionCalculations(exVarMeanCohort,exVarRegOnlyCohort, multipleRegOnlyEffect,       //meanRegOnlyEffect,
												cohortCount,weightedVarAvg, lLevel );
		multipleRegOnlyEffect = 1;//10 19 13
		exVarMeanCohort = Max(exVarMeanCohort, double(0));
		exVarRegOnlyCohort = Max(exVarRegOnlyCohort, double(0));
		for(unsigned int i=0; i< testGroupCount ; i++)
		{
			if(ISc[i])
			{
			//	double localValInSD = (regOnlyEffect[i] - meanRegOnlyEffect) / sdRegOnlyEffect;
			//	double newRegOnlyValue = adjustedMeanRegOnly + (localValInSD *adjustedSDregOnly);
			//	double adjustedRegOnlyWeight = 
				//			(regOnlyEffect[i]/ meanRegOnlyEffect)* exVarRegOnlyCohort;
				
				PT[i] = kAverage +(multipleRegOnlyEffect*regOnlyEffect[i]);
					//((kAverage * exVarMeanCohort )+(regOnlyEffect[i]* adjustedRegOnlyWeight)) / 
						//				(adjustedRegOnlyWeight+exVarMeanCohort);
				
				for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
				{
					preditiveValueArrTD[i][j] *= multipleRegOnlyEffect;
				}
			}
		}
		//double adjustedRegOnlyWeight = (spRegOnlyEffect/ meanRegOnlyEffect)* exVarRegOnlyCohort;
		spPTps =   kAverage + (multipleRegOnlyEffect* spRegOnlyEffect);
			//((kAverage * exVarMeanCohort )+(spRegOnlyEffect * adjustedRegOnlyWeight)) / 
					//					(adjustedRegOnlyWeight+exVarMeanCohort);

	}
	delete []weightedVarAvg;


	
	double sumWeightsChortParent= 0 ;
	double sumWeightsCohortChild = 0 ;
	for( unsigned int i=0; i< cohortCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		bool allowed =true;

		if(allowed)
		{
			sumWeightsChortParent += parentStatForTest->m_predictabilityScores[i]  ;
			sumWeightsCohortChild += m_predictabilityScores[i]  ;
		}
	}		
	
	double sqErr = 0 ;
//	double sumWeightsTestParent = 0 ;
//	double sumWeightsCntrChildd = 0 ;
	meanDep = 0 ;
	for( unsigned int i=0; i< cohortCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		bool condition = true;

		if(condition)
		{
			meanDep += (m_dependentArr[i]*(m_predictabilityScores[i]));
		//	sumWeightsCntrChildd += m_predictabilityScores[i];
		}
	}
	if(sumWeightsCohortChild > 0 )
	{
		meanDep /= sumWeightsCohortChild ;
	}
	varDep=0;
	for( unsigned int i=0; i< cohortCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		bool condition = true;

		if(condition)
		{
			double expoVal = lLevel;// cConfiguration::GetInstance()->GetLLeve lErrorEvaluation();
			double temp = Abs(m_dependentArr[i]- meanDep);
			temp = pow(temp , expoVal);
			varDep += temp*(m_predictabilityScores[i]);
		}
		//meanDep += (m_dependentArr[i]*(m_predictabilityScores[i]));
		//sumWeightsCntrChildd += m_predictabilityScores[i];
	}
	if(sumWeightsCohortChild > 0 )
	{
		varDep /= sumWeightsCohortChild ;
	}
	
	

//	double* preditiveValueArr = new double[m_numOfPredictiveVars];



	double sumWeightsTestParent = 0 ;
	double sumWeightsTestChild = 0 ;
	double meanPredictedShift = 0 ;

	//BUG 10 15 13
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		
		//if(ISc[i])//m_predictabilityScores[i]==0)
		double percAsCntr = parentStatForTest->m_predictabilityScores[i]  / sumWeightsChortParent ;
		double percAsCohort = m_predictabilityScores[i]  / sumWeightsCohortChild;
		bool algoCond = (  
			( percAsCohort > (percAsCntr - 0.00000001))
			                                  ||
							( isFullTestCase) 
						);
		//we want to go in if 
		bool isGo = algoCond;
	

		if(  ISc[i]  && isGo)
//m_predictabilityScores[i]==0)
		{
			sumWeightsTestParent  += parentStatForTest->m_predictabilityScores[i];
			sumWeightsTestChild += m_predictabilityScores[i];
			double shift = PT[i] - m_dependentArr[i];
			meanPredictedShift += shift*parentStatForTest->m_predictabilityScores[i];
			double error = Abs( PT[i] - (m_dependentArr[i]));

			double expoVal = lLevel;//cConfiguration::GetInstance()->GetLL evelErrorEvaluation();
			error = pow(error, expoVal);
			sqErr += error* (parentStatForTest->m_predictabilityScores[i]);
			
		

		//	meanDep += (m_dependentArr[i]*(m_predictabilityScores[i]));
		//	sumWeightsCntrChild += m_predictabilityScores[i];
			if(isCntrOut)
			{
				isCntrOut[i]=true;
			}

		}
		else
			int rrrr=0;
	}
	if(sumWeightsTestParent  >0)//sumWeightsTestParent  , sumWeightsChortParent
	{
		//how much control grup (who improve) are weighted per the enitre set
		double cohortImpPortionParent = sumWeightsTestParent / sumWeightsChortParent;
		//how much this group weights in the child case, per the wegiht of the child
		double cohortImpPortionChild = sumWeightsTestChild / sumWeightsCohortChild;

		sqErr /= sumWeightsTestParent  ;
		meanPredictedShift /= sumWeightsTestParent  ;
	

		//meanDep /= sumWeightsCntrChild ;
	}
	if(IS_ADJUSTED_SP_PREDICTION_PER_TEST_GROUP_SHIFT)
	{
	//	spPTps -= meanPredictedShift;
	}
	
	
	unsigned int countOfCntrGroup=0;
//	varDep = 0 ;
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		//if(ISc[i])//m_predictabilityScores[i]==0)
		double percAsCntr = parentStatForTest->m_predictabilityScores[i]  / sumWeightsChortParent ;
		double percAsCohort = m_predictabilityScores[i]  / sumWeightsCohortChild;
		bool algoCond = (  
			( percAsCohort > (percAsCntr - 0.00000001))
			                                  ||
							( isFullTestCase) 
						);
		//we want to go in if 
		bool isGo = algoCond;
		

		if(  ISc[i]  && isGo)
		{
			double expoVal = lLevel ; //cConfiguration::GetInstance()->GetLLe velErrorEvaluation();
			double temp = Abs(m_dependentArr[i]- meanDep);
			temp = pow(temp , expoVal);
			countOfCntrGroup++;
		}
	}
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		delete [] preditiveValueArrTD[i];
	}
	delete [] preditiveValueArrTD;
	delete []regOnlyEffect ;

	if(countOfCntrGroup >= cConfiguration::GetInstance()->GetMinGroupCountForEvoTest())//PR EDICT_K_EVOLUTION_MIN_GROUP)
	{	
		return sqErr ;
	}
	return 0;
}
*/





///////////end fill array function 10 18 13


void cStatisticStructure::FillRegOnlyPredictionArr(double &spPTps, double* PT, 
	double** preditiveValueArrTD , bool* ISc,	cStatisticStructure* parentStatForTest, unsigned int testGroupCount)
{
		for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
		{
			PT[i]=0;
			if(ISc[i])//m_predictabilityScores[i]==0)
			{
				double prediction = m_regressionBetaZeroConstantTermWeight;
				for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
				{
					double 	betaWeight = (double) m_regressionBetaWeightArray[j];
					double tempPredValueDir = (betaWeight * 
							((double)parentStatForTest->m_predictiveArr[i][j]));
					prediction += tempPredValueDir ;
					preditiveValueArrTD[i][j]= tempPredValueDir; 
				}
				PT[i] = prediction;
			}
		}
		double predictionSP = m_regressionBetaZeroConstantTermWeight;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			double 	betaWeight = (double) m_regressionBetaWeightArray[j];
			predictionSP += (betaWeight * ((double)m_predictive_set[j]));
		}
		spPTps = predictionSP;
}		


//10 11 13

//WITH_ED_MEAN_TO_LINEAR_CATEGORICAL
/*

void cStatisticStructure::AdjustPerCategoricalVaribles(double* meanEDarr, double* sdEDarr , 
	short int* spPredSet, bool isAdjustAlsoContinuesVar, double** categoricalReplacment)
{

	
	//bool isXYX_4_2_15= true;
	if(isAdjustAlsoContinuesVar)
		int sdf = 0 ; 

	for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		if(cConfiguration::GetInstance()->IsCategoricalVariable(j) ||  isAdjustAlsoContinuesVar)
		{
			if((! IS_DEP_BASE_CAT_CONVERSION) || (categoricalReplacment == NULL  )) //4 2 15
			{
				for(unsigned int i = 0 ; i < m_count ; i++)
				{
					if(j==27)
						int sdf =0;
					double edFromSP =  cConfiguration::GetInstance()->CalcualteED(
						spPredSet[j] , m_predictiveArr[i][j] , j);
					double meanED = meanEDarr[j];
					if( (edFromSP == 0) || ((edFromSP < meanED) &&(WITH_ED_MEAN_TO_LINEAR_CATEGORICAL))  )
					//if(edFromSP < meanED)
					{
						if(edFromSP < meanED && (edFromSP >0)) 
						{
							int sdf = 0 ;
						}
						m_predictiveArr[i][j] = spPredSet[j]; 
					}
					else
					{

					//	m_predictiveArr[i][j] = spPredSet[j] + meanEDarr[j]; 

						if(spPredSet[j] ==0)
						{
							m_predictiveArr[i][j] = 100;
						}
						else
						{
							m_predictiveArr[i][j] = 0;
						}
					}
				}
			}
			else
			{
				for(unsigned int i = 0 ; i < m_count ; i++)
				{
					m_predictiveArr[i][j] = categoricalReplacment[j][m_predictiveArr[i][j]];

				}
			
			}
		}
	}
}

*/

/*
void cStatisticStructure::AdjustPe rCategoricalVaribles()
{
	for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		if(cConfiguration::GetInstance()->IsCategoricalVariable(j))
		{
			for(unsigned int i = 0 ; i < m_count ; i++)
			{
				if(m_predictiveArr[i][j] != m_predictive_set[j])
				{
					if(m_predictive_set[j] ==0)
					{
						m_predictiveArr[i][j] = 100;
					}
					else
					{
						m_predictiveArr[i][j] = 0;
					}
				}
			}
		}
	}
}
	*/


/*
double  cStatisticStructure::FillPredictionArr1_19_13(double &percMeanInportance,
	                           double* preditiveValueArr,
	                               bool* isCntrOut,  
								   double &meanDepp,
								   double &varDepp ,   double &spPTps , double * PT,
										bool *ISc , unsigned int cohortCount, 
										unsigned int testGroupCount, 
							bool isToPredictOnlyMean , 
				cStatisticStructure* parentStatForTest , bool isFullTestCase,unsigned int subSetJ,
							bool* isCntrInn, bool isRegOnly, double lLevel , double varUnivers, bool withReducedKN)
{
	

	double** preditiveValueArrTD = new double*[testGroupCount];
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		preditiveValueArrTD[i]= new double[m_numOfPredictiveVars];
		for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
		{
			preditiveValueArrTD[i][j]=0;
		}
	}


	cohortCount = cVarianceCalc::Min((int)cohortCount, (int)m_count);
	testGroupCount = cVarianceCalc::Min((int)testGroupCount, (int)m_count);


	if((isRegOnly )|| (withReducedKN))
	{

		FillRegOnlyPredictionArr(spPTps, PT, preditiveValueArrTD , ISc,	parentStatForTest, testGroupCount);
	}
	else if(IS_KN_SHIFT && (!isToPredictOnlyMean))
//	else if(!isToPredictOnlyMean)
	{
		cohortCount = cVarianceCalc::Min(cohortCount, testGroupCount);
		FillRegOnlyPredictionArr(spPTps, PT, preditiveValueArrTD , ISc,	parentStatForTest, testGroupCount);
		double sumDep = 0.0;
		double weightSum =0.0; 
		for(unsigned int i=0; i< cohortCount; i++) // loop on k group to count the predictivlity sum of weights
		{
			sumDep += ((double)m_dependentArr[i])* ((double)m_predictabilityScores[i]);
			weightSum += (double )m_predictabilityScores[i];
		}
		double sumPrediction=0;
		for(unsigned int i=0; i< cohortCount; i++) // loop on k group to count the predictivlity sum of weights
		{
			sumPrediction += ((double)PT[i])* ((double)m_predictabilityScores[i]);
			if(sumPrediction < -100000)
				int ggg=0;
		}
		
	
		for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
		{
			
			if  (ISc[i])
			//m_predictabilityScores[i]==0)
			{
				double sumOfOtherDep = sumDep -
					(((double)m_dependentArr[i])* ((double)m_predictabilityScores[i]));
				double sumOfOtherPrediction = sumPrediction - 
					    (((double)PT[i])* ((double)m_predictabilityScores[i]));
				double sumOfWeightsOthers = weightSum - (double )m_predictabilityScores[i];
				double averageOtherDep = sumOfOtherDep / sumOfWeightsOthers;
				double avgOtherPrediction = sumOfOtherPrediction / sumOfWeightsOthers;
				double shiftToAdd = averageOtherDep - avgOtherPrediction ; //if real dep is showing highegr values for exapmle than we want to adjust the predictin value
				PT[i] += shiftToAdd ;
			}
		}//genration zero flag, sd score, size of k evolution count  10 5 13
			
		double averageDep = sumDep / weightSum;
		double avgPrediction = sumPrediction / weightSum;
		double shiftToAdd = averageDep - avgPrediction ; //if real dep is showing highegr values for exapmle than we want to adjust the predictin value
		spPTps += shiftToAdd ;
		
	}
	else //if(isToPredictOnlyMean)
	{


		float kAverage = 0 ; //TODAY
		float varDep=0;
		float * weightedVarAvg = new float[m_numOfPredictiveVars];
		//PREDICT_K _COUNT_EVOLUTION 12 6 12 TO DO  1 10 13 add isInSimGroup as i n put for CalculateK averageAndWeightedVarAvg
		double sumOfCohortScores = 0 ;
		CalculateKaverageAndWeightedVarAvg(kAverage, varDep,weightedVarAvg, sumOfCohortScores , cohortCount, NULL);
			//cConfiguration::GetInstance()->GetPr edictKCount(), NULL);
			//(cConfiguration::GetInstance()->GetPredictKC ountEvolution()), NULL);//PREDICT_K_COUNT    );//popChgObj.GetKcount());
		
	



		
		for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
		{
			PT[i]=0;
			if  (ISc[i])
			//m_predictabilityScores[i]==0)
			{
				float cleanWeightedVarAvera[MAX_NUM_OF_PREDICTIVE_VARIABLES];
				double cleanKaverage=0;
				GetCleanAverage ( cleanKaverage , cleanWeightedVarAvera,
						sumOfCohortScores,kAverage, weightedVarAvg,
						m_predictabilityScores[i],
						m_dependentArr[i], m_predictiveArr[i]);
			
				float prediction= cleanKaverage;//  kAverage;
				if(!isToPredictOnlyMean)
					

				{
					for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
					{
						double 	betaWeight= (double)m_regressionBetaWeightArray[j];
						double tempPredValueDir = (betaWeight * 
							( (parentStatForTest->m_predictiveArr[i][j])-
							          (cleanWeightedVarAvera[j] )   )    ); 
						prediction += tempPredValueDir ;
						//for regresion predictiv epower
					//	double onlyRegPredValDir = (betaWeight * 
					//		((double)parentStatForTest->m_predictiveArr[i][j]));
						preditiveValueArrTD[i][j]= tempPredValueDir;//onlyRegPredValDir; 
							
					}
				}
				PT[i]= prediction;
			}
			else
				int ddddd=0;
		}//genration zero flag, sd score, size of k evolution count  10 5 13

		double predictionSP = kAverage;
		if(!isToPredictOnlyMean)
		{
			for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
			{
				double 	betaWeight = (double) m_regressionBetaWeightArray[j];
				predictionSP +=  (betaWeight * ( (m_predictive_set[j])-(weightedVarAvg[j] )   )    );
			}
		}
		spPTps = predictionSP;
		delete []weightedVarAvg;
	}

	
	double sumWeightsChortParent= 0 ;
	double sumWeightsCohortChild = 0 ;
	for( unsigned int i=0; i< cohortCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		bool allowed =true;

		if(allowed)
		{
			sumWeightsChortParent += parentStatForTest->m_predictabilityScores[i]  ;
			sumWeightsCohortChild += m_predictabilityScores[i]  ;
		}
	}		


//	double* preditiveValueArr = new double[m_numOfPredictiveVars];
	for(unsigned int j = 0 ; j< m_numOfPredictiveVars ; j++)
	{
		preditiveValueArr[j]=0;
	}

	double sumWeightsTestParent = 0 ;
	double sumWeightsTestChild = 0 ;
	double meanPredictedShift = 0 ;




	double sqErr = 0 ;//11 22 13
//





	//BUG 10 15 13
	unsigned int countOfCntrGroup=0;
	meanDepp=0;
	varDepp=0;
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		
		double ed = cVarianceCalc::Abs( parentStatForTest->m_predictiveArr[i][subSetJ] - 
								parentStatForTest->m_predictive_set[subSetJ]);
		double edInSD = 0 ;
		if(parentStatForTest->m_sdEdCtoS[subSetJ] > 0)
		{
			edInSD =(ed- parentStatForTest->m_meanEdCtoS[subSetJ]) / 
									parentStatForTest->m_sdEdCtoS[subSetJ]; 
		}




		//if(ISc[i])//m_predictabilityScores[i]==0)
		double percAsCntr = parentStatForTest->m_predictabilityScores[i]  / sumWeightsChortParent ;
		double percAsCohort = m_predictabilityScores[i]  / sumWeightsCohortChild;
		bool algoCond = (  
			      (edInSD  < 0)
		//	( percAsCohort > (percAsCntr - 0.00000001))
			                                  ||
							( isFullTestCase) 
						);
		//we want to go in if 
		bool isGo = algoCond;
		
		if(  ISc[i]  && isGo)
//m_predictabilityScores[i]==0)
		{
			sumWeightsTestParent  += parentStatForTest->m_predictabilityScores[i];
			sumWeightsTestChild += m_predictabilityScores[i];
			double shift = PT[i] - m_dependentArr[i];
			meanPredictedShift += shift*parentStatForTest->m_predictabilityScores[i];
			double error = cVarianceCalc::Abs( PT[i] - (m_dependentArr[i]));

			double expoVal = lLevel;//cConfiguration::GetInstance()->Get LLevelErrorEvaluation();
			error = pow(error, expoVal);
			sqErr += error* (parentStatForTest->m_predictabilityScores[i]);
			countOfCntrGroup++;
			
			for(unsigned int j=0; j< m_numOfPredictiveVars; j++)
			{
				preditiveValueArr[j] += cVarianceCalc::Abs((preditiveValueArrTD[i][j]*
									(parentStatForTest->m_predictabilityScores[i])));
			}
			meanDepp += (  (  ((float)m_dependentArr[i]) )*(parentStatForTest->m_predictabilityScores[i]));
		//	sumWeightsCntrChild += m_predictabilityScores[i];
			if(isCntrOut)
			{
				isCntrOut[i]=true;
			}

		}
		else
			int rrrr=0;
	}
	if(sumWeightsTestParent  >0)//sumWeightsTestParent  , sumWeightsChortParent
	{
		//how much control grup (who improve) are weighted per the enitre set
		double cohortImpPortionParent = sumWeightsTestParent / sumWeightsChortParent;
		//how much this group weights in the child case, per the wegiht of the child
		double cohortImpPortionChild = sumWeightsTestChild / sumWeightsCohortChild;




		sqErr /= sumWeightsTestParent  ;
		meanPredictedShift /= sumWeightsTestParent  ;
		for(unsigned int j=0; j< m_numOfPredictiveVars; j++)
		{
			preditiveValueArr[j] /= sumWeightsTestParent;
		}
		meanDepp /= sumWeightsTestParent ;
	}
	if(IS_ADJUSTED_SP_PREDICTION_PER_TEST_GROUP_SHIFT)
	{
	//	spPTps -= meanPredictedShift;
	}
	

//	varDep = 0 ;
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		double ed = cVarianceCalc::Abs( parentStatForTest->m_predictiveArr[i][subSetJ] - 
								parentStatForTest->m_predictive_set[subSetJ]);
		double edInSD = 0 ;
		if(parentStatForTest->m_sdEdCtoS[subSetJ] > 0)
		{
			edInSD =(ed- parentStatForTest->m_meanEdCtoS[subSetJ]) / 
									parentStatForTest->m_sdEdCtoS[subSetJ]; 
		}


		//if(ISc[i])//m_predictabilityScores[i]==0)
		double percAsCntr = parentStatForTest->m_predictabilityScores[i]  / sumWeightsChortParent ;
		double percAsCohort = m_predictabilityScores[i]  / sumWeightsCohortChild;
		bool algoCond = (  
			      (edInSD  < 0)
		//	( percAsCohort > (percAsCntr - 0.00000001))
			                                  ||
							( isFullTestCase) 
						);
		//we want to go in if 
		bool isGo = algoCond;
		
		if(  ISc[i]  && isGo)
		{
			double expoVal = lLevel ;//cConfiguration::GetInstance()->GetLL evelErrorEvaluation();
			double temp = cVarianceCalc::Abs(  (  ((float)m_dependentArr[i]) )- meanDepp);
			temp = pow(temp , expoVal);
			varDepp += temp*(parentStatForTest->m_predictabilityScores[i]);
	//		countOfCntrGroup++;
		}
	}
	if(sumWeightsTestParent  >0)//sumWeightsTestParent  , sumWeightsChortParent
	{
		varDepp /= sumWeightsTestParent ;
	}


	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		delete [] preditiveValueArrTD[i];
	}
	delete [] preditiveValueArrTD;

	
	//1 12 5 13 check that the 0 is like no effect, that the constant is relatie to the pred arr 
	                      //variance with not relation to the dep variance. also check that it is not efecting mean only and reg only, only kn 

	if((!isToPredictOnlyMean)&& (!isRegOnly)&&(withReducedKN))
	{
		//AdjustPredictionBasedOnKNstrength
			//AdjustPredictionBasedOnKNstrength12_7_13
			double per = AdjustPredictionBasedOnKNstrength12_10_13(percMeanInportance,spPTps , PT,	 testGroupCount,  lLevel);
		
	}
	




	if(countOfCntrGroup >= cConfiguration::GetInstance()->GetMinGroupCountForEvoTest())//PR EDICT_K_EVOLUTION_MIN_GROUP)
	{	
		return sqErr ;
	}
//	varDep = 0 ;
	return 0;
}
*/

/*
	input = 
	isIn to define the sub set of entitier  test group count array
	baseMeanDep , baseVarDep from univers
	
	the process will be to : 
	calcuate the meian mean and var of the kk group using the  the simKprediction using the GetVari anceWithBoolArr
	calcualring the abs of the group mean from the input baseMEanDep
	calcualte the ppolimonoial error using one half k for cohhort and one half fofr test
	performance will be the abs shift of group from univers, devided to the error sqare root

	*/

double  cStatisticStructure::CalculateKgrouopStatistics12_10_13(double &preShift,  double &percenK, double &testMean, double &testVarK  , 
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel, double* PT)
											//unsigned int countK , double meanU , double varU )
{
	//GetVarianceWith BoolArr(percenK, meanK, varK, arr, weightArr,   countU,  isIn,  lLevel);
	preShift=0;
	
	//defining cohort
	int mode=0;
	double meanCohort =0;
	double sumWeightsCohort =0;
	for(unsigned int i = 0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			if((mode ==0)||(PT!=NULL))
			{
				double weight = weightArr[i];
				sumWeightsCohort += weight;
				meanCohort += weight * arr[i];
				mode =1;
			}
			else
			{
				mode =0;
			}	
		}
	}
	meanCohort /= sumWeightsCohort ;


	mode=1;
	double sumWeightsTest=0;
	double sqrErr = 0 ;
	double meanPred = 0 ;
	testMean=0;
	for(unsigned int i = 0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			if((mode ==0)||(PT!=NULL))
			{	
				double weight = weightArr[i];
				double prediction = meanCohort;
				if(PT!=NULL)
				{
					prediction = PT[i];
				}
				double ed = cVarianceCalc::Abs(arr[i] - prediction  );
				ed = pow(ed, lLevel);
				sqrErr += ed * weight;
				sumWeightsTest += weight;
				meanPred += prediction * weight;
				testMean += arr[i]  * weight;
				
				//meanCohort  += weight * arr[i];
				mode =1;
			}
			else
			{
				mode =0;
			}	
		}
	}
	sqrErr /= sumWeightsTest ;
	meanPred /= sumWeightsTest;
	testMean /= sumWeightsTest;
	preShift = meanPred - testMean;
	
	
	
	
	{
		mode=1;
		testVarK=0;
		for(unsigned int i = 0 ; i < countU ; i++)
		{
			if(isIn[i])
			{
				if((mode ==0)||(PT!=NULL))
				{	
					double weight = weightArr[i];
					double ed = cVarianceCalc::Abs(arr[i] - testMean  );
					ed = pow(ed, lLevel);
					testVarK += ed * weight;
					mode =1;
				}
				else
				{
					mode =0;
				}	
			}
		}
		testVarK /= sumWeightsTest ;	
	}
	
	return sqrErr;
}





double  cStatisticStructure::CalculateKgrouopStatistics12_11_13(  
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel, double* PT)
											//unsigned int countK , double meanU , double varU )
{

	//defining cohort
	int mode=0;
	double meanCohort =0;
	double sumWeightsCohort =0;
	for(unsigned int i = 0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			if((mode ==0)||(PT!=NULL))
			{
				double weight = weightArr[i];
				sumWeightsCohort += weight;
				meanCohort += weight * arr[i];
				mode =1;
			}
			else
			{
				mode =0;
			}	
		}
	}
	meanCohort /= sumWeightsCohort ;


	mode=1;
	double sumWeightsTest=0;
	double sqrErr = 0 ;
	double meanPred = 0 ;
	double testMean=0;
	for(unsigned int i = 0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			if((mode ==0)||(PT!=NULL))
			{	
				double weight = weightArr[i];
				double prediction = meanCohort;
				if(PT!=NULL)
				{
					prediction = PT[i];
				}
				double ed = cVarianceCalc::Abs(arr[i] - prediction  );
				ed = pow(ed, lLevel);
				sqrErr += ed * weight;
				sumWeightsTest += weight;
				meanPred += prediction * weight;
				testMean += arr[i]  * weight;
				
				//meanCohort  += weight * arr[i];
				mode =1;
			}
			else
			{
				mode =0;
			}	
		}
	}
	sqrErr /= sumWeightsTest ;
	meanPred /= sumWeightsTest;
	testMean /= sumWeightsTest;
	double	preShift = meanPred - testMean;	
	
	double testVarK=0;
	{
		mode=1;
		testVarK=0;
		for(unsigned int i = 0 ; i < countU ; i++)
		{
			if(isIn[i])
			{
				if((mode ==0)||(PT!=NULL))
				{	
					double weight = weightArr[i];
					double ed = cVarianceCalc::Abs(arr[i] - testMean  );
					ed = pow(ed, lLevel);
					testVarK += ed * weight;
					mode =1;
				}
				else
				{
					mode =0;
				}	
			}
		}
		testVarK /= sumWeightsTest ;	
	}
	
	return ( testVarK-sqrErr) / testVarK;	
		//sqrErr;

}



///////////  CalculateKgrouopStatistics12_12_13 () ///////////////////////////////////////

#define MAX_NUM_OF_TESTS 10 //must be even  number,  2,4,6,....

/*
examle withi a simpe spread over 10 test count


COHOT

//first test :  0,1 2 3 4 . . . . . 10 11 12 13 14 .. .. .. .. ..
//second test : 0,1 2 3 . . . . . 9 10 11 12 13 .. .. .. .. .. 19 
//              0 1 2 . . . . . 8 9 10 11 12 .. .. .. .. .. 18 19
//              0 1 . . . . . 7 8 9 10 11 .. .. .. .. .. 17 18 19
//fifth			0 . . . . . 6 7 8 9 10 .. .. .. .. .. 16 17 18 19
                . . . . . 5 6 7 8 9 .. .. .. .. .. 15 16 17 18 19

TEST

//first test   . . . . . 5 6 7 8 9 .. .. .. .. .. 15 16 17 18 19					
//second test  . . . . 4 5 6 7 8 . .. .. .. .. 14 15 16 17 18 ..
//third test   . . . 3 4 5 6 7 . . .. .. .. 13 14 15 16 17 .. ..
//forth test   . . 2 3 4 5 6 . . . .. .. 12 13 14 15 16 .. .. ..
//fifth test   . 1 2 3 4 5 . . . . .. 11 12 13 14 15 .. .. .. ..
			   0 1 2 3 4 . . . . . 10 11 12 13 14 .. .. .. .. ..
			   ...
			   ....

			   square error of test group when prediction is univerrs = seU

square error of test group when pedicion is mean cohort = seP 
 variance of test group = varTest
 explained variance using universe as mean = ExVarU
 explained variance using profile cohort as mean = ExVarP
 in each time we devide the profile into two  halves, cohort and test, we will calculate:
  exVarU = (varTest-seU) / varTest  
exVarP = (varTest-seP) / varTest
performance = exVarP - exVarU
*/	 
double  GetMeanSubGroup( double &varianceSub, double* arr, float* weightArr, unsigned int  countU, bool* isIn, double lLevel)
{
	double mean = 0 ;
	double sumWeights=0;
	for( unsigned int i=0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			mean += weightArr[i]* arr[i];
			sumWeights += weightArr[i];
		}
	}
	if( sumWeights > 0)
	{
		mean /= sumWeights;
	}

	varianceSub = 0 ;
	for( unsigned int i=0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			double dif =  arr[i] - mean;
			dif =cVarianceCalc:: Abs(dif);
			double sqrDiif =  pow(dif, lLevel);
			varianceSub += sqrDiif *weightArr[i];
		}
	}
	if( sumWeights > 0)
	{
		varianceSub /= sumWeights;
	}
	return mean;

}

/*

 double CalculateSqrErrorSubGroup(	    double* arr, float* weightArr,  unsigned int countU, bool* isIn, 
													double lLevel, double meanForPred, double  sumWeightsUsedForPred  )
 {
	
	double avgSqrError = 0 ;
	double sumWeighits = 0 ;
	for( unsigned int i=0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			


			double prediction =   (( meanForPred * sumWeightsUsedForPred ) -  (arr[i]*weightArr[i] )) / (sumWeightsUsedForPred - weightArr[i] );
				
				//double meanProfile, double  sumWeightsSub
		
			double dif =  arr[i] - prediction;
			dif = Abs(dif);
			double sqrDiif =  pow(dif, lLevel);
			avgSqrError += sqrDiif *weightArr[i];
			sumWeighits += weightArr[i];
		}
	}
	if(sumWeighits >0)
	{
		avgSqrError /= sumWeighits;
	}

	return avgSqrError;
	
 }
*/
	


 double cStatisticStructure::CalculateKgrouopStatistics1_17_14( double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel,
						   double  predictonLearn, bool isOnlySimGroupPerfStart )

 {

	double avgSqrError = 0 ;
	double sumWeighits = 0 ;
	for( unsigned int i=0 ; i < countU ; i++)
	{
		if(isIn[i])
		{
			double dif =  arr[i] - predictonLearn;
			dif = cVarianceCalc::Abs(dif);
			double sqrDiif =  pow(dif, lLevel);
			avgSqrError += sqrDiif *weightArr[i];
			sumWeighits += weightArr[i];
		}
	}
	if(sumWeighits >0)
	{
		avgSqrError /= sumWeighits;
	}

	//return avgSqrError;


	double varianceSub=0;
	meanProfile = GetMeanSubGroup(varianceSub, arr, weightArr,  countU, isIn, lLevel);

	double perform = 0 ;
	if(varianceSub >0)
	{
		perform= (varianceSub - avgSqrError) / varianceSub;
	}
	return perform;
 
 }
	/* this new version will receive and use the entire regCount  , not only the top predict count. it will go one be one on the 
	array of dep values and meassure the square error in two ways, one is based on average of all populaaion, and one option is based on 
	only each group as a separate. we can then calcualte the ex var based on each algo and the difference between the two algos will 
	be the return value of the function. in botho algos we will ignore the speciofic item when using the group average as the predictoed
	value using only the other items  of the group.
	*/


			/*		   
double  cStatisticStructure::CalculateKgrouopStatistics12_20_13(  double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel, double meanUniverse)//, double* PT)
											//unsigned int countK , double meanU , double varU )
{

	unsigned int  numOfTests = MAX_NUM_OF_TESTS;
	if ((numOfTests % 2) != 0)
	{
		numOfTests ++; //must be even number
	}
	int modeRange = numOfTests;
//duble exVarArr[MAX_NUM_OF_TESTS];
//	double exVarP[MAX_NUM_OF_TESTS];
//	double exVarU[MAX_NUM_OF_TESTS];

	double errRateP[MAX_NUM_OF_TESTS];
	double errRateU[MAX_NUM_OF_TESTS];



	//12 15 13
	double performanceArr[MAX_NUM_OF_TESTS];
	for (unsigned int indexTest = 0 ; indexTest < numOfTests ; indexTest++)
	{
		//defining cohort
		int mode=indexTest;
		double meanCohort =0;
		double sumWeightsCohort =0;
		for(unsigned int i = 0 ; i < countU ; i++)
		{
			if(isIn[i])
			{
				if((mode < (modeRange/2 )))
				{
					double weight = weightArr[i];
					sumWeightsCohort += weight;
					meanCohort += weight * arr[i];
				
				}
				mode++;
				if(mode ==modeRange)
				{
					mode =0;
				}	
			}
		}
		meanCohort /= sumWeightsCohort ;

		//defining test group mean anad squaare error
		mode=indexTest + (modeRange/2 )   ;
		mode = mode%MAX_NUM_OF_TESTS;
		
		double sumWeightsTest=0;
		double sqrErrP= 0 ;
		double sqrErrU =0; 
		double testMean=0;
		for(unsigned int i = 0 ; i < countU ; i++)
		{
			if(isIn[i])
			{
				if((mode < (modeRange/2 )))
				{	
					double weight = weightArr[i]; 
					sumWeightsTest += weight;
					
					double edP= Abs(arr[i] - meanCohort  );
					edP= pow(edP,lLevel);
					sqrErrP+= edP* weight;
				
					double edU = Abs(arr[i]- meanUniverse);
					edU= pow(edU,lLevel);
					sqrErrU += edU * weight;
					
					testMean += arr[i]  * weight;
				}
				mode++;
				if(mode ==modeRange)
				{
					mode =0;
				}	
			}
		}
		sqrErrP /= sumWeightsTest ;
		sqrErrU /= sumWeightsTest;
		testMean /= sumWeightsTest;
		//predShift just for debug perpose
		double	preShift = meanCohort - testMean;	 
		meanProfile = (meanCohort + testMean) / 2;
			//12 15 13
	
		performanceArr[indexTest]= (sqrErrU-sqrErrP) / sqrErrU;
	

		//12 15 13
	//ouble shiftFromUniversMean = Abs(meanUniverse -fullGroupWeightMean); 
	//erformArr[indexTest] =  shiftFromUniversMean /  sqrErrorRoot ;
	}

	double avgPerf = 0 ;
//	double countActive = 0 ;
	for (unsigned int indexTest = 0 ; indexTest < numOfTests ; indexTest++)
	{
		avgPerf += 	performanceArr[indexTest] ;
	}
	avgPerf /= numOfTests ;
//vgPerffoArr /= countActive ;
	return avgPerf;//avgExVar;

}


*/



















/*


double  cStatisticStructure::GetVarianceWithBoolArr(double &perentileVal, double &mean, double &var, double* arr, float *weightArr,  
	                       unsigned int testGroupCount, bool* isIn,  double lLevel, unsigned int predictCOunt)
{
	mean = 0 ;
	double sumWeightGroup =0;
	for (unsigned int i =0; i < testGroupCount ; i++)
	{
		if(isIn[i])
		{
			sumWeightGroup += weightArr[i];
			mean += arr[i]* weightArr[i];
		}
		else
			int yyy=0;
	}
	mean /= sumWeightGroup;

	var = 0 ; 
	for (unsigned int i =0; i < testGroupCount ; i++)
	{
		if(isIn[i])
		{
			double temp = arr[i] - mean;
			temp = pow (Abs(temp) ,  lLevel);
			var += temp *  weightArr[i];
		}
	}
	var /= sumWeightGroup;

	double sd = pow(var, double(1/lLevel));


	
	unsigned int counts[NUM_OF_EDIT_SCORE_BUCKETS];

	for (unsigned int i = 0; i < NUM_OF_EDIT_SCORE_BUCKETS; i++)
	{
		counts[i] = 0;
	}
//	double shiftInSD = (unsigned int)( 5*sd);

	double sdShift = 5;

	unsigned int countOfParticipants = 0;
	for (unsigned int i =0; i < testGroupCount ; i++)
	{
		if(isIn[i])
		{
			double dobScore = arr[i];
			double scoreInSD = 0;
			if(sd > 0 )
			{
				scoreInSD = (dobScore - mean) / sd;
			}	
			else
				int ggg=0;
			double shifterSscore = scoreInSD+ sdShift;//shiftInSD;//shift;
			//
			shifterSscore *=100;
			shifterSscore = Max(shifterSscore , double(0));
			short int score = Min<short int>((short int)shifterSscore, NUM_OF_EDIT_SCORE_BUCKETS - 1);
			counts[score]++;
			countOfParticipants++;
		}
	}

	unsigned int sum =0;

	short int maxScoreAllowed=0;

//counts the profiles along the scores from 0 to up till 


	unsigned int topPercentileCount = cConfiguration::GetInstance()->GetPredictKCountEvolution();// cConfiguration::GetInstance()->GetP redictKCount();
	if(predictCOunt >0)
	{
		topPercentileCount = predictCOunt;
	}
//	topPercentileCount = Min(topPercentileCount , countOfParticipants/2); //the perentile group size cannot be smaller than a median count



	for (unsigned int index = 0; (sum <= (topPercentileCount)) && (index < NUM_OF_EDIT_SCORE_BUCKETS); index++)

	{
		sum += counts[index];
		maxScoreAllowed = index;
	}
	double temp =   (double) (maxScoreAllowed);//  + ((short int)1 )) ;//adding 1 to ensure not rounding issue using short int buckets
	temp += 1.1; //adding 1 for rounding and 0.1 for potentiali floating changes
	temp /=100;
	temp -= sdShift ;
	temp *= sd;
	temp += mean;

	perentileVal = temp;//Max(temp,double(0));//((double)maxScoreAllowed) - sdShift;

	return sumWeightGroup;
}

//inputs:
	//spPTps; this is the input and output of thi section . it will be modefied
	//kAverage
	//varDepp 
	//sqErr
	//..input last parameters = varUnivers. chane the name .....
	*/
	/*
	inpuy is:
	     PT, test count, 
	output: adjusted prediction

	we try to see whether therre is ia predicive power even within our profile. 

	in order to see that we can try to ovserve the the profile test group , w hich is now sorted based on the profile only,in two ways
	one way is to see how much getting to a smaller group brings the variance further down, so that the smaller gruop variacne is smaller
	than the larger all test count grouop variance. 

	getting to a smaller variance means that similarity baed on the sim formula we sarted with is valuable.

	then, based on the PT values, we also select half size group, so that we take the half ones that are closer to the input predcitionn
	value from the PT. we then check the variance of that group . 

	eventually we have 3 numbers. one is the variance of the full test count group, the varinace of the more similar half, and the 
	variance of the half which is closer to the prediction based on KN. we prepare groups by sending a bollean true/false to a fu nction
	that knows to do variance with a bollean flag arry.

	when we have that 3 variane, baseVar, smallProfileBaseVar, smallKNbasedVar, 
	profileStrength = (baseVar - smallProfileBaseVar ) / baseVar;
	knStrength = baseVar - (smallKNbasedVar)/baseVar ;
	MAx( ... , 0)


	we can get the strenth of kn vs. profile in this profile group size. we then can adjust the 
	sd as porposd below with this constant so that for exmale if profile strenght is better we stay with only proifle.
	if kn gives us some improvement , for  example it goes to 80% varinae and profile goe to 90% which mensa knSte is 0.2
	vs. 0.1 than in this case we allow our variance or sd of kn prediction array to be in that proportion based on group var.
	for exmaple, if it is 0.2 vs, 0,1 than it is only half useful and we willl reduce the sd by half.

/////////////////////////12 7 13

if (withReducedKN && (!isRegOnly) && (!isMeanBased))
   first call to the 
	
	
	
	*/

/*
void cStatisticStructure::AdjustPredictionBasedOnKNstrength(double &prediction , double* PT,
						unsigned int testGroupCount,  double lLevel)
{

	//PREPARING DEP ARR IN DOUBLE ARRA
	double* depArr = new double [testGroupCount];
	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{
		depArr [i]= (double)m_dependentArr[i];
	}



//SETTING THE BOOL ARRAY READY FOR ALLL GROUP VARIANCE
//seting isIn true for the    " baseVarDep"
	bool* isIn = new bool [testGroupCount];
	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{
		isIn [i]=true;
	}
	
	double baseMedian=0;
	double baseMeanDep = 0 ;
	double baseVarDep = 0;
	double sumAllWeights = GetVarianceWithB oolArr(baseMedian, baseMeanDep, baseVarDep, depArr, m_predScoresAlt,  testGroupCount, isIn,  lLevel);
	


//PREPARE BOOL ARRAY FOR SIM HALF VARIANCE CALCUALTION

	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{
		if(i < (testGroupCount/2) )
		{
			isIn[i] = true;
		}
		else
		{
			isIn [i]=false;
		}
	}

	double similarHalfMedian=0;
	double similarHalfMean=0;
	double simBaseSimGroupVar= 0;
	double sumWeighitsSimGroup=0;
	{
		sumWeighitsSimGroup = GetVarianceWi thBoolArr(similarHalfMedian, similarHalfMean, simBaseSimGroupVar, depArr,
																m_predScoresAlt,  testGroupCount, isIn,lLevel);
	}

	

//PREPARE BOOL ARRAY FOR OTHER HALF VARIANCE CALCUALTION

	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{
		if(i >= (testGroupCount/2) )
		{
			isIn[i] = true;
		}
		else
		{
			isIn [i]=false;
		}
	}

	double otherHalfMedian=0;
	double otherHalfMean=0;
	double simBaseOtherGroupVar= 0;
	double sumWeighitsOtherGroup=0;
	{
		sumWeighitsOtherGroup = GetVarianceWi thBoolArr(otherHalfMedian, otherHalfMean, simBaseOtherGroupVar, depArr,
																m_predScoresAlt,  testGroupCount, isIn,lLevel);
	}


	double avgSimSpliltVar = ((simBaseSimGroupVar*sumWeighitsSimGroup)+ (simBaseOtherGroupVar*sumWeighitsOtherGroup))/ 
																		 (sumWeighitsSimGroup + sumWeighitsOtherGroup);
	double simStrength = (baseVarDep-avgSimSpliltVar)/baseVarDep;
	simStrength=Max(simStrength,double(0));


	
//bring back all bool arr to true for the  prediction based  check
	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{
		isIn [i]=true;
	}

	double predictionMedian=0;
	double predictionMean = 0 ;
	double predictionVar = 0 ;
	{
	
		GetVarianceWithB oolArr(predictionMedian, predictionMean, predictionVar, PT, m_predScoresAlt,  
			testGroupCount, isIn , lLevel);
	}

	//prepare for the half that is 
	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{//if the predictio of an item base on kn is from the farther group than we don't include it
		if(PT[i] > predictionMedian)
		{
			isIn [i]=true;
		}
		else
		{
			isIn [i] = false;
		}
	}
	double predBaseHighHalfMedian = 0 ;
	double predBaseHighHalfMean = 0 ;
	double predBaseHighGroupVar = 0;
	double sumWeighitsHighGroup = 0 ;
	{
		
		sumWeighitsHighGroup = GetVarianceW ithBoolArr( predBaseHighHalfMedian, predBaseHighHalfMean, predBaseHighGroupVar, depArr, m_predScoresAlt,
							testGroupCount, isIn , lLevel);
		int ddd=0;
	}
	
	for(unsigned int i=0 ; i < testGroupCount ; i++)
	{//if the predictio of an item base on kn is from the farther group than we don't include it
		if(PT[i] <= predictionMedian)
		{
			isIn [i]=true;
		}
		else
		{
			isIn [i] = false;
		}
	}
	double predBaseLowHalfMedian = 0 ;
	double predBaseLowHalfMean = 0 ;
	double predBaseLowGroupVar = 0;
	double sumWeighitsLowGroup = 0 ;
	{
		
		sumWeighitsLowGroup = GetVaria nceWithBoolArr( predBaseLowHalfMedian, predBaseLowHalfMean, predBaseLowGroupVar, depArr, m_predScoresAlt,
							testGroupCount, isIn , lLevel);
		int fff=0;
	}
	
}
*/


#define TABLE_DIM_SIZE 5


////////////////////newe adjust predicitno 12 10 13

/*



*/

unsigned int GetDimVal(double predVal )
{
	if( predVal  < -100 )
		return 0;
	else if( predVal   >= -100  && predVal  < 0   )
		return 1;
	else if( predVal   >= 0  && predVal  < 100   )
		return 2;
	else if( predVal   >= 100  && predVal  < 200   )
		return 3;
	else if( predVal   >= 200 )
		return 4;

}

//double algorithSelectionTable[TABLE_DIM_SIZE ][TABLE_DIM_SIZE ];
void CalcualteTableWeightsForAlgoSelection( double** algorithSelectionTable)
{
	
	
	/*
	algorithSelectionTable[0][0]
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	algorithSelectionTable
	*/
	for(unsigned int i = 0 ; i < TABLE_DIM_SIZE ; i++)
	{
		for(unsigned int j = 0 ; j < TABLE_DIM_SIZE ; j++)
		{
			double iWeight = 1;
			double jWeight = 1;
			//algorithSelectionTable[i][j]=0.5;
			if(i==1)
				iWeight *= 2;
			if(i==0)
				iWeight *= 4;
			if(j==3)
				jWeight *= 2;
			if(j==4)
				jWeight *= 4;
			algorithSelectionTable[i][j]= iWeight / (iWeight + jWeight);
		}
	
	}

}
		
void GetTableWeightsForAlgorithSelection(double &simWeight , double &regWeight , 
		double** algorithSelectionTable,   double simPred, double regPred )
{
	unsigned int simDimVal = GetDimVal(simPred );
	unsigned int regDimVal = GetDimVal(regPred );
	double tableVal = algorithSelectionTable[simDimVal][regDimVal] ;
	simWeight = tableVal ;
	regWeight = 1 - tableVal ;
}


/*

double cStatisticStructure::AdjustPredictionBasedOnKNstrength12_10_13(
	double &percMeanInportance, double &prediction , double* PT,
						unsigned int countU,  double lLevel)
{

	//PREPARING DEP ARR IN DOUBLE ARRA
	double* depArr = new double [countU];
	for(unsigned int i=0 ; i < countU; i++)
	{
		depArr [i]= (double)m_dependentArr[i];
	}



//////////////////////////////////////////// ////////////////////" UNIVERSSAL GROUP VARIANCE DATA "
//seting isIn true for the    " baseVarDep"
	//defining the group to be the unives and sendind to the funcction for procesing
	
	bool* isIn = new bool [countU];
	for(unsigned int i=0 ; i < countU; i++)
	{
		isIn [i]=true;
	
	}
	
	double baseMeanDep = 0 ;
	double baseVarDep = 0;
	{
		double baseMedian=0;		
		double sumAllWeights = GetVarianceWithBoolArr(baseMedian, baseMeanDep, baseVarDep, depArr, m_predScoresAlt, 
										countU, isIn,  lLevel,0);
		double sdBaseDep = pow(baseVarDep,double(1/lLevel));
	}



///////////////////////DEFINING THE SIM K GROUP PREDICTION ANAD PERFORMACNE FIGURES /////////////////////
 	unsigned int predictKcount =  PREDICT_COUNT_SELECT_ALGORITHM_TTEST;//     PREDICT_K _COUNT_EVOLUTION;//cConfiguration::GetInstance()->GetPr edictKCount();

	for(unsigned int i=0 ; i < countU; i++)
	{
		if((i < predictKcount) )
		{
			isIn [i]=true;
	
		}
		else
		{
			isIn [i]=false;	
		}
	}

	//pgrade : so that this function will return the ex var, not the error, and that it will do it by calling few times to 
	// differentnn split of two functions. 
	double exVarSim =0;
	double meanProfileSim=0;
	{
	//	double simKmediann = 0 ;
	//	double simKtestMean=0;
	//	double simKtestVarr=0;
	//	double simPredShift = 0 ;
	//	double simKsqrErr = CalculateKgrouopStatistics12_10_13(simPredShift , simKmediann,   simKtestMean, simKtestVarr  , 
	//												depArr, m_predScoresAlt, 	countU, isIn,  lLevel,NULL);//,
	//												predictKcount , baseMeanDep , baseVarDep );

		exVarSim = CalculateKgrouopStatistics12_25_13(  meanProfileSim, depArr, m_predScoresAlt,  countU, isIn,  lLevel);//,baseMeanDep);//,  NULL);
	
		//exVarSim = (simKtestVarr - simKsqrErr) / simKtestVarr;

		
	}
	double simStrength = exVarSim ;
	

	if(PT == NULL)
	{
		delete []isIn;
		delete []depArr;
		percMeanInportance=1;
		prediction = meanProfileSim;
		return exVarSim;
	}

	////////////////////////////////////////////////////
	
//PREPARE BOOL ARRAY and similarity based strength factors group 1
	


//FIND THE PERCENTILE THAT HOLDS THE TOP SIM BASED ON KN  : predictionBaseEDpercntilen
	double* edPredBaseArr = new double[countU];	
	double predictionBaseEDpercntilen=0;
	{	
		
		for(unsigned int i=0 ; i < countU; i++)
		{//if the predictio of an item base on kn is from the farther group than we don't include it
			edPredBaseArr[i] = Abs(PT[i] - prediction);
		}
	
		for(unsigned int i=0 ; i < countU; i++)
		{
			isIn [i]=true;
		}

	//
	
		double predictionBaseEDmean= 0 ;
		double predictionBaseEDvar= 0 ;
		{
	
			GetVarianceWithBoolArr(predictionBaseEDpercntilen, predictionBaseEDmean, predictionBaseEDvar, edPredBaseArr, m_predScoresAlt,  
				countU, isIn , lLevel, predictKcount);
		}

	}
	///////////////////////////////////////////////

	//set the K group this time, a knn over prediction array sub group

	unsigned int tempPredPercentil = 0 ;
	for(unsigned int i=0 ; i < countU; i++)
	{//if the predictio of an item base on kn is from the farther group than we don't include it
		
		if((edPredBaseArr[i] <= (predictionBaseEDpercntilen + 0.5)))
		{
			isIn [i]=true;		
			tempPredPercentil ++;
		}
		else
		{
			isIn [i] = false;
		}
	}

	double meanProfilePrd=0;
	double exVarPrd=0; //same, return now ex var, not error, and by doing more than one split of two functions.
	{
	//	double prdKmedian = 0 ;
	//	double prdKTestMean=0;
	//	double prdKtestVar=0;
	//	double prdPredShift = 0;
	//	double prdKsqrErr = CalculateKgrouopStatistics12_10_13(prdPredShift , prdKmedian,   prdKTestMean, prdKtestVar  , 
		//											depArr, m_predScoresAlt, 	countU, isIn,  lLevel,NULL);//,
	//	//											predictKcount , baseMeanDep , baseVarDep );

	//	exVarPrd = (prdKtestVar - prdKsqrErr) / prdKtestVar;
		exVarPrd = CalculateKgrouopStatistics12_25_13( meanProfilePrd, depArr, m_predScoresAlt,  countU, isIn,  lLevel);// , baseMeanDep);//,  NULL);


	}
	double prdStrength = exVarPrd;
	
	
	unsigned int sizeLP = cConfiguration::GetInstance()->GetSizeOfLPGroupMedium();//SIZE_OF_LP_GROUP_SMALL;

	


	///////////////////////////////////////////////SIM LP GROUP PREDICTION 
	for(unsigned int i=0 ; i < countU; i++)
	{
		if((i < sizeLP) )
		{
			isIn [i]=true;
	
		}
		else
		{
			isIn [i]=false;	
		}
	}

	double meanLP = 0 ;
	double varDepLP = 0;
	{
		double median=0;		
		CutExtremtePredValuesToThresholdNotSymetric();//
					//  meanUniverse ,  varianceUniverse,  threshodForCenter,  expVal );
		for(unsigned int i=0 ; i < sizeLP; i++)
		{
			depArr [i]= (double)m_dependentArr[i];
		}
		double sumAllWeights = GetVarianceWithBoolArr(median, meanLP, varDepLP, depArr, m_predictabilityScores,// m_predScoresAlt, 
										countU, isIn,  lLevel,0);
		//double sdBaseDep = pow(baseVarDep,double(1/lLevel));
	}

	//either both less than 0 and we have two positive weights as outcome, 
	if((simStrength<0) && ( prdStrength < 0))
	{
		simStrength = (-1) / simStrength  ;//for exmaple -  -.01 will be 100 and -0.001 will be 1000   
		prdStrength = (-1) / prdStrength  ;
		percMeanInportance=  simStrength / (simStrength +prdStrength );
	}
	else if((simStrength==0) && ( prdStrength ==0))
	{
		simStrength=prdStrength=1;//should never happen that any of those is 0
		percMeanInportance=1;
	}
	else //at leasat one is positive. we zero the other one and have one pos weight
	{
		simStrength = Max(simStrength , double(0));
		prdStrength = Max(prdStrength, double(0));
		percMeanInportance = 1;
		if(prdStrength >0)
		{
			 percMeanInportance=  simStrength / (simStrength +prdStrength );
		}
	}
	
//to choose stronger the stronger one	
//	simStrength *= simStrength;
//	prdStrength *=prdStrength ;
	

	double newPrediction = 0;
	//meanLP   = meanProfileSim;
	meanProfileSim = meanProfileSim;
	if(IS_SELECT_ALGORITHM_ONLY_PER_SUB_GROUP)
	{
		simStrength = simStrength*simStrength;
		prdStrength = prdStrength*prdStrength;
	}



	if(IS_PROBABILITY_SELECTION_OF_ALGORITHM)
	{

		double **algorithSelectionTable;//[TABLE_DIM_SIZE ][TABLE_DIM_SIZE ];
		algorithSelectionTable = new double*[TABLE_DIM_SIZE ];
		for(unsigned int i = 0 ; i < TABLE_DIM_SIZE ; i++)
		{
			algorithSelectionTable[i] = new double [TABLE_DIM_SIZE ];
		}
		CalcualteTableWeightsForAlgoSelection( algorithSelectionTable); 
		GetTableWeightsForAlgorithSelection(simStrength ,prdStrength , 
			algorithSelectionTable , meanLP,meanProfilePrd );
		for(unsigned int i = 0 ; i < TABLE_DIM_SIZE ; i++)
		{
			delete []algorithSelectionTable[i] ;
		}
		delete []algorithSelectionTable;
		
	}
	if(cConfiguration::GetInstance()->GetIsOnlyProfilePrediction())
	{
		simStrength=1;
		prdStrength=0;
	}
	if( (simStrength + prdStrength )>0)
	{
		newPrediction = 	((  meanLP  * simStrength) +(meanProfilePrd*prdStrength)) / (simStrength + prdStrength );
		prediction = newPrediction;
	}
	
	
	 
	delete []isIn;
	delete []depArr;
	delete []edPredBaseArr;
//	delete []edPredictionBaseArr;
	return exVarSim;
}
	
	*/






void cStatisticStructure::GetCleanAverage ( double &cleanKaverage , 
	  float* cleanWeightedVarAvera,  double sumOfCohortScores, double kAverage, 
	    float* weightedVarAvg, float predictScore,  
		   double dependent,  short int* predictiveArr)
{
	
	cleanKaverage =    
		( kAverage  -  ((predictScore * dependent) / sumOfCohortScores ))
						* (sumOfCohortScores/(sumOfCohortScores - predictScore) );
	for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		cleanWeightedVarAvera[j] = 
		( weightedVarAvg[j]  -  ((predictScore * predictiveArr[j]) / sumOfCohortScores ))
						* (sumOfCohortScores/(sumOfCohortScores - predictScore) );

	}

	int fff=0;

}




void cStatisticStructure::AdaptBetaSet( cStatisticStructure* parentStat)
{
	m_regressionBetaZeroConstantTermWeight = 
						parentStat->m_regressionBetaZeroConstantTermWeight;
	for(unsigned int j=0; j< m_numOfPredictiveVars ; j++)
	{
		m_regressionBetaWeightArray[j] =  parentStat->m_regressionBetaWeightArray[j];
	}


}

/*
void cStatisticStructure::FillPredictionArr9_17_13(double &spPTps , double * PT,
										bool *ISc , unsigned int cohortCount, 
							unsigned int testGroupCount, 
							cStatisticStructure* parentStat)//, bool** edBas edAllowedItems)
{
	cohortCount = Min(cohortCount, m_count);
	testGroupCount= Min(testGroupCount, m_count);

	float kAverage = 0 ; //TODAY
	float varDep=0;
	float * weightedVarAvg = new float[m_numOfPredictiveVars];
	//PREDICT_K _COUNT_EVOLUTION 12 6 12 TO DO  1 10 13 add isInSimGroup as i n put for CalculateK averageAndWeightedVarAvg
	double sumOfCohortScores=0;
	CalculateKaverageAndWeightedVarAvg(kAverage, varDep,
		weightedVarAvg, sumOfCohortScores, cohortCount, 	NULL);//, edBase dAllowedItems);
		//cConfiguration::GetInstance()->GetPr edictKCount(), NULL);
		//(cConfiguration::GetInstance()->GetPredictKC ountEvolution()), NULL);//PREDICT_K_COUNT    );//popChgObj.GetKcount());
	
	
	float *betaArr = m_regressionBetaWeightArray;
	if(	parentStat)
	{
		betaArr = parentStat->m_regressionBetaWeightArray;
	}
	
	for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		PT[i]=0;
		if(ISc[i])//m_predictabilityScores[i]==0)
		{
			float cleanWeightedVarAvera[MAX_NUM_OF_PREDICTIVE_VARIABLES];
			double cleanKaverage=0;
			GetCleanAverage ( cleanKaverage , cleanWeightedVarAvera,
						sumOfCohortScores,kAverage, weightedVarAvg, m_predictabilityScores[i],
						m_dependentArr[i], m_predictiveArr[i]);
			
			float prediction= cleanKaverage;//kAverage; //9 24 13 remove the for loop 
			if(false)
			{
				for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
				{
					float 	betaWeight=betaArr[j];
					prediction += (betaWeight * 
						   ( (m_predictiveArr[i][j])-(cleanWeightedVarAvera[j] )   )    );//    weightedVarAvg[j] )   )    );
				}
			}
			PT[i]= prediction;
		}
	}*/

/*
		for( unsigned int i=0; i< testGroupCount;i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
		{
			PT[i]=0;
			if(ISc[i])//m_predictabilityScores[i]==0)
			{
				float cleanWeightedVarAvera[MAX_NUM_OF_PREDICTIVE_VARIABLES];
				double cleanKaverage=0;
				GetCle anAverage ( cleanKaverage , cleanWeightedVarAvera,
						sumOfCohortScores,kAverage, weightedVarAvg, m_predictabilityScores[i],
						m_dependentArr[i], m_predictiveArr[i]);
			
				float prediction= cleanKaverage;//  kAverage;
				if(!isToPredictOnlyMean)
				{
					for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
					{
						float 	betaWeight=m_regressionBetaWeightArray[j];
						prediction += (betaWeight * ( (m_predictiveArr[i][j])-
							                  (cleanWeightedVarAvera[j] )   )    ); //  (weightedVarAvg[j] )   )    );
					}
				}
				PT[i]= prediction;
			}
		}
		


*/


	/*double predictionSP = kAverage;

	//9 24 13 remove the for loop 
	if(false)
	{
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			double 	betaWeight = (double) betaArr[j];
			predictionSP +=  (betaWeight * ( (m_predictive_set[j])-(weightedVarAvg[j] )   )    );
			//(betaWeight * ((double)m_predictive_set[j]));
		}
	}
	spPTps = predictionSP;
	
	delete []weightedVarAvg;


}
*/









void cStatisticStructure::FillRealArr(double *realValArr)
{
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		realValArr[i] = ((double)m_parentThis->m_dependentArr[i]) ;
	}
}

/////////////////////////////8 15 12 end



/*
void cStatisticStructure::CalculateEditDistanceControlFlaggedAndControlOthers(float *cntrFlgedVarValArr, 
															float *cntrOthersVarValArr, cSimilarityFormula & newFormula)
															
{
	unsigned int simCount= newFormula.GetCount();
	float weightOfControlFlaggged = 0 ;
	float weightOfControlOthers = 0 ;
 	for( unsigned int i=0; (i<  m_count ); i++)//-1 sincne if taking score from next one, make sure there is a next one. but we are not supposed to get there if k control small enough
	{
		float weightOfControlItem = m_parentThis->m_predictabilityScores[i];
		if((weightOfControlItem == 0.0f))// && ((i+1) < count ))
		{
			//weightedScore = m_parentThis->m_predScoresAlt[i];
			weightOfControlItem = m_parentThis->m_predScoresAlt[i];//m_predictabilityScores[i+1];
			if	( i < (cConfiguration::GetInstance()->GetP redictKCountEvolution()))
			{ //FROM HERE
				weightOfControlFlaggged += weightOfControlItem;
				UpdateAllVarialbeVals(cntrFlgedVarValArr, m_predictiveArr[i], weightOfControlItem, newFormula);
			}
			else
			{
				weightOfControlOthers += weightOfControlItem;
				UpdateAllVarialbeVals(cntrOthersVarValArr, m_predictiveArr[i], weightOfControlItem,  newFormula);
			}
		}
	} 

	if( weightOfControlFlaggged>0)//31.8
	{
		for(unsigned int j=0; j< simCount ; j++)//,,,flaggedSumSimVariablesValArr[j]
		{
			cntrFlgedVarValArr[j]/= weightOfControlFlaggged;
		}
	}
	if( weightOfControlOthers>0)
	{
		for(unsigned int j=0; j< simCount ; j++)//,,,flaggedSumSimVariablesValArr[j]
		{
			cntrOthersVarValArr[j]/= weightOfControlOthers;
		}
	}
	
}


*/





/*
void cStatisticStructure::FillZeroPredictibilityScores()
{
	for(unsigned int i= 0; i< (m_count-1) ;i++)
	{
		m_predictabilityScores[i]= Max(m_predictabilityScores[i],m_predictabilityScores[i+1]);
	}
}
*/




/*
this function goes over one cValueBuckets , over all buckets slots, and calculate by doing that 
the weights edit distance averge from the entire collection, to the subject person specific predictive val input.
*/
/*
void cStatisticStructure::CalculateEDmea nOneDimension(float &edMean,float predictiveValInput ,cValueBuckets &buckets)
{
		edMean =0;
		float sumOfAllWeights =0;
	//	float predictiveValInput = ((float)predictiveSet[j])/100.0f ;
		for( unsigned int k = 0 ; k < buckets.GetCount() ; k++)
		{//for each var j we will count all columns of var j values in the regression stat with each weight
			float weight = buckets.GetBucketWeight(k) ;
			float predictiveValueBuckets = cValueBuckets::GetPredictiveValueFromIndex (k);
			edMean += (weight * ( Abs(predictiveValInput - predictiveValueBuckets)     )); 
			sumOfAllWeights += weight ;
		}
		edMean /= sumOfAllWeights;
}
*/
/*
void cStatisticStructure::Calcu lateEDmean( float *edMean, cSimilarityFormula &similarity, short int * predictiveSet)
{
	
	for(unsigned int j=0 ; j< similarity.GetCount() ; j++)
	{
		float predictiveValInput = ((float)predictiveSet[j])/100.0f ;
		CalculateED meanOneDimension(edMean[j],predictiveValInput ,m_ValBucketArr.GetBucketsItem(j));//m_buckets[j]);
	}

}
*/



/*
void cStatisticStructure::CalculateEDVariance( float *edVariance, cSimilarityFormula &similarity, short int * predictiveSet)
{
	
	//build arrays:
	float *meanEDs = new float[similarity.GetCount()]; 

	Calcula teEDmean(meanEDs, similarity, predictiveSet);
	
	for(unsigned int j=0 ; j< similarity.GetCount() ; j++)
	{
		edVariance[j] =0;
		float sumOfAllWeights =0;
		for( unsigned int k = 0 ; k < m_buckets[j].GetCount() ; k++)
		{//for each var j we will count all columns of var j values in the regression stat with each weight
			//meanEDs[j] += 
			float predictiveSetInputVal =  ((float)predictiveSet[j])/100.0f ;
			float predictiveSetBucketSlotVal = cEDbucket::GetPredictiveValueFromIndex (k) ;
			float edOfInputFromSlot =// (  (m_buckets[j].GetBucketWeight(k) ) * 
								Abs( predictiveSetInputVal - predictiveSetBucketSlotVal );
		//	float ed = (  (m_buckets[j].GetBucketWeight(k) ) * 
		//						(Abs( (  ((float)predictiveSet[j])/100.0f) - cEDbucket::GetPredictiveValueFromIndex (k)) ));
			float shiftOfEDslotFromMeanED = Abs(edOfInputFromSlot - meanEDs[j]);
			edVariance[j] += shiftOfEDslotFromMeanED * (m_buckets[j].GetBucketWeight(k));//Abs(ed - meanEDs[j]);
			sumOfAllWeights += m_buckets[j].GetBucketWeight(k);
		}
		edVariance[j] /= sumOfAllWeights;
	}

		//now we got the average ed due to this portion of each dimension. to combine it with . 
		
//		if we get for example 99% of weighting/cases that are different to the subejct person, 
//		like a 1 val of the subect person in in ai 0/1 workld, and 1% that is 1 exact match o nly,
//		than the sum of ED here will be large in the case of suvbject person 1 than of 0, as the average
//		distance is usualy in the 1 range. but what we want to see is how that ed distinguish the persons so that
//		you take some to be near by and others further away. in this regard, if we use the method of pop change
//		we will get a low score to this case, same if the person is 0 or 1, and higher scores to the case where we get
//
//		in the case of on average smaller
//		if we increase the wegiht of the var j, due to more cases of

	delete []meanEDs;
	
}
*/


/*

we are going to fill p different collections, virtual ones, for each one we will want to konw how much did 1%
of change effects the change in ed average. 
to change that 1% we will, for each person i:

get its predictivlity score, which is a consequence of 
orifinalrED = ReverseScore(score(person i) );
ed1s1 + ed2s2 ...    .         =   orifinalrED;
if we have collection 0 different in 1 percent over 0 variable that we have our new score to be:
ed0 * (s0+0.01)  + ed1 * s1 + ......
and that will make our new ed to be 
orifinalrED += ed1*0.01 ;
and the score would be 
float newScore = GetScoreFromOriginal (orifinalrED)

Algorithm Notes 10 22 12
and that new score will be when our person i was tested how would a collection with diff in var 0 behaves.
and object 0 will then get a mean ed, to be tested against the complete ed. the diff between these two 
eds will go to our var 0 sensativity.
we better get for every person i, and update to p diff collections, with p variations in the corresponding var.
for every person up to N

	first, if not already with ED bueckts, make UpdateValueBucketArray (predicivlityScore[i], index?) 
	for every var, to p 
		newScore = GetScoreBasedOnVarAdjustement (j)
		GetCollection(j).UpdateValueBucketArray (newScore, index?)
		

now we have every collection evidanc e about N persons and devided into buckets. like SetEdBuckets or something like that
and then 
*/

void cStatisticStructure::UPdateValueBucketArrOnePerson( cValueBucketsArr & valueBucketArr, float predictScore,
																						unsigned int i)
{
	for (unsigned int j=0 ; j < valueBucketArr.GetCount() ; j++) // PRIORITY 
	{
		UPdateOneValueBucketObjForOnePerson( valueBucketArr.GetBucketsItem(j),
												 predictScore,  i,  j);
//		float predictiveVal = ( float)m_predictiveArr[i][j];
//		predictiveVal /= 100.0f;
//		unsigned int index =  cValueBuckets::GetIndexFromPredictiveValue(predictiveVal);
//		valueBucketArr.GetBucketsItem(j).IncrementBucketSlot( predictScore , index);
	}
}


void cStatisticStructure::UPdateOneValueBucketObjForOnePerson( cValueBuckets & valueBucket,
												float predictScore, unsigned int i, unsigned int j)
{
//	for (unsigned int j=0 ; j < formula.GetCount() ; j++) // PRIORITY 
//	{
		float predictiveVal = ( float)m_predictiveArr[i][j];
		predictiveVal /= 100.0f;
		unsigned int index =  cValueBuckets::GetIndexFromPredictiveValue(predictiveVal);
		valueBucket.IncrementBucketSlot( predictScore , index);
//	}
}

/*
			CalculatePrediction_7_5_14() will check fro all cohort (non test) group,
			the mean dep using edItoIIperJ[i][ii][j] times stghtFor.getweight[j], 
			will be using parentStat-<predictScores for weights 

			*/
















//numOfControlGroup will serve to determine the highers index value that is allowed for control group in initielize
//structure, in order to know how deep to zero the predictibility values for some mode. right now we either send 
//0 or 50000 for highest value as a defauly.

/*
cStatisticStatCover::cStatisticStatCover(unsigned int count,unsigned int numOfPredictiveVars,
		unsigned int numberOfWhatIfFields, unsigned int kCount, unsigned int kControlCount,
		unsigned int resultIndex , cTargetSort & targetSort , cProfileTarget * subjectTarget,
		bool  isLearningTime, float constantScoreWeight, unsigned int numOfControlGroup, bool isControlGroup,
		double * meanArr, double * varianceArr, cStatisticStructure * parentStat, bool isToNormelizeInput,
		 double  exponentialConstant,unsigned int* dynamicPosArr, unsigned int dynPosArrSize )//cConfiguration::GetInstance()->GetEx ponentialEditDistanceScoreConst())
{
	m_wivCount = count; //will get num of what if variations
		// TO DEBUG
	m_statArr = new cStatisticStructure*[m_wivCount ];
	for (unsigned int j = 0; j < m_wivCount ; j++)
	{
		m_statArr[j] = new cStatisticStructure(LINEAR);
	//	m_statArr[j]->SetData(targetSort.GetRealCount(), //GetWhatIfArrayCount(j), 
//numOfPredictiveVars,numberOfWhatIfFields,kCount, kControlCount,  parentStat);
				// cConfiguration::GetInstance()->GetNumOfPredictiveVars(0) need to change 0 to target field index
	}
		//will execute several regressoins, per each what if variatoin, and will store the regression output in the statAtt[j]
		
	
	StatisticProcess( targetSort , PREDICTIVE_STATISTIC_CHECK , resultIndex ,subjectTarget, 
		   kCount, kControlCount,  
		   isLearningTime,constantScoreWeight,
		   numOfControlGroup, isControlGroup, meanArr,  varianceArr , isToNormelizeInput, exponentialConstant ,
		    dynamicPosArr,  dynPosArrSize, NULL); //cConfiguration::GetInstance()->GetExpone ntialEditDistanceScoreConst());
		
		
		
		//this function does the K portion of the K-N algorithm for each of the performance objects in this loop. the  K-N algo score will be the output. 
//PRAR-1 here you should close this function before we go into debugging it	. just don't call this line.
//		float tempScore = CalculatePerfo rmance(statArr, targetSort.GetWhatIfWeights());
	
		
//		performanceList.GetItem(i).SetPerformanceScore(tempScore);

}

*/

cStatisticStatCover::~cStatisticStatCover()
{
	for (unsigned int i = 0 ; i < m_wivCount; i++)
	{
		delete m_statArr[i]; m_statArr[i] = 0;
	}
	delete[] m_statArr; m_statArr = 0;
}

void cStatisticStatCover::DistributeSamplePtrs(cStatisticStatCover &newCover)
{
	for (unsigned int i = 0 ; i < m_wivCount; i++)
	{
		newCover.m_statArr[i]->m_predictiveArrSamplePtr = 
					m_statArr[i]->m_predictiveArrSamplePtr = &(m_statArr[i]->m_predictiveArr);
		newCover.m_statArr[i]->m_dependentArrSamplePtr = 
					m_statArr[i]->m_dependentArrSamplePtr = &(m_statArr[i]->m_dependentArr);
		newCover.m_statArr[i]->m_predictionArrSamplePtr  =
					m_statArr[i]->m_predictionArrSamplePtr = &(m_statArr[i]->m_predicted_dependentArr);
		newCover.m_statArr[i]->m_parentThis = m_statArr[i]->m_parentThis = m_statArr[i]; 

	}
}



/*

void  cStatisticStatCover::Linear Regression(float &averageSE ,float &variance,float &predictiveVariance,
											float * similarityFlags, 
											unsigned int simVarCount, double *allListVarianceArr, double * universalRegVarianceArr)
{
	m_statArr[0]->LinearRegres sion(averageSE ,variance,predictiveVariance,similarityFlags, simVarCount,universalRegVarianceArr);// will 

}
*/




//10 25 16








cMedian::cMedian(unsigned int size)
{
	m_weightsArr = new float[size];
	m_size = size;
	for(unsigned int i=0; i<size ; i++)
	{
		m_weightsArr[i]=0;
	}

}

cMedian::~cMedian()
{
	delete []m_weightsArr;
}
void cMedian::Add(float weight, float value)
{
	unsigned int index = GetIndexFromValue( value);
	m_weightsArr[index] += weight;
}



unsigned int cMedian::GetIndexFromValue(float value)
{
	int tempVal = (int)value;
	tempVal += (m_size/2);
	if(tempVal < 0)
		tempVal =0;
	if(tempVal > ((int)(m_size-1)))
		tempVal = (int)(m_size-1);
	return (unsigned int) tempVal;	
}

float cMedian::GetValueFromIndex( unsigned int index)
{
	int temp = int(index);
	return float(temp - ((int)(m_size/2)));
}

#define PERCENTILE_EXTREME 0.03 //from each side, 3 percent will be ignored

/*
float cMedian::GetTradAverage(float sumOfweights, float average)
{
	float threW = sumOfweights * PERCENTILE_EXTREME;
	float edgeOfLowScores = 0 ;
	float lowEdgeAveragre = FindAverageOfEdge ( edgeOfLowScores, threW , 0 ); //0 is from the low edge. 1 is from the high edge
	
	float edgeOfHighScores = 0 ;
	float highEdgeAverage = FindAverageOfEdge ( edgeOfHighScores, threW , 1 );  //0 is from the low edge. 1 is from the high edge
	
	float averageInIndexForm = GetIndexFromValue(average);
	float tradAverage = (( averageInIndexForm * sumOfweights) - ((lowEdgeAveragre +highEdgeAverage)*threW)) / 
																						(sumOfweights- (2*threW));
	tradAverage = GetValueFromIndex(tradAverage);
	return tradAverage;

}	
*/
float cMedian::FindAverageOfEdge ( float edgeOfLowScores, float threW , int lowEdgeOrHighEdge )
{
	float ongoingSum = 0 ;
	float sumOfValues = 0 ;
	unsigned int edgeIndex=0;
	bool end = false;

	if(lowEdgeOrHighEdge ==0)
	{
		int i=0;
		while((i < ((int)m_size) )&&(!end))
		{
			if(m_weightsArr[i]>0)
					int dddd=0;
			ongoingSum += m_weightsArr[i]; //coungin the weight till threW or a bit more
			sumOfValues += m_weightsArr[i] * i; //counting the sum of values times weight (i is a bucket representing value)
			if(ongoingSum >= threW)
			{
				end = true;
				edgeIndex =i;
			}
			i++;
		}
	}
	if(lowEdgeOrHighEdge ==1)
	{
		int i=m_size-1;
		while((i >= 0 )&&(!end))
		{
			if(m_weightsArr[i]>0)
					int dddd=0;
			ongoingSum += m_weightsArr[i]; //coungin the weight till threW or a bit more
			sumOfValues += m_weightsArr[i] * i; //counting the sum of values times weight (i is a bucket representing value)
			if(ongoingSum >= threW)
			{
				end = true;
				edgeIndex =i;
			}
			i--;
		}
	}

	float extraDif = ongoingSum - threW;
	sumOfValues -= (extraDif*edgeIndex) ;// the responsible for the diff is the edgeIndex where the wieght is passing
									//the threshold. then, that dif times the value which is the index will get decreased.
	return sumOfValues / threW ;
}



float cMedian::GetMedian(float sumOfweights)
{
//	float threW = sumOfweights * PERCENTILE_EXTREME;
	//find at which index does it happen that we reached the 50% of sumOfWeights. start from begining. 	
	float ongoingSum = 0;
	int i = 0 ;  //need to be int since we have a stop below when we get to negative numbers
	unsigned int medianFromBottom=0;
	bool end = false;
	while(  (i < (int(m_size)) )&&(!end))
	{
		ongoingSum += m_weightsArr[i];
		if(ongoingSum >= (sumOfweights/2.0f))
		{
			end = true;
			medianFromBottom = i;
		}
		i++;
	}
	//find at which index does it happen that we reached the 50% of sumOfWeights. start from the end. 	
	ongoingSum = 0;
	i = m_size -1 ; 
	unsigned int medianFromTop=0;
	end = false;
	while((i >=0 )&&(!end))
	{
		ongoingSum += m_weightsArr[i];
		if(ongoingSum >= (sumOfweights/2.0f))
		{
			end = true;
			medianFromTop = i;
		}
		i--;
	}
	unsigned int medianIndex =   (medianFromBottom+ medianFromTop ) / 2 ; 
	return GetValueFromIndex( medianIndex) ;
}
//EEEEEEEEEEEEEEE





//cValueBucketsArr
void cValueBucketsArr::CalculateEDmeanOneDimension(double &edMean,float predictiveValInput ,cValueBuckets &buckets)
{
		edMean =0;
		float sumOfAllWeights =0;
	//	float predictiveValInput = ((float)predictiveSet[j])/100.0f ;
		for( unsigned int k = 0 ; k < buckets.GetCount() ; k++)
		{//for each var j we will count all columns of var j values in the regression stat with each weight
			float weight = buckets.GetBucketWeight(k) ;
			float predictiveValueBuckets = cValueBuckets::GetPredictiveValueFromIndex (k);
			double temp = ( ABS(predictiveValInput - predictiveValueBuckets)     );
			temp = pow(temp , CONSTANT_FOR_ED_MEAN_POW);
			edMean += (weight * temp); 
			sumOfAllWeights += weight ;
		}
		if(sumOfAllWeights > 0)
		{
			edMean /= sumOfAllWeights;
		}
		else
		{ 
			edMean = 0 ;
		}
}



////////////////////////////////////6 28 14






//////////////////////////////////////

cMapingPreArr::cMapingPreArr( cStatisticStructure* stat)
{
	m_stat = stat;
	m_count = m_stat->m_count;
	m_numOfPredictiveVars = m_stat->m_numOfPredictiveVars;
	m_meanReplacedVar = new double[m_numOfPredictiveVars ];
	m_sdReplacedVar = new double[m_numOfPredictiveVars ];

	m_replacedPredTwoDim = new double*[m_count] ;
	
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		m_replacedPredTwoDim[i] = new double[m_numOfPredictiveVars ]; 
		
		for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
		{
			m_replacedPredTwoDim[i][j] = 0.0; 
			
		}
	}
	m_categoMaptingBucket = new double*[m_numOfPredictiveVars ];//[MAX_SIZE_OF_PRED_VALUE]
	for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
	{
		m_categoMaptingBucket[j] = new double[MAX_SIZE_OF_PRED_VALUE];
		for(unsigned int ii = 0 ; ii < MAX_SIZE_OF_PRED_VALUE ; ii++)
		{
			m_categoMaptingBucket[j][ii] = 0 ; 
		}
	}
	//CreateMappingAllVariables();
	//ReplaceTwoDimPredWithCategoryMean( );//categoMaptingBucket, replacedPredTwoDim);
}


/*
void cMapingPreArr::FillPredictionArr( double* predArr, short int** testPredSet, unsigned int count)
{
	for(unsigned int i = 0 ; i < count ; i++)
	{
		predArr[i] = CalcualtePredictedValue( testPredSet[i]);
	}
}

*/






void cMapingPreArr::FillStrengthArr(double* strengthArr)
{
	for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		double tempBeta = m_stat->m_regressionBetaWeightArray[j];
		/*double mappedVAlue = m_stat->m_predictive_set[j];
		if( cConfiguration::GetInstance()->IsCategoricalVariable(j))
		{
			mappedVAlue = m_categoMaptingBucket[j][m_stat->m_predictive_set[j]];
		}
		double temp = tempBeta * mappedVAlue ;*/
		double temp = tempBeta * m_sdReplacedVar[j] ;
		strengthArr[j] = cVarianceCalc::Abs(temp);
			//midSizeRegObj.GetStat()->m_regressionBetaWeightArray[j] * 
		//									midSizeRegObj.GetStat()->m_predictive_set[j];
		//regBasedSim.SetWeight(Abs(strengthArr[j]), j);
	}
}




/*
void cMapingPreArr::ReplaceTwoDimPredWithCategoryMean()
{
	for(unsigned int j = 0 ; j < m_numOfPredictiveVars ; j++)
	{
		int countArr[MAX_SIZE_OF_PRED_VALUE ];
		for(unsigned int ii = 0 ; ii < MAX_SIZE_OF_PRED_VALUE ; ii++ )
		{
			m_categoMaptingBucket[j][ii] = 0.0;
			countArr[ii]=0;
		}
		if( cConfiguration::GetInstance()->IsCategoricalVariable(j))
		{
			for(unsigned int i = 0 ; i < m_count ; i++ )
			{
				int bukSlot = m_stat->m_predictiveArr[i][j];
				if(bukSlot < 0 )
				{
					bukSlot =0; 
				}
				else if(bukSlot >= MAX_SIZE_OF_PRED_VALUE )
				{
					bukSlot = MAX_SIZE_OF_PRED_VALUE -1;				
				}
				countArr[bukSlot ] ++;
				m_categoMaptingBucket[j][bukSlot ] += ((double)m_stat->m_dependentArr[i]);
			}
			for(unsigned int ii = 0 ; ii < MAX_SIZE_OF_PRED_VALUE ; ii++ )
			{
				if(countArr[ii] > 0 )
				{
					m_categoMaptingBucket[j][ii] /= countArr[ii];
				}
			}
		}
		m_meanReplacedVar[j] = 0 ;
//	double* m_sdReplacedVar
		for(unsigned int i = 0 ; i < m_count ; i++ )
		{
		//	int bukSlot = m_stat->m_predictiveArr[i][j];
		//	double mapedVAlue = m_categoMaptingBucket[j][bukSlot ];
			double mappedVAlue = m_stat->m_predictiveArr[i][j];
			if( cConfiguration::GetInstance()->IsCategoricalVariable(j))
			{
				mappedVAlue = m_categoMaptingBucket[j][m_stat->m_predictiveArr[i][j]];
			}
			m_replacedPredTwoDim[i][j] = mappedVAlue ; 
			m_meanReplacedVar[j] += m_replacedPredTwoDim[i][j] ;
		}
		m_meanReplacedVar[j] /= m_count;
		m_sdReplacedVar[j] = 0 ;
		for(unsigned int i = 0 ; i < m_count ; i++ )
		{
			double temp = m_replacedPredTwoDim[i][j] - m_meanReplacedVar[j] ;
			m_sdReplacedVar[j] += temp*temp;
		}
		m_sdReplacedVar[j] /= m_count;
		m_sdReplacedVar[j] = pow(m_sdReplacedVar[j] , 0.5);

	}

}
*/





cMapingPreArr::~cMapingPreArr()
{
	for(unsigned int i = 0 ; i < m_count ; i++)
	{
		delete []m_replacedPredTwoDim[i] ; 
		
	}
	delete []m_replacedPredTwoDim;


	for (unsigned int j = 0 ; j < m_numOfPredictiveVars ; j ++)
	{
		delete [] m_categoMaptingBucket[j] ;
	}
	delete []m_categoMaptingBucket;

	delete []m_meanReplacedVar;
	delete [] m_sdReplacedVar;
}

