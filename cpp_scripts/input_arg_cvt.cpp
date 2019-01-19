/**
 * A funciton to upgrade c-style input argument to c++ style.
 * That is, convert char array to strings.
 */

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> arguments(int argc, char* argv[]) {
    std::vector<std::string> res;
    for (int i = 0; i != argc; ++i) res.push_back(argv[i]);
    return res;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> res = arguments(argc, argv);
    for (auto str : res) {
        std::cout << str << std::endl;
    }
    return 0;
}
