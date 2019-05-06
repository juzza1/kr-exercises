#include <stdio.h>
#define DECODE 0
#define ENCODE 1

void escape(char source[], char target[], int mode);

int main()
{
    char source[100];
    char target[100];
    int c, i;

    for (i = 0; (c = getchar()) != EOF; i++) {
        source[i] = c;
    }
    source[i] = '\0';

    escape(source, target, DECODE);
    printf("Source string:\n");
    printf("%s", source);
    printf("Escaped target string:\n");
    printf("%s", target);
    return 0;
}

void escape(char source[], char target[], int mode)
{
    /* Copy source to target, converting special characters into visible
       escape sequences or vice versa. */

    int i, j;
    i = j = 0;
    while (source[i] != '\0') {
        if (mode == DECODE) {
            switch (source[i]) {
                case '\n':
                    target[j] = '\\';
                    target[++j] = 'n';
                    break;
                case '\t':
                    target[j] = '\\';
                    target[++j] = 't';
                    break;
                default:
                    target[j] = source[i];
                    break;
            }
        } else if (mode == ENCODE) {
            switch (source[i]) {
                case '\\':
                    switch(source[i+1]) { 
                        case 'n':
                            target[j] = '\n';
                            i++;
                            break;
                        case 't':
                            target[j] = '\t';
                            i++;
                            break;
                        default:
                            target[j] = '\\';
                            break;
                    }
                    break;
                default:
                    target[j] = source[i];
                    break;
            }
        }
        i++;
        j++;
    }
    target[j] = '\0';
}
