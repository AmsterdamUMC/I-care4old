*Run before any analysis;
*------------------------------------------------*;

filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");


*Add in period effect and fit among full cohort;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	run;

* adjusted*;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") age_cat(ref='0') chess_cat(ref = '0') cps_nh2(ref = '0') 
abs_cat(ref = '0') pain_nh2 (ref ='0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period female age_cat chess_cat i1ff poor_sleep conflict f2g cps_nh2 abs_cat new_resident urban province_code  
	/ unequalslopes=(cps_nh2 abs_cat new_resident province_code);
	where no_mood_symptoms = 1;
run;


* Use the binary Variable here;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_bin_t2 =   period;
	where no_mood_symptoms = 1;
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") age_cat(ref='0') chess_cont_cat(ref = '0') cps_nh2(ref = '0') 
abs_cont_cat(ref = '0') pain_nh2 (ref ='0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period female age_cat chess_cont_cat i1ff poor_sleep conflict f2g cps_nh2 abs_cont_cat new_resident urban province_code  
	/maxiter = 100 unequalslopes=(female cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
run;


*Run model among province sub-groups;

proc sort data=combined; by province_code; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by province_code;
	run;

*** Adjusted****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") age_cat(ref='0') chess_cat(ref = '0') cps_nh2(ref = '0') 
abs_cat(ref = '0') pain_nh2 (ref ='0')/param=ref;
	model drs_cat_t2 = period female age_cat chess_cat i1ff poor_sleep conflict f2g cps_nh2 abs_cat new_resident urban pain_nh2   
	/maxiter=100 unequalslopes= (cps_nh2 abs_cat new_resident);
	where no_mood_symptoms = 1;
	by province_code;
run;

/*ods select oddsratios;*/
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") age_cat(ref='0') chess_cont_cat(ref = '0') cps_nh2(ref = '0') abs_cont_cat(ref = '0') /param=ref;
	model drs_cat_t2 = period female age_cat chess_cont_cat i1ff poor_sleep conflict f2g  cps_nh2 abs_cont_cat new_resident urban facility_size 
	/maxiter=100 unequalslopes=(female cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by province_code;
run;

*Run model among fac size sub-groups;

proc sort data=combined; by facility_size; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by facility_size;
	run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") chess_cont_cat(ref = '0') cps_nh2(ref = '0') abs_cont_cat(ref = '0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period chess_cont_cat i1ff poor_sleep conflict f2g  cps_nh2 abs_cont_cat new_resident urban province_code / unequalslopes=(cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by facility_size;
run;

****Adjusted***;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID")Province_code (ref='ON') age_cat(ref='0') chess_cont_cat(ref = '0') cps_nh2(ref = '0') 
abs_cont_cat(ref = '0') pain_nh2 (ref ='0')/param=ref;
	model drs_cat_t2 = period female age_cat chess_cat i1ff poor_sleep conflict f2g cps_nh2 abs_cont_cat new_resident urban pain_nh2   
	/ unequalslopes= (cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by facility_size;
run;

*Run model among location sub-groups;
proc sort data=combined; by urban; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by urban;
	run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") chess_cont_cat(ref = '0') cps_nh2(ref = '0') abs_cont_cat(ref = '0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period chess_cont_cat i1ff poor_sleep conflict f2g  cps_nh2 abs_cont_cat new_resident  province_code / unequalslopes=(cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by urban;
run;



*Run model among age sub-groups;
proc sort data=combined; by age_cat; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by age_cat;
	run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") chess_cont_cat(ref = '0') cps_nh2(ref = '0') abs_cont_cat(ref = '0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period chess_cont_cat i1ff poor_sleep conflict f2g  cps_nh2 abs_cont_cat new_resident urban province_code / unequalslopes=(cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by age_cat;
run;



*Run model among CPS sub-groups;
proc sort data=combined; by cps_cat; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by cps_cat;
	run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") chess_cont_cat(ref = '0') abs_cont_cat(ref = '0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period chess_cont_cat i1ff poor_sleep conflict f2g abs_cont_cat new_resident urban province_code / unequalslopes=(abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by cps_cat;
run;



*Run model among sex sub-groups;
proc sort data=combined; by female; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by female;
	run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") chess_cont_cat(ref = '0') cps_nh2(ref = '0') abs_cont_cat(ref = '0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period chess_cont_cat i1ff poor_sleep conflict f2g  cps_nh2 abs_cont_cat new_resident urban province_code / unequalslopes=(cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by female;
run;



*Run model among Pain sub-groups;
proc sort data=combined; by pain_nh2; run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by pain_nh2;
	run;

ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") chess_cont_cat(ref = '0') cps_nh2(ref = '0') abs_cont_cat(ref = '0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 = period chess_cont_cat i1ff poor_sleep conflict f2g  cps_nh2 abs_cont_cat new_resident urban province_code / unequalslopes=(cps_nh2 abs_cont_cat new_resident);
	where no_mood_symptoms = 1;
	by pain_nh2;
run;

***** Full Model*****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0')  age_cat(ref='0') chess_cont_cat(ref = '0') cps_nh2(ref = '0') 
abs_cont_cat(ref = '0') pain_nh2 (ref ='0') province_code(ref = "ON")/param=ref;
	model drs_cat_t2 =  female age_cat chess_cont_cat i1ff poor_sleep conflict f2g cps_nh2 abs_cont_cat new_resident urban province_code/ unequalslopes;  
	where no_mood_symptoms = 1 and period = "COVID";
run;
