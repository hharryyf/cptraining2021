#include <bits/stdc++.h>
#define MAX_SIZE 123511
using namespace std;

vector<int> g[MAX_SIZE];
vector<int> h[MAX_SIZE];
int sz[MAX_SIZE], good[MAX_SIZE], special[MAX_SIZE], ok[MAX_SIZE];
int N, M, maxd = 0, minv = MAX_SIZE;

void dfs(int v, int pre) {
    sz[v] = ok[v];
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            sz[v] += sz[nv];
        }
    }
    good[v] = (sz[v] > 0);
}

void dfs2(int v, int pre, int d=0) {
    if (d > maxd || (d == maxd && v < minv)) {
        maxd = d, minv = v;
    }

    for (auto nv : h[v]) {
        if (nv != pre) {
            dfs2(nv, v, d + 1);
        }
    }
}

int main() {
    int i, cnt = 0, ans = 0;
    scanf("%d%d", &N, &M);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (i = 1; i <= M; ++i) {
        scanf("%d", &special[i]);
        ok[special[i]] = 1;
    }

    dfs(special[1], 0);
    for (i = 1; i <= N; ++i) {
        for (auto v : g[i]) {
            if (good[i] && good[v] && i < v) {
                h[i].push_back(v);
                h[v].push_back(i);
                cnt++;
            }
        }
    }   

    dfs2(special[1], 0);
    int tmp = minv;
    minv = MAX_SIZE;
    dfs2(tmp, 0);
    ans = maxd;
    tmp = minv;
    dfs2(minv, 0);
    printf("%d\n", min(minv, tmp));
    printf("%d\n", 2 * cnt - ans);
    return 0;
}