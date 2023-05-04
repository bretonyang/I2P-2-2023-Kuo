#include <iostream>
#include <algorithm>
#include <string>
#include <map>

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

char *get_str() {
//    char str[] = "abc";
    char *str = new char[4];
    str[0] = 'a', str[1] = 'b', str[2] = 'c', str[4] = '\0';
    return str;
}

class TestBase {
public:
    int cnt;
    TestBase() : cnt(69) {
        cout << "base called" << endl;
    }
};

class SubTest : public TestBase {
public:
    int arr[1024];
    SubTest() = default;
};

void exchange(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int arr[10];
    arr[0] = 10;
    arr[1] = 20;
    cout << arr[0] << ' ' << arr[1] << endl;
    exchange(arr[0], arr[1]);
    cout << arr[0] << ' ' << arr[1] << endl;

//    SubTest t;
//    cout << t.cnt << endl;

//    string key, value;
//
//    map<string, string> person;
//    while (cin >> key >> value) {
//        person[key] = value;
//    }
//    for (auto it = begin(person); it != end(person); it++) {
//        cout << it->first << ": " << it->second << endl;
//    }

//    cout << get_str() << endl;

//    string str = "";
//    cout << !str << endl;
//    Array a;
//    cout << a << endl;

//    PublicDerived obj;
//    ProtectedDerived obj;
//    PrivateDerived obj;
//    cout << obj.pub << endl;
//    cout << obj.prot << endl;
//    cout << obj.pvt << endl;
//    cout << obj.getPub() << endl;
//    cout << obj.getProt() << endl;
//    cout << obj.printPVT() << endl;
//    cout << obj.getPVT() << endl;


    return 0;
}
