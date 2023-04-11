#include <iostream>
#include <cstdlib>

using namespace std;

int friends[1000000];

int comp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> friends[i];
    qsort(friends, N, sizeof(int), comp);
    int home = friends[(N - 1) / 2];
    long long D = 0;
    for (int i = 0; i < N; i++) {
        D += abs(home - friends[i]);
    }
    cout << home << ' ' << D << endl;

    return 0;
}

/**

0 1 2 3

*/
