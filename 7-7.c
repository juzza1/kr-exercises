#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "getline.c"

#define MAXLINE 1000

int patfind(FILE *fp, int maxline, char *pat, int except, int number);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    FILE *fp;
    char pat[100];
    long lineno = 0;
    int c, files, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch(c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }
    if (argc == 0) {
        printf("Usage: find -x -n pattern [file1,[file2,...]]\n");
    } else {
        if (argc == 1) {
            fp = stdin;
            found = patfind(fp, MAXLINE, *argv, except, number);
        } else {
            found = 0;
            strcpy(pat, *argv++);
            while (argc-- > 1) {
                fp = fopen(*argv++, "r");
                found += patfind(fp, MAXLINE, pat, except, number);
            }
        }
    }
    return found;
}

int patfind(FILE *fp, int maxline, char *pat, int except, int number)
{
    char line[MAXLINE];
    int found, lineno = 0;

    while (fgets(line, maxline, fp) > 0) {
        lineno++;
        if ((strstr(line, pat) != NULL) != except) {
            if (number) {
                printf("%ld:", lineno);
            }
            printf("%s", line);
            found++;
        }
    }
    return found;
}
