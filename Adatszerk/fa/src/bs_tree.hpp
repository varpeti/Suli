#ifndef BIN_TREE_HPP_INCLUDED
#define BIN_TREE_HPP_INCLUDED

#include <algorithm>
#include <iostream>

#include "exceptions.hpp"

using namespace std;

//
// Bináris keresőfa osztály
// DEFINÍCIÓ
//
template<class T>
class Bs_tree {
	// Belső csúcs struktúra
	struct Node {
		Node *parent;
		Node *left, *right;
		T key;

		Node(const T& k) :
				parent(nullptr), left(nullptr), right(nullptr), key(k) {
		}
		Node(const T& k, Node *p) :
				parent(p), left(nullptr), right(nullptr), key(k) {
		}
	};

	// Adattag
	Node *root;

	// Felszabadító függvény
	void _destroy(Node *x);

	// Segédfüggvények
	Node *_min(Node *x) const;
	Node *_max(Node *x) const;
	Node *_next(Node *x) const;
	Node *_prev(Node *x) const;

	ostream& _inorder(Node* i, ostream& o);
	ostream& _preorder(Node* i, ostream& o);
	ostream& _postorder(Node* i, ostream& o);

	size_t _size(Node *x) const;

public:
	// Konstruktor és destruktor
	Bs_tree() :
			root(0) {
	}
	~Bs_tree() {
		_destroy(root);
	}

	// Másoló konstruktor és operátor, valamint segéd függvényeik
	Bs_tree(const Bs_tree<T>& t);
	Bs_tree& operator=(const Bs_tree<T>& t);
	Node* getroot() const;
	Node* copyOf(Node* n, Node* p);

	// Alapműveletek
	size_t size() const {
		return _size(root);
	}
	bool isempty() const {
		return root == nullptr;
	}

	bool find(const T& k) const;
	void insert(const T& k);
	void remove(const T& k);

	ostream& inorder(ostream& o);
	ostream& preorder(ostream& o);
	ostream& postorder(ostream& o);

};

//
// Bináris keresőfa osztály
// FÜGGVÉNYIMPLEMENTÁCIÓK
//

// Rekurzívan felszabadítja a csúcsokat.
// A destruktor hívja meg a gyökérre.
template<class T>
void Bs_tree<T>::_destroy(Node *x) {
	// TODO
}

// Segéd függvény a copy constructor-hoz valamint assigment operator-hoz
template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::copyOf(Node* n, Node* p) {
	// TODO
}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template<class T>
Bs_tree<T>::Bs_tree(const Bs_tree<T>& t) {
	root = nullptr;
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template<class T>
Bs_tree<T>& Bs_tree<T>::operator=(const Bs_tree<T>& t) {
	// TODO
}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_min(Node *x) const {
	while (x->left)
	{
		x = x->left;
	} 
	return x;
}

// Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_max(Node *x) const {
	while (x->right)
	{
		x = x->right;
	} 
	return x;
}

// Visszaadja a fából az x csúcs rákövetkezőjét,
// vagy nil-t, ha x az legnagyobb kulcsú elem.
// Előfeltétel: x != nilif(isempty())
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_next(Node *x) const {
	// TODO
}

// Visszaadja a fából az x csúcs megelőzőjét,
// vagy nil-t, ha x az legkisebb kulcsú elem.
// Előfeltétel: x != nil
template<class T>
typename Bs_tree<T>::Node *Bs_tree<T>::_prev(Node *x) const {
	// TODO
}

// Rekurzívan meghatározza, és visszaadja
// az x gyökerű részfa elemeinek számát.
// Megjegyzés: üres fára is működik -> 0-t ad vissza
template<class T>
size_t Bs_tree<T>::_size(Node *x) const {
	// TODO
}

// Lekérdezi, hogy található-e k kulcs a fában.
// Igazat ad vissza, ha található.
template<class T>
bool Bs_tree<T>::find(const T& k) const {
	// TODO
}

// Beszúrja a k értéket a fába.
// Ha már van k érték a fában, akkor nem csinál semmit.
template<class T>
void Bs_tree<T>::insert(const T& k) {
	Node *x = root;
	while (true)
	{
		if (k < x->key) //Kisebb
		{

		} else //nagyobb
		{

		}
	}
}

// Eltávolítja a k értéket a fából.
// Ha nem volt k érték a fában, akkor nem csinál semmit.
template<class T>
void Bs_tree<T>::remove(const T& k) {
	// TODO
}

// Bináris keresőfa bejárások kívülről elérhető függvényei.
template<class T>
ostream& Bs_tree<T>::preorder(ostream& o) {
	// TODO
}

template<class T>
ostream& Bs_tree<T>::postorder(ostream& o) {
	// TODO
}

template<class T>
ostream& Bs_tree<T>::inorder(ostream& o) {
	// TODO
}

// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template<class T>
ostream& Bs_tree<T>::_preorder(Node *i, ostream& o) {
	// TODO
}

// Postorder bejárás.
template<class T>
ostream& Bs_tree<T>::_postorder(Node* i, ostream& o) {
	// TODO
}

// Inorder bejárás.
template<class T>
ostream& Bs_tree<T>::_inorder(Node* i, ostream& o) {
	// TODO
}

template<class T>
typename Bs_tree<T>::Node* Bs_tree<T>::getroot() const {
	// TODO
}

#endif // BIN_TREE_HPP_INCLUDED
