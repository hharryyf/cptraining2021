#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;
typedef long long ll;

const ll inf = 1e14;
ll dist[2][MAX_SIZE][MAX_SIZE];
int N;

void init(int arg) {
    int i, j;
    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < N; ++j) {
            if (arg == 0) {
                dist[0][i][j] = dist[1][i][j] = inf;
            } else {
                dist[1][i][j] = inf;
            }
        }
        dist[0][i][i] = dist[1][i][i] = 0;
    }
}

void addedge(int dim, int from, int to, ll w) {
    dist[dim][from][to] = min(dist[dim][from][to], w);
    dist[dim][to][from] = min(dist[dim][to][from], w);
}


void floyd(int dim) {
    int i, j, k;
    for (k = 0; k < N; ++k) {
        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                dist[dim][i][j] = min(dist[dim][i][j], dist[dim][i][k] + dist[dim][k][j]);
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j, K, M;
        scanf("%d%d%d", &N, &K, &M);
        init(0);
        for (i = 0 ; i < M; ++i) {
            int u, v;
            ll c;
            scanf("%d%d%I64d", &u, &v, &c);
            addedge(0, u, v, c);
        }

        floyd(0);

        ll low = 0, high = 1e12, ans = 1e12;
        while (low <= high) {
            ll mid = (low + high) / 2;
            init(1);
            for (i = 0 ; i < N; ++i) {
                for (j = 0 ; j < N; ++j) {
                    if (dist[0][i][j] <= mid) {
                        addedge(1, i, j, 1);
                    }
                }
            }

            floyd(1);
            bool valid = true;
            for (i = 0 ; i < N; ++i) {
                for (j = 0 ; j < N; ++j) {
                    if (dist[1][i][j] > K) {
                        valid = false;
                        break; 
                    }
                }

                if (!valid) break;
            }

            if (valid) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        printf("%I64d\n", ans);
    }
    return 0;
}