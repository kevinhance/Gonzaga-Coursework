#include <cassert>
#include <iostream>

#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
	head = nullptr;
}

LinkedList::~LinkedList() {
	while (head) {
		LinkedNode *tmp = head;
		head = head->next;
		delete tmp;
	}
}

void LinkedList::addFront(int item) {
	LinkedNode *node = new LinkedNode;
	node->data = item;
	node->next = head;
	head = node;
}

void LinkedList::addBack(int item) {
	LinkedNode *node = new LinkedNode;
	node->next = nullptr;
	node->data = item;
	if (head) {
		LinkedNode *p = head;
		addBackHelper(item, node, p);
		/*while (p->next) {
			p = p->next;
		}
		p->next = node;*/
	} else {
		head = node;
	}
}

void LinkedList::addBackHelper(int item, LinkedNode *node, LinkedNode p) {
	if (!(p->next)) {
		p->next = node;
	}
	else{
		addBackHelper(item, node, p->next);
	}
}

int LinkedList::popFront() {
	// It is an error if pop is called on an empty list
	assert(head);
	int answer = head->data;
	LinkedNode *tmp = head;
	head = head->next;
	delete tmp;
	return answer;
}

int LinkedList::popBack() {
	// It is an error if pop is called on an empty list
	assert(head);

	// If head is the only node, we need to delete that and set
	// head to be null
	if (!head->next) {
		int answer = head->data;
		delete head;
		head = nullptr;
		return answer;
	}

	// Otherwise, we need to find a node that lacks a next pointer, and
	// set the pointer to THAT node to be null.
	LinkedNode *node = head;
	while (node->next->next) {
		node = node->next;
	}
	int answer = node->next->data;
	delete node->next;
	node->next = nullptr;
	return answer;
}

int LinkedList::size() {
	int count = 0;
	LinkedNode *node = head;
	while (node) {
		count++;
		node = node->next;
	}
	return count;
}

int LinkedList::itemCount(int item) {
	int count = 0;
	LinkedNode *node = head;
	while (node) {
		if (node->data == item) {
			count++;
		}
		node = node->next;
	}
	return count;
}

void LinkedList::display() {
	cout << "List: ";
	LinkedNode *node = head;
	while (node) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl << endl;
}