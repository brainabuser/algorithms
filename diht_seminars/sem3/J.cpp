#include <iostream>

using namespace std;

int main() {
    int array[10000], n;
    cin >> n;
    cin >> array[0];
    int max = array[0];
    for (int i = 1; i < n; ++i) {
        cin >> array[i];
        if (array[i] > max) {
            max = array[i];
        }
    }
    cout << max << endl;
    return 0;
}


