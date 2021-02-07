#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int cnt[MAX_SIZE], vis[MAX_SIZE], a[MAX_SIZE];
int N, M;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        if (a[i] <= M) vis[a[i]]++;
    }

    for (i = 1; i <= M; ++i) {
        if (vis[i] > 0) {
            for (j = i; j <= M; j = j + i) {
                cnt[j] += vis[i];
            }
        }
    }

    int mx = 0, idx = 1;
    for (i = 1; i <= M; ++i) {
        // printf("%d\n", cnt[i]);
        if (mx < cnt[i]) {
            mx = cnt[i];
            idx = i;
        }
    }

    printf("%d %d\n", idx, mx);
    if (mx == 0) return 0;
    for (i = 1; i <= N; ++i) {
        if (mx != 0 && (idx % a[i] == 0)) {
            printf("%d ", i);
        }
    }

    printf("\n");
    return 0;
}