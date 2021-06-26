#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 262192
#define MAXLOG 19

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

struct BIT {
    int tree[MAX_SIZE];
    int N;
    void init() {
        memset(tree, 0, sizeof(tree));
        N = 0;
    }

    int shift(int x) {
        return x & (-x);
    }

    void update(int index, int val) {
        if (index <= 0) return;
        while (index <= N) {
            tree[index] += val;
            index += shift(index);
        }  
    }

    int getsum(int index) {
        int ret = 0;
        while (index > 0) {
            ret = ret + tree[index];
            index -= shift(index);
        }
        return ret;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return getsum(r) - getsum(l-1);
    }
};

BIT t;
SA sa;
typedef long long ll;
char s[MAX_SIZE];
int a[MAX_SIZE];
ll par[MAX_SIZE];
ll toxic[MAX_SIZE];
int N;

int main() {
    int i;
    scanf("%s", s);
    N = strlen(s);
    string curr(s);
    curr += '$';
    sa.sort_cyclic_shifts(curr);
    for (i = 0; i < N; ++i) {
        a[i] = sa.rank[i];
    }
    ll cnt = 0;
    int idx = -1;
    t.N = MAX_SIZE - 1;
    for (i = N - 1; i >= 0; --i) {
        cnt += t.query(1, a[i] - 1);
        t.update(a[i], 1);
        toxic[i] = cnt;
        par[i] = N - i;
        par[i] = par[i] * (par[i] - 1);
        toxic[i] = par[i] / 2 - toxic[i] + 1;
        if (toxic[i] > 100000000) break;
        if (idx == -1) {
            idx = i;
        } else if (toxic[idx] * par[i] >= toxic[i] * par[idx]) {
            idx = i;
        }

        // cout << toxic[i] << " " << par[i] << endl;
    }

    printf("%d\n", N - idx);
    return 0;
}