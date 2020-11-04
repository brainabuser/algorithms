//
// Created by Vladimir on 01.11.2020.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Edge {
    explicit Edge(int a, int b) : value(a), index(b) {}
    int value, index;
};

struct Vertex {
    Vertex() = default;
    vector<Edge> neigbours;
};

struct Graph {
    explicit Graph(const size_t &size) {
        vertices.resize(size);
        t_in.resize(size, -1);
        t_up.resize(size, -1);
    }
    mutable vector<int> t_in;
    mutable vector<int> t_up;
    vector<Vertex> vertices;
    void addEdge(const int &from, const int &to, const int &id);
};

void Graph::addEdge(const int &from, const int &to, const int &id) {
    vertices[from].neigbours.emplace_back(to, id);
}

enum Color {
    WHITE, GRAY, BLACK
};

void getBridges(const Graph &graph, set<int> &result);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        graph.addEdge(from - 1, to - 1, i + 1);
        graph.addEdge(to - 1, from - 1, i + 1);
    }
    set<int> result;
    getBridges(graph, result);
    cout << result.size() << endl;
    for (const auto &p: result) {
        cout << p << endl;
    }
    return 0;
}

void DFS_Visit(const Graph &graph, vector<Color> &colors, const int &vertex, int &timer,
               set<int> &result, const int &parent = -1) {
    colors[vertex] = GRAY;
    graph.t_in[vertex] = graph.t_up[vertex] = ++timer;
    for (auto &nbr : graph.vertices[vertex].neigbours) {
        if (nbr.value == parent) {
            continue;
        }
        if (colors[nbr.value] == GRAY) {
            graph.t_up[vertex] = min(graph.t_up[vertex], graph.t_in[nbr.value]);
        }
        if (colors[nbr.value] == WHITE) {
            DFS_Visit(graph, colors, nbr.value, timer, result, vertex);
            graph.t_up[vertex] = min(graph.t_up[vertex], graph.t_up[nbr.value]);
            if (graph.t_in[vertex] < graph.t_up[nbr.value]) {
                result.insert(nbr.index);
            }
        }
    }
    colors[vertex] = BLACK;
}

void getBridges(const Graph &graph, set<int> &result) {
    vector<Color> colors(graph.vertices.size(), WHITE);
    int timer = 0;
    for (int i = 0; i < graph.vertices.size(); ++i) {
        if (colors[i] == WHITE) {
            DFS_Visit(graph, colors, i, timer, result);
        }
    }
}