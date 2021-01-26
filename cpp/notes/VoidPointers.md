#Void pointers
The **void poinetr**, also known as the generic pointer, is a special type of pointer that can be pointed at objects of any data type.
However, because the void pointer does not know what type of object it is pointing to, it cannot be deferenced directly. Rather, the void pointer must first be explicitly cast to another pointer type before it is dereferenced.
```cpp
int value{ 5 };
void *voidPtr{ &value };
 
// std::cout << *voidPtr << '\n'; // illegal: cannot dereference a void pointer
 
int *intPtr{ static_cast<int*>(voidPtr) }; // however, if we cast our void pointer to an int pointer...
 
std::cout << *intPtr << '\n'; // then we can dereference it like normal
```
###Void pointer miscellany
Although some compilers allow deleting a void pointer that points to dynamically allocated memory, doing so should be avoided, as it can result in undefined behavior.
It is not possible to do pointer arithmetic on a void pointer. This is because pointer arithmetic requires the pointer to know what size object it is pointing to, so it can increment or decrement the pointer appropriately.
