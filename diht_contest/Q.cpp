#include <iostream>

#include <cstring>

using namespace std;

void readArray(char **array, const int &size);

void sortArray(char **array, const int &size, int *digitalRoots);

void printNDeleteArray(char **array, const int &size);

int computeDigitalRoot(char *line);

int main() {
    int n;
    cin >> n;
    cin.ignore();
    char **arrayOfStr = new char *[n];
    int *digitalRoots = new int[n];
    readArray(arrayOfStr, n);
    for (int i = 0; i < n; ++i) {
        digitalRoots[i] = computeDigitalRoot(arrayOfStr[i]);
    }
    sortArray(arrayOfStr, n, digitalRoots);
    delete[] digitalRoots;
    printNDeleteArray(arrayOfStr, n);
    return 0;
}

void readArray(char **array, const int &size) {
    for (int i = 0; i < size; ++i) {
        array[i] = new char[1001];
        cin.getline(array[i], 1001);
    }
}

int digitalRoot(int number) {
    return (number == 0) ? number : (number % 10 + digitalRoot(number / 10));
}

int totalDigitalRoot(int number) {
    int result = digitalRoot(number);
    return (result / 10 == 0) ? result : totalDigitalRoot(result);
}

int computeDigitalRoot(char *line) {
    int result = 0;
    int i = 0;
    while (line[i] != '\0') {
        result += line[i] - '0';
        ++i;
    }
    return totalDigitalRoot(result);
}

bool firstMoreThanSecond(char *lhs, char *rhs) {
    if (strlen(rhs) > strlen(lhs)) {
        return false;
    } else if (strlen(rhs) < strlen(lhs)) {
        return true;
    } else {
        for (size_t i = 0; i < strlen(lhs); ++i) {
            if ((lhs[i] - '0') > (rhs[i] - '0')) {
                break;
            } else if ((lhs[i] - '0') < (rhs[i] - '0')) {
                return false;
            }
        }
        return true;
    }
}

void sortArray(char **array, const int &size, int *digitalRoots) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (digitalRoots[j] > digitalRoots[j + 1]) {
                swap(array[j], array[j + 1]);
                swap(digitalRoots[j], digitalRoots[j + 1]);
            }
        }
    }
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if ((digitalRoots[j] == digitalRoots[j + 1]) && (firstMoreThanSecond(array[j], array[j + 1]))) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void printNDeleteArray(char **array, const int &size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << endl;
    }
    for (int i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] array;
}