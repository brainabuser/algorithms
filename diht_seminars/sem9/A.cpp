#include <iostream>

using namespace std;

void readArray(int *array, const int &size);

void printArray(int *array, const int &size);

void buildHeap(int *heap, int heap_size);

void sort(int *heap, int heap_size);

int main() {
    int array[100000], n;
    cin >> n;
    readArray(array, n);
//    cout << "Basic array:" << endl;
//    printArray(array, n);
    buildHeap(array, n);
//    cout << endl << "Basic heap:" << endl;
//    printArray(array, n);
    sort(array, n);
//    cout << endl << "Sorted array:" << endl;
    printArray(array, n);
    return 0;
}

void readArray(int *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

void printArray(int *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << ' ';
    }
}

int leftChild(int index) {
    return 2 * index + 1;
}

int rightChild(int index) {
    return 2 * index + 2;
}

void siftDown(int *heap, int index, int heap_size) {
    int left = leftChild(index);
    int right = rightChild(index);
    int max_index = index;
    if (left < heap_size && heap[left] > heap[max_index]) {
        max_index = left;
    }
    if (right < heap_size && heap[right] > heap[max_index]) {
        max_index = right;
    }
    if (max_index != index) {
        swap(heap[index], heap[max_index]);
        siftDown(heap, max_index, heap_size);
    }
}

void buildHeap(int *heap, int heap_size) {
    for (int i = heap_size / 2; i >= 0; --i) {
        siftDown(heap, i, heap_size);
    }
}

void sort(int *heap, int heap_size) {
    int curr_size = heap_size;
    for (int i = 0; i < heap_size; ++i) {
        swap(heap[0], heap[curr_size - 1]);
        --curr_size;
        siftDown(heap, 0, curr_size);
    }
}

