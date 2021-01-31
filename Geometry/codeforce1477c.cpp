#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

int x[MAX_SIZE], y[MAX_SIZE];
int visited[MAX_SIZE];

typedef long long ll;

ll dist(int v, int u) {
    return 1ll * (x[v] - x[u]) * (x[v] - x[u]) + 1ll * (y[v] - y[u]) * (y[v] - y[u]);
}

int main() {
    vector<int> ret;
    int N, i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &x[i], &y[i]);
    }
    ret.push_back(1);
    visited[1] = 1;
    for (i = 2; i <= N; ++i) {
        int idx = -1;
        for (j = 1; j <= N; ++j) {
            if (visited[j]) continue;
            if (idx == -1 || dist(idx, ret.back()) <= dist(j, ret.back())) idx = j;
        }
        visited[idx] = 1;
        ret.push_back(idx);
    }

    for (auto v : ret) {
        printf("%d ", v);
    }
    return 0;
}