#include <stdio.h>

void krstrncpy(char *s, char *t, int n);
void krstrncat(char *s, char *t, int n);
int krstrncmp(char *s, char *t, int n);

int main()
{
    char a[] = "abcdef";
    char b[] = "defghi";
    char c[10];

    krstrncpy(c, a, 2);
    printf("%s\n", c);
    krstrncat(c, b, 3);
    printf("%s\n", c);
    printf("%d\n", krstrncmp(c, a, 2));

    return 0;
}

void krstrncpy(char *s, char *t, int n)
{
    for (; n > 0; n--) {
        *s++ = *t++;
    }
    *s = '\0';
}

void krstrncat(char *s, char *t, int n)
{
    /* Get end of s */
    while (*s) {
        s++;
    }
    for (; n > 0; n--) {
        *s++ = *t++;
    }
    *s = '\0';
}

int krstrncmp(char *s, char *t, int n)
{
    for (; n > 0; n--) {
        if (*s != *t) {
            return *s - *t;
        }
        s++;
        t++;
    }
    return 0;
}
