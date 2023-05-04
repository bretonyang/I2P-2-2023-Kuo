#include <iostream>
#include <cstring>
#include "function.h"

using namespace std;

namespace oj {

/// char *_val;

BigInt::BigInt(char *s) {
    int len = strlen(s);
    _val = new char[len + 1];
    strcpy(_val, s);
}

BigInt::~BigInt() {
    delete [] _val;
}

BigInt& BigInt::operator++() {
    int carry = 1;
    int len = strlen(_val);
    for (int i = len - 1; i >= 0; i--) {
        int digit = _val[i] - '0' + carry;
        if (digit < 10) {
            carry = 0;
            _val[i] = '0' + digit;
            break;
        }
        else {
            carry = 1;
            _val[i] = '0';
        }
    }
    if (carry == 1) {
        char *tmp = _val;
        _val = new char[len + 2];
        strcpy(_val + 1, tmp);
        _val[0] = '1';
        delete tmp;
    }
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt tmp(_val);
    ++(*this);
    return tmp;
}

BigInt& BigInt::operator--() {
    if (_val[0] != '0') {
        int borrow = 1;
        int len = strlen(_val);
        for (int i = len - 1; i >= 0; i--) {
            int digit = _val[i] - '0' - borrow;
            if (digit >= 0) {
                borrow = 0;
                _val[i] = '0' + digit;
                break;
            }
            else {
                borrow = 1;
                _val[i] = '9';
            }
        }
        if (_val[0] == '0' && len > 1) {
            char *tmp = _val;
            _val = new char[len];
            strcpy(_val, tmp + 1);
            delete tmp;
        }
    }
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt tmp(_val);
    --(*this);
    return tmp;
}

char* BigInt::to_s() {
    return _val;
}

}
