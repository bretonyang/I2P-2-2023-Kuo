#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> &sequence, long long targetSum) {
    // Records how many times a certain "prefixSum" has appeared before
    unordered_map<long long, int> prefixSumCount;
    long long prefixSum = 0;
    int solutions = 0;

    for (int i = 0; i < sequence.size(); i++) {
        prefixSum += (long long) sequence[i];
        prefixSumCount[prefixSum]++;

        if (prefixSum == targetSum)
            solutions++;

        // check if there are some prefix sum(s) encountered before that would yield the target
        // sum when subtracted from the current prefix sum
        if (prefixSumCount.find(prefixSum - targetSum) != end(prefixSumCount))
            solutions += prefixSumCount[prefixSum - targetSum];
    }

    return solutions;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<int> sequence(N);
        for (int i = 0; i < N; i++)
            cin >> sequence[i];

        int num = solve(sequence, K);
        cout << num << endl;
    }

    return 0;
}
