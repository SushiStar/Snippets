#include <iostream>
#include <typeinfo>

struct S{
    // will usually occupy 2 bytes:
    // 3 bits: value of b1
    // 2 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    // 3 bits: unused
    unsigned short b1 : 2, b2 : 6, b3 : 5, : 3;
};

int main(){
    S s;
    s.b1 = 3;
    std::cout << typeid(s.b1).name() << " "<< typeid(short).name() << std::endl;
    std::cout << sizeof(S) << '\n';
    std::cout << s.b1 <<std::endl;


    return 0;
}
