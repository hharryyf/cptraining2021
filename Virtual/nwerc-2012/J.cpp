#include <bits/stdc++.h>

using namespace std;


int main() {
    int x, N, i;
    while (scanf("%d", &x) != EOF) {
        scanf("%d", &N);
        x *= 10000000;
        map<int, int> s;
        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            s[v]++;
        }
        
        int x1 = -1, x2 = -1;
        for (auto vp : s) {
            int v = vp.first;
            if (v * 2 != x) {
                if (s.find(x - v) != s.end()) {
                    if (abs(x1 - x2) <= abs(x - v - v)) {
                        x1 = x - v;
                        x2 = v;
                    }
                }
            } else {
                if (s[v] > 1 && x1 == -1) {
                    x1 = v, x2 = v;
                }
            }
        }

        if (x1 > x2) swap(x1, x2);
        if (x1 == -1) {
            printf("danger\n");
        } else {
            printf("yes %d %d\n", x1, x2);
        }
    }
    return 0;
}