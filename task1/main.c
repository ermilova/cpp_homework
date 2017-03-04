#include<stdio.h>
#include <malloc.h>

int main(int argc, char *argv) {
    int n;
    int **a;
    int x1, y1, x2, y2;

    scanf("%d", &n);
    a = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int) * n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = (j + 1) * (i + 1);
        }
    }

    scanf("%d", &x1);
    while (x1 != 0) {
        scanf("%d %d %d", &y1, &x2, &y2);
        for (int i = x1 - 1; i < x2; i++) {
            for (int j = y1 - 1; j < y2; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        scanf("%d", &x1);
    }

    for (int i = 0; i < n; i++) {
        free(a[i]);
    }

    free(a);
    return 0;
}
