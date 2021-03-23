#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
using namespace std;
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
                x /= n;
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
            result[i] = floor(fa[i].real() + 0.5);
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

int Nu, Nm, Nl;
const int shift = 30001;
int main() {
    int i;
    vector<int> a(65536), c(65536);
    scanf("%d", &Nu);
    for (i = 0 ; i < Nu; ++i) {
        int v;
        scanf("%d", &v);
        a[v + shift]++;
    }

    scanf("%d", &Nm);
    vector<int> b(Nm);
    for (i = 0 ; i < Nm; ++i) scanf("%d", &b[i]);
    scanf("%d", &Nl);
    for (i = 0 ; i < Nl; ++i) {
        int v;
        scanf("%d", &v);
        c[v + shift]++;
    }

    auto ret = ft.multiply(a, c);
    long long ans = 0;
    for (i = 0 ; i < Nm; ++i) {
        if (2 * b[i] + 2 * shift >= 0 && 2 * b[i] + 2 * shift < (int) ret.size()) {
            ans = ans + ret[2 * b[i] + 2 * shift];
        }
    }

    cout << ans << endl;
    return 0;
}