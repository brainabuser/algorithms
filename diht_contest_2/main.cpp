#include <iostream>
#include <cstring>

using namespace std;

struct Contestant {
    int grades = -1;
    int id = -1;
};

void readArray(Contestant *array, const int &size);

void printArray(Contestant *array, const int &size);

void quickSort(Contestant *array, const int &left, const int &right);

int main() {
    int n;
    cin >> n;
    auto *competitors = new Contestant[n];
    readArray(competitors, n);
    quickSort(competitors, 0, n - 1);
    printArray(competitors, n);
    delete[] competitors;
    return 0;
}

void readArray(Contestant *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i].id >> array[i].grades;
    }
}

void printArray(Contestant *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i].id << ' ' << array[i].grades << endl;
    }
}

int partition(Contestant *array, const int &left, const int &right) {
    int pivot = array[(left + right) / 2].grades;
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            ++i;
        } while (array[i].grades > pivot);
        do {
            --j;
        } while (array[j].grades < pivot);
        if (i >= j) {
            return j;
        }
        if (array[i].grades == array[j].grades) {
            if(array[i].id > array[j].id){
                swap(array[i].id, array[j].id);
            }else{
                swap(array[i].grades, array[j].grades);
            }
        } else {
            swap(array[i], array[j]);
        }
    }
}

void quickSort(Contestant *array, const int &left, const int &right) {
    if (left < right) {
        int pivot = partition(array, left, right);
        quickSort(array, left, pivot);
        quickSort(array, pivot + 1, right);
    }
}
