#include <stdio.h>
#include <stdlib.h>


int num_games, num_bills;
int costs[1005];
int bills[1005];


int main()
{
    int count = 0;
    int bill_idx = 0;

    scanf("%d%d", &num_games, &num_bills);
    for (int i = 0; i < num_games; i++) scanf("%d", costs + i);
    for (int i = 0; i < num_bills; i++) scanf("%d", bills + i);

    for (int i = 0; i < num_games; i++) {
        if (bill_idx == num_bills) break;

        if (bills[bill_idx] >= costs[i]) {
            // buy game
            count++;
            bill_idx++;
        }
    }

    printf("%d\n", count);

    return 0;
}
