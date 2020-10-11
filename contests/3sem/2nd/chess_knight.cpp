//
// Created by vladimir on 07.10.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Cell {
    int x;
    int y;
};

struct Graph {
    Graph(int size) {
        dist.resize(size, vector<int>(size, numeric_limits<int>::max()));
    }

    vector<vector<int>> dist;
    vector<Cell> neighbors = {{-1, 2},
                              {1,  2},
                              {-2, 1},
                              {-2, -1},
                              {2,  1},
                              {2,  -1},
                              {1,  -2},
                              {-1, -2}};
};

void BFS(Graph &graph, const Cell &from, const Cell &to);

int main() {
    int n;
    cin >> n;
    Graph vertices(n);
    Cell from{}, to{};
    cin >> from.x >> from.y >> to.x >> to.y;
    BFS(vertices, from, to);
    return 0;
}

void BFS(Graph &graph, const Cell &from, const Cell &to) {
    queue<Cell> level = {};
    vector<vector<Cell>> path(graph.dist.size(), vector<Cell>(graph.dist.size()));
    level.push(from);
    graph.dist[from.x - 1][from.y - 1] = 0;
    while (!level.empty()) {
        auto v = level.front();
        level.pop();
        for (const auto &u: graph.neighbors) {
            if (v.x + u.x > graph.dist.size() || v.y - u.y > graph.dist.size()
                || v.x + u.x < 1 || v.y - u.y < 1) {
                continue;
            }
            if (graph.dist[v.x + u.x - 1][v.y - u.y - 1] > graph.dist[v.x - 1][v.y - 1] + 1) {
                graph.dist[v.x + u.x - 1][v.y - u.y - 1] = graph.dist[v.x - 1][v.y - 1] + 1;
                path[v.x + u.x - 1][v.y - u.y - 1] = v;
                level.push({v.x + u.x, v.y - u.y});
            }
        }
    }
    vector<Cell> result(graph.dist[to.x - 1][to.y - 1] + 1);
    auto temp = to;
    for (auto it = result.rbegin(); it < result.rend(); it = next(it)) {
        *it = temp;
        temp = path[temp.x - 1][temp.y - 1];
    }
    cout << graph.dist[to.x - 1][to.y - 1] << endl;
    for (const auto &item : result) {
        cout << item.x << ' ' << item.y << endl;
    }
    cout << endl;
}

