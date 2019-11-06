#include <iostream>

using namespace std;

int extract(int *heap, int &heap_size);

void insert(int *heap, int &heap_size, int elem);

int main() {
    int heap[100000], n, heap_size = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int command;
        cin >> command;
        if (command) {
            cout << extract(heap, heap_size) << endl;
        } else if (!command) {
            int elem;
            cin >> elem;
            insert(heap, heap_size, elem);
        }
    }
    return 0;
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

int extract(int *heap, int &heap_size) {
    int result = heap[0];
    swap(heap[0], heap[heap_size - 1]);
    --heap_size;
    siftDown(heap, 0, heap_size);
    return result;
}

void insert(int *heap, int &heap_size, int elem){
    heap[heap_size] = elem;
    ++heap_size;
    buildHeap(heap, heap_size);
}
