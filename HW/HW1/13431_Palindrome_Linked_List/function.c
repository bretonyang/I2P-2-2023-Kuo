#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int stack[100005]; // 400,000

bool is_palindrome(node *head) {
    int counter = 0;
    node* tmp = head;

    // Record the reverse order of the list in a stack.
    while (tmp != NULL) {
        stack[counter] = tmp->val;
        counter++;
        tmp = tmp->next;
    }
    counter--; // fix indexing

    // Compare original list and reverse(list)
    tmp = head;
    while (tmp != NULL) {
        if (tmp->val != stack[counter]) {
            return false;
        }
        counter--;
        tmp = tmp->next;
    }
    return true;
}
