#pragma once
#include <iostream>
#include <vector>
#include "level.h"
using namespace std;

class character{
    public:
        string name;
        int gold;
};

class gedering: public character{
    public:
        level gatheringLevel;
        float gatheringSpeed;
        float gatheringYield;
        gedering(){
            gatheringSpeed = 1 + (gatheringLevel.level * 0.5f);
            gatheringYield = 1 + (gatheringLevel.level * 0.05f);
        }
};

class refining: public character{
    public:
        level refiningLevel;
        float refiningEfficiency;
        refining(){
            refiningEfficiency = 1 + (refiningLevel.level * 0.05f);
        }
};

class crafting: public character{
    public:
        level craftingLevel;
        float craftingEfficiency;
        crafting(){
            craftingEfficiency = 1 + (craftingLevel.level * 0.05f);
        }
};

class fighting: public character{
    public:
        level fightingLevel;
        float fightingMastery;
        fighting(){
            fightingMastery = 1 + (fightingLevel.level * 0.01f);
        }
};

struct inventoryItem{
    string name;
    int number;
};

class inventory: public character{
    public:
        vector<inventoryItem> items;
        void putObjectsInventory(string name, int number){
            inventoryItem item;
            item.name = name;
            item.number = number;
            items.push_back(item);
        }
};