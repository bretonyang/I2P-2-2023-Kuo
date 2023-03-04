#include <stdio.h>
#include <stdlib.h>
#include "function.h"


Node* createList(int n) {
    head = malloc(sizeof(Node));
    head->number = 1;
    head->next = NULL;
    head->prev = NULL;

    Node* tmp = head;
    for (int i = 2; i <= n; i++) {
        Node* new_node = malloc(sizeof(Node));
        new_node->number = i;
        new_node->next = NULL;
        new_node->prev = tmp;
        tmp->next = new_node;
        tmp = new_node;
    }
    head->prev = tmp;
    tmp->next = head;
    return head;
}



void solveJosephus(int n, int k) {
    Node* cur_node = head;
    int lucky_num;
    int num_of_nodes = n;

    int tmp_k = k;
    while (tmp_k--) {
        scanf("%d", &lucky_num);

        // after some leave circle, if lucky num is even, count from prev
//        printf("%d %d\n", tmp_k, lucky_num % num_of_nodes);
        if (tmp_k < k - 1 && lucky_num % 2 == 0) {
            cur_node = cur_node->prev;
        }

        /// NOTE: Avoid redundant steps when lucky_num is large
        int steps = lucky_num % num_of_nodes;
        /// NOTE: When steps is 0, we actually want to step through all nodes,
        /// instead of no steps at all
        if (steps == 0) steps = num_of_nodes;

        if (lucky_num % 2) {
            // odd: clockwise
            for (int counter = 1; counter < steps; counter++) {
                cur_node = cur_node->next;
            }
        }
        else {
            // even: counter clockwise
            for (int counter = 1; counter < steps; counter++) {
                cur_node = cur_node->prev;
            }
        }

        printf("%d\n", cur_node->number);

        // delete cur_node
        Node* next_node = cur_node->next;
        cur_node->prev->next = cur_node->next;
        cur_node->next->prev = cur_node->prev;
        free(cur_node);
        cur_node = next_node;

        num_of_nodes--;
    }
}


