#include <stdio.h>

void pstrcat(char *s, char *t);

int main()
{
    char a[10] = "abc";
    char b[] = "ijk";

    printf("a: %s, b: %s\n", a, b);
    pstrcat(a, b);
    printf("%s\n", a);

    return 0;
}

void pstrcat(char *s, char *t)
{
    while (*s != '\0') {
        s++;
    }
    while (*s++ = *t++) {
        ;
    }
}
