#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;
    Node(int val): val(val), next(nullptr) {}
};

int N;
Node *adj[1005];
bool visited[1005];
int farthest_node, max_len;

void add_edge(int u, int v) {
    Node *u_node = new Node(u);
    Node *v_node = new Node(v);
    v_node->next = adj[u]->next;
    adj[u]->next = v_node;
    u_node->next = adj[v]->next;
    adj[v]->next = u_node;
}

void dfs(int s, int current_len) {
    visited[s] = true;
    for (Node *tmp = adj[s]->next; tmp != nullptr; tmp = tmp->next) {
        int v = tmp->val;
        if (!visited[v]) {
            dfs(v, current_len + 1);
        }
    }

    if (current_len > max_len) {
        max_len = current_len;
        farthest_node = s;
    }
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++) {
        adj[i] = new Node(-1); // sentinel node
    }
    int u, v;
    for (int i = 1; i < N; i++) {
        cin >> u >> v;
        add_edge(u, v);
    }
    dfs(1, 0); // randomly pick in [1, N]
    max_len = 0;
    for (int i = 1; i <= N; i++)
        visited[i] = false;
    dfs(farthest_node, 0);
    cout << max_len << endl;

    return 0;
}
