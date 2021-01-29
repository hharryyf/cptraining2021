#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
vector<pair<int, int>> occ[MAX_SIZE * 2];
int tmp[MAX_SIZE * 2], pre[MAX_SIZE * 2];
bool visited[MAX_SIZE * 2];
int N, M;

void solve() {
    int i, j, k;
    M = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &k);
        g[i] = vector<int>(k, 0);
        for (j = 0 ; j < k; ++j) {
            scanf("%d", &g[i][j]);
            tmp[++M] = g[i][j];
        }
    }

    sort(tmp + 1, tmp + 1 + M);
    vector<int> disc;
    for (i = 1; i <= M; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }
    int sz = disc.size(), block_sz = sqrt(M);
    for (i = 0 ; i < sz; ++i) {
        visited[i] = false;
        pre[i] = -1;
        occ[i].clear();
    }
    for (i = 1; i <= N; ++i) {
        for (j = 0 ; j < (int) g[i].size(); ++j) {
            g[i][j] = lower_bound(disc.begin(), disc.end(), g[i][j]) - disc.begin();
        }
    }

    for (i = 1; i <= N; ++i) {
        if ((int) g[i].size() >= block_sz) {
            for (auto v : g[i]) visited[v] = true;
            for (j = 1; j <= N; ++j) {
                if (j == i) continue;
                int curr = 0;
                for (auto nv : g[j]) {
                    curr = curr + (visited[nv] == 1);
                }

                if (curr >= 2) {
                    printf("%d %d\n", i, j);
                    return;
                }
            }
            for (auto v : g[i]) visited[v] = false;
        } else {
            for (auto v : g[i]) {
                for (auto u : g[i]) {
                    if (v < u) {
                        occ[u].emplace_back(v, i);
                    }
                }
            }
        }
    }

    for (i = 0; i < sz; ++i) {
        for (auto np : occ[i]) {
            if (pre[np.first] != -1) {
                printf("%d %d\n", np.second, pre[np.first]);
                return;
            }
            pre[np.first] = np.second;
        }

        for (auto np : occ[i]) {
            pre[np.first] = -1;
        }
    }
    printf("-1\n");
}   

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        solve();
    }
    return 0;
}