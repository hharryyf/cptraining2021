#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 200011
int N;
ll h[MAX_SIZE], backward[MAX_SIZE], val[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &h[i]);
        backward[i] = h[i];
    }

    val[N] = h[N];
    for (i = N - 1; i >= 1; --i) {
        backward[i] = 1ll * (backward[i+1] / h[i]) * h[i];
        if (backward[i] < backward[i+1]) backward[i] += h[i];
        val[i] = val[i+1] + backward[i]; 
    }

    ll ans = val[1], curr = h[1], currh = h[1];
    for (i = 2; i <= N; ++i) {
        ans = min(ans, curr + val[i]);
        if (currh > h[i]) {
            ll nxt = currh / h[i] * h[i];
            if (currh > nxt) nxt += h[i];
            currh = nxt;
        } else {
            currh = h[i];
        }
        curr += currh;
    }
    ans = min(ans, curr);
    printf("%lld\n", ans);
    return 0;
}