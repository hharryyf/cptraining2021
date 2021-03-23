#include <bits/stdc++.h>
#define MAX_SIZE 10111
using namespace std;
typedef long long ll;
const ll inf = 1e17;
ll dp[MAX_SIZE][21][2];
ll wt[MAX_SIZE];
int sz[MAX_SIZE];
ll ans;
vector<pair<int, ll>> g[MAX_SIZE];
int N, K;

void init() {
    int i, j;
    ans = 0;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        g[i].clear();
        sz[i] = 0;
        wt[i] = 0;
        for (j = 0 ; j <= 20; ++j) {
            dp[i][j][0] = dp[i][j][1] = -inf;
        }
    }
}

void dfs(int v, int pre) {
    sz[v] = 1;
    int i, j;
    dp[v][0][0] = 0;
    for (auto np : g[v]) {
        int nv = np.first;
        // ll w = np.second;
        if (nv != pre) {
            dfs(nv, v);
            wt[v] += np.second + wt[nv];
            sz[v] += sz[nv];
        }
    }

    for (auto np : g[v]) {
        for (i = min(K, sz[v]); i >= 0; --i) {
            int nv = np.first;
            ll w = np.second;
            if (nv == pre) continue;
            for (j = 0 ; j <= min(sz[nv], i); ++j) {
                if (j == sz[nv]) {
                    dp[v][i][0] = max(dp[v][i][0], dp[v][i-j][0] + dp[nv][j][0] + w);
                } 
                dp[v][i][0] = max(dp[v][i][0], dp[v][i-j][0] + dp[nv][j][0]);
                // cout << "enter" << " " << dp[v][i][0] << endl;
            }
            ans = max(dp[v][i][0], ans);
        }
    }

    for (i = 0; i <= min(K, sz[v]); ++i) dp[v][i][0] = max(0ll, dp[v][i][0]);
}

void dfs2(int v, int pre) {
    int i, j;
    
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv == pre) continue;
        for (i = min(K, N); i >= 0; --i) {
            j = min(N - sz[nv], i); 
            if (j == N - sz[nv]) {
                ans = max(ans, dp[nv][i-j][0] + wt[1] - wt[nv]); 
            }
        }

        dfs2(nv, v);
    }
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        ll cnt = 0;
        scanf("%d%d", &N, &K);
        init();
        for (i = 1; i < N; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u++, v++;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            cnt += w;
        }

        dfs(1, 0);
        dfs2(1, 0);
        // cout << ans << endl;
        printf("%I64d\n", (cnt - ans) * 2);
    }
    return 0;
}