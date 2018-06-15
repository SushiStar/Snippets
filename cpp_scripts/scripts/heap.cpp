#include <iostream>
#include <queue>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>

struct node{
    int a;
    int f;

    node(int x, int y):a(x), f(y){}
};


struct compare{
    bool operator()(const node* state1, const node* state2){
        return state1->f > state2->f;
    }
};


int main(){
    std::srand(std::time(NULL));
    std::vector<node*> open;
    std::make_heap(open.begin(), open.end(), compare());

    node* p = new node(10,-1);
    open.push_back(p);

    for(int i = 0; i< 50; ++i){
        node* m = new node(std::rand()%200, std::rand()%200);
        
        open.push_back(m);
        std::push_heap(open.begin(), open.end(), compare());
    }
    
    std::vector<node*>::iterator it;
    it = std::find(open.begin(), open.end(), p);
    if(it != open.end()){
        open.erase(it);
    }
    std::make_heap(open.begin(), open.end(), compare());
    while(open.size()>0){
        std::cout<<open.front()->f<<"  "<< open.front()->a<<std::endl;

        std::pop_heap(open.begin(), open.end(), compare()); open.pop_back();
    }
  
    return 0;
}

