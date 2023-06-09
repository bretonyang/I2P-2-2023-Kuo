#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> &nums) {
    int maxlen = 0;
    int L = 0;
    unordered_set<int> seq_set;

    for (int R = 0; R < nums.size(); R++) {
        // erase old nums[L] until duplicate nums[R] is removed
        while (seq_set.find(nums[R]) != end(seq_set)) {
            seq_set.erase(nums[L]);
            L++;
        }
        seq_set.insert(nums[R]);
        maxlen = max(maxlen, (int)seq_set.size()); // same as max(maxlen, R - L + 1)
    }

    return maxlen;
}

int main()
{
    /// Some weird trick that might speed up performance
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        vector<int> nums(N);
        for (int i = 0; i < N; i++)
            cin >> nums[i];

        int maxlen = solve(nums);
        cout << maxlen << endl;
    }

    return 0;
}
