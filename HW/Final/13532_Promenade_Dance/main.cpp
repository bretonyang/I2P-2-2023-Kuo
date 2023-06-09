#include <bits/stdc++.h>

using namespace std;

// time complexity: O(N^2)
int LLIS(vector<int> &sequence) {
    vector<int> LLISEndingAt(sequence.size(), 1);

    for (int i = 1; i < sequence.size(); i++) {
        // find max of LLIS ending at j, where j < i and seq[j] < seq[i].
        for (int j = 0; j < i; j++) {
            if (sequence[j] < sequence[i]) {
                LLISEndingAt[i] = max(LLISEndingAt[i], LLISEndingAt[j] + 1);
            }
        }
    }

    return *max_element(begin(LLISEndingAt), end(LLISEndingAt));
}

// time complexity: O(NlogN)
int fasterLLIS(vector<int> &sequence) {
    vector<int> LISBuilder;

    for (int i = 0; i < sequence.size(); i++) {
        if (LISBuilder.empty() || sequence[i] >= LISBuilder.back()) {
            LISBuilder.push_back(sequence[i]);
        }
        else {
            // binary search for smallest VAL s.t. VAL > sequence[i]
            int low = 0, high = LISBuilder.size() - 1;
            while (low < high) {
                int mid = (low + high) / 2;
                if (LISBuilder[mid] < sequence[i]) {
                    low = mid + 1;
                }
                else {
                    high = mid;
                }
            }
            LISBuilder[low] = sequence[i];
        }
    }

    return LISBuilder.size();
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

    cout << fasterLLIS(seq) << endl; // (length of) longest increasing subsequence

    return 0;
}
