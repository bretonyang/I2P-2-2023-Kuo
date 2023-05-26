#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Example class with overloaded () operator
class MyCallable {
public:
    int operator()(int x, int y) {
        return x + y;
    }

    double operator()(double x, double y) {
        return x * y;
    }

    const string operator()(const string str) {
        return str + " STRING ADD-ON!!!";
    }
};

int main() {
    MyCallable myCallable;

    int result1 = myCallable(3, 4);
    cout << "3 + 4 is: " << result1 << endl;

    double result2 = myCallable(2.5, 1.5);
    cout << "2.5 * 1.5 is: " << result2 << endl;

    const string result3 = myCallable("Hello, world!");
    cout << "str postfixed: " << result3 << endl;

    return 0;
}
