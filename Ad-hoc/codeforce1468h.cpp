#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(int n, int k, int m) {
    vector<int> a = vector<int>(n, 1);
    int sz = (k - 1) / 2;

    for (int i = 0; i < m; ++i) {
        int v;
        scanf("%d", &v);
        a[v-1] = 0;
    }

     if ((n - m) % sz != 0) {
        printf("NO\n");
        return;
    }

    if (((n - m) / sz) % 2 != 0) {
        printf("NO\n");
        return;
    }

    int l = 0, r = 0, cnt = 0;
    for (int i = 0 ; i < n && cnt < sz; ++i) {
        cnt += a[i];
        l = i + 1;
    }

    cnt = 0;
    for (int i = n - 1; i >= 0 && cnt < sz; --i) {
        cnt += a[i];
        r = i - 1;
    }

    // cout << l << " " << r << endl;
    for (int i = l; i <= r; ++i) {
        if (a[i] == 0) {
            printf("YES\n");
            return;
        }
    }

    printf("NO\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, k, m;
        scanf("%d%d%d", &n, &k, &m);
        solve(n, k, m);
    }
    return 0;
}