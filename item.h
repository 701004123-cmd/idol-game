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
            {"Stone Ore",1,10},{"Copper Ore",2,50},{"Iron Ore",3,100},{"Steel Ore",4,500},
            {"Titanium Ore",5,1000},{"Mithril Ore",6,5000},{"Adamant Ore",7,10000},{"Dragon Ore",8,50000000}
        };
        vector<oreInfo> wood = {
            {"Stone Wood",1,10},{"Copper Wood",2,50},{"Iron Wood",3,100},{"Steel Wood",4,500},
            {"Titanium Wood",5,1000},{"Mithril Wood",6,5000},{"Adamant Wood",7,10000},{"Dragon Wood",8,50000000}
        };
        vector<oreInfo> leather = {
            {"Stone Leather",1,10},{"Copper Leather",2,50},{"Iron Leather",3,100},{"Steel Leather",4,500},
            {"Titanium Leather",5,1000},{"Mithril Leather",6,5000},{"Adamant Leather",7,10000},{"Dragon Leather",8,50000000}
        };
        vector<oreInfo> wool = {
            {"Stone Wool",1,10},{"Copper Wool",2,50},{"Iron Wool",3,100},{"Steel Wool",4,500},
            {"Titanium Wool",5,1000},{"Mithril Wool",6,5000},{"Adamant Wool",7,10000},{"Dragon Wool",8,50000000}
        };
};

class refins{
    public:
        vector<refinInfo> bar = {
            {"Stone Bar",10},{"Copper Bar",50},{"Iron Bar",100},{"Steel Bar",500},
            {"Titanium Bar",1000},{"Mithril Bar",5000},{"Adamant Bar",10000},{"Dragon Bar",50000000}
        };
        vector<refinInfo> plank = {
            {"Stone Plank",10},{"Copper Plank",50},{"Iron Plank",100},{"Steel Plank",500},
            {"Titanium Plank",1000},{"Mithril Plank",5000},{"Adamant Plank",10000},{"Dragon Plank",50000000}
        };
        vector<refinInfo> refinedLeather = {
            {"Stone Refined Leather",10},{"Copper Refined Leather",50},{"Iron Refined Leather",100},{"Steel Refined Leather",500},
            {"Titanium Refined Leather",1000},{"Mithril Refined Leather",5000},{"Adamant Refined Leather",10000},{"Dragon Refined Leather",50000000}
        };
        vector<refinInfo> fabric = {
            {"Stone Fabric",10},{"Copper Fabric",50},{"Iron Fabric",100},{"Steel Fabric",500},
            {"Titanium Fabric",1000},{"Mithril Fabric",5000},{"Adamant Fabric",10000},{"Dragon Fabric",50000000}
        };
        int durability = 1;
};

class crafts{
    public:
        vector<toolInfo> axe = {
            {"Stone Axe",2},{"Copper Axe",4},{"Iron Axe",6},{"Steel Axe",8},
            {"Titanium Axe",10},{"Mithril Axe",12},{"Adamant Axe",14},{"Dragon Axe",16}
        };
        vector<toolInfo> pick = {
            {"Stone Pick",2},{"Copper Pick",4},{"Iron Pick",6},{"Steel Pick",8},
            {"Titanium Pick",10},{"Mithril Pick",12},{"Adamant Pick",14},{"Dragon Pick",16}
        };
        vector<toolInfo> skinningKnife = {
            {"Stone Knife",2},{"Copper Knife",4},{"Iron Knife",6},{"Steel Knife",8},
            {"Titanium Knife",10},{"Mithril Knife",12},{"Adamant Knife",14},{"Dragon Knife",16}
        };
        vector<toolInfo> shears = {
            {"Stone Shears",2},{"Copper Shears",4},{"Iron Shears",6},{"Steel Shears",8},
            {"Titanium Shears",10},{"Mithril Shears",12},{"Adamant Shears",14},{"Dragon Shears",16}
        };
        vector<toolInfo> sword = {
            {"Stone Sword",10},{"Copper Sword",50},{"Iron Sword",100},{"Steel Sword",500},
            {"Titanium Sword",1000},{"Mithril Sword",5000},{"Adamant Sword",10000},{"Dragon Sword",50000}
        };
        vector<armorInfo> helmet = {
            {"Stone Helmet",10},{"Copper Helmet",50},{"Iron Helmet",100},{"Steel Helmet",500},
            {"Titanium Helmet",1000},{"Mithril Helmet",5000},{"Adamant Helmet",10000},{"Dragon Helmet",50000}
        };
        vector<armorInfo> chestplate = {
            {"Stone Chestplate",10},{"Copper Chestplate",50},{"Iron Chestplate",100},{"Steel Chestplate",500},
            {"Titanium Chestplate",1000},{"Mithril Chestplate",5000},{"Adamant Chestplate",10000},{"Dragon Chestplate",50000}
        };
        vector<armorInfo> leggings = {
            {"Stone Leggings",10},{"Copper Leggings",50},{"Iron Leggings",100},{"Steel Leggings",500},
            {"Titanium Leggings",1000},{"Mithril Leggings",5000},{"Adamant Leggings",10000},{"Dragon Leggings",50000}
        };
        vector<armorInfo> boots = {
            {"Stone Boots",10},{"Copper Boots",50},{"Iron Boots",100},{"Steel Boots",500},
            {"Titanium Boots",1000},{"Mithril Boots",5000},{"Adamant Boots",10000},{"Dragon Boots",50000}
        };
};