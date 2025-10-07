#include <iostream>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SimpleDictionary.h"
//#include "Dictionary23.h"

using namespace std;

// Number of elements to add to the test dictionary/map
const int NUM_ELEMENTS = 150;

// What data type to use for the keys and values.  Change the type
// after "typedef" and before "KeyType" or "ValueType" to the type
// you want to use.  Valid types are int, double, and string.
typedef string KeyType;
typedef string ValueType;

// What Dictionary type do you want to use as the dictionary class?
// Setting it here rather than passing of abstract class Dictionary
// allows debuggers to give better information.  To test Dictionary23,
// change "SimpleDictionary" below to "Dictionary23"
typedef SimpleDictionary<KeyType, ValueType> DictionaryType;

// Boolean, indicating whether exceptions should be tested.  Your code
// should work with this set to true!
const bool TEST_EXCEPTIONS = true;

// You can ignore the next chunks of code if you want.  They define a
// way to randomly generate ints, strings, and doubles.

// Define a templated function named randomValue that can generate a
// random value of a specified type.  This function of arbitrary type
// is deliberately not defined.  Instead, you can use the specialized
// versions (below) for string, int, and double.
template<class T>
T randomValue();

// Specialization of randomValue for string.  Returns a random string
// with length between MIN_LEN and MAX_LEN (inclusive), with valid characters
// being lowercase and uppercase latin letters.
template<>
string randomValue<string>() {
    const int MIN_LEN = 2;
    const int MAX_LEN = 3;
    string ans;
    int len = rand() % (MAX_LEN - MIN_LEN + 1) + MIN_LEN;
    for (int i=0; i<len; i++) {
        char c = 'A';
        if (rand() % 2 == 0) {
            c = 'a';
        }
        ans += (c + rand() % 26);
    }
    return ans;
}

// Specialization of randomValue for int.  Returns a random value between
// 0 and 999 (inclusive).
template<>
int randomValue<int>() {
    return rand() % 1000;
}

// Specialization of randomValue for double.  Returns a random value between
// 0 and 1 (inclusive), quantized to increments of 0.001.
template<>
double randomValue<double>() {
    return (rand() % 1001) * 0.001;
}

// Perform the test, ensuring that the Dictionary and map contain the
// same values.
template <class K, class V>
void runTest(DictionaryType& d, const map<K, V>& m) {
    // For each key/value pair in the map, assert that the key is found
    // in the dictionary, as well as that getValue returns the right value.
    for (auto &p: m) {
        // Does the given key exist in the Dictionary?
        assert(d.keyExists(p.first) == true);

        // Does the given key have the correct value associated with it?
        assert(d.getValue(p.first) == p.second);

        // Call getKey to find a key associated with the value
        auto key = d.getKey(p.second);

        // Does calling getValue with the found key return the correct
        // value?
        assert(d.getValue(key) == p.second);

        // Search through the map to find the key-value pair associated
        // with the found key
        auto found = m.find(key);

        // Did we find that key in our map?
        assert(found != m.end());

        // Is the value associated with that key equal to the value we
        // looked up?
        assert(found->second == p.second);
    }

    // Loop over randomly generated keys, checking to see if the key
    // exists.  If the key doesn't exist, assert that keyExists properly
    // returns false.  Additionally, if TEST_EXCEPTIONS is true, try
    // running getValue with that key, making sure a DictionaryException
    // is thrown.
    for (int i=0; i<NUM_ELEMENTS * 10; i++) {
        auto k = randomValue<KeyType>();
        if (m.find(k) == m.end()) {
            assert(!d.keyExists(k));
            if (TEST_EXCEPTIONS) {
                bool exceptSuccess = false;
                try {
                    d.getValue(k);
                } catch (DictionaryException &e) {
                    exceptSuccess = true;
                } catch (exception &e) {
                    cerr << "Expected an exception of";
                    cerr << " class DictionaryException" << endl;
                    abort();
                }
                // Assert that the exception was properly thrown.
                assert(exceptSuccess);
            }
        } else {
            assert(d.keyExists(k));
        }
    }
}

int main() {
    time_t seed = time(0);
    cerr << "Current seed: " << seed << endl;

    // change line below ("seed = seed;") to force seed to take on a
    // specific value.
    seed = seed;
    // Seed random number generator, and create our dictionaries.
    srand(seed);

    DictionaryType d;
    map<KeyType, ValueType> m;

    // Create the dictionary by adding a number of keys and values
    cerr << "Creating dictionary...";
    for (int i=0; i<NUM_ELEMENTS; i++) {
        auto k = randomValue<KeyType>();
        auto v = randomValue<ValueType>();
        d.add(k, v);
        m[k] = v;
        runTest(d, m);
        cerr << ".";
    }
    runTest(d, m);

    cerr << "Done" << endl;

    // If you wish, you can uncomment out the following block of code to test
    // the remove function.  This is *NOT* required for part 1 of this
    // assignment.

    /*
    for (int i=0; i<NUM_ELEMENTS * 10; i++) {
        auto k = randomValue<KeyType>();
        auto it = m.find(k);
        if (it != m.end()) {
            cerr << "Removing " << k << "...";
            m.erase(it);
            d.remove(k);
            runTest(d, m);
            cerr << "Done" << endl;
        } else if (TEST_EXCEPTIONS) {
            // If TEST_EXCEPTIONS, test to make sure remove() and getValue()
            // will throw exceptions when necessary.
            bool success = false;
            try {
                d.remove(k);
            } catch (DictionaryException &e) {
                success = true;
            } catch (exception &e) {
                cerr << "Expected an exception of";
                cerr << " class DictionaryException" << endl;
                abort();
            }
            // Assert that the DictionaryException was properly thrown
            // by remove().
            assert(success);
            success = false;
            try {
                d.getValue(k);
            } catch (DictionaryException &e) {
                success = true;
            } catch (exception &e) {
                cerr << "Expected an exception of";
                cerr << " class DictionaryException" << endl;
                abort();
            }
            // Assert that the DictionaryException was properly thrown
            // by getValue().
            assert(success);
        }
    }*/
}