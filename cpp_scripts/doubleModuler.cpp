#include <iostream>
#include <cmath>

using namespace std;


int main(){
    double a = 3.15;
    double b = 1.57;

    double c;

    c = a%b;
    cout<<"3.15%1.57 is: "<<c<<endl;

    c = a/b;
    cout<<"3.15/1.57 is: "<<c<<endl;
   
    c = b%a;
    cout<<"1.57%3.14 is: "<<c<<endl;
   
    c = b/a;
    cout<<"1.57/3.14 is: "<<c<<endl;
    
    return 0; 
}
