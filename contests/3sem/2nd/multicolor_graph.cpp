//
// Created by Vladimir on 15.10.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

struct Graph {
    explicit Graph(int size) {
        vertices.resize(size);
        color.resize(size, "white");
    }

    mutable bool has_cycle = false;
    mutable vector<string> color;
    vector<vector<int>> vertices;
};

void TopSort(const Graph &graph);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    Graph graph(n);
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= n - i; ++j) {
            char color;
            cin >> color;
            if (color == 'B') {
                graph.vertices[i - 1].push_back(i + j);
            } else if (color == 'R') {
                graph.vertices[i + j - 1].push_back(i);
            } else {
                continue;
            }
        }
    }
    TopSort(graph);
    return 0;
}

void DFS_Visit(const Graph &graph, const int &root, deque<int> &answer) {
    graph.color[root - 1] = "gray";
    for (const auto &u : graph.vertices[root - 1]) {
        if (graph.has_cycle) {
            break;
        }
        if (graph.color[u - 1] == "white") {
            DFS_Visit(graph, u, answer);
        } else if (graph.color[u - 1] == "gray") {
            graph.has_cycle = true;
        }
    }
    if (graph.has_cycle) {
        return;
    } else {
        graph.color[root - 1] = "black";
        answer.push_front(root);
    }
}

void TopSort(const Graph &graph) {
    deque<int> answer;
    for (size_t i = 1; i <= graph.vertices.size() && !graph.has_cycle; ++i) {
        if (graph.color[i - 1] == "white") {
            DFS_Visit(graph, i, answer);
        }
    }
    cout << ((graph.has_cycle) ? "NO" : "YES") << endl;
}