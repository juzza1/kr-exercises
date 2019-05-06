#include <math.h>
#include <stdio.h>
#define MAXBUF 50

int htoi(char string[]);

int main()
{
    char charbuf[MAXBUF];
    int c;
    int i;

    i = 0;
    while ((c = getchar()) != '\n') {
        charbuf[i++] = c;
    }
    charbuf[i] = '\0';
    printf("%s converted to decimal: %d\n", charbuf, htoi(charbuf));

    return 0;
}

int htoi(char string[])
{
    int i;
    int first;
    int last;
    int exp;
    int val;

    first = last = 0;
    /* Return hexadecimal string converted to integer */
    if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X')) {
        first = 2;
    } else {
        first = 0;
    }

    for (i = 0; string[i] != '\0'; i++) {
        ;
    }
    last = i - 1;

    exp = val = 0;
    for (i = last; i >= first; i--) {
        if (string[i] >= '0' && string[i] <= '9') {
            val += (string[i] - '0') * pow(10, exp);
        } else if (string[i] >= 'a' && string[i] <= 'f') {
            val += (string[i] - 'a' + 10) * pow(10, exp);
        } else if (string[i] >= 'A' && string[i] <= 'F') {
            val += (string[i] - 'A' + 10) * pow(10, exp);
        } else {
            printf("Invalid character: %c\n", string[i]);
            return 0;
        }
        exp++;
    }

    return val;
}
