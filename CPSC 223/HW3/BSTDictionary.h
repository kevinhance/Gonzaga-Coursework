//Kevin Hance and Mauricio Velazquez
//10/18/17
//CPSCP 223 Assignment 3

//NOTE: Our big-O() values assume that the height h is equal to log(n), where
// 		n is the number of elements in the tree.

#ifndef BSTDICTIONARY_H
#define BSTDICTIONARY_H

#include <iostream>
#include <cassert>

#include "Dictionary.h"

using namespace std;

// Implementation of the Dictionary class, backed by an unsorted array with
// a given maximum size.  Most operations are O(n)

template<class K, class V>
struct Node {
	Node *left;
	Node *right;
	Node *parent;
	V value;
	K key;
	
	Node(K newKey, V newVal) {
		value = newVal;
		key = newKey;
		left = nullptr;
		right = nullptr;
	}
	
	Node(K newKey, V newVal, Node<K, V> leftNode, Node<K, V> rightNode) {
		value = newVal;
		key = newKey;
		left = leftNode;
		right = rightNode;
	}
};

template<class K, class V>
class BSTDictionary: public Dictionary<K, V> {//
    public:
        // Create a dictionary, big-O(1)
		BSTDictionary() {
			rootPtr = nullptr;
			count = 0;
		}
		
		//Constructor, big-O(1)
		BSTDictionary(K newKey, V newVal) {
			rootPtr = new Node<K, V>(newKey, newVal);
			//rootPtr->key = newKey;
			//rootPtr->value = newVal;
            count = 1;
        }

        // destructor, big-O(n)
        ~BSTDictionary() {
            destHelper(rootPtr);
			delete rootPtr;

        }

		
        // Copy constructor, big-O(n)
        BSTDictionary(const BSTDictionary &other) {
            count = other.count;
			rootPtr = copyTree(other->rootPtr);
        }
		
		//Operator =, big-O(n)
        BSTDictionary& operator=(const BSTDictionary &other) {
			//I promise, we tried.
        }

        // Add elements to the dictionary, adding to the end of the array, big-O(logn)
        void add(K key, V value) override {
			if (keyExists(key)) {
				//update value on existing entry
				updateValueHelper(key, value, rootPtr);
			}
			else if(rootPtr != nullptr) {
				addHelper(key, value, rootPtr);
				count++;
			}
			else {
				rootPtr = new Node<K, V>(key, value);
				count++;
			}
		}

        // Return the value associated with the given key.  If the key is not
        // found, calls assert(false).
		//big-O(logn)
        V getValue(K key) const override {
			if(keyExists(key)) {
				return getValueHelper(key, rootPtr);
			}
			else {
				assert(false);
			}
        }

        // Return a key associated with the given value.  If no keys have value
        // associated with them, calls assert(false)
		//big-O(n)
        K getKey(V targetValue) const override {
			Node<K, V>* tempPtr = getKeyHelper(targetValue, rootPtr);
			if(tempPtr && tempPtr->value == targetValue) {
				return tempPtr->key;
			}
			else {
				assert(tempPtr);
				return rootPtr->key;
			}
        }

        // Returns true if the key exists, and false otherwise
		//big-O(logn)
        bool keyExists(K key) const override {
			return keyExistsHelper(key, rootPtr);
        }
		// Returns true if the value exists, and false otherwise
		//big-O(n)
		bool valueExists(V val) const {
			return valueExistsHelper(val, rootPtr);
        }
		
        // Removes a key/value pair from the dictionary.  If key can't be found,
        // no error occurs.
		// big-O(logn)
        void remove(K key) override {
			bool isSuccessful = false;
			isSuccessful = removeValue(rootPtr, key, isSuccessful);
			cout << "Successful: " << isSuccessful << endl;
			count--;
        }

        // Displays the dictionary on standard output
		//big-O(n)
        void display() const override {
			displayHelper(rootPtr);
			cout << endl;
        }

