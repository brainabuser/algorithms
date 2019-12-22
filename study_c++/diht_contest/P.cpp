#include <iostream>

using namespace std;

void readArray(long long *array, const int &size);

void sortArray(long long *array, const int &size);

void printNeededNumbers(long long *array, const int &size, const long long &number);

int main() {
    int n;
    long long number;
    cin >> n >> number;
    long long *a = new long long[n];
    readArray(a, n);
    sortArray(a, n);
    printNeededNumbers(a, n, number);
    delete[] a;
    return 0;
}

void readArray(long long *array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

void sortArray(long long *array, const int &size) {
    for (int i = 1; i < size; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array[j], array[j + 1]);
            --j;
        }
    }
}

void printNeededNumbers(long long *array, const int &size, const long long &number) {
    long long *elem = &array[0];
    long long *begin = &array[1];
    long long *end = &array[size - 1];
    long long *copy_begin = &array[1];
    long long *copy_end = &array[size - 1];
    long long sum = *begin + *elem + *end;
    //Инициализируем трх числа, с суммой которых впоследствии будем сравнивать остальные по близости к заданной нагрузки
    long long close_first = *begin, close_second = *elem, close_third = *end;
    long long close_sum = sum;
    while (elem != end) {
        while (copy_begin != copy_end) {
            sum = *copy_begin + *elem + *copy_end;
            if (abs(sum - number) < abs(close_sum - number)) {
                close_sum = sum;
                close_first = *copy_begin;
                close_second = *elem;
                close_third = *copy_end;
            }
            if (sum < number) {
                ++copy_begin;
            } else if (sum > number) {
                --copy_end;
            } else {
                break;
            }
        }
        ++elem;
        copy_begin = elem + 1;
        copy_end = end;
    }
    cout << close_first << ' ' << close_second << ' ' << close_third << endl;
    return 0;
}