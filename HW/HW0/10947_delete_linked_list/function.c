#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void deleteNode(Node** nd, int position) {
    // special case: first node
    if (position == 1) {
        Node* temp = *nd;
        *nd = temp->next;
        free(temp);
        return;
    }

    // else loop through the list
    Node* cur_node = *nd;
    int counter = 2;

    while (cur_node->next != NULL) {
        if (counter == position) {
            Node* temp = cur_node->next;
            cur_node->next = cur_node->next->next;
            free(temp);
            break;
        }
        cur_node = cur_node->next;
        counter++;
    }
}


Node* createList() {
    // head
    int data;
    scanf("%d", &data);

    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    head->data = data;

    Node* cur_node = head;

    // Read input
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;

        // create a new node
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->next = NULL;
        new_node->data = data;

        // update
        cur_node->next = new_node;
        cur_node = cur_node->next;
    }

    return head;
}
