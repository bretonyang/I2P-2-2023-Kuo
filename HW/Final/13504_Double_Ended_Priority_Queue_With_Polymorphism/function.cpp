#include <bits/stdc++.h>
#include "function.h"

using namespace std;

/** DEPQ with Min-Max Heap */

void DEPQ_MMH::push(int x) {
    mmh.push(x);
}

int DEPQ_MMH::top() const {
    return mmh.get_min();
}

int DEPQ_MMH::bottom() const {
    return mmh.get_max();
}

void DEPQ_MMH::pop_top() {
    mmh.pop_min();
}

void DEPQ_MMH::pop_bottom() {
    mmh.pop_max();
}

int DEPQ_MMH::size() const {
    return mmh.size();
}

bool DEPQ_MMH::empty() const {
    return mmh.empty();
}


/** DEPQ with BST */

void DEPQ_BST::push(int x) {
    bst.insert(x);
}

int DEPQ_BST::top() const {
    return *begin(bst);
}

int DEPQ_BST::bottom() const {
    return *rbegin(bst);
}

void DEPQ_BST::pop_top() {
    bst.erase(begin(bst));
}

void DEPQ_BST::pop_bottom() {
    auto it = end(bst);
    --it;
    bst.erase(it);
}

int DEPQ_BST::size() const {
    return bst.size();
}

bool DEPQ_BST::empty() const {
    return bst.empty();
}

