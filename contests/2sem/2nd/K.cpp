//
// Created by Vladimir on 27.04.2020.
//

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    long double p, h_p, s, h_s;
    cin >> p >> h_p >> s >> h_s;
    cout << fixed << setprecision(7);
    if (s == p) {
        cout << s << endl;
    } else {
        long double x = ((s > p) ? (h_s - h_p) / (1. - p / s) : (h_s - h_p) / (p / s - 1.));
        long double tg_alpha = 1. / sqrt((pow(x / s, 2) - 1.));
        long double result = ((s > p) ? (x - h_s) * tg_alpha : (x + h_s) * tg_alpha);
        cout << ((result < 0.0) ? 0.0 : result) << endl;
    }
    return 0;
}

