#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>

struct node {
    int a;
    int f;

    node(int x, int y) : a(x), f(y) {}
};

struct compare {
    bool operator()(const node* state1, const node* state2) {
        return state1->f > state2->f;
    }
};

class custom_priority_queue
    : public std::priority_queue<node*, std::vector<node*>, compare> {
public:
    bool remove(const node*& value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    std::srand(std::time(NULL));
    std::priority_queue<node*, std::vector<node*>, compare> open;

    node* p = new node(-1, -1);
    open.push(p);

    for (int i = 0; i < 50; ++i) {
        node* m = new node(std::rand() % 200, std::rand() % 200);
        open.push(m);
    }

    //    p->f = 300;
    node* resort = new node(-5, -5);
    open.push(resort);
    open.pop();
    for (; !open.empty();) {
        std::cout << (open.top()->f) << "  " << (open.top()->a) << std::endl;
        open.pop();
    }

    return 0;
}

