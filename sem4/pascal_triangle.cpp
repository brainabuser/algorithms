#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int **matrix = new int *[2 * n + 1];
    for (int i = 0; i < 2 * n + 1; ++i) {
        matrix[i] = new int[2 * n + 1];
    }

    int length = (2 * n + 1) * (2 * n + 1);

    for (int i = 0; i < length; ++i) {

    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}