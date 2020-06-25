#Largest sum contiguous subarray

Kadane's Algorithm:
```
Initialize:
	max_so_far = 0
	max_ending_here = 0
Loop for each element of the array
	(a) max_ending_here = max_ending_here + a[i]
	(b) if (max_ending_here < 0)
		max_ending_here = 0
	(c) if (max_so_far < max_ending_here)
		max_so_far = max_ending_here
return max_so_far
```
