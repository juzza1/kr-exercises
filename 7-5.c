#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> /* atof() */

#include "getline.c"

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getch();
void ungetch(int);
int getop(char[]);
void push(double);
double pop(void);

/* reverse polish calculator */
int main()
{
    char line[100];
    int good = 0;
    double num1, num2;
    char op;

    while (getline(line) != EOF) {
        if ((sscanf(line, "%lf %lf %c \n", &num1, &num2, &op)) == 3) {
            good = 1;
            switch(op) {
            case '+':
                printf("%f %f\n", num1, num2);
                push(num1 + num2);
                break;
            case '-':
                push(num1 - num2);
                break;
            case '*':
                push(num1 * num2);
                break;
            case '/':
                push(num1 / num2);
                break;
            default:
                good = 0;
                printf("error: unknown command %c\n", op);
                break;
            }
            if (good) {
                printf("\t%.8g\n", pop());
            }
        } else {
            printf("malformed input\n");
        }
    }
    return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, d;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '+' && c != '-') {
        return c;       /* Not a number */
    }
    i = 0;
    if (c == '+' || c == '-') { /* Test if sign if followed by number */
        if (isdigit(d = getch()) || d == '.') {
            s[++i] = d;
            c = d;
        } else {
            ungetch(d);
            return c;
        }
    }
    if (isdigit(c)) {   /* Collect integer part */
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    if (c == '.') {     /* Collect fraction part */
        while (isdigit(s[++i] = c = getch())) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
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

#define MAXVAL 100 /* max depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* val stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, cant push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop()
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
