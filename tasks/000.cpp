#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int **array = new int *[n];
    for (int i = 0; i < m; ++i) {
        array[i] = new int[n];
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> array[i][j];
        }
    }
    int j = 0, i = 0;
    while (j < n - 1 && i < m - 1) {
        if((array[i + 1][j] < array[i][j + 1] || j >= n - 1) && i < n - 1){
            cout << ' ' << "down";
            ++i;
        }else{
            cout << ' ' << "right";
            ++j;
        }
    }
    for (int k = 0; k < m; ++k) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}