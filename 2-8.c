#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);
void printbits(unsigned x);

int main()
{
    unsigned int x;

    x = 1251252643;

    printf("x: ");
    printbits(x);
    printf("\nrightrotate x 5 times: ");
    printbits(rightrot(x, 5));
    printf("\n");
    return 0;
}

unsigned int rightrot(unsigned int x, int n)
{
    int i;
    unsigned int mask;
    mask = 1;

    /* Get bitmask for setting highest bit */
    while ((mask << 1) > 0) {
        mask <<= 1;
    }

    for (i = 0; i < n; i++) {
        if (x & 1) {
            x >>= 1;
            x |= mask;
        } else {
            x >>= 1;
            x &= ~mask;
        }
    }
    return x;
}

void printbits(unsigned x)
{
    char bitfield[64];
    unsigned int mask;
    int i;

    mask = 1;
    i = 0;
    while(mask > 0) {
        if (x & mask) {
            bitfield[i] = '1';
        } else {
            bitfield[i] = '0';
        }
        mask <<= 1;
        i++;
    }
    i--;
    /* Remove leading zeros */
    /*
    while (bitfield[i] == '0') {
        i--;
    }
    */
    /* Print the rest */
    while (i >= 0) {
        printf("%c", bitfield[i]);
        i--;
    }
}
