#include <stdio.h>
#define DEFTAB 8

int gettablen(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    /* detab - replace tabs in input with proper number of spaces */
    int c;
    int i;
    int linepos;
    int tablen;

    tablen = gettablen(argc, argv);
    linepos = 0;
    while ((c = getchar()) != EOF) {
        if (linepos >= tablen || c == '\n') {
            linepos = 0;
            if (linepos >= tablen) {
                tablen = gettablen(argc, argv);
            }
        }
        if (c == '\t') {
            for (i = 0; i < (tablen - linepos); i++) {
                putchar(' ');
            }
            tablen = gettablen(argc, argv);
            linepos = 0;
        } else {
            linepos++;
            putchar(c);
        }
    }
    return 0;
}

int gettablen(int argc, char *argv[])
{
    static int current = 0;

    if (argc > 2) {
        if (current >= argc-1) {
            current = 1;
        } else {
            current++;
        }
        return atoi(argv[current]);
    } else {
        return DEFTAB;
    }
}
