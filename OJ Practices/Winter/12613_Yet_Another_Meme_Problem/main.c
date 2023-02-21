#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        long long A, B;
        scanf("%lld %lld", &A, &B);

        long long n = (long long)log10(B);
        printf("%lld\n", A * n);
    }

    return 0;
}

/**


b = 10^n - 1

n = 2, b has 2 choices: 9 and 99

answer = A * n

*/
