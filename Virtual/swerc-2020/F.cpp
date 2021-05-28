#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 2031
using namespace std;

ll c[MAX_SIZE][MAX_SIZE], c2[MAX_SIZE][MAX_SIZE], ans[MAX_SIZE], tree[MAX_SIZE];
int R, N;
ll mod;

int main() {
    int i, j;
    cin >> R >> N >> mod;
    // instead of max heap we build a min heap
    R = N + 1 - R;
    for (i = 0; i <= N; ++i) {
        c[i][0] = 1 % mod;
        c2[i][0] = 1 % (2 * mod);
    }
    // compute the comb numbers
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= i; ++j) {
            c[i][j] = c[i-1][j] + c[i-1][j-1];
            c2[i][j] = c2[i-1][j] + c2[i-1][j-1];
            c[i][j] %= mod;
            c2[i][j] %= (2 * mod);
        }
    }

    tree[0] = tree[1] = 1 % mod;
    for (i = 2; i <= N; ++i) {
        for (j = 0; j <= (i - 1) / 2; ++j) {
            ll curr = 0;
            if (j * 2 == i - 1 && j == (i - 1) / 2) {
                curr = c2[i-1][j] / 2;
            } else {
                curr = c[i-1][j];
            }
            curr = curr * tree[j];
            curr %= mod;
            curr = curr * tree[i - j - 1];
            curr %= mod;
            tree[i] += curr;
            tree[i] %= mod;
        }
    }

    for (i = R; i <= N; ++i) {
        ans[i] = tree[i];
        // j is the size of the "invalid" subtree
        for (j = 1; j <= i - R; ++j) {
            ll del = c[i - R][j] * tree[j+1] % mod;
            del = del * ans[i - j];
            del %= mod;
            ans[i] = ans[i] - del;
            ans[i] %= mod;
            ans[i] += mod;
            ans[i] %= mod;
        }
    }

    printf("%lld\n", ans[N]);
    return 0;
}