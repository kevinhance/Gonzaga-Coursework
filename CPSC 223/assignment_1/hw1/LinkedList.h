#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cassert>
#include <iostream>

//template<struct ListDataType>

struct LinkedNode {
	LinkedNode *next;
	ListDataType data;
};

template<class ListDataType>

class LinkedList {
public:
	// Create an empty linked list
	LinkedList();

	// Deallocates all items in this list
	~LinkedList();

	// Adds a new item to the beginning of the list
	void addFront(ListDataType item);

	// Adds a new item to the end of the list
	void addBack(ListDataType item);

	// Removes the first element of the list and then returns it
	ListDataType popFront();

	// Removes the last element of the list and then returns it
	ListDataType popBack();

	// Returns the size of the list
	ListDataType size();

	// Returns a count of the number of items equal to the passed-in item
	ListDataType itemCount(ListDataType item);

	// Displays the list on cout with items separated by spaces
	void display();
private:
	LinkedNode *head;
};

#endif
