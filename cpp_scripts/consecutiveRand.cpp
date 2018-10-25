#include <cstdlib>
#include <iostream>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));

    int a = rand()%17;
    int b = rand()%17;
    int c = rand()%17;

    printf("a: %d, b: %d, c: %d\n", a, b, c);
    return 0;
}
