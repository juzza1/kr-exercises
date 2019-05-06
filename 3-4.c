#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    char s[100];
    int num;

    num = -500;

    itoa(num, s);
    printf("Numeric rep: %d, string rep: %s\n", num, s);

    return 0;
}

void itoa(int n, char s[])
{
    int i, num, sign;

    sign = n < 0 ? -1 : 1;
    i = 0;
    do {    /* Generate digits in reverse order */
        num = (n % 10) < 0 ? (n % 10) * -1 : n % 10;
        s[i++] = num + '0';  /* Get next digit */
    } while ((n /= 10) != 0);    /* Delete it */
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
