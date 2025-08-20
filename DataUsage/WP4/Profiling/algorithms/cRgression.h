#pragma once


//#define _DEBUG2


//onlt for debug
#define NUM_OF_ITERATION 20//10//10//8 16 15 30//40//20//30//60//1// 2//80//80// 80//3//5//80//10
#define COUNT_OF_PROCESSING_GROUP 25000//4500//3600// 3600//4140//#define
#define IS_LOGISTIC_REGRESSION true

#define SIZE_OF_QUICK_HASH 50000000
#define IS_PERF_TESTS_TO_DEVIDE_BY_SD true
#define CONST_SD_RANGE_LIMIT 10//2.5
#define IS_CONVERT_PERF_TEST_TO_POS_SD false


#define AT_LEAST_X_PARTS_SIM 15//11//16//1 3 15 changed from 12//10  //1 3 16 chagned from 10 to 30
#define SIZE_OF_PARTS 20//30//1 5 16 20  //12 24 15 chaned from 20
#define NUM_OF_CHD_PARTS_ONE_ITERATION 5//2//1 3 16 changed from 2. //2// 5//6//8 //5//12 14 15 changed fom 5 an
//if set it too low the   (AT_LEAST_X_PARTS_SIM * SIZE_OF_PARTS )
#define PERC_OF_EVOLUTION_K_FOR_SIMGRP 0.1

#define PERC_OF_HIGHEST_WEIGHT_AS_SIM_THRESHOLD 0.6//0.8


#define IS_NEW_FLAGGED_SIM_EVOL false//true//false

#define IS_WITH_RANDOM_EVOL true//false//true


#define EXP_CONST_WEIGHTING_MULTIPLE_EVENTS_PER_ITEM 0.7//85//0.8

//how to control size of profile in the end of get best formula. for exmpae, false + 0.0 will be no clean.
// the min size can be a guard that says, take out low thredhosl values but as long as we keep the top X values
#define IS_WITH_HOMOG_SCORING_TEST_GEET_BEST_FOR false
#define THRESHOLD_FOR_TOO_LOW_SIM_VARIABLE 0.5//0.2//0.5//2//0.6//1 4 16 0.3//0.2
#define MIN_SIZE_SIM_FORM_FOR_PROFILE 10

#define CONST_WEGITH_PERF_MULTI_EVENTS 2.0


#define IS_TO_WEIGHT_BY_ALL_REG_PERF false
#define CONT_WEIGHT_ALL_REG 0.0 // if above is true this can tune agressiveness of weight


#define MAX_NUM_OF_ALLPARTS_NUM 70

#define NUM_OF_EXTANDED_GROUPS 5

//#define MAX_SIZE_SIM_FORM_FOR_PROFILE 25

//#define MAX_NUM_OF_ITEMS_FOR_HOMOG_TEST 10000



#define MAX_SIM_PART_FOR_EXACT_POS_SLECTION 10 //should be at least 1 mor thatn thet AT_LEA ST_X_PARTS_SIM 

//(MAX_SIM_PART_FOR_EXACT_POS_SLECTION * (MAX_SIM_PART_FOR_EXACT_POS_SLECTION -1) )/2
#define NUM_OF_ITERATIONS_HOM_TEST 30//50//20//1 3 16 changed from 30 to 20 //30


#define NUM_OF_TIMES_USING_ONE_CHD_ITEM 3//5//3//5//10//2  //12 31 15

#define SAVING_RANDOM_MODE 1
#define TOO_LARGE_TO_OPEN_SELECTION_ARR 1000000// 10000//1500







#define NUM_OF_BASE_PARTS_ONE_ITERATION 20//7//20//8// 15//5//15//7//10
//for end of get best formula
#define NUM_OF_SIMILAR_FOR_HOMG_TEST_PARTS 2//8
#define NUM_OF_BASE_FOR_HOMG_TEST_PARTS 20  //12 14 15  changed form 15






/////////////////////////////////////////////////////////////
//12 28 15 2 fix the end Devi dePerf2dToPerf2dCount end of meta function to the corresponding strategy of this function

//12 28 15 3 : selecti yes or no to go for 
#define IS_TYPE_12_28_15 false
//12 28 15 4
#define IS_SIZE_OF_ALL_ITEM_SAME_AS_OF_CHD false



////////////////////////////////////////////////////////////////



#define IS_OPTION_HOMOG_TEST 1//4//3//2//1



#define MAX_NUM_OF_HOMG_TST_ITERATION 20
#define SAMPLE_SIZE_SIM_GRP_FOR_RISK_GRPS 50




//5 //12 24 15 changed from 3 //12 28 15 check if it is not better to incre it 
#define MAX_NUM_OF_USING_ONE_CHD_ITEM 30//10

//#define NUM_OF_PARTS_GATHER_FOR_TEST 1
/*
#define NUM_OF_CHD_PAR TS_ONE_ITERATION 5 //12 14 15 changed fom 5 an
#define NUM_OF_BASE_PARTS_ON E_ITERATION 10
//for end of get best formula
#define NUM_OF_SIMILAR_FOR_HOMG_TEST_PARTS 8
#define NUM_OF_BASE_FOR_HOMG_TEST_PARTS 12  //12 14 15  changed form 15
*/







#define MIN_NUMB_OF_PARTS 5



#define IS_UPDATE_SIM_FORMULA_PER_FINAL_HOMOG_SCORE true



#define RECOMENDED_MIN_COVERAGE_RESEARCH_PROFILE 0.8
#define MIN_AVG_COVERAGE_FPR_RESEARCCH_PROFILE 0.9
#define UNDER_COVERAGE_THRESHOLD  0.1

#define NO_INTERVENTION_CODE -1
#define LOW_INTERVENTION_CODE 0
#define HIGH_INTERVENTION_CODE 1

#define RECOMENDED_HOMOG_TEST_SIZE 500

#define IS_WITH_ADKUST_DEP_ARRR false

#define MAX_SD_UNITS_FOR_SIM_ED_IN_SD 10.0

#define SIZE_OF_TEST_PART 50
#define NUM_OF_PARTS_CHD_COHORT 5
#define RECOMENDED_NUM_OF_USAGE_PER_ITEMS_AACROSS_LEADERS 5 
#define NUM_OF_PAARTS_PNT_SIM_ARR 10

#define MAX_SIZE_OF_TSORT_FOR_FINAL_CALCULATIONS 1000000

#define MIN_REG_PERFORMANCE_BEFORE_ADJUSTING 0.5

#define MAX_NUM_OF_LEADERS_EVOLUTION 50
#define MAX_NUM_OF_LEADERS_OUTPUT 50
#define MAX_NUM_OF_HOMGENTY_TEST_OUTPUT 10

#define IS_RESEARCH_MODE true
#define MIN_PERC_SIM_FOR_RESEARCH 0.6
#define TARGET_SIM_FOR_RESEARCH 0.8
#define MIN_DIF_OF_MEAN_K_IN_SD 0.2
#define X_RESEARCH_VAR_MIN 3
#define Y_RESEARCH_VAR_MAX 10


#define SIZE_OF_PARTT 20


#define NUM_OF_RISK_GRP_EVOLU_PARTS 1 //for now only 1 and 2 are an option
#define NUM_OF_RISK_GRP_OUTPUT 1
#define NUM_OF_SERVICE_BASED_EVOLU_PARTS 2 //for now o nly 1 and 2 are options
#define IS_WITH_SIM_AND_SERVICE_WEIGHT_TEST_TO_COHORT false


/*
EVOLUTION_PERF_METHOD_TYPE
1:
	only chd vs cohort per risk (fromPntRisktoChd )
2:
	and sometimes it is the multipication of fromPntRisktoChd and fromPntToPntRisk
3:
	and sometimes , if tehre is only one risk kgroup so that means we can just take the higher level pnt and
	compare	to the chd right away.

	if NUM_OF_RISK_GRP_EVOLU_PARTS == 1 than EVOLUTION_PERF_METHOD_TYPE should set to 3


*/
#define EVOLUTION_PERF_METHOD_TYPE 1//if we used 1 need to try also opening the below to be true. if we used 2 than dont 
#define IS_WITH_WEIGHT_OF_PREDICTIABIOTY_EVOLUTION false
#define PROPORTION_OF_RISK_ED_FROM_SERVICE 0.0 //normally it shoudl be 0.5


/*
test 1 - NUM_OF_RISK_GRP_EVOLU_PARTS = 1 and
EVOLUTION_PERF_METHOD_TYPE 3 is forced
 IS_WITH_WEIGHT_OF_PREDICTIABIOTY_EVOLUTION false
#define PROPORTION_OF_RISK_ED_FROM_SERVICE 0.0

test 2 - increae risk groups NUM_OF_RISK_GRP_EVOLU_PARTS to 2 and EVOLUTION_PERF_METHOD_TYPE = 1, decide then

test 3 - cosider the EVOLUTION_PERF_METHOD_TYPE to 2

test 4  - PROPORTION_OF_RISK_ED_FROM_SERVICE can be  0.5 instead o 0. and in orer for that to be active need 
	update the  function with the ii wegihts.
	open IS_WITH_SIM_AND_SERVICE_WEIGHT_TEST_TO_COHORT to be true. 
	11 8 15 needs development

if NUM_OF_RISK_GRP_EVOLU_PARTS == 1 than EVOLUTION_PERF_METHOD_TYPE should set to 3
*/

#define MAX_NUM_OF_EVOLUTION_MEMBERS 10000

#define IS_CLEANING_NOT_FULL_WEIGHTS false
#define PERC_SIMILAR_FOR_RESEARC_PROFILE 0.6
#define MAX_RESEARCH_VAR_NUM 6

#define CONST_ADD_TO_SIM_SCORES_IN_SD 1.0



//9 28 15 6  define  changed from 6 to 1. 
#define NUM_OF_ROUNDS 4//1//6//1//3


#define MIN_ACTIVE_ITEMS_EVOLUTION 61//160//120//70//120 //60




#define IS_USE_OF_VERSION_SP_SIM_FORMULA_EVOLUTION false//true

#define CONST_SIM_SCORE 0.2

#define CONST_SERVICE_STRENGTH 0.2

#define MIN_NUMBER_OF_PARTS 3//2

//for risk adjustment
#define MIN_SAMPLE_SIZE_SIM_GRP_EVOL 100//50

#define CONST_ADDITION_TO_CALC_SCORE 2.0
#define IS_DEFINED_WITH_PRICE_SIZE false

#define IS_WITH_SERVICES false


#define IS_WITH_WEIGHTED_METHOD_PARTS true//false //true//false
#define IS_WITH_FOCUS_ON_SIM_GRP_TEST_ITEMS true//false //true//false




#define IS_SAVING_SEARCH_TIME true  //9  28 15 turn both lines true into false
#define IS_WITH_REDUCING_PERMUTATIONS_EVOLUTION true// 11 24 14 false//11 6 14 false//true// false//10 20 14 //true
#define TOTAL_COMBINATIOSN_FOR_PRED_MANIP_K 1500//7 29 15 //1300

#define IS_PERFORMANCE_SET_FOR_MAX_PER_ITEM false//true//false
#define IS_GOING_AFTER_INDIVIDUAL_ITEMS false



#define IS_ONLY_POSITIVE_HOMG_TEST_STORED false
#define IS_MULT_PERF_TEST_BY_SIZE_OF_SUB_GRP false


#define IS_WITH_PER_ITEM_COMPARATIVE true//false
#define CONST_OF_POP_SIZE_CONSIDERATION 0.0//0.5


#define IS_WITH_FLEXIBLE_GRP_SIZE false//true
#define IS_WITH_SINGLE_TEST_SET false//true//false //cannot be true if the above fliexibe is true.



#define IS_WITH_PROCESSING_FACILITATOR false


#define SORT_TYPE_IN_ADD_SORTED_POS 0
#define IS_LEADERS_OF_PARTS_FOLLOW false //true //false

#define IS_WITH_ADJUST_SIMILARITY_TO_SERVICE_VARIABLES false

#define IS_WITH_PARTITION_OPTIMIZATION true
#define IS_INCLUDE_SIMILARITY_STRENGTH_SCORE_BETWEEN_GRP_LEADERS false
#define IS_INCLUDE_PREDICTIABILITY_GRP_SCORE_FOR_TEST_ITEMS false
#define IS_INCLUDE_PREDICTIABILITY_GRP_SCORE_FOR_COHORT_ITEMS false
#define MAX_NUMBER_OF_PARTS 10000 //9 29 15 changed to 10000 from 1000


#define REQUIRED_MIN_NUM_OF_SIM_GROUPS 7
#define MIN_WEIGHT_I_TO_II_SIM_SCORE 0.5



#define NUM_OF_DEDICATED_GROUPS_FOR_TEST_ANCHOR 1
#define REQUIRED_MAX_NUM_OF_SIM_GROUPS 200
#define NUM_OF_REQIURED_TEST_LEADERS 30
#define IS_WITH_DEVIDE_BY_SD_PERF false


//10 8 16
#define MIN_VALUE_TO_CROSS_INTERNAL_LINEAR_REG 0.05 //0.005//0.5//0.01//8 13 15 increase to high to cencel this feature




#define MIN_AVG_PEARSON_FOR_LAST_GENERATIONS 0.0//0.05//0.0
#define SAMPLE_SIZE_FOR_STOP_EVOLUTION_FLAG 6

#define NUM_OF_PERCENTILE_GRPS_EVOLUTION 10

