#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    int max_house = -1;
    int min_house = 1 + (int)1e9;
    int cur_house;

    for (int i = 0; i <= N; i++) {
        scanf("%d", &cur_house);

        max_house = (cur_house > max_house) ? cur_house : max_house;
        min_house = (cur_house < min_house) ? cur_house : min_house;
    }

    printf("%d\n", 2 * (max_house - min_house));

    return 0;
}

/**

1. not sorted

2. 1 <= N <= 2*10^5

3. 0 <= x_i <= 10^9


0 1 2 3 4 5 6

    @

6*2 = 12

idea: will need to walk through the path twice.
(path: the line segment between min_house and max_house)


*/
