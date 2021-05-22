#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define MAX_SIZE 400111
#define MAXLOG 19
typedef long long ll;
using namespace std;

struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
    const int alphabet = (MAX_SIZE >> 1);
    int n;
    
    void init() {
        memset(p, 0, sizeof(p));
        memset(cnt, 0, sizeof(cnt));
        memset(c, 0, sizeof(c));
        memset(rank, 0, sizeof(rank));
    }

    void sort_cyclic_shifts(string &s) {
        int h, i;
        n = (int) s.size();    
        for (i = 2; i < MAX_SIZE; ++i) logs[i] = logs[i/2]+1;
        for (i = 0; i < n; i++)
            cnt[(int) s[i]]++;
        for (i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (i = 0; i < n; i++)
            p[--cnt[(int) s[i]]] = i;
        c[0][p[0]] = 0;
        int classes = 1;
        for (i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[0][p[i]] = classes - 1;
        }

        vector<int> pn(n), cn(n);
        for (h = 0; (1 << h) < n; ++h) {
            for (i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt, cnt + classes, 0);
            for (i = 0; i < n; i++)
                cnt[c[h][pn[i]]]++;
            for (i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (i = n-1; i >= 0; i--)
                p[--cnt[c[h][pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (i = 1; i < n; i++) {
                pair<int, int> cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[h][p[i-1]], c[h][(p[i-1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            
            for (i = 0 ; i < n; ++i) {
                c[h+1][i] = cn[i];
            }
        }

        for (i = 0 ; i < n; ++i) rank[p[i]] = i;
    }

    int lcp(int i, int j) {
        int ans = 0, k;
        for (k = logs[n]; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
};

SA sa;
char s[MAX_SIZE];


int main() {
    int i, N;
    scanf("%s", s);
    N = strlen(s);
    string st(s);
    st += '$';
    sa.sort_cyclic_shifts(st);
    int low = 1, high = N, ans = N;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cnt = 0;
        for (i = 1; i <= N; ++i) {
            bool ok = false;
            if (i > 1) {
                if (sa.lcp(sa.p[i], sa.p[i-1]) >= mid) ok = true; 
            }

            if (i < N) {
                if (sa.lcp(sa.p[i], sa.p[i+1]) >= mid) ok = true;
            }
            cnt += ok;
        }
        // printf("check %d cnt= %d\n", mid, cnt);
        if (cnt < N - mid + 1) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    for (i = 0; i <= N - ans; ++i) {
        if (sa.rank[i] < N) {
            if (sa.lcp(i, sa.p[sa.rank[i] + 1]) >= ans) continue;
        }

        if (sa.rank[i] > 0) {
            if (sa.lcp(i, sa.p[sa.rank[i] - 1]) >= ans) continue;
        }

        for (int j = i; j < i + ans; ++j) {
            putchar(s[j]);
        }
        break;
    }
    putchar('\n');
    return 0;
}