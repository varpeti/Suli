--[[17.9.11
]]
tárgyteljesítés = {ZH=2, min=50%, kollokvium=true, részvétel=80%, katalógus=true}

ZH = {okt.9, nov.27, dec.11}

Mi az információ visszakeresés?
	Releváns információk keresésének módszerei.
	! nem információ kinyerés - struktúrálatlan szövegből struktúrált adatok készítése
		pl e-mail címek

Bevezetés
	Web: WWW = word wide web
	Internet: Fizikai hálózat

Régebben:
	Könyvtár: információ visszakeresés, papír alapú könyvekből
Mostanában:
	Böngészés: weben, sokkal gyorsabb

Weboldalak száma:
	1993: 130
	1997: 1milka

Web élete:
	1.0 hőskor 1990-2001 (saját információk)
	2.0 közösség (wikipédia, multiplayer)
	3.0	??? 
		semantikus web
		érzékelő
		szociális
		mobil
		VR 

Metaadat
	adat egy adatról 
		mi láthó a képen?
		könyv címe, szerzője stb

Szemnatika
	Konkrét kérdés

Pár statisztika a jelenlegi keresőkről

Információ visszakeresés alapjai:
	Sorrend
	Hierarchia: fejezetek

Kialakulás:
	Hidegháború
		Orosz, Amcsi verseny
		"Sir Timothy" (web atya) CERN-ben
		1993.ápr.30 világháló elérhető a publikum számára
		1990-re rengeteg módszer létezett információ visszakeresésre
		

--[[09.18
]]

1. dia második fele

Adattípúsok
	struktúrált
	félig-struktúrált
	struktúrálatlan

Adott kérdésre válasz:
	Adatbázis - struktúrált
	IR - struktúrálatlan

Bányászat:
	Adatbányászat
		Kiindulás: struktúrált
		Cél: Összefüggések feltárása
	Szövegbányászat
		Kiindulás: struktúrálatlan
		Cél: Összefüggések feltárása
	IR
		Kiindulás: struktúrálatlan
		Cél: Adott információ igényre, minnél gyorsabb nagy revelanciájó adatok kilistázása.

Nyelvtech

Nevek


2. dia

Def:
	IR = (U,IN,Q,O)->R 
		IR = információ visszakeresés
		U = felhasználó
		IN = információ igény
		Q = kereső kérdés
		O = Objektumok halmaza
		R = Válasz objektumok halmaza

	IN = (Q,I)
		I = Meg nem fogalmazott része a kérdésnek


Visszakereső modellek
	1 IR
	2 Klaszikus
	3 Boole
	4 Vektortér


Q és D (Dokumentum) távolságának matematikai mérésén alapul

Klasszikus:
	Boole - logika
	Vektortér - linal
	Valószínűségi - valszám

Boole
	Tartalmazza
	Nem tartalmazza

	Operátorok
		Negáció
		Logikai
			és, vagy

D (dokumentum) m darab j futó 1-től
T (dokumentumok) n darab i futó 1-től


Boole "38. dia"

Feladatok

O[1]=[[Még nyílnak a völgyben a kerti
virágok,
Még zöldell a nyárfa az ablak
előtt,
De látod amottan a téli
világot?
Már hó takará el a bérci tetőt.]]

O[2]=[[Fenyő ága Hósubában,
Mire vársz a Hófúvásban?
Hideg az a Kristálybunda,
Gyere haza Kis
házunkba.]]

O[3]=[[Fekete Pont Fehér
Ágon:
Varjú károg:
Fázom Fázom.]]

t = {"virág","tél","hó","fenyő","bunda","varjú"}

D[1] = {t[1],t[2]}
D[2] = {t[4],t[3],t[5]}
D[3] = {t[6]}

Q = t[3] and t[4]
->
S = {{D[1],D[2]},{D[2]}}
->
R = D[2]

---

Q = not t[1] or not t[2]
S = {{D[2],D[3]},{D[2],D[3]}}
R = {D[2],D[3]}

Vektrotérmodell "45. Dia"

TxD mátrix
	m oszlop (dokszám)
	n sor ()

--[[17.09.25
]]

W[i][j]= az a 0 és 1 közötti súly a T[i] x D[j] mátrixban --(D[j] felül)

Skálafüggetlen hálózat: Hatványfüggvény eloszlás. F(x)=C*x^(-A)


TF-IDF:
W[i][j] = f[i][j] * log(m/F[i])
	f[i][j]		i. dokumentum j. kifejezés előfordulása
	m 			dokumentumok száma
	F[i]		Azon dokumentumok száma melyekben előfordul a T[i] kifejezés


-------------

D = {(2,4),(1,4),(0,1)}

Bináris: 
	W[1]={1,1}
	W[2]={1,1}
	W[3]={0,1}
	--máshogy írva:
	W = {{1,1},{1,1},{0,1}}
Gyakoriság:
	W = {{2,4},{1,4},{0,1}}
MaxNorm:
	W = {{1/2,1},{1/4,1},{0,1}}
NormNorm:
	W = {{1/3,2/3},{1/5,4/5},{0,1}}
TFN:
	W = {{2/q(20),4/q(20)},{1/q(17),4/q(17)},{0,1}}
TF-IDF:
	W = {{2*log(3/2),0},{1*log(3/2),0},{0,0}}

TF-IDF:
	W = {{gyak*log(docszám/EnnyiDockbanVanBenneAKif),}}

--------------


TxD = {	
	{0,1,0,1,1,0,1},
	{0,1,1,0,0,0,0},
	{0,0,0,0,0,1,1},
	{0,0,0,1,0,0,0},
	{0,1,1,0,0,0,0},
	{1,0,0,1,0,0,0},
	{0,0,0,0,1,1,0},
	{0,0,1,1,0,0,0},
	{1,0,0,1,0,0,0},
}


Q = {0,1/q(5),0,0,1/q(5),1/q(5),1/q(5),1/q(5),0}

Számolás, Eredmény: td01.lua

--------------------

Hasnolősági mértékek:
	
	Skalár, dot mérték:
		Minden D[j] dokumentumra:
			R[j] = SUM(i=1, n, TxD[i][j]*Q[i]) 
				-- SUM(futó,max,skalár)
				-- R[j] a D[j] dokumentum a kérdésre adott válasz

	Cosinusz mérték:
		u.a

	Dice mérék:
		Minden D[j] dokumentumra:
			R[j] = 2*SUM(i=1, n, TxD[i][j]*Q[i]) / SUM(i=1, n, TxD[i][j]+Q[i])

	Jaccard együttható:
		Minden D[j] dokumentumra:
			R[j] = SUM(i=1, n, TxD[i][j]*Q[i]) / SUM(i=1, n, (TxD[i][j]+Q[i]) / 2^( TxD[i][j]*Q[i] ) )


					     SUM(i=1, n, TxD[i][j]*Q[i]) 
			R[j]=	-------------------------------------
					SUM(i=1, n,   (TxD[i][j]+Q[i])		)
					   (		--------------------	)
					   (		(2^( TxD[i][j]*Q[i])	)