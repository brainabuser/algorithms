//
// Created by Vladimir on 04.11.2020.
//

#include <iostream>
#include <vector>

using namespace std;

class DSU {
  public:
    explicit DSU(int size) {
        rank.resize(size, 0);
        parent.resize(size);
        weight.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    int FindSet(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = FindSet(parent[x]);
    }
    void Union(int x, int y, int w) {
        x = FindSet(x);
        y = FindSet(y);
        if (x == y) {
            weight[x] += w;
            weight[y] = weight[x];
            return;
        }
        weight[x] += weight[y] + w;
        weight[y] = weight[x];
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[x] = y;
            ++rank[y];
        }
    }
    int GetWeight(int x) {
        return weight[FindSet(x)];
    }
  private:
    vector<int> rank;
    vector<int> parent;
    vector<int> weight;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, request_number;
    cin >> n >> request_number;
    DSU undir_graph(n);
    while (request_number--) {
        int request_id, from;
        cin >> request_id;
        if (request_id == 1) {
            int to, weight;
            cin >> from >> to >> weight;
            undir_graph.Union(from - 1, to - 1, weight);
        } else if (request_id == 2) {
            int vertex;
            cin >> vertex;
            cout << undir_graph.GetWeight(vertex - 1) << '\n';
        }
    }
    return 0;
}