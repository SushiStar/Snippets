/*
 * To calculate if  resize and assginment is faster 
 * than the push back function.
 *
 * The push_back operation is obviously faster than the
 * resize and assignment opeartion.
 *
 */

#include <vector>
#include <ctime>
#include <iostream>

int main () {
    std::vector<uint64_t> push;
    std::vector<uint64_t> assign;
    
    std::clock_t start = std::clock();
    for(uint64_t i = 0; i < 1e8; ++i) push.push_back(i); 
    std::clock_t end = std::clock();
    double t1 = (static_cast<double> (end-start)) / CLOCKS_PER_SEC;

    start = std::clock();
    for(uint64_t i = 0; i < 1e8; ++i) {
        assign.resize(i+1);
        assign.at(i) = i;
    }
    end  = std::clock();
    double t2 = (static_cast<double> (end-start)) / CLOCKS_PER_SEC; 

    std::cout << "t1: " << t1 << " t2  " << t2 << std::endl;
}
