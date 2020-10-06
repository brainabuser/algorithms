//
// Created by vladimir on 06.10.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Graph {
    Graph(int size) {
        colors.resize(size, "undefined");
        vertices.resize(size);
    }

    vector<string> colors;
    vector<vector<int>> vertices;
};

bool BFS(Graph &graph, int root);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t;
        cin >> f >> t;
        graph.vertices[f - 1].push_back(t);
        graph.vertices[t - 1].push_back(f);
    }
    string answer = "YES";
    for (int i = 0; i < n; ++i) {
        if (graph.colors[i] == "undefined") {
            if (!BFS(graph, i + 1)) {
                answer = "NO";
                break;
            }
        }
    }
    cout << answer << endl;
    return 0;
}

bool BFS(Graph &graph, int root) {
    queue<int> level = {};
    graph.colors[root - 1] = "blue";
    level.push(root);
    while (!level.empty()) {
        int v = level.front();
        level.pop();
        for (auto &u: graph.vertices[v - 1]) {
            if (graph.colors[u - 1] == "undefined") {
                graph.colors[u - 1] = (graph.colors[v - 1] == "blue") ? "red" : "blue";
                level.push(u);
            } else if (graph.colors[u - 1] == graph.colors[v - 1]) {
                return false;
            }
        }
    }
    return true;
}
