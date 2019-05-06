#include <stdio.h>

unsigned invert(unsigned x, int p, int n);
void printbits(unsigned x);

int main()
{
    unsigned int x;

    x = 50;

    printf("x: ");
    printbits(x);
    printf("\ninvert x at 4, 3 bits: ");
    printbits(invert(x, 4, 3));
    printf("\n");
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return (~x & (~(~0 << n) << p+1-n)) | (x & ~(~(~0 << n) << p+1-n));
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
    /* Remove leading zeros */
    i--;
    while (bitfield[i] == '0') {
        i--;
    }
    /* Print the rest */
    while (i >= 0) {
        printf("%c", bitfield[i]);
        i--;
    }
}
