#A\* Search
- Is guaranteed to return an optimal path (in fact, for every expanded state) - optimal interms of the solution
- Performs provably mininmal number of state expansions required to guarantee optimality - optimal in terms of teh computations

###Effect of the Heuristic Function
- A\* Search: expands states in the order of $f=g+h$ values.
- Dijkstra's: expands states in the order of $f=g$ values (pretty much)
Intuitively: f(s) - estimate of the cost of a least cost path from start to goal via s.
- Weighted A\*: expands states in the order of $f=g+\varepsilon h$ values, $\varepsilon > 1$ bias: towards states that are closer to goal.

###Backward A\* Search
- Search from goal towards states 
- g values are cost-to-goals
