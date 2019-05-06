#include <stdio.h>
#include <string.h>

void rreverse(char s[], int left, int right);

int main()
{
    char s[] = "abcde";

    printf("%s reversed: ", s);
    rreverse(s, 0, strlen(s)-1);
    printf("%s\n", s);

    return 0;
}

/* rreverse: reverse string in place, recursive version */
void rreverse(char s[], int left, int right)
{
    int temp;

    if (left < right) {
        rreverse(s, left+1, right-1);
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
    }
}
