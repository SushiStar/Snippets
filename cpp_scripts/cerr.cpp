#include <iostream>

int main(){
    int a = 1;
    int b = 2;
    
    if (2 == b) {
        std::cerr << "ok." << std::endl;
        throw("Divison by zero condition!\n");
    }

    std::cout << "a = 1" << std::endl;

    return 0;
}
