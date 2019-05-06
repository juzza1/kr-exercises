#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lines.c"

static int fold;

void krqsort(void *lineptr[], int left, int right,
             int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);
int astrcmp(char *s1, char *s2);

/* sort input lines */
int main(int argc, char *argv[])
{
    extern int fold;
    char usage[] = "usage: sort [-f] [-n] [-r]";
    int nlines;         /* number of input lines read */
    int numeric, reverse;
    fold = numeric = reverse = 0;

    while (argc-- > 1 && (*++argv)[0] == '-') {
        while(*++argv[0]) {
            switch (*argv[0]) {
            case 'f':
                fold = 1;
                break;
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("%s\n", usage);
                return 1;
            }
        }
    }
    if (argc != 0) {
        printf("%s\n", usage);
        return 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        krqsort((void **) lineptr, 0, nlines-1,
                (int (*)(void *, void *))(numeric ? numcmp : astrcmp), reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* krqsort: sort v[left]...v[right] into increasing order */
void krqsort(void *v[], int left, int right,
             int (*comp)(void *, void *), int reverse)
{
    int cmpr, i, last;
    void swap(void *v[], int, int);

    if (left >= right) {    /* do nothing if array contains */
        return;             /* fewer than two elements */
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++) {
        cmpr = (*comp)(v[i], v[left]);
        if ((reverse && cmpr > 0) || (!reverse && cmpr < 0)) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    krqsort(v, left, last-1, comp, reverse);
    krqsort(v, last+1, right, comp, reverse);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

/* astrcmp: agnostic string comparison */
int astrcmp(char *s1, char *s2)
{
    int cont = 1;
    int t1, t2;

    while (cont) {
        if (fold == 1) {
            t1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 - 'A' + 'a' : *s1;
            t2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 - 'A' + 'a' : *s2;
        } else {
            t1 = *s1;
            t2 = *s2;
        }
        if (t1 != t2) {
            cont = 0;
        } else if (t1 == '\0') {
            return 0;
        } else {    /* same char but not end */
            s1++;
            s2++;
        }
    }
    return t1 - t2;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
