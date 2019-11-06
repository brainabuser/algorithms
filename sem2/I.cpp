#include <iostream>

using namespace std;

int main() {
    int x, max, cnt = 1;
    cin >> x;
    max = x;
    do {
        cin >> x;
        if(x > max){
            max = x;
            cnt = 1;
        }else if(x == max){
            ++cnt;
        }
    } while (x != 0);
    cout << cnt << endl;
    return 0;
}

