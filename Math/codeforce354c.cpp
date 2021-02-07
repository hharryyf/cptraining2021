#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1000011

struct ST {
    int a[MAX_SIZE];
    int table[20][MAX_SIZE];
    int logs[MAX_SIZE];
    int n;

    void precompute() {
        int i;
        for (i = 2; i < MAX_SIZE; i++) {
            logs[i] = logs[i/2] + 1;
        }
    }

    int RMQ(int l, int r) {
        if (l > r) return -1;
        int len = r - l + 1;
        return max(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
    }

    void build() {
        int i, j;
        precompute();
        for (i = 1; i <= n; i++) {
            table[0][i] = a[i];
        }
        
        for (i = 1; i <= 19; i++) {
            int prel = (1 << (i - 1));
            for (j = 1; j <= n; j++) {
                if (j + prel <= n) {
                    table[i][j] = max(table[i-1][j], table[i-1][j+prel]);
                } else {
                    table[i][j] = table[i-1][j];
                }
            }
        }
    }
};

ST s;

int main() {
    int N, K, i, j, ans = 1;
    scanf("%d%d", &N, &K);
    s.n = 1000000;
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        s.a[v] = v;
    }

    for (i = 1; i <= s.n; ++i) {
        if (s.a[i] == 0) s.a[i] = -1;
    }

    s.build();
    for (i = 1; i <= s.n; ++i) {
        if (s.RMQ(1, i - 1) != -1) continue;
        int ok = 1;
        for (j = 1; j * i <= s.n ; ++j) {
            int v = s.RMQ(j * i, min((j + 1) * i - 1, s.n));
            if (v == -1) continue;
            if (v - j * i > K) {
                ok = 0;
                break;
            }
        }

        if (ok) {
            ans = max(ans, i);
        }
    }

    printf("%d\n", ans);
    return 0;
}