#include <vector>
#include <iostream>
#include <algorithm>


/*
 * int main() {
 *     std::vector<int> v{8, 1, 2, 3, 4, 5, 6, 7};
 *     std::cout << std::is_sorted(std::next(v.begin()), v.end()) << std::endl;
 *     return 0;
 * }
 */

int main () {
    int last = 0;
    int new_val = 10;
    for (int i = 0;i < 1000; ++i) {
        last = std::exchange(i, new_val);
    }
    return 0;
}
