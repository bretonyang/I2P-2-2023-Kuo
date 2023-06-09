#include <iostream>
#include <queue>

using namespace std;

int main()
{
    long long score = 0;
    priority_queue<int> pq;
    int n, card;
    cin >> n;

    while (n--) {
        cin >> card;
        if (card > 0) {
            pq.push(card);
        }
        else if (card == 0 && !pq.empty()) {
            score += (long long) pq.top();
            pq.pop();
        }
    }
    cout << score << endl;

    return 0;
}
