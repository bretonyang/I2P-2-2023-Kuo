#include <iostream>
#include <algorithm>
#include "function.h"

using namespace std;

Array_MAX_HEAP::Array_MAX_HEAP() = default;

void Array_MAX_HEAP::PUSH(const int &item) {
    int idx = 1 + Count;
    array[idx] = item;
    Count++;

    // swim up
    while (idx > 1 && array[idx] > array[idx / 2]) {
        swap(array[idx], array[idx / 2]);
        idx /= 2;
    }
}

int Array_MAX_HEAP::MAX() const {
    if (!Count) {
        return -1;
    }
    return array[1];
}

int Array_MAX_HEAP::POP() {
    if (!Count) {
        return -1;
    }
    int ret = array[1], idx = 1;
    array[1] = array[Count];
    Count--;

    // sink down
    while (2 * idx <= Count) {
        int left = 2 * idx, right = 2 * idx + 1;
        int max_idx;
        if (right > Count) max_idx = left;
        else max_idx = array[left] >= array[right] ? left : right;

        if (array[idx] >= array[max_idx]) {
            break; // in place
        }
        swap(array[idx], array[max_idx]);
        idx = max_idx;
    }
    return ret;
}

List_MAX_HEAP::List_MAX_HEAP() {
    root = new ListNode(-1); // sentinel root node, whose left child is the root node
}

void List_MAX_HEAP::PUSH(const int &item) {
    if (!Count) {
        ListNode *cur = new ListNode(item);
        cur->parent = root;
        root->left = cur;
        Count++;
        return;
    }
    ListNode *cur = new ListNode(item);
    ListNode *p = findparent(1 + Count, root->left);
    Count++;

    if (p->left == NULL) p->left = cur;
    else p->right = cur;
    cur->parent = p;

    // swim up
    while (cur->parent != root && cur->value > p->value) {
        swap(cur->value, p->value);
        cur = cur->parent;
        p = cur->parent;
    }
}

int List_MAX_HEAP::MAX() const {
    if (!Count) {
        return -1;
    }
    return root->left->value;
}

int List_MAX_HEAP::POP() {
    if (!Count) {
        return -1;
    }
    else if (Count == 1) {
        int ret = root->left->value;
        delete root->left;
        root->left == NULL;
        Count--;
        return ret;
    }
    int ret = root->left->value;
    ListNode *p = findparent(Count, root->left);
    if (p->right == NULL) {
        root->left->value = p->left->value;
        delete p->left;
        p->left = NULL;
    }
    else {
        root->left->value = p->right->value;
        delete p->right;
        p->right = NULL;
    }
    Count--;
    // sink down
    ListNode *cur = root->left;
    while (cur->left != NULL || cur->right != NULL) {
        ListNode *max_child;
        if (cur->right == NULL) max_child = cur->left;
        else if (cur->left == NULL) max_child = cur->right;
        else {
            max_child = cur->left->value >= cur->right->value ? cur->left : cur->right;
        }

        if (cur->value >= max_child->value) {
            break; // in place
        }
        swap(cur->value, max_child->value);
        cur = max_child;
    }

    return ret;
}

void List_MAX_HEAP::deleteTree(ListNode *root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}






