#include "RandomAgent.h"
using namespace std;

RandomAgent::RandomAgent(){};
RandomAgent::~RandomAgent(){};

void RandomAgent::policy(state s){
        bool selectableNotEmpty=true;
        while (selectableNotEmpty){
            for(int j=0;j<s.selectable.size();j++){
                if(s.selectable[j]==true){
                    selectableNotEmpty=true;
                    break;
                }
                else{
                selectableNotEmpty=false;
                }
            }
        rand % s.selectable.size();
            if(s.selectable[i]==true){		
                s.select(i);
            }
        }
};

    
