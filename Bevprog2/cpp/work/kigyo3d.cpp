#include "graphics.hpp"
#include "sstream"
#include "vector"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "algorithm"
#include "iostream"

#define PI 3.141592

using namespace genv;
using namespace std;

const int kx = 1330;
const int ky = 700;
const int kz = round((kx+ky)/2);
const bool teljes = false;
const int nagyszam = kx+ky+kz;

struct Skoord
{	
	double x;
	double y;
	double z;

	Skoord(double cx,double cy,double cz)
	{
		x=cx;
		y=cy;
		z=cz;
	}

	Skoord()
	{
		x=0;
		y=0;
		z=0;
	}

	Skoord operator+(Skoord);
	Skoord operator-(Skoord);
	Skoord operator/(double);
	double operator|(Skoord);

	Skoord forgat(double alpha);
	Skoord lekepzes();
};

Skoord Skoord::operator+(Skoord b)
{
	Skoord c;
	c.x = x+b.x;
	c.y = y+b.y;
	c.z = z+b.z;
	return(c);
}

Skoord Skoord::operator-(Skoord b)
{
	Skoord c;
	c.x = x-b.x;
	c.y = y-b.y;
	c.z = z-b.z;
	return(c);
}

Skoord Skoord::operator/(double b)
{
	Skoord c;
	c.x = x/b;
	c.y = y/b;
	c.z = z/b;
	return(c);
}

double Skoord::operator|(Skoord b)
{
	return sqrt( (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)+(z-b.z)*(z-b.z) );
}

Skoord Skoord::forgat(double alpha)
{
	double se;
	Skoord f=*this;

	//y tengely körüli forgatás (2d-s forgatási mátrixból tippeltem a 3d-st)
	se= f.x*cos(alpha)+f.z*sin(alpha);
	f.z= -f.x*sin(alpha)+f.z*cos(alpha);
	f.x= se;

	//x tengely körüli forgatás 
	se= f.y*cos(PI)-f.z*sin(PI);
	f.z= f.y*sin(PI)+f.z*cos(PI);
	f.y= se;

	//z tengely körüli forgatás
	se= f.x*cos(PI)-f.y*sin(PI);
	f.y= f.x*sin(PI)+f.y*cos(PI);
	f.x= se;
	return f;
}

Skoord Skoord::lekepzes()
{
	double mz = (kz/2 + z)/(kz/2) *12; if (mz<3) mz=3; // Mekkora legyen | ne legyen kissebb 3x3-as nál
	return Skoord(x + z/2 + kx/2,y + z/2 + ky/2,mz); // a Z koordináta a nagyságát adja meg
}


struct Sboxok
{
	//private: 
	Skoord k; //Azért tartom meg a forgatás nélküli koordinátákat is mert a forgatás torzít
	Skoord szin; // Miért ne? ez is 3 :)
	Skoord f; //elforgatott koordináták, azért tárolom külön hogy sortolni lehessen ezek alapján
	Sboxok *kovet; // ki után menjen | NULL ha senki után | publikus lenne ha lehetne, de a SPECIFIKÁCIÓ szent :)

	public:
	Sboxok (Skoord ek, int gszin,Sboxok *ekovet)
	{
		k=k+ek;
		kovet = ekovet;
		
		if (gszin<255) 					{szin.x=255-(gszin-0*255); 	szin.y=(gszin-0*255); 		szin.z=000;} 				else
		if (gszin>255 and gszin<2*255) 	{szin.x=000; 				szin.y=255-(gszin-1*255); 	szin.z=(gszin-1*255);} 		else
		if (gszin>2*255) 				{szin.x=(gszin-2*255); 		szin.y=000; 				szin.z=255-(gszin-2*255);}
		cout << "Leterejottem! " << this << endl;
	}

	~Sboxok ()
	{
		cout << "Meghaltam! " << this << endl;
	}

	void supdate(double alpha,double sebesseg); // forgatás, mozgatás
	void srajzol(); // csak rajzolás
	Skoord getKoords(); //read only
	bool isSlpeep(); // read only
	void setKovet(Sboxok *ekovet); // write only
};

Skoord Sboxok::getKoords()
{
	return k;
}

void Sboxok::setKovet(Sboxok *ekovet)
{
	kovet=ekovet;
}

