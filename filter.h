#ifndef FILTER_H
#define FILTER_H
#include <string>
#include <iostream>

// ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------

class Filter
{
private:
    std::string field_name;
    std::string value;
    std::string action;

public:
    Filter(const std::string &_field_name, const std::string &_value, const std::string &_action = "\"==\"")
     : field_name(_field_name), value(_value),action(_action){}
    ~Filter(){}

    const std::string * get_field_name(){ return &field_name;}
    const std::string * get_value() { return &value;}
    const std::string * get_action() { return &action;}
};


#endif // FILTER_H
