#include <bits/stdc++.h>

using namespace std;

/**

1 2 1 1 3 2 2 1

1 2 2 2 3 3 3 3

*/

long long solve(vector<int> &seq) {
    int N = seq.size();
    long long ans = 0;
    long long current_max = seq[0];

    for (int i = 0; i < N; i++) {
        current_max = (long long) max(current_max, (long long) seq[i]);
        ans += current_max * (i + 1);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> seq(N);
    for (int i = 0; i < N; i++)
        cin >> seq[i];

    cout << solve(seq) << "\n";

    return 0;
}
