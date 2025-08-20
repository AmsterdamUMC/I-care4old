* Encoding: UTF-8.
get file="S:\projectdata2\0000 account shared\Erez datasets\EREZ_HC_sample.sav".
   
   
**frequencies variables =j2a j2a1 

**display dictionary

**frequencies variables= a1y bb1 sourcen collage a2 bb4 b1a b2a cc4 cc6 d1 e1a e3a f3a g2a g2c h1aa h1ab h1ba h1bb h1ca h1cb
     h2c h2d h7a i1a j1g j1h  
    adll cps1 iadl iadl1 death province ichess ibladcap imaple imichoice ipucap


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
recode p2a_2 p2b_2 p2c_2 p2d_2 p2e_2 p2f_2 p2g_2 p2h_2 p2i_2 p2j_2 p2k_2 p2l_2 p2m_2 p2n_2 p2o_2 
p2p_2 p2q_2 p2r_2 p2s_2 p2t_2 p2u_2 p2v_2 p2w_2 p2x_2 p2y_2 p2z_2 (missing=0).
end if .

do if missing(h3). 
recode ig8a (2=1)(missing=sysmis)(else=0)into h3.
end if.
do if missing(k8a).
recode ij7 (missing=sysmis)(2=1)(else=0)into k8a.
end if.
recode  ia2 ia2_2 ia2_3 (1=1)(2=2)(else=sysmis).
do if missing(bb1).
compute bb1=ia2.
if (missing(bb1) and  any(bb1_2,1,2))bb1=bb1_2.
 if (missing(bb1) and  any(ia2,2,1,2))bb1=ia2_2.
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
compute  h2b=ig2b.
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
recode in2k  (missing=sysmis)(1,2,3=1)(else=0)into n3d.
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




** HC FRAILTY SCALE -- labelled   HCFRt1
count  HCFRt1=  h1ba (2,3) h1aa (2,3) h1aa (1,2,3) h1ea (1,2,3) h2i (2,3,4,5,6) h2c (3,4,5,6) 
    h2b (4,5,6) h2h (2,3,4,5,6) h5 (1,2) h6b (1) k5 (1 thru high) k3c (1)
    b2a (1,2,3,4, 5) h1da (2,3) h1ca (1,2,3)  j1h (1,2) c3 (1,2,3,4) f2 (1,2) f2 (2) e1i (1,2) e1h (1,2)
    l1a (1) l2a (1) l2b (1) i3 (2,3,4,5) j1w (1,2) j1u (1,2) j1b (1,2) j1z (1,2) p2g (1,2)
recode  HCFRt1 (24 thru high=24)
count  HCFRt1miss= h1ba  h1aa  h1aa h1ea  h2i  h2c  
    h2b  h2h  h5  h6b  k5 k3c 
    b2a h1da h1ea  j1h  c3  f2  f2  e1i  e1h 
    l1a  l2a  l2b  i3  j1w  j1u  j1b  j1z  p2g(missing)
if ( HCFRt1Miss gt 4) HCFRt1=$sysmis

count  HCFRt1B=  ig1ba (4,5,6) ig1aa (4,5,6) ig1aa (3,4,5,6) ig1ea (3,4,5,6) ig2b (2,3,4,5,6) ig2f (3,4,5,6) 
    ig2g (4,5,6) ig2h (2,3,4,5,6) ig1fa (3,4,5,6) ig6a (3,4) ij1 (1 thru high) ij2c (2,3,4)
    ic1 (1,2,3,4, 5) ig1da (4.5.6) ig1ca (3,4,5,6)  ii1d (1,2,3) id1 (1,2,3,4) if2 (1,2) if2 (1,2) ie1j (1,2,3) ie1i (1,2,3)
    ik2a (1) l2a (1)  l2b (1) ih3 (3,4,5) ii1r (1,2,3) ii1q (1,2,3) ii1l (1,2,3) ii1m (1,2,3) in2b (2,3).
