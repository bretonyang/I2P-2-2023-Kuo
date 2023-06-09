#include <bits/stdc++.h>

#define INF 1000000005

using namespace std;

/**

nums: INF 9 7 9 2 4 5 8 9
ans:      0 1 0 3 3 3 3 0

For each nums[i], we want to find the smallest value > nums[i] that is on the left of nums[i]

Algo:
- create empty stack
- Loop BACKWARDS:
    - push nums[i] into stack
    - all consecutive items from the top of the stack that are < nums[i] have `i` as their answer.

*/
int main()
{
    // read input
    int N;
    cin >> N;
    vector<int> nums;
    nums.push_back(INF);
    for (int i = 1; i <= N; i++) {
        int tmp;
        cin >> tmp;
        nums.push_back(tmp);
    }

    // SOLVE: O(N) solution
    vector<int> ans(N + 1);
    stack<int> st; // stores i instead of num[i]
    for (int i = N; i > 0; i--) {
        st.push(i);
        while (!st.empty() && nums[i - 1] > nums[st.top()]) {
            ans[st.top()] = i - 1;
            st.pop();
        }
    }

    // Print solution
    for (int i = 1; i <= N; i++)
        cout << ans[i] << ' ';
    cout << endl;

    return 0;
}


//int main()
//{
//    int N;
//    cin >> N;
//
//    vector<int> answer;
//    vector<int> nums;
//    nums.push_back(INF);
//    for (int i = 1; i <= N; i++) {
//        int val;
//        cin >> val;
//        nums.push_back(val);
//    }
//
//    // SOLVE: slower than O(N) solution
//    answer.push_back(0);
//    for (int i = 1; i <= N; i++) {
//        if (nums[i - 1] > nums[i]) {
//            answer.push_back(i - 1);
//        }
//        else if (nums[i - 1] == nums[i]) {
//            answer.push_back(answer[i - 1]);
//        }
//        else {
//            int cur = answer[i - 1];
//            while (nums[cur] <= nums[i]) {
//                cur = answer[cur];
//            }
//            answer.push_back(cur);
//        }
//    }
//
//    for (int i = 1; i <= N; i++) {
//        cout << answer[i] << ' ';
//    }
//    cout << endl;
//
//    return 0;
//}
