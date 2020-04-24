//
// Created by Vladimir on 19.04.2020.
//
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vector {
    int head_x;
    int head_y;
    int tail_x;
    int tail_y;
    int x;
    int y;
};

long double scalarProduct(const Vector &lhs, const Vector &rhs);

long double getLength(Vector &v);

long double vectorProduct(const Vector &lhs, const Vector &rhs);

long double vectorProduct(const Vector &lhs, const Vector &rhs);

long double getTriangleSquare(const Vector &lhs, const Vector &rhs);

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    Vector v1{a, b, c, d, c - a, d - b};
    cin >> a >> b >> c >> d;
    Vector v2{a, b, c, d, c - a, d - b};
    cout << setprecision(7);
    cout << getLength(v1) << ' ' << getLength(v2) << endl;
    cout << v1.x + v2.x << ' ' << v1.y + v2.y << endl;
    cout << scalarProduct(v1, v2) << ' ' << vectorProduct(v1, v2) << endl;
    cout << getTriangleSquare(v1, v2) << endl;
    return 0;
}

long double scalarProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

long double getLength(Vector &v) {
    return sqrt(scalarProduct(v, v));
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

long double getTriangleSquare(const Vector &lhs, const Vector &rhs) {
    return 1. / 2 * abs(vectorProduct(lhs, rhs));
}