#include <stdio.h>

int main()
{
    /* Confirm (getchar() != EOF) is either 0 or 1 */
    int c;
    int val;

    while (val = ((c = getchar()) != EOF)) {
        printf("Got %c, Value of c = getchar() != EOF is now %d\n", c, val);
    }
    printf("Got %c, Value of c = getchar() != EOF is now %d\n", c, val);
}
