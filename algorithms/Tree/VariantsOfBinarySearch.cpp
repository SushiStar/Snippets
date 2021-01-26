/// \ contains
/*
 * Find if key is in array
 * Returns: True if key belongs to array
 * 			False if key doesn't belong to array
 */
int a[10];
bool contains(int low, int high, int key) {
    bool ans = false;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < key) {
            low = mid + 1;
        } else if (a[mid] > key) {
            high = mid - 1;
        } else {
            ans = true;
            break;
        }
    }
    return ans;
}

/// \ Index of first occurrence of a key
/*
 * Find the first occurrence index of key in array
 * Returns: an index in range [0, n-1] if key belongs to array,
 * 			-1 if key doesn't belong to array
 */
int first(int low, int high, int key) {
    int ans = -1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < key) {
            low = mid + 1;
        } else if (a[mid] > key) {
            high = mid - 1;
        } else {
            ans = mid;
            high = mid - 1; // attention
        }
    }
    return ans;
}

/// \ Index o last occurrence of a key
/*
 * Find last occurrence index of key in array
 * Returns: an index in range [0, n-1] if key belongs to array,
 * 			-1 if key doesn't belong to array
 */
int last(int low, int high, int key) {
    int ans = -1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] < key) {
            low = mid + 1;
        } else if (a[mid] > key) {
            high = mid - 1;
        } else {
            ans = mid;
            low = mid + 1; // attention
        }
    }
	return ans;
}

/// \ Index of least occurrence of a key
/*
 * Find index of first occurrence of least element greater than key in array
 * Returns: an index in range [0, n-1] if key is not the greatest element in
 * array. -1 if key is the greatest element in the array.
 */
int leastgreater(int low, int high, int key) {
    int ans = -1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] <= key) {
            low = mid + 1;
        } else if (a[mid] > key) {
            ans = mid;
            high = mid - 1;	// attention
        }
    }
	return ans;
}

/// \ Index of greatest element less than key aka. upper bound
/*
 * Find index of last occurrence of greatest element less than key in array
 * Returns: an index in range [0, n-1] if key is not the least element in array
 * 			-1 if key is the least element in array
 */
int greatestLesser(int low, int high, int key) {
	int ans = -1;
	while (low < high) {
		int mid = (high-low)/2+low;
		if (a[mid] < key) {
			ans = mid;
			low = mid + 1;
		} else if (a[mid] >= key) {
			high = mid-1;
		}
	}
	return ans;
}

