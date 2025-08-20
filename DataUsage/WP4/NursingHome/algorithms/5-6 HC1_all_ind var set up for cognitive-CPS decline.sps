* Encoding: UTF-8.
.* Encoding: UTF-8.
get file='s:\projectdata2\0000 account shared\Erez datasets\EREZ_HC_sample.sav'.
compute mbmodel = 0.
add files file = *
/file='S:\projectdata2\0000 account shared\icare4old\HC_models_check.sav'
 /drop=bb2.
if missing(mbmodel) mbmodel = 1.
*frequencies variables = mbmodel.
   
recode ic2c ig1ca ig1cb ig1da ig1db ig1ea ig1eb (500 thru high=sysmis).


*frequencies variables=b2a.

do repeat x1 = ic1 ic2a ic2b id1 id2/
 y1= b2a b1a b1b c2 c3/.
recode x1(500 thru high=sysmis).
if (missing(x1)) x1=y1.
end repeat.
 
compute comm2= id1+id2.
recode ic1 (5=sysmis)(else=copy)into decision2.
recode ig1ca ig1da ig1ea (0,1,2=0)(3,4,5,8=1)(6=2)into cog1a cog1b cog1c.
compute cogIADL=cog1a + cog1b+ cog1c.
 
compute cpsJNM=$sysmis.
do if (b2a eq 4).
if (h2g gt 5)cpsJNM=6.
if (h2g lt 6)cpsJNM=5.
end if.
count impair=b2a (1,2,3) c2 (1,2,3,4,) b1a (1).
count severe= b2a (3) c2 (3,4).
do if (b2a lt 4).
if (any(impair,2,3) and severe eq 2)cpsJNM=4.
if (any(impair,2,3) and severe eq 1)cpsJNM=3.
if (any(impair,2,3) and severe eq 0)cpsJNM=2.
if (impair eq 1)cpsJNM=1.
if (impair eq 0)cpsJNM=0.
end if.

compute cpsJNM_2=$sysmis.
do if (b2a_2 eq 4).
 if (h2g_2 gt 5)cpsJNM_2=6.
 if (h2g_2 lt 6)cpsJNM_2=5.
end if.

count impair=b2a_2 (1,2,3) c2_2 (1,2,3,4,) b1a_2 (1).
count severe= b2a_2 (3) c2_2 (3,4).
do if (b2a_2 lt 4).
if (any(impair,2,3) and severe eq 2)cpsJNM_2=4.
if (any(impair,2,3) and severe eq 1)cpsJNM_2=3.
if (any(impair,2,3) and severe eq 0)cpsJNM_2=2.
if (impair eq 1)cpsJNM_2=1.
 if (impair eq 0)cpsJNM_2=0.
end if.

count partTWO= b2a (2 thru high) b1b (1) c3 ( 2 thru high).
compute basetot=b1a.
do if (basetot eq 1).
recode parttwo (0=1)(1=2)(2=3)(3=4)into basetot.
end if.
if (missing(b1a))parttwo=$sysmis.

recode parttwo (0,1=0)(2 thru high=1)into parttwob.
variable labels parttwob cog cats memory plus 2 or 3 others.
count partTWO_2= b2a_2 (2 thru high) b1b_2 (1) c3_2 (2 thru high).
compute basetot_2=b1a_2.
do if (basetot_2 eq 1).
recode parttwo_2 (0=1)(1=2)(2=3)(3=4)into basetot_2.
end if.
if (missing(b1a_2))parttwo_2= $sysmis.
**

compute NEWcogChange=parttwo_2 - parttwo.
recode newCOGchange (low thru -1=1)(0 thru high=0)into NEWcogIMP.
recode newCOGchange (1 thru high=1)(low thru 0=0)into NEWcogDEC.

recode j1g j1h j1l (1 thru high=1).
compute dement = j1g.
If (j1g eq 0 and j1h gt 0)dement=1.
recode dement (missing=sysmis)(else=0)into dementBOTH.
if (j1g gt 0 and j1h gt 0)dementboth=1.

** cps2 beginning

 ** RESEARCH CODE FOR COGNITIVE PERFORMANCE SCALE, VERSION 2
 NOTE: THIS SPSS CODE IS DESIGNED 
FOR RESEARCHERS 
WORKING WITH 'DIRTY' IN 
WHICH VARIABLES COULD BE MISSING, OUT OF RANGE, OR INCORRECT. IN THE PRODUCTION CODE, STORED SEPARATELY, 
THE CPS2 WOULD NEVER BE CALCULATED
FOR INFORMATION ABOUT THIS CODE, CONTACT JOHN MORRIS.START OF SPSS CODE.

if (missing(ic2a))ic2a=b1a.
compute ic2axx=ic2a.
do if missing(ic2a).
recode ic1 (0=0)(1 thru high=1)into ic2axx.
end if. 

if (missing(id1)) id1=c2. 
do if missing(ic2axx).
recode id1 (0=0)(1 thru high=1)into ic2axx.
end if .

do repeat x1=ig1ca ig1da ig1cb ig1db/
 y1=h1ca h1da h1cb h1db/.
do if missing(x1).
recode y1 (0=0)(1=3)(2=6)into x1.
end if.
end repeat.
recode ig1ca ig1da ig1cb ig1db (8=6)(else=copy)into ig1cayy ig1dayy ig1cbyy ig1dbyy .
count cogPERFORM =ig1cayy ig1dayy (0).
if (missing(ig1cayy) and missing(ig1dayy))cogPERFORM=$sysmis.
do if cogPERFORM eq 1.
if (missing(ig1cayy) or missing(ig1dayy))cogPERFORM=2.
end if.
count cogCAPACITY =ig1cbyy ig1dbyy (0).
if (missing(ig1cbyy) and missing(ig1db))cogCAPACITY=$sysmis.
do if cogCAPACITY eq 1.
if (missing(ig1cbyy) or missing(ig1dbyy))cogCAPACITY=2.
end if.
recode cogPERFORM cogCAPACITY (2 thru high=1)(1=0).
if (missing(cogCAPACITY))cogCAPACITY=cogPERFORM.
 
recode ic1 id1 (0=0)(1=1)(2=2)(3=3)(4=4)(5=5) into ic1aax id1bbX .
if (missing(ic1aax))ic1aax =id1bbx.
if (missing(id1bbx))id1bbx=ic1aax.

compute cpsv2=$sysmis .
if (ic1aax eq 0 and id1bbx eq 0 and ic2axx eq 0)cpsv2=1.
if (cpsv2 eq 1 and not missing(cogcapacity) and cogcapacity eq 1)cpsv2=0.
if (ic1aax eq 0 and id1bbx eq 0 and ic2axx eq 1)cpsv2=2.
if (ic1aax eq 0 and id1bbx eq 1)cpsv2=2.
if (ic1aax eq 0 and any(id1bbx,2,3,4))cpsv2=3.
if (ic1aax eq 1 and id1bbx eq 0 and ic2axx eq 0)cpsv2=2.
if (ic1aax eq 1 and id1bbx eq 0 and ic2axx eq 1)cpsv2=3. 
if (ic1aax eq 1 and id1bbx eq 1 and ic2axx eq 0)cpsv2=3 . 
if (ic1aax eq 1 and id1bbx eq 1 and ic2axx eq 1)cpsv2=4.
if (ic1aax eq 1 and any(id1bbx,2,3,4))cpsv2=3.
if (ic1aax eq 2 and id1bbx eq 0 and ic2axx eq 0)cpsv2=2.
if (ic1aax eq 2 and id1bbx eq 0 and ic2axx eq 1)cpsv2=3.
if (ic1aax eq 2 and id1bbx eq 1 and ic2axx eq 0)cpsv2=3.
if (ic1aax eq 2 and id1bbx eq 1 and ic2axx eq 1)cpsv2=4.
if (ic1aax eq 2 and id1bbx eq 2)cpsv2=4.
if (ic1aax eq 2 and any(id1bbx,3,4))cpsv2=5.
if (ic1aax eq 3 and id1bbx eq 0 and ic2axx eq 0)cpsv2=3.
if (ic1aax eq 3 and id1bbx eq 0 and ic2axx eq 1)cpsv2=4.
If (ic1aax eq 3 and any(id1bbx,1,2))cpsv2=5.
If (ic1aax eq 3 and any(id1bbx,3,4))cpsv2=7.

If (ic1aax eq 4 and any(id1bbx,0,1,2))cpsv2=6.
If (ic1aax eq 4 and any(id1bbx,3,4))cpsv2=7.
if (cpsv2 eq 7 and not missing(ig2e) and range(ig2e,3,6))cpsv2=8.
 

COMPUTE DECISION= ic1aax.
compute memory= ic2axx.
compute understood= id1bbx. 

** end ckeck cpsv2

Variable labels cpsv2 CPS Version 2 September .
value lables cpsv2 
 (0) 0. Intact-1 
 (1) 1. Intact-2 
 (2) 2. Borderline intact 1 
 (3) 3. Borderline intact 2 
 (4) 4. Moderate impair 1 
 (5) 5. Moderate impair 2 
 (6) 6. Severe 1 
 (7) 7. Severe 2
 (8) 8. Very severe impair.

** cpsv2 time 2 start

**OF SPSS CODE:

if (missing(ic2a_2))ic2a_2=b1a_2.
compute ic2axx=ic2a_2.
do if missing(ic2a_2).
recode ic1_2 (0=0)(1 thru high=1)into ic2axx.
end if .

if (missing(id1_2)) id1_2=c2_2. 
do if missing(ic2axx).
recode id1_2 (0=0)(1 thru high=1)into ic2axx.
end if .

do repeat x1=ig1ca_2 ig1da_2 ig1cb_2 ig1db_2/
 y1=h1ca_2 h1da_2 h1cb_2 h1db_2/.
do if missing(x1).
recode y1 (0=0)(1=3)(2=6)into x1.
end if.
end repeat.
recode ig1ca_2 ig1da_2 ig1cb_2 ig1db_2 (8=6)(else=copy)into ig1cayy ig1dayy ig1cbyy ig1dbyy .
count cogPERFORM =ig1cayy ig1dayy (0).
if (missing(ig1cayy) and missing(ig1dayy))cogPERFORM=$sysmis.
do if cogPERFORM eq 1.
if (missing(ig1cayy) or missing(ig1dayy))cogPERFORM=2.
end if.
count cogCAPACITY =ig1cbyy ig1dbyy (0).
if (missing(ig1cbyy) and missing(ig1db))cogCAPACITY=$sysmis.
do if cogCAPACITY eq 1.
if (missing(ig1cbyy) or missing(ig1dbyy))cogCAPACITY=2.
end if.
recode cogPERFORM cogCAPACITY (2 thru high=1)(1=0).
if (missing(cogCAPACITY))cogCAPACITY=cogPERFORM.
 
recode ic1_2 id1_2 (0=0)(1=1)(2=2)(3=3)(4=4)(5=5) into ic1aax id1bbX. 
if (missing(ic1aax))ic1aax =id1bbx.
if (missing(id1bbx))id1bbx=ic1aax.

