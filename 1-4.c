#include <stdio.h>

/* Print Fahrenheit-Celcius table
   for fahr = 0, 20, ..., 300; floating-point version */

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
        fahr = (9.0/5.0) * celcius + 32.0;
        printf("%3.0f\t%6.1f\n", celcius, fahr);
        celcius = celcius + step;
    }
}
