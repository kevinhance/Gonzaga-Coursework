// Practice/Notes for Final CPSC 223 Exam
// Kevin Hance

// 1.

	// Write the appropriate code to go where the comment says it
	// will go to implement a destructor. NOTE: I strongly suggest
	// creating a helper function to use with your destructor.
	
	template <class T>
	struct Node {
		T data;
		Node<T> *left = nullptr;
		Node<T> *right = nullptr;
	};

	template <class T>
	class Tree {
		public:
		// various tree functions, including add, remove, etc.

		// Your code goes here
		~Tree() {
			deleteTree(root);
		}
		
		
		private:
			Node<T> *root = nullptr;
			
			void deleteTree(Node<T> node) {
				if(node->left) 
					deleteTree(node->left);
				if(node->right)
					deleteTree(node->right);
				delete node;
				root = nullptr;
			}
	};
	
// 2. int countOccurrences() of item in a linkedlist with Node* next, head, and double data

	int countOccurrences(int item) {
		Node* navNode = head;
		return countOccHelper(item, navNode);
	}
	
	int countOccHelper(int item, Node* n) {
		if(n) {
			if(n->next)
				return (item == n->data) + countOccHelper(item, n->next);
			else
				return (item == n->data);
		} else 
			return 0;
	}
	
// 3. Add size() to singly Linked List using nodes

	int size() {
		Node* navNode = head;
		return sizeHelper(navNode);
	}
	
	int sizeHelper(Node* n) {
		if(n) 
			return 1 + sizeHelper(n->next);
		else
			return 0;
	}
	
// 4. Pop front for singly Linked List... etc

	int popFront() {
		int returnData = head
		Node* delNode = head;
		head = head->next;
		delete delNode;
		delNode = nullptr;
		return returnData;
	}
	
// 5. Destructor in header file and .cpp file:

	// Header
	~LinkedList();
	
	//CPP:
	~LinkedList {
		
	}
	
	void delHelper(Node* n) {
		if(n->next)
			delHelper(n->next);
		delete n;
		n = nullptr;
		return;
	}
	
// 6. do void print()
	
	void print() {
		printHelper(head);
	}
	
	void printHelper(Node* n){
		cout << n->data;
		if(n->next){
			cout << ", ";
			printHelper(n->next);
			return;
		} else {
			cout << ".";
			return;
		}
	}
	
// 7. implement "convert to array" function

	void convertToArray(int* array) {
		convertToArrayHelper(array, head, 0);
	}
	
	void printHelper(int* array, Node* n, int index){
		array[index] = n->data;
		if(n->next){
			convertToArrayHelper(array, n->next, (index + 1));
		return;
	}
	
// 8. bool isEmpty();

	bool isEmpty() {
		return (size() == 0);
	}
	
// 9. binary tree node, remove element from leaf node

	void removeLeaf(int item) {
		Node* delNode = findNode(item);
		Node* p = delNode->p;
		if(p->left == delNode)
			p->left = nullptr;
		else
			p->right = nullptr;
		delete delNode;
		delNode = nullptr;
	}
	
	Node* findNode(K key, Node* n) {
		if(key = n->key)
			return n;
		else if(key < n->key)
			return findNode(key, n->left);
		else
			return findNode(key, n->right);
	}

// 10. when given a pointer to a node, return pointer to it's in-order successor

	Node* findInOrderSuccessor(Node* node) {
		Node* returnNode;
		if(isLeaf(node->right)) 
			returnNode = node->right;
		 else 
			returnNode = findMinInTree(node->right);
		return returnNode;
	}
			
	Node* findMinInTree(Node* node) {
		Node* returnNode;
		if(isLeaf(node->left))
			returnNode = node->left;
		else 
			returnNode = findMinInTree(node->left);
		
		return returnNode;
	}
	
// 11. bool is2Node(RBNode* node)
	
	bool is2Node(RBNode* node) {
		if(!node->isRed) {
			return(
					!(node->left) ||
					!(node->left.get()->isRed));
		} else {
			return false;
		}
	}

// 12. void adjustRoot(RBNode* root)

	void adjustRoot(RBNode* root) {
		if(is2Node(root)) {
			return;
		} else {
			assert(node->left->isRed && node->right->isRed);
			node->left->isRed = false;
			node->right->isRed = false;
		}
		
	}
	
// 13. void adjustRoot(RBNode* root)

	void adjustRoot(RBNode* root) {
		if(root->is2Node) {
			if(	(root->left && root->left->is2Node) &&
				(root->right && root->right->is2Node)) {
				
				root->left->isRed = true;
				root->right->isRed = true;
				root->isRed = false;
					
			}
		}
	}










