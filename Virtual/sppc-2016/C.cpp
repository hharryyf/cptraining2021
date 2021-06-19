#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma") 
#include <bits/stdc++.h>
#define MAX_SIZE 1000011
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
            result[i] = round(fa[i].real());
            // if (result[i] != 0) result[i] = 1;
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

int N, P;
char s[MAX_SIZE];
int score[MAX_SIZE];

void solve(char ch) {
    vector<int> vc1(N), vc2(N * 2 - 1);
    for (int i = 0 ; i < N; ++i) {
        vc1[i] = (s[i] == ch ? 1 : 0);
    }

    for (int i = 0 ; i < N * 2 - 1; ++i) {
        vc2[i] = (s[i%N] == ch ? 1 : 0);
    }

    reverse(vc1.begin(), vc1.end());

    vector<int> ret = ft.multiply(vc1, vc2);

   /* printf("solve for %c\n", ch);
    for (auto v : ret) {
        printf("%d ", v);
    }
    printf("\n");
    */
    for (int i = N; i < 2 * N - 1; ++i) {
        score[i - (N - 1)] += ret[i];
    }
}

vector<pair<int, int>> ans;

int main() {
    scanf("%d%d", &N, &P);
    scanf("%s", s);
    solve('R');
    solve('Y');
    solve('B');
    for (int i = 1; i < N; ++i) {
        ans.emplace_back(N - score[i], i);
        // printf("%d %d\n", score[i], i);
    }    

    sort(ans.begin(), ans.end());
    int ret = ans[P-1].second;
    for (int i = 0; i < N - 1; ++i) {
        if (ans[i].first == ans[P-1].first) {
            ret = min(ret, ans[i].second);
        }
    }
    printf("%d\n", ret);
    return 0;
}