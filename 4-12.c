#include <stdio.h>

int intlen(int n);
void ritoa(int n, char s[], int len);

int main()
{
    char s[100];
    int num = -222;

    ritoa(num, s, intlen(num)-1);
    printf("%d converted to string: %s\n", num, s);

    return 0;
}

int intlen(int n)
{
    int i;

    i = n >= 0 ? 1 : 2;
    n = n >= 0 ? n : -n;
    for (; (n /= 10) > 0; i++) {
        ;
    }
    return i;
}

/* ritoa: int to string, recursive version */
void ritoa(int n, char s[], int len)
{
    if (n < 0) {
        s[0] = '-';
        n = -n;
    }
    if (n > 9) {
        ritoa(n / 10, s, len-1);
    }
    s[len] = (n % 10 + '0');
    s[len+1] = '\0';
}
