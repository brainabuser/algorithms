#include <iostream>

using namespace std;

int main() {
    int x, temp;
    int cnt = 0;
    cin >> x;
    while (x != 0){
        temp = x;
        cin >> x;
        if(x > temp){
            ++cnt;
        }
    }
    cout << cnt << endl;
    return 0;
}

