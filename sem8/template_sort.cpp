#include <iostream>

using namespace std;

template <typename T>
void readArray(T *array, const int &size);

template <typename T>
void sortArray(T *array, const int &size);

template <typename T>
void printArray(T *array, const int &size);

int main() {
    int n;
    cin >> n;
//    int *array = new int[n];
//    double *array = new double[n];
    float *array = new float[n];
    readArray(array, n);
    sortArray(array, n);
    printArray(array, n);
    delete[] array;
    return 0;
}

template <typename T>
void readArray(T *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

template <typename T>
void sortArray(T *array, const int &size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
}

template <typename T>
void printArray(T *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << ' ';
    }
}
