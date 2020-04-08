#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int size = n + 1;
    int *array = new int[size];
    array[0] = 0;
    array[1] = 0;
    for (int i = 2; i < size; ++i) {
        if (i % 6 == 0) {
            array[i] = min(min(array[i - 1], array[i / 3]), array[i / 2]) + 1;
        } else if (i % 3 == 0) {
            array[i] = min(array[i - 1], array[i / 3]) + 1;
        } else if (i % 2 == 0) {
            array[i] = min(array[i - 1], array[i / 2]) + 1;
        } else {
            array[i] = array[i - 1] + 1;
        }
    }
    cout << array[size - 1] << endl;
    delete[] array;
    return 0;
}