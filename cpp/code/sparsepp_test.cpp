// test on hash_map of sparsepp
//
//

#include <iostream>
#include <cmath>
#include "sparsepp/spp.h"
#include <ctime>


struct hashentry{
    float x, y, z, yaw, vx, vy, vz, w;

    //hashentry():x(0), y(0), z(0), yaw(0), vx(0), vy(0), vz(0), w(0){}

    hashentry(float x_, float y_, float z_, float yaw_,
            float vx_, float vy_, float vz_, float w_): 
        x(x_), y(y_), z(z_), yaw(yaw_), vx(vx_), vy(vy_), vz(vz_), w(w_){}

    bool operator==(const hashentry &out) const{
        float a = std::abs(x - out.x) + std::abs(y - out.y) + std::abs(z - out.z) + std::abs(yaw - out.yaw);
        float b = std::abs(vx - out.vx) + std::abs(vy - out.vy) + std::abs(vz - out.vz) + std::abs(w - out.w);
        if(a+b < 0.0000001) return true;
        return false;
    }
};


std::size_t hashkey(const hashentry &h){

    std::size_t seed = 0;
    spp::hash_combine(seed, h.x);
    spp::hash_combine(seed, h.y);
    spp::hash_combine(seed, h.z);
    spp::hash_combine(seed, h.yaw);
    spp::hash_combine(seed, h.vx);
    spp::hash_combine(seed, h.vy);
    spp::hash_combine(seed, h.vz);
    spp::hash_combine(seed, h.w);

    return seed;
}


int main(){
    hashentry aa(1,1,1,1,1,1,1,1);
    hashentry bb(1,1,1,1,1,1,1,2);
    hashentry cc(1,1,1,1,1,1,1,3);
    hashentry AA(2,1,1,1,1,1,1,4);
    hashentry BB(3,1,1,1,1,1,1,5);

    spp::sparse_hash_map<std::size_t, hashentry*> map;
    
    map[hashkey(aa)] = &aa;
    map[hashkey(bb)] = &bb;
    map[hashkey(cc)] = &cc;
    map[hashkey(AA)] = &AA;

    auto search = map.find(hashkey(bb));
    if(map.end() != search){
        std::cout<< search->second->w<<std::endl;
    }
    
    search = map.find(hashkey(BB));
    if(map.end() != search){
        std::cout<< search->second->w<<std::endl;
    }else{
        std::cout<<"BB not found!"<< std::endl;
    }
    

    return 0;
}
