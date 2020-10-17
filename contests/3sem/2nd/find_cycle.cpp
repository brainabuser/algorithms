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
        parent.resize(size, -1);
    }

    mutable bool has_cycle = false;
    mutable int cycle_start;
    mutable vector<string> color;
    mutable vector<int> parent;
    vector<set<int>> vertices;
};

void DFS(const Graph &graph);

void print_cycle(const Graph &graph, int child);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int j = 0; j < m; ++j) {
        int from, to;
        cin >> from >> to;
        graph.vertices[from - 1].insert(to);
    }
    DFS(graph);
    if (graph.has_cycle) {
        cout << "YES" << endl;
        cout << graph.cycle_start << ' ';
        print_cycle(graph, graph.parent[graph.cycle_start - 1]);
    } else {
        cout << "NO" << endl;
    }
    return 0;
}

void DFS_Visit(const Graph &graph, const int &root) {
    graph.color[root - 1] = "gray";
    for (const auto &u : graph.vertices[root - 1]) {
        if (graph.has_cycle) {
            break;
        }
        if (graph.color[u - 1] == "white") {
            graph.parent[u - 1] = root;
            DFS_Visit(graph, u);
        } else if (graph.color[u - 1] == "gray") {
            graph.has_cycle = true;
            graph.cycle_start = u;
            graph.parent[u - 1] = root;
        }
    }
    if (graph.has_cycle) {
        return;
    } else {
        graph.color[root - 1] = "black";
    }
}

void DFS(const Graph &graph) {
    for (size_t i = 0; i < graph.vertices.size() && !graph.has_cycle; ++i) {
        if (graph.color[i] == "white") {
            DFS_Visit(graph, i + 1);
        }
    }
}

void print_cycle(const Graph &graph, int child) {
    if (child == graph.cycle_start) {
        return;
    }
    print_cycle(graph, graph.parent[child - 1]);
    cout << child << ' ';
}