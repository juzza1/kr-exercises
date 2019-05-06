#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100

int getint(int *pn);
int getch();
void ungetch(int);

int main()
{
    int pn;
    printf("%d\n", getint(&pn));
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
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
    *pn *= sign;
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
