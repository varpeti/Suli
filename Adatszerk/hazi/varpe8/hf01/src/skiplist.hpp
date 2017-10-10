/*/
	A munkámat a "A Skip List Cookbook - William Pugh - 1990" alapján készítettem.
/*/


#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <iostream>
#include <stdlib.h>

#define MAXSZINT 10

//DEF//

class SKIPLIST
{
	private:
		struct NODE
		{
			NODE(int _x);
			~NODE();

			int value;
			NODE *Pnext[MAXSZINT];
		};

		NODE *header;
		int meret;

		int randomLevel();

	protected:
	public:
		SKIPLIST();
		~SKIPLIST();
		void insert(int value);
		void erase(int value);
		bool contains(int searchKey);
		int size();

};

//HEAD

SKIPLIST::NODE::NODE(int _x)
{
	//std::cout << "Letrejottem: " << _x << " " << this << "\n";
	value = _x;
	for (int i = 0; i < MAXSZINT; ++i)
	{
		Pnext[i]=nullptr;
	}
	
}

SKIPLIST::NODE::~NODE()
{
	//std::cout << "Megszuntem: " << value << " " << this << "\n";
}

SKIPLIST::SKIPLIST()
{
	header = new NODE(0);
	meret = 0;
}

SKIPLIST::~SKIPLIST()
{
	
	NODE *x = header;

	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr)
		{
			erase(x->Pnext[i]->value); //Kitörlöm a legkisebbtől kezdve az egészet.
		}
	}
	delete header; //Majd a headert is.
}

//PRIV//

int SKIPLIST::randomLevel() // Ezt késöbb át lehet írni optimálisabbra mint a véletlen.
{
	int lvl = 1; // lvl1 től indul mivel a 0. szintnek mindenképp létre kell jönnie.
	while (rand() %2 == 0 and lvl<MAXSZINT)
	{
		lvl++;
	}
	return lvl;
}


//PROT//

//PUB//

void SKIPLIST::insert(int value)
{
	NODE *update[MAXSZINT];
	NODE *x = header;

	for (int i = MAXSZINT-1; i >= 0; --i) // Megkeresi az szigoróan kissebb értékűt (x), és a keresztül mutatókat (update).
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->value < value)
		{
			x = x->Pnext[i];
		}
		update[i]=x;
	}
	x = x->Pnext[0];
	if (x==nullptr or x->value != value) // Ha nem létezik,
	{
		int newLevel = randomLevel();
		x = new NODE(value);
		for (int i = 0; i < newLevel; ++i) // Létrehozom a szintjeivel együtt,
		{
			x->Pnext[i]=update[i]->Pnext[i]; // amire mutatott az elötte lévő arra fog mutatni,
			update[i]->Pnext[i]=x; // és az elötte lévő rámutat.
		}
		meret++;
	}
}

void SKIPLIST::erase(int value)
{
	NODE *update[MAXSZINT];
	NODE *x = header;

	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->value < value)
		{
			x = x->Pnext[i];
		}
		update[i]=x;
	}
	x = x->Pnext[0];
	if (x!=nullptr and x->value == value) // Ha létezik és megegyezik az értéke
	{
		for (int i = 0; i < MAXSZINT; ++i) //Minden szinten
		{
			if (update[i]->Pnext[i]!=x) break; // Ha van
			update[i]->Pnext[i]=x->Pnext[i]; // A rámutató az adott szinten mutasson arra amire mutatott eddig.
		}
		delete x; //Törlés
		meret--;
	}

}

bool SKIPLIST::contains(int searchKey)
{
	NODE *x = header;
	for (int i = MAXSZINT-1; i >= 0; --i)
	{
		while (x->Pnext[i]!=nullptr and x->Pnext[i]->value < searchKey)
		{
			x = x->Pnext[i];
		}
	}
	x=x->Pnext[0];
	if (x!=nullptr and x->value==searchKey) return true;
	return false;
}

int SKIPLIST::size()
{
	return meret;
}

#endif