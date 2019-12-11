#include <iostream>
#include <exception>
#include <string>

using namespace std;

string AskTimeServer() {
    throw domain_error("kek");
}

class TimeServer {
public:
    string GetCurrentTime() {
        string time;
        try {
            time = AskTimeServer();
        }catch(system_error& e1){
            return LastFetchedTime;
        }
        LastFetchedTime = time;
        return LastFetchedTime;
    }

private:
    string LastFetchedTime = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
