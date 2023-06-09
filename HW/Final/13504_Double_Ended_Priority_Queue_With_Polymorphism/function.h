#include <algorithm>
#include <set>
#include <vector>

/**
 * TODO: Create a cpp and implement the 7 public functions for both DEPQ_BST and DEPQ_MMH.

void DEPQ_BST::push(int x) { ... }
int DEPQ_BST::top() const { ... }
int DEPQ_BST::bottom() const { ... }
void DEPQ_BST::pop_top() { ... }
void DEPQ_BST::pop_bottom() { ... }
int DEPQ_BST::size() const { ... }
bool DEPQ_BST::empty() const { ... }

void DEPQ_MMH::push(int x) { ... }
int DEPQ_MMH::top() const { ... }
int DEPQ_MMH::bottom() const { ... }
void DEPQ_MMH::pop_top() { ... }
void DEPQ_MMH::pop_bottom() { ... }
int DEPQ_MMH::size() const { ... }
bool DEPQ_MMH::empty() const { ... }

 * You can ignore or revel in the detail of the min-max heap.
 */

class DEPQ // the base of our Double-Ended Priority Queue
{
public:
    virtual void push(int) = 0;     // Push an element into the DEPQ.
    virtual int top() const = 0;    // Get the minimum element in the DEPQ.
    virtual int bottom() const = 0; // Get the maximum element in the DEPQ.
    virtual void pop_top() = 0;     // Pop the minimum element in the DEPQ.
    virtual void pop_bottom() = 0;  // Pop the maximum element in the DEPQ.
    virtual int size() const = 0;   // Return the size of the DEPQ.
    virtual bool empty() const = 0; // Return whther the DEPQ is empty.
};

using std::multiset;
class DEPQ_BST : public DEPQ // DEPQ implemented by BST
{
private:
    multiset<int> bst;

public:
    void push(int);     // Push an element into the DEPQ.
    int top() const;    // Get the minimum element in the DEPQ.
    int bottom() const; // Get the maximum element in the DEPQ.
    void pop_top();     // Pop the minimum element in the DEPQ.
    void pop_bottom();  // Pop the maximum element in the DEPQ.
    int size() const;   // Return the size of the DEPQ.
    bool empty() const; // Return whther the DEPQ is empty.
};

using std::vector, std::swap, std::min, std::__lg;
class min_max_heap // It have been done for you, feel free to use its public function!
{
public:
    inline bool empty() const { return v.empty(); } // Determine whether the DEPQ is empty.
    inline int size() const { return v.size(); }    // Return the size of DEPQ.
    void push(int x)                                // Push the element into DEPQ.
    {
        v.push_back(x);
        bubble_up(size() - 1);
    }
    inline int get_min() const { return v.front(); }     // Return the minimum element.
    inline int get_max() const { return v[find_max()]; } // Return the maximum element.
    inline void pop_min() { erase(0); }                  // Pop the minimum element.
    inline void pop_max() { erase(find_max()); }         // Pop the maximum element.

private:
    vector<int> v;           // Base container
    void trickle_down(int x) // The helper function used when poped
    {
        bool is_min = ~__lg(x + 1) & 1;
        while (x + 1 << 1 <= v.size())
        {
            int m = get(x, is_min);
            if (is_min ? v[m] < v[x] : v[m] > v[x])
            {
                swap(v[m], v[x]);
                if (m <= x + 1 << 1)
                    return;
                if (is_min ? v[(m + 1 >> 1) - 1] < v[m] : v[(m + 1 >> 1) - 1] > v[m])
                    swap(v[(m + 1 >> 1) - 1], v[m]);
                x = m;
            }
            else
                return;
        }
    }
    int get(int x, bool is_min) // Get the descendent of `x`.
    {
        int y = (++x << 1) - 1;
        for (int i = 2; i <= 4; i <<= 1)
            for (int j = 0; j < i; j++)
            {
                int tmp = x * i + j - 1;
                if (tmp >= v.size())
                    return y;
                if (is_min ? v[y] > v[tmp] : v[y] < v[tmp])
                    y = tmp;
            }
        return y;
    }
    void bubble_up(int x) // The helper function used when pushed
    {
        if (!x)
            return;
        int p = (x + 1 >> 1) - 1;
        bool is_min = ~__lg(x + 1) & 1;
        if (is_min ? v[p] < v[x] : v[p] > v[x])
        {
            swap(v[p], v[x]);
            bubble_up(p, !is_min);
        }
        else
            bubble_up(x, is_min);
    }
    void bubble_up(int x, bool is_min) // The helper function used when pushed
    {
        while (x > 2)
        {
            int gp = (x + 1 >> 2) - 1;
            if (is_min ? v[x] < v[gp] : v[x] > v[gp])
            {
                swap(v[x], v[gp]);
                x = gp;
            }
            else
                break;
        }
    }
    int find_max() const // Return the index of the maximum element.
    {
        int y = 0;
        for (int i = min(2, int(v.size()) - 1); i; i--)
            if (v[y] < v[i])
                y = i;
        return y;
    }
    void erase(int x) // Erase the element whose index is `x`.
    {
        v[x] = v.back();
        v.pop_back();
        trickle_down(x);
    }
};

class DEPQ_MMH : public DEPQ // DEPQ implemented by min-max heap
{
private:
    min_max_heap mmh;

public:
    void push(int);     // Push an element into the DEPQ.
    int top() const;    // Get the minimum element in the DEPQ.
    int bottom() const; // Get the maximum element in the DEPQ.
    void pop_top();     // Pop the minimum element in the DEPQ.
    void pop_bottom();  // Pop the maximum element in the DEPQ.
    int size() const;   // Return the size of the DEPQ.
    bool empty() const; // Return whther the DEPQ is empty.
};
