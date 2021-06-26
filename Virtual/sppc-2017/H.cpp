#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;
const ll inf = 1e9 + 1;
char s[MAX_SIZE];
ll dp[MAX_SIZE];

int main() {
    int N, i, j;
    scanf("%s", s + 1);
    N = strlen(s + 1);
    for (i = 1; i <= N; ++i) {
        dp[i] = inf;
    }
    for (i = 1; i <= N; ++i) {
        for (j = max(i - 10, 1); j <= i; ++j) {
            // [j, i] + dp[j-1]
            string ss = "";
            for (int k = j; k <= i; ++k) {
                ss += s[k];
            }
            if (ss[0] == '0') continue;
            ll num = atoll(ss.c_str());
            ll sq = sqrt(num);
            if (sq * sq == num) {
                dp[i] = min(dp[i], dp[j-1] + num);
            }
        }
    }

    if (dp[N] == inf) {
        printf("-1\n");
    } else {
        printf("%lld\n", dp[N]);
    }
    return 0;
}