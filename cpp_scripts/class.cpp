/*
 * To test whether the elements in constructor could
 * be constructed with curly braces
 *
 * The answer is: no
 * There's a typo in the book: The C++ programming language, 4th edition; page 49
 */

#include<iostream>

class aa{
    public:
    int a, b, c;

    aa(int a_, int b_, int c_):a(a_), b(b_), c(c_){}
};

int main(){
    aa d(1,2,3);
    std::cout<< d.a<<d.b<<d.c<<std::endl;
    return 0;
}
