#include <stdio.h>

int strend(char *s, char *t);

int main()
{
    char a[] = "abcdefghijlkmnopqrstuvwxyz";
    char b[] = "xy";

    printf("a: %s, b: %s\n", a, b);
    printf("%d\n", strend(a, b));

    return 0;
}

int strend(char *s, char *t)
{
    char *so = s;
    char *to = t;
    /* Get end of s and t */
    while (*s != '\0') {
        s++;
    }
    while (*t != '\0') {
        t++;
    }
    /* Compare from end */
    for (; (*s == *t) && s >= so && t >= to; s--, t--) {
        if (t == to) {
            return 1;
        }
    }
    return 0;
}
