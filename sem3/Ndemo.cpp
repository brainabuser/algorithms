#include <iostream>

using namespace std;

//Функция нахождения НОДа
int greatestCommonDivisor(int a, int b) {
    return (b == 0) ? a : (a, a % b);
}

int main() {
    int array[100000], n;
    cin >> n;
    //Вводим массив
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    int k;
    cin >> k;
    int barray[100000];
    for (int i = 0; i < n; ++i) {
        barray[i] = array[(i + k) % n];
    }
    //Выводим массив
    for (int i = 0; i < n; ++i) {
        cout << barray[i] << " ";
    }
    return 0;
}


