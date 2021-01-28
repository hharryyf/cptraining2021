#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int N;
ll lst, mn;
vector<ll> a, pre;
multiset<ll> s[2];

void init() {
    mn = 0, lst = 0;
    a.clear(), pre.clear(), s[0].clear(), s[1].clear();
    a = vector<ll>(N, 0);
    pre = vector<ll>(N, 0);
}

bool check(ll low, int dim) {
    if (s[dim].empty()) return true;
    if (*s[dim].begin() < low) return false;
    return true;
}

int main() {
    int i, T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        init();
        for (i = 0 ; i < N; ++i) {
            scanf("%I64d", &a[i]);
            if (i == 0) {
                pre[i] = a[i];
            } else {
                pre[i] = a[i] - pre[i-1];
            }

            s[i & 1].insert(pre[i]);
        }

        lst = pre[N-1];
        if (lst == 0 && check(0, 0) && check(0, 1)) {
            printf("YES\n");
            continue;
        }

        bool bad = true;
        for (i = 0 ; i < N - 1; ++i) {
            if (mn < 0) break;
            // swap a[i], a[i+1]
            // pre[i] -> pre[i] - a[i] + a[i+1]
            // pre[i+1] and onwards
            // if j and i has the same cardinality -> pre[j] = pre[j] - 2 * a[i] + 2 * a[i+1]
            // -> pre[j] = pre[j] + 2 * a[i] - 2 * a[i+1]
            s[i & 1].erase(s[i & 1].find(pre[i]));
            mn = min(mn, pre[i]);
            pre[i] = pre[i] - a[i] + a[i+1];
            ll tmp = lst;
            if (i % 2 == (N - 1) % 2) {
                tmp = tmp + a[i + 1] * 2 - a[i] * 2;
            } else {
                tmp = tmp - a[i + 1] * 2 + a[i] * 2;
            }

            if (pre[i] >= 0 && tmp == 0 
               && check(a[i] * 2 - a[i + 1] * 2, i & 1) 
               && check(-a[i] * 2 + a[i + 1] * 2, (i & 1) ^ 1)) {
                bad = false;
                break;
            }
        }

        if (bad) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}