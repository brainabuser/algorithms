//
// Created by Vladimir on 18.02.2020.
//

#include <cstring>

using namespace std;

class MyString {
  private:
    char *str;
  public:
    explicit MyString(int length) { //explicit ждет только int, исключая приведение типов
        str = new char[length + 1];
    }

    explicit MyString(const char *line) {
        str = new char[strlen(line) + 1];
        strcpy(str, line);
    }

    MyString(char c) = delete;//Запрет на преобразование типа char -> MyString
};

int main() {
    MyString line("a");
    return 0;
}