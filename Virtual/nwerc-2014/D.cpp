#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 500021
using namespace std;

ll iceil(ll v) {
    return v / 2 + (v % 2);
}

ll ifloor(ll v) {
    return v / 2;
}

char nxt(char ch) {
    if (ch == 'L') return 'R';
    return 'L';
}

ll N;
int m;
ll wt[MAX_SIZE];
char s[MAX_SIZE][3];
vector<int> g[MAX_SIZE];
int visited[MAX_SIZE];
char ans[MAX_SIZE];
vector<int> ret;
void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }
    ret.push_back(v);
}

int main() {
    int i;
    scanf("%I64d%d", &N, &m);
    wt[1] = N;
    for (i = 1; i <= m; ++i) {
        int v1, v2;
        scanf("%s%d%d", s[i], &v1, &v2);
        g[i].push_back(v1);
        g[i].push_back(v2);        
    }
    
    for (i = 1; i <= m; ++i) {
        if (!visited[i]) dfs(i);
    }

    reverse(ret.begin(), ret.end());
    for (auto v : ret) {
        if (wt[v] % 2 == 0) {
            ans[v] = s[v][0];
        } else {
            ans[v] = nxt(s[v][0]);
        }

        int idx = s[v][0] == 'L' ? 0 : 1;
        if (!g[v].empty()) {
            wt[g[v][idx]] += iceil(wt[v]);
            wt[g[v][idx^1]] += ifloor(wt[v]);
        }
    }

    printf("%s", ans + 1);
    return 0;
}