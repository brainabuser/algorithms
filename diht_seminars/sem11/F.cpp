#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

double computeArea(Point p1, Point p2, Point p3) {
    double a = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
    double b = sqrt(pow((p1.x - p3.x), 2) + pow((p1.y - p3.y), 2));
    double c = sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2));
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
    int n;
    cin >> n;
    Point *array = new Point[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i].x >> array[i].y;
    }
    double max_area = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            for (int k = j; k < n; ++k) {
                double temp = computeArea(array[i], array[j], array[k]);
                if (temp > max_area) {
                    max_area = temp;
                }
            }
        }
    }
    delete[] array;
    cout << setprecision(15) << max_area << endl;
    return 0;
}