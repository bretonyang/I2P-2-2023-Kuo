#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long int lld;

int main()
{
    int T;
    lld A, B;

    scanf("%d", &T);
    while (T--) {
        scanf("%lld %lld", &A, &B);
        lld count = A * (lld)(log10(B));

        printf("%lld\n", count);
    }

    return 0;
}