#define NUM_OF_RISK_GRPS_EVOLUION 2//1  8 9 15

#define IS_8_1_15_TRY false//true

#define SIZE_OF_HASH_FOR_MAPPING 100

///////////////////////////
#define PERC_SIM_MIN_VALUES_TOTAL_WGHT 0.0//1.0// 0.1
#define MAX_NUM_OF_PREDICTIVE_VARIABLES 250



#define IS_DYNAMIC_RESULT_VAL true
#define IS_WITH_FORCING_SIM true
//#define PERC_SIM_WEIGHT 0.1

#define CONST_CUT_WORKING_ARR_FOR_EVOL 0.5


#define THRESHOLD_FOR_TOO_SIMILAR_FOR_PERMUTATION_EVOL 0.98// 0.96//0.95//8//0.95//0.98//1.01//0.98


#define MODE_FOR_TEST_VS_COHORT 3

#define MULTIPLE_CONST 1.0//2.0
#define TARGETED_SIM_NUMBER  300// 150
#define MAX_NUMBER_OF_X_PARTS 100
#define NUMBER_OF_COMPARING_PARTS 20




#define NUMBER_OF_PARTSS 13 //need to be a "rishoni number" so it does not get on the way os limiting base parts sample size

#define IS_WITH_TWO_VALUES_REAL false//true//7 31 15 false


#define IS_WITH_ADJUSTING_ORIGNAL_FORMULA true


#define IS_ABCD_5_24_15 true


#define _DEFINE_DEP_6_7_15  false
#define _DEFINE__SIMILARITY_6_7_15 false



//6 15 15

//do we compare a light child similarity formula as base? or else do we use just clean stragith weight as base?
#define IS_WITH_LIGHT_SIM_AS_BASE true

//do we take what is moving by observation? or else do we only use the two dim array as done by specific action? 
#define  IS_WITH_READUSTING_TWO_DIM_ARR false//true // 6 15 15 false
//then continue checking if good to add a criteria for which j var should be inclued in the pred two dim 
//and place only thoese that are either there alredy from the action taking or are past the 50%+ of a variable. 
//that canb be defined by is the weight of those who have above mean dependent value larger than the weight
//of those who have below
#define IS_ADDING_MAJOR_POP_REQUIRMENET false


#define CONST_SIM_5_26_15 0.1//0.01//0.05// 0.01//05//0.1//0.01//001//0.08//0.01//6 4 15 0.09//0.15//0.3//5 31 15 changed from 0.1 best so far to 0.3  : 0.1//0.3//5 28 15 0.1//1.0// 0.1//0.12//0.07
#define CONST_SIM_LIGHT_FOR_BASE 0.2//0.03//0.1







#define SPECIAL_ADJUST_PREDICT_VECTOR_EVOLUTION 0.05//1.0//5 5 15 //0.1

#define IS_FULL_TEST_AND_COHORT_GRP false//true


#define IS_WITH_SENSATIVITY_EFFECT_EVOL false//true//false



#define IS_DEP_BASE_CAT_CONVERSION true


#define MAX_CATEGORICAL_VALUE 100000

#define CONVERTING_NON_LINEAR_ED_TO_LINEAR 1.0// 0.8// 0.9//0.7//0.8//1.0//0.7 //3 25 15 changed to 0.7 from 0.8

#define MIN_PERC_SIM_TO_AVOID_KN_FEATURES 1.0// 0.95//1.0//1.0 //0.9

#define XYZ_3_14_15 true//false


#define IS_FULL_REG_CONSID_FINAL true//false //true //3 16 15
#define CONSTANT_ADD_WEIGHT_CALC_PRED 10.0//20.0 







#define IS_ABCDE true//false  //4 7 15

#define IS_COVARIANCE_METHOD_PER_TEST_ITEM true//false
#define IS_PEARSON_HOMOG_SCORE true
#define IS_DEVIDE_HOMOG_SCORE_BY_SD false//true


#define IS_WITH_COMBIN_ONLY_EVO false// true
//0.1//0.5//0.1//0.5//0.1//1.0//0.1//1 25 15 changed to 0.5 from 0.1//1.0//1 24 15 0.1//0.5//0.1 //1// 0.5//0.1//1.0//0.2//2.0//1.0//0.1////0.5//1.0//0.3
#define IS_WITH_MULT_BY_EFF false

#define CONST_IN_EFFECT_SD_FOR_HOMOG_SCORE 0.5

#define CONST_ADD_WGHT_EFFECT 0.1

#define IS_ZERO_PNT_FORMULA false  
#define IS_REG_INVOLVED_IN_PRED false

#define IS_WITH_ERR_CHG_PERF_020715 false

#define CONST_ADD_WGHT_REL 0.2

#define  IS_WITH_ADJT_STANDARD_REL_SCORES false//true//false
#define CONST_ADD_TO_RELEV 0.0//0.1//0.0//1
#define CONST_MEAN_COHORT_WGHT_CHD 0.0//2//0.0//0.2//0.5//0.2//0.05//0.5//0.2//0.5//1 22 15 changed from 0.5 to 0.2. 1.0//0.1// 1.0//0.5//1.0

#define IS_INC_COHORT_WGH_EXP 1.0//2.0



#define IS_ORDER_SCORE false//true//true

#define MULT_EFFECT_CONST 0.0// 0.1//0.01//0.3//1// 0.01//1//5
#define IS_EXTREME_CUT_USING_UNIVERSAL true

//1 16 15 xxxx
#define BASE_CONST_ADD 0.01//0.1//0.3//1//2//0.1//1 5 15 1.0// 0.2

//try 1 16 15
#define MULT_CONST_EFFECT_SCORES 0.9



#define IS_WITH_BALANCED_CHD_PNT true//1 17 15///true //false


#define CONST_ADD_TW_CW_EFFECT 0.0//0.5



#define NUM_OF_VARIABLES_PARTICPATE_IN_PAIRS 2//25



#define WEIGHT_REG_BASED_SIM 0.3
#define IS_XXXXXXXXXX false


#define CONST_ADD_TO_REL_PER_BASE 0.1



#define IS_WITH_PARTIAL_TEST_GROUP  false



//play with: 1- this lin e. 2- vectore evolution 3. vector generation
//multiple the cohort or add with vector weighit. firfst play with vector weight evolution



#define IS_WITH_DEVIDE_ERR_WITH_BASE_ERR true

#define MIN_SAMPLE_FOR_TEST_AND_COHORT 10

#define IS_TRY_12_22_14 false
#define IS_WITH_REL_SHIFT_TO_PERC true
#define VAL_TO_SHIFT_REL_SCORE_TO 0.0//0.2//0.0  changed from 0 12 23 14

#define IS_WITH_ADJUSTING_PER_SHIFT_REG_TYPES true  //changed to true in 12 23 14
#define SD_FOR_SHIFT_SCORE_OBJ 0.2


#define IS_WITH_COMPLEX_UPDATE_SIM_FORMULA false//true
#define IS_WITH_DEFAULT_FORM_FROM_REG false


#define IS_MERGE_CHD_WITH_ADJ_PNT true
 // //false//true//false//true//false //true//true


//12 8 14 open true and ch ange 1.0 to 0.1
#define IS_WITH_EFFECT_WEIGHT false //true
#define CONST_MEAN_COHORT_WGHT 1.0//3.0//0.1//

//12 8 14 next test: open back the 0.0 to 0.5 and remove the 
//ADDING_SD_TO_EACH_VAR_ED_SCORE_SOURCE usage and the line with max 0 following using this





#define ADDING_SD_TO_EACH_VAR_ED_SCORE 0.5 //0.2//0.0// 0.5 //0.0//0.5//1.5
//#define ADDING_SD_TO_EACH_VAR_ED_SCORE_SOURCE 0.7 // 

#define IS_WITH_STANDARD_COHORT_SCORES true

//12 7 14 fix. check if we dont ignore the exact match buy mobing all like that
#define ADDING_SD_TO_EACH_VAR_ED_SCORE_TARGET_SORT 3.0 //insteazd of 0.0 last time
#define CONST_FOR_COHORT_SD_TRANSFER 1.0


//12 7 14 false instead of true and 0 instead of 0.5


#define IS_ZERO_SUM_IN_REL_PNT_CHD false



//#define CONS T_MEAN_COHORT_WGHT 1.0//0.3//0.2//1.0//0.1//1.0//0.1//1.0//0.1//0.7//0.1 //0.7//1.5
//#define CONST_MEAN_COHORT_WGHT_CHD 1.5//10.0//0.2//1.0//0.1//1.0//0.1//1.0//0.1//0.7//0.1 //0.7//1.5


#define IS_PEARSON_TEST_ORDER_EVOL false//true







#define MIN_SAMPLE_FOR_HIGH_OR_LOW_REG 20



#define IS_WITH_RESORTING_ENTIRE_BIG_LIST_DURING_EVO false

#define IS_WITH_RELEV_FACTOR_IN_COHORT_ANALY false//true
//changed 1.0 to 0.2 12 1 14. then changed to 1.5
#define MULTIPLE_PEARSON_PRED_REG 1.0//0.1//5//2.0//1.0 //0.0 means no reg effect




//3//1.0//0.3//1.0//0.3//1.0//0.3//11 27 14 changed from  2.0//0.3//2.0// 0.5// 2.0//0.3//0.4//0.2//0.5//0.3//0.15//0.6//1.0//0.5//1.0//0.3//1.0//11 2 14 changed from 0.0//1.0 //if 0.0 than not activated. 1.0 or ano other number "steps" on the ector evolution which without this would work on both the cohort mean and the adjust predcit.


/*
#define MULTIPLE_PEARSON_PRED_REG 1.0 //0.0 means no reg effect
#define SPECIAL_ADJUST_PREDICT_VECTOR_EVOLUTION 2.0// 0.5// 2.0//0.3//0.4//0.2//0.5//0.3//0.15//0.6//1.0//0.5//1.0//0.3//1.0//11 2 14 changed from 0.0//1.0 //if 0.0 than not activated. 1.0 or ano other number "steps" on the ector evolution which without this would work on both the cohort mean and the adjust predcit.
#define ADDING_ SD_TO_EACH_VAR_ED_SCORE 0.7// 1.0 //0.7//1.5
#define CONST_MEAN_COHORT_WGHT 0.1//0.7//0.1 //0.7//1.5
*/





#define NUM_OF_GEN_FORWARD_TO_DEFINE_WEGHT 6//8 19 14 replcaed what was 10
#define INCREASE_GEN_WEIGHT_TIMES_AVG_GEN 5//6//2//5 //for ex ample 100 genrations will get 1% vector weight times 3, if this varibale value is 3.








#define MIN_SD_RATIO_FOR_PREDIC_POWER 0.01 //0.03
#define IS_REG_SD_MODE 0//11 22 14 2 //kind of way to adjust pred based on relevancy to sp and before covriance



#define IS_WITH_SIM_BASE_SIM_FOR false //true//false



//play with this next and with vercotr ebvolution also and with similar approach for cohort scoring
//#define ADDIN G_SD_TO_EACH_VAR_ED_SCORE 0.5
//#define CONST_MEAN_COHORT_WGHT 0.5



#define MAX_SIZE_OF_PRED_VALUE 100000










//11 7 14 was
//#define NUM_OF_GEN_FORWARD_TO_DEFINE_WEGHT 8//8 19 14 replcaed what was 10
//#define INCREASE_GEN_WEIGHT_TIMES_AVG_GEN 3//3//2//5 //for ex ample 100 genrations will get 1% vector weight times 3, if this varibale value is 3.
//new test



#define EXP_INC_SIM_FORMULA 2.0
#define IS_9_6_14_FLAG  true// 10 9 14



//#define IS_EVOLUTION_BY_PARNT_REG true
//11  5 14 going back to old is setting this to true and replace evolution to one version basck
#define IS_FILL_PRED_PNT_WITHREG_SIM true 





#define REDUCE_VARIABLES_THAT_ARE_SIMILAR_ENOUGH 1.0//0.9


#define IS_PAR_EVO_BY_REG_SIM true
#define IS_WEIGHTING_SIM_IN_COHORT_PER_REL false //11 4 14 was true in 11 4 14 rn. now runnign false


//11 2 14 next test:
//is pe arson test order evou turn to true
//strength the vector evolut in both places or in one
//
//11 3 14 was true and 3 . 11 4 14 changed true to false and check (12:00am)



//next tests. 11 1 14
#define IS_WITH_ADJUST_SCORES true //currently running first test with false 11 1 14. now with true.

//
//false//10 18 14 true
//modify only vector evolution of the adjust predictin (11 1 14 a) and so we have two separatel vector evolution?
//play with GetNumberOfManipulationVariables(){return 4;}

//next next set of tests
#define IS_WITH_WEIGTED_REG_ORDER_CONSIDERATON true


//the higher the const the more distant items will have some score and medium distant items will have medium score
	//and so we have less of relative weight to the the real near ones. 
//#define CONST_MAX_ED_IN_REG_ORDER 1.5



#define IS_SPECIAL_EXPO_CUT_FOR_EVOLUTION false//true


//10 29 14 11pm closing two true to be two false
#define IS_ADJUST_COHORT_WGH_BY_SD  true
#define IS_WITH_IND_VAR_SD_COHORT_SCORE true//
//#define CONST_FOR_COHORT_SD_TRANSFER 0.5//0//1.5  //10 31 14




