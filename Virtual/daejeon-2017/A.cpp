#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

vector<int> t[MAX_SIZE];
int f[MAX_SIZE][MAX_SIZE], g[MAX_SIZE][MAX_SIZE];
int N;

void dfs(int v, int pre) {
    int i;
    for (auto nv : t[v]) {
        if (pre != nv) {
            dfs(nv, v);
            for (i = 1; i <= N; ++i) {
                // recursive case of g
                g[v][i] += g[nv][i-1];
            }
        }
    }
    // the answer is bounded, can't be more than N
    g[v][0] = f[v][N] = N;

    for (i = N - 1; i >= 0; --i) {
        // the start state of f[v][i], put a distance i stuff at position v
        f[v][i] =  min(max(1, i) + g[v][max(1, i) + 1], f[v][i + 1]);
        for (auto nv : t[v]) {
            if (nv == pre) continue;
            // we don't put a thing at position v, this transform is very very hard!!!
            f[v][i] = min(f[v][i], f[nv][i+1] + g[v][i+1] - g[nv][i]);
        }
    }

    g[v][0] = f[v][0];
    // always true thing
    for (i = 1; i <= N; ++i) g[v][i] = min(g[v][i], g[v][i-1]);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        t[u].push_back(v);
        t[v].push_back(u);
    }

    dfs(1, 0);

    printf("%d\n", g[1][0]);
    return 0;
}