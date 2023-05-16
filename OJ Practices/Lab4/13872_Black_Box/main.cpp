#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> freq;

int main()
{
    int command, k, x, N;
    cin >> N;
    while (N--) {
        cin >> command;
        if (command == 1) {
            cin >> k >> x;
            freq[x] += k;
        }
        else if (command == 2) {
            cin >> k >> x;
            freq[x] -= k;
            if (freq[x] <= 0) {
                freq.erase(x);
            }
        }
        else if (command == 3) {
            cin >> x;
            if (freq.find(x) != end(freq))
                cout << freq[x] << endl;
            else
                cout << 0 << endl;
        }
        else if (command == 4) {
            if (freq.empty())
                cout << "The box is empty." << endl;
            else
                cout << (rbegin(freq)->first) << endl;
        }
        else if (command == 5) {
            if (freq.empty())
                cout << "The box is empty." << endl;
            else
                cout << (begin(freq)->first) << endl;
        }
    }

    return 0;
}
