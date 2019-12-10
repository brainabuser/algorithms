#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *max = new int[n];
    int *array = new int[n];
    cin >> array[0];
    int max_size = 0;
    int temp_size = 1;
    int *temp = new int[n];
    temp[0] = array[0];
    for (int i = 1; i < n; ++i) {
        cin >> array[i];
    }
    delete[] array;
    delete[] temp;
    delete[] max;
    return 0;
}