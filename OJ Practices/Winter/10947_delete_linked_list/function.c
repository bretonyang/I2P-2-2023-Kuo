#include <stdio.h>
#include <stdlib.h>
#include "function.h"


void deleteNode(Node ** nd, int position) {
    Node* tmp = *nd;
    if (position == 1) {
        *nd = (*nd)->next;
        free(tmp);
        return;
    }

    // traverse
    for (int counter = 2; counter < position && tmp->next != NULL; counter++) {
        tmp = tmp->next;
    }

    // position is too large
    if (tmp->next == NULL) return;

    // normal situation
    Node* nodeToDelete = tmp->next;
    tmp->next = tmp->next->next;
    free(nodeToDelete);
}


static Node* createNode() {
    Node* newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = 0;
    return newNode;
}


Node* createList() {
    Node* head = createNode();
    Node* tmp = head;
    int data;

    scanf("%d", &data);
    if (data == -1) return NULL;

    head->data = data;

    while (1) {
        scanf("%d", &data);
        if (data == -1) break;

        Node* newNode = createNode();
        newNode->data = data;
        tmp->next = newNode;
        tmp = newNode;
    }

    return head;
}
