#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include "character.h"
#include "item.h"
using namespace std;

const char* tierName[8] = {"Stone","Copper","Iron","Steel","Titanium","Mithril","Adamant","Dragon"};

// ==== Global objects ====
geders    geders1;
refins    refins1;
crafts    crafts1;
gedering  gedering1;
refining  refining1;
crafting  crafting1;
fighting  fighting1;
inventory inventory1;

int gatheringTier = 0, refiningTier = 0;
int whatCraft = 0, craftingTier = 0, fightingTier = 0;

// ==== Inventory helpers ====
void addToInventory(string name, int amount){
    for(auto& it : inventory1.items)
        if(it.name == name){ it.number += amount; return; }
    inventory1.putObjectsInventory(name, amount);
}

bool takeFromInventory(string name, int amount){
    for(auto& it : inventory1.items)
        if(it.name == name){
            if(it.number >= amount){ it.number -= amount; return true; }
            return false;
        }
    return false;
}

int getFromInventory(string name){
    for(auto& it : inventory1.items)
        if(it.name == name) return it.number;
    return 0;
}

// ==== EXP bar ====
void drawExpBar(int x, int y, int w, int h, const level& lv, const char* label, Color col){
    float pct = (lv.expForNextLevel > 0) ? (float)lv.exprence / (float)lv.expForNextLevel : 0.f;
    if(pct > 1.f) pct = 1.f;
    DrawRectangle(x, y, w, h, DARKGRAY);
    DrawRectangle(x, y, (int)(w * pct), h, col);
    DrawRectangleLines(x, y, w, h, WHITE);
    DrawText(TextFormat("%s  Lv.%d   %d / %d EXP", label, lv.level, lv.exprence, lv.expForNextLevel),
             x + 6, y + h/2 - 9, 18, WHITE);
}

