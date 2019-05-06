#include <limits.h>
#include <stdio.h>

int main()
{
    printf("Printing limits from limits.h:\n");
    printf("%-8s%-8s%-32s%-s\n", "Type", "Sign", "Min", "Max");
    printf("%-8s%-8s%-32hd%-hu\n", "Char", "u", 0, UCHAR_MAX);
    printf("%-8s%-8s%-32hd%-hd\n", "Char", "s", SCHAR_MIN, SCHAR_MAX);
    printf("%-8s%-8s%-32hd%-hu\n", "Short", "u", 0, USHRT_MAX);
    printf("%-8s%-8s%-32hd%-hd\n", "Short", "s", SHRT_MIN, SHRT_MAX);
    printf("%-8s%-8s%-32d%-u\n", "Int", "u", 0, UINT_MAX);
    printf("%-8s%-8s%-32d%-d\n", "Int", "s", INT_MIN, INT_MAX);
    printf("%-8s%-8s%-32ld%-lu\n", "Long", "u", 0, ULONG_MAX);
    printf("%-8s%-8s%-32ld%-ld\n", "Long", "s", LONG_MIN, LONG_MAX);
    printf("\n");

    unsigned char uc;
    char sc;
    unsigned short us;
    short ss;
    unsigned int ui;
    int si;
    unsigned long ul;
    long sl;
    uc = sc = us = ss = ui = si = ul = sl = 0;

    printf("Printing computed limits:\n");
    printf("%-8s%-8s%-32s%-s\n", "Type", "Sign", "Min", "Max");

    uc--;
    printf("%-8s%-8s%-32hd%-hu\n", "Char", "u", 0, uc);
    sc = uc/2;
    printf("%-8s%-8s%-32hd%-hd\n", "Char", "s", (signed char) (sc+1), sc);

    us--;
    printf("%-8s%-8s%-32hd%-hu\n", "Short", "u", 0, us);
    ss = us/2;
    printf("%-8s%-8s%-32hd%-hd\n", "Short", "s", (signed short) (ss+1), ss);

    ui--;
    printf("%-8s%-8s%-32d%-u\n", "Int", "u", 0, ui);
    si = ui/2;
    printf("%-8s%-8s%-32d%-d\n", "Int", "s", (signed int) (si+1), si);

    ul--;
    printf("%-8s%-8s%-32ld%-lu\n", "Long", "u", 0, ul);
    sl = ul/2;
    printf("%-8s%-8s%-32ld%-ld\n", "Long", "s", (signed long) (sl+1), sl);
    
    return 0;
}
