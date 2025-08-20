* Encoding: UTF-8.
get file="S:\projectdata2\0000 account shared\Erez datasets\EREZ_HC_sample.sav".  
compute mbmodel = 0.
add files file = *
/file='S:\projectdata2\0000 account shared\icare4old\HC_models_check.sav'
 /drop=bb2.
if missing(mbmodel) mbmodel = 1.
*frequencies variables = mbmodel.
   
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
recode p2a_2 p2b_2 p2c_2 p2d_2 p2e_2 p2f_2 p2g_2 p2h_2 p2i_2 p2j_2 p2k_2 p2l_2 p2m_2 p2n_2 p2o_2 p2p_2 p2q_2 p2r_2 p2s_2 p2t_2 p2u_2 p2v_2 p2w_2 p2x_2 p2y_2 p2z_2 (missing=0).
end if .



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


*compute outab=0.
*if (any(country,"BEL","GER","ICE","USA_CL","AUS","JPN","SWED","UK","USA_RI","USA_TX")) outAB=1.
*select if outab eq 0.



**
** JNMXX end of insert
**
*frequencies variables =j2a. 

**frequencies variables=derivation.

*crosstabs tables=kickout by country.


** THE CODE BELOW SHOULD HAVE BEEN IN YOUR PROGRAM – WHY WAS IT MISSING JOHN.

*COUNT allMISS = b2a 
           b1a b1b b3a b3b c1 c2 c3 d1 e1a e1b e1c e1d e1e e1f e1g e1h e1i 
           e3a e3b e3c e3d e3e f1b f2 f3a f3b g1ea g1eb  g1fa g1fb  g1ha g1hb g1ia g1ib   
           g2a g2c h1aa h1ba h1ca h1da h1ea h1fa h1ga  
           h1ab h1bb h1cb h1db h1eb h1fb h1gb 
           h2a h2b h2c h2e h2f h2g h2h h2i h2j    
           h3 h4a h5 h6a h6b h7a h7b i1a i2a i2b i3 
            j1a j1c  j1g j1h  j1j j1k j1l j1n j1o  j1s  j1u j1w j1x  j1y j1z 
            k1a k1b k1c k1d k2a k2c k2e k3a k3c k3d  k3e  k3f k3g k4a k4b k4e k5 k6a k7c 
            k8a k8b k8c k8e k9a l1a l1c l3 m1b n2a  n4 n2b n3a n3c n3e o1e o1f p4a p4b  k9e
            p5 p7 q3    (missing).



count h1aax = h1aa ig1aa (missing).
count h1bax = h1ba ig1ba (missing).
count h1cax = h1ca ig1ca (missing).

count h1abx = h1ab ig1ab (missing).
count h1bbx = h1bb ig1bb (missing).
count h1cbx = h1cb ig1cb (missing).

**crosstabs tables= country by h1aax h1bax h1cax h1abx h1bbx h1cbx
   /cells=count row col tot

**frequencies variables=  h1aa ig1aa h1aax  h1ba ig1ba h1bax 
  h1ca ig1ca h1cax h1ab ig1ab h1abx  h1bb ig1bb h1bbx h1cb ig1cb h1cbx


**frequencies variables= allmiss 
   /statistics
**means tables= allmiss by country
***frequencies variables=b2a 
           b1a b1b b3a b3b c1 c2 c3 d1 e1a e1b e1c e1d e1e e1f e1g e1h e1i 
           e3a e3b e3c e3d e3e f1b f2 f3a f3b g1ea g1eb  g1fa g1fb  g1ha g1hb g1ia g1ib   
           g2a g2c h1aa h1ba h1ca h1da h1ea h1fa h1ga  
           h1ab h1bb h1cb h1db h1eb h1fb h1gb 
           h2a h2b h2c h2e h2f h2g h2h h2i h2j    
           h3 h4a h5 h6a h6b h7a h7b i1a i2a i2b i3 
            j1a j1c  j1g j1h  j1j j1k j1l j1n j1o  j1s  j1u j1w j1x  j1y j1z 
            k1a k1b k1c k1d k2a k2c k2e k3a k3c k3d  k3e  k3f k3g k4a k4b k4e k5 k6a k7c 
            k8a k8b k8c k8e k9a l1a l1c l3 m1b n2a  n4 n2b n3a n3c n3e o1e o1f p4a p4b  k9e
            p5 p7 q3

**frequencies variables= ag


*compute cWHOLE=$sysmis.
*value labels cWHOLE (1)Europe (2)Canada (3)USA (4)Hong Komg (5)New Zealand .
*recode country ("ADH12","ADH6","FIN","ITA","NETH"=1)
   ("CANADA_AB","CANADA_BC","CANADA_MB","CANADA_NL","CANADA_ON","CANADA_YT"=2)
   ("USA_AR","USA_CT","USA_GA","USA_LA","USA_MA","USA_MD","USA_MI","USA_MO","USA_NJ","USA_NY"=3)
   ("CHI"=4)
   ("NEWZ"=5) into cWHOLE .

**service code

do repeat day1a=p1aa p1ba p1ca p1fa p1ga p1ha   /
   day1b=in3aa in3ba in3ca in3ea  in3fa in3ga  /
   hour1a =p1ab p1bb p1cb  p1fb p1gb p1hb / 
   min1a= p1ac p1bc p1cc p1fc p1gc p1hc  /
   min1b=in3ab in3bb in3cb in3eb in3fb in3gb  /.
recode day1a day1b (7 thru 31=7)(32 thru high=sysmis).
recode hour1a (168 thru 336=168)(169 thru high=sysmis).
if (MISSING(hour1a) and day1a eq 0)hour1a=0.
if (missing(min1a) and day1a eq 0)min1a=0.
compute min1a= min1a+(hour1a*60).
if (missing(min1b) and day1b eq 0)min1b=0.
recode min1a min1b (8300 thru high=sysmis).
end repeat.
do repeat day1a=p1aa_2 p1ba_2 p1ca_2 p1fa_2 p1ga_2 p1ha_2   /
   day1b=in3aa_2 in3ba_2 in3ca_2 in3ea_2  in3fa_2 in3ga_2  /
   hour1a =p1ab_2 p1bb_2 p1cb_2  p1fb_2 p1gb_2 p1hb_2 / 
   min1a= p1ac_2 p1bc_2 p1cc_2 p1fc_2 p1gc_2 p1hc_2  /
   min1b=in3ab_2 in3bb_2 in3cb_2 in3eb_2 in3fb_2 in3gb_2  /.
recode day1a day1b (7 thru 31=7)(32 thru high=sysmis).
recode hour1a (168 thru 336=168)(169 thru high=sysmis).
if (MISSING(hour1a) and day1a eq 0)hour1a=0.
if (missing(min1a) and day1a eq 0)min1a=0.
compute min1a= min1a+(hour1a*60).
if (missing(min1b) and day1b eq 0)min1b=0.
recode min1a min1b (8300 thru high=sysmis).
end repeat.



recode      in2e in2j in2i in2a in2b in2d in2f in2h (0=0)(3=1)(1,2=1)(missing=sysmis) into in2ex in2jx in2ix in2ax in2bx in2dx in2fx in2hx.
recode in5c in3ba (0=0)(1 thru high=1)(missing=sysmis)into in5cx in3bax.
do repeat x1=p2a p2b p2e p2f p2g p2j p2l p2m p2t p2v /
  x2= in2ex in2jx in2ix in2ax in2bx in2dx in2fx in2hx in5cx in3bax/.
recode x1 x2 (9 thru high=sysmis).
if (missing(x1))x1=x2.
end repeat.
recode      in2e_2 in2j_2 in2i_2 in2a_2 in2b_2 in2d_2 in2f_2 in2h_2
    (0=0)(3=1)(1,2=1)(missing=sysmis) into in2ex_2 in2jx_2 in2ix_2 in2ax_2 in2bx_2 in2dx_2 in2fx_2 in2hx_2.
recode in5c_2 in3ba_2 (0=0)(1 thru high=1)(missing=sysmis)into in5cx_2 in3bax_2.
do repeat x1=p2a_2 p2b_2 p2e_2 p2f_2 p2g_2 p2j_2 p2l_2 p2m_2 p2t_2 p2v_2 /
  x2= in2ex_2 in2jx_2 in2ix_2 in2ax_2 in2bx_2 in2dx_2 in2fx_2 in2hx_2 in5cx_2 in3bax_2/.
if (missing(x1))x1=x2.
end repeat.

do repeat x1= p4a p4b p4a_2 p4b_2/
  x2= in5a in5b in5a_2 in5b_2/.
recode x1 x2 (100 thru high=sysmsis).
if (missing(x1)) x1=x2.
end repeat.

** end service code  icode to hc


count anypsy= ii1n ii1w ii1o ii1p (0,1,2).
recode anypsy (1 thru high=1).
do if anypsy eq 0.
if (missing(ii1n) and missing(ii1w) and missing(ii1o) and missing(ii1p))anypsy=$sysmis.
end if.
count anypsy_2= ii1n_2 ii1w_2 ii1o_2 ii1p_2 (0,1,2).
recode anypsy_2 (1 thru high=1).
do if anypsy_2 eq 0.
if (missing(ii1n) and missing(ii1w) and missing(ii1o) and missing(ii1p))anypsy_2=$sysmis.
end if.        
count delir = ic3a ic3b ic3c (2) ic4 (1).
recode delir (1 thru high=1).
do if delir eq 0.
if (missing(ic3a) and missing(ic3b) and missing(ic3c) and missing (ic4))delir=$sysmis.
end if.
count delir_2 = ic3a_2 ic3b_2 ic3c_2 (2) ic4_2 (1).
recode delir_2 (1 thru high=1).
do if delir_2 eq 0.
if (missing(ic3a_2) and missing(ic3b_2) and missing(ic3c_2) and missing (ic4_2))delir_2=$sysmis.
end if.
recode ic5 ic5_2  (2=1)(missing=sysmis)(else=0)into COGdec COGdec_2.
recode id3a id3a_2  (0=0)(1=1)(2,3=2)(4=3)into hear hear_2.
recode ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1i ie1j (0=0)(missing=sysmis)(1,2=1)(3=2)into
            ie1ax ie1bx ie1cx ie1dx ie1ex ie1fx ie1gx ie1ix ie1jx.
recode ie1a_2 ie1b_2 ie1c_2 ie1d_2 ie1e_2 ie1f_2 ie1g_2 ie1i_2 ie1j_2 (0=0)(missing=sysmis)(1,2=1)(3=2)into
            ie1ax_2 ie1bx_2 ie1cx_2 ie1dx_2 ie1ex_2 ie1fx_2 ie1gx_2 ie1ix_2 ie1jx_2.
recode ie3a ie3b ie3c ie3d ie3f ie3e (0=0)(missing=sysmis)(1,2=1)(3=2) into 
           ie3ax ie3bx ie3cx ie3dx ie3fx ie3ex.
if (ie3ex gt ie3dx)ie3dx=ie3ex.
recode ie3a_2 ie3b_2 ie3c_2 ie3d_2 ie3f_2 ie3e_2 (0=0)(missing=sysmis)(1,2=1)(3=2) into 
           ie3ax_2 ie3bx_2 ie3cx_2 ie3dx_2 ie3fx_2 ie3ex_2.
if (ie3ex_2 gt ie3dx_2)ie3dx_2=ie3ex_2.
recode if1e if1e_2 (0,1,2,3,8=0)(4=1)(else=sysmis)into if1ex if1ex_2.
recode ip1b1 ip1b2 ip1b1_2 ip1b2_2 (1,2=0)(0=1)(8=2)into ip1b1x ip1b2x  ip1b1X_2 ip1b2X_2.
recode ip1a1 ip1a2 ip1a1_2 ip1a2_2 (1=0)(2=1)(3,4,5,6=2)(7,8=3)(8=8)into  ip1a1x ip1a2x ip1a1x_2 ip1a2x_2.
do repeat
    x1= g1ea g1ea_2 g1eb g1eb_2  g1ha g1hb g1ia g1ib  /
    x2= g1fa g1fa_2  g1fb g1fb_2  g1ha_2 g1hb_2 g1ia_2 g1ib_2 /.
do if x1 eq 2.
recode x2 (missing=8).
end if.
end repeat.
recode ig1aa ig1ba ig1ca ig1da ig1ea ig1ga ig1ha ig1aa_2 ig1ba_2 ig1ca_2 ig1da_2 ig1ea_2 ig1ga_2 ig1ha_2
     (0,1=0)(2,3=1)(4,5=2)(6=3)(8=8)into  ig1aax ig1bax ig1cax ig1dax ig1eax ig1gax ig1hax 
    ig1aax_2 ig1bax_2 ig1cax_2 ig1dax_2 ig1eax_2 ig1gax_2 ig1hax_2.
recode ig1ab ig1bb ig1cb ig1db ig1eb ig1gb ig1hb ig1ab_2 ig1bb_2 ig1cb_2 ig1db_2 ig1eb_2 ig1gb_2 ig1hb_2
     (0,1=0)(2,3=1)(4,5=2)(6=3)(8=8)into  ig1aax ig1bax ig1cax ig1dax ig1eax ig1gax ig1hax 
    ig1abx_2 ig1bbx_2 ig1cbx_2 ig1dbx_2 ig1ebx_2 ig1gbx_2 ig1hbx_2.
recode ig8a ig8a_2 (0,1,3=0)(2=2)(else=sysmis) into ig8ax i8gax_2. 
recode ig3 ig3_2 (0=0)(1=2)(2=4)(3=8)(else=sysmis)into ig3x ig3x_2. 
recode ig1fb ig1fb_2 (0,1,2=0)(3,4,5=1)(6,8=2)into ig1fx ig1fx_2. 
recode ig6b ig6b_2 (0=3)(1=2)(2=1)(3=0)(else=sysmis) into ig6bx ig6bx_2. 
recode ig6a ig6a_2 (0,1,2=0)(3,4=1)(else=sysmis) into ig6ax ig6ax_2. 
recode ih2 ih2_2 (2=2)(missing=sysmis)(else=0)into ih2x ih2_2.
recode ii1m ii1m_2 ii1j ii1k  ii1c ii1d  ii1e ii1f  ii1h ii1a ii1b anypsy ii1g ii1r   ii1s ii1t 
       ii1j_2 ii1k_2  ii1c_2 ii1d_2  ii1e_2 ii1f_2  ii1h_2 ii1a_2 ii1b_2 anypsy_2 ii1g_2 ii1r_2   ii1s_2 ii1t_2 
     (0=0)(1=1)(2,3=2)(else=sysmis) into ii1mx ii1mx_2 
      ii1jx ii1kx  ii1cx ii1dx  ii1ex ii1fx  ii1hx ii1ax ii1bx anypsyx ii1gx ii1rx   ii1sx ii1tx 
       ii1jx_2 ii1kx_2  ii1cx_2 ii1dx_2  ii1ex_2 ii1fx_2  ii1hx_2 ii1ax_2 ii1bx_2 anypsyx_2 ii1gx_2 ii1rx_2   ii1sx_2 ii1tx_2. 
recode ij2l ij2l_2 ij2q ij2q_2 ij2n ij2n_2  ij2e ij2e_2 ij2c ij2c_2 ij2s ij2s_2 ij2j ij2j_2 ij2h ij2h_2 ij2i ij2i_2 
          ij2j ij2h_2 ij2d ij2d_2 
           (0,1=0)(2 thru 4=1)(else=sysmis) into 
           ij2lx ij2lx_2 ij2qx ij2qx_2 ij2nx  ij2nx_2  ij2ex ij2ex_2 ij2cx ij2cx_2 ij2sx ij2sx_2 ij2jx ij2jx_2 ij2hx ij2hx_2 ij2ix ij2ix_2 
          ij2jx ij2hx_2 ij2dx ij2dx_2. 
recode ij3 ij3_2  (0=0)(1 thru 3=1)(else=sysmis) into  ij3x ij3x_2.
recode ij5e ij5e_2 (0,1,2=0)(3=1)(4,5=2)(else=sysmis) into ij5ex ij5ex_2. 
recode ij1 ij1_2 (0=0)(1,2=1)(3=2)into ij1x ij1x_2.
if (not missing(ij12) and ij1x eq 0 and ij12 gt 0)ij1x=1.
if (not missing(ij12_2) and ij1x_2 eq 0 and ij12_2 gt 0)ij1x_2=1.
recode ij8a ij8a_2 (0=0)(1,2=1)(else=sysmis)into ij8ax ij8ax_2. 
recode ij7 ij7_2 (0,1,2,8=0)(3=1)(else=sysmis)into ij7x ij7x_2.
recode if1f if1f_2 (0,1,8=0)(2,3,4=1)(else=sysmis) into if1fx if1fx_2.
recode ik3 ik3_2 (0=0)(1=1)(2,3,4=2)(5=3)(6,7,8,9=4)(else=sysmis)into ik3x ik3x_2. 
recode il7 il7_2  (0=0)(1,2,3,4=1)(else=sysmis) into il7x il7x_2.
recode im3 im3_2 (0=0)(1=1)(2=2)(8=3)(else=sysmis)into im3x im3x_2. 
 
*frequencies variables=im3x.

do repeat
   time1=      b2a 
           b1a b1b b3a b3b c1 c2 c3 d1 e1a e1b e1c e1d e1e e1f e1g e1h e1i 
           e3a e3b e3c e3d e3e f1b f2 f3a f3b g1ea g1eb  g1fa g1fb  g1ha g1hb g1ia g1ib   
           g2a g2c h1aa h1ba h1ca h1da h1ea h1fa h1ga  
           h1ab h1bb h1cb h1db h1eb h1fb h1gb 
           h2a h2b h2c h2e h2f h2g h2h h2i h2j    
           h3 h4a h5 h6a h6b h7a h7b i1a i2a i2b i3 
            j1a j1c  j1g j1h  j1j j1k j1l j1n j1o  j1s  j1u j1w j1x  j1y j1z 
            k1a k1b k1c k1d k2a k2c k2e k3a k3c k3d  k3e  k3f k3g k4a k4b k4e k5 k6a k7c 
            k8a k8b k8c k8e k9a l1a l1c l3 m1b n2a  n4 n2b n3a n3c n3e o1e o1f p4a p4b  k9e
            p5 p7 q3      /
   time2 = ic1  
          ic2a ic2b delir COGdec hear id1 id2 id4a ie1ax ie1bx ie1cx ie1dx ie1ex ie1fx ie1gx ie1ix ie1jx
           ie3ax ie3bx ie3cx ie3dx ie3fx ie3ex if1ex if2 if3 if1d ip1b1x ip1b2x  ip1a1x ip1a2x ip1c1 ip1c2 ip1d1 ip1d2 
          ip2a  ip2b  ig1aax ig1bax ig1cax ig1dax ig1eax ig1gax ig1hax
           ig1aax ig1bax ig1cax ig1dax ig1eax ig1gax ig1hax 
          ig2i ig2h ig2f ig2c ig2d ig2j ig2h ig2b ig2a 
          ig8ax ig3x ig1fx ig6bx ig6ax ig7a ig7b ih1 ih4 ih2x ih3 
            ii1jx ii1kx  ii1cx ii1dx  ii1ex ii1fx  ii1hx ii1ax ii1bx anypsyx ii1gx ii1rx   ii1sx ii1tx ii1mx
           in1d in1a in1h in1c ij2lx ij2qx ij2nx ij2cx ij2sx ij3x ij2hx ij2ix ij5a ij5b ij5ex ij1x ij2dx ij8ax 
           ij7x ij6a ij6b ij6c if1fx ik2a ik2b ik3x ik4d il1  il2 il3 il4 il5 il7x iq1c iq1d in5a in5b in4 
           ir1 iq4 im3x /.
recode time1 time2 (9 thru high=sysmis).

