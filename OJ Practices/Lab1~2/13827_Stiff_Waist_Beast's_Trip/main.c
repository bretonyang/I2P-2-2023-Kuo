#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* next;
} Node;

Node* adj[200005];
int visited[200005];
int path_to[200005];

Node* create_node(int val, Node* next) {
    Node* new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = next;
    return new_node;
}

void dfs(int s) {
    visited[s] = 1;
    Node* tmp = adj[s];
    while (tmp) {
        if (!visited[tmp->val]) {
            path_to[tmp->val] = s;
            dfs(tmp->val);
        }
        tmp = tmp->next;
    }
}

void print_path_to(int s, int t) {
    if (t == s) {
        printf("%d ", s);
        return;
    }
    print_path_to(s, path_to[t]);
    printf("%d ", t);
}

int main()
{
    int N, Q, v, u;
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N - 1; i++) {
        scanf("%d%d", &v, &u);
        Node* v_node = create_node(u, adj[v]);
        Node* u_node = create_node(v, adj[u]);
        adj[v] = v_node;
        adj[u] = u_node;
    }

    int s = 0;
    dfs(s);

    while (Q--) {
        int t;
        scanf("%d", &t);
        print_path_to(s, path_to[t]);
        printf("%d\n", t);
    }

    return 0;
}
