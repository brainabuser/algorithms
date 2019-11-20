#include <iostream>

#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

int main() {
    int n;
    cin >> n;
    Point *array = new Point[n];
    Point center_of_gravity = {0, 0};
    for (int i = 0; i < n; ++i) {
        cin >> array[i].x >> array[i].y;
        center_of_gravity.x += array[i].x / n;
        center_of_gravity.y += array[i].y / n;
    }
    delete[] array;
    cout << setprecision(15);
    cout << center_of_gravity.x << ' ' << center_of_gravity.y << endl;
    return 0;
}