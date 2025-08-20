* Encoding: UTF-8.
get file='S:\projectdata2\0000 account shared\Erez datasets\EREZ_HC_sample.sav'.
compute mbmodel = 0.
add files file = *
/file='S:\projectdata2\0000 account shared\icare4old\HC_models_check.sav'
 /drop=bb2.
if missing(mbmodel) mbmodel = 1.
frequencies variables = mbmodel.
   
**frequencies variables= b1a b2a d1
comput outab=0
if (any(country,"BEL","GER","ICE","USA_CL","AUS","JPN","SWED","UK","USA_RI","USA_TX"))outAB=1
select if outab eq 0

**frequencies variables= b1a b2a d1


** IADL HIIEARCHY**

**frequencies variables = Riadlhi
     /statiatics

do repeat   IADL = Riadlhi Riadlhi_2 /
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
if (iadl eq 0 and (twoi gt 0 or onei gt 0))iadl=1.
end repeat.

compute iadlCHG = Riadlhi - Riadlhi_2.
recode iadlchg (low thru -1=1)(missing=sysmis)(else=0)into iadlWORSE/.
if (riadlhi eq 6)iadlworse=$sysmis.
recode  iadlchg (1 thru high=1)(missing=sysmis)(else=0)into iadlBETTER.
If (riadlhi eq 0)iadlbetter=$sysmis .
**frequencies variables= iadlWORSE iadlBETTER
**means tables= iadlworse iadlbetter by riadlhi
   /statistics



** VARS FROM OTHER MODELS BEGIN
**
**  ENTER NEEDED RECODES
**

recode j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k ii1g j1l j1m j1n j1o j1p j1q
        j1r j1s ii1n ii1w ii1o ii1p j1t j1u j1v j1w j1x j1y j1z j1aa j1ab  (missing=sysmis)(0=0)(1 thru high=1) into 
       j1aD j1bD j1cD j1dD j1eD j1fD j1gD j1hD j1iD j1jD j1kD ii1gD  j1lD j1mD j1nD j1oD j1pD j1qD
        j1rD j1sD ii1nD ii1wD ii1oD ii1pD j1tD j1uD j1vD j1wD j1xD j1yD j1zD j1aaD j1abD.
do if missing(j1sD).
count  xxfill=ii1nD ii1wD ii1oD ii1pD (1).
recode xxfill(1 thru high=1).
if (xxfill eq 0 and missing(ii1nD) and missing(ii1wd) and missing(ii1od) and missing(ii1pD))xxfill=$sysmis.
compute j1sD=xxfill.
end if.

variable labels j1aD j1ad stroke  no vs yes /
   j1bD j1bd chf  no vs yes /
  j1cD j1cd cad  no vs yes /
   j1dD j1dd hypertension no vs yes /
   j1eD j1ed irreg pulse no vs yes /
  j1fD j1fd pvd  no vs yes /
  j1gD j1gd alzheimers no vs yes /
  j1hD j1hd other dementia  no vs yes /.

variable labels   j1iD j1id head trauma  no vs yes /
  j1jD j1jd hemiplegia  no vs yes /
  j1kD j1kd ms  no vs yes /
  ii1wd ii1wd bipolar disorder  no vs yes /
 j1lD j1ld parkinsonism  no vs yes /
  j1mD j1md arthritis  no vs yes /
  j1nD j1nd hip fracture  no vs yes /.
variable labels   j1oD j1oD other fractyre  no vs yes /
  j1pD j1pD osteorporosis  no vs yes /
   j1qD  j1qd cataract  no vs yes /
   j1rD j1rd glaucoma  no vs yes /
   j1sD j1sd any psychiatric diag  no vs yes /
  ii1nD ii1nd  anxiety  no vs yes /
   ii1wD ii1wd bipolar diag  no vs yes /
   ii1oD ii1od depression  no vs yes /
   ii1pD ii1pd schizophrenia  no vs yes / 
  j1tD j1td hiv  no vs yes /
  j1uD j1ud pneumonia  no vs yes /.
