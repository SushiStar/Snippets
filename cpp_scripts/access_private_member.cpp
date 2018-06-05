/*
 * An example for accessing the private member of a class
 */

#include <iostream>

using namespace std;

struct Foo {
public:
    Foo(int v) : x(v){}
    int get() const {
        return x;
    }

private:
    int x;
};


int main(int argc, char* argv[]){
    Foo foo(100);
    std::cerr << "foo.get() " << foo.get() << "  " << endl;
    *reinterpret_cast<int*>(&foo) = 101;
    std::cerr << "foo.get() " << foo.get() << "  " << endl;

    return 0;
}
