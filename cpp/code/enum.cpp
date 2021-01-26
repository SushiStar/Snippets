// enum value cannot be double

#include <iostream>

using namespace std;

int main() {
    enum day { monday = 1, tuesday = 2, wednesday = 3, thursday = 4 };

    day a = monday;

    cout << a << endl;

    return 0;
}
