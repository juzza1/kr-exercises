#include <stdio.h>

int any(char source[], char target[]);

int main()
{
    char source[100];
    char target[100];
    int c;
    int i;

    for (i = 0; (c = getchar()) != '\n'; i++) {
        source[i] = c;
    }
    source[i] = '\0';
    for (i = 0; (c = getchar()) != '\n'; i++) {
        target[i] = c;
    }
    target[i] = '\0';

    printf("%d\n", any(source, target));

    return 0;
}

/* Return first position where any character from target exists in source */
int any(char source[], char target[])
{
    int i;
    int j;

    for (i = 0; source[i] != '\0'; i++) {
        for (j = 0; target[j] != '\0'; j++) {
            if (source[i] == target[j]) {
                return i;
            }
        }
    }
    return -1; /* No match */
}
