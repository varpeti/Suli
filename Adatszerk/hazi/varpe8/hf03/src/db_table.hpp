#ifndef DB_TABLE_H_
#define DB_TABLE_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "exp.hpp"

using namespace std;

class DB_TABLE
{
private:
    std::map<string, vector<string> > table;
    size_t row_size;
    bool alfanumeric(string str);
public:
    DB_TABLE();
    ~DB_TABLE();
    
    void add_column(string name);
    std::vector<string> column_names();
    void add_row();
    size_t row_count();
    void set(string col, size_t row, string value);
    string get(string col, size_t row);
    DB_TABLE join(const DB_TABLE &other, string cond);
};

DB_TABLE::DB_TABLE()
{
    row_size = 0;
}

DB_TABLE::~DB_TABLE()
{
    
}

bool DB_TABLE::alfanumeric(string str) // Trua ha csak szám vagy betű van benne
{
    for (unsigned int i = 0; i < str.size(); ++i)
    {   //                 numbers                                 UPCASE                               letters         
        if ( not( (str.at(i)>=48 and str.at(i)<=57) or (str.at(i)>=65 and str.at(i)<=90) or (str.at(i)>=97 and str.at(i)<=122) ) ) return false;
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
    table[col][row]=value;
}

string DB_TABLE::get(string col, size_t row)
{

}

DB_TABLE DB_TABLE::join(const DB_TABLE &other, string cond)
{

}


#endif