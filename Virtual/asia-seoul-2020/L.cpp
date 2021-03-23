#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
typedef long long ll;

const ll inf = 1e18;
ll h[MAX_SIZE], a[MAX_SIZE][2], b[MAX_SIZE][2];
int N;

ll calc(int i1, int i2) {
    return 1ll * abs(b[i2][0] - a[i1][0]) * llabs(b[i2][1] - a[i1][1]);
}

ll divc(int start, int end, int l, int r) {
    if (start > end || l > r) return -inf;
    int i, pos = l, mid = (start + end)>>1;
    ll ret = calc(mid, l);
    for (i = l + 1; i <= r; ++i) {
        auto curr = calc(mid, i);
        if (curr >= ret) { 
            ret = curr;
            pos = i;
        }
    }
    return max(ret, max(divc(start, mid - 1, l, pos), divc(mid + 1, end, pos, r)));
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%I64d", &h[i]);
    int n = 0, m = 0;
    for (i = 1; i <= N; ++i) {
        if (i == 1 || h[i] > a[n][1]) {
            a[++n][1] = h[i];
            a[n][0] = i;
        }
    }

    vector<pair<ll, ll>> st;
    for (i = N; i >= 1; --i) {
        if (i == N || -h[i] < st.back().second) {
            st.emplace_back(i, -h[i]);
        }
    }

    reverse(st.begin(), st.end());

    for (auto v : st) {
        b[++m][1] = v.second;
        b[m][0] = v.first;
    }

    printf("%I64d\n", divc(1, n, 1, m));
    return 0;
}