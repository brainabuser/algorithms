#include <iostream>

using namespace std;

void printHeap(int *heap, int heap_size);

void heapSort(int *heap, int heap_size);

int main() {
    int heap_size;
    cin >> heap_size;
    int *heap = new int[heap_size];
    for (int i = 0; i < heap_size; ++i) {
        cin >> heap[i];
    }
    heapSort(heap, heap_size);
    printHeap(heap, heap_size);
    delete[] heap;
    return 0;
}

int getLeftChild(int index) {
    return 2 * index + 1;
}

int getRightChild(int index) {
    return 2 * index + 2;
}

int siftDown(int *heap, int heap_size, int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int max_index;
    while (left < heap_size && (heap[index] < heap[left] || heap[index] < heap[right])) {
        if (max(heap[left], heap[right]) > heap[index] && right < heap_size) {
            max_index = (heap[left] >= heap[right]) ? left : right;
        } else {
            max_index = (heap[left] > heap[index]) ? left : index;
        }
        if (max_index != index) {
            swap(heap[index], heap[max_index]);
            index = max_index;
        } else {
            break;
        }
        left = getLeftChild(index);
        right = getRightChild(index);
    }
    return index + 1;
}

void buildHeap(int *heap, int heap_size) {
    int limit = heap_size / 2 - 1;
    for (int i = limit; i >= 0; --i) {
        siftDown(heap, heap_size, i);
    }
}

int extractMax(int *heap, int &heap_size) {
    int elem = heap[0];
    --heap_size;
    swap(heap[0], heap[heap_size]);
    siftDown(heap, heap_size, 0);
    return elem;
}

void heapSort(int *heap, int heap_size) {
    buildHeap(heap, heap_size);
    int curr_size = heap_size;
    for (int i = 0; i < heap_size; ++i) {
        extractMax(heap, curr_size);
    }
}

void printHeap(int *heap, int heap_size) {
    for (int i = 0; i < heap_size; ++i) {
        cout << heap[i] << ' ';
    }
    cout << endl;
}