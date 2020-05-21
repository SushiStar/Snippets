#Heuristic functions
####For grid based navigation:
- Euclidean distance
- Manhattan distance: $h(x,y) = abs(x-x_{goal}) + abs(y - y_{goal})$, efficient in 4-connected grids
- Diagonal distance: $h(x,y) = max(abs(x-x_{goal}), abs(y-y_{goal}))$ efficient in 8-connected grids
- Backward Dijkstra's heuristic: single Dijkstra's on 2D/3D grid cells start at goal cell

###Useful properties to know:
- $h_1(s), h_2(s)$ consistent, then:
    $h(s) = max(h_1(s), h_2(s))$ consistent.
- if A\*j uses $\varepsilon$ consistent heurisitics:
    $h(s_{goal}) = 0 and h(s) \leq \varepsilon c(s, succ(s)) + h(succs(s))$ for all $s \neq s_{goal}$.
    then A\* is $\varepsilon$ suboptimal:
        $$ cost(solution) \leq \varepsilon cost(optimal solution)$$
- Weighted-A\* is A\* wiht $\varepsilon$ consistent heuristics
- $h_1(s), h_2(s)$ consistent, then
    $h(s) = h_1(s) + h_2(s) - \varepsilon$ consistent.

###Utilizing Multiple Heuristic Functions
We can utilize a bunch of inadmissible heuristics simultaneously.
Combining multiple heuristics into one (e.g., taking max) is often inadequate (information is lost; creates local minima; requires all heuristics to be admissible)

####Key idea1: share information (g-values) between searches
Within the while loop of the ComputePath function (note: CLOSED is shared): 
for  i = 1 \.\.\. N:
    removes s with the smallest $f(s) = g(s) + \omega_1 \times h(s)$ from $OPEN_i$;
    expands s and also insert/update its successors into all other OPEN lists;
Benefits:
    - Searches help each other to circumvent local minima.
    - States are expanded at most once across all searches.
    - No completeness guarantees or bounds on solution quality

####Key idea2: Search with admissible heuristics controls expansions
Benefits:
    - Algorithm is complete and provides bounds on solution quality
Within the while loop of the ComputtePath function
if (min. f-value in $OPEN_i \lep \omega_2 \times min. f-value in OPEN_0$):
    remove s with the smallest $f(s) = g(s) + \omega_1 \times h_i(s)$ from $OPEN_i$
    expand s and also insert/update its successors into all other $OPEN$ lists;
else
    remove s with the smallest $f(s) = g(s) + \omega_1 \times h_0(s)$ from $OPEN_0$;
    expands and also insert/update its successors into all other $OPEN$ lists;
