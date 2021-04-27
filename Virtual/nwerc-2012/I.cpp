#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

vector<int> g[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt = 0;

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


int pos(int v) {
	return v * 2;
}

int neg(int v) {
	return v * 2 - 1;
}

void addedge(int x, int y) {
    int fx = x < 0 ? neg(-x) : pos(x), fy = y < 0 ? neg(-y) : pos(y);
    g[fx].push_back(fy);
}

void solve(int n, int m) {
    int i;
    for (i = 1; i <= n * 2; ++i) g[i].clear();
    for (i = 1; i <= n * 2; ++i) {
        cmpid[i] = low[i] = instack[i] = visited[i] = 0;
    }
    
    cnt = 0;
    while (!st.empty()) st.pop();

    addedge(-1, 1);
    for (i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(-x, y);
        addedge(-y, x);
    }

    for (i = 1; i <= n * 2; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= n; ++i) {
        if (cmpid[pos(i)] == cmpid[neg(i)]) {
            printf("no\n");
            return;
        }
    }
    printf("yes\n");
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        solve(n, m);
    }
    return 0;
}