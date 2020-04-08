#include <iostream>

using namespace std;

void hanoiTowers(int quantity, int from, int to,
                  int buf_peg) {
    if (quantity != 0) {
        hanoiTowers(quantity - 1, from, buf_peg, to);

        cout << from << ' ' << to << endl;

        hanoiTowers(quantity - 1, buf_peg, to, from);
    }
}

int main() {
    int n;
    cin >> n;
    hanoiTowers(n, 1, 2, 3);
    return 0;
}