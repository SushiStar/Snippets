/*
 * Three ways to define comparison functions in C++
 *
 * Date: 02/18/2020
 */
#include <vector>
#include <set>
#include <queue>
using namespace std;

// Define operators <()
struct Edge {
    int from, to, weight;
    // the overloaded operator < must be non-member function
    friend bool operator<(Edge &curr, Edge &other) { return curr.weight > other.weight; }
};

struct Edge {
    int from, to, weight;
    friend bool operator<(Edge &a, Edge &b) const {
        return a.weight > b.weight;
    }
};

priority_queue<Edge> pq; // use it directly
set<Edge> s;
std::vector<Edge> vct;
sort(vct.begin(), vct.end());


// Define a custom comparison function
bool cmp(Edge &a, Edge &b) const {
    return a.weight < b.weight;
}
sort(data.begin(), data.end(), cmp);


// Define operator ()()
/*
 * A functor (function object), is an object that can behave like a function.
 * This is done by defining operator()() of a class. In this case, implement
 * operator()() as a comparison function.
 */
std::vector<int> occurrences;
struct cmp {
    bool operator()(int a, int b) {
        return occurrences[a] < occurrences[b];
    }
};

std::set<int, cmp> s;
std::priority_queue<int, std::vector<int>, cmp> pq;