compute cpsv2_2=$sysmis .
if (ic1aax eq 0 and id1bbx eq 0 and ic2axx eq 0)cpsv2_2=1.
if (cpsv2_2 eq 1 and not missing(cogcapacity) and cogcapacity eq 1)cpsv2_2=0.
if (ic1aax eq 0 and id1bbx eq 0 and ic2axx eq 1)cpsv2_2=2.
if (ic1aax eq 0 and id1bbx eq 1)cpsv2_2=2.
if (ic1aax eq 0 and any(id1bbx,2,3,4))cpsv2_2=3.
if (ic1aax eq 1 and id1bbx eq 0 and ic2axx eq 0)cpsv2_2=2.
if (ic1aax eq 1 and id1bbx eq 0 and ic2axx eq 1)cpsv2_2=3 . 
if (ic1aax eq 1 and id1bbx eq 1 and ic2axx eq 0)cpsv2_2=3 . 
if (ic1aax eq 1 and id1bbx eq 1 and ic2axx eq 1)cpsv2_2=4.
if (ic1aax eq 1 and any(id1bbx,2,3,4))cpsv2_2=3.
if (ic1aax eq 2 and id1bbx eq 0 and ic2axx eq 0)cpsv2_2=2.
if (ic1aax eq 2 and id1bbx eq 0 and ic2axx eq 1)cpsv2_2=3.
if (ic1aax eq 2 and id1bbx eq 1 and ic2axx eq 0)cpsv2_2=3.
if (ic1aax eq 2 and id1bbx eq 1 and ic2axx eq 1)cpsv2_2=4.
if (ic1aax eq 2 and id1bbx eq 2)cpsv2_2=4.
if (ic1aax eq 2 and any(id1bbx,3,4))cpsv2_2=5.
if (ic1aax eq 3 and id1bbx eq 0 and ic2axx eq 0)cpsv2_2=3.
if (ic1aax eq 3 and id1bbx eq 0 and ic2axx eq 1)cpsv2_2=4.
If (ic1aax eq 3 and any(id1bbx,1,2))cpsv2_2=5.
If (ic1aax eq 3 and any(id1bbx,3,4))cpsv2_2=7.
If (ic1aax eq 4 and any(id1bbx,0,1,2))cpsv2_2=6.
If (ic1aax eq 4 and any(id1bbx,3,4))cpsv2_2=7.
if (cpsv2_2 eq 7 and not missing(ig2e) and range(ig2e,3,6))cpsv2_2=8.
 
 
Variable labels cpsv2_2 CPS Version 2 September at followup.
value lables cpsv2_2 
 (0) 0 Intact-1 
 (1) 1 Intact-2 
 (2) 2 Borderline intact 1 
 (3) 3 Borderline intact 2 
 (4) 4 Moderate impair 1 
 (5) 5 Moderate impair 2 
 (6) 6 Severe 1 
 (7) 7 Severe 2
 (8) 8 Very severe impair.

**cpsv2 end

compute V2change=cpsv2_2 - cpsv2.
recode v2change(low thru -1=1)(0 thru high=0)into v2IMP.
recode v2change (1 thru high=1)(low thru 0=0)into v2DEC.
if (cpsv2 eq 0)v2imp=$sysmis.
if (cpsv2 gt 7)v2dec=$sysmis.



*frequencies variables=v2DEC v2IMP V2change.

**
** CLEAN VARIABLES
**.

recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j 
 h2a_2 h2b_2 h2c_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
 ig2a ig2b ig2c ig2d ig2e ig2f ig2g ig2h ig2i ig2j 
 ig2a_2 ig2b_2 ig2c_2 ig2d_2 ig2e_2 ig2f_2 ig2g_2 ig2h_2 ig2i_2 ig2j_2 (8=4)(9 thru high=sysmis) .

** COMPENSATE IF ADLs MISSING
**.
compute h2cXX= sum (h2e, h2f, h2h, h2i).
count missloc= h2e h2f h2h h2i (missing).
if (missloc eq 4)h2cxx=$sysmis.
if (missloc lt 4)h2cxx= rnd (h2cxx/(4-missloc)).
if (missing(h2c))h2c=h2cxX.

compute h2cXX_2= sum (h2e_2, h2f_2, h2h_2, h2i_2).
count missloc_2= h2e_2 h2f_2 h2h_2 h2i_2 (missing).
if (missloc_2 eq 4)h2cxx_2=$sysmis.
if (missloc_2 lt 4)h2cxx_2= rnd (h2cxx_2/(4-missloc_2)).
if (missing(h2c_2))h2c_2=h2cxx_2.

do repeat x1= h2a h2b h2c h2e h2f h2g h2h h2i h2j
 h2a_2 h2b_2 h2c_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 /
 y1= ig2i ig2g ig2f ig2c ig2d ig2j ig2h ig2b ig2a 
 ig2i_2 ig2g_2 ig2f_2 ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2/.
if (missing(x1))x1=y1.
if (missing(y1))y1=x1.
end repeat. 

** CREATE CARE HOURS
**.
compute frmhrs=sum(p1ab,p1bb,p1cb,p1db,p1fb,p1gb).
if (missing(p1ab) and missing(p1bb) and missing(p1cb))frmhrs=$sysmis.
variable labels frmhrs hours formal care seven days.
recode g3a (120 thru high=120)/g3b (48 thru high=48).
compute infhrs=g3a.
do if not missing(g3b).
compute infhrs=g3a+g3b.
end if.
variable labels infhrs informal hours seven days.
compute infhrs_2=g3a_2.
do if not missing(g3b_2).
compute infhrs_2=g3a_2+g3b_2.
end if.
variable labels infhrs_2 informal hours time 2 seven days.

recode frmhrs infhrs (low thru -1=sysmis)(168 thru high=168).
if (missing(frmhrs))infhrs=$sysmis.
if (missing(infhrs))frmhrs=$sysmis.
compute tothrs=frmhrs+infhrs.
variable labels tothrs hrs total care seven days .

compute anypsy= ii1n.
if (ii1w gt 0 or ii1o gt 0 or ii1p gt 0)anypsy=1.

do repeat mdshc = j1a j1b j1c 
 j1g j1h j1j j1k j1l j1n 
 j1o j1s j1u 
 j1w j1x j1y /
 icode= ii1j ii1l ii1k
 ii1c ii1d ii1e ii1f ii1h ii1a
 ii1b anypsy ii1q 
 ii1r ii1s ii1t /.
if (missing(mdshc)) mdshc= icode.
if (missing(icode))icode=mdshc.
recode mdshc icode (1 thru high=1).
end repeat.

compute dk3b=k3b.
recode ih3 i1a (8=1)(missing=sysmis)(else=0)into xxfill xxfill2.
if (missing(dk3b))dk3b=xxfill.
if (missing(dk3b))dk3b=xxfill2.

variable labels dk3b dk3b no bowel movmnt 3 days moves v not move.

** CREATE DICHOTOMOUS DIAGNOSIS VARIABLES
**.
recode j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k ii1g j1l j1m j1n j1o j1p j1q
 j1r j1s ii1n ii1w ii1o ii1p j1t j1u j1v j1w j1x j1y j1z j1aa j1ab (missing=sysmis)(0=0)(1 thru high=1) into 
 j1aD j1bD j1cD j1dD j1eD j1fD j1gD j1hD j1iD j1jD j1kD ii1gD j1lD j1mD j1nD j1oD j1pD j1qD
 j1rD j1sD ii1nD ii1wD ii1oD ii1pD j1tD j1uD j1vD j1wD j1xD j1yD 
 j1zD j1aaD j1abD.
do if missing(j1sD).
count xxfill=ii1nD ii1wD ii1oD ii1pD (1).
recode xxfill(1 thru high=1).
if (xxfill eq 0 and missing(ii1nD) and missing(ii1wd) and
  missing(ii1od) and missing(ii1pD))xxfill=$sysmis.
compute j1sD=xxfill.
end if.

variable labels j1aD j1ad stroke no vs yes /
 j1bD j1bd chf no vs yes /
 j1cD j1cd cad no vs yes /
 j1dD j1dd hypertension no vs yes /
 j1eD j1ed irreg pulse no vs yes /
 j1fD j1fd pvd no vs yes /
 j1gD j1gd alzheimers no vs yes /
 j1hD j1hd other dementia no vs yes /.

variable labels j1iD j1id head trauma no vs yes /
 j1jD j1jd hemiplegia no vs yes /
 j1kD j1kd ms no vs yes /
 ii1wd ii1wd bipolar disorder no vs yes /
 j1lD j1ld parkinsonism no vs yes /
 j1mD j1md arthritis no vs yes /
 j1nD j1nd hip fracture no vs yes /.
variable labels j1oD j1oD other fractyre no vs yes /
 j1pD j1pD osteorporosis no vs yes /
 j1qD j1qd cataract no vs yes /
 j1rD j1rd glaucoma no vs yes /
 j1sD j1sd any psychiatric diag no vs yes /
 ii1nD ii1nd anxiety no vs yes /
 ii1wD ii1wd bipolar diag no vs yes /
 ii1oD ii1od depression no vs yes /
 ii1pD ii1pd schizophrenia no vs yes / 
 j1tD j1td hiv no vs yes /
 j1uD j1ud pneumonia no vs yes /.
variable labels j1vD j1vd tuberculosis no vs yes /
 j1wD j1wd uti no vs yes /
 j1xD j1xd cancer no vs yes /
 j1yD j1yd diabetes no vs yes /
 j1zD j1zd emps, copd, asthma no vs yes /
 j1aaD j1aad renal failure no vs yes /
 j1abD j1abd thyroid disease no vs yes /.

do if missing(n3d) .
recode in2k (0=0)(missing=sysmis)(else=1)into n3d.
end if.

** CREATE DICHOTOMOUS HEALTH CONDITION MEASURES
**.
recode ij2m ij2f ij2a ij2b ij2g ij2o ij2p ij4 (0 thru 1=0)(2 thru high=1)(missing=sysmis)into 
 ij2mD ij2fD ij2aD ij2bD ij2gD ij2oD ij2pD ij4D/.
recode k3e k4d k4e k9e ij2j ij2r (0=0)(1 thru high=1)(missing=sysmis)into 
 k3eD k4dD k4eD k9eD ij2jD ij2rD .

variable labels ij2mD ij2mD acid reflux no vs yes /
 ij2fD ij2fD airway secretion no vs yes /
 k3eD k3eD sob no vs yes /
 k4dD k4dD character pain no vs yes /
 k4eD k4eD meds control pain no vs yes /
 k9eD k9eD restrained no vs yes /
 ij2aD ij2aD move to stand no vs yes /
 ij2bD ij2bD turn no vs yes /
 ij2gD ij2gD abnormal thoughts no vs yes /
 ij2jD ij1jD Aphasia no vs yes /
 ij2oD ij2oD difficulty sleeping no vs yes /
 ij2pD ij2pD too much sleep no vs yes /
 ij2rD ij2rD bleeding no vs yes /
 ij4D ij4D fatigue no vs yes /.

recode k1b (1 thru high=1).

do if missing(q4).
 recode im3 (missing=sysmis)(0=0)(1=1)(2=2)(8=3)into q4.
end if.


recode k5 k5_2 (0=0)(0 thru 1=1)(1 thru high=2).
recode ij1 ij1_2 (0=0)(0,1,2=1)(2 thru 3=2).
compute fall_1=k5.
if (missing(fall_1))fall_1=ij1.
if (missing(fall_1))fall1=ij12.
compute fall_2=k5_2.
if (missing(fall_2))fall_2=ij1_2.
if (missing(fall_2))fall_2=ij12.

recode fall_1 fall_2 (0=0)(1 thru high=1) into fallany fallany_2.
recode fall_1 fall_2 (0,1=0)(2 thru high=1)into fallTWO fallTWO_2.
compute fallNEW = 0.
if (missing(fall_2))fallnew=0.
if (fall_1 gt 0)fallnew=$sysmis.
if (fall_2 gt 0 and fallnew eq 0)fallnew=1.

if (age lt 1) age=$sysmis.
if (age gt 111)age=$sysmis.
recode age (low thru 64=1)(65 thru 74=2)(75 thru 79=3)(80 thru 84=4)(85 thru 89=5)(90 thru 94=6)(95 thru high=7)into agecats.
compute gender=bb1.
if (missing(gender)) gender=ia2.
recode gender (missing=1)(else=0) into gendermiss.

compute adlDEC= h3.
recode ig8a (missing=sysmis)(2=1)(else=0)into xxdown.
if (missing(adlDEC))adldec=xxdown .
recode adlDEC (missing=1)(else=0) into adldecmiss. 

compute fallyes= k5.
recode ij1 (0=0)(1 thru high=1)into xxfall.
if (missing(fallyes))fallyes=xxfall.
recode fallyes (missing=1)(else=0) into fallyesmiss.

if (missing(g2a))g2a=ip2a.

** GENERAL RECODE TO EXCLUDE OUT OF RANGE VALUES
**.
recode bb1 bb4 cc4 cc5 cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1 e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c h1ab h1bb h1cb h1db h1eb h1fb h1gb 
 h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
 j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
 k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
 k7a k7b k7c k8a k8b k8c k8d k8e k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a m1b 
 n1 n2a n2b n3b n3c n3e n4 n5c n5d o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
 p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
 p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
 p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4a p4b p4c p5 p6 p7
 (10 thru high=sysmis).
