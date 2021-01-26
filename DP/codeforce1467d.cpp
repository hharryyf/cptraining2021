#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 5011
const ll mod = 1e9 + 7;
using namespace std;
// number of paths start/end at i with length j
ll dp[MAX_SIZE][MAX_SIZE];
// our desired cnt table, cnt[i] = sum(dp[i][j] * dp[i][K-j])
ll cnt[MAX_SIZE];
int N, K, Q, val[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d%d%d", &N, &K, &Q);
    for (i = 1; i <= N; ++i) scanf("%d", &val[i]);
    for (i = 1; i <= N; ++i) dp[i][0] = 1;
    for (j = 1; j < MAX_SIZE; ++j) {
        for (i = 1; i <= N; ++i) {
            dp[i][j] = dp[i-1][j-1] + dp[i+1][j-1];
            dp[i][j] %= mod;
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 0; j <= K; ++j) {
            cnt[i] += dp[i][K-j] * dp[i][j];
            cnt[i] %= mod;
        }
    }

    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        ans = ans + cnt[i] * val[i];
        ans %= mod;
    }

    while (Q-- > 0) {
        int x, v;
        scanf("%d%d", &x, &v);
        ans = ans + cnt[x] * (v - val[x]);
        ans %= mod;
        if (ans < 0) ans += mod;
        val[x] = v;
        printf("%I64d\n", ans);
    }
    return 0;
}