#include <vector>
#include <iostream>

int main() {
    std::vector<int> a {1,1,1,1,1};
    for (auto i = a.size() -1; i-- > 0; ) {
        std::cout << i << std::endl;
    }

    return 0;
}
