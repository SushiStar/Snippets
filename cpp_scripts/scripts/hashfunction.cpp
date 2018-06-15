#include <stdio.h>

#define XYTHETA2INDEX(X, Y, THETA) (THETA + X * 16 + \
									Y * 3000 * 16)

static unsigned int inthash(unsigned int key){
	key += (key << 12);
	key ^= (key >> 22);
	key += (key << 4);
	key ^= (key >> 9);
	key += (key << 10);
	key ^= (key >> 2);
	key += (key << 7);
	key ^= (key >> 12);
	return key;
}
unsigned int GETHASHBIN(
	unsigned int X1,
	unsigned int X2,
	unsigned int Theta)
{

	unsigned int a;
	// a = inthash(inthash(X1) + (inthash(X2) << 1) + (inthash(Theta) << 2)) & (4*3001*3000- 1);

	a = XYTHETA2INDEX(X1, X2, Theta) & (4 *1024 * 1024-1);
	printf("get: %d %d %d id: %d \n", X1, X2, Theta, a);


	return a;
}

int main(){
	for(int i = 0; i < 1000; ++i){
		for(int j = 0; j < 1000; ++j){
			for(int k = 0; k <16; ++k){
				GETHASHBIN(i,j,k);
			}
		}
	}

	return 0;
}