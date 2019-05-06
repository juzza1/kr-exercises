#include <stdio.h>
#include <ctype.h>

int main(int argc, int *argv[])
{
    char usage[] = "usage: 7-1-<lower|upper>\n";
    int c;
    if (argc == 1) {
        if (strcmp(argv[0], "7-1-lower") == 0) {
            printf("success\n");
        } else {
            printf("%s\n", argv[0]);
            printf(usage);
            return 1;
        }
    } else {
        printf(usage);
        return 1;
    }

    while ((c = getchar()) != EOF) {
        putchar(tolower(c));
    }
    return 0;
}
