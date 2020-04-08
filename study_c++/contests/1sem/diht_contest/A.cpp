#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    auto delta = (double)y1 / (y1 + y2) * (x2 - x1);
    cout  << setprecision(9) << fixed << x1 + delta<< endl;
    return 0;
}