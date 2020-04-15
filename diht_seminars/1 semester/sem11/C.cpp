#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

int main() {
    int n;
    cin >> n;
    Point *array = new Point[n];
    double diameter = 0.0;
    for (int i = 0; i < n; ++i) {
        cin >> array[i].x >> array[i].y;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            double temp = sqrt(pow((array[i].x - array[j].x), 2) + pow((array[i].y - array[j].y), 2));
            if(temp > diameter){
                diameter = temp;
            }
        }
    }
    delete[] array;
    cout << setprecision(15);
    cout << diameter << endl;
    return 0;
}