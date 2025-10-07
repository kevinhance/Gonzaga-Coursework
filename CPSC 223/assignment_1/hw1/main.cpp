#include <iostream>
#include <cassert>

#include "LinkedList.h"

using namespace std;

int main() {
	
	LinkedList<int> lst;
	
	assert(lst.size() == 0);
	assert(lst.itemCount(0) == 0);
	cout << "Should display a list with nothing in it" << endl;
	lst.display();

	lst.addFront(1);
	assert(lst.size() == 1);
	assert(lst.itemCount(0) == 0);
	assert(lst.itemCount(1) == 1);

	lst.addFront(2);
	assert(lst.size() == 2);
	assert(lst.itemCount(0) == 0);
	assert(lst.itemCount(1) == 1);
	assert(lst.itemCount(2) == 1);

	lst.addFront(3);
	cout << "Should display 3 2 1" << endl;
	lst.display();
	assert(lst.size() == 3);
	assert(lst.itemCount(0) == 0);
	assert(lst.itemCount(1) == 1);
	assert(lst.itemCount(2) == 1);
	assert(lst.itemCount(3) == 1);


	lst.addFront(12);
	assert(lst.size() == 4);
	assert(lst.itemCount(0) == 0);
	assert(lst.itemCount(1) == 1);
	assert(lst.itemCount(2) == 1);
	assert(lst.itemCount(3) == 1);
	assert(lst.itemCount(12) == 1);

	lst.popFront();
	cout << "Should display 3 2 1" << endl;
	lst.display();
	assert(lst.size() == 3);
	assert(lst.itemCount(0) == 0);
	assert(lst.itemCount(1) == 1);
	assert(lst.itemCount(2) == 1);
	assert(lst.itemCount(3) == 1);
	assert(lst.itemCount(12) == 0);

	lst.addFront(0);
	assert(lst.size() == 4);
	assert(lst.itemCount(0) == 1);
	assert(lst.itemCount(1) == 1);
	assert(lst.itemCount(2) == 1);
	assert(lst.itemCount(3) == 1);

	lst.popBack();
	cout << "Should display 0 3 2" << endl;
	lst.display();
	assert(lst.size() == 3);
	assert(lst.itemCount(0) == 1);
	assert(lst.itemCount(1) == 0);
	assert(lst.itemCount(2) == 1);
	assert(lst.itemCount(3) == 1);

	lst.addBack(0);
	cout << "Should display 0 3 2 0" << endl;
	lst.display();
	assert(lst.size() == 4);
	assert(lst.itemCount(0) == 2);
	assert(lst.itemCount(1) == 0);
	assert(lst.itemCount(2) == 1);
	assert(lst.itemCount(3) == 1);
}