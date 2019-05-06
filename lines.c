#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int getline(char *s, int maxline);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
static char *alloc(int n);

/* getline: read line into s */
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
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
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

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

static char *alloc(int n) /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {   /* fits */
        allocp += n;
        return allocp - n;                      /* old p */
    } else {                                    /* no room */
        return 0;
    }
}
