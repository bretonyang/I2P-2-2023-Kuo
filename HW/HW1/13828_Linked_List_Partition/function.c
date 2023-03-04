#include <stdio.h>
#include <stdlib.h>
#include "function.h"

#define SIZE 100005


int deque[100005]; // 400,000


/**
 * NOTE: No need to put the pivot in the middle, we simply want to
 * partition the list into LEFT and RIGHT 2 parts, where all nodes in LEFT
 * are < pivot, and all nodes in RIGHT are > pivot.
 */
node *partition_linked_list(node *head, int pivot) {
    int min_counter = 0, max_counter = SIZE - 1;
    node* tmp = head;

    // record the correct order in deque
    while (tmp != NULL) {
        if (tmp->val >= pivot) {
            deque[max_counter] = tmp->val;
            max_counter--;
        }
        else {
            deque[min_counter] = tmp->val;
            min_counter++;
        }
        tmp = tmp->next;
    }

    // put the correct val back to each node
    tmp = head;
    for (int i = 0; i < min_counter; i++) {
        tmp->val = deque[i];
        tmp = tmp->next;
    }
    for (int i = SIZE - 1; i > max_counter; i--) {
        tmp->val = deque[i];
        tmp = tmp->next;
    }

    return head;
}

/**

1, 3, 8, 2, 3, 8

1, 2, 3, 8, 3, 8

*/
