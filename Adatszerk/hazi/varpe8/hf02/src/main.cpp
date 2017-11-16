#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


//TODO: összes int-et unsigneddé alakítani

struct Csomagszallitas
{   
        struct Skamion
        {
            int teherbiras;
            int kiindulas;
        };
        struct Stermek
        {
            int hova;
            int suly;
        };

        GRAPH<int,int> graf;
        vector<int> raktarak;
        vector<Skamion> kamionok;
        std::vector<Stermek> termekek;

        void beolvas(ifstream& beg,ifstream& bes);

        void print();
};

void Csomagszallitas::beolvas(ifstream& beg,ifstream& bes)
{   
    int mennyi;
    string line;

    beg >> mennyi; 
    getline(beg,line); // első sor vége
    for (int i = 0; i < mennyi; ++i)
    {
        getline(beg,line);
        stringstream str(line);

        int id,nid,suly;
        str >> id;

        graf.add_node(id,id);
        while (str >> nid and str >> suly)
        {
            graf.add_node(nid,nid); // hozzáadom, ha nem létezne, ha mégis, nem változtat semmin.
            graf.add_line(id,nid,suly);
        }
    }
    beg >> mennyi; // raktárak száma
    for (int i = 0; i < mennyi; ++i)
    {
        int id;
        beg >> id;
        raktarak.push_back(id);
    }

    bes >> mennyi; // kamionok száma
    for (int i = 0; i < mennyi; ++i)
    {
        Skamion kamion;
        bes >> kamion.teherbiras;
        bes >> kamion.kiindulas;
        kamionok.push_back(kamion);
    }

    bes >> mennyi; // termékek száma
    for (int i = 0; i < mennyi; ++i)
    {
        Stermek termek;
        bes >> termek.hova;
        bes >> termek.suly;
        termekek.push_back(termek);
    }
}

void Csomagszallitas::print()
{
    for (int i = 0; i < raktarak.size(); ++i)
    {
        cout << i << " " << raktarak[i] << endl;
    }
    cout << endl;

    for (int i = 0; i < kamionok.size(); ++i)
    {
        cout << i << " " << kamionok[i].teherbiras << " " << kamionok[i].kiindulas << endl;
    }
    cout << endl;

    for (int i = 0; i < termekek.size(); ++i)
    {
        cout << i << " " << termekek[i].hova << " " << termekek[i].suly << endl;
    }
    cout << endl;
}

int main()
{   
    {
        Csomagszallitas book;
        ifstream beg ("graph.txt"); ifstream bes ("simulation.txt");
            book.beolvas(beg,bes);
        beg.close(); bes.close();
        
        //graf.print();
        book.graf.print_dijkstra(0);
        /*GRAPH<int,int>::Path p = book.graf.dijkstra(0,7);
        cout << p.dist << ": ";
        for (auto const& node: p.Pnode)
        {
            cout << node << " ";
        }
        cout << endl;*/
        book.print();

    }
    getchar();
    return 0;
}