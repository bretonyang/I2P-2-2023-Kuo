#include <stdio.h>
#include <stdlib.h>


long long counter = 0;
long long arr_of_lengths[55];
long long K, L, R;


void print_pattern(level) {
    if (level == 0 || counter > R) {
        return;
    }
    else if (counter + arr_of_lengths[level] < L) {
        counter += arr_of_lengths[level];
        return;
    }

    if (counter >= L && counter <= R) {
        printf("O");
    }
    counter++;

    print_pattern(level - 1);

    if (counter >= L && counter <= R) {
        printf("u");
    }
    counter++;

    print_pattern(level - 1);

    if (counter >= L && counter <= R) {
        printf("Q");
    }
    counter++;

    return;
}


void compute_length(int k) {
    arr_of_lengths[1] = 3;
    for (int i = 2; i <= k; i++) {
        arr_of_lengths[i] = 3 + 2 * arr_of_lengths[i - 1];
    }
}


int main() {

    compute_length(50);

    while (scanf("%lld%lld%lld", &K, &L, &R) != EOF) {
        counter = 0;
        print_pattern(K);
        printf("\n");
//        printf("counter: %d\n", counter);
    }

    return 0;
}
