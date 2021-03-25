#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 10011

vector<int> g[MAX_SIZE];
vector<int> ans[MAX_SIZE];
int deg[MAX_SIZE];
int cnt = 0, N;

void addedge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
    deg[u]++, deg[v]++;
}

void dfs(int v, int pre) {
    int id = ++cnt;
    ans[v].push_back(id);
    for (auto nv : g[v]) {
        if (nv != pre) {
            ans[nv].push_back(id);
            dfs(nv, v);
        }
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }

    for (i = 1; i <= N; ++i) {
        if (deg[i] == 1) {
            ans[i].push_back(2);
            dfs(i, 0);
            break;  
        }
    }

    for (i = 1; i <= N; ++i) {
        for (auto v : ans[i]) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}