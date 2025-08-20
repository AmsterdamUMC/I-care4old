libname ccrs 'F:\\CommonData\CCRS';
filename suffix 'F:\CommonOutput\code_exchange';
%include suffix(ren_stem_2009_add_suffix);

%macro create_linked_cohort(input, baseline_date1, baseline_date2, follow_up_time1, follow_up_time2, vars_time2, period_name, follow_up_id, output);

*select baseline ax;
data index;
	set &input(where = (&baseline_date1 <= a3 <= &baseline_date2));
	run;

proc sort data=index; by resident_id_mbun a3; run;
proc sort data=index nodupkey; by resident_id_mbun; run;

*create index table;
proc sql;
	create table next as
	select a.resident_id_mbun, a.a3 as first_ax_date, a.assessment_id_mbun as first_ax_id, a.aa8 as first_ax_type,
			b.a3 as next_ax_date, b.assessment_id_mbun as next_ax_id, b.aa8 as next_ax_type
	from index as a, &input as b
	where a.resident_id_mbun = b.resident_id_mbun and b.a3 - a.a3 in (&follow_up_time1:&follow_up_time2);
quit;

proc sort data=next; by resident_id_mbun next_ax_date; run;
proc sort data=next nodupkey; by resident_id_mbun; run;
 

*link on time1 vars;
proc sql;
	create table next as
	select a.*, b.*

	from next as a, &input as b
	where a.resident_id_mbun = b.resident_id_mbun and a.first_ax_id = b.assessment_id_mbun;

quit; 

data time2;
	set &input(keep = resident_id_mbun assessment_id_mbun &vars_time2);
run;

 %ren_stem(time2, _all_ not(resident_id_mbun assessment_id_mbun), _t2, after);

*Link on time 2 vars;
proc sql;
	create table next as
	select a.*, b.*
	from next as a, time2 as b
	where a.resident_id_mbun = b.resident_id_mbun and a.next_ax_id = b.assessment_id_mbun;

quit;

data &output;
	set next;

	period = &period_name;
	follow_up_id = &follow_up_id;

run;

proc datasets;
	delete index next time2;
	quit;

%mend;



%create_linked_cohort(
					input = ccrs.ccrs_2021q1, 
					baseline_date1 = '01MAR2019'd, 
					baseline_date2 = '31MAR2019'd, 
					follow_up_time1 = 70, 
					follow_up_time2 = 95,
					vars_time2 = drs_nh2 b1,
					period_name = "Pre-COVID", 
					follow_up_id = 1, 
					output = pre_covid_1
);

%create_linked_cohort(
					input = ccrs.ccrs_2021q1, 
					baseline_date1 = '01MAR2020'd, 
					baseline_date2 = '31MAR2020'd, 
					follow_up_time1 = 70, 
					follow_up_time2 = 95,
					vars_time2 = drs_nh2 b1,
					period_name = "COVID", 
					follow_up_id = 1, 
					output = covid_1
);



data combined;
	set pre_covid_: covid_:;

	*Select LTC residents;
	if sector_code = 4;

	*Remove records where the person is comatose at either admission or follow-up, as the DRS isn't scored;
	if b1 = 0 and b1_t2 = 0;

	*Remove people younger than 18;
	if age_assessment ge 18;

	*Keep people from ON, AB, BC, MB, and NL only. SK switched in 2019 and YT is too small.;
	if province_code in ("ON", "AB", "BC", "MB", "NL");

	run;


data sasuser.covid_combined;
	set combined;
	run;


*Select records with a full within last year min;
proc sql; 
	create table sasuser.covid_combined as
	select a.*
	from sasuser.covid_combined as a, ccrs.ccrs_2021q1(where = (aa8 in (1,2,3,4))) as b
	where a.resident_id_mbun = b.resident_id_mbun and a.a3 - b.a3 in (0:365);
	quit;

proc sort data=sasuser.covid_combined nodupkey; by resident_id_mbun a3; run;

*Carry forward last value;

%macro last_full(input, output, var, source);

*Select records with missing vars to be replaced;
	data missing;
		set &input(where = (&var = .));
		run;
	

*Grab variables from full assessments in last year;
	proc sql; 
	create table last_full as
	select a.resident_id_mbun, a.assessment_id_mbun, a.a3, a.follow_up_id, a.aa8, b.&var as prev_&var, b.a3 as prev_date, (a.a3 - b.a3) as gap
	from missing as a left join &source(where = (aa8 in (1,2,3,4))) as b
	on a.resident_id_mbun = b.resident_id_mbun and a.a3 - b.a3 in (0:365);
	quit;

*Previous step may match to more than one full assessment, select most proximate where not missing;
	proc sort data=last_full(where = (prev_&var ne .)) out=last_full; by resident_id_mbun a3 follow_up_id gap;
	proc sort data=last_full(keep = resident_id_mbun assessment_id_mbun a3 follow_up_id prev_&var) nodupkey; by resident_id_mbun a3 follow_up_id; run;

*Merge back onto record;

	proc sort data=missing; by resident_id_mbun assessment_id_mbun; run;
	proc sort data=last_full; by resident_id_mbun assessment_id_mbun; run;

	data missing;
		merge missing(drop = &var) last_full(rename = (prev_&var=&var));
		by resident_id_mbun assessment_id_mbun;
		run; quit;

*Output;

	data &output;
		set missing &input(where = (&var ne .));
		run;

*NOTE* - There may be no previous ax in some instances, so the variable may remain as missing;

*Clean up temp datasets;
	proc datasets; delete last_full missing; run; quit;

%mend;



%last_full(sasuser.covid_combined, sasuser.covid_combined, a5,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, ab3,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, i1r,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, i1f,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, i1ff,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, i1kk,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, i1rr,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, i1uu,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2a,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2b,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2c,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2d,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2e,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2f,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f2g,  ccrs.ccrs_2021q1);
%last_full(sasuser.covid_combined, sasuser.covid_combined, f3b,  ccrs.ccrs_2021q1);


