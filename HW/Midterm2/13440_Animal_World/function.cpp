#include <iostream>
#include "function.h"

using namespace std;

/** Animal */
Animal::Animal() : HP(0) {}
Animal::Animal(string n, string s) : name(n), species(s), HP(0) {}

Animal::~Animal() = default;

string Animal::get_name() { return name; }
string Animal::get_species() { return species; }
int Animal::get_HP() { return HP; }
void Animal::update_HP(int x) { HP = x; }
void Animal::turn_HP_into_zero() { HP = 0; }

void Animal::Talk() {}
void Animal::Breath(int x) { HP += x; }
void Animal::Sleep(int x) { if (HP <= 100) HP *= x; }
void Animal::Eat(Animal *animal) {}
void Animal::Eaten(Animal *animal) {}


/** Cat */
Cat::Cat(string n) : Animal(n, "cat") {}

void Cat::Talk() {
    cout << "Meow" << endl;
}

void Cat::Eat(Animal *animal) {
    if (animal->get_species() == "fish") {
        update_HP(get_HP() + animal->get_HP());
    }
}


/** Fish */
Fish::Fish(string n) : Animal(n, "fish") {}

void Fish::Talk() {
    cout << "?" << endl;
}

void Fish::Eaten(Animal *animal) {
    string s = animal->get_species();
    if (s == "cat" || s == "bird" || s == "human") {
        turn_HP_into_zero();
    }
}


/** Bird */
Bird::Bird(string n) : Animal(n, "bird") {}

void Bird::Talk() {
    cout << "Suba" << endl;
}

void Bird::Eat(Animal *animal) {
    if (animal->get_species() == "fish") {
        update_HP(get_HP() + animal->get_HP());
    }
}

void Bird::Eaten(Animal *animal) {
    if (animal->get_species() == "human") {
        turn_HP_into_zero();
    }
}


/** Human */
Human::Human(string n) : Animal(n, "human") {}

void Human::Talk() {
    cout << "Hello, world" << endl;
}

void Human::Eat(Animal *animal) {
    string s = animal->get_species();
    if (s == "fish" || s == "bird") {
        update_HP(get_HP() + animal->get_HP());
    }
    else if (s == "cat") {
        turn_HP_into_zero();
    }
}

