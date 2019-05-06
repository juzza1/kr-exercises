#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int base);
void reverse(char s[]);

int main()
{
    char s[100];
    int num;

    num = 17;

    itob(num, s, 16);
    printf("Numeric rep: %d, string rep: %s\n", num, s);

    return 0;
}

void itob(int n, char s[], int base)
{
    int i, num, sign;

    sign = n < 0 ? -1 : 1;
    i = 0;
    do {    /* Generate digits in reverse order */
        num = (n % base) < 0 ? (n % base) * -1 : n % base;
        if (num <= 9) {
            s[i++] = num + '0';
        } else {
            s[i++] = (num-10) + 'a';
        }
    } while ((n /= base) != 0);    /* Delete it */
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
