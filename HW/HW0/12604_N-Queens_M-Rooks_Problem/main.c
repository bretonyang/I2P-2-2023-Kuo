#include <stdio.h>
#include <stdlib.h>

# define EMPTY -9999


int N, M;
int W; // N + M, width of the board
long long num_of_solutions = 0;
int queen_pos[15];
int rook_pos[15];
int queen_cnt = 0;
int rook_cnt = 0;


int valid_queen_pos(int row, int col) {
    for (int i = 0; i < row; i++) {
        int qc = queen_pos[i]; // queen's col at i-th row
        int rc = rook_pos[i];
        if (qc != EMPTY && (qc == col - (row - i) || qc == col || qc == col + (row - i))) {
            return 0;
        }
        else if (rc == col - (row - i) || rc == col || rc == col + (row - i)) {
            return 0;
        }
    }
    return 1;
}


int valid_rook_pos(int row, int col) {
    for (int i = 0; i < row; i++) {
        int qc = queen_pos[i]; // queen's col at i-th row
        int rc = rook_pos[i];

        // have to check rook not in path of previous queens
        if (qc != EMPTY && (qc == col - (row - i) || qc == col || qc == col + (row - i))) {
            return 0;
        }
        else if (rc == col) {
            return 0;
        }
    }
    return 1;
}


void dfs(row) {
    if (row == W) {
        num_of_solutions++;
        return;
    }

    for (int c = 0; c < W; c++) {
        if (queen_cnt < N && valid_queen_pos(row, c)) {
            queen_pos[row] = c;
            queen_cnt++;

            dfs(row + 1);

            queen_pos[row] = EMPTY;
            queen_cnt--;
        }
        if (rook_cnt < M && valid_rook_pos(row, c)) {
            rook_pos[row] = c;
            rook_cnt++;

            dfs(row + 1);

            rook_pos[row] = EMPTY;
            rook_cnt--;
        }
    }
}


int main()
{
    while (scanf("%d%d", &N, &M) != EOF) {
        W = N + M;
        for (int i = 0; i < 15; i++) {
            queen_pos[i] = EMPTY;
        }
        for (int i = 0; i < 15; i++) {
            rook_pos[i] = EMPTY;
        }

        num_of_solutions = 0;
        queen_cnt = 0;
        rook_cnt = 0;
        dfs(0);

        printf("%lld\n", num_of_solutions);
    }

    return 0;
}