variable labels  j1vD j1vd tuberculosis  no vs yes /
  j1wD j1wd uti  no vs yes /
  j1xD j1xd cancer  no vs yes /
  j1yD j1yd diabetes  no vs yes /
  j1zD j1zd emps, copd, asthma  no vs yes /
   j1aaD j1aad renal failure  no vs yes /
  j1abD j1abd thyroid disease no vs yes /.
recode p4a p4b (missing=sysmis)(0=0)(else=1)into p4a19 p4b19.
count lessions=n3a n3b il4 (1).
recode lessions h3 (1 thru high=1).


recode k5 k5_2 (0=0)(0 thru 1=1)(1 thru high=2).
recode ij1 ij1_2 (0=0)(1,2=1)(3 thru 3=2).
compute fall_1=k5.
if (missing(fall_1))fall_1=ij1.
if (missing(fall_1))fall_1=ij12.
compute fall_2=k5_2.
if (missing(fall_2))fall_2=ij1_2.
if (missing(fall_2))fall_2=ij12.
recode fall_1 fall_2  (0=0)(1 thru high=1) into fallany fallany_2.
count Ivinfuse=p2h p2i (1,2).
if (ivinfuse eq 0 and missing(p2h) and missing(p2i))ivinfuse=$sysmis.


count communicate =cps (6) c2 c3 (4).
count sensory = c1 d1 (0).
recode sensory (2=2)(else = 0).
count calm = e1f  e1e e3a e3b e3d   k3f k3g (1 thru high).
recode calm (0=2)(else=0).
if (communicate eq 3)calm=0.
count  CogCom = c2 c3 (0 thru 2) cps (0,1).
recode CogCom (3=2)(else=0).
recode h2g h2c h2b (0 thru 2=2)(3=0)(else=0)into eating walking transfer.
count vitality= j1u j1w k2c l1a  l2c   n2a n2b n3a n3b n3c p4a p4b   (1 thru high).
recode vitality (0=2)(else=0).
count stamina= h6a (0) h4a h5 h6b (0).
recode stamina ( 1 thru high=2).
count missT1 = c1   d1  b3b  e1f  e1e  c3  h2b  e3a  e3b  e3d  e3e  h6a  j1u  j1w  k2c  k3f  k3g  j1s 
      k2d  l1a  l1b  l2c  n1  n2a  n2b  n3a  n3b  n3c  p4a  p4b  h6a  b2a (missing).
do if missT1 gt 3.
recode calm CogCom eating walking transfer vitality
     stamina sensory stamina 
     (low thru high=sysmis).
end if .
recode calm CogCom eating walking transfer stamina  vitality sensory 
    (0,1=0)(2=1).
compute intrinsicCOMPOSITE1=  CogCom + eating + walking + transfer + stamina .

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
variable labels del1  delirium symptom present.
recode e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
     h1ab h1bb h1cb h1db h1eb h1fb h1gb (1,2=1)(missing=sysmis)(else=0) into
         e1ad e1bd e1cd e1dd e1ed e1fd e1gd e1hd e1id e3ad e3bd e3cd e3dd e3ed 
     h1abd h1bbd h1cbd h1dbd h1ebd h1fbd h1gbd .
variable labels e1ad sadness e1ad/  e1bd anger e1bd/e1cd fear e1cd/ e1dd hlth com e1dd/e1ed complaint e1ed/ 
   e1fd pained e1fd/ e1gd crying e1gd/ e1hd withdrawls e1hd/ e1id red soc e1id/
   e3ad wandering e3ad/ e3bd verbal e3bd/ e3cd physical e3cd/ e3dd soc inap e3dd/  e3ed resists care e3ed/. 
variable labels  h1abd meal h1abd/  h1bbd housework h1bbd/ h1cbd finance h1cbd/ h1dbd meds h1dbd/ 
    h1ebd phone h1ebd/ h1fbd shopping h1fbd/ h1gbd transportation h1gbd/ .
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (0=1)(missing=0)(else=0)into 
           h2a0 h2b0 h2c0 h2d0 h2e0 h2f0 h2g0 h2h0 h2i0 h2j0.
