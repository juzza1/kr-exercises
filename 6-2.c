#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "getch.c"

#define MAXTREES 100
#define MAXWORD 100

struct inode {
    char *word;
    struct inode *left;
    struct inode *right;
};

struct onode {
    struct inode *inner;
    struct onode *left;
    struct onode *right;
};

struct inode *addinner(struct inode *, char *);
struct onode *addouter(struct onode *, char *, int minlen);
struct inode *ialloc();
struct onode *oalloc();
char *strdup(char *);
void treeprinti(struct inode *);
void treeprinto(struct onode *, int loners);
int getword(char *, int);
int strbeg(char *a, char *b, int len);


/* count C keywords, pointer version */
int main(int argc, char *argv[])
{
    struct onode *groups;   /* Tree of trees of matching groups */
    char word[MAXWORD];

    int minlen;
    if (argc == 1) {
        minlen = 6;
    } else if (argc == 2 && atoi(argv[1]) != 0) {
        minlen = atoi(argv[1]);
    } else {
        printf("usage: %s [minlen]", argv[0]);
        return 1;
    }

    groups = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            groups = addouter(groups, word, minlen);
        }
    }
    printf("Strings shorter than %d or first %d characters different:\n",
            minlen, minlen);
    treeprinto(groups, 1);
    printf("\n\n");
    printf("Strings with first %d chars same and 1+ following different:\n",
            minlen);
    treeprinto(groups, 0);
    return 0;
}

struct inode *addinner(struct inode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = ialloc();
        p->word = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) > 0) {
        p->right = addinner(p->right, w);
    } else if (cond < 0) {
        p->left = addinner(p->left, w);
    }
    return p;
}

struct onode *addouter(struct onode *p, char *w, int minlen)
{
    int cond;

    if (p == NULL) {
        p = oalloc();
        p->inner = addinner(NULL, w);
        p->left = p->right = NULL;
    } else if (strbeg(p->inner->word, w, minlen)) {
        p->inner = addinner(p->inner, w);
    } else if ((cond = strcmp(w, p->inner->word)) > 0) {
        p->right = addouter(p->right, w, minlen);
    } else if (cond < 0) {
        p->left = addouter(p->left, w, minlen);
    }
    return p;
}

/* strbeg: test if len characters from beginning are same, and one or
           more following are different */
int strbeg(char *a, char *b, int len)
{
    if (strlen(a) <= len || strlen(b) <= len) {
        return 0;
    }
    while (len--) {
        if (*a++ != *b++) {
            return 0;
        }
    }
    return 1;
}
    

void treeprinti(struct inode *p)
{
    if (p != NULL) {
        treeprinti(p->left);
        printf("\t%s\n", p->word);
        treeprinti(p->right);
    }
}

void treeprinto(struct onode *p, int loners)
{
    if (p != NULL) {
        treeprinto(p->left, loners);
        if ((loners && p->inner->right == NULL && p->inner->left == NULL) ||
                (!loners && (p->inner->right != NULL ||
                             p->inner->left != NULL))) {
            treeprinti(p->inner);
        }
        treeprinto(p->right, loners);
    }
}

#include <stdlib.h>

struct inode *ialloc()
{
    return (struct inode *) malloc(sizeof(struct inode));
}
struct onode *oalloc()
{
    return (struct onode *) malloc(sizeof(struct onode));
}

char *strdup(char *s)   /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
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
