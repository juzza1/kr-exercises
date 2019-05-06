#include <stdio.h>

int main()
{
    /* Print histogram of letter frequencies */
    int c;
    int i;
    int j;
    int charn[256]; /* Amount of ascii characters */
    for (i = 0; i < 256; i++) {
        charn[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        charn[c]++;
    }
    for (i = 0; i < 256; i++) {
        if (charn[i] > 0) {
            printf("%c: ", i);
            for (j = 0; j < charn[i]; j++) {
                putchar('#');
            }
            putchar('\n');
        }
    }
    return 0;
}
