#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

int dp[MAX_SIZE][21];
int pre[MAX_SIZE];
int N, K;

int cost(int l, int r) {
    int ret = pre[r] - pre[l-1];
    if (ret % 10 >= 5) {
        ret = (ret / 10 + 1) * 10;
    } else {
        ret = ret / 10 * 10;
    }
    return ret;
}

int main() {
    int i, j, k;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &pre[i]);
        pre[i] += pre[i-1];
        for (j = 1; j <= K; ++j) {
            dp[i][j] = 1000000000;
        }
    }

    for (i = 1; i <= N; ++i) {
        dp[i][0] = cost(1, i);
        for (j = 1; j <= K; ++j) {
            dp[i][j] = min(dp[i][j], dp[i][j-1]);
            for (k = 1; k < i; ++k) {
                dp[i][j] = min(dp[i][j], dp[k][j-1] + cost(k+1,i));
            } 
        }
    }

    printf("%d\n", dp[N][K]);
    return 0;
}