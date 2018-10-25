// check the difference between unsinged and signed int 

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

int main(){
	
	int a = 100;
	int b = 101;
	unsigned int  c = 100;
	unsigned int  d = 101;
    printf("%s %d\n",__func__,__LINE__);
	cout<<(a-b)<<endl;
//	cout<<(c-d)<<endl;
	return 0;
}
