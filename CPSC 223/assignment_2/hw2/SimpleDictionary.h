#ifndef SIMPLEDICTIONARY_H
#define SIMPLEDICTIONARY_H

#include <iostream>
#include <cassert>

#include "Dictionary.h"

using namespace std;

// Implementation of the Dictionary class, backed by an unsorted array with
// a given maximum size.  Most operations are O(n)
template<class K, class V>
class SimpleDictionary: public Dictionary<K,V> {
    public:
        // Create a dictionary with a given maximum number of elements
        SimpleDictionary(int num) {
            keys = new K[num];
            values = new V[num];
            maxSize = num;
            count = 0;
        }
		
		

        // Simple destructor
        ~SimpleDictionary() {
            delete[] keys;
            keys = nullptr;
            delete[] values;
            values = nullptr;
        }

		Dictionary& operator=(const Dictionary& other)
		{
			if(this == &other)
			{
				return *this;
			}
			delete keys[];
			delete values[];
			newKeys = new K[maxSize];
			for(int i = 0; i < maxSize; i++)
			{
				newKeys[i] = keys[i];
			}
			newValues = new V[maxSize];
			for(int i = 0; i < maxSize; i++)
			{
				newValues[i] = newValues[i];
			}
			return *this;
		}
		
		Dictionary(const Dictionary& other)
		{
			//something here?
			//private member variables??
			
			if(this == &other)
			{
				return *this;
			}
			delete keys[];
			delete values[];
			newKeys = new K[maxSize];
			for(int i = 0; i < maxSize; i++)
			{
				newKeys[i] = keys[i];
			}
			newValues = new V[maxSize];
			for(int i = 0; i < maxSize; i++)
			{
				newValues[i] = newValues[i];
			}
			return *this;
		}
		
        // Add elements to the dictionary, adding to the end of the array
        void add(K key, V value) override {
            // Check to make sure there is room to add elements
            assert(count < maxSize);
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    values[i] = value;
                    return;
                }
            }
            keys[count] = key;
            values[count] = value;
            count++;
        }

        // Return the value associated with the given key.  If the key is not
        // found, calls assert(false).
        V getValue(K key) const override {
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    return values[i];
                }
            }
            assert(false);
        }

        // Return a key associated with the given value.  If no keys have value
        // associated with them, calls assert(false)
        K getKey(V value) const override {
            for (int i=0; i<count; i++) {
                if (values[i] == value) {
                    return keys[i];
                }
            }
            assert(false);
        }

        // Returns true if the key exists, and false otherwise
        bool keyExists(K key) const override {
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    return true;
                }
            }
            return false;
        }

        // Removes a key/value pair from the dictionary.  If key can't be found,
        // no error occurs.
        void remove(K key) override {
            // find the index of the key
            for (int i=0; i<count; i++) {
                if (keys[i] == key) {
                    keys[i] = keys[count - 1];
                    values[i] = values[count - 1];
                    count--;
                    return;
                }
            }
        }

        // Displays the dictionary on standard output
        void display() const override {
            cout << "Dictionary: ";
            for (int i=0; i<count; i++) {
                cout << keys[i] << "->" << values[i];
                if (i != count-1) {
                    cout << ", ";
                } 
            }
            cout << endl;
        }

        // Returns the number of elements in the dictionary
        int size() const override {
            return count;
        }

    private:
        // Array of keys
        K *keys;

        // Array of values.  Index i in keys corresponds to index i in values
        V *values;

        // Maximum number of elements that can be stored in the dictionary
        int maxSize;

        // Number of elements currently stored in the dictionary
        int count;
};

#endif