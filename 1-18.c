#include <stdio.h>
#define MAXLINE 1000
#define LIM 80

int getline(char lin[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
    int i;
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        i = len - 1;
        while (line[i] == ' ' || line[i] == '\n' || line[i] == '\t') {
            i--;
        }
        if (i > 0) {
            line[i+1] = '\n';
            line[i+2] = '\0';
            printf("%s", line);
        }
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
