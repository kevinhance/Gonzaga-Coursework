#include <iostream>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include "Dictionary23.h"

using namespace std;


int main() {
    Dictionary23<int, int> d;
	d.add(35, 4);
	d.add(14, 3);
	d.add(32, 5);
	d.add(19, 2);
	d.add(13, 45);
	d.add(18, 32);
	d.add(30, 34);
	d.add(69, 37);
	d.add(130, 45);
	d.add(180, 32);
	d.add(300, 34);
	d.add(690, 37);
	
	cout << d.size() << endl;
	cout << endl << endl;
	d.display();
	
	/*// part 2 testing
	cout << "Part 2 testing:" << endl << endl;
	Dictionary23<int, int> dCopy = d;
	cout << "d: should be same as before..." << endl;
	d.display();
	
	cout << endl << "dCopy: should be same also" << endl;
	dCopy.display();
	
	dCopy.add(111, 111);
	d.add(222, 222);
	
	cout << "d: should contain key 222 w/ value 222" << endl;
	d.display();
	
	cout << endl << "dCopy: should contain key 111 w/ value 111" << endl;
	dCopy.display();
	
	dCopy = d;
	
	dCopy.add(333, 333);
	cout << endl << "dCopy: should contain key 222 w/ value 222, and key/val 333" << endl;
	dCopy.display();
	
	cout << "d: should still contain key 222 w/ value 222, not 111 or 333" << endl;
	d.display();
	*/
	
	//part 2 remove testing:
	cout << "300 should be displayed" << endl;
	cout << d.keyExists(180);
	d.remove(180);
	
	
	return 0;
}