#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct BSTNode {
    int val;
    BSTNode *left;
    BSTNode *right;
    BSTNode(int val): val(val), left(nullptr), right(nullptr) {}
};

int N, M, max_level = 0;
int *sum_at_level, *nodes_at_level; // 1-based
BSTNode *root = nullptr;

BSTNode *insert_node(int val, BSTNode *root, int level) {
    if (root == nullptr) {
        sum_at_level[level] += val;
        nodes_at_level[level]++;
        max_level = (level > max_level) ? level : max_level;
        return new BSTNode(val);
    }

    if (val > root->val) {
        root->right = insert_node(val, root->right, level + 1);
    }
    else if (val < root->val) {
        root->left = insert_node(val, root->left, level + 1);
    }
    /// NOTE: repeated values should be ignored according to the problem.
    /// Thus, val == root->val is ignored.

    return root;
}

void print_inorder(BSTNode *root) {
    if (root == nullptr) {
        return;
    }
    print_inorder(root->left);
    cout << root->val << ' ';
    print_inorder(root->right);
}

int comp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main()
{
    cin >> N;
    sum_at_level = new int[N + 1];
    nodes_at_level = new int[N + 1];
    for (int i = 0; i <= N; i++) {
        sum_at_level[i] = nodes_at_level[i] = 0;
    }
    for (int i = 1; i <= N; i++) {
        int val;
        cin >> val;
        root = insert_node(val, root, 1);
    }

    cin >> M;
    while (M--) {
        string command;
        int level;
        cin >> command;
        if (command == "P") {
            if (N <= 0) {
                cout << "NULL" << endl;
            }
            else {
                print_inorder(root);
                cout << endl;
            }
        }
        else if (command == "GetMax") {
            cout << max_level << endl;
        }
        else if (command == "SumLevel") {
            cin >> level;
            if (level <= 0 || level > max_level || N <= 0) {
                cout << 0 << endl;
            }
            else {
                cout << sum_at_level[level] << endl;
            }
        }
        else {
            cin >> level;
            if (level <= 0 || level > max_level || N <= 0) {
                cout << 0 << endl;
            }
            else {
                printf("%.3f\n", (double)sum_at_level[level] / nodes_at_level[level]);
            }
        }
    }
    delete [] sum_at_level;
    delete [] nodes_at_level;
    // delete_tree();
    return 0;
}
