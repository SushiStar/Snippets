#include<iostream>
#include<functional>


int main(){
    
    std::hash<int> hasher;

    int m;

    for(int i = 0; i < 20; ++i){
    
//        m = hasher(i);
        std::cout<<std::hash<int>()(i)<<std::endl;
    }
    return 0;

}
