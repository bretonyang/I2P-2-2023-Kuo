#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int val;
    struct node* next;
} Node;


Node* adj[200005]; // 2,400,000
int path_to[200005]; // 800,000
int visited[200005]; // 800,000


Node* create_node(int val, Node* next) {
    Node* new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = next;
    return new_node;
}


void build_graph(int N) {
    int v, u;
    for (int i = 0; i < N - 1; i++) {
        scanf("%d%d", &v, &u);
        Node* v_node = create_node(v, adj[u]->next);
        Node* u_node = create_node(u, adj[v]->next);
        adj[v]->next = u_node;
        adj[u]->next = v_node;
    }
}


void dfs(int s) {
    visited[s] = 1;

    // visit neighbors of s
    Node* tmp = adj[s]->next;
    while (tmp != NULL) {
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


/// for debugging
void print_graph(int N) {
    printf("Adjacency List:\n");
    for (int i = 0; i < N; i++) {
        Node* tmp = adj[i]->next;
        printf("%d: ", i);
        while (tmp != NULL) {
            printf("%d ", tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
    }
    printf("Path To:\n");
    for (int i = 0; i < N; i++) {
        printf("%d: %d\n", i, path_to[i]);
    }
}


int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);

    // initialize adjacency_list
    for (int i = 0; i < N; i++) {
        adj[i] = malloc(sizeof(Node));
        adj[i]->next = NULL;
        adj[i]->val = -1; // don't care value
    }

    // setup graph
    int source = 0;
    build_graph(N);

    // build up path_to
    path_to[source] = source;
    dfs(source);

    // print path to each target
    for (int i = 0; i < Q; i++) {
        int t;
        scanf("%d", &t);
        print_path_to(source, path_to[t]);
        printf("%d\n", t);
    }

//    print_graph(N); /// for debugging

    return 0;
}
