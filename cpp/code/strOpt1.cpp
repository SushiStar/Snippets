#include <string>
#include <iostream>

int main(){
    std::string name = "Niels Stroustrup";

    // the first number is the position of first target character
    // the second number is the length of the traget string
    // same as below
    std::string s = name.substr(6,10);
    std::cout << s << std::endl;

    name.replace(0,5,"nicholas");
    std::cout << name << std::endl;

    name[0] = std::toupper(name[0]);
    std::cout << name << std::endl;

    return 0;
}
