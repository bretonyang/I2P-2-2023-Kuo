#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    multiset<int> mulset;
    string command;
    while (cin >> command) {
        if (command == "Insert") {
            int x;
            cin >> x;
            mulset.insert(x);
        }
        else if (command == "Query") {
            int x, k;
            cin >> x >> k;
            multiset<int>::iterator it = mulset.lower_bound(x);
            while (k > 1 && it != end(mulset)) {
                ++it;
                --k;
            }
            if (k > 1)
                cout << -1 << endl;
            else {
                if (it == end(mulset)) {
                    cout << -1 << endl;
                }
                else {
                    cout << *it << endl;
                }

            }
        }
    }

    return 0;
}
