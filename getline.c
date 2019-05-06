#include <stdio.h>

int getline(char *s);
int getline(char *s)
{   
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return c;
}
