#include <iostream>

#include <cstring>

using namespace std;

#define max_request_size 12

#define capacity 200000

struct NodeMin {
    int insert = -1;
    int index_max = -1;
};

struct NodeMax {
    int insert = -1;
    int index_min = -1;
};

struct MinHeap {
    int size = 0;
    NodeMin *nodes = new NodeMin[capacity];
};

struct MaxHeap {
    int size = 0;
    NodeMax *nodes = new NodeMax[capacity];
};

struct DoubleHeap {
    int *values = new int[capacity];
    MinHeap *min_heap = new MinHeap;
    MaxHeap *max_heap = new MaxHeap;
};

void insert(DoubleHeap *heap, int value, int insert_index);

void extractMin(DoubleHeap *heap);

void extractMax(DoubleHeap *heap);

void getMin(DoubleHeap *heap);

void getMax(DoubleHeap *heap);

void clear(DoubleHeap *heap, int used_memory);

int size(DoubleHeap *heap);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int request_number;
    cin >> request_number;
    auto *my_heap = new DoubleHeap;
    for (int i = 0; i < request_number; ++i) {
        my_heap->values[i] = -1;
        my_heap->min_heap->nodes[i] = NodeMin();
        my_heap->max_heap->nodes[i] = NodeMax();
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
        }
        if (!strcmp(request, "extract_min")) {
            extractMin(my_heap);
        }
        if (!strcmp(request, "get_min")) {
            getMin(my_heap);
        }
        if (!strcmp(request, "extract_max")) {
            extractMax(my_heap);
        }
        if (!strcmp(request, "get_max")) {
            getMax(my_heap);
        }
        if (!strcmp(request, "size")) {
            cout << size(my_heap) << endl;
        }
        if (!strcmp(request, "clear")) {
            clear(my_heap, insert_counter);
        }
    }
    delete my_heap->min_heap;
    delete my_heap->max_heap;
    delete[] my_heap->values;
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

int minSiftDown(DoubleHeap *heap, int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    NodeMin *nodes = heap->min_heap->nodes;
    NodeMax *max_nodes = heap->max_heap->nodes;
    int *values = heap->values;
    int size = heap->min_heap->size;
    int min_index = index;
    while ((min(right, left)) < size &&
           values[nodes[index].insert] > min(values[nodes[left].insert], values[nodes[right].insert])) {
        if (right < size && values[nodes[right].insert] < values[nodes[min_index].insert]) {
            min_index = right;
        }
        if (left < size && values[nodes[left].insert] < values[nodes[min_index].insert]) {
            min_index = left;
        }
        if (min_index != index) {
            swap(nodes[index], nodes[min_index]);
            swap(max_nodes[nodes[index].index_max].index_min, max_nodes[nodes[min_index].index_max].index_min);
            index = min_index;
        } else {
            break;
        }
        left = getLeftChild(index);
        right = getRightChild(index);
    }
    return index;
}

int maxSiftDown(DoubleHeap *heap, int index) {
    int left = getLeftChild(index);
    int right = getRightChild(index);
    NodeMax *nodes = heap->max_heap->nodes;
    NodeMin *min_nodes = heap->min_heap->nodes;
    int *values = heap->values;
    int size = heap->min_heap->size;
    int max_index = index;
    while ((min(right, left)) < size &&
           values[nodes[index].insert] < min(values[nodes[left].insert], values[nodes[right].insert])) {
        if (right < size && values[nodes[right].insert] > values[nodes[max_index].insert]) {
            max_index = right;
        }
        if (left < size && values[nodes[left].insert] > values[nodes[max_index].insert]) {
            max_index = left;
        }
        if (max_index != index) {
            swap(nodes[index], nodes[max_index]);
            swap(min_nodes[nodes[index].index_min].index_max, min_nodes[nodes[max_index].index_min].index_max);
            index = max_index;
        } else {
            break;
        }
        left = getLeftChild(index);
        right = getRightChild(index);
    }
    return index;
}

int minSiftUp(DoubleHeap *heap, int index) {
    NodeMin *nodes = heap->min_heap->nodes;
    NodeMax *max_nodes = heap->max_heap->nodes;
    int *values = heap->values;
    while (index != 0 && values[nodes[index].insert] < values[nodes[getParent(index)].insert]) {
        swap(nodes[index], nodes[getParent(index)]);
        swap(max_nodes[nodes[index].index_max].index_min, max_nodes[nodes[getParent(index)].index_max].index_min);
        index = getParent(index);
    }
    return index;
}