variable labels h2a0 bed 0/ h2b0 transfer 0 /h2c0 loc ins 0 / h2d0 loc out 0 /
   h2e0 dress up  0 h2e0/  h2f0 deres low 0 h2f0 /  h2g0 eat 0 h2g0/ 
   h2h0 toilet 0 h1h0/ h2i0  hyg 0 h2i0/ h2j0 bath 0 h2j0/.

recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (2=1)(missing=0)(else=0)into 
           h2a2 h2b2 h2c2 h2d2 h2e2 h2f2 h2g2 h2h2 h2i2 h2j2.
variable labels h2a2 bed 2 h2a2/ h2b2 transfer 2 h2b2/h2c2 loc ins 2 h2c2/ h2d2 loc out 2 h2d2/
   h2e2 dress up  2 h2e2/  h2f2 deres low 2 h2f2 /  h2g2 eat 2 h2g2/
   h2h2 toilet 2 h2i2/ h2i2  hyg 2 h2g2/ h2j2 bath 2 h2j2 /.
recode h4a (0=1)(missing=sysmis)(else=0) into h4a0 /
     h4a (1=1)(missing=sysmis)(else=0) into h4a1/
   p6(2=2)(missing=sysmis)(else=0)into p62/
     h7a  m1a m1b ivinfuse  (1 thru high=1)/i1a  i3 (8=1)(missing=sysmis)(else=0)into i1a8  i38/.


recode h6a (1 =1)(missing=sysmis)(else=0)into h6a0 /
   cps (missing=sysmis)(2 thru high=1)(else=0)into cps2/ 
   cps (missing=sysmis)(4 thru high=1)(else=0)into cps4/ 
   intrinsiccomposite1 (4,5=1)(missing=sysmis)(else=0)into capacity45 /
    adlh (1,2=1)(missing=sysmis)(else=0)into adlh12 /.

**
**
** HOSPITAL  // FRAILTY //  QUALITY OF LIFE // WALKING // CAPACITY // COGNITIVE //  
**
     cc4 bb4 
     b1a b2a b2b b3a b3b 
     c3 c3 d1 
         e1ad e1bd e1cd e1dd e1ed e1fd e1gd e1hd e1id
      e3ad e3bd e3cd e3dd e3ed
     g1ga g1ha  
      h1abd h1bbd h1cbd h1dbd h1ebd h1fbd h1gbd 
     h2a h2b h2c h2d h2e h2f h2g 
     h2a0 h2b0 h2c0 h2d0 h2e0 h2f0 h2g0 h2h0 h2i0 h2j0
    h2a2 h2b2 h2c2 h2d2 h2e2 h2f2 h2g2 h2h2 h2i2 h2j2
      h3 h4a h4a0 h4a1  h5  h6a h6a0 h6b h7a h7c 
     i1a i1a8 i2b i3 i38  
     j1bd   j1gd j1hd j1id j1ld j1nd j1od j1ud j1wd j1zd  j1xd j1aad 
     k2a k2c k2e k3a k3b k3c k3d k3e k3f k3g k4a k4b k6a  k8a k8b k8c k8e 
     l1a l2c l3 
    m1a m1b 
    n1  n2a n2b n3a n3b n3c n3d  n5c
   p2p p2o  p4a19 p4b19 p6 p7
   adlh adlh12 cps cps4 cps2   lessions fallany  ivinfuse del1 communicate 
   calm CogCom eating walking transfer stamina  vitality 
    sensory intrinsiccomposite1 capacity45 
** OTHER VARS
    
         

**
**  END OF VAR LIST 
****display dictionary

**temporary
  select if not missing(RIADLHI)
  frequencies variables= a1y bb1 sourcen collage a2 bb4 b1a b2a cc4 cc6 d1 e1a e3a f3a g2a g2c h1aa h1ab h1ba h1bb h1ca h1cb
     h2c h2d h7a i1a j1g j1h  
    adll cps1 iadl iadl1 death province ichess ibladcap imaple imichoice ipucap