recode  HCFRt1B (24 thru high=24).
count  HCFRt1bmiss= ig1ba  ig1aa  ig1aa  ig1ea  ig2b  ig2f  
    ig2g  ig2h  ig1fa  ig6a ij1  ij2c 
    ic1  ig1da  ig1ca  ii1d  id1  if2  if2  ie1j  ie1i 
    ik2a l2a  l2b  ih3  ii1r  ii1q  ii1l  ii1m in2b  (missing).

**frequencies variables=  HCFRt1  HCFRt1miss  HCFRt1b  HCFRt1bmiss
    /statistics
**frequencies variables=  h1ba  h1aa  h1aa h1ea  h2i  h2c  
    h2b  h2h  h5  h6b  k5 k3c 
    b2a h1da h1ea  j1h  c3  f2  f2  e1i  e1h 
    l1a  l2a  l2b  i3  j1w  j1u  j1b  j1z p2g
**frequencies variables=  ig1ba  ig1aa  ig1aa  ig1ea  ig2b  ig2f  
    ig2g  ig2h  ig1fa  ig6a ij1  ij2c 
    ic1  ig1da  ig1ca  ii1d  id1  if2  if2  ie1j  ie1i 
    ik2a l2a  l2b  ih3  ii1r  ii1q  ii1l  ii1m in2b


**recode  HCFRt1miss (15 thru high=15)
  if ( HCFRt1Miss gt 4) HCFRt1=$sysmis



**frequencies variables=country




** CAP TEST

count itemx=   k2a i2b (1) j1u j1n (1,2) 
     H3 (1).
if (missing(k2a) and missing(j1u) and missing(h3))itemx=$sysmis.
if (missing(bladcap) and b2a eq 4)bladcap=0.
if (missing(bladcap) and any(i1a,0,1))bladcap=1. 
**if (any(i1a,2,3,4,5,8) and (b2a lt 2 and h2c lt 4) 
       and aa0h3a eq 0)bladcap=3 .
** if (any(i1a,2,3,4,5,8) and (b2a lt 2 and h2c lt 4) 
       and aa0h3a eq 1 and itemx gt 0)bladcap=3. 
if (any(i1a,2,3,4,5,8) and (b2a lt 2 and h2c lt 4) 
       and itemx gt 0)bladcap=3 .


if (missing(bladcap) and b2a lt 4)bladcap=2.
value labels bladcap (0)pr cog (1)no prob (2)prv dec (3)fac imp.
variable labels bladcap bladder cap July 2007 home care version.
**
** END BLADDER CAP    July 2007
**

compute bladT1 = i1a.
compute bladT2 = i1a_2.
recode bladT1 bladT2 (6 thru high=sysmis).
recode bladt1 (1 thru 5=0)(else=sysmis)into bladIMP.
if (bladIMP eq 0 and bladT2 lt bladT1)bladIMP=1.
recode bladT1 (0 thru 4=0)(else=sysmis)into bladDEC.
if (bladDEC eq 0 and bladT2 gt bladT1)bladDEC=1.

Compute chgCONT = $sysmis.
if (i1a gt 2 and not missing(bladt2))chgCONT=0.
if (chgCONT eq 0 and bladT2 lt 3)chgCONT=1.
var labels chgCONT from incontinent to continent.

Compute chgINCONT = $sysmis.
if (i1a lt 3  and not missing(i1a_2))chgINCONT=0.
if (chgINCONT eq 0 and i1a_2 gt 2)chgINCONT=1.
variable labels chgINCONT from continent to INcontinent.

**crosstabs tables= chgcont chgincont by cWHOLE
    /cells=count row col TOTAL




