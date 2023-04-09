#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *prev;
    Node *next;

    // list initialization
    Node(int data): data(data), prev(nullptr), next(nullptr) {}
};

Node* build_list(int N, string &str, Node *sentinel) {
    Node *cur = new Node(0);
    cur->next = cur;
    cur->prev = cur;
    sentinel->next = cur; // sentinel->next is always the head of list

    for (int i = 1; i <= N; i++) {
        Node *new_node = new Node(i);
        if (str[i - 1] == 'L') { // left of cur
            new_node->next = cur;
            new_node->prev = cur->prev;
            cur->prev->next = new_node;
            cur->prev = new_node;
            // Updates the head (only when inserting at left)
            if (new_node->next == sentinel->next) {
                sentinel->next = new_node;
            }
        }
        else { // right of cur
            new_node->prev = cur;
            new_node->next = cur->next;
            cur->next->prev = new_node;
            cur->next = new_node;
        }
        cur = new_node;
    }
}

void print_list(Node* head) {
    Node* tail = head->prev;
    while (head != tail) {
        cout << head->data << ' ';
        head = head->next;
    }
    cout << tail->data << ' ' << endl;
}

void delete_list(Node* head) {
    Node* tail = head->prev;
    while (head != tail) {
        Node *tmp = head->next;
        delete head;
        head = tmp;
    }
    delete tail;
}

int main()
{
    int T, N;
    string S;
    cin >> T;
    Node* sentinel = new Node(-1);
    while (T--) {
        cin >> N >> S;
        sentinel->next = nullptr;
        build_list(N, S, sentinel);
        print_list(sentinel->next);
        delete_list(sentinel->next);
    }
    delete sentinel;

    return 0;
}
