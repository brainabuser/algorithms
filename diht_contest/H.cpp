#include <iostream>

using namespace std;

void countFrequencies(int *array, int *amount, const int &size);

int findIndexMostFrequent(int *array, const int &size);

int main() {
    int n;
    cin >> n;
    int ages[100000];
    int amount[100000] = {0,};
    countFrequencies(ages, amount, n);
    int max_index = findIndexMostFrequent(amount, n);
    int min_elem = ages[max_index];
    for (int i = 0; i < n; ++i) {
        if (amount[i] == amount[max_index]) {
            min_elem = min(min_elem, ages[i]);
        }
    }
    cout << min_elem << endl;
    return 0;
}

int indexIfContains(const int &elem, int *array, const int &size) {
    for (int j = 0; j < size; ++j) {
        if (array[j] == elem) {
            return j;
        }
    }
    return -1;
}

void countFrequencies(int *array, int *amount, const int &size) {
    int j = -1;
    for (int i = 0; i < size; ++i) {
        int temp;
        cin >> temp;
        int index = indexIfContains(temp, array, i);
        if (index == -1) {
            ++j;
            array[j] = temp;
            ++amount[j];
        } else {
            ++amount[index];
        }
    }
}

int findIndexMostFrequent(int *array, const int &size) {
    int max_index = 0;
    int max = array[max_index];
    for (int i = 1; i < size; ++i) {
        if (array[i] > max) {
            max = array[i];
            max_index = i;
        }
    }
    return max_index;
}