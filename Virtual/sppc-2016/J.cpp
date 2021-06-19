#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

const int inf = 3e7;
int dp1[MAX_SIZE][3], dp2[MAX_SIZE][3], a[MAX_SIZE], N;

int main() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < 3; ++j) {
            dp1[i][j] = dp2[i][j] = inf;
            dp2[i][j] *= -1;
        }
    }

    dp1[1][1] = dp2[1][1] = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 2; i <= N; ++i) {
        if (a[i] - a[i-1] <= 1000) {
            if (i == N || a[i+1] - a[i] > 1000) {
                dp1[i][0] = min(dp1[i-1][2], dp1[i-1][1] + 1);
            }
            // dp1[i][1] = dp1[i-1][0];
            dp1[i][2] = dp1[i-1][1];
            if (i == N || a[i+1] - a[i] > 1000) {
                dp2[i][0] = max(dp2[i-1][2], dp2[i-1][1] + 1);
            }
            // dp2[i][1] = dp2[i-1][0];
            dp2[i][2] = dp2[i-1][1];
        } else if (a[i] - a[i-1] >= 2000) {
            dp1[i][1] = dp1[i-1][0];
            dp2[i][1] = dp2[i-1][0]; 
        } else {
            dp1[i][0] = min(dp1[i-1][2], dp1[i-1][1] + 1);
            dp1[i][1] = dp1[i-1][0];
            dp1[i][2] = dp1[i-1][1];
            dp2[i][0] = max(dp2[i-1][2], dp2[i-1][1] + 1);
            dp2[i][1] = dp2[i-1][0];
            dp2[i][2] = dp2[i-1][1];
        }
    }

    if (dp2[N][0] < 0 || dp1[N][0] >= inf) {
        printf("Impossible\n");
        return 0;
    }

    if (dp1[N][0] == dp2[N][0]) {
        printf("Cars without trailers: %d\n", dp1[N][0]);
        printf("Cars with trailers: %d\n", (N - dp1[N][0] * 2) / 3);
    } else {
        printf("Ambiguous\n");
    }
    return 0;
}