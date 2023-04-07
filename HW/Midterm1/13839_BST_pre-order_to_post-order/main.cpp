#include <iostream>

#define INF 1000000005

using namespace std;

int N, pre_idx = 0;
int preorder[1001000]; /// wtf, actual limit: 1e6

void postorder(int range_min, int range_max) {
    if (pre_idx >= N) return;

    int cur = preorder[pre_idx];
    if (cur < range_min || cur > range_max) return;

    pre_idx++;
    postorder(range_min, cur);
    postorder(cur, range_max);
    cout << cur << ' ';
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> preorder[i];
    }

    postorder(0, INF);

    return 0;
}

/**

10
5 3 1 4 8 7 6 12 9 10

*/


