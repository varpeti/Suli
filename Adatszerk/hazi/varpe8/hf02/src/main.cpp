#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


//TODO: összes int-et unsigneddé alakítani

struct Csomagszallitas
{   
        struct Stermek
        {
            int hova;
            int suly;
            bool uton;
            bool operator<(const Stermek &B) {return suly<B.suly;}
        };
        struct Skamion
        {
            int teherbiras;
            int pozicio;
            vector<Stermek*> plato;
            bool operator<(const Skamion &B) {return teherbiras<B.teherbiras;}
            int get_teherbiras() {int a=teherbiras;for(int i=0;i<plato.size();++i)a-=plato[i]->suly;return a;}
        };
        

        GRAPH<int,int> graf;
        vector<int> raktarak;
        vector<Skamion> kamionok;
        std::vector<Stermek> termekek;

        void beolvas(ifstream& beg,ifstream& bes);
        void bepakol();
        void kiszalit();

        void print(); //TODO: remove
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
        bes >> kamion.pozicio;
        kamionok.push_back(kamion);
    }

    bes >> mennyi; // termékek száma
    for (int i = 0; i < mennyi; ++i)
    {
        Stermek termek;
        bes >> termek.hova;
        bes >> termek.suly;
        termek.uton = false;
        for(int i=0;i<raktarak.size();++i)if(termek.hova==raktarak[i])continue; // Lehet hogy a raktárba szól a csomag. Ez esetben nem törődünk a kiszálítással. 
        termekek.push_back(termek);
    }
}

