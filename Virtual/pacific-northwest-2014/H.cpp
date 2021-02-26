#include <bits/stdc++.h>

using namespace std;

const int inf = 1e8;
int dp[1011][5011];
int a[21];
int N, M;

void solve() {
    int i, j, k, ans = -inf;
    for (i = 0; i < 1011; ++i) {
        for (j = 0 ; j < 5011; ++j) {
            dp[i][j] = -inf;
        }
    }

    scanf("%d%d", &N, &M);
    dp[0][0] = 0;
    for (i = 1; i <= M; ++i) scanf("%d", &a[i]);
    for (i = 1; i < 1011; ++i) {
        for (j = 0; j <= N; ++j) {
            for (k = 1; k <= M; ++k) {
                if (j + i * a[k] <= N) {
                    dp[i][j + i * a[k]] = max(dp[i][j + i * a[k]], dp[i-1][j] + a[k]);
                }
            }
        }
    }

    for (i = 1; i < 1011; ++i) {
        ans = max(ans, dp[i][N]);
    }

    if (ans < 0) ans = -1;
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        solve();
    }
    return 0;
}