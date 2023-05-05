struct Node{
    Node *prev;
    Node *next;
    int val;
    int tag;
};

class KuoYangPresent {
public:
	KuoYangPresent(int k);
	void Push(int x);
	void Pop();
	void Reverse();
	void ProgrammingTanoshi();
	void KuoYangTeTe();
	void PrintList();

private:
	Node *head, *mid, *tail; // use head as a sentinel
	int sz, k;
	int now; // count of how many modulations
	bool reverse;
};

