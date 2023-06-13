#include <bits/stdc++.h>

using namespace std;

int maxWeightIncreasingSubseq(vector<int>& seq, vector<int> &weights) {
    int N = seq.size();
    vector<int> subseq;
    vector<int> indexOfSubseq;
    vector<int> trace(N, -1);
    vector<int> sumOverTrace(N);

    // init sumOverTrace
    for (int i = 0; i < N; i++) sumOverTrace[i] = weights[i];

    for (int i = 0; i < N; i++) {
        if (subseq.empty() || seq[i] > subseq.back()) {
            if (!subseq.empty()) {
                trace[i] = indexOfSubseq.back();
                sumOverTrace[i] = max(sumOverTrace[trace[i]] + weights[i], sumOverTrace[i]);
                sumOverTrace[i] = max(sumOverTrace[trace[i]], sumOverTrace[i]);
            }
            subseq.push_back(seq[i]);
            indexOfSubseq.push_back(i);
        }
        else {
            int idx = lower_bound(begin(subseq), end(subseq), seq[i]) - begin(subseq);
            if (idx > 0) {
                trace[i] = indexOfSubseq[idx - 1];
                sumOverTrace[i] = max(sumOverTrace[trace[i]] + weights[i], sumOverTrace[i]);
                sumOverTrace[i] = max(sumOverTrace[trace[i]], sumOverTrace[i]);
            }
            subseq[idx] = seq[i];
            indexOfSubseq[idx] = i;
        }
    }

    return *max_element(begin(sumOverTrace), end(sumOverTrace));
}

int main()
{
    int N;
    string name;
    cin >> N;
    unordered_map<string, int> indexOfName;
    vector<int> seq(N);
    vector<int> weights(N);

    for (int i = 0; i < N; i++) {
        cin >> name;
        indexOfName[name] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> name;
        seq[i] = indexOfName[name] + 1; // change to 1-based
    }
    for (int i = 0; i < N; i++)
        cin >> weights[i];

    cout << maxWeightIncreasingSubseq(seq, weights) << endl;

    return 0;
}
