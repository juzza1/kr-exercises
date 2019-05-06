#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
    int y = 1988;
    int m = 10;
    int d = 14;
    int ed, em;

    printf("%d.%d was %dth day in the year %d\n",
           d, m, day_of_year(y, m, d), y);
    month_day(y, day_of_year(y, m, d), &em, &ed);
    printf("%dth day in the year %d was %d.%d\n",
           day_of_year(y, m, d), y, ed, em);

    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    char *dtp;
    int leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    dtp = daytab[leap];
    if (!(month >= 1 && month <= 12 && day >= 1 &&
            day <= *(dtp+month))) {
        return -1;
    }
    for (; dtp < daytab[leap] + month; dtp++) {
        day += *dtp;
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    char *dtp;
    int leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    dtp = daytab[leap];
    if (!(yearday >= 1 && yearday <= 365+leap)) {
        *pday = *pmonth = -1;
        return;
    }
    for (; yearday > *dtp; dtp++) {
        yearday -= *dtp;
    }
    *pmonth = dtp - daytab[leap];
    *pday = yearday;
}
