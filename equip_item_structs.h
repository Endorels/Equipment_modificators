#ifndef EQUIP_ITEM_STRUCTS_H
#define EQUIP_ITEM_STRUCTS_H

#include <string>
#include <iostream>

class equip_item_struct
{
private:
    std::string ident;
    std::string type;
    int level;
    std::string rarity;

public:
    equip_item_struct(const std::string &_ident,const std::string &_type,const int &_level, const std::string &_rarity) : ident(_ident), type(_type), level(_level), rarity(_rarity){}
    virtual ~equip_item_struct();

    const std::string * get_ident(){ return &ident;}
    const std::string * get_type() { return &type;}
    const std::string * get_rarity() { return &rarity;}
    const int * get_level() { return &level;}
};

equip_item_struct::~equip_item_struct() {}

class weapon_struct : public equip_item_struct
{
private:
    double damage;
    double speed;

public:
    weapon_struct() = delete;
    weapon_struct(const std::string &_ident,const std::string &_type,const int &_level, const std::string &_rarity, const double &_damage,const double &_speed) :
        equip_item_struct(_ident,_type, _level,_rarity), damage(_damage), speed(_speed){}
    ~weapon_struct();

    const double * get_damage() { return &damage;}
    const double * get_speed() { return &speed;}
};

weapon_struct::~weapon_struct(){}

class armor_struct : public equip_item_struct
{
private:
    double protection;

public:
    armor_struct() = delete;
    explicit armor_struct(const std::string &_ident,const std::string &_type,const int &_level, const std::string &_rarity, const double &_protection) :
        equip_item_struct(_ident,_type, _level,_rarity), protection(_protection){}
    ~armor_struct();

    const double * get_protection() { return &protection;}
};

armor_struct::~armor_struct(){}


#endif // EQUIP_ITEM_STRUCTS_H
