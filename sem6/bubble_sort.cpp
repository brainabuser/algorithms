#include <iostream>

using namespace std;

int main() {
    cout << "Bubble sort algorithm:" << endl;
    int n;
    cout << "Enter the size of int array" << endl;
    cin >> n;
    int *array = new int[n];
    cout << "Enter " << n << " values of int array" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
    cout << "Sorted int array:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    delete[] array;
    return 0;
}