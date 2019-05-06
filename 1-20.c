#include <stdio.h>

int main()
{
    /* detab - replace tabs in input with proper number of spaces */
    int c;
    int i;
    int linepos;
    int tablen;
    tablen = 8;

    linepos = 0;
    while ((c = getchar()) != EOF) {
        if (linepos >= tablen || c == '\n') {
            linepos = 0;
        }
        if (c == '\t') {
            for (i = 0; i < (tablen - linepos); i++) {
                putchar(' ');
            }
            linepos = 0;
        } else {
            linepos++;
            putchar(c);
        }
    }
    return 0;
}
