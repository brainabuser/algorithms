//
// Created by Vladimir on 18.11.2020.
//


#include <iostream>
#include <vector>

using namespace std;

void readGraph(vector<vector<int>> &graph);

void printClosureMatrix(const vector<vector<int>> &dist);

void processAllPairs(vector<vector<int>> &dist);

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    readGraph(graph);
    processAllPairs(graph);
    printClosureMatrix(graph);
    return 0;
}

void readGraph(vector<vector<int>> &graph) {
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            cin >> graph[i][j];
        }
    }
}

void printClosureMatrix(const vector<vector<int>> &dist) {
    for (int i = 0; i < dist.size(); ++i) {
        for (int j = 0; j < dist.size(); ++j) {
            cout << (dist[i][j] != 0) << ' ';
        }
        cout << endl;
    }
}
void processAllPairs(vector<vector<int>> &dist) {
    for (int k = 0; k < dist.size(); ++k) {
        for (int i = 0; i < dist.size(); ++i) {
            for (int j = 0; j < dist.size(); ++j) {
                if (dist[i][j] != 0 && dist[i][k] != 0 && dist[k][j] != 0) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                } else if (dist[i][k] != 0 && dist[k][j] != 0) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}