recode f2 (missing=sysmis)(1,2=1)(else=0)into f21/
    h2b h2d (1=1)(missing=sysmis) (else=0)into h2b1 h2d1 /
    h4a (1=1)(missing=sysmis)(else=0)into h4a1 /
    h4a (0,1=1)(missing=sysmis)(else=0)into h4a01 /
    j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1y j1z j1aa j1ab (1,2=1)(missing=sysmis)(else=0)into 
     j1a1 j1b1 j1c1 j1d1 j1e1 j1f1 j1g1 j1h1 j1i1 j1j1 j1k1 j1l1 j1m1 j1n1 j1o1 j1p1 j1q1 j1r1 j1s1 j1t1 j1u1 j1v1 j1w1 j1x1 j1y1 j1z1 j1aa1 j1ab1 /
     k4a (missing=sysmis)(2,3=1)(else=0)into k4a2/k4b (missing=sysmis)(3,4=1)(else=0)into k4b3 /
    b2a (1=1)(missing=sysmis)(else=0)into b2a1 /
   h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (missing=sysmis)(1=1)(else=0) into 
     h2a1 h2b1 h2c1 h2d1 h2e1 h2f1 h2g1 h2h1 h2i1 h2j1 / 
     h5 (missing=sysmis)(0,1=1)(else=0) into h501/
    h1da (missing=sysmis)(0=1)(else=0)into h1da0 /.


count bladIMPcap2023= b1a (0) b2a (0) f2 (1,2) h1aa h1ba h1ca h1da (0) h2j (0,1) 
     h7a (1) i2b (1) k2c (1) k8e (1) k9d (1) l1a (1).
if (b2a eq 4) bladimpcap2023=0.


recode bladIMPcap2023  (0 thru 2=0)(3 thru high=1)into bladIMP3/
    bladIMPcap2023  (0 thru 3=0)(4 thru high=1)into bladIMP4/
    bladIMPcap2023  (0 thru 4=0)(5 thru high=1)into bladIMP5.


count HCmiss = bb1 bb4 cc4 cc5 cc6 cc7   
     b1a b1b b2a b2b b3a
    c1 c2 c3  d1  
    e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e  
     f1b f2 f3a f3b
   g1ea  g1fa   g1ha g1ia  g2a g2b g2c g3a g3b
    h1aa h1ba h1ca h1da h1ea h1fa h1ga h1ab h1bb h1cb h1db h1eb h1fb h1gb h2a h2b h2c h2e h2f h2g h2h h2i h2j h3 h4a h4b h5 h6a h6b h7a h7b 
    i1a i2a i2b i3
    j1a j1b j1c  j1g j1h  j1j j1k j1l  j1n j1o j1s  j1u j1w j1x j1y j1z 
     k1a k1b k1c k1d k2a  k2c k2e  k3a k3b k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a k7c k8a k8b k8c k8e  
      k9a k9b k9d  
    l1a   l2d l2c l2d l3
    m1a m1b   
    n1 n2a n2b n3a n3b n3d n3e n4   n5c 
    o1a  o1e o1f o1g   
     p1aa p1ba p1ca p1da  p1fa p1ga p1ha 
    p2a p2e p2f p2g p2h p2i p2k p2l p2m p2o p2p  p2v p2w 
    p4a p4b p4c  p6 p7
      q4 (missing).

recode b2a (missing=sysmis) (2 thru 4=1)(else=0)into b2a24/
    c2 c3 (missing=sysmis)(2 thru high=1)(else=0)into c22 c32/
    h1aa h1ba h1ca (missing=sysmis)(3,8=1)(else=0)into h1aa38 h1ba38 h1ca38 / 
    h2b  h2d h2f h2j h2g h2i(missing=sysmis)(2 thru high=1)(else=0)into h2b2  h2d2 h2f2 h2j2 h2g2 h2i2 /
    h2d h2f h2j h2g h2i (4 thru high=1)(missing=sysmis)(else=0)into  h2d4 h2f4 h2j4 h2g4 h2i4 /
   h5 (missing=sysmis)(2=1)(else=0)into h52 / h6a (missing=sysmis)(3=3)(else=0)into h6a3/
    l3 (missing=sysmis)(1,2=1)(else=0)into l312/.

do if not missing(chgincont).
recode   b1a b2a24 b2b c22 c32  h1aa38 h1ba38 h1ca38 
    h2b2 h2d2 h2f2 h2j2 h2g2 h2i2 h2d4  h2f4 h2i h2g4 h2j4 h2i4 
    h52 h6a3 j1g1 j1h1 j1l1 j1w k3f k3g k9e l312 (missing=0).
end if .


