#include <iostream>

using namespace std;

bool Xor(const bool &x, const bool &y);

int main() {
    bool x, y;
    cin >> x >> y;
    cout << Xor(x, y) << endl;
    return 0;
}

bool Xor(const bool &x, const bool &y){
    return x^y;
}
