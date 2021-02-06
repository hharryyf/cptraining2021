#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT  (index<<1|1)
typedef long long ll;
#define MAX_SIZE 262192
using namespace std;

struct segt {
    int cnt[2];
    ll val;
};

segt tree[MAX_SIZE];
int a[MAX_SIZE];
char s[MAX_SIZE];
ll x, y;
int N;

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.cnt[0] = t1.cnt[0] + t2.cnt[0];
    ret.cnt[1] = t1.cnt[1] + t2.cnt[1];
    ret.val = t1.val + t2.val + x * t1.cnt[0] * t2.cnt[1] + y * t1.cnt[1] * t2.cnt[0];
    return ret;
} 

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].cnt[a[l]] = 1;
        tree[index].cnt[a[l] ^ 1] = 0;
        tree[index].val = 0;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index].cnt[val] = 1;
        tree[index].cnt[val ^ 1] = 0;
        tree[index].val = 0;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

int main() {
    int i;
    scanf("%s", s + 1);
    N = strlen(s + 1);
    scanf("%I64d%I64d", &x, &y);
    for (i = 1; i <= N; ++i) {
        if (s[i] == '?') {
            a[i] = 0;
        } else {
            a[i] = s[i] - '0';
        }
    }

    build(1, N, 1);
    ll ans = tree[1].val;
    for (i = 1; i <= N; ++i) {
        if (s[i] == '?') {
            update(i, 1, N, 1, 1);
        }

        ans = min(ans, tree[1].val);
    }

    for (i = 1; i <= N; ++i) {
        if (s[i] == '?') {
            a[i] = 1;
        } else {
            a[i] = s[i] - '0';
        }
    }

    build(1, N, 1);
    ans = min(ans, tree[1].val);
    for (i = 1; i <= N; ++i) {
        if (s[i] == '?') {
            update(i, 1, N, 1, 0);
        }

        ans = min(ans, tree[1].val);
    }

    cout << ans << endl;
    return 0;
}