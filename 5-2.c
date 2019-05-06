#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100

int getfloat(double *pn);
int getch();
void ungetch(int);

int main()
{
    double pn;
    int rval;
    rval = getfloat(&pn);
    printf("rval: %d, result: %f\n", rval, pn);
    return 0;
}

/* getfloat: get next float from input into *pn */
int getfloat(double *pn)
{
    double mul;
    int c, sign;

    while (isspace(c = getch())) {
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);     /* Not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    if (!isdigit(c)) {
        ungetch(c);
        return 0;
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    if (c == '.') {
        c = getch();
    }
    for (mul = 1.0; isdigit(c); c = getch(), mul *= 10.0) {
        *pn = 10 * *pn + (c - '0');
    }
    *pn = (*pn*sign) / mul;
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}

int buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch()         /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
