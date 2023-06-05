## Monotonic Stack / Queue

### Monotone stack
**Monotonic Stack contains the elements which are either increasing only or decreasing only.**

Monotonic stacks has the following properties:
* Meet the elements from the top of the stack to the bottom of the stack has strict monotonicity.
* Meet the last-in-first-out feature of the stack the sooner the element that is near the bottom of the stack.
Because the monotonic stack can only operate on top of the stack, it is generally used only where there is a limit on one side of the array.

Nearest Smaller/Larger Element: **One common use case of a monotonic stack is to find the
nearest smaller or larger element for each element in a given sequence.** This can be done
efficiently by iterating through the sequence and pushing each element onto the stack.
While pushing, elements that violates the monotonic property are propped, and the top
element of the stack at each iteration represents the nearest smaller or larger element
for the current element.

Efficient Time Complexity: The use of a monotonic stack can often provide an efficient
solution to problems that involves finding nearest smaller/larger elements. By using the
monotonic property, it reduces the number of comparisons and allows for a linear-time
solution in many cases.

Using a monotonically increasing stack when:
1. Finding the next greater element: If the problem requires finding the next greater
   element for each element in a given sequence, you would use a monotonically increasing
   stack. This stack helps in maintaining a non-decreasing order of elements, allowing you
   to efficiently track the next greater elements.
2. Calculating maximum/minimum: When you need to calculate the maximum or minimum value in
   a sliding window or subarray, a monotonically increasing stack is suitable. The stack
   helps in keeping track of elements in increasing order, allowing you to find the
   maximum or minimum element efficiently.
3. Removing smaller elements: If you want to remove smaller elements from a sequence and
   keep only the larger elements, a monotonically increasing stack can be used. By
   comparing the current element with the top of the stack, you can remove elements that
   are smaller and retain only the larger ones.

Using a monotonically decreasing stack when:
1. Finding the next smaller element: If the problem requires finding the next smaller
   element for each element in a given sequence, you would use a monotonically decreasing
   stack. This stack helps in maintaining a non-increasing order of elements, allowing you
   to efficiently track the next smaller elements.
2. Calculating maximum/minimum: similar to the increase stack, a monotonically decreasing
   stack can be used to calculate maximum or minimum value in a sliding window or
   subarray. The stack helps in keeping track of the elements in decreasing order,
   allowing you to find the maximum or minimum element efficiently.
3. Removing larger elements: If you want to remove larger elements from a sequence and
   keep only the smaller elements, a monotonically decreasing stack can be used. By
   comparing the current element with the top of the stack, you can remove elements that
   are larger and retain only the smaller ones.

### Montone queue
A monotone queue is a data structure in which an element within a queue has strict monotonicity, which is divided into monotone increment queue and monotonically descending queue.

Monotone queue satisfies two properties:
* The monotonic queue must meet the strict monotonicity from the head to the end of the team.
* In front of the queue than the queue in order to the advanced team.
