filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");

*------------------------------------------------*;
****Check which VARs are significant and put them in logistic mode****;
proc sort data=combined; by period; run;

proc freq data=combined;
	table(

		female 
		age_cat 
		married
		lived_alone

		cps_cat 
		adl_cat 
		chess_cat 
		ise_cat
		abs_cat
		pain_nh2
		i1ff /*anxiety*/
		Poor_sleep
		f2g /*change hard*/

		Major_comorbidity_grp
		Major_comorbidity_cat

		new_resident

		province_code
		facility_size
		urban


/*
/*		i1u /*stroke*/
/*		i1f /*CHF*/
/*		adrd /*dementia*/
/*		i1rr /*cancer*/
/*		i1a /*diabetes*/
/*		i1kk /*COPD*/
/*		i1uu /*Renal failure*/
       
/*		i1ii /*schiozphrenia*/
/*		i1hh /*manic depressive*/
		
		
		
/*		F1C
		F1b
		F1a
		F1d
		F1e
		F1f
		conflict
		f2e no family contact
		f2f /*recent loss*/
		

		
		)*drs_cat_t2  /chisq;

	where no_mood_symptoms = 1;
	by period;
run;

proc freq data=combined;
	table(
	i1ff /*anxiety*/
		Poor_sleep
		f2g /*change hard*/

		Major_comorbidity_grp
		Major_comorbidity_cat

		new_resident

)*drs_cat_t2  /chisq;

	where no_mood_symptoms = 1;
	by period;
run;

filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");


*****Model with sig vars pre-COVID from chisq test above****;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =  female age_cat F1c F2g cps_cat adl_cat chess_cat ise_cat abs_cat pain_nh2 Major_comorbidity_cat province_code facility_size urban;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;


*****  Full Model with sig vars pre-COVID from the above****;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =  female age_cat F2g cps_cat adl_cat ise_cat abs_cat pain_nh2 province_code facility_size urban;
	where no_mood_symptoms = 1 and period = "Pre-COVID";
	run;

*****Model of COVID derived from Full Model pre-COVID with sig vars****;
	proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =  female age_cat F2g cps_cat adl_cat chess_cat ise_cat abs_cat pain_nh2 Major_comorbidity_cat province_code facility_size urban;
	where no_mood_symptoms = 1 and period = "COVID";
	run;

	

	***** supplement p value between groups at the bivariate level****;
	proc freq data=combined;
	table(

		female 
		age_cat 
		married
		cps_cat 
		chess_cat 
		ise_cat
		abs_cat
		pain_nh2
		province_code
		facility_size
		urban

		)*drs_cat_t2  /chisq;

	where no_mood_symptoms = 1;
	by period;
run;


****Table 2****;
proc freq data=combined;
table period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


****Fig 2****;
proc freq data=combined;
table province_code *period *drs_cat_t2  /chisq;
where no_mood_symptoms = 1;
run;

****Table 2 supp****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 =   F2g i1ff conflict cps_cat adl_cat chess_cat ise_cat abs_cat pain_nh2 Major_comorbidity_cat province_code facility_size urban;
	where no_mood_symptoms = 1 and period = "COVID";
	run;

**** Suppl table 2 including all Vars under Table 3****;
proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = female age_cat cps_cat  chess_cat ABS_cat i1ff conflict f2g new_resident province_code
facility_size urban;
	where no_mood_symptoms = 1 and period = "COVID";
	run;


**** Suppl table 2 equal and unequal slopes****;

proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') cps_cat(ref = '0') adl_cat(ref = '0') chess_cat(ref = '0') ise_cat(ref = '0') abs_cat(ref = '0') 
						pain_nh2(ref = '0') Major_comorbidity_cat(ref = '0') province_code(ref = "ON") facility_size(ref = "S") /param=ref ;
	model drs_cat_t2 = female age_cat  chess_cat ABS_cat i1ff conflict f2g new_resident province_code
facility_size urban/unequalslopes=(cps_nh2 abs_cat new_resident);
	where no_mood_symptoms = 1 and period = "COVID";
	run;



proc logistic data=combined descending;
	class drs_cat_t2(ref = '0') age_cat(ref = '0') Female(ref='0') Married(ref='0') i1ff(ref='0') f2g(ref='0') cps_cat(ref = '0') 
 	chess_cat(ref = '0') chess_cont_cat(ref='0')  abs_cont_cat(ref = '0')  province_code(ref = "ON") facility_size(ref = "S") new_resident (ref='0')  
	urban (ref='0') /param=ref;
	model drs_cat_t2 = female age_cat chess_cat i1ff  conflict f2g  
			cps_cat abs_cont_cat new_resident urban province_code facility_size / unequalslopes=(cps_cat abs_cont_cat new_resident province_code);

where no_mood_symptoms = 1 and period = "Pre-COVID";
run;


	
