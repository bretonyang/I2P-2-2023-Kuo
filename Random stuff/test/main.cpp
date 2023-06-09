#include <iostream>

using namespace std;

class base {
public:
    virtual void print() {
        cout << "base" << endl;
    }
};

class deri1 : public base {
public:
    void print() {
        cout << "deri1" << endl;
    }
};

class deri2 : public deri1 {
public:
    void print() {
        cout << "deri2" << endl;
    }
};

int main()
{
    base *p = new deri2();
    ((deri1*)p)->print();

    return 0;
}
