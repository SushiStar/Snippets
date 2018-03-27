#include <stdio.h>


int main() {
    char a[10];
    for(int i = 0; i < 10 ; ++i) {
        a[i] = (char)i; 
    }
    printf("%s\n",a);
    return 0;
}
