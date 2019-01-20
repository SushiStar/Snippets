#include <cstdlib>
#include <iostream>

void digits() {
    for (int i = 0; i != 10; ++i)
        //std::cout << static_cast<char>('0' + i) << std::endl;
        std::cout << '0' + i << std::endl;
}
int main() {
    digits();
    return 0;
}
