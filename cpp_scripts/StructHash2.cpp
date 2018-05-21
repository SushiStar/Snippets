// hash a struct into unordered_map
// version: 1.2
// Date: May/21/2018
// hash the object directly

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


namespace std
{
    template<> struct hash<point>{
        typedef point argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const noexcept{
            return hash_value(s);           
        }
    };
}



int main(){
    point a(1,2);
    point b(1,2);
    std::unordered_map<point ,point*> mmp;
        
    mmp[a] = &a;
    if(&a == mmp[b]){
        std::cout<<"Good!"<<std::endl;
    }else{
        std::cout<<"Bad!"<<std::endl;
    }

    return 0;
}
