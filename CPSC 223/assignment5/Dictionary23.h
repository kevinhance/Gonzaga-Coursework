// Kevin Hance and Mauricio Velazquez
// 11/13/2017
// CPSC 223
// HW #4

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
            //iterate through in pre-order, add every element
			copyHelper(other.rootptr.get());
        }

        Dictionary23& operator=(const Dictionary23 &other) {
            //destructor process (don't actually delete object)
			rootptr = nullptr;
			count = 0;
			//then same process as copy constructor
			copyHelper(other.rootptr.get());
			if(!(other.count == count)) {
				cout << "other.count: " << other.count << ", this count: " << count;
				assert(other.count == count);
			}
			return *this;
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
							leaf->isTwoNode = false;
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
			if(!(keyExists(key))) {
				throw DictionaryException("Key doesn't exist");
			} else {
				return getValueHelper(key, rootptr.get());
			}
        }

        // Return a key associated with the given value.  If no keys have value
        // associated with them, throws an exception
        K getKey(V value) const override {
			K returnKey;
			if(!(valueExists(value))) {
				throw DictionaryException("Value doesn't exist");
			} else if(valueExists(value)) {
				Node23<K, V> *tempptr = getKeyHelper(value, rootptr.get());
				
				if(!(tempptr->isTwoNode) && tempptr->largeValue == value) {
						returnKey = tempptr->largeKey;
				} else {
					returnKey = tempptr->smallKey;
				}
			}
			return returnKey;
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
				assert(rootptr.get());
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
			Node23<K, V> *node = findNode(key, rootptr.get());
			if(node) {
				cout << "node exists, smallKey = " << node->smallKey << endl;
				if(!isLeaf(node)) {
					//swap key and value in node with smallest key and value in the
					//in order successor node
					cout << "!isLeaf(node) conditional entered" << endl;
					//first, find in order successor node
					Node23<K, V> *inOrderSuccessor = findInOrderSuccessor(node);
					assert(inOrderSuccessor);
					K tempKey;
					V tempVal;
					cout << "inOrderSuccessor key, val: " << inOrderSuccessor->smallKey << ", "
						<< inOrderSuccessor->smallValue << endl;
					cout << "key were swapping that with:" << key << endl;
					if(node->isTwoNode || node->smallKey == key) {
						//easy swap
						tempKey = inOrderSuccessor->smallKey;
						tempVal = inOrderSuccessor->smallValue;
						inOrderSuccessor->smallKey = node->smallKey;
						inOrderSuccessor->smallValue = node->smallValue;
						node->smallKey = tempKey;
						node->smallValue = tempVal;
					} else {
						//check in node for correct key/value
						tempKey = inOrderSuccessor->smallKey;
						tempVal = inOrderSuccessor->smallValue;
						inOrderSuccessor->smallKey = node->largeKey;
						inOrderSuccessor->smallValue = node->largeValue;
						node->largeKey = tempKey;
						node->largeValue = tempVal;
					}
					
				}
			}
		}

        // Displays the dictionary on standard output
        void display() const override {
			displayHelper(rootptr.get());
			cout << endl;
        }

        // Returns the number of elements in the dictionary
        int size() const override {
            return count;
        }
