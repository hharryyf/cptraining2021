#include <bits/stdc++.h>
#define MAX_SIZE 500411
using namespace std;
const int mod = 1000000007;
const int shift = 221211;

int add(int u, int v) {
    if (u > mod) u -= mod;
    if (v > mod) v -= mod;
    int ret = u + v;
    if (ret > mod) ret -= mod;
    if (ret < 0) ret += mod;
    return ret;
}

int idx(int x) {
    assert(x + shift >= 0);
    assert(x + shift < MAX_SIZE);
    return x + shift;
}

int dp[102][MAX_SIZE];
int pre[MAX_SIZE];
int a, b, k, t;

int main() {
    int i, j;
    scanf("%d%d%d%d", &a, &b, &k, &t);
    int low = a - b - 2 * k * t, high = a - b + 2 * k * t; 
    dp[0][idx(a-b)] = 1;
    pre[idx(a-b)] = 1;
    for (i = idx(a-b+1); i <= idx(high); ++i) pre[i] = 1;
    for (i = 1; i <= t; ++i) {
        for (j = low; j <= high; ++j) {
            // dp[i][j] = dp[i-1][j-2k] + 2*dp[i-1][j-2k+1] + ... + (2k+1)*dp[i-1][j] + ... + 2*dp[i-1][j+2k-1] + dp[i-1][j+2k]    
            // dp[i][j-1] = dp[i-1][j-2k-1] + 2 * dp[i-1][j-2k] + ... + (2k+1) * dp[i-1][j-1] + ... + 2*dp[i-1][j+2k-2] + dp[i-1][j+2k-1]
            // dp[i][j] - dp[i][j-1] = dp[i-1][j-2k] + 2*dp[i-1][j-2k+1] + ... + (2k+1)*dp[i-1][j] + ... + 2*dp[i-1][j+2k-1] + dp[i-1][j+2k]
            // - dp[i-1][j-2k-1] - 2 * dp[i-1][j-2k] - ... - (2k+1) * dp[i-1][j-1] - ... - 2*dp[i-1][j+2k-2] - dp[i-1][j+2k-1]
            // = -dp[i-1][j-2k-1] - dp[i-1][j-2k]-dp[i-1][j-2k+1] - ... - dp[i-1][j-1] + dp[i-1][j] + ... + dp[i-1][j+2k]
            dp[i][idx(j)] = add(add(dp[i][idx(j-1)], pre[idx(min(j+2*k, high))] - pre[idx(j-1)]), add(-pre[idx(j-1)], pre[idx(j - 2 * k - 2)]));
        }

        for (j = low ; j <= high; ++j) {
            pre[idx(j)] = add(dp[i][idx(j)],  (j > low ? pre[idx(j-1)] : 0));
        }
    }

    int ans = 0;
    for (i = 1; i <= high; ++i) {
        ans = add(ans, dp[t][idx(i)]);
    }

    printf("%d\n", (ans % mod + mod) % mod);
    return 0;
}