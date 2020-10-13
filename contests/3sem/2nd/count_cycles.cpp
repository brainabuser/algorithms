//
// Created by Vladimir on 13.10.2020.
//

//
// Created by vladimir on 08.10.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>

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

void DFS(const Graph &graph, int &cycles);

int main() {
    int n;
    cin >> n;
    Graph graph(n);
    for (int j = 0; j < n; ++j) {
        int to;
        cin >> to;
        graph.vertices[j].insert(to);
    }
    int cycles = 0;
    DFS(graph, cycles);
    cout << cycles << endl;
    return 0;
}

void DFS_Visit(const Graph &graph, const int &root) {
    graph.color[root - 1] = "gray";
    for (const auto &u : graph.vertices[root - 1]) {
        if (graph.color[u - 1] == "white") {
            DFS_Visit(graph, u);
        } else if (graph.color[u - 1] == "gray") {
            graph.has_cycle = true;
        }
    }
    graph.color[root - 1] = "black";
}

void DFS(const Graph &graph, int &cycles) {
    for (size_t i = 0; i < graph.vertices.size(); ++i) {
        if (graph.color[i] == "white") {
            DFS_Visit(graph, i + 1);
        }
        if (graph.has_cycle) {
            ++cycles;
            graph.has_cycle = false;
        }
    }
}