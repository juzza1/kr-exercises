#include <stdio.h>
#define NONE 0
#define FALSE 0
#define TRUE 1

void expand(char source[], char target[]);

int main()
{
    char string[100];
    char target[200];
    int c, i;
        
    for (i = 0; (c = getchar()) != EOF; i++) {
        string[i] = c;
    }
    string[i] = '\0';
    printf("Original string:\n");
    printf("%s", string);
    expand(string, target);
    printf("Expanded string:\n");
    printf("%s", target);
    return 0;
}

void expand(char source[], char target[])
{
    int i, j, longexp, tempc;

    i = j = 0;
    longexp = FALSE;
    while (source[i] != '\0') {
        if (isalphanum(source[i]) && source[i+1] == '-' &&
                isalphanum(source[i+2])) {  /* Correct expansion format */
            if (source[i] <= source[i+2]) { /* Ascending */
                if (longexp) {
                    tempc = source[i]+1;
                } else {
                    tempc = source[i];
                }
                for (; tempc <= source[i+2]; tempc++, j++) {
                    target[j] = tempc;
                }
            } else {                        /* Descending */
                if (longexp) {
                    tempc = source[i]-1;
                } else {
                    tempc = source[i];
                }
                for (; tempc >= source[i+2]; tempc--, j++) {
                    target[j] = tempc;
                }
            } /* Check whether format is a-b-c or a-b */
            if (source[i+3] == '-' && isalphanum(source[i+4])) {
                i += 2;
                longexp = TRUE;
            } else {
                i += 3;
                longexp = FALSE;
            }
        } else { /* Literal */
            target[j] = source[i];
            i++;
            j++;
        }
    }
    target[j] = '\0';
}

int isalphanum(int c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z')) {
        return TRUE;
    } else {
        return FALSE;
    }
}
