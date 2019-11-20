#include <iostream>

using namespace std;

int min(const int &, const int &, const int &c, const int &d);

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << min(a, b, c, d) << endl;
    return 0;
}

int min(const int &a, const int &b, const int &c, const int &d) {
    int first_min = (a > b) ? b : a;
    int second_min = (c > d) ? d : c;
    return (first_min < second_min) ? first_min : second_min;
}
