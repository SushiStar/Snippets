#include<iostream>
#include<algorithm>
#include<ctime>
#include<stdlib.h>

int main(){
    std::srand(time(NULL));   
    std::vector<int> test;

    for(int i =0; i < 7; ++i){
        test.push_back(rand()%10);
    }

    int key;

    key = std::hash()
}
