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
	unique_ptr<Node23> mid_r;
    unique_ptr<Node23> right;
    Node23 *parent; // only if it would be useful

    bool isTwoNode = true;

    K smallKey; // if it's a two-node, smallKey and smallValue are used
    V smallValue;
	
	K midKey;
	V midValue;
	
	K tempKey;
	V tempValue;
	
    K largeKey;
    V largeValue;
};

template<class K, class V>
class Dictionary23: public Dictionary<K,V> {
    public:
        // Create a dictionary with a given maximum number of elements
        Dictionary23() {
            //NOTHING
        }

        // Simple destructor
        ~Dictionary23() {
            //No code required
			//After this is run, rootptr deletes itself,
			//causing all children to delete themselves
        }
		

        // Copy constructor
        Dictionary23(const Dictionary23 &other) {
            //iterate through in pre-order
			copyHelper(other->rootptr.get());
        }

        Dictionary23& operator=(const Dictionary23 &other) {
            //destructor process (don't actually delete object)
			rootptr = nullptr;
			//then same process as copy constructor
			copyHelper(other->rootptr.get());
        }

        // Add elements to the dictionary, adding to the end of the array
        void add(K key, V value) override {
            if(rootptr == nullptr) { 
				rootptr = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				rootptr->isTwoNode = true;
				rootptr->smallKey = key;
				rootptr->smallValue = value;
				rootptr->left = nullptr;
				rootptr->right = nullptr;
				rootptr->parent = nullptr;
				
			} else {
				
				Node23<K, V> *leaf = findLeaf(key, rootptr.get());
					if(leaf->isTwoNode) {						// if the leaf we find is a two-node,
						if(key < leaf->smallKey) {				// then we can easily put the new data
							leaf->largeKey = leaf->smallKey;	// in that node, turning it to a 3-node
							leaf->largeValue = leaf->smallValue;
							leaf->smallKey = key;
							leaf->smallValue = value;
							leaf->mid = nullptr;
							leaf->isTwoNode = false;
						} else {
							leaf->largeKey = key;
							leaf->largeValue = value;
						}
					} else {
						if(key < leaf->smallKey) {
							leaf->midKey = leaf->smallKey;
							leaf->midValue = leaf->smallValue;
							leaf->smallKey = key;
							leaf->smallValue = value;
						} else if(key < leaf->largeKey) {
							leaf->midKey = key;
							leaf->midValue = value;
						} else if(key > leaf->largeKey) {
							leaf->midKey = leaf->largeKey;
							leaf->midValue = leaf->largeValue;
							leaf->largeKey = key;
							leaf->largeValue = value;
						}
						split(leaf);
						
					}
			}
			count++;
		}

        // Return the value associated with the given key.  If the key is not
        // found, throws an exception
        V getValue(K key) const override {
			try{
				if(!(keyExists(key))) {
					throw DictionaryException("Key does not exist in tree");
				} else {
					return getValueHelper(key, rootptr.get());
				}
			} catch(const DictionaryException &topic) {
				cout << topic.what() << endl;
				return -999; // if returned, function has tried and caught exception
			}
        }

        // Return a key associated with the given value.  If no keys have value
        // associated with them, throws an exception
        K getKey(V value) const override {
			K returnKey = -999;
			try {
				if(valueExists(value)) {
					Node23<K, V> *tempptr = getKeyHelper(value, rootptr.get());
					
					if(!(tempptr->isTwoNode) && tempptr->largeValue == value) {
							returnKey = tempptr->largeKey;
					} else
						returnKey = tempptr->smallKey;
				}
				return returnKey;
			} catch(const DictionaryException &topic) {
				cout << topic.what() << endl;
				return returnKey; // if returned, function has tried and caught exception
			}	
        }

        // Returns true if the key exists, and false otherwise
        bool keyExists(K key) const override {
            try {
				return keyExistsHelper(key, rootptr.get());
			} catch(const DictionaryException &topic) {
				cout << topic.what() << endl;
				return false;
			}
        }
		
		bool valueExists(V val) const {
			bool returnBool = 0;
			try {
				returnBool = valueExistsHelper(val, rootptr.get());
			} catch(const DictionaryException &topic) {
				cout << topic.what() << endl;
				returnBool = false;
			}
			return returnBool;
		}

        // Removes a key/value pair from the dictionary.  If key can't be found,
        // no error occurs.
        void remove(K key) override {
            // NOTHING
        }

        // Displays the dictionary on standard output
        void display() const override {
            cout << rootptr->smallValue << " " << rootptr->smallKey << endl;
			displayHelper(rootptr.get());
			cout << endl;
        }

        // Returns the number of elements in the dictionary
        int size() const override {
            return count;
        }

    private:
        
		unique_ptr<Node23<K, V>> rootptr = nullptr;

        // Number of elements currently stored in the dictionary
        int count = 0;
		
