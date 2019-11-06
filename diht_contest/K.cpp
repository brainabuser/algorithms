#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    matrix[0][0] = 1;
    //Заполняем первый столбец и первую строку массива
    for (int i = 1; i < n; ++i) {
        matrix[0][i] = (i % 2 != 0) ? (matrix[0][i - 1] + 1) : ((i + 1) * (i + 1));
        matrix[i][0] = (i % 2 != 0) ? ((i + 1) * (i + 1)) : (matrix[i - 1][0] + 1);
    }
    //Изменяя k, движемся по диагонали
    for (int k = 1; k < n; ++k) {
        for (int i = k; i < n; ++i) {
            matrix[k][i] = matrix[k - 1][i] + ((i % 2 != 0) ? 1 : -1);
            matrix[i][k] = matrix[i][k - 1] + ((i % 2 != 0) ? -1 : 1);
        }
    }
    //Выводим массив
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}