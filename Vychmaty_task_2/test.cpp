#include <cmath>
#include <iostream>
#include <fstream>

#include <limits>

#include <vector>

using namespace std;

double getF1_alpha(const double &alpha, const double &step);

double getF_alpha(const double &alpha, const double &step);

double getF(const double &x, const double &y);

int main() {
    ofstream output("output.csv");
    cout << "Enter the error value" << endl;
    double error;
    cin >> error;
    double prev_alpha, curr_alpha;
    double y1, y0, x0, x1; //Граничные условия
    x0 = y0 = prev_alpha = 0.0;
    x1 = 1;
    y1 = 2;
    double t = 0.1;//Шаг
    double last_elem = numeric_limits<double>::max();

    vector<double> x(11), z(11);
    x[0] = 0.0;
    while (last_elem - y1 > error) {
        size_t x_size = x.size();
        for (size_t i = 0; i < x_size - 1; ++i) {
            x[i + 1] = x[i] + t;
            vector<double> bk(4);
            bk[0] = getF(x[i], z[i]);
            bk[1] = 2 * getF(x[i] + t / 2.0, z[i] + t / 2.0 * bk[0]);
            bk[2] = 2 * getF(x[i] + t / 2.0, z[i] + t / 2.0 * bk[1]);
            bk[3] = getF(x[i] + t, z[i] + t * bk[2]);
            size_t bk_size = bk.size();
            z[i + 1] = z[i];
            for (size_t j = 0; j < bk_size; ++j) {
                z[i + 1] += 1.0 / 6.0 * t * bk[j];
            }
        }
        last_elem = z[x_size - 1];
    }
    return 0;
}

double getF1_alpha(const double &alpha, const double &step) {

}

double getF_alpha(const double &alpha, const double &step) {

}

double getF(const double &x, const double &y) {
    return x * sqrt(y);
}