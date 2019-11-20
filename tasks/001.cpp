#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        sum += array[i];
    }
    int avg = sum / n;
    for (int i = 0; i < n; ++i) {
        if (array[i] >= avg) {
            cout << array[i] << ' ';
        }
    }
    delete[] array;
    return 0;
}