#ifndef Dictionary23_H
#define Dictionary23_H

#include <iostream>
#include <cassert>
#include <memory>
#include "Dictionary.h"

using namespace std;

// Implementation of the Dictionary class, backed by an unsorted array with
// a given maximum size.  Most operations are O(n)
template <class K, class V>
struct Node23 {
    unique_ptr<Node23> left;
    unique_ptr<Node23> mid;
    unique_ptr<Node23> right;
    Node23 *parent; // only if it would be useful

    bool isTwoNode = true;

    K smallKey; // if it's a two-node, smallKey and smallValue are used
    V smallValue;

    K largeKey;
    V largeValue;
};

template<class K, class V>
class Dictionary23: public Dictionary<K,V> {
    public:
        // Create a dictionary with a given maximum number of elements
        Dictionary23() {
            
        }

        // Simple destructor
        ~Dictionary23() {
            
        }
		

        // Copy constructor
        Dictionary23(const Dictionary23 &other) {
            
        }

        Dictionary23& operator=(const Dictionary23 &other) {
            
        }

        // Add elements to the dictionary, adding to the end of the array
        void add(K key, V value) override {
            
        }

        // Return the value associated with the given key.  If the key is not
        // found, throws an exception
        V getValue(K key) const override {
        }

        // Return a key associated with the given value.  If no keys have value
        // associated with them, throws an exception
        K getKey(V value) const override {
            
        }

        // Returns true if the key exists, and false otherwise
        bool keyExists(K key) const override {
            return keyExistsHelper(key, rootptr.get());
        }

        // Removes a key/value pair from the dictionary.  If key can't be found,
        // no error occurs.
        void remove(K key) override {
            
        }

        // Displays the dictionary on standard output
        void display() const override {
            
        }

        // Returns the number of elements in the dictionary
        int size() const override {
            
        }

    private:
        
		unique_ptr<Node23<K, V>> rootptr = nullptr;

        // Number of elements currently stored in the dictionary
        int count;
		
		bool keyExistsHelper(K key, Node* root) const {
			if(root->isTwoNode) {
				if(root->smallKey == key)
					return true;
				else if(!(root->left)||!(root->right)) {
					assert(!(root->left)&&!(root->right)); // make sure we don't have a root with only one child
					return false;
				}
				else if(key < root->smallKey)
					return keyExistsHelper(key, root->left.get());
				else
					return keyExistsHelper(key, root->right.get());
			}
			else {
				if(root->smallKey == key || root->largeKey == key)
					return true;
				else if(!(root->left)||!(root->mid)||!(root->right)) {
					assert(!(root->left)&&!(root->mid)&&!(root->right)); // make sure we don't have a root with only one child
					return false;
				}
				else if(key < root->smallKey)
					return keyExistsHelper(key, root->left);
				else if(key < root->largeKey)
					return keyExistsHelper(key, root->mid);
				else if(key > root->largeKey)
					return keyExistsHelper(key, root->right);
			}
		}
			
};

#endif