* Encoding: UTF-8.

** master 99
get file="S:\projectdata2\0000 account shared\spss\2024 IADL Model mdshc20_3asm_with_icodes DISEASES.sav"

frequencies variables= hc_iadl_model
     /statistics


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

compute iadlCHG = Riadlhi - Riadlhi_2
**frequencies variables = Riadlhi Riadlhi_2 iadlCHG
     /statiatics
**crosstabs tables= riadlhi by iadlchg
   /cells=count row col tot
recode iadlchg (low thru -1=1)(missing=sysmis)(else=0)into iadlWORSE/
if (riadlhi eq 6)iadlworse=$sysmis
**frequencies variables= riadlhi riadlhi_2 iadlchg iadlworse 
**means tables =iadlworse by riadlhi_2 by riadlhi

recode  iadlchg (1 thru high=1)(missing=sysmis)(else=0)into iadlBETTER
If (riadlhi eq 0)iadlbetter=$sysmis 
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
recode p4a p4b (missing=sysmis)(0=0)(else=1)into p4a19 p4b19
count lessions=n3a n3b il4 (1).
recode lessions h3 (1 thru high=1).


recode k5 k5_2 (0=0)(0 thru 1=1)(1 thru high=2).
recode ij1 ij1_2 (0=0)(1,2=1)(3 thru 3=2).
compute fall_1=k5.
if (missing(fall_1))fall_1=ij1.
if (missing(fall_1))fall_1=ij12.
compute fall_2=k5_2.
if (missing(fall_2))fall_2=ij1_2.
if (missing(fall_2))fall_2=ij12
recode fall_1 fall_2  (0=0)(1 thru high=1) into fallany fallany_2.
count Ivinfuse=p2h p2i (1,2)
if (ivinfuse eq 0 and missing(p2h) and missing(p2i))ivinfuse=$sysmis


count communicate =cps (6) c2 c3 (4)
count sensory = c1 d1 (0)
recode sensory (2=2)(else = 0)
count calm = e1f  e1e e3a e3b e3d   k3f k3g (1 thru high)
recode calm (0=2)(else=0)
if (communicate eq 3)calm=0
count  CogCom = c2 c3 (0 thru 2) cps (0,1)
recode CogCom (3=2)(else=0)
recode h2g h2c h2b (0 thru 2=2)(3=0)(else=0)into eating walking transfer
count vitality= j1u j1w k2c l1a  l2c   n2a n2b n3a n3b n3c p4a p4b   (1 thru high)
recode vitality (0=2)(else=0)
count stamina= h6a (0) h4a h5 h6b (0)
recode stamina ( 1 thru high=2)
count missT1 = c1   d1  b3b  e1f  e1e  c3  h2b  e3a  e3b  e3d  e3e  h6a  j1u  j1w  k2c  k3f  k3g  j1s 
      k2d  l1a  l1b  l2c  n1  n2a  n2b  n3a  n3b  n3c  p4a  p4b  h6a  b2a (missing)
do if missT1 gt 3
. recode calm CogCom eating walking transfer vitality
     stamina sensory stamina 
     (low thru high=sysmis)
end if 
recode calm CogCom eating walking transfer stamina  vitality sensory 
    (0,1=0)(2=1)
compute intrinsicCOMPOSITE1=  CogCom + eating + walking + transfer + stamina 

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
     h1abd h1bbd h1cbd h1dbd h1ebd h1fbd h1gbd 
var labels e1ad sadness e1ad/  e1bd anger e1bd/e1cd fear e1cd/ e1dd hlth com e1dd/e1ed complaint e1ed/ 
   e1fd pained e1fd/ e1gd crying e1gd/ e1hd withdrawls e1hd/ e1id red soc e1id/
   e3ad wandering e3ad/ e3bd verbal e3bd/ e3cd physical e3cd/ e3dd soc inap e3dd/  e3ed resists care e3ed/ 
var labels  h1abd meal h1abd/  h1bbd housework h1bbd/ h1cbd finance h1cbd/ h1dbd meds h1dbd/ 
    h1ebd phone h1ebd/ h1fbd shopping h1fbd/ h1gbd transportation h1gbd/ 
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (0=1)(missing=0)(else=0)into 
           h2a0 h2b0 h2c0 h2d0 h2e0 h2f0 h2g0 h2h0 h2i0 h2j0
var labels h2a0 bed 0/ h2b0 transfer 0 /h2c0 loc ins 0 / h2d0 loc out 0 /
   h2e0 dress up  0 h2e0/  h2f0 deres low 0 h2f0 /  h2g0 eat 0 h2g0/ 
   h2h0 toilet 0 h1h0/ h2i0  hyg 0 h2i0/ h2j0 bath 0 h2j0/

recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (2=1)(missing=0)(else=0)into 
           h2a2 h2b2 h2c2 h2d2 h2e2 h2f2 h2g2 h2h2 h2i2 h2j2
var labels h2a2 bed 2 h2a2/ h2b2 transfer 2 h2b2/h2c2 loc ins 2 h2c2/ h2d2 loc out 2 h2d2/
   h2e2 dress up  2 h2e2/  h2f2 deres low 2 h2f2 /  h2g2 eat 2 h2g2/
   h2h2 toilet 2 h2i2/ h2i2  hyg 2 h2g2/ h2j2 bath 2 h2j2 /
