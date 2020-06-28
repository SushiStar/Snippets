#Quicksort
Quicksort is a divide-and-conquer method for sorting. It works by *partitioning* an array into two subarrays, then sorting the subarrays independently.
Quicksort is complementary to mergesort: for mergesort, we break the array into two subarrays to be sorted and then combine the ordered subarrays to make whole ordered array; for quicksort, we rearrange the array such that, when teh two subarrays are sorted, the whole array is ordered.

In the first instance, we do the two recursive calls *before* working on the whole array; in the second instance, we do the two recursive calls *after* working on the whole array.
```java
public class Quick {
	public static void sort(Comparable[] a) {
		StdRandom.shuffle(a);				// Eliminate dependence on input.
		sort(a, 0, a.length-1);
	}

	private static void sort(Comparable[] a, int lo, int hi) {
		if (hi <= lo) return;
		int j = partition(a, lo, hi);
		sort(a, lo, j-1);	// sort left part a[lo .. j-1]
		sort(a, j+1, hi);	// sort right part a[j+1 .. hi]
	}

	private static int partition(Comparable[] a, int lo, int hi) {
		// Partition into a[lo .. i-1], a[i], a[i+1 .. hi].
		int i = lo, j = hi+1;		// left and right scan indices
		Comparable v = a[lo];		// partitioning item
		while (true) {
			// scan right, scan left, check for scan complete, and exchange.
			while (less(a[++i], v)) if (i == hi) break;
			while (less(v, a[--j])) if (j == lo) break;
			if (i >= j) break;
			exch(a, i, j);
		}
		exch(a, lo, j); 	// Put v = a[j] into position
		return j;			// with a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
	}
}
```
Quicksort is a recursive program that sorts a subarary a[lo .. hi] by using a partition() method that puts a[i] into position and arranges the rest of the entries such that the recursive calls finish the sort.

The crux of the method is the partitioning process, which rearranges the array to make the following three conditions hold:
* The entry a[j] is in its final place in the array, for some j.
* No entry in a[lo] through a[j-1] is greater than a[j].
* No entry in a[j+1] through a[hi] is less than a[j].

This code partitions on the item v in a[lo]. The main loop exits when the scan indices i and j cross.
Within the loop, we increment i while a[i] is less than v and decrement j while a[j] is greater than v, then do an exchange to maintain the invariant property that no entries to the left of i are greater than v and no entries to the right of j are smaller than v. Once the indices meet, we complete the partitioning by exchangeing a[lo] with a[j] (j points to the rightmost entry smaller than v). (thus leaving the partitioning value in a[j]).

**Time Complexity**: Quicksort uses $2NlgN$ compares on the average to sort an array of length N with distinct keys.
