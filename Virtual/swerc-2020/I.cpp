#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
int visited[MAX_SIZE], dist[MAX_SIZE];
int N, M;
int BFS(int u) {
    queue<int> q;
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) dist[i] = MAX_SIZE, visited[i] = 0;
    q.push(u);
    dist[u] = 0;
    int ans = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        for (auto nv : g[v]) {
            if (!visited[nv] && dist[nv] > dist[v] + 1) {
                q.push(nv);
                dist[nv] = dist[v] + 1;
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        if (!visited[i]) return -1;
        ans = max(ans, dist[i]);
    }

    return ans;
}


int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = N;
    srand(19260817);
    for (i = 0 ; i < 200; ++i) {
        int v = rand() % N + 1;
        int d = BFS(v);
        if (d == -1) {
            printf("-1\n");
            return 0;
        }
        ans = min(ans, d);
    }

    int d = 1, ds = 1;
    while (d < ans) {
        d = d * 2;
        ds++;
    }
    printf("%d\n", ds);
    return 0;
}