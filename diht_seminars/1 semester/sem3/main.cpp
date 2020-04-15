#include <iostream>

#include "test.h"

using namespace std;

struct Test{
    void sayHello(){
        cout << "Hello" << endl;
    }
};

int main() {
    cout << a << endl;
    Test test;
    test.sayHello();
    cout << (char)27 << endl;
    return 0;
}

