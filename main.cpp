#include <iostream>
#include <memory>
#include <vector>
#include "invenroty_equip_items.h"

int main()
{
    // --- create modificators
    modificator mod1("eagle_eye","DamageBuff", 10, std::vector<filter>{filter("level", "4", ">="),filter("type", "Range")});
    modificator mod2("donatium_steel","ProtectionBuff", 15, std::vector<filter>{filter("rarity", "Rare")});
    modificator mod3("rage_drink","SpeedBuff", 0.4, std::vector<filter>{filter("type", "Range"),filter("type", "Melee")});

    std::vector<modificator> mods_mass;
    mods_mass.reserve(10);
    mods_mass.push_back(mod1);
    mods_mass.push_back(mod2);
    mods_mass.push_back(mod3);


    // --- create equp items
    weapon item1(std::make_shared<weapon_struct>("axe_01", "Melee", 3, "Common", 12.0, 0.9), mods_mass);
    weapon item2(std::make_shared<weapon_struct>("revolver_01", "Range", 5, "Common", 42.0, 2.0), mods_mass);
    weapon item3(std::make_shared<weapon_struct>("revolver_02", "Range", 3, "Rare", 50.0, 2.1), mods_mass);
    weapon item4(std::make_shared<weapon_struct>("machinegun_01", "Range", 5, "Epic", 83.1, 10.0), mods_mass);
    armor item5(std::make_shared<armor_struct>("jacket_01", "Armour", 2, "Common", 2.0), mods_mass);
    armor item6(std::make_shared<armor_struct>("bulletprof_vest_01", "Armour", 5, "Rare", 30.0), mods_mass);

    // --- put in inventory
    std::vector<inventory_equip_item*> inventory_stash;
    inventory_stash.reserve(10);
    inventory_stash.push_back(&item1);
    inventory_stash.push_back(&item2);
    inventory_stash.push_back(&item3);
    inventory_stash.push_back(&item4);
    inventory_stash.push_back(&item5);
    inventory_stash.push_back(&item6);

    // --- equip / unequip
    for(auto &it : inventory_stash)
    {
        it->equip();
        it->unequip();
    }

    return 0;
}
