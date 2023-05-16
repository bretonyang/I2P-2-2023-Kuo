#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> freq;

int main()
{
    string command;
    int x, k;
    while (cin >> command) {
        if (command == "Insert") {
            cin >> x;
            freq[x]++;
        }
        else if (command == "Query") {
            cin >> x >> k;
            int ans;
            bool found = false;
            for (auto it = freq.lower_bound(x); it != end(freq); it++) {
                int num = it->first;
                if (k <= freq[num]) {
                    found = true;
                    ans = num;
                    break;
                }
                k -= freq[num];
            }
            if (found)
                cout << ans << endl;
            else
                cout << -1 << endl;
        }
    }

    return 0;
}
