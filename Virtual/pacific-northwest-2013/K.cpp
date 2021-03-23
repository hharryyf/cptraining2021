#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 50111
using namespace std;
typedef long long ll;

struct rolling_hash {
    ll val[MAX_SIZE];
    ll ep[MAX_SIZE];
    ll mod = 1e9 + 9;
    int base = 47;
    int N;
    void init(int base=47, ll mod=1e9+9) {
        int i;
        this->base = base, this->mod = mod;
        ep[0] = 1;
        for (i = 1; i < MAX_SIZE; ++i) {
            ep[i] = ep[i-1] * base;
            ep[i] %= mod; 
        }
    }

    void calc(char st[], int N) {
        this->N = N;
        for (int i = 1 ; i <= N; ++i) {
            int v = st[i] - 'A' + 1;
            if (st[i] == '(') v = 27;
            if (st[i] == ')') v = 28;
            val[i] = val[i-1] * base + v;
            val[i] %= mod;
        }
    }

    ll decode(int l, int r) {
        ll valL = val[l-1] * ep[r - l + 1];
        ll valR = val[r];
        return ((valR - valL) % mod + mod) % mod;
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        return decode(l1, r1) == decode(l2, r2);
    }
};

rolling_hash h[2][2];
char ss[MAX_SIZE], tt[MAX_SIZE];
int sz[MAX_SIZE];
vector<char> s[2];
vector<int> g[2][MAX_SIZE];
int L[2][MAX_SIZE], R[2][MAX_SIZE];
int N, M;

void init() {
    int i;
    memset(ss, 0, sizeof(char));
    memset(tt, 0, sizeof(char));
    for (i = 0 ; i < MAX_SIZE; ++i) {
        g[0][i].clear();
        g[1][i].clear();
        s[0].clear();
        s[1].clear();
        sz[i] = 0;
    }
}

char tp[2][MAX_SIZE], sp[4];

void dfs(int dim, int v) {
    s[dim].push_back('(');
    L[dim][v] = (int) s[dim].size();
    s[dim].push_back(tp[dim][v]);
    if (!dim) sz[v] = 1;
    for (auto nv : g[dim][v]) {
        dfs(dim, nv);
        if (!dim) sz[v] += sz[nv];
    }
    s[dim].push_back(')');
    R[dim][v] = (int) s[dim].size();
}

int main() {
    h[0][0].init();
    h[0][1].init(53, 19260817);
    h[1][0].init();
    h[1][1].init(53, 19260817);
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        scanf("%d%d", &N, &M);
        for (j = 0 ; j < 2; ++j) {
            for (i = 1; i <= (j == 0 ? N : M); ++i) {
                int v;
                scanf("%s%d", sp, &v);
                tp[j][i] = sp[0];
                if (v != -1) g[j][v+1].push_back(i);
            }

            dfs(j, 1);
        }

        for (j = 0 ; j < 2; ++j) {
            for (i = 0 ; i < (int) s[j].size(); ++i) {
                tp[j][i+1] = s[j][i];
            }

            h[j][0].calc(tp[j], s[j].size());
            h[j][1].calc(tp[j], s[j].size());
        }

        map<pair<ll, ll>, int> mp;
        for (i = 1; i <= N; ++i) {
            mp[make_pair(h[0][0].decode(L[0][i], R[0][i]), h[0][1].decode(L[0][i], R[0][i]))] = sz[i];
        }

        int ans = 0;
        for (i = 1; i <= M; ++i) {
            ans = max(ans, mp[make_pair(h[1][0].decode(L[1][i], R[1][i]), h[1][1].decode(L[1][i], R[1][i]))]);
        }

        printf("%d\n", ans);
    }
    return 0;
}
