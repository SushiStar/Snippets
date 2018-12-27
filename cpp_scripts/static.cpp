/*
 * To verify whether static variable is modifiable when program is running.
 *
 * Answer: Modifiable;
 *
 */
#include <iostream>

static int a = 10;

int main() {
    
    std::cout << "a is: " << a << std::endl;

    a = 100;

    std::cout << "After modification: " << a << std::endl;

    return 0;
}