#define IS_WITH_FEATURE_SELECTION false//false //10 10 14 false







//8 30 14 changed to 1500// 1200// try 1900
#define TOTAL_COMBINATIOSN_FOR_PRED_MANIP_N 200//8 30 14 changed to 1500// 1200// try 1900




#define ED_IN_SD_COUNT_AS_SIM 0.3
#define IS_USING_AVG_COHORT_AS_PRED_PNT true //10 18 14
#define POW_ORDER_SCORE_RELEV  1.0

#define IS_INCLUDE_REG_IN_PREDICTION true
#define IS_INCLUDE_REG_WIDE false
#define IS_INCLUDE_REG_CONSERVTIVE false
#define IS_DYNAMIC_REG_METHOD false//true


#define CONSTANT_ADD_WEIGHT_CALC 5//20//9 20 14 5//10//10//100

#define TIMES_PARNT_MORE_WEIGTED_IN_PREDUCTION 0.5//5//0.4//0.5//1.0//0.2//0.5// 2.0//0.5// 1.2//3.0 //1.0//0.5// 2.0//1.0

//10 19 14

//10 30 14 cange the first two to 0.2 from 0.6. also thet forth one but it is not used. only the 
#define CONST_ED_ADJUSTEMETN 0.2// 0.6// 0.2 // 0.01//0.01 //0.1// try 0.03, 0.3 

#define INCREASE_POS_ED_SCORE_EVO_BASE 0.2//0.6//0.2//0.05//8 31 14 //0.2 // 0.01// 0.1//0.01// 0.1 //try 0.03, 0.3
#define INCREASE_POS_ED_SCORE_EVO_BASE_RELEV 0.2//0.6 //0.2 //10 17 14

#define INCREASE_POS_ED_SCORE_EVO_CHD 0.2// 0.6 //0.2//0.01//1//0.08//0.8// try 0.1 



#define POW_EVOL_MERGE_PAR_CHD_ED 1.0

#define NUM_OF_ITERATIONS_N 0//5// 10 //0
#define MIN_EX_VAR_TO_USE_KN 1.0//0.2//1.0//0.2//0.3



#define WITH_ED_MEAN_TO_LINEAR_CATEGORICAL true





#define IS_WITH_MULT_PER_SIM_POTENTIAL false//true

//#define IS_WITH_REG_EVOLUTION_9_23_14 true
#define IS_EvolutionNEW_9_21_14 false//true

#define IS_LOCAL_REG_EVOLUTION true



#define IS_PEARSON_IN_KN true
#define IS_WITH_REG_SIM_FOR_SCORING false

//used to be 0 and false in the last culumn.
#define POW_VALUE_PNT_OVER_CHD 0.0 //1.0
#define IS_ADDING_PARNT_ED_TO_CHD true


//true//false //9 19 14 true

#define POW_VALUE_TEST_GRP 1.0f//0.2f//0.5f//1.0f//0.5f//0.5f


#define IS_WITHSFT_IS_KN_PERF false


#define EXP_MERGE_BASE_TO_CHD_VAL 1// 1.5//8 31 14//1.1//5//2.0//1.0 //8 30 14 1.5//1.0//1.5





//8 31 14 instead of 1.0  and false

//for same version to be sent as true, 1, 1.0f


#define IS_DIFFERENT_TEST_GROUPS true
#define IS_DIFFERENT_SET_CLEAN true

#define ADDIONG_SD_VALUE_TO_GEN_WEIGHT 2.0//1.0// 8 27 14 // 2.0//1.0//2.0

#define POW_BASE_OVER_CHD 0.0//1.0//9 2 14 0.01//1.0//0//1.5// 0.5//1.0 //8 9 14






#define IS_EVOLUTION_8_18_14 true
#define WITH_VECTOR_RECURSIVE_STRENGTH true//false


#define PERC_MEAN_RELEV_FOR_ADJUSTENT 1.0//0.1//2.0

#define INCREASE_POS_ED_RELEVANCY_SCORE_EVO_CHD  0.1

#define IS_WITH_ADJUST_WEIGHT_COHORT_CHD false


///8 3 13 play with defines
#define IS_WITH_CALCULATE_ADJUSTED_SUM_RELEVANCY_WEIGT false// true //false




//and add number of iterations








#define FLAG_7_31_14 false //try true


//#define CONST_DECREASE_SCORE_PREVIOUS_SAMPLE 100 
#define IS_DYNAMIC_ORDER_SCORE false
#define IS_WITH_SUB_SET_COHORT  false //true 




#define IS_ADAJUST_BY_MEAN_DEP false






#define IS_DYNAMIC_VECTOR_WEIGT false//false //??

#define IS_NORMELIZ_DEP_EVOL false



#define IS_EVOLUTION_6_29_14 true
#define IS_EVOLUTION_7_25_14 false
#define IS_STABLE_STAT_FOR_MEAN_AND_ED true

	

#define NUM_OF_COHORT_SUB_SET 0
#define IS_WITH_ED_ADJUT_OTHERS true



//7 11 14
//100//20// 10// 40//10 //20  //7 11 14 play with 1/10/10
#define IS_EVOLUTION_7_11_14 false

//7 11 14 note: try cohort sub set features taken from evolution 6 29 14 func.

#define IS_EVOLUTION_6_20_14 true






//#define IS_DIFFERENT_TEST_GROUPS false
#define IS_CALC_PREDICTION_FROM_SUB_SET_WITH_REG true

/*
//7 11 14
#define CONSTANT_ADD_WEIGHT_CALC 20// 10// 40//10 //20  //7 11 14 play with 1/10/10
#define IS_EVOLUTION_7_11_14 false
#define IS_EVOLUTION_6_29_14 true
//7 11 14 note: try cohort sub set features taken from evolution 6 29 14 func.

#define IS_ADAJUST_BY_MEAN_DEP true
#define IS_EVOLUTION_6_20_14 true
*/

#define IS_MULTIPLE_ADJUST_BY_MEAN_STEPS true
#define EVOLUTION_BY_REG false


#define SIZE_OF_CASH_SUB_SET_COHOT 30
#define IS_WITH_ALL_VARIABELES_PREDICTION true


//0.1 //147 12.8 with  0.01/1  and 1000  and parent sim. change to 1/1/100 parent with 1000 eolution 0.1 vector

#define IS_STRENTGH_FOR_PARENT_SIM true
//need to be smaller when new scoring
#define IS_ED_MEAN_BASE_ON_SP_EVOLOTION false
#define ED_MEAN_SD_MODE 3

#define MIN_SAMPLE_FOR_COHORT 2000 //dif from othe run. also con //
	
//#define TOTAL_COMBINATIOSN_FOR_PRED_MANIP 1000//600  6 29 14


///////////////////////////////////////

#define IS_REHAUB false





#define IS_FORM_ABSOLUTE_ORDER true
#define IS_ADJUST_ORDER_BY_MEAN_SHT_FROM_PAR false
//100 or higher would mean that this feature is canceled, not in use
                      //this will maintain todady version. for new feature any  number from 1 to 99.



////////////////////////////////

#define EXP_VALUE_GET_ORDER_SCORE 1

//#define IS_DEVIDE_ORDER_SCORE_BY_SD false



//#define IS_TO_IGNORE_EVOLUTION false

#define CONSTANT_ADD_WEIGHT_CALC_EVOL  0.2


//#define CONSTANT_ADD_WEIGHT_CALC_EVOL  1

//GetIsWithSubSetTestGroup false GetPercTestStartValue 1.0





//5 18 14 note 5: adding this as true. false will be maitaining the 5 18 14 version
//#define IS_START_LINEAR_CONT_TEST_GRP_ZERO true

//5 18 14 not 6: set to false to maintain the 5 18 14 version
#define IS_WITH_SEMI_RANDOM_PREDICTIVE_SELECTION true


//5 18 14  note 6:  // if set to false would maintain the 5 18 14 version . set to true we get a new behaviour
//#define IS_DEFAULT_FORMULA_BY_REGRESSION true
//////////////////////////////////////////////////////////////////

//#define IS_TO_DEVIDE_ED_BY_ED_SD false


//#define IS_ORDER_SCORE_L_2 true



//#define IS_EXPON_UPDGRADE_FOR_TEST_GROUP_SIMILAR false
//#define EXPO_VALUE_TO_DIFFERENTIATE_TEST_GROUP 1.5 //1.5
//#define SIZE_OF_LP_GROUP_MEDIUM 200
//#define PREDICT_K_COUNT_EVOLUTION 500
//#define IS_DEVIDE_BY_VAR_EVOLUTIONN false


//5 18 14 note 1:
//adding the IS_EXTREME_CUT_USING_UNIVERSAL  . In the version recevie on 5 18 14 
//it did not exsit and would behave as false. need to check with true to selct best option

//5 18 14 note 2:
//adding call to the config instead of INCREASE_PRED_CNT_FOR_KCOUNT_EVO_ARR. in the verion recevied on 5 18 14 the value was 
//per the below define and was set to 1. we can now check 2, 3, etc. 
//#define INCREASE_PRED_CNT_FOR_KCOUNT_EVO_ARR 1


//5 18 14 note 3: //new define. if set to false we keep the version from 5 18 14 as is. if set to true we can play with the
  //two new other paramters PERC_TEST_START_VALUE and  PERC_TEST_END_VALUE 
//#define IS_WITH_SUB_SET_TEST_GRP true
//#define PERC_TEST_START_VALUE 1.0//0.8//0.2//1.0//0.5
//#define PERC_TEST_END_VALUE 1.0//0.2//0.1//0.3//

//5 18 14 note 4: we want to play withi thie as config, if there is one lets replace the define with the config


//5 18 14 note 7: fixed devide by zero bug at edit distance target sort. 
//        note 8 : also we need to look for a leak fixed in the new not used version.


#define IS_STR_OVER_BASE true
#define IS_WEIGHT_INC_STRE_SUBJECT_TARG true


//#define IS_ONLY_PROFILE_PREDICTION true

//2 22 14  two define parameters:

//#define IS_VERSION_3_2_14 true




#define NUM_OF_VARIABLES_PARTICPATE_IN_TRIPLES 15


#define EXP_FOR_CUT_EXTREME_PREDICT 1.0

#define SDs_THRESHOLD_FOR_EXTREMET 1//0.8 not so good //1.3//100//1.3 //2 24 14

//#define NUMBER_OF_MANIPULATION_VARIABLES 1
//#define IS_TO_INCLUDE_PREVIOUS_WEIGTHS_IN_CURRENT_INTERN_REG false

//#define IS_COMPARE_SET_TO_STRAIGHT_FORMULA true
//#define IS_COMPARE_SET_TO_ZERO_FORMULA false


//#define LOCAL_GEN_VECTOR_EVOLUTION 0.5 //need to redo the config

//#define IS_TO_SHIFT_DEP_PERF_BY_MEAN_EVOLUTION false



#define PERCENTAGE_ERR_DIM_EVO 0.5


#define IS_CENTER_EVOLUTION false


/////////////////////////////////////////////////////////////////

#define IS_TWO_DIOMENSION_EVOLUTION false

#define IS_START_EACH_GEN_FROM_STRAIGHT_FORM false
#define IS_START_EACH_GEN_FROM_ZERO true









#define IS_SUB_GROUP_TESTT false





#define NUM_OF_SORT_OBJECT_EVOLUTION 1



#define IS_SELECT_ALGORITHM_ONLY_PER_SUB_GROUP false

#define IS_PROBABILITY_SELECTION_OF_ALGORITHM false
#define PREDICT_COUNT_SELECT_ALGORITHM_TTEST 200



#define NUMBER_OF_LOCALGENNS_ITER 5
#define IS_DEVIDE_BY_AVG_ERROR_FOR_EX_VAR false



#define IS_NORMELIZE_DPENDENT false
//#define IS_FULL_TEST_GROUP false //ohad, how come this is alreaday in the config?

//#define SIZE_OF_LP_GROUP 100
//#define SIZE_OF_LP_GROUP_SMALL 100

//#define SIZE_OF_LP_GROUP_LARGE 1000

#define IS_SAME_WEIGHT_EACH_GENERATION true

#define IS_EXTRA_TEST_GROUP_ISOLATION false

#define IS_WITH_SD_EFFECT_PERFOR true

#define LOCAL_GEN_VECTOR_WEIGT 0.05//1 //0.3//0.3//0.01
//#define LOCAL_GEN_VECTOR_WEIGT_TEST 0.10
//#define LOCAL_GEN_VECTOR_WEIGT_LEARN 0.10

#define MAX_NUM_OF_GENERATION 500

#define MAX_NUM_OF_REG_EVOLUTION_COUNT 2000

//this is how much more we want to decrease those who appeared. 1 is some middle value, 
// 2 for exmale  will make more difference as 0.5 goes to 0.25 but 0.25 goes to ~0.06
#define DECREASE_STRENGTH_CONST 0.01 //1 23 14 was 0.3
#define IS_START_EACH_GEN_WITH_PREVIOUS_FORM true

#define MAX_NUM_OF_LOCAL_GENERATIONS 300

#define IS_WITH_SORT_PER_GENERATION true
//#define DECREASE_ITEM_WEIGTS_APPEAR_PER_GEN 1.3
#define MULTIPLE_SELECTION_FACTOR_ED 0//5

#define IS_PPI_CASE_ALLOWED false


