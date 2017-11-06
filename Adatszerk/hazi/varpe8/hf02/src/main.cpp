#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


void beolvas(ifstream& be,GRAPH &graf)
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

        graf.insert(id);
        while (str >> nid and str >> suly)
        {
            graf.add_szomszed(id,nid,suly);
        }
    }
}

int main()
{   
    {
        GRAPH graf;

        ifstream be ("graph.txt");
            beolvas(be,graf);
        be.close();

        graf.get_tav(0,3);

    }
    getchar();
    return 0;
}