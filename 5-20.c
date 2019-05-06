#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "getch.c"

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

int dodcl();
int undcl(); void dcl();
void dirdcl();

int gettoken();
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

int main(char argc, char *argv[])
{
    if (argc == 1) {
        return dodcl();
    } else if (argc == 2 && (strcmp(argv[1], "-u") == 0)) {
        return undcl();
    } else {
        printf("usage: dcl [-u]\n");
        return 1;
    }
}

int dodcl() /* convert declaration to words */
{
    int c;
    while (gettoken() != EOF) {     /* 1st token on line */
        strcpy(datatype, token);    /* is the datatype */
        out[0] = '\0';
        dcl();  /* parse rest of line */
        if (tokentype != '\n') {
            printf("syntax error\n");
            /* go to next line */
            while ((c = getch()) != '\n' && c != EOF) {
                ;
            }
            if (c == EOF) {
                ungetch(c);
            }
        } else {
            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    return 0;
}


/* undcl: convert word description to declaration */
int undcl()
{
    int lcp, type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            } else if (type == '*') {
                /* Test if redundant parentheses */
                lcp = strlen(out) - 1;
                if (lcp >= 1 && (out[lcp] == ']' ||
                        (out[lcp] == ')' && out[lcp - 1] == '('))) {
                    sprintf(temp, "(*%s)", out);
                } else {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

int gettoken()  /* return next token */
{
    int c;
    int lwl;
    char *p = token;
    char temp[100];
    char *t = temp;

    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        strcpy(temp, token);
        while (strcmp(temp, "const") == 0 || strcmp(temp, "static") == 0) {
            t = temp;
            while ((c = getch()) == ' ' || c == '\t') {
                ;
            }
            for (*t++ = c; isalnum(c = getch());) {
                *t++ = c;
            }
            *t = '\0';
            ungetch(c);
            strcat(token, " ");
            strcat(token, temp);
        }
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

/* dcl: parse a declarator */
void dcl()
{
    int ns;

    for (ns = 0; gettoken() == '*';) {  /* count *'s */
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dircdl: parse a direct declarator */
void dirdcl()
{
    int type;

    if (tokentype == '(') {         /* (dcl) */
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
        }
    } else if (tokentype == NAME) { /* variable name */
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else if (type == BRACKETS) {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        } else {    /* Function declaration */
            strcat(out, " function with arguments type");
            while ((type = gettoken()) != ')') {
                if (type == ',') {
                    strcat(out, ",");
                } else if (tokentype == NAME) {
                    strcat(out, " ");
                    strcat(out, token);
                } else if (tokentype == '*') {
                    strcat(out, " pointer to");
                }
            }
            strcat(out, " returning");
        }
    }
}
