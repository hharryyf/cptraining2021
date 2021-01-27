#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 998244353;

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

int generator (int p) {
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= fastpower (res, phi / fact[i]) != 1;
        if (ok)  return res;
    }
    return -1;
}

struct NTT {
    void ntt(vector<int>& P , int op){
        int len = P.size() , i , j , k;
        for (int i = 1, j = 0; i < len; i++) {
            int bit = len >> 1;
            for (; j & bit; bit >>= 1) {
                j ^= bit;
            }
            j ^= bit;

            if (i < j) {
                swap(P[i], P[j]);
            }
        }

        for(i = 1; i < len; i <<= 1){
            ll gn = fastpower(3 , (mod - 1) / (i << 1));
            if(op == -1) gn = fastpower(gn , mod - 2);
            for(j = 0; j < len; j += (i << 1)){
                ll g = 1;
                for(k = 0; k < i; ++k , g = g * gn % mod){
                    ll x = P[j + k] , y = g * P[j + k + i] % mod;
                    P[j + k] = (x + y) % mod;
                    P[j + k + i] = (x - y + mod) % mod;
                }
            }
        }

        if(op == -1){
            ll inv = fastpower(len , mod - 2);
            for(i = 0; i < len; ++i)P[i] = (1ll * P[i] * inv) % mod;
        }
    }
 
    vector<int> multiply(vector<int> const & aa , vector<int> const & bb){
        int n = aa.size() , m = bb.size(), len = 1 , i;
        while(len < n + m)len <<= 1;
        vector<int> a(len) , b(len);
        for(i = 0; i < n; ++i)a[i] = aa[i];
        for(i = 0; i < m; ++i)b[i] = bb[i];
        ntt(a , 1);
        ntt(b , 1);
        vector<int> c(len);
        for(i = 0; i < len; ++i)c[i] = (1ll * a[i] * b[i]) % mod;
        ntt(c , -1);
        while(!c.empty() && c.back() == 0)c.pop_back();
        return c;
    }

    vector<int> pw(vector<int> const &vc, int p) {
        vector<int> ret(vc.size());
        ret[0] = 1;
        vector<int> base(vc.begin(), vc.end());
        while (p > 0) {
            if (p % 2 == 1) {
                ret = multiply(ret, base);
                p--;
            } else {
                base = multiply(base, base);
                p /= 2;
            }
        }

        return ret;
    }
};

NTT ntt;

int main() {
    int N, K, i;
    vector<int> vc(10);
    scanf("%d%d", &N, &K);
    for (i = 0; i < K; ++i) {
        int v;
        scanf("%d", &v);
        vc[v] = 1;
    }

    vc = ntt.pw(vc, N / 2);
    ll ans = 0;
    for (auto v : vc) {
        ans = ans + 1ll * v * v;
        ans %= mod;
    }
    printf("%I64d\n", (ans + mod) % mod);
    return 0;
}