#include <iostream>

using namespace std;


//Функция перестановки значений аргументов
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

//Функция нахождения НОДа
int greatestCommonDivisor(int a, int b) {
    while (b != 0) {
        a = abs(a);
        b = abs(b);
        if (b < a) {
            swap(a, b);
        }
        b %= a;
    }
    return a;
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
    int gcd = greatestCommonDivisor(n, k);
    for (int i = 0; i < gcd; ++i) {
        int temp = array[i];
        int j = i;
        while (true) {
            int curr = (n + j - k) % n;
            if (curr == i) {
                break;
            }
            array[j] = array[curr];
            j = curr;
        }
        array[j] = temp;
    }
    //Выводим массив
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    return 0;
}