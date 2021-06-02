#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;

vector<int> g[MAX_SIZE];
int deg[MAX_SIZE];
int tp[MAX_SIZE], visited[MAX_SIZE];
deque<int> q;
vector<int> ans;
int N, M;

int solve(int p) {
    int i;
    ans.clear();
    q.clear();    
    for (i = 1; i <= N; ++i) {
        visited[i] = 0;
        deg[i] = 0;
    }

    for (i = 1; i <= N; ++i) {
        for (auto v : g[i]) {
            deg[v]++;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (deg[i] == 0) {
            if (tp[i] == 1) {
                q.push_front(i);
            } else {
                q.push_back(i);
            }
        }
    }

    int curr = p;
    while (!q.empty()) {
        int nxt;
        if (curr == 1) {
            nxt = q.front();
            q.pop_front();
        } else {
            nxt = q.back();
            q.pop_back();
        }

        if (visited[nxt]) continue;
        curr = tp[nxt];
        visited[nxt] = 1;
        ans.push_back(nxt);
        for (auto nv : g[nxt]) {
            deg[nv]--;
            if (deg[nv] == 0 && !visited[nv]) {
                if (tp[nv] == 1) {
                    q.push_front(nv);
                } else {
                    q.push_back(nv);
                }
            }
        }
    }   

    int ret = 0;
    for (i = 0 ; i < (int) ans.size() - 1; ++i) {
        if (tp[ans[i]] != tp[ans[i+1]]) {
            ret++;
        }
    }

    return ret;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        for (i = 1; i <= N; ++i) {
            g[i].clear();
        }

        for (i = 1; i <= N; ++i) {
            scanf("%d", &tp[i]);
        }

        for (i = 1; i <= M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
        }
      
        printf("%d\n", min(solve(1), solve(2)));
    }
    return 0;
}