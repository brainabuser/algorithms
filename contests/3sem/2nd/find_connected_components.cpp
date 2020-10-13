//
// Created by Vladimir on 13.10.2020.
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

    mutable vector<string> color;
    vector<set<int>> vertices;
};

struct Component {
    explicit Component(int size, int begin) : size(size), begin(begin) {}
    int size, begin;
};

void DFS(const Graph &graph, vector<Component> &answer);

void DFS_Visit(const Graph &graph, const int &root, int &depth, bool print);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int j = 0; j < m; ++j) {
        int from, to;
        cin >> from >> to;
        graph.vertices[from - 1].insert(to);
        graph.vertices[to - 1].insert(from);
    }
    vector<Component> components;
    DFS(graph, components);
    graph.color.assign(n, "white");
    auto size = components.size();
    cout << size << endl;
    while (size--) {
        int depth = 0;
        cout << components.back().size << endl;
        DFS_Visit(graph, components.back().begin + 1, depth, true);
        cout << endl;
        components.pop_back();
    }
    return 0;
}

void DFS_Visit(const Graph &graph, const int &root, int &depth, bool print) {
    graph.color[root - 1] = "gray";
    for (const auto &u : graph.vertices[root - 1]) {
        if (graph.color[u - 1] == "white") {
            ++depth;
            DFS_Visit(graph, u, depth, print);
        }
    }
    if (print) {
        cout << root << ' ';
    }
    graph.color[root - 1] = "black";
}

void DFS(const Graph &graph, vector<Component> &answer) {
    for (size_t i = 0; i < graph.vertices.size(); ++i) {
        int depth = 1;
        if (graph.color[i] == "white") {
            DFS_Visit(graph, i + 1, depth, false);
            answer.emplace_back(depth, i);
        }
    }
}