#include <iostream>
#include <map>

#include "conio.h"

using namespace std;

char *fortunes[] = {
        "Money will come to you as fast as possible.\n",
        "You will find your new love.\n",
        "Money you contribute will generate revenue.\n",
        "Close friend will be looking for your appreciation.\n"
};

int main() {
    int chance;

    cout << "If you want to know your fate, then press any key:\n";

    while (!kbhit()) {
        rand();
    }
    chance = rand();
    chance = chance % 5;
    cout << fortunes[chance];

    return 0;
}