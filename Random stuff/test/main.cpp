#include <bits/stdc++.h>

using namespace std;

vector<int> pathOfLIS(vector<int>& nums) {
    vector<int> sub, subIndex; // Store index instead of value for tracing path purpose
    vector<int> trace(nums.size(), -1); // trace[i] point to the index of previous number in LIS

    for (int i = 0; i < nums.size(); ++i) {
        if (sub.empty() || nums[i] > sub.back()) {
            if (!sub.empty())
                trace[i] = subIndex.back();
            sub.push_back(nums[i]);
            subIndex.push_back(i);
        }
        else {
            int idx = lower_bound(begin(sub), end(sub), nums[i]) - begin(sub);
            if (idx > 0)
                trace[i] = subIndex[idx - 1];
            sub[idx] = nums[i];
            subIndex[idx] = i;
        }
    }

    vector<int> path;
    int t = subIndex.back();

    while (t != -1) {
        path.push_back(nums[t]);
        t = trace[t];
    }
    reverse(begin(path), end(path));

    return path;
}

int main() {
    vector<int> nums = {2, 6, 8, 3, 4, 5, 1};
    vector<int> res = pathOfLIS(nums); // [2, 3, 4, 5]
    for (int x : res)
        cout << x << " ";
    return 0;
}
