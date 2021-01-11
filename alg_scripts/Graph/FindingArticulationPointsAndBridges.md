# Finding Articulation Points and Bridges(Undirected Graph)

An **Articulation Point** is defined as a *vertex* in a graph G whose removal (all edges incident to this vertex are also removed) disconnects G. A graph without any articulation point is called **Biconnected**. Similarly, a **Bridge** is defined as an *edge* in a graph G whose removal disconnects G.

We now maintain two numbers: `dfs_num(u)` and `dfs_low(u)`. Here, `dfs_num(u)` now stores the iteration counter when  the vertex `u` is visited *for the first time* (not just for distinguishing UNVISITED and EXPLORED/VISITED). The other number `dfs_low(u)` stores the lowest `dfs_num` reachable from the current DFS spanning subtree of `u`. At the beginning, `dfs_low(u) = dfs_num(u)` when vertex `u` is visited for the first time. Then, `dfs_low(u)` can only be made smaller if there is a cycle (a back edge exists). Note that we do not update `dfs_low(u)` with a back edge (u, v) if v is a direct parent of u.

When we are in a vertex `u` with `v` as its neighbor and `dfs_low(v) >= dfs_num(u)`, then u is an articulation vertex. This is because the fact that `dfs_num(v)` is not smaller than `dfs_num(u)` implies that there is no back edge from vertex `v`  that can reach another vertex `w` with a lower `dfs_num(w)` than `dfs_num(u)`. A vertex `w` with lower `dfs_num(w)` than vertex `u` with `dfs_num(u)` implies that `w` is the ancestor of u in the DFS spanning tree.

The process to find bridges is similar. When `dfs_low(v) > dfs_num(u)`, then edge u-v is a bridge (notice that we remove the equality test '=' for  finding bridges).

```cpp
void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNubmerCounter++;  // dfs_low[u] <= dfs_num[u]
  for (int j = 0; j < (int)AdjList[u].size(); ++j) {
    ii v = AdjList[u][j];
    if (dfs_num[v] == UNVISITED) {
      dfs_parent[v] = u;
      if (u == dfsRoot) rootChildren++;  // special case if u is a root

      articulationPointAndBridge(v);

      if (dfs_low[v] >= dfs_num[u])  // for articulation point
        articulation_vectex[u] = true;     // store this information first

      if (dfs_low[v] > dfs_num[u])  // for bridge
        bridge[v][u] = bridge[u][v] = true;
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);  // update dfs_low

    } else if (v!= dfs_parent[u])  // a back edge and not direct cycle
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);  // update
  }
}

int main() {
  dfsNumberCounter = 0;
  dfs_num.assign(V, UNVISITED);
  dfs_low.assign(V, 0);
  dfs_parent.assign(V, 0);
  articulation_vertex.assign(V, 0);
  for (int i = 0; i < V; ++i) {
    if (dfs_num[i] == UNVISITED) {
      dfsRoot = i;
      rootChildren = 0;
      articulationPointAndBridge(i);
      articulation_vertex[dfsRoot] = (rootChildren > 1);
    }
  }
  for (int i = 0; i < V; ++i) {
    if (articulation_vertex[i]) {
      printf(" Vertex %d\n", i);
    }
  }
}
```
Leetcode questions related: 1192 / 802
