#Structs
###C++11/14: Non-static member initialization
Starting with C++11, it's possible to given non-static (normal) struct members a default value:
```cpp
struct Rectangle{
    double length{1.0};
    double width{1.0};
};
int main() {
    Rectangle x; // length = 1.0, width =1.0
    return 0;
}
```
Unfortunately, in C++11, the non-static member initialization synatx is incompatible with the initializer list and uniform initialization syntax:
```cpp
struct Rectangle {
    double length{1.0};
    double width{1.0};
};

int main() {
    Rectangle x{2.0,2.0};       // uniform initialization
    return 0;
}
```
Consequently, in C++11, you'll have to decide whether you want to use non-static member initialization or uniform initizlization.
However, in C++14, this restriction was lifted and both can be used.

###Struct size and data structure alignment
We can only say that the size of a struct will be at least as large as the size of all the variables it contains.
But it could be larger. For performance reasons, the compiler will sometimes add gaps into structures (this is called **padding**).

####Accessing structs across multiple files
Because struct declarations do not take any memeory, if you want to share a struct declaration across mulitple files (so you can instantiate variables of that struct in multiple files), put the struct declaration in a header fiel, and #include that header file anywhere you need it.
