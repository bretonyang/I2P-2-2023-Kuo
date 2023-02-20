#include <stdio.h>
#include <stdlib.h>


int is_leap(int year) {
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        return 1;
    }
    return 0;
}


int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        int year;
        scanf("%d", &year);

        int first_day = 0;
        int orig_is_leap = is_leap(year);
        while (1) {
            year++;

            if (is_leap(year)) {
                first_day = (first_day + 366) % 7;
            }
            else {
                first_day = (first_day + 365) % 7;
            }

            // either both are leap year or both are regular year
            if (first_day == 0 && !(orig_is_leap ^ is_leap(year))) {
                break;
            }
        }

        printf("%d\n", year);
    }

    return 0;
}
