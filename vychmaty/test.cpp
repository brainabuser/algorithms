#include <iostream>

#include <cmath>

#include <iomanip>

using namespace std;

long double
computePolynomValue(long double *coeffs, const int &size, long double *x, const long double &point);

void printArray(long double *array, const int &size, const char *discription);

int main() {
    int n;
    cout << "Enter the needed amount of nodes" << endl;
    cin >> n;
    long double step = 2.0 / (n - 1);
    const int size = n;
    //Задаем сетку из узловых точек и значения функции в них
    auto *x = new long double[size];
    auto *f_x = new long double[size];
    x[0] = -1.0;
    f_x[0] = sin(M_PI * (1.0 + x[0]));
    for (int i = 1; i < size; ++i) {
        x[i] = x[0] + i * step;
        f_x[i] = sin(M_PI * (1.0 + x[i]));
    }
    //Заполняем нулями
    auto **t_matrix = new long double *[size];
    for (int i = 0; i < size; ++i) {
        t_matrix[i] = new long double[size + 2]();
    }
    //Заполняем первые два стобца узловыми точками и соответствующими значениями функции
    for (int i = 0; i < size; ++i) {
        t_matrix[i][0] = x[i];
        t_matrix[i][1] = f_x[i];
    }
    for (int i = 1; i < size; ++i) {
        for (int j = 2; j <= i + 1; ++j) {
            t_matrix[i][j] =
                    (t_matrix[i][j - 1] - t_matrix[i - 1][j - 1]) / (t_matrix[i][0] - t_matrix[i - j + 1][0]);
        }
    }
    //Заполняем массив коэффициентов интерполянта Ньютона
    auto *newton_coeffs = new long double[size];
    for (int i = 0; i < size; ++i) {
        newton_coeffs[i] = t_matrix[i][i + 1];
    }
    //Чистим память, выделенную под треугольную матрицу коэффициентов
    for (int i = 0; i < size; ++i) {
        delete[] t_matrix[i];
    }
    delete[] t_matrix;
    //Вычисляем значения интерполянта Ньютона в узлах и заполняем соответствующий массив
    auto *p_values = new long double[size];
    for (int i = 0; i < size; ++i) {
        p_values[i] = computePolynomValue(newton_coeffs, size, x, x[i]);
    }
    printArray(x, size, "Nodes at [-1, 1]:");
    delete[] x;
    printArray(newton_coeffs, size, "Coefficients of Newton`s interpolant:");
    //Чистим память, выжеденную под массив коэффициентов
    //
    printArray(f_x, size, "Values of function f(x) = sin(PI * (1 + x)) at nodes:");
    delete[] f_x;
    printArray(p_values, size, "Values of Newton`s interpolant at nodes:");
    delete[] p_values;
    cout << "Enter the fineness of the split:" << endl;
    cin >> n;
    step = 2.0 / (n - 1);
    const int n_size = n;
    //Задаем равномерную сетку
    x = new long double[n_size];
    f_x = new long double[n_size];
    auto *c_x = new long double[n_size];
    auto *c_f_x = new long double[n_size];
    for (int k = 0; k < n_size; ++k) {
        x[k] = cos(M_PI * (2 * k - 1.0) / (2 * n_size));
        c_f_x[k] = sin(M_PI * (1.0 + x[k]));
    }
    x[0] = -1.0;
    f_x[0] = sin(M_PI * (1.0 + x[0]));
    for (int i = 1; i < n_size; ++i) {
        x[i] = x[0] + i * step;
        f_x[i] = sin(M_PI * (1.0 + x[i]));
    }
    p_values = new long double[n_size];
    auto *c_values = new long double[n_size];
    for (int i = 0; i < n_size; ++i) {
        p_values[i] = computePolynomValue(newton_coeffs, size, x, x[i]);
        c_values[i] = computePolynomValue(newton_coeffs, size, c_x, c_x[i]);
    }
    delete[] x;
    delete[] c_x;
    delete[] newton_coeffs;
    //Ищем модуль максимального отклонения значения интерполянта от значения функции на равномерной сетке
    long double p_max = 0.0;
    long double c_max = 0.0;
    for (int i = 0; i < n_size; ++i) {
        long double p_temp = fabsl(f_x[i] - p_values[i]);
        long double c_temp = fabsl(c_f_x[i] - c_values[i]);
        if (p_temp > p_max) {
            p_max = p_temp;
        }
        if (c_temp > c_max) {
            c_max = c_temp;
        }
    }
    delete[] f_x;
    delete[] c_f_x;
    delete[] p_values;
    delete[] c_values;
    cout << "Value of maximal deviation on uniform grid from the value of the original function is " << p_max << endl;
    cout << "Value of maximal deviation on Chebyshev`s grid from the value of the original function is " << c_max << endl;
    //    //Выводим треугольную матрицу
//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size + 2; ++j) {
//            cout << setw(10) << setprecision(3);
//            cout << t_matrix[i][j] << ' ';
//        }
//        cout << endl;
//    }
//    cout << endl;
    return 0;
}

long double
computePolynomValue(long double *coeffs, const int &size, long double *x, const long double &point) {
    long double result = 0.0;
    for (int i = 0; i < size; ++i) {
        long double product = 1.0;
        for (int j = 0; j < i; ++j) {
            product *= (point - x[j]);
        }
        result += coeffs[i] * product;
    }
    return result;
}

void printArray(long double *array, const int &size, const char *discription) {
    cout << discription << endl;
    bool isFirst = true;
    cout << "[";
    for (int i = 0; i < size; ++i) {
        if (isFirst) {
            isFirst = false;
        } else {
            cout << ", ";
        }
        cout << array[i];
    }
    cout << "]\n\n";
}