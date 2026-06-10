#include <iostream>

using namespace std;

class level{
    public:
        int level;
        int exprence;
        int expForNextLevel;

        int levelUp (int exprenceFromWork){
            exprence =+ exprenceFromWork;
            if(exprence == expForNextLevel){
                expForNextLevel = expForNextLevel * 0.25;
                level =+ 1;
            }else if (exprence >= expForNextLevel){
                exprence =- expForNextLevel;
                expForNextLevel = expForNextLevel * 0.25;
                level =+ 1;
            }
        }
};