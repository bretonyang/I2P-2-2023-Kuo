#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int val;
    struct node* next;
} Node;


void print_list(Node* sentinel) {
    Node* cur = sentinel->next;
    while (cur != NULL) {
        printf("%d\n", cur->val);
        cur = cur->next;
    }
}

void add(Node* sentinel, int idx, int num) {
    Node* cur = sentinel;
    while (idx--) {
        cur = cur->next;
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->val = num;
    new_node->next = cur->next;
    cur->next = new_node;
}

void cut(Node* sentinel, int a, int b) {
    Node *node_before_start, *start_node, *end_node;
    node_before_start = sentinel;
    while (a--) {
        node_before_start = node_before_start->next;
    }
    start_node = node_before_start->next;
    end_node = node_before_start;
    while (b--) {
        end_node = end_node->next;
    }
    node_before_start->next = end_node->next;
    end_node->next = sentinel->next;
    sentinel->next = start_node;
}

int main()
{
    int num_cards, num_ops, idx, num, a, b;
    char command[4];
    scanf("%d %d", &num_cards, &num_ops);

    Node* sentinel = malloc(sizeof(Node));
    sentinel->next = NULL;

    // Create list
    Node* cur = sentinel;
    while (num_cards--) {
        int val;
        scanf("%d", &val);
        Node* new_node = malloc(sizeof(Node));
        new_node->val = val;
        new_node->next = NULL;

        cur->next = new_node;
        cur = cur->next;
    }

    // Perform commands on list
    while (num_ops--) {
        scanf("%s", command);
        if (command[0] == 'A') {
            scanf("%d %d", &idx, &num);
            add(sentinel, idx, num);
        }
        else {
            scanf("%d %d", &a, &b);
            cut(sentinel, a, b);
        }
    }

    print_list(sentinel);

    return 0;
}
