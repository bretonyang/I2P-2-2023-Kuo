#include <stdio.h>
#include <stdlib.h>


int N;
char board[105][105];

int I_coord[10100][2];
int I_count = 0;

char target[] = "ICPCASIASG";
int target_len = 10;

int dr[] = {-1, -2, -1, -2, 1, 2, 1, 2};
int dc[] = {-2, -1, 2, 1, -2, -1, 2, 1};


int valid(int row, int col) {
    return row >= 0 && row < N && col >= 0 && col < N;
}


// idx: our current index in the target string
int dfs(int row, int col, int idx) {
    if (idx == target_len) {
        return 1;
    }

    // loop through 8 next positions
    for (int i = 0; i < 8; i++) {
        int nr = row + dr[i]; // next row
        int nc = col + dc[i]; // next col
        if (valid(nr, nc) && board[nr][nc] == target[idx]) {
            if (dfs(nr, nc, idx + 1)) {
                return 1;
            }
        }
    }

    return 0;
}


int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &board[i][j]);
            if (board[i][j] == 'I') {
                I_coord[I_count][0] = i;
                I_coord[I_count][1] = j;
                I_count++;
            }
        }
    }

    int possible = 0;
    for (int i = 0; i < I_count; i++) {
        if (dfs(I_coord[i][0], I_coord[i][1], 1)) {
            possible = 1;
            break;
        }
    }

    if (possible) printf("YES\n");
    else printf("NO\n");

    return 0;
}

