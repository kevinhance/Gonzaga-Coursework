#pragma once

const int MAX_NUM_ITEMS = 20;

class Heap {
public:
    // Create an empty heap
    Heap();

    // Add an element into a heap, reheaping the heap as necessary
    void add(double value);

    // Return the largest element in the heap
    double peek() const;

    // Returns the largest element in the heap and remove it from the heap,
    // reheaping the heap as necessary
    double pop();

    // Display the heap array
    void printHeap();

    // Return the number of elements in the heap
    int size();
private:
    // Given an index, return the index of the left child of that element
    int leftChildIndex(int index);

    // Given an index, return the index of the right child of that element
    int rightChildIndex(int index);

    // Given an index, return the index of the parent of that element
    int parentIndex(int index);

    // Returns true if the passed-in element has a parent, false otherwise
    bool hasParent(int index);

    // Returns true if the passed-in element has a left child, false otherwise
    bool hasLeftChild(int index);

    // Returns true if the passed-in element has a right child, false otherwise
    bool hasRightChild(int index);

    // Array containing the elements in the heap
    double data[MAX_NUM_ITEMS];

    // Number of elements currently being stored
    int numItems;
};