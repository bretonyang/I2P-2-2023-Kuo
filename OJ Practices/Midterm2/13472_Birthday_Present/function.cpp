#include <iostream>
#include "function.h"

using namespace std;

Node *make_node(int val, int tag) {
    return new Node{nullptr, nullptr, val, tag};
}

KuoYangPresent::KuoYangPresent(int k) : k(k), sz(0), now(0), reverse(false) {
    tail = mid = head = make_node(-1, -1); // as a sentinel head
}

void KuoYangPresent::Push(int x) {
    sz++;
    Node *n = make_node(x, now);
    if (!reverse) {
        n->prev = tail;
        tail->next = n;
        tail = tail->next;
        if (sz % 2 == 1) {
            mid = mid->next;
        }
    }
    else {
        n->prev = head;
        n->next = head->next;
        head->next->prev = n;
        head->next = n;
        if (sz % 2 == 0) {
            mid = mid->prev;
        }
    }
}

void KuoYangPresent::Pop() {
    sz--;
    Node *tmp = mid->prev;
    mid->prev->next = mid->next;
    mid->next->prev = mid->prev;
    delete mid;
    mid = tmp;
}

void KuoYangPresent::Reverse() {
    reverse = !reverse;
}

void KuoYangPresent::ProgrammingTanoshi() {
    now++;
}

void KuoYangPresent::KuoYangTeTe() {}

int calc(int val, int k, int times) {
    return times == 0 ? val : val % k;
}

void KuoYangPresent::PrintList() {
    if (!reverse) {
        for (Node *tmp = head->next; tmp != nullptr; tmp = tmp->next) {
            cout << calc(tmp->val, k, now - tmp->tag) << ' ';
        }
    }
    else {
        for (Node *tmp = tail; tmp != head; tmp = tmp->prev) {
            cout << calc(tmp->val, k, now - tmp->tag) << ' ';
        }
    }
    cout << endl;
}
