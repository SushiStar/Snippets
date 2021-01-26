# Knapsack Problem
Given n items, each with its own value $V_i$, and weight $W_i$, $i \in [1, n-1]$, and a maximum knapsack size $S$, compute the maximum value of items we can carry, if we can either ignore or take a particular item (hence the term 1-0 for take or ignore).

>To solve this problem, we have to use the DP concept as this problem satisfies the two prerequesites for DP to be applicable:
>	1. This problem has optimal substructures. The solution for the sub-problem is part of the solution for the original problem.
>	2. This problem has overlapping sub-problems.

We can implement the **top-down** DP by adding these two additional steps:
1. Initialize a DP 'memo' table with initial dummy values that are not used in the problem.
2. At the start of the recursive function, check if this state has been computed before.
	* If it has, simply return the value from the DP memo table, O(1).
	* If it has not been computed, perform the computation as per normal (only once) and then store the computed value to the DP memo table.

**Bottom-up** DP:
1. Determine the required set of parameters that uniquely describe the problem (the state). This step is similar to what we have discussed in recursive backtracking and top-down DP earlier.
2. If there are N parameters required to represent the states, prepare an N dimensional DP table, with one entry per state. This is equivalent to the memo table in top-down DP. However, there are differences. In bottom-up DP, we only need to initialize some cells of the DP table with known initial values (the base cases). Recall that in top- down DP, we initialize the memo table completely with dummy values (usually -1) to indicate that we have not yet computed the values.
3. Now, with the base-case cells/states in the DP table already filled, determine the cells/states that can be filled next (the transitions). Repeat this process until the DP table is complete. For the bottom-up DP, this part is usually accomplished through iterations, using loops (more details about this later).

```cpp
// 0-1 Knapsack DP (Top-Down) - faster as not all states are visited

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 1010
#define MAX_W 40

int i, T, G, ans, N, MW, V[MAX_N], W[MAX_N], memo[MAX_N][MAX_W];

int value(int id, int w) {
  if (id == N || w == 0) return 0;
  if (memo[id][w] != -1) return memo[id][w];
  if (W[id] > w)         return memo[id][w] = value(id + 1, w);
  return memo[id][w] = max(value(id + 1, w), V[id] + value(id + 1, w - W[id]));
}

int main() {
  scanf("%d", &T);
  while (T--) {
    memset(memo, -1, sizeof memo);

    scanf("%d", &N);
    for (i = 0; i < N; i++)
      scanf("%d %d", &V[i], &W[i]);

    ans = 0;
    scanf("%d", &G);
    while (G--) {
      scanf("%d", &MW);
      ans += value(0, MW);
    }

    printf("%d\n", ans);
  }

  return 0;
}

// 0-1 Knapsack DP (Bottom-Up)
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &N);
    for (i = 1; i<= N; i++)
      scanf("%d %d", &V[i], &W[i]);
    ans = 0;
    scanf("%d", &G);
    while (G--) {
      scanf("%d", &MW);
      for (i = 0; i <= N;  i++) C[i][0] = 0;
      for (w = 0; w <= MW; w++) C[0][w] = 0;
      for (i = 1; i <= N; i++)
        for (w = 1; w <= MW; w++) {
          if (W[i] > w) C[i][w] = C[i - 1][w];
          else          C[i][w] = max(C[i - 1][w], V[i] + C[i - 1][w - W[i]]);
        }
      ans += C[N][MW];
    }
    printf("%d\n", ans);
  }
  return 0;
}
```
