#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// maps 0~N-1 to the position of
int map[10005]; // 40020
int tmp[10005]; // 40020

char str[10005];

int Q;


int main()
{
    // Read input and init arrays
    scanf("%s", str);
    int str_len = strlen(str);

    for (int i = 0; i < str_len; i++) {
        map[i] = i;
    }

    scanf("%d", &Q);

    // deal with Q queries
    while (Q--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);

        // NOTE: l and r are 1-based
        // fix them
        l = l - 1;
        r = r - 1;

        // SOLVE:
        for (int idx = l; idx <= r; idx++) {
            // update
            int target_idx = l + (idx - l + k) % (r - l + 1);
            tmp[target_idx] = map[idx];
        }
        for (int idx = l; idx <= r; idx++) {
            // update
            map[idx] = tmp[idx];
        }
    }

    for (int i = 0; i < str_len; i++) {
        printf("%c", str[map[i]]);
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

