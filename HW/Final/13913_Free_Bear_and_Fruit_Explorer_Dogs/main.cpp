#include <bits/stdc++.h>

using namespace std;

int main()
{
    // read input
    int n, id;
    cin >> n;
    unordered_map<int, int> freq; // id: freq
    set<int> ids;
    for (int i = 0; i < n; i++) {
        cin >> id;
        freq[id]++;
        ids.insert(id);
    }

    // solve
    int teams = 0;
    for (int id : ids) {
        // search until id is used up
        while (freq[id] > 0) {
            int curId = id;
            // find all consecutive sequence starting with id
            while (freq.find(curId + 1) != end(freq) && freq[curId + 1] > 0) {
                freq[curId + 1]--; // update visited id's freq count
                curId++;
            }
            teams++;
            freq[id]--;
        }
        freq.erase(id); // erase searched id
    }

    cout << teams << endl;

    return 0;
}
