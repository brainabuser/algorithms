#include <iostream>

using namespace std;

struct Elem {
    int length;
    int time;
    int cnt = 0;
};

int main() {
    int size;
    cin >> size;
    Elem *array = new Elem[size];
    int temp1, temp2;
    cin >> temp1 >> temp2;
    array[0].time = temp1;
    array[0].length = temp2;
    int min_time, max_time;
    min_time = max_time = temp1;
    for (int i = 1; i < size; ++i) {
        cin >> temp1 >> temp2;
        array[i].time = temp1;
        array[i].length = temp2;
        if (temp1 < min_time) {
            min_time = temp1;
        }
        if (temp1 > max_time) {
            max_time = temp1;
        }
    }
    int limit = max_time - min_time + 1;
    for (int i = 0; i < limit; ++i) {

    }
    delete[] array;
    return 0;
}

