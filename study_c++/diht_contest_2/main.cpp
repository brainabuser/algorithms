#include <iostream>

#include <string>

using namespace std;

class Man {
public:
    explicit Man(string const &name) {
        cout << "God(Vladimir) created " << name << endl;
        this->name = name;
    }

    void sayHelloTo(Man const &man) {
        cout << this->name << " said hello to " << man.name << endl;
    }

    void die() {
        cout << this->name << " has died " << endl;
    }

    string getName() const {
        return this->name;
    }

    ~Man() {
        die();
        delete this;
    }

private:
    string name;
    double health = 100.0;
    int heist_level = 0;
};

class BlackMan : public Man {
public:
    void shoot(Man const &man) {
        cout << this->name << "has shot " << man.getName() << endl;
    }

    void kill(Man const &man) {
        cout << this->name << "has killed " << man.getName() << endl;
    }

private:
    string name;
    double health = 100.0;
    int heist_level = 0;
};

enum CommandType {
    CREATE = 1, KILL, SHOOT, SAY_HELLO
};

int main() {
    cout << "List of commands:" << endl;
    cout << "To create person: (1) + <name_of_person>" << endl;
    cout << "To kill: (2) + <name_of_person>" << endl;
    cout << "To shoot: (3) + <name_of_person>" << endl;
    cout << "To say hello: (4) + <name_of_person>" << endl;
    cout << "To end game: (5)" << endl;
    while (true) {
        int command;
        cin >> command;
        if (command == 5) {
            cout << "GAME OVER" << endl;
            break;
        }
        command = (CommandType) command;
        switch (command) {
            case CREATE: {
                string name;
                cout << "Enter the name" << endl;
                cin >> name;
                Man *man = new Man(name);
                break;
            }
            case KILL: {
                string name;
                cin >> name;
                break;
            }
            case SHOOT: {
                break;
            }
            case SAY_HELLO: {
                break;
            }
        }
    }
    return 0;
}