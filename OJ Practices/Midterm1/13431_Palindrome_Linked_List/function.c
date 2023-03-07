#include <stdio.h>
#include <stdlib.h>
#include "function.h"

node* reverse(node* head);

/// e.g.
/// 1 2 3 4: right 1 2, left 3 4
/// 1 2 3 4 5: right 1 2 (3), left 4 5

/// Find the middle point using a slow and a fast pointer
/// then reverse the right list and compare it with the left list
bool is_palindrome(node *head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }

    node* slow = head;
    node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    node* reversed_right = reverse(slow->next);
    node* left = head;
    while (reversed_right != NULL) {
        if (left->val != reversed_right->val) {
            return false;
        }
        left = left->next;
        reversed_right = reversed_right->next;
    }
    return true;
}

node* reverse(node* head) {
    node* sentinel = malloc(sizeof(node));
    sentinel->next = NULL;
    while (head != NULL) {
        node* next = head->next;
        head->next = sentinel->next;
        sentinel->next = head;
        head = next;
    }
    node* tmp = sentinel->next;
    free(sentinel);
    return tmp;
}

//int stack[100005];

//bool is_palindrome(node *head) {
//    int counter = 0;
//    node* cur_node = head;
//    while (cur_node != NULL) {
//        stack[counter++] = cur_node->val;
//        cur_node = cur_node->next;
//    }
//    cur_node = head;
//    counter--;
//    while (cur_node != NULL) {
//        if (cur_node->val != stack[counter--]) {
//            return false;
//        }
//        cur_node = cur_node->next;
//    }
//    return true;
//}
