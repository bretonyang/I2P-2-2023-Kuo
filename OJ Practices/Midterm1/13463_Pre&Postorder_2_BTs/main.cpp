#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
int n;
int pre[MAXN], post[MAXN];
long long dp[MAXN][MAXN];

int find(int x) {
    for (int i = n - 1; i >= 0; i--) {
        if (post[i] == x) {
            return i;
        }
    }
    return -1;
}

long long solve(int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    if (l >= r) {
        return 1;
    }
    int cnt = find(pre[l + 1]);
    long long ans = 0;
    for (int i = l + 1; i < r; i++) {
        if (find(pre[i]) == cnt - 1) {
            ans += solve(l + 1, i) * solve(i + 1, r - 1);
        }
    }
    return dp[l][r] = ans;
}


int main() {
    memset(dp, -1, sizeof(dp));
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> post[i];
    }
    cout << solve(0, n - 1) << endl;
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
