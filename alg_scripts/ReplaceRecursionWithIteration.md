#Replace Recursion with Iteration

###Motivation
Complex Recursion that is hard to understand should probably be considered a "bad smell" in the code and a good candidate to be replaced with Iteration (usually in combination with some other Refactorings). Moreover, iterative solutions are usually more efficient than recursive solutions as they don't incur the overhead of the multiple method calls. Whenever recursive method is called, local fields are put on the method stack and used again after the recursive call is completed. The general approach to Refactoring could probably be to implement the alternative Stack that "simulates" the method stack where the local field could be placed.

###Mechanics
- Determine the base case of the Recursion. Base, case, when reached, causes Recursion to end. Every Recursion must have a defined base case. In addition, each recursive call must make a progress towards teh base case (otherwise recursive calls would be performed infinitely).
- Implement a loop that will iterate until the base case is reached.
- Make a progress towards teh base case. Send the new arguments to the top of the loop instead to the recursive method.

##Recursion v.s. Iteration
- Iterative functions are typically faster than their recursive counterparts. So if speed is an issue, you would normally use iteration.
- If the stack limit is too constraining then you will prefer iteration over recursion.
- Some precedures are very naturally programmed recursively, and ll but unmanageable iteratively. Here, then, the choice is clear
