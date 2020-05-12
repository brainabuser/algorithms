//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>

using namespace std;

enum Request {
    ADD_EDGE = 1, VERTEX = 2
};

void printVertex(const vector<int> &v);

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int request;
        cin >> request;
        auto r = (Request) request;
        int source;
        switch (r) {
            case ADD_EDGE:
                int value;
                cin >> source >> value;
                graph[source - 1].push_back(value);
                graph[value - 1].push_back(source);
                break;
            case VERTEX:
                cin >> source;
                printVertex(graph[source - 1]);
                break;
        }
    }
    return 0;
}

void printVertex(const vector<int> &v) {
    for (const auto &i : v) {
        cout << i << ' ';
    }
    cout << endl;
}