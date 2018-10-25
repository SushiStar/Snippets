/**
 * test on std::stoi function with 2 numbers in 1 string
 */

#include <iostream>
#include <string>

int main() {
    std::string a("1243  558");

    int m = std::stoi(a);

    std::cout << "a is: " << a << "     m is: " << m << std::endl;

    return 0;
}
