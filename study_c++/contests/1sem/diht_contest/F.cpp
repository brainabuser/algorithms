#include <iostream>

using namespace std;

void readArray(long long *array, const long long &size);

int main() {
    int n;
    cin >> n;
    long long *array = new long long[n];
    readArray(array, n);
    long long min_elem, max_elem, min_elem2, max_elem2, max_elem3;
    min_elem = 30000;
    min_elem2 = 30000;
    max_elem = -30000;
    max_elem2 = -30000;
    max_elem3 = -30000;
    for (int i = 0; i < n; ++i) {
        if (array[i] <= min_elem) {
            min_elem2 = min_elem;
            min_elem = array[i];
        } else if (array[i] < min_elem2) {
            min_elem2 = array[i];
        }
        if (array[i] >= max_elem) {
            max_elem3 = max_elem2;
            max_elem2 = max_elem;
            max_elem = array[i];
        } else if (array[i] >= max_elem2) {
            max_elem3 = max_elem2;
            max_elem2 = array[i];
        } else if (array[i] > max_elem3) {
            max_elem3 = array[i];
        }
    }
    if (min_elem * min_elem2 * max_elem > max_elem * max_elem2 * max_elem3) {
        cout << max_elem << ' ' << min_elem2 << ' ' << min_elem << endl;
    } else {
        cout << max_elem << ' ' << max_elem2 << ' ' << max_elem3 << endl;
    }
    delete[] array;
    return 0;
}

void readArray(long long *array, const long long &size) {
    for (long long i = 0; i < size; ++i) {
        cin >> array[i];
    }
}
