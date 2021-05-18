#include <bits/stdc++.h>
#define MAX_SIZE 100011 
using namespace std;

vector<int> g[MAX_SIZE];
vector<pair<int, int>> deg;
int d[MAX_SIZE];
int N, M;
int dp[MAX_SIZE];

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 0 ; i < M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        ++u, ++v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (i = 1; i <= N; ++i) {
        deg.emplace_back((int) g[i].size(), i);        
        d[i] = (int) g[i].size();
    }
    sort(deg.begin(), deg.end());
    for (auto np : deg) {
        dp[np.second] = 1;
        for (auto nv : g[np.second]) {
            if (d[nv] < np.first) {
                dp[np.second] = max(dp[np.second], dp[nv] + 1);
            }
        }
    }

    int ans = 0;
    for (i = 1; i <= N; ++i) {
        ans = max(ans, dp[i]);
    }

    printf("%d\n", ans);
    return 0;
}