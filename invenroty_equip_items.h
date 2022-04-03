#ifndef INVENROTY_EQUIP_ITEMS_H
#define INVENROTY_EQUIP_ITEMS_H

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <string>
#include "modificators.h"
#include "equip_item_structs.h"

// ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------------------
// ------------    Abstract Equip item class
// ----------------------------------------------------------------------------------------------------------

class Inventory_equip_item
{
    equip_item_struct * item;
    std::set<std::shared_ptr<Modificator>> modificators;

public:
    Inventory_equip_item(equip_item_struct * _item, std::vector<std::shared_ptr<Modificator>> &mods) : item(_item) { get_modificator(mods);}
    virtual ~Inventory_equip_item(){}

    bool check_values(const std::string &action, const std::string &value_this, const std::string &value_comp);
    bool check_values(const std::string &action, const int &value_this, const int &value_comp);

    virtual void get_modificator(std::vector<std::shared_ptr<Modificator>> &mods);
    virtual void show_modificators();
    virtual void equip() = 0;
    virtual void unequip() = 0;
};

bool Inventory_equip_item::check_values(const std::string &action, const std::string &value_this, const std::string &value_comp)
{
    if(action == "\"==\"")
        return value_this == value_comp;

    if(action == "\"<\"")
        return value_this < value_comp;

    if(action == "\">\"")
        return value_this > value_comp;

    if(action == "\"<=\"")
        return value_this <= value_comp;

    if(action == "\">=\"")
        return value_this >= value_comp;

    return false;
}

bool Inventory_equip_item::check_values(const std::string &action, const int &value_this, const int &value_comp)
{
    if(action == "\"==\"")
        return value_this == value_comp;

    if(action == "\"<\"")
        return value_this < value_comp;

    if(action == "\">\"")
        return value_this > value_comp;

    if(action == "\"<=\"")
        return value_this <= value_comp;

    if(action == "\">=\"")
        return value_this >= value_comp;

    return false;
}

// ----------------------------------------------------------------------------------------------------------
// ------------    Weapon class
// ----------------------------------------------------------------------------------------------------------

class Weapon : public Inventory_equip_item
{
private:
   std::shared_ptr<weapon_struct> item;

public:
    Weapon() = delete;
    Weapon(std::shared_ptr<weapon_struct>weapon_str, std::vector<std::shared_ptr<Modificator>> &mods);
    ~Weapon();

    void equip();
    void unequip();

};

Weapon::Weapon(std::shared_ptr<weapon_struct>weapon_str, std::vector<std::shared_ptr<Modificator>> &mods) : Inventory_equip_item(weapon_str.get(), mods), item(weapon_str){}
Weapon::~Weapon(){}
void Weapon::equip()
{
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    std::cout << " - Weapon " << *item->get_ident() << " equipped." << std::endl;
    show_modificators();
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Weapon::unequip()
{
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    std::cout << " - Weapon " << *item->get_ident() << " unequipped." << std::endl;
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

// ----------------------------------------------------------------------------------------------------------
// ------------    Armor class
// ----------------------------------------------------------------------------------------------------------

class Armor : public Inventory_equip_item
{
private:
   std::shared_ptr<armor_struct> item;

public:
    Armor() = delete;
    Armor(std::shared_ptr<armor_struct>armor_str, std::vector<std::shared_ptr<Modificator>> mods);
    ~Armor();

    void equip();
    void unequip();

};

Armor::~Armor(){}
Armor::Armor(std::shared_ptr<armor_struct>armor_str, std::vector<std::shared_ptr<Modificator>> mods) : Inventory_equip_item(armor_str.get(), mods), item(armor_str){}

void Armor::equip()
{
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    std::cout << " - Armor " << *item->get_ident() << " equipped." << std::endl;
    show_modificators();
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Armor::unequip()
{
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    std::cout << " - Armor " << *item->get_ident() << " unequipped." << std::endl;
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

// ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------

void Inventory_equip_item::get_modificator(std::vector<std::shared_ptr<Modificator>> &mods)
{
    for(auto &it : mods)
    {
        for(auto &it2 : *it->get_mass())
        {
            if(*it2->get_field_name() == "\"level\"")
            {
                if(check_values(*it2->get_action(), *item->get_level(), std::stoi(*it2->get_value())))
                {
                    modificators.emplace(it);
                    break;
                }
            }
            else if(*it2->get_field_name() == "\"type\"")
            {
               if(check_values(*it2->get_action(), *item->get_type(), *it2->get_value()))
               {
                   modificators.emplace(it);
                   break;
               }
            }
            else if(*it2->get_field_name() == "\"rarity\"")
            {
               if(check_values(*it2->get_action(), *item->get_rarity(), *it2->get_value()))
               {
                   modificators.emplace(it);
                   break;
               }
            }
        }
    }
}

void Inventory_equip_item::show_modificators()
{
    for(auto &it : modificators)
    {
        std::cout << "[ Modificator : " << *it->get_ident() << " | Type : " << *it->get_type() <<  " | Value : " << *it->get_value() << " ]" << std::endl;
    }
}

#endif // INVENROTY_EQUIP_ITEMS_H
