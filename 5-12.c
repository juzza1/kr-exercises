#include <stdio.h>
#define DEFTAB 8

int gettablen(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    /* detab - replace tabs in input with proper number of spaces */
    int c, i, linepos, tablen, start;
    char usage[] = "Usage: entab [-m] [+n]";

    tablen = 8;
    linepos = start = 0;
    while (--argc > 0 && ((*++argv)[0] == '-' || (*argv)[0] == '+')) {
        switch(*argv[0]) {
        case '-':
            start = atoi(++argv[0]);
            break;
        case '+':
            tablen = atoi(++argv[0]);
            break;
        default:
            printf("Unknown argument: %s\n", *argv);
            printf("%s\n", usage);
            return 1;
        }
    }
    if (argc != 0) {
        printf("%s\n", usage);
        return 1;
    }
    /* Ignore beginning */
    while (--start >= 0) {
        putchar(getchar());
    }
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
