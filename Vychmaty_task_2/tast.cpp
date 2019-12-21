#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;


float f1(vector<float> &z) {
    return z[2];
}

float f2(vector<float> &z) {
    return z[0] * sqrt(z[1]);
}


int main(void) {
    int Tk = 2;
    float h = 0.01;
    int N = (int) Tk / h - (int) 1 / h;
    int i, l;
    float F1, F2;
    vector<function<float(vector<float> &)> > f;
    f.push_back(f1);
    f.push_back(f2);
    vector<float> k1(2, 0);
    vector<float> k2(2, 0);
    vector<float> k3(2, 0);
    vector<float> k4(2, 0);
    vector<vector<float> > k(4, k1);
    float alpha1 = 0.1;
    float alpha2;
    vector<float> z;
    vector<float> v;

    while (true) {

        z = {1, 0, alpha1};
        //cout << z.at(0) << "	" << z.at(1) << endl;
        for (i = 1; i <= N; i++) {
            //z = {1, 0, alpha1};
            v = z;
            for (l = 0; l < 2; l++) {
                k[0][l] = f[l](v);
                //cout << k[0][l] << endl;

                v.at(0) = z.at(0) + (float) h / 2;
                v.at(1) = z.at(1) + k[0][l] * (float) h / 2;
                v.at(2) = z.at(2) + k[0][l] * (float) h / 2;
                k[1][l] = f[l](v);

                v.at(0) = z.at(0) + (float) h / 2;
                v.at(1) = z.at(1) + k[1][l] * (float) h / 2;
                v.at(2) = z.at(2) + k[1][l] * (float) h / 2;
                k[2][l] = f[l](v);

                v.at(0) = z.at(0) + h;
                v.at(1) = z.at(1) + k[2][l] * h;
                v.at(2) = z.at(2) + k[2][l] * h;
                k[3][l] = f[l](v);
            }
            z.at(1) = z.at(1) + (k[0][0] + 2 * k[1][0] + 2 * k[2][0] + k[3][0]) * (float) h / 6;
            z.at(2) = z.at(2) + (k[0][1] + 2 * k[1][1] + 2 * k[2][1] + k[3][1]) * (float) h / 6;
            z.at(0) = z.at(0) + h;
            //cout << z.at(0) << "	" << z.at(1) << endl;
        }
        F1 = z.at(1) - 2;

        z = {1, 0, alpha1 + h};
        for (i = 1; i <= N; i++) {

            v = z;
            for (l = 0; l < 2; l++) {
                k[0][l] = f[l](v);
                //cout << k[0][l] << endl;

                v.at(0) = z.at(0) + (float) h / 2;
                v.at(1) = z.at(1) + k[0][l] * (float) h / 2;
                v.at(2) = z.at(2) + k[0][l] * (float) h / 2;
                k[1][l] = f[l](v);

                v.at(0) = z.at(0) + (float) h / 2;
                v.at(1) = z.at(1) + k[1][l] * (float) h / 2;
                v.at(2) = z.at(2) + k[1][l] * (float) h / 2;
                k[2][l] = f[l](v);

                v.at(0) = z.at(0) + h;
                v.at(1) = z.at(1) + k[2][l] * h;
                v.at(2) = z.at(2) + k[2][l] * h;
                k[3][l] = f[l](v);
            }
            z.at(1) = z.at(1) + (k[0][0] + 2 * k[1][0] + 2 * k[2][0] + k[3][0]) * (float) h / 6;
            z.at(2) = z.at(2) + (k[0][1] + 2 * k[1][1] + 2 * k[2][1] + k[3][1]) * (float) h / 6;
            z.at(0) = z.at(0) + h;
            cout << z.at(0) << "	" << z.at(1) << endl;
        }
        F2 = z.at(1) - 2;
        //cout << "kek" << endl;
        alpha2 = alpha1 - h * (float) F1 / (F2 - F1);
        cout << F2 << endl;
        //cout << alpha2 << endl;
        if (abs(F2) < 0.01) {
            cout << alpha2 << endl;
            break;
        }
        alpha1 = alpha2;


    }

    return 0;
}