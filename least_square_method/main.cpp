#include <iostream>

#include <fstream>

#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream input("D:\\HARD WORK PAYS OFF\\Labs\\5 sem\\input.csv");
    if (!input.is_open()) {
        throw runtime_error("File not found.");
    }
    long double Sx, Sy, Sxy, Sx2, Sy2;
    Sx = Sy = Sxy = Sx2 = Sy2 = 0.0;
    int n;
    cout << "Enter the number of points:" << endl;
    cin >> n;
    auto *x =  new long double[n];
    auto *y =  new long double[n];
    for (int i = 0; i < n; ++i) {
        if (input) {
            input >> x[i];
            input.ignore(1);
            input >> y[i];
            cout << x[i] << "/" << y[i] << endl;
        }
        Sx += x[i] / n;
        Sy += y[i] / n;
        Sxy += x[i] * y[i] / n;
        Sx2 += x[i] * x[i] / n;
        Sy2 += y[i] * y[i] / n;
    }
    const long double b = (Sxy - Sx * Sy) / (Sx2 - Sx * Sx);
    const long double a = Sy - b * Sx;
    const long double delta_b = 1/sqrt(n) * sqrt((Sy2 - Sy * Sy) / (Sx2 - Sx * Sx) - b * b);
    const long double delta_a = delta_b * sqrt((Sx2) - (Sx * Sx));
    ofstream output("D:\\HARD WORK PAYS OFF\\Labs\\5 sem\\output.txt");
    output << "y = " << b;
    if (a > 0.0) {
        output << "*x+" << a << endl;
    } else if (a < 0.0) {
        output << "*x " << a << endl;
    }
    output << endl << "Error of b = " << delta_b << endl;
    output << endl << "Error of a = " << delta_a << endl;
    delete []x;
    delete []y;
    return 0;
}