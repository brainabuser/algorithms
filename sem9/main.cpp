#include <iostream>

using namespace std;

int main() {
    int array[3] = {3, 2, 1};
    int *p1 = array;
    int *p2 = array + 1;
    int *p3 = array + 2;
    cout << *p1 << endl;
    cout << *p2 << endl;
    cout << *p3 << endl;
    return 0;
}