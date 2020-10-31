The const after the argument list in the function declarations indicates that these functions do
not modify the state of a class:
    `void getVal() const{/* */}`
const_cast is used to cast away the constness of variables:
1. const_cast can be used to can be used to change non-const class members inside a const member function.
2. const_cast can be used to pass const data to a function that does not receive const.
3. it is undefined behavior to modify a value which is initially defined as const.
4. const_cast is considered safer than simple type casting.
5. const_cast can also be used to cast away volatile attribute.
