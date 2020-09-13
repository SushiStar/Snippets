# Next Permutation
The lexicographic or lexicographical order (aka lexical order, dictionary order) means that the words are arranged in a similar fashion as they are presumed to appear in a dictionary.

STL provides `std::next_permutation` which returns the next permutation in lexicographic order by in-place rearranging the specified object as a lexicographically greater permutation. The function returns true if next higher permutation exists else if returns false to indicate that the object is already at the highest possible permutation and reset the range according to the first permutation.

```cpp
template <typename T>
bool NextPermutation(std::vector<T>& elems) {
  const int N = elems.size();

  int li = -1;  // Last index for which elems[i+1] > elems[i].
  int next_candidate_index = li + 1;
  for (int i = 0; i < N; ++i) {
    if ((i + 1 < N) && elems[i + 1] > elems[i]) {
      li = i;
      next_candidate_index = li + 1;
    }
    if (li >= 0 && elems[i] > elems[li] &&
        elems[i] < elems[next_candidate_index]) {
      next_candidate_index = i;
    }
  }

  if (li == -1) return false;

  swap(elems[li], elems[next_candidate_index]);
  reverse(elems.begin() + li + 1, elems.end());

  return true;
}

template <typename T>
vector<vector<T>> GetPermutations(const vector<T>& e) {
  vector<vector<T>> permutations;

  std::vector<T> elems(e);
  sort(elems.begin(), elems.end());

  do {
    permutations.emplace_back(elems);
  } while (NextPermutation(elems));

  return permutations;
}
```
