#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

ld dp[55][5011], p[55];
int n, m, r, t[55], d[55];

bool check(ld T) {
    int i, j;
    memset(dp, 0, sizeof(dp));
    for (i = m - 1; i >= 0; --i) {
        for (j = 0; j <= r - n - 1; ++j) {
            dp[i][j] = p[i] * (dp[i+1][j] + t[i+1] - t[i]);
            if (j + d[i] <= r - n - 1) {
                dp[i][j] += (1.0 - p[i]) * min(T, dp[i+1][j + d[i]] + t[i+1] - t[i] + d[i]);
            } else {
                dp[i][j] += (1.0 - p[i]) * T;
            }
        }
    }

    return dp[0][0] <= T;
}

int main() {
    int i;
    scanf("%d%d%d", &n, &r, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%Lf%d", &t[i], &p[i], &d[i]);
    }
    t[++m] = n;
    p[m] = 1.0;
    d[m] = 0;
	t[0] = 0;
    p[0] = 1.0;
    d[0] = 0;
    ld low = 0, high = 1e18, ans = 0;
    for (i = 0 ; i < 100; ++i) {
        if (low > high) break;
        ld mid = (low + high) / 2.0;
        if (check(mid)) {
            high = mid;
            ans = mid;
        } else {
            low = mid;
        }
    }

    printf("%.10Lf\n", ans);
    return 0;
}