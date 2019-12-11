#include <iostream>

using namespace std;

int kStatistic(int *array, int left, int right, int k);

int main() {
    int n, k;
    cin >> n >> k;
    int *array = new int[n];
    cin >> array[0] >> array[1];
    for (int i = 2; i < n; ++i) {
        array[i] = (123 * array[i - 1] + 45 * array[i - 2]) % (10000000 + 4321);
    }
    cout << kStatistic(array, 0, n - 1, k - 1) << endl;
    delete[] array;
    return 0;
}

int partition(int *array, const int &left, const int &right) {
    int pivot = array[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            ++i;
        } while (array[i] < pivot);
        do {
            --j;
        } while (array[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(array[i], array[j]);
    }
}

int kStatistic(int *array, int left, int right, int k) {
    int pivot = partition(array, left, right);
    if (k < pivot) {
        return kStatistic(array, left, pivot, k);
    } else if (k > pivot) {
        return kStatistic(array, pivot + 1, right, k);
    } else {
        return array[k];
    }
}
