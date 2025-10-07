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
const int NUM_ELEMENTS = 150;

// Thoroughly test the dictionary to ensure it contains the same key-value
// pairs as the passed-in map
void runTest(Dictionary<int, int> *d, const map<int, int>& m) {
    for (auto &p: m) {
        // Does the given key exist in the Dictionary?
        assert(d->keyExists(p.first) == true);

        // Does the given key have the correct value associated with it?
        assert(d->getValue(p.first) == p.second);

        // Call getKey to find a key associated with the value
        auto key = d->getKey(p.second);

        // Does calling getValue with the found key return the correct
        // value?
        assert(d->getValue(key) == p.second);

        // Search through the map to find the key-value pair associated
        // with the found key
        auto found = m.find(key);

        // Did we find that key in our map?
        assert(found != m.end());

        // Is the value associated with that key equal to the value we
        // looked up?
        assert(found->second == p.second);
    }

    for (int i=0; i<NUM_ELEMENTS * 10; i++) {
        int k = rand() % (NUM_ELEMENTS * 5);
        if (m.find(k) == m.end()) {
            assert(!d->keyExists(k));
        } else {
            assert(d->keyExists(k));
        }
    }
}

int main() {
    
    Dictionary<int, int> *d = new BSTDictionary<int, int>;
    map<int, int> m;

    // Choose a random starting seed based on the current time.  If you
    // encounter a bug, you can change this line from being equal to
    // time(0) to being equal to the random seed value that is output.
    // Using the same random seed will ensure you get the same sequence of
    // operations.
    auto randomSeed = time(0);
    cout << "Running with randomSeed = " << randomSeed << endl;
    srand(randomSeed);

    // Test to make sure the two are equivalent when empty
    runTest(d, m);

    // Add a random key-value pair, checking to ensure the two are equivalent
    // after each add operation
    for (int i=0; i<NUM_ELEMENTS; i++) {
        int k = rand() % (NUM_ELEMENTS * 5);
        int v = rand() % (NUM_ELEMENTS * 5) + NUM_ELEMENTS * 5;
        d->add(k, v);
        m[k] = v;
        runTest(d, m);
    }

    // Randomly choose a key to remove.  If the key exists, remove the
    // key-value pair from the two and check to ensure the two are equivalent
    for (int i=0; i<NUM_ELEMENTS; i++) {
        int k = rand() % (NUM_ELEMENTS * 5);
        auto it = m.find(k);
        if (it != m.end()) {
            m.erase(it);
            d->remove(k);
            runTest(d, m);
        }
    }

    delete d;
}
