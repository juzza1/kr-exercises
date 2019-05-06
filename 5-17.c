#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lines.c"

#define MAXFIELDS 10

#define DIRE 0x1
#define FOLD 0x2
#define NUMERIC 0x4
#define REVERSE 0x8

void krqsort(void *lineptr[], int left, int right,
             int (*comp)(void *, void *, unsigned int *),
             int field, unsigned int *);
int numcmp(char *, char *, unsigned int *);
int astrcmp(char *s1, char *s2, unsigned int *);
void fldcpy(char t[], char s[], int field);

/* sort input lines */
int main(int argc, char *argv[])
{
    char usage[] = "usage: sort [-d] [-f] [-n] [-r] [[-d] [-f] [-n] [-r]]...";
    int fields[MAXFIELDS];
    int *fp = fields;
    unsigned int fieldops[MAXFIELDS];
    unsigned int *fop = fieldops;
    int field, nlines;
    unsigned int argmask;

    if (argc == 1) {
        *fp++ = -1;
        *fop++ = 0;
    }
    while (argc-- > 1 && (*++argv)[0] == '-') {
        field = -1;
        argmask = 0;
        while(*++argv[0]) {
            switch (*argv[0]) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': 
                field = atoi(*argv);
                break;
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
        if (fp-fields >= MAXFIELDS) {
            printf("too many fields. max: %d\n", MAXFIELDS);
            return 1;
        } else {
            *fp++ = field;
            *fop++ = argmask;
        }
    }
    if (argc != 0) {
        printf("%s\n", usage);
        return 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        while (--fp - fields >= 0) {
            --fop;
            krqsort((void **) lineptr, 0, nlines-1,
                    (int (*)(void *, void *, unsigned int *))
                    ((*fop & NUMERIC) ? numcmp : astrcmp), *fp, fop);
        }
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* krqsort: sort v[left]...v[right] into increasing order */
void krqsort(void *v[], int left, int right,
             int (*comp)(void *, void *, unsigned int *),
             int field, unsigned int *fop)
{
    int cmpr, len, i, last;
    void swap(void *v[], int, int);

    char c1[MAXLEN], c2[MAXLEN];  /* comparison strings */

    if (left >= right) {    /* do nothing if array contains */
        return;             /* fewer than two elements */
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++) {
        fldcpy(c1, v[i], field);
        fldcpy(c2, v[left], field);
        cmpr = (*comp)(c1, c2, fop);
        if (((*fop & REVERSE) && cmpr > 0) ||
                (!(*fop & REVERSE) && cmpr < 0)) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    krqsort(v, left, last-1, comp, field, fop);
    krqsort(v, last+1, right, comp, field, fop);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char s1[], char s2[], unsigned int *fop)
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
int astrcmp(char s1[], char s2[], unsigned int *fop)
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

/* fldcpy: copy blank-delimited field from s to t */
void fldcpy(char t[], char s[], int field)
{
    int len;
    if (field < 0) {
        strcpy(t, s);
        return;
    }
    while (*s == ' ' || *s == '\t') {       /* ignore leading whitespace */
        s++;
    }
    while (field-- > 0) {
        while (*s != ' ' && *s != '\t') {   /* gather non-blanks */
            if (*s == '\0') {
                *t = '\0';
                return;
            } else {
                s++;
            }
        }
        while (*s == ' ' || *s == '\t') {   /* skip until next non-blank */
            s++;
        }
    }
    for (len = 0; *(s+len)!=' ' && *(s+len)!='\t' && *(s+len)!='\0'; len++) {
        ;
    }
    strcpy(t, s);
    t[len] = '\0';
}
