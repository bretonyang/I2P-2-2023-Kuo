#include <stdio.h>
#include <stdlib.h>


int is_leap(int year) {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}


int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        int year;
        scanf("%d", &year);
        int day = 0;
        int orig_year_is_leap = is_leap(year);

        while (1) {
            if (is_leap(year)) {
                day = (day + 2) % 7;
            }
            else {
                day = (day + 1) % 7;
            }

            year++;
            if (day == 0) {
                if (orig_year_is_leap && !is_leap(year)) {
                    continue;
                }
                else if (!orig_year_is_leap && is_leap(year)) {
                    continue;
                }
                else {
                    break;
                }
            }
        }
        printf("%d\n", year);
    }

    return 0;
}


/**

Consider the weekday of 1/1.
If next year we encounter:

 1. normal year
    -> 365 days
    -> year starts with (weekday + 1) % 7

 2. leap year
    -> 366 days
    -> year starts with (weekday + 2) % 7


 a. if original year is leap year
    -> result year has to be leap year too

 b. if original is not leap and current is leap
    -> continue



*/
