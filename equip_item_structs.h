#ifndef EQUIP_ITEM_STRUCTS_H
#define EQUIP_ITEM_STRUCTS_H

#include <string>

class equip_item_struct
{
public:
    equip_item_struct(){}
    virtual ~equip_item_struct(){}
};

class weapon_struct : public equip_item_struct
{
private:
    std::string ident;
    std::string type;
    int level;
    std::string rarity;
    double damage;
    double speed;

public:
    weapon_struct() = delete;
     explicit weapon_struct(const std::string &_ident,const std::string &_type,const int &_level, const std::string &_rarity, const double &_damage,const double &_speed) :
        ident(_ident), type(_type), level(_level), rarity(_rarity), damage(_damage), speed(_speed){}
    ~weapon_struct(){}

    const std::string * get_ident() { return &ident;}
    const std::string * get_type() { return &type;}
    const std::string * get_rarity() { return &rarity;}
    const int * get_level() { return &level;}
};

class armor_struct : public equip_item_struct
{
private:
    std::string  ident;
    std::string type;
    int level;
    std::string rarity;
    double protection;

public:
    armor_struct() = delete;
     explicit armor_struct(const std::string &_ident,const std::string &_type,const int &_level, const std::string &_rarity, const double &_protection) :
        ident(_ident), type(_type), level(_level), rarity(_rarity), protection(_protection){}
    ~armor_struct(){}

    const std::string * get_ident() { return &ident;}
    const std::string * get_type() { return &type;}
    const std::string * get_rarity() { return &rarity;}
    const int * get_level() { return &level;}
};


#endif // EQUIP_ITEM_STRUCTS_H
