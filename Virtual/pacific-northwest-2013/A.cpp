#include <bits/stdc++.h>

using namespace std;



int main() {
    int T, N, D;
    scanf("%d", &T);
    while (T-- > 0) {
        int ans = 0;
        scanf("%d%d", &N, &D);
        for (int i = 0 ; i < N; ++i) {
            int v, f, c;
            scanf("%d%d%d", &v, &f, &c);
            if (D * c <= f * v) ans++;
        }

        printf("%d\n", ans);
    }
    return 0;
}