if (missing(time1) and time2 lt 9)time1=time2. 
end repeat.

recode b1a (1 thru high=1).

*COUNT allMISS = b2a 
           b1a b1b b3a b3b c1 c2 c3 d1 e1a e1b e1c e1d e1e e1f e1g e1h e1i 
           e3a e3b e3c e3d e3e f1b f2 f3a f3b g1ea g1eb  g1fa g1fb  g1ha g1hb g1ia g1ib   
           g2a g2c h1aa h1ba h1ca h1da h1ea h1fa h1ga  
           h1ab h1bb h1cb h1db h1eb h1fb h1gb 
           h2a h2b h2c h2e h2f h2g h2h h2i h2j    
           h3 h4a h5 h6a h6b h7a h7b i1a i2a i2b i3 
            j1a j1c  j1g j1h  j1j j1k j1l j1n j1o  j1s  j1u j1w j1x  j1y j1z 
            k1a k1b k1c k1d k2a k2c k2e k3a k3c k3d  k3e  k3f k3g k4a k4b k4e k5 k6a k7c 
            k8a k8b k8c k8e k9a l1a l1c l3 m1b n2a  n4 n2b n3a n3c n3e o1e o1f p4a p4b  k9e
            p5 p7 q3    (missing).


**frequencies variables= allmiss 
   /statistics
**means tables= allmiss by country state 


**   EXCLUDE CASES THERE ARE FROM COLLAGE OR SITES WITH SMALL N'S AND MANY MISSING OR 
     MISSING 150 OR MORE ITEMS IN ABOBE     john morris 2022
**
compute kickOUT=0
if (sourcen eq 17.01 or collage eq 1 or allmiss gt 149 or country eq "ICE" or country eq "NETH" 
    or country eq "USA_RI" or country eq "USA_TX" or country eq "AUS")kickout=1

**frequencies variables=kickout.


*select if kickout eq 0.


**frequencies variables=kickout.
**
**   END OF EXCLUDE CASE CODE**
**

**
**frequencies variables= country sourcen source
   
**frequencies variables= state collage
**frequencies variables = h2c_2


recode q1 (0 thru 7=0)(8 thru high=1)into med8.
recode q1 (0 thru 8=0)(9 thru high=1)into med9.
recode q1 (0 thru 4=0)(5 thru high=1)into med5.

recode h2a h2b h2c  h2d h2e h2f h2g h2h  h2i h2j 
  h2a_2 h2b_2 h2c_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
  ig2a ig2b ig2c ig2d ig2e ig2f ig2g ig2h ig2i ig2j  
   ig2a_2 ig2b_2 ig2c_2 ig2d_2 ig2e_2 ig2f_2 ig2g_2 ig2h_2 ig2i_2 ig2j_2 (8=4)(9 thru high=sysmis). 

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

**frequencies variables = h2a h2b h2c h2c_2 h2cxx h2d h2e h2f h2g h2h  h2i h2j 
    h2a_2 h2b_2 h2c_2 h2cxx_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
    /statistics
**correlation variables = h2a h2b h2c h2cxx h2d h2e h2f h2g h2h  h2i h2j 
     

do repeat x1= h2a h2b h2c   h2e h2f h2g h2h  h2i h2j
  h2a_2 h2b_2 h2c_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 /
   y1= ig2i ig2g ig2f  ig2c ig2d ig2j ig2h ig2b ig2a                 
    ig2i_2 ig2g_2 ig2f_2  ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2/.
if (missing(x1))x1=y1.
if (missing(y1))y1=x1.
end repeat.   
**
**frequencies variables=h2a h2b h2c   h2e h2f h2g h2h  h2i h2j
  h2a_2 h2b_2 h2c_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
    ig2i ig2g ig2f  ig2c ig2d ig2j ig2h ig2b ig2a                 
    ig2i_2 ig2g_2 ig2f_2  ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2.
 
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
variable labels tothrs hrs total care seven days. 

compute anypsy= ii1n.
if (ii1w gt 0 or ii1o gt 0 or ii1p gt 0)anypsy=1.

do repeat mdshc = j1a j1b j1c 
        j1g j1h  j1j j1k j1l  j1n 
        j1o j1s  j1u 
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


if (p2g gt 0) j1aa=1.
variable labels dk3b dk3b no bowel movmnt 3 days no v y.
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

do if missing(n3d). 
recode in2k (0=0)(missing=sysmis)(else=1)into n3d.
end if.

recode ij2m ij2f ij2a ij2b ij2g ij2o ij2p ij4  (0 thru 1=0)(2 thru high=1)(missing=sysmis)into 
  ij2mD ij2fD ij2aD ij2bD ij2gD ij2oD ij2pD ij4D.
recode k3e k4d k4e k9e ij2j ij2r (0=0)(1 thru high=1)(missing=sysmis)into 
  k3eD k4dD k4eD k9eD ij2jD ij2rD.  



variable labels  ij2mD ij2mD acid reflux no vs yes /
   ij2fD ij2fD airway secretion no vs yes /
  k3eD k3eD sob no vs yes /
  k4dD k4dD character pain no vs yes /
 k4eD k4eD meds control pain no vs yes /
   k9eD k9eD restrained  no vs yes /
   ij2aD ij2aD move to stand  no vs yes /
   ij2bD ij2bD turn  no vs yes /
   ij2gD ij2gD abnormal thoughts  no vs yes /
   ij2jD ij1jD Aphasia  no vs yes /
  ij2oD ij2oD difficulty sleeping  no vs yes /
   ij2pD ij2pD too much  sleep  no vs yes /
   ij2rD ij2rD bleeding  no vs yes /
   ij4D ij4D fatigue  no vs yes /.

recode k1b (1 thru high=1).


do if missing(q4).
recode im3 (missing=sysmis)(0=0)(1=1)(2=2)(8=3)into q4.
end if.

recode k5 k5_2 (0=0)(0 thru 1=1)(1 thru high=2).
recode ij1 ij1_2 (0=0)(0,1,2=1)(2 thru 3=2).
compute fall_1=k5.
if (missing(fall_1))fall_1=ij1.
if (missing(fall_1))fall_1=ij12.
compute fall_2=k5_2.
if (missing(fall_2))fall_2=ij1_2.
if (missing(fall_2))fall_2=ij12.

**frequencies variables= fall_1 ij1 ij12 k5 k5_2

if (age lt 1) age=$sysmis.
if (age gt 111)age=$sysmis.
recode age (low thru 64=1)(65 thru 74=2)(75 thru 79=3)(80 thru 84=4)(85 thru 89=5)(90 thru 94=6)(95 thru high=7)into agecats.
**.
compute gender=bb1.
if (missing(gender)) gender=ia2.
recode gender (missing=1)(else=0) into gendermiss.


compute adlDEC= h3.
recode ig8a (missing=sysmis)(2=1)(else=0)into xxdown.
if (missing(adlDEC))adldec=xxdown.  
recode adlDEC (missing=1)(else=0) into adldecmiss. 

compute fallyes= k5.
recode ij1 (0=0)(1 thru high=1)into xxfall.
if (missing(fallyes))fallyes=xxfall.
recode fallyes (missing=1)(else=0) into fallyesmiss.

if (missing(g2a))g2a=ip2a.

recode p4a p4a_2 p4b p4b_2 in5a in5a_2 in5b in5b_2 (160 thru high=sysmis).
if (missing(p4a))p4a=in5a.
if (missing(p4a_2))p4a_2=in5a_2.
if (missing(p4b))p4b=in5b.
if (missing(p4a_2))p4b_2=in5b_2.



**.
compute hosed=0.
if (missing(p4a) and missing(p4b) and missing(cc4))hosed=$sysmis.
do if hosed eq 0.
compute xvisit=p4a+p4b.
if (missing(xvisit) and not missing(p4a))xvisit=p4a.
if (missing(xvisit) and not missing(p4b))xvisit=p4b.
if (xvisit eq 0 and cc4 gt 0)xvisit=1.
recode xvisit (0=0)(1=1)(2=2)(3=3)(4 thru high=4)into hosed.
end if.

recode  bb1  bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c  h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z  p4c p5 p6 p7
    (10 thru high=sysmis).
recode  g3a g3b age (999 thru high=sysmis).
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j H2a_2 h2b_2 h2c_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 (9 thru high=sysmis).
**frequencies variables =   bb1 age bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c g3a g3b h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4a p4b p4c p5 p6 p7



*count commonMISS = bb1 age bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c g3a g3b h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4c p5 p6 p7 (missing).

recode ih2 (missing=sysmis)(2=1)(else=0)into cathFILL.
if (missing(i2b))i2b=cathFILL.
recode k5 (0=0)(1 thru high=1)(missing=sysmis)into fellone.
recode ij1 (missing=sysmis)(0=0)(1 thru high=1)into xxFILL.
if (missing(fellONE))fellONE= xxfill.
recode ij12 (0=0)(1=1)(else=sysmis) into xxfill.
if (missing(fellONE))fellONE=xxfill.

recode k5 (0,1=0)(2 thru high=1)(missing=sysmis)into felltwo.
recode ij1 (missing=sysmis)(0,1,2=0)(3 thru high=1) into xxFILL.
if (missing(felltwo))felltwo= xxfill.
recode ij12 (0,1=0)(else=sysmis)into xxfill.
if (missing(felltwo))felltwo=xxfill.

recode ij2h (missing=sysmis)(0=0)(1 thru high=1)into xxFILL.
if (missing(k3f))k3f=xxfill.


** fill in missing with icodes
do repeat
    x1= bb1 cc8 p7 p5 k9e /
    fill=ia2 ib5a iq4 ir1 in4  /
if (missing(x1))x1=fill
end repeat

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
recode ik3 (missing=sysmis)(5,6=1)(else=0) into fill.
if (missing(l2d))l2d=fill.
recode ik3 (missing=sysmis)(0,1=0)(2=1)(3,4=2)(5=3)(6 thru high=4) into fill.
if (missing(l3))l3=fill.
count skin_a=il1 il3 il4 il5 il6 (1 thru high).
recode skin_a (1 thru high=1).
if (skin_a eq 0 and missing(il1) and missing(il3) and missing(il4) and missing(il5) and missing(il6))skin_a=$sysmis.
if (missing(n1))n1=skin_a.
recode il4 (missing=sysmis)(0=0)(1 thru high=1) into fill.
if (missing(n3b))n3b=fill.
recode il7 (0=0)(1 thru high=1) into fill.
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
recode in2i (0=0)(2,3=1)(1=3) into fill.
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

** CREATE ADL HIERARCHY 
**
**  locomotion substituted for walking
     eating substituted for bed mobility
     toilet use substiruted for transfer.
do repeat  ig2b  = ig2b ig2b_2/
           ig2g  = ig2g ig2g_2/
           ig2e  = ig2f ig2f_2/
           ig2i  = ig2j ig2j_2/
           ze1g  = ze1g xe1g/
           ze1f  = ze1f xe1f/
           ze1c  = ze1c xe1c/
           ze1e  = ze1e xe1e/
           early = early pearly/ 
           mid   = mid pmid/
           late  = late plate/
           adlh  = adlhfill adlhfill_2 /
            xx   = xx zz/ 
         aa= aa bb/
         ig2bfill= h2i h2i_2/ 
         ig2gfill= h2b h2b_2/
         ig2efill= h2c h2c_2 /
         ig2ifill =h2g h2g_2/
         ig2eTOIL= h2h h2h_2/
         h2htoil=ig2h ig2h_2/.
if (missing(ig2b))ig2b=ig2bfill.
if (missing(ig2g))ig2g=ig2gfill.
if (missing(ig2e))ig2e=ig2efill.
if (missing(ig2i))ig2i=ig2ifill.     
if (missing(ig2g))ig2g=ig2eTOIL.
if (missing(ig2g))ig2g=h2htoil.
if (missing(ig2bfill))ig2bfill=ig2b.
if (missing(ig2gfill))ig2gfill= ig2g.
if (missing(ig2efill))ig2efill=ig2e.
if (missing(ig2ifill))ig2ifill=ig2i.  
recode ig2b ig2g ig2e ig2i 
     (0,1=0)(2=1)(3=2)(4,5=3)(6,8=4) 
     (else=sysmis) into ze1g ze1f ze1c ze1e .
compute early = ze1g .
compute mid = ze1c .
compute late = ze1e . 
compute xx = early+mid+late+ze1f.
compute aa=xx.
** new patch dec 2011 JNM
     This excludes strange cases where folks seems not to walk but are good in everything else.
do if xx lt 9. 
Recode mid late (4=0).
end if. 
** new patch dec 2011 JNM.
compute xx = early+mid+late+ze1f.
compute adlh=$sysmis.
if (xx < 16 & (mid = 4 or  late = 4)) adlh = 5 .
Do if missing(adlh) .
if (xx < 16 & (mid = 3 | late = 3)) adlh = 4 .
End if.
if (late < 3 & mid<3 & (early>2 |ze1f>2)) adlh = 3.
if ((late<3 & mid<3 & early<3 & ze1f<3) & (late = 2 |mid=2 |early=2 |ze1f=2)) adlh = 2 .
if (late < 2 & mid<2 & early<2 & ze1f<2) adlh = 1 .
if (xx=0 & ze1f=0 & early=0) adlh = 0 .
if xx=16 adlh = 6.
End repeat .

variable labels 
     adlhfill '(adlh) adl hierarchy 0-6 baseline revised dec 2011'/
     adlhfill_2  '(adlh) follow-up adl hierarchy 0-6'.
value labels adlhfill adlhfill_2
 0 '(0) all zero' 
 1 '(1) supervision' 
 2 '(2) limited'
 3 '(3) early 3-4' 
 4 '(4) mid late 3'
 5 '(5) mid late 4' 
 6 '(6) all four' /.

**frequencies variables= aa bb  adlh adlh2 adlhfill adlhfill_2 h2c ig2e h2g ig2i h2h ig2g h2i ig2b

**correlation  variables adlh adlh2 adlhfill adlhfill_2

if (missing(adlh))adlh=adlhfill.
if (missing(adlh2))adlh2 = adlhfill_2.


**frequencies variables adlh adlh2 adlhfill adlhfill_2
**correlation  variables adlh adlh2 adlhfill adlhfill_2

compute adlCHG= adlh2-adlh.
recode adlchg (low thru -1=1)(0 thru high=0)into ADLimp.
recode adlchg (low thru 0=0)(1 thru high=1)into adlDEC.
if (adlh eq 0)adlimp=$sysmis.
if (adlh eq 6)adldec=$sysmis.

**frequencies variables= adlIMP adlDEC




**  check for missing vars by state coutry province groups
**frequencies variables= commonMISS
 bb1 age bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c g3a g3b h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 fellone k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4a p4b p4c p5 p6 p7 

do repeat
   mdshc= h1ab h1bb h1cb h1db h1eb h1fb h1gb  h1ab_2 h1bb_2 h1cb_2 h1db_2 h1eb_2 h1fb_2 h1gb_2   h1ab_3 h1bb_3 h1cb_3 h1db_3 h1eb_3 h1fb_3 h1gb_2  /
   icode= ig1ab ig1bb ig1cb ig1db ig1eb ig1gb ig1hb  ig1ab_2 ig1bb_2 ig1cb_2 ig1db_2 ig1eb_2 ig1gb_2 ig1hb_2  ig1ab_3 ig1bb_3 ig1cb_3 ig1db_3 ig1eb_3 ig1gb_3 ig1hb_3/.
do if missing(mdshc).
recode icode (0,1,2=0)(3,4,8=1)(5,6=2)into mdshc.
end if.
end repeat.
**  Mich amd maryland each missing about 90000 at baseline  why?  oct 2021

do repeat
   mdshc= h2a h2b h2c  h2e h2f h2g h2h  h2i h2j  h2a_2 h2b_2 h2c_2  h2e_2 h2f_2 h2g_2 h2h_2  h2i_2 h2j_2
        h2a_3 h2b_3 h2c_3  h2e_3 h2f_3 h2g_3 h2h_3  h2i_3 h2j_3 /
    icode = ig2i ig2g ig2f ig2c ig2d ig2j ig2h ig2b ig2a ig2i_2 ig2g_2 ig2f_2 ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2 
        ig2i_3 ig2g_3 ig2f_3 ig2c_3 ig2d_3 ig2j_3 ig2h_3 ig2b_3 ig2a_3 /.
if (missing(mdshc))mdshc=icode.
end repeat.


do repeat locorig = h2c h2c_2 h2d h2d_2/
    locNEW= locI locI_2 locO locO_2/
    gait= k6a k6a_2 k6a k6a_2/
    mode= h4a h4a_2 h4a h4a_2.
compute locnew=locorig.
recode locnew (8=4).
compute locnew=locnew+1.
do if (locnew eq 1).
if (gait eq 0 and mode lt 2)locnew =0.
end if.
end repeat.

variable labels   locI new locomotion inside t1/
    locI_2 new locomotion inside t2/
    locO new locomotion outside t1/
    locO_2 new locomotion outside t2/.
value labels   locI locI_2 locO locO_2
    (0)ind and gait ind and no walkr or wheelchair
    (1)inp othr er (2) set up help (3) supervision (4)limit ass
    (5)exten ass (6) max assist (7)tot dep.

count ambxx= k6a (0) h4a(0,1).
if (missing(K6a) and missing(h4a))ambxx=$sysmis.
 
compute walkIMp = locI_2.
recode walkIMP (low thru high=0).
if (locI_2 lt locI) walkIMP=1.
if (locI eq 0) walkimp=$sysmis.
variable labels walkIMP  improvement in walking performance on new measure.



compute walkDEc = locI_2.
recode walkDEC (low thru high=0).
if (locI lt locI_2) walkDEC=1.
if (locI eq 7) walkDEC=$sysmis.
variable labels walkDEC  decline in walking performance on new measu.

**frequencies variables= walkimp walkdec
  crosstabs tables= walkimp walkdec by loci
   /cells=count row col tot


**frequencies variables= walkimp adlimp walkdec adldec

**crosstabs tables=  walkimp by adlimp 
    / cells=count row col TOT  
     /statistics= chisqur risk
**crosstabs tables= walkdec by adldec
    / cells=count row col TOT  
     /statistics= chisqur risk

count iadl2s_2= h1ab_2 h1bb_2 (2).
if (missing(h1ab_2) and missing(h1bb_2))iadl2s_2=$sysmis.

count iadl2s= h1ab h1bb (2).
if (missing(h1AB) and missing(h1bb))iadl2s=$sysmis.
  

recode iadl2s_2 (0,1,2,3=0)(4=0)into iadlIMP.
if (iadl2s_2 lt iadl2s ) iadlimp=1.
if (iadl2s eq 0)iadlimp=$sysmis.  
var labels iadlimp improvement in capacity iadl meal prep and housework.

compute iadlalt= h1ab + h1bb.
compute iadlalt_2= h1ab_2 + h1bb_2.
compute iadlaltimp= iadlalt_2 - iadlalt.
if (iadlalt eq 0)iadlaltimp=$sysmis.
recode iadlaltimp (low thru -1=1)(missing=sysmis)(else=0).

**
** rEPLACE MISSING adl CODE VALUES
recode h2a h2b h2c  h2e h2f h2g h2h  h2i h2j (0=0)(1=1)(2=2)(3=3)(4,8=4)(5=5)(6=6) into
    h2a_a h2b_a h2c_a  h2e_a h2f_a h2g_a h2h_a  h2i_a h2j_a
do repeat
   item1=h2a_a h2b_a h2b_a h2b_a h2b_a h2b_a h2e_a h2b_a /
   item2=h2c_a  h2f_a h2f_a h2e_a h2e_a h2e_a h2f_a h2g_a / 
   item3= h2f_a   h2i_a h2i_a h2i_a h2i_a  h2f_a h2i_a h2c_a  /
   miss1= tran_1  loco_1 upper_1 lower_1 eat_1 hyg_1 bath_1 bed_1 /
   fill= tran_a  loco_a upper_a lower_a eat_a hyg_a bath_a bed_a/
