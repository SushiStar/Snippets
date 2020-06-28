#Insertion Sort
The algorithm that people often use to sort bridge hands is to consider the cards one at a time, inserting each into its proper place among those already considered (keeping them sorted).
In a computer implementation, we need to make space to insert the current item by moving larger items one position to the right, before inserting the current item into the vacated position.

**Time complexity**: Insertion sort uses $N^2/4$ compares and $N^2/4$ exchanges to sort a randomly ordered array of length $N$ on average. The worst case is $N^2$ compares and $N^2$ exchanges and teh best caes is $N-1$ compares and 0 exchanges.

```cpp
void insertionSort(int arr[], int n) {
	int i, key, j;
	for (int i = 1; i < n; ++i) {
		key = arr[i];
		j = i-1;
		// Move elements of array[0, ..., i-1], that are greater
		// than key, to one position ahead of their current position
		while (j >= 0 && arr[j] > key) {
			arr[j+1] = arr[j];
			--j;
		}
		arr[j+1] = key;
	}
}
```

####Partially sorted arrays:
- An array where each entry is not far from its final position
- A small array appended to a large sorted array
- An array with only a few entries that are not in place
Insertion sort is an efficient method for such arrays; selection sort is not. Indeed, when the number of inversions is low, insertion sort is likely to be faster than any sorting method that we generally consider.
**Ths number of exchanges used by insertion sort is equal to the number of inversions in the array, and the number of compares is at least equal to the number of inversions and at most equal to the number of inversions plus the array size minus 1.
