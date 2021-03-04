#include <bits/stdc++.h>
#define MAX_SIZE 1011
typedef long long ll;
using namespace std;
struct position {
    int x, y;
    ll cost;
    position(int x, int y, int cost) {
        this->x = x, this->y = y, this->cost = cost;
    }

    bool operator < (position other) const {
        return cost > other.cost;
    }
};

const ll inf = 1e10;
char g[MAX_SIZE][MAX_SIZE];
int cost[300], N, M, K;
int visited[MAX_SIZE][MAX_SIZE];
ll dist[MAX_SIZE][MAX_SIZE];
int dx[4] = {1, 0, 0, -1}, dy[4] = {0, 1, -1, 0};
void init() {
    int i;
    for (i = 0 ; i < 26; ++i) cost[i] = 0;
}

void dijkstra() {
    int i, j;
    priority_queue<position> q;
    for (i = 0; i <= N; ++i) {
        for (j = 0; j <= M; ++j) {
            visited[i][j] = 0;
            if (g[i][j] == 'E') {
                dist[i][j] = 0;
                q.push(position(i, j, 0));
            } else {
                dist[i][j] = inf;
            }
        }
    }

    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (p.x == 1 || p.y == 1 || p.x == N  || p.y == M ) {
            printf("%I64d\n", p.cost);
            return;
        }

        if (visited[p.x][p.y]) continue;
        visited[p.x][p.y] = 1;
        dist[p.x][p.y] = min(dist[p.x][p.y], p.cost);
        for (i = 0 ; i < 4; ++i) {
            int x = p.x + dx[i], y = p.y + dy[i];
            if (x <= 0 || y <= 0 || x >= N + 1 || y >= M + 1) continue;
            if (!visited[x][y]) {
                int w = 0;
                if (x >= 1 && x <= N && y >= 1 && y <= M) w = cost[g[x][y] - 'A']; 
                if (dist[x][y] > p.cost + w) {
                    dist[x][y] = p.cost + w;
                    q.push(position(x, y, dist[x][y]));
                }
            }
        }
    }
}

char ss[4];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int K;
        scanf("%d%d%d", &K, &M, &N);
        init();
        while (K-- > 0) {
            int v;
            scanf("%s%d", ss, &v);
            cost[ss[0] - 'A'] = v;
        }

        for (int i = 1; i <= N; ++i) {
            scanf("%s", g[i] + 1);
        }

        dijkstra();
    }
    return 0;
}