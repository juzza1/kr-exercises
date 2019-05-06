#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {          /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist *lookup(char *);
struct nlist *install(char *name, char *defn);
char *strdup(char *);
void undef(char *name);

int main(int argc, char *argv[])
{
    char *a[] = {"kuu", "1"};
    char *b[] = {"nn", "5"};
    char *c[] = {"hh", "10"};
    install(a[0], a[1]);
    install(b[0], b[1]);
    install(c[0], c[1]);

    struct nlist *krw;
    krw = lookup("kuu");
    if (krw != NULL) {
        printf("%s: %s\n", krw->name, krw->defn);
    }
    undef("kuu");
    krw = lookup("kuu");
    if (krw != NULL) {
        printf("%s: %s\n", krw->name, krw->defn);
    }
    return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;  /* found */
        }
    }
    return NULL;        /* not found */
}

void undef(char *name)
{
    struct nlist *np, *prev;
    unsigned hashv;

    hashv = hash(name);
    np = hashtab[hashv];
    if (strcmp(np->name, name) == 0) {  /* It's the first in chain */
        hashtab[hashv] = np->next;
    } else {
        while (np->next != NULL) {
            prev = np;
            np = np->next;
            if (strcmp(np->name, name) == 0) {
                prev->next = np->next;
                return;
            }
        }
    }
}
    

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {    /* already there */
        free((void *) np->defn);    /*free previous defn */
    }
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

/* strdup: make a duplicate of s */
char *strdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}