recode g3a g3b age (999 thru high=sysmis).
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j H2a_2 h2b_2 h2c_2 h2d_2 h2e_2 
  h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 (9 thru high=sysmis).

count commonMISS = bb1 age bb4 cc4 cc5 cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1 e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c g3a g3b h1ab h1bb h1cb h1db h1eb h1fb h1gb 
 h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
 j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
 k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
 k7a k7b k7c k8a k8b k8c k8d k8e k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a m1b 
 n1 n2a n2b n3b n3c n3e n4 n5c n5d o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
 p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
 p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
 p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4a p4b p4c p5 p6 p7 (missing).

recode ih2 (missing=sysmis)(2=1)(else=0)into cathFILL.
if (missing(i2b))i2b=cathFILL.
recode k5 (0=0)(1 thru high=1)(missing=sysmis)into fellone.
recode ij1 (missing=sysmis)(0=0)(1 thru high=1)into xxFILL.
if (missing(fellONE))fellONE= xxfill.
recode ij12 (0=0)(1=1)(else=sysmis) into xxfill.
if (missing(fellONE))fellONE=xxfill.

recode k5 (0,1=0)(2 thru high=1)(missing=sysmis)into felltwo.
recode ij1 (missing=sysmis)(0,1,2=0)(3 thru high=1)into xxFILL.
if (missing(felltwo))felltwo= xxfill.
recode ij12 (0,1=0)(else=sysmis)into xxfill.
if (missing(felltwo))felltwo=xxfill.

recode ij2h (missing=sysmis)(0=0)(1 thru high=1)into xxFILL.
if (missing(k3f))k3f=xxfill.


** fill in missing with icodes.

do repeat
 x1= bb1 cc8 p7 p5 k9e /
 fill=ia2 ib5a iq4 ir1 in4 /.
if (missing(x1))x1=fill.
end repeat.

recode ia4 (1=1)(2,3=2)(4=3)(5=4)(6=5)into fill.
if (missing(bb4))bb4=fill.
count del_1= ic3a ic3b ic3c (2).
recode del_1 (1 thru high=1).
if (del_1 eq 0 and missing(ic3a) and missing(ic3b) and missing(ic3c))del_1=$sysmis.
if (missing(b3a))b3a=del_1.
recode if1e (0,8=0)(missing=sysmis)(else=1)into fill.
if (missing(f1b))f1b=fill.
compute tran_a=max(h2c,h2h).
if (missing(h2c) and missing(h2h))tran_a=$sysmis.
if (missing(h2b))h2b=tran_a.
recode ij8b (0,1=0)(2,3=1)(else=sysmis)into fill.
if (missing(k7a))k7a=fill.
recode ik3 (missing=sysmis)(5,6=1)(else=0)into fill.
if (missing(l2d))l2d=fill.
recode ik3 (missing=sysmis)(0,1=0)(2=1)(3,4=2)(5=3)(6 thru high=4)into fill.
if (missing(l3))l3=fill.
count skin_a=il1 il3 il4 il5 il6 (1 thru high).
recode skin_a (1 thru high=1).
if (skin_a eq 0 and missing(il1) and missing(il3) and missing(il4) and missing(il5) and missing(il6))skin_a=$sysmis.
if (missing(n1))n1=skin_a.
recode il4 (missing=sysmis)(0=0)(1 thru high=1)into fill.
if (missing(n3b))n3b=fill.
recode il7 (0=0)(1 thru high=1)into fill.
if (missing(n3e))n3e=fill.
recode in2k (0=0)(1 thru high=1)into fill.
if (missing(n5c))n5c=fill.
if (missing(o1b))o1b=iq1a.
if (missing(o1e))o1e=iq1c.
if (missing(o1f))o1f=iq1d.
if (missing(o1g))o1g=iq1e.
if (missing(p1ja))p1ja=in3ha.
recode in2j (0=0)(2,3=1)(1=3)into fill.
if (missing(p2b))p2b=fill.
recode in2i (0=0)(2,3=1)(1=3)into fill.
if (missing(p2e))p2e=fill.
recode in3fa (missing=sysmis)(0=0)(1 thru high=1)into fill.
if (missing(p2o))p2o=fill.
recode in3ea (missing=sysmis)(0=0)(1 thru high=1)into fill.
if (missfing(p2p))p2p=fill.
recode in2m (missing=sysmis)(0=0)(1 thru high=1)into fill.
if (missing(p2s))p2s=fill.


compute h2cPRED =(h4a*.236)+ (h6a*.156)+( h2j *.443)+(-.399).
compute h2cRND = rnd(h2cPRED).
variable labels h2cRND meddy predicted version of h2c loc in home.

recode h2c (missing=1)(else=-0)into locMISS.


** CREATE NEW EXPANDED LOCOMOTION VAR

**.
do repeat locorig = h2c h2c_2 h2d h2d_2/
 locNEW= locI locI_2 locO locO_2/
 gait= k6a k6a_2 k6a k6a_2/
 mode= h4a h4a_2 h4a h4a_2/.
compute locnew=locorig.
recode locnew (8=4).
compute locnew=locnew+1.
do if (locnew eq 1).
if (gait eq 0 and mode lt 2)locnew =0.
end if.
end repeat.

variable labels locI new locomotion inside t1/
 locI_2 new locomotion inside t2/
 locO new locomotion outside t1/
 locO_2 new locomotion outside t2/.
value labels locI locI_2 locO locO_2
 (0)0 ind and gait ind and no walkr or wheelchair
 (1)1 inp othr er (2)2 set up help (3)3 supervision (4)4 limit ass
 (5)5 exten ass (6)6 max assist (7)7 tot dep.

count ambxx= k6a (0) h4a(0,1).
if (missing(K6a) and missing(h4a))ambxx=$sysmis.
 
compute walkimp = locI_2.
recode walkimp (low thru high=0).
if (locI_2 lt locI) walkimp=1.
if (locI eq 0) walkimp=$sysmis.
variable labels walkimp improvement in walking performance on new measure.


compute walkDEc = locI_2.
recode walkDEC (low thru high=0).
if (locI lt locI_2) walkDEC=1.
if (locI eq 7) walkDEC=$sysmis.
variable labels walkDEC decline in walking performance on new measu.


count iadl2s_2= h1ab_2 h1bb_2 (2).
if (missing(h1ab_2) and missing(h1bb_2))iadl2s_2=$sysmis.

count iadl2s= h1ab h1bb (2).
if (missing(h1AB) and missing(h1bb))iadl2s=$sysmis.
 

recode iadl2s_2 (0,1,2,3=0)(4=0)into iadlIMP.
if (iadl2s_2 lt iadl2s ) iadlimp=1.
if (iadl2s eq 0)iadlimp=$sysmis .
variable labels iadlimp improvement in capacity iadl meal prep and housework.

compute iadlalt= h1ab + h1bb.
compute iadlalt_2= h1ab_2 + h1bb_2.
compute iadlaltimp= iadlalt_2 - iadlalt.
if (iadlalt eq 0)iadlaltimp=$sysmis.
recode iadlaltimp (low thru -1=1)(missing=sysmis)(else=0).

**
** rEPLACE MISSING adl CODE VALUES.
recode h2a h2b h2c h2e h2f h2g h2h h2i h2j (0=0)(1=1)
 (2=2)(3=3)(4,8=4)(5=5)(6=6) into
 h2a_a h2b_a h2c_a h2e_a h2f_a h2g_a h2h_a h2i_a h2j_a.
do repeat
 item1=h2a_a h2b_a h2b_a h2b_a h2b_a h2b_a h2e_a h2b_a /
 item2=h2c_a h2f_a h2f_a h2e_a h2e_a h2e_a h2f_a h2g_a / 
 item3= h2f_a h2i_a h2i_a h2i_a h2i_a h2f_a h2i_a h2c_a /
 miss1= tran_1 loco_1 upper_1 lower_1 eat_1 hyg_1 bath_1 bed_1 /
 fill= tran_a loco_a upper_a lower_a eat_a hyg_a bath_a bed_a/.
count miss1= item1 item2 item3 (missing).
compute fill=$sysmis.
do if (miss1 lt 3).
compute fill=sum (item1,item2,item3).
compute fill=rnd(fill/(3-miss1)).
end if.
end repeat.

if (missing(h2b_a))h2b_a=tran_a.
if (missing(h2c_a))h2c_a=loco_a.
if (missing(h2e_a))h2e_a=upper_a.
if (missing(h2f_a))h2f_a=lower_a.
if (missing(h2g_a))h2g_a=eat_a .
if (missing(h2i_a))h2i_a=hyg_a.
if (missing(h2j_a))h2j_a=bath_a.
if (missing(h2a_a))h2a_a=bed_a.
variable labels h2b_a transfer recoded t1.
variable labels h2c_a locomotion in home recoded t1.
variable labels h2e_a dress upper recoded t1.
variable labels h2f_a dress lower recoded t1.
variable labels h2g_a eating recoded t1.
variable labels h2i_a hygiene recoded t1.
variable labels h2j_a bathing recoded t1.
variable labels h2a_a bed mobility recoded t1.
**end replace missing adl numbers for baseline
**


** rEPLACE MISSING adl CODE VALUES.
recode h2a_2 h2b_2 h2c_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 
 h2j_2 (0=0)(1=1)(2=2)(3=3)(4,8=4)(5=5)(6=6) into
 h2a_b h2b_b h2c_b h2e_b h2f_b h2g_b h2h_b h2i_b h2j_b.
do repeat
 item1=h2a_b h2b_b h2b_b h2b_b h2b_b h2b_b h2e_b h2b_b /
 item2=h2c_b h2f_b h2f_b h2e_b h2e_b h2e_b h2f_b h2g_b / 
 item3= h2f_b h2i_b h2i_b h2i_b h2i_b h2f_b h2i_b h2c_b /
 miss1= tran_1 loco_1 upper_1 lower_1 eat_1 hyg_1 bath_1 bed_1 /
 fill= tran_b loco_b upper_b lower_b eat_b hyg_b bath_b bed_b/.
count miss1= item1 item2 item3 (missing).
compute fill=$sysmis.
do if (miss1 lt 3).
compute fill=sum (item1,item2,item3).
compute fill=rnd(fill/(3-miss1)).
end if.
end repeat.

if (missing(h2b_b))h2b_b=tran_b.
if (missing(h2c_b))h2c_b=loco_b.
if (missing(h2e_b))h2e_b=upper_b.
if (missing(h2f_b))h2f_b=lower_b.
if (missing(h2g_b))h2g_b=eat_b. 
if (missing(h2i_b))h2i_b=hyg_b.
if (missing(h2j_b))h2j_b=bath_b.
if (missing(h2a_b))h2a_b=bed_b.
variable labels h2b_b transfer recoded t2.
variable labels h2c_b locomotion in home recoded t2.
variable labels h2e_b dress upper recoded t2.
variable labels h2f_b dress lower recoded t2.
variable labels h2g_b eating recoded t2.
variable labels h2i_b hygiene recoded t2.
variable labels h2j_b bathing recoded t2.
variable labels h2a_b bed mobility recoded t2.
**end replace missing adl numbers for followup 1 or time 2.
**

recode h2c_a h2c_b (0,1=0)(2 thru 5=1)(6 thru high=2)into loc_1 loc_2.
compute LOC_d=loc_2-loc_1.
recode loc_d (low thru 0=0)(1 thru high=1).
if (loc_1 eq 2)loc_d=$sysmis.
variable labels loc_d locomotion decline.

