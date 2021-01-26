/*
 * This is the file for testing convert function
 */

#include<iostream>
#include<stdio.h>
//#define CONTXY2DISC(X, CELLSIZE) (((X)>=0)?((int)((X)/(CELLSIZE))):((int)((X)/(CELLSIZE))-1))

using namespace std;


int main() {
    double cellsize = 0.0250000000;


    double m  = 0.07500;

    double n = m/cellsize;

    int t = (int) (n+0.5);
    printf("%.25f %d\n",n,t);
//    cout<<n<<endl<<t<<endl;
    return 0;
}
