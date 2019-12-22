#include <iostream>

#include <cassert>

using namespace std;

template<typename E>
int sum(const E &x, const E &y) {
    return x + y;
}

void testSum() {
    assert(sum(2, 3) == 5);
    assert(sum(2.0, 3.0) == 5.0);
    assert(sum(20, -20) == 0);
    assert(sum(0.0, -1.0) == -1.0);
    assert(sum(2, 0) == 2);
    cout << "OK" << endl;
}

int main() {
    testSum();
    return 0;
}