recode  h1aa (missing=sysmis)(3=1)(else=0)into h1aa3 / h2d  h2c (missing=sysmis)(2 thru high=1)(else=0)into h2d2 h2c2/
    h5 (missing=sysmis)(1,2=1)(else=0)into h512/
    j1g j1h j1l (missing=sysmis)(1,2=1)(else=0) into j1g1 j1h1 j1l1 .
count mental= k3f k3g (1).
recode mental (1,2=1)/ i3 (missing=sysmis)(2 thru high=1)(else=0) into i32/ .

count newincDECcap = b1a (1) h1aa3   h5 (1,2) j1g j1h j1l (1,2)   h2c (2 thru high)  i3 (2 thru high) mental (1,2).

count modelMISS =  b1a  h1ca  h2d  h2j  h5  j1g j1h j1l (missing).
if (missing(i1a)) newincDECcap = $sysmis.


compute bladcap2023=$sysmis.
do if not missing(newincdeccap).
compute bladcap2023=4.
if (i1a eq 0 and any(newincDECcap,0))bladcap2023=0.
if (i1a eq 0 and any(newincDECcap,1,2,3))bladcap2023=1.
if (i1a eq 0 and any(newincDECcap,4,5))bladcap2023=2.
if (i1a eq 0 and newincDECcap gt 5)bladcap2023=3.
if (i1a eq 1 and any(newincDECcap,0,1,2))bladcap2023=0.
if (i1a eq 1 and any(newincDECcap,3,4,5,6))bladcap2023=1.
if (i1a eq 1 and newincDECcap gt 6 )bladcap2023=2.
if (i1a eq 2 and any(newincDECcap,0,1,2))bladcap2023=2.
if (i1a eq 2 and newincDECcap gt 2) bladcap2023=3.

if (i1a eq 3 and any(newincDECcap,0,1,2,3))bladcap2023=7.
if (i1a eq 3 and any(newincDECcap,4,5,6,7,8))bladcap2023=6.
if (i1a eq 4 and any(newincDECcap,0,1,2))bladcap2023=6.
if (i1a eq 4 and any (newincDECcap,3,4))bladcap2023=5.
if (i1a eq 4 and newincDECcap gt 4)bladcap2023=4.
if (i1a eq 5 and any(newincDECcap,0))bladcap2023=6.
if (i1a eq 5 and any(newincDECcap,0,1,2))bladcap2023=5.
if (i1a eq 5 and newincDECcap gt 2 )bladcap2023=4.
if (i1a eq 8) bladcap2023=8.
end if.
**if (not missing(i1a_2) and missing(bladCAP2023))bladcap2023=2

recode cps (0 thru 3=0)(4 thru high=1)into POORcog.



sort cases by batch country  facility resid_n2 a1d a1m a1y  .
save outfile="S:\projectdata2\0000 account shared\Erez datasets\incontinence_HC.sav"
 /keep=batch country  facility resid_n2 a1d a1m a1y  
  bladDEC  bladt1 bladT2   bladIMP chgINCONT chgCONT
bladIMPcap2023 
bladIMP3 bladIMP4 bladIMP5 
 Ig2f
Ig1aa
Ig1fa
Ic2a
Ii1c
Ii1d
Ii1g
Ij2h ij2i
Ih3
b1a b2a24 b2b c22 c32  h1aa38 h1ba38 h1ca38 
    h2b2 h2d2 h2f2 h2j2 h2g2 h2i2 h2d4  h2f4 h2i h2g4 h2j4 h2i4 
    h52 h6a3 j1g1 j1h1 j1l1 j1w k3f k3g k9e l312 h2c2 bladcap2023 newincDECcap.







frequencies variables=Ih3
b1a b2a24 b2b c22 c32  h1aa38 h1ba38 h1ca38 
    h2b2 h2d2 h2f2 h2j2 h2g2 h2i2 h2d4  h2f4 h2i h2g4 h2j4 h2i4 
    h52 h6a3 j1g1 j1h1 j1l1 j1w k3f k3g k9e l312 h2c2  bladcap2023 newincDECcap.
















