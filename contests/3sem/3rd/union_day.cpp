//
// Created by Vladimir on 06.11.2020.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Vertex {
    Vertex() = default;
    Vertex(int x, int y, int id = -1) : x(x), y(y), id(id) {}
    int x{}, y{}, id{};
    vector<int> adj;
    mutable double weight = numeric_limits<double>::max();
};

struct Graph {
    explicit Graph(int size) : vertices(size) {
        for (auto &v : vertices) {
            v.adj.reserve(size - 1);
        }
    }
    vector<Vertex> vertices;
};

void makeGraph(Graph &graph, const vector<Vertex> &cities);
double findMST(const Graph &graph);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    Graph graph(n);
    vector<Vertex> cities(n);
    for (int k = 0; k < n; ++k) {
        int x, y;
        cin >> x >> y;
        cities[k] = Vertex(x, y, k);
    }
    makeGraph(graph, cities);
    cout << setprecision(7) << findMST(graph) << '\n';
    return 0;
}

double getDistance(const Vertex &lhs, const Vertex &rhs) {
    return sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2));
}

void makeGraph(Graph &graph, const vector<Vertex> &cities) {
    for (int i = 0; i < graph.vertices.size(); ++i) {
        auto c_i = cities[i];
        graph.vertices[i].x = c_i.x;
        graph.vertices[i].y = c_i.y;
        graph.vertices[i].id = c_i.id;
        for (int j = i + 1; j < graph.vertices.size(); ++j) {
            auto c_j = cities[j];
            graph.vertices[i].adj.push_back(c_j.id);
            graph.vertices[j].x = c_j.x;
            graph.vertices[j].y = c_j.y;
            graph.vertices[j].adj.push_back(c_i.id);
        }
    }
}

double findMST(const Graph &graph) {
    vector<bool> used(graph.vertices.size(), false);
    double result = 0.0;
    graph.vertices[0].weight = 0.0;
    for (size_t i = 0; i < graph.vertices.size(); ++i) {
        Vertex min_v;
        for (const auto &v : graph.vertices) {
            if (!used[v.id] && (min_v.id == -1 || v.weight < min_v.weight)) {
                min_v = v;
            }
        }
        used[min_v.id] = true;
        result += min_v.weight;
        for (const auto &e : graph.vertices[min_v.id].adj) {
            auto d = getDistance(min_v, graph.vertices[e]);
            if (!used[e] && d < graph.vertices[e].weight) {
                graph.vertices[e].weight = d;
            }
        }
    }
    return result;
}