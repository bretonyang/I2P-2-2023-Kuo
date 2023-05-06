#include <iostream>

#include "function.h"

using namespace std;

// Dereference the iterator
template <typename T>
T &linked_list<T>::iterator::operator*()
{
    return n->val;
}

// Forward the itarator by pre-increament
template <typename T>
typename linked_list<T>::iterator linked_list<T>::iterator::operator++()
{
    n = n->next;
    return *this;
}

// Merge two sorted linked list internally
template <typename T>
typename linked_list<T>::node *linked_list<T>::merge(node *lhs, node *rhs)
{
    node *sentinel = new node(); /// NOTE: node() zero initializes each field of `node` (incl. `T val`)
    node *tmp = sentinel;
    while (lhs && rhs) {
        if (lhs->val <= rhs->val) {
            tmp->next = lhs;
            lhs = lhs->next;
        }
        else {
            tmp->next = rhs;
            rhs = rhs->next;
        }
        tmp = tmp->next;
    }

    if (rhs) tmp->next = rhs;
    else if (lhs) tmp->next = lhs;

    tmp = exchange(sentinel->next, nullptr); /// NOTE: node's destructor will delete until nullptr
    delete sentinel;
    return tmp;
}

// Don't forget thess lines; otherwise compiler would not generate reference symbols and you'll get a CE.
template class linked_list<int>;
template class linked_list<string>;
