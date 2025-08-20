* Encoding: UTF-8.
Get file='S:\projectdata2\0000 account shared\Erez datasets\frailty_hc_mb.sav'.
sort cases by batch country facility resid_n2 a1y a1m a1d .
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\frailty_hcmb_use.sav'.

Get file='S:\projectdata2\0000 account shared\Erez datasets\cognition_HC.sav'.
rename variables (b2b=b2bcog).
rename variables (b1b=b1bcog).
rename variables (j1bd=j1bdcog).
rename variables (h1fbs=h1fbscog).
rename variables (h1gbs=h1gbscog).
sort cases by batch country facility resid_n2 a1y a1m a1d .
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\cognition_HC_use.sav'.

Get file='S:\projectdata2\0000 account shared\Erez datasets\incontinence_HC.sav'.
compute iH3cont=Ih3.
rename variables (b1a=b1acont).
rename variables (b2b=b2bcont).
rename variables (h2d2=h2d2cont).
rename variables (k3f=k3fcont).
rename variables (k3g=k3gcont).
sort cases by batch country facility resid_n2 a1y a1m a1d .
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\incontinence_HC_use.sav'.

Get file='S:\projectdata2\0000 account shared\Erez datasets\hosp_hc.sav'.
sort cases by batch country facility resid_n2 a1y a1m a1d .
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\hosp_HC_use.sav'.

Get file='S:\projectdata2\0000 account shared\Erez datasets\iadl_hc.sav'.
sort cases by batch country facility resid_n2 a1y a1m a1d .
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\iadl_HC_use.sav'.

Get file='S:\projectdata2\0000 account shared\Erez datasets\locomotion_hc.sav'.
sort cases by batch country facility resid_n2 a1y a1m a1d .
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\locomotion_HC_use.sav'.

match files
 file='S:\projectdata2\0000 account shared\Erez datasets\frailty_hcmb_use.sav'
 /file='S:\projectdata2\0000 account shared\Erez datasets\hosp_hc_use.sav'
 /file='S:\projectdata2\0000 account shared\Erez datasets\incontinence_hc_use.sav'
 /file='S:\projectdata2\0000 account shared\Erez datasets\iadl_hc_use.sav'
 /file='S:\projectdata2\0000 account shared\Erez datasets\cognition_hc_use.sav'
 /file='S:\projectdata2\0000 account shared\Erez datasets\locomotion_hc_use.sav'
 /by batch country facility resid_n2 a1y a1m a1d .

frequencies variables = country.
save outfile='S:\projectdata2\0000 account shared\Erez datasets\Hc_matched.sav'.

*Get file='S:\projectdata2\0000 account shared\Erez datasets\Hc_matched.sav'.
*match files file=*
 /file=file1a/in= 'S:\projectdata2\0000 account shared\Erez datasets\locomotion_hc_new.sav'
 /by batch country facility resid_n2 a1y a1m a1d .

Get file='S:\projectdata2\0000 account shared\Erez datasets\locomotion_hc_new.sav'.
sort cases by batch country facility resid_n2 a1y a1m a1d .
compute outcomes=$sysmis.
Save outfile='S:\projectdata2\0000 account shared\Erez datasets\locomotion_HC_new_use.sav'.


match files
 file='S:\projectdata2\0000 account shared\Erez datasets\Hc_matched.sav'
 /file='S:\projectdata2\0000 account shared\Erez datasets\locomotion_hc_new_use.sav'
 /by batch country facility resid_n2 a1y a1m a1d .





frequencies variables=h2cB
j1o
hosp1
hosp2 
n2b1
lessions 
fallany 
infuse
p4b1 
n2a1 
bladdec 
bladT1 
bladT2 
bladIMP
bladIMPcap2023
chgINCONT
chgINCONT 
bladIMP3
bladIMP4 
bladIMP5 
KIN 
KINd 
locI 
 locI_2 
 locO 
 locO_2
 loc_d
 b2a2 
 b2a3 
aaarisk
cccrisk 
xxxrisk
zzzrisk 
IADLdec 
IADLdown.

