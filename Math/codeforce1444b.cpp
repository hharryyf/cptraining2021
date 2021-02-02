#include <bits/stdc++.h>
typedef long long ll; 
using namespace std;
#define MAX_SIZE 300011
const ll mod = 998244353;

ll inv(ll v) {
    ll p = mod - 2, ret = 1;
    while (p > 0) {
        if (p % 2 == 0) {
            v = v * v;
            v %= mod;
            p /= 2;
        } else {
            ret = ret * v;
            ret %= mod;
            p--;
        }
    }

    return ret;
}

ll fac[MAX_SIZE], ivfac[MAX_SIZE];

void init() {
    int i;
    fac[0] = ivfac[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        fac[i] = fac[i-1] * i;
        ivfac[i] = ivfac[i-1] * inv(i);
        fac[i] %= mod;
        ivfac[i] %= mod;
    }
}

ll C(int n, int k) {
    if (n < k) return 0;
    ll ret = fac[n] * ivfac[n-k];
    ret %= mod;
    ret *= ivfac[k];
    ret %= mod;
    return ret;
}

int a[MAX_SIZE], N;

int main() {
    int i;
    scanf("%d", &N);
    init();
    for (i = 1; i <= N * 2; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a + 1, a + 1 + N * 2);
    ll ans = 0;
    for (i = 1; i <= 2 * N; ++i) {
        if (i <= N) ans = ans - C(2*N, N) * a[i];
        else {
            ans = ans + C(2 * N, N) * a[i];
        }
        ans %= mod;
        if (ans < 0) ans += mod;
    }

    printf("%I64d\n", ans);
    return 0;
}