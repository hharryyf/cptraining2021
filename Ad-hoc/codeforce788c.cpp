#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;
const int inf = 1e8;
int visited[MAX_SIZE], dist[MAX_SIZE];
int ok[MAX_SIZE];
set<int> s;

int main() {
    int i, N, K;
    scanf("%d%d", &N, &K);
    for (i = 0 ; i < MAX_SIZE; ++i) {
        dist[i] = inf;
    }

    for (i = 0 ; i < K; ++i) {
        int v;
        scanf("%d", &v);
        s.insert(N - v);
        ok[1000 - (N - v)] = 1;
    }

    queue<int> q;
    vector<int> diff;
    for (auto v : s) diff.push_back(v);
    q.push(1000);
    dist[1000] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        if (ok[v]) {
            printf("%d\n", dist[v] + 1);
            return 0;
        }

        for (auto d : diff) {
            if (d + v <= 2000 && d + v >= 0 && !visited[d + v]) {
                dist[d + v] = min(dist[d + v], dist[v] + 1);
                q.push(d + v);
            }
        }
    }

    printf("-1\n");
    return 0;
}