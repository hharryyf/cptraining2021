#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
typedef int ll;
using namespace std;
#define MAX_SIZE 200011
const ll mod = 1009;
int f[MAX_SIZE];
using cd = complex<double>;
const double PI = acos(-1);

struct FFT {
    void fft(vector<cd> & a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (cd & x : a)
                x /= (cd) n;
        }
    }

    vector<int> multiply(vector<int> const& a, vector<int> const& b) {
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < (int) a.size() + (int) b.size()) 
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = (long long) (fa[i].real() + 0.5) % mod;
        }
        return result;
    }

    vector<int> pw(vector<int> const &a, int p) {
        vector<int> ret(a.size());
        vector<int> base(a.begin(), a.end());
        ret[0] = 1;
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

FFT ft;
int cnt[MAX_SIZE];
vector<int> poly[MAX_SIZE];
struct node {
    int sz, id;
    node(int id, int sz) {
        this->id = id;
        this->sz = sz;
    }

    bool operator < (node other) const {
        return sz > other.sz;
    }
};

priority_queue<node> q;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int main() {
    int i, N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    for (i = 0 ; i < N; ++i) {
        int v;
        scanf("%d", &v);
        cnt[v]++;
    }

    for (i = 1; i <= M; ++i) {
        poly[i] = vector<int>(cnt[i] + 1, 1);
        q.push(node(i, cnt[i] + 1));
    }

    while ((int) q.size() >= 2) {
        auto v1 = q.top();
        q.pop();
        auto v2 = q.top();
        q.pop();
        int a = find(v1.id), b = find(v2.id);
        f[a] = b;
        poly[b] = ft.multiply(poly[b], poly[a]);
        poly[a].clear();
        q.push(node(b, (int) poly[b].size()));
    }

    int v = q.top().id;
    printf("%d\n", poly[find(v)][K]);
    return 0;
}