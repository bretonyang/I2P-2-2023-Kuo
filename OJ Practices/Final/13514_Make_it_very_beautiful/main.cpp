#include <bits/stdc++.h>

using namespace std;

// imagine we have a moving window
void solve(vector<int> sequence, int Q) {
    int L, R; // guaranteed to be increasing
    unordered_map<int, int> freq;
    int left = 1, right = 1;
    int ans = 0;
    while (Q--) {
//        scanf("%d %d", &L, &R);
        cin >> L >> R;

        // move right to position R
        while (right <= R) {
            int val = sequence[right];
            if (freq[val] == 0) { // no count in window
                freq[val]++;
            }
            else if (freq[val] > 0) { // already in window, duplicate
                freq[val]++;
                ans++;
            }
            right++;
        }

        // move left to position L
        while (left < L) {
            int val = sequence[left];
            if (freq[val] == 1) {
                freq[val]--;
            }
            else if (freq[val] > 1) {
                freq[val]--;
                ans--;
            }
            left++;
        }

//        printf("%d\n", ans);
        cout << ans << "\n";
    }
}

int main()
{
    /// NOTE: if use these, don't use std::endl !!!
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    /// NOTE: have to use scanf/printf to avoid TLE
    /// basically cin/cout is too slow!!
    int T;
//    scanf("%d", &T);
    cin >> T;
    while (T--) {
        int N, Q;
//        scanf("%d %d", &N, &Q);
        cin >> N >> Q;
        vector<int> sequence(N + 1);
        for (int i = 1; i <= N; i++)
//            scanf("%d", &sequence[i]);
            cin >> sequence[i];
        solve(sequence, Q);
//        printf("\n");
        cout << "\n";
    }

    return 0;
}