#define SIZE_OF_LONG_PROFILE_GROUP 200
#define ZIZE_OF_LONG_PROF_TEST_GROUP 200 //to pass the threshil

#define NRGATIVE_THRESHOLD_FOR_FEATURE_SELECTION -0.001 // -0.1//-0.001 //-0.1 //-0.001// -0.1 //(-0.0005)//used to be -.005
#define IS_KN_SHIFT false
#define SIMPLE_METHOD_OF_CHILD_PREDICTION true//true

#define IS_MEAN_ONLY true
#define IS_WITH_MOVING_FEATURE_SELECTION true


//////////////////////////////////////////////////////

#define L_LEVEL_PREDICT 2
#define IS_CUTTING_DEPENDENT_EXTREME true//false//true  //10 8 16  cpy to a center place and decide if good to keep
 
#define EXPONENSIAL_CONS_EVOLUTION 1.0 //to get more chance to thin variable areas
#define ADJUSTAVG_PER_IMP false


#define NUM_OF_K_CHECK_ITERATIONS 9
//#define IS_SIMPLE_PREDICT false   // add to the config DONE
//#define ADITIONAL_EVOLUTION_VECTOR_VALUE 0.3  // add to the config DONE
#define SIZE_OF_PROFILE_GROUP_OUTPUT 600

#define IS_AIMING_FOR_FULL_PROFILE false

//#define PREDICT_K_EVOLUTION_FINAL   200  // add to the config   DONE
//#define PREDICT_K_EVOLUTION_LONG_PROFILE_SIZE 100 //keep the same as predic k evolution final
//#define VECTOR_INC_EVOLUTION 0.5 //try to get more than 50% in  one variable weight in the sim formula  // add to the config  DONE
//#define LINEAR_CONST_EVOLUTION 1.0  // add to the config  DONE

//#define PREDICT_N_CONSTANT 0  // add to the config



//////////////////////////////DONT CHANGE SECTION//////////////////
#define DEBUG1
//eeeeeeeeeeeeeeee
#define NULL 0


//#define MIN_EDIT_DISTANCE 15
//true //this potential to be rechecked later
#define PERC_DELUTION_PRED_VARS 0.01 //not sure if needed
#define IS_ANALYTIC_K_CONTROL_GROUP_ZERO_CLEAN false// 
#define IS_ADJUSTED_SP_PREDICTION_PER_TEST_GROUP_SHIFT false


#define IS_ADJUST_PREDICT_VALUES_PER_ONE_CNTR_ITEM false
//if we want to starst not form the equal weights default, but from a reg beta list.
#define IS_TO_SET_DEFAULT_SIM_FROM_REG_BETA false
//#define IS_TO_PREDICT_ONLY_BY_MEAN_EVO true  //not sure if needed

//#define IS_TO_PREDICT_ONLY_BY_MEAN_PREDICT false  //relevant when calling old Predict only
//#define IS_REG_STAT_FOR_MSD_UNIVERSAL true
///////////


#define MAINLOOP_STAGE_ONLY_SIM_K 1 
#define MAINLOOP_STAGE_OTHERS_K 2

/////////////////////////////////////////////////9 16 13


//#define new preidct count and predict cohort to be small and perhaps predict evolution //9 15 13




//#define MAX_ED_FOR_N_GROUP_ALLOWED 15
//#define PERC_SIMILAR_IN_MID_SIZE_ARRAY 0.75

//#define PERC_REMOVE_FREQUENT_EXACT_MATCH 0.2
//#define TOTAL_PERC_REMOVE_LOW_PERFORMANCE_SIM_VARS 0.5


//6 28 13
//#define IS_SYMETRIC_TEST_ALL true//false
//#define MIN_SIM_GROUP_COUNT_FOR_EVO_TESTS 20//50

//#define ADJUST_PER_IMP_ONLY_ALLOWED false


//#define IS_WITH_BalanceDPsCombinationsWithZeroSumStrech false

#define THRESHOLD_FOR_PER_WEIGHT_DISTRIBUTION_FOR_REG_PRED_VALIDITY 0.04
#define THRESHOLD_FOR_PER_WEIGHT_DISTRIBUTION_FOR_EXACT_MATCH_REG_PRED_VALIDITY 0.008
#define IS_NEVER_NORMELIZE_REGRESSION_PRED_VAR false

#define IS_ADJUST_BY_MULTIPLE_CHILD_SORT_LIST false

#define STRENGTH_OF_PERC_PUSH_ONE_VAR_CLEAN 0.05
//#define ED_THAT_COUNTS_AS_EXACT_MATCH 30
//#define MIN_EXACT_MATCH_RATIO 0.05

#define IS_WITH_UPDATE_COLLECTIONS_STRECHNESS true
#define IS_ADJUSTING_META_REG_WEIGHT_PER_SUM_OF_RELEVANCY false

#define IS_DYNAMIC_CONSTANT_FOR_SIM_THRESHOLD false
#define MODE_FOR_CONTROL_GROUPS 3//2
//#define IS_CONTROL_GROUP_STABLE_ACROSS_GENERATIONS false
#define POWER_EFFECT_CONSTANT 0.3
#define MIN_MEMBER_COUNT_PER_META_REGRESSION_FORMULA 100
#define IS_ADVANCED_SELECTION_FOR_META_REGRESSION_INCLUSION true
#define MIN_SIM_STRENGTH_DP_REG  0//proved to be forces to 0 for now //it is negative since this is via sim sd and small/minus sim sd means more similar to sp
#define MIN_PERC_EFFECT_DP_REG 0 //0.75
#define  MIN_SIM_STRENGTH_FOR_CUTTING_SIM_GROUP 0.08
#define IS_REGRESSION_IN_PERFORMANCE_PROCESSING false //true
#define IS_EXPAND_PERFORMANCE_LIST true 
#define IS_ADJUST_Y_VALUES_WITH_SD false// false//true//false//false
#define CONSTANT_PREDICT_SCORE_MODIFIER 1
#define IS_WITH_EXTRA_META_REGRE_VARIABLE false
//when turning is clean flagged to true you should also turn the "is adjust y values to mean" to be true too.
#define IS_CLEAN_FLAGGED_IMP_Y false
#define IS_ADJUST_Y_VALUES_WITH_MEAN false//true//true
#define IS_WITH_SYMETRIC_AVG_DIS_OPTION false //true//false
#define IS_ADJUST_ERROR_REDUC_PER_AVG_CONTROL_GROUP false
//#define PREDICT_K_COUN T_EVOLUTION 800//5000//1200//1500//1000//50000// 1500//50000//1500//1500//600//1000 //12 6 12 50000
#define NUM_OF_TOP_SIMILAR_FOR_GEN_SET 500
//#define L_LEVEL_ERROR_EVOLUTION 1.6//1.3 //1.8//2
//#define CORE_VECTOR_WEIGHT_CHANGE 0.15f //0.1f//0.07 //0.05//0.1//0.05//0.05f// 0.1f// 0.1f
//#define MULTIPLE_CORE_VECTOR_WGT_CHG 2//8.0//2.0f//3.0  //12 25 12 
#define IS_REGRESSION_BASED_CNTR_GROUP_AVG_DELTA true
#define IS_ALIGN_PARENT_TARGET_SORT_TO_PARENT_WITH_SD false
#define MAX_SIM_PER_VARIABLE_TO_BE_INCLUDED_FOR_META_REG 40

///////////////////////////////////////
#define IS_FLAGGED_REQUIRED_FOR_LINEAR_MEETA_REGRESSIONS true
#define IS_FLAGGED_RELATION_TO_SP true

#define WITH_RELATTIVE_TO_MEAN_ONE_CONTROL_ITEM false
//#define WITH_COMPLEX_DIMENSION_CUT 


//one one can be true. from following two. 
//false and true will give us culumn  123ert
//true and false will give us culumn 456yui
//false and false will give us culumn dfghjk
#define IS_WITH_RANDOM_EFFECT_PARENT_STAT false
#define IS_WITH_UNIVERSAL_ADJUSTEMENT_FOR_CLEAN false //true

//if IS_WITH_RAN DOM_EFFECT_PARENT_STAT is also true than you can put this true:
#define IS_WITH_REGRESSION_CHILD_EFFECT_FOR_CLEAN false // 12 14 `1 change false
 
//#define MAX_NUM_OF_PERFORMANCE_CANDIDATES_RANDOM 1000

#define IS_CHECK_FOR_SAMPLE_SIZE_REGRESSION true//true // false  //11 17 12
#define IS_SENSATIVITY_EDIT_DISTANCE true
#define PRECENTAGE_WEIGHT_CHANGE_FOR_SENSATIVITY_CHECK 0.1
#define  EFFECT_OF_SENSATIVITY_ON_EDIT_DISTANCE 0//1.0f //the larger the constant is, toward the 1 value, 
						//it is more agressive toward taking sensativity stronger. 0.1 will be like almost no effect on ed
#define CONSTANT_FOR_UPGRADE_EVOLUTION_PER_SENSATIVITY 0//0.1 //0.3
#define CONSTANT_FOR_ED_MEAN_POW 1//0.7

#define MAX_PERCENT_WEIGHT_OF_ONE_DIMENSION 0.6f
#define DYNAMICN_SEEK__DEVIDE_CONSTANT 10.0f //20.0f//7.0f //5.0
#define DYNAMICN_SEEK__ADD_CONSTANT 0.1//3.6 //0005// 0.01f  //0.2 //OHAD 8 15 12
#define COUNT_OF_TESTING_GROUP 500  //right now taking from the end

#define EXTREME_DEPENDENT_VAL 301//500 //300
#define IS_MUTATION_SINGLE_VARS true
//#define PREDICT_K_COUNT 800//500//400//500//750//1000// 1200//1000//1500
#define K_COUNT_POP_CHANGE_FLAGGED 1000
#define IS_DYNAMIC_PREDICT_COUNT false

#define IS_TO_ZERO_WEIGHTS_WITH_ZERO_VAL false	
#define IS_SINGLE_PERF_TEST false 
#define IS_SQR_ERR_EVOLUTION false
//0.5f//2.0f //when sending the regression total weight change, it can
				//be probaby a number less than 1, since the tests can be extreme but the atualy change can be careful


#define MAX_DISTANCE_BETWEEN_REV_VAL_TO_PREDICTION 200

#define FUNCTION_CATEGORY_PARENT_BETA 1  //will be called frm k constant and pp
#define FUNCTION_CATEGORY_SELF_BETA 2   //will be called from n constant seek and pp
#define FUNCTION_CATEGORY_SELF_ALL 3 //here will use as control check or even weight accordingly the two dimenesions
#define FUNCTION_CATEGORY_BASIC_REGRESSION 4
//EREZ - move MAX_NUM_OF_REGRESSION_COUNT to configuration
//#define SIMILARITY_STATISTIC_CHECK 's'
#define MISSING_RESULT_VALUE 10000
#define MAX_NUM_OF_REGRESSION_COUNT 500000
#define PREDICTIVE_STATISTIC_CHECK 'p'
#define SIMILARITY_STATISTIC_TYPE 's'
//for create extended k and k controll arrays
//#define K_GROUP_TYPE 0
//#define K_CONTROL_TYPE 1

#define IS_SAVING_PROCESS_TIME false

#define SAMPLE_SIZE_FOR_HOMOGENITY_SHIFT 200
#define SAMPLE_SIZE_FOR_SCORE_CUT 500
#define SAMPLE_SIZE_FOR_SCORE_CUT_LARGE_ARRAY 5000



//NEW CODE 8 15 12
#define VALUE_TO_START_EDIT_THRESHOLD 20



#define SAMPLE_SIZE_FOR_SIGNIFICANT_PREDICTIVE_DIFF 15
#define VALUE_FOR_SIGNIFICANT_PREDICTIVE_SIFF 40  //to check valid variable for regression
#define VALUE_FOR_SIGNIFICANT_SIMILARITY_SCORE_SIFF 50  // 50 is 0.5 SD times 100 . 

#define EMPTY_KN_PERFORMANCE_SCORE 0.0f //1000000.0

//va;lues for vector mutations so we gestimate conversion of formula and data  exchange

//#define CHANGE_OF_POPULATION_K_GROUP 0.05f

//#define MAX_NUM_OF_PERFORMANCE_CANDIDATES_PEERS 60
#define MAX_NUM_OF_PROFILE_DIMENSIONS 300




/*
these will define what type of consants are used in flagged se function. for pp (performacne procesing) we use partial flagged
type of contant. for dynamic constants function we use basic regreson constant. not sure if we need the control regression constant,
not used yet.


*/
//#define BASIC_REGRESSION_CONSTANT 1
//#define PARTIAL_FLAGGED_REGRESSION_CONSTANT 2
//#define CONTROL_REGRESSION_CONSTANT 3
#define NUM_OF_MUTATION_ITERATIONS 1

#define MAX_NUM_OF_PREDICTIVE_VARS MAX_NUM_OF_PREDICTIVE_VARIABLES //100 //7 14 12 uniting with th eother one of 250 PPPPP

#define MULTIPLE_FOR_N_CONSTANT_SEEK 0.003
#define N_CONSTANT_SEEK_ITERATION_NUM 9

#define SAMPLE_FOR_VARIABLE_CORRELATION 5

