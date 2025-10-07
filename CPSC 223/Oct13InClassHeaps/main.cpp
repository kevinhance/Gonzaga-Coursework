#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Heap.h"

using namespace std;

int main() {

    // My test code is commented out below.  It adds 10 random elements and
    // then pops them from the heap.  The popped-out elements should happen
    // in order from largest to smallest.
    
    Heap h;
    srand(time(0));
    for (int i=0; i<10; i++) {
        h.add(rand() % 100 + 1);
        h.printHeap();
    }

    while (h.size() != 0) {
        cout << h.pop() << endl;
    }
}