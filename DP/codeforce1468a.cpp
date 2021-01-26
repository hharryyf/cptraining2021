#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;

int tree[MAX_SIZE];
void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = -MAX_SIZE;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, int val=-1) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        if (val >= 0) {
            tree[index] = max(tree[index], val);
        } else {
            tree[index]++;
        }
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return -MAX_SIZE;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int a[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i;
        set<int> vis;
        scanf("%d", &N);
        build(1, N, 1);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            vis.insert(a[i]);
        }

        int ans = 0;
        for (i = 1; i <= N; ++i) {
            int curr = max(query(1, a[i], 1, N, 1), 0) + 1;
            if (i >= 2) curr = max(2, curr);
            //cout << "i= " << i << " curr= " << curr << endl;
            //cout << query(2, 2, 1, N, 1) << endl;
            while (!vis.empty()) {
                int v = *vis.begin();
                if (v >= a[i]) break;
                vis.erase(v);
                update(v, 1, N, 1);
            }
            vis.insert(a[i]);
            update(a[i], 1, N, 1, curr);
            ans = max(ans, curr);
        }

        printf("%d\n", ans);
    }
    return 0;
}