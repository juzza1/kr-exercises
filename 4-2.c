#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 100

double atof(char s[]);
int getline(char line[], int max);

int main()
{
    double sum, atof(char []);
    char line[MAXLINE];
    int getline(char line[], int max);

    sum = 0;
    while (getline(line, MAXLINE) > 0) {
        printf("\t%g\n", sum += atof(line));
    }

    return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double e, val, power;
    int esign, i, sign;

    for (i = 0; isspace(s[i]); i++) { /* Skip whitespace */
        ;
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
    }
    esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') {
        i++;
    }
    for (e = 0.0; isdigit(s[i]); i++) {
        e = 10.0 * e + (s[i] - '0');
    }
    e = esign == -1 ? 1/pow(10.0, e) : pow(10.0, e);
    return sign * val / power * e;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}
