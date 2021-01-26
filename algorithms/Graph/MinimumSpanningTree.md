# Minimum Spanning Tree
Motivating Problem: Given a connected, undirected, and weighted graph $G$, select a subset of edges $E' \in G$ such that the graph $G$ is (still) connected and the total weight of the selected edges $E'$ is minimal.
* To satisfy the connectivity criteria, we need at least $V - 1$ edges that form a *tree* and this tree must spans (covers) all $V \in G$ -- the *spanning tree*.

This MST problem can be solved with several well-known algorithms, i.e. Prim’s and Kruskal’s. Both are Greedy algorithm.

### Kruskal's Algorithm
This algorithm first sorts E edges based on non decreasing weight. This can be easily done by sorting the edges in an EdgeList data structure. Then, kruskal's algorithm *greedily* tries to add each edge to MST as long as such addition does not form a cycle. This cycle check can be done easily using the lightweight Union-Find Disjoint Sets discussed before.
The overall runtime of this algorithm is O(sorting + trying to add each edge x cost of Union-Find operations) = O(ElogE + E) = O(ElogE).
```cpp
vector<pair<int,ii>> EdgeList;   // (weight, two vertices) of the edge
for (int i =0 ; i < C; ++i) {
  scanf("%d %d %d", &u, &v, &w);    // read the triple: (u, v, w)
  EdgeList.push_back(make_pair(w, ii(u, v)));
}
sort(EdgeList.begin(), EdgeList.end());   // sort by edge weight O(E log E)

int mst_cost = 0;
UnionFind UF(V);            // all V are disjoint sets initially
for (int i = 0; i < E; ++i) {
  // if ( UF.numSets == 1) break;
  pair<int, ii> front = EdgeList[i];
  if (!UF.isSameSet(front.second.first, front.second.second)) { // check
    mst_cost += front.first;       // add the weight of e to MST
    UF.unionSet(front.second.first, front.second.second);
  }
}
// note: the number of disjoint sets must eventually be 1 for a valid MST
```

### Prim's Algorithm
Robert Clay Prim's algorithm takes a starting vertex (for simplicity, we take vertex 0), flags it as 'taken', and enqueues a pair of information into a priority queue: The weight w and the other end point $u$ of the edge $0 -> u$ that is not taken yet. These pairs are sorted in priority queue based on  increasing weight and if tie, by increasing vertex number. Then Prim's algorithm greedily selects the pair $(w, u)$ in front of the priority queue -- which has the minimum weight w - if the end point of this edge -- which is u -- has not been taken before. This is to prevent cycle. If this pair $(w, u)$ is valid then the weight w is added to the MST cost, u is marked as taken and pair $(w',v)$ of each edge $u->v$ with weight $w'$ that is incident to $u$ is enqueued into the priority queue if v has not been taken before. This process is repeated until the priority queue is empty.
The complexity is run in $O(ElogV)$

```cpp
vi taken;     // global boolean flag to avoid cycle
priority_queue<ii> pq;  // priority queue to heop choose shorter edges
                        // note: default setting for C++ STL priority_queue is a max heap
void process(int vtx) {   // so, we  use -ve sign to reverse the sort order
  taken[vtx] = 1;.
    for (int j = 0; j < (int)AdjList[vtx].size(); ++j) {
      ii v = AdjList[vtx][j];
      if (!taken[v.first]) pq.push(ii(-v.second, -v.first));
                          // sort by (inc) weight then be (inc) id
    }
}
// inside int main() -- assume the graph is sorted in AdjList, pq is empty
taken.assign(V, 0);       // no vertex is taken at the beginning
process(0);               // take vertex 0 and process all edges incident to vertex 0
mst_cost = 0;
while (!pq.empty()) {
  ii front = pq.top();  pq.pop();
  u = -front.second, w = -front.first;    // neage the id and weight again
  if (!taken[u])            // we have not connected this vertex yet
    mst_cost += w, process(u);  // take u, process all edges incident to u
}
printf("MST cost = %d\n", mst_cost);
```
