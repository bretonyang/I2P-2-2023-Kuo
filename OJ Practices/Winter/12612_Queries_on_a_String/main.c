#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char str[10005];
int indices[10005];
int tmp[10005];


int main()
{
    scanf("%s", str);

    int str_len = strlen(str);
    for (int i = 0; i < str_len; i++) {
        indices[i] = i;
    }

    int M;
    scanf("%d", &M);

    // Doing queries
    while (M--) {
        int K, L, R;
        scanf("%d%d%d", &L, &R, &K);

        // fix 1-based to 0-based
        L--;
        R--;

        // store shifted result in tmp array
        for (int idx = L; idx <= R; idx++) {
            int target_idx = L + (idx - L + K) % (R - L + 1);
            tmp[target_idx] = indices[idx];
        }

        // store tmp result to real indices array
        for (int idx = L; idx <= R; idx++) {
            indices[idx] = tmp[idx];
        }
    }

    for (int i = 0; i < str_len; i++) {
        printf("%c", str[indices[i]]);
    }
    printf("\n");

    return 0;
}


/**

a   b   a   c   a   b   a
0   1   2   3   4   5   6

        5   2   3   4
5   2   0   1

b   a   a   b   c   a   a


*/
