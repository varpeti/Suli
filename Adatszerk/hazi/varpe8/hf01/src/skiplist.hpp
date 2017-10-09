#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <iostream>
#include <stdlib.h>

//DEF//

class SKIPLIST
{
	private:
		struct NODE
		{
			NODE(int _x);
			~NODE();

			int value;
			int szint;
			NODE *Pnext;
			NODE *Pdown;
		};

		NODE *node; //kezdő
		int maxszint;
		int meret;

		NODE *search(int x,int szint);
		bool isEmpty();

	protected:
	public:
		SKIPLIST();
		~SKIPLIST();
		void insert(int x);
		void erase(int x);
		bool contains(int x);
		int size();

};

//HEAD

SKIPLIST::NODE::NODE(int _x)
{
	//std::cout << "Letrejottem: " << _x << " " << this << "\n";
	Pnext 	= nullptr;
	Pdown	= nullptr;
	value 	= _x;
	szint 	= 0;
}

SKIPLIST::NODE::~NODE()
{
	//std::cout << "Megszuntem: " << value << " " << this << "\n";
}

SKIPLIST::SKIPLIST()
{
	maxszint = 10;
	meret = 0;
	node = new NODE(0);
	for (int i = 0; i < maxszint; ++i) //Maxszint magas
	{
		NODE *seged = new NODE(0);
		seged->Pdown=node;
		node=seged;
		node->szint=i+1;
	}
	
}

SKIPLIST::~SKIPLIST()
{
	while(!isEmpty())
	{
		if (node->Pnext!=nullptr) { //Érték törlés
			erase(node->Pnext->value);
		}else
		{	// Szint törlés
			NODE *s = node->Pdown;
			delete node;
			node = s;
		}
	}
	delete node;
}

//PRIV//

SKIPLIST::NODE *SKIPLIST::search(int x, int szint)
{
	NODE *futo = node;
	NODE *last = node;

	while (true) {
		//std::cout << x << "-" << last->value << " " << szint << "-" << futo->szint << "\n";
		if (futo->Pnext!=nullptr and futo->Pnext->value<=x) { // Addig megy jobbra míg kisebb vagy egyenlő a következővel.
			last = futo;
			futo = futo->Pnext;
		}else
		if (futo->Pdown and futo->szint>szint) { // Addig megy lefe míg tud, vagy szintbe nem ér
			futo = futo->Pdown;
		}else // Ha megtaláltuk vagy nem létezik, és nagyon megközelítettük.
		{
			return last;
		}
	}
	
}

bool SKIPLIST::isEmpty()
{
	return (node->Pnext==nullptr and node->Pdown==nullptr);
}


//PROT//

//PUB//

void SKIPLIST::insert(int x)
{
	NODE *eredmeny = search(x,0);
	if (eredmeny->Pnext!=nullptr and eredmeny->Pnext->value<x) eredmeny=eredmeny->Pnext;

	//std::cout << eredmeny->value << " " << x << "\n";
	if 	( 	!(eredmeny->value<x or eredmeny==node or isEmpty())  //Ha nem kisebb vagy nem fej vagy nem üres.
			or (eredmeny->Pnext!=nullptr and eredmeny->Pnext->value==x) // vagy létezik
		) return; 

	NODE *uj = new NODE(x);
	uj->value=x; 				// Az új értéke
	uj->szint=0;				// Az új szintje
	uj->Pnext=eredmeny->Pnext;	// Az új megkapja az előzőnek a következőjét.
	eredmeny->Pnext=uj;			// Az előző lévő megkapja az újat rákövetkezőnek.


	NODE *futo = uj;
	while ((rand() % 2)==0 and futo->szint<maxszint) // Fentebbi szintek
	{

		NODE *fenti = new NODE(x);

		fenti->value=x; 			// Fentebbi értéke ugyan az.
		uj->szint=futo->szint+1;	// Fentebbi szintje egyel nagyobb.
		fenti->Pdown=futo; 			// Fentebbi alatt lévő lesz a lentebbi.

		eredmeny = search(x,uj->szint); // Megkeresi a szintben az előzőt.
		if (eredmeny->Pnext!=nullptr) eredmeny=eredmeny->Pnext;
		fenti->Pnext=eredmeny->Pnext; 	// Az új megkapja az előzőnek a következőjét.
		eredmeny->Pnext=fenti;			// Az előző lévő megkapja az újat rákövetkezőnek.			

		futo=fenti; // tovább lép
	}
	meret++;
}

void SKIPLIST::erase(int x)
{
	if (isEmpty()) return;
	NODE *elozo = search(x,0);
	if (elozo->Pnext==nullptr or elozo->Pnext->value!=x) return; // Nem létezik.
	NODE *eredmeny = elozo->Pnext;
		
	while (true) // Középen tesztelős ciklus :D // Ameddig létezik alatta lévő addig 
	{
		NODE *elozo = search(x,eredmeny->szint);
		elozo->Pnext=eredmeny->Pnext; 			// köti össze az előzővel magát
		if (eredmeny->Pdown==nullptr) {delete eredmeny; break;}
		NODE *s = eredmeny->Pdown;
		delete eredmeny;						// és törli magát. 
		eredmeny=s;
	}
	meret--;
}

bool SKIPLIST::contains(int x)
{
	if (isEmpty()) return false;

	NODE *eredmeny = search(x,0);
	if (eredmeny->Pnext!=nullptr) eredmeny=eredmeny->Pnext;
	return (eredmeny->value==x and eredmeny!=node); // Ha egyezik és nem a head.
}

int SKIPLIST::size()
{
	return meret;
}

#endif