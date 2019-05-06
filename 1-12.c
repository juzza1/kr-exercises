#include <stdio.h>
#define OUT 0
#define IN 1

int main()
{
    /* Write one word per line from input */
    int c;
    int pos;
    pos = OUT;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            pos = OUT;
        } else {
            if (pos == OUT) {
                putchar('\n');
            }
            pos = IN;
            putchar(c);
        }
    }
}
