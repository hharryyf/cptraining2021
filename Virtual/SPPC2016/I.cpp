#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 200011
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

ll tree[MAX_SIZE * 8];
int tmp[MAX_SIZE], x[MAX_SIZE], y[MAX_SIZE];
vector<int> disc;

void update(int pt, int l, int r, int index, ll val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = max(tree[index], val);
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

ll query(int start, int end, int l, int r, int index) {
    if (start > r || l > end || start > end || l > r) return 0;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int N, i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        tmp[i * 2 - 1] = x[i];
        tmp[i * 2] = y[i];
    }

    sort(tmp + 1, tmp + 2 * N + 1);
    for (i = 1; i <= 2 * N; ++i) {
        if (i == 1 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    int sz = disc.size();

    for (i = 1; i <= N; ++i) {
        int idx = lower_bound(disc.begin(), disc.end(), x[i]) - disc.begin() - 1;
        ll v = query(0, idx, 0, sz - 1, 1);
        idx = lower_bound(disc.begin(), disc.end(), y[i]) - disc.begin();
        update(idx, 0, sz - 1, 1, v + y[i] - x[i] + 1);
    }

    cout << tree[1] << endl;
    return 0;
}