//----------------------------------------------------------------End-of-public-member-functions/variables---------------------------------------------------------------------------------------------------------
    private:
        
		unique_ptr<Node23<K, V>> rootptr = nullptr;

        // Number of elements currently stored in the dictionary
        int count = 0;
		
		bool keyExistsHelper(K key, Node23<K, V> *root) const {
			if(!root) {
				throw DictionaryException("Key does not exist, tree is empty");
				return false;
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
					else //if(key > root->largeKey)
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
				else //if(key > root->largeKey)
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
						if(root->left && root->right) {
							returnVal = valueExistsHelper(val, root->left.get()) +
										valueExistsHelper(val, root->right.get());
						} else {
							return 0;
						}
					}
				} else {
					if(root->smallValue == val || root->largeValue == val)
						returnVal = 1;
					else {
						if(root->left && root->mid && root->right) {
							returnVal = valueExistsHelper(val, root->left.get()) +
										valueExistsHelper(val, root->mid.get()) +
										valueExistsHelper(val, root->right.get());
						} else {
							return 0;
						}
						// else, we've hit a leaf and the value isn't in this subtree
						// so we just return 0
					}
				}
			} else {
				throw DictionaryException("Node passed into valueExistsHelper() is nullptr");
				return 0;
			}
			return returnVal;
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
		
		Node23<K, V>* findNode(K key, Node23<K, V> *root) {
			try {
				if(!root) {
					throw DictionaryException("Root node is null");
				} else{
					if(!keyExists(key))
						throw DictionaryException("Key doesn't exist, node can't be found");
					else if(root->smallKey == key || ((!root->isTwoNode) && root->largeKey == key)) {
						//if the node we're looking at contains the target key, return it
						return root;
					} else if(root->isTwoNode) {
						if(key < root->smallKey && root->left)
							return findNode(key, root->left.get());
						else if(root->right)
							return findNode(key, root->right.get());
						else
							throw DictionaryException("Key exists, but couldn't be found. Final leaf: 2-node");
					} else {
						if(key < root->smallKey && root->left)
							return findNode(key, root->left.get());
						else if(key < root->largeKey && root->mid)
							return findNode(key, root->mid.get());
						else if (root->right)
							return findNode(key, root->right.get());
						else
							throw DictionaryException("Key exists, but couldn't be found. Final leaf: 3-node");
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
		}
		
		bool isLeaf(Node23<K, V> *node) const {
			bool returnBool = false;
			if(node && !(node->left)) {
				assert(!(node->right));
				returnBool = true;
			}
			return returnBool;
		}
				
		
		
		void split (Node23<K, V> *node) {
			if(!(node->parent)) { //if node is the root of the tree, easy case.
				unique_ptr<Node23<K, V>> p = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				p->isTwoNode = true;
				p->parent = nullptr;
				p->smallKey = node->midKey;
				p->smallValue = node->midValue;
				assert(p);
				
				//now that we have a unique pointer to p, we need the two child nodes
				unique_ptr<Node23<K, V>> n1 = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				unique_ptr<Node23<K, V>> n2 = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				assert(n1);
				assert(n2);
				
				
				//n1 data setting
				n1->smallValue = node->smallValue;
				n1->smallKey = node->smallKey;
				n1->isTwoNode = true;
				n1->parent = p.get();
				
				//n2 data setting
				n2->smallValue = node->largeValue;
				n2->smallKey = node->largeKey;
				n2->isTwoNode = true;
				n2->parent = p.get();
				
				//setting the pointers if the node is not a leaf node
				if(!isLeaf(node)) {
					n1->left  = move(node-> left);
					n1->mid	  = nullptr;
					n1->right = move(node->mid);
					n2->left  = move(node->mid_r);
					n2->mid	  = nullptr;
					n2->right = move(node->right);
					
					n1->left->parent = n1.get();
					n1->right->parent = n1.get();
					n2->left->parent = n2.get();
					n2->right->parent = n2.get();
				}
				//if the node IS a leaf, we should make sure all of the child-pointer are set to nullptr
				else {
					n1->left  = nullptr;
					n1->mid	  = nullptr;
					n1->right = nullptr;
					n2->left  = nullptr;
					n2->mid	  = nullptr;
					n2->right = nullptr;
				}
				
				//now that n1 and n2 are good to go, we transfer ownership to the parent
				p->left  = move(n1);
				p->right = move(n2);
				p->mid	 = nullptr;
				//p is the root of the tree, so we need to transfer ownership to the dictionary class itself
				rootptr = move(p);
				
			} else { //if node isn't the root of the tree, it has a parent
				//first we need a dumb pointer to the parent
				Node23<K, V> *p = node->parent;
				
				//now, we need to make and set values for n1 and n2
				unique_ptr<Node23<K, V>> n1 = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				unique_ptr<Node23<K, V>> n2 = unique_ptr<Node23<K, V>>(new Node23<K, V>);
				assert(n1);
				assert(n2);
				
				//n1 data setting
				n1->smallValue = node->smallValue;
				n1->smallKey = node->smallKey;
				n1->isTwoNode = true;
				n1->parent = p;
				
				//n2 data setting
				n2->smallValue = node->largeValue;
				n2->smallKey = node->largeKey;
				n2->isTwoNode = true;
				n2->parent = p;
				
				//setting the pointers if the node is not a leaf node
				if(!isLeaf(node)) {
					n1->left  = move(node-> left);
					n1->mid	  = nullptr;
					n1->right = move(node->mid);
					n2->left  = move(node->mid_r);
					n2->mid	  = nullptr;
					n2->right = move(node->right);
					
					n1->left->parent = n1.get();
					n1->right->parent = n1.get();
					n2->left->parent = n2.get();
					n2->right->parent = n2.get();
				}
				//if the node IS a leaf, we should make sure all of the child-pointer are set to nullptr
				else {
					n1->left  = nullptr;
					n1->mid	  = nullptr;
					n1->right = nullptr;
					n2->left  = nullptr;
					n2->mid	  = nullptr;
					n2->right = nullptr;
				}
				
				//now that n1 and n2 are good to go, we need to figure out where we put the middle value from node.
				//we know it'll go into the parent, but where it goes in the parent is dependant on the arity and
				//key values of the parent.
				bool fourNode = false;
				K tempKey;
				V tempVal;
				assert(p);
				assert(node);
				
				
				//first, if the parent is a two-node:
				if(p->isTwoNode) {	//if parent is a two node, easy case.
					if(node->midKey < p->smallKey) {
					//case 1: root->mid is less than p->small, so p->small goes to p->large and root->mid goes to small
						p->largeKey = p->smallKey;
						p->largeValue = p->smallValue;
						p->smallKey = node->midKey;
						p->smallValue = node->midValue;
					//pointer stuff:
						assert(p->right);
						p->left = move(n1);
						p->mid  = move(n2);
						// p->right is unchanged
					} else {
					//case 2: p->mid is greater than small, so we just put it in the right
						p->largeKey = node->midKey;
						p->largeValue = node->midValue;
					//pointer stuff:
						assert(p->left);
						p->mid	 = move(n1);
						p->right = move(n2);
						// p->left is unchanged
					}
					p->isTwoNode = false;
				} else {
					//three node case
					if(node->midKey < p->smallKey) {
						//case 1: p->mid < p->small, so we swap small and mid
						tempKey = p->smallKey;
						tempVal = p->smallValue;
						p->smallKey = node->midKey;
						p->smallValue = node->midValue;
						p->midKey = tempKey;
						p->midValue = tempVal;
						//pointer stuff:
						// p->right is unchanged
						p->mid_r = move(p->mid);
						p->mid   = move(n2);
						p->left  = move(n1);
						assert(p->right);
					}
					else if(node->midKey < p->largeKey) {
						//case 2: p->mid < p->large
						p->midKey = node->midKey;
						p->midValue = node->midValue;
						//pointer stuff:
						// p->right is unchanged
						p->mid_r = move(n2);
						p->mid   = move(n1);
						assert(p->left);
						assert(p->right);
					}
					else {
						//case 3: node->mid > p->large
						p->midKey = p->largeKey;
						p->midValue = p->largeValue;
						p->largeKey = node->midKey;
						p->largeValue = node->midValue;
						//pointer stuff:
						p->mid_r = move(n1);
						p->right = move(n2);
						assert(p->left);
						assert(p->mid);
					}
					fourNode = true;
					p->isTwoNode = false;
				}
				if(fourNode)
					split(p);
			}	
		}
		
		void copyHelper(Node23<K, V> *otherNode) {
			if(otherNode->isTwoNode) {
				add(otherNode->smallKey, otherNode->smallValue);
				if(!(isLeaf(otherNode))) {
					copyHelper(otherNode->left.get());
					copyHelper(otherNode->right.get());
				}
			} else {
				add(otherNode->smallKey, otherNode->smallValue);
				add(otherNode->largeKey, otherNode->largeValue);
				if(!(isLeaf(otherNode))) {
					copyHelper(otherNode->left.get());
					copyHelper(otherNode->mid.get());
					copyHelper(otherNode->right.get());
				}
			}
		}
		
		Node23<K, V>* findInOrderSuccessor(Node23<K, V> *node) {
			Node23<K, V> *returnNode;
			if(isLeaf(node->right.get())) {
				returnNode = node->right.get();
			} else {
				returnNode = findMinInTree(node->right.get());
			}
			return returnNode;
		}
			
		Node23<K, V>* findMinInTree(Node23<K, V> *node) {
			Node23<K, V> *returnNode;
			if(isLeaf(node->left.get()))
				returnNode = node->left.get();
			else {
				returnNode = findMinInTree(node->left.get());
			}
			return returnNode;
		}
};

#endif