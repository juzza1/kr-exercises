#include <stdio.h>

int main()
{
    int c;
    while ((c = getchar()) != EOF) {
        if (c > 127) {  
            printf(" o%o ", c);
        } else {
            putchar(c);
        }
    }
}
