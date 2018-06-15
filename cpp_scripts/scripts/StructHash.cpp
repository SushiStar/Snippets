// hash a struct into unordered_map
// version: 1.0
// Date: May/21/2018
// to build a hashfunction key value pair is <int, point>

#include<boost/functional/hash.hpp>
#include<iostream>
#include<unordered_map>

class point
{
public:
    double x;
    double y;
    
    point(): x(0), y(0){}
    point(double x, double y):x(x), y(y) {}

    bool operator==(point const& other) const{
        return x == other.x && y == other.y;
    }
};

std::size_t hash_value(point const& p){
    std::size_t seed = 0;
    boost::hash_combine(seed, p.x);
    boost::hash_combine(seed, p.y);
    return seed;
}


int main(){
    point a(1,2);
    point b(3,4);
    std::unordered_map<std::size_t ,point*> mmp;
    
     
    mmp[hash_value(a)] = &a;
    mmp[hash_value(b)] = &b;
    
    std::cout<<mmp[hash_value(a)]<<std::endl;
    std::cout<<mmp[hash_value(b)]<<std::endl;

    std::cout<<hash_value(a)<<"  "<<hash_value(b)<<std::endl;

    return 0;
}
