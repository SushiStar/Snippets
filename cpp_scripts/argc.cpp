/* This file is used to test the input of 
 * argc and argv in main function
 */

#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(int argc,char* argv[]){
// the first argument of the input to 
// this program should be the name of 
// executable: a.out Then useful argument
// starts at argv[1]
    for(int i=1; i<argc; ++i){
//        printf("%d\n", atoi(argv[i]));
        printf("%s\n",argv[i]); 

    }

    return 0;
}
