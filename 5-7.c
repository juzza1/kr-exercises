#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define STACKSIZE 100000

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int maxlines, char stack[]);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
    char stack[STACKSIZE];

    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES, stack)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int getline(char *s, int maxline);

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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) {    /* do nothing if array contains */
        return;             /* fewer than two elements */
    }
    swap(v, left, (left + right/2));
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
