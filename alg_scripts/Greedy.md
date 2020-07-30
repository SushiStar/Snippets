# Greedy
An algorithm is said to be greedy if it makes the locally optimal choice at each step with the hope of eventually reaching the globally optimal solution. In some cases, greedy works -- the solution is short and runs effectively. For *many* others, however, it does not. As discussed in other typical situations, a problem must exhibit these two properties in order for a greedy algorithm to work:
* It has optimal sub-structures.
  Optimal solution to the problem contains optimal solutions to the sub-problems.
* It has the greedy property (difficult to prove in time-critical contest environment!).
  If we make a choice that seems like the best at the moment and proceed to solve the remaning subproblem, we reach the optimal solution. We will never have to reconsider our previous choices.
