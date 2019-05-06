#include <stdio.h>
#define FALSE 0
#define TRUE 1

int main()
{
    /* entab - replace spaces in input with tabs */
    int blankc;
    int c;
    int linepos;
    int tablen;
    tablen = 8;

    blankc = linepos = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            while (blankc > 0) {
                putchar(' ');
                blankc--;
            }
            putchar(c);
        } else {
            blankc++;
        }
        linepos++;
        
        if (linepos == tablen && blankc > 0) {
            putchar('\t');
            blankc = 0;
            linepos = 0;
        }

        if (linepos == tablen || c == '\n' || c == '\t') {
            linepos = 0;
        }
    }
    return 0;
}