/*
#define DEFAULT_N_CONS TANT_EVOLUTION 0.2f//150 //default Nconstant: 

#define DEFAULT_K_CONS TANT_EVOLUTION 0.5f// 2.9f//0.5f//0.5f//0.2//2.0//0.5f//1.0f
#define DEFAULT_K_CONS TANT_N_SEEK 0.5f//0.2f//0.5f
#define DEFAULT_K_CONS TANT_PREDICT 0.2f//0.5f//0.2f//0.5f  make sense more that it should be more than the best n constant calculated in the dyamic n seek function

#define EXPONENTIAL_K_CONST_EVOLUTION 1.2f//1.75f//1.1f//1.1
#define EXPONENTIAL_K_CONST_N_SEEK 1.2f //1.1f
#define EXPONENTIAL_K_CONST_PREDICT 1.0f//1.2f

#define EXPEDITING_EVOLUTION_CONSTANT 1.0f //sin ce we have multipe winner in pp function we need also more "power" to evolve. just a short cut. could improve it and do a calculation of how multiple are sharing how much

#define DYNAMICN_SE EK__DEVIDE_CONSTANT 5.0f//7.0f //5.0
#define DYNAMICN_SEEK __ADD_CONSTANT 0.1f  //0.2
#define PREDICT_  n K_COUNT 1000//750//	1000// 1200//1000//1500
*/
//new section 7 25 12
//#define DEFAULT_N_CONSTANT_EVOLUTION 1.2f//0.005f//150 //default Nconstant: 

//**************
//#define //DEFAULT_K_CONSTANT_EVOLUTION 0.1f// 2.9f//0.5f//0.5f//0.2//2.0//0.5f//1.0f
#define DEFAULT_K_CONSTANT_N_SEEK 0.1f//0.2f//0.5f
#define DEFAULT_K_CONSTANT_PREDICT 0.2f//0.5f//0.2f//0.5f  make sense more that it should be more than the best n constant calculated in the dyamic n seek function

#define EXPONENTIAL_K_CONST_EVOLUTION 1.0f//1.75f//1.1f//1.1
#define EXPONENTIAL_K_CONST_N_SEEK 1.0f //1.1f
#define EXPONENTIAL_K_CONST_PREDICT 1.0f//1.2f






#define EXPEDITING_EVOLUTION_CONSTANT 1.0f //sin ce we have multipe winner in pp function we need also more "power" to evolve. just a short cut. could improve it and do a calculation of how multiple are sharing how much
//////////////////////////////////////////////////////////////////end of new section 7 25 12
#define IS_UNIVERSAL_REG_STANDARDIZED true //false// PRIORITY to false //XXXXX

#define EXPONENTIAL_K_CONST_PROFILING EXPONENTIAL_K_CONST_PREDICT//1.5
//#define PROFILING_K_COUNT PREDICT_K_COUNT //500





//#define DEFAULT_K_CONSTANT 0.05f
//#define K_COUNT_FROM_ANALYTIC_PROCESSING 50000//100  //ccc
//#define K_CONTROL_COUNT_FROM_ANALYTIC_PROCESSING 750
 //this one goes to the predict functin, havinh  members form some weighted k n and 
//predict for the subject person. when we improve finding the right k, we will change this value to a range. like what we do with n constant

//#define K_COUNT_FROM_N_CONSTANT_SEEK  500//PREDIC  T_K_COUNT//300 //needs to be double than the next one, d ule to optin of predictivlity =0 for hafl	
//#define K_CONTROL_COUNT_FROM_N_CONSTANT_SEEK 500// PREDICT_ K_COUNT//300
//#define PARTIAL_FLAGGED_CONTROL_COUNT_FROM_N_CONSTANT_SEEK 100

//#define IS_N_SEEK_K_CONTROL_GROUP_ZERO_CLEAN true


//2000
#define K_COUNT_FROM_K_CONSTANT_SEEK 600 
#define SHIFT_CHECK_K_COUNT 100  //since only one to 3 mode will be counted, we need a large count. 1000 will give us 333 control group

//7 31 12 changed from 500 to 150.
#define K_CONTROL_COUNT_FROM_N_DYNAMIC_SEEK 250//300 ANALYTIC_PROCESSING 750//100  //

#define IS_TRADITIONAL_PREDICTION false // true

#define WITH_EVOLUTION  true
#define SEMI_K_AVERAGE true





#define PERC_TARGET_4_REGR_VALIDATION 0.25f




// New definitions: types of regression to run 
#define LINEAR 0 
#define LINEAR_TWO_STEPS 1 // here we take only significant betas and run regression again
#define STEPWISE 2 
#define LOGISTIC 3  // CHANGED THESE CONSTANTS DEFINES ! 18/12/2011 (Zuk)


//#define HUNDRED 100 // WHY WE need it?

#define PVAL_SIGNIFICANCE_CUTOFF 1 // 0.05 // Cutoff for p-values for each beta of regression (we take only beta's with p-value below this cutoff) 

//**************************************GENERAL*********************************************

// File general.h - Macros, prototypes and constant of the DNA package
#ifndef _GENERAL_H_
#define _GENERAL_H_


// New types defined 
typedef unsigned long int word;   // machine word (32 bit on windows - pc)
typedef unsigned char byte;       // a byte

// Macroes 
#define BIT(block, num)  ( ((block) >> (num)) & (1UL) )  // get the i-th bit from a word
#define BITS(block, num1, num2)  ( ((block) >> (num1)) & ((1UL << (num2+1-num1))-1) )  // get the i-th to j-th bits from a word


//EREZ check if we odn't have any issue with ^
// inverse the order of the bits in a word
#define INVERSE(block) 
//	(block) = (((block)&0x0000FFFF) << 16 ) ^ (((block) >> 16)&0x0000FFFF); \
//	(block) = (((block)&0x00FF00FF) << 8 ) ^ (((block) >> 8)&0x00FF00FF); \
//	(block) = (((block)&0x0F0F0F0F) << 4 ) ^ (((block) >> 4)&0x0F0F0F0F); \
//	(block) = (((block)&0x33333333) << 2 ) ^ (((block) >> 2)&0x33333333); \
//	(block) = (((block)&0x55555555) << 1 ) ^ (((block) >> 1)&0x55555555); 

// inverse the even and the odd bits in a block
#define INV_PAR(block) \
	(block) = (((block)&0x55555555) << 1 ) ^ (((block) >> 1)&0x55555555); 

// inverse the order of bytes in a word (this is for changing indians)
#define INDY(block) \
//	(block) = (((block)&0x0000FFFF) << 16 ) ^ (((block) >> 16)&0x0000FFFF); \
//	(block) = (((block)&0x00FF00FF) << 8 ) ^ (((block) >> 8)&0x00FF00FF); 






// swap elements 
#define SWAP(A, B, TEMP)	\
			(TEMP) = (A);   \
			(A) = (B);      \
			(B) = (TEMP);


// swap two arrays (convert size from words to bytes)
#define SWAP_ARRAYS(A, B, TEMP, len_in_bytes)	\
	memcpy((TEMP), (A), (len_in_bytes));  \
	memcpy((A), (B), (len_in_bytes));  \
	memcpy((B), (TEMP), (len_in_bytes));  

// swap bits inside one word
#define SWAP_S(addr) \
	(addr) = ((addr)&0x20) ^ (((addr)&0x1) << 4) ^ (((addr)&0x1E) >> 1);

#define ARGMAX(x,y) ((x) > (y) ? (0) : (1))
#define ARGMIN(x,y) ((x) < (y) ? (0) : (1))

#define ARGMAX3(x,y,z, A) \
        (t_xy) = (ARGMAX((y),(x))); \
        (t_xz) = (ARGMAX((z),(x))); \
        (t_yz) = (ARGMAX((y),(z))); \
        (A) = (1-(t_xy)*(t_xz)) * (1 + (t_yz));


#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) < (y) ? (x) : (y)

#define ABS(x)  ((x) > 0 ?  (x) : (-(x)))

#ifndef TRUE
#define TRUE 0
#endif
#ifndef FALSE
#define FALSE 1
#endif


#define MAX_MODEL_SIZE 6

#define WORD_SIZE 32
#define HALF_WORD_SIZE (WORD_SIZE/2)




// end of line in ASCII
#define EOLN 10

// TAB in ASCII
#define TAB 9

#define SEQ_LEN 100
#define PRINT_IN_ROW 20



// Discrete and Continunuos flags
#define DISCRETE 0
#define CONTINUOUS 1

// Number of steps we do until we perform scaling !!
#define DO_SCALE 1
  

// Constants 
#define ONE_PI 3.141592654
#define SQRT_2PI 2.506628274
#define ONE_OVER_2PI 0.1591549430
#define ONE_OVER_2SQRT_PI  0.3989422802
#define ONE_OVER_2SQRT_PI_LOG (-0.9189385337)
#define EPSILON 0.000001



#endif 


//***********************************END OF GENERAL *********************************



/*

more notes:
there could be cases where one will not have 

*/
#define NUM_OF_BUCKET_SLOTS 24

class cValueBuckets
{
	float m_bucketSlots[NUM_OF_BUCKET_SLOTS];
	float m_sumOfWeights;
public:
	cValueBuckets()
	{
		m_sumOfWeights=0;
		for (unsigned int i = 0 ; i < NUM_OF_BUCKET_SLOTS ; i++)
		{
			m_bucketSlots[i]=0;
		}
	}
	unsigned int GetCount () { return NUM_OF_BUCKET_SLOTS;}
	float GetBucketWeight(unsigned int index) { return m_bucketSlots[index];}

#define MAX_SD_PREDICTIVE_VAL 3.0f
	static float GetPredictiveValueFromIndex (unsigned int k)
	{
		float val = ((float)k) /    ( (float)((NUM_OF_BUCKET_SLOTS -1) / (MAX_SD_PREDICTIVE_VAL*2)));
		val -= MAX_SD_PREDICTIVE_VAL ;
		return val;		
	}

	static unsigned int GetIndexFromPredictiveValue(float predictiveVal)
	{
		if(predictiveVal < (-MAX_SD_PREDICTIVE_VAL))
			predictiveVal = -MAX_SD_PREDICTIVE_VAL;
		if(predictiveVal > (MAX_SD_PREDICTIVE_VAL))
			predictiveVal = MAX_SD_PREDICTIVE_VAL;
		predictiveVal += MAX_SD_PREDICTIVE_VAL; //now make sure it is 0 or positive between 0 and 6 SD
		predictiveVal *= ((NUM_OF_BUCKET_SLOTS -1) / (MAX_SD_PREDICTIVE_VAL*2));
		return (unsigned int ) predictiveVal;
		
	}
	void IncrementBucketSlot(float val, unsigned int index)
	{
		m_bucketSlots[index]+= val;
		m_sumOfWeights += val;
	}
};


class cValueBucketsArr 
{
	cValueBuckets * m_arr;
	unsigned int m_count;
public:

	cValueBucketsArr()
	{
		m_count = 0;
		m_arr = NULL;
	}
	cValueBucketsArr(unsigned int count)
	{
		InitielizeBuckets(count);
		//m_count = count;
		//m_arr = new cValueBuckets[m_count];
	}

	~cValueBucketsArr()
	{
		if(m_arr)
			delete []m_arr;
	}
	unsigned int GetCount()
	{
		return m_count;
	}

	void InitielizeBuckets(unsigned int count)
	{
		m_count = count;
		m_arr = new cValueBuckets[m_count];
	}

	cValueBuckets& GetBucketsItem(unsigned int i)
	{
		return m_arr[i];	
	}


//cValueBucketsArr
static void CalculateEDmeanOneDimension(double &edMean,float predictiveValInput ,cValueBuckets &buckets);
	
void CalculateEDmean( double *edMean, unsigned int simCount, short int * predictiveSet)
{
	
	for(unsigned int j=0 ; j< simCount ; j++)
	{
		float predictiveValInput = ((float)predictiveSet[j])/100.0f ;
		CalculateEDmeanOneDimension(edMean[j],predictiveValInput , GetBucketsItem(j));//m_buckets[j]);
	}

}




	
};







class cPopChangeInWeight;
class cSimilarityFormula;
// Or:
// 1. Test if rounding is needed of 
class cStatisticStructure
{
public:
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//regression inputs 
	unsigned int m_count; // number of ??? (individuals?) YES, OUR 2,000 OR SO ARRY 
	unsigned int m_numOfPredictiveVars; // number of total variables
	unsigned int m_numOfControlledVars; // number of what if variatlves
	short int ** m_predictiveArr; // 2D array of predictive variables X individuals. YES, X HERE IS m_count. short int 16bit (st.d. * 100)
	double ** m_subPredictiveArr; 
	cStatisticStructure *m_parentStat;//if this varivle is set to null it means we have to allocated memory and then delete.
								//we also have to calculate one by one when setting the sd value from input profile target.
	float * m_predictabilityScores; // array of predicatbility score for each individual assessment. 1 is average. Use as weights for weighted average  
	float * m_predScoresAlt;
	short int * m_dependentArr; // the dependent variable (vector)
	

	// NEW VARIABLES: For the target individual 
	short int * m_predictive_set; // (part of regression output) array of predictive variables (addition to m_pred ictiveArr, one more individuals. The individual itself)
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//regression outputs (also serve as input for K-N algorithm)
	float m_regressionPerformanceScore; //  performace of regression:  "total explained variance" .
								//: What is this number in terms of regression success? between 0 and 1 - fraction of variance explained. Do not multiply this by 100 !!!  
	// array of regression coefficients for all variables. the size is of m_numOfPredictiveVars
	float * m_regressionBetaWeightArray; // coefficients of regression. Beta's, excluding the constant coefficient
	float m_regressionBetaZeroConstantTermWeight; // constant coefficient of regression beta0, including the constant
	float * m_pValueArray; //NEW . same size of m_regressionBetaWeightArray, each beta weight will have a p value
	//float * m_regressionSensitivityCoefficient; // NEW: 18/12/2011 SENSITIVITY FOR EACH VARIABLE, (Zuk)
	float *m_controlledVarsSensativity;
	float m_predictedResult; // guess for this individual (regression output) 
	float m_traditionalPrediction;
	

