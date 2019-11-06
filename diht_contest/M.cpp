#include <iostream>

using namespace std;

void readArray(unsigned long long **array, const int &size);

void printArray(unsigned long long **array, const int &size);

unsigned long long **multiply(unsigned long long **a, unsigned long long **b, int n);

unsigned long long **matrixPower(unsigned long long **a, int n, int m);

int main() {
    int n;
    cin >> n;
    unsigned long long **a = new unsigned long long *[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new unsigned long long[n];
    }
    int degree;
    cin >> degree;
    readArray(a, n);
    a = matrixPower(a, n, degree);
    printArray(a, n);
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}

void readArray(unsigned long long **array, const int &size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> array[i][j];
        }
    }
}

unsigned long long **multiply(unsigned long long **a, unsigned long long **b, int n) {
    unsigned long long sum;
    unsigned long long **result = new unsigned long long *[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new unsigned long long[n];
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            sum = 0;
            for (int r = 0; r < n; ++r) {
                sum += a[j][r] * b[r][i];
            }
            result[j][i] = sum;
        }
    }
    return result;
}

unsigned long long **matrixPower(unsigned long long **a, int n, int m) {
    if (m == 1) {
        return a;
    }
    if (m % 2 != 0)
        return multiply(matrixPower(a, n, m - 1), a, n);
    else {
        a = matrixPower(a, n, m / 2);
        return multiply(a, a, n);
    }
}

void printArray(unsigned long long **array, const int &size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << array[i][j] << ' ';
        }
        cout << endl;
    }
}
