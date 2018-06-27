// test the calculation of floating numbers.
#include <iostream>

int main(){
    float a = 0.5236;
    float b = 6.0214;


    for (int i = 0; i<10; ++i){
        int A = (int)(a * 10000);
        int B = (int)(b * 10000);
        std::cout<<A<<" "<< B<< std::endl;
    }
    
    return 0;

}
