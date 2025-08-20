/*General rules for creating and naming variables

- variables with no time suffix are measured at baseline; _t2 means the variable was measured at follow-up
- binary variables that are created do not have a suffix; append _cat for variables with 3 or more levels
- use numerical variables levels (e.g., married = 1) not character strings (e.g., married = "Yes") because:
	- references to character strings (e.g., where married = "Yes") are case-sensitive ("Yes" != "yes", "YES", and "yeS") and easy to mess up
	- it's a real pain to remember the exact spelling of the string, with numbers 0 is always the lowest level. 

- variables are only created in *this* file; run the file before starting any analysis. 

*/


data combined;
	set sasuser.covid_combined;


*Identify the sub-group of residents with no mood symptoms at baseline;
	no_mood_symptoms= .;
		if drs_nh2 = 0 and e1o = 0 and e1p = 0 and e1e = 0 and e1g = 0 and i1gg = 0 then no_mood_symptoms= 1;
		else if drs_nh2 ne 0 or e1o ne 0 or e1p ne 0 or e1e ne 0 or e1g ne 0 or i1gg ne 0 then no_mood_symptoms = 0;

*Collapse DRS at time2 into 3 categories to measure outcomes;
	drs_cat_t2 = .;
		if drs_nh2_t2 = 0 then drs_cat_t2 = 0;
		else if drs_nh2_t2 in (1,2) then drs_cat_t2 = 1;
		else if drs_nh2_t2 ge 3 then drs_cat_t2 = 2;

*Create a binary variable for DRS cats;
		if drs_cat_t2 = 0 then drs_bin_t2 = 0;
		else if drs_cat_t2 in (1,2) then drs_bin_t2 = 1;
		



*Recode variables as needed;

	female = .;
		if aa2='F' then female=1; 
		else if aa2 in ("M", "O") then female = 0;

	lived_alone = .;
		if ab3 = 0 then lived_alone = 0;
		else if ab3 = 1 then lived_alone = 1;
		else if ab3 in (., 9) then lived_alone = 9;

	comatose = .;
	if B1 = 1 then comatose = 1;
	else if B1 = 0 then comatose = 0;

	

	age_cat = .;
		if age_assessment in (18:44) then age_cat = 0;
		else if age_assessment in (45:64) then age_cat = 1;
		else if age_assessment in (65:74) then age_cat = 2;
		else if age_assessment in (75:84) then age_cat = 3;
		else if age_assessment in (85:94) then age_cat = 4;
		else if age_assessment ge 95 then age_cat = 5;

	married = .;
		if a5 = 2 then married = 1;
		else if a5 in (1,3,4,5,9) then married = 0;

	cps_cat = .;
		if cps_nh2 = 0 then cps_cat = 0;
		else if cps_nh2 in (1,2) then cps_cat = 1;
		else if cps_nh2 in (3,4) then cps_cat = 2;
		else if cps_nh2 in (5,6) then cps_cat = 3;


	
	/*cps_cat_collapsed = .;
		cps_cat_collapsed = cps_nh2; 
		if cps_nh2  ge 3 then cps_cat_collapsed = 2;*/
	

	adl_cat = .;
		if adl_hier_nh2 = 0 then adl_cat = 0;
		else if adl_hier_nh2 in (1,2) then adl_cat = 1;
		else if adl_hier_nh2 in (3,4) then adl_cat = 2;
		else if adl_hier_nh2 in (5,6) then adl_cat = 3;

	chess_cat = .;
		if chess_nh2 = 0 then chess_cat = 0;
		else if chess_nh2 in (1,2) then chess_cat = 1;
		else if chess_nh2 ge 3 then chess_cat = 2;

	chess_cont_cat = .;
		chess_cont_cat = chess_nh2;
		if chess_nh2 ge 3 then chess_cont_cat = 3;

	ise_cat = .;
		if soceng_nh2 = 0 then ise_cat = 0;
		else if soceng_nh2 in (1,2) then ise_cat = 1;
		else if soceng_nh2 in (3,4) then ise_cat = 2;
		else if soceng_nh2 in (5,6) then ise_cat = 3;

	abs_cat = .;
		if abs_nh2 = 0 then abs_cat = 0;
		else if abs_nh2 in (1:4) then abs_cat = 1;
		else if abs_nh2 ge 5 then abs_cat = 2;

	abs_cont_cat = .;
		if abs_nh2 in (0:4) then abs_cont_cat = abs_nh2;
		else if abs_nh2 ge 5 then abs_cont_cat = 5;

	if j2a=0 then pain_nh2=0;
 else if j2a=1 then pain_nh2=1;
 else if j2a=2 and j2b in (1,2) then pain_nh2=2;
 else if j2a=2 and j2b=3 then pain_nh2=3;

	adrd = .;
		if i1r = 1 or i1v = 1 then adrd=1;
		else if i1r = 0 and i1v = 0 then adrd = 0;
		else if i1r = . then adrd = 0;

	Poor_sleep = .;
		if E1k = 0  or E1j = 0 then Poor_sleep= 0;
		else if E1k in (1,2) or E1j in (1,2) then Poor_sleep = 1;

	conflict = .;
		if f2a = 1 or f2b = 1 or f2c = 1 or f2d = 1 then conflict = 1;
		else if f2a = 0 and f2b = 0 and f2c = 0 and f2d = 0 then conflict = 0;

	new_resident = .;
		if aa8 = 1 then new_resident = 1;
		else if aa8 in (2,3,4,5,10) then new_resident = 0; 

	urban = .;
		if FAC_URBAN_RURAL_CODE = 1 then urban = 1;
		else if FAC_URBAN_RURAL_CODE then urban = 0;





