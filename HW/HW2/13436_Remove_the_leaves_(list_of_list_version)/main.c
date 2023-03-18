#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int val;
    struct node* next;
} Node;

/// Note that vertices are 1-based
Node* adj[20005];
int deg[20005];
int removed[20005];
int queue[20005];
// total: ~80000 * 4 = 320,000


Node* create_node(int val, Node* next) {
    Node* new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->next = next;
    return new_node;
}


void init_values(int N) {
    for (int i = 1; i <= N; i++) {
        removed[i] = 0;
        deg[i] = 0;
        adj[i] = create_node(i, NULL);
    }
}


void create_adj(int N) {
    int v, u;
    for (int i = 0; i < N - 1; i++) {
        scanf("%d%d", &v, &u);
        deg[v]++;
        deg[u]++;
        Node* v_node = create_node(u, adj[v]->next);
        Node* u_node = create_node(v, adj[u]->next);
        adj[v]->next = v_node;
        adj[u]->next = u_node;
    }
}


void free_adj(int N) {
    for (int i = 1; i <= N; i++) {
        Node* tmp = adj[i];
        while (tmp != NULL && tmp->next != NULL) {
            Node* next = tmp->next;
            free(tmp);
            tmp = next;
        }
        free(tmp);
    }
}


int solve(int N, int K) {
    int num_vertices = N;
    while (K-- && num_vertices > 0) {
        int queue_idx = 0;
        for (int v = 1; v <= N; v++) {
            if (!removed[v] && deg[v] <= 1) {
                removed[v] = 1;
                num_vertices--;
                Node* tmp = adj[v]->next;
                while (tmp) {
                    if (!removed[tmp->val]) {
                        queue[queue_idx++] = tmp->val;
                    }
                    tmp = tmp->next;
                }
            }
        }
        for (int w = 0; w < queue_idx; w++) {
            deg[queue[w]]--;
        }
    }

    return num_vertices;
}


/// For Debugging
void print_adj(int N) {
    printf("Adjacency List:\n");
    for (int i = 1; i <= N; i++) {
        Node* tmp = adj[i]->next;
        printf("%d: ", i);
        while (tmp != NULL) {
            printf("%d ", tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
    }
    printf("Adjacency List finished\n");
}
void print_info(int N) {
    printf("Removed:\n");
    for (int i = 1; i <= N; i++) {
        printf("%d ", removed[i]);
    }
    printf("\nRemoved Finished\n");
    printf("Degree:\n");
    for (int i = 1; i <= N; i++) {
        printf("%d ", deg[i]);
    }
    printf("\nDegree Finished\n");
}


int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, K;
        scanf("%d%d", &N, &K);

        init_values(N);
        create_adj(N);

//        print_adj(N); /// For Debugging

        // Put this here so that we still read in input
        if (K == N) {
            printf("0\n");
            continue;
        }
        int num_vertices_left = solve(N, K);

//        print_info(N); /// For Debugging

        printf("%d\n", num_vertices_left);
        free_adj(N);
    }

    return 0;
}

/**

numVertices = N, list_of_nodes = [...]
for k in range(K):
    queue = Queue()
    for v in list_of_nodes:
        if not removed[v] and deg[v] <= 1:
            numVertices--
            removed[v] = true
            for w in list_of_nodes[v].adj:
                if not removed[w]:
                    queue.enqueue(w)
        list_of_nodes.remove(v)
    for v in queue:
        deg[V]--

*/
