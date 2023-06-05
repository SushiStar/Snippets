# The stack and the heap
The memory that a program uses is typically divided into a few different areas, called segments:

- The **code segment** (also called a text segment), where the compiled program sits in memory. The code setment is typically read-only
- The **bss segment** (also called the uninitialized data segment), where zero-initialized global and static variables are stored.
- The **data segment** (also called the initialized data segment), where initialized global and static variables are stored.
- The **heap**, where dynamically allocated variables are allocated from.
- The **call stack**, where function parameters, local variables, and other function-related information are stored.

### The heap segment
The heap segment keeps track of memory used for dynamic memory allocation.
It is worth knowing that sequential memory requests may not result in sequential memory addresses being allocated.
The heap has advantages and disadvantages:

- Allocating memory on the heap is comparatively slow.
- Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the application ends.
- Dynamically allocated memory must be accessed through a pointer. Deferencing a pointer is slower than asccessing a variable directly.
- Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.

### The call stack
The call stack has a much more interesting role to play. The call stack keeps track of all the active functions (those that have been called but have not yet terminated) from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.
The call stack is implemented as a stack data structure.
###The stack data structure
A data structure is a programming mechanism for organizing data so that it can be used efficiently.
###The call stack segment
The call stack segment holds the memory used for the call stack. When the application starts, the main() function is pushed on the calls stack by the operating system. Then the program begins executing.
When a function call is encountered, the function is pushed onto the call stack. When the current function ends, that function is poped off the call stack.
###Stack overflow
Stack overflow happens when all the memory in the stack has been allocated -- in that caes, further allocations begin overflowing into other sections of memory.
Stack overflow is generally the result of allocating too many variables on the stack, and /or making too many nested function calls.
The stack has pros and cons:

- Allocating memory on the stack is comparatively fast
- Memory allocated on the stack stays in scope as long as it is on the stack. It is destoryed when it is popped off the stack.
- All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
- Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space.
