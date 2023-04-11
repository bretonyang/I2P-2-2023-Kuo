#include <iostream>
using namespace std;

const int MAXN = 30;

int N;
int preorder[MAXN], postorder[MAXN];
int dp[MAXN][MAXN];

int count(int i, int j) {
    if (dp[i][j] > 0) {
        return dp[i][j];
    }
    if (i >= j) {
        return 1;
    }
    int k = i + 1;
    while (k < N && postorder[k - 1] != preorder[i + 1]) {
        k++;
    }
    int res = 0;
    for (int x = i + 1; x <= k; x++) {
        for (int y = k; y < j; y++) {
            res += count(x, y) * count(y + 1, j);
        }
    }
    dp[i][j] = res;
    return res;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> preorder[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> postorder[i];
    }
    cout << count(0, N) << endl;
    return 0;
}



/**

pre:  1 2
post: 2 1

pre:  1 2 3
post: 3 2 1
=> 1 is the root
=> 2 3, 3 2: only 2 nodes => only one permutation
Does 1 have 1 or 2 chilren?
=> since preorder and postorder are opposite
=> so 1 have 1 child


With 1 the root.
1.
pre:  1
post: 1

    1


2.
pre:  1 2
post: 2 1

      1
     /
    2


3.
pre:  1 2 3
post: 2 3 1

       1
      / \
     2   3

pre: 1 2 3
post: 3 2 1


       1      1       1       1
      /      /         \       \
     2      2           2       2
    /        \         /         \
   3          3       3           3


4.
pre:  1 2 3 4
post: 4 3 2 1


*/
