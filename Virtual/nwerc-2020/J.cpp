#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
set<int> A, B;
vector<int> path;
int visited[MAX_SIZE];

void dfs(int v) {
    visited[v] = 1;
    path.push_back(v);
    A.erase(v);
    if (A.size() == B.size()) {
        printf("%d %d\n", (int) path.size(), (int) A.size());
        for (auto v : path) {
            printf("%d ", v);
        }
        printf("\n");
        for (auto v : A) {
            printf("%d ", v);
        }
        printf("\n");
        for (auto v : B) {
            printf("%d ", v);
        }
        printf("\n");
        exit(0);
    }

    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }

    path.pop_back();
    B.insert(v);
    if (A.size() == B.size()) {
        printf("%d %d\n", (int) path.size(), (int) A.size());
        for (auto v : path) {
            printf("%d ", v);
        }
        printf("\n");
        for (auto v : A) {
            printf("%d ", v);
        }
        printf("\n");
        for (auto v : B) {
            printf("%d ", v);
        }
        printf("\n");
        exit(0);
    }
}

int main() {
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (i = 0 ; i < m; ++i) {
        int v, u;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (i = 1; i <= n; ++i) A.insert(i);
    dfs(1);
    return 0;
}