recode h4a (0=1)(missing=sysmis)(else=0) into h4a0 /
     h4a (1=1)(missing=sysmis)(else=0) into h4a1/
   p6(2=2)(missing=sysmis)(else=0)into p62/
     h7a  m1a m1b ivinfuse  (1 thru high=1)/i1a  i3 (8=1)(missing=sysmis)(else=0)into i1a8  i38/


recode h6a (1 =1)(missing=sysmis)(else=0)into h6a0 /
   cps (missing=sysmis)(2 thru high=1)(else=0)into cps2/ 
   cps (missing=sysmis)(4 thru high=1)(else=0)into cps4/ 
   intrinsiccomposite1 (4,5=1)(missing=sysmis)(else=0)into capacity45 /
    adlh (1,2=1)(missing=sysmis)(else=0)into adlh12 /

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



do if missing(cc4)
. recode ia13 (0=0)(4,5=1)(3=2)(2=3)(1=4)into cc4
end if
do if missing(bb4)
. recode ia4 (1=1)(2,3=2)(4=3)(5=4)(6=5)into bb4
end if
do if (missing(g1ga))
. if (g1ea eq 2)g1ga=1
. if (missing(g1ga) and ip1a1 eq 9)g1ga=1
end if 
do if missing(g1ha)
. if (g1ea eq 2) g1ha =1
. if  (missing(g1ha) and ip1a1 eq 9)g1ha=1
end if
do if missing(g1ha)
. recode ip1c1 (1=0)(0,8=1)into g1ha
end if 
do if missing(h3)
. recode ig8a (0,1,3=0)(2=1)into h3
end if
if (missing(h7a))h7a=ig7a
if (missing(h7b))h7b=ig7b
do if missing(l3)
. recode ik3 (0,1=0)(2=1)(3=2)(4,5,6,7,8=3)(9=4)into l3
end if
if (missing(n2a))n2a=il1
if (missing(m1a)) m1a=ik4d
if (missing(m1b))m1b=ik4c
if (missing(p7))p7=iq4


count Present =b1a b2a c1 c3 (0 thru high)
recode present (1 thru high =1)

do if present eq 1 or j1ac eq 1
. recode j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u 
    j1v j1w j1x j1y j1z j1aa j1ab (missing=0)
end if
do if present eq 1 or i2c eq 1
. recode i2a i2b (mising=0)
end if
do if present eq 1 or k1e eq 1
. recode k1a k1b k1c k1d (missing=0)
end if
do if present eq 1 or k2f eq 1
. recode k2a k2b k2c k2d k2e (missing=0)
end if
do if present eq 1 or k3h eq 1
. recode k3a k3b k3c k3d k3e k3f k3g (missing=0)
end if
do if present eq 1 or k8f eq 1
. recode k8a k8b k8c k8d k8e (missing=0)
end if
do if present eq 1 or k9f eq 1
. recode k9a k9b k9c k9d k9e (missing=0)
end if
do if present eq 1 or n3f eq 1
. recode n3a n3b n3c n3d n3e (missing=0)
end if
do if present eq 1 or n5e eq 1
. recode n5a n5b n5c n5d (missing=0)
end if
do if present eq 1 or o1i eq 1
. recode o1a o1b o1c o1d o1e o1f o1g o1h (missing=0)
end if
do if present eq 1 or p2aa eq 1
. recode p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z (missing=0)
end if 


count Present_2 = b1a_2 b2a_2 c1_2 c3_2 (0 thru high)
recode present_2 (1 thru high =1)

do if present_2 eq 1 or j1ac_2 eq 1
. recode j1a_2 j1b_2 j1c_2 j1d_2 j1e_2 j1f_2 j1g_2 j1h_2 j1i_2 j1j_2 j1k_2 j1l_2 j1m_2 j1n_2 j1o_2 j1p_2 j1q_2 j1r_2 j1s_2 j1t_2 j1u_2 
    j1v_2 j1w_2 j1x_2 j1y_2 j1z_2 j1aa_2 j1ab_2 (missing=0)
