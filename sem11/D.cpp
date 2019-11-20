#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

struct Point {
    double x, y, distance;
};

Point *sortArray(Point *array, const int &size);

void printArray(Point *array, const int &size);

int main() {
    int n;
    cin >> n;
    Point *array = new Point[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i].x >> array[i].y;
        array[i].distance = sqrt(pow(array[i].x, 2) + pow(array[i].y, 2));
    }
    printArray(sortArray(array, n), n);
    delete[] array;
    return 0;
}

Point *sortArray(Point *array, const int &size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j].distance > array[j + 1].distance) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
    return array;
}


void printArray(Point *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i].x << ' ' << array[i].y << endl;
    }
}