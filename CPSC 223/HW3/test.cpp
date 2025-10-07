//Kevin Hance and Mauricio Velazquez
//10/18/17
//CPSCP 223 Assignment 3

#include <iostream>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include "BSTDictionary.h"

using namespace std;

// How many elements to go up to in the dictionary

// Thoroughly test the dictionary to ensure it contains the same key-value
// pairs as the passed-in map


int main() {
	BSTDictionary<int, int> *d = new BSTDictionary<int, int>(2, 14);
	//d->display();
	
	d->add(4, 7);
	d->add(3, 5);
	d->add(1, 6);
	d->add(20, 85);
	d->add(0, 64);
	
	BSTDictionary<int, int> *d2 = new BSTDictionary<int, int>(*d); //copy
	
	//cout << d->keyExists(20);
	
	d->display();
	
	cout << endl << endl;
	
	d->add(1, 8);
	d->add(20, 40);
	d->add(0, 78);
	
	d->display();
	
	cout << d->size() << endl;
	
	d->remove(0);
	d->display();
	
	cout << d->size() << endl;
	
	d->remove(4);
	d->remove(20);
	d->remove(3);
	
	d->display();
	
	cout << d->size() << endl;
	
	//BSTDictionary<int, int> *d2 = d;
	//d->display();
	d2->display();
	
	return 0;
}
