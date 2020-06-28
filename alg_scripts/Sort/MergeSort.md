#Merge Sort
To sort an array, divide it into two halves, sort the two havles (recursively), and then merge the results.
One of merge sort's most attractive properties is that it guarantees to sort any array of N items in time proporitonal to $Nlog(N)$. Its prime disadavntage is that it uses extra space proportional to N.

####Abstract in-place merge
The straightforward approach to implementing merging is to design a method that merges two disjoint ordered arrays of Compararble objects into a third array. However, when we mergesort a large array, we are doing a huge number of merges, so the cost of creating a new array to hold the output every time that we do a merge is problematic. It would be more desirable to have an in-place method so that we could sort the first half of the array in place, then sort the second half of the array in place, then do the merge of the two halves by moving the items around withint the array, without using a significant amount of other extra space.
```java
public static void merge(Comparable[] a, int lo, int mid, int hi) {
	int i = lo, j = mid+1;
	for (int k = lo; k <= hi; ++k) // Copy a[lo...hi] to aux[lo...hi];
		aux[k] = a[k];
	for (int k = lo; k <= hi; ++k) // Merge back to a[lo ... hi].
		if (i > mid) 	a[k] == aux[j++];
		else if (j > hi) a[k] = aux[i++];
		else if (less(aux[j], aux[i])) a[k] = aux[j++];
		else a[k] = aux[i++];
}
```
This method merges by first copying into the auxiliary array aux[] then merging back to a[]. In the merge (the second for loop), there are four conditions: left half exhausted (take from the right), right half exhausted (take from left), current key on right less than current key on left (take from the right), and current key on right greater than or equal to current key on left (take from the left).
####Top-down merge sort
```java
public class Merge {
	private static void sort (Comparable[] a) {
		aux = new Comparable[a.length];	// allocate space just once.
		sort(a, 0, a.length-1);
	}
	private static void sort(Comparable[] a , int lo, int hi) {
		if (hi <= lo) return;
		int mid = lo + (hi-lo)/2;
		sort (a, lo, mid);
		sort (a, mid+1, hi);
		merge(a, lo, mid, hi);
	}
}
```
**Time Complexity**: Top-down mergesort uses at most $6NlgN$ array accesses to sort an array of length N.
####Bottom-up merge sort
```java
public class MergeBU {
	prviate static Comparable[] aux;
	// see previous code for merge();

	public static void sort(Comparable[] a) {
		int N = a.length;
		aux = new Comparable[N];
		for (int sz = 1; sz < N; sz *= 2)
			for (int lo = 0; lo < N-sz; lo+=sz*2)
				merge(a, lo, lo+sz-1, Math.min(lo+sz+sz-1, N-1));
	}
}
Bottom-up mergesort consists of a sequence of passes over the whole array, doing sz-by-sz merges, starting with sz equal to 1 and doubling sz on each pass. The final subarray is of size sz only when the array size is an even multiople of sz (otherwise it is less than sz).
```
**Time Complexity**: Bottom-up mergesort uses between $1/2NlgN$ and $NlgN$ compares and at most $6NlgN$ array accesses to sort an array of length $N$.
No compare-based sorting algorithms can guarantee to sort N items with fewer than $lg(N) ~ NlgN$ compares.
Merge sort is an asymptotically optimal compare-based sorting algorithm.
