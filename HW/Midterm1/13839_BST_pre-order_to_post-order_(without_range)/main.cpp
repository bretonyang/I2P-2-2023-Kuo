#include <iostream>
#define INF 1000000005

using namespace std;

int preorder[1001000], right_child[1001000], parent_stack[1001000]; // wtf, actual limit: 1e6
// For the sample input, right_child[] is:  4, 4, 3, 4, 6, 6, 6

void postorder(int low, int high) {
    if (low > high) return;

    if (low < high) {
        postorder(low + 1, right_child[low] - 1);
        postorder(right_child[low], high);
    }
    cout << preorder[low] << ' '; // i.e., if low <= high
}

void fill_right_child(int N) {
    int stack_size = 0;
    preorder[N] = INF;
    for (int i = 0; i < N; i++) {
        parent_stack[stack_size++] = i;
        while (stack_size > 0 && preorder[i + 1] > preorder[parent_stack[stack_size - 1]]) {
            right_child[parent_stack[stack_size - 1]] = i + 1;
            stack_size--;
        }
    }
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> preorder[i];

    fill_right_child(N);
    postorder(0, N - 1);

    return 0;
}
