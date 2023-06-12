#include <iostream>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, L;
    cin >> N >> L;

    deque<int> dq;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;

        // Remove elements from the front of the deque if they are out of the current window
        if (!dq.empty() && dq.front() <= i - L)
            dq.pop_front();

        // Remove elements from the back of the deque if they are smaller than the current element
        while (!dq.empty() && num > dq.back())
            dq.pop_back();

        dq.push_back(num);

        // Print the maximum value in the current window
        if (i >= L - 1)
            cout << dq.front() << " ";
    }

    cout << endl;

    return 0;
}
