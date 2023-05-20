#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<bool> on_stack;
    int V;
    int E;
    bool cycle_found = false;

    // v: currect vertex, p: parent of v
    void dfs_cycle_detect(int v) {
        visited[v] = true;
        on_stack[v] = true;

        for (int w : adj[v]) {
            if (!visited[w]) {
                dfs_cycle_detect(w);
                if (cycle_found) return;
            }
            else if (on_stack[w]) {
                cycle_found = true;
                return;
            }
        }
        on_stack[v] = false;
    }

public:
    Graph(int V, int E) : V(V), E(E), adj(V), visited(V, false), on_stack(V, false) {
        int v, w;
        for (int i = 0; i < E; i++) {
            cin >> v >> w;
            v--; // fix to 0-based
            w--;
            adj[v].push_back(w); // v --> w
        }
        for (int i = 0; i < V && !cycle_found; i++) {
            if (!visited[i])
                dfs_cycle_detect(i);
        }
    }

    bool has_cycle() {
        return cycle_found;
    }
};

int main()
{
    int k, num = 0, V, E;
    cin >> k;
    while (k--) {
        cin >> V >> E;
        Graph g(V, E);
        if (g.has_cycle())
            num++;
    }
    cout << num << endl;

    return 0;
}
