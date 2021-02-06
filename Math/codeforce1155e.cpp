#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int INF = 2; // it doesn't actually have to be infinity or a big number
const ll mod = 1e6 + 3;
ll fastpower(ll v, ll p) {
    ll ret = 1;
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

int gauss (vector<vector<ll>> a, vector<ll> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                ll c = (a[i][col] * fastpower(a[row][col], mod - 2)) % mod;
                for (int j=col; j<=m; ++j) {
                    a[i][j] -= a[row][j] * c;
                    a[i][j] %= mod;
                    if (a[i][j] < 0) a[i][j] += mod;
                }
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m] * fastpower(a[where[i]][i], mod - 2);
            ans[i] %= mod;
            if (ans[i] < 0) ans[i] += mod;
        }
    }
    for (int i=0; i<n; ++i) {
        ll sum = 0;
        for (int j=0; j<m; ++j) {
            sum += ans[j] * a[i][j];
            sum %= mod;
            if (sum < 0) sum += mod;
        }
        if (abs(sum - a[i][m]) > 0)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

int main() {
    int i, j;
    vector<vector<ll>> a = vector<vector<ll>>(11, vector<ll>(12, 0));
    for (i = 0 ; i < 11; ++i) {
        printf("? %d\n", i);
        fflush(stdout);
        for (j = 0; j <= 10; ++j) {
            a[i][j] = fastpower(i, j);
        }
        scanf("%I64d", &a[i][11]);
    }

    vector<ll> ans(11);
    gauss(a, ans);
    for (i = 0 ; i < mod; ++i) {
        ll curr = 0;
        for (j = 0 ; j < 11; ++j) {
            curr = curr + fastpower(i, j) * ans[j];
            curr %= mod;
            if (curr < 0) curr += mod;
        }

        if (curr == 0) {
            printf("! %d\n", i);
            fflush(stdout);
            return 0;
        }
    }

    printf("! -1\n");
    fflush(stdout);
    return 0;
}