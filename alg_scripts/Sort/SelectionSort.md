#Selection sort
Repeatedly selecting the smallest in the remaining item.
1. Find the smallest item in the array and exchange it with the first entry (itself if the first entry is already the smallest).
2. Findt he next smallest item and exchange it with the second entry.
3. Continue in this way until the entire array is sorted.

```java
public class Selection {
	public static void sort(Comparable[] a) {
		int N = a.length;
		for (int i= 0; i < N; ++i) {
			int min = i;
			for (int j = i+1; j < N; ++j) {
				if (less(a[j], a[min])) min = j;
			}
			exch(a, i, min);
		}
	}
}
```
**Time Complexity**: $O(n^2)$;
