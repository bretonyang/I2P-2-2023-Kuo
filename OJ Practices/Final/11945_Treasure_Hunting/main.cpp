#include <bits/stdc++.h>

#define INF 1000000005

using namespace std;

/**

key ideas:
1. only one distTo is needed
2. only call bfs on target nodes is sufficient

*/

int N, M, K;

vector<int> goals;
vector<int> adj[100005];

bool visited[100005] = {};
// After all the bfs calls on goals, this will be the shortest dist to some goal
int distTo[100005] = {};

int bfs(int s) {
    fill(visited, visited + N, false);

    queue<int> q;
    q.push(s);
    distTo[s] = 0;
    visited[s] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int w : adj[v]) {
            // if current potential dist to w is < old dist to w
            // => some previous goal is closer to w!!!
            // => all other neighbors of w is also closer to some previous goal!!!
            if (!visited[w] && distTo[v] + 1 < distTo[w]) {
                visited[w] = true;
                distTo[w] = distTo[v] + 1;
                q.push(w);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> K;

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--; // fix 1-based to 0-based
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int goal;
        cin >> goal;
        goals.push_back(goal - 1); // fix to 0-based
    }

    fill(distTo, distTo + 100005, INF);
    for (int i = 0; i < K; i++) {
        bfs(goals[i]);
    }

    for (int i = 0; i < N; i++) {
        cout << distTo[i] << "\n";
    }

    return 0;
}
