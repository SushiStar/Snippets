# SegmentTree
A Segment Tree is a data structure that allows answering range queries over an array
effectively, while still being flexible enough to allow modifying the array.

A Segment Tree can also be generalized to larger dimensions. One important property of
Segment Tree is that they require linear memory storage. The stardard Segment Tree
requires $4n$ vertices for working on an array of size $n$.

## Construction
Before constructing the segment tree, we need to decide:
1. the *value* that gets stored at each node of the segment tree. For example, in a sum
   Segment Tree, a node would store the sum of the elements in its range $[l, r]$.
2. the *merge* operation that merges two siblings in a segment tree. For example, in a sum
   Segment Tree, the two nodes corresponding to the ranges $a[l1 ... r1]$ and $a[l2 ... r2]$
   would be merged into a node corresponding to the range $a[l1 ... r2]$ by adding the
   values of the two nodes.

Now, for construction of the segment tree, we start at the bottom level (the leave
vertices) and assign them their respective values. On the basis 0f these values, we can
compute the values of the previous level, using the $merge$ function. And on the basis of
those, we can compute the values of the previous, and repeate the procedure until we reach
the root vertex.

It is convenient to describe this operation recursively in the order direction, i.e., from
the root vertex to the leaf vertices. The construction procedure, if called on a non-leaf
vertex, does the following:
1. recursively construct the values of the two child vertices.
2. merge the computed values of these children.

We start at the root vertex, and hence, we are able to compute the entire segment tree.
The time complexity of this construction is $O(n)$, assuming that the merge operation is
constant time (the merge operation  gets called $n$ times, which is equal to the number of
internal nodes in the segment tree).