#ifndef MODIFICATORS_H
#define MODIFICATORS_H

#include <vector>
#include <string>
#include "filter.h"

class modificator
{

public:
    std::string ident;
    std::string type;
    double value;
    std::vector<filter> mass;

    modificator() = delete;
    modificator(const std::string &_ident, const std::string &_type, const double &_value,const std::vector<filter> &_mass)
        : ident(_ident), type(_type), value(_value), mass(_mass){}
    ~modificator(){}
};

#endif // MODIFICATORS_H
