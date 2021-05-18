#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll query(int x, int y) {
    if (x > 1000000 || x < 0 || y < 0 || y > 1000000) return -1;
    ll d;
    printf("%d %d\n", x, y);
    fflush(stdout);
    scanf("%lld", &d);
    return d;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n-- > 0) {
        int i;
        ll d = query(1, 1);    
        for (i = 0; i <= 1000000; ++i) {
            ll x = i;
            if (1ll * (1 - x) * (1 - x) <= d) {
                ll y = sqrt(d - 1ll * (1 - x) * (1 - x));
                if (y * y == d - 1ll * (1 - x) * (1 - x)) {
                    ll t = query(x, 1 - y);
                    if (t == 0) break;
                    t = query(x, 1 + y);
                    if (t == 0) break;
                }
            }
        }
    }
    return 0;
}