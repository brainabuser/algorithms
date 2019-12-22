#include <iostream>

using namespace std;

int l = 6;

int& a() {
    int b = 6;
    return b;
}

int main() {
    int& c = a();
    cout << c << endl;
    return 0;
}
