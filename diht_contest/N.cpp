#include <iostream>

using namespace std;

void readArray(int *array, const int &size);

int countSwapsInSortOf(int *array, const int &size);

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    readArray(array, n);
    cout << countSwapsInSortOf(array, n) << endl;
    delete[] array;
    return 0;
}

void readArray(int *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

int countSwapsInSortOf(int *array, const int &size) {
    int swaps = 0;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
                ++swaps;
            }
        }
    }
    return swaps;
}
