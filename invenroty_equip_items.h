#ifndef INVENROTY_EQUIP_ITEMS_H
#define INVENROTY_EQUIP_ITEMS_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "modificators.h"
#include "equip_item_structs.h"

class inventory_equip_item
{
public:
    inventory_equip_item(){}
    virtual ~inventory_equip_item(){}

    virtual void equip() = 0;
    virtual void unequip() = 0;
    virtual void show_modificators() = 0;

};


class weapon : public inventory_equip_item
{
private:
   std::shared_ptr<weapon_struct> item;
   std::vector<std::shared_ptr<modificator>> modificators;

public:
    weapon() = delete;
    weapon(std::shared_ptr<weapon_struct>weapon_str, std::vector<std::shared_ptr<modificator>> &mods) : item(weapon_str), modificators(mods){}
    ~weapon(){}

    void equip()
    {
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
        std::cout << " - Weapon " << *item->get_ident() << " equipped." << std::endl;
        show_modificators();
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    }

    void unequip()
    {
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
        std::cout << " - Weapon " << *item->get_ident() << " unequipped." << std::endl;
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    }

    void show_modificators()
    {
        for(auto &it : modificators)
        {
            std::cout << "[ Weapon Mod : " << it->ident << " | Type : " << it->type <<  " | Value : " << it->value << " ]" << std::endl;
        }
    }
};

class armor : public inventory_equip_item
{
private:
   std::shared_ptr<armor_struct> item;
   std::vector<std::shared_ptr<modificator>> modificators;


public:
    armor() = delete;
    armor(std::shared_ptr<armor_struct>armor_str, std::vector<std::shared_ptr<modificator>> &mods) : item(armor_str), modificators(mods){}
    ~armor(){}

    void equip()
    {
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
        std::cout << " - Armor " << *item->get_ident() << " equipped." << std::endl;
        show_modificators();
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    }

    void unequip()
    {
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
        std::cout << " - Armor " << *item->get_ident() << " unequipped." << std::endl;
        std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
    }

    void show_modificators()
    {
        for(auto &it : modificators)
        {
            std::cout << "[ Armor Mod : " << it->ident << " | Type : " << it->type <<  " | Value : " << it->value << " ]" << std::endl;
        }
    }
};

#endif // INVENROTY_EQUIP_ITEMS_H