do if missing(cc4).
recode ia13 (0=0)(4,5=1)(3=2)(2=3)(1=4)into cc4.
end if.
do if missing(bb4).
recode ia4 (1=1)(2,3=2)(4=3)(5=4)(6=5)into bb4.
end if.
do if (missing(g1ga)).
if (g1ea eq 2)g1ga=1.
 if (missing(g1ga) and ip1a1 eq 9)g1ga=1.
end if .
do if missing(g1ha).
 if (g1ea eq 2) g1ha =1.
 if  (missing(g1ha) and ip1a1 eq 9)g1ha=1.
end if.
do if missing(g1ha).
recode ip1c1 (1=0)(0,8=1)into g1ha.
end if .
do if missing(h3).
recode ig8a (0,1,3=0)(2=1)into h3.
end if.
if (missing(h7a))h7a=ig7a.
if (missing(h7b))h7b=ig7b.
do if missing(l3).
recode ik3 (0,1=0)(2=1)(3=2)(4,5,6,7,8=3)(9=4)into l3.
end if.
if (missing(n2a))n2a=il1.
if (missing(m1a)) m1a=ik4d.
if (missing(m1b))m1b=ik4c.
if (missing(p7))p7=iq4.


count Present =b1a b2a c1 c3 (0 thru high).
recode present (1 thru high =1).

do if present eq 1 or j1ac eq 1.
recode j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u 
    j1v j1w j1x j1y j1z j1aa j1ab (missing=0).
end if.
do if present eq 1 or i2c eq 1.
recode i2a i2b (mising=0).
end if.
do if present eq 1 or k1e eq 1.
recode k1a k1b k1c k1d (missing=0).
end if.
do if present eq 1 or k2f eq 1.
recode k2a k2b k2c k2d k2e (missing=0).
end if.
do if present eq 1 or k3h eq 1.
recode k3a k3b k3c k3d k3e k3f k3g (missing=0).
end if.
do if present eq 1 or k8f eq 1.
recode k8a k8b k8c k8d k8e (missing=0).
end if.
do if present eq 1 or k9f eq 1.
recode k9a k9b k9c k9d k9e (missing=0).
end if.
do if present eq 1 or n3f eq 1.
recode n3a n3b n3c n3d n3e (missing=0).
end if.
do if present eq 1 or n5e eq 1.
recode n5a n5b n5c n5d (missing=0).
end if.
do if present eq 1 or o1i eq 1.
recode o1a o1b o1c o1d o1e o1f o1g o1h (missing=0).
end if.
do if present eq 1 or p2aa eq 1.
recode p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z (missing=0).
end if .


count Present_2 = b1a_2 b2a_2 c1_2 c3_2 (0 thru high).
recode present_2 (1 thru high =1).

do if present_2 eq 1 or j1ac_2 eq 1.
 recode j1a_2 j1b_2 j1c_2 j1d_2 j1e_2 j1f_2 j1g_2 j1h_2 j1i_2 j1j_2 j1k_2 j1l_2 j1m_2 j1n_2 j1o_2 j1p_2 j1q_2 j1r_2 j1s_2 j1t_2 j1u_2 
    j1v_2 j1w_2 j1x_2 j1y_2 j1z_2 j1aa_2 j1ab_2 (missing=0).
