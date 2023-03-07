#include <stdio.h>
#include <stdlib.h>
#include "function.h"


node *partition_linked_list(node *head, int pivot) {
    node* sentinel = malloc(sizeof(node));
    sentinel->next = head;

    node* prev_of_cur = sentinel;
    node* tail_of_left = sentinel;
    while (prev_of_cur != NULL && prev_of_cur->next != NULL) {
        if (prev_of_cur->next->val < pivot) {
            node* tmp = prev_of_cur->next;
            prev_of_cur->next = prev_of_cur->next->next;
            tmp->next = tail_of_left->next;
            tail_of_left->next = tmp;
            tail_of_left = tail_of_left->next;

            /// if the original prev_of_cur->next and tail_of_left->next are the same node
            /// then after swapping, prev_of_cur->next will still be the same node, so we
            /// should move prev_of_cur forward, since its next node is already explored.
            if (prev_of_cur->next == tail_of_left) {
                prev_of_cur = prev_of_cur->next;
            }
        }
        else {
            /// Only move prev_of_cur forward if next node is not swapped
            prev_of_cur = prev_of_cur->next;
        }
    }

    head = sentinel->next;
    free(sentinel);
    return head;
}