count miss1= item1 item2 item3 (missing)
compute fill=$sysmis
do if (miss1) lt 3
. compute fill=sum (item1,item2,item3)
. compute fill=rnd(fill/(3-miss1))
end if
end repeat

if (missing(h2b_a))h2b_a=tran_a.
if (missing(h2c_a))h2c_a=loco_a.
if (missing(h2e_a))h2e_a=upper_a.
if (missing(h2f_a))h2f_a=lower_a.
if (missing(h2g_a))h2g_a=eat_a. 
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


** rEPLACE MISSING adl CODE VALUES
recode h2a_2 h2b_2 h2c_2  h2e_2 h2f_2 h2g_2 h2h_2  h2i_2 h2j_2 (0=0)(1=1)(2=2)(3=3)(4,8=4)(5=5)(6=6) into
    h2a_b h2b_b h2c_b  h2e_b h2f_b h2g_b h2h_b  h2i_b h2j_b
do repeat
   item1=h2a_b h2b_b h2b_b h2b_b h2b_b h2b_b h2e_b h2b_b /
   item2=h2c_b  h2f_b h2f_b h2e_b h2e_b h2e_b h2f_b h2g_b / 
   item3= h2f_b   h2i_b h2i_b h2i_b h2i_b  h2f_b h2i_b h2c_b  /
   miss1= tran_1  loco_1 upper_1 lower_1 eat_1 hyg_1 bath_1 bed_1 /
   fill= tran_b  loco_b upper_b lower_b eat_b hyg_b bath_b bed_b/
count miss1= item1 item2 item3 (missing)
compute fill=$sysmis
do if (miss1) lt 3
. compute fill=sum (item1,item2,item3)
. compute fill=rnd(fill/(3-miss1))
end if
end repeat

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
**end replace missing adl numbers for followup 1 or time 2
**

recode h2c_a h2c_b (0,1=0)(2 thru 5=1)(6 thru high=2)into loc_1 loc_2.
compute LOC_d=loc_2-loc_1.
recode loc_d (low thru 0=0)(1 thru high=1).
if (loc_1 eq 2)loc_d=$sysmis.
variable labels loc_d locomotion decline.
value labels loc_d.
**frequencies variables=loc_d.


**recode h2a_a h2c_a h2j_a h2a_b h2c_b h2j_b  (0,1=0)(6=2)(2 thru high=1)into bed_1 loc_1 bath_1 bed_2 loc_2 bath_2


