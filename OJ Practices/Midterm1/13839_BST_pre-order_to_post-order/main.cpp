#include <iostream>
#include <stack>

#define INF 1000000005

using namespace std;

int N;
int preorder[1000500]; // limit: 1e6
int right_child[1000500];

void compute_right_child() {
    stack<int> node_stack;
    preorder[N] = INF; // to set last position to N
    for (int i = 0; i < N; i++) {
        node_stack.push(i);
        while (!node_stack.empty() && preorder[node_stack.top()] < preorder[i + 1]) {
            int idx = node_stack.top();
            node_stack.pop();
            right_child[idx] = i + 1;
        }
    }
}

void print_postorder(int start, int end) {
    if (start > end)
        return;

    int right = right_child[start];
    print_postorder(start + 1, right - 1);
    print_postorder(right, end);
    cout << preorder[start] << ' ';
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> preorder[i];
    compute_right_child();
    print_postorder(0, N - 1);

    return 0;
}
/**
     0  1  2  3  4  5  6
pre: 5  4  1  2  7  6  9
     4  4  3  4  6  6  7

        5
       / \
      4   7
     /   / \
    1   6   9
     \
      2

post: 2 1 4 6 9 7 5

*/
