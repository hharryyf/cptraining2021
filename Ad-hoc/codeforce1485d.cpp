#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            int x;
            scanf("%d", &x);
            if ((i + j) % 2) {
                printf("%d ", 720720);
            } else {
                printf("%d ", 720720 + x * x * x * x);
            }
        }

        printf("\n");
    }
    return 0;
}