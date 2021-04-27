#include <bits/stdc++.h>
#define MAX_SIZE 202
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE], t[MAX_SIZE];
ll fac[MAX_SIZE];
int visited[MAX_SIZE];
int N, K;
int lcnt = 0, rcnt = 0;
void dfs(int v) {
    visited[v] = 1;
    if (v <= K) {
        lcnt++;
    } else {
        rcnt++;
    }

    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }
    }
}

int main() {
    int i, j, k;
    fac[0] = 1;
    for (i = 1; i <= 20; ++i) fac[i] = fac[i-1] * i;
    while (scanf("%d", &K) != EOF) {
        scanf("%s", s + 1);
        scanf("%s", t + 1);
        N = strlen(s + 1);
        memset(visited, 0, sizeof(visited));
        for (i = 0 ; i < MAX_SIZE; ++i) {
            for (j = 0 ; j < MAX_SIZE; ++j) {
                a[i][j] = 1;
            }
            visited[i] = 0;
            g[i].clear();
        }

        for (i = 1; i <= N / K; ++i) {
            for (j = 1; j <= K; ++j) {
                for (k = 1; k <= K; ++k) {
                    int l = (i - 1) * K + j, r = (i - 1) * K + k;
                    if (s[l] != t[r]) {
                        a[j][k] = 0;
                    }   
                }
            }
        }
        
        bool flag = false;
        for (i = 1; i <= K; ++i) {
            for (j = 1; j <= K; ++j) {
                if (a[i][j]) {
                    g[i].push_back(K + j);
                    g[K + j].push_back(i);
                    flag = true;
                }
            }
        }
        
        if (!flag) {
            printf("0\n");
            continue;
        }

        ll ret = 1;
        for (i = 1; i <= 2 * K; ++i) {
            if (!visited[i]) {
                lcnt = rcnt = 0;
                dfs(i);
                ret = ret * fac[lcnt];
                if (lcnt != rcnt) ret = 0;
            }
        }

        printf("%lld\n", ret);
    }
    return 0;
}