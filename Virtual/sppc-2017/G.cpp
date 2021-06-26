#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
int N, deg[MAX_SIZE], in[MAX_SIZE];

bool valid(int k) {
    int i;
    queue<int> q;
    for (i = 1; i <= N; ++i) {
        deg[i] = (int) g[i].size();
        in[i] = 1;
        if (deg[i] < k) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (!in[v]) continue;
        in[v] = 0;
        deg[v] = 0;
        for (auto nv : g[v]) {
            if (in[nv]) {
                deg[nv]--;
                if (deg[nv] < k) q.push(nv);
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        if (in[i] == 1) return false;
    }

    return true;
}

int main() {
    int M, i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int low = 1, high = N, ans = N;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (valid(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}