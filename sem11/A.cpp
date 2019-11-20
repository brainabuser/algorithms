#include <iostream>

#include <cmath>

using namespace std;

struct Point{
    int x, y;
    double length;
};

int main(){
    Point point;
    int n;
    cin >> n;
    Point max_point = {0, 0, 0.0};
    for(int i = 0; i < n; ++i){
        cin >> point.x >> point.y;
        point.length = sqrt(point.x * point.x + point.y * point.y);
        if(point.length > max_point.length){
            max_point = point;
        }
    }
    cout << max_point.x << ' ' << max_point.y << endl;
    return 0;
}