bool Sboxok::isSlpeep()
{
	return not kovet;
}

void Sboxok::supdate(double alpha,double sebesseg)
{	
	if (kovet) {
		Skoord c = kovet->getKoords();
		Skoord a = c-k; //vektor számolás 
		double h = c|k; if (h==0) h=1; //normalizálás
		k=k+a/(h/sebesseg); //mozgatás
	}

	f = k.forgat(alpha);
}

void Sboxok::srajzol()
{

	Skoord a = f.lekepzes();

	if (a.x>=kx-a.z or a.x<0) return; // ne jelenjen meg ha ki megy a képernyőről
	if (a.y>=ky-a.z or a.y<0) return;

	/*stringstream str;
	str << int(k.x) << " " << int(k.y) << " " << int(k.z);
	string s = str.str(); //*/

	gout << color(szin.x,szin.y,szin.z)
		<< move_to(a.x,a.y)
		<< box(a.z,a.z);
		//text(s);
}





/* A JÁTÉK RÉSZE*/

struct Srekord
{	
	int pont;
	int elet;
	int kaja;
	int maxkaja;
	double sebesseg;
	const int hosszszorzo;

	Sboxok *fej;
	Sboxok *farok;
	Sboxok *target;
	Sboxok *cel;
	// A target az tárolódik a vektorban;

	Srekord(int &szin,vector<Sboxok*> &boxok,int elet,int maxkaja,double sebesseg,int hosszszorzo) : pont(0),kaja(0),elet(elet),maxkaja(maxkaja),sebesseg(sebesseg),hosszszorzo(hosszszorzo)
	{
		fej = new Sboxok(Skoord(0,0,0),szin,NULL);
		boxok.push_back(fej); if (szin<3*255) szin++; else szin=0;
		farok = fej;
		target = 0;
		cel = 0;
	}
	
};

void pontkiir(int pont);

double update(int i,vector<Sboxok*> &boxok,Skoord eger,Srekord &rekord,double alpha)
{
	if (!boxok[i]->isSlpeep() or rekord.fej==boxok[i]) return nagyszam; // Ha  nem kaja vagy fej akkor nem vizsgálunk rá.
	if ((boxok[i]->getKoords().forgat(alpha)|rekord.fej->getKoords().forgat(alpha))<10) // Megeszi ha a közelébe ért
	{
		if (rekord.cel==boxok[i]){ // ha a célt ette meg
			for (Sboxok *box : boxok)
				if (box->isSlpeep() and box!=boxok[i]) {rekord.cel=box; break; // Célt választ
			}
			rekord.pont+=rekord.sebesseg*27;
		}else{ // Ha nem a célt ette meg
			rekord.elet--;
		}

		delete boxok[i];
		boxok[i] = boxok[boxok.size()-1];
		boxok.pop_back();
		rekord.kaja--;
	}
	Skoord a = boxok[i]->getKoords().forgat(alpha).lekepzes(); a.z=0; // pontok helyzete a képernyőn
	return a|eger; //egértől való távolság
}

bool rendez(Sboxok* a, Sboxok* b) { return (a->f.z < b->f.z); } // A f.z koordinátára rendezek hogy ami hátrébb van elöbb rajzolódjon ki