	double *m_predicted_dependentArr; // NEW: 8/12/2011 what is predicted by the regression for each individual, of length m_count
	short int m_regression_type; // NEW: 8/12/2011 Regression flag: //scheck if used
	// 0 - standard linear regression (LINEAR), 1 - two-stage linear 2 - stepwise regression  (STEPWISE),  3 - logistic regression (LOGISTIC)
	short int ***m_predictiveArrSamplePtr ;
	short int ** m_dependentArrSamplePtr ;
	double** m_predictionArrSamplePtr ;//12345 DE BUG1
	cStatisticStructure * m_parentThis ;

	double m_meanDependent;
	double m_sdDependent;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// input for K-N algorithm
	unsigned int m_kCount; // number of individuals in the k group. a prefix set of the m_count.
	unsigned int m_kControlCount; // number of individuals in the control group  
	unsigned int * m_kPositionList ; // array of indices for the group of k individuals out of the array. Look in m_pred ictiveArr
	unsigned int * m_kControlPositionList ; // array of indices for the control group of k_ctrl individuals out of the array m_pred ictiveArr

	unsigned int * m_kControlProfileIdArr ; //array size k control count with input profile id list. DONT UNDERSTAND THIS (Zuk)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//output of K-N algorithm
	//NEW m_controlPredictErrArr - Control Prediction Error Array.
	// Here we want the list of differences between predicted value and real dependent value from dependant array. 
	// the size of the array will be m_kControlCount. 
	// position i in the m_controlPredictErrArr will store the value in  m_predic tiveArr[m_kControlPositionList[i]] compute using k-n algorithm minus m_dependentArr
	float  * m_controlPredictErrArr; // length is m_kControlCount. Difference in prediction for each individual
	float m_KNperformanceScore; // performance of the k-n algorithm (?) YES, average of squared error
	float m_kAverage;
	double m_spPrediction;


//9 26 12
	cValueBucketsArr m_ValBucketArr;// * m_buckets;
//	unsigned int m_numOfEDbuckets;

	
	double* m_meanEdCtoS ;
	double* m_sdEdCtoS  ;
	double *m_meanArr;
	double* m_sdArr ;




	// 1. Add sensitivity: beta^2/var. explained in percent of st.d. (regression output)
	// 2. Add missing values -> 0 (average) 


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//))))))))))))))))))))))))))))))))))
	// Constructor: set to zero or null all values 
	cStatisticStructure(short int regressionType)
	{
//input for regression
		m_count = 0;
		m_spPrediction=0;
		m_numOfPredictiveVars = 0 ;
		m_numOfControlledVars = 0 ;
		m_predictiveArr = NULL;
		m_subPredictiveArr=NULL;
		m_predictabilityScores = NULL;
		m_predScoresAlt = NULL;
		m_dependentArr = NULL;
		m_regression_type = regressionType;
		


		m_predictiveArrSamplePtr = NULL;
		m_dependentArrSamplePtr = NULL;
		m_predictionArrSamplePtr = NULL;
		m_parentThis = NULL;
//regression output
		m_regressionPerformanceScore = 0.0;
		m_regressionBetaWeightArray = NULL;//
	//	m_regressionSensitivityCoefficient = NULL;
		m_controlledVarsSensativity = NULL;
		m_predicted_dependentArr = NULL;
		m_pValueArray = NULL;
		m_predictive_set = NULL;
		m_regressionBetaZeroConstantTermWeight= 0;

		//for the K-N algorithm
		m_kCount = 0 ;
		m_kControlCount = 0;
		m_kPositionList = NULL;
		m_kControlPositionList = NULL ;
		m_kControlProfileIdArr = NULL;
//K-N algorithh output
		m_controlPredictErrArr = NULL;
		m_KNperformanceScore = 0.0;
		m_predictedResult = 0;
		m_traditionalPrediction=0;
		m_kAverage = 0.0;
		m_meanEdCtoS = NULL;
		m_sdEdCtoS  =NULL;
		m_meanArr = NULL;
		m_sdArr =NULL;

		m_meanDependent=0;
		m_sdDependent=0;

//		m_buckets = NULL;
	//	m_numOfEDbuckets = 0 ;
	}
	// What does this method do? THIS IS TO OPEN THE MEMORY AND TO SENT THE SIZE READY TO GET DATA SET IN
	void SetData(unsigned int count, unsigned int numOfPredictiveVars, unsigned int numOfControlledVars, unsigned int kCount, 
											unsigned int kControlCount, cStatisticStructure * parentStat);
	
	// Destructor: Free memory
	~cStatisticStructure();
	

	void AlignPredictiblityScores()
	{
		for (unsigned int i=0; i < m_count ; i++)
		{
			if(m_predictabilityScores[i] != 0)
			{
				m_predictabilityScores[i] =1;
			}
			else
			{
				int ggg=0;
			}
		}
	}

	
void FillPercSimGroup_7_27_15(double* percSimArr,	double simEDconst,
	           double* edSDarr , double* edMeanArr);


	void CheckSampleSize_11_22_14(bool *predictiveAllowed, double sdDep);

void   CalculateMeanAndSumWeightsWithExp(double &mean, double &sumWeights, double &var, double exp);

void CalculateMeanAndSDofEDcontrolTPsp(unsigned int predictCohortCount);
	
double CalculateErrorPerInputCntrGrp_2_28_14( cStatisticStructure* ctrGrpStat, double exp);

void PrepareStructureOfSimAndReg_9_16_13(
			bool* allowedVariableReg , 
							bool* allowedVariableSim,  
							unsigned int simCount, unsigned int kCount );

void NormelizeAndCutExtremeDependent();

void ConvertDependentToByValue();

void FillPredictionArr9_17_13(double &spPTps , double * PT,
										bool *ISc , unsigned int regKcount, 
							unsigned int predictKcount, 
							cStatisticStructure* parentStat);//, bool** edBasedAllowedItems);

void AdjustPerCategoricalVaribles(double* meanEDarr , double* sdEDarr,
	short int* predSet, bool isAdjustAlsoContinuesVar, double** categoricalReplacment);

void CutExtremtePredValuesToThresholdNotSymetric();
	 //double meanUniverse , double varianceUniverse, double threshodForCenter, double expVal );

void RemoveCohortNonSimilarKcount( unsigned int perfListIndex, unsigned int predictCohortCount);

void FindThoseWhoGainWeight(bool* isGainArr);


double CalculateErrorComareTpParent_2_27_14(double meanParent, double sumWeightParent, 
						double varParent,     cStatisticStructure* parentStat ,  cStatisticStructure* ctrGrpStat, double exp);
	
	
//	void  AdjustPerEDAllowed(bool**	edBasedAllowedItems, 
//		      unsigned int kCount , unsigned int varIndex);
double CalculatePrediction_7_5_14(double* outWeights, unsigned int indexI , 
				bool* isTestGrp,double***edItoIIperJ, 
				cSimilarityFormula &sim , double* inWeights,
				         double constIncScore);

double CalculateKgrouopStatistics12_25_13(  double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel );

void FillEDbasedAllowedItems( bool**	edBasedAllowedItems, 
												  unsigned int kCount, unsigned int numOfSim);
	
void CalcualteSDofEDfromSP_6_28_14(double* meanEDarr, double* sdEDarr);

void CutExtremtePredValuesToThreshold( double meanUniverse , double varianceUniverse, double threshodForCenter, double expVal);

void CopyDependentArray(cStatisticStructure* parentStat);


void FillPercSimGroup(double* percSimArr,	double simEDconst , double* edSD);


double  FillPredictionArr10_18_13(
	                           double* preditiveValueArr,
	                               bool* isCntrOut,  
								   double &meanDep,
								   double &varDep ,   double &spPTps , double * PT,
										bool *ISc , unsigned int cohortCount, 
										unsigned int testGroupCount, 
							bool isToPredictOnlyMean , 
							cStatisticStructure* parentStatForTest , bool isFullTestCase,
							 bool isRegOnly, double lLevel );


void FillPredictionCalculations(double &exVarMeanCohort,
								double &exVarRegOnlyCohort, double &multipleRegOnlyEffect,
								unsigned int cohortSize,float* cleanWeightedVarAvera,double  lLevel);


void CalculatedMeanSDweighted(double &mean, double &variance,  double* arr, 
							  unsigned int count,float* predScores , double lLevel);

double CacuaultePredictionValueWithIgnore(  double mean, double sumWeight  , double itemValueToIgnore,  
			                            float weightOfItemToIgnore);

void CalculatedMeanSDweighted(double &mean, double &variance,  short int* arr, 
							  unsigned int count,float* predScores, double lLevel);

double CalculateErrorComareTpParent(double meanParent, double sumWeightParent, double varParent, cStatisticStructure* parentStat );

//void AdjustPerCategori calVaribles();

	void CheckExVarWithAdjustedSigArr(float &adjPerScore, bool* predSigStart, 
													   int posToCheckRemived, unsigned int testGroupCount);

	void ScoringEfficiencyArray(float* effArr, int* posArrFromBeta,
									unsigned int numToScore ,bool* predSigStart, 
									unsigned int testGroupCount, float exVarStart);

	
	static void SortPositionArr_9_14_13(int* posArr, const float* inputBetaSet, unsigned int size);

	






	
void   CalculateMeanAndSumWeights(double &meanParent, double &sumWeightParent , double &var);


void TrasferToSubSet( bool * predictiveSignificantSample);
	
void PrepareAllowedVariablesForCollectionVariations(bool* allowedVariable, 
										bool* inputAllowedVariables, unsigned int simCount);
	
	void PrepareMeanAndSDforGeneralAndED(unsigned int predictCohortCount);

	static double  CalculateCollectinoStrech(float * predScoreArr, unsigned int count);

	void TrasferBackToFullSet(float* betaArr , double* regressionBetaWeightArray, 
										bool* allowedVariable	, unsigned int P);

	
	void SetEDbuckets(cSimilarityFormula & formula);
	
	double CalculatedStrechness();
	static double  CalculatedStrechnessChildOverParent(cStatisticStructure* parentStat,
																 cStatisticStructure* childStat);
	static void UpdateChildOverParentStrechness(double sumStrechParent,
		                                          cStatisticStructure* parentStat,
																 cStatisticStructure* childStat);
	void UPdateValueBucketArrOnePerson(cValueBucketsArr & valueBucketArr, float predictScore, unsigned int i);

	void UPdateOneValueBucketObjForOnePerson( cValueBuckets & valueBucket,
												float predictScore, unsigned int i, unsigned int j);
	double CalculateKgrouopStatistics12_10_13( double &preShift, double &percenK, double &meanK, double &varK  , 
												 double* arr, float *weightArr,  
	                       unsigned int universCount, bool* isIn,  double lLevel, double* PT);//,
										//	unsigned int countK , double meanU , double varU );
	
 double CalculateKgrouopStatistics1_17_14( double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel,
						   double  predictonLearn, bool isOnlySimGroupPerfStart );
	
double   CalculateKgrouopStatistics12_12_13(  double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel,  double meanUniverse);//, double* PT);
double  CalculateKgrouopStatistics12_11_13(  
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel, double* PT);

double  CalculateKgrouopStatistics12_20_13(  double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel, double meanUniverse);
	

double  CalculateKgrouopStatistics12_21_13(  double &meanProfile,
												 double* arr, float *weightArr,  
	                       unsigned int countU, bool* isIn,  double lLevel);

void NormelizeDependent_7_26_14();


	void  UpdateChildOverParentStrechnessOLD(double sumStrechParent,
		                                  cStatisticStructure* parentStat,
															 cStatisticStructure* childStat);

	void FillRealArr(double *realValArr);
	
	double AdjustPredictionBasedOnKNstrength12_10_13(double &percMeanInportance, double &prediction , double* PT,
						unsigned int testGroupCount,  double lLevel);
	
	void AdjustPredictionBasedOnKNstrength12_7_13(double &percMeanInportance, double &prediction , double* PT,
						unsigned int testGroupCount,  double lLevel);

	double  FillPredictionArr1_19_13(double &percMeanInportance, double* preditiveValueArr, bool* isCntrOut, double &meanDep, double &varDep ,   double &spPTps , double * PT, bool *ISc ,
		unsigned int cohortCount, 	unsigned int testGroupCount, 
		bool isToPredictOnlyMean , cStatisticStructure* parentStatForTest  , 
		bool isFullTestCase,unsigned int subSetJ, bool* isCntrIn, bool isRegOnly, double lLevel,double varUnivers , bool withReducedKN);

	
	void FillRegOnlyPredictionArr(double &spPTps, double* PT, 
	             double** preditiveValueArrTD ,bool* ISc, cStatisticStructure* parentStatForTest, unsigned int testGroupCount);
	

