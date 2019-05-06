#include <stdio.h>

int bitcount(unsigned x);

int main()
{
    return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;
    b = 0;
    while(x > 0) {
        x &= (x-1);
        b++;
    }
    return b;
}