**create delirium measure
count del_1= b3a b3b (1) ic3a ic3b ic3c (2) ic4(1)
count del_2= b3a_2 b3b_2 (1) ic3a_2 ic3b_2 ic3c_2(2) ic4_2(1)
recode del_1 del_2 (1 thru high=1)
if (del_1 eq 0 and missing(b3a) and missing(b3b) and missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1=$sysmis
if (del_2 eq 0 and missing(b3a_2) and missing(b3b_2) and missing(ic3a_2) and missing(ic3b_2) and missing(ic3c_2) and missing(ic4_2))del_2=$sysmis
var labels del_1 delirium time 1
var labels del_2 delirium time 2
 
**frequencies variables= del_1 del_2 delcap 
**frequencies variables= b3a b3b  ic3a ic3b ic3c  ic4
**crosstabs tables=del_1 by del_2 
   /cells=count row col tot
**

**if (del_1a eq 0 and missing(b3a) and Missing(b3b))del_1a=$sysmis
  if (del_1b eq 0 and missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1b=$sysmis
  if (del_1c eq 0 and missing(b3a) and missing(b3b) and missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1c=sysmis

**frequencies variables= b3a b3b ic3a ic3b ic3c ic4 del_1a del1_b del1_c
**frequencies variables= h3 ig8a h5 ig1fb h7a ig7a

do if missing(h3).
recode ig8a (2=1)(0,1,3=0)into h3.
end if.
do if missing(h5).
recode ig1fb  (0,1,2=0)(3=1)(4,5,6,7,8=2)into h5.
end if.
do if missing(h7a).
recode ig7a (0=0)(1=1)(else=sysmis)into h7a.
end if.


**frequencies variables=e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e
do repeat
   mdshc = e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e  /
   icode=  ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1i ie1j ie3a ie3b ie3c ie3d ie3f /
do if missing(mdshc)
. recode icode (0,1=0)(2=1)(3=2)into mdshc
end if
end repeat

recode h7a h7b i2a i2b (1 thru high=1).
recode f2 (0=0)(1,2=1)into f212. 
recode e1a e1b e1c e1d e1e e1f  e1g e1h e1i  e3a e3b e3c e3d e3e 
   f2 f3a ie1f  ie1h ie1k (missing=sysmis)(0=0)(1 thru high=1) into
  e1a12 e1b12 e1c12 e1d12 e1e12 e1f12 e1g12 e1h12 e1i12 
  e3a12 e3b12 e3c12 e3d12 e3e12  f212  f3a13 ie1f13  ie1h12 ie1k12.   

recode ie2a ie2b ie2c if1a if1b if1c if1e if1f if1g  (missing,8=sysmis)(0=0)(1 thru high=1)into ie2a13 ie2b13 ie2c13 
   if1a0 if1b0 if1c0 if1e0 if1f0 if1g0. 
recode  if1a if1b if1c if1e if1f if1g (missing,8=sysmis)(0,1=0)(2 thru high=1) into
    if1a01 if1b01 if1c01 if1e01 if1f01 if1g01. 
recode f2 (missing=sysmis)(2=1)(else=0)into f22.
recode f3a (missing=sysmis)(3=2)(else=0)into f3a3.
recode f3a (missing=sysmis)(0,1=0)(else=1)into f3a23. 
variable labels e1a12 e1a12 sadness  no vs yes /
  e1b12 e1b12 anger no vs yes /
  e1c12 e1c12 fears  no vs yes /
  e1d12 e1d12 health complaints  no vs yes /
  e1e12 e1e12 repetirive complaints  no vs yes /
  e1f12 e1f12 sad facial expressions  no vs yes /
  e1g12 e1g12 crying, tearful  no vs yes /
  e1h12 e1h12 withdrawal  no vs yes /
  e1i12 e1i12 reduced social interactions no vs yes /
  e3a12 e2a12 wandering no vs yes /
  e3b12 e3b12 verbally abusive  no vs yes /
  e3c12 e3c12 physically abusive no vs yes /
  e3d12 e3d12 socially inappropriate  no vs yes /
  e3e12 e3e12 resists care  no vs yes /
  ie2a13 ie2a13 self report little interest no vs yes /
  ie2b13 ie2b13 self report anxious, restless no vs yes /
  ie2c13 ie2c13 self report sad, depressed no vs yes /
  f212 f212 decline social activities no vs yes /
  f22 f22 declined in soc act and distressed  no vs yes /
  f3a13 alone never vs other no vs yes /
  f3a3 f3a3 less all time vs all time no vs yes /
  f3a23 f3a23 not long alone vs long alone no vs yes /
  ie3f13 ie3f13 public sexual behavior no vs yes /.
variable labels  if1a0 if1a0 never vs oth part in act of interest no vs yes /
   if1b0 if1b0 never vs other visit socl relat or family  no vs yes /
   if1c0 if1c0 never vs other other interactions with socl rel or family no vs yes /
   if1e0 if1e0 never vs other conflict or anger  no vs yes /
   if1f0 if1f0 never vs other fearful of family or close frd no vs yes /
   if1g0 if1g0 never vs other neglected, aboused, mistreated no vs yes / 
   if1a01 if1a01 within 30 days part in act or int no vs yes /
   if1b01 if1b01 within 30 days vis soc rel or fam no vs yes /
   if1c01 if1c01 within 30 days oth int wth soc rel or fam no vs yes /
   if1e01 if1e01 within 30 days conflict or anger no vs yes /
   if1f01 if1f01 within 30 days fearful fam mem or close aqu
   if1g01 if1g01 within 30 days neglected, abused, mistreated no vs yes /.


count missadl_a= h2a_a h2b_a h2c_a h2e_a h2f_a h2g_a h2i_a h2j_a (missing). 


**frequencies variables= country b1a b1b b2a b2b b3a b3b c1 c2 c3 d1 
   e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e f1a f1b f2 f3a f3b 
   g1ea g1fa g1ga g1ha g1ia g1ja g1ka g1la g2a g2b g2c g2d g3a g3b 
   h1ab h1bb h1cb h1db h1eb h1fb h1gb h2a h2b h2c h2d h2e h2f h2g h2i h2j 
**frequencies variables=    h3 h4a h4b h5 h6a h6b h7a h7b h7c i1a i1b i2a i2b i3
   j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u
   j1v j1w j1x j1y j1z j1aa j1ab
   k1a k1b k1c k1d k2a k2b k2c k2d k2e k3a k3b k3c k3d k3e k3f k3g
**frequencies variables=     k4a k4b k4c k4d k4e k5 k6a k6b k7a k7b k7c k8a k8b k8c k8d k8e 
   l1a l1b l1c l2a l2b l2c l2d l3 m1a m1b m1c n1 n2a n2b n3a n3b n3c n3d n3e 
   n4 n5a n5b n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b 
  p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja
**frequencies variables=  p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n p2o p2p
  p2q p2r p2s p2u p2v p2w p2x p2y p2z p3a p3b p3c p3d 
  p4a p4b p4c p5 p6 p7 q1 q2a q2b q2c q2d q3 q4  
      missadl missadl_a
    sourcen source  country state collage usa

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
variable labels del1  delirium symptom present.

** HOME CARE FRAILTY SCALE IN PAPER MAY 2016
** THIS IS REPLACED BY NEW FRAILTY MEASURE BELOW
** 
count frailtyHC= h2c (3 thru high) h1bb h1ab h1db (2)
   B2a c3 f2 e1i h5 h6b j1z j1aa j1b k2d
   K3c j1u j1w j1h l1a l2b (1 thru high)
   K5 e1h i3 (2 thru high) 
   H2i h2g h1ab (1 thru high) 
   H1eb h1cb (2 thru high)    
   H2b (3 thru high)
count frailtyMISS=  h2c  h1bb h1ab h1db 
   B2a c3 f2 e1i h5 h6b j1z j1aa j1b k2d
   K3c j1u j1w j1h l1a l2b 
   K5 e1h i3  
   H2i h2g h1ab  
   H1eb h1cb     
   H2b 
 (missing)

 




**
recode c3 h4a h5  k6a h1ab h1bb h6b h2c fall_1 (missing=sysmis)(0=0)(1 thru high=1)into c3X h4aX h5x h6aX h1abX h1bbX h6bX h2cX k5x
var labels  c3X c3x understand 0 vs other /  
   h4aX h4ax assistive device  none  vs other /
   h5x h5x up and down stairs without help vs other /
  h6aX h6ax days out  every day vs other /
  h1abX h1abx meal prep no difficulty vs other /
   h1bbX h1bbx ordinary housework  no difficulty vs other /
   h6bX h6bx hrs phy activity  two or more vs less/ 
   h2cX loc in home  indep vs other /  
   k5x k5x fell 1 or more times/
**  
compute frmhrs=sum(p1ab,p1bb,p1cb,p1db,p1fb,p1gb)
if (missing(p1ab) and missing(p1bb) and missing(p1cb))frmhrs=$sysmis
var labels frmhrs hours formal care seven days
recode g3a (120 thru high=120)/g3b (48 thru high=48)
compute infhrs=g3a
do if not missing(g3b)
. compute infhrs=g3a+g3b
end if
var labels infhrs informal hours seven days
compute infhrs_2=g3a_2
do if not missing(g3b_2)
. compute infhrs_2=g3a_2+g3b_2
end if
var labels infhrs_2 informal hours time 2 seven days

recode frmhrs infhrs (low thru -1=sysmis)(168 thru high=168).
if (missing(frmhrs))infhrs=$sysmis.
if (missing(infhrs))frmhrs=$sysmis.
compute tothrs=frmhrs+infhrs.
variable labels tothrs tothrs hrs total care seven days. 


if (MISSING(H1AB)) H1AB= IG1AB.

recode g1fa (0 thru 2=0)(3 thru high=1)(else =sysmis)into g1fa0.
recode g1ga g1ha g1ia g1ja g1ka  g1la (0=0)(missing=sysmis)(else=1) into g1ga0 g1ha0 g1ia0 g1ja0 g1ka0  g1la0.
recode h5 (0=0)(1 thru high=1)into h5x.

recode  infhrs frmhrs tothrs (0 thru 15=0)(15 thru high=1) into  infhrs15 frmhrs15 tothrs15. 
variable labels infhrs15 inf care hrs 15 or more no v yes/
   frmhrs15  form care hrs 15 or more  no v yes/
   tothrs15 tot hrs care 15 or more  no v yes/.

recode g2b g2c f3b  (1 thru high=1).
recode frailtyhc (0 thru 11=0)(12 thru high=1) into frailtyhc12.
recode h1ab h1bb h1cb h1db h1eb h1fb h1gb (0 thru 1=0)(2 thru high=1)into  h1ab3 h1bb3 h1cb3 h1db3 h1eb3 h1fb3 h1gb3. 
variable labels h1ab3 h1ab3 meal preparation not dep vs dep /
  h1bb3 h1bb3 ordinary housework not dep vs dep /
  h1cb3 h1cb3 manage finances not dep vs dep /
  h1db3 h1db3 manage medications not dep vs dep /
  h1eb3 h1eb1 phone use not dep vs dep /
  h1fb3 h1fb3 shopping not dep vs dep /
  h1gb3 h1gb3 transportationnot dep vs dep /. 
recode h2a h2b h2c h2d h2e h2f h2g h2h  h2i h2j (0,1=0)(2 thru high=1)into h2a2 h2b2 h2c2 h2d2 h2e2 h2f2 h2g2 h2h2  h2i2 h2j2. 
recode h2a h2b h2c h2d h2e h2f h2g h2h  h2i h2j (0=0)(1 thru high=1)into h2a1 h2b1 h2c1 h2d1 h2e1 h2f1 h2g1 h2h1  h2i1 h2j1. 
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
  i1a2 i1a2 bladder  continent  yes vs no /
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
   widow  widow widowed/
   sepDIV  sepdiv separated or divorced/
variable labels age60 60 or older/
    age70  70 or older/
    age80 80 or older/
    age90 90 or older.
recode cc5 (1=1)(missing=sysmis)(else=0)into priHOME/
    cc5 (2=1)(missing=sysmis)(else=0)into withHC/
    cc5 (3,4,5=1)(missing=sysmis)(else=0)into supHOUSE/.
variable labels priHOME prihome prihome live in private home no home care services /
    withHC withhc private home with home care services/
    suphouse suphouse lives in a supported housing environment/.
recode cc6 (1=1)(missing=sysmis)(else=0)into  liveALONE/   
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
recode country ("USA_CT"=1)(else=0) into usa_conn /
   country ("USA_CA","USA_CT","USA_GA","USA_LA","USA_MA",
        "USA_MO","USA_NJ","USA_NY","USA_RI","USA_TX"=1)(else=0)into usa /
   country ("USA_GA"=1)(else=0)into usa_georgia /
   country ("USA_LA"=1)(else=0)into usa_louisia  /
   country ("USA_MA"=1)(else=0)into usa_mass /
   country ("USA_MO"=1)(else=0)into usa_missouri /
   country ("USA_NJ"=1)(else=0)into usa_newJersey /
   country ( "USA_NY"=1)(else=0)into usa_NewYork /.



compute bchange=b1a_2 - b1a .
compute hchange =h2a_2 - h2a.

**frequencies variables= missadl commonmiss age  h7a h7b  b1a b1a_2 b2a h2a_2 h2a h2a_2 
   h2b h2c h2c_2  h2d h2e h3 bchange hchange  country
**means tables= missadl commonmiss age bchange hchange missadl h7a h7b b1a b1a_2 b2a h2a_2 h2a h2a_2 
   h2b h2c h2c_2  h2d h2e h3   by country
   
  
compute personBELIEVES = h7a.
if (missing(h7a))personBELIEVES = ig7a. 

do if missing( h3).
recode ig8a (missing=sysmis)(2=1)(else=0)into h3.
end if.
do if missing (j1n). 
recode ii1a (missing=sysmis)(1,2,3=1)(else=0) into j1n.
end if.
do if missing(j1o).
recode ii1b (missing=sysmis)(1,2,3=1)(else=0) into j1o.
end if.
do if missing(h2c).

compute h2c= ig2f.
end if. 

compute h2c9=h2c.
if (missing(h2c9))h2c9=h2h.
if (missing(h2c9))h2c9=h2j.

compute h2c9_2=h2c_2.
if (missing(h2c9_2))h2c9_2=h2h_2.
if (missing(h2c9_2))h2c9_2=h2j_2.

count missMODEL= adlh h7a h7b h7c h3 j1n j1o l1a l2b (missing).

do if missing(p2p).
recode  p1fa (0=0)(1 thru high=1)(missing=sysmis) into p2p.
end if.
do if missing(p2p).
recode  in3ea (0=0)(1 thru high=1)(missing=sysmis)into p2p.
end if.

do if missing(p2o).
recode  p1ga (0=0)(1 thru high=1)(missing=sysmis) into p2o.
end if.
do if missing(p2o).
recode  in3fa (0=0)(1 thru high=1)(missing=sysmis)into p2o.
end if.


recode p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja (0=0)(missing=sysmis)(else=1) into
    p1aa1 p1ba1 p1ca1 p1da1 p1ea1 p1fa1 p1ga1 p1ha1 p1ia1 p1ja1.

variable labels  p1aa1 p1aa1  home health aides/
   p1ba1 p1ba1 visiting nurses/
   p1ca1 p1ca1 homemaking services/
   p1da1 p1da1 meals/
   p1ea1 p1ea1 volunteer services/
   p1fa1 p1fa1 physical therapy/
   p1ga1 p1ga1 occupational therapy/
   p1ha1 p1ha1 speech therapy/
   p1ia1 p1ia1 day care or day hosp/
   p1ja1 p1ja1 soc worker in home.


if (missing(p2v)) p2v=p2w.
do if missing(p2v).
recode p1ba (0=0)(1 thru high=1)(missing=sysmis) into p2v.
end if.
do if Missing(p2v).
recode in3ba (0=0)(1 thru high=1)into p2v.
end if. 


recode p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l (0=0)(missing=sysmis)(else=1)into 
   p2a1 p2b1 p2c1 p2d1 p2e1 p2f1 p2g1 p2h1 p2i1 p2j1 p2k1 p2l1. 
recode p2m p2n p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z (0=0)(missing=sysmis)(else=1) into
  p2m1 p2n1 p2o1 p2p1 p2q1 p2r1 p2s1 p2t1 p2u1 p2v1 p2w1 p2x1 p2y1 p2z1/.
Recode p4a p4b p4c  (0=0)(1 thru high=1)into p4a19 p4b19 p4c19.
Recode p4a p4b p4c  (0,1=0)(2 thru high=1) into p4a29 p4b29 p4c29.
recode in2c in2g in2k in2l in2m in2n in2d (missing=sysmis)(0=0)(1 thru high=1) into
   in2c1 in2g1 in2k1 in2l1 in2m1 in2n1 in2d1. 
recode p3a p3b p3c p3d (missing=sysmis)(0,1=0)(2 thru high=1)into p3a2 p3b2 p3c2 p3d2.
variable labels  p2a1 p2a1 oxygen/
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
  p2z1  p2z1 special diet/
  p4a19 p4a19 hosp admit/
  p4b19 p4b19 er visit/
  p4c19 p4c19 emergent care.

variable labels   in2c1 in2c1 infection control/
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

if (missing(p2j1))p2j1=in2d1.   
recode ir3 ir4 (missing=sysmis)(0 thru 2=0)(else=1)into ir30 ir40.
recode ir3 ir4 (missing=sysmis)(8 thru high=1)(else=0)into ir38 ir48.
recode ir5 (missing=sysmis)(0,1,2=0)(else=1)into ir52/.
variable labels ir30 ir30 0 to 2 ADLs indep pre deteriotate/
   ir38 ir38 8 plus adls ind pre deteriotate/
   ir40 ir40 0 to 2 Iadls indep pre deteriorate/
   ir48 ir48 8 plus IADLs indep pre deteriorate/ 
   ir52 ir52 onset beyond 30 days ago/.

recode  ij1    ij2a ij2b  ij2e ij2f  ij2g ij2h ij2i ij2j ij2k ij2l ij2m ij2n ij2o ij2p ij2q ij2r ij2s ij3 ij4 ij7 ij8a ij8b  (0=0)(1 thru high=1)
    INTO  ij10  ij2a0 ij2b0  ij2e0 ij2f0  ij2g0 ij2h0 ij2i0 ij2j0 ij2k0 
    ij2l0 ij2m0 ij2n0 ij2o0 ij2p0 ij2q0 ij2r0 ij2s0 ij30 ij40 ij70 ij8a0 ij8b0.             
recode k4a (3=1)(missing=sysmis)(else=0)into k4a3/
        k4b l3 n2a (1 thru high=1)(0=0)into k4b1  l31 n2a1.
recode p6 (missing=sysmis)(2=1)(else=0)into p62.
recode p6 (missing=sysmis)(1=1)(else=0)into p61.
recode in1d in1h in1e in1g in1f in1a in1c in1b k1a k1e k1c k1d (0=0)(1 thru high=1).
do if missing(n5d).
recode in2n (0,1=0)(2 thru high=1) into fillxx.
compute n5d=fillxx.
end if.
recode n2b (0=0)(1 thru high=1) into n2b1.
recode  l2c il6 (2 thru high=1).
recode iq1a o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b 
     iq2 iq3a iq3b iq3c iq4 iq1b ( 1 thru high=1).
recode q4 (missing=sysmis)(2=1)(else=0)into q42.
recode q4 (missing=sysmis)(3=1)(else=0)into q43.
recode p2t (0,1=0)(2 thru high=1)into  physician.
recode in5c (0=0)(1 thru high=1) into fillxx.
if (missing(physician))physician= fillxx.
recode ir2 (missing=sysmis)(0=0)(else=1)into ir20.
recode ir2 (Missing=sysmis)(2=1)(else=0)into ir22.
recode  b1b ic2c ic4 (missing=sysmis)(0=0)(1 thru high=1).

variable labels physician physician visit/
   p61 p6a improves fewer services/
   p62 p62 deteriorated more services/
    q42 q42 low medication compliance/
    q43 q43 Receives no medications/
   med8 med8 8 or more medications in last 7 days/
    ir20 ir20 self suff improved/
    ir22 ir22 self suff deteriorated.

recode ii1m ii1n ii1w ii1o ii1p ii1q ii1r ( 1 thru high=1) into ii1mD ii1nD ii1wD ii1oD ii1pD ii1qD ii1rD. 
variable labels  ii1mD copd/
  ii1nD ii1nD anxiety/
  ii1wD ii1wD bipolar/
  ii1oD ii1oD depression/
  ii1pD ii1pD schizophrenia /
  ii1qD ii1qD pneumonia /
  ii1rD  ii1rD UTI.
recode ig8a (missing=sysmis)(0=1)(else=0)into ig8a0.
variable labels ig8a0 ig8a0 adl improve.

recode b2a (0=0)(missing=sysmis)(else=1)into b2a0.
recode b2a (0 thru 3=0)(4 thru high=1)(else=sysmis)into b2a4.
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
   ic5_zero  ic5_zero decision improve no v yes/
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


count missall=  b1a b1b b2a b2b b3a b3b c1 c2 c3 d1 
   e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e f1a f1b f2 f3a f3b 
   g1ea g1fa g1ga g1ha g1ia g1ja g1ka g1la g2a g2b g2c g2d g3a g3b 
   h1ab h1bb h1cb h1db h1eb h1fb h1gb h2a h2b h2c h2d h2e h2f h2g h2i h2j 
   h3 h4a h4b h5 h6a h6b h7a h7b h7c i1a i1b i2a i2b i3
   j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u
   j1v j1w j1x j1y j1z j1aa j1ab
   k1a k1b k1c k1d k2a k2b k2c k2d k2e k3a k3b k3c k3d k3e k3f k3g
     k4a k4b k4c k4d k4e k5 k6a k6b k7a k7b k7c k8a k8b k8c k8d k8e 
   l1a l1b l1c l2a l2b l2c l2d l3 m1a m1b m1c n1 n2a n2b n3a n3b n3c n3d n3e 
   n4 n5a n5b n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b 
  p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja
  p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n p2o p2p
  p2q p2r p2s p2u p2v p2w p2x p2y p2z p3a p3b p3c p3d 
  p4a p4b p4c p5 p6 p7 q1 q2a q2b q2c q2d q3 q4 (missing).


**means tables=walkimp by j1nd j1od b2b h3 n5b n5c
   

recode missall (0=0)(1 thru 20=1)(21 thru 40=2)(41 thru 50=3)(51 thru 99=4)
     (100 thru 119=5)(120 thru high=6)into missCATS.
value labels missCATS (0) none (1) 1-20 (2)21-40 (3)41-50 (4)51-99 (5)100-119 (6)120 thru HIGHEST.
variable labels misscats missing items of about 200 total.
** IADL HIIEARCHY**

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
if (iadl eq 0 and (twoi gt 0 or onei gt 0))iadl=-1.
end repeat.



** adl hierarchy    fill in missing data 
**
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j (8=4)(else=copy)into 
      h2aR h2bR h2cR h2dR h2eR h2fR h2gR h2hR h2iR h2jr
compute xxfill=h2b
if (missing(h2b))xxfill=h2f
compute h2cr2=h2cr
if (missing(h2cr))h2cr2=xxfill
compute h2cR = h2cr2

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

recode    adlh (0 thru 3=0)(4 thru high=1) into adlh4/
  adlh (0=0)(missing=sysmis)(else=1)into adlh0/
   adlh (0 thru 2=0)(missing=sysmis)(else=1)into adlh3/.
variable labels adlh4  adlh4 0 to 3 vss 4 or higher/
   adlh0 adlh0 0 vs 1 or higher/
   adlh3 adlh3 0 thru 2 vs 3 or higher/.


recode riadlhi (missing=sysmis) (0=0)(1 thru high=1)into riadlhi0.
recode riadlhi (missing=sysmis)(0,1=0)(2 thru high=1)into riadlhi1.
recode riadlhi (missing=sysmis)(0 thru 2=0)(3 thru high=1)into riadlhi2.
variable labels riadlhi0 riadlhi0  0 vs 1 or higher/
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

compute walkIMp2 = locI_2xx.
recode walkIMP2 (low thru high=0).
if (locI_2xx lt locIxx) walkIMP2=1.
if (locIxx eq 0) walkimp2=$sysmis.
variable labels walkIMP2  improvement in walking performance on updated new measure.

compute walkDEc2= loci_2xx.
recode walkDEC2(low thru high=0).
if (locixx lt locI_2xx) walkDEC2=1.
if (locIxx eq 7) walkDEC2=$sysmis.
variable labels walkDEC2  decline in walking performance on updatednew measure.

count LOCriskVARS= j1kd p1ca1 n4 j1ld suphouse h4b0 withhc p2s1 n5d p1aa1 j1gd p1da1 q43 widow f3a23 f3a13 
   h4a4 k3c  p1ha1 k4a3 h2g2 physician b2b ic5_two f22 p1fa1 h1cb3 p2j1 f212 h6a3 k7a l1a id3a_zero h1db3 prihome g2a h5x p2l1 k9a j1nD del1
   h1ab3 h1bb3 k2e n3a p4a29 cc412 b3a h1fb3 h1gb3 p2f1 infhrs15 k9d g2b h6bx  h6b j1od  p4a19 h3 h2i2 h1abx p2e1 frailtyhc12 
   h2j2 h7a h2a2 h2e2 h7b n5c h2h2 frailtycu4 h2f2 adlh3 h2b2 adlh4 adlh0 h2c2 h2cx (missing).


**
** **   FOR LOCOMOTION REGRESSION
**   vars removed because of high missing count:   70 or older, 80, or older, 90 or older 
**
**  code to replace cases wher less than 10% missing --  fill in with code oppisite predictor direction
**


** recode j1kd p1ca1 n4 j1ld suphouse h4b0 withhc p2s1 n5d p1aa1 j1gd p1da1 q43 widow f3a23 f3a13  
   h4a4 k3c  p1ha1 k4a3 h2g2 physician b2b ic5_two f22 p1fa1 h1cb3 p2j1 f212 h6a3 k7a l1a id3a_zero h1db3 prihome g2a h5x p2l1 k9a j1nD del1
   h1ab3 h1bb3 k2e n3a p4a29 cc412 b3a h1fb3 h1gb3 p2f1 infhrs15 k9d g2b h6bx  h6b j1od  p4a19 h3 h2i2 h1abx p2e1 frailtyhc12 
   h2j2 h7a h2a2 h2e2 h7b n5c h2h2 frailtycu4 h2f2 adlh3 h2b2 adlh4 adlh0 h2c2 h2cx (missing=1)(else=0)

do repeat 
  zero=   k3g n3c b2a0 c20 f3b if1e k3f m1b e1e12 k3f m1b e1e12 e1g12 e1c12 e1d12 e1h12 j1uD k4dd e1f12 k4b1  fellone k8e e1i12 h52 k2c k9c h1eb3 
    h1bbx k8c l2c p4b29 h4a4 k3c k4a3 h2g2 b2b ic5_two f22 h1cb3 f212 h6a3 k7a l1a h1db3 h5x k9a j1nd del1 h1ab3 h1bb3 k2e
    n2a n3a p4a29 cc412 b3a h1fb3 h1gb3 k9d h6bx h6b j1od p4a19 h3 h2i2 h1abx p2e1 h2j2 h7a h2a2 h2e2 h7b 
   n5c h2h2 h2f2 adlh3 adlh4 adlh0 h2b2 /.
recode zero (missing=0).
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
variable labels canTREAT  chemo or radiation.

 
count canTREAT =p2f1 p2l1 (1 thru high).
recode canTREAT( 1 thru high=1).
if (canTREAT eq 0 and missing(p2f1) and missing(p2l1)) canTREAT=$sysmis.
variable labels canTREAT  chemo or radiation.
 

count infusion =p2h1 p2i1 (1 thru high).
recode infusion( 1 thru high=1).
if (infusion eq 0 and missing(p2h1) and missing(p2i1)) infusion=$sysmis.
variable labels infusion iv infusion.

count delhal= k3f k3g (1 thru high).
count ptTHER=p1fa1 p2p1 (1 thru high).
recode ptTHER (1 thru hig=1).
if (ptTHER eq 0 and missing(p1fa1) and missing(p2p1)) ptTHER=$sysmis.
variable labels ptTHER physical therapy.
recode delhal (1 thru high=1).
variable labels delhal  has delusion or halucination. 

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

recode  adlh1 adlh3  adlh4 h4b0 n3d j1kd j1ld j1gd j1hd  widow (missing=0).

if (missing(h7c))h7c=h7b.

recode adlh (0=0)(1 thru high=1)(missing=sysmis)into modLOCimp.
count modLOCimp= h7a h7c h3 j1nd j1od  n3d p4a19  cc412 p2p1 p2o1 l1a (1 thru high) 
         h1fb3 h1gb3 h2a2  h4a4  h6a3 j1gd j1hd j1ld  (0) k7a adlh1 adlh4 (1).
if (missing(h2c))modLOCimp=$sysmis.
  
recode modLOCimp (0,1,2=1)(3,4=2)(5,6=3)(7,8=4)(9,10=5)(11,12=6)(13,14=7)(15,16=8)(17 thru high=9).
do if any(loci,5,6,7).
. compute modLOCimp=modLOCimp+1.
. recode modLOCimp (10 thru high=10).
end if.
count lowestx= h2c (0) cps(6) adlh (0).
if (lowestx gt 0)modLOCimp=1.

value labels modLOCimp  (1)one - lowest risk count  0-2  (2)two 3-4 (3)three 5-6 (4)four 7-8 (5)five 9-10
      (6)six  11-12 (7)seven 13-14 (8)eight 15-16 (9)nine  17 plus (10)ten  Highest risk improve.
variable labels modLOCimp Model to predict likelihood that locomotion will improve - recover status.


recode p1aa_2 p1ba_2 p1ca_2 p1da_2 p1ea_2 p1fa_2 P1ga_2 p1ha_2 p1ia_2 p1ja_2 (1 thru high=1). 

**** OLDER HOSPITAL RISK CODE --- BEGINNING


recode   p4a p4a_2 p4b p4b_2 (1 thru high=1)(missing=sysmis)(else=0) into p4a19 p4a19_2 p4b19 p4b19_2. 

count heT1 =p4a p4b (1 thru high).
count heT2=p4a_2 p4b_2 (1 thru high).
if (missing(p4a) and missing(p4b))heT1=$sysmis.
if (missing(p4a_2) and missing(p4b_2))heT2=$sysmis.

recode p4b (0=0)(missing=sysmis)(1 thru high=1)into ed1.

compute hosp1=$sysmis.     
recode p4a (0=0)(1=1)(2=2)(3 thru high=3) into hosp1.
          
if (p4a eq 0 and cc4 gt 0)hosp1=1.
if (missing(hosp1) and (not missing(p4a) or not missing(cc4)))hosp1=0.

compute hosED2=$sysmis.              
if (p4a_2 gt 0 or p4b_2 gt 0 or cc4_2 gt 0)hosED2=1.
if (missing(hosED2) and (not missing(p4a_2) or not missing(p4b_2)))hosED2=0.
recode p4a_2 p4b_2 (0=0)(1 thru high=1)(else=sysmis)into hosp2 ed2.
if (hosp2 eq 0 and cc4_2 gt 0)hosp2=1.

recode a1y (low thru 2009=1)(2010 thru high =2)(missing=sysmis)into assYR.

**frequencies variables= hosed p4a p4b in5a in5b cc4 hosed2 p4a_2 p4b_2 cc4_2 in5a_2 in5b_2

**crosstabs tables= assyr by hosed2
    /cells=count row col tot

*compute derivation=$sysmis.  
* if (any(dataset,"1","2","5","7","10","11"))derivation=1.    
*if (dataset eq "7" and a1m eq 2)derivation=0.
 *if (dataset eq "5" and a1y lt 2007)derivation=0.
 *if (any(a1m,1,4,7,10))derivation=0.
 *if (missing(hosed))derivation=$sysmis.
 *value labels derivation (0)retest (1)test.
 *variable labels derivation the sample to create the hos ed risk model.

** Select TEST DATA sample.
*select if derivation eq 1.
** Select reTEST DATA sample.
 *select if derivation eq 0.
**
** CREATE Hospital-ED Risk Index Nov 23, 2013
count Ivinfuse=p2h p2i (1,2)
if (ivinfuse eq 0 and missing(p2h) and missing(p2i))ivinfuse=$sysmis
count renal=j1aa (1,2) p2g (1,2)
if (renal eq 0 and missing(j1aa) and missing(p2g))renal=$sysmis
count HOSEDrisk= j1u (1,2) L1a (1) k2d (1) J1w (1,2) p6 (2)
     N2b (1,2,3,4) k5 (2 thru high) renal (1,2) j1x (1,2) j1z (1,2) p4c (1 thru high)
     Q1 (9 thru high) p2v (1,2) p2j (1,2) n5c(1) IVinfuse (1,2)
count HOSEDmiss =  j1u  L1a  k2d  J1w  p6 
     N2b  k5 renal  j1x j1z p4c 
     Q1  p2v  p2j  n5c ivinfuse (missing)
if (HOSEDmiss gt 4)HOSEDrisk=$sysmis
count PROTECT=j1g (1,2) p1ia (1 thru high)
recode PROTECT (2=1)     
if (protect eq 0 and missing(j1g) and missing(p1ia))protect=$sysmis
if (HOSEDrisk gt 0 and PROTECT gt 0)HOSEDrisk=HOSEDrisk-1
var labels HOSEDrisk hospital ed risk model final nov 23 2013
recode HOSEDrisk (6 thru high=6)


**POSITIVE RISK FACTORS  
     J1u      Pneumonia (1,2)
     L1a     Unintended weight loss (1) 
     K2d     Loss of appetite (1)
     J1w     Urinary tract infection (1,2)        NO
     P6         Overall Deteriorated (2)
     N2b      Stasis ulcer (1,2,3,4) 
     Fell2     Fell (k5=2 thru high)
     Renal    Renal failure (j1aa=1,2) or dialysis (p2g=1,2)
     J1x       Cancer, not skin cancer (1,2)
     J1z        Emphysema/COPD/Asthma (1,2)
     p4c       Emergent MD care (1 or higher)      NO
     Q1        Number of medications (9 or higher)   CHECKING
     p2v       Daily Nurse monitoring (1,2)
     P2j        Medication by injection (1,2)
     N5c       Surgical wound care (1) 
     infuse    IV infusion central (p2h=1,2) or IV infusion perihperal (p2i=1,2) 
**PROTECTIVE FACTORS
      J1g       Alzhimers (1,2)       
      P1ia     Day Care     (1 thru high)



recode j1a to j1ab (1,2=1)/k4a (0,1=0)(2 thru high=1).
          
recode  n2a n2b j1x j1c j1b j1a j1f j1o j1s j1y j1ab (1 thru high=1)/
   Q1 (0 thru 8=0)(9 thru high=1) /k5 (0=0)(1 thru high =1)into fell1/
   K5 (0,1=0)(2 thru high=1)(else=sysmis)into fell2/
   B2a c2 c3 (0=0)(1 thru high=1)into decs stood stand/
   E1a to e1i (1 thru high=1)/e3a to e3e (0,1=0)(2=1)/
   H2C H2I H2J (0,1,2=0)(3 THRU HIGH=1)/
   H5 (0=0)(1,2=1)/i1a i3 (0,1,2=0)(3 thru high=1)/.

recode cc6 (1=1)(2 thru high=0)/f3a (2,3=1)(0,1=0)/
    H1ab h1bb h1cb h1db h1fb h1gb (0=0)(1,2=1)/o2b (0=0)(1 thru high=1)/
    P1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja (0=0)(1 thru high=1)/
    P2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    P2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z (0,3=0)(1,2=1)(missing=sysmis)/
    P4c (1 thru high=1)/p6 (0,1=0)(2=1)/q4 (1 thru 2=1)(3=0).

recode l3 (1 thru high=1)/.

recode p2b (0=0)(1 thru high=1)into respirator.
if (p2c gt 0)respirator=1.
count infuse = p2h p2i (1,2).
recode infuse (2=1).
if (infuse eq 0 and missing(p2h) and missing(p2i))infuse=$sysmis.
  
*frequencies variables=infuse.
**


recode p4c_2 (1 thru high=1).
compute dement= j1g.
if (j1h gt 0)demen=1.



recode fall_1 fall_2  (0=0)(1 thru high=1) into fallany fallany_2.
recode fall_1 fall_2 (0,1=0)(2 thru high=1)into fallTWO fallTWO_2.
compute fallNEW = 0.
if (missing(fall_2))fallnew=0.
if (fall_1 gt 0)fallnew=$sysmis.
if (fall_2 gt 0 and fallnew eq 0)fallnew=1.

**crosstabs tables=hosed2 by fall_1 fallany
   /cells=count row col tot
   /statistics= chisqur risk  



if (missing(cardcap))cardcap=cardcap2.
count drsfill=    e1a e1b e1c e1d e1e e1f e1g e1h e1i  e2  ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1h ie1i ie1j ie1k  ii1o ii1n  (1 thru high).

count drsmiss=    e1a e1b e1c e1d e1e e1f e1g e1h e1i  e2  ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1h ie1i ie1j ie1k  ii1o ii1n  (missing).
if (drsmiss eq 23)drsfill=$sysmis.
if (not missing(drs))drsfill=drs.
recode drsfill (1 thru high=1).
**


recode cc4(0=0)(1 thru high=1)into cc4HOS.
compute  edhos= max(p4a,p4b).
**.
compute divert=0.
compute l2bx=l2b.
if (missing(l2bx) and ik2b lt 3)l2bx=ik2b.
if (missing(l2bx) and l2c lt 3)l2bx=l2c.
if (missing(l2bx))l2bx=0.
count cardiac =j1b j1c ii1l ii1k (1 thru high).
count UTIcopd= j1u j1z  ii1a ii1m (1 thru high).
count WTdec= l1a l2bx ik2a (1).
count oxygen = p2a  (1,2)  in2e (2,3).
count fall90= k5 ij1 (1 thru high).
count STROKEdia= j1a j1y  ii1t  ii1j (1 thru high).
count stasis = n2b il3 (1 thru high).
count ADLdecline= h3 (1) ig8a (2).
compute h7cfill=h7c.
if (missing(h7cfill))h7cfill=h7a.
if (missing(h7cfill))h7cfill=h7b.
count INcath=  i2b (1) ih2(2).
count cardcap2 = k3a k3e k3c (1) ij2e ij3  j1e ij2c  (1 thru high).
recode cardcap2 (1 thru high=1).

if (missing(cardcap))cardcap=cardcap2.
count drsfill=    e1a e1b e1c e1d e1e e1f e1g e1h e1i  e2  ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1h ie1i ie1j ie1k  ii1o ii1n  (1 thru high).

count drsmiss=    e1a e1b e1c e1d e1e e1f e1g e1h e1i  e2  ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1h ie1i ie1j ie1k  ii1o ii1n  (missing).
if (drsmiss eq 23)drsfill=$sysmis.
if (not missing(drs))drsfill=drs.
recode drsfill (1 thru high=1).
**.
do if edhos gt 1.
if (cardcap eq 1)divert=6.
if (cardcap eq 0 and INcath gt 0)divert =6.
if (cardcap eq 0 and INcath eq 0)divert=5.
end if.
**.
do if edhos eq 1.
if (cardcap eq 1 and cardiac gt 0)divert=5.
if (cardcap eq 1 and cardiac eq 0)divert=4.
if (divert eq 0 and cardcap eq 0 and h7cfill eq 0 and drsfill gt 0)divert=4.
if (divert eq 0 and cardcap eq 0 and h7cfill eq 0 and drsfill eq 0)divert=3.
if (divert eq 0 and cardcap eq 0 and h7cfill gt 0)divert=2.
end if.
**.
do if edhos eq 0.
if (divert eq 0 and cardcap eq 1 and cardiac gt 0 and UTIcopd gt 0)divert=4. 
if (divert eq 0 and cardcap eq 1 and cardiac gt 0 and UTIcopd eq 0)divert=3.
if (divert eq 0 and cardcap eq 1 and cardiac eq 0 and WTdec gt 0)divert=3.  
if (divert eq 0 and cardcap eq 1 and cardiac eq 0 and WTdec eq 0 and oxygen gt 0)divert= 4. 
if (divert eq 0 and cardcap eq 1 and cardiac eq 0 and WTdec eq 0 and oxygen eq 0)divert=2. 
if (divert eq 0 and cardcap eq 0 and fall90 gt 0 and STROKEdia gt 0)divert=3.
if (divert eq 0 and cardcap eq 0 and fall90 gt 0 and STROKEdia eq 0)divert=2.
if (divert eq 0 and cardcap eq 0 and fall90 eq 0 and stasis gt 0)divert=2.
if (divert eq 0 and cardcap eq 0 and fall90 eq 0 and stasis eq 0 and 
  ADLdecline gt 0)divert=2.
if (divert eq 0 and cardcap eq 0 and fall90 eq 0 and stasis eq 0 and 
  ADLdecline eq 0 and WTdec gt 0)divert=2.
if (divert eq 0 and cardcap eq 0 and fall90 eq 0 and stasis eq 0 and 
  ADLdecline eq 0 and WTdec eq 0)divert=1.
end if.
**. 
if (divert eq 0)divert=$sysmis. 
**
** end of code to create DIVERT
**.


count strokeDIA = j1a j1y (1 thru high).
if (missing(j1a) and missing(j1y))strokeDIAB=$sysmis.

count cardREsp= k3a k3e k3c (1) j1e(1 thru high).
if (missing(k3a) and missing(k3e) and missing(K3c))cardRESP = $sysmis.
count catUTI= j1w (1 thru high) i2b (1).
if (missing(j1w) and missing(i2b))catUTI=$sysmis.
count cardiac =j1b j1c (1 thru high).
if (missing(j1b) and missing(j1c)) cardiac=$sysmis.
count mixDIAG = j1z j1aa j1w  j1u (1 thru high).
if (missing(j1z) and missing(j1aa) and missing(j1w) and missing(j1u))mixDIAG= $sysmis.
count nutr = l1a l2a (1).
if (missing(l1a) and missing(l2a))nutr=$sysmis.
recode cc4 (0=0)(1 thru high=1)(missing=sysmis) into cc414.
recode cc5 (1.5=0)(2 thru high=1)into cc5234.



do if not missing (hosed). 
recode  j1aad j1ud  j1zd  l1a falltwo n2b1 k2d j1xd p2j n5c p2v infuse p62
    j1bd p2a1 n1 n2a1 h3 n3d  j1nd j1od b3b n5b l2a l2b l2c j1ad 
    j1fd e1a12 e1d12 e1e12 e1i12 f212 j1ed j1sd 
    k7a  k8a k8b k8c k8e n3a n3b  n3c  n3d n4  j1wd i2b  
    cardcap strokedia cardresp catuti cardiac mixdiag nutr cc5234 h7a  (missing=0).
end if.


** RISKhosp0=$sysmis
do if not missing(p4a) or not missing(p4b) or not missing(cc4)
. recode  j1zd  fallany   infuse
        j1aad  j1ed  i2b  
     k8c     j1bd l1a    
      k8a j1sd j1od k2d j1wd n3d (missing=0)
end if

recode p2a p2e p2f p2g  p2l  (1,2=1)(missing=sysmis)(else=0) into
    p2ad p2ed p2fd p2gd  p2ld.
recode n2a (0=0)(1 thru high=1) into n2a1.
do if not missing(hosed2).
recode  n2a1 j1ad j1yd  k3e k3d j1cd  k3a  k7c  p2ad p2ed p2fd p2gd  p2ld
     k2a k3b  k2c  j1xd k2e h3 j1nd 
     (missing=0). 
end if.

count lessions=n3a n3b il4 (1).
recode lessions h3 (1 thru high=1).

do if  not missing(hosed2).
recode j1zd  fallany   infuse i2b  
     k8a k8c     j1bd l1a  j1od j1wd n3d  
    h3 j1nd  j1xd n2a1  p2ad p2gd
     p2ld p2fd p2m1 n2b1 lessions n3c j1ld j1ud j1yd k3e
     k3c k6a k3e k8b k8e (missing=0).
end if.  


do if missing(k3b).
recode ih3 (8=1)(missing=sysmis)(else=0)into k3b.
end if.
do if missing(b3b).
recode ic5 (missing=sysmis)(2=1)(else=0)into b3b.
end if.
recode ij2g ij2f ij4 (0=0)(missing=sysmis)(else=1)into ij2g1 ij2f1 ij41. 
recode l3 ik3 (0=0)(missing=sysmis)(else=1)into l31 ik3.
if (missing(l31)) l3a=ik3.  
if (missing(p7))p7=q4.
** frequencies variables= h5x i1a2 i32 delhal delir k3b k2a b3b   
     e3a12 e3b12 e3c12 e3d12 e3e12 f3a13 b2b f3b f22 k3a p7
     iq3a iq3b iq3c  ij2g1 ij2f1 ij41 l31 l3a p7 

recode  h5x i1a2 i32 delhal delir k3b k2a b3b   
     e3a12 e3b12 e3c12 e3d12 e3e12 f3a13 b2b f3b f22 k3a p7 (missing=0).

**crosstabs tables= hosed2 by 
     h7a
    j1aad j1ud  j1zd  l1a falltwo fall_1 fallany  n2b1 k2d j1xd p2j n5c p2v infuse p62
    j1bd p2a1 n1 n2a1 h3 n3d  j1nd j1od b3b n5b l2a l2b l2c j1ad 
    j1fd e1a12 e1d12 e1e12 e1i12 f212 j1ed j1sd 
    k7a  k8a k8b k8c k8e n3a n3b  n3c  n3d  n4
    n4     cardcap strokedia cardresp catuti cardiac mixdiag nutr cc5234 
    j1wd  j1xd l2a k2e  h3  i2b  
    h1aa ig1aa h1aax  h1ba ig1ba h1bax 
  h1ca ig1ca h1cax h1ab ig1ab h1abx  h1bb ig1bb h1bbx h1cb ig1cb h1cbx
    delhal
   /cells=count row col tot
   /statistics= chisqur risk  

do if not missing(hosp2). 
recode h7a j1ud n2b1 p2j p62 n1 l2b l2c j1ad e1a12 e1e12 e1i12 f212 
     k8c k8a j1wd fallany j1nd j1od j1bd j1xd l1a l2a l2b l2c k2e n2a1 n3d h3 i2b infuse p2a p2g
      j1zd  fallany   infuse i2b p2a p2g  j1sd k8b k8e cc5234  p4b (missing=0).
end if.
recode p4b (0=0)(1 thru high=1)(missing=sysmis) into p4b1.
recode lessions (1 thru high=1).
**crosstabs tables= hosed2 by j1ud j1sd j1ad n2b1 h7a cc5234 p62 n3c lessions
   /cells=count row col tot
   /statistics= chisqur risk.  

recode bb1(1=1)(else=0)into male.

do if not missing(hosp2).
recode 
     j1aad j1ad j1ud j1wd k3c l1a k3a j1ed e1a12 e1d12 e1e12 p2a l2b k8c n5c 
     male k8a j1ld n2a1  cps26 cps234  (missing=0).
end if.
do if not missing(hosp2). 
recode  k8c k8a k8b k8e j1wd fallany j1nd j1od j1bd j1xd l1a  l2a l2b l2c k2e n2a1 n3d h3 i2b infuse p2a p2g
     j1zd j1ld cc5234 
       h7a j1ud n2b1 p2j p62 n1 l2b l2c j1ad e1a12 e1e12 e1i12 f212 n3c lessions p4b1 j1aad (missing=0).
end if.

*frequencies variables=hosp2.
**  Create hospital risk items baseline
count Ivinfuse=p2h p2i (1,2)
if (ivinfuse eq 0 and missing(p2h) and missing(p2i))ivinfuse=$sysmis
**.
count predHOSP0 =    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1xd   infuse 
    p4b1 j1aad   l1a n5c n2a1   ( 1)  h1aa (0)
   h1fa(0) k8c (1)  j1n j1o (1 thru high).
recode  predhosp0 (8 thru high=8).
count predHOSP1 =   j1bd j1zd infuse j1aad  n2b1 (1)  h1aa (0)   h1fa (0) k8a (1).
**

recode h1fa h1aa (0=1)(missing=sysmis)(else=0)into  h1fa0 h1aa0.
recode j1d j1f j1n j1o (1 thru high=1).

do if not missing(hosp2).
recode  j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1xd infuse p4b1 j1aad l1a n2a1 h1aa0 h1fa0 k8c j1d j1f j1n j1o (missing=0).
end if .

**temporary 
  select if hosp1 eq 0
**logistic regression hosp2 with  j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1xd infuse p4b1 j1aad l1a n2a1 h1aa0 h1fa0 k8c j1d j1f j1n j1o
     /method enter j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1xd infuse p4b1 j1aad l1a n2a1 h1aa0 h1fa0 k8c
     /metod fstep j1d j1f j1n j1o
   /external.  







compute hospRISKa=$sysmis.
do if hosp1 eq 0.
recode predhosp0 (0=1)(1=2)(2=3)(3,4=4)(5=5)(6 thru high=6) into hospRISKa.
end if.
do if hosp1 eq 1.
recode predhosp1 (0,1=7)(2,3=8)(4,5=9)(6 thru high=10) into hospRISKa.
end if.
do if hosp1 eq 2.
recode predhosp1 (0,1,2=8)(3,4=9)(5 thru high=10)into hospRISKa.
end if.
do if hosp1 gt 2.
recode predhosp1 (0=8)(1,2=9)(3  thru high=10)into hospRISKa.
end if.
variable labels hospriska  hospial risk scale at baseline october 2023.
value labels hospriska (1) 1. Very Low - No prior hosp  (2) 2. (3) 3.  (4) 4. Typical  No prior hosp (5) 5. (6) 6. High - No prior hosp
   (7) 7. Low - Prior hosp (8)8. Typical - Prior hosp (9)9. (10) 10. High - Prior hosp.





**   means tables= hosp2 by hospriska by country




**means tables= hosp2 by predhosp0 by hosp1
**means tables= hosp2 by predhosp1 by hosp1


do repeat  time1 = p2p p1fa p1ba p2v q4  p2r p2t /
    time2= p2p_2 p1fa_2 p1ba_2 p2v_2 q4_2  p2r_2  p2t_2 /
    service = pt_b pt_a nurse_b daily_b med_b day_b dr_b /.
compute service=$sysmis.
do if not missing(time1) and not missing(time2).
if (time1 lt 1 and time2 lt 1)service=0.
If (time1 gt 0 and time2 lt 1)service=1.
if (time1 gt 0 and time2 gt 0)service=2.
if (time1 lt 1 and time2 gt 0)service=3.
end if.
end repeat.

value labels pt_b pt_1 nurse_b daily_b med_b day_b 
  dr_b (0) none (1) time1 only (2) t1 and t2 (3) time2 only.
variable labels pt_b physical therapy /
   pt_a pt p1 /nurse_b visit nurse /
   daily_b daily nurse monitor /med_b med compliant / day_b day hospital / dr_b dr or clin visit /. 


recode cps b2a (missing=sysmis)(0=1)(else=0)into cps0 b2a0 /
    h4a (missing=sysmis)(2=1)(else=0)into h4a2.
  
recode  j1a j1b j1c j1d j1e j1f j1n j1o j1u j1v j1w j1x j1y j1z j1aa (1 thru high =1).
*means tables= hosp2 by hospriska by  j1a j1b j1c j1d j1e j1f j1n j1o j1u j1v j1w j1x j1y j1z j1aa. 
 
**means hosp2 by hospriska by cc6 bb4 cc5 bb1 f3a f3b g2a g2b g2c o2a o2b n5c p7 



*means hosp2 by hospriska by pt_b pt_a nurse_b daily_b med_b   day_b dr_b
   /statistics


**frequencies variables= hospriska hosp1 hosp2 p4a p4a_2 p4b P4b_2
means tables= hosp2 p4b_2 by hospriska
   /statistics

**frequencies hospriska
frequencies variables= hosp2
means tables= hosp2 by hospriska
    /statistics


recode h1aa h1fa h1ga (missing=sysmis)(0=1)(else=0)into h1aa0 h1fa0 h1ga0.
recode h1ea (missing=sysmis)(3=1)(else=0) into h1ea3.
do if not missing(hosp2).
recode  j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd 
     h1aa0 h1fa0 cps0 b2a0 h4a2 k8c k8a p2g j1aad  n2b1   k3e k3f k3g 
     (missing=0).
end if.


*means tables= hosp2   by hospriska by cwhole
   /statistics

*temporary
select if cwhole eq 2
means tables= hosp2 by hospriska by country

*temporary
select if cwhole eq 3

*means tables= hosp2 by  hospriska by country





*means tables= hosp2 by predHOSP0 by hosp1
means tables = hosp2 by predhosp1 by hosp1


*temporary
select if hosp1 eq 0
crosstabs tables= hosp2 by j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd 
     h1aa0 h1fa0 cps0 b2a0 h4a2 k8c
  /cells= count row col tot
    /statistics= risk



*temporary
select if hosp1 gt 0
crosstabs tables= hosp2 by j1bd j1zd j1aad h1aa0 h1fa0 k8a  n2b1 j1g infuse k3e k3f k3g cps0
    /cells=count row col tot
    /statistics= risk



*temporary
select of hosp1 eq 0 
means tables= hosp2 by predhosp0
statistics all

*temporary. 
*select of hosp1 gt 0.
*means tables= hosp2 by predhosp1 by hosp1.




*temporary 
select if hosp1 eq 0
logistic regression hosp2 with    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd 
     h1aa0 h1fa0 cps0 b2a0 h4a2 k8c
     /method enter    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd 
    /method fstep   h1aa0 h1fa0 cps0 b2a0 h4a2 k8c
   /external.  

*temporary
select if hosp1 gt 0
logistic regression hosp2 with  j1bd j1zd k8a infuse p2g j1aad  n2b1 
     h1aa0 h1fa0 k8c
    /method enter j1bd j1zd k8a infuse p2g j1aad  n2b1 
   /method fstep h1aa0 h1fa0 k8c




*crosstabs tables= hosp2 by h1aa0 h1fa0 cps0  b2a0  h4a2   k8c
    /cells=count row col tot
    /statistics= risk

*temporary 
select if hosp1 gt 0
crosstabs tables= hosp2 by h1aa0 h1fa0 cps0  b2a0  h4a2   k8c
    /cells=count row col tot
    /statistics= risk



**logistic regression hosp2 with    j1bd j1zd k8a infuse p2g j1aad n2b1
     h1aa0 h1fa0 h1ga0 h1ea3 l1a n2a1 lessions n3c 
     /method enter   j1bd j1zd k8a infuse p2g j1aad n2b1
    /method fstep   h1aa0 h1fa0 h1ga0 h1ea3 l1a n2a1 lessions n3c 
   /external.  




**temporary
  select if hosp1 gt 0
  means hosp2 by predhosp1 by h1aa h1ba h1ca h1da h1ea h1fa h1ga 
  h1ab h1bb h1cb h1db h1eb h1fb h1gb 

if (H1fa0 eq 1)predhosp1=predhosp1+1.
if (h1aa0 eq 1)predhosp1=predhosp1+1.

 
recode p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja (0=0)(missing=sysmis)(else=1) into
    p1aa1 p1ba1 p1ca1 p1da1 p1ea1 p1fa1 p1ga1 p1ha1 p1ia1 p1ja1.

recode p1aa_2 p1ba_2 p1ca_2 p1da_2 p1ea_2 p1fa_2 p1ga_2 p1ha_2 p1ia_2 p1ja_2 (0=0)(missing=sysmis)(else=1) into
    p1aa1_2 p1ba1_2 p1ca1_2 p1da1_2 p1ea1_2 p1fa1_2 p1ga1_2 p1ha1_2 p1ia1_2 p1ja1_2.

variable labels  p1aa1 p1aa1  home health aides/
   p1ba1 p1ba1 visiting nurses/
   p1ca1 p1ca1 homemaking services/
   p1da1 p1da1 meals/
   p1ea1 p1ea1 volunteer services/
   p1fa1 p1fa1 physical therapy/
   p1ga1 p1ga1 occupational therapy/
   p1ha1 p1ha1 speech therapy/
   p1ia1 p1ia1 day care or day hosp/
   p1ja1 p1ja1 soc worker in home.
*means tables= hosp2 by p1aa1 p1ba1 p1ca1 p1da1 p1ea1 p1fa1 p1ga1 p1ha1 p1ia1 p1ja1.

*means tables= hosp2 by p1aa1_2 by p1aa1 
means tables= hosp2 by p1ba1_2 by p1ba1 
means tables= hosp2 by p1ca1_2 by p1ca1 
means tables= hosp2 by p1da1_2 by p1da1 
means tables= hosp2 by p1ea1_2 by p1ea1 
means tables= hosp2 by p1fa1_2 by p1fa1 
means tables= hosp2 by p1ga1_2 by p1ga1 
means tables= hosp2 by p1ha1_2 by p1ha1 
means tables= hosp2 by p1ia1_2 by p1ia1 
means tables= hosp2 by p1ja1_2 by p1ja1.


*means tables= hosp2 by hospriska
   /statistics

*frequencies variables= hospriska




*frequencies variables=hosp2.
 
*select if not missing(hosp2).

*frequencies variables=hosp2.

recode hosp1  j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd k8a
    k8c h3 j1nd  (missing=0).


*frequencies variables= hosp2    k8c k8a k8b k8e j1wd fallany j1nd j1od j1bd j1xd l1a  l2a l2b l2c k2e n2a1 n3d h3 i2b infuse p2a p2g
     j1zd j1ld cc5234 
       h7a j1ud n2b1 p2j p62 n1 l2b l2c j1ad e1a12 e1e12 e1i12 f212 n3c lessions p4b1 frail20 j1aad. 


*logistic regression hosp2 with    k8c k8a k8b k8e j1wd fallany j1nd j1od j1bd j1xd l1a  l2a l2b l2c k2e n2a1 n3d h3 i2b infuse p2a p2g
     j1zd j1ld cc5234 
       h7a j1ud n2b1 p2j p62 n1 l2b l2c j1ad e1a12 e1e12 e1i12 f212 n3c lessions p4b1 frail20 j1aad 
    /method enter
      j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1   l1a n5c n2a1 j1nd 
    k8a   n2b1 
    /method fstep  j1ed  k8c  k8b k8e j1bd l2a l2b l2c k2e n3d h3 i2b 
   /external.  



**temporary
  select if  hosp1 eq 0
  crosstabs tables= hosp2 by n5c
    /cells=count row col tot  
     /statistics= chisqur risk
**

**temporary
  select if  hosp1 gt 0 
  crosstabs tables= hosp2 by  j1bd j1zd k8a j1bd infuse p2g j1aad  n2b1
    /cells=count row col tot  
     /statistics= chisqur risk
**



**logistic regression hosp2 with   
    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd  p2j n1 e1a12 cc5234 infuse p2g l2a l2b  
     j1aad j1ad j1ud j1wd k3c l1a k3a j1ed e1a12 e1d12 e1e12 p2a l2b k8c n5c 
     male k8a j1ld n2a1  cps26 cps234 frail20
   /method enter j1bd j1zd k8a infuse p2g j1aad 
    /method fstep
   j1wd p62 n2b1 n3c lessions fallany j1od j1xd  p4b1      male j1ed l1a n5c n2a1
    j1nd j1ld j1ud k3c k8a k8c k8e n4 n5c
   /external  
   
**temporary
  select if hosp1 gt 0
  means tables= hosp2 by predhosp1 by hosp

**temporary
  select if  hosp1 gt 0
  logistic regression hosp2 with   
     k8c k8a k8b k8e j1wd fallany j1nd j1od j1bd j1xd l1a  l2a l2b l2c k2e n2a1 n3d h3 i2b infuse p2a p2g
     j1zd j1ld cc5234 
       h7a j1ud n2b1 p2j p62 n1 l2b l2c j1ad e1a12 e1e12 e1i12 f212 n3c lessions p4b1 frail20 j1aad 
    /method enter
     j1bd j1zd k8a infuse p2g l2a j1aad 
    /method fstep   k8c  p4b1 p62  frail20  n2b1
   /external  



count predHOSP0 =    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd ( 1).
recode  predhosp0 (8 thru high=8).
count predHOSP1 =   j1bd j1zd k8a infuse p2g j1aad  n2b1 (1).
**
temporary
select if hosp1 gt 0
means hosp2 by predhosp1 by h2a h2b h2c h2d h2e h2f h2g h2h h2i  h2j h3 h5 





*logistic regression hosp2 with   
     k8c k8a k8b k8e j1wd fallany j1nd j1od j1bd j1xd l1a  l2a l2b l2c k2e n2a1 n3d h3 i2b infuse p2a p2g
     j1zd j1ld cc5234 
       h7a j1ud n2b1 p2j p62 n1 l2b l2c j1ad e1a12 e1e12 e1i12 f212 n3c lessions p4b1 frail20 j1aad 
    /method enter
      j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd ( 1)
    k8a   n2b1 
    /method fstep   k8c  k8b k8e j1bd l2a l2b l2c k2e n3d h3 i2b jjjjjjjjjjjj 
   /external.  


  *  j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd ( 1)
    k8a   n2b1 .



count clinicalCOMPLEX= h3(1), I2b(1), j1b(1,2,3), j1c(1,2,3) j1n (1,2,3), j1o (1,2,3), j1u (1,2,3), j1w (1,2,3), 
    j1z (1,2,3), j1aa (1,2,3), k2a (1), k2c (1), k2e (1), k3a (1), k3b (1), k3c (1), k3e (1), k3f (1), k3g (1), k4b (2,3,4), k6a (1),
    k8b (1), k8c (1), k8e (1), l1a (1), l2c (1), n2a (1,2,3,4,5), n2b (1), n3a (1), n3b (1), n3c (1),  
   n3d (1), p2b (1,2,3), p2f (1,2,3), p2g (1,2,3), p2l (1,2,3).
recode clinicalCOMPLEX (12 thru high=12).



recode p4c (missing=sysmis)(0=0)(1 thru high=1)into p4c1.
recode p4c (0=0)(missing=sysmis)(else=1) intp p4c1/
   q2a q2b q2c q2d (0=0)(missing=sysmis)(else=1)into q2a1 q2b1 q2c1 q2d1.










**crosstabs tables= hosp2 by p1aa1 p1ba1 p1ca1 p1da1 p1ea1 p1fa1 p1ga1 p1ha1 
     /statistics= chisqur risk
    /cells=count row col tot  
 

**crosstabs tables= hosp2 by p1ia1 p1ja1 p2a1 p2n1 p2o1 p2q1 p2r1 p2s1 p2t1 p2u1 p2v1 
     /statistics= chisqur risk
    /cells=count row col tot  
 

**crosstabs tables= hosp2 by p2w1 p2x1 p2y1 p2z1 g2a g2b g2c h6a h6b
     /statistics= chisqur risk
    /cells=count row col tot  
 

 





*means tables= hosp2  by state.
*means tables= hosp2  by sourcen.


*temporary.
*select if not missing(hosp2).
*frequencies variables= divert hospriska.


compute PerHOSP2=$sysmis.
if (hosp2 gt 0 or ed2 gt 0)perHOSP2=0.
if (perHOSP2 eq 0 and hosp2 gt 0)perHOSP2=1.









recode p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja (0=0)(missing=sysmis)(else=1) into
    p1aa1 p1ba1 p1ca1 p1da1 p1ea1 p1fa1 p1ga1 p1ha1 p1ia1 p1ja1.

recode p1aa_2 p1ba_2 p1ca_2 p1da_2 p1ea_2 p1fa_2 p1ga_2 p1ha_2 p1ia_2 p1ja_2 (0=0)(missing=sysmis)(else=1) into
    p1aa1_2 p1ba1_2 p1ca1_2 p1da1_2 p1ea1_2 p1fa1_2 p1ga1_2 p1ha1_2 p1ia1_2 p1ja1_2.

variable labels  p1aa1 p1aa1  home health aides/
   p1ba1 p1ba1 visiting nurses/
   p1ca1 p1ca1 homemaking services/
   p1da1 p1da1 meals/
   p1ea1 p1ea1 volunteer services/
   p1fa1 p1fa1 physical therapy/
   p1ga1 p1ga1 occupational therapy/
   p1ha1 p1ha1 speech therapy/
   p1ia1 p1ia1 day care or day hosp/
   p1ja1 p1ja1 soc worker in home.


if (missing(p2v)) p2v=p2w.
do if missing(p2v).
recode p1ba (0=0)(1 thru high=1)(missing=sysmis)into p2v.
end if.
do if Missing(p2v).
recode in3ba (0=0)(1 thru high=1)into p2v.
end if .

recode p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2a_2 p2b_2 p2c_2 p2d_2 p2e_2 p2f_2 p2g_2 p2h_2 p2i_2 p2j_2 p2k_2 p2l_2 (0=0)(missing=sysmis)(else=1)into 
   p2a1 p2b1 p2c1 p2d1 p2e1 p2f1 p2g1 p2h1 p2i1 p2j1 p2k1 p2l1 
   p2a1_2 p2b1_2 p2c1_2 p2d1_2 p2e1_2 p2f1_2 p2g1_2 p2h1_2 p2i1_2 p2j1_2 p2k1_2 p2l1_2 .

recode p2m p2n p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z (0=0)(missing=sysmis)(else=1) into
  p2m1 p2n1 p2o1 p2p1 p2q1 p2r1 p2s1 p2t1 p2u1 p2v1 p2w1 p2x1 p2y1 p2z1/.

recode p2m_2 p2n_2 p2o_2 p2p_2 p2q_2 p2r_2 p2s_2 p2t_2 p2u_2 p2v_2 p2w_2 p2x_2 p2y_2 p2z_2 (0=0)(missing=sysmis)(else=1) into
  p2m1_2 p2n1_2 p2o1_2 p2p1_2 p2q1_2 p2r1_2 p2s1_2 p2t1_2 p2u1_2 p2v1_2 p2w1_2 p2x1_2 p2y1_2 p2z1_2 /.

Recode p4a p4b p4c  p4a_2 p4b_2 p4c_2 (0=0)(1 thru high=1)into p4a19 p4b19 p4c19 p4a19_2 p4b19_2 p4c19_2.


Recode p4a p4b p4c  (0,1=0)(2 thru high=1)into p4a29 p4b29 p4c29.
recode in2c in2g in2k in2l in2m in2n in2d (missing=sysmis)(0=0)(1 thru high=1) into
   in2c1 in2g1 in2k1 in2l1 in2m1 in2n1 in2d1 .
recode p3a p3b p3c p3d (missing=sysmis)(0,1=0)(2 thru high=1)into p3a2 p3b2 p3c2 p3d2.
variable labels  p2a1 p2a1 oxygen/
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
  p2z1  p2z1 special diet/
  p4a19 p4a19 hosp admit/
  p4b19 p4b19 er visit/
  p4c19 p4c19 emergent care.

variable labels   in2c1 in2c1 infection control/
   in2g1 in2g1 suctioning/
   in2k1 in2k1 wound care/
   in2l1 in2l1 scheduled toileting/
   in2m1 in2m1 palliative care/
   in2n1 in2n1 turning, positioning/
   in2d1 in2d1 iv meds .
variable labels p3a2 presence oxygen/
  p3b2 p3b2 presence iv with help /
  p3c2 p3c2 presence catheter with help/
  p3d2 p3d2 presence ostomy with help /
var labels p4a19 p4a19 one plus hosp admit /
  p4b19 p4b19 one plus er visit /
  p4c19 p4c19 one plus emergent care/
  p4a29 p4a29 two plus hosp admits/
 p4b29 p4b29 two plus er visits/
  p4c29 tp4c29 wo plus emergent care/.

recode   n5a n5b n5c n5d n5a_2 n5b_2 n5c_2 n5d_2 (0=0)(1=1)(else=sysmis).
 
** HC FRAILTY SCALE -- labelled   HCFRt1.
count  HCFRt1=  h1ba (2,3) h1aa (2,3) h1aa (1,2,3) h1ea (1,2,3) h2i (2,3,4,5,6) h2c (3,4,5,6) 
    h2b (4,5,6) h2h (2,3,4,5,6) h5 (1,2) h6b (1) k5 (1 thru high) k3c (1)
    b2a (1,2,3,4, 5) h1da (2,3) h1ca (1,2,3)  j1h (1,2) c3 (1,2,3,4) f2 (1,2) f2 (2) e1i (1,2) e1h (1,2)
    l1a (1) l2a (1) l2b (1) i3 (2,3,4,5) j1w (1,2) j1u (1,2) j1b (1,2) j1z (1,2) p2g (1,2).
recode  HCFRt1 (24 thru high=24).
count  HCFRt1miss= h1ba  h1aa  h1aa h1ea  h2i  h2c  
    h2b  h2h  h5  h6b  k5 k3c 
    b2a h1da h1ea  j1h  c3  f2  f2  e1i  e1h 
    l1a  l2a  l2b  i3  j1w  j1u  j1b  j1z  p2g(missing).
if ( HCFRt1Miss gt 4) HCFRt1=$sysmis.

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

 
**means tables=  HCFRt1 by cWHOLE
   /statistics


** CAP TEST

**   OLD BLADDER CAP
**
**   BEGINNING BLADDER CAP July 2007
**
compute bladcap=$sysmis 
**
     B2a     Decision making
     K2a     Diarrhea
     I1a       Bladder continence
     I2b       Indwelling catheter
     J1u       Pneumonia
     J1n       Hip fracture
     H2c      Walk in room
     H3       ADL decline

count itemx=   k2a i2b (1) j1u j1n (1,2) 
     H3 (1).
if (missing(k2a) and missing(j1u) and missing(h3))itemx=$sysmis.
if (missing(bladcap) and b2a eq 4)bladcap=0.
if (missing(bladcap) and any(i1a,0,1))bladcap=1. 
**if (any(i1a,2,3,4,5,8) and (b2a lt 2 and h2c lt 4) 
       and aa0h3a eq 0)bladcap=3 .
** if (any(i1a,2,3,4,5,8) and (b2a lt 2 and h2c lt 4) 
       and aa0h3a eq 1 and itemx gt 0)bladcap=3 .
if (any(i1a,2,3,4,5,8) and (b2a lt 2 and h2c lt 4) 
       and itemx gt 0)bladcap=3. 
if (missing(bladcap) and b2a lt 4)bladcap=2.
value labels bladcap (0)pr cog (1)no prob (2)prv dec (3)fac imp.
var labels bladcap bladder cap July 2007 home care versiop.
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
if (bladt1 gt 1 and not missing(bladt2))chgCONT=0.
if (chgCONT eq 0 and bladT2 lt 2)chgCONT=1.
var labels chgCONT from incontinent to continent.

Compute chgINCONT = $sysmis.
if (bladt1 LT 4  and not missing(bladt2))chgINCONT=0.
if (chgINCONT eq 0 and bladT2 gt 3)chgINCONT=1.
var labels chgINCONT from continent to INcontinent.

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


count bladIMPcap2023= f2 (1,2) h1da (0) h2d (1) h2e (1)  h2j (1) h4a (0,1) h7a (1)  i2b (1) k3c (1) k4a (2,3) k6a(1) k8a(1) m1a(1).
if (( Ii1a eq 1 or b1a eq 4) and bladIMPcap2023 gt 0)bladIMPcap2023=0.
if (missing(i1a) or i1a gt 5) bladIMPcap2023=$sysmis.

**recode bladIMPcap2023 (0 thru 4=0)(5 thru high=1)
***frequencies variables= bladIMPcap2023



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
**

*frequencies variables= hcmiss
    /statistics.


count presentT2= b1a_2 b2a_2 c1_2 c2_2 d1_2 h1aa_2 h2a_2  i1a_2 j1g_2 (low thru high).
recode presentT2 (1 thru high=1)(0=0)into T2case .
count presentT1= b1a b2a c1 c2 d1 h1aa h2a  i1a j1g (low thru high).
recode presentT1 (0=0)(1 thru high=1)into T1case.



*select if (HCmiss lt 51)  and (a1y gt 1999 or missing(a1y)).


** recode so pre Icode will fit into Icode
**
compute HRSthree=$sysmis
do if g3a lt 800 and g3b lt 800
. compute HRSthree= g3a+g3b
. compute HRSthree= rnd (HRSthree/7)
. compute HRSthree= rnd (HRSthree * 3)
end if

recode bb4 (1=1)(2=2)(3=4)(4=5)(5=6)(6=3)(else=sysmis) into marital /
   cc4 (0=0)(1=4)(2=3)(3=2)(4=1)into priorHS /
   cc5 (1=1)(2=1)(3=2)(4=9)(5=14)into residence /
   cc6  (1=1)(2=2)(3=3)(4=4)(5=7)(6=8)into LIVEwith /
   b2b (missing=sysmis)(2=1)(else=0)into DECISIONworse/
   b3a (missing=sysmis)(1=2)(else=0)into ATTENTION / 
   c1 (missing=sysmis)(0=0)(1=1)(2=3)(3=4) into hear/
   e1a e1b e1c e1d e1e e1f e1g e1h e1i (missing=sysmis)(0=0)(1=2)(2=3) into  sadness anger unrealistic health anxious
     sad crying withdrawal reduced / 
    e3a e3b e3c e3d e3e (0=0)(1=2)(2=3) into wander verbal physical social resists /   
    g1ea  (0=1)(1=0) (2=2)(missing=sysmis)into LIVEcl/
    g1fa (0=0)(1=1)(else=sysmis)into LIVEwth/ 
    g1ha g1ia (0=0)(1=1)(missing=sysmis)into IADLcare ADLcare/ 
    g2a g2c  (0=0)(1=1)(else=sysmis)  into NOTcont CAREdis /.
   


recode h2a h2b h2c  h2d h2e h2f h2g h2h  h2i h2j 
  h2a_2 h2b_2 h2c_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
  ig2a ig2b ig2c ig2d ig2e ig2f ig2g ig2h ig2i ig2j  
   ig2a_2 ig2b_2 ig2c_2 ig2d_2 ig2e_2 ig2f_2 ig2g_2 ig2h_2 ig2i_2 ig2j_2 (8=4)(9 thru high=sysmis). 



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

**frequencies variables = h2a h2b h2c h2c_2 h2cxx h2d h2e h2f h2g h2h  h2i h2j 
    h2a_2 h2b_2 h2c_2 h2cxx_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
    /statistics
**correlation variables = h2a h2b h2c h2cxx h2d h2e h2f h2g h2h  h2i h2j 
     

do repeat x1= h2a h2b h2c   h2e h2f h2g h2h  h2i h2j
  h2a_2 h2b_2 h2c_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 /
   y1= ig2i ig2g ig2f  ig2c ig2d ig2j ig2h ig2b ig2a                 
    ig2i_2 ig2g_2 ig2f_2  ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2/.
if (missing(x1))x1=y1.
if (missing(y1))y1=x1.
end repeat.   
**
**frequencies variables=h2a h2b h2c   h2e h2f h2g h2h  h2i h2j
  h2a_2 h2b_2 h2c_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 
    ig2i ig2g ig2f  ig2c ig2d ig2j ig2h ig2b ig2a                 
    ig2i_2 ig2g_2 ig2f_2  ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2.
 
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
variable labels tothrs hrs total care seven days. 

compute anypsy= ii1n.
if (ii1w gt 0 or ii1o gt 0 or ii1p gt 0)anypsy=1.

do repeat mdshc = j1a j1b j1c 
        j1g j1h  j1j j1k j1l  j1n 
        j1o j1s  j1u 
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

variable labels dk3b dk3b no bowel movmnt 3 days no v y.
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

do if missing(n3d). 
recode in2k (0=0)(missing=sysmis)(else=1)into n3d.
end if.

recode ij2m ij2f ij2a ij2b ij2g ij2o ij2p ij4  (0 thru 1=0)(2 thru high=1)(missing=sysmis)into 
  ij2mD ij2fD ij2aD ij2bD ij2gD ij2oD ij2pD ij4D.
recode k3e k4d k4e k9e ij2j ij2r (0=0)(1 thru high=1)(missing=sysmis)into 
  k3eD k4dD k4eD k9eD ij2jD ij2rD.  



variable labels  ij2mD ij2mD acid reflux no vs yes /
   ij2fD ij2fD airway secretion no vs yes /
  k3eD k3eD sob no vs yes /
  k4dD k4dD character pain no vs yes /
 k4eD k4eD meds control pain no vs yes /
   k9eD k9eD restrained  no vs yes /
   ij2aD ij2aD move to stand  no vs yes /
   ij2bD ij2bD turn  no vs yes /
   ij2gD ij2gD abnormal thoughts  no vs yes /
   ij2jD ij1jD Aphasia  no vs yes /
  ij2oD ij2oD difficulty sleeping  no vs yes /
   ij2pD ij2pD too much  sleep  no vs yes /
   ij2rD ij2rD bleeding  no vs yes /
   ij4D ij4D fatigue  no vs yes /.

recode k1b (1 thru high=1).


do if missing(q4).
recode im3 (missing=sysmis)(0=0)(1=1)(2=2)(8=3)into q4.
end if.

recode k5 k5_2 (0=0)(0 thru 1=1)(1 thru high=2).
recode ij1 ij1_2 (0=0)(0,1,2=1)(2 thru 3=2).
compute fall_1=k5.
if (missing(fall_1))fall_1=ij1.
if (missing(fall_1))fall_1=ij12.
compute fall_2=k5_2.
if (missing(fall_2))fall_2=ij1_2.
if (missing(fall_2))fall_2=ij12.

**frequencies variables= fall_1 ij1 ij12 k5 k5_2

if (age lt 1) age=$sysmis.
if (age gt 111)age=$sysmis.
recode age (low thru 64=1)(65 thru 74=2)(75 thru 79=3)(80 thru 84=4)(85 thru 89=5)(90 thru 94=6)(95 thru high=7)into agecats.
**.
compute gender=bb1.
if (missing(gender)) gender=ia2.
recode gender (missing=1)(else=0) into gendermiss.


compute adlDEC= h3.
recode ig8a (missing=sysmis)(2=1)(else=0)into xxdown.
if (missing(adlDEC))adldec=xxdown.  
recode adlDEC (missing=1)(else=0) into adldecmiss. 

compute fallyes= k5.
recode ij1 (0=0)(1 thru high=1)into xxfall.
if (missing(fallyes))fallyes=xxfall.
recode fallyes (missing=1)(else=0) into fallyesmiss.

if (missing(g2a))g2a=ip2a.

recode p4a p4a_2 p4b p4b_2 in5a in5a_2 in5b in5b_2 (160 thru high=sysmis).
if (missing(p4a))p4a=in5a.
if (missing(p4a_2))p4a_2=in5a_2.
if (missing(p4b))p4b=in5b.
if (missing(p4a_2))p4b_2=in5b_2.



**.
compute hosed=0.
if (missing(p4a) and missing(p4b) and missing(cc4))hosed=$sysmis.
do if hosed eq 0.
compute xvisit=p4a+p4b.
if (missing(xvisit) and not missing(p4a))xvisit=p4a.
if (missing(xvisit) and not missing(p4b))xvisit=p4b.
if (xvisit eq 0 and cc4 gt 0)xvisit=1.
recode xvisit (0=0)(1=1)(2=2)(3=3)(4 thru high=4)into hosed.
end if.

recode  bb1  bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c  h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z  p4c p5 p6 p7
    (10 thru high=sysmis).
recode  g3a g3b age (999 thru high=sysmis).
recode h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j H2a_2 h2b_2 h2c_2 h2d_2 h2e_2 h2f_2 h2g_2 h2h_2 h2i_2 h2j_2 (9 thru high=sysmis).
**frequencies variables =   bb1 age bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c g3a g3b h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4a p4b p4c p5 p6 p7




recode ih2 (missing=sysmis)(2=1)(else=0)into cathFILL.
if (missing(i2b))i2b=cathFILL.
recode k5 (0=0)(1 thru high=1)(missing=sysmis)into fellone.
recode ij1 (missing=sysmis)(0=0)(1 thru high=1)into xxFILL.
if (missing(fellONE))fellONE= xxfill.
recode ij12 (0=0)(1=1)(else=sysmis) into xxfill.
if (missing(fellONE))fellONE=xxfill.

recode k5 (0,1=0)(2 thru high=1)(missing=sysmis)into felltwo.
recode ij1 (missing=sysmis)(0,1,2=0)(3 thru high=1) into xxFILL.
if (missing(felltwo))felltwo= xxfill.
recode ij12 (0,1=0)(else=sysmis)into xxfill.
if (missing(felltwo))felltwo=xxfill.

recode ij2h (missing=sysmis)(0=0)(1 thru high=1)into xxFILL.
if (missing(k3f))k3f=xxfill.


** fill in missing with icodes
do repeat
    x1= bb1 cc8 p7 p5 k9e /
    fill=ia2 ib5a iq4 ir1 in4  /
if (missing(x1))x1=fill
end repeat

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
recode ik3 (missing=sysmis)(5,6=1)(else=0) into fill.
if (missing(l2d))l2d=fill.
recode ik3 (missing=sysmis)(0,1=0)(2=1)(3,4=2)(5=3)(6 thru high=4) into fill.
if (missing(l3))l3=fill.
count skin_a=il1 il3 il4 il5 il6 (1 thru high).
recode skin_a (1 thru high=1).
if (skin_a eq 0 and missing(il1) and missing(il3) and missing(il4) and missing(il5) and missing(il6))skin_a=$sysmis.
if (missing(n1))n1=skin_a.
recode il4 (missing=sysmis)(0=0)(1 thru high=1) into fill.
if (missing(n3b))n3b=fill.
recode il7 (0=0)(1 thru high=1) into fill.
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
recode in2i (0=0)(2,3=1)(1=3) into fill.
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

** CREATE ADL HIERARCHY 
**
**  locomotion substituted for walking
     eating substituted for bed mobility
     toilet use substiruted for transfer.
do repeat  ig2b  = ig2b ig2b_2/
           ig2g  = ig2g ig2g_2/
           ig2e  = ig2f ig2f_2/
           ig2i  = ig2j ig2j_2/
           ze1g  = ze1g xe1g/
           ze1f  = ze1f xe1f/
           ze1c  = ze1c xe1c/
           ze1e  = ze1e xe1e/
           early = early pearly/ 
           mid   = mid pmid/
           late  = late plate/
           adlh  = adlhfill adlhfill_2 /
            xx   = xx zz/ 
         aa= aa bb/
         ig2bfill= h2i h2i_2/ 
         ig2gfill= h2b h2b_2/
         ig2efill= h2c h2c_2 /
         ig2ifill =h2g h2g_2/
         ig2eTOIL= h2h h2h_2/
         h2htoil=ig2h ig2h_2/.
if (missing(ig2b))ig2b=ig2bfill.
if (missing(ig2g))ig2g=ig2gfill.
if (missing(ig2e))ig2e=ig2efill.
if (missing(ig2i))ig2i=ig2ifill.     
if (missing(ig2g))ig2g=ig2eTOIL.
if (missing(ig2g))ig2g=h2htoil.
if (missing(ig2bfill))ig2bfill=ig2b.
if (missing(ig2gfill))ig2gfill= ig2g.
if (missing(ig2efill))ig2efill=ig2e.
if (missing(ig2ifill))ig2ifill=ig2i.  
recode ig2b ig2g ig2e ig2i 
     (0,1=0)(2=1)(3=2)(4,5=3)(6,8=4) 
     (else=sysmis) into ze1g ze1f ze1c ze1e .
compute early = ze1g .
compute mid = ze1c .
compute late = ze1e . 
compute xx = early+mid+late+ze1f.
compute aa=xx.
** new patch dec 2011 JNM
     This excludes strange cases where folks seems not to walk but are good in everything else.
do if xx lt 9. 
Recode mid late (4=0).
end if. 
** new patch dec 2011 JNM.
compute xx = early+mid+late+ze1f.
compute adlh=$sysmis.
if (xx < 16 & (mid = 4 or  late = 4)) adlh = 5 .
Do if missing(adlh) .
if (xx < 16 & (mid = 3 | late = 3)) adlh = 4 .
End if.
if (late < 3 & mid<3 & (early>2 |ze1f>2)) adlh = 3.
if ((late<3 & mid<3 & early<3 & ze1f<3) & (late = 2 |mid=2 |early=2 |ze1f=2)) adlh = 2 .
if (late < 2 & mid<2 & early<2 & ze1f<2) adlh = 1 .
if (xx=0 & ze1f=0 & early=0) adlh = 0 .
if xx=16 adlh = 6.
End repeat .

variable labels 
     adlhfill '(adlh) adl hierarchy 0-6 baseline revised dec 2011'/
     adlhfill_2  '(adlh) follow-up adl hierarchy 0-6'.
value labels adlhfill adlhfill_2
 0 '(0) all zero' 
 1 '(1) supervision' 
 2 '(2) limited'
 3 '(3) early 3-4' 
 4 '(4) mid late 3'
 5 '(5) mid late 4' 
 6 '(6) all four' /.

**frequencies variables= aa bb  adlh adlh2 adlhfill adlhfill_2 h2c ig2e h2g ig2i h2h ig2g h2i ig2b

**correlation  variables adlh adlh2 adlhfill adlhfill_2

if (missing(adlh))adlh=adlhfill.
if (missing(adlh2))adlh2 = adlhfill_2.


**frequencies variables adlh adlh2 adlhfill adlhfill_2
**correlation  variables adlh adlh2 adlhfill adlhfill_2

compute adlCHG= adlh2-adlh.
recode adlchg (low thru -1=1)(0 thru high=0)into ADLimp.
recode adlchg (low thru 0=0)(1 thru high=1)into adlDEC.
if (adlh eq 0)adlimp=$sysmis.
if (adlh eq 6)adldec=$sysmis.

**frequencies variables= adlIMP adlDEC




**  check for missing vars by state coutry province groups
**frequencies variables= commonMISS
 bb1 age bb4  cc4  cc5  cc6 cc7 cc8 a2 b1a b1b b2a b2b b3a b3b c1 c2 c3 d1  e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e 
 f1b f2 f3a f3b g1ea g1fa g1ha g1ia g2a g2b g2c g3a g3b h1ab h1bb h1cb h1db h1eb h1fb h1gb   
  h2a h2b h2c h2d h2e h2f h2g h2h h2i h2j  h3 h4a h4b h5 h6a h6b h7a h7b i1a i2a i2b i3 
  j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u j1v j1w j1x j1z j1aa j1ab
  k1a k1b k1c k1d k2a k2c k2d k2e k3a k3c k3d k3e k3f k3g k4a k4b k4e k5 fellone k6a 
  k7a k7b k7c k8a k8b k8c k8d k8e  k9a k9b k9c k9d k9e l1a l2c l2d l3 m1a  m1b 
  n1 n2a n2b n3b  n3c n3e  n4 n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b
   p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja 
   p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n
    p2o p2p p2q p2r p2s p2t p2u p2v p2w p2x p2y p2z p4a p4b p4c p5 p6 p7 

do repeat
   mdshc= h1ab h1bb h1cb h1db h1eb h1fb h1gb  h1ab_2 h1bb_2 h1cb_2 h1db_2 h1eb_2 h1fb_2 h1gb_2   h1ab_3 h1bb_3 h1cb_3 h1db_3 h1eb_3 h1fb_3 h1gb_2  /
   icode= ig1ab ig1bb ig1cb ig1db ig1eb ig1gb ig1hb  ig1ab_2 ig1bb_2 ig1cb_2 ig1db_2 ig1eb_2 ig1gb_2 ig1hb_2  ig1ab_3 ig1bb_3 ig1cb_3 ig1db_3 ig1eb_3 ig1gb_3 ig1hb_3/.
do if missing(mdshc).
recode icode (0,1,2=0)(3,4,8=1)(5,6=2)into mdshc.
end if.
end repeat.
**  Mich amd maryland each missing about 90000 at baseline  why?  oct 2021

do repeat
   mdshc= h2a h2b h2c  h2e h2f h2g h2h  h2i h2j  h2a_2 h2b_2 h2c_2  h2e_2 h2f_2 h2g_2 h2h_2  h2i_2 h2j_2
        h2a_3 h2b_3 h2c_3  h2e_3 h2f_3 h2g_3 h2h_3  h2i_3 h2j_3 /
    icode = ig2i ig2g ig2f ig2c ig2d ig2j ig2h ig2b ig2a ig2i_2 ig2g_2 ig2f_2 ig2c_2 ig2d_2 ig2j_2 ig2h_2 ig2b_2 ig2a_2 
        ig2i_3 ig2g_3 ig2f_3 ig2c_3 ig2d_3 ig2j_3 ig2h_3 ig2b_3 ig2a_3 /.
if (missing(mdshc))mdshc=icode.
end repeat.


do repeat locorig = h2c h2c_2 h2d h2d_2/
    locNEW= locI locI_2 locO locO_2/
    gait= k6a k6a_2 k6a k6a_2/
    mode= h4a h4a_2 h4a h4a_2.
compute locnew=locorig.
recode locnew (8=4).
compute locnew=locnew+1.
do if (locnew eq 1).
if (gait eq 0 and mode lt 2)locnew =0.
end if.
end repeat.

variable labels   locI new locomotion inside t1/
    locI_2 new locomotion inside t2/
    locO new locomotion outside t1/
    locO_2 new locomotion outside t2/.
value labels   locI locI_2 locO locO_2
    (0)ind and gait ind and no walkr or wheelchair
    (1)inp othr er (2) set up help (3) supervision (4)limit ass
    (5)exten ass (6) max assist (7)tot dep.

count ambxx= k6a (0) h4a(0,1).
if (missing(K6a) and missing(h4a))ambxx=$sysmis.
 
compute walkIMp = locI_2.
recode walkIMP (low thru high=0).
if (locI_2 lt locI) walkIMP=1.
if (locI eq 0) walkimp=$sysmis.
variable labels walkIMP  improvement in walking performance on new measure.



compute walkDEc = locI_2.
recode walkDEC (low thru high=0).
if (locI lt locI_2) walkDEC=1.
if (locI eq 7) walkDEC=$sysmis.
variable labels walkDEC  decline in walking performance on new measu.

**frequencies variables= walkimp walkdec
  crosstabs tables= walkimp walkdec by loci
   /cells=count row col tot


**frequencies variables= walkimp adlimp walkdec adldec

**crosstabs tables=  walkimp by adlimp 
    / cells=count row col TOT  
     /statistics= chisqur risk
**crosstabs tables= walkdec by adldec
    / cells=count row col TOT  
     /statistics= chisqur risk

count iadl2s_2= h1ab_2 h1bb_2 (2).
if (missing(h1ab_2) and missing(h1bb_2))iadl2s_2=$sysmis.

count iadl2s= h1ab h1bb (2).
if (missing(h1AB) and missing(h1bb))iadl2s=$sysmis.
  

recode iadl2s_2 (0,1,2,3=0)(4=0)into iadlIMP.
if (iadl2s_2 lt iadl2s ) iadlimp=1.
if (iadl2s eq 0)iadlimp=$sysmis.  
var labels iadlimp improvement in capacity iadl meal prep and housework.

compute iadlalt= h1ab + h1bb.
compute iadlalt_2= h1ab_2 + h1bb_2.
compute iadlaltimp= iadlalt_2 - iadlalt.
if (iadlalt eq 0)iadlaltimp=$sysmis.
recode iadlaltimp (low thru -1=1)(missing=sysmis)(else=0).

**
** rEPLACE MISSING adl CODE VALUES
recode h2a h2b h2c  h2e h2f h2g h2h  h2i h2j (0=0)(1=1)(2=2)(3=3)(4,8=4)(5=5)(6=6) into
    h2a_a h2b_a h2c_a  h2e_a h2f_a h2g_a h2h_a  h2i_a h2j_a
do repeat
   item1=h2a_a h2b_a h2b_a h2b_a h2b_a h2b_a h2e_a h2b_a /
   item2=h2c_a  h2f_a h2f_a h2e_a h2e_a h2e_a h2f_a h2g_a / 
   item3= h2f_a   h2i_a h2i_a h2i_a h2i_a  h2f_a h2i_a h2c_a  /
   miss1= tran_1  loco_1 upper_1 lower_1 eat_1 hyg_1 bath_1 bed_1 /
   fill= tran_a  loco_a upper_a lower_a eat_a hyg_a bath_a bed_a/
count miss1= item1 item2 item3 (missing)
compute fill=$sysmis
do if (miss1) lt 3
. compute fill=sum (item1,item2,item3)
. compute fill=rnd(fill/(3-miss1))
end if
end repeat

if (missing(h2b_a))h2b_a=tran_a.
if (missing(h2c_a))h2c_a=loco_a.
if (missing(h2e_a))h2e_a=upper_a.
if (missing(h2f_a))h2f_a=lower_a.
if (missing(h2g_a))h2g_a=eat_a. 
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


** rEPLACE MISSING adl CODE VALUES
recode h2a_2 h2b_2 h2c_2  h2e_2 h2f_2 h2g_2 h2h_2  h2i_2 h2j_2 (0=0)(1=1)(2=2)(3=3)(4,8=4)(5=5)(6=6) into
    h2a_b h2b_b h2c_b  h2e_b h2f_b h2g_b h2h_b  h2i_b h2j_b
do repeat
   item1=h2a_b h2b_b h2b_b h2b_b h2b_b h2b_b h2e_b h2b_b /
   item2=h2c_b  h2f_b h2f_b h2e_b h2e_b h2e_b h2f_b h2g_b / 
   item3= h2f_b   h2i_b h2i_b h2i_b h2i_b  h2f_b h2i_b h2c_b  /
   miss1= tran_1  loco_1 upper_1 lower_1 eat_1 hyg_1 bath_1 bed_1 /
   fill= tran_b  loco_b upper_b lower_b eat_b hyg_b bath_b bed_b/
count miss1= item1 item2 item3 (missing)
compute fill=$sysmis
do if (miss1) lt 3
. compute fill=sum (item1,item2,item3)
. compute fill=rnd(fill/(3-miss1))
end if
end repeat

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
**end replace missing adl numbers for followup 1 or time 2
**

recode h2c_a h2c_b (0,1=0)(2 thru 5=1)(6 thru high=2)into loc_1 loc_2.
compute LOC_d=loc_2-loc_1.
recode loc_d (low thru 0=0)(1 thru high=1).
if (loc_1 eq 2)loc_d=$sysmis.
variable labels loc_d locomotion decline.
value labels loc_d.
**frequencies variables=loc_d.


**recode h2a_a h2c_a h2j_a h2a_b h2c_b h2j_b  (0,1=0)(6=2)(2 thru high=1)into bed_1 loc_1 bath_1 bed_2 loc_2 bath_2


**create delirium measure
count del_1= b3a b3b (1) ic3a ic3b ic3c (2) ic4(1)
count del_2= b3a_2 b3b_2 (1) ic3a_2 ic3b_2 ic3c_2(2) ic4_2(1)
recode del_1 del_2 (1 thru high=1)
if (del_1 eq 0 and missing(b3a) and missing(b3b) and missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1=$sysmis
if (del_2 eq 0 and missing(b3a_2) and missing(b3b_2) and missing(ic3a_2) and missing(ic3b_2) and missing(ic3c_2) and missing(ic4_2))del_2=$sysmis
var labels del_1 delirium time 1
var labels del_2 delirium time 2
 
**frequencies variables= del_1 del_2 delcap 
**frequencies variables= b3a b3b  ic3a ic3b ic3c  ic4
**crosstabs tables=del_1 by del_2 
   /cells=count row col tot
**

**if (del_1a eq 0 and missing(b3a) and Missing(b3b))del_1a=$sysmis
  if (del_1b eq 0 and missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1b=$sysmis
  if (del_1c eq 0 and missing(b3a) and missing(b3b) and missing(ic3a) and missing(ic3b) and missing(ic3c) and missing(ic4))del_1c=sysmis

**frequencies variables= b3a b3b ic3a ic3b ic3c ic4 del_1a del1_b del1_c
**frequencies variables= h3 ig8a h5 ig1fb h7a ig7a

do if missing(h3).
recode ig8a (2=1)(0,1,3=0)into h3.
end if.
do if missing(h5).
recode ig1fb  (0,1,2=0)(3=1)(4,5,6,7,8=2)into h5.
end if.
do if missing(h7a).
recode ig7a (0=0)(1=1)(else=sysmis)into h7a.
end if.


**frequencies variables=e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e
do repeat
   mdshc = e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e  /
   icode=  ie1a ie1b ie1c ie1d ie1e ie1f ie1g ie1i ie1j ie3a ie3b ie3c ie3d ie3f /
do if missing(mdshc)
. recode icode (0,1=0)(2=1)(3=2)into mdshc
end if
end repeat

recode h7a h7b i2a i2b (1 thru high=1).
recode f2 (0=0)(1,2=1)into f212. 
recode e1a e1b e1c e1d e1e e1f  e1g e1h e1i  e3a e3b e3c e3d e3e 
   f2 f3a ie1f  ie1h ie1k (missing=sysmis)(0=0)(1 thru high=1) into
  e1a12 e1b12 e1c12 e1d12 e1e12 e1f12 e1g12 e1h12 e1i12 
  e3a12 e3b12 e3c12 e3d12 e3e12  f212  f3a13 ie1f13  ie1h12 ie1k12.   

recode ie2a ie2b ie2c if1a if1b if1c if1e if1f if1g  (missing,8=sysmis)(0=0)(1 thru high=1)into ie2a13 ie2b13 ie2c13 
   if1a0 if1b0 if1c0 if1e0 if1f0 if1g0. 
recode  if1a if1b if1c if1e if1f if1g (missing,8=sysmis)(0,1=0)(2 thru high=1) into
    if1a01 if1b01 if1c01 if1e01 if1f01 if1g01. 
recode f2 (missing=sysmis)(2=1)(else=0)into f22.
recode f3a (missing=sysmis)(3=2)(else=0)into f3a3.
recode f3a (missing=sysmis)(0,1=0)(else=1)into f3a23. 
variable labels e1a12 e1a12 sadness  no vs yes /
  e1b12 e1b12 anger no vs yes /
  e1c12 e1c12 fears  no vs yes /
  e1d12 e1d12 health complaints  no vs yes /
  e1e12 e1e12 repetirive complaints  no vs yes /
  e1f12 e1f12 sad facial expressions  no vs yes /
  e1g12 e1g12 crying, tearful  no vs yes /
  e1h12 e1h12 withdrawal  no vs yes /
  e1i12 e1i12 reduced social interactions no vs yes /
  e3a12 e2a12 wandering no vs yes /
  e3b12 e3b12 verbally abusive  no vs yes /
  e3c12 e3c12 physically abusive no vs yes /
  e3d12 e3d12 socially inappropriate  no vs yes /
  e3e12 e3e12 resists care  no vs yes /
  ie2a13 ie2a13 self report little interest no vs yes /
  ie2b13 ie2b13 self report anxious, restless no vs yes /
  ie2c13 ie2c13 self report sad, depressed no vs yes /
  f212 f212 decline social activities no vs yes /
  f22 f22 declined in soc act and distressed  no vs yes /
  f3a13 alone never vs other no vs yes /
  f3a3 f3a3 less all time vs all time no vs yes /
  f3a23 f3a23 not long alone vs long alone no vs yes /
  ie3f13 ie3f13 public sexual behavior no vs yes /.
variable labels  if1a0 if1a0 never vs oth part in act of interest no vs yes /
   if1b0 if1b0 never vs other visit socl relat or family  no vs yes /
   if1c0 if1c0 never vs other other interactions with socl rel or family no vs yes /
   if1e0 if1e0 never vs other conflict or anger  no vs yes /
   if1f0 if1f0 never vs other fearful of family or close frd no vs yes /
   if1g0 if1g0 never vs other neglected, aboused, mistreated no vs yes / 
   if1a01 if1a01 within 30 days part in act or int no vs yes /
   if1b01 if1b01 within 30 days vis soc rel or fam no vs yes /
   if1c01 if1c01 within 30 days oth int wth soc rel or fam no vs yes /
   if1e01 if1e01 within 30 days conflict or anger no vs yes /
   if1f01 if1f01 within 30 days fearful fam mem or close aqu
   if1g01 if1g01 within 30 days neglected, abused, mistreated no vs yes /.


count missadl_a= h2a_a h2b_a h2c_a h2e_a h2f_a h2g_a h2i_a h2j_a (missing). 


**frequencies variables= country b1a b1b b2a b2b b3a b3b c1 c2 c3 d1 
   e1a e1b e1c e1d e1e e1f e1g e1h e1i e3a e3b e3c e3d e3e f1a f1b f2 f3a f3b 
   g1ea g1fa g1ga g1ha g1ia g1ja g1ka g1la g2a g2b g2c g2d g3a g3b 
   h1ab h1bb h1cb h1db h1eb h1fb h1gb h2a h2b h2c h2d h2e h2f h2g h2i h2j 
**frequencies variables=    h3 h4a h4b h5 h6a h6b h7a h7b h7c i1a i1b i2a i2b i3
   j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1m j1n j1o j1p j1q j1r j1s j1t j1u
   j1v j1w j1x j1y j1z j1aa j1ab
   k1a k1b k1c k1d k2a k2b k2c k2d k2e k3a k3b k3c k3d k3e k3f k3g
**frequencies variables=     k4a k4b k4c k4d k4e k5 k6a k6b k7a k7b k7c k8a k8b k8c k8d k8e 
   l1a l1b l1c l2a l2b l2c l2d l3 m1a m1b m1c n1 n2a n2b n3a n3b n3c n3d n3e 
   n4 n5a n5b n5c n5d  o1a o1b o1c o1d o1e o1f o1g o1h o2a o2b 
  p1aa p1ba p1ca p1da p1ea p1fa p1ga p1ha p1ia p1ja
**frequencies variables=  p2a p2b p2c p2d p2e p2f p2g p2h p2i p2j p2k p2l p2m p2n p2o p2p
  p2q p2r p2s p2u p2v p2w p2x p2y p2z p3a p3b p3c p3d 
  p4a p4b p4c p5 p6 p7 q1 q2a q2b q2c q2d q3 q4  
      missadl missadl_a
    sourcen source  country state collage usa

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
variable labels del1  delirium symptom present.

** HC FRAILTY SCALE 2023

recode b2b c2 h2a h2g (0=0)(1thru high=1)into b2b1 c21 h2a1 h2g1.

recode  HCFRt1miss (15 thru high=15).
if ( HCFRt1Miss gt 4) HCFRt1=$sysmis.


if (age lt 1) age=$sysmis.
if (age gt 111)age=$sysmis.
recode age (low thru 64=1)(65 thru 74=2)(75 thru 79=3)(80 thru 84=4)(85 thru 89=5)(90 thru 94=6)(95 thru high=7)into agecats.
**
**temporary
  select if not missing( HCFRt1)
  frequencies variables= bb1 bb2 country bb4  cc4 cc5 cc6  cc7 cc8  b1a b1b b2a b2b c1 c2 c3 d1 
   agecats age h3 b2b   
   h1aa h1ba h1ca h1da h1ea h1fa h1ga h2a h2b h2c h2d h2e h2f h2g h2i 
  h2j h4a h4b h5 h6a h6b i1a j1a j1b j1c j1d j1e j1f j1g j1h j1i j1j j1k j1l j1u j1w j1x k3c k3d k3e k3f k3g  k4a k5 k6a k8a k8b k8c k8d k8e l1a
     /statistics 


if (missing(h2c_2)) h2c_2 =ig2f_2.
if (missing(h2b_2))h2b_2= ig2g_2.
do if missing(h5_2).
recode ig1fa (0,1=0)(2,3=1)(4 thru high=2)into h5_2.
end if.
if (missing(k5_2))k5_2= ij1.

*frequencies variables= h2c_2 h2b_2 h5_2 k5_2. 


count tempT2= h1ba_2 (2,3) h1aa_2 (2,3) h1aa_2 (1,2,3) h1ea_2 (1,2,3) h2i_2 (2,3,4,5,6) h2c_2 (3,4,5,6) 
    h2b_2 (4,5,6) h2h_2 (2,3,4,5,6) h5_2 (1,2) h6b_2 (1) k5_2 (1 thru high) k3c_2 (1)
    b2a_2 (1,2,3,4, 5) h1da_2 (2,3) h1ca_2 (1,2,3)  j1h_2 (1,2) c3_2 (1,2,3,4) f2_2 (1,2) f2_2 (2) e1i_2 (1,2) e1h_2 (1,2)
    l1a_2 (1) l2a_2 (1) l2b_2 (1) i3_2 (2,3,4,5) j1w_2 (1,2) j1u_2 (1,2) j1b_2 (1,2) j1z_2 (1,2) p2g_2 (1,2).
recode tempt2 (24 thru high=24).
count tempT2miss= h1ba_2  h1aa_2  h1aa_2 h1ea_2  h2i_2  h2c_2  
    h2b_2  h2h_2  h5_2  h6b_2  k5_2 k3c_2 
    b2a_2 h1da_2 h1ea_2  j1h_2  c3_2  f2_2  f2_2  e1i_2  e1h_2 
    l1a_2  l2a_2  l2b_2  i3_2  j1w_2  j1u_2  j1b_2  j1z_2 p2g_2 (missing).

*frequencies variables= h1ba_2  h1aa_2  h1aa_2 h1ea_2  h2i_2  h2c_2  
    h2b_2  h2h_2  h5_2  h6b_2  k5_2 k3c_2 
    b2a_2 h1da_2 h1ea_2  j1h_2  c3_2  f2_2  f2_2  e1i_2  e1h_2 
    l1a_2  l2a_2  l2b_2  i3_2  j1w_2  j1u_2  j1b_2  j1z_2 p2g_2 .





recode tempT2miss (15 thru high=15).
if (tempt2Miss gt 4)tempt2=$sysmis.
recode  j1a j1b j1c j1e j1f j1l j1n j1o j1u j1w j1x j1y j1z j1aa (1 thru high=1).

recode tempT2 (missing=sysmis)(else=1)into frailtychange.
 
do if frailtychange eq 1 and not missing( HCFRt1).
if (missing( HCFRt1))frailtychange=$sysmis.
if (tempt2 lt  HCFRt1)frailtychange =0.
if (tempt2 gt  HCFRt1) frailtychange=2.
end if.
value labels frailtychange (0)improve (1)same (2)worse.

recode frailtychange (missing=sysmis)(0=1)(else=0)into frailtybetter.


**frequencies variables=  HCFRt1 tempt2 frailtychange
   /statistics
  temporary
  select if not missing(tempT2)
  frequencies variables=  HCFRt1 tempt2 frailtychange
  /statistics
 
recode tempT2 (missing=sysmis)(else=0)into frailtyUP2.

compute xxx=$sysmis.
do if frailtyup2 eq 0.
compute xxx=tempT2 -  HCFRt1.
if (xxx  gt 1 )frailtyUP2 = 1.
if (missing( HCFRt1))frailtyUP2=$sysmis.
end if.
value labels frailtychange (0)improve (1)same (2)worse.
recode frailtychange (0,1=0)(missing=sysmis)(2=1) into frailtyWORSE.
if (missing( HCFRt1) or missing(tempT2))frailtyworse=$sysmis.

recode j1g j1h j1l j1u j1w j1o j1n (2=1)/
    c2 c3 b2a h2c h2d h2f h2g (missing=sysmis)(0=0)(else=1) into c2B c3B h2aB h2cB h2dB h2fB h2gB.
**   HCFRt1 b1a j1g j1h  c2B c3B h2aB h2cB h2dB h2fB h2gB c2 c3 b1b b2a b2b  h2c h2d h2e h2f h2g  h6a h6b i1a i3 i2b  

** Create two sub-scales to Predict HC Frailty decline (worsen)
   The other sub scale is the HC Frailty scale

count  frailtydec07 =  b1a (1)   j1g   j1h   j1l   h2g (1 thru high)  b2b (1). 
count  frailtydec07b =  ic2a (1)   ii1c ii1d   ii1h (1,2,3)   ig2j (1 thru high) ic5  (2).
*frequencies variables= b1a ic2a j1g ii1c j1h ii1d j1l ii1h h2g ig2j b2b ic5.

count miss7b = ic2a   ii1c ii1d   ii1h    ig2j  ic5 (missing).
count rebound = h2cb i2b j1u j1w j1o (1 thru high).
count reboundb = ig2f  (1 thru high) ih2 (1)  ii1q ii1r ii1a  (1 thru high).
*frequencies variables= h2cb ig2f ic2b ih2 j1u ii1q j1w ii1r j1o ii1a.


count missboundb =ig2f  ih2  ii1q ii1r ii1a (missing).


do if missing( HCFRt1).
recode frailtydec07 rebound  frailtydec07b reboundb (low thru high=sysmis).
end if.


*frequencies variables= frailtydec07 frailtydec07b miss7b rebound reboundb missboundb.
 

recode frailtydec07 (4 thru high=4).
recode rebound (4 thru high=4).

recode h2g (0=0)(missing=sysmis)(1 thru high=1)into h2g0.
if (missing(h2g0) and not missing(frailtyworse))h2g0=0.

do if  HCFRt1 gt 8.
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
do if  HCFRt1 lt 9.
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

value labels frailtyrisk (1) 1. Improvr 1 (2) 2. Improve 2 (3) 3. Improve 3 (4) 4. typical 1
    (5) 5. typical 2 (6) 6. typical 3 (7) 7. decline 1 (8) 8. decline 2 (9) 9, decline 3.




*frequencies variables=frailtyrisk HCFRt1miss frailtydec07.



recode cps (0,1=0)(2 thru high=1)into cps1/.
recode   b2a j1k j1j j1i j1n c2  j1u j1w  j1o j1l (0=0)(1 thru high=1)(missing=sysmis)into b2a1 j1k1 j1j1 j1i1 j1n1 c21 j1u1 j1w1 j1o1 j1l1. 
do if not missing(tempt2).
recode  b2a1 b2b  j1k1 j1j1 j1i1 j1n1 c21 j1u1 j1w1 j1o1 k3b  (missing=0).
end if.

recode ih3 (8=1)(missing=sysmis)(else=0)into k3bX.
if (k3b eq 0 and k3bx gt 0)k3b=1.










do if not missing(frailtyworse).
recode b1a   b1b   b2b1  c21   j1g   j1h   j1l   
   h2a1  h2g  k3b
     h2cb i2b k2c l1b j1u j1w j1o j1n (missing=0).
end if.




do if rebound gt 0.
compute  frailtydec07= frailtydec07 - 1.
if ( frailtydec07 lt 0) frailtydec07=0.
end if .











recode frailtyhc (0 thru 5=1)(missing=sysmis)(else=0)into frail05 /
  frailtyhc (6 thru 11=1)(missing=sysmis)(else=0)into frail11 /
  frailtyhc (12 thru 16=1)(missing=sysmis)(else=0)into frail16 /
  frailtyhc (17 thru high=1)(missing=sysmis)(else=0)into frail20 /.
variable labels frail05 frail05 no vs yes/
    frail11 frail11 score 6 -11 no vs yes/
    frail16 frail16 score 12-16 no vs yes/
    frail20 frail20 score 17-20 no vs yes/.

**   FRAILTY MODIFIED FOR CHECKUP


count frailtyCU= h2c (3 thru high) h1bb h1ab h1db (2)
   B2a c3 f2 e1i h5 h6b j1z  j1b 
   K3c  j1w j1h l1a  (1 thru high)
   K5 e1h (2 thru high) 
   H2i h2g h1ab (1 thru high) 
   H1eb h1cb (2 thru high).    
count frailtyMISS=  h2c  h1bb h1ab h1db 
   B2a c3 f2 e1i h5 h6b j1z  j1b
   K3c j1w j1h l1a  
   K5 e1h 
   H2i h2g h1ab  
   H1eb h1cb      
 (missing).

if (frailtyMISS gt 6)frailtyCU=$sysmis.
do if range(frailtymiss,1,6).
compute xtemp=frailtyCU/(23-frailtymiss).
Compute frailtyCU=frailtyCU+(xtemp*frailtyMISS).           
If (frailtyCU gt 24)frailtyCU=24.
Compute frailtyCU=rnd(frailtyCU).
end if.
var labels frailtyCU Current interRAI CHECKUP Frailty Scale May 2016.
value labels frailtyCU (0)0.00 No Frailty Markers (7)7.00  Median 
   (20)20.00 Highest Frailty Count.
recode frailtyCU (20 thru high=20).


do if not missing(hosp2).
recode 
 frail20 (missing=0).
end if.
do if not missing(hosp2). 
recode   frail20 (missing=0).
end if.

*select if not missing(frailtyworse).

recode frailtydec07 (0=0)(1 thru hi=1) into frailtydec07_c.
recodE rebound (0=0)(1 thru hi=1) into rebound_c.
recodE HCFRT1 (0 thru 8=0)(9 thru hi=1) into HCFRT1_c.

variable labels
 HCFRT1 '(HCFRT1) Baseline Frailty Score [0-24]'/
 HCFRT1_c '(HCFRT1_c) Baseline Frailty Score [0-8=0 9-24=1]'/
 frailtyworse '[friltyworse]' Frailty Worsen/
 frailtydec07 '(frailtydec07) Baseline Frailty SUBSET1 - Cognition [0-4]'/
 rebound '(rebound) Baseline Frailty SUBSET1 - Clinical [0-4]'/
 frailtyrisk '(frailtyrisk) Baseline Frilty Risk Score [1-9]'/ 
 frailtydec07_c '(frailtydec07_c) Baseline Frailty SUBSET1 - Cognition collapsed [0-1]'/
 rebound_c '(rebound_c) Baseline Frailty SUBSET1 - Clinical collapsed [0-1]'/.

 
select if (mbmodel eq 1).
sort cases by case_lbl.
select if any(case_lbl,'HC3','HC4','HC5','HC7').
save outfile="S:\projectdata2\0000 account shared\Erez datasets\HOSP_model_compare.sav"
 /keep=country case_lbl hosp1 hosp2 hospriska 
    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd k8a k8c h3 .


*sort cases by batch country  facility resid_n2 a1d a1m a1y  .
* outfile="S:\projectdata2\0000 account shared\Erez datasets\HOSP_HC.sav"
 /keep=batch country  facility resid_n2 a1d a1m a1y  hosp1 hosp2 hospriska 
    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd k8a k8c h3 .

*frequencies  variables=country  hosp1 hosp2 hospriska 
    j1bd j1zd j1wd p62 n2b1 n3c lessions fallany j1od j1xd   infuse p2g 
    p4b1 j1aad  bb1  j1ed  l1a n5c n2a1 j1nd k8a k8c h3 j1nd HCFRt1 frailtydec07 rebound frailtyrisk frailtycu b1a   b1b    c21   j1g   j1h   j1l   
   h2a1  h2g  k3b
     h2cb i2b k2c l1b j1u j1w j1o j1n .

