end if
do if present_2 eq 1 or i2c_2 eq 1
. recode i2a_2 i2b_2 (mising=0)
end if
do if present_2 eq 1 or k1e_2 eq 1
. recode k1a_2 k1b_2 k1c_2 k1d_2 (missing=0)
end if
do if present_2 eq 1 or k2f_2 eq 1
. recode k2a_2 k2b_2 k2c_2 k2d_2 k2e_2 (missing=0)
end if
do if present_2 eq 1 or k3h_2 eq 1
. recode k3a_2 k3b_2 k3c_2 k3d_2 k3e_2 k3f_2 k3g_2 (missing=0)
end if
do if present_2 eq 1 or k8f_2 eq 1
. recode k8a_2 k8b_2 k8c_2 k8d_2 k8e_2 (missing=0)
end if
do if present_2 eq 1 or k9f_2 eq 1
. recode k9a_2 k9b_2 k9c_2 k9d_2 k9e_2 (missing=0)
end if
do if present_2 eq 1 or n3f_2 eq 1
. recode n3a_2 n3b_2 n3c_2 n3d_2 n3e_2 (missing=0)
end if
do if present_2 eq 1 or n5e_2 eq 1
. recode n5a_2 n5b_2 n5c_2 n5d_2 (missing=sysmis)
end if
do if present_2 eq 1 or o1i_2 eq 1
. recode o1a_2 o1b_2 o1c_2 o1d_2 o1e_2 o1f_2 o1g_2 o1h_2 (missing=0)
end if
do if present_2 eq 1 or p2aa_2 eq 1
. recode p2a_2 p2b_2 p2c_2 p2d_2 p2e_2 p2f_2 p2g_2 p2h_2 p2i_2 p2j_2 p2k_2 p2l_2 p2m_2 p2n_2 p2o_2 p2p_2 p2q_2 p2r_2 p2s_2 p2t_2 p2u_2 p2v_2 p2w_2 p2x_2 p2y_2 p2z_2 (missing=0)
end if 
recode m1a m1b p7(1 thru high=1)


