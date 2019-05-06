#include <stdio.h>
#define MAXIN 10000
#define NOCOM 0
#define COM 1

int main()
{
    int charbuf[MAXIN];
    int c;
    int i;
    int state;

    state = 0;
    while ((c = getchar()) != EOF) {
        if (state == 0) {
            if (c == '/') {
                state = 1;
            } else if (c == '"') {
                state = 5;
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
            if (c == '\\') {
                state = 6;
            } else if (c == '"') {
                state = 0;
            }
        } else if (state == 6) {
            if (c != '\\') {
                state = 5;
            }
        } else if (state == -1) {
            state = 0;
        } else {
            state = 0;
        }

        if (state == 0 || state == 5 || state == 6) {
            putchar(c);
        }
    }

    return 0;
}
