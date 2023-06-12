#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long card;
    unordered_map<long long, long long> freq;
    map<long long, set<long long>> freqToCards;

    while (N--) {
        cin >> card;

        freq[card]++;
        freqToCards[freq[card]].insert(card);

        // Get the set of cards with most frequency
        // Then get the max card in that set
        cout << *(rbegin(rbegin(freqToCards)->second)) << "\n";
    }

    return 0;
}
