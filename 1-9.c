#include <stdio.h>

int main()
{
    /* Replace multiple blanks with a single blank */
    int c;
    int blank;
    blank = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blank = 1;
        } else {
            if (blank == 1) {
                putchar(' ');
                blank = 0;
            }
            putchar(c);
        }
    }
    return 0;
}
