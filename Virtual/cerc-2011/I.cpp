#include <bits/stdc++.h>
#define MAX_SIZE 2097312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)

using namespace std;

int tree[MAX_SIZE];

struct qrs {
    int l, r, id;
    bool operator < (qrs other) const {
        return r < other.r;
    }
};

qrs q[MAX_SIZE];
int ans[MAX_SIZE];
int N, Q;

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index] = MAX_SIZE;
    if (l == r) {
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    }
    if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    }
    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int a[MAX_SIZE], p[MAX_SIZE];
map<int, int> pre;

int main() {
    int i, j;
    while (scanf("%d%d", &N, &Q) != EOF) {
        if (N == 0 && Q == 0) break;
        build(1, N, 1);
        for (i = 1; i <= N; ++i) p[i] = -1;
        pre.clear();
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            if (pre.find(a[i]) != pre.end()) {
                p[i] = pre[a[i]];
            } else {
                p[i] = -1;
            }
            pre[a[i]] = i;
        }

        for (i = 1; i <= Q; ++i) {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].id = i;
            ans[i] = -1;
        }

        sort(q + 1, q + 1 + Q);

        for (i = 1, j = 1; i <= N; ++i) {
            if (p[i] != -1) {
                update(p[i], 1, N, 1, i);
            }

            while (j <= Q && q[j].r <= i) {
                int val = query(q[j].l, q[j].r, 1, N, 1);
                // cout << "query " << q[j].l << " " << q[j].r << " get " << val << endl;
                if (val <= q[j].r) {
                    ans[q[j].id] = a[val];
                } else {
                    ans[q[j].id] = -1;
                }
                j++;
            }
        }

        for (i = 1; i <= Q; ++i) {
            if (ans[i] == -1) {
                printf("OK\n");
            } else {
                printf("%d\n", ans[i]);
            }
        }
        printf("\n");
    }
    return 0;
}