end if.
do if present_2 eq 1 or i2c_2 eq 1.
recode i2a_2 i2b_2 (mising=0).
end if.
do if present_2 eq 1 or k1e_2 eq 1.
recode k1a_2 k1b_2 k1c_2 k1d_2 (missing=0).
end if.
do if present_2 eq 1 or k2f_2 eq 1.
recode k2a_2 k2b_2 k2c_2 k2d_2 k2e_2 (missing=0).
end if.
do if present_2 eq 1 or k3h_2 eq 1.
recode k3a_2 k3b_2 k3c_2 k3d_2 k3e_2 k3f_2 k3g_2 (missing=0).
end if.
do if present_2 eq 1 or k8f_2 eq 1.
recode k8a_2 k8b_2 k8c_2 k8d_2 k8e_2 (missing=0).
end if.
do if present_2 eq 1 or k9f_2 eq 1.
recode k9a_2 k9b_2 k9c_2 k9d_2 k9e_2 (missing=0).
end if.
do if present_2 eq 1 or n3f_2 eq 1.
recode n3a_2 n3b_2 n3c_2 n3d_2 n3e_2 (missing=0).
end if.
do if present_2 eq 1 or n5e_2 eq 1.
recode n5a_2 n5b_2 n5c_2 n5d_2 (missing=sysmis).
end if.
do if present_2 eq 1 or o1i_2 eq 1.
recode o1a_2 o1b_2 o1c_2 o1d_2 o1e_2 o1f_2 o1g_2 o1h_2 (missing=0).
end if.
do if present_2 eq 1 or p2aa_2 eq 1.
recode p2a_2 p2b_2 p2c_2 p2d_2 p2e_2 p2f_2 p2g_2 p2h_2 p2i_2 p2j_2 p2k_2 p2l_2 p2m_2 p2n_2 p2o_2 p2p_2 p2q_2 p2r_2 p2s_2 p2t_2 p2u_2 p2v_2 p2w_2 p2x_2 p2y_2 p2z_2 (missing=0).
end if .
recode m1a m1b p7(1 thru high=1).


