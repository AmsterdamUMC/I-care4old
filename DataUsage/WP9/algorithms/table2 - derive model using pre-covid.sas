*Run before any analysis;
*------------------------------------------------*;

filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");

*------------------------------------------------*;

*Univariable;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   cps_nh2;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   cps_nh2/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

****cps_cat******
proc logistic data=combined descending;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   cps_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;




proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   cps_nh2/unequalslopes;
	where no_mood_symptoms = 1 and period = "COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   abs_cont_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   abs_cont_cat/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

	proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   abs_cont_cat/unequalslopes;
	where no_mood_symptoms = 1 and period = "COVID";
	run;



proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   conflict;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = adl_hier_nh2  ;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = adl_hier_nh2/unequalslopes;  
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = adl_hier_nh2/unequalslopes;  
	where no_mood_symptoms = 1 and period = "COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = chess_nh2;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = soceng_nh2;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = province_code;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = province_code/unequalslopes; 
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = facility_size;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = age_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") conflict f2g new_resident (ref='0')  urban (ref='0') /param=ref ;
	model drs_cat_t2 = urban;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;
 
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") conflict f2g new_resident (ref='0')  urban (ref='0') /param=ref ;
	model drs_cat_t2 = urban/unequalslopes; 
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") conflict f2g new_resident (ref='0')  urban (ref='0') /param=ref ;
	model drs_cat_t2 = new_resident;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;
	
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						province_code(ref = "ON") facility_size(ref = "S") conflict f2g new_resident (ref='0')  urban (ref='0') /param=ref ;
	model drs_cat_t2 = new_resident/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = Female;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = Female/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = Married;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = Lived_alone;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1u;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1f;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = adrd;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1rr;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1a;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1kk;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1uu;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1ff;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1ii;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;



proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = i1hh;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;



proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = poor_sleep;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = f2e;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = f2f;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = f2g;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0')   /param=ref ;
	model drs_cat_t2 = ise_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0')   /param=ref ;
	model drs_cat_t2 = F1a;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0')   /param=ref ;
	model drs_cat_t2 = F1b;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0')   /param=ref ;
	model drs_cat_t2 = F1c;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;	

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0')   /param=ref ;
	model drs_cat_t2 = F1d;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0')   /param=ref ;
	model drs_cat_t2 = F1e;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0')   /param=ref ;
	model drs_cat_t2 = F1f;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;




*Multivariable;

*Add sig variables from previous step;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref ;



	model drs_cat_t2 = chess_nh2 adrd i1rr i1kk i1ff i1ii poor_sleep conflict f2f f2g facility_size f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);



where no_mood_symptoms = 1 and period = "Pre-COVID";
run;

*Remove COPD;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref;

	model drs_cat_t2 = chess_nh2 adrd i1rr i1ff i1ii poor_sleep conflict f2f f2g facility_size f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


*Remove Schezophrenia i1ii;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref;

	model drs_cat_t2 = chess_nh2 adrd i1rr i1ff poor_sleep conflict f2f f2g facility_size f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


*Remove Recent loss f2f;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref;

	model drs_cat_t2 = chess_nh2 adrd i1rr i1ff poor_sleep conflict f2g facility_size f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


*Remove facility size;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref;

	model drs_cat_t2 = chess_nh2 adrd i1rr i1ff poor_sleep conflict f2g f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


*Remove adrd;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref;

	model drs_cat_t2 = chess_nh2 i1rr i1ff poor_sleep conflict f2g f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


*Adding urban & province_code, dropping cancer and f1c, replacing chess as categorical due to low n above 3;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0') i1u(ref='0') i1f(ref='0') adrd(ref='0') i1rr(ref='0') i1a(ref='0')
	i1kk(ref='0') i1uu(ref='0') i1ff(ref='0') i1ii(ref='0') i1hh(ref='0') Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') chess_cont_cat(ref='0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref;

	model drs_cat_t2 = chess_cont_cat i1ff poor_sleep conflict f2g  
			cps_nh2 abs_cont_cat new_resident urban province_code  / unequalslopes=(cps_nh2 abs_cont_cat new_resident province_code);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;

/* Univariate Pain_nh2 */
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   pain_nh2;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   pain_nh2/unequalslopes;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   pain_nh2/unequalslopes;
	where no_mood_symptoms = 1 and period = "COVID";
	run;

/* Univariate Major_comorbidity_cat */
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =  Major_comorbidity_cat;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;



proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =  Major_comorbidity_cat;
	where no_mood_symptoms = 1 and period = "COVID";
	run;



*Add sig variables and MCC cat instead of individual health conditions;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') Lived_alone(ref='0')  Poor_sleep(ref='0') f2e(ref='0') f2f(ref='0') f2g(ref='0') cps_nh2(ref = '0') 
	adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_cont_cat(ref = '0') ise_cat(ref = '0')
pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') F1a(ref = '0') F1b(ref = '0') F1c(ref = '0') F1d(ref = '0') F1e(ref = '0') F1f(ref = '0') /param=ref ;



	model drs_cat_t2 = chess_nh2 pain_nh2 Major_comorbidity_cat poor_sleep conflict f2f f2g facility_size f1c 
			cps_nh2 abs_cont_cat new_resident / unequalslopes=(cps_nh2 abs_cont_cat new_resident);



where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


/* Univariate with MCC*/
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_nh2(ref = '0') adl_hier_nh2(ref = '0') chess_nh2(ref = '0') soceng_nh2(ref = '0') abs_nh2(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = Major_comorbidity_cat  ;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;
