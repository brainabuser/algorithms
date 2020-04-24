//
// Created by Vladimir on 24.04.2020.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
    long double x;
    long double y;
};

struct Vector {
    long double x;
    long double y;
};

long double getSquare(const vector<Point> &polygon);

int main() {
    int n;
    cin >> n;
    vector<Point> polygon;
    for (int i = 0; i < n; ++i) {
        Point temp{};
        cin >> temp.x >> temp.y;
        polygon.push_back(temp);
    }
    polygon.push_back(polygon.front());
    cout << fixed << setprecision(15);
    cout << getSquare(polygon) << endl;
    return 0;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

long double getTriangleSquare(const Vector &lhs, const Vector &rhs) {
    return 1. / 2 * vectorProduct(lhs, rhs);
}

long double getSquare(const vector<Point> &polygon) {
    vector<Vector> vectors;
    for (const auto & i : polygon) {
        vectors.push_back(Vector{i.x, i.y});
    }
    vectors.push_back(vectors.front());
    long double result = 0.0;
    for (size_t i = 1; i < vectors.size(); ++i) {
        result += getTriangleSquare(vectors.at(i - 1), vectors.at(i));
    }
    return fabsl(result);
}