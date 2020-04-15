//
// Created by Vladimir on 18.02.2020.
//

class Student {
    int year;
    int math;
    const int id;
  public:
    Student(int y, int m,) : year(y), math(m), id(sId) {}//Список инициализации, необходим при инициализации констант

    Student(const Student &that);
};

Student::Student(const Student &that) {
    this->math = that.math;
    this->year = that.year;
}

int main(){
    return 0;
}
