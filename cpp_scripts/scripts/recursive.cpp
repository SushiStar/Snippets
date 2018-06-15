#include <iostream>

using namespace std;

void crazy(int &i){
	
	cout<<i<<endl;
	++i;

	crazy(i);


};


int main(){
	
	int i = 0;

	crazy(i);

	return 0;

}

// 174687 times before it cracks