#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

unordered_map<int, int> freq;
set<int> numbers;

int main()
{
    int N;
    cin >> N;
    while (N--) {
        int q;
        cin >> q;
        if (q == 1) {
            int k, x;
            cin >> k >> x;
            numbers.insert(x);
            freq[x] += k;
        }
        else if (q == 2) {
            int k, x;
            cin >> k >> x;
            freq[x] -= k;
            if (freq[x] <= 0) {
                freq[x] = 0;
                numbers.erase(x);
            }
        }
        else if (q == 3) {
            int x;
            cin >> x;
            cout << freq[x] << endl;
            // if x not in map, added to map, and default init value (0).
        }
        else if (q == 4) {
            if (numbers.empty()) {
                cout << "The box is empty." << endl;
            }
            else {
                cout << *rbegin(numbers) << endl;
            }
        }
        else if (q == 5) {
            if (numbers.empty()) {
                cout << "The box is empty." << endl;
            }
            else {
                cout << *begin(numbers) << endl;
            }
        }
    }

    return 0;
}
