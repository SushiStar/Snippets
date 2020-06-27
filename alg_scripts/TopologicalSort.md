#Topological sort (Directed Acyclic Graph)
Topological sort (or topological ordering) of a Directed Acyclic Graph (DAG) is a linear ordering of the vertices in the DAG so that vertex $u$ comes before vertex $v$ if edge ($u -> v$) exists in the DAG. Every DAG has at least one and possibly more topological sort(s).
One application of topological sorting is to find a possible sequence of modules that a university student has to take to fullfill graduation requirement. Each module has certain pre-requisites to be met.

```cpp
// modified DFS method
vi ts;		// global vector to store the toposort in reverse order

void dfs2(int u) {
	dfs_num[u] = VISITED;
	for (int j = 0; j < (int)AdjList[u].size(); ++j) {
		ii v = AdjList[u][j];
		if (dfs_num[v.first] == UNVISITED)
			dfs2(v.first);
	}
	ts.push_back(u);
}
```

This approach is based on the following fact: **A DAG has at least one vertex with in-degree 0 and one vertex with out-degree 0**.
1. Compute in-degree (number of incoming edges) for each of the vertex present in the DAG and initialize the count of visited nodes as 0.
2. Pick all the vertices with in-degree as 0 and add them into a queue (Enqueeu operation).
3. Remove a vertex from the queue (Dequeue operation) and then:
	* Increment count of visited nodes by 1.
	* Decrease in-degree by 1 for all its neighboring nodes.
	* If in-degree of a neighboring nodes is reduced to 0, then add it to the queue.
4. Repeat Step 3. untill the queue is empty.
5. If count of visited nodes is not equal to the number of nodes in the graph then the topological sort is not possible for the given graph.

```cpp
void Graph::topologicalSort() {
    /// Create a vector to store indegrees of all vertices.
    vector<int> in_degree(V, 0);

    // Traverse adjacency lists to fill indegrees of vertices.
	// This step takes O(V+E) time.
    for (int u = 0; u < V; u++)
        for (int j = 0; j < adj[u].size(); ++j)
            in_degree[adj[u][j]]++;

    // Create an queue and enqueue all vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    // Create a vector to store result (A topological ordering of the vertices)
    vector<int> top_order;

    // One by one dequeue vertices from queue and enqueue
    // adjacents if indegree of adjacent becomes 0
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        top_order.push_back(u);
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            // If in-degree becomes zero, add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);
        cnt++;
    }
    if ((int)top_order.size() != V)
        cout << "There exists a cycle in the graph\n";
	return;
}
```
