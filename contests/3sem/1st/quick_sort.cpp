#include <iostream>

#include <vector>


using namespace std;

void readArray(vector<int> &array, const int &size);

void printArray(const vector<int> &array);

void quickSort(vector<int> &array, const int &left, const int &right);

int main() {
    int n;
    cin >> n;
    vector<int> array;
    array.reserve(n);
    readArray(array, n);
    quickSort(array, 0, n - 1);
    printArray(array);
    return 0;
}

void readArray(vector<int> &array, const int &size) {
    for (int i = 0; i < size; ++i) {
        int temp;
        cin >> temp;
        array.emplace_back(temp);
    }
}

void printArray(const vector<int> &array) {
    for (const auto &item : array) {
        cout << item << ' ';
    }
}

int partition(vector<int> &array, const int &left, const int &right) {
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

void quickSort(vector<int> &array, const int &left, const int &right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot);
        quickSort(array, pivot + 1, right);
    }
}