void Csomagszallitas::print()
{
    for (int i = 0; i < raktarak.size(); ++i)
    {
        cout << raktarak[i] << endl;
    }
    cout << endl;

    for (int i = 0; i < kamionok.size(); ++i)
    {
        cout << kamionok[i].teherbiras << " " << kamionok[i].pozicio << " | ";
        for (int j = 0; j < kamionok[i].plato.size(); ++j)
        {
            cout << kamionok[i].plato[j]->suly << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < termekek.size(); ++i)
    {
        cout << termekek[i].hova << " " << termekek[i].suly << endl;
    }
    cout << endl;
}

/*void Csomagszallitas::bepakol() // A raktárba szállítandó már ki van véve.
{
    sort(termekek.begin(), termekek.end());
    sort(kamionok.begin(), kamionok.end());
    for (int k = 0; k < kamionok.size(); ++k)
    {
        int last = -1;
        for (int i = 0; i < termekek.size(); ++i) // Sorba berakja a legkisebtől kezdve
        {   
            if (kamionok[k].get_teherbiras()<termekek[i].suly) break; //Ha nincs hely a következőnek kilép
            if (termekek[i].uton) continue; // Ha már be van pakolva egy másik kamionba.

            kamionok[k].plato.push_back(&termekek[i]);
            termekek[i].uton = true;
            last = i;

        } 
        if (kamionok[k].get_teherbiras()==0 or kamionok[k].plato.empty()) continue; // Ha tökéletesen tele lett rakva, vagy nem fért bele semmi, tovább lép.
        
        for (int i = last+1; i < termekek[i].suly; ++i)
        {
            cout << kamionok[k].get_teherbiras() << " " << termekek[last].suly << " " << termekek[i].suly << endl;
            if (kamionok[k].get_teherbiras()+termekek[last].suly>=termekek[i].suly) // Addig cserélek nehezebb csomagokra könnyebbet míg teli nem lesz a kamion: ezért a több könnyebb csomag marad a következő kamionba.
            {
                kamionok[k].plato[kamionok[k].plato.size()-1]->uton=false;
                kamionok[k].plato[kamionok[k].plato.size()-1]=&termekek[i];
                last=i;
            }
        }
    }
    // TODO: Újragondolni, mert nem a legoptimálisabb végeredményt adja: 
    // Ha többet kéne kivenni hogy egy nagyobbat bepakolhasson, akkor nem jó.
    // Pl: Csomagok súlya: 1 1 1 1 3 3, kamionok teherbírása: A5 B5, Végeredmény: A: 1 1 1 1 B: 3, Optimális: A: 1 1 3 B: 1 1 3
    // A brute force (minden lehetőség megvizsgálata) jobban működött, de a specifikáció szerint ötletes megoldás kell. 
}*/

void Csomagszallitas::bepakol() // A raktárba szállítandó már ki van véve.
{
    sort(termekek.begin(), termekek.end());
    sort(kamionok.begin(), kamionok.end()); 
    bool csere = true;
    int fut = termekek.size();
    while (csere and fut>=0) // Ha nem történik csere kilép.
    {
        csere = false;
        for (int k = kamionok.size()-1; k>=0 ; --k)
        {
            for (int i = termekek.size()-1; i>=0; --i) // Sorba berakja a legnagyobtól kezdve
            {   
                if (termekek[i].uton or kamionok[k].get_teherbiras()<termekek[i].suly) continue; //Ha nincs hely vagy ha már be van pakolva egy másik kamionba.
    
                kamionok[k].plato.push_back(&termekek[i]);
                termekek[i].uton = true;
            } 
        }
        for (int k = 0; k < kamionok.size() ; ++k) 
        {
            if (kamionok[k].plato.empty()) continue; // Ha nem fért bele semmi, tovább lép.
            
            for (int j = 0; j<kamionok[k].plato.size(); ++j) // Legkisebb súlyútól megy.
            {
                for (int i = termekek.size()-1; i>=0; --i) // Legnagyobb súlyútól megy.
                {   
                    if (termekek[i].uton or kamionok[k].get_teherbiras()+kamionok[k].plato[j]->suly<=termekek[i].suly or kamionok[k].plato[j]->suly==termekek[i].suly) continue; //Kicseréli ha megéri kicserélni.
                
                    kamionok[k].plato[j]->uton=false;
                    kamionok[k].plato[j]=&termekek[i];
                    termekek[i].uton=true;
                    csere=true;
                } 
            }
        }
        fut--;
    }
    // TODO: Újragondolni, mert nem a legoptimálisabb végeredményt adja: 
    // Autoteszteken elhasalt. (vs brute force)
    // Pl: Csomagok súlya: 1 1 1 1 2 2 3 3 4, kamionok teherbírása: A5 B6, Végeredmény: A: 1 1 2 B: 1 1 2, Optimális: A: 1 1 1 2 B: 1 2 3
    // A brute force (minden lehetőség megvizsgálata) jobban működött, de a specifikáció szerint ötletes megoldás kell. 
    
}

void Csomagszallitas::kiszalit()
{
    for (int k = 0; k < kamionok.size(); ++k)
    {
        cout << k << ". kamion:\n";
        for (int j = 0; j<kamionok[k].plato.size(); ++j)
        {
            cout << "\tMozgas:\n\t\tHonnan: " << kamionok[k].pozicio << "\n\t\tHova: " << kamionok[k].plato[j]->hova;

            GRAPH<int,int>::Path p = graf.dijkstra(kamionok[k].pozicio,kamionok[k].plato[j]->hova);
            cout << "\n\t\tHossz: " << p.dist << "\n\t\tUtvonal: ";
            for (int i = p.Pnode.size()-1; i>=0; --i)
            {
                cout << p.Pnode[i] << " ";
            }
            cout << endl;

            kamionok[k].pozicio=kamionok[k].plato[j]->hova;
            
        }
    }
    // A kamionok a kiszállítás során, mindig a lehető legrövidebb úton közlekednek 
    // az egyes megrendelők között. A kamion tudja melyik csomóponban van éppen, 
    // és tudja, hogy melyik csomópontba kell a terméket kiszállítani. A legrövidebb 
    // út megkereséséhez a Dijkstra algoritmust használja.  

    cout << "Az alabbi csomagok nem kerultek kiszallitasra (hova;suly): ";
    for (int i = 0; i < termekek.size(); ++i)
    {
        if (!termekek[i].uton) cout << "(" << termekek[i].hova << ";" << termekek[i].suly << ") ";
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
    
        //book.graf.print_dijkstra(0);

        book.bepakol();
        book.kiszalit();
        book.print();


    }
    getchar();
    return 0;
}