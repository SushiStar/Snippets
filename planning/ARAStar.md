# ARA\*
Planing is a repeated process:

- partially-known environments
- dynamic environments
- imperfect execution of plans
- imprecise localization

Several methodologies to achieve this:
- anythime heuristic search: return the best plan possible within T msecs
- incremental heuristic search: speed up search by reusing previous efforts
- real-time heuristic search: plan few steps towards the goal and re-plan

### ARA\*
Constructing anytime search based on weighted A\*:
**Making A\* reuse old values**:
initialize OPEN with all overconsistent states;
while ($f(s_{goal}) >  minimum f-value in OPEN$)
     remove s with the smallest $g(s) + h(s)$ from OPEN;
     insert s into CLOSED
     $v(s) = g(s)$;
     for every successor s' of s such that s' not in CLOSED
        if $g(s') > g(s) + c(s, s')$
           $g(s') = g(s) + c(s, s')$
           insert $s'$ into OPEN;

### Incremental heuristic search

- Identifying the boundaries of the previously generated search tree that remains to be valid and re-starting the search from it
- Fixing the previously generated search tree by re-using as much of it as possible
- Restarting search form scratch but "learning" heuristics values

**D\*** Lite
```
until goal is reached
    computepathwithreuse(); // modified to fix underconsistent states
    publish optimal path;
    follow the path until map is updated with new sensor information
    update the corresponding edge costs;
    set $s_{start}$ to the current state of the agent.
```
>This search is done backwards, this way, root of the search tree remains the same and g-values are more likely to remain the same in between two calls to `ComputePathWithReuse()`.

### Anytime Incremental Heuristic Search
```latex
set $$\varepsilon$$ to large value;
until goal is reached
computePathwithReuse()
   publish $$\varepsilon$$ suboptimal path;
   follow the path until map is updated with new sensor information
   update the corresponding edge costs
   set $s_{start}$ to the current state of the agent;
   if significant changes were observed
     increase $\varepsilon$ or replan form scratch;
     else
     decrease $\varepsilon$
```