void updatedraw(vector<Sboxok*> &boxok,double alpha,Skoord eger,Srekord &rekord,int &szin)
{
	//draw

	gout << color(000,000,000) //képernyő törlés
			<< move_to(0,0) 
			<< box(kx,ky);

	gout << color(25,25,25); //Pontszám
	pontkiir(rekord.pont);

	//update

	while (rekord.kaja<rekord.maxkaja) // Ha nincs elég kaja lespawnol
	{
		Sboxok *a = new Sboxok(Skoord(rand()%kx-kx/2,rand()%ky-ky/2,rand()%kz-kz/2),rand()%(3*255),NULL); // random hely szín és nem mozog
		boxok.push_back(a);
		a->supdate(alpha,rekord.sebesseg); // Updateljük hogy ne villanjon fel 0,0,0 nál

		for (int i = 0; i < rekord.hosszszorzo; ++i)
		{
			rekord.farok = new Sboxok(rekord.farok->getKoords(),szin,rekord.farok); // kígyó növelése
			boxok.push_back(rekord.farok); if (szin<=3*255) szin++; else szin=0;
			rekord.farok->supdate(alpha,rekord.sebesseg);
		}
		
		rekord.kaja++;
	}

	Skoord ffej = rekord.fej->getKoords().forgat(alpha).lekepzes(); // Vonalakhoz | Ismert hiba: ha 

	if (rekord.target) { // ha van target
		Skoord ftarget = rekord.target->getKoords().forgat(alpha).lekepzes();

	//draw

		gout << color(255,255,255)
			<< move_to(ffej.x + ffej.z/2, ffej.y + ffej.z/2) // a Z koordináta a nagyságukat adja meg
			<< line_to(ftarget.x + ftarget.z/2, ftarget.y + ftarget.z/2); //kirajzolom a vonalat a tragethez
	}

	//update

	if (rekord.cel) { // ha van cél
		Skoord fcel = rekord.cel->getKoords().forgat(alpha).lekepzes();
		Skoord a = fcel-ffej; // vektor számolás
		double d = (fcel|ffej); if (d>50) d/=50; else d=1;
		a = (a/d);  // normálás csak nem egységre

	//draw

		gout << color(255,255,255) // Vonal rajzolás a cél felé
			<< move_to(ffej.x + ffej.z/2, ffej.y + ffej.z/2)
			<< line(a.x + a.z/2, a.y + a.z/2); 
	}else{
		for (Sboxok *box : boxok) if (box->isSlpeep() and box!=rekord.fej) {rekord.cel=box; break;} // Az első célt kiválasztja
	}

	//update

	int mintav = nagyszam;

	vector<Sboxok*> rajZ = boxok; // új vektor a sorba rajzoláshoz
	std::sort(rajZ.begin(), rajZ.end(),rendez); // sorba rendezés f.z koordináta szerint


	for (int i = 0; i < boxok.size(); ++i)
	{
		boxok[i]->supdate(alpha,rekord.sebesseg+(rand()%200/100)); //a sebességen van random faktor hogy kígyószerű legyen
		double tav = update(i,boxok,eger,rekord,alpha);
		if (tav<mintav) {mintav=tav; rekord.target=boxok[i];} // kiválasztja az egérhez a legközelebbit

		//draw
		rajZ[i]->srajzol(); // rajz a sorba rendezett vektor alapján
	}


	//update

	rekord.fej->setKovet(rekord.target); // Induljon a target felé

	//draw

	gout << color(255,0,0);
	for (int i = 0; i < int(rekord.elet); ++i)
	{
		gout << move_to(10+i*40,10) << box(25,25);
	}

	gout << refresh;

}

void menurajz(string s1, string s2, string s3) // Nincs kölön struck menühöz, nem is kell mert kevés dolog van benne, nem lesz bővítve
{
	int akx=kx/2, aky=ky/2;
	int h1 = gout.twidth(s1);
	int h2 = gout.twidth(s2);
	int h3 =gout.twidth(s3);
	int bky = ky/7;
	gout << color(000,000,100) //képernyő törlés
			<< move_to(0,0) 
			<< box(kx,ky) 
			<< color(000,200,000) // Új játék menüpont
			<< move_to(akx-h1/2,aky-bky/2-bky)
			<< text(s1)
			<< color(200,200,000) // Információk menüpont
			<< move_to(akx-h2/2,aky-bky/2)
			<< text(s2)
			<< color(200,000,000) // Kilépés menüpont
			<< move_to(akx-h3/2,aky-bky/2+bky)
			<< text(s3)
			<< refresh;
}

