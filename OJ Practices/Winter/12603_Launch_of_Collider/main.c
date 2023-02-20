#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    char directions[200005];
    int positions[200005];
    for (int i = 0; i < N; i++) {
        scanf(" %c", directions + i);
    }
    for (int i = 0; i < N; i++) {
        scanf(" %d", positions + i);
    }

    int min_time = (int)1e9;
    int cur_R_position = -1;

    for (int i = 0; i < N; i++) {
        if (directions[i] == 'R') {
            // 'R' particle
            cur_R_position = positions[i];
        }
        else if (cur_R_position != -1) {
            // 'L' particle
            int new_time = (positions[i] - cur_R_position) / 2;
            min_time = (new_time < min_time) ? new_time : min_time;
        }
    }

    printf("%d\n", (min_time == (int)1e9) ? -1 : min_time);

    return 0;
}