        // Returns the number of elements in the dictionary
		//big-O(1)
        int size() const override {
            return count;
        }

		
		
    private:
        
		void updateValueHelper(K targetKey, V newVal, Node<K, V> *ptr) {
			
			if(ptr->key == targetKey) {
				ptr->value = newVal;
			}
			else if(targetKey < ptr->key) {
				updateValueHelper(targetKey, newVal, ptr->left);
			}
			else {
				updateValueHelper(targetKey, newVal, ptr->right);
			}
			return;
		}
		
		int keyExistsHelper(K targetKey, Node<K, V> *ptr) const {
			if(ptr->key == targetKey) {
				return 1;
			}
			else {
				if(ptr->left && ptr->right) {
					return keyExistsHelper(targetKey, ptr->left)
						+ keyExistsHelper(targetKey, ptr->right);
				}
				else if(ptr->left) {
					return keyExistsHelper(targetKey, ptr->left);
				}
				else if(ptr->right) {
					return keyExistsHelper(targetKey, ptr->right);
				}
				else {
					return 0;
				}
			}
		}
		
		int valueExistsHelper(V targetVal, Node<K, V> *ptr) const {
			if(ptr->value == targetVal) {
				return 1;
			}
			else {
				if(ptr->left && ptr->right) {
					return valueExistsHelper(targetVal, ptr->left)
						+ valueExistsHelper(targetVal, ptr->right);
				}
				else if(ptr->left) {
					return valueExistsHelper(targetVal, ptr->left);
				}
				else if(ptr->right) {
					return valueExistsHelper(targetVal, ptr->right);
				}
				else {
					return 0;
				}
			}
		}
		
		V getValueHelper(K targetKey, Node<K, V> *ptr) const {
			if(ptr->key == targetKey) {
				return ptr->value;
			}
			else if(targetKey < ptr->key) {
					return getValueHelper(targetKey, ptr->left);
			}
			else {
				return getValueHelper(targetKey, ptr->right);
			}
		}
		
		Node<K, V>* getKeyHelper(V targetVal, Node<K, V> *ptr) const {
			Node<K, V> *helpPtr = ptr;
			if(helpPtr != nullptr) {
				if(helpPtr->value == targetVal) {
					return helpPtr;
				}
				
				else if(helpPtr->left && helpPtr->right) {
					helpPtr = getKeyHelper(targetVal, ptr->left);
					if(helpPtr) {
						return helpPtr;
					}
					
					helpPtr = getKeyHelper(targetVal, ptr->right);
					if(helpPtr) {
						return helpPtr;
					}
				}
				
				else if(helpPtr->left) {
					helpPtr = getKeyHelper(targetVal, ptr->left);
					if(helpPtr) {
						return helpPtr;
					}
				}
				
				else if(helpPtr->right) {
					helpPtr = getKeyHelper(targetVal, ptr->right);
					if(helpPtr) {
						return helpPtr;
					}
				}
			return nullptr;	
			}
			
			else {
				return helpPtr;
			}
		}
		
		void destHelper(Node<K, V> *subtreePtr) const {
			
			if(subtreePtr != nullptr)
			{
				destHelper(subtreePtr->left);
				destHelper(subtreePtr->right);
				subtreePtr->left = nullptr;
				subtreePtr->right = nullptr;
			}
		}
		
		void displayHelper(Node<K, V> *subtreePtr) const {
			if(subtreePtr != nullptr)
			{
				if(subtreePtr->left) {
					displayHelper(subtreePtr->left);
				}
				cout << "Key: " << subtreePtr->key;
				cout << ", Value: " << subtreePtr->value << endl;
				if(subtreePtr->right) {
					displayHelper(subtreePtr->right);
				}
			}
		}
		