	static void LinearRegressionInternalDoubleAPI( double &averageSE, double &variance, double & zeroConstant, 
		double * betaArr , double& regressionPerformanceScore,double * predicted_dependentArr,
							double **predictiveArr,	unsigned int N, 
			unsigned int p,  double * dependentArr, double * predictabilityScores, 
			unsigned int sizeOfTestGroup , bool isControlGroup, bool isLogisticReg);

//	void CalculateEDVariance( float *edVariance, cSimilarityFormula &similarity, short int * predictiveSet);
	void CalculateEDsensativity( float *edSensativityArr,  cSimilarityFormula &similarity);//, short int * predictiveSet)
	void UpdateEdSensativity( float *edSensativityArr, 	 cSimilarityFormula &similarity);

	void ConsiderEfficientPredictoinVariables_9_13_13( bool* predictiveSignificantSamp, unsigned int testGroupCount  );

	void AdaptBetaSet( cStatisticStructure* parentStat);

	static double GetVarianceWithBoolArr(double &median, double &mean, double &var, double* arr, float *weightArr,  
	                       unsigned int testGroupCount, bool* isIn,  double lLevel, unsigned int predictKcount);
void GetCleanAverage ( double &cleanKaverage , 
	  float* cleanWeightedVarAvera,  double sumOfCohortScores, double kAverage, 
	    float* weightedVarAvg, float predictScore,  
		   double dependent,  short int* predictiveArr);

void AdjustPredictionBasedOnKNstrength(double &prediction , double* PT,
						unsigned int testGroupCount,  double lLevel );

//	void Calc ulateEDmean( float *edMean, cSimilarityFormula &similarity, short int * predictiveSet);
//	static void Calcula teEDmean OneDimension(float &edMean,float predictiveValInput ,cValueBuckets &buckets);
	static 	double CalculatePredScoreFromEditDisScore(double editScore, double knExpConstant,  
		double knConstant);// ,double meanScoreArr, double sdScoreArr );
			//		predictiblityScore  = 	1/(1+ (editScore * constantScoreWeight ));//1.0f / (scoreArr[i] + constantScoreWeight );
	static double CalculateEditDistanceScoreFromPredictabilityScore (double predictiblityScore,  double constant );

//9 11 13
	void ConsiderEfficientPredictoinVariables(	bool* predictiveSignificantSample, unsigned int testGroupCount );
	void AlocateMatchingGroups8_15_12(bool *kControlflagged, unsigned int &controlFlaggedCount, 
							  bool * controlOthers, unsigned int &controlOthersCount,unsigned int count);

//EEE for three functions 	
	//static void StepRegression(	cStatisticStructure  *stat ); // step-wise regrerssion in an order based on array ordering .. ?  We don't need this. It is part of linear regression 
	void LinearRegression ( double &averageSE ,double &variance,double &predictiveVariance,float * similarityflags , 
		unsigned int simVarCount	, double *allListVarianceArr, bool *predictiveSignificantSample ,
		unsigned int sizeTestGroup , bool isControl , bool isSetStraightReg);
		
	
	void TrasferBackToFullSet_2_7_24(double* orgBetaArr , double*  regressionBetaAray,   bool*  isPredictive, int sigCount, 
				   double** twoDimArrShort,   double** twoDimArr, int N, int P);

	void TrasferToSubSet_2_7_24(  double** twoDimArrShort,	bool*   isPredictive, double** twoDimArr, int N, int P,  double* meanPredArr);

	void FillPerGapBetweenHihgestLowestVariable(double* gapBetweenPercLowToHighVar,  double* meanPredArr,
	bool* isPredictivee, double** predictiveArr,   int N,   int simVarCount);
	
	bool LinearRegression2_7_24(double* betaArr, double &averageSE ,double &variance,double &perforanceScore, 
		double** twoDimArr, double*depArr,	unsigned int simVarCount,bool *isPredictive, unsigned int sizeTestGroup,
		bool  isLogReg );
	
	void CalculatePopData( double & percContFlaggedWgt, double & percContOthersWgt, unsigned int totalCount);

	float CalculateMeanVal(unsigned int flagPos);
//	void FillPredictionArr( double* universalPrediction, bool *isInSimGroup, 
//												double *predicScoreModifier	,bool isRegressionOnlyPred );

	static void LinearRegressionInternal(float &averageSE ,float &variance,	float & regressionBetaZeroConstantTermWeight, 
		float * regressionBetaWeightArray , float& regressionPerformanceScor,double * predicted_dependentArr,
		float *pValueArray,		short int **predictiveArr,	unsigned int N, 
			unsigned int p,  short int * dependentArray, float * predictabilityScores,  short int regression_type);	

	
	double GetSPprediction() { return m_spPrediction;}
	
	double TraditionalPredict(short int * predictiveSet)
	{
		double pred = m_regressionBetaZeroConstantTermWeight;
		for (unsigned int j=0; j < m_numOfPredictiveVars; j++) 
		{
			pred += m_regressionBetaWeightArray[j] * ((double)predictiveSet[j]);
		}  
		return pred;
	}
	
	void PrepareAllowedVariablesForCollectionVariations_9_6_13(bool* allowedVariableReg , 
				bool* allowedVariableSim,  unsigned int simCount,
				unsigned int kCount , cSimilarityFormula &simFormula);

	bool IsMatchingAnyFlag(short int * matchingSet, short int * coreSet, cSimilarityFormula & newFormula);
	void FillZeroPredictibilityScores();
	void CalculatedRegressionConstantsNEW12345678(float &constantRecomendControl,
									   float &totalControlWeightSelf, 
			 unsigned int kConstant,   int functionCategory );
		
	static bool IsMatchingAllFlagsNew(float & flaggedDistance, float & nonFlaggedDistance, short int * matchingSet, short int * coreSet,
		cSimilarityFormula & newFormula);

	void CalculateFlagged_SE_AND_VAR__08_15_12 ( 	float &controllFlagedSE,
						float & controlFlaggedVar, float &cFlaggedWeightt,	float &controlOthersSE, 
															float &controlOthersVar, float & cOthersWeigiht);


	void CalculateFlagged_SE_AND_VAR__08_25_12 ( 	float &controllFlagedSE,
			float & controlFlaggedVar, float &cFlaggedWeightt,	float &controlOthersSE, 
			float &controlOthersVar, float & cOthersWeigiht, 
			cPopChangeInWeight & popChgObj,	double * predictedValArr, double * realValArr);
	
	void PrepareAllowedVariablesForCollectionVariationsNEW(bool* allowedVariable, 
										bool* inputAllowedVariables, unsigned int simCount);



	void CalculateFlagged_SE_AND_VAR__08_25_12 ( 	
	float &controllFlagedSE,
			float & controlFlaggedVar, float &cFlaggedWeightt,	float &controlOthersSE, 
			float &controlOthersVar, float & cOthersWeigiht, 
			cPopChangeInWeight & popChgObj, double * predictionArrUniversalBased,
			double * predictedValArr, double * realValArr,  cStatisticStructure * universalStat);


	
	//	float CalculateAndRecomend ShiftInPrediction(unsigned int count,float *weightedVarAvg,float kAverage );

	float CalculateAndRecomendShiftInPrediction(unsigned int totalCount);

	float CalculateAndRecomendShiftInPredictionSubSet(unsigned int controlStartIndex,
					unsigned int controlSetSize, unsigned int count, float 	kAverage, float  * weightedVarAvg);
	void CalculateKaverageForPredictionShift(float &kAverage, float *weightedVarAvg, float & weightOfKcount, 
								unsigned int controlStartIndex,unsigned int controlSetSize, unsigned int totalCount);


//	void AdjustKFirstMembersScoresNEW(unsigned int numToAdjust, float nConstant,
//								float expKconstant, double kConstant, bool isCreatingKscore);

	void CalculateFlagged_SE_AND_VAR__05_11_12 ( float &predictionShift, float &sumOfMeanDistanceFlaggedToOthers,
		float &controllFlagedSE, float & controlFlaggedVar, float &cFlaggedWeightt,
		float &controlOthersSE, float &controlOthersVar, float & cOthersWeigiht,
		cSimilarityFormula &childDeltaFlags, unsigned int kConstant, 	unsigned int  kControlCount, 
		unsigned int flaggedCount, 
		int functionCategory, float curNconstant, float defaultKconstant);


	
	void UpdateAllVarialbeVals(float *varValArr, short int * predictiveArr, 
													float weight, cSimilarityFormula & newFormula);
	void CalculateEditDistanceControlFlaggedAndControlOthers(float *cntrFlgedVarValArr, 
																float *cntrOthersVarValArr,cSimilarityFormula & newFormula);
	void CalculateEditDistanceCollection(float * colVarValArr, cSimilarityFormula & newFormula);


	void UpdateFlaggedVarialbeVals(float *flaggedSumSimVariablesValArr, cSimilarityFormula& childDeltaFlags,
				short int * predictiveVarArr,float weightOfControlItem);	
	void CalculateFlaggedPopulationSE_NEW (float  &flaggedSE , float &flaggedPerformance,
					float &varFlaggedDependent,		float &othersSE, float &othersPerformance, float &varOthersDependent ,	
					cSimilarityFormula &parentFlags, cSimilarityFormula &childFlags, unsigned int count );
	void CalculateVariableMeanAndVariance(float * meanArr , float *varianceArr , unsigned int j );
	void CalculateItemsContributionToVariance(float &sumOfAllContribution ,	float* itemsContributionToVariacne,
													 float *meanArr, float *varianceArr, float *missingVarianceArr);
	
	void CalculateNflagged_5_10_12 ( 		float &partialFlaggedSE, float &partialFlaggedVar, 
		float &partialFllagedWegiht,float &otthersSE , float & otthersVar,	float & othersWegiht,	
		cSimilarityFormula &childDeltaFlags,unsigned int maxFlaggedCount);
	float CalculateVar(unsigned int flagPos, float mean);


//	void CalculateFlagged_S E_AND_VAR_12345678 ( 
//		float &controllFlagedSE, float & controlFlaggedVar, 
//		float &controlOthersSE, float &controlOthersVar,
//		cSimilarityFormula &childDeltaFlags, unsigned int kConstant, 	unsigned int  kControlCount, 
//		int functionCategory);
//	void Adjus  tKFirstMembersScores(unsigned int numToAdjust, float nConstant, float kConstant);

//	void CalculateFlagged_SE_AND_VAR_5757575757 ( 
//		float &controllFlagedSE, float & controlFlaggedVar, 
//		float &controlOthersSE, float &controlOthersVar,
//		cSimilarityFormula &childDeltaFlags, unsigned int kConstant, 	unsigned int  kControlCount, 
//		int functionCategory);
	
	void CalculateKaverageAndWeightedVarAvg(float & kAverage, float &varDep, float *weightedVarAvg,
										double &sumOfCohortScores, unsigned int kCount,
							 cPopChangeInWeight *popWeight);//, bool** edBasedAllowedItems);



/*	void CalculateFlagg ed_SE_AND_VAR_12345 (float &constantConttrol, float &percOfControlWeight,float &kControlSE, float & varControlDep,
					float  &flaggedSE , float &flaggedPerformance,
					float &varFlaggedDependent,		float &othersSE, float &othersPerformance, float &varOthersDependent ,	
					cSimilarityFormula &parentFlags, cSimilarityFormula &childFlags, 
					cSimilarityFormula &childDeltaFlags , unsigned int partialFlaggdeMaxCount, unsigned int  kConstant, 
					unsigned int  kControlCount,  int typeOfRegressionConstant);
*/

	void CalculateFlagged_SE_AND_VAR_12345 ( 
		float &partialFlaggedSE, float &partialFlaggedVar, 
		float &otthersSE , float & otthersVar,			
		float &controllFlagedSE, float & controlFlaggedVar, 
		float &controlOthersSE, float &controlOthersVar,
		cSimilarityFormula &childDeltaFlags,
		unsigned int  partialFlaggdeMaxCount, unsigned int kConstant, 	unsigned int  kControlCount, 
		bool isUseSameWeightsInKcount, bool isUseZeroScoreForKcontrol, int functionCategory);

	void CalculatedRegressionConstantsNEW(float &constantRecommendFlagged, 
			float & constantRecommendOthers, float &constantRecomendControl,
			bool * partialFlagged,bool * others, unsigned int kConstant, bool isFlagged, bool isUseSameWeightsInKcount);
	void CalculateFlagged_SE_AND_VAR (float  &flaggedSE , float &flaggedPerformance,
					float &varFlaggedDependent,		float &othersSE, float &othersPerformance, float &varOthersDependent ,	
					cSimilarityFormula &parentFlags, cSimilarityFormula &childFlags, cSimilarityFormula &childDeltaFlags);
	void AdjustPredictiblityPerFrequency(float &predictiveVariance, double  *allListVariableVariance, bool *predictiveSignificantSample);

	void CalculateMissingVarianceData(float &allVariableSumMissingVariance, float *meanArr, 
			float *varianceArr , float * missingVarianceArr ,   float * sumOfMissingVariances ,float sumOfWeights, 
						 double *allListVariableVariance,  bool *predictiveSignificantSample, float progressStrength);
	void AdjustPredictiblityPerContributionWeight( float *itemsContributionToVariacne,float sumOfAllContribution,
														float allVariableSumMissingVariance ,	   float sumOfPredictWeights);
		
	void CreateSamplePredictiveSets(short int ** flaggedPredictiveSets , short int * flaggedDependets ,
		  unsigned int countOfFlagged,    short int ** othersPredictiveSets , short int * othersDependets ,
		 unsigned int countOfOthers , cSimilarityFormula & flags);

