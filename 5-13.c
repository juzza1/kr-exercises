#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define STACKSIZE 100000
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int getline(char *s, int maxline);
int readlines(char *lineptr[], int maxlines, char stack[]);
void writelines(char *lineptr[], int nlines);

/* sort input lines */
int main(int argc, char *argv[])
{
    char *orgp;
    char stack[STACKSIZE];
    char usage[] = "Usage: tail [-n]";

    int last, nlines;

    if (argc == 1) {
        last = 10;
    } else if (argc == 2 && argv[1][0] == '-' && isdigit(argv[1][1])) {
        orgp = argv[1];
        printf("%c\n", *++argv[1]);
        while (*argv[1]) {
            if (!isdigit(*argv[1])) {
                printf("%s\n", usage);
                return 1;
            }
            argv++[1];
        }
        last = atoi(orgp+1);
    } else {
        printf("%s\n", usage);
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES, stack)) >= 0) {
        writelines(lineptr, nlines<last ? nlines : last);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


int getline(char *s, int maxline)
{
    int c, n;

    for (n = 0; (c = getchar()) != '\n' && c != EOF && n < maxline; n++) {
        *s++ = c;
    }
    if (c == '\n') {
        n++;
        *s++ = c;
    }
    *s = '\0';
    return n;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char stack[])
{
    int len, nlines;
    char *sp, line[MAXLEN];
    sp = stack;

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (len + sp) > (stack + STACKSIZE)) {
        /*if (nlines >= maxlines || (p = alloc(len)) == NULL) { */
            return -1;
        } else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(sp, line);
            lineptr[nlines++] = sp;
            sp += len;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}
