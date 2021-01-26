# DFS Spanning Tree
Running DFS on a connected graph generates a DFS *spanning tree* (or *spanning forest* if the graph is disconnected).
With the help of one more vertex state: $EXPLORED = 2$ (visited by not yet completed) on top of $VISITED$ (visited and completed), we can use this DFS spanning tree (or forest) to classify graph edges into three types:
1. Tree edge: The edge traversed by DFS, i.e. an edge from a vertex currently with state: $EXPLORED$ to a vertex with state: $UNVISITED$.
2. **Back edge: Edge that is part of a cycle, i.e. an edge from a vertex currently with state: $EXPLORED$ to a vertex with state: $EXPLORED$ too.**
3. Forward/Cross edges from vertes with state: $EXPLORED$ to vertex with state: $VISITED$.
