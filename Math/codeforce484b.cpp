#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1000011

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
    if (l > r) return 4 * MAX_SIZE;
    int len = r - l + 1;
    return max(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
}

void build() {
    int i, j;
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

int s[MAX_SIZE], vis[MAX_SIZE];

int main() {
    int i, j, N;
    precompute();
    n = 1000000;
    for (i = 1; i <= n; ++i) a[i] = -1;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &s[i]);
        a[s[i]] = s[i];
    } 

    build();
    int ans = 0;
    for (i = 1; i <= N; ++i) {
        if (vis[s[i]]) continue;
        vis[s[i]] = 1;
        if (s[i] == 1) continue;
        for (j = 1; j * s[i] <= n; ++j) {
            int q = RMQ(s[i] * j, min(s[i] * (j + 1) - 1, n));
            if (q == -1) continue;
            ans = max(ans, q - s[i] * j);
        }
    }

    printf("%d\n", ans);
    return 0;
}