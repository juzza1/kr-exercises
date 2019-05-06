#include <stdio.h>
#define MAXIN 10000
#define NOCOM 0
#define COM 1

int main()
{
    int bra;
    int curl;
    int par;
    int charbuf[MAXIN];
    int c;
    int i;
    int state;

    bra = curl = par = state = 0;
    while ((c = getchar()) != EOF) {
        if (state == 0) {
            if (c == '/') {
                state = 1; /* Try-if comment state */
            } else if (c == '"') {
                state = 5; /* Comment state */
            } else if (c == '\'') {
                state = 7; /* Single quote state */
            }
        } else if (state == 1) {
            if (c == '*') {
                state = 2; /* comment state */
            } else {
                putchar('/');
                if (c != '/') {
                    state = 0;
                }
            }
        } else if (state == 2) {
            if (c == '*') {
                state = 3;
            }
        } else if (state == 3) {
            if (c == '/') {
                state = -1;
            } else if (c != '*') {
                state = 2;
            }
        } else if (state == 5) {
            if (c == '\\') { /* Escape state inside quote */
                state = 6;
            } else if (c == '"') {
                state = 0;
            }
        } else if (state == 6) {
            if (c != '\\') {
                state = 5;
            }
        } else if (state == 7) {
            state = 8;
        } else if (state == 8) {
            if (c == '\'') {
                state = 0;
            } else {
                printf("Error! Single quote not closed.\n");
            }
        } else if (state == -1) {
            state = 0;
        } else {
            state = 0;
        }

        if (state == 0 || state == 5 || state == 6) {
            putchar(c);
        }
        if (state == 0) {
            if (c == '[') {
                bra++;
            } else if (c == ']') {
                bra--;
            } else if (c == '{') {
                curl++;
            } else if (c == '}') {
                curl--;
            } else if (c == '(') {
                par++;
            } else if (c == ')') {
                par--;
            }
        }
    }
    if (bra != 0 || curl != 0 || par != 0) {
        printf("Error! Bad format.\n");
    }

    return 0;
}
