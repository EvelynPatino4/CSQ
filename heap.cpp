#include "heap.h"

HEAP::HEAP(int size) : isMax(true), capacity(size), heapSize(0) {
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2 * index + 1;
}

int HEAP::rightChild(int index) {
    return 2 * index + 2;
}

int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert" << endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while (index != 0 && array[parent(index)] < array[index]) {
        swap(array[parent(index)], array[index]);
        index = parent(index);
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    array[0] = array[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // Search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete" << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    heapifyDown(index);
}

void HEAP::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heapSize && array[left] > array[largest])
        largest = left;
    if (right < heapSize && array[right] > array[largest])
        largest = right;

    if (largest != index) {
        swap(array[index], array[largest]);
        heapifyDown(largest);
    }
}

void HEAP::buildH(int arr[], int n) {
    if (n > capacity) {
        cout << "Input array is larger than heap capacity." << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        array[i] = arr[i];

    heapSize = n;

    for (int i = parent(heapSize - 1); i >= 0; i--)
        heapifyDown(i);
}

void HEAP::replace(int oldData, int newData) {
    int index = -1;
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == oldData) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't replace" << endl;
        return;
    }

    array[index] = newData;

    if (newData > oldData)
        heapifyUp(index);
    else
        heapifyDown(index);
}

void HEAP::heapSort(int arr[], int n) {
    buildH(arr, n); 

    for (int i = n - 1; i > 0; i--) {
        swap(array[0], array[i]); 
        heapSize--;
        heapifyDown(0); 
    }

   
    for (int i = 0; i < n; i++)
        arr[i] = array[i];
}

void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; 
    }

    cout << array[index] << endl;

    printHeap(leftChild(index), depth + 1);
}

void HEAP::switchMinMax() {
    
    isMax = !isMax;

    
    for (int i = parent(heapSize - 1); i >= 0; i--) {
        if (isMax) {
            heapifyDown(i);  // Max-heapify
        } else {
            heapifyDownMin(i);  // Min-heapify
        }
    }

    /
    cout << (isMax ? "Max heap" : "Min heap") << " active now." << endl;
}