	void CalulateKNperformance (unsigned int predictCount, float predictionShift);
	//void CalulateK NperformanceNEW (unsigned int countOfHistogramUnit);

//	void CalulateKNperf ormanceForInputK(float & prediction, float & performance,
  //			short int * predictiveSet, short int dependentVar, short int ** kPredictiveSet, 
	//								short int* kDependentArr, 	cSimilarityFormula & formula);
	
/*	void CalculateFlag gedPopulationSE (float & constantConstrol, unsigned int testGroupCount, float &kControlSE,float  &flaggedSE , float &flaggedPerformance, float &varFlaggedDependent,
				float &othersSE, float &othersPerformance, float &varOthersDependent ,	
				cSimilarityFormula &parentFlags, cSimilarityFormula &childFlags, 	unsigned int count, float tempKconstant );
*/
//	void CalulateKNperformanc eForInputKwithReverse(float & prediction, float & performance,
//  	short int * kControlPredictiveSet, short int kControlDependentVar, short int ** kPredictiveSet, short int* kDependentArr  );

	void GetFlaggedCount(int &fc, int &oc, cSimilarityFormula &flags);

	void CalculatedRegressionConstants(float &constantRecommendFlagged, 
									float &constantRecommendOthers, cSimilarityFormula & childDeltaFlags);


//	void CalulateKNperformanceNEW(short int & prediction, float & performance,
	//	short int * predictiveSet, short int dependentVar, 	cSimilarityFormula & formula, float * editDistanceScores );

	void FillEditDistanceScores(float *editDistanceScores, short int* predictiveSet, 
										   cSimilarityFormula & formula);

	void CalculateKgroupStatisticsNEW(float &kAverage, float *weighted_var_average, 
													   float * editDistanceScores);

	
void AlocateMatchingGroups(bool *kControlflagged, unsigned int & controlFlaggedCount, 
												bool * controlOthers, unsigned int &controlOthersCount, 
						unsigned int	count, unsigned int maxFlaggedCount,  float matchDis,
						cSimilarityFormula& childDeltaFlags);

	static bool SymmetricMatrixInvert(double  **V, unsigned int predictedVariableNum); // function for inverting a matrix 

	float simple_linear_regression(float *Y, short int **X,unsigned int pIndex,unsigned  int N, float *r_square, float *pval);

	void	FlexiblePredictionErrorCalc(float * flexibleError, float *predictionArr, 
								  short int * dependentVals,  unsigned int count, 
								  unsigned int countOfHistogramUnit,cSimilarityFormula &kDistrubution);
	void 	SortThreeArraysPerPredictionValue(float *predictionArr,   short int * dependentVals,  unsigned int count);
	//float ErrorValue(short int *errArray, unsigned int count);
	void CalculateGroupPreidctionOld(float * errorArray, float *predictionArr, 
					  short int * dependentVals, unsigned int startIndex, unsigned int count);

	void CalculateKgroupStatisticsDependentAndPredictive(float *weighted_var_average, 
																					float &standardDevKgroupDepepdent);

	void CalculateKgroupStatisticsDependentAndPredictiveOld(float *weighted_var_average, 
																					float &standardDevKgroupDepepdent);

	void TrasferToSubSet(   short int **predictveArr ,	  bool * predictiveSignificantSample);

	//TrasferToS ubSet(  double** predictiveArr  ,double **DPrg, bool* allowedVariable );
		
	void TrasferBackToFullSet(float *regressionBetaWeightArray ,float *pValueArray, 
				bool *predictiveSignificantSample	, unsigned int simCount);

		//by sd : standardDevPredictionControl and multiple by k group sd: standardDevKgroupDepepdent
//	void AdjustDeltaPredictionControlGroup(float * delta_prediction_ctrl, float averargePredictedDeltaValue ,
//						float 	standardDevPredictionControl, float standardDevKgroupDepepdent ,cSimilarityFormula &  kContrtolPredDis);

	void CalculateGroupPreidction(float * errorArray, float *predictionArr, 
		 short int * dependentVals, unsigned int startIndex, unsigned int count, cSimilarityFormula & kDistribution);

//void 	cStatisticStructure::CalculateGroupPreidction(float * errorArray, float *predictionArr, 
//					  short int * dependentVals, unsigned int startIndex, unsigned int count);


	bool IsAlmost0edCohort(unsigned int predictiveIndex,	double minSDforAllowedRegVar, unsigned int countToCheckSig);

	void CheckSampleSize(bool *isSignificant);
	void CheckSampleSizeNew(bool *isSignificant);
	bool IsSignificantSampleSizeOnePredictive(unsigned int predictiveIndex, double minSDforAlllowedRegVar, double sdDep);
	
	void 	CalculateHistogramDistribution(cSimilarityFormula & groupDis , unsigned int * positionList, 
		unsigned int startIndex,unsigned int count);

	void CalculateKcontrolGroupStatistics(float * delta_prediction_ctrl,float &averargePredictedDeltaValue,
			float &standardDevPredictionControl, float * weighted_var_average );



static bool IsMatchingAllFlags(short int * matchingSet, short int * coreSet,
											 cSimilarityFormula & newFormula , float matchedDis);

void CalculateFlagged_SE_AND_VAR_NEWWWWW (float &kControlSE,float  &flaggedSE , float &flaggedPerformance,
					float &varFlaggedDependent,		float &othersSE, float &othersPerformance, float &varOthersDependent ,	
					cSimilarityFormula &parentFlags, cSimilarityFormula &childFlags, cSimilarityFormula &childDeltaFlags );

};

class cTargetSort; class cProfileTarget; class cPerformanceList;

class cStatisticStatCover
{
public:
	cStatisticStructure** m_statArr ;
	unsigned int m_wivCount ;
	cStatisticStatCover(unsigned int count,unsigned int numOfPredictiveVars,
		unsigned int numberOfWhatIfFields, unsigned int kCount, unsigned int kControlCount,
		unsigned int resultIndex , cTargetSort & targetSort , cProfileTarget * subjectTarget,
		bool  isLearningTime, float constantScoreWeight, unsigned int numOfControlGroup,bool isControlGroup,
		double * meanArr, double * varianceArr, cStatisticStructure * parentStat , bool isToNormelizeInput, 
		double expConstnat, unsigned int* dynamicPosArr, unsigned int dynPosArrSize);

	//10 25 16
	cStatisticStatCover(unsigned int count,unsigned int numOfPredictiveVars,
		unsigned int numberOfWhatIfFields, unsigned int kCount, unsigned int kControlCount,
		unsigned int resultIndex , cTargetSort & targetSort , cProfileTarget * subjectTarget,
		bool  isLearningTime, float constantScoreWeight, unsigned int numOfControlGroup,bool isControlGroup,
		double * meanArr, double * varianceArr, cStatisticStructure * parentStat , bool isToNormelizeInput, 
		double expConstnat, unsigned int* dynamicPosArr, unsigned int dynPosArrSize, bool* isInDynamicPosArr);


	~cStatisticStatCover();
	
	void  LinearRegression(float &averageSE ,float &variance,float &predictiveVariance,float * similarityFlags, 
				unsigned int simVarCount, double *allListVarianceArr, double *universalRegVarianceArr);


	//10 25 16
	void  StatisticProcess ( cTargetSort &smallSizeTargetSort, 
		  char  statisticType ,		unsigned int resultIndex ,  cProfileTarget * profileTarget, 
		   unsigned int kCount, unsigned int kControlCount,   bool isLearningTime,
		   float constantScoreWeight, unsigned int numOfControlCount, bool isControlGroup,
		   double * meanArr, double * varianceArr, bool isToNormelizeInput , double exponConst,
		   unsigned int* dynamicPosArr, unsigned int dynPosArrSize, bool* isItemPosIncluded);
	//10 25 16
	bool InitielizeStatisticStructure(cStatisticStructure* stat,  cProfileTarget ** arr,float *scoreArr,
			unsigned int resultIndex, char statisticType , cProfileTarget * profileTarget, 
			bool isLearningTime,float constantScoreWeight, unsigned int numOfControlCount, bool isControlGroup,
			double * meanArr, double * varianceArr, bool isToNormelizeInput,
			double meanScoreArr, double sdScoreArr , double exponsnConstant,
			unsigned int* dynamicPosArr, unsigned int dynPosArrSize, bool* isInDunamicPosArr);
	
	float GetCountInfoForFlagged5_29_12 (float & difOfFlaggedFromTotal, float * leaderArrOfCorelations, cPerformanceList & perfList, 
		unsigned int listIndex, bool * isSignificant);
		//( float * weightsArr , cPerformanceList &perfList);


/*	void CalculateFl aggedPopulationSE (float & constantConstrol, float &percOfControlWeight, float &kControlSE, float & varControlDep, float  &flaggedSE , float &flaggedPerformance, float &varFlaggedDependent,
				float &othersSE, float &othersPerformance, float &varOthersDependent, 
					cSimilarityFormula &parentFlags, cSimilarityFormula &childFlags, 
					cSimilarityFormula &childDeltaFlags,
					unsigned int count, float * whatIfWeights , 
					unsigned int partialFlaggdeMaxCount, unsigned int  kConstant, 	unsigned int  kControlCount , int typeOfRegressionConstant );
*/

//	void CalculateFlagge dPopulationSE111111 (
//			float &controllFlagedSE, float & controlFlaggedVar, 
//			float &controlOthersSE, float &controlOthersVar,
//			cSimilarityFormula &childDeltaFlags,
//			float * whatIfWeights,
//			unsigned int  kConstant, 	unsigned int  kControlCount,  int functionCategory);


void	CalculateFlaggedPopulationSE (
			float &partialFlaggedSE, float &partialFlaggedVar, 
			float &otthersSE , float & otthersVar,			
			float &controllFlagedSE, float & controlFlaggedVar, 
			float &controlOthersSE, float &controlOthersVar,
			cSimilarityFormula &childDeltaFlags,	
			float * whatIfWeights,
			unsigned int  partialFlaggdeMaxCount, unsigned int  kConstant, 	unsigned int  kControlCount,
			bool isUseSameWeightsInKcount , bool isUseZeroScoreForKcontrol, int functionCategory);


	void DistributeSamplePtrs(cStatisticStatCover &otherCover);

//	void Adjus tKFirstMembe rsScores(unsigned int numToAdjust, float nConstant, float kConstant);

	//void GetCountInfoForFlagged(float &curFlaggedCount, float &curOthersCount );

	void GetCountInfoForFlagged(float &flaggedCount, float &othersCount, float &totalCount,
				cSimilarityFormula & childFlags, unsigned int maxNumberOfPartialFlagged);


	void AdjustPrediction(cStatisticStatCover ** controlStatCover, unsigned int count);
	
	void XXXXXXXXXXXXXXX(float * probNatural,float *probCondLeader,float &sumOfTotalWeights,
		float &sumOfLeaderConditionWeights,	cPerformanceList& perfList, unsigned int listIndex,	 bool* isSignificant);

	void XXXXXXXXXXXXXXX_6_12_12(float * probNatural,float *probCondLeader,float &sumOfTotalWeights,
				float &sumOfLeaderConditionWeights, cPerformanceList& perfList, unsigned int listIndex,	 bool* isSignificant);

//	void  CalculateFlag gedPopulationSE111111 (
//			float &controllFlagedSE, float & controlFlaggedVar, 
//			float &controlOthersSE, float &controlOthersVar,
//			cSimilarityFormula &childDeltaFlags,
//			float * whatIfWeights,
//			unsigned int  kConstant, 	unsigned int  kControlCount,  int functionCategory);

//void CalculateFlaggedPopulationSE1111(
//			float &controllFlagedSE, float & controlFlaggedVar, 
//			float &controlOthersSE, float &controlOthersVar,
//			cSimilarityFormula &childDeltaFlags,
//			float * whatIfWeights,
//			unsigned int  kConstant, 	unsigned int  kControlCount,  int functionCategory);
	


};

class cMedian
{
	float* m_weightsArr;
	unsigned int m_size;
public:
	cMedian(unsigned int size);
	~cMedian();
	void Add(float weight, float value);
	float GetMedian(float sumOfweights);
	float GetValueFromIndex( unsigned int index);
	unsigned int GetIndexFromValue(float value);
	float FindAverageOfEdge ( float edgeOfLowScores, float threW , int lowEdgeOrHighEdge );
	float GetTradAverage(float sumOfweights, float average);

};






class cMapingPreArr
{
	unsigned int m_count;
	unsigned int m_numOfPredictiveVars;
	cStatisticStructure* m_stat;

	void CreateMappingAllVariables();
public:
	
	double** m_replacedPredTwoDim;
	double** m_categoMaptingBucket;
	double* m_meanReplacedVar;
	double* m_sdReplacedVar;

	cMapingPreArr( cStatisticStructure* stat);

	~cMapingPreArr();

	double GetMappedOrRegValue(short int** arr, unsigned int i , unsigned int j);
		
	void MapCatergricalVariableInStat(bool* predictiveAllowed);


	void CheckPredictivePower (bool* predictiveAllowed, double sdDep);

	
//	void ReplaceTwoDimPredWithCategoryMean();

	double CalcualtePredictedValue( short int* predictive_set);
	void FillPredictionArr( double* predArr, short int** testPredSet, unsigned int count);

	void FillStrengthArr(double* strengthArr);
	//11 19 14
	

};