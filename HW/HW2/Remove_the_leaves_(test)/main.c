#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* next;
} Node;

Node* adj[20005];
int deg[20005];
int removed[20005];
int num_vertices;
int deg1_nodes[20005];
int initialized[20005];
int init_cnt = 1, T;

Node* create_node(int val, Node* next) {
    Node* new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = next;
    return new_node;
}

void build_graph(int N) {
    int v, u;
    for (int i = 1; i <= N - 1; i++) {
        scanf("%d%d", &v, &u);
        if (initialized[v] != init_cnt) {
            adj[v] = NULL;
            deg[v] = 0;
            initialized[v]++;
        }
        if (initialized[u] != init_cnt) {
            adj[u] = NULL;
            deg[u] = 0;
            initialized[u]++;
        }
        Node* v_node = create_node(v, adj[u]);
        Node* u_node = create_node(u, adj[v]);
        adj[v] = u_node;
        adj[u]= v_node;
        deg[v]++;
        deg[u]++;
        removed[i] = 0;
    }
    removed[N] = 0;
    init_cnt++;
}

void free_graph(int N) {
    for (int i = 1; i <= N; i++) {
        Node* tmp = adj[i];
        while (tmp != NULL) {
            Node* next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
}

void solve(int N, int K) {
    int deg1_cnt = 0, tmp_deg1_cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 1) {
            deg1_nodes[deg1_cnt++] = i;
            if (K > 0) num_vertices--;
        }
    }

    K--;
    while (K-- > 0 && num_vertices > 0) {
        if (num_vertices <= 2) {
            num_vertices = 0;
            break;
        }
        tmp_deg1_cnt = 0;
        for (int i = 0; i < deg1_cnt; i++) {
            int cur_node = deg1_nodes[i];
            Node* tmp = adj[cur_node];

            while (tmp != NULL) {
                if (!removed[tmp->val]) {
                    deg[tmp->val]--;
                    if (deg[tmp->val] == 1) {
                        deg1_nodes[tmp_deg1_cnt++] = tmp->val;
                        num_vertices--;
                        removed[tmp->val] = 1;
                    }
                }
                tmp = tmp->next;
            }
        }
        deg1_cnt = tmp_deg1_cnt;
    }
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        int N, K;
        scanf("%d%d", &N, &K);

        build_graph(N);
        num_vertices = N;
        solve(N, K);
        printf("%d\n", num_vertices);

        free_graph(N);
    }
    return 0;
}
