// Kevin Hance and Mauricio Velazquez
// CPSC 223 - Professor Schroeder
// Assignment 1
// 9/11/2017

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

using namespace std;

struct LinkedNode {
	LinkedNode *next;
	int data;
};

template<class ListDataType>
class LinkedList {
public:

	LinkedList(){
		head = nullptr;
	}


	~LinkedList(){
		while (head) {
		LinkedNode *tmp = head;
		head = head->next;
		delete tmp;
		}
	}


	void addFront(ListDataType item){
	LinkedNode *node = new LinkedNode;
	node->data = item;
	node->next = head;
	head = node;
	}



	void addBack(ListDataType item){
		LinkedNode *node = new LinkedNode;
		node->next = nullptr;
		node->data = item;
		assert(head);
		if (head){
			LinkedNode *p = head;
			addBackHelper(item, node, p);
		} else {
			head = node;
		}
	}

	


	ListDataType popFront(){
		assert(head);
		ListDataType answer = head->data;
		LinkedNode *tmp = head;
		head = head->next;
		delete tmp;
		return answer;
	}

	ListDataType popBack(){
		assert(head);

		if (!head->next) {
			ListDataType answer = head->data;
			delete head;
			head = nullptr;
			return answer;
		}

		LinkedNode *node = head;
		return popBackHelper(node);
	}

	

	ListDataType size() {
		ListDataType count = 0;
		LinkedNode *node = head;
		return sizeHelper(node, count);
	}

	
	
	ListDataType itemCount(ListDataType item){
		ListDataType count = 0;
		LinkedNode *node = head;

		return itemCountHelper(item, node, count);
	}

	


	void display(){
		cout << "List: ";
		LinkedNode *node = head;
		displayHelper(node);
		return;
	}

	
private:
	LinkedNode *head;
	
	void addBackHelper(int item, LinkedNode *node, LinkedNode *p)
	{
		if (!(p->next)){
			p->next = node;
		}
		else{
			addBackHelper(item, node, p->next);
		}
	}
	
	
	void displayHelper(LinkedNode *node){
		if(!(node)){
			cout << endl << endl;
			return;
		}
		else{
			cout << node->data << " ";
			return displayHelper(node->next);
		}
	}
	
	ListDataType itemCountHelper(ListDataType item, LinkedNode *node, ListDataType count){
		if(!(node)){
			return count;
		}
		else{
			if (node->data == item) {
				count++;
			}
			return itemCountHelper(item, node->next, count);
		}
	}
	
	ListDataType popBackHelper(LinkedNode *node){
		if(!(node->next->next))
		{
			ListDataType answer = node->next->data;
			delete node->next;
			node->next = nullptr;
			return answer;
		}
		else
		{
			return popBackHelper(node->next);
		}
	}
	
	ListDataType sizeHelper(LinkedNode *node, ListDataType count)
	{
		if(!(node)){
			return count;
		}
		else{
			return sizeHelper(node->next, count + 1);
		}
	}
};

#endif
