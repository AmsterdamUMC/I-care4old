

filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");


**** Suppl Table 1*****
****Female*****;
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
ods rtf file='f:\commonoutput\code_exchange\ For Reem\Decline-Model\COVID Final Model.rtf';
	proc logistic data=combined descending;
class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') pain_nh2(ref = '0') chess_cat(ref = '0') abs_cat(ref = '0')  
	  province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
model drs_cat_t2 =  female age_cat cps_cat adl_cat chess_cat abs_cat  pain_nh2 i1ff conflict f2g new_resident province_code 
facility_size urban 
/ maxiter = 100 unequalslopes=(female cps_cat adl_cat abs_cat new_resident province_code urban);
	where no_mood_symptoms = 1 and period = "COVID";
	run;
ods rtf close;


