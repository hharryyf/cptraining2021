#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int visited[MAX_SIZE];
vector<int> a;
vector<pair<int, int>> g[MAX_SIZE];

void dfs(int v, int t) {
    if ((int) a.size() >= 1000000) return;
    a.push_back(v);
    int i, sz = g[v].size();
    for (i = sz - 1; i >= 0; --i) {
        if (g[v][i].first < t) break;
        dfs(g[v][i].second, g[v][i].first);
    }
}

int main() {
    int Q, i, L, R;
    scanf("%d%d%d", &Q, &L, &R);
    visited[0] = 1;
    for (i = 1; i <= Q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (!visited[x]) continue;
        g[x].push_back(make_pair(i, y));
        visited[y] = 1;
    }

    dfs(0, 0);

    int sz = a.size();
    for (i = L ; i < R; ++i) {
        printf("%d ", a[i % sz]);
    }
    printf("\n");
    return 0;
}