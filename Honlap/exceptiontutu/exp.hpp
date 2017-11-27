#ifndef EXP_H_
#define EXP_H_

#include <exception>

class invalid_column_name : public std::exception
{
public:
    invalid_column_name(){};
};

class invalid_index : public std::exception
{
public:
    invalid_index(){};
};

class invalid_value : public std::exception
{
public:
    invalid_value(){};
};

class invalid_condition : public std::exception
{
public:
    invalid_condition(){};
};

#endif