#include <iostream>

#include <cstring>

using namespace std;

class Monster {
  protected:
    char *name;
    int health;
  public:
    Monster(const char *n, int h) : health(h) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    ~Monster() {
        delete[] name;
    }
    void getHealth() const {
        cout << "I am a monster and my health is " << health << endl;
    }
};

class Demon : public Monster {
  private:
    int brain;
  public:
    Demon(const char *n, int h, int b) : Monster(n, h), brain(b) {
        cout << "I am a demon and my health is " << health << endl;
    }
    void getBrain() const {
        cout << "I am a demon and my brain is " << brain << endl;
    }
};

int main() {
    Monster m("Bad guy", 10);
    Demon d("Vampire", 20, 5);
    d.getHealth();
    Monster &m2 = d;
    m2.getHealth();
    Monster *m3 = &d;
    m3->getHealth();
//    m3->getBrain();
    return 0;
}