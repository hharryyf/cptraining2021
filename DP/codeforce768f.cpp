#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
ll fac[MAX_SIZE], inv[MAX_SIZE];
int F, W, H;

ll fastpower(ll v, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * v;
            ret %= mod;
            p--;
        } else {
            v = v * v;
            v %= mod;
            p /= 2;
        }
    }

    return ret;
}

void init() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i < MAX_SIZE; ++i) {
        fac[i] = fac[i-1] * i;
        inv[i] = inv[i-1] * fastpower(i, mod - 2);
        fac[i] %= mod;
        inv[i] %= mod;
    }
}

ll C(int n, int k) {
    if (n < k) return 0;
    return ((fac[n] * inv[k]) % mod * inv[n-k]) % mod;
}

ll add(ll v, ll u) {
    return (v + u) % mod;
}

ll cost(ll n, ll k, ll low) {
    n = n - k * low;
    if (n < 0) return 0;
    return C(n + k - 1, n);
}

ll calc(int num, int limit) {
    ll v1 = cost(F, num, 1) * cost(W, num, limit) * 2;
    ll v2 = cost(F, num, 1) * cost(W, num + 1, limit);
    ll v3 = cost(F, num, 1) * cost(W, num - 1, limit);
    return add(add(v1, v2), v3);
}

int main() {
    init();
    scanf("%d%d%d", &F, &W, &H);
    H++;

    if (W == 0) {
        printf("1\n");
        return 0;
    }

    if (W < H) {
        printf("0\n");
        return 0;
    }

    if (W == 0) {
        printf("1\n");
        return 0;
    }

    if (F == 0) {
        printf("1\n");
        return 0;
    }

    ll ans = 0;
    for (int i = 1; i <= F; ++i) {
        ans += calc(i, H);
        ans %= mod;
    }
    
    ans = ans + mod;
    ans %= mod;
    // total way = 
    // v1 = C(F - 1, F - num) * C(W - 1, W - num) * 2;
    // v2 = C(F - 1, F - num) * C(W - 1, W - num + 1);
    // v3 = C(F - 1, F - num) * C(W - 1, W - num - 1);
    // C(F-1, F - num) * (C(w-1, w-num) * 2 + c(W-1,w-num+1) + c(w-1,w-num-1))
    // C(F-1, F - num) * ((C(w-1, w-num) + c(W-1,w-num+1)) + (c(w-1,w-num-1) + C(w-1, w-num)))
    // C(F-1, F - num) * (C(W, W-num+1) + C(W, W-num))
    // C(F-1, F - i) * C(W + 1, i) i = 1..F = C(W + F, W)
    ans = ans * fastpower(C(W + F, W), mod - 2);
    ans = ans % mod;
    printf("%I64d\n", ans);
    return 0;
}