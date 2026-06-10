#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include "character.h"
#include "item.h"
using namespace std;
// global objects
geders geders1;
refins refins1;
crafts crafts1;
gedering gedering1;
refining refining1;
crafting crafting1;
fighting fighting1;
inventory inventory1;

// global variables
int gatheringTier;
int refiningTier;
int whatCraft;
int craftingTier;
int fightingTier;
int timeEnd;

void addToInventory(string name, int amount){
    for(int i = 0; i < inventory1.items.size(); i++){
        if(inventory1.items[i].name == name){
            inventory1.items[i].number += amount;
            return;
        }
    }
    inventory1.putObjectsInventory(name, amount);
}

bool takeFromInventory(string name, int amount){
    for(int i = 0; i < inventory1.items.size(); i++){
        if(inventory1.items[i].name == name){
            if(inventory1.items[i].number >= amount){
                inventory1.items[i].number -= amount;
                return true;
            } else {
                cout << "Not enough " << name << "! Required: " << amount << " Available: " << inventory1.items[i].number << endl;
                return false;
            }
        }
    }
    cout << name << " not found in inventory!" << endl;
    return false;
}

void gather(int resource){
    time_t start = time(0);
    int gatheredAmount = 0;
    int gatheringExp = 0;
    int lastSecond = -1;

    string resourceName;
    vector<oreInfo>* resourceVec;
    switch(resource){
        case 1: resourceName = "Ore";     resourceVec = &geders1.ore;     break;
        case 2: resourceName = "Wood";    resourceVec = &geders1.wood;    break;
        case 3: resourceName = "Leather"; resourceVec = &geders1.leather; break;
        case 4: resourceName = "Wool";    resourceVec = &geders1.wool;    break;
    }

    int tier = gatheringTier - 1;
    while(true){
        if((int)difftime(time(0), start) >= timeEnd) break;
        int now = (int)difftime(time(0), start);
        if((int)fmod(now, (*resourceVec)[tier].durability * gedering1.gatheringSpeed) == 0 && now != lastSecond){
            int yield = (int)(gedering1.gatheringYield);
            gatheredAmount += yield;
            addToInventory((*resourceVec)[tier].name, yield);
            cout << resourceName << ": " << gatheredAmount << endl;
            gatheringExp += gatheredAmount * (*resourceVec)[tier].exp;
            cout << "Exp: " << gatheringExp << endl;
        }
    }
}

void refine(int resource){
    time_t start = time(0);
    int refinedAmount = 0;
    int refiningExp = 0;
    int lastSecond = -1;

    string rawName;
    string refinedName;
    vector<oreInfo>*   rawVec;
    vector<refinInfo>* refinedVec;

    switch(resource){
        case 1: rawName = "oreT"+to_string(refiningTier);      refinedName = "barT"+to_string(refiningTier);            rawVec = &geders1.ore;     refinedVec = &refins1.bar;            break;
        case 2: rawName = "woodT"+to_string(refiningTier);     refinedName = "plankT"+to_string(refiningTier);          rawVec = &geders1.wood;    refinedVec = &refins1.plank;          break;
        case 3: rawName = "leatherT"+to_string(refiningTier);  refinedName = "refinedLeatherT"+to_string(refiningTier); rawVec = &geders1.leather; refinedVec = &refins1.refinedLeather; break;
        case 4: rawName = "woolT"+to_string(refiningTier);     refinedName = "fabricT"+to_string(refiningTier);         rawVec = &geders1.wool;    refinedVec = &refins1.fabric;         break;
    }

    int tier = refiningTier - 1;
    while(true){
        if((int)difftime(time(0), start) >= timeEnd) break;
        int now = (int)difftime(time(0), start);
        if(now != lastSecond){
            lastSecond = now;
            if(!takeFromInventory(rawName, 1)) break;
            int amount = (int)(refining1.refiningEfficiency);
            refinedAmount += amount;
            addToInventory(refinedName, amount);
            cout << refinedName << ": " << refinedAmount << endl;
            refiningExp += refinedAmount * (*refinedVec)[tier].exp;
            cout << "Exp: " << refiningExp << endl;
        }
    }
}

void craft(){
    time_t start = time(0);
    int craftedAmount = 0;
    int lastSecond = -1;

    string itemName;
    vector<toolInfo>*  toolVec  = nullptr;
    vector<armorInfo>* armorVec = nullptr;

    switch(whatCraft){
        case 1: itemName = "Axe";        toolVec  = &crafts1.axe;        break;
        case 2: itemName = "Pickaxe";    toolVec  = &crafts1.pick;       break;
        case 3: itemName = "Sword";      toolVec  = &crafts1.sword;      break;
        case 4: itemName = "Helmet";     armorVec = &crafts1.helmet;     break;
        case 5: itemName = "Chestplate"; armorVec = &crafts1.chestplate; break;
        case 6: itemName = "Leggings";   armorVec = &crafts1.leggings;   break;
        case 7: itemName = "Boots";      armorVec = &crafts1.boots;      break;
    }

    int tier = craftingTier - 1;
    string tierStr = to_string(craftingTier);

    while(true){
        if((int)difftime(time(0), start) >= timeEnd) break;
        int now = (int)difftime(time(0), start);
        if(now != lastSecond){
            lastSecond = now;
            bool canCraft = false;

            switch(whatCraft){
                case 1: case 2:
                    canCraft = takeFromInventory("plankT"+tierStr, 6) && takeFromInventory("barT"+tierStr, 2);
                    break;
                case 3:
                    canCraft = takeFromInventory("barT"+tierStr, 20) && takeFromInventory("refinedLeatherT"+tierStr, 12);
                    break;
                case 4: case 5: case 6: case 7:
                    canCraft = takeFromInventory("barT"+tierStr, 8);
                    break;
            }

            if(canCraft){
                craftedAmount++;
                addToInventory(itemName+"T"+tierStr, 1);
                cout << itemName << " T" << craftingTier << " crafted! Total: " << craftedAmount << endl;
            } else {
                break;
            }
        }
    }
}

int main(){
        InitWindow(1280, 720, "Idol Game");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Idol Game", 100, 100, 40, WHITE);
        EndDrawing();
    }

    CloseWindow();
}