int main()
{
	srand (time(NULL));

	gout.open(kx,ky,teljes);

	gout.load_font("font.ttf",40);

	gin.timer(20);

	double alpha 		= 0;
	double rpx			= 0;
	const double mertek = 0.03;

	Skoord eger			  (0,0,0); 			// A Z koordináta nem használt
	int szin 			= rand()%(3*255);


	event ev;
	while (gin >> ev) // Main ciklus
	{ 
		menurajz("Új játék (0-9)","Információk (h)","Kilépés (ESC)");
		double nehezseg = -1;
		while(gin >> ev and nehezseg==-1) // Menü cikluss
		{
			if (ev.type==ev_key)
			{
				if (ev.keycode=='0') nehezseg=0;
				else if (ev.keycode=='1') nehezseg=1;
				else if (ev.keycode=='2') nehezseg=2;
				else if (ev.keycode=='3') nehezseg=3;
				else if (ev.keycode=='4') nehezseg=4;
				else if (ev.keycode=='5') nehezseg=5;
				else if (ev.keycode=='6') nehezseg=6;
				else if (ev.keycode=='7') nehezseg=7;
				else if (ev.keycode=='8') nehezseg=8;
				else if (ev.keycode=='9') nehezseg=9;
				else if (ev.keycode=='h') {
					menurajz("Kígyó mozgatás: egér | Kamera mozgatás: a,d","Cél: a kígyó általl (rövid) vonallal mutatott kaja megevése","Halál: Nem a kívánt kaja elfogyasztása");
					while(gin >> ev and ev.keycode!=key_escape); // várunk ESC-re
					menurajz("Új játék (0-9)","Információk (h)","Kilépés (ESC)"); // Vissza rajzolom a menüt
				}
				else if (ev.keycode==key_escape) return 0; // Kilépés
			}
			
		}

		nehezseg=((nehezseg+1)/10)*5;
		vector<Sboxok*> boxok;
		Srekord	rekord (szin,boxok,5,50,nehezseg,10); // szin,boxok,elet,kajaszam,sebesseg,hosszszorzó

		while(gin >> ev and ev.keycode!=key_escape and rekord.elet>0) // Játék ciklus
		{
			if (ev.type==ev_timer) 
			{
				alpha+=rpx; // forgatás
				updatedraw(boxok,alpha,eger,rekord,szin);
			
			}
			else if (ev.type==ev_key)
			{
				if (ev.keycode==key_right 	or ev.keycode=='d') rpx=mertek;
				if (ev.keycode==key_left 	or ev.keycode=='a') rpx=-mertek;

				if (-ev.keycode==key_right 	or -ev.keycode=='d') rpx=0;
				if (-ev.keycode==key_left 	or -ev.keycode=='a') rpx=0;
			}
			else if (ev.type==ev_mouse)
			{
				eger.x=ev.pos_x;
				eger.y=ev.pos_y;
			}
		}


		while (0<boxok.size()) // Játék utáni memória felaszabadítás
		{
			delete boxok[boxok.size()-1];
			boxok.pop_back();
		}
	}
	return 0;
}

void pontkirajz(int x, int y, int sz)
{
	switch(sz) //Hmm ctrl+c ctrl+v a "kockás" játékból :D
	{
		case 0: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30) << box(30,90) << move_to(x,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90); break;
		case 1: gout << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90); break;
		case 2: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30,y+30+90) << box(90,30); break;
		case 3: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30); break;
		case 4: gout << move_to(x,y+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90); break;
		case 5: gout << move_to(x+30,y) << box(90,30) << move_to(x,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30,y+30+90) << box(90,30); break;
		case 6: gout << move_to(x+30,y) << box(90,30) << move_to(x,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30,y+30+90) << box(90,30) << move_to(x,y+30+90+30) << box(30,90); break;
		case 7: gout << move_to(x+30+90,y+30) << box(30,90) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y) << box(90,30); break;
		case 8: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30) << move_to(x,y+30+90+30) << box(30,90); break;
		case 9: gout << move_to(x+30,y) << box(90,30) << move_to(x+30+90,y+30) << box(30,90) << move_to(x,y+30) << box(30,90) << move_to(x+30,y+30+90+30+90) << box(90,30) << move_to(x+30+90,y+30+90+30) << box(30,90) << move_to(x+30,y+30+90) << box(90,30); break;
	}
}

void pontkiir(int pont)
{

	int seged, s2;
	s2=pont;

	seged = s2/10000;
	s2=s2-10000*seged;
	pontkirajz(kx/2-2*160-75,ky/2-135,seged);

	seged = s2/1000;
	s2=s2-1000*seged;
	pontkirajz(kx/2-1*160-75,ky/2-135,seged);

	seged = s2/100;
	s2=s2-100*seged;
	pontkirajz(kx/2-0*160-75,ky/2-135,seged);

	seged = s2/10;
	s2=s2-10*seged;
	pontkirajz(kx/2+1*160-75,ky/2-135,seged);

	seged = s2;
	pontkirajz(kx/2+2*160-75,ky/2-135,seged);
}
