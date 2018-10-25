#include<stdio.h>
#include<stdlib.h>
int main(){ 
   int *a;
   a = malloc(sizeof(int));
   *a = 20;

   int *b;
   b = a;
   free(a);
   printf("%d\n",*b);

   return 0;
}
