#include <iostream>

using namespace std;

void readArray(int *array, const int &size);

void sort(int *array, const int &size);

void printArray(const int *array, const int &size);

int main() {
    cout << "Insertion sort algorithm:" << endl;
    int n;
    cout << "Enter the size of int array" << endl;
    cin >> n;
    int *array = new int[n];
    readArray(array, n);
    sort(array, n);
    printArray(array, n);
    delete[] array;
    return 0;
}

void readArray(int *array, const int &size) {
    cout << "Enter " << size << " values of int array" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

void sort(int *array, const int &size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
}

void printArray(const int *array, const int &size) {
    cout << "Sorted int array:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
}