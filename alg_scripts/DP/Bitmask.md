## Backtracking with Bitmask
N-Queens problem
We will straightforwardly use three bitmasks for rw, ld, and rd to represent the state of the search.
The on bits in bitmasks rw, ld, and rd describe which rows are attacked in the next column, due to row, left diagonal, or right dagnoal attacks from previously placed queens, respectively.
We firstly show the short code of this recursive backtracking with bitmask for the (general) n-queens problem with $n = 5$ and then explain how it works.
```cpp
int ans = 0, OK=(1<<5)-1;     // testing for n = 5 queens

void backtrack(int rw, int ld, int rd) {
  if (rw == OK) {ans++; return;}
  if pos = OK & (~(rw|ld|rd));    // the '1's in pos are available
  while (pos) {
    int p = pos & -pos;           // Least Significant One -- this is fast
    pos -= p;
    backtrack(rw | p, (ld | p) << 1, (rd | p) >> 1);
  }
}

int main {
  backtrack(0, 0, 0);
  printf("%d\n", ans);
  return 0;
}
```
Complete Search (the recursive backtrackign) will try all possible rows (that is, all the *on bits* in variable pos) of a certain column one by one:
```cpp
for (p = 0; p < n; ++p)
  if (pos && (1 <<p))
    // process p
```
However, this is not the most efficient way. As the recursive backtracking goes deeper, less and less rows are available for selection. Instead of trying all rows, we can speed up the loop above by just trying all the on bits in variable `pos`. The loop below runs in $O(k)$ instead of $O(n)$:
```cpp
while (pos) {
  int p = pos&(-pos);   // determine the Least Significant Bit  in pos
  pos -= p;             // turn off that bit
  // process p;
}
```
## DP with Bitmask
Some of the modern DP problems require a (small) set of Boolean as one of the parameters of the DP state. This is another situation where bitmask technique can be useful. This technique is suitable for DP as the integer can be used as the index of the DP table. We have seen this technique once when we discuss DP TSP.

#### Forming Quiz Teams: minimum weight perfect matching on a small general weighted graph
The matching state is represented by a **bitmask**. We start with a state where nothing is matched yet, i.e. $bitmask=000000$. If item 0 and item 2 are matched, we can turn on two bits (bit 0 and bit 2) at the same time via this simple bit operation, i.e. bitmask $| (1 << 0) | (1 << 2)$, thus the state becomes $bitmask=000101$. Notice that index starts from 0 and counted from the right. If from this state, item 1 and item 5 are matched next, the state will become bitmask=100111. The perfect matching is obtained when the state is all ‘1’s, in this case: bitmask=111111.
