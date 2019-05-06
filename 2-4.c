#include <stdio.h>
#define FALSE 0
#define TRUE 1

void squeeze(char dellist[], char string[]);

int main()
{
    char dellist[1000];
    char string[1000];
    int c;
    int i;

    printf("Enter target string:\n");
    for(i = 0; (c = getchar()) != '\n'; i++) {
        string[i] = c;
    }
    string[i] = '\0';
    printf("Enter dellist:\n");
    for(i = 0; (c = getchar()) != '\n'; i++) {
        dellist[i] = c;
    }
    dellist[i] = '\0';

    printf("String is: %s\n", string);
    printf("Will remove: %s\n", dellist);
    squeeze(dellist, string);
    printf("Result: %s\n", string);

    return 0;
}

/* Remove all characters in dellist from string */
void squeeze(char dellist[], char string[])
{
    int i;
    int j;
    int k;
    int nodel;

    for (i = j = 0; string[i] != '\0'; i++) {
        nodel = TRUE;
        for (k = 0; dellist[k] != '\0'; k++) {
            if (string[i] == dellist[k]) {
                nodel = FALSE;
            }
        }
        if (nodel) {
            string[j++] = string[i];
        }
    }
    string[j] = '\0';
}
