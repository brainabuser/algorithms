#include <iostream>

using namespace std;

long long gcdExtended(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1; // Храним результаты промежуточных вызовов
    long long gcd = gcdExtended(b % a, a, &x1, &y1);
    // Обновляем значения "x" и "y"
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    long long x0, y0;
    long long ex_gcd = gcdExtended(a, b, &x0, &y0);
    if (c % ex_gcd != 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    long long x = x0 * c / ex_gcd, y = y0 * c / ex_gcd;
    long long k_x = b / ex_gcd;
    long long k_y = a / ex_gcd;
    while (a * x + b * y != c) {
        x += k_x;
        y -= k_y;
    }
    //Получаем какой-то положительный "x"
    while (x < 0) {
        x += k_x;
        y -= k_y;
    }
    //Получаем наименьший отрицательный "x"
    while (x > 0) {
        x -= k_x;
        y += k_y;
    }
    if (x != 0) {
        x += k_x;
        y -= k_y;
    }
    cout << x << ' ' << y << endl;
    return 0;
}