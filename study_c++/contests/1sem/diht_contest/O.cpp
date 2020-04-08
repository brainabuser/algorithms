#include <iostream>

using namespace std;

void readArray(int *array, const int &size);

void sortArray(int *array, const int &size);

void printArray(int *array, const int &size);

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    readArray(array, n);
    sortArray(array, n);
    printArray(array, n);
    delete[] array;
    return 0;
}

void readArray(int *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

void sortArray(int *array, const int &size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
}

void printArray(int *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << ' ';
    }
}
