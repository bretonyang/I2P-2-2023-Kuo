#include <stdio.h>
#include <stdlib.h>


int num_games, num_bills;
int costs[1005];
int bills[1005];


int main()
{
    scanf("%d %d", &num_games, &num_bills);
    for (int i = 0; i < num_games; i++) scanf("%d", costs + i);
    for (int i = 0; i < num_bills; i++) scanf("%d", bills + i);

    int count = 0;
    int bill_idx = 0;
    for (int game_idx = 0; game_idx < num_games; game_idx++) {
        if (bill_idx == num_bills) break;

        if (bills[bill_idx] >= costs[game_idx]) {
            count++;
            bill_idx++;
        }
    }

    printf("%d\n", count);

    return 0;
}
