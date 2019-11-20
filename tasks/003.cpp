#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int **array = new int *[n];
    for (int i = 0; i < n; ++i) {
        array[i] = new int[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> array[i][j];
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << array[j][i] << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}