#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>

/// #include <bits/stdc++.h>
/// This includes all header files for c++

using namespace std;

int comp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main()
{
    /// sort()
    int arr[] = {1, 3, 5, 2, 4};
//    sort(arr, arr + 5);
    qsort(arr, 5, sizeof(int), comp);
    for (auto val : arr)
        cout << val << ' ';
    cout << endl;

    /// vector
    vector<int> vec;
    cout << vec.size() << ' ' << vec.empty() << endl;

    for (int i = 0; i < 5; i++) {
        vec.push_back(i);
    }
    cout << vec.size() << endl;
    int a = vec.front();
    int b = vec.back();
    cout << a << ' ' << b << endl;
    vec.pop_back();
    for (auto item : vec) {
        cout << item << ' ';
    }
    cout << endl;

    /// queue
    queue<int> q;
    for (int i = 0; i < 5; i++)
        q.push(i);
    cout << q.size() << endl;
    // no iterator for queue<>
    while (!q.empty()) {
        cout << q.front() << ' ';
        q.pop();
    }
    cout << endl;
    cout << q.size() << endl;


    return 0;
}
