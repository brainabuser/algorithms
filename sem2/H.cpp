#include <iostream>

using namespace std;

int main() {
    int x, max, ex_max = 0;
    cin >> x;
    max = x;
    do {
        cin >> x;
        if (x > max) {
            ex_max = max;
            max = x;
        }else if(x > ex_max){
            ex_max = x;
        }
    } while (x != 0);
    cout << ex_max << endl;
    return 0;
}

