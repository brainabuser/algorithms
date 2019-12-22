#include <iostream>

#include <cstring>

using namespace std;

#define max_request_size 12

#define capacity 200000

struct Node {
    int index = -1;
    int value = -1;
};

struct Heap {
    int size = 0;
    int *insert_numbers = new int[200000];
    Node *nodes = new Node[200000];
};

void insert(Heap *heap, int value, int insert_index);

void extractMin(Heap *heap);

void extractByIndex(Heap *heap, int insert_index);

void changeByIndex(Heap *heap, int insert_index, int new_value);

void getMin(Heap *heap);

void clear(Heap *heap, int extra_memory);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int request_number;
    cin >> request_number;
    Heap *my_heap = new Heap;
    for (int i = 0; i < request_number; ++i) {
        my_heap->insert_numbers[i] = -1;
        my_heap->nodes[i] = Node();
    }
    int insert_counter = 0;
    for (int i = 0; i < request_number; ++i) {
        char request[max_request_size];
        cin >> request;
        if (!strcmp(request, "insert")) {
            int value;
            cin >> value;
            insert(my_heap, value, insert_counter);
            ++insert_counter;
        } else if (!strcmp(request, "extract_min")) {
            extractMin(my_heap);
        } else if (!strcmp(request, "delete")) {
            int index;
            cin >> index;
            extractByIndex(my_heap, index - 1);
        } else if (!strcmp(request, "change")) {
            int index, new_value;
            cin >> index >> new_value;
            changeByIndex(my_heap, index - 1, new_value);
        } else if (!strcmp(request, "get_min")) {
            getMin(my_heap);
        } else if (!strcmp(request, "size")) {
            cout << my_heap->size << endl;
        } else if (!strcmp(request, "clear")) {
            clear(my_heap, insert_counter);
        }
    }
    delete[] my_heap->nodes;
    delete[] my_heap->insert_numbers;
    delete my_heap;
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
    Node *nodes = heap->nodes;
    int *inserts = heap->insert_numbers;
    int min_index = index;
    while ((min(right, left)) < heap->size &&
           nodes[inserts[index]].value > min(nodes[inserts[left]].value, nodes[inserts[right]].value)) {
        if (right < heap->size && nodes[inserts[right]].value < nodes[inserts[min_index]].value) {
            min_index = right;
        }
        if (left < heap->size && nodes[inserts[left]].value < nodes[inserts[min_index]].value) {
            min_index = left;
        }
        if (min_index != index) {
            swap(nodes[inserts[index]].index, nodes[inserts[min_index]].index);
            swap(inserts[index], inserts[min_index]);
            index = min_index;
        } else {
            break;
        }
        left = getLeftChild(index);
        right = getRightChild(index);
    }
    return index;
}

int siftUp(Heap *heap, int index) {
    Node *nodes = heap->nodes;
    int *inserts = heap->insert_numbers;
    while (index != 0 && nodes[inserts[index]].value < nodes[inserts[getParent(index)]].value) {
        swap(nodes[inserts[index]].index, nodes[inserts[getParent(index)]].index);
        swap(inserts[index], inserts[getParent(index)]);
        index = getParent(index);
    }
    return index;
}

void insert(Heap *heap, int value, int insert_index) {
    Node *nodes = heap->nodes;
    int *inserts = heap->insert_numbers;
    ++(heap->size);
    inserts[heap->size - 1] = insert_index;
    nodes[insert_index].value = value;
    nodes[insert_index].index = heap->size - 1;
    siftUp(heap, heap->size - 1);
    cout << "ok" << endl;
}

void extractMin(Heap *heap) {
    if (heap->size == 0) {
        cout << "error" << endl;
        return;
    }
    Node *nodes = heap->nodes;
    int *inserts = heap->insert_numbers;
    --(heap->size);
    int needed_insert = inserts[0];
    int value_to_delete = nodes[needed_insert].value;
    if (heap->size != 0) {
        swap(nodes[inserts[0]].index, nodes[inserts[heap->size]].index);
        swap(inserts[0], inserts[heap->size]);
        siftDown(heap, 0);
    }
    nodes[needed_insert].index = -1;
    cout << value_to_delete << endl;
}

void extractByIndex(Heap *heap, int insert_index) {
    Node *nodes = heap->nodes;
    int *inserts = heap->insert_numbers;
    int needed_index = nodes[insert_index].index;
    if (needed_index >= 0 && needed_index < heap->size && heap->size > 0) {
        --(heap->size);
        int needed_insert = inserts[needed_index];
        if (heap->size != 0) {
            swap(nodes[inserts[needed_index]].index, nodes[inserts[heap->size]].index);
            swap(inserts[needed_index], inserts[heap->size]);
            siftDown(heap, siftUp(heap, needed_index));
        }
        nodes[needed_insert].index = -1;
        cout << "ok" << endl;
        return;
    }
    cout << "error" << endl;
}

void changeByIndex(Heap *heap, int insert_index, int new_value) {
    Node *nodes = heap->nodes;
    int *inserts = heap->insert_numbers;
    int needed_index = nodes[insert_index].index;
    if (needed_index >= 0 && needed_index < heap->size && heap->size > 0) {
        nodes[inserts[needed_index]].value = new_value;
        siftDown(heap, siftUp(heap, needed_index));
        cout << "ok" << endl;
        return;
    }
    cout << "error" << endl;
}


void getMin(Heap *heap) {
    if (heap->size == 0) {
        cout << "error" << endl;
        return;
    }
    cout << heap->nodes[heap->insert_numbers[0]].value << endl;
}

void clear(Heap *heap, int extra_memory) {
    heap->size = 0;
    for (int i = 0; i < extra_memory; ++i) {
        heap->insert_numbers[i] = -1;
        heap->nodes[i] = Node();
    }
    cout << "ok" << endl;
}

void printHeap(Heap *heap) {
    cout << "indexes:" << endl;
    for (int i = 0; i < heap->size; ++i) {
        cout << heap->insert_numbers[i] << ' ';
    }
    cout << endl;
    cout << "heap:" << endl;
    for (int i = 0; i < heap->size; ++i) {
        cout << heap->nodes[heap->insert_numbers[i]].value << ' ';
    }
    cout << endl;
}