#include <bits/stdc++.h>
#define MAX_SIZE 2011
typedef long long ll;
using namespace std;

ll dp[MAX_SIZE];
ll pre[MAX_SIZE], a[MAX_SIZE * 100];
int x[MAX_SIZE], N, M, K;

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &K);
    for (i = 1; i <= N; ++i) scanf("%I64d", &a[i]);
    sort(a + 1, a + 1 + N);
    for (i = 1; i <= M; ++i) {
        int v, u;
        scanf("%d%d", &v, &u);
        if (v <= K) x[v] = max(x[v], u);
    }

    for (i = 1; i <= K; ++i) {
        pre[i] = pre[i-1] + a[i];
    }

    for (i = 1; i <= K; ++i) {
        dp[i] = dp[i-1] + a[i];
        for (j = 1; j <= i; ++j) {
            int l = i - j + x[j];
            dp[i] = min(dp[i], dp[i-j] + pre[i] - pre[l]);
        }
    }

    printf("%I64d\n", dp[K]);
    return 0;
}