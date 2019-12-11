#include <iostream>

using namespace std;

void readArray(int *array, const int &size);

void printArray(int *array, const int &size);

void quickSort(int *array, const int &left, const int &right);

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    readArray(array, n);
    quickSort(array, 0, n - 1);
    printArray(array, n);
    delete[] array;
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

int partition(int *array, const int &left, const int &right) {
    int pivot = array[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            ++i;
        } while (array[i] < pivot);
        do {
            --j;
        } while (array[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(array[i], array[j]);
    }
}

void quickSort(int *array, const int &left, const int &right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot);
        quickSort(array, pivot + 1, right);
    }
}
