#pragma once
#include <iostream>
using namespace std;

class level{
    public:
        int level = 0;
        int exprence = 0;
        int expForNextLevel = 100;

        void levelUp(int exprenceFromWork){
            exprence += exprenceFromWork;
            if(exprence >= expForNextLevel){
                exprence -= expForNextLevel;
                expForNextLevel = (int)(expForNextLevel * 1.25);
                level += 1;
            }
        }
};