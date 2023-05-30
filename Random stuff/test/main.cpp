#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <cmath>
#include <algorithm>

using namespace std;

/* Helper code */

template <class T>
void print_sequence(T seq) {
    for (auto i : seq)
        cout << i << ' ';
    cout << endl;
}


/* Testing code */

class Node {
public:
    int val;
    Node(int val) : val(val) {}
};

ostream& operator<<(ostream &out, const Node &n) {
    return out << n.val;
}

void test(vector<Node> &seq) {
    seq.push_back(Node(-1));
}


int main()
{
    list<vector<int>> l1;
    list<vector<int>> l2;
    vector<int>v1{1, 2, 3};
    l1.push_back(v1);
    l2.push_back(v1);
    vector<int>v2{2, 3};
    l1.push_back(v2);
    l2.push_back(v2);
    vector<int>v3{5};
    vector<int>v4{5};
    l1.push_back(v3);
    l2.push_back(v4);

    cout << (l1 == l2) << endl;

    return 0;
}
