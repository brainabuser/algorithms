//
// Created by Vladimir on 19.04.2020.
//
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vector {
    long double x;
    long double y;
};

struct Line {
    long double a;
    long double b;
    long double c;
    Vector v;
};

long double getDistance(const Line &lhs, const Line &rhs);

long double vectorProduct(const Vector &lhs, const Vector &rhs);

bool isTheSame(const Line &lhs, const Line &rhs);

int main() {
    long double a, b, c;
    cin >> a >> b >> c;
    Line l1{a, b, c};
    l1.v = {b, -a};
    cin >> a >> b >> c;
    Line l2{a, b, c};
    l2.v = {b, -a};
    cout << fixed;
    cout << setprecision(7);
    cout << l1.v.x << ' ' << l1.v.y << endl;
    cout << l2.v.x << ' ' << l2.v.y << endl;
    long double det = vectorProduct(l1.v, l2.v);
    if (fabs(det) >= 10e-5) {
        long double x = -(l1.c * l2.b - l2.c * l1.b) / det;
        long double y = -(l1.a * l2.c - l2.a * l1.c) / det;
        cout << x << ' ' << y << endl;
    } else {
        if (isTheSame(l1, l2)) {
            cout << 0.0 << endl;
        } else {
            cout << getDistance(l1, l2) << endl;
        }
    }
    return 0;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

long double getDistance(const Line &l1, const Line &l2) {
    long double x;
    long double y;
    x = (l1.a != 0.0) ? -l1.c / l1.a : 0.0;
    y = (l1.a != 0.0) ? 0.0 : -l1.c / l1.b;
    return fabsl(l2.a * x + l2.b * y + l2.c) / sqrt(pow(l2.a, 2) + pow(l2.b, 2));
}

bool isTheSame(const Line &l1, const Line &l2) {
    Vector v1{l1.a, l1.c};
    Vector v2{l2.a, l2.c};
    Vector v3{l1.b, l1.c};
    Vector v4{l2.b, l2.c};
    Vector v5{l1.a, l1.b};
    Vector v6{l2.a, l2.b};
    return (vectorProduct(v1, v2) == 0.0)
           && (vectorProduct(v3, v4) == 0.0)
           && (vectorProduct(v5, v6) == 0.0);
}