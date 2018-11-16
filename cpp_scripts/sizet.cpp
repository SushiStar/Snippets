#include <vector>
#include <iostream>

int main() {
    std::vector<int> a;
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);

    for (auto i = a.size() -1; i >= 0; --i) {
        std::cout << i << std::endl;
    }

    return 0;
}
