#Dynamic memory allocation with new and delete
* Static memory allocation happens for static and global variables. Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.
* Automatic memory allocation happens for function parameters and local variables. Memory for these types of variables is allocated when teh relevant block is entered, and freed when the block is exited, as many times as necessary.
Most normal variables (including fixed arrays) are allocated in a portion of memory called **stack**. The amount of stack memory for a program is generally quite small. If you exceed this number, stack overflow will result.
**Dynamic memory allocation** is a way for running programs to request memory from the operating system when needed. This memory is allocated from a much larger pool of memory managed by the operating system called the heap.

###Dangling pointers
In most cases, the memory returned to the operating system will contain the same values it had before it was returned, and the pointer will be left pointing to the now deallocated memory.
A pointer that is pointing to deallocated memory is called a dangling pointer. Deferencing or deleting a dangling pointer will lead to undefined behavior.
Firstly, try to avoid having multiple pointers point at the same piece of dynamic memory. If this is not possible, be clear which pointer "owns" the memory and which are just accessing it.
Secondly, when you delete a pointer, if that pointer is not going out of scope immediately afterward, set the pointer to 0.

###Operator new can fail
If new fails, a *bad_alloc* exception is thrown. New can return a null pointer if memory can't be allocated.
```cpp
int *value = new (std::nothrow) int; // value will be set to a null pointer if the integer allocation fails
```
###Memory leaks
Memory leaks happen when your program loses the address of some bit of dynamically allocated memory before giving it back to teh operating system.
Memory leaks eat up free memory while the program is running, making less memory available not only to this program, but to other programs as well.
A memory can occur if a pointer holding the address of the dynamically allocated memory is assigned another value.
