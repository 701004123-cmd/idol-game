#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct oreInfo{
    string name;
    int durability;
    int exp;
};

struct refinInfo{
    string name;
    int exp;
};

struct toolInfo{
    string name;
    int speed;
};

struct armorInfo{
    string name;
    int defense;
};

class geders{
    public:
        vector<oreInfo> ore = {
            {"oreT1", 1, 10},
            {"oreT2", 2, 50},
            {"oreT3", 3, 100},
            {"oreT4", 4, 500},
            {"oreT5", 5, 1000},
            {"oreT6", 6, 5000},
            {"oreT7", 7, 10000},
            {"oreT8", 8, 50000000}
        };
        vector<oreInfo> wood = {
            {"woodT1", 1, 10},
            {"woodT2", 2, 50},
            {"woodT3", 3, 100},
            {"woodT4", 4, 500},
            {"woodT5", 5, 1000},
            {"woodT6", 6, 5000},
            {"woodT7", 7, 10000},
            {"woodT8", 8, 50000000}
        };
        vector<oreInfo> leather = {
            {"leatherT1", 1, 10},
            {"leatherT2", 2, 50},
            {"leatherT3", 3, 100},
            {"leatherT4", 4, 500},
            {"leatherT5", 5, 1000},
            {"leatherT6", 6, 5000},
            {"leatherT7", 7, 10000},
            {"leatherT8", 8, 50000000}
        };
        vector<oreInfo> wool = {
            {"woolT1", 1, 10},
            {"woolT2", 2, 50},
            {"woolT3", 3, 100},
            {"woolT4", 4, 500},
            {"woolT5", 5, 1000},
            {"woolT6", 6, 5000},
            {"woolT7", 7, 10000},
            {"woolT8", 8, 50000000}
        };
};

class refins{
    public:
        vector<refinInfo> bar = {
            {"barT1", 10},
            {"barT2", 50},
            {"barT3", 100},
            {"barT4", 500},
            {"barT5", 1000},
            {"barT6", 5000},
            {"barT7", 10000},
            {"barT8", 50000000}
        };
        vector<refinInfo> plank = {
            {"plankT1", 10},
            {"plankT2", 50},
            {"plankT3", 100},
            {"plankT4", 500},
            {"plankT5", 1000},
            {"plankT6", 5000},
            {"plankT7", 10000},
            {"plankT8", 50000000}
        };
        vector<refinInfo> refinedLeather = {
            {"refinedLeatherT1", 10},
            {"refinedLeatherT2", 50},
            {"refinedLeatherT3", 100},
            {"refinedLeatherT4", 500},
            {"refinedLeatherT5", 1000},
            {"refinedLeatherT6", 5000},
            {"refinedLeatherT7", 10000},
            {"refinedLeatherT8", 50000000}
        };
        vector<refinInfo> fabric = {
            {"fabricT1", 10},
            {"fabricT2", 50},
            {"fabricT3", 100},
            {"fabricT4", 500},
            {"fabricT5", 1000},
            {"fabricT6", 5000},
            {"fabricT7", 10000},
            {"fabricT8", 50000000}
        };

        int durability = 1;
};

class crafts{
    public:
        vector<toolInfo> axe = {
            {"axeT1", 2},
            {"axeT2", 4},
            {"axeT3", 6},
            {"axeT4", 8},
            {"axeT5", 10},
            {"axeT6", 12},
            {"axeT7", 14}, 
            {"axeT8", 16}
        };
        vector<toolInfo> pick = {
            {"pickT1", 2}, 
            {"pickT2", 4}, 
            {"pickT3", 6}, 
            {"pickT4", 8},
            {"pickT5", 10}, 
            {"pickT6", 12}, 
            {"pickT7", 14}, 
            {"pickT8", 16}
        };
        vector<toolInfo> sword = {
            {"swordT1", 10}, 
            {"swordT2", 50}, 
            {"swordT3", 100}, 
            {"swordT4", 500},
            {"swordT5", 1000}, 
            {"swordT6", 5000}, 
            {"swordT7", 10000}, 
            {"swordT8", 50000}
        };
        vector<armorInfo> helmet = {
            {"helmetT1", 10}, 
            {"helmetT2", 50}, 
            {"helmetT3", 100}, 
            {"helmetT4", 500},
            {"helmetT5", 1000}, 
            {"helmetT6", 5000}, 
            {"helmetT7", 10000}, 
            {"helmetT8", 50000}
        };
        vector<armorInfo> chestplate = {
            {"chestplateT1", 10}, 
            {"chestplateT2", 50}, 
            {"chestplateT3", 100}, 
            {"chestplateT4", 500},
            {"chestplateT5", 1000}, 
            {"chestplateT6", 5000}, 
            {"chestplateT7", 10000}, 
            {"chestplateT8", 50000}
        };
        vector<armorInfo> leggings = {
            {"leggingsT1", 10}, 
            {"leggingsT2", 50}, 
            {"leggingsT3", 100}, 
            {"leggingsT4", 500},
            {"leggingsT5", 1000},
             {"leggingsT6", 5000}, 
             {"leggingsT7", 10000}, 
             {"leggingsT8", 50000}
        };
        vector<armorInfo> boots = {
            {"bootsT1", 10}, 
            {"bootsT2", 50}, 
            {"bootsT3", 100}, 
            {"bootsT4", 500},
            {"bootsT5", 1000}, 
            {"bootsT6", 5000}, 
            {"bootsT7", 10000}, 
            {"bootsT8", 50000}
        };
};