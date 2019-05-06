#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "getch.c"

#define MAXWORD 100
#define MAXNODES 100
#define MAXLINES 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *strdup(char *);
void getnodes(struct tnode nodes[], struct tnode *p);
void qqsort(struct tnode nodes[], int left, int right);

int np = 0;

/* word frequency count */
int main()
{
    struct tnode *root;
    struct tnode nodes[MAXNODES];
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    getnodes(nodes, root);
    qqsort(nodes, 0, np-1);
    while (np--) {
        printf("%4d %s\n", nodes[np].count, nodes[np].word);
    }
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void qqsort(struct tnode nodes[], int left, int right)
{
    int i, last;
    void swap(struct tnode nodes[], int i, int j);

    if (left >= right) {
        return;
    }
    swap(nodes, left, (left+right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (nodes[i].count < nodes[left].count) {
            swap(nodes, ++last, i);
        }
    }
    swap(nodes, left, last);
    qqsort(nodes, left, last-1);
    qqsort(nodes, last+1, right);
}

void swap(struct tnode nodes[], int i, int j)
{
    struct tnode temp = nodes[j];
    nodes[j] = nodes[i];
    nodes[i] = temp;
}


/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

void getnodes(struct tnode nodes[], struct tnode *p)
{
    if (p != NULL) {
        getnodes(nodes, p->left);
        if (np < MAXNODES) {
            nodes[np++] = *p;
        }
        getnodes(nodes, p->right);
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
