#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "getch.c"

#define MAXWORD 100
#define MAXLINES 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct tnode {
    char *word;
    int linenums[MAXLINES];
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *strdup(char *);

/* word frequency count */
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond, i;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        for (i = 0; i < MAXLINES; i++) {
            p->linenums[i] = 0;
        }
        p->linenums[lc] = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->linenums[lc] = 1;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;
    if (p != NULL) {
        treeprint(p->left);
        printf("\t%s", p->word);
        for (i = 0; i < MAXLINES; i++) {
            if (p->linenums[i] != 0) {
                printf(" %d", i + 1);
            }
        }
        printf("\n");
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc()
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    int cont;
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }
    if (c == '#') { /* Preprocessor line, go to next line */
        while ((c = getch()) != '\n') {
            ;
        }
        return getword(word, lim);
    }
    /* String constant */
    if (c == '"') {
        *w++ = c;
        while ((*w++ = c = getch()) != '"') {
            /* Always consume escaped char */
            if (c == '\\') {
                *w++ = getch();
            }
        }
        *w = '\0';
        return word[0];
    }
    if (c == '/') {
        if ((c = getch()) == '*') {
            *w++ = '/';
            *w++ = '*';
            while (1) {
                if ((c = getch()) == '*') {
                    if ((c = getch()) == '/') {
                        *w++ = '*';
                        *w++ = '/';
                        break;
                    } else {
                        ungetch(c);
                        c = '*';
                    }
                }
                *w++ = c;
            }
            *w = '\0';
            return word[0];
        } else {
            ungetch(c);
            c = '/';
        }
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
