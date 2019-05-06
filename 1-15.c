#include <stdio.h>
#define CELCIUS 0
#define FAHR 1

/* Print Fahrenheit-Celcius table
   for fahr = 0, 20, ..., 300; floating-point version */

int conv(int val, int type);

int main()
{
    float fahr, celcius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celcius = lower;
    printf("C\tF\n");
    while (celcius <= upper) {
        fahr = conv(celcius, FAHR);
        printf("%3.0f\t%6.1f\n", celcius, fahr);
        celcius = celcius + step;
    }
}

/* Conv - convert between temperature units */
int conv(int val, int type)
{
    if (type == CELCIUS) {
        return (5.0/9.0) * (val - 32.0);
    } else if (type == FAHR) {
        return (9.0/5.0) * val + 32.0;
    }
    return 0;
}
