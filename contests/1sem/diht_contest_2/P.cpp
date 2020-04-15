#include <iostream>

using namespace std;

struct Constestant {
    int id = -1;
    int grades = -1;
};

void readArray(Constestant *array, const int &size);

void printArray(Constestant *array, const int &size);

void quickSort(Constestant *array, const int &left, const int &right);

int main() {
    int n;
    cin >> n;
    auto *array = new Constestant[n];
    readArray(array, n);
    quickSort(array, 0, n - 1);
    printArray(array, n);
    delete[] array;
    return 0;
}

void readArray(Constestant *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i].id >> array[i].grades;
    }
}

void printArray(Constestant *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i].id << ' ' << array[i].grades << endl;
    }
}

int partition(Constestant *array, const int &left, const int &right) {
    Constestant pivot = array[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            ++i;
        } while (array[i].grades > pivot.grades || (array[i].grades == pivot.grades && array[i].id < pivot.id));
        do {
            --j;
        } while (array[j].grades < pivot.grades || (array[j].grades == pivot.grades && array[j].id > pivot.id));
        if (i >= j) {
            return j;
        }
        swap(array[i], array[j]);
    }
}

void quickSort(Constestant *array, const int &left, const int &right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot);
        quickSort(array, pivot + 1, right);
    }
}
