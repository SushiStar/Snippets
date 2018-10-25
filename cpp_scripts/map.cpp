#include <iostream>
#include <cstdlib>
#include <time.h>
#include <unordered_map>


int main(){
    std::unordered_map<int, int> mmp;
    std::srand(time(NULL));
    for(int i = 0; i < 50; ++i){
        mmp.insert(std::make_pair(i, rand()%100));
    }
    for(auto p:mmp){
        std::cout<<p.first<<"  "<<p.second<<std::endl;
    }
    
    std::unordered_map<int, int> mmp2 = mmp;

//    mmp2.erase(20);
    for(auto p:mmp){
        if(p.first == 20){
            std::cout<<"succs"<<std::endl;
        }
    }
    for(auto p:mmp2){
        if(p.first == 20){
            std::cout<<"fail"<<std::endl;
        }
    }

    if(mmp == mmp2){
        std::cout<<"wrong\n";

    }else{
        std::cout<<"true\n";
    }

    return 0;
}
