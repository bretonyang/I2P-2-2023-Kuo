#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

Person::Person(const string &name, const int age): name(name), age(age) { }

/// We must initialize static non-const members outside of class
/// Also, we don't have to specify static keyword
int Person::population = 0;

Person::Person(istream &is) {
    read(is, *this);
}

Person::~Person() {
    cout << "destructor called" << endl;
}

bool Person::is_adult() const {
    return age >= 18;
}

Person &Person::combine(const Person &other) {
    age += other.age;
    name += ' ' + other.name;
    return *this;
}

Person add(const Person &lhs, const Person &rhs) {
    Person p = lhs; // p is a copy of lhs
    p.combine(rhs);
    return p;
}

istream &read(istream &is, Person &p) {
    is >> p.name >> p.age;
    return is;
}

ostream &print(ostream &os, const Person &p) {
    os << "Name: " << p.name << ", Age: " << p.age;
    return os;
}
