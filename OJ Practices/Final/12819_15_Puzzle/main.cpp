#include <bits/stdc++.h>

using namespace std;
using State = vector<int>;
using pqPair = pair<int, State>;

int N = 4; // board size

bool inRange(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

set<State> neighbors(State s) {
    static int dr[] = {-1, 0, 1, 0};
    static int dc[] = {0, -1, 0, 1};
    set<State> res;
    int row, col;

    for (int i = 0; i < N * N; i++) {
        if (s[i] == 0) {
            row = i / N;
            col = i % N;
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if (inRange(nr, nc)) {
            swap(s[row * N + col], s[nr * N + nc]);
            res.insert(s);
            swap(s[row * N + col], s[nr * N + nc]);
        }
    }
    return res;
}

bool isTarget(State s) {
    for (int i = 0; i < N * N - 1; i++) {
        if (s[i] != i + 1) return false;
    }
    return s[N * N - 1] == 0;
}

int manhattan(State s) {
    int res = 0, row, col, expectedRow, expectedCol;
    for (int i = 0; i < N * N; i++) {
        if (s[i] != 0) {
            row = i / N;
            col = i % N;
            expectedRow = (s[i] - 1) / N; // fix 1-based issue
            expectedCol = (s[i] - 1) % N;
            res += abs(row - expectedRow) + abs(col - expectedCol);
        }
    }
    return res;
}

int nLinearConflicts(State s) {
    int conflicts = 0;

    // precalculate the correct (row, col) for each value
    vector<int> rowPosOfVal(N * N);
    vector<int> colPosOfVal(N * N);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            rowPosOfVal[s[r * N + c]] = r;
            colPosOfVal[s[r * N + c]] = c;
        }
    }

    // row conflicts
    for (int r = 0; r < N; r++) { // row
        for (int cl = 0; cl < N; cl++) { // col pointer at left
            for (int cr = cl + 1; cr < N; cr++) { // col pointer at right
                int goalValAt_r_cl = r * N + cl + 1;
                int goalValAt_r_cr = r * N + cr + 1;
                if (goalValAt_r_cl != 0 && goalValAt_r_cr != 0  // ignore 0 tile
                    && r == rowPosOfVal[goalValAt_r_cl]     // means goalValAt_r_cl is at its goal position row
                    && r == rowPosOfVal[goalValAt_r_cr]   // goal position of vals to check are on the same row
                    && colPosOfVal[goalValAt_r_cl] > colPosOfVal[goalValAt_r_cr]) { // goal col position of vals to check are conflicted (left > right)
                    conflicts++;
                }
            }
        }
    }

    // column conflicts
    for (int c = 0; c < N; c++) { // col
        for (int rU = 0; rU < N; rU++) { // row pointer at upper
            for (int rD = rU + 1; rD < N; rD++) { // row pointer at down
                int goalValAt_rU_c = rU * N + c + 1;
                int goalValAt_rD_c = rD * N + c + 1;
                if (goalValAt_rU_c != 0 && goalValAt_rD_c != 0
                    && c == colPosOfVal[goalValAt_rU_c]     // goalValAt_rU_c is at correct column
                    && c == colPosOfVal[goalValAt_rD_c]   // goalValAt_rD_c is also at the correct column
                    && rowPosOfVal[goalValAt_rU_c] > rowPosOfVal[goalValAt_rD_c]) { // but their row position is conflicted
                    conflicts++;
                }
            }
        }
    }

    return conflicts;
}

// linear conflicts
int h(State s) {
    return manhattan(s) + 2 * nLinearConflicts(s);
}

int astar(State s) {
    map<State, int> distTo;
    priority_queue<pqPair, vector<pqPair>, greater<pqPair>> q;
    map<State, bool> visited;

    q.push(make_pair(0, s));
    distTo[s] = 0;

    while (!q.empty()) {
        State v = q.top().second;
        q.pop();

        if (visited[v]) continue; // return if popped before
        visited[v] = true;

        int distToV = distTo[v];

        if (isTarget(v)) return distToV; // return if target found

        for (State w : neighbors(v)) {
            if (distTo.find(w) == end(distTo) || distToV + 1 < distTo[w]) {
                distTo[w] = distToV + 1;
                q.push(make_pair(distToV + 1 + h(w), w));
            }
        }
    }
}

int main()
{
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);

    State s(N * N);
    for (int i = 0; i < N * N; i++) cin >> s[i];

    int steps = astar(s);
    cout << steps << endl;

    return 0;
}
