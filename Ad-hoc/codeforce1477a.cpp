#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 200011
ll a[MAX_SIZE], K;

int main() {
    int i, T, N;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%I64d", &N, &K);
        for (i = 0 ; i < N; ++i) scanf("%I64d", &a[i]);
        sort(a, a + N);
        ll g = 0;
        for (i = 0 ; i < N - 1; ++i) {
            g = __gcd(g, a[i+1] - a[i]);
        }

        ll diff = llabs(K - a[0]);
        if (diff % g == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}