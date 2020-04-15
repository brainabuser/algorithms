#include <iostream>

using namespace std;

void readArray(int **array, const int &n, const int &m);

void printArray(int **array, const int &n, const int &m);

int getSum(int **array, const int &n, const int &m);

int **getPrefixSumArray(int **array, const int &n, const int &m);

int main() {
    int n, m;
    cin >> n >> m;
    int **a = new int *[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[m];
    }
    readArray(a, n, m);
    int **result = getPrefixSumArray(a, n, m);
    printArray(result, n, m);
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
        delete[] result[i];
    }
    delete[] a;
    delete[] result;
    return 0;
}

void readArray(int **array, const int &n, const int &m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> array[i][j];
        }
    }
}

int getSum(int **array, const int &n, const int &m) {
    int result = 0;
    for (int i = 0; i <= m; ++i) {
        result += array[n][i];
    }
    return result;
}


int **getPrefixSumArray(int **array, const int &n, const int &m) {
    int **result = new int *[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new int[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i][j] = getSum(array, i, j) + ((i != 0) ? result[i - 1][j] : 0);
        }
    }
    return result;
}


void printArray(int **array, const int &n, const int &m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
}
