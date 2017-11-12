#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


void beolvas(ifstream& be,GRAPH<int,int> &graf)
{   
    int mennyi;
    string line;

    be >> mennyi; 
    getline(be,line); //első sor vége
    for (int i = 0; i < mennyi; ++i)
    {
        getline(be,line);
        stringstream str(line);

        int id,nid,suly;
        str >> id;

        graf.add_node(id,id);
        while (str >> nid and str >> suly)
        {
            graf.add_node(nid,nid); // hozzáadom, ha nem létezne.
            graf.add_line(id,nid,suly);
        }
    }
}

int main()
{   
    {
        GRAPH<int,int> graf;

        ifstream be ("graph.txt");
            beolvas(be,graf);
        be.close();
        graf.print();
        graf.print_dijkstra(0);
        GRAPH<int,int>::Path p = graf.dijkstra(0,3);
        cout << p.dist << ": ";
        for (auto const& node: p.Pnode)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    getchar();
    return 0;
}