// ==== Main ====
int main(){
    InitWindow(1280, 720, "Idol Game");
    SetTargetFPS(60);

    int screen = 0; // 0=menu 1=gather 2=refine 3=craft 4=inventory

    // Gathering
    bool  gathering      = false;
    float gatherProgress = 0.f;
    int   totalGathered  = 0;
    int   gatherResource = 1; // 1=ore 2=wood 3=leather 4=wool

    // Refining
    bool  refining2      = false;
    float refineProgress = 0.f;
    int   totalRefined   = 0;
    int   refineResource = 1;

    // Crafting
    bool  crafting2     = false;
    float craftProgress = 0.f;
    int   totalCrafted  = 0;

    // ==== Buttons ====
    Rectangle btnBack  = {20, 20, 100, 40};
    Rectangle btnStart = {540, 560, 200, 50};

    Rectangle resBtns[4] = {
        {100,160,220,50},{340,160,220,50},{580,160,220,50},{820,160,220,50}
    };
    // No unicode arrows — ASCII only
    const char* resNames[4]    = {"Ore",        "Wood",         "Leather",          "Wool"};
    const char* refResNames[4] = {"Ore->Bar",   "Wood->Plank",  "Leather->Refined", "Wool->Fabric"};

    Rectangle tierBtns[8];
    for(int i=0;i<8;i++) tierBtns[i] = {100.f + i*140.f, 280, 120, 50};

    Rectangle craftItemBtns[9];
    for(int i=0;i<9;i++) craftItemBtns[i] = {100.f+(i%5)*230.f, 130.f+(i/5)*65.f, 210, 52};
    const char* craftNames[9] = {"Axe","Pick","Knife","Shears","Sword","Helmet","Chestplate","Leggings","Boots"};

    Rectangle btnGather    = {490, 180, 300, 55};
    Rectangle btnRefine    = {490, 255, 300, 55};
    Rectangle btnCraft     = {490, 330, 300, 55};
    Rectangle btnInventory = {490, 405, 300, 55};

    // Tool required per resource per tier
    const char* toolNames[4][8] = {
        {"Stone Pick","Copper Pick","Iron Pick","Steel Pick","Titanium Pick","Mithril Pick","Adamant Pick","Dragon Pick"},
        {"Stone Axe","Copper Axe","Iron Axe","Steel Axe","Titanium Axe","Mithril Axe","Adamant Axe","Dragon Axe"},
        {"Stone Knife","Copper Knife","Iron Knife","Steel Knife","Titanium Knife","Mithril Knife","Adamant Knife","Dragon Knife"},
        {"Stone Shears","Copper Shears","Iron Shears","Steel Shears","Titanium Shears","Mithril Shears","Adamant Shears","Dragon Shears"}
    };

    while(!WindowShouldClose()){
        Vector2 mouse   = GetMousePosition();
        bool    clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        float   dt      = GetFrameTime();

        // ==== Update: Gathering ====
        if(gathering && gatheringTier > 0){
            vector<oreInfo>* rv;
            switch(gatherResource){
                case 1: rv=&geders1.ore;     break;
                case 2: rv=&geders1.wood;    break;
                case 3: rv=&geders1.leather; break;
                default:rv=&geders1.wool;    break;
            }

            // Tool check — stop if required tool not in inventory
            string reqTool = toolNames[gatherResource-1][gatheringTier-1];
            if(getFromInventory(reqTool) < 1){
                gathering = false;
            } else {
                float dur = (float)(*rv)[gatheringTier-1].durability / (gedering1.gatheringSpeed);
                if(dur < 0.1f) dur = 0.1f;
                gatherProgress += dt / dur;
                if(gatherProgress >= 1.f){
                    gatherProgress = 0.f;
                    int yield = (int)gedering1.gatheringYield;
                    if(yield < 1) yield = 1;
                    totalGathered += yield;
                    addToInventory((*rv)[gatheringTier-1].name, yield);
                    // EXP from item.h
                    gedering1.gatheringLevel.levelUp((*rv)[gatheringTier-1].exp);
                    // Recalculate stats after level up
                    gedering1.gatheringSpeed = 1.f + (gedering1.gatheringLevel.level * 0.5f);
                    gedering1.gatheringYield = 1.f + (gedering1.gatheringLevel.level * 0.05f);
                }
            }
        }

        // ==== Update: Refining ====
        if(refining2 && refiningTier > 0 && refineResource > 0){
            float dur = (float)refins1.durability * refining1.refiningEfficiency;
            if(dur < 0.1f) dur = 1.f;
            refineProgress += dt / dur;
            if(refineProgress >= 1.f){
                refineProgress = 0.f;
                string tName = tierName[refiningTier-1];
                string rawName, refinedName;
                int    refExp = 0;
                switch(refineResource){
                    case 1: rawName=tName+" Ore";     refinedName=tName+" Bar";             refExp=refins1.bar[refiningTier-1].exp;             break;
                    case 2: rawName=tName+" Wood";    refinedName=tName+" Plank";           refExp=refins1.plank[refiningTier-1].exp;           break;
                    case 3: rawName=tName+" Leather"; refinedName=tName+" Refined Leather"; refExp=refins1.refinedLeather[refiningTier-1].exp;  break;
                    default:rawName=tName+" Wool";    refinedName=tName+" Fabric";          refExp=refins1.fabric[refiningTier-1].exp;          break;
                }
                if(!takeFromInventory(rawName, 1)){
                    refining2 = false;
                } else {
                    int amount = (int)refining1.refiningEfficiency;
                    if(amount < 1) amount = 1;
                    totalRefined += amount;
                    addToInventory(refinedName, amount);
                    // EXP
                    refining1.refiningLevel.levelUp(refExp);
                    refining1.refiningEfficiency = 1.f + (refining1.refiningLevel.level * 0.05f);
                }
            }
        }

        // ==== Update: Crafting ====
        if(crafting2 && craftingTier > 0 && whatCraft > 0){
            float dur = 2.f / crafting1.craftingEfficiency;
            if(dur < 0.2f) dur = 0.2f;
            craftProgress += dt / dur;
            if(craftProgress >= 1.f){
                craftProgress = 0.f;
                string tName = tierName[craftingTier-1];
                string itemName;
                bool ok = false;
                int  cExp = 0;
                switch(whatCraft){
                    case 1: itemName=tName+" Axe";        ok=takeFromInventory(tName+" Plank",6)&&takeFromInventory(tName+" Bar",2); cExp=crafts1.axe[craftingTier-1].speed*10;        break;
                    case 2: itemName=tName+" Pick";       ok=takeFromInventory(tName+" Plank",6)&&takeFromInventory(tName+" Bar",2); cExp=crafts1.pick[craftingTier-1].speed*10;       break;
                    case 3: itemName=tName+" Knife";      ok=takeFromInventory(tName+" Plank",4)&&takeFromInventory(tName+" Bar",2); cExp=crafts1.skinningKnife[craftingTier-1].speed*10; break;
                    case 4: itemName=tName+" Shears";     ok=takeFromInventory(tName+" Bar",4);                                      cExp=crafts1.shears[craftingTier-1].speed*10;     break;
                    case 5: itemName=tName+" Sword";      ok=takeFromInventory(tName+" Bar",20)&&takeFromInventory(tName+" Refined Leather",12); cExp=crafts1.sword[craftingTier-1].speed*10; break;
                    case 6: itemName=tName+" Helmet";     ok=takeFromInventory(tName+" Bar",8);  cExp=crafts1.helmet[craftingTier-1].defense*5;     break;
                    case 7: itemName=tName+" Chestplate"; ok=takeFromInventory(tName+" Bar",8);  cExp=crafts1.chestplate[craftingTier-1].defense*5;  break;
                    case 8: itemName=tName+" Leggings";   ok=takeFromInventory(tName+" Bar",8);  cExp=crafts1.leggings[craftingTier-1].defense*5;    break;
                    case 9: itemName=tName+" Boots";      ok=takeFromInventory(tName+" Bar",8);  cExp=crafts1.boots[craftingTier-1].defense*5;       break;
                }
                if(ok){
                    totalCrafted++;
                    addToInventory(itemName, 1);
                    // EXP
                    crafting1.craftingLevel.levelUp(cExp);
                    crafting1.craftingEfficiency = 1.f + (crafting1.craftingLevel.level * 0.05f);
                } else {
                    crafting2 = false;
                }
            }
        }

        // ==== Input ====
        if(screen == 0){
            if(clicked){
                if(CheckCollisionPointRec(mouse,btnGather))    { screen=1; gathering=false; gatherProgress=0; totalGathered=0; }
                if(CheckCollisionPointRec(mouse,btnRefine))    { screen=2; refining2=false; refineProgress=0; totalRefined=0; }
                if(CheckCollisionPointRec(mouse,btnCraft))     { screen=3; crafting2=false; craftProgress=0;  totalCrafted=0; }
                if(CheckCollisionPointRec(mouse,btnInventory))   screen=4;
            }
        }
        else if(screen == 1){
            if(clicked){
                if(CheckCollisionPointRec(mouse,btnBack)){ screen=0; gathering=false; }
                for(int i=0;i<4;i++)
                    if(CheckCollisionPointRec(mouse,resBtns[i])){ gatherResource=i+1; gathering=false; gatherProgress=0; totalGathered=0; }
                for(int i=0;i<8;i++)
                    if(CheckCollisionPointRec(mouse,tierBtns[i])){ gatheringTier=i+1; gathering=false; gatherProgress=0; totalGathered=0; }
                if(CheckCollisionPointRec(mouse,btnStart)){
                    // Only start if tool exists
                    if(!gathering && gatheringTier > 0){
                        string reqTool = toolNames[gatherResource-1][gatheringTier-1];
                        if(getFromInventory(reqTool) >= 1) gathering = true;
                    } else {
                        gathering = false;
                    }
                }
            }
        }
        else if(screen == 2){
            if(clicked){
                if(CheckCollisionPointRec(mouse,btnBack)){ screen=0; refining2=false; }
                for(int i=0;i<4;i++)
                    if(CheckCollisionPointRec(mouse,resBtns[i])){ refineResource=i+1; refining2=false; refineProgress=0; totalRefined=0; }
                for(int i=0;i<8;i++)
                    if(CheckCollisionPointRec(mouse,tierBtns[i])){ refiningTier=i+1; refining2=false; refineProgress=0; totalRefined=0; }
                if(CheckCollisionPointRec(mouse,btnStart)) refining2=!refining2;
            }
        }
        else if(screen == 3){
            if(clicked){
                if(CheckCollisionPointRec(mouse,btnBack)){ screen=0; crafting2=false; }
                for(int i=0;i<9;i++)
                    if(CheckCollisionPointRec(mouse,craftItemBtns[i])){ whatCraft=i+1; crafting2=false; craftProgress=0; totalCrafted=0; }
                for(int i=0;i<8;i++)
                    if(CheckCollisionPointRec(mouse,tierBtns[i])){ craftingTier=i+1; crafting2=false; craftProgress=0; totalCrafted=0; }
                if(CheckCollisionPointRec(mouse,btnStart)) crafting2=!crafting2;
            }
        }
        else if(screen == 4){
            if(clicked && CheckCollisionPointRec(mouse,btnBack)) screen=0;
        }

        // ==== Draw ====
        BeginDrawing();
        ClearBackground({20,20,20,255});

        // ---- Menu ----
        if(screen == 0){
            DrawText("IDOL GAME", 490, 40, 50, WHITE);

            // Nav buttons
            auto menuBtn = [&](Rectangle r, const char* lbl, Color hover){
                DrawRectangleRec(r, CheckCollisionPointRec(mouse,r) ? hover : DARKGRAY);
                int tw = MeasureText(lbl, 22);
                DrawText(lbl, (int)(r.x+r.width/2-tw/2), (int)(r.y+r.height/2-11), 22, WHITE);
            };
            menuBtn(btnGather,    "GATHERING", {80,160,80,255});
            menuBtn(btnRefine,    "REFINING",  {60,120,200,255});
            menuBtn(btnCraft,     "CRAFTING",  {200,120,30,255});
            menuBtn(btnInventory, "INVENTORY", GRAY);

            // All 4 skill bars
            drawExpBar(100, 490, 1080, 38, gedering1.gatheringLevel, "Gathering", {60,180,60,255});
            drawExpBar(100, 534, 1080, 38, refining1.refiningLevel,  "Refining",  {60,140,220,255});
            drawExpBar(100, 578, 1080, 38, crafting1.craftingLevel,  "Crafting",  {220,140,40,255});
            drawExpBar(100, 622, 1080, 38, fighting1.fightingLevel,  "Fighting",  {200,50,50,255});
        }

        // ---- Gathering ----
        else if(screen == 1){
            DrawText("GATHERING", 490, 15, 38, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY); DrawText("BACK", 35, 30, 20, WHITE);

            // Skill bar
            drawExpBar(100, 60, 1080, 32, gedering1.gatheringLevel, "Gathering", {60,180,60,255});

            // Resource
            DrawText("Resource:", 100, 108, 20, LIGHTGRAY);
            for(int i=0;i<4;i++){
                Color c = (gatherResource==i+1) ? GOLD : (CheckCollisionPointRec(mouse,resBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(resBtns[i], c);
                int tw = MeasureText(resNames[i], 20);
                DrawText(resNames[i], (int)(resBtns[i].x+resBtns[i].width/2-tw/2), (int)(resBtns[i].y+15), 20, WHITE);
            }

            // Tier
            DrawText("Tier:", 100, 248, 20, LIGHTGRAY);
            for(int i=0;i<8;i++){
                Color c = (gatheringTier==i+1) ? GOLD : (CheckCollisionPointRec(mouse,tierBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(tierBtns[i], c);
                DrawText(tierName[i], (int)tierBtns[i].x+5, (int)tierBtns[i].y+15, 15, WHITE);
            }

            // Info
            if(gatheringTier > 0){
                string reqTool = toolNames[gatherResource-1][gatheringTier-1];
                bool hasTool = getFromInventory(reqTool) >= 1;

                DrawText("Required tool:", 100, 345, 20, LIGHTGRAY);
                DrawText(reqTool.c_str(), 290, 345, 20, hasTool ? YELLOW : RED);
                DrawText(hasTool ? "(have)" : "(missing!)", 600, 345, 20, hasTool ? GREEN : RED);

                vector<oreInfo>* rv;
                switch(gatherResource){
                    case 1: rv=&geders1.ore; break; case 2: rv=&geders1.wood; break;
                    case 3: rv=&geders1.leather; break; default: rv=&geders1.wool; break;
                }
                DrawText(TextFormat("In inventory: %d", getFromInventory((*rv)[gatheringTier-1].name)), 100, 372, 20, LIGHTGRAY);
                DrawText(TextFormat("+%d EXP per gather", (*rv)[gatheringTier-1].exp), 100, 398, 18, {150,255,150,255});
            }

            // Progress bar
            DrawText("Progress:", 100, 430, 20, LIGHTGRAY);
            DrawRectangle(100, 454, 1080, 30, DARKGRAY);
            DrawRectangle(100, 454, (int)(1080*gatherProgress), 30, {60,200,60,255});
            DrawRectangleLines(100, 454, 1080, 30, WHITE);
            DrawText(TextFormat("Gathered this session: %d", totalGathered), 100, 490, 20, WHITE);

            // Start/Stop
            bool hasTool = (gatheringTier > 0) && (getFromInventory(toolNames[gatherResource-1][gatheringTier-1]) >= 1);
            Color cBtn = gathering ? RED : (hasTool ? GREEN : DARKGRAY);
            DrawRectangleRec(btnStart, cBtn);
            const char* lbl = gathering ? "STOP" : "START";
            DrawText(lbl, (int)(btnStart.x+btnStart.width/2-MeasureText(lbl,22)/2), (int)(btnStart.y+14), 22, WHITE);
        }

        // ---- Refining ----
        else if(screen == 2){
            DrawText("REFINING", 500, 15, 38, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY); DrawText("BACK", 35, 30, 20, WHITE);

            drawExpBar(100, 60, 1080, 32, refining1.refiningLevel, "Refining", {60,140,220,255});

            // Resource
            DrawText("Resource:", 100, 108, 20, LIGHTGRAY);
            for(int i=0;i<4;i++){
                Color c = (refineResource==i+1) ? GOLD : (CheckCollisionPointRec(mouse,resBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(resBtns[i], c);
                DrawText(refResNames[i], (int)resBtns[i].x+8, (int)resBtns[i].y+15, 17, WHITE);
            }

            // Tier
            DrawText("Tier:", 100, 248, 20, LIGHTGRAY);
            for(int i=0;i<8;i++){
                Color c = (refiningTier==i+1) ? GOLD : (CheckCollisionPointRec(mouse,tierBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(tierBtns[i], c);
                DrawText(tierName[i], (int)tierBtns[i].x+5, (int)tierBtns[i].y+15, 15, WHITE);
            }

            // Info
            if(refiningTier > 0 && refineResource > 0){
                string tName = tierName[refiningTier-1];
                string rawName, refinedName;
                int refExp = 0;
                switch(refineResource){
                    case 1: rawName=tName+" Ore";     refinedName=tName+" Bar";             refExp=refins1.bar[refiningTier-1].exp;            break;
                    case 2: rawName=tName+" Wood";    refinedName=tName+" Plank";           refExp=refins1.plank[refiningTier-1].exp;          break;
                    case 3: rawName=tName+" Leather"; refinedName=tName+" Refined Leather"; refExp=refins1.refinedLeather[refiningTier-1].exp; break;
                    default:rawName=tName+" Wool";    refinedName=tName+" Fabric";          refExp=refins1.fabric[refiningTier-1].exp;         break;
                }
                DrawText(TextFormat("Raw (%s): %d",     rawName.c_str(),     getFromInventory(rawName)),     100, 345, 20, LIGHTGRAY);
                DrawText(TextFormat("Refined (%s): %d", refinedName.c_str(), getFromInventory(refinedName)), 100, 372, 20, YELLOW);
                DrawText(TextFormat("+%d EXP per refine", refExp), 100, 398, 18, {150,200,255,255});
            }

            // Progress bar
            DrawText("Progress:", 100, 430, 20, LIGHTGRAY);
            DrawRectangle(100, 454, 1080, 30, DARKGRAY);
            DrawRectangle(100, 454, (int)(1080*refineProgress), 30, SKYBLUE);
            DrawRectangleLines(100, 454, 1080, 30, WHITE);
            DrawText(TextFormat("Refined this session: %d", totalRefined), 100, 490, 20, WHITE);

            // Start/Stop
            Color cBtn = refining2 ? RED : GREEN;
            DrawRectangleRec(btnStart, cBtn);
            const char* lbl = refining2 ? "STOP" : "START";
            DrawText(lbl, (int)(btnStart.x+btnStart.width/2-MeasureText(lbl,22)/2), (int)(btnStart.y+14), 22, WHITE);
        }

        // ---- Crafting ----
        else if(screen == 3){
            DrawText("CRAFTING", 500, 15, 38, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY); DrawText("BACK", 35, 30, 20, WHITE);

            drawExpBar(100, 60, 1080, 32, crafting1.craftingLevel, "Crafting", {220,140,40,255});

            // Item type
            DrawText("Item:", 100, 100, 20, LIGHTGRAY);
            for(int i=0;i<9;i++){
                Color c = (whatCraft==i+1) ? GOLD : (CheckCollisionPointRec(mouse,craftItemBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(craftItemBtns[i], c);
                int tw = MeasureText(craftNames[i], 20);
                DrawText(craftNames[i], (int)(craftItemBtns[i].x+craftItemBtns[i].width/2-tw/2), (int)(craftItemBtns[i].y+16), 20, WHITE);
            }

            // Tier
            DrawText("Tier:", 100, 250, 20, LIGHTGRAY);
            for(int i=0;i<8;i++){
                Color c = (craftingTier==i+1) ? GOLD : (CheckCollisionPointRec(mouse,tierBtns[i]) ? GRAY : DARKGRAY);
                DrawRectangleRec(tierBtns[i], c);
                DrawText(tierName[i], (int)tierBtns[i].x+5, (int)tierBtns[i].y+15, 15, WHITE);
            }

            // Materials + info
            if(whatCraft > 0 && craftingTier > 0){
                string tName = tierName[craftingTier-1];
                DrawText("Materials:", 100, 330, 20, LIGHTGRAY);
                switch(whatCraft){
                    case 1: case 2:
                        DrawText(TextFormat("%s Plank x6 (have: %d)", tName.c_str(), getFromInventory(tName+" Plank")), 100, 356, 18, WHITE);
                        DrawText(TextFormat("%s Bar x2   (have: %d)", tName.c_str(), getFromInventory(tName+" Bar")),   100, 378, 18, WHITE);
                        break;
                    case 3:
                        DrawText(TextFormat("%s Plank x4 (have: %d)", tName.c_str(), getFromInventory(tName+" Plank")), 100, 356, 18, WHITE);
                        DrawText(TextFormat("%s Bar x2   (have: %d)", tName.c_str(), getFromInventory(tName+" Bar")),   100, 378, 18, WHITE);
                        break;
                    case 4:
                        DrawText(TextFormat("%s Bar x4   (have: %d)", tName.c_str(), getFromInventory(tName+" Bar")), 100, 356, 18, WHITE);
                        break;
                    case 5:
                        DrawText(TextFormat("%s Bar x20       (have: %d)", tName.c_str(), getFromInventory(tName+" Bar")),               100, 356, 18, WHITE);
                        DrawText(TextFormat("%s Ref.Leath x12 (have: %d)", tName.c_str(), getFromInventory(tName+" Refined Leather")),   100, 378, 18, WHITE);
                        break;
                    default:
                        DrawText(TextFormat("%s Bar x8   (have: %d)", tName.c_str(), getFromInventory(tName+" Bar")), 100, 356, 18, WHITE);
                        break;
                }
                string itemName;
                switch(whatCraft){
                    case 1:itemName=tName+" Axe";break;        case 2:itemName=tName+" Pick";break;
                    case 3:itemName=tName+" Knife";break;      case 4:itemName=tName+" Shears";break;
                    case 5:itemName=tName+" Sword";break;      case 6:itemName=tName+" Helmet";break;
                    case 7:itemName=tName+" Chestplate";break; case 8:itemName=tName+" Leggings";break;
                    case 9:itemName=tName+" Boots";break;
                }
                DrawText(TextFormat("In inventory: %d", getFromInventory(itemName)), 100, 402, 20, YELLOW);
            }

            // Progress bar
            DrawText("Progress:", 100, 430, 20, LIGHTGRAY);
            DrawRectangle(100, 454, 1080, 30, DARKGRAY);
            DrawRectangle(100, 454, (int)(1080*craftProgress), 30, ORANGE);
            DrawRectangleLines(100, 454, 1080, 30, WHITE);
            DrawText(TextFormat("Crafted this session: %d", totalCrafted), 100, 490, 20, WHITE);

            // Start/Stop
            Color cBtn = crafting2 ? RED : GREEN;
            DrawRectangleRec(btnStart, cBtn);
            const char* lbl = crafting2 ? "STOP" : "START";
            DrawText(lbl, (int)(btnStart.x+btnStart.width/2-MeasureText(lbl,22)/2), (int)(btnStart.y+14), 22, WHITE);
        }

        // ---- Inventory ----
        else if(screen == 4){
            DrawText("INVENTORY", 480, 15, 38, WHITE);
            DrawRectangleRec(btnBack, DARKGRAY); DrawText("BACK", 35, 30, 20, WHITE);

            if(inventory1.items.empty()){
                DrawText("Inventory is empty.", 100, 150, 25, LIGHTGRAY);
            } else {
                int col=0, row=0;
                for(auto& it : inventory1.items){
                    int x = 100 + col*400, y = 130 + row*30;
                    DrawText(TextFormat("%-28s x%d", it.name.c_str(), it.number), x, y, 18, WHITE);
                    if(++col >= 3){ col=0; row++; }
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}