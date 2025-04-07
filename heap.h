#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class HEAP {
private:
    int* array;
    int capacity;
    int heapSize;

    int leftChild(int index);
    int rightChild(int index);
    int parent(int index);

    // These are for a Max Heap
    void heapifyUp(int index);
    void heapifyDown(int index); // for max-heap

    // Helper function for a Min Heap - only if you do the Extra Credit
    void heapifyDownMin(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heapSize && array[left] < array[smallest])
            smallest = left;
        if (right < heapSize && array[right] < array[smallest])
            smallest = right;

        if (smallest != index) {
            swap(array[index], array[smallest]);
            heapifyDownMin(smallest);
        }
    }

public:
    HEAP(int size);
    ~HEAP();

    void buildH(int arr[], int n); 
    void insertH(int data);
    void deleteMax();
    void deleteH(int data);
    int peek();

    void replace(int oldData, int newData);
    void heapSort(int arr[], int n);

    void printHeap(int index, int depth);

    void switchMinMax();  

    bool isMax = true; 
};

#endif
