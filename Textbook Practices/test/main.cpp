#include <iostream>
#include <string>

#include "function.h"

using namespace std;

class Array {
friend ostream &operator<<(ostream &out, const Array &arr);

public:
    Array() = default;

private:
    int data[10] = {0};
};

ostream &operator<<(ostream &out, const Array &arr) {
    for (auto val : arr.data) {
        out << val << ' ';
    }
    return out;
}

bool operator!(const string &str) {
    return (str == "") ? true : false;
}

class Base {
public:
    int pub = 1;
    int getPVT() { return pvt; }
protected:
    int prot = 2;
private:
    int pvt = 3;
};

class PublicDerived : public Base {
public:
    int getProt() { return prot; }
};

class ProtectedDerived : protected Base {
public:
    int getPub() { return pub; }
    int getProt() { return prot; }
};

class PrivateDerived : private Base {
public:
    int getPub() { return pub; }
    int getProt() { return prot; }
};

int main()
{
//    string str = "";
//    cout << !str << endl;
//    Array a;
//    cout << a << endl;

//    PublicDerived obj;
//    ProtectedDerived obj;
    PrivateDerived obj;
//    cout << obj.pub << endl;
//    cout << obj.prot << endl;
//    cout << obj.pvt << endl;
    cout << obj.getPub() << endl;
    cout << obj.getProt() << endl;
//    cout << obj.printPVT() << endl;
//    cout << obj.getPVT() << endl;


    return 0;
}
