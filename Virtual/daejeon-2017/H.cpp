#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 400011
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
int N, M;
char s[MAX_SIZE], t[MAX_SIZE];
int score[MAX_SIZE];

void solve(char c1, char c2) {
    vector<int> v1(N);
    vector<int> v2(M);
    for (int i = 0 ; i < N; ++i) {
        if (s[i] == c1) v1[i] = 1;
    }

    for (int i = 0 ; i < M; ++i) {
        if (t[i] == c2) v2[i] = 1;
    }

    reverse(v2.begin(), v2.end());
    auto vc = ft.multiply(v1, v2);
    //printf("matching %c %c\n", c1, c2);
    for (int i = 0 ; i < (int) vc.size(); ++i) {
        score[i] += vc[i];
        //printf("%d ", vc[i]);
    }
    //printf("\n");
}

int main() {
    int i;
    scanf("%d%d", &N, &M);
    scanf("%s", s);
    scanf("%s", t);
    solve('S', 'R');
    solve('R', 'P');
    solve('P', 'S');
    int ans = 0;
    for (i = M - 1; i < MAX_SIZE; ++i) {
        ans = max(ans, score[i]);
        // printf("%d ", score[i]);
    }
    //printf("\n");
    printf("%d\n", ans);
    return 0;
}