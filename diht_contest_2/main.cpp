#include <iostream>

#include <cstring>

using namespace std;

#define max_request_size 12

struct Node {
    int value;
    int insert_number;
};

struct Heap {
    int size;
    int capacity;
    Node *heap;
};

void extractMin(Heap *heap);

void insert(Heap *heap, Node new_node);

void extractByIndex(Heap *heap, int index);

void changeByIndex(Heap *heap, int index, int new_value);

void getMin(Heap *heap);

void clear(Heap *heap);

int main() {
    int request_number;
    cin >> request_number;
    Heap *heap = new Heap{0, request_number, new Node[request_number]};
    int insert_counter = 0;
    for (int i = 0; i < request_number; ++i) {
        char request[max_request_size];
        cin >> request;
        if (!strcmp(request, "insert")) {
            int value;
            cin >> value;
            insert(heap, Node{value, ++insert_counter});
        } else if (!strcmp(request, "extract_min")) {
            extractMin(heap);
        } else if (!strcmp(request, "delete")) {
            int insert_index;
            cin >> insert_index;
            extractByIndex(heap, insert_index);
        } else if (!strcmp(request, "change")) {
            int insert_index, new_value;
            cin >> insert_index >> new_value;
            changeByIndex(heap, insert_index, new_value);
        } else if (!strcmp(request, "get_min")) {
            getMin(heap);
        } else if (!strcmp(request, "size")) {
            cout << heap->size << endl;
        } else if (!strcmp(request, "clear")) {
            clear(heap);
        }
    }
    delete[] heap->heap;
    delete heap;
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

int siftDown(Heap *heap, int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    int min_index;
    while (left < heap->size &&
           (heap->heap[index].value > heap->heap[left].value || heap->heap[index].value > heap->heap[right].value)) {
        if (min(heap->heap[left].value, heap->heap[right].value) < heap->heap[index].value && right < heap->size) {
            min_index = (heap->heap[left].value < heap->heap[right].value) ? left : right;
        } else {
            min_index = (heap->heap[left].value < heap->heap[index].value) ? left : index;
        }
        if (min_index != index) {
            swap(heap->heap[index], heap->heap[min_index]);
            index = min_index;
        } else {
            break;
        }
        left = getLeftChild(index);
        right = getRightChild(index);
    }
    return index;
}

void extractMin(Heap *heap) {
    if (heap->size == 0) {
        cout << "error" << endl;
        return;
    }
    int elem = heap->heap[0].value;
    --(heap->size);
    if (heap->size != 0) {
        heap->heap[0] = heap->heap[heap->size];
        siftDown(heap, 0);
    }
    cout << elem << endl;
}

int siftUp(Heap *heap, int index) {
    while (index != 0 && heap->heap[index].value < heap->heap[getParent(index)].value) {
        swap(heap->heap[index], heap->heap[getParent(index)]);
        index = getParent(index);
    }
    return index;
}

void insert(Heap *heap, Node new_node) {
    ++(heap->size);
    heap->heap[heap->size - 1] = new_node;
    siftUp(heap, heap->size - 1);
    cout << "ok" << endl;
}

void extractByIndex(Heap *heap, int insert_index) {
    for (int i = 0; i < heap->size; ++i) {
        if (heap->heap[i].insert_number == insert_index) {
            --(heap->size);
            if (heap->size != 0) {
                swap(heap->heap[i], heap->heap[heap->size]);
                siftDown(heap, siftUp(heap, i));
            }
            cout << "ok" << endl;
            return;
        }
    }
    cout << "error" << endl;
}

void changeByIndex(Heap *heap, int insert_index, int new_value) {
    for (int i = 0; i < heap->size; ++i) {
        if (heap->heap[i].insert_number == insert_index) {
            heap->heap[i].value = new_value;
            siftDown(heap, siftUp(heap, i));
            cout << "ok" << endl;
            return;
        }
    }
    cout << "error" << endl;
}

void getMin(Heap *heap) {
    if (heap->size == 0) {
        cout << "error" << endl;
        return;
    }
    cout << heap->heap[0].value << endl;
}

void clear(Heap *heap) {
    delete[] heap->heap;
    heap->heap = new Node[heap->capacity];
    heap->size = 0;
    cout << "ok" << endl;
}


void printList(const Dequeue *dequeue) {
    Node *curr = dequeue->head;
    bool isFirst = true;
    cout << '[';
    while (curr) {
        if (isFirst) {
            cout << curr->value;
            isFirst = false;
        } else {
            cout << ", " << curr->value;
        }
        curr = curr->next;
    }
    cout << "]\n";
}