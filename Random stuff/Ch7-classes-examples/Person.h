#ifndef Person_H
#define Person_H

#include <iostream>
#include <string>

class Person {
public:
    Person() = default; // can also be in Person.cpp, Person::Person() = default;
    Person(const std::string &name): name(name) {} // name(name) is the constructor initilizer
    Person(const std::string &name, const int age);
    Person(std::istream &);
    ~Person();

    bool is_adult() const;
    Person &combine(const Person &);
    std::string get_name() const { return name; }

private:
    std::string name;
    int age = 0;
    static int population; /// can't initialize static non-const members inside class

/// NOTE: friend declarations can be put anywhere in the class
friend std::istream &read(std::istream &, Person &);
friend std::ostream &print(std::ostream &, const Person &);
friend Person add(const Person &, const Person &);
};

std::istream &read(std::istream &, Person &);
std::ostream &print(std::ostream &, const Person &);
Person add(const Person &, const Person &);

#endif // Person_H
