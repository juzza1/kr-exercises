#include <stdio.h>
#define MAXLINE 1000
#define LIM 80
#define FALSE 0
#define TRUE 1

int getline(char lin[], int maxline);
void copy(char to[], char from[]);
void reverse(char to[], char from[]);

/* print longest input line */
int main()
{
    int len;
    char line[MAXLINE];
    char reversed[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        reverse(reversed, line);
        printf("%s", reversed);
    }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

void reverse(char to[], char from[])
{
    /* Reverse string: keep existing end-of-line newline */
    int i;
    int j;
    int nl;

    /* Get string end */
    for (i = 0; from[i] != '\0'; i++) {
        ;
    }
    i--;

    if (from[i] == '\n') {
        nl = TRUE;
        i--;
    } else {
        nl = FALSE;
    }

    j = 0;
    while (i >= 0) {
        to[j] = from[i];
        i--;
        j++;
    }
    if (nl == TRUE) {
        to[j] = '\n';
        j++;
    }
    to[j] = '\0';
}
