#include <bits/stdc++.h>
#define MAX_SIZE 10011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
int cnt, N, cid = 1;

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
            cmpid[st.top()] = cid;
            st.pop();
        }

        cmpid[st.top()] = cid++;
        instack[st.top()] = 0;
        st.pop();
    }
}

int pos(int x, char ch) {
    if (ch == 'R') {
        return 2 * x;
    } else {
        return 2 * x - 1;
    }
}

int neg(int x, char ch) {
    if (ch == 'R') {
        return 2 * x - 1;
    }
    return 2 * x;
}

char s[4], t[4], r[4];

void add(int u, int v) {
    g[u].push_back(v);
}
// R means true
// B means false
int main() {
    int i, N, M;
    scanf("%d%d", &N, &M);
    for (i = 0 ; i < M; ++i) {
        int v, u, w;
        scanf("%d%s%d%s%d%s", &v, s, &u, t, &w, r);
        add(neg(v, s[0]), pos(u, t[0]));
        add(neg(u, t[0]), pos(v, s[0]));
        add(neg(v, s[0]), pos(w, r[0]));
        add(neg(w, r[0]), pos(v, s[0]));
        add(neg(u, t[0]), pos(w, r[0]));
        add(neg(w, r[0]), pos(u, t[0]));
    }

    for (i = 1 ; i <= 2 * N; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (cmpid[2 * i] == cmpid[2 * i - 1]) {
            printf("-1\n");
            return 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (cmpid[2 * i] < cmpid[2 * i - 1]) {
            printf("R");
        } else {
            printf("B");
        }
    }
    printf("\n");
    return 0;
}