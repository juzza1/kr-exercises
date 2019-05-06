#include <stdio.h>
#define MAXWORD 100
#define FALSE 0
#define TRUE 1

int main()
{
    /* Print histogram of word lengths */
    int c;
    int i;
    int j;
    int left;
    int lens[MAXWORD];
    int lensc[MAXWORD];

    for (i = 0; i < MAXWORD; i++) {
        lens[i] = 0;
    }

    i = 0;
    while ((c = getchar()) != EOF) {
        if (i >= 0 && (c == ' ' || c == '\n' || c == '\t')) {
            lens[i]++;
            i = 0;
        } else if (i < MAXWORD) {
            i++;
        }
    }
    /* Print lengths horizontally */
    for (i = 0; i < MAXWORD; i++) {
        if (lens[i] != 0) {
            printf("%d: ", i);
            for (j = 0; j < lens[i]; j++) {
                putchar('#');
            }
            putchar('\n');
        }
    }
    /* Print lengths vertically */
    /* Header */
    for (i = 0; i < MAXWORD; i++) {
        if (lens[i] != 0) {
            printf(" %d ", i);
        }
    }
    putchar('\n');
    /* Numbers */
    /* Copy lens */
    for (i = 0; i < MAXWORD; i++) {
        lensc[i] = lens[i];
    }
    left = TRUE;
    while (left != 0) {
        for (i = 0; i < MAXWORD; i++) {
            if (lens[i] != 0) {
                if (lensc[i] > 0) {
                    printf(" # ");
                    lensc[i]--;
                } else {
                    printf("   ");
                }
            }
        }
        putchar('\n');
        left = FALSE;
        /* Check if more numbers left */
        for (i = 0; i < MAXWORD; i++) {
            if (lensc[i] > 0) {
                left = TRUE;
            }
        }
    }
    return 0;
}
