#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> findMaxWeightIncreasingSubsequence(const vector<int>& seq, const vector<int>& weight) {
    int N = seq.size();
    vector<int> dp(N, 1);
    vector<int> weights = weight;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (seq[i] > seq[j] && weights[i] + weights[j] > weights[i]) {
                dp[i] = dp[j] + 1;
                weights[i] = weights[i] + weights[j];
            }
        }
    }

    int maxLength = *max_element(dp.begin(), dp.end());
    int maxWeight = 0;
    int maxWeightIdx = -1;

    for (int i = 0; i < N; i++) {
        if (dp[i] == maxLength && weights[i] > maxWeight) {
            maxWeight = weights[i];
            maxWeightIdx = i;
        }
    }

    return make_pair(maxWeight, maxWeightIdx);
}

int main() {
    vector<int> seq = {1, 6, 2, 3, 5, 4};
    vector<int> weight = {1, 9, 3, 3, 1, 1};

    pair<int, int> result = findMaxWeightIncreasingSubsequence(seq, weight);
    int maxWeight = result.first;
    int maxWeightIdx = result.second;

    cout << "Maximum weight increasing sequence: ";
    for (int i = 0; i <= maxWeightIdx; i++) {
        if (weight[i] < weight[maxWeightIdx] && seq[i] < seq[maxWeightIdx]) {
            cout << seq[i] << " ";
        }
    }
    cout << seq[maxWeightIdx] << endl;

    cout << "Maximum weight: " << maxWeight << endl;

    return 0;
}
