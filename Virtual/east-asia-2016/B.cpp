#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

int bad[2], ans[MAX_SIZE];

int len(int l, int r) {
    return r - l + 1;
}

int oddlen(int l, int r) {
    return ((len(l, r) & 1) && (r & 1)) ? (len(l, r) / 2 + 1) : (len(l, r) / 2); 
}

int evenlen(int l, int r) {
    return len(l, r) - oddlen(l, r);
}

ll calc(int odd, int even, int oddeven) {
    if (odd >= 62 || even >= 62) return 1ll << 62;
    return (odd < 0 ? 0 : 1ll << odd) + (even < 0 ? 0 : 1ll << even) - (oddeven < 0 ? 0 : 1ll << oddeven);
}

void solve() {
    bad[0] = bad[1] = 0;
    int i, mid, N;
    ll K;
    scanf("%d%I64d", &N, &K);
    mid = (N + 1) / 2;
    // aim is to make sure both odd/even case we can fill the first half
    if (N % 4 == 2) mid++;
    for (i = 1; i <= N; ++i) {
        if (i <= mid) {
            ans[i] = 0;
            int odd = len(i + 1, mid) + evenlen(mid + 1, N);
            int even = len(i + 1, mid) + oddlen(mid + 1, N);
            int oddeven = len(i + 1, mid);
            ll tol = calc(odd, even, oddeven);
            if (tol < K) {
                ans[i] = 1;
                K -= tol;
            }
        } else {
            // the position of the opposite bit
            int rev = N & 1? N - i + 1 : (i & 1 ? N - i : N - i + 2);
            ans[i] = 0;
            if (ans[i] != ans[rev]) bad[i & 1]++;
            int freeodd = bad[0] ? -1 : oddlen(i + 1, N);
            int freeeven = bad[1] ? -1 : evenlen(i + 1, N);
            int del = bad[0] || bad[1] ? -1 : 0;
            ll tol = calc(freeodd, freeeven, del);
            if (tol < K) {
                if (ans[i] != ans[rev]) bad[i & 1]--;
                ans[i] = 1;
                K -= tol;
                if (ans[i] != ans[rev]) bad[i & 1]++;
            }
        }
    }

    if (K == 1) {
        for (i = 1; i <= N; ++i) {
            printf("%d", ans[i]);
        }
        printf("\n");
    } else {
        printf("NOT FOUND!\n");
    }
}


int main() {
    int t, T;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t) {  
        printf("Case #%d: ", t);     
        solve();
    }
    return 0;
}