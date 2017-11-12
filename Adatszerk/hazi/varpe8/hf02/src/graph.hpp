/*
    Irányított=1
    Súlyott=1   Súlyozás=unsigned int
    Hurokél=1
    Töbszörösél=1
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <map>

template<class K,class V>
class GRAPH
{
private:
    struct Node
    {
        V value;
        struct Line
        {
            Node* node;
            unsigned int weight;
        };
        std::vector<Line> Pnext;
    };
    std::map<K, Node*> nodes;
public:
    GRAPH();
    ~GRAPH();

    void add_node(K key,V value);
    void add_line(K key1, K key2,unsigned int weight); // Összeköti key1-et key2-vel weight súlyal, de fordítva nem.
    /*TODO
    void del_node(K key);
    void del_line(K key1, K key2);
    */
    void print(); //TODO: remove 
    void print_dijkstra(K key); //TODO: remove


    struct Path
    {
        unsigned int dist;
        std::vector<V> Pnode;
        Path() {dist = -1;}
    };
    Path dijkstra(K key1, K key2);
};

template<class K,class V>
GRAPH<K,V>::GRAPH()
{

}

template<class K,class V>
GRAPH<K,V>::~GRAPH()
{

}

template<class K,class V>
void GRAPH<K,V>::add_node(K key, V value)
{
    if ( nodes.find(key) == nodes.end() ) { // Ha nincs hozzáadja
        Node* node = new Node;
        node->value = value;
        nodes[key] = node;
    }else{                                  // Ha van megváltoztatka
        nodes[key]->value=value;
    }
}

template<class K,class V>
void GRAPH<K,V>::add_line(K key1, K key2,unsigned int weight)
{
    if ( nodes.find(key1) == nodes.end() or nodes.find(key2) == nodes.end() ) return; // Ha nincs ilyen node kilép
    typename Node::Line line;
    line.node = nodes[key2];
    line.weight = weight;
    nodes[key1]->Pnext.push_back(line); // Hozzácsatolja a key1-eshez a key2-est.
}

template<class K,class V>
typename GRAPH<K,V>::Path GRAPH<K,V>::dijkstra(K key1, K key2)
{
    if ( nodes.find(key1) == nodes.end() or nodes.find(key2) == nodes.end()) return Path(); // Ha nincs ilyen node kilép

    std::map<Node*, unsigned int> dist; // Távolság
    std::map<Node*, bool> vis;  // Láttuk-e már
    std::map<Node*, Node*> prev; // Útvisszakereséshez.

    for (typename std::map<K,Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        dist[i->second]=-1;
        vis[i->second]=false;
        prev[i->second]=nullptr;
    }

    dist[nodes[key1]] = 0;

    for (typename std::map<K,Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        Node* a = i->second;
        vis[a] = true;

        if (a->Pnext.empty()) continue;
        Node* cur = a->Pnext[0].node;

        if (a == nodes[key2]) break; //Kilépünk ha megvan.

        for (unsigned int j = 0; j < a->Pnext.size(); ++j)
        {
            Node* b = a->Pnext[j].node;
            if (vis[b]) continue;
            unsigned int alt = ( dist[a]==(unsigned int)(-1) ? -1 : dist[a]+a->Pnext[j].weight );
            if (alt < dist[b]){
                dist[b] = alt;
                prev[b] = a;
            }
        }
    }
    
    Path p;
    p.dist = dist[nodes[key2]];
    Node* x = nodes[key2];
    while (prev[x]!=nullptr)
    {
        p.Pnode.push_back(x->value);
        x = prev[x]; 
    }
    return p;
}



//////////////////DEBUG////////////////// TODO: remove

template<class K,class V>
void GRAPH<K,V>::print()
{
    for (typename std::map<K,Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        std::cout << i->first << ": ";
        for (unsigned int j = 0; j < i->second->Pnext.size(); ++j)
        {
            std::cout << i->second->Pnext[j].node->value << " " <<  i->second->Pnext[j].weight << " | ";
        }
        std::cout << "\n";
    }
}

template<class K,class V>
void GRAPH<K,V>::print_dijkstra(K key)
{
    if ( nodes.find(key) == nodes.end()) return; // Ha nincs ilyen node kilép

    std::map<Node*, unsigned int> dist; // Távolság
    std::map<Node*, bool> vis;  // Láttuk-e már
    std::map<Node*, Node*> prev; // Útvisszakereséshez.

    for (typename std::map<K,Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        dist[i->second]=-1;
        vis[i->second]=false;
        prev[i->second]=nullptr;
    }

    dist[nodes[key]] = 0;

    for (typename std::map<K,Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {   
        Node* a = i->second;
        vis[a] = true;

        if (a->Pnext.empty()) continue;
        Node* cur = a->Pnext[0].node;

        for (unsigned int j = 0; j < a->Pnext.size(); ++j)
        {
            Node* b = a->Pnext[j].node;
            if (vis[b]) continue;
            unsigned int alt = ( dist[a]==(unsigned int)(-1) ? -1 : dist[a]+a->Pnext[j].weight );
            if (alt < dist[b]){
                dist[b] = alt;
                prev[b] = a;
            }
        }
    }
    
    for (typename std::map<K,Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
    {
        std::cout << i->first << " " << dist[i->second] << ": ";
        Node* x = i->second;
        while (prev[x]!=nullptr)
        {
            std::cout << x->value << " ";
            x = prev[x]; 
        }
        std::cout << "\n";
    }
}


#endif