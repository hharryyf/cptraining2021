#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

int visited[MAX_SIZE], N, M;
vector<int> g[MAX_SIZE];
void init() {
    int i;
    for (i = 1; i <= N; ++i) {
        g[i].clear();
        visited[i] = 0;
    }
}

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) dfs(nv);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        init();
        for (int i = 1; i <= M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs(1);
        bool bad = false;
        for (int i = 1; i <= N; ++i) {
            if (!visited[i]) {
                printf("NO\n");
                bad = true;
                break;
            }
        }

        if (bad) continue;
        for (int i = 1; i <= N; ++i) {
            visited[i] = -1;
        }

        printf("YES\n");
        vector<int> ret;
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (visited[v] == 1) continue;
            if (visited[v] == 0) {
                for (auto nv : g[v]) {
                    if (visited[nv] == -1) {
                        q.push(nv);
                    }
                }
            } else {
                visited[v] = 1;
                ret.push_back(v);
                for (auto nv : g[v]) {
                    visited[nv] = 0;
                    q.push(nv);
                }
            }
        }
        
        sort(ret.begin(), ret.end());
        printf("%d\n", (int) ret.size());
        for (auto v : ret) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}