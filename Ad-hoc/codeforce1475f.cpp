#include <bits/stdc++.h>
#define MAX_SIZE 4011
using namespace std;

int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
int cnt = 0;
stack<int> st;
vector<int> g[MAX_SIZE];

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    visited[v] = low[v] = ++cnt;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]);
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            instack[st.top()] = 0;
            cmpid[st.top()] = v;
            st.pop();
        }

        cmpid[st.top()] = v;
        instack[st.top()] = 0;
        st.pop();

    }
}

int N;
char a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE];

void init() {
    cnt = 0;
    while (!st.empty()) st.pop();
    for (int i = 0 ; i <= 4 * N + 1; ++i) {
        visited[i] = low[i] = instack[i] = cmpid[i] = 0;
        g[i].clear();
    }
}

int pos(int x) {
    return x * 2 - 1;
}

int neg(int x) {
    return x * 2;
}

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        init();
        for (i = 1; i <= N; ++i) scanf("%s", a[i] + 1);
        for (i = 1; i <= N; ++i) scanf("%s", b[i] + 1);
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                if (a[i][j] == b[i][j]) {
                    g[pos(i)].push_back(pos(N + j));
                    g[pos(N + j)].push_back(pos(i));
                    g[neg(N + j)].push_back(neg(i));
                    g[neg(i)].push_back(neg(N + j));
                } else {
                    // pos(i) <-> neg(N + j)
                    // neg(i) <-> pos(N + j)
                    g[pos(i)].push_back(neg(N + j));
                    g[neg(i)].push_back(pos(N + j));
                    g[neg(N + j)].push_back(pos(i));
                    g[pos(N + j)].push_back(neg(i));
                }
            }
        }

        for (i = 1; i <= 4 * N; ++i) {
            if (!visited[i]) {
                tarjan(i);
            }
        }

        int bad = 0;
        for (i = 1; i <= 2 * N; ++i) {
            if (cmpid[pos(i)] == cmpid[neg(i)]) {
                bad = 1;
            }
        }

        printf("%s\n", bad ? "NO" : "YES");
    }
    
    return 0;
}