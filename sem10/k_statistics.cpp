#include <iostream>

using namespace std;

int kStatistics(int *array, int left, int right, int k);

int main() {
    int a[5] = {1, 2, 2, 3, 1};
    int k;
    cin >> k;
    cout << kStatistics(a, 0, 4, k) << endl;
    return 0;
}

int partition(int *array, const int &left, const int &right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (array[j] <= pivot) {
            ++i;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[right]);
    return i + 1;
}

int randomizedPartition(int *array, const int &left, const int &right) {
    int i = left + rand() % (right - left + 1);
    swap(array[i], array[right]);
    return partition(array, left, right);
}

int kStatistics(int *array, int left, int right, int k) {
    int pivot = randomizedPartition(array, left, right);
    if (k < pivot) {
        return kStatistics(array, left, pivot - 1, k);
    } else if (k > pivot) {
        return kStatistics(array, pivot + 1, right, k);
    } else {
        return array[k];
    }
}
