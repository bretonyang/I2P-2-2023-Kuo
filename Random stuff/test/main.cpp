#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
using dict = map<string, int, less<string>>;

template<typename T> void print(T iterable);
bool cmp(int a, int b);


int main()
{
    array<int, 8> arr = {1, 4, 2, 6, 9, 0, 23, 7};
    print(arr);

    sort(begin(arr), end(arr), greater<int>());
//    sort(arr.begin(), arr.end(), cmp);

    print(arr);

    return 0;
}

bool cmp(int a, int b) {
    return a > b;
}

template<typename T>
void print(T iterable) {
    for (auto v : iterable)
        cout << v << ' ';
    cout << endl;
}
