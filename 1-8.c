#include <stdio.h>

int main()
{
    int c, blank_cnt, newline_cnt, tab_cnt;

    blank_cnt = newline_cnt = tab_cnt = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blank_cnt++;
        } else if (c == '\n') {
            newline_cnt++;
        } else if (c == '\t') {
            tab_cnt++;
        }
    }
    printf("Got %d blanks, %d newlines and %d tabs.\n",
           blank_cnt, newline_cnt, tab_cnt);
}
