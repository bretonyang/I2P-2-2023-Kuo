#include <iostream>
#include <cstring>
#include "function.h"

#define SIZE 1000001

using namespace std;

bool inserted[SIZE];
bool ordered[SIZE];

song *make_song(int num, song *pre, song *next) {
    song *s = new song();
    s->num = num;
    s->pre = pre;
    s->next = next;
    return s;
}

void my_print(song *st, song *en) {
    song *now = st;
    while(now != en){
        cout << now->num << ' ';
        now = now->next;
    }
}

void ordering_system::initialize() {
    tmp2 = make_song(-1, nullptr, nullptr);
    tmp1 = make_song(-1, nullptr, tmp2);
    head = make_song(-1, nullptr, tmp1);
    tmp2->pre = tmp1;
    tmp1->pre = head;
    head->pre = tmp2;
    tmp2->next = head;
    memset(inserted, false, SIZE);
    memset(ordered, false, SIZE);
}

void ordering_system::order(int k) {
    song *new_song = make_song(k, head->pre, head);
    head->pre->next = new_song;
    head->pre = new_song;
    ordered[k] = true;
}

void ordering_system::play() {
    song *play_song = nullptr;
    if (tmp1->next != tmp2) { // inserted song
        play_song = tmp1->next;
        tmp1->next->next->pre = tmp1;
        tmp1->next = tmp1->next->next;
    }
    else if (tmp2->next != head) { // ordered song
        play_song = tmp2->next;
        tmp2->next->next->pre = tmp2;
        tmp2->next = tmp2->next->next;
    }

    if (play_song == nullptr) {
        cout << "All songs are played." << "\n";
    }
    else {
        cout << play_song->num << "\n";
        play_song->pre = tmp1->pre;
        play_song->next = tmp1;
        tmp1->pre->next = play_song;
        tmp1->pre = play_song;
    }
}

void ordering_system::show() {
    my_print(head->next, tmp1);
    cout << "\n";
    my_print(tmp1->next, tmp2);
    my_print(tmp2->next, head);
    cout << "\n";
}

/**

- k (not in inserted) and (not in ordered): insert end

- k (not in inserted) and (in ordered): insert end, remove from ordered
- k (in inserted): insert front, remove

*/
void ordering_system::insert(int k) {
    if (!inserted[k] && !ordered[k]) {
        // add to end of inserted
        song *new_song = make_song(k, tmp2->pre, tmp2);
        tmp2->pre->next = new_song;
        tmp2->pre = new_song;
        inserted[k] = true;
    }
    else if (!inserted[k] && ordered[k]) {
        // add to end of inserted
        song *new_song = make_song(k, tmp2->pre, tmp2);
        tmp2->pre->next = new_song;
        tmp2->pre = new_song;
        inserted[k] = true;

        // remove from ordered
        song *tmp = tmp2->next, *next;
        while (tmp != head) {
            if (tmp->num == k) {
                next = tmp->next;
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                delete tmp;
                tmp = next;
            }
            else {
                tmp = tmp->next;
            }
        }
    }
    else {
        // add to front of inserted
        song *new_song = make_song(k, tmp1, tmp1->next);
        tmp1->next->pre = new_song;
        tmp1->next = new_song;

        // remove from inserted and ordered
        song *tmp = new_song->next, *next;
        while (tmp != head) {
            if (tmp->num == k) {
                next = tmp->next;
                tmp->pre->next = tmp->next;
                tmp->next->pre = tmp->pre;
                delete tmp;
                tmp = next;
            }
            else {
                tmp = tmp->next;
            }
        }
    }
}

void ordering_system::destroy() {
    song *tmp = head->next, *next = nullptr;
    while (tmp != head) {
        next = tmp->next;
        delete tmp;
        tmp = next;
    }
    delete head;
}
