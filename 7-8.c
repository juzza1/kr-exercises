#include <stdio.h>
#include <stdlib.h>

/* Files as pages with page number and filename */
int main(int argc, char *argv[])
{
    FILE *fp;
    int c, pages;
    int pc = 0;

    if (argc == 1) {
        printf("Usage: %s file [file,...]\n", argv[0]);
        return 1;
    }
    argv++;
    pages = argc - 1;
    while (--argc) {
        if ((fp = fopen(*argv, "r")) != NULL) {
            pc++;
            printf("%d/%d: %s\n", pc, pages, *argv);
            while ((c = getc(fp)) != EOF) {
                putchar(c);
            }
            if (argc > 1) {
                printf("\n\n");
            }
            argv++;
        } else {
            fprintf(stderr, "Could not open %s\n", *argv);
        }
    }
}
