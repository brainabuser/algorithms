#include<iostream>
#include<map>
#include<sstream>
#include<iomanip>
#include<set>
#include<string>

using namespace std;

class Date {
public:
    int GetYear() const{
        return this->year;
    }
    int GetMonth() const{
        return this->month;
    }
    int GetDay() const{
        return this->day;
    }
    explicit Date(const string& date){
        stringstream input(date);
        int year, month, day;
        char del1, del2;
        if(!(input >> year >> del1 >> month >> del2 >> day) || del1 != '-' || del2 != '-' || input.peek() != -1)
        {
            throw invalid_argument("Wrong date format: " + date);
        }
        if(month <= 0 || month > 12){
            throw invalid_argument("Month value is invalid: " + to_string(month));
        }
        if(day <= 0 || day > 31){
            throw invalid_argument("Day value is invalid: " + to_string(day));
        }
        this->year = year;
        this->month = month;
        this->day = day;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear() == rhs.GetYear()){
        if(lhs.GetMonth() == rhs.GetMonth()){
            return lhs.GetDay() < rhs.GetDay();
        }else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }else {
        return lhs.GetYear() < rhs.GetYear();
    }
}

class Database {
public:
    void AddEvent(const Date& date, const string& event){
        dateToEvents[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event){
        try{
            for(const string& s : dateToEvents.at(date)){
                if(s == event){
                    if(dateToEvents.at(date).size() == 1){
                        dateToEvents.at(date).clear();
                        dateToEvents.erase(date);
                        return true;
                    }else{
                        return dateToEvents.at(date).erase(event);
                    }
                }
            }
            return false;
        }catch(out_of_range& e){
            return false;
        }
    }
    int DeleteDate(const Date& date){
        try{
            int amount = dateToEvents.at(date).size();
            dateToEvents.at(date).clear();
            dateToEvents.erase(date);
            return amount;
        }catch(out_of_range& e){
            return 0;
        }
    }

    void Find(const Date& date) const{
        try{
            for(const string& s : dateToEvents.at(date)){
                cout << s << endl;
            }
        }catch(out_of_range& e){
            return;
        }
    }

    void Print() const{
        for(const auto& d : dateToEvents){
            for(const string& s : d.second)
                cout << setw(4) << setfill('0') << d.first.GetYear() << '-'
                     << setw(2) << setfill('0') << d.first.GetMonth() << '-'
                     << setw(2) << setfill('0') << d.first.GetDay() << ' '
                     << s << endl;
        }
    }
private:
    map<Date, set<string>> dateToEvents;
};

int main() {
    Database db;
    string command;
    while (getline(cin, command)) {
        try{
            if(command.empty()){
                continue;
            }
            string request;
            stringstream input(command);
            getline(input, request, ' ');
            if(request == "Add"){
                string date, event;
                getline(input, date, ' ');
                getline(input, event);
                db.AddEvent(Date(date), event);
            }else if (request == "Del") {
                string date, event;
                getline(input, date, ' ');
                if(getline(input, event)){
                    if(db.DeleteEvent(Date(date), event)){
                        cout << "Deleted successfully" << endl;
                    }else{
                        cout << "Event not found" << endl;
                    }
                }else{
                    int amount = db.DeleteDate(Date(date));
                    cout << "Deleted " << amount << " events" << endl;
                }
            }else if (request == "Find") {
                string date;
                getline(input, date);
                db.Find(Date(date));
            }else if (request == "Print") {
                db.Print();
            }else{
                cout << "Unknown command: " << request << endl;
            }
        }catch(invalid_argument& e1){
            cout << e1.what() << endl;
            return 0;
        }catch(exception& e2){
            cout << e2.what() << endl;
            return 0;
        }
    }
    return 0;
}
