#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
const ll inf = 1e10;
ll x[MAX_SIZE], y[MAX_SIZE];
vector<ll> xsum, ysum;
vector<ll> dx, dy;
vector<int> xcnt, ycnt;
ll d;
int N;

/*
    / \
   /   \
   \   /
    \ /
  x + L, x + R
  -x + U, -x + D
*/

ll L = inf, R = -inf, U = inf, D = -inf;

ll cost(vector<int> &vcnt, vector<ll> &vsum, vector<ll> &pos, ll coord) {
    if (pos.front() >= coord) return vsum.back() - coord * N;
    if (pos.back() <= coord) return coord * N - vsum.back();
    int idx = upper_bound(pos.begin(), pos.end(), coord) - pos.begin() - 1;
    int c1 = vcnt[idx], c2 = N - c1;
    ll sm1 = vsum[idx], sm2 = vsum.back() - sm1;
    return 1ll * c1 * coord - sm1 + sm2 - 1ll * c2 * coord;
}

ll calc(ll xpos) {
    ll ret = 1e17;
    ll l = max(-xpos + D, xpos + R), r = min(-xpos + U, xpos + L);
    int i;
    for (i = 0 ; i < 80 && l + 5 <= r; ++i) {
        ll lp = l + (r - l) / 3;
        ll rp = r - (r - l) / 3;
        if (cost(ycnt, ysum, dy, lp) <= cost(ycnt, ysum, dy, rp)) {
            r = rp;
        } else {
            l = lp;
        }
    }
    
    ret = cost(ycnt, ysum, dy, l);
    for (i = l; i <= r; ++i) {
        ret = min(ret, cost(ycnt, ysum, dy, i));
    }

    return ret + cost(xcnt, xsum, dx, xpos);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%I64d%I64d", &x[i], &y[i]);
    }

    scanf("%I64d", &d);
    for (i = 1; i <= N; ++i) {
        // up point (x[i], y[i] + D), down point (x[i], y[i] - D)
        // left point (x[i] - D, y[i]), right point (x[i] + D, y[i])
        L = min(L, y[i] - x[i] + d);
        R = max(R, y[i] - x[i] - d);
        U = min(U, y[i] + d + x[i]);
        D = max(D, x[i] + y[i] - d);
        if (L < R || U < D) {
            printf("impossible\n");
            return 0;
        }
    }

    sort(x + 1, x + 1 + N);
    sort(y + 1, y + 1 + N);
    for (i = 1; i <= N; ++i) {
        if (i == 1 || x[i] != x[i-1]) {
            dx.push_back(x[i]);
        }

        if (i == 1 || y[i] != y[i-1]) {
            dy.push_back(y[i]);
        }
    }

    xcnt = vector<int>(dx.size(), 0);
    ycnt = vector<int>(dy.size(), 0);
    xsum = vector<ll>(dx.size(), 0ll);
    ysum = vector<ll> (dy.size(), 0ll);
    for (i = 1; i <= N; ++i) {
        int idx = lower_bound(dx.begin(), dx.end(), x[i]) - dx.begin();
        xcnt[idx]++;
        xsum[idx] += x[i];
        idx = lower_bound(dy.begin(), dy.end(), y[i]) - dy.begin();
        ycnt[idx]++;
        ysum[idx] += y[i];
    }

    for (i = 1; i < (int) dx.size(); ++i) {
        xcnt[i] += xcnt[i-1];
        xsum[i] += xsum[i-1];
    }

    for (i = 1; i < (int) dy.size(); ++i) {
        ycnt[i] += ycnt[i-1];
        ysum[i] += ysum[i-1];
    }

    ll ans = 1e17, l = (D - L + 1) / 2, r = (U - R) / 2;
    for (i = 0; i < 80 && l + 5 <= r; ++i) {
        ll lp = l + (r - l) / 3, rp = r - (r - l) / 3;
        if (lp > rp) break;
        if (calc(lp) <= calc(rp)) {
            r = rp;
        } else {
            l = lp;
        }
    }
    
    ans = calc(l);
    for (i = l; i <= r; ++i) {
        ans = min(ans, calc(i));
    }
    
    printf("%I64d\n", ans);
    return 0;
}