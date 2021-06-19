#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

struct node {
    int r, c, ht;
    bool operator <(node other) const {
        return ht > other.ht;
    }
};

int h[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int ret[MAX_SIZE][MAX_SIZE];
int N, M;

int dx[8] = {0,0,1,-1,1,1,-1,-1};
int dy[8] = {1,-1,0,0,1,-1,1,-1};

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &h[i][j]);
        }
    }

    int sx, sy;
    long long ans = 0;
    scanf("%d%d", &sx, &sy);
    priority_queue<node> q;
    ret[sx][sy] = h[sx][sy];
    q.push(node{sx, sy, h[sx][sy]});
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if (visited[curr.r][curr.c]) continue;
        visited[curr.r][curr.c] = 1;
        ans = ans - ret[curr.r][curr.c];
        for (i = 0 ; i < 8; ++i) {
            int tx = dx[i] + curr.r, ty = dy[i] + curr.c;
            if (tx <= 0 || tx > N || ty <= 0 || ty > M) continue;
            if (!visited[tx][ty] && ret[tx][ty] > max(ret[curr.r][curr.c], h[tx][ty])) {
                ret[tx][ty] = max(ret[curr.r][curr.c], h[tx][ty]);
                q.push(node{tx, ty, ret[tx][ty]});
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}