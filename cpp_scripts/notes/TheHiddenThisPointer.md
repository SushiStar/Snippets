#The hidden \*this pointer
```cpp
int main() {
    Simple simple(1);
    simple.setID(2);
    std::cout << simple.getID() << '\n';
    return 0;
}
```
Although the call to function setID() looks like it only has one argument, it actually has two. When compiled, the compiler converts `simple.setID(2)`; into the following:
```cpp
setID(&simple, 2);  // note that simple has been changed from an object prefix to a function argument.
```
Since the function call now has an added argument, themember function definition needs to be modified to accept (and use) this argument as a parameter. Consequently, the following member function:
```cpp
void setID(int id) {m_id = id;}
```
Is converted by the compiler into:
```cpp
void setID(Simple* const this, int id) {this->m_id = id;}
```
When the compiler compiles a normal member function, it implicitly adds a new  parameter to the function named "this". The **this pointer** i sa hidden const pointer that holds the address of the object the member function was called on.
Putting it all toghther:
1. When we call `simple.setID(2)`, the compiler actually calls setID(&simple, 2).
2. Inside setID(), the "this" pointer holds the address of object simple.
3. Any member variables inside setID() are prefixed with "this->". So when we say m\_id = id, the compiler is actually executing `this->m_id=id`, which in this case updates simple.m_id to id.

###"this" always points to the object being operated on
###Explicitly referencing "this"
First, if you have a constructor (or member function) that has a parameter with the same name as a member variable, you can disambiguate them by using "this":
```cpp
class Something {
private:
    int data;
public:
    Something(int data) {
        this->data = data;  // this->data is the member, data is the local parameter
    }
}
```
Note that our constructor is taking a parameter of the same name as a member variable. In this case, "data" refers to the parameter, and "this->data" refers to the member variable. Although this is acceptable coding practice, we find using the "m\_" prefix on all member variable names provides a better solution by preventing duplicate names altogether.

>Recommendation:
>Do not add `this->` to all uses of your class members. Only do so when you have a specific reason to.


###Chaining member functions
Second, it can sometimes be fuseful to have a clas member function return the object it was working with as a return value. The primary reason to do is to allow a series of member function to be "chained" together, so several member functions can be called on the same object.
If you make each function return \*this, we can chain the calls together.
```cpp
class Calc {
private:
    int m_value;
public:
    Calc() {m_value = 0}

    Calc& add(int value) {m_value += value; return *this;}
    Calc& sub(int value) {m_value -= value; return *this;}
    Calc& mult(int value) {m_value *= value; return *this;}
    int getValue() {return m_value;}
}

int main() {
    Calc calc;
    calc.add(5).sub(3).mult(4);
    std::cout << calc.getValue() << '\n';
    return 0;
}
```

##Summary
The "this" pointer is a hidden parameter implicitly adde to any non-static member function. Most of the time, you will not need to access it directly, but you can if needed. It's worth noting that "this" is a const pointer -- you can change the underlying object it points to, but you can not make it point to something else.
