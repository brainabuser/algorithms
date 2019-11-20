#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int **array = new int *[n];
    for (int i = 0; i < n; ++i) {
        array[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> array[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            swap(array[i][j], array[j][i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}