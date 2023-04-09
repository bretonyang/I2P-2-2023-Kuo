#include <iostream>
#include "function.h"

using namespace std;

List_stack::List_stack() {
    head = new ListNode(-1); // sentinel
    tail = new ListNode(-1); // sentinel
    head->nextPtr = tail, head->prevPtr = tail;
    tail->nextPtr = head, tail->prevPtr = head;
}

List_stack::~List_stack() {
    ListNode* tmp = head;
    while (tmp != tail) {
        ListNode* next = tmp->nextPtr;
        delete tmp;
        tmp = next;
    }
    delete tail;
}

void List_stack::push(const int &data) {
    ListNode *new_node = new ListNode(data);
    new_node->nextPtr = tail;
    new_node->prevPtr = tail->prevPtr;
    tail->prevPtr->nextPtr = new_node;
    tail->prevPtr = new_node;
}

void List_stack::pop() {
    if (tail->prevPtr != head) {
        ListNode *tmp = tail->prevPtr;
        tail->prevPtr->prevPtr->nextPtr = tail;
        tail->prevPtr = tail->prevPtr->prevPtr;
        delete tmp;
    }
}

void List_stack::print() {
    if (tail->prevPtr != head) {
        ListNode *tmp = tail->prevPtr;
        while (tmp != head->nextPtr) {
            cout << tmp->data << ' ';
            tmp = tmp->prevPtr;
        }
        cout << tmp->data;
    }
}
