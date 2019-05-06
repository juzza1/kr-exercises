#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
void printbits(unsigned x);

int main()
{
    unsigned int x;
    unsigned int y;

    x = 17;
    y = 26;

    printf("x: ");
    printbits(x);
    printf("\ny: ");
    printbits(y);
    printf("\nsetbits to x and y: ");
    printbits(setbits(x, 2, 3, y));
    printf("\n");
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    x &= ~(~(~0 << n) << p+1-n);    /* Set bits to be changed to 0 */
    y = (y & ~(~0 << n)) << p+1-n;  /* Set other bits to 0 */
    return (x |= y);
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
