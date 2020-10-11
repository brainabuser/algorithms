//
// Created by vladimir on 07.10.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Cell {
    int x, y;
};

struct Graph {
    Graph(int rows, int cols) {
        dist.resize(rows, vector<int>(cols));
    }

    vector<vector<int>> dist;
    vector<Cell> neighbors = {{-1, 0},
                              {0,  1},
                              {1,  0},
                              {0,  -1}};
};

void BFS(Graph &graph, const Cell &from);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n, m);
    vector<Cell> restaurants;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int temp;
            cin >> temp;
            if (temp == 1) {
                restaurants.push_back({i + 1, j + 1});
                graph.dist[i][j] = 0;
            } else if (temp == 0) {
                graph.dist[i][j] = numeric_limits<int>::max();
            }
        }
    }
    for (auto &rest : restaurants) {
        BFS(graph, rest);
    }
    for (const auto &row : graph.dist) {
        for (const auto &elem : row) {
            cout << elem << ' ';
        }
        cout << endl;
    }
    return 0;
}

void BFS(Graph &graph, const Cell &from) {
    queue<Cell> level = {};
    level.push(from);
    while (!level.empty()) {
        auto v = level.front();
        level.pop();
        for (auto &u: graph.neighbors) {
            if (v.x + u.x > graph.dist.size()
                || v.y - u.y > graph.dist.front().size()
                || v.x + u.x < 1
                || v.y - u.y < 1
                || graph.dist[v.x + u.x - 1][v.y - u.y - 1] == 0) {
                continue;
            }
            if (graph.dist[v.x + u.x - 1][v.y - u.y - 1] > graph.dist[v.x - 1][v.y - 1] + 1) {
                graph.dist[v.x + u.x - 1][v.y - u.y - 1] = graph.dist[v.x - 1][v.y - 1] + 1;
                level.push({v.x + u.x, v.y - u.y});
            }
        }
    }
}
