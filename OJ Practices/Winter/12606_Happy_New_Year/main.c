#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    int min = 5 + (int)1e9;
    int max = -1;

    scanf("%d", &N);

    for (int i = 0; i <= N; i++) {
        int x;
        scanf("%d", &x);

        min = (x < min) ? x : min;
        max = (x > max) ? x : max;
    }

    printf("%d\n", 2 * (max - min));

    return 0;
}
