#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef int ll;
const int inf = 500000000;

int N, M, L, U;
vector<pair<int, ll>> g[MAX_SIZE];
int dist[MAX_SIZE], visited[MAX_SIZE];
pair<int, int> edg[MAX_SIZE];

void dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    for (int i = 2; i < MAX_SIZE; ++i) dist[i] = inf;
    memset(visited, 0, sizeof(visited));
    q.push(make_pair(0, 1));
    dist[1] = 0;
    while (!q.empty()) {
        auto np = q.top();
        q.pop();
        int curr = np.second, d = np.first;
        if (visited[curr]) continue;
        visited[curr] = 1;
        dist[curr] = d;
        for (auto nv : g[curr]) {
            int w = nv.second, v = nv.first;
            if (!visited[v] && dist[v] > dist[curr] + w) {
                dist[v] = dist[curr] + w;
                q.push(make_pair(dist[v], v));
            }
        } 
    }
}

int main() {
    int i, ans = 0;
    scanf("%d%d%d%d", &N, &M, &L, &U);
    for (i = 1; i <= M; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        x++, y++;
        g[x].emplace_back(y, 2 * w);
        g[y].emplace_back(x, 2 * w);
        edg[i] = {x, y};
    }   

    dijkstra();
    for (i = 1; i <= M; ++i) {
        if (dist[edg[i].first] < U || dist[edg[i].second] < U) ans++;
    }

    printf("%d\n", ans);
    return 0;
}