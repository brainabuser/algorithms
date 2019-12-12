#include <iostream>

using namespace std;

#define capacity 100000

struct Node {
    int time = -1;
    int length = -1;
    int end = -1;
};

struct Heap {
    int size = 0;
    Node *nodes = new Node[capacity];
};

void insert(Heap *heap, Node new_node);

int extractMin(Heap *heap);

void quickSort(Node *array, const int &left, const int &right);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int request_number;
    cin >> request_number;
    Heap *my_heap = new Heap;
    Node *array = new Node[request_number];
    for (int i = 0; i < request_number; ++i) {
        cin >> array[i].time >> array[i].length;
        array[i].end = array[i].time + array[i].length;
        my_heap->nodes[i] = Node();
    }
    quickSort(array, 0, request_number - 1);
    int max_load = 0;
    for (int i = 0; i < request_number; ++i) {
        while (my_heap->size > 0 && my_heap->nodes[0].end <= array[i].time) {
            extractMin(my_heap);
        }
        insert(my_heap, array[i]);
        if (max_load < my_heap->size) {
            max_load = my_heap->size;
        }
    }
    cout << max_load << endl;
    delete[] array;
    delete[] my_heap->nodes;
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
    int min_index = index;
    while ((min(right, left)) < heap->size &&
           nodes[index].end > min(nodes[left].end, nodes[right].end)) {
        if (right < heap->size && nodes[right].end < nodes[min_index].end) {
            min_index = right;
        }
        if (left < heap->size && nodes[left].end < nodes[min_index].end) {
            min_index = left;
        }
        if (min_index != index) {
            swap(nodes[index], nodes[min_index]);
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
    while (index != 0 && nodes[index].end < nodes[getParent(index)].end) {
        swap(nodes[index], nodes[getParent(index)]);
        index = getParent(index);
    }
    return index;
}

void insert(Heap *heap, Node new_node) {
    Node *nodes = heap->nodes;
    ++(heap->size);
    nodes[heap->size - 1] = new_node;
    siftUp(heap, heap->size - 1);
}

int extractMin(Heap *heap) {
    if (heap->size == 0) {
        return -1;
    }
    --(heap->size);
    Node *nodes = heap->nodes;
    int value = nodes[0].end;
    if (heap->size != 0) {
        swap(nodes[0], nodes[heap->size]);
        siftDown(heap, 0);
    }
    return value;
}

int partition(Node *array, const int &left, const int &right) {
    int pivot = array[(left + right) / 2].time;
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            ++i;
        } while (array[i].time < pivot);
        do {
            --j;
        } while (array[j].time > pivot);
        if (i >= j) {
            return j;
        }
        swap(array[i], array[j]);
    }
}

void quickSort(Node *array, const int &left, const int &right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot);
        quickSort(array, pivot + 1, right);
    }
}