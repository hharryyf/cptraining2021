#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;


struct edge {
    int from, to;
};

int N;
vector<int> deg;
edge edg[MAX_SIZE];
vector<int> g[MAX_SIZE];
int bad[MAX_SIZE];

void init() {
    int i;
    deg.clear();
    for (i = 1; i <= N; ++i) {
        g[i].clear();
    }

    for (i = 1; i < N; ++i) {
        if (!bad[edg[i].from] && !bad[edg[i].to]) {
            g[edg[i].from].push_back(edg[i].to);
            g[edg[i].to].push_back(edg[i].from);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (!bad[i]) {
            if ((int) g[i].size() <= 1) {
                deg.push_back(i);
            }
        }
    }
}

int visited[MAX_SIZE], pre[MAX_SIZE];

void markvis(int u, int v) {
    int i;
    queue<int> q;
    for (i = 1 ; i <= N; ++i) {
        pre[i] = visited[i] = 0;
    }

    q.push(u);
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        if (curr == v) break;
        if (visited[curr]) continue;
        visited[curr] = 1;
        for (auto nv : g[curr]) {
            if (!visited[nv]) {
                q.push(nv);
                pre[nv] = curr;
            }
        }
    }

    int curr = v;
    while (curr != 0) {
        bad[curr] = 1;
        curr = pre[curr];
    }
}

int conn[MAX_SIZE];

void dfs(int v, int pre) {
    conn[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre && !bad[nv]) dfs(nv, v);
    }
}

void query(int u, int v) {
    int i, ret;
    printf("? %d %d\n", u, v);
    fflush(stdout);
    scanf("%d", &ret);
    if (ret == -1) {
        exit(0);
    }

    markvis(u, v);
    for (i = 1; i <= N; ++i) conn[i] = 0;
    dfs(ret, 0);
    for (i = 1; i <= N; ++i) {
        if (!bad[i] && !conn[i]) bad[i] = 1;
    }
    bad[ret] = 0;
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        edg[i].from = u, edg[i].to = v;
    }

    while (true) {
        init();
        if (deg.empty()) {
            printf("! %d\n", -1);
            return 0;
        }

        if ((int) deg.size() == 1) {
            printf("! %d\n", deg.back());
            return 0;
        }

        query(deg[0], deg[1]);
    }
    return 0;
}