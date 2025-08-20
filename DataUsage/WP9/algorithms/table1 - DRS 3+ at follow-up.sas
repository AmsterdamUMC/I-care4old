*Run before any analysis;
*------------------------------------------------*;

filename base "F:\CommonOutput\code_exchange\for Reem\decline-model\Luke's Approach\";
%include base("2-create-vars.sas");

*------------------------------------------------*;

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

		Major_comorbidity_grp
		Major_comorbidity_cat

/*
/*		i1u /*stroke*/
/*		i1f /*CHF*/
/*		adrd /*dementia*/
/*		i1rr /*cancer*/
/*		i1a /*diabetes*/
/*		i1kk /*COPD*/
/*		i1uu /*Renal failure*/
       i1ff /*anxiety*/
/*		i1ii /*schiozphrenia*/
/*		i1hh /*manic depressive*/
		
		Poor_sleep
		
		F1C
		F1b
		F1a
		F1d
		F1e
		F1f
		conflict
		f2e /*no family contact*/
		f2f /*recent loss*/
		f2g /*change hard*/

		new_resident

		province_code
		facility_size
		urban

		 )* period/chisq;

	where no_mood_symptoms = 1;

run;

/* test p value, col and row percent and freq */
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

		Major_comorbidity_grp
		Major_comorbidity_cat

/*
/*		i1u /*stroke*/
/*		i1f /*CHF*/
/*		adrd /*dementia*/
/*		i1rr /*cancer*/
/*		i1a /*diabetes*/
/*		i1kk /*COPD*/
/*		i1uu /*Renal failure*/
  /*      i1ff /*anxiety*/
/*		i1ii /*schiozphrenia*/
/*		i1hh /*manic depressive*/
		
		Poor_sleep
		
		F1C
		F1b
		F1a
		F1d
		F1e
		F1f
		conflict
		f2e /*no family contact*/
		f2f /*recent loss*/
		f2g /*change hard*/

		new_resident

		province_code
		facility_size
		urban

		)*drs_cat_t2  /chisq;

	where no_mood_symptoms = 1;
	by period;
run;

***Check***;
proc freq data=combined;
table Period* Female * drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 

***Check 2***;
proc freq data=combined;
table  Female * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 


*************************************************************************************************************
***test whether there is a significant difference in DRS during each period among the different variables***;
*** us the variable first then period and DRS***;

***female***;
proc freq data=combined;
table  Female * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 


****Overall****;
proc freq data=combined;
table   period *drs_cat_t2 /chisq;
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


***lived_alone***;
 proc freq data=combined;
table  lived_alone * period *drs_cat_t2 /chisq;
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



***Major_comorbidity_grp***;
 proc freq data=combined;
table  Major_comorbidity_grp * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


***Poor_sleep***;
 proc freq data=combined;
table  Poor_sleep * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;



***F1C***;
 proc freq data=combined;
table  F1C * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;



***F1b***;
 proc freq data=combined;
table  F1b * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;



***F1a***;
 proc freq data=combined;
table  F1a * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;


	
***F1d***;
 proc freq data=combined;
table  F1d * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;



***F1e***;
 proc freq data=combined;
table  F1e * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

 
***F1f***;
 proc freq data=combined;
table  F1f * period *drs_cat_t2 /chisq;
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



***f2e***;
 proc freq data=combined;
table  f2e * period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run;

	
***f2f***;
 proc freq data=combined;
table  f2f * period *drs_cat_t2 /chisq;
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

*************************************************************************************************************;
  proc freq data=combined;
table  period *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 


proc freq data=combined;
table  period * Female *drs_cat_t2 /chisq;
where no_mood_symptoms = 1;
run; 



proc freq data=combined;
table major_comorbidity_count;
by period;
where no_mood_symptoms = 1;
run;

proc freq data=combined;
	table(F1a F1b F1c F1d F1e F1f) *drs_cat_t2 /chisq norow nopercent;
	where no_mood_symptoms = 1;
	by period;
run;


proc freq data=combined;
	table(F1a F1b F1c F1d F1e F1f) /chisq;
	where no_mood_symptoms = 1;
	by period;
run;



proc freq data=combined;
	table(F1a F1b F1c F1d F1e F1f) *period /chisq norow nopercent;
	where no_mood_symptoms = 1;
	
run;





proc freq data=combined;
	table period *drs_cat_t2;
	where no_mood_symptoms = 1;
	
run;

proc freq data=combined;
	table period *drs_cat_t2;
	where no_mood_symptoms = 0;
	
run;

proc freq data=combined;
	table drs_cat_t2;
	where no_mood_symptoms = 1;
	
run;


proc freq data=combined;
	table B1;
	where no_mood_symptoms = 1;
run;


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
		Major_comorbidity_cat

	/*
/*		i1u /*stroke*/
/*		i1f /*CHF*/
/*		adrd /*dementia*/
/*		i1rr /*cancer*/
/*		i1a /*diabetes*/
/*		i1kk /*COPD*/
/*		i1uu /*Renal failure*/
  /*      i1ff /*anxiety*/
/*		i1ii /*schiozphrenia*/
/*		i1hh /*manic depressive*/
		
		Poor_sleep
		
		F1C
		conflict
		f2e /*no family contact*/
		f2f /*recent loss*/
		f2g /*change hard*/

		new_resident

		province_code
		facility_size
		urban

		)*period /chisq;

	where no_mood_symptoms = 1;
run;

proc freq data=combined;
table age_cat;
where no_mood_symptoms = 1;
	by period;
run;


proc freq data=combined;
table age_cat;
where no_mood_symptoms = 1;
	
run;


proc freq data=combined;
table cps_cat;
where no_mood_symptoms = 1;
	
run;


proc freq data=combined;
table female;
where no_mood_symptoms = 1;
	
run;


proc freq data=combined;
table facility_size;
where no_mood_symptoms = 1;
	
run;



/*baseline characteristics by period with no mood symptoms*/
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

		Major_comorbidity_count
/*
/*		i1u /*stroke*/
/*		i1f /*CHF*/
/*		adrd /*dementia*/
/*		i1rr /*cancer*/
/*		i1a /*diabetes*/
/*		i1kk /*COPD*/
/*		i1uu /*Renal failure*/
  /*      i1ff /*anxiety*/
/*		i1ii /*schiozphrenia*/
/*		i1hh /*manic depressive*/
		
		Poor_sleep
		
		F1C
		F1b
		F1a
		F1d
		F1e
		F1f
		conflict
		f2e /*no family contact*/
		f2f /*recent loss*/
		f2g /*change hard*/

		new_resident

		province_code
		facility_size
		urban

		)*period /chisq norow nopercent;

	where no_mood_symptoms = 1;
	
run;


proc freq data=combined;
table female * period * drs_cat_t2/chisq;
where no_mood_symptoms =1;
run;



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

		Major_comorbidity_grp
		Major_comorbidity_cat

/*
/*		i1u /*stroke*/
/*		i1f /*CHF*/
/*		adrd /*dementia*/
/*		i1rr /*cancer*/
/*		i1a /*diabetes*/
/*		i1kk /*COPD*/
/*		i1uu /*Renal failure*/
  /*      i1ff /*anxiety*/
/*		i1ii /*schiozphrenia*/
/*		i1hh /*manic depressive*/
		
		Poor_sleep
		
		F1C
		F1b
		F1a
		F1d
		F1e
		F1f
		conflict
		f2e /*no family contact*/
		f2f /*recent loss*/
		f2g /*change hard*/

		new_resident

		province_code
		facility_size
		urban

		 )* drs_cat_t2/chisq;

	where no_mood_symptoms = 1;
	by period;
run;
