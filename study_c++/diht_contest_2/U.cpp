#include <iostream>

using namespace std;

void getAnswer(int **array, int* weights, int n_size, int m_size);

int main() {
    int n, m;
    cin >> n >> m;
    int n_size = n + 1;
    int m_size = m + 1;
    int **array = new int *[n_size];
    int *costs = new int[n_size]();
    int *weights = new int[n_size]();
    for (int i = 0; i < n_size; ++i) {
        array[i] = new int[m_size]();
    }
    for (int i = 1; i < n_size; ++i) {
        cin >> weights[i];
    }
    for (int i = 1; i < n_size; ++i) {
        cin >> costs[i];
    }
    for (int i = 1; i < n_size; ++i) {
        for (int j = 1; j < m_size; ++j) {
            if (j >= weights[i]) {
                array[i][j] = max(array[i - 1][j], costs[i] + array[i - 1][j - weights[i]]);
            } else {
                array[i][j] = array[i - 1][j];
            }
        }
    }
    getAnswer(array, weights, n_size - 1, m_size - 1);
    for (int i = 0; i < n_size; ++i) {
        delete[] array[i];
    }
    delete[] array;
    delete[] weights;
    delete[] costs;
    return 0;
}

void getAnswer(int **array, int* weights, int n_size, int m_size) {
    if (array[n_size][m_size] == 0) {
        return;
    }
    if(array[n_size - 1][m_size] == array[n_size][m_size]){
        getAnswer(array, weights, n_size - 1, m_size);
    }else{
        getAnswer(array, weights, n_size - 1, m_size - weights[n_size]);
        cout << n_size << endl;
    }
}