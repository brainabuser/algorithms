//
// Created by Vladimir on 04.11.2020.
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class DSU {
  public:
    explicit DSU(int size) {
        rank.resize(size, 0);
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    int FindSet(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = FindSet(parent[x]);
    }
    void Union(int x, int y) {
        x = FindSet(x);
        y = FindSet(y);
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[x] = y;
            ++rank[y];
        }
    }
  private:
    vector<int> rank;
    vector<int> parent;
};

struct Request {
    string command;
    int from, to;
};

int main() {
    int n, m;
    int request_number;
    cin >> n >> m >> request_number;
    DSU undir_graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
    }
    stack<Request> requests;
    stack<string> answers;
    while (request_number--) {
        Request temp;
        cin >> temp.command >> temp.from >> temp.to;
        requests.push(temp);
    }
    while (!requests.empty()) {
        auto request = requests.top();
        if (request.command == "ask") {
            auto a = undir_graph.FindSet(request.from - 1);
            auto b = undir_graph.FindSet(request.to - 1);
            auto ans = ((a == b) ? "YES" : "NO");
            answers.push(ans);
        } else if (request.command == "cut") {
            undir_graph.Union(request.from - 1, request.to - 1);
        }
        requests.pop();
    }
    while (!answers.empty()) {
        cout << answers.top() << endl;
        answers.pop();
    }
    return 0;
}
