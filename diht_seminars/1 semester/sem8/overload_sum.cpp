#include <iostream>
#include <cstring>

using namespace std;

int mySum(int a, int b) {
    return a + b;
}

int mySum(int *array, const int &size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

char *mySum(char *a, char *b) {
    char *sum = new char[strlen(a) + strlen(b)];
    return strcat(strcpy(sum, a), b);
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int a = 2, b = 3;
    char first[] = "one";
    char second[] = "two";
    cout << "Two int numbers sum:" << endl << mySum(a,b) << endl;
    cout << "Integer array values sum:" << endl << mySum(array, 5) << endl;
    char *result = mySum(first, second);
    cout << "Char arrays values sum:" << endl << result << endl;
    delete[] result;
    return 0;
}