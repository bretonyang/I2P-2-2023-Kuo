#include <bits/stdc++.h>

using namespace std;

vector<int> pathOfLIS(vector<int>& seq) {
    vector<int> subseq;
    vector<int> indexOfSubseq;
    vector<int> edgeTo(seq.size(), -1);

    for (int i = 0; i < seq.size(); i++) {
        if (subseq.empty() || seq[i] > subseq.back()) {
            if (!subseq.empty())
                edgeTo[i] = indexOfSubseq.back();
            subseq.push_back(seq[i]);
            indexOfSubseq.push_back(i);
        }
        else {
            int idx = lower_bound(begin(subseq), end(subseq), seq[i]) - begin(subseq);
            if (idx > 0)
                edgeTo[i] = indexOfSubseq[idx - 1];
            subseq[idx] = seq[i];
            indexOfSubseq[idx] = i;
        }
    }

    // follow the edgeTo to get back the LIS
    vector<int> path;
    int tmp = indexOfSubseq.back();
    while (tmp != -1) {
        path.push_back(seq[tmp]);
        tmp = edgeTo[tmp];
    }
    reverse(begin(path), end(path));

    return path;
}

int main()
{
    int N;
    cin >> N;
    vector<int> seq(N);
    for (int i = 0; i < N; i++)
        cin >> seq[i];

    vector<int> LIS = pathOfLIS(seq);
    cout << LIS.size() << endl;

    return 0;
}
