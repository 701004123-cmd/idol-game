#include <iostream>
#include <level.h>
#include <vector>

using namespace std;

class character{
    public:
        string name;
        int gold;
};
//gedering level
class gedering: public character{
    level gedering;

};
//refining level
class refining: public character{
    level refining;

};
//crafting level
class crafting: public character{
    level crafting;

};
//fighting level 
class fighting: public character{
    level fighting;
};

//inventory
class inventory: public character{
    vector<string> objectName;
    vector<int> objectQuality;

    void putObjectsInvantory (string name,int number){
        objectName.push_back(name);
        for(int i=0; i<objectName.size(); i++){
            if(name==objectName[i]){
               objectQuality[i].push_back(number); 
            }
        }
    }
};