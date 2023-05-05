#include <iostream>
#include "function.h"

using namespace std;

Node* make_node(int val, int tag) {
    Node *n = new Node;
    n->next = nullptr;
    n->prev = nullptr;
    n->val = val;
    n->tag = tag;
    return n;
}

KuoYangPresent::KuoYangPresent(int k) : k(k), sz(0), now(0), reverse(false) {
    head = make_node(-1, -1);
    tail = mid = head;
}

void KuoYangPresent::Push(int x) {
    sz++;
    Node *n = make_node(x, now);
    if (reverse) {
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
        if (sz % 2 == 0) {
            mid = mid->prev;
        }
    }
    else {
        n->prev = tail;
        tail->next = n;
        if (sz % 2 == 1) {
            mid = mid->next;
        }
        tail = n;
    }
}

void KuoYangPresent::Pop() {
    sz--;
    Node *tmp = mid->prev;
    mid->next->prev = mid->prev;
    mid->prev->next = mid->next;
    delete mid;
    mid = tmp; // since length is guaranteed to be odd
}

void KuoYangPresent::Reverse() {
    reverse = !reverse;
}

void KuoYangPresent::ProgrammingTanoshi() {
    now++;
}

void KuoYangPresent::KuoYangTeTe() { /* ??? */ }

int calc(int val, int k, int times) {
//    while (times > 0 && val > k) {
//        val = val % k;
//        times--;
//    }
//    return val;
    for (int i = 0; i < times; i++) {
        val %= k;
        if (val <= 1) break;
    }
    return val;
}

// each number has to be mod by (now - tag) times
void KuoYangPresent::PrintList() {
    if (reverse) {
        Node *tmp = tail;
        while (tmp != head) {
            cout << calc(tmp->val, k, now - tmp->tag) << ' ';
            tmp = tmp->prev;
        }
    }
    else {
        Node *tmp = head->next;
        while (tmp != nullptr) {
            cout << calc(tmp->val, k, now - tmp->tag) << ' ';
            tmp = tmp->next;
        }
    }
    cout << endl;
}
