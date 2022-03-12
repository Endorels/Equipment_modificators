#ifndef MODIFICATORS_H
#define MODIFICATORS_H

#include <vector>
#include <string>
#include "filter.h"

class Modificator
{
private:
    std::string ident;
    std::string type;
    double value;
    std::vector<Filter> mass;

public:
    Modificator() = delete;
    Modificator(const std::string &_ident, const std::string &_type, const double &_value,const std::vector<Filter> &_mass)
        : ident(_ident), type(_type), value(_value), mass(_mass){}
    ~Modificator(){}

    const std::string * get_ident(){ return &ident;}
    const std::string * get_type() { return &type;}
    const double * get_value() { return &value;}
    std::vector<Filter> * get_mass() { return &mass;}
};

#endif // MODIFICATORS_H
