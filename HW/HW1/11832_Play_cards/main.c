#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int val;
    struct node* next;
} Node;


Node* sentinel;


void create_list(int n) {
    sentinel = malloc(sizeof(Node));
    sentinel->next = NULL;

    int val;
    Node* tmp = sentinel;
    while (n--) {
        scanf("%d", &val);

        Node* new_node = malloc(sizeof(Node));
        new_node->val = val;
        new_node->next = NULL;

        tmp->next = new_node;
        tmp = tmp->next;
    }
}

void print_list() {
//    printf("Printing list: ");
//    Node* tmp = sentinel->next;
//    while (tmp != NULL) {
//        printf("%d ", tmp->val);
//        tmp = tmp->next;
//    }
//    printf("\n");

    Node* tmp = sentinel->next;
    while (tmp != NULL) {
        printf("%d\n", tmp->val);
        tmp = tmp->next;
    }
}

void free_list() {
    Node* cur = sentinel;
    while (cur != NULL) {
        Node* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

/// assumes idx is always in valid range
void add(int idx, int num) {
    Node* tmp = sentinel;
    while (idx--) {
        tmp = tmp->next;
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->val = num;
    new_node->next = tmp->next;
    tmp->next = new_node;
}

void cut(int start, int interval) {
    Node* node_before_start = sentinel;
    while (start--) {
        node_before_start = node_before_start->next;
    }
    Node* start_node = node_before_start->next;
    Node* end_node = node_before_start;
    while (interval--) {
        end_node = end_node->next;
    }
    node_before_start->next = end_node->next;
    end_node->next = sentinel->next;
    sentinel->next = start_node;
}


int main()
{
    int num_cards, num_operations;
    char command[4];
    scanf("%d %d", &num_cards, &num_operations);

    create_list(num_cards);

    while (num_operations--) {
        scanf("%s", command);
        if (command[0] == 'A') {
            int idx, num;
            scanf("%d %d", &idx, &num);
            add(idx, num);
        }
        else {
            int a, b;
            scanf("%d %d", &a, &b);
            cut(a, b);
        }
    }

    print_list();

    free_list();

    return 0;
}

