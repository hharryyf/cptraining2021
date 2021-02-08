#include <bits/stdc++.h>
#define MAX_SIZE 503
typedef long long ll;
using namespace std;

ll a[MAX_SIZE];
int N;

int main() {
    int i, j, k;
    ll ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%I64d", &a[i]);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            for (k = 1; k <= N; ++k) {
                ans = max(ans, a[i] | a[j] | a[k]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}