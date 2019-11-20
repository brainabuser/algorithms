#include <iostream>

using namespace std;

struct Student {
    char name[100000];
    char surname[100000];
    double avg_grade = 0.0;
};

int main() {
    int n;
    cin >> n;
    Student *students = new Student[n];
    double max_avg = 0.0;
    for (int i = 0; i < n; ++i) {
        cin.ignore(1);
        cin.getline(students[i].surname, 100000, ' ');
        cin.getline(students[i].name, 100000, ' ');
        int math, phys, info;
        cin >> math >> phys >> info;
        double avg = (math + phys + info) / 3.0;
        students[i].avg_grade = avg;
        if (avg > max_avg) {
            max_avg = avg;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (students[i].avg_grade == max_avg) {
            cout << students[i].surname << ' ' << students[i].name << endl;
        }
    }
    delete[] students;
    return 0;
}