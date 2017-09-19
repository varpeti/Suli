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


