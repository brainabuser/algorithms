#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

double computePerimeter(Point p1, Point p2, Point p3){
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)) + sqrt(pow((p1.x - p3.x), 2) + pow((p1.y - p3.y), 2)) + sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2));
}

int main() {
    int n;
    cin >> n;
    Point *array = new Point[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i].x >> array[i].y;
    }
    double max_perimeter = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            for (int k = j; k < n; ++k) {
                double temp = computePerimeter(array[i], array[j], array[k]);
                if (temp > max_perimeter) {
                    max_perimeter = temp;
                }
            }
        }
    }
    delete[] array;
    cout << setprecision(15) << max_perimeter << endl;
    return 0;
}