int maxSiftUp(DoubleHeap *heap, int index) {
    NodeMax *nodes = heap->max_heap->nodes;
    NodeMin *min_nodes = heap->min_heap->nodes;
    int *values = heap->values;
    while (index != 0 && values[nodes[index].insert] > values[nodes[getParent(index)].insert]) {
        swap(nodes[index], nodes[getParent(index)]);
        swap(min_nodes[nodes[index].index_min].index_max, min_nodes[nodes[getParent(index)].index_min].index_max);
        index = getParent(index);
    }
    return index;
}

void insert(DoubleHeap *heap, int value, int insert_index) {
    NodeMax *max_nodes = heap->max_heap->nodes;
    NodeMin *min_nodes = heap->min_heap->nodes;
    int *values = heap->values;
    ++(heap->max_heap->size);
    ++(heap->min_heap->size);
    int size = heap->max_heap->size;
    values[insert_index] = value;
    max_nodes[size - 1].index_min = min_nodes[size - 1].index_max = size - 1;;
    min_nodes[size - 1].insert = max_nodes[size - 1].insert = insert_index;
    maxSiftUp(heap, size - 1);
    minSiftUp(heap, size - 1);
    cout << "ok" << endl;
}

void extractMin(DoubleHeap *heap) {
    if (size(heap) == 0) {
        cout << "error" << endl;
        return;
    }
    NodeMin *min_nodes = heap->min_heap->nodes;
    NodeMax *max_nodes = heap->max_heap->nodes;
    int *values = heap->values;
    int size = heap->min_heap->size;
    int value_to_delete = values[min_nodes[0].insert];
    int needed_index = min_nodes[0].index_max;
    --(heap->min_heap->size);
    --(heap->max_heap->size);
    if (size != 1) {
        swap(min_nodes[0], min_nodes[size - 1]);
        swap(max_nodes[min_nodes[0].index_max].index_min, max_nodes[min_nodes[size - 1].index_max].index_min);
        minSiftDown(heap, 0);
        swap(max_nodes[needed_index], max_nodes[size - 1]);
        swap(min_nodes[max_nodes[needed_index].index_min].index_max,
             min_nodes[max_nodes[size - 1].index_min].index_max);
        maxSiftDown(heap, maxSiftUp(heap, needed_index));
    }
    cout << value_to_delete << endl;
}

void extractMax(DoubleHeap *heap) {
    if (size(heap) == 0) {
        cout << "error" << endl;
        return;
    }
    NodeMin *min_nodes = heap->min_heap->nodes;
    NodeMax *max_nodes = heap->max_heap->nodes;
    int *values = heap->values;
    int size = heap->max_heap->size;
    int value_to_delete = values[max_nodes[0].insert];
    int needed_index = max_nodes[0].index_min;
    --(heap->min_heap->size);
    --(heap->max_heap->size);
    if (size != 1) {
        swap(max_nodes[0], max_nodes[size - 1]);
        swap(min_nodes[max_nodes[0].index_min].index_max, min_nodes[max_nodes[size - 1].index_min].index_max);
        maxSiftDown(heap, 0);
        swap(min_nodes[needed_index], min_nodes[size - 1]);
        swap(max_nodes[min_nodes[needed_index].index_max].index_min,
             max_nodes[min_nodes[size - 1].index_max].index_min);
        minSiftDown(heap, minSiftUp(heap, needed_index));
    }
    cout << value_to_delete << endl;
}

int size(DoubleHeap *heap) {
    return heap->max_heap->size;
}

void getMin(DoubleHeap *heap) {
    if (size(heap) == 0) {
        cout << "error" << endl;
        return;
    }
    cout << heap->values[heap->min_heap->nodes[0].insert] << endl;
}

void getMax(DoubleHeap *heap) {
    if (size(heap) == 0) {
        cout << "error" << endl;
        return;
    }
    cout << heap->values[heap->max_heap->nodes[0].insert] << endl;
}

void clear(DoubleHeap *heap, int used_memory) {
    heap->min_heap->size = 0;
    heap->max_heap->size = 0;
    for (int i = 0; i < used_memory; ++i) {
        heap->values[i] = -1;
        heap->min_heap->nodes[i] = NodeMin();
        heap->max_heap->nodes[i] = NodeMax();
    }
    cout << "ok" << endl;
}
