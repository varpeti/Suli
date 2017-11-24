#ifndef DB_TABLE_H_
#define DB_TABLE_H_

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "hash.hpp"
#include "exp.hpp"

using namespace std;

class DB_TABLE
{
private:
    std::map<string, vector<string> > table;
    size_t row_size;

    bool alfanumeric(string str);
    bool contain_p0(string str);
public:
    DB_TABLE();
    //~DB_TABLE();
    
    void add_column(string name);
    std::vector<string> column_names();
    void add_row();
    size_t row_count();
    void set(string col, size_t row, string value);
    string get(string col, size_t row);
    DB_TABLE join(DB_TABLE &other, string cond);
};

DB_TABLE::DB_TABLE()
{
    row_size = 0;
}

bool DB_TABLE::alfanumeric(string str) // Trua ha csak szám vagy betű van benne
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {   //                 numbers                                 UPCASE                               letters         
        if ( not( (str.at(i)>=48 and str.at(i)<=57) or (str.at(i)>=65 and str.at(i)<=90) or (str.at(i)>=97 and str.at(i)<=122) ) ) return false;
    }
    return true;
}

bool DB_TABLE::contain_p0(string str) // False ha tartalmaz \0-at
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {      
        if ( str.at(i)=='\0' ) return false;
    }
    return true;
}

void DB_TABLE::add_column(string name)
{
    if ( name=="" or  table.find(name)!=table.end() or !alfanumeric(name) ) 
    {
        throw invalid_column_name();
    }
    std::vector<string> v(row_size,"");
    table[name]=v;
}

std::vector<string> DB_TABLE::column_names()
{
    std::vector<string> names;
    for (std::map<string, std::vector<string> >::iterator i = table.begin(); i != table.end(); ++i)
    {
        names.push_back(i->first);
    }
    return names;
}

void DB_TABLE::add_row()
{
    for (std::map<string, std::vector<string> >::iterator i = table.begin(); i != table.end(); ++i)
    {
        i->second.push_back("");
    }
    row_size++;
}

size_t DB_TABLE::row_count()
{
    return row_size;
}

void DB_TABLE::set(string col, size_t row, string value)
{
    if ( table.find(col)==table.end() or row>row_size ) throw invalid_index();
    if ( !contain_p0(value) ) throw invalid_value();
    table[col][row]=value;
}

string DB_TABLE::get(string col, size_t row)
{
    if ( table.find(col)==table.end() or row>row_size ) throw invalid_index();
    return table[col][row];
}

DB_TABLE DB_TABLE::join(DB_TABLE &other, string cond)
{   
    struct sCo
    {
        string ca;
        string cb;
    };
    std::vector<sCo> sco;
    string line1;
    stringstream str1(cond);
    while(getline(str1,line1,','))
    {
        string line2;
        stringstream str2(line1);
        bool e = true;
        sCo p;
        while(getline(str2,line2,'='))
        {   
            if (e) {p.ca = line2; e=false;}
            else   {p.cb = line2;         }
        }
        sco.push_back(p);
    }

   for (int j = 0; j < sco.size(); ++j)
    {
        for (int i = 0; i < sco.size(); ++i)
        {
            if (sco[j].ca==sco[i].cb) throw invalid_condition();
        }
    }

    DB_TABLE uj;
    HASH hash;
    // Az A tábláből feltöltöm a hashtáblát
    for (int i = 0; i < table.size(); ++i)
    {   
        string ca="";
        for (int j = 0; j < sco.size(); ++j)
        {
            if (table.find(sco[j].ca)==table.end()) throw invalid_condition();
            ca += table[sco[j].ca][i] + '\0';
        }
        cout << ca << endl; 
        hash.set(ca);
    }

    //A B tábláblól pedig megnézem hogy benne van-e
    for (int i = 0; i < other.table.size(); ++i)
    {   
        string cb="";
        for (int j = 0; j < sco.size(); ++j)
        {
            if (other.table.find(sco[j].cb)==other.table.end()) throw invalid_condition();
            cb += other.table[sco[j].cb][i] + '\0';
        }
        cout << cb << " " << hash.get(cb) << endl;
        if (hash.get(cb)) 
        {
            for (std::map<string, std::vector<string> >::iterator it = table.begin(); it != table.end(); ++it)
            {
                std::vector<string> v;
                v.push_back(it->second[i]);
                uj.table[it->first]=v;
            }
            for (std::map<string, std::vector<string> >::iterator it = other.table.begin(); it != other.table.end(); ++it)
            {
                std::vector<string> v;
                v.push_back(it->second[i]);
                uj.table[it->first]=v;
            }
            uj.row_size++;
        }
    }

    return uj;

}


#endif