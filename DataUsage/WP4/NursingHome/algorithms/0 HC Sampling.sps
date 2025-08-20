* Encoding: UTF-8.
* Encoding: .
get file="S:\projectdata2\0000 account shared\spss\2023-08-new mdshc20_3asm_with_icodes jnm.sav".  

COUNT allMISS = b2a 
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

frequencies variables=allmiss country.
select if (allmiss lt 16).
frequencies variables=allmiss country.

compute cWHOLE=$sysmis.
recode country ("ADH12","ADH6","FIN","ITA","NETH"=1)
   ("CANADA_AB","CANADA_BC","CANADA_MB","CANADA_NL",
    "CANADA_NS","CANADA_ON","CANADA_YT"=2)
   ("USA_AR","USA_CT","USA_GA","USA_LA","USA_MA","USA_MD","USA_MI","USA_MO","USA_NJ","USA_NY"=3)
   ("CHI"=4)
   ("NEWZ"=5)into cWHOLE .
value labels cWHOLE 
     (1) "(1) Europe" 
     (2) "(2) Canada" 
     (3) "(3) Usa" 
     (4) "(4) Hong Kong" 
     (5) "(5) New Zealand".

if missing (cwhole) cwhole=99.
frequencies variables=allmiss country cwhole.
temporary.
select if (cwhole eq 99).
frequencies variables = country.
select if (cwhole lt 99).
save outfile = 'S:\projectdata2\0000 account shared\Erez datasets\EREZ_HC_sample.sav'.






