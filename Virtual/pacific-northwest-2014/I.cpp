#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 2097333
using namespace std;
struct segt {
    int mx, mn, lz;
};

int N, Q;
segt tree[MAX_SIZE];
int id[MAX_SIZE], sz[MAX_SIZE], a[MAX_SIZE], rid[MAX_SIZE], cnt;
vector<int> g[MAX_SIZE >> 1];

void dfs(int v) {
    id[v] = ++cnt;
    rid[id[v]] = v;
    sz[v] = 1;
    for (auto nv : g[v]) {
        dfs(nv);
        sz[v] += sz[nv];
    }
}

void init() {
    int i;
    cnt = 0;
    for (i = 1; i <= N; ++i) {
        g[i].clear();
        id[i] = sz[i] = 0;
    }
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
            tree[LEFT].mx += tree[index].lz;
            tree[LEFT].mn += tree[index].lz;
            tree[RIGHT].mx += tree[index].lz;
            tree[RIGHT].mn += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].lz = 0;
    if (l == r) {
        tree[index].mx = tree[index].mn = a[rid[l]];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].mx = max(tree[LEFT].mx, tree[RIGHT].mx);
    tree[index].mn = min(tree[LEFT].mn, tree[RIGHT].mn);
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].mx += val, tree[index].mn += val;
        tree[index].lz += val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    }
    tree[index].mx = max(tree[LEFT].mx, tree[RIGHT].mx);
    tree[index].mn = min(tree[LEFT].mn, tree[RIGHT].mn);
}

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.lz = 0;
    ret.mn = min(t1.mn, t2.mn);
    ret.mx = max(t1.mx, t2.mx);
    return ret;
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        return tree[index];
    }

    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    } 

    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

char s[4];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        init();
        for (i = 2; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            g[v].push_back(i);
        }

        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        dfs(1);
        build(1, N, 1);
        scanf("%d", &Q);
        while (Q-- > 0) {
            int v;
            scanf("%s%d", s, &v);
            int l = id[v], r = id[v] + sz[v] - 1;
            if (s[0] == 'Q') {
                auto ret = query(l, r, 1, N, 1);
                printf("%d\n", ret.mx - ret.mn);
            } else {
                int u;
                scanf("%d", &u);
                update(l, r, 1, N, 1, u);
            }
        }
    }
    return 0;
}