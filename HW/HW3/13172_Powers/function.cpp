#include <iostream>
#include <string>
#include "function.h"

using namespace std;

special_power::special_power(int n) : n(n) {}

// x^n % 880301
int special_power::fpow(int x) {
    /// use the identity: (a * b) % m = [(a % m) * (b % m)] % m
    long long num = 1;
    for (int i = 0; i < n; i++) {
        num = (num * x) % 880301;
    }
    return (int)num;
}

// x^n % m
int special_power::fpow(int x, int m) {
    long long num = 1;
    for (int i = 0; i < n; i++) {
        num = (num * x) % m;
    }
    return (int)num;
}

// 2^n % 880301
int special_power::fpow() {
    long long num = 1;
    for (int i = 0; i < n; i++) {
        num = (num * 2) % 880301;
    }
    return (int)num;
}

// s^n
string special_power::fpow(string s) {
    string str = "";
    for (char c : s) {
        str += string(n, c);
    }
    return str;
}

// s^n % m
string special_power::fpow(string s, int m) {
    string str = "";
    for (char c : s) {
        str += string(n, c);
    }
    if (str.length() >= m) {
        str = str.substr(0, m);
    }
    return str;
}