		bool keyExistsHelper(K key, Node23<K, V> *root) const {
			if(!root) {
				throw DictionaryException("Key does not exist, tree is empty");
			} else {
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
						return keyExistsHelper(key, root->left.get());
					else if(key < root->largeKey)
						return keyExistsHelper(key, root->mid.get());
					else if(key > root->largeKey)
						return keyExistsHelper(key, root->right.get());
				}
			}
		}
		
		V getValueHelper(K key, Node23<K, V> *root) const {
			if(root->isTwoNode) {
				if(root->smallKey == key)
					return root->smallValue;
				else if(key < root->smallKey)
					return getValueHelper(key, root->left.get());
				else
					return getValueHelper(key, root->right.get());
			} else {
				if(root->smallKey == key)
					return root->smallValue;
				else if(root->largeKey == key)
					return root->largeValue;
				else if(key < root->smallKey)
					return getValueHelper(key, root->left.get());
				else if(key < root->largeKey)
					return getValueHelper(key, root->mid.get());
				else if(key > root->largeKey)
					return getValueHelper(key, root->right.get());
			}
		}
		
		Node23<K, V>* getKeyHelper(V val, Node23<K, V> *root) const {
			Node23<K, V> *helpptr = root;
			if(helpptr) {
				if(helpptr->isTwoNode) {
					if(helpptr->smallValue == val)
						return helpptr;
					else if(helpptr->left) {
						assert(helpptr->right);
						helpptr = getKeyHelper(val, root->left.get());
						if(helpptr)
							return helpptr;
						helpptr = getKeyHelper(val, root->right.get());
						if(helpptr)
							return helpptr;
					}
				} else {
					if(helpptr->smallValue == val || helpptr->largeValue == val)
						return helpptr;
					else if(helpptr->left) {
						assert(helpptr->mid);
						assert(helpptr->right);
						helpptr = getKeyHelper(val, root->left.get());
						if(helpptr)
							return helpptr;
						helpptr = getKeyHelper(val, root->mid.get());
						if(helpptr)
							return helpptr;
						helpptr = getKeyHelper(val, root->right.get());
						if(helpptr)
							return helpptr;
					}
				}
				return nullptr;
			} else {
				throw DictionaryException("Node passed into getKeyHelper is nullptr");
			}
		}
		
		int valueExistsHelper(V val, Node23<K, V> *root) const {
			int returnVal = 0;
			if(root) {
				if(root->isTwoNode) {
					if(root->smallValue == val)
						returnVal = 1;
					else {
						returnVal = valueExistsHelper(val, root->left.get()) +
									valueExistsHelper(val, root->right.get());
					}
				} else {
					if(root->smallValue == val || root->largeValue == val)
						returnVal = 1;
					else {
						if(root->left) {
							assert(root->mid);
							assert(root->right);
							returnVal = valueExistsHelper(val, root->left.get()) +
										valueExistsHelper(val, root->mid.get()) +
										valueExistsHelper(val, root->right.get());
						}
						// else, we've hit a leaf and the value isn't in this subtree
						// so we just return 0
					}
					
					return returnVal;
				}
			} else {
				throw DictionaryException("Node passed into valueExistsHelper() is nullptr");
			}
		}
			
		
		Node23<K, V>* findLeaf(K key, Node23<K, V> *root) {
			try {
				if(root == nullptr) {
					throw DictionaryException("Root node is null");
				} else{

					if(root->left == nullptr)
					{
						return root;
				} else if(root->isTwoNode) {
					if(key < root->smallKey)
						return findLeaf(key, root->left.get());
					else
						return findLeaf(key, root->right.get());
				} else {
					if(key < root->smallKey)
						return findLeaf(key, root->left.get());
					else if(key < root->largeKey)
						return findLeaf(key, root->mid.get());
					else 
						return findLeaf(key, root->right.get());
					}
				}			
			} catch(const DictionaryException &topic) {
				cout << topic.what() << endl;
				return nullptr;
			}
		}
		
		void displayHelper(Node23<K, V> *root) const {
			if(root) {
				if(root->isTwoNode) {
					if(root->left) 
						displayHelper(root->left.get());
					
					cout << "Key: " << root->smallKey;
					cout << ", Value: " << root->smallValue << endl;
					if(root->right) 
						displayHelper(root->right.get());
					
				} else {
					if(root->left) 
						displayHelper(root->left.get());
					
					cout << "Key: " << root->smallKey;
					cout << ", Value: " << root->smallValue << endl;
						
					if(root->mid)
						displayHelper(root->mid.get());
					
					cout << "Key: " << root->largeKey;
					cout << ", Value: " << root->largeValue << endl;
					
					if(root->right) 
						displayHelper(root->right.get());
				}
			}
			
			/*if(!root) {
				return;
			} if(!root->left) {
				cout << "Key: " << root->smallKey;
				cout << ", Value: " << root->smallValue << endl;
			} else if(root->isTwoNode
				displayHelper(root->left.get());
				*/
		}
		
		bool isLeaf(Node23<K, V> *node) const {
			bool returnBool = false;
			if(node && !(node->left)) {
				assert(!(node->right));
				returnBool = true;
			}
			return returnBool;
		}
				
		
		void copyHelper(Node23<K, V> *otherNode) {
			if(otherNode->isTwoNode()) {
				add(otherNode->smallKey, otherNode->smallValue);
				if(!(otherNode->isLeaf())) {
					copyHelper(otherNode->left.get());
					copyHelper(otherNode->right.get());
				}
			} else {
				add(otherNode->smallKey, otherNode->smallValue);
				add(otherNode->largeKey, otherNode->largeValue);
				if(!(otherNode->isLeaf())) {
					copyHelper(otherNode->left.get());
					copyHelper(otherNode->mid.get());
					copyHelper(otherNode->right.get());
				}
			}
		}
		
		
		void split(Node23<K, V> *root) {
			unique_ptr<Node23<K, V>> p = unique_ptr<Node23<K, V>>(new Node23<K, V>);//RHS of = may be incorrect
			if(!(root->parent)) { //if the node we're trying to split is the root of the tree...
				p = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				p->isTwoNode = true;
				p->parent = nullptr;
				p->smallKey = root->midKey;
				p->smallValue = root->midValue;
				assert(p);
				//rootptr = move(p);	//set new node p's data to that of current root's mid,
									//then set p as the root with small and large as children of p.
			} else {
				//if root->parent->parent exists, p should be set to one of that nodes children
				if(root->parent->parent) {
					Node23<K, V> *grandma = root->parent->parent;
					assert(grandma);
					if(grandma->left.get() == root->parent) {//Case 1
						assert(grandma->left);
						p = move(grandma->left);
						assert(p);
					} else if(grandma->mid.get() == root->parent) {//Case 2
						assert(grandma->mid);
						p = move(grandma->mid);
						assert(p);
					} else if(grandma->right.get() == root->parent) {//Case 3
						assert(grandma->right);
						p = move(grandma->right);
						assert(p);
					}
				} else {
					assert(rootptr.get() == root->parent);
					p = move(rootptr);//case 4
					assert(p);
					assert(!rootptr);
				}
				assert(p.get() == root->parent);
			}
			
			unique_ptr<Node23<K, V>> n1 = unique_ptr<Node23<K, V>>(new Node23<K, V>);
			unique_ptr<Node23<K, V>> n2 = unique_ptr<Node23<K, V>>(new Node23<K, V>);
			assert(n1);
			assert(n2);
			
			p->left  = move(n1);
			p->right = move(n2);
			p->mid	 = nullptr;
			
			//n1 data setting
			n1->smallValue = root->smallValue;
			n1->smallKey = root->smallKey;
			n1->isTwoNode = true;
			n1->parent = p.get();
			
			//n2 data setting
			n2->smallValue = root->largeValue;
			n2->smallKey = root-> largeKey;
			n2->isTwoNode = true;
			n2->parent = p.get();
			
			if(!isLeaf(root)) {
				n1->left  = move(root-> left);
				n1->right = move(root->mid);
				n2->left  = move(root-> mid_r);
				n2->right = move(root->right);
			}
			
			p->midValue = root->midValue;
			p->midKey = root->midKey;
			bool fourNode = false;
			//V tempVal;
			//K tempKey;
			if(p->isTwoNode) {	//if parent is a two node, easy case.
				if(p->midKey < p->smallKey) {
				//case 1: p->mid is less than small, so small goes to large and mid goes to small
					p->largeKey = p->smallKey;
					p->largeValue = p->smallValue;
					p->smallKey = p->midKey;
					p->smallValue = p-> midValue;
				//pointer stuff:
					p->left = move(n1);
					p->right  = move(n2);
					// p->right is unchanged
				} else {
				//case 2: p->mid is greater than small, so we just put it in the right
					p->largeValue = p->midValue;
					p->largeKey = p->midKey;
				//pointer stuff:
					p->mid	 = move(n1);
					p->right = move(n2);
					// p->left is unchanged
				}
				p->isTwoNode = false;
			} else {	//if parent is a three node, hard case. recursive split required.
				fourNode = true;
				
				if(p->midKey < p->smallKey) {
				//case 1: p->mid < p->small, so we swap small and mid
					p->tempKey = p->smallKey;
					p->tempValue = p->smallValue;
					p->smallKey = p->midKey;
					p->smallValue = p-> midValue;
					p->midKey = p->tempKey;
					p->midValue = p->tempValue;
				//pointer stuff:
					// p->right is unchanged
					p->mid_r = move(p->mid);
					p->mid   = move(n2);
					p->left  = move(n1);
					
				} else if(p->midKey < p->largeKey) {
				//case 2: p->mid > p->small but less than p->large, so we dont move anything
				//pointer stuff:
					// p->right and p->left is unchanged
					p->mid_r = move(n2);
					p->mid   = move(n1);
				
				} else {
				//case 3: p->mid > p-large, last available case, so we swap mid and large
					p->tempKey = p->largeKey;
					p->tempValue = p->largeValue;
					p->largeKey = p->midKey;
					p->largeValue = p-> midValue;
					p->midKey = p->tempKey;
					p->midValue = p->tempValue;
				//pointer stuff:
					p->mid_r = move(n1);
					p->right = move(n2);
				}
					
			}
			if(!rootptr) {
				rootptr = move(p);
			
			} if(fourNode) {
				split(p.get());
			}
		}
				
			
				
		
				
		
};

#endif