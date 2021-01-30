#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

struct segt {
    int val, lz;
};

char s[MAX_SIZE];
char f[MAX_SIZE];
segt tree[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].lz = -1;
    if (l == r) {
        tree[index].val = s[l] - '0';
        return; 
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].val = tree[LEFT].val + tree[RIGHT].val;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != -1) {
        if (l != r) {
            tree[LEFT].lz = tree[RIGHT].lz = tree[index].lz;
            tree[LEFT].val = (MID - l + 1) * tree[index].lz;
            tree[RIGHT].val = (r - MID) * tree[index].lz;
        }
    }
    tree[index].lz = -1;
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) return tree[index].val;
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

void update(int start, int end, int l, int r, int index, int v) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].val = v * (r - l + 1);
        tree[index].lz = v;
        return;
    }
    if (end <= MID) {
        update(start, end, l, MID, LEFT, v);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v);
    } else {
        update(start, end, l, MID, LEFT, v);
        update(start, end, MID + 1, r, RIGHT, v);
    }
    tree[index].val = tree[LEFT].val + tree[RIGHT].val;
}

int check(int l, int r, int index) {
    if (l > r) return 1;
    pushdown(l, r, index);
    if (l == r) return tree[index].val == (f[l] - '0');
    return check(l, MID, LEFT) && check(MID + 1, r, RIGHT);
}

pair<int, int> q[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, Q, valid = 1;
        scanf("%d%d", &N, &Q);
        scanf("%s%s", f + 1, s + 1);
        build(1, N, 1);
        for (int i = 1; i <= Q; ++i) scanf("%d%d", &q[i].first, &q[i].second);
        while (Q > 0) {
            int l = q[Q].first, r = q[Q].second, mx;
            if ((r - l + 1) % 2 == 0) {
                mx = ((r - l + 1) / 2) - 1;
            } else {
                mx = (r - l + 1) / 2;
            }

            int val = query(l, r, 1, N, 1), d = (r - l + 1) - val;
            if (val <= mx) {
                update(l, r, 1, N, 1, 0);
            } else if (d <= mx) {
                update(l, r, 1, N, 1, 1);
            } else {
                valid = 0;
            }
            Q--;
        }
        
        printf("%s\n", (check(1, N, 1) && valid) ? "YES" : "NO");
    }
    return 0;
}