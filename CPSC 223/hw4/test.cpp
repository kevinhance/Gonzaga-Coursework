#include <iostream>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include "Dictionary23.h"

using namespace std;


int main() {
    Dictionary23<int, int> *d = new Dictionary23<int, int>;
	d->add(35, 4);
	d->add(14, 3);
	d->add(32, 5);
	d->add(19, 2);
	d->add(13, 45);
	d->add(18, 32);
	d->add(30, 34);
	d->add(69, 37);
	cout << d->size() << endl;
	cout << endl << endl;
	d->display();
	return 0;
}