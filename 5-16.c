#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lines.c"

#define MAXFIELDS 10

#define DIRE 0x1
#define FOLD 0x2
#define NUMERIC 0x4
#define REVERSE 0x8

static unsigned int fieldops[MAXFIELDS];
static unsigned int *fop = fieldops;    /* pointer to field options */

void krqsort(void *lineptr[], int left, int right,
             int (*comp)(void *, void *));
int numcmp(char *, char *);
int astrcmp(char *s1, char *s2);
int getfield(char *s, int field);

/* sort input lines */
int main(int argc, char *argv[])
{
    char usage[] = "usage: sort [-f] [-n] [-r]";
    int nlines;             /* number of input lines read */
    int numeric, reverse;
    unsigned int argmask;
    numeric = reverse = 0;

    while (argc-- > 1 && (*++argv)[0] == '-') {
        argmask = 0;
        while(*++argv[0]) {
            switch (*argv[0]) {
            case 'd':
                argmask |= DIRE;
                break;
            case 'f':
                argmask |= FOLD;
                break;
            case 'n':
                argmask |= NUMERIC;
                break;
            case 'r':
                argmask |= REVERSE;
                break;
            default:
                printf("%s\n", usage);
                return 1;
            }
        }
        if (fop - fieldops >= MAXFIELDS) {
            printf("too many fields. max: %d\n", MAXFIELDS);
            return 1;
        } else {
            *fop++ = argmask;
        }
    }
    if (argc != 0) {
        printf("%s\n", usage);
        return 1;
    }
    if (fop - fieldops <= 1) {  /* 0-1 fields specified */
        fop = fieldops;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        krqsort((void **) lineptr, 0, nlines-1,
                (int (*)(void *, void *))
                ((*fop & numeric) ? numcmp : astrcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* krqsort: sort v[left]...v[right] into increasing order */
void krqsort(void *v[], int left, int right, int (*comp)(void *, void *))
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
        if (((*fop & REVERSE) && cmpr > 0) || (!(*fop & REVERSE) && cmpr < 0)) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    krqsort(v, left, last-1, comp);
    krqsort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
        if (*fop & DIRE) {   /* Directory comparison */
            while (!((*s1 >= 'a' && *s1 <= 'z') ||
                     (*s1 >= 'A' && *s1 <= 'Z') ||
                     (*s1 >= '0' && *s1 <= '9') ||
                      *s1 == ' ' || *s1 == '\0')) {
                s1++;
            }
            while (!((*s2 >= 'a' && *s2 <= 'z') ||
                     (*s2 >= 'A' && *s2 <= 'Z') ||
                     (*s2 >= '0' && *s2 <= '9') ||
                      *s2 == ' ' || *s2 == '\0')) {
                s2++;
            }
        }
        if (*fop & FOLD) {
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

/* getfield: get start of blank delimited field from s, return length */
int getfield(char *s, int field)
{
    int len;
    char *start;
    while (*s == ' ' || *s == '\t') {       /* ignore leading whitespace */
        s++;
    }
    while (field-- >= 0) {
        while (*s != ' ' && *s != '\t') {   /* gather non-blanks */
            if (*s == '\0') {
                return -1;
            } else {
                s++;
            }
        }
        while (*s == ' ' || *s == '\t') {   /* skip until next non-blank */
            s++;
        }
    }
    for (len = 0, start = s; *start != ' ' && *start != '\t'; len++, start++) {
        ;
    }
    return len;
}
