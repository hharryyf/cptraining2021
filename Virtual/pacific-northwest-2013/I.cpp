#include <bits/stdc++.h>
#define MAX_SIZE 4011
using namespace std;

int a[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        int mn = a[1], mx = a[1];
        for (i = 1; i <= N; ++i) {
            mn = min(a[i], mn);
            mx = max(a[i], mx);
        }

        int mid = (mn + mx) / 2;
        int mxL = mn, mnR = mx;
        for (i = 1; i <= N; ++i) {
            if (a[i] <= mid) mxL = max(a[i], mxL);
            if (a[i] >= mid) mnR = min(mnR, a[i]);
        }

        printf("%d\n", max(mx - mnR, mxL - mn));
    }
    return 0;
}