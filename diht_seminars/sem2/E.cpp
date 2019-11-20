#include <iostream>

using namespace std;

int main() {
    int x, max;
    cin >> x;
    max = x;
    do {
        cin >> x;
        if(x > max){
            max = x;
        }
    } while (x != 0);
    cout << max << endl;
    return 0;
}

