#include <ctime>
#include <iostream>
//using namespace std;


int main(){
    clock_t begin = clock();

    clock_t end = clock();

    auto diff = end - begin;

    double elapsed_secs = double(diff) / CLOCKS_PER_SEC;

    std::cout<<elapsed_secs<<std::endl;
    return 0;
}
