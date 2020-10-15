//
// Created by Vladimir on 15.10.2020.
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
        component_id.resize(size);
        color.resize(size, "white");
    }

    mutable vector<string> color;
    mutable vector<int> component_id;
    vector<set<int>> vertices;
};

deque<int> TopSort(const Graph &graph);

void DFS_Visit(const Graph &graph, const int &root, deque<int> &answer);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    Graph graph_t(n);
    for (int j = 0; j < m; ++j) {
        int from, to;
        cin >> from >> to;
        graph.vertices[from - 1].insert(to);
        graph_t.vertices[to - 1].insert(from);
    }
    auto order = TopSort(graph);
    vector<deque<int>> g_condensation;
    for (const auto &elem : order) {
        deque<int> connected_component;
        if (graph_t.color[elem - 1] == "white") {
            DFS_Visit(graph_t, elem, connected_component);
            g_condensation.push_back(connected_component);
        }
    }
    auto cond_len = g_condensation.size();
    cout << cond_len << endl;
    for (int id = 1; id <= cond_len; ++id) {
        auto cc_len = g_condensation[id - 1].size();
        for (int j = 0; j < cc_len; ++j) {
            graph.component_id[g_condensation[id - 1][j] - 1] = id;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << graph.component_id[i] << ' ';
    }
    cout << endl;
    return 0;
}

void DFS_Visit(const Graph &graph, const int &root, deque<int> &answer) {
    graph.color[root - 1] = "gray";
    for (const auto &u : graph.vertices[root - 1]) {
        if (graph.color[u - 1] == "white") {
            DFS_Visit(graph, u, answer);
        }
    }
    graph.color[root - 1] = "black";
    answer.push_front(root);
}

deque<int> TopSort(const Graph &graph) {
    deque<int> answer;
    for (size_t i = 1; i <= graph.vertices.size(); ++i) {
        if (graph.color[i - 1] == "white") {
            DFS_Visit(graph, i, answer);
        }
    }
    return answer;
}