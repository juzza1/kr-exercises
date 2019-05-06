#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "getch.c"

int minscanf(char *fmt, ...);

int main()
{
    char s[100];
    printf("%d\n", minscanf("%d", &s));
    return 0;
}

/* minprintf: minimal printf with variable argument list */
int minscanf(char *fmt, ...)
{
    va_list ap; /*points to each unnamed arg in turn */
    int found = 0;
    int i;
    char c;
    char *cval, *p;
    int *ival;
    char cbuf[100];

    va_start(ap, fmt);  /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        while (isspace(*p)) {               /* Ignore whitespace in format */
            *p++;
        }
        while (isspace(c = getch())) {    /* Ignore whitespace in input */
            ;
        }
        if (c == EOF) { /* EOF and format string not exhausted */
            return EOF;
        }
        if (*p != '%') {    /* literal */
            if (c == *p) {
                cval = va_arg(ap, char *);
                *cval = c;
                found++;
                continue;
            }
            return found;   /* failure, end */
        }
        switch (*++p) {
        case 'd': case 'i':
            for (i = 0; isdigit(c); i++) {
                cbuf[i] = c;
                c = getch();
            }
            ungetch(c);
            cbuf[i] = '\0';
            if (strlen(cbuf) == 0) {  /* couldn't match */
                return found;
            }
            ival = va_arg(ap, int *);
            *ival = atoi(cbuf);
            found++;
            break;
        case 's':
            for (i = 0; !isspace(c); i++) {
                cbuf[i] = c;
                c = getch();
            }
            ungetch(c);
            cbuf[i] = '\0';
            if (strlen(cbuf) == 0) {  /* couldn't match */
                return found;
            }
            cval = va_arg(ap, char *);
            strcpy(cval, cbuf);
            found++;
            break;
        }
    }
    va_end(ap); /* clean up when done */
    return found;
}
