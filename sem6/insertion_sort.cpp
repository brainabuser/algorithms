#include <iostream>

using namespace std;

int main() {
    cout << "Insertion sort algorithm:" << endl;
    int n;
    cout << "Enter the size of int array" << endl;
    cin >> n;
    int *array = new int[n];
    cout << "Enter " << n << " values of int array" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
    cout << "Sorted int array:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    delete[] array;
    return 0;
}