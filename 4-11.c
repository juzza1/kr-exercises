#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* atof() */
#include <string.h>

#define MAXOP 100   /* max size of operand or operator */
#define MAXVAL 100 /* max depth of val stack */
#define VARSTORE 26 /* size of variable store */
#define NUMBER '0'  /* signal that a number was found */
#define PRINT '1'
#define DUPLICATE '2'
#define SWAP '3'
#define CLEAR '4'
#define SIN '5'
#define COS '6'
#define TAN '7'
#define EXP '8'
#define POW '9'
#define STORE 'S'
#define LOAD 'L'
#define ERR 'E'

int getch();
void ungetch(int);
void ungets(char[]);
int getop(char[]);
void push(double);
double pop(void);


int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* val stack */

/* reverse polish calculator */
int main()
{
    int i, type;
    double op2, op3;
    char s[MAXOP];
    double vars[VARSTORE];
    int goodval[VARSTORE];
    for (i = 0; i < VARSTORE; i++) {
        goodval[i] = 0;
    }

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0) {
                push(pop() / op2);
            } else {
                printf("error: zero divisor\n");
            }
            break;
        case '%':
            op2 = pop();
            push((int)pop() % (int)op2);
            break;
        case PRINT:
            if (sp > 0) {
                op2 = pop();
                push(op2);
                printf("\tElement on top of the stack: %.8g\n", op2);
            } else {
                printf("\tCan't print top element, stack is empty.\n");
            }
            break;
        case DUPLICATE:
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case SWAP:
            op2 = pop();
            op3 = pop();
            push(op2);
            push(op3);
            break;
        case CLEAR:
            sp = 0;
            break;
        case SIN:
            push(sin(pop()));
            break;
        case COS:
            push(cos(pop()));
            break;
        case TAN:
            push(tan(pop()));
            break;
        case EXP:
            push(exp(pop()));
            break;
        case POW:
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case STORE:
            op2 = pop();
            push(op2);
            vars[s[0]] = op2;
            goodval[s[0]] = 1;
            break;
        case LOAD:
            if (goodval[s[0]]) {
                push(vars[s[0]]);
            } else {
                printf("error: variable %c not yet saved.\n", 'a' + s[0]);
            }
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, d;
    static int uc = -2;

    /* ignore leading whitespace */
    if (uc == -2) {
        s[0] = c = getch();
    } else {
        s[0] = c = uc;
        uc = -2;
    }
    while (c == ' ' || c == '\t') {
        s[0] = c = getch();
    }
    if (c == EOF) {
        return c;
    }
    if (c == '\n') {
        return c;
    }
    /* gather op until whitespace */
    for (i = 1; (c = getch()) != ' ' && c != '\n' && c != '\t'; i++) {
        s[i] = c;
    }
    s[i] = '\0';
    uc = c;
    if (strcmp(s, "PRINT") == 0) {
        return PRINT;
    } else if (strcmp(s, "DPL") == 0) {
        return DUPLICATE;
    } else if (strcmp(s, "SWAP") == 0) {
        return SWAP;
    } else if (strcmp(s, "CLR") == 0) {
        return CLEAR;
    } else if (strcmp(s, "SIN") == 0) {
        return SIN;
    } else if (strcmp(s, "COS") == 0) {
        return COS;
    } else if (strcmp(s, "TAN") == 0) {
        return TAN;
    } else if (strcmp(s, "EXP") == 0) {
        return EXP;
    } else if (strcmp(s, "POW") == 0) {
        return POW;
    } else if (strlen(s) == 1) {
        if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/' ||
                s[0] == '%') {
            return s[0];
        } else if (s[0] >= 'a' && s[0] <= 'z') {
            s[0] -= 'a';
            return STORE;
        } else if (s[0] >= 'A' && s[0] <= 'Z') {
            s[0] -= 'A';
            return LOAD;
        }
    }

    i = 0;
    if (s[i] == '+' || s[i] == '-') { /* Test if sign if followed by number */
        i++;
    }
    while (isdigit(s[i])) {   /* Check integer part */
        i++;
    }
    if (s[i] == '.') {          /* Check fraction part */
        i++;
        while (isdigit(s[i])) {
            i++;
        }
    }
    if (s[i] == '\0') {
        return NUMBER;
    } else {
        return ERR;
    }
}

#define BUFSIZE 100

int buf[BUFSIZE];  /* buffer for ungetch */
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

void ungets(char s[]) /* push string back onto input */
{
    int i;
    for (i = strlen(s)-1; i >= 0; i--) {
        ungetch(s[i]);
    }
}

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
