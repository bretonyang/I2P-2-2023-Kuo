#include <bits/stdc++.h>

using namespace std;
using State = vector<int>;

int N = 3; // board size

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

int limitedBFS(State s, int maxSteps) {
    // NOTE: using vector<int> as key type for unordered_map requires custom hash function!
    map<State, int> distTo;
    queue<State> q;
    map<State, bool> visited;
    q.push(s);
    distTo[s] = 0;
    visited[s] = true;
    while (!q.empty()) {
        State v = q.front();
        q.pop();
        int distToV = distTo[v];

        if (distToV > maxSteps || isTarget(v)) {
            return distToV;
        }

        for (State w : neighbors(v)) {
            if (!visited[w]) {
                visited[w] = true;
                distTo[w] = distToV + 1;
                q.push(w);
            }
        }
    }
    return maxSteps + 1; // didn't find any solution
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        State s(N * N);
        for (int i = 0; i < N * N; i++) cin >> s[i];

        int steps = limitedBFS(s, 14);
        if (steps > 14)
            cout << "You'd better skip this game." << endl;
        else
            cout << "You can solve it within " << steps << " steps." << endl;
    }

    return 0;
}
