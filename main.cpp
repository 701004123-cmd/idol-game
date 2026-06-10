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

    int screen = 0; // 0=menu, 1=gather, 2=refine, 3=craft, 4=inventory
    bool gathering = false;
    float gatherProgress = 0.0f;
    double gatherStart = 0.0;
    int totalGathered = 0;

    // menu buttons
    Rectangle btnGather    = {490, 200, 300, 60};
    Rectangle btnRefine    = {490, 290, 300, 60};
    Rectangle btnCraft     = {490, 380, 300, 60};
    Rectangle btnInventory = {490, 470, 300, 60};

    // tier buttons
    Rectangle tierBtns[8];
    for(int i = 0; i < 8; i++){
        tierBtns[i] = {100.0f + i * 140.0f, 300, 120, 60};
    }

    // start/stop button
    Rectangle btnStart = {540, 500, 200, 60};

    // back button
    Rectangle btnBack = {20, 20, 100, 40};

    const char* pickNames[8] = {"Stone Pick", "Copper Pick", "Iron Pick", "Steel Pick", "Titanium Pick", "Mithril Pick", "Adamant Pick", "Dragon Pick"};

    while(!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        float dt = GetFrameTime();

        // gathering progress update
        if(gathering && gatheringTier > 0){
            float duration = geders1.ore[gatheringTier-1].durability * gedering1.gatheringSpeed;
            gatherProgress += dt / duration;
            if(gatherProgress >= 1.0f){
                gatherProgress = 0.0f;
                int yield = (int)(gedering1.gatheringYield);
                totalGathered += yield;
                addToInventory(geders1.ore[gatheringTier-1].name, yield);
            }
        }

        // input
        if(screen == 0){
            if(clicked){
                if(CheckCollisionPointRec(mouse, btnGather))    { screen = 1; gathering = false; gatherProgress = 0; totalGathered = 0; }
                if(CheckCollisionPointRec(mouse, btnRefine))    screen = 2;
                if(CheckCollisionPointRec(mouse, btnCraft))     screen = 3;
                if(CheckCollisionPointRec(mouse, btnInventory)) screen = 4;
            }
        }
        else if(screen == 1){
            if(clicked){
                if(CheckCollisionPointRec(mouse, btnBack)){ screen = 0; gathering = false; }
                for(int i = 0; i < 8; i++){
                    if(CheckCollisionPointRec(mouse, tierBtns[i])) gatheringTier = i + 1;
                }
                if(CheckCollisionPointRec(mouse, btnStart)) gathering = !gathering;
            }
        }
        else{
            if(clicked && CheckCollisionPointRec(mouse, btnBack)) screen = 0;
        }

        BeginDrawing();
        ClearBackground({20, 20, 20, 255});

        if(screen == 0){
            DrawText("IDOL GAME", 500, 100, 50, WHITE);

            Color cG = CheckCollisionPointRec(mouse, btnGather) ? GRAY : DARKGRAY;
            DrawRectangleRec(btnGather, cG);
            DrawText("GATHERING", 545, 218, 25, WHITE);

            Color cR = CheckCollisionPointRec(mouse, btnRefine) ? GRAY : DARKGRAY;
            DrawRectangleRec(btnRefine, cR);
            DrawText("REFINING", 552, 308, 25, WHITE);

            Color cC = CheckCollisionPointRec(mouse, btnCraft) ? GRAY : DARKGRAY;
            DrawRectangleRec(btnCraft, cC);
            DrawText("CRAFTING", 552, 398, 25, WHITE);

            Color cI = CheckCollisionPointRec(mouse, btnInventory) ? GRAY : DARKGRAY;
            DrawRectangleRec(btnInventory, cI);
            DrawText("INVENTORY", 545, 488, 25, WHITE);
        }
        else if(screen == 1){
            DrawText("GATHERING", 530, 50, 40, WHITE);

            // back
            DrawRectangleRec(btnBack, DARKGRAY);
            DrawText("BACK", 38, 30, 20, WHITE);

            // tier buttons
            DrawText("Select Tier:", 100, 260, 25, LIGHTGRAY);
            for(int i = 0; i < 8; i++){
                Color c = (gatheringTier == i+1) ? GOLD : (CheckCollisionPointRec(mouse, tierBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(tierBtns[i], c);
                DrawText(TextFormat("T%d", i+1), (int)tierBtns[i].x + 45, (int)tierBtns[i].y + 18, 25, WHITE);
            }

            // required tool
            if(gatheringTier > 0){
                DrawText("Required Tool:", 100, 400, 25, LIGHTGRAY);
                DrawText(pickNames[gatheringTier-1], 100, 435, 25, YELLOW);
            }

            // progress bar
            DrawText("Progress:", 100, 510, 25, LIGHTGRAY);
            DrawRectangle(100, 540, 800, 40, DARKGRAY);
            DrawRectangle(100, 540, (int)(800 * gatherProgress), 40, GREEN);
            DrawRectangleLines(100, 540, 800, 40, WHITE);

            // total gathered
            DrawText(TextFormat("Gathered: %d", totalGathered), 100, 595, 25, WHITE);

            // start/stop button
            Color cBtn = gathering ? RED : GREEN;
            DrawRectangleRec(btnStart, cBtn);
            DrawText(gathering ? "STOP" : "START", gathering ? 600 : 595, 518, 25, WHITE);
        }
        else if(screen == 2){
            DrawText("REFINING", 540, 50, 40, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY);
            DrawText("BACK", 38, 30, 20, WHITE);
        }
        else if(screen == 3){
            DrawText("CRAFTING", 540, 50, 40, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY);
            DrawText("BACK", 38, 30, 20, WHITE);
        }
        else if(screen == 4){
            DrawText("INVENTORY", 520, 50, 40, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY);
            DrawText("BACK", 38, 30, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}