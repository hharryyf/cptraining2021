#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, ans = 10000, i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        ans = min(ans, y / x);
    }
    printf("%d\n", ans);
    return 0;
}