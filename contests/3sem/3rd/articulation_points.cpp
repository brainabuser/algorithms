//
// Created by Vladimir on 01.11.2020.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Graph {
    explicit Graph(const size_t &size) {
        adjacency_list.resize(size);
        t_in.resize(size, 0);
        t_up.resize(size, 0);
    }
    mutable vector<int> t_in;
    mutable vector<int> t_up;
    vector<vector<int>> adjacency_list;
};

enum Color {
    WHITE, GRAY, BLACK
};

void getArticulationPoints(const Graph &graph, set<int> &result);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        graph.adjacency_list[to - 1].push_back(from);
        graph.adjacency_list[from - 1].push_back(to);
    }
    set<int> result;
    getArticulationPoints(graph, result);
    cout << result.size() << endl;
    for (const auto &p: result) {
        cout << p << endl;
    }
    return 0;
}

void DFS_Visit(const Graph &graph, vector<Color> &colors, const int &vertex_id, bool is_root, int &timer,
               set<int> &result) {
    colors[vertex_id] = GRAY;
    graph.t_in[vertex_id] = graph.t_up[vertex_id] = ++timer;
    int n_child = 0;
    for (const auto &nbr : graph.adjacency_list[vertex_id]) {
        if (colors[nbr - 1] == GRAY) {
            graph.t_up[vertex_id] = min(graph.t_up[vertex_id], graph.t_in[nbr - 1]);
        } else if (colors[nbr - 1] == WHITE) {
            DFS_Visit(graph, colors, nbr - 1, false, timer, result);
            ++n_child;
            graph.t_up[vertex_id] = min(graph.t_up[vertex_id], graph.t_up[nbr - 1]);
            if (graph.t_in[vertex_id] <= graph.t_up[nbr - 1] && !is_root) {
                result.insert(vertex_id + 1);
            }
        }
    }
    colors[vertex_id] = BLACK;
    if (is_root && n_child >= 2) {
        result.insert(vertex_id + 1);
    }
}

void getArticulationPoints(const Graph &graph, set<int> &result) {
    vector<Color> colors(graph.adjacency_list.size(), WHITE);
    int timer = 0;
    for (int i = 0; i < graph.adjacency_list.size(); ++i) {
        if (colors[i] == WHITE) {
            DFS_Visit(graph, colors, i, true, timer, result);
        }
    }
}