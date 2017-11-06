#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <map>
#include <vector>

class GRAPH
{
private:
    struct Pont
    {
        std::map<Pont*,unsigned int> szomszedok; // unsigned int a súlya

        //Pont() {std::cout << "L" << this << std::endl;}
        //~Pont(){std::cout << "M" << this << std::endl;}
    };
    std::map<unsigned int,Pont*> pontok;

    bool letezik(unsigned int id);
public:
    GRAPH();
    ~GRAPH();

    void insert(unsigned int id);
    void add_szomszed(unsigned int id,unsigned int nid,unsigned int suly);
    unsigned int get_tav(unsigned int a,unsigned int b);
};

GRAPH::GRAPH()
{

}

GRAPH::~GRAPH()
{
    for (std::map<unsigned int,Pont*>::iterator i = pontok.begin(); i != pontok.end(); ++i)
    {
        delete pontok[i->first];
        pontok.erase(i->first);
    }
}

bool GRAPH::letezik(unsigned int id)
{
    std::map<unsigned int,Pont*>::const_iterator it = pontok.find(id);
    return it!=pontok.end();
}


void GRAPH::insert(unsigned int id)
{
    if (letezik(id)) return;
    pontok[id] = new Pont;
}

void GRAPH::add_szomszed(unsigned int id,unsigned int nid,unsigned int suly)
{
    if (!letezik( id)) insert( id); //foolproof
    if (!letezik(nid)) insert(nid);

    pontok[id]->szomszedok[pontok[nid]]=suly;
}

unsigned int GRAPH::get_tav(unsigned int a, unsigned int b)
{
    std::map<Pont*, unsigned int> tavolsag;
    std::map<Pont*,Pont*> elozo;
    std::vector<Pont*> Q;

    for (std::map<unsigned int,Pont*>::iterator i = pontok.begin(); i != pontok.end(); ++i)
    {
        tavolsag[i->second] = -1; // alulcsordul
        elozo[i->second] = nullptr;
        Q.push_back(i->second);
    }

    tavolsag[pontok[a]] = 0; // 0 a kezdő táv.

    while (!Q.empty())
    {   
        Pont *u = Q[0];
        unsigned int j = 0;
        for (unsigned int i = 0; i < Q.size(); ++i)// A legkisebb távolsággal rendelkező Q-ban lévő Pont
        {
           if (tavolsag[Q[i]]<tavolsag[u]) {u=Q[i];j=i;}
        }

        Q[j] = Q[Q.size()-1]; Q.pop_back(); // Cserés törlés

        if (u == pontok[b]) { // Ha megvan a keresett táv.
            std::vector<Pont*> S;
        }

        for (std::map<Pont*,unsigned int>::iterator i = u->szomszedok.begin(); i != u->szomszedok.end(); ++i)
        {
            unsigned int tav = tavolsag[u] + i->second;
            if (tav < tavolsag[i->first]) 
            {
                tavolsag[i->first] = tav;
                elozo[i->first] = i->first;
            }
        }
    }
    return 0
}
    


#endif