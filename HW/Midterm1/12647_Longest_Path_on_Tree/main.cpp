#include <iostream>
#include <vector>

using namespace std;

int N;
int max_len, longest_root;
bool visited[1005];
vector<int> adj[1005];

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void dfs(int s, int cur_len) {
    visited[s] = true;
    for (int v : adj[s]) {
        if (!visited[v]) {
            dfs(v, cur_len + 1);
        }
    }
    if (cur_len > max_len) {
        max_len = cur_len;
        longest_root = s;
    }
}

int main()
{
    cin >> N;
    int u, v;
    for (int i = 1; i < N; i++) {
        cin >> u >> v;
        add_edge(u, v);
    }

    dfs(1, 0); // just randomly pick a number in [1, N]
    for (int i = 1; i <= N; i++)
        visited[i] = false;
    max_len = 0;
    dfs(longest_root, 0);
    cout << max_len << endl;

    return 0;
}