***CALCULATE SCALE ONLY WHEN NO VARIABLE HAS AN INVALID VALUE  **; 
IF	I1AA IN (0,1) AND I1BB IN (0,1) AND I1CC IN (0,1) AND I1D  IN (0,1) AND
	I1DD IN (0,1) AND I1E  IN (0,1) AND I1F  IN (0,1) AND I1JJ IN (0,1) AND
	I1K	 IN (0,1) AND I1KK IN (0,1) AND I1Q	 IN (0,1) AND I1R  IN (0,1) AND
	I1RR IN (0,1) AND I1S  IN (0,1) AND I1T	 IN (0,1) AND I1TT IN (0,1) AND
	I1U	 IN (0,1) AND I1UU IN (0,1) AND I1V	 IN (0,1) AND I1W  IN (0,1) AND
	I1X	 IN (0,1) AND I1Y  IN (0,1) AND I1Z  IN (0,1) AND I2G  IN (0,1) AND
	I2J	 IN (0,1) AND I2L  IN (0,1) AND P1AA IN (0,1) AND P1AB IN (0,1) AND
	P1AG IN (0,1) AND P1AH IN (0,1) AND P1AI IN (0,1) AND P1AJ IN (0,1) AND
	P1AL IN (0,1) AND P1BDA IN (0,1,2,3,4,5,6,7) AND (0<=P1BDB<=9999)	  	
THEN DO;
	
	**  CALCULATE TEMPORARY VARIABLES  **;
		**(1)	T_heart**;
		IF 		I1D=1  OR I1E=1  OR I1F=1  OR I1K=1 	THEN 	T_heart=1;
		ELSE                          							T_heart=0;


		**(2)	T_liver**;
		IF 		I1TT=1 OR I2L=1 						THEN 	T_liver=1;
		ELSE                    								T_liver=0;


		**(3)	T_lung**;
		IF 		I1JJ=1 OR I1KK=1 OR	I2G=1  OR  
				I2J=1  OR P1AI=1 OR	P1AJ=1 OR 
				P1AL=1 OR P1AG=1 OR	
				P1BDA>0 OR P1BDB>0	   					THEN	T_lung=1;
		ELSE                                            		T_lung=0;


		**(4)	T_kidney**;
		IF 		I1UU=1 OR P1AB=1		 				THEN 	T_kidney=1;
		ELSE    		                 						T_kidney=0;

		**(5)	T_neuro**;
		IF 		I1Q=1 									THEN 	T_neuro=1;   
		ELSE IF I1R=1 OR I1V=1 							THEN	T_neuro=1; 
		ELSE IF I1U=1 OR I1S=1 OR I1DD=1 				THEN	T_neuro=1; 
		ELSE IF I1W=1 OR I1Z=1 OR I1BB=1				THEN 	T_neuro=1; 
		ELSE IF I1X=1 									THEN	T_neuro=1; 
		ELSE IF I1Y=1 									THEN 	T_neuro=1; 
		ELSE IF I1AA=1 									THEN 	T_neuro=1; 
		ELSE IF I1CC=1 									THEN 	T_neuro=1; 
		ELSE IF I1T=1 									THEN 	T_neuro=1; 
		ELSE 												 	T_neuro=0;

		**(6)	T_cancer_treat**;
		IF 		I1RR=1 AND (P1AA=1 OR P1AH=1) 			THEN	T_cancer_treat=1;
		ELSE                                  					T_cancer_treat=0;


	**  CALCULATE OUTPUT  **;
		Major_comorbidity_count = T_heart + T_liver + T_lung + T_kidney + T_cancer_treat + T_neuro;

	***Collapsing into 3 groups*************; ***Major_comorbidity_grp;
Major_comorbidity_grp=.;
if Major_comorbidity_count=0             then Major_comorbidity_grp =0;
else if Major_comorbidity_count in(1,2)  then Major_comorbidity_grp =1;
else if Major_comorbidity_count ge 3    then Major_comorbidity_grp =2;

	***Collapsing into 4 groups*************; ***Major_comorbidity_cat;
Major_comorbidity_cat=.;
if Major_comorbidity_count=0             then Major_comorbidity_cat =0;
else if Major_comorbidity_count in(1,2)  then Major_comorbidity_cat =1;
else if Major_comorbidity_count in (3,4)    then Major_comorbidity_cat =2;
else if Major_comorbidity_count in (5,6)    then Major_comorbidity_cat =3;
END;
run;



	
