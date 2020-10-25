# Functions

### Small
The first rule of functions is that they should be small.
The second rule of functions is that *they should be smaller than that*.

### Do One Thing
**Functions should do one thing. They should do it well. They should do it only.**
If a function does only those steps that are one level below the stated name of the function, then the function is doing one thing.

### One Level of Abstraction per Function
### Reading Code from Top to Bottom: *The Stepdown Rule*
We want every function to be followed by those at the next level of abstraction so that we can read the program, descending one level of abstraction at a time as we read down the list of functions.
### Switch Statements
They can be tolerated if they appear only once, are used to create polymorphic objects, and are hidden behind an inheritance relationship so that the rest of the system can't see them.
### Use Descriptive Names  
Don't be afraid to use long function names. A long descriptive name is better than a short enigmatic name.
