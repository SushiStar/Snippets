/* This small program shows the return-by-reference
 * operation in c++
 *
 * Author: Wei Du
 * Date:01/14/2018
 */

#include<iostream>
using namespace std;

class rbr{
public:
    int a;

    int& rf();


};

int& rbr::rf(){
    return a;
}

int main(){
    rbr m;
    m.a = 1;

    int& b = m.rf();

    cout<<"This is m.a: "<<m.a<<endl;
    cout<<"This is b: "<<b<<endl;

    b = 2;

    cout<<"After setting b to 2, m.a is: "<<m.a<<endl;

    return 0;
}
