#include <stdio.h>

#define BUFSIZE 100
#define MAXVAL 100          /* max depth of val stack */

int lc = 0;                 /* line count */

int getch();
void ungetch(int);

static int buf[BUFSIZE];    /* buffer for ungetch */
static int bufp = 0;        /* next free position in buf */

int getch(void)             /* get a (possibly pushed back) character */
{
    int c;
    c = bufp > 0 ? buf[--bufp] : getchar();
    if (c == '\n') {
        lc++;
    }
    return c;
}

void ungetch(int c)         /* push character back on input */
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
        if (c == '\n') {
            lc--;
        }
    }
}
