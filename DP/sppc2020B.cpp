#include <bits/stdc++.h>
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MAX_SIZE 262292
typedef long long ll;
using namespace std;

const ll inf = 1e17;

ll C;
int N, K;
ll dp[52][MAX_SIZE >> 1], day[52], F[52], tree[52][MAX_SIZE];

void build(int l, int r, int index, int dim) {
    if (l > r) return;
    if (l == r) {
        tree[dim][index] = dp[dim][l];
        return;
    }

    build(l, MID, LEFT, dim);
    build(MID + 1, r, RIGHT, dim);
    tree[dim][index] = max(tree[dim][LEFT], tree[dim][RIGHT]);
}

ll query(int start, int end, int l, int r, int index, int dim) {
    if (start > end || l > r || start > r || l > end) return -inf;
    if (start <= l && r <= end) return tree[dim][index];
    if (end <= MID) return query(start, end, l, MID, LEFT, dim);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT, dim);
    return max(query(start, end, l, MID, LEFT, dim), query(start, end, MID + 1, r, RIGHT, dim));
}

void update(int pt, int l, int r, int index, int dim, ll val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[dim][index] = val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, dim, val);
    } else {
        update(pt, MID + 1, r, RIGHT, dim, val);
    }

    tree[dim][index] = max(tree[dim][LEFT], tree[dim][RIGHT]);
}

int main() {
    int i, j;
    // scanf("%d%lld%d", &N, &C, &K);
    cin >> N >> C >> K;
    C *= 100;
    // dp[i][j] = max(dp[i-1][k] + (k - j) * (day[i] - day[i] / 100 * F[i]), k = j + 1 ..K)
    // dp[i-1][k] >= (k - j) * day[i] / 100 * F[i]
    // dp[i-1][k] - k * day[i] / 100 * F[i] >= -j * day[i] / 100 * F[i]
    // 
    // dp[i][j] = max(dp[i-1][k] + (-j + k) * (day[i] + day[i] / 100 * F[i]), k = 0..j - 1)
    for (i = 1; i <= N; ++i) {
        cin >> day[i] >> F[i];
        day[i] *= 100;
    }
    
    for (i = 0 ; i <= K; ++i) {
        dp[0][i] = -inf;
    }

    dp[0][0] = C;
    build(0, K, 1, 0);
    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        set<pair<ll, int>> st;
        for (j = 0 ; j <= K; ++j) {
            st.insert(make_pair(dp[i-1][j] - 1ll * j * day[i] / 100 * F[i], j));
        }

        for (j = 0 ; j <= K; ++j) {
            dp[i][j] = dp[i-1][j];
            st.erase(make_pair(dp[i-1][j] - 1ll * j * day[i] / 100 * F[i], j));
            while (!st.empty()) {
                auto p = *st.rbegin();
                if (p.first >= 1ll * -j * day[i] / 100 * F[i]) {
                    update(p.second, 0, K, 1, i - 1, dp[i-1][p.second] + 1ll * p.second * (day[i] - day[i] / 100 * F[i]));
                    st.erase(p);
                } else {
                    break;
                }
            }
            if (j > 0) {
                dp[i][j] = max(dp[i][j], query(0, j - 1, 0, K, 1, i - 1) - (day[i] + day[i] / 100 * F[i]) * j);
            }

            if (j < K) {
                dp[i][j] = max(dp[i][j], query(j + 1, K, 0, K, 1, i - 1) - (day[i] - day[i] / 100 * F[i]) * j);
            }

            update(j, 0, K, 1, i - 1, dp[i-1][j] + (day[i] + day[i] / 100 * F[i]) * j);
            if (dp[i][j] < 0) dp[i][j] = -inf;
            if (i == N) ans = max(ans, dp[i][j]);
        }
        for (j = 0; j <= K; ++j) {
            update(j, 0, K, 1, i, -inf);
        }
    }

    std::cout << ans << endl;
    return 0;
}