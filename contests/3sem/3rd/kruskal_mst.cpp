//
// Created by Vladimir on 08.11.2020.
//

#include <iostream>
#include <vector>

using namespace std;

class DSU {
  public:
    bool isAllConnected = false;
    explicit DSU(int size) {
        rank.resize(size, 0);
        parent.resize(size);
        kids.resize(size, 1);
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
//            weight[x] += w;
//            weight[y] = weight[x];
            return;
        }
        weight[x] += weight[y] + w;
        weight[y] = weight[x];
        if (rank[x] > rank[y]) {
            parent[y] = x;
            if (x != y) {
                kids[x] += kids[y];
            }
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[x] = y;
            ++rank[y];
        }
        auto s = kids.size();
        isAllConnected = (kids[x] == s || kids[y] == s);
    }
    int GetWeight(int x) {
        return weight[FindSet(x)];
    }
  private:
    vector<int> rank;
    vector<int> parent;
    vector<int> kids;
    vector<int> weight;
};

int findMST(DSU &undir_graph, const int &edges_num);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    DSU undir_graph(n);
    cout << findMST(undir_graph, m) << '\n';
    return 0;
}

int findMST(DSU &undir_graph, const int &edges_num) {
    int i = 0;
    while (i++ < edges_num && !undir_graph.isAllConnected) {
        int from, to, weight;
        cin >> from >> to >> weight;
        undir_graph.Union(from - 1, to - 1, weight);
    }
    return undir_graph.GetWeight(0);
}