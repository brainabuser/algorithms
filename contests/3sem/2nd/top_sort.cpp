//
// Created by Vladimir on 13.10.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <deque>

using namespace std;

struct Graph {
    explicit Graph(int size) {
        vertices.resize(size);
        color.resize(size, "white");
    }

    mutable bool has_cycle = false;
    mutable vector<string> color;
    vector<set<int>> vertices;
};

void TopSort(const Graph &graph);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int j = 0; j < m; ++j) {
        int from, to;
        cin >> from >> to;
        graph.vertices[from - 1].insert(to);
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
    for (size_t i = 0; i < graph.vertices.size() && !graph.has_cycle; ++i) {
        if (graph.color[i] == "white") {
            DFS_Visit(graph, i + 1, answer);
        }
    }
    if (graph.has_cycle) {
        cout << -1 << endl;
    } else {
        for (const auto &elem: answer) {
            cout << elem << ' ';
        }
        cout << endl;
    }
}