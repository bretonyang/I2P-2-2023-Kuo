#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;
    Node *prev;
    Node(int val): val(val), next(nullptr), prev(nullptr) {}
};

Node *front_sentinel, *tail_sentinel;

void init() {
    front_sentinel = new Node(-1);
    tail_sentinel = new Node(-1);
    Node *head = new Node(0);
    front_sentinel->next = head;
    tail_sentinel->prev = head;
    head->prev = front_sentinel;
    head->next = tail_sentinel;
}

void solve(int N, const string &str) {
    Node *cur = front_sentinel->next;
    for (int i = 1; i <= N; i++) {
        Node *new_node = new Node(i);
        if (str[i - 1] == 'L') {
            new_node->prev = cur->prev;
            new_node->next = cur;
            cur->prev->next = new_node;
            cur->prev = new_node;
        }
        else if (str[i - 1] == 'R') {
            new_node->next = cur->next;
            new_node->prev = cur;
            cur->next->prev = new_node;
            cur->next = new_node;
        }
        else if (str[i - 1] == 'F') {
            new_node->next = front_sentinel->next;
            new_node->prev = front_sentinel;
            front_sentinel->next->prev = new_node;
            front_sentinel->next = new_node;
        }
        else {
            new_node->prev = tail_sentinel->prev;
            new_node->next = tail_sentinel;
            tail_sentinel->prev->next = new_node;
            tail_sentinel->prev = new_node;
        }
        cur = new_node;
    }
    // print list
    Node *tmp = front_sentinel->next;
    while (tmp != tail_sentinel) {
        cout << tmp->val << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

void free_list() {
    Node *tmp = front_sentinel;
    while (tmp != nullptr) {
        Node *next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        init();
        string str;
        cin >> str;
        solve(N, str);
        free_list();
    }

    return 0;
}
