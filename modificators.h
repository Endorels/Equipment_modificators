#ifndef MODIFICATORS_H
#define MODIFICATORS_H

#include <vector>
#include <string>
#include "filter.h"

class Modificator
{

public:
    std::string ident;
    std::string type;
    double value;
    std::vector<Filter> mass;

    Modificator() = delete;
    Modificator(const std::string &_ident, const std::string &_type, const double &_value,const std::vector<Filter> &_mass)
        : ident(_ident), type(_type), value(_value), mass(_mass){}
    ~Modificator(){}
};

#endif // MODIFICATORS_H