do if missing(h1aa).
 recode ig1aa (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1aa.
end if.
do if missing(h1ba).
recode ig1ba (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1ba.
end if.
do if missing(h1ca).
recode ig1ca (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1ca.
end if.
do if missing(h1da).
recode ig1da (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1da.
end if.
do if missing(h1fa).
recode ig1ga (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1fa.
end if.
do if missing(k6a).
recode ij2d (Missing=sysmis)(1 thru 4 =1)(else=0)into k6a.
end if.
recode h7a h7b (1 thru high=1).
recode b2a (missing=sysmis)(2 thru high=1)(else=0)into b2a2.
recode h6a (0=0)(1=1)(else=sysmis).
recode k4b (3,4=1)(missing=sysmis)(else=0)into k4b3.
recode c3 (2 thru high=1)(missing=sysmis)(else=0)into c32.
recode h5 (0=1)(missing=sysmis)(else=0)into h50.
recode communicate (2 thru high=1)(missing=sysmis)(else=0)into communicate2.


count missKEY= 
     cc4 bb4 
     b1a b2a b2b b3b 
     c3 c3 
     e1a e1b e1c e3a e3b e3c e3d   
     g1ga g1ha  
     h1aa h1ab h1ba h1bb  h1fa h1fb h1ga h1gb  
     h2a h2b h2c h2g h3 h4a h6a h6b h7a h7c 
     i1a i2b i3 
     j1bd   j1gd j1hd j1id j1ld j1nd j1od j1ud j1wd j1zd  j1xd j1aad 
     k2a k2c k2e k3a k3b k3c k3d k3f k3g k4a k6a  k8a k8b k8c k8e 
     l1a l2c l3 
    m1a m1b 
    n1  n2a n2b n3a n3b n3c n3d  n5c
   p2p p2o  p4a19 p4b19 p6 p7
   adlh cps  (missing).

**frequencies variables= misskey
Ask if this should be highlighted out.
*select if missKEY lt 20.

do if not missing(iadlworse).
recode b1a b2a2 e1gd e3ad e3bd e3cd e3dd e3ed h1abd h1bbd h1fbd  h2d0 h2a0 h2f0 
     j1gd j1hd k2c k2e k3b k3f k3g k8a n3a n3d n5c 
    cps4 cps2 eating
    h1ebd h2j0 h3 h4a1 h6a h7a h7b i1a8 j1ld j1od k7b k3c k4b k4b3 k6a k8c
    l1a m1a m1b p4a19 p62 p7 ivinfuse cogcom  b2b c32 h1fbd h2a0 h2b0 h2c0 h2e0 h2g0 h2h0 h2j0 h50 h6a adlh12 del1
    communicate2 transfer stamina  capacity45  (missing=0).
end if.

**logistic regression iadlworse with     b1a b2a2 e3ad e3bd e3cd e3dd e3ed h1abd h1bbd h1fbd   
     j1gd j1hd k2c k2e k3b k3f k3g k4b3 k8a n3a n3d n5c cps4 cps2 eating
    b2b c32 h1fbd h2a0 h2b0 h2c0 h2e0 h2g0 h2h0 h2j0 h50 h6a adlh12 del1
    communicate2 transfer stamina  capacity45 
    /method fstep
    /external
**means tables= iadlbetter by h1ab h2j
** countIADLimpa = ig1bb ig1gb (5,6) 
count IADLimpA= h1bbd h1fbd (1)   h2f (1) n3d (1) h6b (1) k3c (1) p4a19 (1) h1ab (2) h2j (1 thru high). 
count IADLdec = b1a (1) h1abd h1bbd h1fbd (0) j1gd j1hd  h2j0 (1) h1ab (0,1).
recode iadldec (6 thru high=6).

compute IADLdown=$sysmis.
If (riadlhi eq 5 and any(iadlDEC,0,1))IADLdown = 0.
If (riadlhi eq 5 and any(iadlDEC,2,3,4,5,6))IADLdown = 1.
If (riadlhi eq 4 and any(iadlDEC,0,1,2,3))IADLdown = 1.
If (riadlhi eq 4 and any(iadlDEC,4,5,6))IADLdown = 2.
If (riadlhi eq 3 and any(iadlDEC,0,1,2,3))IADLdown = 2.
If (riadlhi eq 2 and any(iadlDEC,0,1,2,3))IADLdown = 2.
If (riadlhi eq 3 and any(iadlDEC,4,5))IADLdown = 3.
if (riadlhi eq 2 and any(iadlDEC,4))IADLdown = 3.
if (riadlhi eq 1 and any(iadlDEC,2,3,4))IADLdown = 3.
If (riadlhi eq 3 and any(iadlDEC,6))IADLdown = 4.
If (riadlhi eq 2 and any(iadlDEC,5,6))IADLdown = 4.
If (riadlhi eq 1 and any(iadlDEC,5,6))IADLdown = 4.
If (riadlhi eq 0 and any(iadlDEC,4,5,6))IADLdown = 4.
variable labels iadldown risk iadl decline final model dec 5 2023.
value labels IADLdown (0) 0. Low (1) 1. Tyical (2) 2. High (3) 3. Very high (4) 4. Extremely high.
select if (country eq 'USA_MA') or (mbmodel eq 1).
if (mbmodel eq 1) country = 'MODELING TEST'.
*frequencies variables = country mbmodel Iadldown Iadlworse iadlbetter.
*means tables= Iadlworse Iadlbetter by Iadldown 
    /statistics.

rename variables (b1a=b1aD).
*sort cases by b1ad  h1abd h1bbd h1fbd  j1gd 
  j1hd  h2j0  h1ab riadlhi iadlDEC 
  IADLdown iadlworse iadlbetter.
*list variables =  country  b1ad  h1abd h1bbd h1fbd  j1gd 
  j1hd  h2j0  h1ab riadlhi iadlDEC 
  IADLdown iadlworse iadlbetter.
sort cases by case_lbl. 
select if (mbmodel eq 1).
select if any(case_lbl,'HC3','HC4','HC5','HC7').
save outfile="S:\projectdata2\0000 account shared\Erez datasets\IADL_model_compare.sav"
 /keep=country case_lbl b1ad  h1abd h1bbd h1fbd  j1gd 
  j1hd  h2j0  h1ab riadlhi iadlDEC 
  IADLdown iadlworse iadlbetter.

*sort cases by batch country  facility resid_n2 a1d a1m a1y  .
*
save outfile="S:\projectdata2\0000 account shared\Erez datasets\iadl_hc.sav"
 /keep=batch country  facility resid_n2 a1d a1m a1y  
   b1ad  h1abd h1bbd h1fbd  j1gd j1hd  h2j0  h1ab riadlhi iadlDEC 
  IADLdown iadlworse iadlbetter.










