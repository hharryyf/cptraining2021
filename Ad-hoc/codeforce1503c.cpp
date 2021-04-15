#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 200011
int N;
pair<ll,ll> a[MAX_SIZE];

int main() {
    int i;
    ll ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%I64d%I64d", &a[i].first, &a[i].second);
        ans += a[i].second;
        a[i].second += a[i].first;
    }

    sort(a + 1, a + 1 + N);
    ll curr = a[1].second;
    for (i = 2; i <= N; ++i) {
        if (a[i].first > curr) {
            ans = ans + a[i].first - curr;
            curr = a[i].second;
        }
        curr = max(curr, a[i].second);
    }

    printf("%I64d\n", ans);
    return 0;
}