variable labels h2cB ' (h2cB) tranferring oneself from surfaces such as bed, chair, wheelchair,standing position [0=independent 1=needs assistance]'/
j1o '(j1o) other fracture r-[0=not present 1=present]'/
hosp1 '(hosp1) r-[0=not admitted to hospital,1=admitted to hospital]'/
hosp2 '(hosp2) hospitalization at follow-up r-[0=not admitted to hospital,1=admitted to hospital]'/ 
n2b1 '(n2b1) Stasis ulcer [0=no,1=stasis ulcer stage 1-4]'/
lessions '(lessions) major skin problems r[0=no skin problems needing teatment 1=yes skin problems needing treatment]'/
fallany '(fallany) any fall r-[0=no,1=yes]'/
infuse '(infuse) infusions r-[0=no,1=yes]'/
p4b1 '(p4b1) ER visits in last 90 days since last assessment r-[0=no,1=yes]' /
n2a1 '(n2a1) pressure ulcer r-[0=no,1=yes]'/
bladdec '(bladDec) Bladder decline outcome r-[0=did not decline,1=decline]'/
bladT1 '(BLADT1) continence at baseline r-[0=continent,1=continent with catheter,2=usually continent,3=occassionally incontinent,4=frequently incontinent,5=incontinent]'/
bladT2 '(BLADT2) continence at follow-up r-[0=continent,1=continent with catheter,2=usually continent,3=occassionally incontinent,4=frequently incontinent,5=incontinent]'/
bladIMP '(BLADIMP) Bladder improvement r-[0=bladder did not improve,1=bladder improved]'/
bladIMPcap2023 '(bladIMPcap2023) r-[0=,1=,2=,3=,4=,5=,6=,7=,8=,9=,10=,11=,12=]'/
chgCONT '(chgINCONT) from continent to incontinent r-[0=no,1=yes]'/
chgINCONT '(chgINCONT) from continent to incontinent r-[0=no,1=yes]'/
bladIMP3 '(bladIMP3) r-[0=,1=]'/
bladIMP4 '(bladIMP4) r-[0=,1=]'/
bladIMP5 '(bladIMP5) r-[0=,1=]'/
KIN '(KIN) WIth family with child (cognition) r-[0=no,1=yes]'/
KINd '(KIND) WIth family with child (locomotion) r-[0=no,1=yes]'/
locI '(locI) new locomotion inside t1 r-[0=ind and gait ind and no walkr or wheelchair,1=inp othr er,2=set up help,3=supervision,4=limit ass,5=exten ass,6=max assist,7=tot dep]'/
 locI_2 '(locI_2) new locomotion inside t2 r-[0=ind and gait ind and no walkr or wheelchair,1=inp othr er,2=set up help,3=supervision,4=limit ass,5=exten ass,6=max assist,7=tot dep]'/
 locO '(locO) new locomotion outside t1 r-[0=ind and gait ind and no walkr or wheelchair,1=inp othr er,2=set up help,3=supervision,4=limit ass,5=exten ass,6=max assist,7=tot dep]'/
 locO_2 '(locO_2) new locomotion outside t2 r-[0=ind and gait ind and no walkr or wheelchair,1=inp othr er,2=set up help,3=supervision,4=limit ass,5=exten ass,6=max assist,7=tot dep]'/
 loc_d '(loc_d) locomotion decline r-[0=no,1=yes]'/
 b2a2 '(B2A2) COGNITIVE SKILLS FOR DAILY DECISION MAKING (cognition) r-[0=independent,1=impaired]'/n
 b2a3 '(B2A3) COGNITIVE SKILLS FOR DAILY DECISION MAKING (locomotion) r-[0=independent,1=impaired]'/
aaarisk '(aaarisk) Component 1 r-[0=,1=,2=,3=,4=,5=]'/
cccrisk '(cccrisk) Protective adjustor forcomponent 1 r-[0=,1=,2=,3=,4=,5=]'/
xxxrisk '(xxxrisk) Component 2 r-[0=,1=,2=,3=,4=]'/
zzzrisk '(zzzrisk) Protective adjustor forcomponent 2 r-[0=,1=,2=,3=,4=]'/
IADLdec '(IADLdec) IADL decline r-[0=lowest rate of decline,1=typical decline,2=typical decline,3=high decline,4=very high decline,5=very high decline,6=extremely high decline]'/
IADLdown '(IADLdown) risk of iadl decline final model OUTCOME r-[0=Low,1=Typical,2=High,3=Very high,4=Extremely high]'/.

