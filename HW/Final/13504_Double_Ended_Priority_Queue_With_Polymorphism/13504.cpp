#include "function.h"
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("tune=native")
#pragma message("GL; HF!")
#endif
#if __cpluplus < 201103L
#define nullptr NULL
#endif
using namespace std;

inline void check(bool x)
{
    if (x)
        return;
    cout << "WA\n";
    exit(0);
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    while (cin >> q)
    {
        DEPQ *depq_bst = new DEPQ_BST(), *depq_mmh = new DEPQ_MMH;
        while (q--)
        {
            char c;
            cin >> c;
            switch (c)
            {
            case '0':
            {
                int x;
                cin >> x;
                depq_bst->push(x);
                depq_mmh->push(x);
                break;
            }
            case '1':
                check(depq_bst->empty() == depq_mmh->empty());
                if (depq_mmh->empty())
                    continue;
                check(depq_bst->top() == depq_mmh->top());
                cout << depq_bst->top() << '\n';
                break;
            case '2':
                check(depq_bst->empty() == depq_mmh->empty());
                if (depq_bst->empty())
                    continue;
                check(depq_bst->bottom() == depq_mmh->bottom());
                cout << depq_mmh->bottom() << '\n';
                break;
            case '3':
                check(depq_bst->empty() == depq_mmh->empty());
                if (depq_mmh->empty())
                    continue;
                depq_bst->pop_top();
                depq_mmh->pop_top();
                break;
            case '4':
                check(depq_bst->empty() == depq_mmh->empty());
                if (depq_bst->empty())
                    continue;
                depq_bst->pop_bottom();
                depq_mmh->pop_bottom();
                break;
            case '5':
                check(depq_bst->size() == depq_mmh->size());
                cout << depq_bst->size() << '\n';
            }
        }
        delete depq_bst;
        delete depq_mmh;
    }
    return 0;
}
