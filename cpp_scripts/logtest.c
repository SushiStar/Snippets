#include<math.h>
#include<stdio.h>

int main(){

    int a = 15;
    double logvalue = log(a)/log(2);
    if(0.001 > logvalue - floor(logvalue)){
        printf("true\n");
    }else{
        printf("false\n");
    }


    return 0;
}
