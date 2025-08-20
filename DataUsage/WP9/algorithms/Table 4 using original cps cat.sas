
filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");




****TABLE 4 Proportional Odds Stats Stratified Model ****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	run;

* Adjusted*;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  province_code(ref = "ON") facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident province_code 
facility_size urban 
	/maxiter = 100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1;
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


**Adjusted**;
	ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON')  cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period  age_cat  cps_cat adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size province_code 
	/ maxiter=100 unequalslopes=(cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1;
	by female;
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


**Adjusted**;
	ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON')  cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period female  cps_cat adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size province_code 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
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


**Adjusted**;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON')   adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") cps_cat(ref='0') /param=ref;

	model drs_cat_t2 = period female  age_cat  adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident facility_size province_code 
	/unequalslopes=(female  adl_cat abs_cat new_resident province_code urban)
	maxiter=100;
	where no_mood_symptoms = 1;
	
	oddsratio period / at (cps_cat ="0");
	oddsratio period / at (cps_cat ="1");
	oddsratio period / at (cps_cat ="2");
	oddsratio period / at (cps_cat ="3");
 
run;




***Unadjusted using Collapsed CPS***;
ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref='Pre-COVID')  /param=ref;
	model drs_cat_t2 =   period;
	where no_mood_symptoms = 1;
	by cps_cat_collapsed;
	run;


**Adjusted using collapsed cps variable**;
proc sort data=combined; by cps_cat_collapsed; run;
	ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON')   adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period female  age_cat  adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size province_code 
	/ maxiter= 100 unequalslopes=(female  adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1;
	by cps_cat_collapsed;
run;

Proc freq data= combined;
Table cps_cat_collapsed;
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

* Adjusted*;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size urban 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident  urban);
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

* Adjusted*;
	ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	   /param=ref;
	model drs_cat_t2 = period female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
province_code  urban 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
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


* Adjusted*;
	ods select oddsratios;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size province_code 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code);
	where no_mood_symptoms = 1;
	by urban;
run;