do if missing(h1aa)
. recode ig1aa (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1aa
end if
do if missing(h1ba)
. recode ig1ba (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1ba
end if
do if missing(h1ca)
. recode ig1ca (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1ca
end if
do if missing(h1da)
. recode ig1da (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1da
end if
do if missing(h1fa)
. recode ig1ga (0,1,2=0)(3=1)(5,5=2)(6=3)(8=8)into h1fa
end if
do if missing(k6a)
. recode ij2d (Missing=sysmis)(1 thru 4 =1)(else=0)into k6a
end if
recode h7a h7b (1 thru high=1)
recode b2a (missing=sysmis)(2 thru high=1)(else=0)into b2a2
recode h6a (0=0)(1=1)(else=sysmis)
recode k4b (3,4=1)(missing=sysmis)(else=0)into k4b3
recode c3 (2 thru high=1)(missing=sysmis)(else=0)into c32
recode h5 (0=1)(missing=sysmis)(else=0)into h50
recode communicate (2 thru high=1)(missing=sysmis)(else=0)into communicate2


count missKEY= 
     cc4 bb4 
     (missing)

**frequencies variables= misskey

select if missKEY lt 20

do if not missing(iadlworse)
. recode b1a b2a2 e1gd e3ad e3bd e3cd e3dd e3ed h1abd h1bbd h1fbd  h2d0 h2a0 h2f0 
     j1gd j1hd k2c k2e k3b k3f k3g k8a n3a n3d n5c 
    cps4 cps2 eating
    h1ebd h2j0 h3 h4a1 h6a h7a h7b i1a8 j1ld j1od k7b k3c k4b k4b3 k6a k8c
    l1a m1a m1b p4a19 p62 p7 ivinfuse cogcom  b2b c32 h1fbd h2a0 h2b0 h2c0 h2e0 h2g0 h2h0 h2j0 h50 h6a adlh12 del1
    communicate2 transfer stamina  capacity45  (missing=0)
end if


**logistic regression iadlworse with     b1a b2a2 e3ad e3bd e3cd e3dd e3ed h1abd h1bbd h1fbd   
     j1gd j1hd k2c k2e k3b k3f k3g k4b3 k8a n3a n3d n5c cps4 cps2 eating
    b2b c32 h1fbd h2a0 h2b0 h2c0 h2e0 h2g0 h2h0 h2j0 h50 h6a adlh12 del1
    communicate2 transfer stamina  capacity45 
    /method fstep
    /external
**means tables= iadlbetter by h1ab h2j
** countIADLimpa = ig1bb ig1gb (5,6) 
count IADLimpA= h1bbd h1fbd (1)   h2f (1) n3d (1) h6b (1) k3c (1) p4a19 (1) h1ab (2) h2j (1 thru high) 
count IADLdec = b1a (1) h1abd h1bbd h1fbd (0) j1gd j1hd  h2j0 (1) h1ab (0,1)
recod iadldec (6 thru high=6)
** 
recode h1ab h1bb h1fb (missing=sysmis)(0=1)(else=0) into h1ab0 h1bb0 h1fb0 /
    h2j (missing=sysmis)(0=1)(else=0) into h2j01/
   h1ab (missing=sysmis)(0,1=1)(else=0)into h1ab01

**frequencies variables = iadlworse riadlhi
    b1a h1ab0 h1bb0 h1fb0 j1gd j1hd h2j0 h1ab01
**crosstabs tables= iadlworse  by 
    b1a h1ab0 h1bb0 h1fb0 j1gd j1hd h2j0 h1ab01
   /cells=count row col tot
   /statistics= risk



If (riadlhi eq 0 and any(iadlDEC,4,5,6))IADLdown = 4
compute iadlDOWN2 =$sysmis
if (riadlhi eq 5 and any(iadlDEC,0,1))iadlDOWN2=0
if (riadlhi eq 5 and iadlDEC gt 1)iadlDOWN2=1
if (riadlhi eq 4 and iadlDEC lt 2)iadlDOWN2=1
if (riadlhi eq 4 and any(iadlDEC,2,3))iadlDOWN2=2
if (riadlhi eq 4 and any(iadlDEC,4,5,6))iadlDOWN2=3
if (riadlhi eq 3 and any(iadlDEC,0,1,2))iadlDOWN2=2
if (riadlhi eq 3 and iadlDEC eq 3)iadlDOWN2=3
if (riadlhi eq 3 and iadlDEC gt 3)iadlDOWN2=4
if (riadlhi eq 2 and iadlDEC lt 4)iadlDOWN2=2
if (riadlhi eq 2 and iadlDEC eq 4)iadlDOWN2 =3
if (riadlhi eq 2 and iadlDEC gt 4)iadlDOWN2=4
if (riadlhi eq 1)iadlDOWN2=4
if (riadlhi eq 0)iadlDOWN2=4


var labels iadlDOWN2 risk iadl decline final model dec 5 2023
value labels IADLdown2 (0) 0. Low (1) 1. Tyical (2) 2. High (3) 3. Very high (4) 4. Extremely high

compute iadl2=iadldec
if (J1G GT 0 or j1h gt 0)iadl2=iadl2+1
compute iadl3= iadl2
If (b3b eq 1 or c3 gt 2 or communicate gt 0)iadl3=iadl3+1

recode  h1ab (0,1=0)(low thru high=1)into h1ab01 
count dement = j1g j1h (1 thru high)
recode dement (2=1)
frequencies variables= b1a h1abd h1bbd h1fbd j1gd j1hd  dement  h1ab01 b3b c3 communicate 
means tables iadlworse by  iadl3 by b1a h1abd h1bbd h1fbd j1gd j1hd  dement   h1ab01 b3b c3 communicate 
dement   
kill code

compute iadlDOWN3 =$sysmis
if (riadlhi eq 5 and any(iadl3,0,1))iadlDOWN3=0
if (riadlhi eq 5 and iadl3 gt 1)iadlDOWN3=1
if (riadlhi eq 4 and iadl3 lt 2)iadlDOWN3=1
if (riadlhi eq 4 and any(iadl3,2,3))iadlDOWN3=2
if (riadlhi eq 4 and any(iadl3,4,5,6))iadlDOWN3=3
if (riadlhi eq 3 and any(iadl3,0,1,2))iadlDOWN3=2
if (riadlhi eq 3 and iadl3 eq 3)iadlDOWN3=3
if (riadlhi eq 3 and iadl3 gt 3)iadlDOWN3=4
if (riadlhi eq 2 and iadl3 lt 4)iadlDOWN3=2
if (riadlhi eq 2 and iadl3 eq 4)iadlDOWN3 =3
if (riadlhi eq 2 and iadl3 gt 4)iadlDOWN3=4
if (riadlhi eq 1)iadlDOWN3=4
if (riadlhi eq 0)iadlDOWN3=4

frequencies variables= iadldown2 iadldown3 
     /statistics

means tables= iadlworse by iadldec iadldown2 iadldown3 iadl3
    /statistics

means tables= iadlworse by  iadldown2 by iadldown3
    /statistics
kill code

 
compute iadlNEW=$sysmis
if (iadldown2 eq 0 and any(hc_iadl_model,0,1,2))iadlnew=0
if (iadldown2 eq 0 and any(hc_iadl_model,3,4,5,6,7))iadlnew=1
if (iadldown2 eq 0 and any(hc_iadl_model,0,8,9))iadlnew=0

if (iadldown2 eq 1 and any(hc_iadl_model,0,1,2))iadlnew=0
if (iadldown2 eq 1 and any(hc_iadl_model,3))iadlnew=1
if (iadldown2 eq 1 and any(hc_iadl_model,4,5))iadlnew=2
if (iadldown2 eq 1 and any(hc_iadl_model,6,7))iadlnew=3
if (iadldown2 eq 1 and any(hc_iadl_model,8,9))iadlnew=4

if (iadldown2 eq 2 and any(hc_iadl_model,0,1,2,3))iadlnew=1
if (iadldown2 eq 2 and any(hc_iadl_model,4,5))iadlnew=2
if (iadldown2 eq 2 and any(hc_iadl_model,6,7))iadlnew=3
if (iadldown2 eq 2 and any(hc_iadl_model,8))iadlnew=4
if (iadldown2 eq 2 and any(hc_iadl_model,9))iadlnew=5

if (iadldown2 eq 3 and any(hc_iadl_model,0))iadlnew=4
if (iadldown2 eq 3 and any(hc_iadl_model,1))iadlnew=5
if (iadldown2 eq 3 and any(hc_iadl_model,2,3,4,5,6,7))iadlnew=3
if (iadldown2 eq 3 and any(hc_iadl_model,8))iadlnew=4
if (iadldown2 eq 3 and any(hc_iadl_model,9))iadlnew=5

if (iadldown2 eq 4 and any(hc_iadl_model,0,1,2))iadlnew=5
if (iadldown2 eq 4 and any(hc_iadl_model,3))iadlnew=3
if (iadldown2 eq 4 and any(hc_iadl_model,4,5,6,7))iadlnew=3
if (iadldown2 eq 4 and any(hc_iadl_model,8))iadlnew=4
if (iadldown2 eq 4 and any(hc_iadl_model,9))iadlnew=5

recode iadlnew (3,4=0)(5=1)(else=sysmis) into iadlTARGET

means tables= iadlworse by iadldown2 by communicate fallany 

means tables= iadlworse by iadldown2 by ivinfuse b2b b3b c3 g1ga  h1bbd
    h1ab h1bb h1cb h1db h1eb h4a i2b
means tables= iadlworse by iadldown2 by  j1ld j1a j1b j1c j1d j1e j1g j1g j1h 
means tables= iadlworse by iadldown2 by j1i j1j j1k j1m j1n j1o j1p
 
means tables= iadlworse by iadldown2 by    n2a n2b n3d n5c p7 adlh cps
kill code

temporary
select if not missing(iadlTARGET)
means tables= iadlworse by 
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
    /statistics
kill code
  
select if not missing(hc_iadl_model)
frequencies variables = iadldown2 iadlnew
   /statistics
means tables = iadlworse by hc_iadl_MODEL iadldown2 iadlnew
     /statistics
 
means tables = iadlworse by hc_iadl_MODEL iadldown2 BY iadlnew
kill code

select if not missing(hc_iadl_model)
frequencies variables= hc_iadl_model iadldown2
    /statistics
crosstabs tables= hc_iadl_model by iadldown2
    /cells=count row col tot 
means tables=  iadlworse by hc_iadl_model iadldown2
   /statistics
means tables=  iadlworse by hc_iadl_model by iadldown2
kill code


kill code


count Present =b1a b2a c1 c3 (0 thru high).
recode present (1 thru high =1).

do if present eq 1 or j1ac eq 1.
recode j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o 
 j1p j1q j1r j1s j1t j1u j1v j1w j1x j1y j1z j1aa j1ab (missing=0).
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
recode j1a_2 j1b_2 j1c_2 j1d_2 j1e_2 j1f_2 j1g_2 j1h_2 j1i_2 
 j1j_2 j1k_2 j1l_2 j1m_2 j1n_2 j1o_2 j1p_2 j1q_2 j1r_2 j1s_2 j1t_2 j1u_2 
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

do if missing(h3) .
recode ig8a (2=1)(missing=sysmis)(else=0)into h3.
end if.
do if missing(k8a).
recode ij7 (missing=sysmis)(2=1)(else=0)into k8a.
end if.
recode ia2 ia2_2 ia2_3 (1=1)(2=2)(else=sysmis).
do if missing(bb1).
compute bb1=ia2.
if (missing(bb1) and any(bb1_2,1,2))bb1=bb1_2.
** if (missing(bb1) and any(ia2,2,1,2))bb1=ia2_2.
end if.
do if missin(g2c).
compute g2c=ip2b.
end if.
do if missing(g1c).
compute g1c= ip2b.
end if.
do if missing(i3).
compute i3=ih3.
end if.
do if missing(b2b).
recode ic5 (missing=sysmis)(2=1)(else=0)into b2b.
end if.
do if missing(h2b).
compute h2b=ig2b.
end if.
do if missing(h5).
recode ig1fa (0,1=0)(2,3,4,5=1)(6,8=2)(else=sysmis)into h5.
end if.
do if missing(l2d).
recode ik3 (missing=sysmis)(3 thru high=3)(else=0)into l2d.
end if.
do if missing(l3).
recode ik3 (0,1=0)(2=1)(3,4=2)(5,6,7,8=3)(9=4)(else=0)into l3.
end if.
do if missing(n1).
if (il4 eq 1 or il5 eq 1 or il6 eq 1)n1=1.
if (il4 eq 0 or il5 eq 0 or il6 eq 0)n1=0.
end if.
do if missing(n3b).
if (il4 eq 1 or il5 eq 1)n3b=1.
if (il4 eq 0 or il5 eq 0)n3b=0.
end if.
do if missing(n3d).
recode in2k (missing=sysmis)(1,2,3=1)(else=0)into n3d.
end if.
do if missing(n5c).
recode in2k (missing=sysmis)(1,2,3=1)(else=0)into n5c.
end if .
do if missing(n3e).
recode il7 (missing=sysmis)(1,2,3,4=1)(else=0)into n3e.
end if.
do if missing(o1e).
compute o1e= iq1c.
end if.
do if missing(o1g).
compute o1g=iq1e.
end if.
do if missing(o1a).
compute o1a=iq1a.
end if.
do if missing(o1f).
compute o1f=iq1d.
end if .
do if missing(p2e).
recode in2i (missing=sysmis)(1=3)(2,4=1)(0=0)into p2e.
end if .
do if missing(p2k).
recode ih3 (missing=sysms)(1=1)(else=0) into p2k.
end if .
do if missing(p2o).
recode in3fa (missing=sysmis)(1 thru 7=1)(else=0)into p2o.
end if.
do if missing(p2p).
recode in3ea (missing=sysmis)(1,2,3=1)(else=0)into p2p.
end if.
do if missing(p2v).
recode in3ba (missing=sysmis)(7=1)(else=0) into p2v.
end if.
do if missing(p2w).
recode in3ba (1 thru 6=1)(else=0) into p2w.
end if .
do if missing(p7).
compute p7 = iq4.
end if .
do if missing(q4).
recode im3 (missing=sysmis)(0=0)(1=1)(2=2)(8=3)into q4.
end if.
do if missing(f1b).
recode if1e (missing=sysmis)(1 thru 4=1)(else=0)into f1b.
end if.

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

** HC FRAILTY SCALE -- labelled HCFRt1.
count HCFRt1= h1ba (2,3) h1aa (2,3) h1aa (1,2,3) h1ea (1,2,3) h2i (2,3,4,5,6) h2c (3,4,5,6) 
 h2b (4,5,6) h2h (2,3,4,5,6) h5 (1,2) h6b (1) k5 (1 thru high) k3c (1)
 b2a (1,2,3,4, 5) h1da (2,3) h1ca (1,2,3) j1h (1,2) c3 (1,2,3,4) f2 (1,2) f2 (2) e1i (1,2) e1h (1,2)
 l1a (1) l2a (1) l2b (1) i3 (2,3,4,5) j1w (1,2) j1u (1,2) j1b (1,2) j1z (1,2) p2g (1,2).
recode HCFRt1 (24 thru high=24).
count HCFRt1miss= h1ba h1aa h1aa h1ea h2i h2c 
 h2b h2h h5 h6b k5 k3c 
 b2a h1da h1ea j1h c3 f2 f2 e1i e1h 
 l1a l2a l2b i3 j1w j1u j1b j1z p2g(missing).
if ( HCFRt1Miss gt 4) HCFRt1=$sysmis.

*frequencies variables = HCFRt1 HCFRt1miss.

count HCFRt1B= ig1ba (4,5,6) ig1aa (4,5,6) ig1aa (3,4,5,6) ig1ea (3,4,5,6) ig2b (2,3,4,5,6) ig2f (3,4,5,6) 
 ig2g (4,5,6) ig2h (2,3,4,5,6) ig1fa (3,4,5,6) ig6a (3,4) ij1 (1 thru high) ij2c (2,3,4)
 ic1 (1,2,3,4, 5) ig1da (4.5.6) ig1ca (3,4,5,6) ii1d (1,2,3) id1 (1,2,3,4) if2 (1,2) if2 (1,2) ie1j (1,2,3) ie1i (1,2,3)
 ik2a (1) l2a (1) l2b (1) ih3 (3,4,5) ii1r (1,2,3) ii1q (1,2,3) ii1l (1,2,3) ii1m (1,2,3) in2b (2,3).
recode HCFRt1B (24 thru high=24).
count HCFRt1bmiss= ig1ba ig1aa ig1aa ig1ea ig2b ig2f 
 ig2g ig2h ig1fa ig6a ij1 ij2c 
 ic1 ig1da ig1ca ii1d id1 if2 if2 ie1j ie1i 
 ik2a l2a l2b ih3 ii1r ii1q ii1l ii1m in2b (missing).


*frequencies variables = HCFRt1b HCFRt1bmiss.

**recode HCFRt1miss (15 thru high=15)
 if (HCFRt1Miss gt 4) HCFRt1=$sysmis.

**recode so pre Icr will fit into Icr.

compute HRSthree=$sysmis.
do if g3a lt 800 and g3b lt 800.
compute HRSthree= g3a+g3b.
compute HRSthree= rnd (HRSthree/7).
compute HRSthree= rnd (HRSthree * 3).
end if.

*frequencies variables = hrsthree.

recode bb4 (1=1)(2=2)(3=4)(4=5)(5=6)(6=3)(else=sysmis) into marital /
 cc4 (0=0)(1=4)(2=3)(3=2)(4=1)into priorHS /
 cc5 (1=1)(2=1)(3=2)(4=9)(5=14)into residence /
 cc6 (1=1)(2=2)(3=3)(4=4)(5=7)(6=8)into LIVEwith /
 b2b (missing=sysmis)(2=1)(else=0)into DECISIONworse/
 b3a (missing=sysmis)(1=2)(else=0)into ATTENTION / 
 c1 (missing=sysmis)(0=0)(1=1)(2=3)(3=4) into hear/
 e1a e1b e1c e1d e1e e1f e1g e1h e1i (missing=sysmis)
 (0=0)(1=2)(2=3) into sadness anger unrealistic health anxious
 sad crying withdrawal reduced / 
 e3a e3b e3c e3d e3e (0=0)(1=2)(2=3) into wander verbal physical 
 social resists / 
 g1ea (0=1)(1=0) (2=2)(missing=sysmis)into LIVEcl/
 g1fa (0=0)(1=1)(else=sysmis)into LIVEwth/ 
 g1ha g1ia (0=0)(1=1)(missing=sysmis)into IADLcare ADLcare/ 
 g2a g2c (0=0)(1=1)(else=sysmis) into NOTcont CAREdis /.
do if g1ea eq 2.
compute IADLcare=8.
compute ADLcare=8.
end if.
** HC FRAILTY SCALE 2023.
recode HCFRt1miss (15 thru high=15).
if ( HCFRt1Miss gt 4) HCFRt1=$sysmis.
if (age lt 1) age=$sysmis.
if (age gt 111)age=$sysmis.
recode age (low thru 64=1)(65 thru 74=2)(75 thru 79=3)(80 thru 84=4)(85 thru 89=5)(90 thru 94=6)(95 thru high=7)into agecats.
if (missing(h2c-2)) h2c_2 =ig2f_2.
if (missing(h2b_2))h2b_2= ig2g_2.
do if missing(h5_2).
recode ig1fa (0,1=0)(2,3=1)(4 thru high=2)into h5_2.
end if.
if (missing(k5_2))k5_2= ij1.

count tempT2= h1ba_2 (2,3) h1aa_2 (2,3) h1aa_2 (1,2,3) h1ea_2 (1,2,3) h2i_2 (2,3,4,5,6) h2c_2 (3,4,5,6) 
 h2b_2 (4,5,6) h2h_2 (2,3,4,5,6) h5_2 (1,2) h6b_2 (1) k5_2 (1 thru high) k3c_2 (1)
 b2a_2 (1,2,3,4, 5) h1da_2 (2,3) h1ca_2 (1,2,3) j1h_2 (1,2) c3_2 (1,2,3,4) f2_2 (1,2) f2_2 (2) e1i_2 (1,2) e1h_2 (1,2)
 l1a_2 (1) l2a_2 (1) l2b_2 (1) i3_2 (2,3,4,5) j1w_2 (1,2) j1u_2 (1,2) j1b_2 (1,2) j1z_2 (1,2) p2g_2 (1,2).
recode tempt2 (24 thru high=24).
count tempT2miss= h1ba_2 h1aa_2 h1aa_2 h1ea_2 h2i_2 h2c_2 
 h2b_2 h2h_2 h5_2 h6b_2 k5_2 k3c_2 
 b2a_2 h1da_2 h1ea_2 j1h_2 c3_2 f2_2 f2_2 e1i_2 e1h_2 
 l1a_2 l2a_2 l2b_2 i3_2 j1w_2 j1u_2 j1b_2 j1z_2 p2g_2 (missing).

recode tempT2miss (15 thru high=15).
if (tempt2Miss gt 4)tempt2=$sysmis.
recode j1a j1b j1c j1e j1f j1l j1n j1o j1u j1w j1x j1y 
    j1z j1aa (1 thru high=1).

recode tempT2 (missing=sysmis)(else=1)into frailtychange.

*frequencies variables = frailtychange.

do if frailtychange eq 1 and not missing( HCFRt1).
if (missing( HCFRt1))frailtychange=$sysmis.
if (tempt2 lt HCFRt1)frailtychange =0.
if (tempt2 gt HCFRt1) frailtychange=2.
end if.
value labels frailtychange (0)improve (1)same (2)worse.

recode frailtychange (missing=sysmis)(0=1)(else=0)into frailtybetter.
recode tempT2 (missing=sysmis)(else=0)into frailtyUP2.

compute xxx=$sysmis.
do if frailtyup2 eq 0.
compute xxx=tempT2 - HCFRt1.
if (xxx gt 1 )frailtyUP2 = 1.
if (missing( HCFRt1))frailtyUP2=$sysmis.
end if.
value labels frailtychange (0)improve (1)same (2)worse.
recode frailtychange (0,1=0)(missing=sysmis)(2=1) into frailtyWORSE.
if (missing( HCFRt1) or missing(tempT2))frailtyworse=$sysmis.

recode j1g j1h j1l j1u j1w j1o j1n (2=1)/
 c2 c3 b2a h2c h2d h2f h2g (missing=sysmis)(0=0)(else=1) 
 into c2B c3B h2aB h2cB h2dB h2fB h2gB.
** HCFRt1 b1a j1g j1h c2B c3B h2aB h2cB h2dB h2fB h2gB c2 c3 b1b b2a b2b h2c h2d h2e h2f h2g h6a h6b i1a i3 i2b .
** Create two sub-scales to Predict HC Frailty decline (worsen)
 The other sub scale is the HC Frailty scale.

count frailtydec07 = b1a (1) j1g j1h j1l h2g (1 thru high) b2b (1) .
count frailtydec07b = ic2a (1) ii1c ii1d ii1h (1,2,3) ig2j (1 thru high) ic5 (2).

*FREQUENCIES variables = frailtydec07 frailtydec07b.

count miss7b = ic2a ii1c ii1d ii1h ig2j ic5 (missing).
count rebound = h2cb i2b j1u j1w j1o (1 thru high).
count reboundb = ig2f (1 thru high) ih2 (1) ii1q ii1r ii1a (1 thru high).

count missboundb =ig2f ih2 ii1q ii1r ii1a (missing).

do if missing( HCFRt1).
recode frailtydec07 rebound frailtydec07b reboundb (low thru high=sysmis).
end if.

recode frailtydec07 (4 thru high=4).
recode rebound (4 thru high=4).

recode h2g (0=0)(missing=sysmis)(1 thru high=1)into h2g0.
if (missing(h2g0) and not missing(frailtyworse))h2g0=0.

do if HCFRt1 gt 8.
if (rebound eq 0 and frailtydec07 eq 0)frailtyrisk= 3.
if (rebound eq 0 and frailtydec07 eq 1)frailtyrisk=4.
if (rebound eq 0 and frailtydec07 gt 1)frailtyrisk=5.
if (rebound eq 1 and frailtydec07 eq 0) frailtyrisk=3.
if (rebound eq 1 and frailtydec07 eq 1)frailtyrisk= 3.
if (rebound eq 1 and frailtydec07 gt 1)frailtyrisk= 3.
if (rebound eq 2)frailtyrisk=3.
if (rebound eq 3)frailtyrisk=2.
if (rebound eq 4)frailtyrisk=1.
end if.
do if HCFRt1 lt 9.
if (frailtydec07 eq 0 and any(rebound, 4))frailtyrisk=3.
if (frailtydec07 eq 0 and any(rebound, 3))frailtyrisk=4.
if (frailtydec07 eq 0 and any(rebound, 2))frailtyrisk=5.
if (frailtydec07 eq 0 and any(rebound, 1))frailtyrisk=6.
if (frailtydec07 eq 0 and any(rebound, 0))frailtyrisk=7.
if (frailtydec07 eq 1 and any(rebound, 4))frailtyrisk=4.
if (frailtydec07 eq 1 and any(rebound, 3))frailtyrisk=4.
if (frailtydec07 eq 1 and any(rebound, 2))frailtyrisk=4.
if (frailtydec07 eq 1 and any(rebound, 1))frailtyrisk=6.
if (frailtydec07 eq 1 and any(rebound, 0))frailtyrisk=7.
if (frailtydec07 eq 2 and any(rebound, 4))frailtyrisk=5.
if (frailtydec07 eq 2 and any(rebound, 3))frailtyrisk=6.
if (frailtydec07 eq 2 and any(rebound, 2))frailtyrisk=6.
if (frailtydec07 eq 2 and any(rebound, 1))frailtyrisk=7.
if (frailtydec07 eq 2 and any(rebound, 0))frailtyrisk=8.
if (frailtydec07 eq 3 and any(rebound, 4))frailtyrisk=4.
if (frailtydec07 eq 3 and any(rebound, 3))frailtyrisk=4.
if (frailtydec07 eq 3 and any(rebound, 2))frailtyrisk=8.
if (frailtydec07 eq 3 and any(rebound, 1))frailtyrisk=8.
if (frailtydec07 eq 3 and any(rebound, 0))frailtyrisk=9.
if (frailtydec07 eq 4 and any(rebound, 4))frailtyrisk=4.
if (frailtydec07 eq 4 and any(rebound, 3))frailtyrisk=4.
if (frailtydec07 eq 4 and any(rebound, 2))frailtyrisk=9.
if (frailtydec07 eq 4 and any(rebound, 1))frailtyrisk=9.
if (frailtydec07 eq 4 and any(rebound, 0))frailtyrisk=9.
end if.

value labels frailtyrisk 
 (1) 1 Improvr 1 (2) 2 Improve 2 (3) 3 Improve 3 (4) 4 typical 1
 (5) 5 typical 2 (6) 6 typical 3 (7) 7 decline 1 (8) 8 decline 2 
  (9) 9 decline 3.

*frequencies variables = frailtyrisk frailtychange frailtyworse.
crosstabs tables = frailtyrisk by frailtyworse.
recode frailtydec07 (0=0)(1 thru hi=1) into frailtydec07_c.
recodE rebound (0=0)(1 thru hi=1) into rebound_c.
recodE HCFRT1 (0 thru 8=0)(9 thru hi=1) into HCFRT1_c.

variable labels
 HCFRT1 '(HCFRT1) Baseline Frailty Score [0-24]'/
 HCFRT1_c '(HCFRT1_c) Baseline Frailty Score [0-8=0 9-24=1]'/
 frailtyworse '[friltyworse] Frailty Worsen'/
 frailtydec07 '(frailtydec07) Baseline Frailty SUBSET1 - Cognition [0-4]'/
 rebound '(rebound) Baseline Frailty SUBSET1 - Clinical [0-4]'/
 frailtyrisk '(frailtyrisk) Baseline Frilty Risk Score [1-9]'/ 
 frailtydec07_c '(frailtydec07_c) Baseline Frailty SUBSET1 - Cognition collapsed [0-1]'/
 rebound_c '(rebound_c) Baseline Frailty SUBSET1 - Clinical collapsed [0-1]'/.

sort cases by case_lbl. 
select if (mbmodel eq 1).
select if any(case_lbl,'HC3','HC4','HC5','HC7').
save outfile="S:\projectdata2\0000 account shared\Erez datasets\FRAIL_model_compare.sav"
 /keep=country case_lbl j1o HCFRT1_c frailtydec07_c rebound_c
 frailtyworse frailtyrisk b1a 
 b2b j1g j1h j1l h2g h2cb i2b j1u b1b k2c .

kill code.
*frequencies variables=frailtyworse.
sort cases by batch country facility resid_n2 a1d a1m a1y .
save outfile="S:\projectdata2\0000 account shared\Erez datasets\frailty_hc_mb.sav"
 /keep=batch country facility resid_n2 a1d a1m a1y j1o HCFRT1_c frailtydec07_c rebound_c
 frailtyworse frailtyrisk b1a 
 b2b j1g j1h j1l h2g h2cb i2b j1u b1b k2c .













