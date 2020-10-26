# Functions

### Small
The first rule of functions is that they should be small.
The second rule of functions is that *they should be smaller than that*.

### Do One Thing
**Functions should do one thing. They should do it well. They should do it only.**
If a function does only those steps that are one level below the stated name of the function, then the function is doing one thing.
*Open-closed Principle*: Software entities should be open for extension but closed for modification.
*Single Responsibility principle*: Software engities should have responsibility over a single part of that programs' functionality, which it should encapsulate.

### One Level of Abstraction per Function
### Reading Code from Top to Bottom: *The Stepdown Rule*
We want every function to be followed by those at the next level of abstraction so that we can read the program, descending one level of abstraction at a time as we read down the list of functions.
### Switch Statements
They can be tolerated if they appear only once, are used to create polymorphic objects, and are hidden behind an inheritance relationship so that the rest of the system can't see them.
### Use Descriptive Names  
Don't be afraid to use long function names. A long descriptive name is better than a short enigmatic name.

### Function Arguments
Arguments are hard. They take a lot of conceptual power.
Arguments are even harder from a testing point of view. Imagine the difficulty of writing all the test cases to ensure that all the various combinations of arguments work properly.
We don't usually expect information to be going out throught the arguments.

### Flag Arguments
Flag aruments are ulgy. Passing a boolean into a function is a terrible practice. It immediately complicates the signature of the method, loudly proclaiming that this function does more than one thing. It does one thing if the flag is true and another if false.

### Argument Objects
When a function seems to need more than three arguments, it is likely that some of those arguments ought to be wrapped into a class of their own. When groups of variables are passed together, they are likely part of a concept and deserves a name of its own.

### Command Query Separation
Functions should either do something or answer something, but not both. Either your function should change the state of an object, or it should return some information about that object.

### Prefer Exceptions to Return Error Codes
Returning error codes from command functions is a subtle violation of command query separation.
When you return an error code, you create the problem that the caller must deal with the error immediately. On the other hand, if you use exceptions instead of returned error codes, then the error processing code can be separated from the happy path code and can be simplified.

### Extract Try/Catch Blocks
`try/catch` blocks are ugly in their own right. They confuse the structure of the code and mix error processing with normal processing. So it is better to extract the bodies of the `try` and `catch` blocks out into functions of their own.
