#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define MAXLINES 100

int main(char argc, char *argv[])
{
    FILE *f1, *f2;
    char line1[MAXLINE], line2[MAXLINE];
    if (argc != 3) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 1;
    }
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    if (f1 == NULL || f2 == NULL) {
        fprintf(stderr, "Could not open %s\n", f1 == NULL ? argv[1] : argv[2]);
        return 2;
    }
    while (fgets(line1, MAXLINES, f1) && fgets(line2, MAXLINES, f2)) {
        if (strcmp(line1, line2) != 0) {
            printf("%s%s", line1, line2);
            break;
        }
    }
    return 0;
}
