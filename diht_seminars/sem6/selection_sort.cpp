#include <iostream>

using namespace std;

int main() {
    cout << "Selection sort algorithm:" << endl;
    int n;
    cout << "Enter the size of int array" << endl;
    cin >> n;
    int *array = new int[n];
    cout << "Enter " << n << " values of int array" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int min_i = i;
        for (int j = i + 1; j < n; ++j) {
            if (array[j] < array[min_i]) {
                min_i = j;
            }
        }
        swap(array[i], array[min_i]);
    }
    cout << "Sorted int array:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    delete[] array;
    return 0;
}