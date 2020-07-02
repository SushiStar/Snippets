#Backtracking with Bitmask
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
