#include <iostream>
#include <cstring>
#include "function.h"
using namespace std;

int n, q;

string species[1009];
Animal *animal[1009];

int main() {
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++ i) {
		string name;
		cin >> species[i] >> name;
		
		if (species[i] == "cat")
			animal[i] = new Cat(name);
		else if (species[i] == "fish")
			animal[i] = new Fish(name);
		else if (species[i] == "bird")
			animal[i] = new Bird(name);
		else if (species[i] == "human")
			animal[i] = new Human(name);
	}
	
	while ( q -- ) {
		string op; int i;
		cin >> op >> i;
		
		if (op == "Name") {
			cout << animal[i]->get_name() << endl;
			
		} else if (op == "Species") {
			cout << animal[i]->get_species() << endl;
			
		} else if (op == "HP") {
			cout << animal[i]->get_HP() << endl;
			
		} else if (op == "Talk") {
			animal[i]->Talk();
				
		} else if (op == "Breath") {
			int x;
			cin >> x;
			animal[i]->Breath(x);
			
		} else if (op == "Sleep") {
			int x;
			cin >> x;
			animal[i]->Sleep(x);
			
		} else if (op == "Eat") {
			int j;
			cin >> j;
			animal[i]->Eat(animal[j]);
			animal[j]->Eaten(animal[i]);
			
		}
	}
}
