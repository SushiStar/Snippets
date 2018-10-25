#include<iostream>
#include<cmath>
#include<ctime>

double inline Sqrt(double x) {
    unsigned int  i = *(unsigned int *) &x;
    i += 127 << 23;
    i >>= 1;
    return *(double*) &i;
}


int main() {
    double m;
    std::clock_t start = std::clock();
    for(int i = 0; i < 10000; ++i) {
        m = std::sqrt((double)i);
    }
    std::clock_t end = std::clock();
    double err1 = (double)(end - start)/CLOCKS_PER_SEC;

    start = std::clock();
    for(int i = 0; i < 10000; ++i) {
        m = Sqrt((double)i);
    }
    end = std::clock();
    double err2 = (double)(end - start)/CLOCKS_PER_SEC;

    std::cout << "err1: " << err1 << std::endl << "err2: " << err2 << std::endl;

    return 0;
}
