#include <iostream>
#include "function.h"

#define SIZE 101

using namespace std;

/**

Copy construction:
Each subobject is copied in the manner appropriate to its type:
- if the subobject is of class type, the copy constructor for the class is used;
- if the subobject is an array, each element is copied, in the manner appropriate to the element type;
- if the subobject is of scalar type, the built-in assignment operator is used.

Copy assignment:
Each subobject is assigned in the manner appropriate to its type:
- if the subobject is of class type, the copy assignment operator for the class is used (as if by explicit qualification; that is, ignoring any possible virtual overriding functions in more derived classes);
- if the subobject is an array, each element is assigned, in the manner appropriate to the element type;
- if the subobject is of scalar type, the built-in assignment operator is used.

*/

Polynomial::Polynomial() = default;

Polynomial::Polynomial(const int greatestPower, const int coefficients[51]) {
    this->greatestPower = greatestPower;
    for (int i = 0; i <= greatestPower; i++) {
        this->coefficients[i] = coefficients[i];
    }
    for (int i = greatestPower + 1; i < SIZE; i++) {
        this->coefficients[i] = 0;
    }
}

Polynomial Polynomial::add(const Polynomial rhs) const {
    int result[SIZE];
    int max_power = max(greatestPower, rhs.greatestPower);
    for (int i = 0; i <= max_power; i++) {
        result[i] = coefficients[i] + rhs.coefficients[i];
    }
    return Polynomial(max_power, result);
}

Polynomial Polynomial::subtract(const Polynomial rhs) const {
    int result[SIZE];
    int max_power = max(greatestPower, rhs.greatestPower);
    for (int i = 0; i <= max_power; i++) {
        result[i] = coefficients[i] - rhs.coefficients[i];
    }
    return Polynomial(max_power, result);
}

Polynomial Polynomial::multiplication(const Polynomial rhs) const {
    int result[SIZE] = {};
    int max_power = greatestPower + rhs.greatestPower;
    for (int i = 0; i <= greatestPower; i++) {
        for (int j = 0; j <= rhs.greatestPower; j++) {
            result[i + j] += coefficients[i] * rhs.coefficients[j];
        }
    }
    return Polynomial(max_power, result);
}

void Polynomial::output() const {
    for (int i = greatestPower; i > 0; i--) {
        cout << coefficients[i] << ' ';
    }
    cout << coefficients[0];
}
