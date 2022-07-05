/**
 * @file SegmentTreeImpl.cpp
 * @author Wei Du (wweeii.du@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-07-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>

// given an array with size n
#define MAXN 400
int n, t[4 * MAXN];

/**
 * @brief recursively build segment tree;
 *        of array rang [tl, tr]
 *
 * @param a array
 * @param v node index, where t is the array container storying the tree nodes
 * @param tl left bound
 * @param tr right bound
 */
void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2; // split from middle
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm, tr);
  }
}

/**
 * @brief sum of range
 *
 * @param v node idx
 * @param tl node left boundary
 * @param tr node right boundary
 * @param l query left boundary
 * @param r query right boundary
 * @return int
 */
int sum(int v, int tl, int tr, int l, int r) {
  if (l > r) return 0;
  if (l == tl && r == tr) { // exact match
    return t[v];
  }
  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, std::min(r, tm)) +
         sum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    t[v] == new_val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(v * 2, tl, tm, pos, new_val);
    } else {
      update(v * 2 + 1, tm + 1, tr, pos, new_val);
    }
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
}