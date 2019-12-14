#include <iostream>

using namespace std;

void reverse(int *array, const int &n);

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    int *length = new int[n];
    int *prev = new int[n];
    int max_length = 1;
    int max_index = 0;
    for (int i = 0; i < n; ++i) {
        length[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; ++j) {
            if (array[j] < array[i] && length[j] + 1 > length[i]) {
                length[i] = length[j] + 1;
                prev[i] = j;
            }
            if (length[i] > max_length) {
                max_length = length[i];
                max_index = i;
            }
        }
    }
    int pos = max_index;
    int *answer = new int[max_length];
    int cnt = 0;
    while(pos != -1){
        answer[cnt++] = array[pos];
        pos = prev[pos];
    }
    delete[] array;
    reverse(answer, max_length);
    for(int i = 0; i < max_length; ++i){
        cout << answer[i] << ' ';
    }
    delete[] answer;
    delete[] length;
    delete[] prev;
    return 0;
}

void reverse(int *array, const int &n){
    for(int i = 0; i < n / 2; ++i){
        int temp = array[i];
        array[i] = array[n - i - 1];
        array[n - i - 1] = temp;
    }
}