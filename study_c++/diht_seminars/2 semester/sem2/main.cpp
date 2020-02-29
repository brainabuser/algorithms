#include <iostream>

using namespace std;

class Complex {
  private:
    float real;
    float im;
  public:
    Complex() = default;

    explicit Complex(float first, float second = 0) {//первый аргумент ТОЛЬКО float
        real = first;
        im = second;
    }

    float getReal() const {
        return real;
    }

    float getIm() const {
        return im;
    }

    ~Complex();//В основном для "зачистки" динамической памяти

    Complex &operator=(const Complex &that) {//Переопределяем оператор присваивания
        if (this == &that) {
            return *this;
        }
        this->~Complex();
    }
};

int main() {
    Complex number(2, 3);
    Complex number1;
    cout << number.getReal() << ":" << number.getIm() << endl;
    cout << number1.getReal() << ":" << number1.getIm() << endl;
    return 0;
}