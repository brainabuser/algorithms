//
// Created by Vladimir on 11.02.2020.
//

#ifndef INC_2_SEMESTER_STUDENT_H
#define INC_2_SEMESTER_STUDENT_H

class Student {

  public:
    const static int n = 3;
    static int amountGetYear;

  private:
    char name[40];
    int year;
    char department[10];
    const char university[5] = "MIPT";
    int marks[n];

    mutable double averageMark = 0;//может меняться в константных методах
    double countAverage() const;

  public:
    double getAverage() const;

    int getYear() const;

    void setYear(const int& currYear);

    void setName(const char *newName);

    const char *getName() const;

    const char *getDepartment() const;

    void setDepartment(const char *department);

    const int *getMarks() const;

    void setMarks(const int *marks);

    //Статические методы реализуются в хедерах
    static void increaseAmount() {
        ++amountGetYear;
    }
};

#endif //INC_2_SEMESTER_STUDENT_H