**create delirium measure.
count del_1= b3a b3b (1) ic3a ic3b ic3c (2) ic4(1).
count del_2= b3a_2 b3b_2 (1) ic3a_2 ic3b_2 ic3c_2(2) ic4_2(1).
recode del_1 del_2 (1 thru high=1).
if (del_1 eq 0 and missing(b3a) and missing(b3b) and
  missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1=$sysmis.
if (del_2 eq 0 and missing(b3a_2) and missing(b3b_2) and 
missing(ic3a_2)  and missing(ic3b_2) and missing(ic3c_2) 
and missing(ic4_2))del_2=$sysmis.
variable labels del_1 delirium time 1.
variable labels del_2 delirium time 2.


do if missing(h3).
recode ig8a (2=1)(0,1,3=0)into h3.
end if.
do if missing(h5).
recode ig1fb (0,1,2=0)(3=1)(4,5,6,7,8=2)into h5.
end if.
do if missing(h7a).
recode ig7a (0=0)(1=1)(else=sysmis)into h7a.
end if.

do repeat
 mdshc = e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e /
 icode= ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1i ie1j ie3a ie3b ie3c ie3d ie3f /.
do if missing(mdshc).
recode icode (0,1=0)(2=1)(3=2)into mdshc.
end if.
end repeat.

 
recode h7a h7b i2a i2b (1 thru high=1).
recode f2 (0=0)(1,2=1)into f212 .
recode e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f2 f3a ie1f ie1h ie1k (missing=sysmis)(0=0)(1 thru high=1) into
 e1a12 e1b12 e1c12 e1d12 e1e12 e1f12 e1g12 e1h12 e1i12 
 e3a12 e3b12 e3c12 e3d12 e3e12 f212 f3a13 ie1f13 ie1h12 ie1k12 . 


recode ie2a ie2b ie2c if1a if1b if1c if1e if1f if1g (missing,8=sysmis)(0=0)(1 thru high=1)into ie2a13 ie2b13 ie2c13 
 if1a0 if1b0 if1c0 if1e0 if1f0 if1g0 .
recode if1a if1b if1c if1e if1f if1g (missing,8=sysmis)(0,1=0)(2 thru high=1) into
 if1a01 if1b01 if1c01 if1e01 if1f01 if1g01 .
recode f2 (missing=sysmis)(2=1)(else=0)into f22.
recode f3a (missing=sysmis)(3=2)(else=0)into f3a3.
recode f3a (missing=sysmis)(0,1=0)(else=1)into f3a23 .
variable labels e1a12 e1a12 sadness no vs yes /
 e1b12 e1b12 anger no vs yes /
 e1c12 e1c12 fears no vs yes /
 e1d12 e1d12 health complaints no vs yes /
 e1e12 e1e12 repetirive complaints no vs yes /
 e1f12 e1f12 sad facial expressions no vs yes /
 e1g12 e1g12 crying, tearful no vs yes /
 e1h12 e1h12 withdrawal no vs yes /
 e1i12 e1i12 reduced social interactions no vs yes /
 e3a12 e2a12 wandering no vs yes /
 e3b12 e3b12 verbally abusive no vs yes /
 e3c12 e3c12 physically abusive no vs yes /
 e3d12 e3d12 socially inappropriate no vs yes /
 e3e12 e3e12 resists care no vs yes /
 ie2a13 ie2a13 self report little interest no vs yes /
 ie2b13 ie2b13 self report anxious, restless no vs yes /
 ie2c13 ie2c13 self report sad, depressed no vs yes /
 f212 f212 decline social activities no vs yes /
 f22 f22 declined in soc act and distressed no vs yes /
 f3a13 alone never vs other no vs yes /
 f3a3 f3a3 less all time vs all time no vs yes /
 f3a23 f3a23 not long alone vs long alone no vs yes /
 ie3f13 ie3f13 public sexual behavior no vs yes /.
variable labels if1a0 if1a0 never vs oth part in act of interest no vs yes /
 if1b0 if1b0 never vs other visit socl relat or family no vs yes /
 if1c0 if1c0 never vs other other interactions with socl rel or family no vs yes /
 if1e0 if1e0 never vs other conflict or anger no vs yes /
 if1f0 if1f0 never vs other fearful of family or close frd no vs yes /
 if1g0 if1g0 never vs other neglected, aboused, mistreated no vs yes / 
 if1a01 if1a01 within 30 days part in act or int no vs yes /
 if1b01 if1b01 within 30 days vis soc rel or fam no vs yes /
 if1c01 if1c01 within 30 days oth int wth soc rel or fam no vs yes /
 if1e01 if1e01 within 30 days conflict or anger no vs yes /
 if1f01 if1f01 within 30 days fearful fam mem or close aqu
 if1g01 if1g01 within 30 days neglected, abused, mistreated no vs yes /.


count missadl_a= h2a_a h2b_a h2c_a h2e_a h2f_a h2g_a h2i_a h2j_a (missing). 

recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (0 thru 2=0)(3 thru high=1) into
 h2a02 h2b02 h2c02 h2d02 h2e02 h2f02 h2g02 h2h02 h2i02 h2j02 .
variable labels h2a02 h2a02 bed mobility 0-2 vs oth/
 h2b02 h2b02 transfer 0-2 vs oth/
 h2c02 h2c02 loc inside 0-2 vs oth/
 h2d02 h2d02 loc outside 0-2 vs oth/
 h2e02 h2e02 dress upper 0-2 vs oth/
 h2f02 h2f02 dress lower 0-2 vs oth/
 h2g02 h2g02 eating 0-2 vs oth/
 h2h02 h2h02 toilet 0-2 vs oth /
 h2i02 h2i02 h2i02 hygiene 0-2 vs oth /
 h2j02 h2j02 bathing 0-2 vs oth/.

recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (missing=sysmis)(1=0)(else=1) into
 h2aset h2bset h2cset h2dset h2eset h2fset h2gset h2hset h2iset h2jset .
variable labels h2aset h2aset bed mobility setup vs oth/
 h2bset h2bset transfer setup vs oth/
 h2cset h2cset loc inside setup vs oth/
 h2dset h2dset loc outside setup vs oth/
 h2eset h2eset dress upper setup vs oth/
 h2fset h2fset dress lower setup vs oth/
 h2gset h2gset eating setup vs oth/
 h2hset h2hset toilet setup vs oth /
 h2iset h2iset h2iset hygiene setup vs oth /
 h2jset h2jset bathing setup vs oth/.

recode h1ab h1bb h1cb h1db h1eb h1fb h1gb (missing=sysmis)(1=1)(else=0)into
 h1abs h1bbs h1cbs h1dbs h1ebs h1fbs h1gbs.
VARiable LABELS= h1abs h1abs meal some dif vs oth/
 h1bbs h1bbs house some diff vs oth/
 h1cbs h1cbs finance some dif vs oth/
 h1dbs h1dbs meds some dif vs oth/
 h1ebs h1ebs phone some dif vs oth/
 h1fbs h1fbs shop some dif vs oth/
 h1gbs h1gbs transportation some dif vs oth/.
 

recode b2a cps (missing=sysmis)(0 thru 2=0)(else=1)into b2a02 cps02.
variable labels cps02 cps02 cps 0 thru 2 vs other/
 b2a01 b2a02 decision making 0 thru 2 vs oth.

**
recode c3 h4a h5 h6a h1ab h1bb h6b h2c fall_1 (missing=sysmis)(0=0)(1 thru high=1)into c3X h4aX h5x h6aX h1abX h1bbX h6bX h2cX k5x
 variable labels c3X c3x understand 0 vs other / 
 h4aX h4ax assistive device none vs other /
 h5x h5x up and down stairs without help vs other /
 h6aX h6ax days out every day vs other /
 h1abX h1abx meal prep no difficulty vs other /
 h1bbX h1bbx ordinary housework no difficulty vs other /
 h6bX h6bx hrs phy activity two or more vs less/ 
 h2cX loc in home indep vs other / 
 k5x k5x fell 1 or more times/
** .

compute frmhrs=sum(p1ab,p1bb,p1cb,p1db,p1fb,p1gb).
if (missing(p1ab) and missing(p1bb) and missing(p1cb))frmhrs=$sysmis.
variable labels frmhrs hours formal care seven days/.
recode g3a (120 thru high=120)/g3b (48 thru high=48).
compute infhrs=g3a.
do if not missing(g3b).
compute infhrs=g3a+g3b.
end if.
variable labels infhrs informal hours seven days.
compute infhrs_2=g3a_2.
do if not missing(g3b_2).
compute infhrs_2=g3a_2+g3b_2.
end if.
variable labels infhrs_2 informal hours time 2 seven days.

recode frmhrs infhrs (low thru -1=sysmis)(168 thru high=168).
if (missing(frmhrs))infhrs=$sysmis.
if (missing(infhrs))frmhrs=$sysmis.
compute tothrs=frmhrs+infhrs.
variable labels tothrs tothrs hrs total care seven days .

if (MISSING(H1AB)) H1AB= IG1AB.

recode g1fa (0 thru 2=0)(3 thru high=1)(else =sysmis)into g1fa0.
variable labels g1fa0 helper fam vs frd or neighbor.
recode g1ga g1ha g1ia g1ja g1ka g1la (0=0)(missing=sysmis)(else=1) into g1ga0 g1ha0 g1ia0 g1ja0 g1ka0 g1la0.
recode h5 (0=0)(1 thru high=1)into h5x.

recode infhrs frmhrs tothrs (0 thru 15=0)(15 thru high=1) into infhrs15 frmhrs15 tothrs15. 
variable labels infhrs15 inf care hrs 15 or more no v yes/
 frmhrs15 form care hrs 15 or more no v yes/
 tothrs15 tot hrs care 15 or more no v yes/.

recode g2b g2c f3b (1 thru high=1).
recode frailtyhc (0 thru 11=0)(12 thru high=1) into frailtyhc12.
recode h1ab h1bb h1cb h1db h1eb h1fb h1gb (0 thru 1=0)(2 thru high=1)into h1ab3 h1bb3 h1cb3 h1db3 h1eb3 h1fb3 h1gb3. 
variable labels h1ab3 h1ab3 meal preparation not dep vs dep /
 h1bb3 h1bb3 ordinary housework not dep vs dep /
 h1cb3 h1cb3 manage finances not dep vs dep /
 h1db3 h1db3 manage medications not dep vs dep /
 h1eb3 h1eb1 phone use not dep vs dep /
 h1fb3 h1fb3 shopping not dep vs dep /
 h1gb3 h1gb3 transportationnot dep vs dep / .
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (0,1=0)(2 thru high=1)into h2a2 h2b2 h2c2 h2d2 h2e2 h2f2 h2g2 h2h2 h2i2 h2j2. 
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (0=0)(1 thru high=1)into h2a1 h2b1 h2c1 h2d1 h2e1 h2f1 h2g1 h2h1 h2i1 h2j1 .
variable labels h2a2 h2a2 mobility in bed indep vs not in /
 h2b2 h2b2 transfer indep vs not in /
 h2c2 h2c2 locomotion in home indep vs not in /
 h2d2 h2d2 locomotion outside indep vs not in /
 h2e2 h2e2 dress upper body indep vs not in /
 h2f2 h2f2 dress lower body indep vs not in /
 h2g2 h2g2 eating indep vs not in /
 h2h2 h2h2 toilet use indep vs not in /
 h2i2 h2i2 personal hygiene indep vs not in /
 h2j2 h2j2 bathingindep vs not in /.
recode h4a (0 thru 3=0)(4 thru high=1) into h4a4.
recode h4b (0=0)(1 thru high=1)into h4b0/
 h5 (0 thru 1=0)( 2 thru high=1)into h52/
 h6a (0 thru 2=0)(3 thru high=1)into h6a3/
 ig6a (0,1=0)(2 thru high=1)into ig6a2/
 i1a i3 (0,1=0)(2 thru high=1)into i1a2 i32/
 ig4 ig5 (0=0)(1 thru high=1) into ig41 ig51.
do if missing(i32).
recode ih3 (0,1=0)(2 thru high=1)(missing=sysmis)into i32.
end if.
variable labels h4a4 h4a4 wheelchair inside no vs yes /
 h4b0 h4b0 assis device outdoors no vs yes /
 h52 h52 stairs yes vs not at all /
 h6a3 h6a3 days out yes vs no /
 ig6a2 ig6a hrs of exercise less than 1 hr vs more /
 i1a2 i1a2 bladder continent yes vs no /
 i32 i32 bowel continent yes vs no/
 ig41 ig41 distance walked did not walk vs walk/
 ig51 ig51 wheeled by others yes vs no /.

recode numdays1 (missing=sysmis)(low thru 225=0)(226 thru high=1)into numdayDICH.
recode numdays1 (missing=0)(0=1)(1 thru 135=2)(136 thru 225=3)(226 thru 410=4)
 (411 thru 775=5)(776 thru high=6)into days1REC.
value labels days1REC (0) missing (1)zero dsys (2)one thru 135 days (3)136 thru 225 days (4)226 thru 410 days
 (5)411 thru 775 days (6)776 thru high days.

if (missing(bb1))bb1=ia2.
recode ia4 (1=1)(2=2)(3=6)(4=3)(5=4)(6=5) into xxfill.
if (missing(bb4))bb4=xxfill.
if (missing(a2))a2=ia8.
recode ia12a (1=1)(2=2)(3=3)(4=4)(5=5)(6=5)(7=5)(8=6)into xxfill2.
if (missing(cc6))cc6=xxfill2.
recode cps (0=0)(1 thru high=1)into cps16/
 cps (0,1=0)(2 thru high=1)into cps26/
 cps (2,3,4=1)(misssing=sysmis)(else=0) into cps234/
 cps (1=1)(missing=sysmis)(else=0)into cps1/
 cps (5,6=1)(missing=sysmis)(else=0)into cps56.
recode bb4 (1=1)(missing=sysmis)(else=0)into nevMAR/
 bb4 (2=1)(missing=sysmis)(else=0)into mar/
 bb4 (3=1)(missing=0)(else=0)into widow/
 bb4 (4,5=1)(missing=sysmis)(else=0)into sepDIV.
recode age (low thru 59=0)(59 thru high=1)into age60/
 age (low thru 69=0)(69 thru high=1)into age70/
 age (low thru 79=0)(79 thru high=1)into age80/
 age (low thru 89=0)(89 thru high=1)into age90.
variable labels cps16 cps16 cps cognite score of 1 to 6/
 cps26 cps26 cps cognitve score of 2 to 6/
 cps234 cps234 cps cognitive score of 2, 3, 4/
 cps1 cps1 cps cognitive score of 1/
 cps56 cps56 cps cognitive score of 5 or 6/
 nevMAr nevmar never married/
 mar mar married/
 widow widow widowed/
 sepDIV sepdiv separated or divorced/.
variable labels age60 60 or older/
 age70 70 or older/
 age80 80 or older/
 age90 90 or older.
recode cc5 (1=1)(missing=sysmis)(else=0)into priHOME/
 cc5 (2=1)(missing=sysmis)(else=0)into withHC/
 cc5 (3,4,5=1)(missing=sysmis)(else=0)into supHOUSE/.
variable labels priHOME prihome prihome live in private home no home care services /
 withHC withhc private home with home care services/
 suphouse suphouse lives in a supported housing environment/.
recode cc6 (1=1)(missing=sysmis)(else=0)into liveALONE/ 
 cc6 (2,3=1)(missing=sysmis)(else=0)into withSPOUSE/
 cc6 (4=1)(missing=sysmis)(else=0)into withCHILD/
 cc6 (5 thru high=1)(missing=sysmis)(else=0)into withOTHERS/.
variable labels liveALONE lives aalone by self/
 withSPOUSE lives with spouse/ 
 withCHILD lives with child /
 withOTHERS lives with others not spouse or child/.


recode country ("ADH12","ADH6"=1)(else=0)into adHOC/
 country ("CANADA_AB","CANADA_BC","CANADA_MB","CANADA_NL",
 "CANADA_NS","CANADA_ON","CANADA_YT"=1)(else=0)into canada.
recode country ("CANADA_AB"=1)(else=0)into CAN_alberta.
recode country ("CANADA_BC"=1)(else=0)into CAN_britCOL.
recode country ("CANADA_MB"=1)(else=0)into CAN_manitoba.
recode country ("CANADA_NS"=1)(else=0)into CAN_novaScotia.
recode country ("CANADA_ON"=1)(else=0)into CAN_ontario.
recode country ("NEWZ"=1)(else=0)into NewZealand.
recode country ("CHI"=1)(else=0)into HongKong.
recode country ("ADH12","ADH6","GER","FIN","ITA"=1)(else=0)into europe/.
variable labels adHOC caases from adhoc study/
 canada all availabe canadian provinces /
 CAN_britcol british columbia/.
recode country ("USA_CT"=1)(else=0)into usa_conn /
 country ("USA_CA","USA_CT","USA_GA","USA_LA","USA_MA",
 "USA_MO","USA_NJ","USA_NY","USA_RI","USA_TX"=1)(else=0)into usa /
 country ("USA_GA"=1)(else=0)into usa_georgia /
 country ("USA_LA"=1)(else=0)into usa_louisia /
 country ("USA_MA"=1)(else=0)into usa_mass /
 country ("USA_MO"=1)(else=0)into usa_missouri /
 country ("USA_NJ"=1)(else=0)into usa_newJersey /
 country ( "USA_NY"=1)(else=0)into usa_NewYork /.

VARiable LABELS h1abs h1abs meal some dif vs oth.
 
count kin= withchild withspouse(1 thru high).
recode kin (1 thru high=1).
do if not missing(walkdec).
recode kin withchild withspouse k8a ii1gd k8a ii1gd k2c ij2bd n4 ij2gd (missing=0).
end if.
recode b2a (0 thru 2=0)(3 thru high=1)into b2a3.

do if not missing(walkdec).
recode h2bset h2iset h2jset h2j02 h2eset h2hset h2f02 h1fbs h1gbs k3c 
 h1fb3 h6b b2a3 h2a2 h4a4 
 h2f02 j1ld h7a h2b02 k6a
 j1nd h2d2 i2b k2c j1od k7c dk3b age80
 kin k8a ij2gd (missing=0).
end if.
**.
do if not missing(walkdec).
recode h2bset h2iset h2jset h2j02 h2eset h2hset h2f02 h1fbs h1gbs k3c 
 h1fb3 h6b b2a3 h2a2 h4a4 
 h2f02 j1ld h7a h2b02 k6a
 j1nd h2d2 i2b k2c j1od k7c dk3b age80
 kin k8a ij2gd (missing=0).
end if.

*frequencies variables=walkdec.


count ambDECrisk2= h2bset h2iset ij2gd k8a (0) h2eset h2hset h1fbs h1gbs k3c kin (1)
 h1fb3 h6b j1ld (1) b2a3 h2a2 h2j02 h4a4 k7c h2d2 (0) h2b02 age80 (1).
 
variable labels ambdecrisk2 walk dec use with loci 0-3.

count dement= j1g j1h (1 thru high).
recode dement (1 thru high=1).
count heart = k3a j1b j1c j1e j1f (1 thru high).
recode heart (1 thru high=1).
count infection = j1t j1u j1v j1w (1 thru high).
recode infection (1 thru high=1).
count unsteady = k3c k6a (1 thru high).
recode unsteady (1 thru high=1).

count ambDECtwo2= h1fb3 h2eset h2f02 j1ld (1) h2d2 h2iset h7a k7c k3c (0)
 b2a3 h6b k6a kin dk3b (1).
variable labels ambdectwo2 walkdec risk with loci 4 thru high.

do if not missing(walkdec).
recode h1fb3 h2e02 h2f02 j1ld j1gd j1hd cps02 h4a4 h7a b2a3
 h6b h3 h1gbs h6a3 h2bset h2eset h2iset h2jset h2hset 
 h2j02 h1fbs k3c dk3b h2b02 
 h2c2 h2a2 j1nd i2b k2c j1od k6a e1a12 e1d12 j1ud b3a
 e1h12 e1e12 h5x (missing=0).
end if.

do if not missing(walkdec).
recode j1nd h2d2 i2b k2c j1od k7c dk3b age80 age90 age70 (missing=0).
end if .

recode b2a (0 thru 2=0)(3 thru high=1)into b2a3.
**.
compute locRISK=$sysmis.
do if loci eq 0.
recode ambDECrisk2 (0 thru 5=0)(6=4)(7,8=5)(9,10=6)(11=7)(12=9)(13=10)(14=12)(15=14)(16 thru high=15)into locRISK.
end if.
do if loci eq 1.
recode ambDECrisk2 (0 thru 4=0)(5 thru 6=2)(7,8=3)(9,10=4)(11=6)(12=7)(13=8)(14=10)(15=13)(16 thru high=15)into locRISK.
end if.
do if loci eq 2.
recode ambDECrisk2 (0 thru 4=0)(5 thru 6=3)(7,8=4)(9=5)(10=6)(11=7)(12=9)(13=11)(14=12)(15=13)(16,17=14)(18 thru high=15)into locRISK.
end if.
do if loci eq 3.
recode ambDECrisk2 (0 thru 4=0)(5 thru 6=3)(7 thru 9=4)(10=5)(11=6)(12,13=7)(14=8)(15 thru 17=9)(18 thru high=12)into locRISK.
end if.
do if loci eq 4.
recode ambDECtwo2 (0 thru 1=0)(2 thru 6=3)(7,8=4)(9=5)(10=6)(11=7)(12=8)(13 thru high=10)into locRISK.
end if.
do if loci eq 5.
recode ambDECtwo2 (0 thru 5=0)(6,7=1)(8=2)(9,10=3)(11=5)(12=6)(13 thru high=9) into locRISK.
end if.
do if loci eq 6.
recode ambDECtwo2 (0 thru 4=0)(5 thru 7=1)(8,9=2)(10=3)(11,12=4)(13 thru high=7) into locRISK.
end if.
do if missing(locRISK).
recode ambDECtwo2 (0=0)(1 thru high=1)into locRISK.
end if.

*frequencies variables=ambDECrisk2 loci .

variable labels locRISK Risk of Loc Decline Final model brokrn into 5% bands.
value labels locRISK (0)0 - lowest risk 0-4% (1)one (2)two (3)three (4)four (5)five (6)six (7)seven (8)eight
 (9) nine (10)ten (11)eleven (12)twelve (13)thirteen (14)fourteen (15)fifteen - highest risk
 70% plus.

recode h2a (1=1)(missing=sysmis)(else=0)into h2aone.
recode frailtyhc (missing=sysmis)(0 thru 11=0)(12 thru high=1)into frailty12 .
recode c2 c3 (missing=sysmis)(0 thru 1=0)(2 thru high=1) into c2TWO c3TWO.
do if not missing(walkdec).
recode h2iset h1gbs dk3b h2aONE n3d h1fb3
 h6a3 j1ld h2b02 h2aset h2bset h2gset h2iset
 h1dbs h1ebs h1gbs frailty12 h3 
 c2TWO c3TWO h6b k2c k8a k8e (missing=0).
end if.

recode j1aa (1 thru high=1).

compute del=$sysmis.
if (b3a eq 0 and b3b eq 0)del=0.
if (b3a eq 1 or b3b eq 1)del=1.
compute del_2=$sysmis.
if (b3a_2 eq 0 and b3b eq 0)del_2=0.
if (b3a eq 1 or b3b_2 eq 1)del_2=1.
compute del1=del.
do if (missing(del1) or del1 eq 0).
count xxyy= ic3a ic3b ic3c (2) ic4 (1).
recode xxyy (1 thru high=1).
if (xxyy eq 0 and missing(ic3a) and missing(ic4))xxyy=$sysmis.
if (not missing(xxyy))del1=xxyy.
end if.
variable labels del1 delirium symptom present.


** HOME CARE FRAILTY SCALE IN PAPER MAY 2016
** THIS IS REPLACED BY NEW FRAILTY MEASURE BELOW
** .

count frailtyHC= h2c (3 thru high) h1bb h1ab h1db (2)
 B2a c3 f2 e1i h5 h6b j1z j1aa j1b k2d
 K3c j1u j1w j1h l1a l2b (1 thru high)
 K5 e1h i3 (2 thru high) 
 H2i h2g h1ab (1 thru high) 
 H1eb h1cb (2 thru high) 
 H2b (3 thru high).
count frailtyMISS= h2c h1bb h1ab h1db 
 B2a c3 f2 e1i h5 h6b j1z j1aa j1b k2d
 K3c j1u j1w j1h l1a l2b 
 K5 e1h i3 
 H2i h2g h1ab 
 H1eb h1cb 
 H2b 
 (missing).

 
if (frailtyMISS gt 6)frailtyHC=$sysmis.

do if range(frailtymiss,1,6).
compute xtemp=frailtyhc/(29-frailtymiss).
compute frailtyHC=frailtyHC+(xtemp*frailtyMISS). 
if (frailtyHC gt 24)frailtyHC=24.
compute frailtyHC=rnd(frailtyhc).
end if.
variable labels frailtyHC Current interRAI Home Care Frailty Scale May 2016.
value labels frailtyHC (0)0.00 No Frailty Markers (7)7.00 Median 
 (20)20.00 Highest Frailty Count.
recode frailtyHC (20 thru high=20).
**
** END OF OLD FRAILTY SCALE 

recode frailtyhc (0 thru 5=1)(missing=sysmis)(else=0)into frail05 /
 frailtyhc (6 thru 11=1)(missing=sysmis)(else=0)into frail11 /
 frailtyhc (12 thru 16=1)(missing=sysmis)(else=0)into frail16 /
 frailtyhc (17 thru high=1)(missing=sysmis)(else=0)into frail20 /.
variable labels frail05 frail05 no vs yes/
 frail11 frail11 score 6 -11 no vs yes/
 frail16 frail16 score 12-16 no vs yes/
 frail20 frail20 score 17-20 no vs yes/.

if (frailtyMISS gt 6)frailtyCU=$sysmis.

do if range(frailtymiss,1,6).
compute xtemp=frailtyCU/(23-frailtymiss).
compute frailtyCU=frailtyCU+(xtemp*frailtyMISS). 
if (frailtyCU gt 24)frailtyCU=24.
compute frailtyCU=rnd(frailtyCU).
end if.
variable labels frailtyCU Current interRAI CHECKUP Frailty Scale May 2016.
value labels frailtyCU (0)0.00 No Frailty Markers (7)7.00 Median 
 (20)20.00 Highest Frailty Count.
recode frailtyCU (20 thru high=20).
**

** END FRAILTY MODIFIED FOR CHECK UP

recode frailtycu (0,1=0)(2 thru high=1)into frailty3.
compute filtA=0.
count filta= b2a c3 h1ab h1eb h5 e1i f2 k3c (1 thru high).
if (missing(b2a) and missing(h1ab) and missing(k3c) and filta eq 0)filta=$sysmis.
**
recode frailtycu (0 thru 3=0)(4 thru high=1) into frailtyCU4.

compute bchange=b1a_2 - b1a .
compute hchange =h2a_2 - h2a.
 
compute personBELIEVES = h7a.
if (missing(h7a))personBELIEVES = ig7a. 

do if missing( h3).
recode ig8a (missing=sysmis)(2=1)(else=0)into h3.
end if.
do if missing (j1n) .
recode ii1a (missing=sysmis)(1,2,3=1)(else=0)into j1n.
end if.
do if missing(j1o).
recode ii1b (missing=sysmis)(1,2,3=1)(else=0)into j1o.
end if.
do if missing(h2c).
compute h2c= ig2f.
end if .

compute h2c9=h2c.
if (missing(h2c9))h2c9=h2h.
if (missing(h2c9))h2c9=h2j.

compute h2c9_2=h2c_2.
if (missing(h2c9_2))h2c9_2=h2h_2.
if (missing(h2c9_2))h2c9_2=h2j_2.

count missMODEL= adlh h7a h7b h7c h3 j1n j1o l1a l2b (missing).

do if missing(p2p).
recode p1fa (0=0)(1 thru high=1)(missing=sysmis)into p2p.
end if.
do if missing(p2p).
recode in3ea (0=0)(1 thru high=1)(missing=sysmis)into p2p.
end if.

do if missing(p2o).
recode p1ga (0=0)(1 thru high=1)(missing=sysmis)into p2o.
end if.
do if missing(p2o).
recode in3fa (0=0)(1 thru high=1)(missing=sysmis)into p2o.
end if.

recode p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja (0=0)(missing=sysmis)(else=1) into
 p1aa1 p1ba1 p1ca1 p1da1 p1ea1 p1fa1 p1ga1 p1ha1 p1ia1 p1ja1.

variable labels p1aa1 p1aa1 home health aides n vs y/
 p1ba1 p1ba1 visiting nurses n vs y/
 p1ca1 p1ca1 homemaking services n vs y/
 p1da1 p1da1 meals n vs y/
 p1ea1 p1ea1 volunteer services n vs y/
 p1fa1 p1fa1 physical therapy n vs y /
 p1ga1 p1ga1 occupational therapy n vs y/
 p1ha1 p1ha1 speech therapy n vs y/
 p1ia1 p1ia1 day care or day hosp n vs y/
 p1ja1 p1ja1 soc worker in home n vs y/.

if (missing(p4a))p4a=in5a.

recode p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l (0=0)(missing=sysmis)(else=1)into 
 p2a1 p2b1 p2c1 p2d1 p2e1 p2f1 p2g1 p2h1 p2i1 p2j1 p2k1 p2l1 .
recode p2m p2n p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z (0=0)(missing=sysmis)(else=1) into
 p2m1 p2n1 p2o1 p2p1 p2q1 p2r1 p2s1 p2t1 p2u1 p2v1 p2w1 p2x1 p2y1 p2z1/.
Recode p4a p4b p4c (0=0)(1 thru high=1)into p4a19 p4b19 p4c19.
Recode p4a p4b p4c (0,1=0)(2 thru high=1)into p4a29 p4b29 p4c29.
recode in2c in2g in2k in2l in2m in2n in2d (missing=sysmis)(0=0)(1 thru high=1) into
 in2c1 in2g1 in2k1 in2l1 in2m1 in2n1 in2d1 .
recode p3a p3b p3c p3d (missing=sysmis)(0,1=0)(2 thru high=1)into p3a2 p3b2 p3c2 p3d2.
variable labels p2a1 p2a1 oxygen/
 p2b1 p2b1 respirator for brething /
 p2c1 p2c1 other resp/
 p2d1 p2d1 alch or drug treat/
 p2e1 p2e1 transfusion/
 p2f1 p2f1 chemotherapy/
 p2g1 p2g1 dialysis/
 p2h1 p2h1 iv infusion central/
 p2i1 p2i1 ic infus peripheral/
 p2j1 p2j1 med by injection/
 p2k1 p2k1 ostomy care/
 p2l1 p2l1 radiation/
 p2m1 p2m1 trach care/
 p2n1 p2n1 exercise therapy/
 p2o1 p2o1 occupational therapy/
 p2p1 p2p1 physical therapy/
 p2q1 p2q1 day center/
 p2r1 p2r1 day hospital/
 p2s1 p2s1 hospice care/
 p2t1 p2t1 physn or clinic visit/
 p2u1 p2u1 respite care/
 p2v1 p2v daily nurse monitoring/
 p2w1 less dailly nurs mon/
 p2x1 p2x1 alert bracelet/
 p2y1 p2y1 skin treatment/
 p2z1 p2z1 special diet/
 p4a19 p4a19 hosp admit/
 p4b19 p4b19 er visit/
 p4c19 p4c19 emergent care.

variable labels in2c1 in2c1 infection control/
 in2g1 in2g1 suctioning/
 in2k1 in2k1 wound care/
 in2l1 in2l1 scheduled toileting/
 in2m1 in2m1 palliative care/
 in2n1 in2n1 turning, positioning/
 in2d1 in2d1 iv meds .
variable labels p3a2 presence oxygen/
 p3b2 p3b2 presence iv with help /
 p3c2 p3c2 presence catheter with help/
 p3d2 p3d2 presence ostomy with help /.
variable labels p4a19 p4a19 one plus hosp admit /
 p4b19 p4b19 one plus er visit /
 p4c19 p4c19 one plus emergent care/
 p4a29 p4a29 two plus hosp admits/
 p4b29 p4b29 two plus er visits/
 p4c29 tp4c29 wo plus emergent care/.

if (missing(p2j1))p2j1=in2d1 .
recode ir3 ir4 (missing=sysmis)(0 thru 2=0)(else=1)into ir30 ir40.
recode ir3 ir4 (missing=sysmis)(8 thru high=1)(else=0)into ir38 ir48.
recode ir5 (missing=sysmis)(0,1,2=0)(else=1)into ir52/.
variable labels ir30 ir30 0 to 2 ADLs indep pre deteriotate/
 ir38 ir38 8 plus adls ind pre deteriotate/
 ir40 ir40 0 to 2 Iadls indep pre deteriorate/
 ir48 ir48 8 plus IADLs indep pre deteriorate/ 
 ir52 ir52 onset beyond 30 days ago/.

recode ij1 ij2a ij2b ij2e ij2f ij2g ij2h ij2i ij2j ij2k ij2l ij2m ij2n ij2o ij2p ij2q ij2r ij2s ij3 ij4 ij7 ij8a ij8b (0=0)(1 thru high=1)
 INTO ij10 ij2a0 ij2b0 ij2e0 ij2f0 ij2g0 ij2h0 ij2i0 ij2j0 ij2k0 
 ij2l0 ij2m0 ij2n0 ij2o0 ij2p0 ij2q0 ij2r0 ij2s0 ij30 ij40 ij70 ij8a0 ij8b0. 
recode k4a (3=1)(missing=sysmis)(else=0)into k4a3/
 k4b l3 n2a (1 thru high=1)(0=0)into k4b1 l31 n2a1.
recode p6 (missing=sysmis)(2=1)(else=0)into p62.
recode p6 (missing=sysmis)(1=1)(else=0)into p61.
recode q1 (0 thru 7=0)(8 thru high=1)into med8.
recode in1d in1h in1e in1g in1f in1a in1c in1b k1a k1e k1c k1d (0=0)(1 thru high=1).
do if missing(n5d).
recode in2n (0,1=0)(2 thru high=1)into fillxx.
compute n5d=fillxx.
end if.
recode n2b (0=0)(1 thru high=1) into n2b1.
recode l2c il6 (2 thru high=1).
recode iq1a o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b 
 iq2 iq3a iq3b iq3c iq4 iq1b ( 1 thru high=1).
recode q4 (missing=sysmis)(2=1)(else=0)into q42.
recode q4 (missing=sysmis)(3=1)(else=0)into q43.
recode p2t (0,1=0)(2 thru high=1)into physician.
recode in5c (0=0)(1 thru high=1) into fillxx.
if (missing(physician))physician= fillxx.
recode ir2 (missing=sysmis)(0=0)(else=1)into ir20.
recode ir2 (Missing=sysmis)(2=1)(else=0)into ir22.
recode b1b ic2c ic4 (missing=sysmis)(0=0)(1 thru high=1).

variable labels physician physician visit/
 p61 p6a improves fewer services/
 p62 p62 deteriorated more services/
 q42 q42 low medication compliance/
 q43 q43 Receives no medications/
 med8 med8 8 or more medications in last 7 days/
 ir20 ir20 self suff improved/
 ir22 ir22 self suff deteriorated.

if (missing(p2v)) p2v=p2w.
do if missing(p2v).
recode p1ba (0=0)(1 thru high=1)(missing=sysmis)into p2v.
end if.
do if Missing(p2v).
recode in3ba (0=0)(1 thru high=1)into p2v.
end if .

recode p2v (0,3=0)(1,2=1)into p2v1.

do if not missing(walkdec).
recode p1aa1 p1ba1 p1ca1 p1da1 p1ga1 p1ha1 p1ja1
 p2a1 p2b1 p2c1 p2e1 p2h1 p2i1 p2j1 p2k1 p2m1 p2o1 p2p1 p2v1 (missing=0).
end if.

count services = p1aa1 p1ca1 p1ja1
 p2a1 p2e1 p2j1 p2o1 p2p1 p2v1 (1).
recode services (0=0)(1=1)(2=2)(3=3)(4 thru high=4) into services2.

recode locrisk (13 thru high=13)(else=copy)into locRISK13.

recode ii1m ii1n ii1w ii1o ii1p ii1q ii1r ( 1 thru high=1) into ii1mD ii1nD ii1wD ii1oD ii1pD ii1qD ii1rD .
variable labels ii1mD copd/
 ii1nD ii1nD anxiety/
 ii1wD ii1wD bipolar/
 ii1oD ii1oD depression/
 ii1pD ii1pD schizophrenia /
 ii1qD ii1qD pneumonia /
 ii1rD ii1rD UTI.
recode ig8a (missing=sysmis)(0=1)(else=0)into ig8a0.
variable labels ig8a0 ig8a0 adl improve.
recode b2a (0=0)(missing=sysmis)(else=1)into b2a0.
recode b2a (0 thru 2=0)(missing=sysmis)(else=1)into b2a02.
recode ic5 (2=1)(missing=sysmis)(else=0)into ic5_two.
recode ic5 (0=1)(missing=sysmis)(else=0)into ic5_zero.
recode ic3a (2=1)(missing=sysmis)(else=0)into ic3a_two.
recode ic3a (0=1)(missing=sysmis)(else=0)into ic3a_zero.
recode ic3b (2=1)(missing=sysmis)(else=0)into ic3b_two.
recode ic3b (0=1)(missing=sysmis)(else=0)into ic3b_zero.
recode c1 (0=0)(missing=sysmis)(else=1)into c10.
recode id3a (0 thru 2=1)(missing=sysmis)(else=0) into id3a_zero.
recode c2 (0 thru 2=1)(missing=sysmis)(else=0)into c20.
recode id1 (0 thru 2=1)(missing=sysmis)(else=0)into id10.
recode c3 (0 thru 2=1)(missing=sysmis)(else=0)into c302.
recode id2 (0 thru 2=1)(else=sysmis)(else=0)into id2_zero.
recode d1 (0 thru 2=1)(missing=sysmis)(else=0)into d102.
recode ia12b ia12c (missing=sysmis)(0=0)(1 thru high=1)into ia12b0 ia12c0.
recode b3a b3b (0=0)(1 thru high=1).
recode cc4 (missing=sysmis)(0=0)(1 thru high=1)into cc40.
recode cc4 (missing=sysmis)(1,2=1)(else=0)into cc412.

variable labels b2a0 decision 0 vs oth/
 b2a02 b2a decision 0-2 b=vs oth /
 ic5_two ic5_two decis decline no v yes/
 ic5_zero ic5_zero decision improve no v yes/
 ic3a_two ic3a_two easily distracted two no vs yes dif normal/
 ic3a_zero ic3a_zero easily distracted zero no vs any yes/
 ic3b_two ic3b_two dis speech two no vs yes dif norml/
 ic3b_zero ic3b_zero dis speech zero no vs any yes/
 c10 c10 hearing zero vs oth/
 id3a_zero hearing 0-2/
 c20 c20 understood 3,4 = 0 0-2 1 /
 id10 uderstood 0-2/
 c302 c302 understand 0-2/
 id2_zero understand 0-2/
 d102 d102 vision 0-2/
 ia12b0 ia12b0 lives with new person no vs yes/
 ia12c0 ia12c0 better live elsewwher no vs yes/
 cc40 cc40 recent hospitalization o vs other/
 cc412 cc412 recent hosp in 2 weeks no vs yes/.

count missall= b1a b1b b2a b2b b3a b3b c1 c2 c3 d1 
 e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e f1a f1b f2 f3a f3b 
 g1ea g1fa g1ga g1ha g1ia g1ja g1ka g1la g2a g2b g2c g2d g3a g3b 
 h1ab h1bb h1cb h1db h1eb h1fb h1gb h2a h2b h2c h2d h2e h2f h2g h2i h2j 
 h3 h4a h4b h5 h6a h6b h7a h7b h7c i1a i1b i2a i2b i3
 j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u
 j1v j1w j1x j1y j1z j1aa j1ab
 k1a k1b k1c k1d k2a k2b k2c k2d k2e k3a k3b k3c k3d k3e k3f k3g
 k4a k4b k4c k4d k4e k5 k6a k6b k7a k7b k7c k8a k8b k8c k8d k8e 
 l1a l1b l1c l2a l2b l2c l2d l3 m1a m1b m1c n1 n2a n2b n3a n3b n3c n3d n3e 
 n4 n5a n5b n5c n5d o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b 
 p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja
 p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n p2o p2p
 p2q p2r p2s p2u p2v p2w p2x p2y p2z p3a p3b p3c p3d 
 p4a p4b p4c p5 p6 p7 q1 q2a q2b q2c q2d q3 q4 (missing).

recode missall (0=0)(1 thru 20=1)(21 thru 40=2)(41 thru 50=3)(51 thru 99=4)
 (100 thru 119=5)(120 thru high=6)into missCATS.
value labels missCATS (0) none (1) 1-20 (2)21-40 (3)41-50 (4)51-99 (5)100-119 (6)120 thru HIGHEST.
variable labels misscats missing items of about 200 total.

** IADL HIIEARCHY**

do repeat IADL = Riadlhi Riadlhi_2 /
 meal= h1ab h1ab_2/
 house = h1bb h1bb_2 /
 shop= h1fb h1fb_2 /
 finance = h1cb h1cb_2/
 meds = h1db h1db_2 /
 twoi = basetwo futwo/
 onei = baseone fuone/
 missi = basemiss fumiss/.
compute iadl=$sysmis.
count twoi = meal house shop finance meds (2).
count onei= meal house shop finance meds (1,2).
count missi= meal house shop finance meds (missing).
if (twoi eq 5)iadl=6.
if any(twoi,3,4)iadl=5.
if (any(twoi,2))iadl=4.
if (missing(iadl) and twoi lt 2 and onei gt 3)iadl=3.
if (missing(iadl) and twoi lt 2 and any(onei,2,3))iadl=2.
if (missing(iadl) and twoi lt 2 and onei eq 1)iadl=1.
if (missing(iadl) and twoi lt 2 and onei eq 0 and missi lt 5)iadl=0. 
if (iadl eq 0 and (twoi gt 0 or onei gt 0))iadl=-1.
end repeat.

** adl hierarchy fill in missing data 
**.
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (8=4)(else=copy)into 
 h2aR h2bR h2cR h2dR h2eR h2fR h2gR h2hR h2iR h2jr.
compute xxfill=h2b.
if (missing(h2b))xxfill=h2f.
compute h2cr2=h2cr.
if (missing(h2cr))h2cr2=xxfill.
compute h2cR = h2cr2.

recode h2a_2 h2b_2 h2c_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 (8=4)(else=copy)into 
 h2aR_2 h2bR_2 h2cR_2 h2dR_2 h2eR_2 h2fR_2 h2gR_2 h2hR_2 h2iR_2 h2jr_2.
compute xxfill=h2b_2.
if (missing(h2b))xxfill=h2f_2.
compute h2cr2_2=h2cr_2.
if (missing(h2cr_2))h2cr2_2=xxfill.
compute h2cR_2 = h2cr2_2.
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (8=4)(else=copy)into 
 h2aR h2bR h2cR h2dR h2eR h2fR h2gR h2hR h2iR h2jr.
compute xxfill=h2b.
if (missing(h2b))xxfill=h2f.
compute h2cr2=h2cr.
if (missing(h2cr))h2cr2=xxfill.
compute h2cR = h2cr2.
count fouradl6 = h2ir h2hr h2cr h2gr (6).
count eatloc6 = h2gr h2cr (6).
count eatloc4 = h2gr h2cr (4,5).
count pertoil4= h2ir h2hr (4,5,6).
count limit = h2ir h2hr h2cr h2gr (3).
count supervision = h2ir h2hr h2cr h2gr (2).
count xxmiss = h2ir h2hr h2cr h2gr (2).
**.
compute adlhN=$sysmis.
if (fouradl6 eq 4) adlhN=6.
if (missing(adlhN) and eatloc6 gt 0)adlhN=5.
if (missing(adlhN) and eatloc4 gt 0)adlhN=4.
if (missing(adlhN) and pertoil4 gt 0)adlhN=3.
if (missing(adlhN) and limit gt 0)adlhN=2.
if (missing(adlhN) and supervision gt 0)adlhN=1.
if (missing(adlhN) and supervision eq 0)adlhN=0.
if (xxmiss eq 4)adlhN=$sysmis.
compute adlh =adlhN.

recode adlh (0 thru 3=0)(4 thru high=1) into adlh4/
 adlh (0=0)(missing=sysmis)(else=1)into adlh0/
 adlh (0 thru 2=0)(missing=sysmis)(else=1)into adlh3/.
variable labels adlh4 adlh4 0 to 3 vss 4 or higher/
 adlh0 adlh0 0 vs 1 or higher/
 adlh3 adlh3 0 thru 2 vs 3 or higher/.

recode riadlhi (missing=sysmis) (0=0)(1 thru high=1)into riadlhi0.
recode riadlhi (missing=sysmis)(0,1=0)(2 thru high=1)into riadlhi1.
recode riadlhi (missing=sysmis)(0 thru 2=0)(3 thru high=1)into riadlhi2.
variable labels riadlhi0 riadlhi0 0 vs 1 or higher/
 riadlhi1 riadlhi2 0,1 vs 2 or higher/
 riadlhi2 riadlhi2 0,1,2 vs 3 or higher.

do repeat locorig = h2cr h2cr_2 /
 locNEW= locIxx locI_2xx /
 gait= k6a k6a_2 /
 mode= h4a h4a_2 /.
compute locnew=locorig.
recode locnew (8=4).
compute locnew=locnew+1.
do if (locnew eq 1).
if (gait eq 0 and mode lt 2)locnew =0.
if (gait eq 0 and missing(mode))locnew=0.
if (missing(gait) and mode lt 2)locnew =0.
end if.
end repeat.

compute walkdec2 = locI_2xx.
recode walkdec2 (low thru high=0).
if (locI_2xx lt locIxx) walkdec2=1.
if (locIxx eq 0) walkdec2=$sysmis.
variable labels walkdec2 improvement in walking performance on updated new measure.

compute walkDEc2= loci_2xx.
recode walkDEC2(low thru high=0).
if (locixx lt locI_2xx) walkDEC2=1.
if (locIxx eq 7) walkDEC2=$sysmis.
variable labels walkDEC2 decline in walking performance on updatednew measure.

count LOCriskVARS= j1kd p1ca1 n4 j1ld suphouse h4b0 withhc p2s1 n5d p1aa1 j1gd p1da1 q43 widow f3a23 f3a13 
 h4a4 k3c p1ha1 k4a3 h2g2 physician b2b ic5_two f22 p1fa1 h1cb3 p2j1 f212 h6a3 k7a l1a id3a_zero h1db3 prihome g2a h5x p2l1 k9a j1nD del1
 h1ab3 h1bb3 k2e n3a p4a29 cc412 b3a h1fb3 h1gb3 p2f1 infhrs15 k9d g2b h6bx h6b j1od p4a19 h3 h2i2 h1abx p2e1 frailtyhc12 
 h2j2 h7a h2a2 h2e2 h7b n5c h2h2 frailtycu4 h2f2 adlh3 h2b2 adlh4 adlh0 h2c2 h2cx (missing).

do repeat 
 zero= k3g n3c b2a0 c20 f3b if1e k3f m1b e1e12 k3f m1b e1e12 e1g12 e1c12 e1d12 e1h12 j1uD k4dd e1f12 k4b1 fellone k8e e1i12 h52 k2c k9c h1eb3 
 h1bbx k8c l2c p4b29 h4a4 k3c k4a3 h2g2 b2b ic5_two f22 h1cb3 f212 h6a3 k7a l1a h1db3 h5x k9a j1nd del1 h1ab3 h1bb3 k2e
 n2a n3a p4a29 cc412 b3a h1fb3 h1gb3 k9d h6bx h6b j1od p4a19 h3 h2i2 h1abx p2e1 h2j2 h7a h2a2 h2e2 h7b 
 n5c h2h2 h2f2 adlh3 adlh4 adlh0 h2b2 /.
recode zero (missig=0).
end repeat.

recode adlh (0=0)(missing=sysmis)(1 thru high=1)into adlh1.
recode adlh (4,5,6=1)(missing=sysmis)(else=0)into adlh4.
count otTHER=p1ga1 p2o1 (1 thru high).
recode otTHER (1 thru high=1).
if (otTHER eq 0 and missing(p1ga1) and missing(p2o1))otTHER=$sysmis.
variable labels otTHER ocupational therapy.

count ptTHER=p1fa1 p2p1 (1 thru high).
recode ptTHER (1 thru high=1).
if (ptTHER eq 0 and missing(p1fa1) and missing(p2p1))ptTHER=$sysmis.
variable labels ptTHER physical therapy.

count canTREAT =p2f1 p2l1 (1 thru high).
recode canTREAT( 1 thru high=1).
if (canTREAT eq 0 and missing(p2f1) and missing(p2l1))canTREAT=$sysmis.
variable labels canTREAT chemo or radiation.
 
count canTREAT =p2f1 p2l1 (1 thru high).
recode canTREAT( 1 thru high=1).
if (canTREAT eq 0 and missing(p2f1) and missing(p2l1))canTREAT=$sysmis.
variable labels canTREAT chemo or radiation.

count infusion =p2h1 p2i1 (1 thru high).
recode infusion( 1 thru high=1).
if (infusion eq 0 and missing(p2h1) and missing(p2i1))infusion=$sysmis.
variable labels infusion iv infusion.

count delhal= k3f k3g (1 thru high).
count ptTHER=p1fa1 p2p1 (1 thru high).
recode ptTHER (1 thru hig=1).
if (ptTHER eq 0 and missing(p1fa1) and missing(p2p1))ptTHER=$sysmis.
variable labels ptTHER physical therapy.
recode delhal (1 thru high=1).
variable labels delhal has delusion or halucination. 

count woundcare = n3d n5c (1 thru high).

compute h7cfill=h7c.
if (missing(h7cfill))h7cfill=h7a.
if (missing(h7cfill))h7cfill=h7b.
compute l2bfill=l2b.
if (missing(l2b))l2bfill=l1a.
recode h2c (missing=sysmis)(0=0)(1 thru high=1) into h2czz.

recode if1a if1b if1c (0,1=0)(2 thru high=1)(missing=sysmis)into if1a01 if1b01 if1c01.
recode bmi (low thru 18=0)(18 thru 21=0)(21 thru 26=1)(26 thru 30=1)(30 thru high=0)into bmi0.
variable labels bmi0 normal 21 thru 30.

recode adlh1 adlh3 adlh4 h4b0 n3d j1kd j1ld j1gd j1hd widow (missing=0).

if (missing(h7c))h7c=h7b.

recode adlh (0=0)(1 thru high=1)(missing=sysmis)into modLOCimp.
count modLOCimp= h7a h7c h3 j1nd j1od n3d p4a19 cc412 p2p1 p2o1 l1a (1 thru high) 
 h1fb3 h1gb3 h2a2 h4a4 h6a3 j1gd j1hd j1ld (0) k7a adlh1 adlh4 (1).
if (missing(h2c))modLOCimp=$sysmis.

recode modLOCimp (0,1,2=1)(3,4=2)(5,6=3)(7,8=4)(9,10=5)(11,12=6)(13,14=7)(15,16=8)(17 thru high=9).
do if any(loci,5,6,7).
compute modLOCimp=modLOCimp+1.
recode modLOCimp (10 thru high=10).
end if.
count lowestx= h2c (0) cps(6) adlh (0).
if (lowestx gt 0)modLOCimp=1.

value labels modLOCimp (1)one - lowest risk count 0-2 (2)two 3-4 (3)three 5-6 (4)four 7-8 (5)five 9-10
 (6)six 11-12 (7)seven 13-14 (8)eight 15-16 (9)nine 17 plus (10)ten Highest risk improve.
variable labels modLOCimp Model to predict likelihood that locomotion will improve - recover status.

recode p1aa_2 p1ba_2 p1ca_2 p1da_2 p1ea_2 p1fa_2 P1ga_2 p1ha_2 
  p1ia_2 p1ja_2 (1 thru high=1). 

compute walkdecB=walkdec.
if (Missing(walkdec) and not missing(loci_2) and loci eq 0)walkdecB=0.

recode widow f3a13 n2b1 k3c k4a3 h2g2 b2b f22 h1cb3 f212 h6a3 k7a l1a
 id3a_zero h1db3 prihome h5x k9a del1 h1ab3 k2e n3a b3a h1gb3 k9d 
 h6bx h6b h2i2 h1abx h2j2 h2a2 h2e2 h2h2 h2f2 h2f2 h2b2 h2c2 h2cx (missing=0).
recode h7a h7b h3 h3 j1nd j1od l2bfill adlh1 adlh4
 h1fb3 h1gb3 h2a2 h2h2 h4a4 h6a3 j1ld j1gd j1hd
 in2n1 in2l1 p1ca1 in2g1 suphouse withhc p2s1 n5d p1aa1 q2d p2z1 k1c p1ha1
 physician p1fa1 p2c1 prihome p2l1 p4a29 cc412 p2f1 p2k1 p2t1 p3a2 p3c2
 p2h1 p4a19 p2o1 p2e1 p2n1 p3d2 p2p1 n5c p2v1 p2i1 (missing=0).


recode k5 (0=0)(1 thru high=1)into falla.
recode k5 (0,1=0)(2 thru high=1)into fall.
recode e3a e3b e3c e3d e3e b2a (2=1)(missing=sysmis)(else=0) into e3a2 e3b2 e3c2 e3d2 e3e2 b2a2.

** frequencies variables= v2dec age70 age80 age90 e3a2 e3b2 e3c2 e3d2 e3e2 b2a2 h1ebs h1gbs h1fbs 
 dement parttwob j1gd j1hd j1ld b1a b1b b2b b3b k3f k3g kin falla 

do if not missing(v2dec).
recode age70 age80 age90 e3a2 e3b2 e3c2 e3d2 e3e2 b2a2 h1ebs h1gbs h1fbs 
 dement parttwob j1gd j1hd j1ld b1a b1b b2b b3b k3f k3g kin falla (missing=0).
end if.

do if not missing(v2dec).
recode k8a j1ad j1bd j1fd j1jd j1wd
 j1zd k2c k2e k8c n1 n2a1 n2b1 n3b l1a (missing=0).
end if .

do repeat x1=cogRISKdec12 aaarisk bbbrisk cccrisk/.
compute x1 =$sysmis.
end repeat.
do if not missing(cpsv2).
count aaarisk= age70 age80 e3c2 e3d2 j1gd j1hd j1ld kin b3b (1 thru high).
count cccrisk = j1bd j1jd j1fd n2a1 k8a del1 (1).
end if .
recode aaarisk (5 thru high=5).
recode cccrisk (5 thru high=5).

do repeat x1= xxxrisk yyyrisk zzzrisk/.
compute x1 =$sysmis.
end repeat.
do if not missing(cpsv2).
count xxxrisk= age70 e3c2 e3d2 b2a2 j1gd j1hd j1ld kin (1 thru high).
count yyyrisk = k2e k8c h1fbs j1bd j1jd j1fd n2a1 k8a (0). 
count zzzrisk =k2e k8c h1fbs j1bd j1jd j1fd n2a1 k8a (1).
end if .
**.
recode xxxrisk (4 thru high=4).
recode zzzrisk (4 thru high=4).

do if cpsv2 lt 4.
compute cogRISKdec= aaarisk+5.
if (aaarisk eq 0 and cccrisk gt 3) cogRISKdec=cogRISKdec-1.
if (aaarisk eq 1 and cccrisk gt 2) cogRISKdec=cogRISKdec-1.
if (aaarisk eq 2 and cccrisk gt 1) cogRISKdec=cogRISKdec-1.
if (aaarisk eq 3 and cccrisk gt 1) cogRISKdec=cogRISKdec-1.
if (aaarisk eq 4 and cccrisk gt 1) cogRISKdec=cogRISKdec-1.
end if.
do if cpsv2 gt 3.
compute cogRISKdec= xxxrisk +1.
** no adjustment when xxxrisk eq 0.
if (xxxrisk eq 1 and zzzrisk gt 1) cogRISKdec=cogRISKdec-1.
if (xxxrisk eq 2 and zzzrisk gt 0) cogRISKdec=cogRISKdec-1.
if (xxxrisk eq 3 and zzzrisk gt 0) cogRISKdec=cogRISKdec-1.
if (xxxrisk eq 4 and zzzrisk gt 0) cogRISKdec=cogRISKdec-1.
if (xxxrisk eq 5 and zzzrisk gt 0) cogRISKdec=cogRISKdec-1.
end if.
variable labels cogRISKdec risk of cps decline april 2022.
value labels cogRISKdec (1)1 lowest risk (2)2 (3)3 (4)4 (5)5 (6)6 (7)7 (8)8 (9)9 (10)10 Highest risk.

*display labels.
*frequencies variables = locrisk cogriskdec.

rename variables (j1g=j1gdd).
rename variables (j1h=j1hdd).
rename variables (j1l=j1ldd).
rename variables (k8a=k8ad).
rename variables (k8c=k8cd).
rename variables (n2a1=n2a1cog).
rename variables (j1wd =j1wdcog).
rename variables (j1zd =j1zdcog).
rename variables (k2c=k2ccog).
rename variables (n2b1=n2b1cog).
rename variables (l1a=l1acog).


rename variables (b1b=b1bcog).
compute j1ldcog= j1ld.

select if (mbmodel eq 1).
sort cases by case_lbl. 
select if any(case_lbl,'HC3','HC4','HC5','HC7').
save outfile="S:\projectdata2\0000 account shared\Erez datasets\COG_model_compare.sav"
 /keep=country case_lbl cogriskdec cpsv2
aaarisk
cccrisk
xxxrisk 
zzzrisk 
p1ia1
In2l1
p3c2 p1ja1 In2n1 In2k1 p2a1 p2j1 p4a29 p1da1 p2y1 p2v p2p1 p1ba1 p2z1
p2t1 p1aa1 Del1 h1fb k2e k8cD j1f j1b j1j n2a K8aD B2a2 b3b j1ldd Age80
Age70 j1gdd j1hdd e3c e3d Kin h1fbs j1fd  j1bd j1jd n2a1cog j1ldcog e3c2 e3d2  
e3b2 
e3a2
e3e2 
 h1ebs
h1gbs
dement 
 b1bcog
b2b
 k3f
k3g
falla
 j1ad
 j1bd
j1wdcog
j1zdcog k2ccog n1 n2b1cog n3b l1acog v2dec v2imp v2change.

kill code.

sort cases by batch country  facility resid_n2 a1d a1m a1y  .
save outfile="S:\projectdata2\0000 account shared\Erez datasets\cognition_hc.sav"
 /keep=batch country  facility resid_n2 a1d a1m a1y cogriskdec cpsv2
aaarisk
cccrisk
xxxrisk 
zzzrisk 
p1ia1
In2l1
p3c2 p1ja1 In2n1 In2k1 p2a1 p2j1 p4a29 p1da1 p2y1 p2v p2p1 p1ba1 p2z1
p2t1 p1aa1 Del1 h1fb k2e k8cD j1f j1b j1j n2a K8aD B2a2 b3b j1ldd Age80
Age70 j1gdd j1hdd e3c e3d Kin h1fbs j1fd  j1bd j1jd n2a1cog j1ldcog e3c2 e3d2  
e3b2 
e3a2
e3e2 
 h1ebs
h1gbs
dement 
 b1bcog
b2b
 k3f
k3g
falla
 j1ad
 j1bd
j1wdcog
j1zdcog
k2ccog n1 n2b1cog n3b l1acog v2dec v2imp v2change.

rename variables (age80=age80d).
rename variables (iG2f=Ig2fd).
rename variables (k8ad=k8add).
rename variables (kin=kind).
rename variables (j1od=j1odloc).
rename variables (j1gd=j1gdloc).
rename variables (j1hd=j1hdloc).
rename variables (k2ccog=k2cloc).
rename variables (age90=age90loc).
rename variables (age70=age70loc).



save outfile="S:\projectdata2\0000 account shared\Erez datasets\locomotion_hc.sav"
 /keep=batch country  facility resid_n2 a1d a1m a1y walkdec locrisk locI locI_2 locO locO_2 loc_d h2eset h2hset h1fbs h1gbs k3c 
h1fb3 h6b j1ld h2b02 age80D h2bset h2jset ij2gd k8add b2a3 h2a2 h2j02 h4a4 k7c h2d2
h1fb3 h2eset h2f02  j1ld b2a3 h6b k6a kinD dk3b  h2d2 h2iset h7a k7c k3c ig2fD  h2jset k2cloc age90loc age70loc j1gdloc j1hdloc loci
walkdec walkimp ambdecrisk2 ambDECtwo2.