value labels locI locI_2 locO locO_2
 (0)0 ind and gait ind and no walkr or wheelchair
 (1)1 inp othr er (2)2 set up help (3)3 supervision (4)4 limit ass
 (5)5 exten ass (6)6 max assist (7)7 tot dep.


display labels.

frequencies variables = country.
sample .4778.
frequencies variables = country.

save outfile='S:\projectdata2\0000 account shared\Erez datasets\HC_outcomes_520.sav'
/keep=BATCH
COUNTRY
FACILITY
resid_n2
a1d
a1m
a1y
j1o
HCFRT1_c
frailtydec07_c
rebound_c
frailtyWORSE
frailtyrisk
b1a
b2b
j1g
j1h
j1l
h2g
h2cB
i2b
j1u
b1b
k2c
hosp1
hosp2
hospRISKa
j1bD
j1zD
j1wD
p62
n2b1
n3c
lessions
fallany
j1oD
j1xD
infuse
p2g
p4b1
j1aaD
bb1
j1eD
l1a
n5c
n2a1
j1nD
k8a
k8c
h3
bladDEC
bladT1
bladT2
bladIMP
chgINCONT
chgCONT
bladIMPcap2023
bladIMP3
bladIMP4
bladIMP5
iG2f
iG1aa
iG1fa
iC2a
iI1c
iI1d
iI1g
iJ2h
iJ2i
iH3
b1aD
h1abd
h1bbd
h1fbd
j1gD
j1hD
h2j0
h1ab
Riadlhi
IADLdec
IADLdown
cogRISKdec
cpsv2
aaarisk
cccrisk
xxxrisk
zzzrisk
p1ia1
in2l1
p3c2
p1ja1
in2n1
in2k1
p2a1
p2j1
p4a29
p1da1
p2y1
p2v
p2p1
p1ba1
p2z1
p2t1
p1aa1
del1
h1fb
k2e
k8cd
j1f
j1b
j1j
n2a
k8ad
b2a2
b3b
j1ldd
age80
age70
j1gdd
j1hdd
e3c
e3d
kin
locRISK
locI
locI_2
locO
loco_2
LOC_d
h2eset
h2hset
h1fbs
h1gbs
k3c
h1fb3
h6b
j1lD
h2b02
age80d
h2bset
h2iset
ij2gD
k8add
b2a3
h2a2
h2j02
h4a4
k7c
h2d2
h2f02
k6a
kind
dk3b
h7a
Ig2fd
outcomes
iadlworse
iadlbetter
Kin h1fbscog j1fd j1bdcog j1jd n2a1cog j1ldcog e3c2 e3d2 
e3b2 
e3a2
e3e2 
 h1ebs
h1gbscog
dement 
 b1bcog
b2bcog
 k3f
k3g
falla
 j1ad
j1wdcog
j1zdcog
k2ccog n1 n2b1cog n3b l1acog v2dec
h2jset k2cloc age90loc age70loc j1gdloc j1hdloc loci
walkdec
iH3cont b1acont b2a24 b2bcont c22 c32 h1aa38 h1ba38 h1ca38 
 h2b2 h2d2cont h2f2 h2j2 h2g2 h2i2 h2d4 h2f4 h2i h2g4 h2j4 h2i4 
 h52 h6a3 j1g1 j1h1 j1l1 j1w k3fcont k3gcont k9e l312 h2c2 bladcap2023 newincDECcap
walkdecrev walkimprev ambdecrisk2rev ambDECtwo2rev locirev locrisknew
 h4a0 h1jb2 h2eb1 h2eb3 k4a1 cc6b3 h6b dk3b h2b3 h1ab2 h1cb2 h2jb1 h2f2 h4a4 i1a5 h6a1 j1l1.

