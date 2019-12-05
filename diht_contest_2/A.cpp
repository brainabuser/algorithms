#include <iostream>

using namespace std;

int extractMax(int *heap, int &heap_size);

int insert(int *heap, int &heap_size, int capacity, int value);

enum RequestType {
    DELETE = 1, INSERT
};

int main() {
    int capacity, request_number;
    cin >> capacity >> request_number;
    int *heap = new int[capacity];
    int heap_size = 0;
    for (int i = 0; i < request_number; ++i) {
        RequestType request;
        int temp;
        cin >> temp;
        request = (RequestType) temp;
        switch (request) {
            case DELETE:
                cout << extractMax(heap, heap_size) << endl;
                break;
            case INSERT:
                cin >> temp;
                cout << insert(heap, heap_size, capacity, temp) << endl;
                break;
        }
    }
    for (int i = 0; i < heap_size; ++i) {
        cout << heap[i] << ' ';
    }
    delete[] heap;
    return 0;
}

int getLeftChild(int index) {
    return 2 * index + 1;
}

int getRightChild(int index) {
    return 2 * index + 2;
}

int getParent(int index) {
    return (index - 1) / 2;
}

int siftDown(int *heap, int index, int heap_size) {
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

int extractMax(int *heap, int &heap_size) {
    if (heap_size == 0) {
        return -1;
    } else if (heap_size == 1) {
        --heap_size;
        cout << heap_size << ' ';
        return heap[heap_size];
    }
    int elem = heap[0];
    --heap_size;
    swap(heap[0], heap[heap_size]);
    cout << siftDown(heap, 0, heap_size) << ' ';
    return elem;
}

int sifrUp(int *heap, int index) {
    while (index != 0 && heap[index] > heap[getParent(index)]) {
        swap(heap[index], heap[getParent(index)]);
        index = getParent(index);
    }
    return index + 1;
}

int insert(int *heap, int &heap_size, int capacity, int value) {
    if (heap_size >= capacity) {
        return -1;
    } else {
        ++heap_size;
        heap[heap_size - 1] = value;
        return sifrUp(heap, heap_size - 1);
    }
}