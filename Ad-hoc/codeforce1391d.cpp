#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

char s[MAX_SIZE];
int dp[MAX_SIZE][8];
int cost[8], ok[8][8];
int N, M;
const int inf = 1e7;
vector<vector<char>> vc;

bool check(int v, int u) {
    vector<vector<int>> a = vector<vector<int>>(2, vector<int>(N, 0));
    int i;
    for (i = 0 ; i < N; ++i) {
        a[0][i] = (v >> i) & 1;
    }

    for (i = 0 ; i < N; ++i) {
        a[1][i] = (u >> i) & 1;
    }

    for (i = 0 ; i < N - 1; ++i) {
        if ((a[0][i] + a[0][i+1] + a[1][i] + a[1][i+1]) % 2 == 0) return false;
    }
    return true;
}

int main() {
    int i, j, k;
    scanf("%d%d", &N, &M);
    if (min(N, M) > 3) {
        printf("-1\n");
        return 0;
    }

    if (min(N, M) == 1) {
        printf("0\n");
        return 0;
    }

    if (N > M) {
        vc = vector<vector<char>>(M, vector<char>(N, '0'));
        for (i = 0 ; i < N; ++i) {
            scanf("%s", s);
            for (j = 0 ; j < M; ++j) {
                vc[j][i] = s[j];
            }
        }
        swap(N, M);
    } else {
        vc = vector<vector<char>>(N, vector<char>(M, '0'));
        for (i = 0 ; i < N; ++i) {
            scanf("%s", s);
            for (j = 0 ; j < M; ++j) {
                vc[i][j] = s[j];
            }
        }
    } 

    for (j = 0; j < M; ++j) {
        for (i = 0; i < (1 << N); ++i) {
            dp[j][i] = inf;
        }
    }

    for (i = 0 ; i < (1 << N); ++i) {
        for (j = 0 ; j < (1 << N); ++j) {
            ok[i][j] = check(i, j);
//            cout << ok[i][j] << " ";
        }
//        cout << endl;
    }

    for (j = 0 ; j < (1 << N); ++j) {
        dp[0][j] = 0;
        for (k = 0 ; k < N; ++k) {
            if (vc[k][0] != ((j >> k) & 1) + '0') {
                dp[0][j]++;
            }
        }
      //  printf("%d ", dp[0][j]);
    }
    //cout << endl;
    for (i = 0; i < M - 1; ++i) {
        // col (i + 1)
        for (j = 0 ; j < (1 << N); ++j) {
            cost[j] = 0;
            for (k = 0 ; k < N; ++k) {
                if (vc[k][i+1] != ((j >> k) & 1) + '0') {
                    cost[j]++;
                }
            }
        }

        for (j = 0 ; j < (1 << N); ++j) {
            for (k = 0; k < (1 << N); ++k) {
                if (ok[j][k]) {
                    dp[i+1][k] = min(dp[i+1][k], dp[i][j] + cost[k]);
                }
            }
        }
    }

    int ans = inf;
    for (i = 0 ; i < (1 << N); ++i) {
        ans = min(ans, dp[M - 1][i]);
    }

    printf("%d\n", (ans < inf) ? ans : -1);
    return 0;
}