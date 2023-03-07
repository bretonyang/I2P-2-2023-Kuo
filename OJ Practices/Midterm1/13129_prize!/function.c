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
        tmp = tmp->next;
    }
    head->prev = tmp;
    tmp->next = head;
    return head;
}

void solveJosephus(int n, int k) {
    Node* cur_node = head;
    int lucky_num, num_of_people_left = n;

    for (int i = 0; i < k; i++) {
        scanf("%d", &lucky_num);

        if (i > 0 && lucky_num % 2) {
            // after someone left and lucky_num is odd
            cur_node = cur_node->next;
        }

        int steps = lucky_num % num_of_people_left;
        if (lucky_num % 2) {
            // odd: clockwise
            if (!steps) {
                cur_node = cur_node->prev; // prev node
            }
            else {
                for (int j = 1; j < steps; j++) {
                    cur_node = cur_node->next;
                }
            }
        }
        else {
            // even: counter clockwise
            if (!steps) {
                cur_node = cur_node->next; // next node
            }
            else {
                for (int j = 1; j < steps; j++) {
                    cur_node = cur_node->prev;
                }
            }
        }
        printf("%d\n", cur_node->number);
        // delete cur_node
        Node* tmp = cur_node->prev;
        cur_node->prev->next = cur_node->next;
        cur_node->next->prev = cur_node->prev;
        free(cur_node);
        num_of_people_left--;
        cur_node = tmp;
    }
}

