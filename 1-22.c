#include <stdio.h>
#define FALSE 0
#define TRUE 1
#define BUFEND -1
#define MAXBUF 1000
#define MAXLINE 10

char charbuf[MAXBUF];

void addbuf(int c, int bufpos);
int setbuff(int start);
void printbuf(int start, int end);

int main()
{
    extern char charbuf[];
    int blank;
    int bufpos;
    int c;
    int linepos;
    int ws_start;
    int ws_end;
    int tablen;
    tablen = 8;

    charbuf[0] = '\0';

    blank = FALSE;
    bufpos = linepos = ws_start = ws_end = 0;
    while ((c = getchar()) != EOF) {

        /* Keep track of blank positions */
        if (c == ' ' || c == '\t') {
            if (blank == FALSE) {
                ws_start = bufpos;
                blank = TRUE;
            }
        } else if (blank == TRUE) {
            ws_end = bufpos;
            blank = FALSE;
        }

        /* Limit reached, print current buffer */
        if (linepos >= MAXLINE && blank == FALSE) {
            if (ws_start > 0) { /* There was blank */
                printbuf(0, ws_start-1);
                putchar('\n');
                bufpos = linepos = setbuff(ws_end);
            } else {            /* No blank */
                printbuf(0, BUFEND);
                putchar('\n');
                bufpos = linepos = 0;
            }
            ws_start = ws_end = 0;
        }

        addbuf(c, bufpos);
        if (c == '\n') {
            printbuf(0, BUFEND);
            bufpos = linepos = 0;
        } else {
            if (c == '\t') {
                linepos += tablen - (linepos % tablen);
            } else {
                linepos++;
            }
            bufpos++;
        }

    }

    return 0;
}

void addbuf(int c, int bufpos)
{
    /* Add character to buffer, make it the last character */

    extern char charbuf[];
    charbuf[bufpos] = c;
    charbuf[bufpos+1] = '\0';
}

int setbuff(int start)
{
    /* Delete items from the left until start is at index 0.

       Return last index. */

    extern char charbuf[];
    char temp[MAXBUF];
    int i;
    int j;

    i = 0;
    j = start;
    while (charbuf[j] != '\0') {
        temp[i] = charbuf[j];
        i++;
        j++;
    }
    temp[i] = '\0';
    i = 0;
    /* Copy temp to original */
    while ((charbuf[i] = temp[i]) != '\0') {
        i++;
    }
    return i;
}

void printbuf(int start, int end)
{
    /* Print buffer from start to end. */

    extern char charbuf[];
    int i;

    if (end == BUFEND) {
        for (i = start; charbuf[i] != '\0'; i++) {
            putchar(charbuf[i]);
        }
    } else {
        for (i = start; i <= end; i++) {
            putchar(charbuf[i]);
        }
    }
}
