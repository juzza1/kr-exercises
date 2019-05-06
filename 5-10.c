#include <stdio.h>
#include <string.h>
#define OTHER '0'
#define NUMBER '1'
#define SZ 1000

int getop(char *op);
int pop();
void push(int n);
    
int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("usage: expr op [op]...\n");
        return 1;
    }
    int op;

    while (argc-- > 1) {
        ++argv;
        switch (getop(*argv)) {
        case OTHER:
            switch((*argv)[0]) {
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op = pop();
                push(pop() - op);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op = pop();
                push(pop() / op);
                break;
            default:
                printf("Unknown argument: %s\n", *argv);
                break;
            }
            break;
        case NUMBER:
            push(atoi(*argv));
            break;
        default:
            break;
        }
    }
    printf("\t%d\n", pop());
    return 0;
}

int getop(char *op)
{
    if (strlen(op) == 1) {
        if (!isdigit(*op)) {
            return OTHER;
        }
        return NUMBER;
    }
    if (strlen(op) >= 2 && (*op == '+' || *op == '-')) {
        while (*++op) {
            if (!isdigit(*op)) {
                return OTHER;
            }
        }
    }
    return NUMBER;
}

static int stack[SZ];
static int *sp = stack;

int pop()
{
    if (sp > 0) {
        return *--sp;
    } else {
        printf("stack empty\n");
        return 0;
    }
}

void push(int n)
{
    if (sp <= (stack + SZ)) {
        *sp++ = n;
    } else {
        printf("stack full\n");
    }
}
