#Getting Started

##Insertion Sort (algorithm example)
Pseudocode:
```
INSERTION_SORT(A)
   for j = 2 to A.length
        key = A[j]
        // insert A[j] into the sorted sequence A[1...j-1]
        i = j-1
        while (i) > 0 and A[i] > key
        A[i+1] = A[i]
        i = i-1
    A[i+1] = key
```
##Analyzing Algorithms
Predicting the resources that the algorithm requires.
###Worst-case and average-case analysis
* The worst-case running time of an algorithm gives us an upper bound of the running time for any input.
  Knowing it provides a guarantee that the algorithm will never take any longer.
* For some algorithms, the worst case occurs fairly often.
* The "average case" if often roughly as bad as the worst case. 
###Order of growth
We consider only the leading term of the function, since the lower order terms are relatively insignificant for large values of $n$.
##Designing Algorithm
###The divide-and-conquer approach
They break the problem into several subproblems that are similar to the original problems but smaller in size, sovle the small problems recursively, and then combine these solutions to create a solution to the original problem.
* Divide the problem into several subproblems.
* Conquer the subproblems by solving them resursively or in a straightforward manner if the size of the subproblem is small enough.
* Combine the solutions to the subproblems into the solution for the original problem.
```
MERGE(A, p, q, r)
n_1 = q-p+1
n_2 = r - q
let L[1...n_1+1] R[1...n_2+1] be new arrays
for i = 1 to n_1
    L[i] = A[p+i-1]
for j = 1 to n_2
    R[j] = A[q+j]
    L[n_1+1] = Inf
    R[n_2+1] = Inf
i = 1
j = 1
for k = p to r
    if L[i] <= R[j]
        A[k] = L[i]
        i = i+1
    else 
        A[k] = R[j]
        j = j+1

MERGE-SORT(A, p, r)
if p < r
    q = (p+r)/2
    MERGE-SORT(A,p,q)
    MERGE-SORT(A,q+1,r)
    MERGE(A, p, q, r)
```
When an algorithm contains a recursive to itself, we can often define its running time by a ***recurrence equation*** or ***recurrence***, which describes the overall running time on a problem of size n in terms of the running time on smaller inputs.
