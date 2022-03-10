#ifndef FILTER_H
#define FILTER_H
#include <string>

class filter
{
public:
    std::string field_name;
    std::string value;
    std::string action;

    filter(const std::string &_field_name, const std::string &_value, const std::string &_action = "\"==\"")
     : field_name(_field_name), value(_value),action(_action){}
    ~filter(){}
};


#endif // FILTER_H
