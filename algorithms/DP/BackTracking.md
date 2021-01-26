# BackTracking
### Simple Backtracking: 8 Queens Chess Problem
>In chess (with an 8x8 board), it is possible to place eight queens on the board such that no two queens attack each other. Determine *all* such possible arrangements given the position of one of the queens (i.e. coordinate $(a, b)$ must contain a queen). Output the possibilities in lexicographical (sorted) order.
> 1. No two queens can share the same column or the same row.
> 2. No two queens can share any of the two diagonal lines: `abs(i-k) != abs(j-l)`.

A recursive backtracking solution places the queens one by one in columns 0 to 7, observing all the constraints above. Finally, if a candidate solution is found, check if at least one of the queens satisfies the input constraints, i.e. row[b] == a.
```cpp
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
int row[8], TC, a, b, lineCounter;			// use global variables
bool place(int r, int c) {
	for (int prev = 0; prev < c; ++prev) 	// check previously placed queens
		if (row[prev] == r || (abs(row(prev]-r) == abs(prev-c))))
		return false;						// share same row or same diagonal -> infeasible
	return true;
}

void backtrack(int c) {
	if (c == 8 && row[b] == a) {			// candidate sol, (a, b) has 1 queen
		// solution documentation
	}
	for (int r = 0; r < 8; ++r) {			// try all possible row
		if (place(r, c)) {					 // if can place a queen at this col and row
			row[c] = r;
			backtrack(c+1);					 // put this queen here and resurse
		}
	}
}

int main() {
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d %d", &a, &b);
		a--;
		b--;								// switch to 0-based indexing
		memset(row, 0, sezeof(row));
		lineCounter = 0;
		//...
	}
}
```

### More chanllenging Backtracking: n-Queen Problem
>Given an nxn chessboard (3 < n < 15) where some of the cells are bad (queens can not be placed on those bad cells), how many ways can you place n queens in the chessboard so that no two queens attach each other?
The major issue with the previous n-queens code is that it is quite slow when checking whether the position of a new queen is valid since we compare the new queen's position with the previous c-q queens' positions. It is better to store the same information with three boolean arrays (we use bitsets for now):
```cpp
bitset<30> rw, ld, rd; 		// for the largest n = 14, we have 27 diagnoals
```
Initially all $n$ rows ($rw$), $2 \times n-1$ left diagonals (`ld`), and $2 \times n-1$ right diagonals (`rd`) are unused (these three bitsets are all set to false). When a queen is placed at cell (r, c), we flag `rw[r] = true` to disallow this row from being used again. Furthermore, all `(a, b)` where `abs(r-a) = abs(c-b)` also cannot be used anymore. There are two possibilities after removing the `abs` function: $r - c = a - b$ and $r + c  = b + a$. Note that $r + c$ and $r - c$ represent indices for two diagnoal axes. As $r - c$ can be negative, we add an offset of $n-1$ to both sides of the equation so that $r-c + n-1 =  a-b + n-1$. If a queen is placed on cell `(r, c)`, we flag `ld[r-c+n-1]=true` and `rd[r+c]=true` to disallow these two diagonals from being used again.
```cpp
void backtrack(int c) {
	if (c==n) {
		ans++;
		return;
	}
	for (int r = 0; r < n; ++r) {
		if (board[r][c] != '*' && !rw[r] && !ld[r-c+n-1] && !rd[r+c]) {
			rw[r] = ld[r-c+n-1] = rd[r+c] = true;		// flag off
			backtrack(c+1);
			rw[r] = ld[r-c+n-1] = rd[r+c]] = flase;		// restore
		}
	}
}
```
### Tips
#### Filtering versus Generating
Programs that examine lots of (if not all) candidate solutions and choose the ones that are correct (or remove the incorrect ones) are called "filters". Usually 'filter' programs are written iteratively.
Programs that gradually build solutions and immediately prune invalid partial solutions are called 'generators'. Usually, 'generator' programs are easier to implement when written recursively as it gives us greater flexibility for pruning the search space.
Generally, filters are easier to code but run slower, given that it usually far more difficult to prune more of the search space iteratively.

#### Prune Infeasible/Inferior Search Space early
When generating solutions using recursive backtracking, we may encounter a partial solution that will never lead to a full solution. We can prune teh search there and explore other parts of the search space.
In other problems, we may be able to compute the 'Potential worth' of a partial (and still valid) solution. If the potential worth is inferior to the worth of the current best found valid solution so far, we can prune the search there.

#### Utilize Symmetries
Some problems have symmetries and we should try to exploit symmetries to reduce execution time. However, we have to remark that it is true sometimes considering symmetries can actually complicate the code. In competitive programming, this is usually not the best way (we want shorter code to minimize bugs). If the gain obtained by dealing with symmetry is not significant in solving the problem, just ignore this tip.

#### Pre-Computation
Sometimes it is helpful to generate tables or other data structures that accelerate the lookup of a result prior to teh execution of the program itself. This is called Pre-Communication, int which one trades memory/space for time.

#### Try solving the Problem Backwards
Some contest problems look far easier when they are solved 'backwards' than when they are solved using a frontal attack. Be prepared to attempt unconventional approaches to problems.

#### Optimizing Your Source Code
1. A biased opinion: Use C++ instead of Jave.
2. For C/C++ users, use the faster C-style scanf/printf rather than cin/cout.
3. Use the expected O(nlogn) but cache-friendly quicksort in C++ STL `algorithm::sort` rather than the true O(nlogn) but non cache-friendly heapsort (its root-to-leaf / leaf-to-root operations span a wide range of indices -- lots of cache misses).
4. Access a 2D array in a row major fashion (row by row) rather than in a column major fashion -- multidimensional arrays are stored in a row-major order in memory.
5. Bit manipulation on the built-int integer data types (up to the 64-bit integer) is more efficient than index manipulation in an array of booleans (see bitmask). If we need more than 64 bits, use the C++ STL bitset rather than `vector<bool>`.
6. Use lower level datastructures/types at all times if you do not need the extra functionality in the higher level (or larger) ones.
7. Declare most data structures once by placing them in global scope. Allocate enough memory to deal with the largest input of the problem. This way, we do not ahve to pass the data structures around as function argument. For problems with multiple test cases, simply clear/reset the contents of the data structure before dealing with each test case.
8. When you have the option to write your code either iteratively or recursively, choose the iterative version. Example: The iteractive C++ STL `next_permutation` and iterative subset generation techniques using bitmask are (far) faster than if you write similar routines recursively (mainly due to overheads in function calls).
9. Array access in (nested) loops can be slow. If you have an array A and you frequently access the value of `A[i]` (without changing it) in nested loops, it may be beneficial to use a local variable `temp = A[i]` and works with temp instead.
10. In C/C++, appropriate usage of macros or inline functions can reduce runtime.
11. Using C-style character arrays will yield faster execution than when using the C++ STL string.