		Node<K, V> copyTree(const Node<K, V> *oldTreeRootPtr) {
			/*if(oldTreeRootPtr == nullptr) {
				return nullptr;
			}
			else {
				*newTreePtr = new Node<K, V>;
				newTreePtr->key = oldTreeRootPtr->key;
				newTreePtr->value = oldTreeRootPtr->value;
				
				newTreePtr->left = copyTree(oldTreeRootPtr->left);
				newTreePtr->right = copyTree(oldTreeRootPtr->right);
			}
			return newTreePtr;*/
			
			Node<K, V> *newTreePtr;
			
			if(oldTreeRootPtr != nullptr) {
				newTreePtr = Node<K, V>(oldTreeRootPtr->key, oldTreeRootPtr->value, nullptr, nullptr);
				newTreePtr->left = copyTree(oldTreeRootPtr->left);
				newTreePtr->right = copyTree(oldTreeRootPtr->right);
			}
			return newTreePtr;
			
		}
		
		void addHelper(K newKey, V newValue, Node<K, V> *ptr) {
			if (newKey < ptr->key) {
				if(ptr->left == nullptr) {
					ptr->left = new Node<K, V>(newKey, newValue);
				}
				else {
					addHelper(newKey, newValue, ptr->left);
				}
			}
			else {
				if(ptr->right == nullptr) {
					ptr->right = new Node<K, V>(newKey, newValue);
				}
				else {
					addHelper(newKey, newValue, ptr->right);
				}
			}
			
		}
		
		Node<K, V>* removeValue(Node<K, V> *subtreePtr, K targetKey, bool isSuccessful) {
			if(subtreePtr == nullptr) {
				isSuccessful = false;
			}
			
			else if (subtreePtr->key == targetKey) {
				subtreePtr = removeNode(subtreePtr);
				isSuccessful = true;
			}
			
			else if (subtreePtr->key > targetKey) {
				Node<K, V> *tempPtr = removeValue(subtreePtr->left, targetKey, isSuccessful);
				subtreePtr->left = tempPtr;
			}
			
			else {
				Node<K, V> *tempPtr = removeValue(subtreePtr->right, targetKey, isSuccessful);
				subtreePtr->right = tempPtr;
			}
			return subtreePtr;
		}
		
		Node<K, V>* removeNode(Node<K, V> *nodePtr) {
			if(nodePtr->left == nullptr && nodePtr->right == nullptr) {
				nodePtr = nullptr;
				return nodePtr;
			}
			
			else if(nodePtr->left == nullptr || nodePtr->right == nullptr) {
				Node<K, V> *nodeToConnectPtr = nullptr;
				if(nodePtr->left != nullptr) {
					nodeToConnectPtr = nodePtr->left;
				}
				else {
					nodeToConnectPtr = nodePtr->right;
				}
				
				//nodePtr = nullptr;
				delete nodePtr;
				return nodeToConnectPtr;
			}
			
			else {
				K newNodeKey = nodePtr->right->key;
				V newNodeValue = getValue(newNodeKey);
				Node<K, V> *tempPtr = removeLeftmostNode(nodePtr->right, newNodeKey);
				nodePtr->right = tempPtr;
				nodePtr->key = newNodeKey;
				nodePtr->value = newNodeValue;
				return nodePtr;
			}
		}
		
		Node<K, V>* removeLeftmostNode(Node<K, V> *nodePtr, K inorderSuccessor) {
			if(nodePtr->left == nullptr) {
				inorderSuccessor = nodePtr->key;
				return removeNode(nodePtr);
			}
			else {
				Node<K, V> *tempPtr = removeLeftmostNode(nodePtr->left, inorderSuccessor);
				nodePtr->left = tempPtr;
				return nodePtr;
			}
		}
					
		//void swapNodes(Node<K, V> *node1, Node<K, V> *node2) {
			//Node<K, V> *temp = new Node(node1->
		
		
		
		// Root node of tree
		Node<K, V> *rootPtr;

        // Number of elements currently stored in the dictionary
        int count;
		
		
};

#endif