#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1024+5;
ll tree[N<<1][N<<1];
int n;
ll maxv = -1e18;
const ll inf = 1e18;

int shift(int x) {
    return x & (-x);
}

void update(int x, int y, ll val) {
    while (x <= n) {
        int ty = y;
        while (ty <= n) {
            tree[x][ty] = max(tree[x][ty], val);
            ty = ty + shift(ty);
        }
        x = x + shift(x);
    }
}

ll query(int x, int y) {
    ll ret = -inf;
    while (x >= 1) {
        int ty = y;
        while (ty >= 1) {
            ret = max(tree[x][ty], ret);
            ty = ty - shift(ty);
        }
        x = x - shift(x);
    }
    return ret;
}

struct qrs {
    int id, l, r;
    ll sm;
    bool operator < (qrs other) const {
        if (sm != other.sm) return sm < other.sm;
        if (id != other.id) return id < other.id;
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

qrs q[4511111];
ll ans[200011];
ll pre[2011];
int sz, m, qsz = 0;

int main() {
    int i, j;
    scanf("%d%d", &sz, &m);
    n = sz;
    for (i = 1; i <= sz; ++i) {
        scanf("%I64d", &pre[i]);
        pre[i] += pre[i-1];
    }

    for (i = 0 ; i < 2058; ++i) {
        for (j = 0 ; j < 2058; ++j) {
            tree[i][j] = -inf;
        }
    }
    for (i = 1 ; i <= sz; ++i) {
        for (j = 1; j <= i; ++j) {
            q[qsz++] = qrs{0, n - j + 1, i, pre[i] - pre[j-1]};
        }
    }

    for (i = 1; i <= m; ++i) {
        int l, r;
        ll v;
        scanf("%d%d%I64d", &l, &r, &v);
        q[qsz++] = qrs{i, n - l + 1, r, v};
    }

    sort(q, q + qsz);
    for (i = 0 ; i < qsz; ++i) {
        if (q[i].id == 0) {
            update(q[i].l, q[i].r, q[i].sm);
        } else {
            ans[q[i].id] = query(q[i].l, q[i].r);
        }
    }

    for (i = 1; i <= m; ++i) {
        if (ans[i] != -inf) {
            printf("%I64d\n", ans[i]);
        } else {
            printf("NONE\n");
        }
    }
    return 0;
}