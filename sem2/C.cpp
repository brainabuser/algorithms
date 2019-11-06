#include <iostream>

using namespace std;

int main() {
    int x, cnt;
    cnt = 0;
    double sum = 0.0;
    cin >> x;
    do {
        sum += x;
        ++cnt;
        cin >> x;
    } while (x != 0);
    cout << sum / cnt << endl;
    return 0;
}

