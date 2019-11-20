#include <iostream>

using namespace std;

void readArray(int *array, const int &size);

void quickSort(int *array, const int &left, const int &right);

void printArray(int *array, const int &size, const char *discription);

int main() {
    cout << "Enter the number of elements in integer array:" << endl;
    int n;
    cin >> n;
    int *array = new int[n];
    cout << "Enter " << n << " elements of integer array:" << endl;
    readArray(array, n);
    printArray(array, n, "Unsorted integer array:");
    quickSort(array, 0, n - 1);
    printArray(array, n, "Sorted integer array:");
    delete[] array;
    return 0;
}

void readArray(int *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

int partition(int *array, const int &left, const int &right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (array[j] <= pivot) {
            ++i;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[right]);
    return i + 1;
}

int randomizedPartition(int *array, const int &left, const int &right) {
    int i = left + rand() % (right - left + 1);
    swap(array[i], array[right]);
    return partition(array, left, right);
}

void quickSort(int *array, const int &left, const int &right) {
    if (left < right) {
        int pivot = randomizedPartition(array, left, right);
        quickSort(array, left, pivot - 1);
        quickSort(array, pivot + 1, right);
    }
}

void printArray(int *array, const int &size, const char *discription) {
    cout << discription << endl;
    bool isFirst = true;
    cout << "[";
    for (int i = 0; i < size; ++i) {
        if (isFirst) {
            isFirst = false;
        } else {
            cout << ", ";
        }
        cout << array[i];
    }
    cout << "]\n\n";
}