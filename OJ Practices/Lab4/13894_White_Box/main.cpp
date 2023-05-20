#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

map<int, int> num_to_freq; // maps one number to a frequency
map<int, set<int>> freq_to_nums; // maps a frequncy to a set of numbers

int main() {
    int N;
    cin >> N;
    while (N--) {
        int op;
        cin >> op;

        if (op == 1) {
            int k, x;
            cin >> k >> x;
            // if x was in the box
            if (num_to_freq.find(x) != end(num_to_freq)) {
                // remove the old freq-num pair
                int cnt = num_to_freq[x];
                set<int> &tmp_nums = freq_to_nums[cnt];
                tmp_nums.erase(x);

                // if set of nums is empty, remove this frequency from the map
                if (tmp_nums.empty()) {
                    freq_to_nums.erase(cnt);
                }
            }
            num_to_freq[x] += k;
            freq_to_nums[num_to_freq[x]].insert(x);
        } else if (op == 2) {
            int k, x;
            cin >> k >> x;
            // if x is still in the box
            if (num_to_freq.find(x) != end(num_to_freq)) {
                // remove the old freq-num pair
                int cnt = num_to_freq[x];
                set<int> &tmp_nums = freq_to_nums[cnt];
                tmp_nums.erase(x);

                // if set of nums is empty, remove this frequency from the map
                if (tmp_nums.empty()) {
                    freq_to_nums.erase(cnt);
                }

                if (cnt <= k) {
                    num_to_freq.erase(x);
                } else {
                    num_to_freq[x] -= k;
                    freq_to_nums[num_to_freq[x]].insert(x);
                }
            }
        } else if (op == 3) {
            int x;
            cin >> x;
            if (num_to_freq.find(x) != end(num_to_freq))
                cout << num_to_freq[x] << endl;
            else
                cout << 0 << endl;
        } else if (op == 4) {
            if (num_to_freq.empty())
                cout << "The box is empty." << endl;
            else
                cout << (rbegin(num_to_freq)->first) << endl;
        } else if (op == 5) {
            if (num_to_freq.empty())
                cout << "The box is empty." << endl;
            else
                cout << (begin(num_to_freq)->first) << endl;
        } else if (op == 6) {
            if (freq_to_nums.empty())
                cout << "The box is empty." << endl;
            else {
                // iterator the the element with the most frequency
                auto it = rbegin(freq_to_nums);
                int tmp_f = it->first; // the max frequency
                int tmp_n = *(rbegin(it->second)); // last element in the set
                cout << tmp_n << " " << tmp_f << endl;
            }
        }
    }

    return 0;
}
