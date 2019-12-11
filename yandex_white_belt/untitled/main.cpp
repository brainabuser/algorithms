#include <iostream>
#include <memory.h>

using namespace std;

int main()
{
    int* p = new int[5];
    memset(p, 0, sizeof (int) * 5);
    int c;
    memset(&c, 0, sizeof (int));
    cout << c + *p << endl;
    return 0;
}
