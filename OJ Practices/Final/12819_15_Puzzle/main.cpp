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

    // setup for later convenient comparison
    vector<int> pR(N * N + 1);
    vector<int> pC(N * N + 1);
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            pR[s[r * N + c]] = r;
            pC[s[r * N + c]] = c;
        }
    }

    // row conflicts
    for (int r = 0; r < N; r++) {
        for (int cl = 0; cl < N; cl++) {
            for (int cr = cl + 1; cr < N; cr++) {
                int goalValAt_r_cl = r * N + cl + 1;
                int goalValAt_r_cr = r * N + cr + 1;
                if (goalValAt_r_cl && goalValAt_r_cr
                    && r == pR[goalValAt_r_cl] && pR[goalValAt_r_cl] == pR[goalValAt_r_cr]
                    && pC[goalValAt_r_cl] > pC[goalValAt_r_cr]) {
                    conflicts++;
                }
            }
        }
    }

    // column conflicts -
    for (int c = 0; c < N; c++) {
        for (int rU = 0; rU < N; rU++) {
            for (int rD = rU + 1; rD < N; rD++) {
                int goalValAt_rU_c = rU * N + c + 1;
                int goalValAt_rD_c = rD * N + c + 1;
                if (goalValAt_rU_c && goalValAt_rD_c
                    && c == pC[goalValAt_rU_c] && pC[goalValAt_rU_c] == pC[goalValAt_rD_c]
                    && pR[goalValAt_rU_c] > pR[goalValAt_rD_c]) {
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
//    map<State, int> heuristicTable;
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
                /// Somehow, below is runtime error
//                if (heuristicTable.find(w) == end(heuristicTable)) {
//                    heuristicTable[w] = h(w);
//                }
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
