#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data) {
        this->data = data;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

void solve(int N, string &str) {

}

int main()
{
    int T, N;
    string S;
    cin >> T;
    while (T--) {
        cin >> N >> S;
        solve(N, S);
    }

    return 0;
}
