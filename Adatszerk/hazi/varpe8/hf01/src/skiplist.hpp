#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <iostream>
#include <stdexcept>
#include <stdlib.h>

//DEF//

class SKIPLIST
{
	private:
		struct NODE
		{
			NODE();
			~NODE();

			int value;
			int szint;
			NODE *Pnext;
			NODE *Pdown;
		};

		NODE *node; //kezdő

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

SKIPLIST::NODE::NODE()
{
	std::cout << "Letrejottem: " << this << "\n";
	Pnext 	= nullptr;
	Pdown	= nullptr;
	value 	= 0;
	szint 	= 0;
}

SKIPLIST::NODE::~NODE()
{
	std::cout << "Megszuntem: " << this << "\n";
}

SKIPLIST::SKIPLIST()
{
	node = new NODE;
}

SKIPLIST::~SKIPLIST()
{

}

//PRIV//

SKIPLIST::NODE *SKIPLIST::search(int x, int szint)
{
	NODE *futo = node;

	while (true) {
		//std::cout << x << "-" << futo->value << " " << szint << "-" << futo->szint << "\n";
		if (futo->Pnext!=nullptr and futo->Pnext->value<=x) { // Addig megy jobbra míg kisebb vagy egyenlő a következővel.
			futo = futo->Pnext;
		}else
		if (futo->Pdown and futo->szint>szint) { // Addig megy lefe míg tud, vagy szintbe nem ér
			futo = futo->Pdown;
		}else // Ha megtaláltuk vagy nem létezik, és nagyon megközelítettük.
		{
			//std::cout << x << "-" << futo->value << " " << szint << "-" << futo->szint << "\n";
			return futo;
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
	if (eredmeny->value<x or isEmpty()) { //Ha kisebb vagy üres.
		NODE *uj = new NODE;
		uj->value=x; 				// Az új értéke
		uj->szint=0;				// Az új szintje
		uj->Pnext=eredmeny->Pnext;	// Az új megkapja az előzőnek a következőjét.
		eredmeny->Pnext=uj;			// Az előző lévő megkapja az újat rákövetkezőnek.


		NODE *futo = uj;
		while ((rand() % 2)==0) // Fentebbi szintek
		{

			NODE *fenti = new NODE;

			fenti->value=x; 			// Fentebbi értéke ugyan az.
			uj->szint=futo->szint+1;	// Fentebbi szintje egyel nagyobb.
			fenti->Pdown=futo; 			// Fentebbi alatt lévő lesz a lentebbi.

			eredmeny = search(x,uj->szint); // Megkeresi a szintben az előzőt.
			fenti->Pnext=eredmeny->Pnext; 	// Az új megkapja az előzőnek a következőjét.
			eredmeny->Pnext=fenti;			// Az előző lévő megkapja az újat rákövetkezőnek.			

			futo=fenti; // tovább lép
		}
	}
}

void SKIPLIST::erase(int x)
{

}

bool SKIPLIST::contains(int x)
{
	if (isEmpty()) {throw std::underflow_error("Empty");}

	NODE *eredmeny = search(x,0);
	return (eredmeny->value==x);
}

int SKIPLIST::size()
{

}

#endif