#include <iostream>
#include <cstring>
#include "function.h"

using namespace std;

// construct a new Str by linked list of Char
Str::Str(char* text) : Str() {
    int len = strlen(text);
    if (len != 0) {
        head = new Char(text[0]);
        Char *tmp = head;
        for (int i = 1; i < len; i++) {
            Char *new_char = new Char(text[i]);
            tmp->next = new_char;
            tmp = tmp->next;
        }
        tail = tmp;
    }
}

// copy constructor
Str::Str(const Str &udda_str) : Str() {
    if (udda_str.head) {
        head = new Char(udda_str.head->text);
        Char *udda_tmp = udda_str.head->next;
        Char *tmp = head;
        while (udda_tmp) {
            Char *new_char = new Char(udda_tmp->text);
            tmp->next = new_char;
            tmp = tmp->next;
            udda_tmp = udda_tmp->next;
        }
        tail = tmp;
    }
}

Str& Str::strInsert(const Str &udda_str) {
    Char *udda_tmp = udda_str.head;
    Char *tmp = tail;
    while (udda_tmp) {
        Char *new_char = new Char(udda_tmp->text);
        tmp->next = new_char;
        tmp = tmp->next;
        udda_tmp = udda_tmp->next;
    }
    tail = tmp;

    return *this;
}










