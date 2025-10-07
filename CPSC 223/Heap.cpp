#include "Heap.h"
#include <iostream>
#include <cassert>
#include <utility>

// Aaron's

using namespace std;

// Create an empty heap
Heap::Heap() {
    numItems = 0;
}

// Add an element into a heap, reheaping the heap as necessary
void Heap::add(double value) {
    assert(numItems < MAX_NUM_ITEMS);
    data[numItems] = value;
    bool haveSwapped = true;
    int index = numItems;
    while (haveSwapped && hasParent(index)) {
        haveSwapped = false;
        if (data[parentIndex(index)] < data[index]){
            swap(data[parentIndex(index)],data[index]);
            index = parentIndex(index);
            haveSwapped = true;
        }
    }

    numItems++;
}

// Return the largest element in the heap
double Heap::peek() const {
    assert(numItems > 0);
    return data[0];
}

// Returns the largest element in the heap and remove it from the heap,
// reheaping the heap as necessary
double Heap::pop() {
    assert(numItems > 0);
    int index = 0;
    double answer = data[0];
    data[0] = data[numItems - 1];  // swaps value with the last item in the heap
    numItems--;
    bool haveSwapped = true;
    while (haveSwapped && hasLeftChild(index)) {
        haveSwapped = false;
        int leftIdx = leftChildIndex(index);
        int rightIdx = rightChildIndex(index);
        if (hasRightChild(index)){
            if (data[leftIdx] > data[rightIdx]){
                swap(data[leftIdx],data[index]);
                //  if the left index is larger than the right, swap the value with the left
                index = leftIdx;
                haveSwapped = true;
            }else{
                swap(data[rightIdx],data[index]);
                // if the right index is larger than the left, swap the value with the right
                index = rightIdx;
                haveSwapped = true;
            }
        }else{
            if (data[leftIdx] > data[index]){
                swap(data[leftIdx],data[index]);
                index = leftIdx;
                haveSwapped = true;
            }
        }
    }

    return answer;
}

// Display the heap array
void Heap::printHeap() {
    cout << "Heap: ";
    for (int i=0; i<numItems; i++) {
        cout << data[i] << ", ";
    }
    cout << endl;
}

// Return the number of elements in the heap
int Heap::size() {
    return numItems;
}


// Given an index, return the index of the left child of that element
int Heap::leftChildIndex(int index) {
    return 2*index + 1;
}

// Given an index, return the index of the right child of that element
int Heap::rightChildIndex(int index) {
    return 2*index + 2;
}

// Given an index, return the index of the parent of that element
int Heap::parentIndex(int index) {
    return (index - 1)/2;
}

// Returns true if the passed-in element has a parent, false otherwise
bool Heap::hasParent(int index) {
    return index > 0;
}

// Returns true if the passed-in element has a left child, false otherwise
bool Heap::hasLeftChild(int index) {
    return leftChildIndex(index) < numItems;
}

// Returns true if the passed-in element has a right child, false otherwise
bool Heap::hasRightChild(int index) {
    return rightChildIndex(index) < numItems;
}
