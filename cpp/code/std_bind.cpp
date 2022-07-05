/**
 * std::bind is not a very lightweight thing and should be used very judiciously
 * std::bind is designed to swallow all of the extra arguments passed to it.
 */

#include <functional>
#include <iostream>
#include <string>

template<typename T>
void print(T i, const std::string &s) {
    std::cout << i << ' ' << s << '\n';
}

int main() {
    int i{5};

    // it copies the arguments it passed int
    const auto f = std::bind(&print<int>, std::placeholders::_1, std::placeholders::_2);
    f(i, "hello");
    i = 6;
    f(i, "world");

    std::function<void (int , const std::string&)> f2(f);
    f2(i, "test");

}
