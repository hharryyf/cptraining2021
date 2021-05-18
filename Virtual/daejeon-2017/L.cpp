#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 52
using namespace std;
const ll inf = 1e16;
ll dp[3][MAX_SIZE][MAX_SIZE * MAX_SIZE * MAX_SIZE];
ll cost[3][MAX_SIZE];
int target[3], cnt[3];
vector<pair<int, ll>> g[3][MAX_SIZE];
int P;

void init() {
    int i, j, k;
    for (i = 0 ; i < 3; ++i) {
        for (j = 1 ; j < MAX_SIZE; ++j) {
            for (k = 0 ; k < MAX_SIZE * MAX_SIZE * MAX_SIZE; ++k) {
                dp[i][j][k] = inf;
                if (j == 1 && k == 0) {
                    dp[i][j][k] = 0;
                }
            }
        }
    }
}

int main() {
    int i, j, k;
    scanf("%d", &P);
    init();

    for (i = 0 ; i < P; ++i) {
        int n, m;
        scanf("%d%d", &n, &m);
        cnt[i] = n;
        for (j = 1; j <= n; ++j) {
            scanf("%lld", &cost[i][j]);
        }
        for (j = 1; j <= m; ++j) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            g[i][u].emplace_back(v, w);
        }
        scanf("%d", &target[i]);
    }

    for (i = 0; i < P; ++i) {
        for (j = 0 ; j < (MAX_SIZE * MAX_SIZE * MAX_SIZE) - 1; ++j) {
            for (k = 1; k <= cnt[i]; ++k) {
                for (auto np : g[i][k]) {
                    int nv = np.first;
                    ll w = np.second;
                    dp[i][k][j+1] = min(dp[i][k][j+1], dp[i][k][j] + cost[i][k]);
                    dp[i][nv][j+1] = min(dp[i][nv][j+1], dp[i][k][j] + w); 
                }
            }
        } 
    }

    ll ans = inf;
    for (i = 0 ; i < MAX_SIZE * MAX_SIZE * MAX_SIZE; ++i) {
        ans = min(ans, dp[0][target[0]][i] + dp[1][target[1]][i] + dp[2][target[2]][i]);
    }

    printf("%lld\n", ans);
    return 0;
}