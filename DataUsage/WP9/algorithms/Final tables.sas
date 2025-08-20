filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");

*------------------------------------------------*;

****Supplement TABLE 1****;
***Female*****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   female;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


	proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   female/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****Age_cat****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   age_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****Married****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   Married;
		where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****Lived_alone****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
		model drs_cat_t2 = Lived_alone;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****CPS_cat******;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   cps_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

	proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   cps_cat/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****ADL_cat****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = adl_cat; 
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = adl_cat/unequalslopes; 
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


***CHESS****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = chess_cat; 
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****ABS_cat******;
	proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   abs_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   abs_cat/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


****ISE******;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   ise_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

****Major comorbidity count****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') 
Major_comorbidity_grp (ref='0')abs_cat(ref = '0') pain_nh2(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   Major_comorbidity_grp;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;
****Pain******;
	proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   pain_nh2;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


*** Anxiety diagnosis I1ff***;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   i1ff;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

***Conflict***;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   conflict;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

***Does not adjust F2g***;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   F2g;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


***Newly admitted resident aa8***;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	new_resident;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	new_resident/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


***Province***;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	province_code;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;
	
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	province_code/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


***facility_size****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	facility_size;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


***urban****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	urban;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   	urban/ unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


*****************************************************************************************************************************************************


****TABLE 1 Baseline Characteristics****;
proc freq data=combined;
	table(

		female 
		age_cat 
		married
		cps_cat 
		/*cps_cat_collapsed*/
		adl_cat 
		chess_cat 
		ise_cat
		abs_cat
		pain_nh2
        i1ff /*anxiety*/
		conflict
		f2g /*change hard*/
		new_resident
		province_code
		facility_size
		urban
		Poor_sleep
		Major_Comorbidity_grp


		 )* period/chisq;

	where no_mood_symptoms = 1;

run;

******************************************************************************************************************************************************
****TABLE 2 Transitions in Mood****;
*** us the variable first then period and DRS***;

****Overall****;
proc freq data=combined;
table   period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 
***female***;
proc freq data=combined;
table  Female * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 

***age_cat***;
 proc freq data=combined;
table  age_cat * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


***married***;
 proc freq data=combined;
table  married * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***cps_cat ***;
 proc freq data=combined;
table  cps_cat * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***adl_cat***;
 proc freq data=combined;
table  adl_cat * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***chess_cat***;
 proc freq data=combined;
table  chess_cat * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***ise_cat***;
 proc freq data=combined;
table  ise_cat * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***abs_cat***;
 proc freq data=combined;
table  abs_cat * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***pain_nh2***;
 proc freq data=combined;
table  pain_nh2 * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

*** Anxiety diagnosis****;
 proc freq data=combined;
table  i1ff * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

***conflict***;
 proc freq data=combined;
table  conflict * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;
	
***f2g***;
 proc freq data=combined;
table  f2g * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


***	new_resident***;
 proc freq data=combined;
table  new_resident * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


***province_code***;
 proc freq data=combined;
table  province_code * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


***facility_size***;
 proc freq data=combined;
table  facility_size * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


***	urban***;
 proc freq data=combined;
table  urban * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

********************************************************************************************************************************************************


****TABLE 3****;
**** FINAL Model PRE-COVID******;
ods rtf file='f:\commonoutput\code_exchange\ For Reem\Decline-Model\Pre-COVID Final Model.rtf';
proc logistic data=combined descending;
class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
model drs_cat_t2 =  female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident province_code 
facility_size urban 
/maxiter = 100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;
	ods rtf close;



*** Full Model COVID replicated from Pre-COVID above***;

	proc logistic data=combined descending;
class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
model drs_cat_t2 =  female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident province_code 
facility_size urban 
/ maxiter = 100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1 and period = "COVID";
	run;
ods rtf close;



****************************************************************************************************************************************************************

****TABLE 4 Proportional Odds Stats Stratified Model ****;
ods rtf file = "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\Output\Final table Original cps cat.rtf";
*Add in period effect and fit among full cohort;

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
	
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON')  cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period|female  age_cat  cps_cat adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size province_code 
	/ maxiter=100 unequalslopes=(cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1;

	oddsratio period / at (female = 0);
	oddsratio period / at (female = 1);
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

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON')  cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") age_cat (ref='0') /param=ref;
	model drs_cat_t2 = period|age_cat female  cps_cat adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size province_code 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1;
	
	oddsratio period / at (age_cat = "0");
	oddsratio period / at (age_cat = "1");
	oddsratio period / at (age_cat = "2");
	oddsratio period / at (age_cat = "3");
	oddsratio period / at (age_cat = "4");
	oddsratio period / at (age_cat = "5");
 
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


****For Luke's attention*****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON') cps_cat (ref='0')  adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') 
	abs_cat(ref = '0')  facility_size(ref = "S") /param=ref;

	model drs_cat_t2 = period|cps_cat female  age_cat  adl_cat urban chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  facility_size province_code 
	/unequalslopes =(female  adl_cat abs_cat new_resident province_code urban)
	maxiter= 100;

	where no_mood_symptoms = 1;

	oddsratio period / at (cps_cat = "0");
	oddsratio period / at (cps_cat = "1");
	oddsratio period / at (cps_cat = "2");
	oddsratio period / at (cps_cat = "3");
 
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
	  facility_size(ref = "S") Province_code (ref='ON') /param=ref;
	model drs_cat_t2 = period|Province_code female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
facility_size urban 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident  urban);
	where no_mood_symptoms = 1;
	

	oddsratio period / at (Province_code = "ON");
	oddsratio period / at (Province_code = "AB");
	oddsratio period / at (Province_code = "BC");
	oddsratio period / at (Province_code = "MB");
	oddsratio period / at (Province_code = "NL");
 
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
	
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size (ref='S') /param=ref;
	model drs_cat_t2 = period|facility_size female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
	province_code  urban 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1;
	
	oddsratio period / at (facility_size = "S");
	oddsratio period / at (facility_size = "M");
	oddsratio period / at (facility_size = "L");
	
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
	
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') period(ref = "Pre-COVID") province_code (ref='ON') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  facility_size(ref = "S") /param=ref;
	model drs_cat_t2 = period|urban female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident  
	facility_size province_code 
	/ maxiter=100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code);
	where no_mood_symptoms = 1;

	oddsratio period / at (Urban = 0);
	oddsratio period / at (Urban = 1);
	

run;

ods rtf close;



*******n for each strata covering the entire period Pre and COvid******;


Proc freq data=combined;
Table period;
where no_mood_symptoms = 1;
run;

Proc freq data=combined;
Table period * province_code;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * female;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * age_cat;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * urban;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * facility_size;
where no_mood_symptoms = 1;
run;





Proc freq data=combined;
Table period * cps_cat;
where no_mood_symptoms = 1;
run;

Proc freq data=combined;
Table period * province_code;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * female;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * age_cat;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * urban;
where no_mood_symptoms = 1;
run;


Proc freq data=combined;
Table period * facility_size;
where no_mood_symptoms = 1;
run;

