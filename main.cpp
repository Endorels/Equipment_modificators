#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include "invenroty_equip_items.h"

inline  std::vector<std::string> explode(std::string source, std::string separator, bool empty = true)
  {
    std::vector<std::string> out;

    std::string::size_type pos = 0;
    std::string::size_type find_pos;

    find_pos = source.find(separator, pos);

    while(find_pos != source.npos)
    {
      if(pos != find_pos)
      {
        out.push_back(source.substr(pos, find_pos - pos));
      }
      else
      {
        if(empty == true)
        {
            out.push_back("");
        }
      }
      pos = find_pos + separator.length();
      find_pos = source.find(separator, pos);
    }

    std::string tmp = source.substr(pos);
    out.push_back(source.substr(pos));

    return out;
  };

std::vector<std::shared_ptr<inventory_equip_item>> get_inventory(const std::string &path, std::vector<std::shared_ptr<modificator>> &mods_mass)
{
    std::vector<std::shared_ptr<inventory_equip_item>> inventory;

    std::string line;
    std::ifstream in(path.c_str());
    if (in.is_open())
    {
        while (getline(in, line))
        {
            line.erase(std::find(line.begin(),line.end(),'}') + 1, line.end());
            line.erase(std::remove(line.begin(),line.end(),'}'), line.end());
            line.erase(std::remove(line.begin(),line.end(),' '), line.end());
            line.erase(std::remove(line.begin(),line.end(),'{'), line.end());

            auto expl = explode(line,",", false);
            // --- create equp items
            switch (expl.size())
            {
            case 5: // Armor
            {
                try
                {
                    std::string ident = explode(expl[0],":",false)[1];
                    std::string type = explode(expl[1],":",false)[1];
                    int level = std::stoi(explode(expl[2],":",false)[1]);
                    std::string rarity = explode(expl[3],":",false)[1];
                    double protection = std::stod(explode(expl[4],":",false)[1]);

                    auto item = std::make_shared<armor>(std::make_shared<armor_struct>(ident, type, level, rarity, protection), mods_mass);
                    inventory.push_back(item);
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                    in.close();
                }
                break;
            }
            case 6: // Weapon
            {
                try
                {
                    std::string ident = explode(expl[0],":",false)[1];
                    std::string type = explode(expl[1],":",false)[1];
                    int level = std::stoi(explode(expl[2],":",false)[1]);
                    std::string rarity = explode(expl[3],":",false)[1];
                    double damage = std::stod(explode(expl[4],":",false)[1]);
                    double speed = std::stod(explode(expl[5],":",false)[1]);

                    auto item = std::make_shared<weapon>(std::make_shared<weapon_struct>(ident, type, level, rarity, damage, speed), mods_mass);
                    inventory.push_back(item);
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                    in.close();
                }
                break;
            }
            }
        }
    }
    in.close();

    return  inventory;
}

std::vector<std::shared_ptr<modificator>> get_modificators(const std::string &path)
{
    std::vector<std::shared_ptr<modificator>> modificators;

    std::string line;
    std::ifstream in(path.c_str());
    if (in.is_open())
    {
        while (getline(in, line))
        {
            // -- modify string
            line.erase(std::remove(line.begin(),line.end(),' '), line.end());
            if(line.back() == ',')
                line.pop_back();
            if(line.back() == '}')
                line.pop_back();
            if(line.front() == '{')
                line = line.substr(1,line.size());

            // -- take out filters
            auto start_filt = std::find(line.begin(),line.end(),'[');
            auto end_filt = std::find(line.begin(),line.end(),']');
            std::string filters = "";
            for(auto it = start_filt+1; it != end_filt; ++it)
                filters += *it;

            // -- write filters in vector
            std::vector<filter> filters_vect;

            bool search = true;
            while (search)
            {
                auto start = std::find(filters.begin(),filters.end(),'{');
                auto end = std::find(filters.begin(),filters.end(),'}');
                if(start == filters.end() || end == filters.end())         // end of search
                {
                    search = false;
                    break;
                }

                std::string filt_curr = "";
                for(auto it = start+1; it != end; ++it)
                    filt_curr += *it;

                auto split = explode(filt_curr, ",", false);
                switch (split.size())
                {
                case 2:
                {
                    filters_vect.push_back(filter(split[0],split[1]));
                    break;
                }
                case 3:
                {
                    filters_vect.push_back(filter(split[0],split[2],split[1]));
                    break;
                }
                }

                filters.erase(start,end+1);
            }


            // -- erase info about filters
            line.erase(start_filt,end_filt+1);

            auto vect = explode(line,",", false);
            switch (vect.size())
            {
            case 4:
            {
                try
                {
                    std::string ident = explode(vect[0],":",false)[1];
                    std::string type = explode(vect[2], ":", false)[1];
                    double value = std::stod(explode(vect[3], ":", false)[1]);

                    auto mod = std::make_shared<modificator>(ident, type, value, filters_vect);
                    modificators.push_back(mod);
                }
                catch (std::exception &e)
                {
                    std::cout << e.what() << std::endl;
                    in.close();
                }

            }
            }
        }
    }
    in.close();

     return modificators;
}

int main()
{
    // -- get modificators from file
    std::vector<std::shared_ptr<modificator>> mods_(get_modificators("C:\\C++\\Inventory\\resourses\\modificators.txt"));

    // --- put in inventory
    std::vector<std::shared_ptr<inventory_equip_item>> inventory(get_inventory("C:\\C++\\Inventory\\resourses\\inventory.txt", mods_));

    // --- equip / unequip
    for(auto &it : inventory)
    {
        it->equip();
        it->unequip();
    }

    return 0;
}
