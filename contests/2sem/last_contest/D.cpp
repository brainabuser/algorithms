//
// Created by Vladimir on 26.05.2020.
//

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class NumberList {
  private:
    struct Person {
        string email;
        set<string> numbers;
    };
    map<string, Person> name_to_person;
  public:
    void addPerson(const string &name, const string &number = "", const string &email = "") {
        if (name_to_person.count(name) != 0) {
            cout << "FAIL" << endl;
            return;
        }
        if (!number.empty() && !email.empty()) {
            name_to_person[name] = {email, {number}};
        } else if (number.empty()) {
            Person temp;
            temp.email = email;
            name_to_person[name] = temp;
        } else if (email.empty()) {
            Person temp;
            temp.numbers.insert(number);
            name_to_person[name] = temp;
        } else {
            name_to_person[name] = {};
        }
        cout << "DONE" << endl;
    }
    void addPhone(const string &name, const string &number) {
        if (name_to_person.count(name) != 0 && name_to_person.at(name).numbers.count(number) == 0) {
            name_to_person.at(name).numbers.insert(number);
            cout << "DONE" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }
    void replaceEmail(const string &name, const string &new_email) {
        if (name_to_person.count(name) != 0) {
            name_to_person.at(name).email = new_email;
            cout << "DONE" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }
    void replacePhone(const string &name, const string &new_phone, const string &old_phone) {
        if (name_to_person.count(name) != 0 && name_to_person.at(name).numbers.count(old_phone) != 0
            && name_to_person.at(name).numbers.count(new_phone) == 0) {
            name_to_person.at(name).numbers.erase(old_phone);
            name_to_person.at(name).numbers.insert(new_phone);
            cout << "DONE" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }
    void deletePerson(const string& name) {
        if (name_to_person.count(name) != 0) {
            name_to_person.erase(name);
            cout << "DONE" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }
    void deletePhone(const string& name, const string& phone) {
        if (name_to_person.count(name) != 0 && name_to_person.at(name).numbers.count(phone) != 0) {
            name_to_person.at(name).numbers.erase(phone);
            cout << "DONE" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }
    void printPerson(const string& name) {
        if (name_to_person.count(name) == 0) {
            cout << "FAIL" << endl;
        } else {
            cout << "Name: " << name << ';' << endl;
            if (!name_to_person.at(name).numbers.empty()) {
                cout << "Phones: ";
                int cnt = 1;
                for (const auto &item : name_to_person.at(name).numbers) {
                    cout << item;
                    if (!(cnt == name_to_person.at(name).numbers.size() ||
                          name_to_person.at(name).numbers.size() == 1)) {
                        cout << ", ";
                    }
                    ++cnt;
                }
                cout << ';' << endl;
            }
            if (!name_to_person.at(name).email.empty()) {
                cout << "Email: " << name_to_person.at(name).email << ';' << endl;
            }
        }
    }
};

bool containsDog(const string &line) {
    return line.find_first_of('@') != line.npos;
}

int main() {
    string line;
    NumberList nb;
    while (getline(cin, line)) {
        istringstream is(line);
        string command;
        is >> command;
        string number, email, name;
        if (command == "AddPerson") {
            is >> name;
            string first, second;
            if (!is.str().empty()) {
                is >> first;
                if (containsDog(first)) {
                    email = first;
                } else {
                    number = first;
                }
                if (!is.str().empty()) {
                    is >> second;
                    number = (containsDog(first)) ? second : first;
                    email = (containsDog(first)) ? first : second;
                }
            }
            nb.addPerson(name, number, email);
        } else if (command == "AddPhone") {
            is >> name >> number;
            nb.addPhone(name, number);
        } else if (command == "ReplaceEmail") {
            is >> name >> email;
            nb.replaceEmail(name, email);
        } else if (command == "ReplacePhone") {
            string new_number;
            is >> name >> number >> new_number;
            nb.replacePhone(name, new_number, number);
        } else if (command == "DeletePerson") {
            is >> name;
            nb.deletePerson(name);
        } else if (command == "PrintPerson") {
            is >> name;
            nb.printPerson(name);
        } else if (command == "DeletePhone") {
            is >> name >> number;
            nb.deletePhone(name, number);
        } else if (command == "Finish") {
            break;
        }
    }
    return 0;
};