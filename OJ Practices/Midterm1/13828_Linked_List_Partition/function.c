#include <stdio.h>
#include <stdlib.h>
#include "function.h"

#define SIZE 100005

int deque[SIZE];


node *partition_linked_list(node *head, int pivot) {
    int left_counter = 0, right_counter = SIZE - 1;
    node* cur_node = head;
    while (cur_node != NULL) {
        if (cur_node->val < pivot) {
            deque[left_counter++] = cur_node->val;
        }
        else {
            deque[right_counter--] = cur_node->val;
        }
        cur_node = cur_node->next;
    }
    cur_node = head;
    for (int i = 0; i < left_counter; i++) {
        cur_node->val = deque[i];
        cur_node = cur_node->next;
    }
    for (int i = SIZE - 1; i > right_counter; i--) {
        cur_node->val = deque[i];
        cur_node = cur_node->next;
    }
    return head;
}

