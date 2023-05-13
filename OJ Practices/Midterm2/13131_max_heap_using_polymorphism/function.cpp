#include <bits/stdc++.h>
#include "function.h"

using namespace std;

Array_MAX_HEAP::Array_MAX_HEAP() = default;

void Array_MAX_HEAP::PUSH(const int &val) {
    Count++;
    array[Count] = val;

    // swim up
    for (int i = Count; i > 1; i /= 2) {
        if (array[i] > array[i / 2])
            swap(array[i], array[i / 2]);
        else break;
    }
}

int Array_MAX_HEAP::MAX() const {
    if (!Count) return -1;
    return array[1];
}

int Array_MAX_HEAP::POP() {
    if (!Count) {
        return -1;
    }
    Count--;
    int maximum = array[1];
    array[1] = array[Count + 1];

    // sink down
    int i = 1;
    while (2 * i <= Count) {
        int c = 2 * i;
        if (c < Count && array[c] < array[c + 1]) c++;

        if (array[i] < array[c]) {
            swap(array[i], array[c]);
            i = c;
        }
        else break;
    }

    return maximum;
}

// List

List_MAX_HEAP::List_MAX_HEAP() {
    root = NULL;
}

void List_MAX_HEAP::PUSH(const int &val) {
    Count++;
    if (root == NULL) {
        root = new ListNode(val);
    }
    else {
        ListNode *cur = new ListNode(val);
        ListNode *p = findparent(Count, root);

        if (p->left == NULL) p->left = cur;
        else p->right = cur;
        cur->parent = p;

        // swim up
        while (cur != root) {
            if (cur->value > p->value) {
                swap(cur->value, p->value);
                cur = cur->parent;
                p = cur->parent;
            }
            else {
                break;
            }
        }
    }
}

int List_MAX_HEAP::MAX() const {
    if (!Count) return -1;
    return root->value;
}

int List_MAX_HEAP::POP() {
    if (!Count) return -1;
    Count--;
    int maximum = root->value;

    if (Count == 0) {
        delete root;
        root = NULL;
    }
    else {
        ListNode *cur;
        ListNode *parent = findparent(Count + 1, root);
        if (parent->right == NULL) {
            cur = parent->left;
            parent->left = NULL;
        }
        else {
            cur = parent->right;
            parent->right = NULL;
        }

        root->value = cur->value;
        delete cur;
        cur = root;

        // swim down
        while (cur->left != NULL) {
            ListNode *child = cur->left;
            if (cur->right != NULL && cur->right->value > child->value) child = cur->right;

            if (cur->value < child->value) {
                swap(cur->value, child->value);
                cur = child;
            }
            else break;
        }
    }

    return maximum;
}

void List_MAX_HEAP::deleteTree(ListNode *root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
