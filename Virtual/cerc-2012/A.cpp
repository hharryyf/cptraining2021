#include <bits/stdc++.h>
#define MAX_SIZE 1048597
using namespace std;

int visited[MAX_SIZE];
int money[22][22];
int N;
int T;

void init() {
    int i, j;
    scanf("%d", &N);
    for (i = 0 ; i < (1 << N); ++i) visited[i] = 0;
    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < N; ++j) {
            scanf("%d", &money[i][j]);
        }
    }
}

int isstable(int v) {
    int i, j, ret = 0;
    for (i = 0 ; i < N; ++i) {
        if (v & (1 << i)) {
            int tol = 0;
            for (j = 0 ; j < N; ++j) {
                if (v & (1 << j)) {
                    tol += money[i][j];
                }
            }

            if (tol > 0) ret |= (1 << i);
        }
    }
    return ret;
}

void dfs(int v) {
    visited[v] |= 1;
    int mask = isstable(v), i;
    if (mask == 0) {
        visited[v] = 2;
        if (__builtin_popcount(v) == 1) {
            visited[v] = 3;
        }
        return;
    }

    for (i = 0 ; i < N; ++i) {
        if (mask & (1 << i)) {
            if (visited[v ^ (1 << i)] != 0) continue;
            dfs(v ^ (1 << i));
        }
    }
}

int main() {
    int i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        init();  
        dfs((1 << N) - 1);
        int ans = 0;
        for (i = 0; i < (1 << N); ++i) {
            if (visited[i] == 3) {
                for (j = 0 ; j < N; ++j) {
                    if (i & (1 << j)) {
                        ans |= (1 << j);
                    }
                }
            }
        }

        if (ans == 0) {
            printf("0\n");
            continue;
        }

        int flag = 0;
        for (i = 0 ; i < N; ++i) {
            if (ans & (1 << i)) {
                if (flag) {
                    printf(" %d", i + 1);
                } else {
                    printf("%d", i + 1);
                }
                flag = 1;
            } 
        }
        printf("\n");
    }
    return 0;
}