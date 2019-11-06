#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int array[20][20], barray[20][20], carray[20][20];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            scanf("%d", &array[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            scanf("%d", &barray[i][j]);
            carray[i][j] = array[i][j] + barray[i][j];
            printf("%d ", carray[i][j]);
        }
        printf("\n");
    }
    return 0;
}