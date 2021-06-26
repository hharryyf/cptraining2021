#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int i, w = n, b = 0, r = 0;
    for (i = 1; i <= n; ++i) {
        ll t1 = n - i; // t1 is n - b
        ll t2 = sqrt(1ll * n * n - t1 * t1); // t2 is n - w
        if (t2 * t2 == 1ll * n * n - t1 * t1) {
            int rp = t2 - i;
            if (rp > r) {
                b = i;
                w = n - t2;
                r = t2 - i;
            }
        }
    }
    printf("2\n");
    cout << b << " " << w << endl;
    return 0;
}