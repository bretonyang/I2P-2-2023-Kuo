#include <stdio.h>
#include <stdlib.h>


int K;
long long L, R;
long long lengths[52]; /// NOTE: lengths might be too large!!!!
long long cur_len = 0;


void print_pattern(int level) {
    if (level == 0) {
        return;
    }
    else if (cur_len + lengths[level] < L) {
        cur_len += lengths[level];
        return;
    }

    if (cur_len >= L && cur_len <= R) printf("O");
    cur_len++;

    if (cur_len <= R) print_pattern(level - 1);

    if (cur_len >= L && cur_len <= R) printf("u");
    cur_len++;

    if (cur_len <= R) print_pattern(level - 1);

    if (cur_len >= L && cur_len <= R) printf("Q");
    cur_len++;
}


void calc(int maxK) {
    lengths[1] = 3;
    for (int i = 2; i <= maxK; i++) {
        lengths[i] = 3 + 2 * lengths[i - 1];
    }
}


int main()
{
    calc(51);
    while (scanf("%d %lld %lld", &K, &L, &R) != EOF) {
        cur_len = 0;
        print_pattern(K);
        printf("\n");
    }

    return 0;
}
