//
// Created by Vladimir on 22.04.2020.
//

#include <iostream>
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

bool isConvex(const vector<Point> &polygon);

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
    cout << (isConvex(polygon) ? "YES" : "NO") << endl;
    return 0;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

bool isConvex(const vector<Point> &polygon) {
    vector<Vector> vectors;
    for (size_t i = 1; i < polygon.size(); ++i) {
        vectors.push_back(Vector{polygon.at(i).x - polygon.at(i - 1).x,
                           polygon.at(i).y - polygon.at(i - 1).y});
    }
    vectors.push_back(vectors.front());
    short currS = 0, prevS = 0;
    for (size_t i = 1; i < vectors.size(); ++i) {
        long double result = vectorProduct(vectors.at(i - 1), vectors.at(i));
        if (fabsl(result) > 0.0) {
            short temp = currS;
            currS = (signbit(result)) ? -1 : 1;
            if (currS != prevS && prevS != 0) {
                return false;
            } else {
                prevS = temp;
            }
        }
    }
    return true;
}