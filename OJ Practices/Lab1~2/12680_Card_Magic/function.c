#include <stdio.h>
#include <stdlib.h>
#include "function.h"

Node* ReadOneList() {
    Node* sentinel = (Node*)malloc(sizeof(Node));
    scanf("%d: ", &(sentinel->size));
    sentinel->data = (int*)malloc(sentinel->size * sizeof(int));
    for(int i=0; i<(sentinel->size); i++) {
        int x;
        scanf("%d", &x);
        getchar();
        *((sentinel->data)+i) = x;
    }
    sentinel->next = NULL;
    return sentinel;
}

void PrintList(Node* sentinel) {
    sentinel = sentinel->next;
    while(sentinel != NULL) {
        printf("%d", *(sentinel->data));
        for(int i=1; i<(sentinel->size); i++)
            printf(" %d", *((sentinel->data)+i));
        printf("\n");
        Node* temp = sentinel;
        sentinel = sentinel->next;
    }
}

void Merge(Node* sentinel, int x, int y) {
    /// return if same stack (can't merge)
    if(x == y) return;

    /// Traverse to the correct x and y nodes while keeping track of their prev
    Node* prev_x = sentinel;
    Node* temp_x = prev_x->next;
    Node* prev_y = sentinel;
    Node* temp_y = prev_y->next;
    x--;
    while(x--) {
        prev_x = prev_x->next;
        temp_x = temp_x->next;
        if(temp_x == NULL) return;
    }
    y--;
    while(y--) {
        prev_y = prev_y->next;
        temp_y = temp_y->next;
        if(temp_y == NULL) return;
    }

    /// Create new node and copy x and y's data into new node's data
    Node* new_head = (Node*)malloc(sizeof(Node));
    new_head->size = temp_x->size + temp_y->size;
    new_head->data = (int*)malloc((new_head->size) * sizeof(int));
    int i;
    for(i=0; i<temp_y->size; i++)
        *((new_head->data)+i) = *((temp_y->data)+i);
    for(int j=0; j<temp_x->size; j++)
        *((new_head->data)+i+j) = *((temp_x->data)+j);

    /// Connect new node with original list
    /// Change it to: prev->new->next

    /// case: prev->y->x->next
    if(temp_y == prev_x) {
        prev_y->next = new_head;
        new_head->next = temp_x->next;
    }
    /// case: prev->x->y->next
    else if(temp_x == prev_y) {
        prev_x->next = new_head;
        new_head->next = temp_y->next;
    }
    /// case: x and y are not adjacent
    else {
        prev_y->next = new_head;
        new_head->next = temp_y->next;
        prev_x->next = temp_x->next;
    }

    free(temp_x->data);
    free(temp_x);
    free(temp_y->data);
    free(temp_y);
}

void Cut(Node* sentinel, int x, int y) {
    /// Traverse to the correct node and keep track of its prev
    Node* prev = sentinel;
    Node* temp = sentinel->next;
    x--;
    while(x--) {
        prev = prev->next;
        temp = temp->next;
    }

    /// return if size <= 1
    if(temp->size < 2) return;

    /// Create 2 new nodes
    int size_1 = y;
    int size_2 = temp->size - y;
    Node* new_head_1 = (Node*)malloc(sizeof(Node));
    Node* new_head_2 = (Node*)malloc(sizeof(Node));
    new_head_1->size = size_1;
    new_head_2->size = size_2;
    new_head_1->data = (int*)malloc(new_head_1->size * sizeof(int));
    new_head_2->data = (int*)malloc(new_head_2->size * sizeof(int));

    /// Copy data into 2 nodes
    int i;
    for(i=0; i<new_head_1->size; i++)
        *(new_head_1->data+i) = *(temp->data+i);
    for(int j=0; j<new_head_2->size; j++)
        *(new_head_2->data+j) = *(temp->data+i+j);

    /// connect 2 new nodes with original list
    prev->next = new_head_1;
    new_head_1->next = new_head_2;
    new_head_2->next = temp->next;

    free(temp->data);
    free(temp);
}
